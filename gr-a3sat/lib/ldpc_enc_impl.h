#ifndef INCLUDED_A3SAT_LDPC_ENC_IMPL_H
#define INCLUDED_A3SAT_LDPC_ENC_IMPL_H

#include <a3sat/ldpc_enc.h>
#include <a3sat/paritiesEncoder.h>

namespace gr {
    namespace a3sat {

        /**
         * LDPC Encoder with Generator Matrix (5120, 1024) based on CCSD 131.1-1-O-1
         */
        class ldpc_enc_impl : public ldpc_enc {
        private:
            /**
             * the number of rows with square quasi-cyclic matrices in the Generator Matrix
             */
            static const uint8_t generatorRows = 32;

            /**
             * the number of columns with square quasi-cyclic matrices in the Generator Matrix
             */
            static const uint8_t generatorColumns = 8;

            /**
             * the size of each square quasi-cyclic matrix
             */
            static const uint8_t sizeSquareCyclicMatrix = 128;

            static const uint16_t sizeParity = 16362; //check

            /**
             * the position of the Parity Bits in the Generator Matrix (Identity matrix excluded). Since the Generator Matrix
             * consists of square cyclic block matrices, only the parities in the first line of each sub-matrix have been kept
             */
            uint16_t* rowsParityBits = parityBits;

            /**
             * the total number of square quasi-cyclic matrices starting from 0
             */
            static const int totalQuasiCyclicMatrices = generatorColumns * generatorRows;

            /**
             * the positions in vector rowsParityBits where the parities belong to a new block matrix.
             */
            uint16_t* positionRows = positionParities;

            /**
             * size of the initial message
             */
            static const int sizeInitialMessage = 4096;

            /**
             * size of the encoded message.
             */
            static const int sizeEncodedMessage = generatorColumns * sizeSquareCyclicMatrix;

            /**
             * size of the full message that will be transited consisting of the initial message and the encoded message
             */
            static const int sizeMessage = sizeInitialMessage + sizeEncodedMessage;


        public:

            /**
             * Class initialiser. Sets the output to be multiple of sizeInitialMessage
             */
            ldpc_enc_impl();

            /**
             * Class Destructor
             */
            ~ldpc_enc_impl() override;

            /**
             * Defines the required input number of bits to produce a certain number of output bits
             * @param noutput_items The number of output bits
             * @param ninput_items_required The number of input bits needed to produce noutput_items
             */
            void forecast(int noutput_items, gr_vector_int &ninput_items_required);

            /**
             * The encoding of the initial message
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

#endif /* INCLUDED_A3SAT_LDPC_ENC_IMPL_H */

