#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <climits>
#include "conv_dec_impl.h"
#include <iostream>

namespace gr {
    namespace a3sat {

        conv_dec::sptr
        conv_dec::make(bool soft_decision_decoding)
        {
            return gnuradio::get_initial_sptr
                    (new conv_dec_impl());
        }

        conv_dec_impl::conv_dec_impl()
                : gr::block("conv_dec",
                            gr::io_signature::make(1, 1, sizeof(bool)),
                            gr::io_signature::make(1, 1, sizeof(char))) {

            set_output_multiple(6);
        }

        conv_dec_impl::~conv_dec_impl()
        {
        }

        void
        conv_dec_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required) {
            ninput_items_required[0] = noutput_items * rate;
        }

        int
        conv_dec_impl::general_work (int noutput_items,
                                     gr_vector_int &ninput_items,
                                     gr_vector_const_void_star &input_items,
                                     gr_vector_void_star &output_items) {
            const bool *in = (const bool *) input_items[0];
            unsigned int *out = (unsigned int *) output_items[0];

            for (int i = 0; i < pow(2, constraint_length - 1); i++) {
                path_metric[i] = UINT_MAX;
                paths[i] = 0;
            }

            path_metric[0] = 0;

            for (int inputItem = 0; inputItem < noutput_items; inputItem++) {

                for (int i = 0; i < pow(2, constraint_length - 1); i++) {
                    t_path_metric[i] = UINT_MAX;
                    t_paths[i] = 0;
                }

                bool transmitted_symbol[2] = {in[rate * inputItem], in[rate * inputItem + 1]};

                for (int state = 0; state < pow(2, constraint_length - 1); state++) {
                    if (path_metric[state] != UINT_MAX) {

                        // Convert each state to binary
                        temp_state = state;
                        for (int j = 1; j < constraint_length; j++) {
                            if (temp_state > 0) {
                                bin_state[constraint_length - j - 1] = temp_state % 2;
                                temp_state = temp_state / 2;
                            } else bin_state[constraint_length - j - 1] = 0;
                        }

                        tr_one[0] = 1;
                        tr_zero[0] = 0;

                        for (int i = 0; i < constraint_length - 1; i++) {
                            tr_one[i + 1] = bin_state[i];
                            tr_zero[i + 1] = bin_state[i];
                        }

                        pm_one = 0;
                        pm_zero = 0;

                        pm_one = calculate_path_metric(rate, constraint_length, tr_one, generator, transmitted_symbol);
                        pm_zero = calculate_path_metric(rate, constraint_length, tr_zero, generator, transmitted_symbol);

                        // Update paths
                        tot_pm_one = pow(pm_one, 2) + path_metric[state];
                        next_state = (state >> 1) ^ int(pow(2, constraint_length - 2));

                        if (t_path_metric[next_state] > tot_pm_one) {
                            t_path_metric[next_state] = tot_pm_one;
                            t_paths[next_state] = (paths[state] << 1) ^ 1;
                        }

                        tot_pm_zero = pow(pm_zero, 2) + path_metric[state];
                        next_state = state >> 1;

                        if (t_path_metric[next_state] > tot_pm_zero) {
                            t_path_metric[next_state] = tot_pm_zero;
                            t_paths[next_state] = paths[state] << 1;
                        }
                    }
                }
                memcpy(path_metric, t_path_metric, sizeof(t_path_metric));
                memcpy(paths, t_paths, sizeof(t_paths));
            }

            optimal_path = path_metric[0];
            optimal_path_index = 0;

            for (int i = 1; i < int(pow(2, (constraint_length - 1))); i++) {
                if (path_metric[i] < optimal_path && paths[i] != 0) {
                    optimal_path = path_metric[i];
                    optimal_path_index = i;
                }
            }

            // Convert path_metric to binary for the output
            for (int j = 0; j < noutput_items; j++) {
                if (paths[optimal_path_index] > 0) {
                    binary_optimal_path[noutput_items - j - 1] = paths[optimal_path_index] % 2;
                    paths[optimal_path_index] = paths[optimal_path_index] / 2;
                } else binary_optimal_path[noutput_items - j - 1] = 0;
            }

            for(int outIndex = 0; outIndex < noutput_items; outIndex++){
                *out = binary_optimal_path[outIndex];
                out++;
            }

            consume_each(noutput_items);
            return noutput_items;
        }

        int conv_dec_impl::calculate_path_metric(int rate, int constraint_length, bool *state, bool (*generator)[7], bool *transmitted_symbol) {
            int parity_bit = 0;
            int path_metric = 0;

            for (int gen_k = 0; gen_k < rate; gen_k++) {
                parity_bit = 0;
                for (int state_bit = 0; state_bit < constraint_length; state_bit++) {
                    parity_bit ^= state[state_bit] * generator[gen_k][state_bit];
                }
                path_metric += abs(parity_bit - transmitted_symbol[gen_k]);
            }
            return path_metric;
        }

    } /* namespace a3sat */
} /* namespace gr */
