#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: uhf_band_gr_leo
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

from PyQt5 import Qt
from gnuradio import qtgui
from gnuradio.filter import firdes
import sip
from gnuradio import blocks
import numpy
from gnuradio import digital
from gnuradio import gr
import sys
import signal
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
import leo
from gnuradio import qtgui

class uhf_band_gr_leo(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "uhf_band_gr_leo")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("uhf_band_gr_leo")
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

        self.settings = Qt.QSettings("GNU Radio", "uhf_band_gr_leo")

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
        self.Dipole_Antenna = Dipole_Antenna = leo.dipole_antenna_make(5, 436e6, 2, 80)
        self.Helical_Antenna = Helical_Antenna = leo.helix_antenna_make(1, 436e6,0, 0, 8, 0.1725, 0.689)
        self.AcubeSAT = AcubeSAT = leo.satellite_make('TLE_1', '1 69696U 16025E   23183.00000000  .00002000  00000-0  49111-4 0  6969', '2 69696  97.3759 191.5890 0001000 000.0000 000.0000 15.24261762696969', 436e6, 436e6, 30, Dipole_Antenna, Dipole_Antenna, 1, 315, 10000)
        self.AUTH_GS = AUTH_GS = leo.tracker_make(AcubeSAT, 22.959887, 40.627233, 0.056, '2023-07-03T15:25:00.000000Z', '2023-07-03T15:32:00.000000Z', 1000, 436e6, 436e6, 30, Helical_Antenna, Helical_Antenna, 0.4, 345, 10000)
        self.samp_rate_0 = samp_rate_0 = 20000
        self.samp_rate = samp_rate = 100000
        self.UHF_Band_LEO_Model = UHF_Band_LEO_Model = leo.leo_model_make(AUTH_GS, 0, 5,
          													6, 7,
          													1, 3,
          													True, 7.5, 0, 25)

        ##################################################
        # Blocks
        ##################################################
        self.qtgui_waterfall_sink_x_0 = qtgui.waterfall_sink_c(
            1024*4, #size
            firdes.WIN_BLACKMAN_hARRIS, #wintype
            0, #fc
            samp_rate, #bw
            "Received Signal", #name
            1 #number of inputs
        )
        self.qtgui_waterfall_sink_x_0.set_update_time(0.10)
        self.qtgui_waterfall_sink_x_0.enable_grid(True)
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
        self.digital_gmsk_mod_0 = digital.gmsk_mod(
            samples_per_symbol=2,
            bt=0.35,
            verbose=False,
            log=False)
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_gr_complex*1, samp_rate,True)
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_cc(10000000)
        self.analog_random_source_x_0 = blocks.vector_source_b(list(map(int, numpy.random.randint(0, 255, 10000))), True)
        self.S_Band_Downlink = leo.channel_model(samp_rate, UHF_Band_LEO_Model, 1)



        ##################################################
        # Connections
        ##################################################
        self.connect((self.S_Band_Downlink, 0), (self.blocks_throttle_0, 0))
        self.connect((self.analog_random_source_x_0, 0), (self.digital_gmsk_mod_0, 0))
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.S_Band_Downlink, 0))
        self.connect((self.blocks_throttle_0, 0), (self.qtgui_waterfall_sink_x_0, 0))
        self.connect((self.digital_gmsk_mod_0, 0), (self.blocks_multiply_const_vxx_0, 0))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "uhf_band_gr_leo")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_Dipole_Antenna(self):
        return self.Dipole_Antenna

    def set_Dipole_Antenna(self, Dipole_Antenna):
        self.Dipole_Antenna = Dipole_Antenna
        self.Dipole_Antenna.set_pointing_error(80)

    def get_Helical_Antenna(self):
        return self.Helical_Antenna

    def set_Helical_Antenna(self, Helical_Antenna):
        self.Helical_Antenna = Helical_Antenna
        self.Helical_Antenna.set_pointing_error(0)

    def get_AcubeSAT(self):
        return self.AcubeSAT

    def set_AcubeSAT(self, AcubeSAT):
        self.AcubeSAT = AcubeSAT

    def get_AUTH_GS(self):
        return self.AUTH_GS

    def set_AUTH_GS(self, AUTH_GS):
        self.AUTH_GS = AUTH_GS

    def get_samp_rate_0(self):
        return self.samp_rate_0

    def set_samp_rate_0(self, samp_rate_0):
        self.samp_rate_0 = samp_rate_0

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)
        self.qtgui_waterfall_sink_x_0.set_frequency_range(0, self.samp_rate)

    def get_UHF_Band_LEO_Model(self):
        return self.UHF_Band_LEO_Model

    def set_UHF_Band_LEO_Model(self, UHF_Band_LEO_Model):
        self.UHF_Band_LEO_Model = UHF_Band_LEO_Model



def main(top_block_cls=uhf_band_gr_leo, options=None):

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
