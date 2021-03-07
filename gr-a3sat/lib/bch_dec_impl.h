/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_BCH_DEC_IMPL_H
#define INCLUDED_A3SAT_BCH_DEC_IMPL_H

#include <a3sat/bch_dec.h>

namespace gr {
  namespace a3sat {

    class bch_dec_impl : public bch_dec
    {
     private:

     public:
      bch_dec_impl();
      ~bch_dec_impl();

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

    };

  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_BCH_DEC_IMPL_H */

