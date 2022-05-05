#ifndef INCLUDED_A3SAT_BCH_PDU_ENCODER_IMPL_H
#define INCLUDED_A3SAT_BCH_PDU_ENCODER_IMPL_H

#include <a3sat/bch_pdu_encoder.h>
#include <pmt/pmt.h>

namespace gr {
  namespace a3sat {
      const uint16_t MAX_PACKET_SIZE = 512;

    class bch_pdu_encoder_impl : public bch_pdu_encoder
    {
     private:

        /**
             * The output number of bits of the encoder.
         */
        static const uint8_t n_bch = 64;

        /**
         * The input number of bits to the encoder.
         */
        static const uint8_t k_bch = 56;

        /**
         * PMT to be transmitted in between frames for synchronization purposes
         */
        pmt::pmt_t idle_seq;

        /**
         * Buffer of the transmitted CLTU
         */
        uint8_t transmitted_cltu[MAX_PACKET_SIZE];
        uint8_t uncoded_frame[MAX_PACKET_SIZE*8];

        void handle_acquired_sequence(pmt::pmt_t message);
        void handle_idle_sequence();

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

