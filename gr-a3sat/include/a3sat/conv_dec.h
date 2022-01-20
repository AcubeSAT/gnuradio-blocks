/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_CONV_DEC_H
#define INCLUDED_A3SAT_CONV_DEC_H

#include <a3sat/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace a3sat {

    /*!
     * \brief Convolutional Decoder based on CCSDS 130.1-G-3
     * \ingroup a3sat
     *
     */
    class A3SAT_API conv_dec : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<conv_dec> sptr;
      static sptr make(bool soft_decision_decoding = false);

    };

  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_CONV_DEC_H */

