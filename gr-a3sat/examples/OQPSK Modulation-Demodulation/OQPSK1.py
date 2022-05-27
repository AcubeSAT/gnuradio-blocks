#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: OQPSK_Mod_Demod
# Author: SpaceDot
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

import os
import sys
sys.path.append(os.environ.get('GRC_HIER_PATH', os.path.expanduser('~/.grc_gnuradio')))

from OQPSK_mod import OQPSK_mod  # grc-generated hier_block
from PyQt5 import Qt
from gnuradio import qtgui
from gnuradio.filter import firdes
import sip
from gnuradio import blocks
import pmt
from gnuradio import channels
from gnuradio import digital
from gnuradio import gr
import signal
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
from gnuradio.qtgui import Range, RangeWidget
import math
import satnogs
from gnuradio import qtgui

class OQPSK1(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "OQPSK_Mod_Demod")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("OQPSK_Mod_Demod")
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

        self.settings = Qt.QSettings("GNU Radio", "OQPSK1")

        try:
            if StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
                self.restoreGeometry(self.settings.value("geometry").toByteArray())
            else:
                self.restoreGeometry(self.settings.value("geometry"))
        except:
            pass

        ##################################################
        # Variables
        ##################################################
        self.sps = sps = 4
        self.nfilts = nfilts = 32
        self.variable_ieee802_15_4_variant_decoder_0 = variable_ieee802_15_4_variant_decoder_0 = satnogs.ieee802_15_4_variant_decoder_make([0x55]*12, 14, [79, 121, 97], 5, satnogs.crc.CRC32_C, satnogs.whitening.make_ccsds(True), True, 255, True)
        self.variable_ieee802_15_4_encoder_0 = variable_ieee802_15_4_encoder_0 = satnogs.ieee802_15_4_encoder_make(0x55, 12, [79, 121, 97], satnogs.crc.CRC32_C, satnogs.whitening.make_ccsds(True), True)
        self.taps = taps = [1.0, 0.25-0.25j, 0.50 + 0.10j, -0.3 + 0.2j]
        self.samp_rate = samp_rate = 205*1000
        self.rrc_taps = rrc_taps = firdes.root_raised_cosine(nfilts, nfilts, 1.0/float(sps), 0.5, 11*sps*nfilts)
        self.qpsk = qpsk = digital.constellation_rect([0.707+0.707j, -0.707+0.707j, -0.707-0.707j, 0.707-0.707j], [0, 1, 2 , 3],
        4, 2, 2, 1, 1).base()
        self.phase_bw = phase_bw = 6.28/100
        self.ntaps = ntaps = 11
        self.noise = noise = 0.0001
        self.freq_offset = freq_offset = 0.00
        self.eq_gain = eq_gain = 0.01
        self.arity = arity = 4
        self.alpha = alpha = 0.5

        ##################################################
        # Blocks
        ##################################################
        self._noise_range = Range(0.00001, 1, 0.0001, 0.0001, 200)
        self._noise_win = RangeWidget(self._noise_range, self.set_noise, 'noise', "counter_slider", float)
        self.top_grid_layout.addWidget(self._noise_win)
        self._freq_offset_range = Range(0, 1, 0.001, 0.00, 200)
        self._freq_offset_win = RangeWidget(self._freq_offset_range, self.set_freq_offset, 'freq_offset', "counter_slider", float)
        self.top_grid_layout.addWidget(self._freq_offset_win)
        self.satnogs_frame_encoder_0 = satnogs.frame_encoder(variable_ieee802_15_4_encoder_0)
        self.satnogs_frame_decoder_0 = satnogs.frame_decoder(variable_ieee802_15_4_variant_decoder_0, 1 * 1)
        self.satnogs_ber_calculator_0 = satnogs.ber_calculator(64, 10000, 10)
        self.qtgui_waterfall_sink_x_0 = qtgui.waterfall_sink_c(
            1024*4, #size
            firdes.WIN_BLACKMAN_hARRIS, #wintype
            0, #fc
            samp_rate, #bw
            "Received Signal", #name
            1 #number of inputs
        )
        self.qtgui_waterfall_sink_x_0.set_update_time(0.10)
        self.qtgui_waterfall_sink_x_0.enable_grid(False)
        self.qtgui_waterfall_sink_x_0.enable_axis_labels(True)



        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        colors = [0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_waterfall_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_waterfall_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_waterfall_sink_x_0.set_color_map(i, colors[i])
            self.qtgui_waterfall_sink_x_0.set_line_alpha(i, alphas[i])

        self.qtgui_waterfall_sink_x_0.set_intensity_range(-140, 10)

        self._qtgui_waterfall_sink_x_0_win = sip.wrapinstance(self.qtgui_waterfall_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_waterfall_sink_x_0_win)
        self.qtgui_time_sink_x_0 = qtgui.time_sink_c(
            1024, #size
            samp_rate, #samp_rate
            "", #name
            1 #number of inputs
        )
        self.qtgui_time_sink_x_0.set_update_time(0.10)
        self.qtgui_time_sink_x_0.set_y_axis(-1, 1)

        self.qtgui_time_sink_x_0.set_y_label('Amplitude', "")

        self.qtgui_time_sink_x_0.enable_tags(True)
        self.qtgui_time_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0.enable_autoscale(False)
        self.qtgui_time_sink_x_0.enable_grid(False)
        self.qtgui_time_sink_x_0.enable_axis_labels(True)
        self.qtgui_time_sink_x_0.enable_control_panel(False)
        self.qtgui_time_sink_x_0.enable_stem_plot(False)


        labels = ['Signal 1', 'Signal 2', 'Signal 3', 'Signal 4', 'Signal 5',
            'Signal 6', 'Signal 7', 'Signal 8', 'Signal 9', 'Signal 10']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ['blue', 'red', 'green', 'black', 'cyan',
            'magenta', 'yellow', 'dark red', 'dark green', 'dark blue']
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]
        styles = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1]


        for i in range(2):
            if len(labels[i]) == 0:
                if (i % 2 == 0):
                    self.qtgui_time_sink_x_0.set_line_label(i, "Re{{Data {0}}}".format(i/2))
                else:
                    self.qtgui_time_sink_x_0.set_line_label(i, "Im{{Data {0}}}".format(i/2))
            else:
                self.qtgui_time_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_time_sink_x_0_win)
        self.qtgui_const_sink_x_0 = qtgui.const_sink_c(
            1024*4, #size
            "", #name
            1 #number of inputs
        )
        self.qtgui_const_sink_x_0.set_update_time(0.10)
        self.qtgui_const_sink_x_0.set_y_axis(-2, 2)
        self.qtgui_const_sink_x_0.set_x_axis(-2, 2)
        self.qtgui_const_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, "")
        self.qtgui_const_sink_x_0.enable_autoscale(False)
        self.qtgui_const_sink_x_0.enable_grid(True)
        self.qtgui_const_sink_x_0.enable_axis_labels(True)


        labels = ['', '', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "red", "red", "red",
            "red", "red", "red", "red", "red"]
        styles = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        markers = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_const_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_const_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_const_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_const_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_const_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_const_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_const_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_const_sink_x_0_win = sip.wrapinstance(self.qtgui_const_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_const_sink_x_0_win)
        self.digital_pfb_clock_sync_xxx_1_0 = digital.pfb_clock_sync_fff(sps, 2* math.pi/100.0, rrc_taps, nfilts, nfilts/2, 2, 2)
        self.digital_pfb_clock_sync_xxx_1 = digital.pfb_clock_sync_fff(sps, 2* math.pi/100.0, rrc_taps, nfilts, nfilts/2, 2, 2)
        self.digital_diff_decoder_bb_1 = digital.diff_decoder_bb(4)
        self.digital_costas_loop_cc_0 = digital.costas_loop_cc(phase_bw, 4, False)
        self.digital_constellation_decoder_cb_0 = digital.constellation_decoder_cb(qpsk)
        self.digital_cma_equalizer_cc_0 = digital.cma_equalizer_cc(15, 1, 0.01, 2)
        self.channels_channel_model_0_0 = channels.channel_model(
            noise_voltage=noise,
            frequency_offset=freq_offset,
            epsilon=1.0,
            taps=[1],
            noise_seed=0,
            block_tags=True)
        self.blocks_unpack_k_bits_bb_0 = blocks.unpack_k_bits_bb(2)
        self.blocks_tagged_stream_multiply_length_0 = blocks.tagged_stream_multiply_length(gr.sizeof_gr_complex*1, 'packet_len', sps *8)
        self.blocks_tagged_stream_align_0 = blocks.tagged_stream_align(gr.sizeof_gr_complex*1, 'packet_len')
        self.blocks_pdu_to_tagged_stream_0 = blocks.pdu_to_tagged_stream(blocks.byte_t, 'packet_len')
        self.blocks_message_strobe_random_0 = blocks.message_strobe_random(pmt.intern("TEST"), blocks.STROBE_POISSON, 1, 1)
        self.blocks_float_to_complex_2 = blocks.float_to_complex(1)
        self.blocks_float_to_complex_0 = blocks.float_to_complex(1)
        self.blocks_delay_1 = blocks.delay(gr.sizeof_float*1, 1)
        self.blocks_complex_to_float_1 = blocks.complex_to_float(1)
        self.blocks_complex_to_float_0 = blocks.complex_to_float(1)
        self.OQPSK_mod_0 = OQPSK_mod(
            alpha=0.5,
            delay=2,
            n_taps=11,
            samp_rate=32000,
            sps=4,
            symbol_rate=1,
        )



        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_message_strobe_random_0, 'strobe'), (self.satnogs_ber_calculator_0, 'trigger'))
        self.msg_connect((self.satnogs_ber_calculator_0, 'pdu'), (self.satnogs_frame_encoder_0, 'pdu'))
        self.msg_connect((self.satnogs_frame_decoder_0, 'out'), (self.satnogs_ber_calculator_0, 'received'))
        self.msg_connect((self.satnogs_frame_encoder_0, 'pdu'), (self.blocks_pdu_to_tagged_stream_0, 'pdus'))
        self.connect((self.OQPSK_mod_0, 0), (self.blocks_tagged_stream_multiply_length_0, 0))
        self.connect((self.blocks_complex_to_float_0, 0), (self.digital_pfb_clock_sync_xxx_1, 0))
        self.connect((self.blocks_complex_to_float_0, 1), (self.digital_pfb_clock_sync_xxx_1_0, 0))
        self.connect((self.blocks_complex_to_float_1, 0), (self.blocks_delay_1, 0))
        self.connect((self.blocks_complex_to_float_1, 1), (self.blocks_float_to_complex_2, 1))
        self.connect((self.blocks_delay_1, 0), (self.blocks_float_to_complex_2, 0))
        self.connect((self.blocks_float_to_complex_0, 0), (self.digital_cma_equalizer_cc_0, 0))
        self.connect((self.blocks_float_to_complex_2, 0), (self.digital_constellation_decoder_cb_0, 0))
        self.connect((self.blocks_float_to_complex_2, 0), (self.qtgui_const_sink_x_0, 0))
        self.connect((self.blocks_float_to_complex_2, 0), (self.qtgui_time_sink_x_0, 0))
        self.connect((self.blocks_float_to_complex_2, 0), (self.qtgui_waterfall_sink_x_0, 0))
        self.connect((self.blocks_pdu_to_tagged_stream_0, 0), (self.OQPSK_mod_0, 0))
        self.connect((self.blocks_tagged_stream_align_0, 0), (self.channels_channel_model_0_0, 0))
        self.connect((self.blocks_tagged_stream_multiply_length_0, 0), (self.blocks_tagged_stream_align_0, 0))
        self.connect((self.blocks_unpack_k_bits_bb_0, 0), (self.satnogs_frame_decoder_0, 0))
        self.connect((self.channels_channel_model_0_0, 0), (self.blocks_complex_to_float_0, 0))
        self.connect((self.digital_cma_equalizer_cc_0, 0), (self.digital_costas_loop_cc_0, 0))
        self.connect((self.digital_constellation_decoder_cb_0, 0), (self.digital_diff_decoder_bb_1, 0))
        self.connect((self.digital_costas_loop_cc_0, 0), (self.blocks_complex_to_float_1, 0))
        self.connect((self.digital_diff_decoder_bb_1, 0), (self.blocks_unpack_k_bits_bb_0, 0))
        self.connect((self.digital_pfb_clock_sync_xxx_1, 0), (self.blocks_float_to_complex_0, 0))
        self.connect((self.digital_pfb_clock_sync_xxx_1_0, 0), (self.blocks_float_to_complex_0, 1))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "OQPSK1")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_sps(self):
        return self.sps

    def set_sps(self, sps):
        self.sps = sps
        self.set_rrc_taps(firdes.root_raised_cosine(self.nfilts, self.nfilts, 1.0/float(self.sps), 0.5, 11*self.sps*self.nfilts))
        self.blocks_tagged_stream_multiply_length_0.set_scalar(self.sps *8)

    def get_nfilts(self):
        return self.nfilts

    def set_nfilts(self, nfilts):
        self.nfilts = nfilts
        self.set_rrc_taps(firdes.root_raised_cosine(self.nfilts, self.nfilts, 1.0/float(self.sps), 0.5, 11*self.sps*self.nfilts))

    def get_variable_ieee802_15_4_variant_decoder_0(self):
        return self.variable_ieee802_15_4_variant_decoder_0

    def set_variable_ieee802_15_4_variant_decoder_0(self, variable_ieee802_15_4_variant_decoder_0):
        self.variable_ieee802_15_4_variant_decoder_0 = variable_ieee802_15_4_variant_decoder_0

    def get_variable_ieee802_15_4_encoder_0(self):
        return self.variable_ieee802_15_4_encoder_0

    def set_variable_ieee802_15_4_encoder_0(self, variable_ieee802_15_4_encoder_0):
        self.variable_ieee802_15_4_encoder_0 = variable_ieee802_15_4_encoder_0

    def get_taps(self):
        return self.taps

    def set_taps(self, taps):
        self.taps = taps

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.qtgui_time_sink_x_0.set_samp_rate(self.samp_rate)
        self.qtgui_waterfall_sink_x_0.set_frequency_range(0, self.samp_rate)

    def get_rrc_taps(self):
        return self.rrc_taps

    def set_rrc_taps(self, rrc_taps):
        self.rrc_taps = rrc_taps
        self.digital_pfb_clock_sync_xxx_1.update_taps(self.rrc_taps)
        self.digital_pfb_clock_sync_xxx_1_0.update_taps(self.rrc_taps)

    def get_qpsk(self):
        return self.qpsk

    def set_qpsk(self, qpsk):
        self.qpsk = qpsk

    def get_phase_bw(self):
        return self.phase_bw

    def set_phase_bw(self, phase_bw):
        self.phase_bw = phase_bw
        self.digital_costas_loop_cc_0.set_loop_bandwidth(self.phase_bw)

    def get_ntaps(self):
        return self.ntaps

    def set_ntaps(self, ntaps):
        self.ntaps = ntaps

    def get_noise(self):
        return self.noise

    def set_noise(self, noise):
        self.noise = noise
        self.channels_channel_model_0_0.set_noise_voltage(self.noise)

    def get_freq_offset(self):
        return self.freq_offset

    def set_freq_offset(self, freq_offset):
        self.freq_offset = freq_offset
        self.channels_channel_model_0_0.set_frequency_offset(self.freq_offset)

    def get_eq_gain(self):
        return self.eq_gain

    def set_eq_gain(self, eq_gain):
        self.eq_gain = eq_gain

    def get_arity(self):
        return self.arity

    def set_arity(self, arity):
        self.arity = arity

    def get_alpha(self):
        return self.alpha

    def set_alpha(self, alpha):
        self.alpha = alpha



def main(top_block_cls=OQPSK1, options=None):

    if StrictVersion("4.5.0") <= StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
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
