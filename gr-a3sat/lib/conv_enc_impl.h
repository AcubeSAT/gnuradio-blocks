/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_CONV_ENC_IMPL_H
#define INCLUDED_A3SAT_CONV_ENC_IMPL_H

#include <a3sat/conv_enc.h>
#include <iostream>

namespace gr {
    namespace a3sat {
/*!
 * \brief Implements a convolutional encoder
 * \ingroup a3sat
 *
 * Input: 2048 bit frame
 * Output: Encoded 4096 bit frame
 */
        class conv_enc_impl : public conv_enc
        {
            /*!
             * \param generator The generator polynomials used for the encoding, but inversed
             * \param rate The number of the generator polynomials
             * \param constraintLength The length of each generator polynomial
             */

        private:
            bool generator[2][7] = {{1, 0, 0, 1, 1, 1, 1}, {1, 1, 0, 1, 1, 0, 1}};
            unsigned int rate;
            unsigned int constraintLength;

        public:
            conv_enc_impl(unsigned int rate, unsigned int constraint_length);
            ~conv_enc_impl();

            int general_work(int noutput_items,
                             gr_vector_int &ninput_items,
                             gr_vector_const_void_star &input_items,
                             gr_vector_void_star &output_items);

            void forecast(int noutput_items,
                          gr_vector_int &ninput_items_required);

        };

    } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_CONV_ENC_IMPL_H */