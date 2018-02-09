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
fill_initial_ppi_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
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

  Double_t
  ppi = ((nvect->PartInfo(4))->fP.P())/1000.;
  h1->Fill(ppi,weight);

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

  for ( i = nvect->Nprimary() ; i < nvect->Npart() ; i++ ){
	if ((nvect->PartInfo(i))->fIsAlive){
	  ip = abs((nvect->PartInfo(i))->fPID);
	  if (( ip == 211 ) || ( ip == 111 )){
		npi = npi + 1.;
		if ( ppi < (nvect->PartInfo(i))->fP.P()/1000. ){
		  ppi = ((nvect->PartInfo(i))->fP.P())/1000.;

		  p1 = (nvect->PartInfo(4))->fP.Vect();
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
	h_cospi->Fill(cospi,weight);
  }

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
  h_ppi0  = new TH1D("initial_ppi","Initial p_{#pi}",
					300, 0., 3.);
  h_numpi = new TH1D("numpi","Number of #pi",
					 10, 0., 10.);
  h_ppi   = new TH1D("final_ppi","Final p_{#pi}(highest momentum)",
					300, 0., 3.);
  h_ppidif= new TH1D("ppi_diff","Difference of p_{#pi}(highest momentum)",
					 301, -1.505, 1.505);
  h_cospi = new TH1D("cospi","cos({#pi})(highest momentum)",
					 200,-1., 1.);

  Double_t weight = 1.;

  for ( nev = 0 ; nev < nevents ; nev++ ){

	if ((nev % 10000) == 0){
	  cout << "Processing event #" << nev << endl;
	}

	tn->GetEntry(nev);
	weight = 1.;
	fill_initial_ppi_hist(nvect, h_ppi0, weight);
	fill_final_pi_hists(nvect, h_numpi, h_ppi, h_ppidif, h_cospi, weight);

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
