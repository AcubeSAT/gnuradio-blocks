/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_BCH_ENC_IMPL_H
#define INCLUDED_A3SAT_BCH_ENC_IMPL_H

#include <a3sat/bch_enc.h>
#include <unordered_map>

namespace gr {
    namespace a3sat {
        /**
         * The encoder of the BCH(56,64) code that is specified in CCSDS 231.0-B-3
         * The generator polynomial of the encoder is g(x) = x^7 + x^6 + x^2 + 1
         **/
        class bch_enc_impl : public bch_enc {
        private:
            /**
             * The output number of bits of the encoder.
             */
            static const uint8_t n_bch = 64;

            /**
             * The input number of bits to the encoder.
             */
            static const uint8_t k_bch = 56;

        public:

            /**
             * Initializes an object of the class and sets the output to be a multiple of n_bch.
             */
            bch_enc_impl();
            /**
            * Destroys the object of the class.
            */

            ~bch_enc_impl();

            /**
             * @brief Defines the required input number of bits to produce a certain number of output bits
             * @details As the code is a BCH(56,64), input/output = 56/64
             * @param noutput_items The number of output bits
             * @param ninput_items_required The number of input bits needed to produce noutput_items
             * @return void
             */

            void forecast(int noutput_items, gr_vector_int &ninput_items_required);

            /**
             * Performs the encoding of the input data. Due to the forecast and set output multiple functions, the input
             * data is a multiple of k_bch. The input data is divided in segments of k_bch bits and performs polynomial
             * division with g(x) on these segments. The division is performed by byte (7 bytes in total). The 1 byte
             * remainder (7 bits + 1 that is always zero) is appended to the end of each segment and results in the
             * n_bch codewords.
             * @param noutput_items The number of output bits
             * @param ninput_items The number of input bits on each port
             * @param input_items The input buffer
             * @param output_items The output buffer
             * @return noutput_items
             */


            int general_work(int noutput_items,
                             gr_vector_int &ninput_items,
                             gr_vector_const_void_star &input_items,
                             gr_vector_void_star &output_items);
        };

    } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_BCH_ENC_IMPL_H */

