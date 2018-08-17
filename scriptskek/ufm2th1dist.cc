
//  Class to convert a random number drawn from [0,1) uniform distribution
//  into a random number following a TH1D distribution.
//
//  2011.08: First version by S. Tobayama

#include "ufm2th1dist.h"
#include <iostream>
using namespace std;

Ufm2TH1dist::~Ufm2TH1dist()
{
  delete [] binEdgs;
  delete [] binIntg;
}

void Ufm2TH1dist::Init(TH1D* hist)//Initialize using specified histogram
{
  TH1D htmp(*hist);
  Double_t *bItgtmp;
  nbin=htmp.GetNbinsX();
  binEdgs = new Double_t [nbin+1];
  binIntg = new Double_t [nbin+1];
  Double_t rCmpInt=htmp.ComputeIntegral();//should return 1.
  bItgtmp = htmp.GetIntegral();
  for (int i=0; i<=nbin; i++) {
    binEdgs[i]=htmp.GetBinLowEdge(i+1);
    binIntg[i]=bItgtmp[i];
  }
  binEdgs[nbin] = binEdgs[nbin-1]+htmp.GetBinWidth(nbin-1);
}

double Ufm2TH1dist::GetValue(double rnd)
{
  double tmp;
  for (int i=1; i<=nbin; i++) {
    if (rnd<binIntg[i]) {
      tmp=binEdgs[i-1]+(binEdgs[i]-binEdgs[i-1])*(rnd-binIntg[i-1])/(binIntg[i]-binIntg[i-1]);
      break;
    }
  }
  return tmp;
}
