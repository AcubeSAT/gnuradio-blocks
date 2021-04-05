/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_CONV_ENC_IMPL_H
#define INCLUDED_A3SAT_CONV_ENC_IMPL_H

#include <a3sat/conv_enc.h>
#include <iostream>

namespace gr {
  namespace a3sat {

    class conv_enc_impl : public conv_enc
    {
     private:
        unsigned int rate;
        unsigned int constraint_length;

    public:
      conv_enc_impl(unsigned int rate, unsigned int constraint_length);
      ~conv_enc_impl();

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

      void forecast(int noutput_items,
            gr_vector_int &ninput_items_required);

      int get_rate();
      int get_constraint_length();

    };

  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_CONV_ENC_IMPL_H */