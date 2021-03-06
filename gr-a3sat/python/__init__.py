#
# Copyright 2008,2009 Free Software Foundation, Inc.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

# The presence of this file turns this directory into a Python package

'''
This is the GNU Radio A3SAT module. Place your Python package
description here (python/__init__.py).
'''
from __future__ import unicode_literals

# import swig generated symbols into the a3sat namespace
try:
    # this might fail if the module is python-only
    from .a3sat_swig import *
except ModuleNotFoundError:
    pass

# import any pure python here
#
