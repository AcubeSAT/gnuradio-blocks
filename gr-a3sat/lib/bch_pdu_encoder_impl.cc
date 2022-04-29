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

        idle_seq = pmt::make_u8vector(32, 0);
        for (uint8_t i = 0; i < 16; i++){
            pmt::u8vector_set(idle_seq, i*2, 1);
        }

        message_port_register_in(pmt::mp("acquisition"));
        message_port_register_in(pmt::mp("idle"));
        message_port_register_out(pmt::mp("pdu"));

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

        if (pmt::is_blob(message)) {
            b = message;
        } else if (pmt::is_pair(message)) {
            b = pmt::cdr(message);
        } else {
            throw std::runtime_error(alias() + ": received a malformed pdu message");
        }

        size_t len = pmt::blob_length(b);
        uint8_t *d = (uint8_t *) pmt::blob_data(b);

        // DO BCH
        message_port_pub(pmt::mp("pdu"), pmt::init_u8vector(len, d));
    }

    void bch_pdu_encoder_impl::handle_idle_sequence(){
        // Transmit idle
        message_port_pub(pmt::mp("pdu"), idle_seq);
    }
  } /* namespace a3sat */
} /* namespace gr */

