/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_CONV_DEC_IMPL_H
#define INCLUDED_A3SAT_CONV_DEC_IMPL_H

#include <a3sat/conv_dec.h>

namespace gr {
    namespace a3sat {
/*!
 * \brief The soft decision decoder of the convolutional code of rate 1/2 bits ber symbol as specified in CCSDS 131.0-B-3.
 * \ingroup a3sat
 *
 * Input: Convolutional encoded 4096 bit frame
 * Output: Decoded 2048 bit frame
 */
        class conv_dec_impl : public conv_dec {
            /*!
             * \param rate Number of the generator polynomials used for the encoding
             * \param constraintLength Length of each generator polynomial used for the encoding
             * \param generator The generator polynomials used for the encoding
             * \param transmittedSymbol The received bits at each timestep
             * \param paths The paths of the trellis
             * \param pathMetric The path metric of each path of the trellis
             * \param transmittedPaths The paths calculated in each timestep t
             * \param branchMetric The branch metric of each state in timestep t
             * \param binaryState Current state in binary form
             * \param nextState The following state in each case of 1 / 0 transmitted
             * \param transmittedOne State if 1 was transmitted
             * \param transmittedZero State if 0 was transmitted
             * \param branchMetricOne The “distance” between the transmitted symbol and the received symbol in case 1 was the next transmitted bit
             * \param branchMetricZero The “distance” between the transmitted symbol and the received symbol in case 0 was the next transmitted bit
             * \param temporaryState Helpful variable used for the conversion of variable state to binary
             * \param optimalPath The path with the minimum path metric
             * \param optimalPathIndex The index of the path with the minimum path metric
             */
        private:
            static const uint8_t rate = 2;
            static const uint8_t constraintLength = 7;
            static const uint16_t decodedWordLength = 2048;
            float transmittedSymbol[2];
            bool paths[64][decodedWordLength];
            double pathMetric[64];
            bool transmittedPaths[64][decodedWordLength];
            double branchMetric[64];
            bool binaryState[6];
            uint8_t nextState;
            bool transmittedOne[7];
            bool transmittedZero[7];
            double branchMetricOne;
            double branchMetricZero;
            double pathMetricOne;
            double pathMetricZero;
            uint8_t temporaryState;
            double optimalPath;
            uint8_t optimalPathIndex;
            float voltageReference[2];

        public:
            /**
             * Initializes an object of the class and sets the output to be a multiple of the encodedCodewordLength.
             */
            conv_dec_impl();

            /*!
            * Destroys the object of the class.
            */
            ~conv_dec_impl();

            /*!
             * @brief Performs the decoding of the input data.
             * Due to the forecast and set output multiple functions, the input data is a multiple of the output data divided by the rate of the encoder.
             * The decoder consists of two main steps. It calculates the branch metric for the next set of parity bits, and computes the path metric for the next column.
             * In the end a Trellis diagram is created and the path with the minimum path metric is selected as the transmitted codeword.
             * @param noutput_items
             * @param ninput_items
             * @param input_items
             * @param output_items
             * @return noutput_items
             */
            int general_work(int noutput_items,
                             gr_vector_int &ninput_items,
                             gr_vector_const_void_star &input_items,
                             gr_vector_void_star &output_items);

            /*!
             * @brief Defines the required input number of bits to produce a certain number of output bits
             * @details As the code is a Convolutional of rate 1/2, input/output = 2
             * @param noutput_items
             * @param ninput_items_required
             */
            void forecast(int noutput_items, gr_vector_int &ninput_items_required);

            /*!
             * @brief Calculates the “distance” between the transmitted and the received symbols.
             * It calculates the parity bits that should be produced given a specific state of the encoder
             * and compares them with the received bits. Then it calculates the absolute difference between them.
             * (i.e. If the received bits are 00 and the calculated parity bits are 11, the branch metric would be 2.)
             * @param state The current sequence of bits which will be multiplied with the generator polynomials in order to produce the parity bits.
             * @return The calculated branch metric
             */
            float calculateBranchMetric(bool *state);
        };

    } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_CONV_DEC_IMPL_H */
