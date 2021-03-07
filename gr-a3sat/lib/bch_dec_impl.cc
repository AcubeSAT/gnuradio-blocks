/*
 * Copyright 2021 SpaceDot.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "bch_dec_impl.h"

namespace gr {
  namespace a3sat {

    bch_dec::sptr
    bch_dec::make()
    {
      return gnuradio::get_initial_sptr
        (new bch_dec_impl());
    }

    bch_dec_impl::bch_dec_impl()
      : gr::block("bch_dec",
              gr::io_signature::make(64, 64, sizeof(bool)),
              gr::io_signature::make(56, 56, sizeof(bool)))
    {}

    bch_dec_impl::~bch_dec_impl()
    {
    }

    int
    bch_dec_impl::general_work (int noutput_items,
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

