#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2021 SpaceDot.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#
import sys
import os

sys.path.append("/home/efthamar/Desktop/spaceDOT/Repos/error-correction-codes/gr-a3sat/build/swig")

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import a3sat_swig as a3sat

class qa_conv_enc(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_001_conv_enc(self):
        # set up fg
        src_data = (1, 0, 1, 1, 0, 1, 0, 0, 0)
        expected_result = (1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1)
        conv_enc = a3sat.conv_enc()
        src = blocks.vector_source_b(src_data, False, 1, [])
        self.tb.connect(src, conv_enc)
        dst = blocks.vector_sink_b()
        self.tb.connect(conv_enc, dst)
        self.tb.run()
        print("OK")
        result_data = dst.data()
        self.assertTupleEqual(expected_result, result_data, "test failed")
        # check data

if __name__ == '__main__':
    gr_unittest.run(qa_conv_enc)
