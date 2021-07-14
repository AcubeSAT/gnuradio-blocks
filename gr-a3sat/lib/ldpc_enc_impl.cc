/*
 * Copyright 2021 SpaceDot.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ldpc_enc_impl.h"

namespace gr {
    namespace a3sat {

        ldpc_enc::sptr
        ldpc_enc::make() {
            return gnuradio::get_initial_sptr
                    (new ldpc_enc_impl());
        }


        ldpc_enc_impl::ldpc_enc_impl()
                : gr::block("ldpc_enc",
                            gr::io_signature::make(1, 1, sizeof(bool)),
                            gr::io_signature::make(1, 1, sizeof(bool))) {
            set_output_multiple(sizeMessage);
        }

        void ldpc_enc_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required) {
            ninput_items_required[0] = (noutput_items / sizeMessage) * sizeInitialMessage;
        }


        ldpc_enc_impl::~ldpc_enc_impl() {
        }

        int
        ldpc_enc_impl::general_work(int noutput_items,
                                    gr_vector_int &ninput_items,
                                    gr_vector_const_void_star &input_items,
                                    gr_vector_void_star &output_items) {

            const char *input_message = (const char *) input_items[0];
            char *output_message = (char *) output_items[0];
            bool message[sizeInitialMessage]; // 4096
            for (int i = 0; i < sizeInitialMessage; i++) {
                int temp = (int) input_message[i];
                message[i] = temp % 2;
            }
            bool encodedMessage[sizeEncodedMessage]; //1024
            for (bool &i : encodedMessage) {
                i = false;
            }
            for (int row = 0; row < generatorRows; row++) {
                for (int column = 0; column < generatorColumns; column++) {
                    uint16_t index = row * generatorColumns + column;
                    uint16_t thisParityPosition = positionRows[index];
                    uint16_t lengthOfParity;
                    if (thisParityPosition != positionRows[totalQuasiCyclicMatrices - 1]) {
                        uint16_t nextParityPosition = positionRows[index + 1];
                        lengthOfParity = nextParityPosition - thisParityPosition;
                    } else {
                        lengthOfParity = sizeParity - thisParityPosition;//positionRows[totalQuasiCyclicMatrices - 1] + 1 - thisParityPosition;
                    }
                    for (int i = 0; i < lengthOfParity; i++) {
                        uint16_t initialParity =
                                rowsParityBits[thisParityPosition + i] - column * sizeSquareCyclicMatrix;
                        for (int j = 0; j < sizeSquareCyclicMatrix; j++) {
                            uint16_t updatedParity = initialParity + j;
                            if (updatedParity >= sizeSquareCyclicMatrix) {
                                updatedParity -= sizeSquareCyclicMatrix;
                            }
                            encodedMessage[column * sizeSquareCyclicMatrix + updatedParity] ^= message[
                                    row * sizeSquareCyclicMatrix + j];
                        }
                    }
                }
            }
            for (int i = 0; i < sizeMessage; i++) {
                if (i < sizeInitialMessage) {
                    if (message[i]) {
                        output_message[i] = '\001';
                    } else {
                        output_message[i] = '\000';
                    }
                } else {
                    if (encodedMessage[i]) {
                        output_message[i] = '\001';
                    } else {
                        output_message[i] = '\000';
                    }
                }
            }
            consume(0, ninput_items[0]);
            return noutput_items;
        }

    } /* namespace a3sat */
} /* namespace gr */

