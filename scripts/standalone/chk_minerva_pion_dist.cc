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
fill_final_pi_hists(NeutVect *nvect, 
					TH1D *h_numpi, 
					TH1D *h_ppi, 
					TH1D *h_pp1, 
					TH2D *h_W_numpi,
					Double_t weight)
{
  Int_t    ip,mode;
  Int_t i;

  mode = abs(nvect->Mode);
  if (abs(mode)==2) return 0; /* skip 2p2h */

  ip = abs((nvect->PartInfo(3))->fPID);
  /* delta absorption check */
  if ((ip == 2224)||( ip == 2214 ) || ( ip == 2114 ) || ( ip == 1114 )){
	return 0;
  }
	
  TVector3 p1,p2;
  TVector3 p3nu, p3N, p3l, p3W;
  Double_t Enu, EN, El, EW, W;
  Int_t npi =0;
  Int_t idx = -1;
  Double_t cospi = 1.;
  Double_t ppi   = 0;
  Double_t Epi   = 0;

  npi = 0;
  p3nu = (nvect->PartInfo(0))->fP.Vect();
  p3N  = (nvect->PartInfo(1))->fP.Vect();
  p3l  = (nvect->PartInfo(2))->fP.Vect();

  Enu  = (nvect->PartInfo(0))->fP.E();
  EN   = (nvect->PartInfo(1))->fP.E();
  El   = (nvect->PartInfo(2))->fP.E();
  
  EW   = Enu+EN-El;
  p3W  = p3nu+p3N-p3l;
  
  W    = sqrt(EW*EW-p3W*p3W);
  //  h_W->Fill(W/1000., weight);
  if (W<1800){
	for ( i = 0 ; i < nvect->Npart() ; i++ ){
	  if ((nvect->PartInfo(i))->fIsAlive){
		ip = abs((nvect->PartInfo(i))->fPID);
		//		if (( ip == 211 ) || ( ip == 111 )){
		if ( ip == 211 ){
		  Epi = ((nvect->PartInfo(i))->fP.E())/1000.;
		  ppi = ((nvect->PartInfo(i))->fP.P())/1000.;
		  
		  npi = npi + 1.;
		  h_ppi->Fill(ppi,weight);
		  idx = i;
		}
	  }
	}
  }
  
  h_numpi->Fill(npi+0.5, weight);
  if (npi > 0){
	h_pp1->Fill(((nvect->PartInfo(3))->fP.P())/1000.,
				weight);
  }
  h_W_numpi->Fill(W/1000.,npi+0.5, weight);
  return 0;
}

///////////////////////////////////////////////////////////
Int_t
chk_pion_dist(char *fname,char *fname_out)
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

  TH1D *h_ppi0, *h_numpi, *h_ppi, *h_pp1;
  TH2D *h_W_numpi;
  h_ppi0  = new TH1D("initial_ppi","Initial p_{#pi}",
					300, 0., 3.);
  h_numpi = new TH1D("numpi","Number of #pi",
					 10, 0., 10.);
  h_ppi   = new TH1D("final_ppi","Final p_{#pi} all",
					300, 0., 3.);
  h_pp1   = new TH1D("pp1","P_proton before rescat",
					 300, 0., 3.);
  h_W_numpi = new TH2D("W_vs_numpi","W_vs_numpi",
					   18, 0., 1.8,
					   10, 0., 10.);
  
  Double_t weight = 1.;

  for ( nev = 0 ; nev < nevents ; nev++ ){

	if ((nev % 10000) == 0){
	  cout << "Processing event #" << nev << endl;
	}

	tn->GetEntry(nev);
	weight = 1.;
	fill_final_pi_hists(nvect, h_numpi, h_ppi, h_pp1, h_W_numpi, weight);

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

  chk_pion_dist(argv[1],argv[2]);

}
