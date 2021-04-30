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
        static const uint16_t parity_Rows[];
        static const uint16_t position_Rows[];
        static const uint16_t parity_Columns[];
        static const uint16_t position_Columns[];
        static const uint16_t block_rows = 8;
        static const uint16_t block_columns = 32;
        constexpr static const double noise_var = 0.5;
        static const uint16_t size_message = 1024;
        static const uint16_t size_parity; // is equal to length(parity_Rows)
        static const uint16_t width_parity_matrix = 4096;
        static const uint16_t height_parity_matrix = 1024;

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

