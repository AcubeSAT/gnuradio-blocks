/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_BCH_ENC_IMPL_H
#define INCLUDED_A3SAT_BCH_ENC_IMPL_H

#include <a3sat/bch_enc.h>

namespace gr {
  namespace a3sat {

    class bch_enc_impl : public bch_enc
    {
     private:
        static const unsigned int n_bch=64;
        static const unsigned int k_bch=56;
     public:
        bch_enc_impl();
      ~bch_enc_impl();
      void forecast(int noutput_items, gr_vector_int& ninput_items_required);
      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_BCH_ENC_IMPL_H */

