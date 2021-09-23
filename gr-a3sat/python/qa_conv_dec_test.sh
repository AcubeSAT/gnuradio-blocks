#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir="/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/python"
export GR_CONF_CONTROLPORT_ON=False
export PATH="/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/python":$PATH
export LD_LIBRARY_PATH="":$LD_LIBRARY_PATH
export PYTHONPATH=/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig:$PYTHONPATH
/usr/bin/python3 /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/python/qa_conv_dec.py 
