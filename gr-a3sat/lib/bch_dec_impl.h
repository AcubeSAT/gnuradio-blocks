#ifndef INCLUDED_A3SAT_BCH_DEC_IMPL_H
#define INCLUDED_A3SAT_BCH_DEC_IMPL_H

#include <a3sat/bch_dec.h>
#include <unordered_map>

namespace gr {
    namespace a3sat {
        /**
         * The decoder of the BCH(56,64) code that is specified in CCSDS 231.0-B-3
         * The decoder calculates the syndromes and then finds the error location in
         * the codeword when there is at most one error in the codeword and then corrects
         * it.
         **/
        class bch_dec_impl : public bch_dec {
        private:
            /**
             * The input number of bits to the decoder.
             */
            static const uint8_t n_bch = 64;

            /**
            * The output number of bits of the decoder.
            */
            static const uint8_t k_bch = 56;

            /**
            * The hash map that assigns the syndromes to the bit error location.
            */
            typedef std::unordered_map<int, int> hash;
            static hash syndromes_hash;
        public:

            /**
             * Initializes an object of the class and sets the output to be a multiple of k_bch.
             */
            bch_dec_impl();
            /**
            * Destroys the object of the class.
            */

            ~bch_dec_impl();

            /**
             * @brief Defines the required input number of bits to produce a certain number of output bits
             * @details As the code is a BCH(56,64), input/output = 64/56
             * @param noutput_items The number of output bits
             * @param ninput_items_required The number of input bits needed to produce noutput_items
             * @return void
             */
            void forecast(int noutput_items, gr_vector_int &ninput_items_required);

            /**
             * Performs the decoding of the input data. Due to the forecast and set output multiple functions, the input
             * data is a multiple of n_bch. The input data is divided in segments of n_bch bits and  syndrome decoding
             * is performed on these segments. The syndrome indicates the error location if there is at most one error.
             * The decoder corrects that error and outputs the first 56 bits of the corrected n_bch segment. If there is
             * more than one errors in a segment, the decoding stops and no more decoding is performed on the input data.
             *
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

#endif /* INCLUDED_A3SAT_BCH_DEC_IMPL_H */

