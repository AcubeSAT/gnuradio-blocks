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
 * @brief The encoder of the convolutional code of rate 1/2 bits ber symbol as specified in CCSDS 131.0-B-3.
 *        The generator polynomials of the encoder are g1(x) = x^6 + x^5 + x^4 + x^3 + 1    &   g2(x) = x^6 + x^4 + x^3 + x + 1
 *        The bit generated from the second generator is inversed as described in 3.3.2 section of CCSDS 131.0-B-3.
 * @ingroup a3sat
 *
 * Input: 2048 bit frame
 * Output: Encoded 4096 bit frame
 */
        class conv_enc_impl : public conv_enc
        {
            /**
             * @param generator The generator polynomials used for the encoding, but inversed
             * @param rate The number of the generator polynomials
             * @param constraintLength The length of each generator polynomial
             * @param decodedCodewordLength The length of the encoded codeword
             */
        private:
//            inline static const bool generator[2][7] = {{1, 0, 0, 1, 1, 1, 1}, {1, 1, 0, 1, 1, 0, 1}};
//            bool generator[2][7];
            static const uint8_t rate = 2;
            static const uint8_t constraintLength = 7;
            static const uint16_t encodedCodewordLength = 4096;

        public:
            /**
             * Initializes an object of the class and sets the output to be a multiple of the encodedCodewordLength.
             */
            conv_enc_impl();

            /*!
            * Destroys the object of the class.
            */
            ~conv_enc_impl();

            /*!
             * @brief Performs the encoding of the input data.
             * Due to the forecast and set output multiple functions, the input data is a multiple of the output data and the rate of the encoder.
             * The sliding window of the encoder contains 7 (constraintLength) bits and 2 (rate) parity bits are produced, by multiplying the message bits
             * with each of the generator polynomials.
             * @param noutput_items The number of output bits
             * @param ninput_items The number of input bits on each port
             * @param input_items The input buffer
             * @param output_items The output buffer
             * @return noutput_items
             */
            int general_work(uint16_t noutput_items,
                             gr_vector_int &ninput_items,
                             gr_vector_const_void_star &input_items,
                             gr_vector_void_star &output_items);

            /*!
             * @brief Defines the required input number of bits to produce a certain number of output bits.
             * @details As the code is a Convolutional of rate 1/2, input/output = 1/2
             * @param noutput_items
             * @param ninput_items_required
             */
            void forecast(uint16_t noutput_items,
                          gr_vector_int &ninput_items_required);

        };

    } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_CONV_ENC_IMPL_H */