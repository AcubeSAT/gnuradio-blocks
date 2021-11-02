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


class qa_conv_enc(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    """ 
    This function tests the functionality of the convolutional encoding block.
    First, it reads a bit stream contained in a file, then encodes it and compares the encoder's output with the initial stream. 
    """
    def test_001_conv_enc(self):
        # Read message bit stream
        src_bit_stream = open(r"../python/encoder_src_data", "r")
        src_data = tuple(map(int, src_bit_stream.readlines()))
        src_bit_stream.close()

        # Read encoded bit stream
        dst_bit_stream = open(r"../python/encoder_dst_data", "r")
        expected_result = tuple(map(int, dst_bit_stream.readlines()))
        dst_bit_stream.close()

        conv_enc = a3sat.conv_enc()
        src = blocks.vector_source_b(src_data, False, 1, [])
        self.tb.connect(src, conv_enc)
        dst = blocks.vector_sink_b()
        self.tb.connect(conv_enc, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertTupleEqual(expected_result, result_data, "test failed")


if __name__ == '__main__':
    gr_unittest.run(qa_conv_enc)
