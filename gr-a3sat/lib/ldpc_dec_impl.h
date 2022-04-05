#ifndef INCLUDED_A3SAT_LDPC_DEC_IMPL_H
#define INCLUDED_A3SAT_LDPC_DEC_IMPL_H

#include <a3sat/ldpc_dec.h>
#include <a3sat/paritiesColumnms.h>
#include <a3sat/paritiesRows.h>


namespace gr {
    namespace a3sat {

        /**
        * LDPC Decoder based on CCSDS 131.1-0-1. The dimensions of Generator Matrix
        * are 5120x1024 (rate 4/5).
        */

        class ldpc_dec_impl : public ldpc_dec {
        private:

            /**
             * The total number of parity bits that are found in the Parity Matrix
             */
            const uint32_t sizeParity = 2095360;

            /**
             * The position of parity bits in the Rows of the Parity Matrix
             */
            uint16_t *rowsParityBits = paritiesRowsDecoder;

            /**
             * The number of Rows in the Parity Matrix
             */
            const uint16_t totalRows = 1024;

            /**
             * The positions in rowsParityBits in which a new Row starts
             */
            uint64_t *positionRows = positionRowsDecoder;

            /**
             * The position of parity bits in the Columns of the Parity Matrix
             */
            uint16_t *columnsParityBits = paritiesColumnsDecoder;

            /**
             * The number of columns in the Parity Matrix
             */
            const uint16_t totalColumns = 5120;

            /**
             * The positions in columnsParityBits in which a new Column starts
             */
            uint64_t *positionColumns = positionColumnsDecoder;

            /**
             * The noise variance added by the channel. Noise is considered to be AWG
             */
            float noiseVar = 0.2;

            /**
             * The length of the received Message that enters the decoder
             */
            const uint16_t sizeReceivedMessage = 5120;

            /**
             * The length of the initial Message sent prior encoding. The output of the decoder will have this length
             */
            const uint16_t sizeInitialMessage = 4096;


        public:

            /**
             * Class initialiser. Sets the output to be multiple of sizeInitialMessage
             */
            ldpc_dec_impl();

            /**
             * Class Destructor
             */
            ~ldpc_dec_impl();

            /**
             * Defines the required input number of bits to produce a certain number of output bits
             * @param noutput_items The number of output bits
             * @param ninput_items_required The number of input bits needed to produce noutput_items
             */
            void forecast(int noutput_items, gr_vector_int &ninput_items_required);

            /**
             * The decoding of the received message. Due to function forecast, the input data is always multiple to sizeReceivedMessage.
             * @param noutput_items The number of output bits
             * @param ninput_items The number of input bits on each port
             * @param input_items The input buffer
             * @param output_items The output buffer
             * @return noutput_items
             */
            int general_work(int noutput_items,
                             gr_vector_int &ninput_items,
                             gr_vector_const_void_star &input_items,
                             gr_vector_void_star &output_items);

            /**
             * Function that checks whether the decoding process is complete or needs to continue
             * @param decodedMessage the message that has been decoded
             * @return true if the process needs to continue, false otherwise
             */
            bool checkDecoder(const bool *decodedMessage);
        };


    } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_LDPC_DEC_IMPL_H */
