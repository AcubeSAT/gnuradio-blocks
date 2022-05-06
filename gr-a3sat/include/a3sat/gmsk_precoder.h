
#ifndef INCLUDED_A3SAT_GMSK_PRECODER_H
#define INCLUDED_A3SAT_GMSK_PRECODER_H

#include <a3sat/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace a3sat {

    /*!
     * \brief <+description of block+>
     * \ingroup a3sat
     *
     */
    class A3SAT_API gmsk_precoder : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<gmsk_precoder> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of a3sat::gmsk_precoder.
       *
       * To avoid accidental use of raw pointers, a3sat::gmsk_precoder's
       * constructor is in a private implementation
       * class. a3sat::gmsk_precoder::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_GMSK_PRECODER_H */

