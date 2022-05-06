#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "gmsk_precoder_impl.h"

namespace gr {
  namespace a3sat {

    gmsk_precoder::sptr
    gmsk_precoder::make()
    {
      return gnuradio::get_initial_sptr
        (new gmsk_precoder_impl());
    }


    
    gmsk_precoder_impl::gmsk_precoder_impl()
      : gr::block("gmsk_precoder",
              gr::io_signature::make(1, 1, sizeof(bool)),
              gr::io_signature::make(1, 1, sizeof(bool))
    {}

    gmsk_precoder_impl::~gmsk_precoder_impl()
    {
    }

    void
    gmsk_precoder_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      int ninput_items_required[0] = noutput_items;
    }

    int
    gmsk_precoder_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const bool *in = const bool *input_items[0];
      bool *out = bool *output_items[0];

      for (uint16_t i = 0; i < ninput_items[0]; i++){
        out[i] = in[i] + prev_bit + curr_k;
        prev_bit = in[i];
        curr_k += 1;
      }
      consume_each (noutput_items);
      
      return noutput_items;
    }

  } /* namespace a3sat */
} /* namespace gr */

