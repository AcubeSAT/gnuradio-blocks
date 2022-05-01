#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "bch_pdu_encoder_impl.h"

namespace gr {
  namespace a3sat {

    bch_pdu_encoder::sptr
    bch_pdu_encoder::make()
    {
      return gnuradio::get_initial_sptr
        (new bch_pdu_encoder_impl());
    }

    /*
     * The private constructor
     */
    bch_pdu_encoder_impl::bch_pdu_encoder_impl()
      : gr::block("bch_pdu_encoder",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0))
    {
        // Create the idle pmt used for synchronization
        idle_seq = pmt::make_u8vector(32, 0);
        for (uint8_t i = 0; i < 16; i++){
            pmt::u8vector_set(idle_seq, i*2, 1);
        }

        // Add the start sequence to the transmitted CLTU
        uint8_t cltu_header[2] = {0b11101011, 0b10010000};
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
    bch_pdu_encoder_impl::~bch_pdu_encoder_impl()
    {
    }

    void bch_pdu_encoder_impl::handle_acquired_sequence(pmt::pmt_t message){
        pmt::pmt_t b;
        static const uint8_t generator = 197;
        static const uint8_t bit_position[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

        if (pmt::is_blob(message)) {
            b = message;
        } else if (pmt::is_pair(message)) {
            b = pmt::cdr(message);
        } else {
            throw std::runtime_error(alias() + ": received a malformed pdu message");
        }

        uint16_t len = pmt::blob_length(b);

        uint8_t *uncoded_frame = (uint8_t *) pmt::blob_data(b);

        // Determine how many codeblocks there are in the p
        uint16_t num_of_codeblocks = len/56;

        // Iterate over the yet uncoded codeblocks
        for (uint16_t codeblock_i; codeblock_i < num_of_codeblocks; codeblock_i++){
            uint8_t encoded_codeblock[64];

        }

        uint8_t* uncoded_curr = uncoded_frame;
        // skip header of cltu
        uint8_t* transmitted_cltu_codeblocks_curr = transmitted_cltu + 2;

        for (int i = 0; i < len; i += n_bch) {
            uint8_t remainder = 0;
            uint8_t current_byte = 0;
            uint8_t temp = 0;

            memcpy(transmitted_cltu_codeblocks_curr, uncoded_curr, sizeof(uint8_t) * k_bch);
            transmitted_cltu_codeblocks_curr += k_bch;

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
            for (int bit = 7; bit >= 0; bit--) {
                *transmitted_cltu_codeblocks_curr = (uint8_t) (remainder & bit_position[bit]) != 0x00;
                transmitted_cltu_codeblocks_curr++;
            }
        }

        // TODO: Add trailer
        message_port_pub(pmt::mp("pdu"), pmt::init_u8vector(len, transmitted_cltu));
    }

    void bch_pdu_encoder_impl::handle_idle_sequence(){
        // Transmit idle
        message_port_pub(pmt::mp("pdu"), idle_seq);
    }
  } /* namespace a3sat */
} /* namespace gr */

