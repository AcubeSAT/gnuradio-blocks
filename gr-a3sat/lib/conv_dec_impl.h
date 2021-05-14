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
             * \param binaryOptimalPath The optimal path converted to binary
             */
        private:
            static const int rate = 2;
            static const int constraintLength = 7;
            bool generator[2][7] = {{1, 1, 1, 1, 0, 0, 1},
                                    {1, 0, 1, 1, 0, 1, 1}};
            unsigned int paths[64];
            unsigned int pathMetric[64];
            unsigned int transmittedPaths[64];
            unsigned int branchMetric[64];
            bool binaryState[6] = {0};
            unsigned int nextState = 0;
            bool transmittedOne[7] = {0};
            bool transmittedZero[7] = {0};
            unsigned int branchMetricOne = 0;
            unsigned int branchMetricZero = 0;
            unsigned int pathMetricOne = 0;
            unsigned int pathMetricZero = 0;
            int temporaryState = 0;
            unsigned int optimalPath = 0;
            unsigned int optimalPathIndex = 0;
            unsigned int binaryOptimalPath[6] = {};

        public:
            conv_dec_impl();

            ~conv_dec_impl();

            int general_work(int noutput_items,
                             gr_vector_int &ninput_items,
                             gr_vector_const_void_star &input_items,
                             gr_vector_void_star &output_items);

            void forecast(int noutput_items, gr_vector_int &ninput_items_required);

            int calculate_path_metric(int rate,
                                      int constraint_length,
                                      bool state[],
                                      bool generator[][7],
                                      bool transmitted_symbol[]);
        };

    } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_CONV_DEC_IMPL_H */
