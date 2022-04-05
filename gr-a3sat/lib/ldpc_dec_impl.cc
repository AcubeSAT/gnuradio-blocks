#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ldpc_dec_impl.h"
#include <cmath>
#include <numeric>

namespace gr {
    namespace a3sat {

        ldpc_dec::sptr
        ldpc_dec::make() {
            return gnuradio::get_initial_sptr
                    (new ldpc_dec_impl());
        }

        ldpc_dec_impl::ldpc_dec_impl()
                : gr::block("ldpc_dec",
                            gr::io_signature::make(1, 1, sizeof(float)),
                            gr::io_signature::make(1, 1, sizeof(bool))) {
            set_output_multiple(sizeInitialMessage);
        }

        void ldpc_dec_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required) {
            ninput_items_required[0] = (noutput_items / sizeInitialMessage) * sizeReceivedMessage;
        }


        ldpc_dec_impl::~ldpc_dec_impl() {
        }

        bool ldpc_dec_impl::checkDecoder(const bool *decodedMessage) {

            int sum = std::accumulate(decodedMessage, decodedMessage + sizeInitialMessage, 0);
            if (sum == 0) {
                return true;
            } else {
                uint16_t totalSum = 0;
                for (int i = 0; i < totalRows; i++) {
                    uint64_t thisParity = positionRows[i];
                    uint64_t nextParity;
                    if (thisParity != positionRows[totalRows - 1]) {
                        nextParity = positionRows[i + 1];
                    } else {
                        nextParity = sizeParity;
                    }
                    uint64_t lengthParity = nextParity - thisParity;
                    uint16_t partialSum = 0;
                    for (int j = 0; j < lengthParity; j++) {
                        uint16_t parity = rowsParityBits[thisParity + j];
                        partialSum ^= decodedMessage[parity];
                    }
                    totalSum += partialSum;
                }
                if (totalSum != 0) {
                    return true;
                } else {
                    return false;
                }
            }

        }

        int
        ldpc_dec_impl::general_work(int noutput_items,
                                    gr_vector_int &ninput_items,
                                    gr_vector_const_void_star &input_items,
                                    gr_vector_void_star &output_items) {

            const auto *in = (const float *) input_items[0];
            char *output_message = (char *) output_items[0];

            for (int package = 0; package < ninput_items[0]; package += sizeReceivedMessage) {

                bool out[sizeReceivedMessage] = {false};
                double initialDecodedMessage[sizeReceivedMessage];
                for (int i = 0; i < sizeReceivedMessage; i++) {
                    initialDecodedMessage[i] = 1 / (1 + std::exp(-2 * in[i + package] / noiseVar));
                }
                auto *q0 = new double[sizeParity];
                auto *q1 = new double[sizeParity];
                auto *r0 = new double[sizeParity];
                auto *r1 = new double[sizeParity];
                auto *Q0 = new double[sizeReceivedMessage];
                auto *Q1 = new double[sizeReceivedMessage];

                for (int i = 0; i < sizeParity; i++) {
                    uint64_t parity = rowsParityBits[i];
                    q1[i] = initialDecodedMessage[parity];
                    q0[i] = 1 - q1[i];
                }
                for (int i = 0; i < sizeReceivedMessage; i++){
                    Q1[i] = initialDecodedMessage[i];
                }
                uint8_t counter = 0;
                while (checkDecoder(out) && counter < 50) {

                    uint64_t rowNode[totalRows] = {0};
                    uint64_t columnNode[totalColumns] = {0};

                    for (int i = 0; i < sizeParity; i++) {
                        uint16_t positionOfParity = columnsParityBits[i];
                        uint64_t thisParity = positionRows[positionOfParity];
                        uint64_t nextParity;
                        if (thisParity != positionRows[totalRows - 1]) {
                            nextParity = positionRows[positionOfParity + 1];
                        } else {
                            nextParity = sizeParity;
                        }
                        uint64_t lengthOfParity = nextParity - thisParity;
                        double vectorWithq1[lengthOfParity];
                        for (int j = 0; j < lengthOfParity; j++) {
                            vectorWithq1[j] = q1[thisParity + j];
                        }
                        double temp = 1;
                        double possibility;
                        for (int k = 0; k < lengthOfParity; k++) {
                            if (k != rowNode[positionOfParity]) {
                                possibility = 1 - 2 * vectorWithq1[k];
                                temp *= possibility;
                            }
                        }
                        rowNode[positionOfParity] += 1;
                        r0[i] = 0.5 + 0.5 * temp;
                        r1[i] = 1 - r0[i];
                    }
                    for (int i = 0; i < sizeParity; i++) {
                        uint16_t positionOfParity = rowsParityBits[i];
                        double possibility1 = Q1[positionOfParity];
                        uint64_t thisParity = positionColumns[positionOfParity];
                        uint64_t nextParity;
                        if (thisParity != positionColumns[totalColumns - 1]) {
                            nextParity = positionColumns[positionOfParity + 1];
                        } else {
                            nextParity = sizeParity;
                        }
                        uint64_t lengthOfParity = nextParity - thisParity;
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
                        }
                        columnNode[positionOfParity]++;
                        q0[i] = (1 - possibility1) * temp0;
                        q1[i] = possibility1 * temp1;
                        double K = 1 / (q1[i] + q0[i]);
                        q0[i] *= K;
                        q1[i] *= K;
                    }
                    for (int i = 0; i < sizeReceivedMessage; i++) {
                        uint16_t positionOfParity = rowsParityBits[i];
                        double possibility1 = Q1[positionOfParity];
                        uint64_t thisParity = positionColumns[i];
                        uint64_t nextParity;
                        if (thisParity != positionColumns[totalColumns - 1]) {
                            nextParity = positionColumns[i + 1];
                        } else {
                            nextParity = sizeParity;
                        }
                        uint64_t lengthOfParity = nextParity - thisParity;
                        double vectorWithr1[lengthOfParity];
                        double vectorWithr0[lengthOfParity];
                        for (int j = 0; j < lengthOfParity; j++) {
                            vectorWithr0[j] = r0[thisParity + j];
                            vectorWithr1[j] = r1[thisParity + j];
                        }
                        double temp0 = 1;
                        double temp1 = 1;
                        for (int k = 0; k < lengthOfParity; k++) {
                            temp0 *= vectorWithr0[k];
                            temp1 *= vectorWithr1[k];
                        }
                        Q0[i] = (1 - possibility1) * temp0;
                        Q1[i] = possibility1 * temp1;
                        double K = 1 / (Q1[i] + Q0[i]);
                        Q1[i] *= K;
                        Q0[i] *= K;
                    }
                    for (int i = 0; i < sizeReceivedMessage; i++) {
                        if (Q1[i] > Q0[i]) {
                            out[i] = true;
                        } else {
                            out[i] = false;
                        }
                    }
                    counter += 1;
                }
                for (int i = 0; i < sizeInitialMessage; i++) {
                    if (out[i]) {
                        output_message[i + (package / sizeReceivedMessage) * sizeInitialMessage] = '\001';
                    } else {
                        output_message[i + (package / sizeReceivedMessage) * sizeInitialMessage] = '\000';
                    }
                }
                delete[]q0;
                delete[]q1;
                delete[]r0;
                delete[]r1;
                delete[]Q0;
                delete[]Q1;
            }
            consume(0, (noutput_items / sizeInitialMessage) * sizeReceivedMessage);

            return noutput_items;
        }

    }

} /* namespace a3sat */
/* namespace gr */
