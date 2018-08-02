#!/bin/csh
#setenv CERN /home/skofl/sklib_g77/cern
setenv CERN /home/skofl/sklib_gcc4.8.5/cern
setenv CERN_LEVEL 2005
setenv CERN_ROOT ${CERN}/${CERN_LEVEL}
setenv PATH ${CERN_ROOT}/bin:$PATH
#setenv CERNLIB $CERN_ROOT/lib
