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
    Then decodes the modified stream and compares it to the initial one. 
    """

    def test_soft_decoding(self):
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
                decoder_bit_stream.append(round(random.uniform(0.0, 0.49), 4))
            else:
                decoder_bit_stream.append(round(random.uniform(0.5, 1.0), 4))

        decoder_message = tuple(decoder_bit_stream)

        # Decode the message
        conv_dec = a3sat.conv_dec(False)
        src = blocks.vector_source_f(decoder_message, False, 1, [])
        self.tb.connect(src, conv_dec)
        dst = blocks.vector_sink_b()
        self.tb.connect(conv_dec, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertTupleEqual(initial_message, result_data, "Test failed")


if __name__ == '__main__':
    gr_unittest.run(qa_conv_dec)
