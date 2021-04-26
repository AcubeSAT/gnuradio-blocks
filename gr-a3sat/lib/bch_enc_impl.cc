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
#include <cstring> // for memcpy

namespace gr {
    namespace a3sat {

        bch_enc::sptr
        bch_enc::make() {
            return gnuradio::get_initial_sptr
                    (new bch_enc_impl(56, 64));
        }


        bch_enc_impl::bch_enc_impl(unsigned int k, unsigned int n)
                : gr::block("bch_enc",
                            gr::io_signature::make(1, 1, sizeof(char)),
                            gr::io_signature::make(1, 1, sizeof(char)))
                            {
            set_output_multiple(n);
            this->k_bch = k;
            this->n_bch = n;
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
            uint8_t generator = 197;
            uint8_t bit_pos[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
                for (int i = 0; i < noutput_items; i += get_n_bch()) {
                    uint8_t remainder=0;
                    uint8_t current_byte=0;
                    uint8_t temp =0;
                    memcpy(out, in, sizeof(uint8_t) * get_k_bch());
                    out += get_k_bch();

                    for (int bytes = 0; bytes < get_k_bch() / 8; bytes++) {
                        current_byte = 0;

                        for (int bit = 7; bit >=0; bit--) {
                            temp = *in++;
                            current_byte |= temp << bit;
                        }

                        remainder ^= current_byte;
                        for (int pos = 0; pos < 8; pos++) {
                            if ((remainder & 0x80) != 0) {
                                remainder ^= generator;
                                remainder <<= 1;
                            }
                            else{
                                remainder <<= 1;
                            }
                        }
                    }
                    for(int bit =7; bit>=0; bit--) {
                    *out = (uint8_t) (remainder&bit_pos[bit]) != 0x00;
                    out++;
                }
                }

                consume_each(ninput_items[0]);
                return noutput_items;
        }

        int bch_enc_impl::get_n_bch() { return n_bch; }

        int bch_enc_impl::get_k_bch() { return k_bch; }

        } /* namespace a3sat */
    } /* namespace gr */
