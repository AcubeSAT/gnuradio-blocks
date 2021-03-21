/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_BCH_ENC_H
#define INCLUDED_A3SAT_BCH_ENC_H

#include <a3sat/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace a3sat {

    
    /*!
     * \brief BCH Encoder based on CCSDS 230.1-G-2
     * \ingroup a3sat
     */
    class A3SAT_API bch_enc : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<bch_enc> sptr;

      static sptr make();
    };

  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_BCH_ENC_H */

