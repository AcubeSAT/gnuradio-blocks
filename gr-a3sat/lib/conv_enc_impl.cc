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
        (new conv_enc_impl(2, 3));
    }

    conv_enc_impl::conv_enc_impl(unsigned int rate, unsigned int constraint_length)
      : gr::block("conv_enc",
              gr::io_signature::make(1, 1, sizeof(bool)),
              gr::io_signature::make(1, 1, sizeof(bool)))
    {
        set_output_multiple(6);
        this->rate = rate;
        this->constraint_length = constraint_length;
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

      bool generator[][3] = {{1, 1, 1}, {1, 1, 0}};

      for (int j = 1; j < 3; j++){
          for (int gen_k = 0; gen_k < 2; gen_k++) {
            for (int i = 0; i < j; i++){
                *out ^= in[i] * generator[gen_k][3 - j + i];
            }
            *out++;
        }
      }

      for(int offset = 0; offset < ninput_items[0] - 2; offset++){
          for (int gen_k = 0; gen_k < 2; gen_k++) {
            for(int i = 0; i < 3; i++) {
                *out ^= in[i + offset] * generator[gen_k][i];
            }
            *out++;
          }
      }

      consume_each (ninput_items[0]);

      return noutput_items;
    }

  int conv_enc_impl::get_rate() {return rate;}
  int conv_enc_impl::get_constraint_length() {return constraint_length;}

  } /* namespace a3sat */
} /* namespace gr */

