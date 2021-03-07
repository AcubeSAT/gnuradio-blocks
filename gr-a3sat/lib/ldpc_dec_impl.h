/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_LDPC_DEC_IMPL_H
#define INCLUDED_A3SAT_LDPC_DEC_IMPL_H

#include <a3sat/ldpc_dec.h>

namespace gr {
  namespace a3sat {

    class ldpc_dec_impl : public ldpc_dec
    {
     private:

     public:
      ldpc_dec_impl();
      ~ldpc_dec_impl();

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

    };

  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_LDPC_DEC_IMPL_H */

