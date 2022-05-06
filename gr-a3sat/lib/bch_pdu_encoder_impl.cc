#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "bch_pdu_encoder_impl.h"

namespace gr {
    namespace a3sat {

        bch_pdu_encoder::sptr
        bch_pdu_encoder::make() {
            return gnuradio::get_initial_sptr
                    (new bch_pdu_encoder_impl());
        }

        /*
         * The private constructor
         */
        bch_pdu_encoder_impl::bch_pdu_encoder_impl()
                : gr::block("bch_pdu_encoder",
                            gr::io_signature::make(0, 0, 0),
                            gr::io_signature::make(0, 0, 0)) {
            // Create the idle pmt used for synchronization
            idle_seq = pmt::make_u8vector(32, 0);
            for (uint8_t i = 0; i < 16; i++) {
                pmt::u8vector_set(idle_seq, i * 2, 1);
            }

            // Add the start sequence to the transmitted CLTU
            memcpy(transmitted_cltu, cltu_header, 2);

            // Register message ports
            message_port_register_in(pmt::mp("acquisition"));
            message_port_register_in(pmt::mp("idle"));
            message_port_register_out(pmt::mp("pdu"));

            // Register message handlers
            set_msg_handler(pmt::mp("acquisition"),
                            [this](pmt::pmt_t msg) {
                                this->handle_acquired_sequence(msg);
                            });

            set_msg_handler(pmt::mp("idle"),
                            [this](pmt::pmt_t msg) {
                                this->handle_idle_sequence();
                            });
        }

        /*
         * Our virtual destructor.
         */
        bch_pdu_encoder_impl::~bch_pdu_encoder_impl() {
        }

        void bch_pdu_encoder_impl::handle_acquired_sequence(pmt::pmt_t message) {
            pmt::pmt_t b;
            static const uint8_t generator = 197;
            static const uint8_t bit_position[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
            static const uint8_t filler_bytes[] = {0x55, 0x55, 0x55, 0x55, 0x55, 0x55};
            if (pmt::is_blob(message)) {
                b = message;
            } else if (pmt::is_pair(message)) {
                b = pmt::cdr(message);
            } else {
                throw std::runtime_error(alias() + ": received a malformed pdu message");
            }

            uint16_t len = pmt::blob_length(b);

            float number_of_codewords = (static_cast < float > (len)) / 7;
            uint8_t *uncoded_frame_1 = (uint8_t *) pmt::blob_data(b);
            float temp = number_of_codewords - floor(number_of_codewords);
            uint8_t fill = static_cast < uint8_t >(round(temp * 7));
            memcpy(uncoded_frame_1 + fill, filler_bytes, 7 - fill);
            len = len + 7 - fill;


            for (int i = 0; i < len; i++) {
                for (int bit = 0; bit < 8; bit++) {
                    uncoded_frame[(i * 8) + 7 - bit] = (uint8_t) ((uncoded_frame_1[i] & bit_position[bit]) != 0x00);
                }
            }

            uint8_t *uncoded_curr = uncoded_frame;
            for (int i = 0; i < len / 7; i++) {
                uint8_t remainder = 0;
                uint8_t current_byte = 0;
                uint8_t temp = 0;

                memcpy(transmitted_cltu + 2 + i * n_bch / 8, uncoded_frame_1, sizeof(uint8_t) * k_bch / 8);

                for (int bytes = 0; bytes < k_bch / 8; bytes++) {
                    current_byte = 0;

                    for (int bit = 7; bit >= 0; bit--) {
                        temp = *uncoded_curr++;
                        current_byte |= temp << bit;
                    }

                    remainder ^= current_byte;
                    for (int position = 0; position < 8; position++) {
                        if ((remainder & 0x80) != 0) {
                            remainder ^= generator;
                            remainder <<= 1;
                        } else {
                            remainder <<= 1;
                        }
                    }
                }
                *(transmitted_cltu + 2 + (i + 1) * (n_bch / 8) - 1) = remainder;

            }

            memcpy(transmitted_cltu + 2 + len * n_bch / k_bch, cltu_trailer, 8);
            message_port_pub(pmt::mp("pdu"), pmt::init_u8vector(len, transmitted_cltu));
        }

        void bch_pdu_encoder_impl::handle_idle_sequence() {
            // Transmit idle
            message_port_pub(pmt::mp("pdu"), idle_seq);
        }
    } /* namespace a3sat */
} /* namespace gr */

