/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_BCH_DEC_H
#define INCLUDED_A3SAT_BCH_DEC_H

#include <a3sat/api.h>
#include <gnuradio/block.h>

namespace gr {
    namespace a3sat {

        /*!
         * \brief BCH Decoder based on CCSDS 230.1-G-2
         */
        class A3SAT_API bch_dec : virtual public gr::block
        {
        public:
            typedef boost::shared_ptr<bch_dec> sptr;

            static sptr make();
        };

    } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_BCH_DEC_H */


