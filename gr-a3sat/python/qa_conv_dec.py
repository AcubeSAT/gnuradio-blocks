#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2021 SpaceDot.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#
import sys

sys.path.append('../cmake-build-debug/swig')

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import a3sat_swig as a3sat
import random


class qa_conv_dec(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    """
    This function tests the functionality of the convolutional decoder block.
    It initializes a stream of 2048 random generated bits.
    Encodes them using the convolutional encoder block. 
    Each bit in the stream is then represented with a float value in the range of [0.0, 1.0].
    O -> [0.0, 0.5] & 1 -> [0.5, 1.0] 
    Extra noise is added in order to add some errors in the bit float representation. 
    Then decodes the stream and compares it to the initial one.
    """

    def soft_decoding(self, num_of_flipped_bits):
        # Generate random bits as message
        encoder_bit_stream = []
        decoder_bit_stream = []

        codeword_length = 2048

        for i in range(codeword_length):
            bit = random.getrandbits(1)
            encoder_bit_stream.append(bit)

        # Encode the message
        initial_message = tuple(encoder_bit_stream)

        conv_enc = a3sat.conv_enc()
        encoder = blocks.vector_source_b(initial_message, False, 1, [])
        self.tb.connect(encoder, conv_enc)
        encoder_output = blocks.vector_sink_b()
        self.tb.connect(conv_enc, encoder_output)
        self.tb.run()
        encoded_message = encoder_output.data()

        for i in range(codeword_length*2):
            if encoded_message[i] == 0:
                decoder_bit_stream.append(round(random.uniform(0.0, 0.5), 4))
            else:
                decoder_bit_stream.append(round(random.uniform(0.5, 1.0), 4))

        decoder_message = tuple(decoder_bit_stream)

        corrupted_message = self.add_noise(decoder_message, num_of_flipped_bits)

        # Decode the message
        conv_dec = a3sat.conv_dec(False)
        src = blocks.vector_source_f(corrupted_message, False, 1, [])
        self.tb.connect(src, conv_dec)
        dst = blocks.vector_sink_b()
        self.tb.connect(conv_dec, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertTupleEqual(initial_message, result_data, "Test failed")

    """
    This function calls the add_noise function 3 times with different num_of_corrupted_bits param. 
    """
    def test_soft_decoding(self):
        for i in range(3):
            for num_of_errors in range(0, 4):
                self.soft_decoding(num_of_errors)

    """
    A function that receives a message containing float representation of random bits and 
    adds noise in a certain number of bits in random positions.
    
    Arguments
    ---------
    
    message : tuple
       the message to be modified
    number_of_corrupted_bits: int
       the number of bits to be corrupted with noise
    """
    def add_noise(self, message, number_of_corrupted_bits):
        message = list(message)

        for i in range(number_of_corrupted_bits):
            position = random.randint(0, 2048)
            noise = round(random.uniform(0.5, 1.0), 4)
            if message[position] <= 0.5:
                message[position] += noise
            else:
                message[position] -= noise

        return tuple(message)


if __name__ == '__main__':
    gr_unittest.run(qa_conv_dec)
