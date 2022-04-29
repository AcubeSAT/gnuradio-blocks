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

    }

    void bch_pdu_encoder_impl::handle_idle_sequence(){

    }
  } /* namespace a3sat */
} /* namespace gr */

