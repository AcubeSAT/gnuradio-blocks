#ifndef INCLUDED_A3SAT_BCH_PDU_ENCODER_IMPL_H
#define INCLUDED_A3SAT_BCH_PDU_ENCODER_IMPL_H

#include <a3sat/bch_pdu_encoder.h>
#include <pmt/pmt.h>

namespace gr {
  namespace a3sat {

    class bch_pdu_encoder_impl : public bch_pdu_encoder
    {
     private:
        void handle_acquired_sequence(pmt::pmt_t message);
        void handle_idle_sequence();
        bool acquiring_signal = false;

     public:
      bch_pdu_encoder_impl();
      ~bch_pdu_encoder_impl();

      pmt::pmt_t encode(
                pmt::pmt_t acquisition_sequence
                );

    };

  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_BCH_PDU_ENCODER_IMPL_H */

