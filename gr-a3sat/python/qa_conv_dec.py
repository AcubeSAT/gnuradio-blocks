#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2021 SpaceDot.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#
import sys

sys.path.append('../build/swig')

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
    Modifies the initial stream by flipping a number of bits in random position. 
    Then decodes the modified stream and compares it to the initial one. 
    
    Arguments
    ---------
    
    num_of_flipped_bits: int
        the number of bits to be flipped in the initial stream
    """

    def encode_stream_with_error(self, num_of_flipped_bits):
        # Generate random bits as message
        message_bit_stream = []

        for i in range(2048):
            bit = random.getrandbits(1)
            message_bit_stream.append(bit)

        # Encode the message
        initial_message = tuple(message_bit_stream)

        conv_enc = a3sat.conv_enc()
        encoder = blocks.vector_source_b(initial_message, False, 1, [])
        self.tb.connect(encoder, conv_enc)
        encoder_output = blocks.vector_sink_b()
        self.tb.connect(conv_enc, encoder_output)
        self.tb.run()
        encoded_message = encoder_output.data()

        # Flip some bits and add errors to the initial message
        corrupted_message = self.flip_bits(encoded_message, num_of_flipped_bits)

        # Decode the message
        conv_dec = a3sat.conv_dec(False)
        src = blocks.vector_source_b(corrupted_message, False, 1, [])
        self.tb.connect(src, conv_dec)
        dst = blocks.vector_sink_b()
        self.tb.connect(conv_dec, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertTupleEqual(initial_message, result_data, "test failed")

    """
    This function calls the encode_stream_with_error function 3 times with different num_of_flipped_bits param. 
    """
    def test_001_conv_dec(self):
        for i in range(3):
            for num_of_errors in range(1, 4):
                self.encode_stream_with_error(num_of_errors)

    """
    A function that receives a message containing random bits and flips a certain number of bits in random positions. 
    
    Arguments
    ---------
    
    message : tuple 
        the message to be modified
    number_of_bits: int
        the number of bits to be flipped
    """

    def flip_bits(self, message, number_of_bits):
        message = list(message)

        for i in range(number_of_bits):
            position = random.randint(0, 2048)
            if message[position] == 1:
                message[position] = 0
            else:
                message[position] = 1

        return tuple(message)


if __name__ == '__main__':
    gr_unittest.run(qa_conv_dec)
