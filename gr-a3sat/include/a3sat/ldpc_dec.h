/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_LDPC_DEC_H
#define INCLUDED_A3SAT_LDPC_DEC_H

#include <a3sat/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace a3sat {

    /*!
     * \brief LDPC Decoder based on CCSDS 130.1-G-3
     * \ingroup a3sat
     *
     */
    class A3SAT_API ldpc_dec : virtual public gr::block
    {
     public:
      typedef std::shared_ptr<ldpc_dec> sptr;

      static sptr make();
    };

  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_LDPC_DEC_H */

