
//  neutroot flux histogram interface
//
//  2011.08: First version by S. Tobayama

#include <iostream>
#include <string>
#include <stdlib.h>
#include <TFile.h>

#include "ufm2th1dist.h"

using namespace std;

#if defined(g77)
#define FUNCTION_RETURN double
#else
#define FUNCTION_RETURN float
#endif

extern "C"
{

  FUNCTION_RETURN fntotpau_(int *,float *);
  
  void nulltermstr(char *, int);
  
  int loadflx_(int *, char *, char *, int *, 
			   int, int);

  FUNCTION_RETURN rndenuevtrt_(float *);

}

const char
flavor_string[4][10] =
  {
	"numu","numub","nue","nueb"
  };

const char
flavor_title[4][20] =
  {
	"#nu_{#mu}","#bar{#nu}_{#mu}","#nu_{e}","#bar{#nu}_{e}"
  };

const int
pidtbl[4] =
  {
	14,-14,12,-12
  };

Ufm2TH1dist EnuEvtrt;

void
nulltermstr(char *str, int len)
{
  int i;
  for (i = 0 ; i < len ; i++){
    if (str[i] == ' '){
      str[i]='\0';
      break;
    }
  }
}

int loadflx_(int *IDPTEVCT, char *filename, char *histname, int *inMeV, 
			 int fnlen, int hnlen)
{
  int i;
  int pididx;
  int nbins;//number of bins
  Double_t *BEdgs;
  double EScl;
  double tcrs;
  float ebinctr;
  TH1D *hflxr, *hflx, *hrate;
  TH1D *h_flux, *h_rate;
  char cPath[256];
  
  for (i=0; i<4; i++) {
    if (*IDPTEVCT==pidtbl[i]) {
      pididx=i;
    }
  }
  
  nulltermstr(filename,fnlen);
  nulltermstr(histname,hnlen);
  
  strcpy(cPath,gDirectory->GetPath());
  TFile histfile(filename,"READ");
  gDirectory->cd(cPath);
  if (histfile.IsZombie()){
    cout << "Flux histogram ROOT file '" << filename << "' does not exist!" << endl;
    return -1;
  }
  else {
    cout << "Input ROOT file: " << filename << endl;
  }
  
  hflxr = (TH1D*)(histfile.Get(histname));
  
  if (hflxr==0){
    cout << "Histogram '" << histname << "' does not exist in '" << filename << "'!" << endl;
    return -1;
  }
  else {
    cout << "Using flux histogram: " << histname << endl;
  }
  
  cout << "Neutrino flavor: " << flavor_string[pididx] << endl;
  
  if (*inMeV==1) {
    cout << "FLux histogram in MeV" << endl;
    EScl=1e-3;
  }
  else {
    cout << "Flux histogram in GeV" << endl;
    EScl=1.;
  }
  
  nbins=hflxr->GetNbinsX();
  BEdgs = new Double_t [nbins+1];
  for (i=0; i<=nbins; i++) {
    BEdgs[i]=hflxr->GetBinLowEdge(i+1)*EScl;//Bin edges in GeV
  }
  
  hflx = new TH1D(Form("flux_%s",flavor_string[pididx]),
                  Form("%s flux",flavor_title[pididx]),nbins,BEdgs);//Flux histogram
  hrate = new TH1D(Form("evtrt_%s",flavor_string[pididx]),
                   Form("%s event rate",flavor_title[pididx]),nbins,BEdgs);//Event rate histogram
  hflx->GetXaxis()->SetTitle("E_{#nu} (GeV)");
  hrate->GetXaxis()->SetTitle("E_{#nu} (GeV)");
  
  for (i=1; i<=nbins; i++) {
    ebinctr=(float)(hflx->GetXaxis()->GetBinCenter(i));
    tcrs=fntotpau_(IDPTEVCT,&ebinctr);
    hflx->SetBinContent(i,hflxr->GetBinContent(i));
    hrate->SetBinContent(i,hflxr->GetBinContent(i)*tcrs);
  }
  
  EnuEvtrt.Init(hrate);//Initialize using event rate histogram
  
  h_flux = (TH1D *)hflx->Clone("fluxhisto");
  h_rate = (TH1D *)hrate->Clone("ratehisto");

  TFile ofile(Form("%s_o.root",histname), "RECREATE");
  hflx->Write();// Write histograms to file
  hrate->Write();
  h_flux->Write();
  h_rate->Write();

  ofile.Close();// Close the file
  
  delete [] BEdgs;
  
  return 0;
}

FUNCTION_RETURN rndenuevtrt_(float *Rnd)
{
  FUNCTION_RETURN Enu;
  double rnum=*Rnd;
  Enu=EnuEvtrt.GetValue(rnum);
  return Enu*1e3;//Enu in MeV
}
