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

    conv_dec_impl::conv_dec_impl(unsigned int rate, unsigned int constraint_length)
      : gr::block("conv_dec",
              gr::io_signature::make(1, 1, sizeof(bool)),
              gr::io_signature::make(1, 1, sizeof(bool))) {

        set_output_multiple(3);
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
                       gr_vector_void_star &output_items)
    {
      const bool *in = (const bool*) input_items[0];
      bool *out = (bool*) output_items[0];

      bool generator[][3] = {{1, 1, 1}, {1, 1, 0}};

      unsigned int path_metric[int(pow(2, this->constraint_length - 1))];
      unsigned int paths[int(pow(2, this->constraint_length - 1))];
      unsigned int t_path_metric[int(pow(2, this->constraint_length - 1))];
      unsigned int t_paths[int(pow(2, this->constraint_length - 1))];
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

      path_metric[0] = 0;

      for(int i = 1; i < pow(2, this->constraint_length - 1); i++){
          path_metric[i] = UINT_MAX;
      }

      for(int t = 0; t < noutput_items; t++){

          for(int i = 1; i < pow(2, this->constraint_length - 1); i++){
              path_metric[i] = UINT_MAX;
          }

          bool transmitted_symbol[2] = {in[this->rate * t], in[this->rate * (t+1)]};

          for(int state = 0; state <pow(2, this->constraint_length - 1); state++){
            if(path_metric[state] != UINT_MAX){

                for(int j = 0; j < this->constraint_length; j++){
                    if(state > 0) {
                        bin_state[this->constraint_length - j - 1] = state % 2;
                        state = state / 2;
                    }
                    else bin_state[j] = 0;
                }

                memcpy(tr_one, bin_state, (this->constraint_length - 1)*sizeof(bool));
                tr_one[0] = 1;

                memcpy(tr_zero, bin_state, (this->constraint_length - 1)*sizeof(bool));
                tr_zero[0] = 0;

                pm_one = 0;
                pm_zero = 0;

                for (int gen_k = 0; gen_k < this->rate; gen_k++) {
                    for(int i = 0; i < 3; i++) {
                        par_one ^= tr_one[i + gen_k] * generator[gen_k][i];
                    }
                    pm_one = abs(par_one - transmitted_symbol[gen_k]);
                }

                for (int gen_k = 0; gen_k < this->rate; gen_k++) {
                    for(int i = 0; i < 3; i++) {
                        par_one ^= tr_zero[i + gen_k] * generator[gen_k][i];
                    }
                    pm_zero = abs(par_zero - transmitted_symbol[gen_k]);
                }

                // Update paths
                tot_pm_one = pow(pm_one, 2) + path_metric[state];
                next_state = state + 1;

                if(t_path_metric[next_state] > tot_pm_one){
                    t_path_metric[next_state] = tot_pm_one;
                    t_paths[next_state] = paths[state] + 1;
                }

                tot_pm_zero = pow(pm_zero, 2) + path_metric[state];
                next_state = state / 2;

                if(t_path_metric[next_state] > tot_pm_zero){
                    t_path_metric[next_state] = tot_pm_zero;
                    t_paths[next_state] = paths[state] + 0;
                }

            memcpy(path_metric, t_path_metric, pow(2, this->constraint_length - 1) * sizeof(unsigned int));
            memcpy(paths, t_paths, pow(2, this->constraint_length - 1) * sizeof(unsigned int));

            unsigned int min;
            unsigned int min_state;
            min = path_metric[0];
            min_state = 0;
            for(int i = 1; i < noutput_items; i++){
                if(path_metric[i] < min){
                    min_state = i;
                }
            }

            for(int i = 0; i < noutput_items; i++){
                *out++ = paths[state];
            }
            }
          }
      }

      consume_each (noutput_items);

      return noutput_items;
    }


  } /* namespace a3sat */
} /* namespace gr */

