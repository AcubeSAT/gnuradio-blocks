#ifndef INCLUDED_A3SAT_CONV_ENC_IMPL_H
#define INCLUDED_A3SAT_CONV_ENC_IMPL_H

#include <a3sat/conv_enc.h>

namespace gr {
  namespace a3sat {

    class conv_enc_impl : public conv_enc
    {
     private:

     public:
      conv_enc_impl(bool puncturing_enabled);
      ~conv_enc_impl();

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

    };

  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_CONV_ENC_IMPL_H */

