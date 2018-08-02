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
					Double_t weight)
{

  Int_t    ip,mode;
  Int_t i;

  Double_t npi = 0.5;
  Double_t ppi   = 0;

  for ( i = 0 ; i < nvect->Npart() ; i++ ){
	if ((nvect->PartInfo(i))->fIsAlive){
	  ip = abs((nvect->PartInfo(i))->fPID);
	  if (( ip == 211 ) || ( ip == 111 )){
		npi = npi + 1.;
		ppi = ((nvect->PartInfo(i))->fP.P())/1000.;
		h_ppi->Fill(ppi,weight);
	  }
	}
  }

  h_numpi->Fill(npi, weight);

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

  TH1D *h_ppi0, *h_numpi, *h_ppi, *h_ppidif, *h_cospi;
  h_numpi = new TH1D("numpi","Number of #pi",
					 10, 0., 10.);
  h_ppi   = new TH1D("final_ppi","Final p_{#pi}(highest momentum)",
					300, 0., 3.);

  Double_t weight = 1.;

  for ( nev = 0 ; nev < nevents ; nev++ ){

	if ((nev % 10000) == 0){
	  cout << "Processing event #" << nev << endl;
	}

	tn->GetEntry(nev);
	weight = 1.;
	fill_final_pi_hists(nvect, h_numpi, h_ppi, weight);

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
