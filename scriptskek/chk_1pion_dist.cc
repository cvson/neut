#include <TROOT.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TSystem.h>
#include <TMath.h>

#include <iostream>
#include <stdlib.h>

#include "../../include/neutvect.h"
#include "../../include/neutvtx.h"

using namespace std;

Int_t
fill_initial_ppi_hist(NeutVect *nvect, 
					  TH1D *h1, TH1D *h_cospi, TH1D *h_invms,
					  Double_t weight)
{
  /* select resonance single pion mode : 11, 12, 13, 31, 32, 33, 34 */

  Int_t    ip,mode;
  Int_t i;

  mode = abs(nvect->Mode);

  if (( mode < 11 ) || ( mode > 34  )){
	return 0;
  }
  if (( mode > 13 ) && ( mode < 31 )){
	return 0;
  }
  
  ip = abs((nvect->PartInfo(3))->fPID);
  /* delta absorption check */
  if ((ip == 2224)||( ip == 2214 ) || ( ip == 2114 ) || ( ip == 1114 )){
	return 0;
  }
  ip = abs((nvect->PartInfo(4))->fPID);
  if (( ip != 211 ) && ( ip != 111 )){
	cout << "IP is not pion " << ip << " mode= " << mode << endl;
	return -1;
  }

  Double_t ppi, W;
  ppi = ((nvect->PartInfo(4))->fP.P())/1000.;
  if (ppi>1.){
	cout << ppi << endl;
  }
  h1->Fill(ppi,weight);

  TLorentzVector fR;
  fR = (nvect->PartInfo(3))->fP + (nvect->PartInfo(4))->fP;
  W = sqrt(fR.E() * fR.E() - fR.P()*fR.P());
  h_invms->Fill(W/1000.,weight);

  TVector3 p1 = (nvect->PartInfo(0))->fP.Vect();
  TVector3 p2 = (nvect->PartInfo(4))->fP.Vect();
  Double_t cospi = cos(p1.Angle(p2));

  h_cospi->Fill(cospi,weight);

  return 0;
}

Int_t
fill_final_pi_hists(NeutVect *nvect, 
					TH1D *h_numpi, 
					TH1D *h_ppi, 
					TH1D *h_ppidif, 
					TH1D *h_cospi,
					Double_t weight)
{
  /* select resonance single pion mode : 11, 12, 13, 31, 32, 33, 34 */

  Int_t    ip,mode;
  Int_t i;

  mode = abs(nvect->Mode);

  if (( mode < 11 ) || ( mode > 34  )){
	return 0;
  }
  if (( mode > 13 ) && ( mode < 31 )){
	return 0;
  }
  
  ip = abs((nvect->PartInfo(3))->fPID);
  /* delta absorption check */
  if ((ip == 2224)||( ip == 2214 ) || ( ip == 2114 ) || ( ip == 1114 )){
	return 0;
  }
  ip = abs((nvect->PartInfo(4))->fPID);
  if (( ip != 211 ) && ( ip != 111 )){
	cout << "IP is not pion " << ip << " mode= " << mode << endl;
	return -1;
  }
	
  TVector3 p1,p2;
  Double_t npi = 0.5;
  Int_t idx = -1;
  Double_t cospi = 1.;
  Double_t ppi   = 0;

  for ( i = 2 ; i < nvect->Npart() ; i++ ){
	if ((nvect->PartInfo(i))->fIsAlive){
	  ip = abs((nvect->PartInfo(i))->fPID);
	  if (( ip == 211 ) || ( ip == 111 )){
		npi = npi + 1.;
		if ( ppi < (nvect->PartInfo(i))->fP.P()/1000. ){
		  ppi = ((nvect->PartInfo(i))->fP.P())/1000.;

		  p1 = (nvect->PartInfo(0))->fP.Vect();
		  p2 = (nvect->PartInfo(i))->fP.Vect();
		  cospi = cos(p1.Angle(p2));

		  idx = i;
		}
	  }
	}
  }

  h_numpi->Fill(npi, weight);
  if ( idx >= 0 ){
	h_ppidif->Fill(ppi-((nvect->PartInfo(4))->fP.P())/1000.,weight);
	h_ppi->Fill(ppi,weight);
	if ( (nvect->PartInfo(4))->fPID == (nvect->PartInfo(idx))->fPID ){
	  h_cospi->Fill(cospi,weight);
	}
  }

  return 0;
}

