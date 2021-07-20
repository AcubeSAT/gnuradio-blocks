#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ldpc_enc_impl.h"

namespace gr {
  namespace a3sat {

    ldpc_enc::sptr
    ldpc_enc::make()
    {
      return gnuradio::get_initial_sptr
        (new ldpc_enc_impl());
    }


    ldpc_enc_impl::ldpc_enc_impl()
      : gr::block("ldpc_enc",
              gr::io_signature::make(4096, 4096, sizeof(bool)),
              gr::io_signature::make(5120, 5120, sizeof(bool)))
    {}

    ldpc_enc_impl::~ldpc_enc_impl()
    {
    }

    int
    ldpc_enc_impl::general_work (int noutput_items,
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

