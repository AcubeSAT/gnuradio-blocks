#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2021 SpaceDot.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#
import sys

sys.path.append("../build/swig")

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import a3sat_swig as a3sat
import random


class qa_conv_dec(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    # Encoded bit stream without errors
    def test_001_conv_dec(self):
        src_bit_stream = open(r"encoder_dst_data", "r")
        src_data = tuple(map(int, src_bit_stream.readlines()))
        src_bit_stream.close()

        dst_bit_stream = open(r"encoder_src_data", "r")
        expected_result = tuple(map(int, dst_bit_stream.readlines()))
        dst_bit_stream.close()

        conv_dec = a3sat.conv_dec()
        src = blocks.vector_source_b(src_data, 1, [])
        self.tb.connect(src, conv_dec)
        dst = blocks.vector_sink_b()
        self.tb.connect(conv_dec, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertTupleEqual(expected_result, result_data, "test failed")

    def test_002_conv_dec(self):
        src_bit_stream = open(r"decoderSrcData_OneError", "r")
        src_data = tuple(map(int, src_bit_stream.readlines()))
        src_bit_stream.close()

        dst_bit_stream = open(r"encoder_src_data", "r")
        expected_result = tuple(map(int, dst_bit_stream.readlines()))
        dst_bit_stream.close()

        conv_dec = a3sat.conv_dec()
        src = blocks.vector_source_b(src_data, 1, [])
        self.tb.connect(src, conv_dec)
        dst = blocks.vector_sink_b()
        self.tb.connect(conv_dec, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertTupleEqual(expected_result, result_data, "test failed")

    # Generates message random bits. Encodes them. Flips some bits. Decodes them. Checks if decoded and initial stream match.
    # def test_001_conv_dec(self):
    #     # Generate random bits as message
    #     message_bit_stream = open(r"message_bit_stream", "w+")
    #
    #     for i in range(2048):
    #         bit = random.getrandbits(1)
    #         message_bit_stream.writelines(str(bit) + " ")
    #
    #     # Encode the message
    #
    #     initial_message = tuple(map(int, message_bit_stream.readlines()))
    #
    #     message_bit_stream.close()
    #
    #     conv_enc = a3sat.conv_enc()
    #     encoder = blocks.vector_source_b(initial_message, False, 1, [])
    #     self.tb.connect(initial_message, conv_enc)
    #     encoder_output = blocks.vector_sink_b()
    #     self.tb.connect(encoder, encoder_output)
    #     self.tb.run()
    #     encoded_message = encoder_output.data()
    #
    #     # Decode the message
    #
    #     conv_dec = a3sat.conv_dec()
    #     src = blocks.vector_source_b(encoded_message, False, 1, [])
    #     self.tb.connect(src, conv_dec)
    #     dst = blocks.vector_sink_b()
    #     self.tb.connect(conv_dec, dst)
    #     self.tb.run()
    #     result_data = dst.data()
    #     self.assertTupleEqual(initial_message, result_data, "test failed")

if __name__ == '__main__':
    gr_unittest.run(qa_conv_dec)
