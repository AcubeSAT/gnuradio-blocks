#ifndef INCLUDED_A3SAT_CONV_DEC_IMPL_H
#define INCLUDED_A3SAT_CONV_DEC_IMPL_H

#include <a3sat/conv_dec.h>

namespace gr {
  namespace a3sat {
/*!
 * \brief Implements a convolutional decoder
 * \ingroup a3sat
 *
 * Input: Convolutional encoded 4096 bit frame
 * Output: Decoded 2048 bit frame
 */
    class conv_dec_impl : public conv_dec
    {
        /*!
         * \param rate The number of the generator polynomials used for the encoding.
         * \param constraint_length The length of each generator polynomial used for the encoding.
         */
     private:
        unsigned int rate;
        unsigned int constraint_length;

     public:
      conv_dec_impl(unsigned int rate, unsigned int constraint_length);
      ~conv_dec_impl();

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

      void forecast(int noutput_items, gr_vector_int &ninput_items_required);

    };

  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_CONV_DEC_IMPL_H */

