'''
This module tests BCH encoder-decoder

'''

import sys

sys.path.append("../build/swig")

from gnuradio import gr
from gnuradio import blocks
import a3sat_swig as a3sat

import random


for test_repetitions in range(500): # Run the test 500 times
  print("Start Of Run", test_repetitions+1)
  positions_of_bitflip = range(56)
  flag = True
  for position in positions_of_bitflip: # Every time this for loop runs we change the value of a different bit so we test all positions
     # Initialise a list of 56 random bits
     random_src = []
     for i in range(56):  # Size of input is 56 bits
         random_src.append(round(random.random()))  # round(random.random()) returns either 0 or 1

     # Encoding routine
     tb_enc = gr.top_block()
     vector_src_enc = blocks.vector_source_b(random_src, False, 1, [])
     bch_enc = a3sat.bch_enc()
     dst_enc = blocks.vector_sink_b()
     tb_enc.connect((vector_src_enc, 0), (bch_enc, 0))
     tb_enc.connect((bch_enc, 0), (dst_enc, 0))
     tb_enc.run()
     tb_enc.stop()
     encoded_data = dst_enc.data()  # This is a tuple of 64 bits

     #bit_flipped_data will serve as input to the decoder, it is the a list that has the same elements as encoded_data with one bitflip
     bit_flipped_data = list(encoded_data)
     bit_flipped_data[position] = 1 - bit_flipped_data[position] # the bitflip

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


     error_counter = 0
     for i in range(len(result_data)):
         if random_src[i] != result_data[i]:
             error_counter += 1

     error_rate = error_counter/56
     if error_counter != 0:
      flag = False
      print("- For BitFlipPosition =", position, "we have", error_counter, "errors or", error_rate, "error rate")

  if flag:
   print("No Errors")
  print("****************")
