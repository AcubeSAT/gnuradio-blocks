/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_CONV_DEC_IMPL_H
#define INCLUDED_A3SAT_CONV_DEC_IMPL_H

#include <a3sat/conv_dec.h>
#include <unordered_map>

namespace gr {
    namespace a3sat {
/*!
 * \brief Implements a convolutional Viterbi soft decision decoder
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
             * \param branchMetricOne Branch metric if 1 was transmitted
             * \param branchMetricZero Branch metric if 0 was transmitted
             * \param temporaryState Helpful variable used for the conversion of variable state to binary
             * \param optimalPath The path with the minimum path metric
             * \param optimalPathIndex The index of the path with the minimum path metric
             */
        private:
            static const int rate = 2;
            static const int constraintLength = 7;
            bool generator[2][7] = {{1, 1, 1, 1, 0, 0, 1},
                                    {1, 0, 1, 1, 0, 1, 1}};
            bool transmittedSymbol[2];
            unsigned int paths[64][6];
            unsigned int pathMetric[64];
            unsigned int transmittedPaths[64][6];
            unsigned int branchMetric[64];
            bool binaryState[6];
            unsigned int nextState;
            bool transmittedOne[7];
            bool transmittedZero[7];
            unsigned int branchMetricOne;
            unsigned int branchMetricZero;
            unsigned int pathMetricOne;
            unsigned int pathMetricZero;
            int temporaryState;
            unsigned int optimalPath;
            unsigned int optimalPathIndex;

        public:
            conv_dec_impl();

            ~conv_dec_impl();

            int general_work(int noutput_items,
                             gr_vector_int &ninput_items,
                             gr_vector_const_void_star &input_items,
                             gr_vector_void_star &output_items);

            void forecast(int noutput_items, gr_vector_int &ninput_items_required);

            /*
             * @brief Calculates the branch metric to the next state.
             */
            int calculateBranchMetric(bool *state);
        };

    } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_CONV_DEC_IMPL_H */
