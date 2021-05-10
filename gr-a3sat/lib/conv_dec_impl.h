/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_CONV_DEC_IMPL_H
#define INCLUDED_A3SAT_CONV_DEC_IMPL_H

#include <a3sat/conv_dec.h>
#include <unordered_map>

namespace gr {
    namespace a3sat {
/*!
 * \brief Implements a convolutional Viterbi soft decision decoder
 * \ingroup a3sat
 *
 * Input: Convolutional encoded 4096 bit frame
 * Output: Decoded 2048 bit frame
 */
        class conv_dec_impl : public conv_dec {
            /*!
             * \param rate Number of the generator polynomials used for the encoding.
             * \param constraint_length Length of each generator polynomial used for the encoding.
             * \param constraint_length The length of each generator polynomial.
             * \param paths
             * \param path_metric The path metric of each path of the trellis
             * \param t_paths
             * \param t_path_metric The branch metric of each state in timestep t
             * \param bin_state Current state in binary form
             * \param next_state The following state in each case of 1 / 0 transmitted
             * \param tr_one
             * \param tr_zero
             * \param tot_pm_one
             * \param tot_pm_zero
             * \param temp_state
             * \param optimal_path
             * \param optimal_path_index
             * \param binary_optimal_path
             */
        private:
            static const int rate = 2;
            static const int constraint_length = 7;
            bool generator[2][7] = {{1, 1, 1, 1, 0, 0, 1},
                                    {1, 0, 1, 1, 0, 1, 1}};
            unsigned int paths[64];
            unsigned int path_metric[64];
            unsigned int t_paths[64];
            unsigned int t_path_metric[64];
            bool bin_state[6] = {0};
            unsigned int next_state = 0;
            bool tr_one[7] = {0};
            bool tr_zero[7] = {0};
            unsigned int pm_one = 0;
            unsigned int pm_zero = 0;
            unsigned int tot_pm_one = 0;
            unsigned int tot_pm_zero = 0;
            int temp_state = 0;
            unsigned int optimal_path = 0;
            unsigned int optimal_path_index = 0;
            unsigned int binary_optimal_path[6] = {};
//            std::unordered_map<unsigned int, bool[]> binary_states;

        public:
            conv_dec_impl();

            ~conv_dec_impl();

            int general_work(int noutput_items,
                             gr_vector_int &ninput_items,
                             gr_vector_const_void_star &input_items,
                             gr_vector_void_star &output_items);

            void forecast(int noutput_items, gr_vector_int &ninput_items_required);

            int calculate_path_metric(int rate,
                                      int constraint_length,
                                      bool state[],
                                      bool generator[][7],
                                      bool transmitted_symbol[]);
        };

    } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_CONV_DEC_IMPL_H */