///////////////////////////////////////////////////////////
Int_t
chk_1pion_dist(char *fname,char *fname_out)
{

  gSystem->Load("../neutclass/neutvtx.so");
  gSystem->Load("../neutclass/neutpart.so");
  gSystem->Load("../neutclass/neutfsipart.so");
  gSystem->Load("../neutclass/neutfsivert.so");
  gSystem->Load("../neutclass/neutnucfsistep.so");
  gSystem->Load("../neutclass/neutnucfsivert.so");
  gSystem->Load("../neutclass/neutvect.so");
  
  TFile *f;
  f = new TFile(fname);
  if (f->IsZombie()){
	cout << "Failed to open " << fname << "." << endl;
	return 0;
  }

  TFile *f_out;
  f_out = new TFile(fname_out,"RECREATE");
  if (f->IsZombie()){
	cout << "Failed to open " << fname << "." << endl;
	return 0;
  }

  TTree  *tn;
  NeutVtx *nvtx;
  NeutVect *nvect;

  tn = (TTree *)(f->Get("neuttree"));
  if (tn == 0){
	cout << "Failed to find neut tree in file " << fname << "." << endl;
	return 0;
  }

  nvtx = new NeutVtx();
  tn->SetBranchAddress("vertexbranch",&nvtx);
  nvect = new NeutVect();
  tn->SetBranchAddress("vectorbranch",&nvect);

  Int_t nevents, nev;
  nevents = tn->GetEntries();

  TH1D  *h_flux, *h_rate;
  double flux_integ, rate_integ, rate_norm;
  h_flux = (TH1D *)(f->Get("fluxhisto"));
  if ( h_flux != 0 ){
	flux_integ = h_flux->GetSumOfWeights();
  }
  h_rate = (TH1D *)(f->Get("ratehisto"));
  if ( h_rate != 0 ){
	rate_integ = h_rate->GetSumOfWeights();
  }else{
	rate_integ = (double)(nevents);
  }
  cout << " flux_sum = " << flux_integ << endl;
  cout << " rate_sum = " << rate_integ << endl;

  rate_norm = rate_integ/(double)(nevents);

  TH1D *h_ppi0, *h_numpi, *h_ppi, *h_ppidif, *h_icospi, *h_fcospi;
  TH1D *h_invms;
  h_ppi0  = new TH1D("initial_ppi","Initial p_#pi",
					150, 0., 3.);
  h_invms = new TH1D("W","Invariant mass",
					 80, 1., 2.);
  h_numpi = new TH1D("numpi","Number of #pi",
		 		 10, 0., 10.);
  h_ppi   = new TH1D("final_ppi","Final p_#pi(highest momentum)",
					150, 0., 3.);
  h_ppidif= new TH1D("ppi_diff","Difference of p_#pi (highest momentum)",
					 301, -1.505, 1.505);
  h_icospi = new TH1D("cosipi","cos(#theta_#pi)(initial)",
					 100,-1., 1.);
  h_fcospi = new TH1D("cosfpi","cos(#theta_pi)(after FSI)",
					 100,-1., 1.);

  Double_t weight;
  weight = rate_norm;

  for ( nev = 0 ; nev < nevents ; nev++ ){

	if ((nev % 10000) == 0){
	  cout << "Processing event #" << nev << endl;
	}

	tn->GetEntry(nev);
	//	weight = 1.;
	fill_initial_ppi_hist(nvect, h_ppi0, h_icospi, h_invms, weight);
	fill_final_pi_hists(nvect, h_numpi, h_ppi, h_ppidif, h_fcospi, weight);

  }

  f_out->Write();
  f_out->Close();
  return 0;
}
  
int
main(int argc, char **argv)
{
  if ( argc < 3 ){
	cout << "need input filename and output filename" << endl;
	exit(0);
  }

  chk_1pion_dist(argv[1],argv[2]);

}
