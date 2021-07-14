/*
 * Copyright 2021 SpaceDot.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ldpc_dec_impl.h"
#include <cmath>

namespace gr {
    namespace a3sat {

        ldpc_dec::sptr
        ldpc_dec::make() {
            return gnuradio::get_initial_sptr
                    (new ldpc_dec_impl());
        }

        ldpc_dec_impl::ldpc_dec_impl()
                : gr::block("ldpc_dec",
                            gr::io_signature::make(5120, 5120, sizeof(double)),
                            gr::io_signature::make(4096, 4096, sizeof(bool))) {}

        void ldpc_dec_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required) {
            ninput_items_required[0] = (noutput_items / sizeInitialMessage) * sizeReceivedMessage;
        }


        ldpc_dec_impl::~ldpc_dec_impl() {
        }

        bool ldpc_dec_impl::checkDecoder(const bool decodedMessage[sizeInitialMessage]) {

            uint8_t totalSum = 0;
       /*     for (int i = 0; i < sizePositionRows; i++) {
                uint8_t thisParity;
                uint8_t nextParity;
                if (positionRows[i] != positionRows[sizePositionRows - 1]) {
                    thisParity = positionRows[i];
                    nextParity = positionRows[i + 1];

                } else {
                    thisParity = positionRows[i];
                    nextParity = positionRows[sizePositionRows - 1] + 1;
                }
                uint8_t lengthParity = nextParity - thisParity;
                for (int j = 0; j < lengthParity; j++) {
                    uint8_t paritiy = rowsParityBits[thisParity + j];
                    totalSum ^= decodedMessage[paritiy];
                }
            }*/
            if (totalSum != 0)
            {
                return true;
            }else {
                return false;
            }

        }

        int
        ldpc_dec_impl::general_work(int noutput_items,
                                    gr_vector_int &ninput_items,
                                    gr_vector_const_void_star &input_items,
                                    gr_vector_void_star &output_items) {
            const auto *in = (const double *) input_items[0];
            bool *out = (bool *) output_items[0];


           /*const char *input_message = (const char *) input_items[0];
            char *output_message = (char *) output_items[0];
            bool in[sizeReceivedMessage]; // 4096
            for (int i = 0; i < sizeReceivedMessage; i++) {
                int temp = (int) input_message[i];
                in[i] = temp % 2;
            }
            bool out[sizeInitialMessage];
            for (bool & i : out) {
                i = true;
            }*/
/*
            double initialDecodedMessage[sizeReceivedMessage];
            for (int i = 0; i < sizeReceivedMessage; i++) {
                initialDecodedMessage[i] = 1 / (1 + exp(-2 * in[i] / noiseVar));
            }
            double q0[sizeParity];
            double q1[sizeParity];
            double r0[sizeParity];
            double r1[sizeParity];
            double Q0[sizeInitialMessage];
            double Q1[sizeInitialMessage];

            for (int i = 0; i < sizeParity; i++) {
                uint8_t parity = rowsParityBits[i];
                q1[i] = initialDecodedMessage[parity];
                q0[i] = 1 - q1[i];
            }
            while (checkDecoder(out)) {

                uint8_t rowNode[sizePositionRows];
                uint8_t columnNode[sizePositionColumns];
                for (int i = 0; i < sizePositionRows; i++) {
                    rowNode[i] = 0;
                    columnNode[i] = 0;
                }
                for (int i = 0; i < sizeParity; i++) {
                    uint8_t positionOfParity = columnsParityBits[i];
                    uint8_t thisParity = positionRows[positionOfParity];
                    uint8_t nextParity;
                    if (thisParity != positionRows[sizePositionRows - 1]) {
                        nextParity = positionRows[positionOfParity + 1];
                    } else {
                        nextParity = positionRows[sizePositionRows - 1] + 1;
                    }
                    uint8_t lengthOfParity = nextParity - thisParity;
                    double vectorWithq1[lengthOfParity];
                    for (int j = 0; j < lengthOfParity; j++) {
                        vectorWithq1[j] = q1[thisParity + j];
                    }
                    double temp = 1;
                    double possibility;
                    for (int k = 0; lengthOfParity; k++) {
                        if (k != rowNode[positionOfParity]) {
                            possibility = 1 - 2 * vectorWithq1[k];
                        }
                        temp *= possibility;
                    }
                    rowNode[positionOfParity] += 1;
                    r0[i] = 0.5 + 0.5 * temp;
                    r1[i] = 1 - r0[i];
                }
                for (int i = 0; i < sizeParity; i++) {
                    uint8_t positionOfParity = rowsParityBits[i];
                    double possibility1 = initialDecodedMessage[positionOfParity];
                    uint8_t thisParity = positionColumns[positionOfParity];
                    uint8_t nextParity;
                    if (thisParity != positionColumns[positionOfParity]) {
                        nextParity = positionColumns[positionOfParity + 1];
                    } else {
                        nextParity = positionColumns[sizePositionColumns - 1];
                    }
                    uint8_t lengthOfParity = nextParity - thisParity;
                    double vectorWithr1[lengthOfParity];
                    double vectorWithr0[lengthOfParity];
                    for (int j = 0; j < lengthOfParity; j++) {
                        vectorWithr0[j] = r0[thisParity + j];
                        vectorWithr1[j] = r1[thisParity + j];
                    }
                    double temp0 = 1;
                    double temp1 = 1;
                    for (int k = 0; k < lengthOfParity; k++) {
                        if (k != columnNode[positionOfParity]) {
                            temp0 *= vectorWithr0[k];
                            temp1 *= vectorWithr1[k];
                        }
                        if (temp0 < 1e-06 && temp1 < 1e-06) {
                            temp0 *= 1e+06;
                            temp1 *= 1e+06;
                        }
                        columnNode[positionOfParity]++;
                        q0[i] = (1 - possibility1) * temp0;
                        q1[i] = possibility1 * temp1;
                        double K = 1 / (q1[i] + q0[k]);
                        q0[i] *= K;
                        q1[i] *= K;
                    }
                }
                for (int i = 0; i < sizeInitialMessage; i++) {
                    uint8_t positionOfParity = rowsParityBits[i];
                    double possibility1 = initialDecodedMessage[positionOfParity];
                    uint8_t thisParity = positionColumns[positionOfParity];
                    uint8_t nextParity;
                    if (thisParity != positionColumns[positionOfParity]) {
                        nextParity = positionColumns[positionOfParity + 1];
                    } else {
                        nextParity = positionColumns[sizePositionColumns - 1];
                    }
                    uint8_t lengthOfParity = nextParity - thisParity;
                    double vectorWithr1[lengthOfParity];
                    double vectorWithr0[lengthOfParity];
                    for (int j = 0; j < lengthOfParity; j++) {
                        vectorWithr0[j] = r0[thisParity + j];
                        vectorWithr1[j] = r1[thisParity + j];
                    }
                    double temp0 = 1;
                    double temp1 = 1;
                    for (int k = 0; lengthOfParity; k++) {
                        temp0 *= vectorWithr0[k];
                        temp1 *= vectorWithr1[k];
                    }
                    Q0[i] = (1 - possibility1) * temp0;
                    Q1[i] = possibility1 * temp1;
                    double K = 1 / (Q1[i] + Q0[i]);
                    Q1[i] *= K;
                    Q0[i] *= K;
                }
                for (int i = 0; i < sizeInitialMessage; i++) {
                    if (Q1[i] > Q0[i]) {
                        out[i] = true;
                      //  output_message[i] = '\001';
                    } else {
                        out[i] = false;
                      //  output_message[i] = '\000';
                    }
                }
            }*/
            consume_each(noutput_items);

            return noutput_items;
        }

    }

} /* namespace a3sat */
/* namespace gr */
