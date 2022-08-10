
#ifndef INCLUDED_A3SAT_GMSK_PRECODER_IMPL_H
#define INCLUDED_A3SAT_GMSK_PRECODER_IMPL_H

#include <a3sat/gmsk_precoder.h>

namespace gr {
  namespace a3sat {

    class gmsk_precoder_impl : public gmsk_precoder
    {
     private:
      bool prev_bit = 1;

     public:
      gmsk_precoder_impl();
      ~gmsk_precoder_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

    };

  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_GMSK_PRECODER_IMPL_H */

