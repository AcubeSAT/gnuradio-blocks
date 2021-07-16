/*
 * Copyright 2021 SpaceDot.
 */

#ifndef INCLUDED_A3SAT_LDPC_DEC_IMPL_H
#define INCLUDED_A3SAT_LDPC_DEC_IMPL_H

#include <a3sat/ldpc_dec.h>
//#include "a3sat/paritiesColumnsDecoder.h"
//#include "a3sat/paritiesRowsDecoder.h"


namespace gr {
    namespace a3sat {

        class ldpc_dec_impl : public ldpc_dec {
        private:

            static const uint16_t sizeParity = 5;

            inline static const uint16_t rowsParityBits[sizeParity] = {0, 1, 2, 1, 3};

            static const uint16_t sizePositionRows = 2; //check

            inline static const uint8_t positionRows[sizePositionRows] = {0, 3};

            inline static const uint16_t columnsParityBits[sizeParity] = {0, 0, 1, 0, 1};

            static const uint8_t sizePositionColumns = 4;

            inline static const uint8_t positionColumns[sizePositionColumns] = {0, 1, 3, 4};

            constexpr static const float noiseVar = 0.2;

            static const uint16_t sizeReceivedMessage = 4;//5120;

            static const uint16_t sizeInitialMessage = 4;//4096;



            //constexpr static const double *a = positionColumns;




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
