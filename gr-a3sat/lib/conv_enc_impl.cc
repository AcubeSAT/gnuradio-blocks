/*
 * Copyright 2021 SpaceDot.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "conv_enc_impl.h"

namespace gr {
    namespace a3sat {

        conv_enc::sptr
        conv_enc::make()
        {
            return gnuradio::get_initial_sptr
                    (new conv_enc_impl(2, 7));
        }

        conv_enc_impl::conv_enc_impl(unsigned int rate, unsigned int constraintLength)
                : gr::block("conv_enc",
                            gr::io_signature::make(1, 1, sizeof(bool)),
                            gr::io_signature::make(1, 1, sizeof(bool)))
        {
            set_output_multiple(18);
            this->rate = rate;
            this->constraintLength = constraintLength;
        }

        void
        conv_enc_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required)
        {
            ninput_items_required[0] =  noutput_items/this->rate;
        }

        conv_enc_impl::~conv_enc_impl(){
        }

        int
        conv_enc_impl::general_work (int noutput_items,
                                     gr_vector_int &ninput_items,
                                     gr_vector_const_void_star &input_items,
                                     gr_vector_void_star &output_items)
        {
            bool *in = (bool *) input_items[0];
            bool *out = (bool *) output_items[0];

            for (int generatorBit = 1; generatorBit < this->constraintLength; generatorBit++){
                for (int iGenerator = 0; iGenerator < this->rate; iGenerator++) {
                    for (int stateBit = 0; stateBit < generatorBit; stateBit++){
                        *out ^= in[stateBit] * this->generator[iGenerator][this->constraintLength - generatorBit + stateBit];
                    }
                    *out++;
                }
            }

            for(int generatorBit = 0; generatorBit < ninput_items[0] - (this->constraintLength - 1); generatorBit++){
                for (int iGenerator = 0; iGenerator < this->rate; iGenerator++) {
                    for(int stateBit = 0; stateBit < this->constraintLength; stateBit++) {
                        *out ^= in[stateBit + generatorBit] * this->generator[iGenerator][stateBit];
                    }
                    *out++;
                }
            }

            consume_each (ninput_items[0]);

            return noutput_items;
        }

    } /* namespace a3sat */
} /* namespace gr */
