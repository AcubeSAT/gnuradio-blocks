/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_LDPC_DEC_IMPL_H
#define INCLUDED_A3SAT_LDPC_DEC_IMPL_H

#include <a3sat/ldpc_dec.h>

namespace gr {
    namespace a3sat {

        class ldpc_dec_impl : public ldpc_dec {
        private:

            static const uint16_t rowsParityBits[];

            static const uint16_t sizePositionRows = 1024; //check

            static const uint16_t positionRows[sizePositionRows];

            static const uint16_t columnsParityBits[];

            static const uint8_t sizePositionColumns = 1024;

            static const uint16_t positionColumns[sizePositionColumns];

            constexpr static const float noiseVar = 0.2;

            static const uint16_t sizeReceivedMessage = 5120;

            static const uint16_t sizeInitialMessage = 4096;

            static const uint16_t sizeParity;




        public:
            ldpc_dec_impl();

            ~ldpc_dec_impl();

            void forecast(int noutput_items, gr_vector_int &ninput_items_required);

            int general_work(int noutput_items,
                             gr_vector_int &ninput_items,
                             gr_vector_const_void_star &input_items,
                             gr_vector_void_star &output_items);

            bool checkDecoder(const bool decodedMessage[sizeInitialMessage]);
        };


    } // namespace a3sat
} // namespace gr

#endif /* INCLUDED_A3SAT_LDPC_DEC_IMPL_H */
