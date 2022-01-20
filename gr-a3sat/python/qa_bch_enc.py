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


class qa_bch_enc(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    # Encoding one codeword
    def test_001_t(self):
        vector_src = blocks.vector_source_b((1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
                                             0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
                                             1, 0, 1, 0, 1, 0))
        expected_result = (
            1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
            1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0)
        bch_enc = a3sat.bch_enc()
        self.tb.connect((vector_src, 0), (bch_enc, 0))
        dst = blocks.vector_sink_b(1, 128)
        self.tb.connect((bch_enc, 0), (dst, 0))
        self.tb.run()
        self.tb.stop()
        result_data = dst.data()
        self.assertTupleEqual(expected_result, result_data)

    # Encoding two codewords
    def test_002_t(self):
        vector_src = blocks.vector_source_b((1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
                                             0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
                                             1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
                                             0, 1, 0, 1, 0, 1,
                                             0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
                                             1, 0, 1, 0, 1, 0))
        expected_result = (
            1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
            1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0,
            1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
            1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0)
        bch_enc = a3sat.bch_enc()
        self.tb.connect((vector_src, 0), (bch_enc, 0))
        dst = blocks.vector_sink_b(1, 128)
        self.tb.connect((bch_enc, 0), (dst, 0))
        self.tb.run()
        self.tb.stop()
        result_data = dst.data()
        self.assertTupleEqual(expected_result, result_data)

    def test_003_t(self):
        src_bit_stream = open(r"../../python/encoder_src_data.txt", "r")
        src_data = tuple(map(int, src_bit_stream.readlines()))
        src_bit_stream.close()

            # Read encoded bit stream
        dst_bit_stream = open(r"../../python/encoder_dst_data.txt", "r")
        expected_result = tuple(map(int, dst_bit_stream.readlines()))
        dst_bit_stream.close()

        bch_enc = a3sat.bch_enc()
        src = blocks.vector_source_b(src_data, False, 1, [])
        self.tb.connect(src, bch_enc)
        dst = blocks.vector_sink_b()
        self.tb.connect(bch_enc, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertTupleEqual(expected_result, result_data, "test failed")

    def test_004_t(self):
        src_bit_stream = open(r"../../python/encoder_src_data2.txt", "r")
        src_data = tuple(map(int, src_bit_stream.readlines()))
        src_bit_stream.close()

        # Read encoded bit stream
        dst_bit_stream = open(r"../../python/encoder_dst_data2.txt", "r")
        expected_result = tuple(map(int, dst_bit_stream.readlines()))
        dst_bit_stream.close()

        bch_enc = a3sat.bch_enc()
        src = blocks.vector_source_b(src_data, False, 1, [])
        self.tb.connect(src, bch_enc)
        dst = blocks.vector_sink_b()
        self.tb.connect(bch_enc, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertTupleEqual(expected_result, result_data, "test failed")


if __name__ == '__main__':
    gr_unittest.run(qa_bch_enc)
