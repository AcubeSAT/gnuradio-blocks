
#ifndef INCLUDED_A3SAT_BCH_PDU_ENCODER_H
#define INCLUDED_A3SAT_BCH_PDU_ENCODER_H

#include <a3sat/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace a3sat {

    /*!
     * \brief <+description of block+>
     * \ingroup a3sat
     *
     */
    class A3SAT_API bch_pdu_encoder : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<bch_pdu_encoder> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of a3sat::bch_pdu_encoder.
       *
       * To avoid accidental use of raw pointers, a3sat::bch_pdu_encoder's
       * constructor is in a private implementation
       * class. a3sat::bch_pdu_encoder::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_BCH_PDU_ENCODER_H */

