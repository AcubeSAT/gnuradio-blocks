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
            char *out = (char *) output_items[0];

            memset(pathMetric, UINT_MAX, sizeof(pathMetric));
            memset(paths, 0, sizeof(paths));

            pathMetric[0] = 0;

            for (int inputItem = 0; inputItem < noutput_items; inputItem++) {

                memset(branchMetric, UINT_MAX, sizeof(branchMetric));
                memset(transmittedPaths, 0, sizeof(transmittedPaths));

                transmittedSymbol[0] = in[rate * inputItem];
                transmittedSymbol[1] = in[rate * inputItem + 1];

                for (int state = 0; state < pow(2, constraintLength - 1); state++) {
                    if (pathMetric[state] != UINT_MAX) {

                        /* TODO: Implement the below conversion of state to binary form using hashMaps */
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

                        branchMetricOne = calculateBranchMetric(transmittedOne);
                        branchMetricZero = calculateBranchMetric(transmittedZero);

                        pathMetricOne = pow(branchMetricOne, 2) + pathMetric[state];
                        nextState = (state >> 1) ^ int(pow(2, constraintLength - 2));

                        if (branchMetric[nextState] > pathMetricOne) {
                            branchMetric[nextState] = pathMetricOne;
                            memcpy(transmittedPaths[nextState], paths[state],sizeof(paths[state]));
                            transmittedPaths[nextState][inputItem] = 1;
                        }

                        pathMetricZero = pow(branchMetricZero, 2) + pathMetric[state];
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

            optimalPath = pathMetric[0];
            optimalPathIndex = 0;

            for (int i = 1; i < int(pow(2, (constraintLength - 1))); i++) {
                if (pathMetric[i] < optimalPath) {
                    optimalPath = pathMetric[i];
                    optimalPathIndex = i;
                }
            }

            for(int outIndex = 0; outIndex < noutput_items; outIndex++){
                *out = paths[optimalPathIndex][outIndex];
                out++;
            }

            consume_each(noutput_items);
            return noutput_items;
        }

        int conv_dec_impl::calculateBranchMetric(bool *state) {
            int parityBit = 0;
            int branchMetric = 0;

            for (int iGenerator = 0; iGenerator < rate; iGenerator++) {
                parityBit = 0;
                for (int stateBit = 0; stateBit < constraintLength; stateBit++) {
                    parityBit ^= state[stateBit] * generator[iGenerator][stateBit];
                }
                branchMetric += abs(parityBit - transmittedSymbol[iGenerator]);
            }
            return branchMetric;
        }

    } /* namespace a3sat */
} /* namespace gr */
