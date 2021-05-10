/*
 * Copyright 2021 SpaceDot.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "conv_enc_impl.h"

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
        // We don't use puncturing patterns so this is not really needed
        conv_enc::make(bool puncturing_enabled)
        {
            return gnuradio::get_initial_sptr
                    (new conv_enc_impl(puncturing_enabled));
        }


        conv_enc_impl::conv_enc_impl(bool puncturing_enabled)
                : gr::block("conv_enc",
                // Accept streams less than the assumed block size
                            gr::io_signature::make(3, 4096, sizeof(bool)),
                            gr::io_signature::make(6, 8192, sizeof(bool)))
        {}

        conv_enc_impl::~conv_enc_impl()
        {
        }

        int
        conv_enc_impl::general_work (int noutput_items,
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

