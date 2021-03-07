/*
 * Copyright 2021 SpaceDot.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "conv_dec_impl.h"

namespace gr {
  namespace a3sat {

    conv_dec::sptr
    conv_dec::make(bool soft_decision_decoding)
    {
      return gnuradio::get_initial_sptr
        (new conv_dec_impl(soft_decision_decoding));
    }

    conv_dec_impl::conv_dec_impl(bool soft_decision_decoding)
      : gr::block("conv_dec",
              gr::io_signature::make(6, 8192, sizeof(bool)),
              gr::io_signature::make(3, 4096, sizeof(bool)))
    {}

    conv_dec_impl::~conv_dec_impl()
    {
    }

    int
    conv_dec_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const bool *in = (const bool*) input_items[0];
      bool *out = (bool*) output_items[0];

      consume_each (noutput_items);

      return noutput_items;
    }

  } /* namespace a3sat */
} /* namespace gr */

