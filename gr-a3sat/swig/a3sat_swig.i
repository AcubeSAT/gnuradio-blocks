/* -*- c++ -*- */

#define A3SAT_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "a3sat_swig_doc.i"

%{
#include "a3sat/conv_enc.h"
#include "a3sat/conv_dec.h"
#include "a3sat/ldpc_enc.h"
#include "a3sat/ldpc_dec.h"
#include "a3sat/bch_enc.h"
#include "a3sat/bch_dec.h"
#include "a3sat/gmsk_precoder.h"
%}

%include "a3sat/conv_enc.h"
GR_SWIG_BLOCK_MAGIC2(a3sat, conv_enc);
%include "a3sat/conv_dec.h"
GR_SWIG_BLOCK_MAGIC2(a3sat, conv_dec);
%include "a3sat/ldpc_enc.h"
GR_SWIG_BLOCK_MAGIC2(a3sat, ldpc_enc);
%include "a3sat/ldpc_dec.h"
GR_SWIG_BLOCK_MAGIC2(a3sat, ldpc_dec);
%include "a3sat/bch_enc.h"
GR_SWIG_BLOCK_MAGIC2(a3sat, bch_enc);
%include "a3sat/bch_dec.h"
GR_SWIG_BLOCK_MAGIC2(a3sat, bch_dec);
%include "a3sat/gmsk_precoder.h"
GR_SWIG_BLOCK_MAGIC2(a3sat, gmsk_precoder);
