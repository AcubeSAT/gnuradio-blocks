/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_CONV_ENC_H
#define INCLUDED_A3SAT_CONV_ENC_H

#include <a3sat/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace a3sat {

    /*!
     * \brief Convolutional Encoder based on CCSDS 130.1-G-3
     * \ingroup a3sat
     *
     */
    class A3SAT_API conv_enc : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<conv_enc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of a3sat::conv_enc.
       *
       * To avoid accidental use of raw pointers, a3sat::conv_enc's
       * constructor is in a private implementation
       * class. a3sat::conv_enc::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_CONV_ENC_H */

