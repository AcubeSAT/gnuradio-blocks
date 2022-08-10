import sys
sys.path.append('../cmake-build-debug/swig')


from gnuradio import gr, gr_unittest
from gnuradio import blocks
import a3sat_swig as a3sat

class qa_gmsk_precoder(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_001_t(self):
        vector_src = blocks.vector_source_b((0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1,
                                             0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1,
                                             0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
                                             0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1))

        expected_result = (1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0,
                           1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0,
                           1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0,
                           1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0)

        gmsk_precoder = a3sat.gmsk_precoder()
        self.tb.connect((vector_src, 0), (gmsk_precoder, 0))
        dst = blocks.vector_sink_b(1, 128)
        self.tb.connect((gmsk_precoder, 0), (dst, 0))
        self.tb.run()
        self.tb.stop()
        result_data = dst.data()
        self.assertTupleEqual(expected_result, result_data)


if __name__ == '__main__':
    gr_unittest.run(qa_gmsk_precoder)
