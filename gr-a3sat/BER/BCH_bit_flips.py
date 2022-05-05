'''
This script tests the BCH encoder-decoder
'''
import sys

sys.path.append("../build/swig")

from gnuradio import gr
from gnuradio import blocks
import a3sat_swig as a3sat

import random


def BCH_bit_flips(test_repetitions):
    INPUT_SIZE = 56  # Size of input to the encoder is 56 bits
    for test_repetition in range(test_repetitions):
        print("Start Of Run", test_repetition + 1)
        has_No_Errors = True
        # Every time this for loop runs we change the value of a different bit so we test all positions
        for position_of_bitflip in range(INPUT_SIZE):
            # Initialise a list of 56 random "bits" (integers of value 0 or 1)
            random_src = [random.randint(0, 1) for _ in range(INPUT_SIZE)]

            # Encoding routine
            tb_enc = gr.top_block()
            vector_src_enc = blocks.vector_source_b(random_src, False, 1, [])
            bch_enc = a3sat.bch_enc()
            dst_enc = blocks.vector_sink_b()
            tb_enc.connect((vector_src_enc, 0), (bch_enc, 0))
            tb_enc.connect((bch_enc, 0), (dst_enc, 0))
            tb_enc.run()
            tb_enc.stop()
            encoded_data = dst_enc.data()  # This is a tuple of 64 "bits" (integers of value 0 or 1)

            # bit_flipped_data will serve as input to the decoder, it is a list that has the same elements as encoded_data with one bitflip
            bit_flipped_data = list(encoded_data)
            bit_flipped_data[position_of_bitflip] = 1 - bit_flipped_data[position_of_bitflip]  # the bitflip

            # Decoding routine
            tb_dec = gr.top_block()
            vector_src_dec = blocks.vector_source_b(bit_flipped_data, False, 1, [])
            bch_dec = a3sat.bch_dec()
            tb_dec.connect(vector_src_dec, bch_dec)
            dst_dec = blocks.vector_sink_b()
            tb_dec.connect(bch_dec, dst_dec)
            tb_dec.run()
            tb_dec.stop()
            result_data = dst_dec.data()

            error_counter = sum(i != j for i, j in zip(random_src, result_data))
            error_rate = error_counter / INPUT_SIZE
            if error_counter != 0:
                has_No_Errors = False
                print(
                    f"- For position_of_bitflip = {position_of_bitflip}, we have {error_counter} errors, or {error_rate}")
        if has_No_Errors:
            print("No Errors")
        print("****************")


BCH_bit_flips(500)  # Run the test 500 times
