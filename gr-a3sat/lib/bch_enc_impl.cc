/*
 * Copyright 2021 SpaceDot.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <fstream>
#include <gnuradio/io_signature.h>
#include "bch_enc_impl.h"
#include <string>
#include <cstring>

namespace gr {
    namespace a3sat {

        bch_enc::sptr
        bch_enc::make() {
            return gnuradio::get_initial_sptr
                    (new bch_enc_impl());
        }


        bch_enc_impl::bch_enc_impl()
                : gr::block("bch_enc",
                            gr::io_signature::make(1, 1, sizeof(char)),
                            gr::io_signature::make(1, 1, sizeof(char))) {
            set_output_multiple(n_bch);
        }

        void bch_enc_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required) {
            ninput_items_required[0] = (noutput_items / n_bch) * k_bch;
        }

        bch_enc_impl::~bch_enc_impl() {
        }

        int
        bch_enc_impl::general_work(int noutput_items,
                                   gr_vector_int &ninput_items,
                                   gr_vector_const_void_star &input_items,
                                   gr_vector_void_star &output_items) {
            uint8_t *in = (uint8_t *) input_items[0];
            uint8_t *out = (uint8_t *) output_items[0];
            static const uint8_t generator = 197;
            static const uint8_t bit_position[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
            for (int i = 0; i < noutput_items; i += n_bch) {
                uint8_t remainder = 0;
                uint8_t current_byte = 0;
                uint8_t temp = 0;
                memcpy(out, in, sizeof(uint8_t) * k_bch);
                out += k_bch;

                for (int bytes = 0; bytes < k_bch / 8; bytes++) {
                    current_byte = 0;

                    for (int bit = 7; bit >= 0; bit--) {
                        temp = *in++;
                        current_byte |= temp << bit;
                    }

                    remainder ^= current_byte;
                    for (int position = 0; position < 8; position++) {
                        if ((remainder & 0x80) != 0) {
                            remainder ^= generator;
                            remainder <<= 1;
                        } else {
                            remainder <<= 1;
                        }
                    }
                }
                for (int bit = 7; bit >= 0; bit--) {
                    *out = (uint8_t) (remainder & bit_position[bit]) != 0x00;
                    out++;
                }
            }

            consume_each(ninput_items[0]);
            return noutput_items;
        }

    } /* namespace a3sat */
} /* namespace gr */
