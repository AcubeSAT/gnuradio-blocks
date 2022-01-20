#ifndef INCLUDED_A3SAT_LDPC_ENC_IMPL_H
#define INCLUDED_A3SAT_LDPC_ENC_IMPL_H

#include <a3sat/ldpc_enc.h>

namespace gr {
  namespace a3sat {

    class ldpc_enc_impl : public ldpc_enc
    {
     private:

     public:
      ldpc_enc_impl();
      ~ldpc_enc_impl();
    
      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

    };

  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_LDPC_ENC_IMPL_H */

