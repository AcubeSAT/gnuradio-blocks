#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ldpc_dec_impl.h"

namespace gr {
  namespace a3sat {

    ldpc_dec::sptr
    ldpc_dec::make()
    {
      return gnuradio::get_initial_sptr
        (new ldpc_dec_impl());
    }

    ldpc_dec_impl::ldpc_dec_impl()
      : gr::block("ldpc_dec",
              gr::io_signature::make(5120, 5120, sizeof(bool)),
              gr::io_signature::make(4096, 4096, sizeof(bool)))
    {}

      ldpc_dec_impl::~ldpc_dec_impl()
    {
    }

    int
    ldpc_dec_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const bool *in = (const bool *) input_items[0];
      bool *out = (bool *) output_items[0];

     consume_each (noutput_items);

      return noutput_items;
    }

  } /* namespace a3sat */
} /* namespace gr */

