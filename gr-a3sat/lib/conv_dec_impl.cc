/*
 * Copyright 2021 SpaceDot.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <climits>
#include "conv_dec_impl.h"
#include <iostream>

namespace gr {
    namespace a3sat {

        conv_dec::sptr
        conv_dec::make(bool soft_decision_decoding)
        {
            return gnuradio::get_initial_sptr
                    (new conv_dec_impl());
        }

        conv_dec_impl::conv_dec_impl()
                : gr::block("conv_dec",
                            gr::io_signature::make(1, 1, sizeof(bool)),
                            gr::io_signature::make(1, 1, sizeof(char))) {

            set_output_multiple(6);
        }

        conv_dec_impl::~conv_dec_impl()
        {
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
            const bool *in = (const bool *) input_items[0];
            unsigned int *out = (unsigned int *) output_items[0];

            for (int i = 0; i < pow(2, constraintLength - 1); i++) {
                pathMetric[i] = UINT_MAX;
                paths[i] = 0;
            }

            pathMetric[0] = 0;

            for (int inputItem = 0; inputItem < noutput_items; inputItem++) {

                for (int i = 0; i < pow(2, constraintLength - 1); i++) {
                    branchMetric[i] = UINT_MAX;
                    transmittedPaths[i] = 0;
                }

                bool transmitted_symbol[2] = {in[rate * inputItem], in[rate * inputItem + 1]};

                for (int state = 0; state < pow(2, constraintLength - 1); state++) {
                    if (pathMetric[state] != UINT_MAX) {

                        temporaryState = state;
                        for (int j = 1; j < constraintLength; j++) {
                            if (temporaryState > 0) {
                                binaryState[constraintLength - j - 1] = temporaryState % 2;
                                temporaryState = temporaryState / 2;
                            } else binaryState[constraintLength - j - 1] = 0;
                        }

                        transmittedOne[0] = 1;
                        transmittedZero[0] = 0;

                        for (int i = 0; i < constraintLength - 1; i++) {
                            transmittedOne[i + 1] = binaryState[i];
                            transmittedZero[i + 1] = binaryState[i];
                        }

                        branchMetricOne = 0;
                        branchMetricZero = 0;

                        branchMetricOne = calculate_path_metric(rate, constraintLength, transmittedOne, generator, transmitted_symbol);
                        branchMetricZero = calculate_path_metric(rate, constraintLength, transmittedZero, generator, transmitted_symbol);

                        pathMetricOne = pow(branchMetricOne, 2) + pathMetric[state];
                        nextState = (state >> 1) ^ int(pow(2, constraintLength - 2));

                        if (branchMetric[nextState] > pathMetricOne) {
                            branchMetric[nextState] = pathMetricOne;
                            transmittedPaths[nextState] = (paths[state] << 1) ^ 1;
                        }

                        pathMetricZero = pow(branchMetricZero, 2) + pathMetric[state];
                        nextState = state >> 1;

                        if (branchMetric[nextState] > pathMetricZero) {
                            branchMetric[nextState] = pathMetricZero;
                            transmittedPaths[nextState] = paths[state] << 1;
                        }
                    }
                }
                memcpy(pathMetric, branchMetric, sizeof(branchMetric));
                memcpy(paths, transmittedPaths, sizeof(transmittedPaths));
            }

            optimalPath = pathMetric[0];
            optimalPathIndex = 0;

            for (int i = 1; i < int(pow(2, (constraintLength - 1))); i++) {
                if (pathMetric[i] < optimalPath && paths[i] != 0) {
                    optimalPath = pathMetric[i];
                    optimalPathIndex = i;
                }
            }

            for (int j = 0; j < noutput_items; j++) {
                if (paths[optimalPathIndex] > 0) {
                    binaryOptimalPath[noutput_items - j - 1] = paths[optimalPathIndex] % 2;
                    paths[optimalPathIndex] = paths[optimalPathIndex] / 2;
                } else binaryOptimalPath[noutput_items - j - 1] = 0;
            }

            for(int outIndex = 0; outIndex < noutput_items; outIndex++){
                *out = binaryOptimalPath[outIndex];
                out++;
            }

            consume_each(noutput_items);
            return noutput_items;
        }

        int conv_dec_impl::calculate_path_metric(int rate, int constraint_length, bool *state, bool (*generator)[7], bool *transmittedSymbol) {
            int parityBit = 0;
            int pathMetric = 0;

            for (int gen_k = 0; gen_k < rate; gen_k++) {
                parityBit = 0;
                for (int state_bit = 0; state_bit < constraint_length; state_bit++) {
                    parityBit ^= state[state_bit] * generator[gen_k][state_bit];
                }
                pathMetric += abs(parityBit - transmittedSymbol[gen_k]);
            }
            return pathMetric;
        }

    } /* namespace a3sat */
} /* namespace gr */
