import sys

sys.path.append('../build/swig')

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import a3sat_swig as a3sat
import satnogs


class qa_bch_pdu_encoder(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_001_t(self):
        self.samp_rate = samp_rate = 32000

        satnogs_multi_format_msg_sink_0 = satnogs.multi_format_msg_sink(0, False, False, './pdu_output')
        satnogs_debug_msg_source_raw_1 = satnogs.debug_msg_source_raw([55, 55], 10, False)
        satnogs_debug_msg_source_raw_0 = satnogs.debug_msg_source_raw(
            [51, 68, 85, 102, 42, 56, 10], 0.5, False)
        a3sat_bch_pdu_encoder_0 = a3sat.bch_pdu_encoder()
        self.tb.msg_connect((a3sat_bch_pdu_encoder_0, 'pdu'), (satnogs_multi_format_msg_sink_0, 'in'))
        self.tb.msg_connect((satnogs_debug_msg_source_raw_0, 'msg'), (a3sat_bch_pdu_encoder_0, 'acquisition'))
        self.tb.msg_connect((satnogs_debug_msg_source_raw_1, 'msg'), (a3sat_bch_pdu_encoder_0, 'terminate'))
        self.tb.run()
        self.tb.stop()
        result = ()
        expected = (51, 68, 85, 102, 42, 56, 10)
        try:
            with open("pdu_output", "rb") as f:
                byte = f.read(1)
                result = result + (byte,)
                while byte:
                    byte = f.read(1)
                    result = result + (byte,)
                    print(byte)
        except IOError:
            print('Error While Opening the file!')

        self.assertTupleEqual(expected, result)


if __name__ == '__main__':
    gr_unittest.run(qa_bch_pdu_encoder)
