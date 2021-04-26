#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2021 SpaceDot.
#
# SPDX-License-Identifier: GPL-3.0-or-later
import sys
sys.path.append("/home/konkapo/COMMS/error-correction-codes/gr-a3sat/build/swig")

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import a3sat_swig as a3sat

class qa_bch_dec(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_001_t(self):
        data = (
            1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
            1,
            0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0)
        vector_src = blocks.vector_source_b(data, False, 1, [])

        expected_result = (1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
                           0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
                           1, 0, 1, 0, 1, 0)
        bch_enc = a3sat.bch_dec()
        self.tb.connect((vector_src, 0), (bch_enc, 0))
        # self.tb.connect(self.unpack, self.bch_enc)
        dst = blocks.vector_sink_b(1, 128)
        self.tb.connect((bch_enc, 0), (dst, 0))
        self.tb.run()
        self.tb.stop()
        result_data = dst.data()
        self.assertTupleEqual(expected_result, result_data, 56)
        # self.assertEqual(len(expected_result), len(result_data))


if __name__ == '__main__':
    gr_unittest.run(qa_bch_dec)
