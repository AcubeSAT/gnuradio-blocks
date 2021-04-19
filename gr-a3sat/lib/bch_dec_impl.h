/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_BCH_DEC_IMPL_H
#define INCLUDED_A3SAT_BCH_DEC_IMPL_H

#include <a3sat/bch_dec.h>
#include <unordered_map>
namespace gr {
  namespace a3sat {

    class bch_dec_impl : public bch_dec
    {
     private:
        int n_bch;
        int k_bch;
        std::unordered_map<int, int> syndromes_hash;
     public:
        bch_dec_impl(unsigned int k, unsigned int n);
      ~bch_dec_impl();
      void forecast(int noutput_items, gr_vector_int& ninput_items_required);
      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
        int get_n_bch();
        int get_k_bch();

    };

  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_BCH_DEC_IMPL_H */

