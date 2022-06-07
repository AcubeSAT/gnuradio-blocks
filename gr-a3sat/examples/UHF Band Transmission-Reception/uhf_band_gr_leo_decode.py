#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: uhf_band_gr_leo_decode
# GNU Radio version: 3.8.1.0

from distutils.version import StrictVersion

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print("Warning: failed to XInitThreads()")

from gnuradio import blocks
from gnuradio import digital
from gnuradio import gr
from gnuradio.filter import firdes
import sys
import signal
from PyQt5 import Qt
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
import a3sat
import leo
import math
import satnogs
from gnuradio import qtgui

class uhf_band_gr_leo_decode(gr.top_block, Qt.QWidget):

    def __init__(self, cfo=0, excess_bw=0.35, snr=12, sps=2):
        gr.top_block.__init__(self, "uhf_band_gr_leo_decode")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("uhf_band_gr_leo_decode")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "uhf_band_gr_leo_decode")

        try:
            if StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
                self.restoreGeometry(self.settings.value("geometry").toByteArray())
            else:
                self.restoreGeometry(self.settings.value("geometry"))
        except:
            pass

        ##################################################
        # Parameters
        ##################################################
        self.cfo = cfo
        self.excess_bw = excess_bw
        self.snr = snr
        self.sps = sps

        ##################################################
        # Variables
        ##################################################
        self.Turnstile_Antenna = Turnstile_Antenna = leo.custom_antenna_make(3,436e6, 0, 10, 2.64 , 72, 0)
        self.Helical_Antenna = Helical_Antenna = leo.helix_antenna_make(1, 436e6,0, 0, 8, 0.1725, 0.689)
        self.AcubeSAT = AcubeSAT = leo.satellite_make('TLE_1', '1 69696U 16025E   23183.00000000  .00002000  00000-0  49111-4 0  6969', '2 69696  97.3759 191.5890 0001000 000.0000 000.0000 15.24261762696969', 436e6, 436e6, 30, Turnstile_Antenna, Turnstile_Antenna, .4, 315, 20000)
        self.nfilts = nfilts = 64
        self.AUTH_GS = AUTH_GS = leo.tracker_make(AcubeSAT, 22.959887, 40.627233, 0.056, '2023-07-03T15:25:00.000000Z', '2023-07-03T15:32:00.000000Z', 128*10000, 436e6, 436e6, 41.14, Helical_Antenna, Helical_Antenna, 0.4, 245, 20000)
        self.variable_ieee802_15_4_variant_decoder_0 = variable_ieee802_15_4_variant_decoder_0 = satnogs.ieee802_15_4_variant_decoder_make([0x55]*7, 14, [79, 121, 97], 5, satnogs.crc.CRC32_C, satnogs.whitening.make_ccsds(True), True, 64, False)
        self.variable_ieee802_15_4_encoder_1 = variable_ieee802_15_4_encoder_1 = satnogs.ieee802_15_4_encoder_make(0x55, 7, [79, 121, 97], satnogs.crc.CRC32_C, satnogs.whitening.make_ccsds(True), True)
        self.samp_rate = samp_rate = 128000
        self.rrc_taps = rrc_taps = firdes.root_raised_cosine(nfilts, nfilts, 1.0/float(sps), excess_bw, 11*sps*nfilts)
        self.UHF_Band_LEO_Model = UHF_Band_LEO_Model = leo.leo_model_make(AUTH_GS, 1, 5,
          													6, 0,
          													1, 3,
          													True, 7.5, 0, 25)

        ##################################################
        # Blocks
        ##################################################
        self.satnogs_frame_encoder_0 = satnogs.frame_encoder(variable_ieee802_15_4_encoder_1)
        self.satnogs_frame_decoder_0 = satnogs.frame_decoder(variable_ieee802_15_4_variant_decoder_0, 1 * 1)
        self.satnogs_debug_msg_source_0 = satnogs.debug_msg_source('TEST', 0.01, True)
        self.satnogs_ber_calculator_0 = satnogs.ber_calculator(64, 1000, 10)
        self.leo_channel_model_1 = leo.channel_model(2000000, UHF_Band_LEO_Model, 1)
        self.digital_gmsk_mod_0 = digital.gmsk_mod(
            samples_per_symbol=2,
            bt=0.35,
            verbose=False,
            log=False)
        self.digital_gmsk_demod_0 = digital.gmsk_demod(
            samples_per_symbol=2,
            gain_mu=0.175,
            mu=0.5,
            omega_relative_limit=0.005,
            freq_error=0.0,
            verbose=False,log=False)
        self.blocks_throttle_2 = blocks.throttle(gr.sizeof_char*1, samp_rate,True)
        self.blocks_pdu_to_tagged_stream_0 = blocks.pdu_to_tagged_stream(blocks.byte_t, 'packet_len')
        self.blocks_packed_to_unpacked_xx_1 = blocks.packed_to_unpacked_bb(1, gr.GR_MSB_FIRST)
        self.blocks_pack_k_bits_bb_0 = blocks.pack_k_bits_bb(8)
        self.a3sat_bch_enc_1 = a3sat.bch_enc()
        self.a3sat_bch_dec_1 = a3sat.bch_dec()



        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.satnogs_ber_calculator_0, 'pdu'), (self.satnogs_frame_encoder_0, 'pdu'))
        self.msg_connect((self.satnogs_debug_msg_source_0, 'msg'), (self.satnogs_ber_calculator_0, 'trigger'))
        self.msg_connect((self.satnogs_frame_decoder_0, 'out'), (self.satnogs_ber_calculator_0, 'received'))
        self.msg_connect((self.satnogs_frame_encoder_0, 'pdu'), (self.blocks_pdu_to_tagged_stream_0, 'pdus'))
        self.connect((self.a3sat_bch_dec_1, 0), (self.satnogs_frame_decoder_0, 0))
        self.connect((self.a3sat_bch_enc_1, 0), (self.blocks_pack_k_bits_bb_0, 0))
        self.connect((self.blocks_pack_k_bits_bb_0, 0), (self.digital_gmsk_mod_0, 0))
        self.connect((self.blocks_packed_to_unpacked_xx_1, 0), (self.a3sat_bch_enc_1, 0))
        self.connect((self.blocks_pdu_to_tagged_stream_0, 0), (self.blocks_throttle_2, 0))
        self.connect((self.blocks_throttle_2, 0), (self.blocks_packed_to_unpacked_xx_1, 0))
        self.connect((self.digital_gmsk_demod_0, 0), (self.a3sat_bch_dec_1, 0))
        self.connect((self.digital_gmsk_mod_0, 0), (self.leo_channel_model_1, 0))
        self.connect((self.leo_channel_model_1, 0), (self.digital_gmsk_demod_0, 0))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "uhf_band_gr_leo_decode")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_cfo(self):
        return self.cfo

    def set_cfo(self, cfo):
        self.cfo = cfo

    def get_excess_bw(self):
        return self.excess_bw

    def set_excess_bw(self, excess_bw):
        self.excess_bw = excess_bw
        self.set_rrc_taps(firdes.root_raised_cosine(self.nfilts, self.nfilts, 1.0/float(self.sps), self.excess_bw, 11*self.sps*self.nfilts))

    def get_snr(self):
        return self.snr

    def set_snr(self, snr):
        self.snr = snr

    def get_sps(self):
        return self.sps

    def set_sps(self, sps):
        self.sps = sps
        self.set_rrc_taps(firdes.root_raised_cosine(self.nfilts, self.nfilts, 1.0/float(self.sps), self.excess_bw, 11*self.sps*self.nfilts))

    def get_Turnstile_Antenna(self):
        return self.Turnstile_Antenna

    def set_Turnstile_Antenna(self, Turnstile_Antenna):
        self.Turnstile_Antenna = Turnstile_Antenna
        self.Turnstile_Antenna.set_pointing_error(10)

    def get_Helical_Antenna(self):
        return self.Helical_Antenna

    def set_Helical_Antenna(self, Helical_Antenna):
        self.Helical_Antenna = Helical_Antenna
        self.Helical_Antenna.set_pointing_error(0)

    def get_AcubeSAT(self):
        return self.AcubeSAT

    def set_AcubeSAT(self, AcubeSAT):
        self.AcubeSAT = AcubeSAT

    def get_nfilts(self):
        return self.nfilts

    def set_nfilts(self, nfilts):
        self.nfilts = nfilts
        self.set_rrc_taps(firdes.root_raised_cosine(self.nfilts, self.nfilts, 1.0/float(self.sps), self.excess_bw, 11*self.sps*self.nfilts))

    def get_AUTH_GS(self):
        return self.AUTH_GS

    def set_AUTH_GS(self, AUTH_GS):
        self.AUTH_GS = AUTH_GS

    def get_variable_ieee802_15_4_variant_decoder_0(self):
        return self.variable_ieee802_15_4_variant_decoder_0

    def set_variable_ieee802_15_4_variant_decoder_0(self, variable_ieee802_15_4_variant_decoder_0):
        self.variable_ieee802_15_4_variant_decoder_0 = variable_ieee802_15_4_variant_decoder_0

    def get_variable_ieee802_15_4_encoder_1(self):
        return self.variable_ieee802_15_4_encoder_1

    def set_variable_ieee802_15_4_encoder_1(self, variable_ieee802_15_4_encoder_1):
        self.variable_ieee802_15_4_encoder_1 = variable_ieee802_15_4_encoder_1

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_2.set_sample_rate(self.samp_rate)

    def get_rrc_taps(self):
        return self.rrc_taps

    def set_rrc_taps(self, rrc_taps):
        self.rrc_taps = rrc_taps

    def get_UHF_Band_LEO_Model(self):
        return self.UHF_Band_LEO_Model

    def set_UHF_Band_LEO_Model(self, UHF_Band_LEO_Model):
        self.UHF_Band_LEO_Model = UHF_Band_LEO_Model


def argument_parser():
    parser = ArgumentParser()
    parser.add_argument(
        "--cfo", dest="cfo", type=eng_float, default="0.0",
        help="Set cfo [default=%(default)r]")
    parser.add_argument(
        "--excess-bw", dest="excess_bw", type=eng_float, default="350.0m",
        help="Set excess_bw [default=%(default)r]")
    parser.add_argument(
        "--snr", dest="snr", type=eng_float, default="12.0",
        help="Set snr [default=%(default)r]")
    parser.add_argument(
        "--sps", dest="sps", type=intx, default=2,
        help="Set samples per symbol [default=%(default)r]")
    return parser


def main(top_block_cls=uhf_band_gr_leo_decode, options=None):
    if options is None:
        options = argument_parser().parse_args()

    if StrictVersion("4.5.0") <= StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls(cfo=options.cfo, excess_bw=options.excess_bw, snr=options.snr, sps=options.sps)
    tb.start()
    tb.show()

    def sig_handler(sig=None, frame=None):
        Qt.QApplication.quit()

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    timer = Qt.QTimer()
    timer.start(500)
    timer.timeout.connect(lambda: None)

    def quitting():
        tb.stop()
        tb.wait()
    qapp.aboutToQuit.connect(quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
