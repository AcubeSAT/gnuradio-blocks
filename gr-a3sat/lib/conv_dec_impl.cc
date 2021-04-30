/*
 * Copyright 2021 SpaceDot.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <climits>
#include "conv_dec_impl.h"

namespace gr {
  namespace a3sat {

    conv_dec::sptr
    conv_dec::make(bool soft_decision_decoding)
    {
      return gnuradio::get_initial_sptr
        (new conv_dec_impl(2,3));
    }

    conv_dec_impl::conv_dec_impl(int rate, int constraint_length)
      : gr::block("conv_dec",
              gr::io_signature::make(1, 1, sizeof(bool)),
              gr::io_signature::make(1, 1, sizeof(char))) {

        set_output_multiple(6);
        this->rate = rate;
        this->constraint_length = constraint_length;
    }

    void
    conv_dec_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required) {
        ninput_items_required[0] = noutput_items * this->rate;
    }

    conv_dec_impl::~conv_dec_impl()
    {
    }

    int
    conv_dec_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items) {
        const bool *in = (const bool *) input_items[0];
        char *out = (char *) output_items[0];

        bool generator[][3] = {{1, 1, 1},
                               {1, 1, 0}};

        unsigned int path_metric[4];
        char paths[4][6];
        unsigned int t_path_metric[4];
        char t_paths[4][6];
        bool bin_state[2] = {};
        unsigned int next_state;
        bool tr_one[3] = {};
        bool tr_zero[3] = {};
        unsigned int pm_one = 0;
        unsigned int pm_zero = 0;
        unsigned int tot_pm_one = 0;
        unsigned int tot_pm_zero = 0;
        bool par_one = 0;
        bool par_zero = 0;
        int temp_state = 0;
        unsigned int min;
        unsigned int min_state;

        path_metric[0] = 0;

        for (int i = 1; i < pow(this->constraint_length - 1, 2); i++) {
            path_metric[i] = UINT_MAX;
        }

        for(int j = 0; j < 4; j++){
            for (int i = 0; i < 6; i++) {
                paths[j][i] = ' ';
            }
        }

        for (int t = 0; t < noutput_items; t++) {

            for (int i = 0; i < pow(2, this->constraint_length - 1); i++) {
                t_path_metric[i] = UINT_MAX;
            }

            for(int i = 0; i < 4; i++){
                for (int j = 0; j < 6; j++) {
                    t_paths[i][j] = ' ';
                }
            }

            bool transmitted_symbol[2] = {in[this->rate * t], in[this->rate * t + 1]};

            for (int state = 0; state < pow(2, this->constraint_length - 1); state++) {
                if (path_metric[state] != UINT_MAX) {
                    // Convert each state to binary
                    temp_state = state;
                    for (int j = 1; j < this->constraint_length; j++) {
                        if (temp_state > 0) {
                            bin_state[this->constraint_length - j - 1] = temp_state % 2;
                            temp_state = temp_state / 2;
                        } else bin_state[this->constraint_length - j - 1] = 0;
                    }

                    // 1 is transmitted
                    tr_one[0] = 1;
                    for (int i = 1; i < this->constraint_length; i++) {
                        tr_one[i + 1] = bin_state[i];
                    }

                    // 0 is transmitted
                    tr_zero[0] = 0;
                    for (int i = 0; i < this->constraint_length; i++) {
                        tr_zero[i + 1] = bin_state[i];
                    }

                    // Calculate path metrics
                    pm_one = 0;
                    pm_zero = 0;

                    for (int gen_k = 0; gen_k < this->rate; gen_k++) {
                        par_one = 0;
                        for (int i = 0; i < this->constraint_length; i++) {
                            par_one ^= tr_one[i] * generator[gen_k][i];
                        }
                        pm_one += abs(par_one - transmitted_symbol[gen_k]);
                    }

                    for (int gen_k = 0; gen_k < this->rate; gen_k++) {
                        par_zero = 0;
                        for (int i = 0; i < this->constraint_length; i++) {
                            par_zero ^= tr_zero[i] * generator[gen_k][i];
                        }
                        pm_zero += abs(par_zero - transmitted_symbol[gen_k]);
                    }

                    // Update paths
                    tot_pm_one = pow(pm_one, 2) + path_metric[state];
                    next_state = (state + 4) >> 1;

                    if (t_path_metric[next_state] > tot_pm_one) {
                        t_path_metric[next_state] = tot_pm_one;
                        int i = 0;
                        while(paths[state][i] != ' '){
                            t_paths[next_state][i] = paths[state][i];
                            i++;
                        }
                        t_paths[next_state][i] = '1';
                    }

                    tot_pm_zero = pow(pm_zero, 2) + path_metric[state];
                    next_state = state >> 1;

                    if (t_path_metric[next_state] > tot_pm_zero) {
                        t_path_metric[next_state] = tot_pm_zero;
                        int i = 0;
                        while(paths[state][i] != ' '){
                            t_paths[next_state][i] = paths[state][i];
                            i++;
                        }
                        t_paths[next_state][i] = '0';
                    }
                }
            }
            memcpy(path_metric, t_path_metric, sizeof(t_path_metric));
            memcpy(paths, t_paths, sizeof(t_paths));
            }

        min = path_metric[0];
        min_state = 0;

        for (int i = 1; i < int(pow(2, (this->constraint_length - 1))); i++) {
            if (path_metric[i] < min) {
                min = path_metric[i];
                min_state = i;
            }
        }

        for(int i = 0; i < noutput_items; i++){
            *out++ = paths[min_state][i];
        }

        consume_each(noutput_items);

        return noutput_items;
    }

  } /* namespace a3sat */
} /* namespace gr */

