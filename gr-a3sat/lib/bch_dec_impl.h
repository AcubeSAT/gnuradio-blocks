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
        static const uint8_t n_bch=64;
        static const uint8_t k_bch=56;
        typedef std::unordered_map<int, int> hash;
        static hash syndromes_hash;
     public:
        bch_dec_impl();
      ~bch_dec_impl();


        void forecast(int noutput_items, gr_vector_int& ninput_items_required);
        int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };
  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_BCH_DEC_IMPL_H */

