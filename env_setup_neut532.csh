#!/bin/csh
setenv CXX g++34
setenv CPP "gcc34 -E"
setenv CC gcc34
setenv FC g77

setenv SKLIB /usr/local/sklib_g77

setenv CERN $SKLIB/cern
setenv CERN_LEVEL 2005
setenv CERN_ROOT ${CERN}/${CERN_LEVEL}
setenv CERNLIB $CERN_ROOT/lib

setenv ROOTSYS $SKLIB/root_v5.28.00h
##for g77
setenv SKOFL_ROOT $SKLIB/skofl_11c
setenv ATMPD_ROOT $SKLIB/atmpd_11d

setenv NEUT_ROOT /disk01/usr3/cvson/nuicise/neut/neut_5.3.2


setenv MACHINE Linux_pc


if ($?LD_LIBRARY_PATH) then
 setenv LD_LIBRARY_PATH  $SKOFL_ROOT/lib:`$ROOTSYS/bin/root-config --libdir`:$LD_LIBRARY_PATH
  #setenv LD_LIBRARY_PATH $SKOFL_ROOT/lib:$ATMPD_ROOT/lib:$ROOTSYS/lib:$CERNLIB:$LD_LIBRARY_PATH
else
  setenv LD_LIBRARY_PATH  $SKOFL_ROOT/lib:`$ROOTSYS/bin/root-config --libdir`
  #LD_LIBRARY_PATH=$SKOFL_ROOT/lib:$ATMPD_ROOT/lib:$ROOTSYS/lib:$CERNLIB
endif

set PATH = ( $SKOFL_ROOT/bin $ATMPD_ROOT/bin $ROOTSYS/bin $CERN_ROOT/bin $PATH )
unset SKLIB
