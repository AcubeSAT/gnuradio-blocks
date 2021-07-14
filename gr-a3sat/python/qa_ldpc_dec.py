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


class qa_ldpc_dec(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None
"""
    def test_001_t(self):
        # set up fg
        data = (1 in range (5120))#(1.0319,-1.1308,0.95664,-0.96574)0
        vector_src = blocks.vector_source_b(data)
        expected_results = (0 in range (4096))
        ldpc_dec = a3sat.ldpc_dec()
        self.tb.connect(vector_src, ldpc_dec)
        dst = blocks.vector_sink_b()
        self.tb.connect((ldpc_dec, 0), (dst, 0))
        self.tb.run()
        self.tb.stop()
        result_data = dst.data()
        self.assertTupleEqual(expected_results, result_data)
        # check data
"""

if __name__ == '__main__':
    gr_unittest.run(qa_ldpc_dec)
