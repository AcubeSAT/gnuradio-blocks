#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "conv_dec_impl.h"
#include <iostream>
#include <cmath>

namespace gr {
    namespace a3sat {

        conv_dec::sptr
        conv_dec::make(bool soft_decision_decoding) {
            return gnuradio::get_initial_sptr
                    (new conv_dec_impl());
        }

        conv_dec_impl::conv_dec_impl()
                : gr::block("conv_dec",
                            gr::io_signature::make(1, 1, sizeof(float)),
                            gr::io_signature::make(1, 1, sizeof(bool))) {
            set_output_multiple(decodedWordLength);
        }

        conv_dec_impl::~conv_dec_impl() {
        }

        void
        conv_dec_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required) {
            ninput_items_required[0] = noutput_items * rate;
        }

        int
        conv_dec_impl::general_work (int noutput_items,
                                     gr_vector_int &ninput_items,
                                     gr_vector_const_void_star &input_items,
                                     gr_vector_void_star &output_items) {
            const float *in = (const float *) input_items[0];
            uint8_t *out = (uint8_t *) output_items[0];

            const uint8_t maxNumOfStates = static_cast<uint8_t>(pow(2, constraintLength - 2));

            memset(pathMetric, INT8_MAX, sizeof(pathMetric));
            memset(paths, 0, sizeof(paths));

            pathMetric[0] = 0;

            for (uint16_t inputItem = 0; inputItem < noutput_items; inputItem++) {

                memset(branchMetric, INT8_MAX, sizeof(branchMetric));
                memset(transmittedPaths, 0, sizeof(transmittedPaths));

                transmittedSymbol[0] = in[rate * inputItem];
                transmittedSymbol[1] = in[rate * inputItem + 1];

                for (uint8_t state = 0; state < pow(2, constraintLength - 1); state++) {
                    if (pathMetric[state] != INT8_MAX) {

                        /*!
                         * Converts the current state to binary array.
                         */
                        temporaryState = state;
                        for (uint8_t i = 0; i < constraintLength - 1; i++) {
                            if (temporaryState > 0) {
                                binaryState[constraintLength - i - 2] = temporaryState % 2;
                                temporaryState /= 2;
                            } else {
                                binaryState[constraintLength - i - 2] = 0;
                            }
                        }

                        /*!
                         * Performs pre-padding in the transmitted codeword based on the previous state.
                         * Then it calculates the corresponding branch metric for each case (0/ 1 transmission) for any of the possible next states.
                         * Finally it updates transmitted paths in the trellis diagram.
                         */
                        transmittedOne[0] = 1;
                        transmittedZero[0] = 0;

                        for (uint8_t index = 0; index < constraintLength - 1; index++) {
                            transmittedOne[index + 1] = binaryState[index];
                            transmittedZero[index + 1] = binaryState[index];
                        }

                        branchMetricOne = calculateBranchMetric(transmittedOne);
                        branchMetricZero = calculateBranchMetric(transmittedZero);

                        pathMetricOne = branchMetricOne + pathMetric[state];
                        nextState = (state >> 1) ^ maxNumOfStates;

                        if (branchMetric[nextState] > pathMetricOne) {
                            branchMetric[nextState] = pathMetricOne;
                            memcpy(transmittedPaths[nextState], paths[state],sizeof(paths[state]));
                            transmittedPaths[nextState][inputItem] = 1;
                        }

                        pathMetricZero = branchMetricZero + pathMetric[state];
                        nextState = state >> 1;

                        if (branchMetric[nextState] > pathMetricZero) {
                            branchMetric[nextState] = pathMetricZero;
                            memcpy(transmittedPaths[nextState], paths[state],sizeof(paths[state]));
                            transmittedPaths[nextState][inputItem] = 0;
                        }
                    }
                }
                memcpy(pathMetric, branchMetric, sizeof(branchMetric));
                memcpy(paths, transmittedPaths, sizeof(transmittedPaths));
            }

            /*!
             * Computes the path with the minimum path metric.
             */
            optimalPath = pathMetric[0];
            optimalPathIndex = 0;

            for (uint8_t path = 1; path < uint8_t(pow(2, (constraintLength - 1))); path++) {
                if (pathMetric[path] < optimalPath) {
                    optimalPath = pathMetric[path];
                    optimalPathIndex = path;
                }
            }

            for(uint16_t outIndex = 0; outIndex < noutput_items; outIndex++){
                *out = paths[optimalPathIndex][outIndex];
                out++;
            }

            consume_each(noutput_items);
            return noutput_items;
        }

        float conv_dec_impl::calculateBranchMetric(bool *state) {
            uint8_t parityBit = 0;
            float branchMetric_2 = 0.0;
            bool generator[2][7] = {{1, 1, 1, 1, 0, 0, 1}, {1, 0, 1, 1, 0, 1, 1}};

            voltageReference[0] = 0.0;
            voltageReference[1] = 1.0;

            for (uint8_t iGenerator = 0; iGenerator < rate; iGenerator++) {
                parityBit = 0;
                for (uint8_t stateBit = 0; stateBit < constraintLength; stateBit++) {
                    parityBit ^= state[stateBit] * generator[iGenerator][stateBit];
                }
                /*!
                 * xor operation with the iGenerator is used, so that the parity bit when generated from the second generator is inversed.
                 * e.x. (parityBit = 1) iGenerator=0: 1 ^ iGenerator = 1, iGenerator=1: 1 ^ iGenerator = 0
                 */
                branchMetric_2 += float(pow(voltageReference[parityBit^iGenerator] - transmittedSymbol[iGenerator], 2));
            }
            return branchMetric_2;
        }

    } /* namespace a3sat */
} /* namespace gr */
