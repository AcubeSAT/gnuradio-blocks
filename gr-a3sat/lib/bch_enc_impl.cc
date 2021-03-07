/*
 * Copyright 2021 SpaceDot.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "bch_enc_impl.h"

namespace gr {
  namespace a3sat {

    bch_enc::sptr
    bch_enc::make()
    {
      return gnuradio::get_initial_sptr
        (new bch_enc_impl());
    }


    bch_enc_impl::bch_enc_impl()
      : gr::block("bch_enc",
              gr::io_signature::make(56, 56, sizeof(bool)),
              gr::io_signature::make(64, 64, sizeof(bool)))
    {}

    bch_enc_impl::~bch_enc_impl()
    {
    }

    int
    bch_enc_impl::general_work (int noutput_items,
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

