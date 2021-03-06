#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "conv_enc_impl.h"

namespace gr {
    namespace a3sat {

        conv_enc::sptr
        conv_enc::make() {
            return gnuradio::get_initial_sptr
                    (new conv_enc_impl());
        }

        conv_enc_impl::conv_enc_impl()
                : gr::block("conv_enc",
                            gr::io_signature::make(1, 1, sizeof(bool)),
                            gr::io_signature::make(1, 1, sizeof(bool))) {
            set_output_multiple(rate);
        }

        void
        conv_enc_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required) {
            ninput_items_required[0] =  noutput_items/rate;
        }

        conv_enc_impl::~conv_enc_impl() {
        }

        int
        conv_enc_impl::general_work (int noutput_items,
                                     gr_vector_int &ninput_items,
                                     gr_vector_const_void_star &input_items,
                                     gr_vector_void_star &output_items) {
            bool *in = (bool *) input_items[0];
            bool *out = (bool *) output_items[0];

            bool generator[2][7] = {{1, 0, 0, 1, 1, 1, 1}, {1, 1, 0, 1, 1, 0, 1}};
            /*!
             * @brief Ignores the padding bits added in the encoder's sliding window and
             * multiplies only the message bits with the respective bits of the
             * generator polynomials.
             * The bit generated from the second generator is inversed according to the CCSDS 131.0-B-3.
             * This process iterates until the sliding window
             * of the encoder contains only message bits.
             */
            for (uint8_t generatorBit = 1; generatorBit < constraintLength; generatorBit++) {
                for (uint8_t iGenerator = 0; iGenerator < rate; iGenerator++) {
                    for (uint8_t stateBit = 0; stateBit < generatorBit; stateBit++) {
                        *out ^= in[stateBit] * generator[iGenerator][constraintLength - generatorBit + stateBit];
                    }
                    if (iGenerator == 1){
                        *out ^= 1;
                    }
                    else{
                        *out ^= 0;
                    }
                    out++;
                }
            }

            /*!
             * @brief Multiplies the encoder's sliding window bits with each generator polynomial.
             */
            for(uint16_t generatorBit = 0; generatorBit < ninput_items[0] - (constraintLength - 1); generatorBit++) {
                for (uint8_t iGenerator = 0; iGenerator < rate; iGenerator++) {
                    for (uint8_t stateBit = 0; stateBit < constraintLength; stateBit++) {
                        *out ^= in[generatorBit + stateBit] * generator[iGenerator][stateBit];
                    }
                    /*!
                     * xor operation with the iGenerator is used, so that the bit generated from the second generator is inversed.
                     * e.x. (bit = 1) iGenerator=0: 1 ^ iGenerator = 1, iGenerator=1: 1 ^ iGenerator = 0
                     */
                    *out ^= iGenerator;
                    out++;
                }
            }

            consume_each (ninput_items[0]);

            return noutput_items;
        }

    } /* namespace a3sat */
} /* namespace gr */
