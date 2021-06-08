/*
 * Copyright 2021 SpaceDot.
 */

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
              gr::io_signature::make(1, 1, sizeof(bool)),
              gr::io_signature::make(1, 1, sizeof(bool)))
    {}

//        void ldpc_enc_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required) {
//            ninput_items_required[0] = (noutput_items / n_bch) * k_bch;
//        }


        ldpc_enc_impl::~ldpc_enc_impl()
    {
    }

    int
    ldpc_enc_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const bool *message = (const bool*) input_items[0];
      bool *encoded_message = (bool*) output_items[0];
        for (int row = 0; row < gr::a3sat::ldpc_enc_impl::Generator_rows; row++){
            for (int column = 0; column < gr::a3sat::ldpc_enc_impl::Generator_columns; column++){
                uint16_t position_of_this_parity = gr::a3sat::ldpc_enc_impl::position_Rows[row+column];
                uint16_t position_of_next_parity = gr::a3sat::ldpc_enc_impl::position_Rows[row+column+1];
                int length_of_parity_submatrix = position_of_next_parity - position_of_this_parity;
                for (int i = 0; i<length_of_parity_submatrix; i++){
                    uint16_t parity = gr::a3sat::ldpc_enc_impl::Rows_Parity_bits[position_of_this_parity+i];
                    uint16_t position_in_square_matrix = parity % gr::a3sat::ldpc_enc_impl::size_square_cyclic_matrix;
                    for (int j = 0; j < gr::a3sat::ldpc_enc_impl::size_square_cyclic_matrix; j++)
                        if (position_in_square_matrix + j < size_square_cyclic_matrix) {
                            encoded_message[gr::a3sat::ldpc_enc_impl::size_square_cyclic_matrix * column +
                                            position_in_square_matrix + j] ^= message[
                                    parity + j];
                        } else {
                            encoded_message[gr::a3sat::ldpc_enc_impl::size_square_cyclic_matrix * column +
                                            position_in_square_matrix + j -
                                            gr::a3sat::ldpc_enc_impl::size_square_cyclic_matrix] ^= message[parity -
                                    gr::a3sat::ldpc_enc_impl::size_square_cyclic_matrix + j];
                        };
                }
            }
        }
      
      consume_each (noutput_items);

      return noutput_items;
    }

  } /* namespace a3sat */
} /* namespace gr */

