#include <TROOT.h>
#include <TTree.h>
#include <TH1D.h>
#include <TFile.h>
#include <TSystem.h>
#include <TMath.h>

#include <iostream>
#include <stdlib.h>

#include "../../include/neutvect.h"
#include "../../include/neutvtx.h"

using namespace std;

bool 
isCC(int mode)
{
  if ( abs(mode) < 30 ){
	return true;
  }
  return false;

}

bool 
isNC(int mode)
{
  if ( abs(mode) >= 30 ){
	return true;
  }
  return false;

}

bool 
isCC1pi(int mode)
{
  /* CC1pi : 11, 12, 13 , -11, -12, -13 */

  if (( abs(mode) > 10 )&&( abs(mode) < 14 )){
	return true;
  }
  return false;

}

bool 
isCCdis(int mode)
{
  /* CCDIS : 21(W<2), 26(W>2) */

  if (( abs(mode) == 21 )||( abs(mode) == 26  )){
	return true;
  }
  return false;

}

bool
isLepton(Int_t ip)
{

  if (( ip != 12 ) && ( ip != 14 ) && ( ip != 16 ) &&
	  ( ip != 11 ) && ( ip != 13 ) && ( ip != 15 )){
	cout << "IP is not lepton.. " << ip << endl;
	return false;
  }
  return true;
  
}

/* generic functions */
Int_t
fill_energy(NeutVect *nvect, Int_t idx, TH1D *h1, Double_t weight)
{
  Double_t energy;
  
  energy = (nvect->PartInfo(idx))->fP.E();
  energy = energy / 1000.;
  h1->Fill(energy,weight);
  
  return 0;

}

Int_t
fill_momentum(NeutVect *nvect, Int_t idx, TH1D *h1, Double_t weight)
{
  Double_t p;
  
  p = (nvect->PartInfo(idx))->fP.P();
  p = p / 1000.;
  h1->Fill(p,weight);

  return 0;

}

Int_t
fill_costhetaL(NeutVect *nvect, Int_t idx, TH1D *h1, Double_t weight)
{
  Double_t costhetaL;

  if ( (nvect->PartInfo(idx))->fP.P() > 0 ){
	costhetaL = 
	  (nvect->PartInfo(idx))->fP.Pz() /
	  (nvect->PartInfo(idx))->fP.P();
  }else{
	return 0;
  }

  h1->Fill(costhetaL,weight);
  return 0;

}

Int_t
fill_phiL(NeutVect *nvect, Int_t idx, TH1D *h1, Double_t weight)
{
  Double_t phiL;

  if ( (nvect->PartInfo(idx))->fP.P() > 0 ){
	phiL = TMath::ATan2((nvect->PartInfo(idx))->fP.Py(),
						(nvect->PartInfo(idx))->fP.Px());
  }else{
	return 0;
  }
	
  h1->Fill(phiL,weight);
  return 0;

}

Int_t
fill_opening_angle(NeutVect *nvect, int idx1, int idx2, TH1D *h1, 
				   Double_t weight)
{
  TVector3 p1,p2;
  Double_t costheta;
  
  p1 = (nvect->PartInfo(idx1))->fP.Vect();
  p2 = (nvect->PartInfo(idx2))->fP.Vect();

  costheta = cos(p1.Angle(p2));

  h1->Fill(costheta,weight);
  
}

/////////////////////////////////////////////////////////////////////////
Int_t
fill_in_enu_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
  Int_t    ip;

  ip = (nvect->PartInfo(0))->fPID;
  if (( ip != 12 ) && ( ip != 14 ) && ( ip != 16 )){
	cout << "IP is not neutrino.. " << ip << endl;
	return -1;
  }
	
  fill_energy(nvect, 0, h1, weight);

  return 0;
}

Int_t
fill_out_plep_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
  Int_t    idx,ip;
  
  if (abs(nvect->Mode)==2){
	idx = 3;
  }else{
	idx = 2;
  }

  ip = (nvect->PartInfo(idx))->fPID;
  if (isLepton(ip)){
	fill_momentum(nvect, idx, h1, weight);
  }else{
	return -1;
  }
  return 0;
}

Int_t
fill_in_pnuc1_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
  Int_t    ip,mode;

  mode = abs(nvect->Mode);

  if (( mode == 16 ) || ( mode == 36 )){
	return 0;
  }

  ip = (nvect->PartInfo(1))->fPID;
  if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
	  ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
	cout << "IP is not nucleon " << ip << " mode= " << mode << endl;
	return -1;
  }
	
  fill_momentum(nvect, 1, h1, weight);

  return 0;
}

Int_t
fill_in_pnuc2_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
  /* only for 2p2h interaction */

  Int_t    ip,mode;

  mode = abs(nvect->Mode);

  if ( mode != 2 ){
	return 0;
  }

  ip = (nvect->PartInfo(2))->fPID;
  if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
	  ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
	cout << "IP is not nucleon " << ip << endl;
	return -1;
  }
	
  fill_momentum(nvect, 2, h1, weight);

  return 0;
}

Int_t
fill_out_pnuc1_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{

  Int_t    idx,ip;
  Int_t    mode;

  Double_t e1,e2;

  idx = 3;

  mode = abs(nvect->Mode);

  if (( mode == 16 ) || ( mode == 36 )){
	return 0;
  }

  if ( mode == 2 ){
	idx = 4;
	e1 = (nvect->PartInfo(4))->fP.E();
	e2 = (nvect->PartInfo(5))->fP.E();
	if ( e1 < e2 ){
	  idx = 5;
	}
  }

  ip = (nvect->PartInfo(idx))->fPID;
  if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
	  ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
	cout << "IP is not nucleon " << ip << endl;
	return -1;
  }
	
  fill_momentum(nvect, idx, h1, weight);

  return 0;
}

Int_t
fill_out_pnuc2_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
  /* only for 2p2h interaction */

  Int_t    idx,ip,mode;

  Double_t e1,e2;

  idx = 5;

  mode = abs(nvect->Mode);

  if ( mode == 2 ){
	e1 = (nvect->PartInfo(4))->fP.E();
	e2 = (nvect->PartInfo(5))->fP.E();
	if ( e1 < e2 ){
	  idx = 4;
	}
  }else{
	return 0;
  }

  ip = (nvect->PartInfo(idx))->fPID;
  if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
	  ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
	cout << "IP is not nucleon " << ip << endl;
	return -1;
  }
	
  fill_momentum(nvect, idx, h1, weight);

  return 0;
}

Int_t
fill_coslep_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
  Int_t    idx,ip,mode;
  Double_t coslep;

  idx = 2;

  mode = abs(nvect->Mode);

  if ( mode == 2 ){
	idx = 3;
  }

  ip = abs((nvect->PartInfo(idx))->fPID);
  if (isLepton(ip)){
	coslep = (nvect->PartInfo(0))->fP.Vect()*(nvect->PartInfo(idx))->fP.Vect();
	coslep = coslep / 
	  ((nvect->PartInfo(0))->fP.P()*(nvect->PartInfo(idx))->fP.P());
	h1->Fill(coslep,weight);
  }else{
	return -1;
  }
  return 0;
}

Int_t
fill_q2_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
  Int_t    idx,ip,mode;
  TLorentzVector q4;
  Double_t q2;

  idx = 2;

  mode = abs(nvect->Mode);

  if ( mode == 2 ){
	idx = 3;
  }

  ip = abs((nvect->PartInfo(idx))->fPID);
  if (isLepton(ip)){
	q4 =  (nvect->PartInfo(idx))->fP - (nvect->PartInfo(0))->fP;
	q2 = q4 * q4;
	q2 = q2 / 1000. / 1000.;
	h1->Fill(q2,weight);
  }else{
	return -1;
  }
  return 0;
}

Int_t
fill_in_dir_costhetaL_nuc1_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{

  Int_t    idx,ip;
  Int_t    mode;

  idx = 1;

  mode = abs(nvect->Mode);

  if (( mode == 16 ) || ( mode == 36 )){
	return 0;
  }

  if ( mode == 2 ){
	idx = 2;
  }

  ip = (nvect->PartInfo(idx))->fPID;
  if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
	  ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
	cout << "IP is not nucleon " << ip << endl;
	return -1;
  }
	
  fill_costhetaL(nvect, idx, h1, weight);

  return 0;
}

Int_t
fill_in_dir_costhetaL_nuc2_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{

  Int_t    idx,ip;
  Int_t    mode;

  mode = abs(nvect->Mode);
  if ( mode != 2 ){
	return 0;
  }

  idx = 2;

  ip = (nvect->PartInfo(idx))->fPID;
  if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
	  ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
	cout << "IP is not nucleon " << ip << endl;
	return -1;
  }
	
  fill_costhetaL(nvect, idx, h1, weight);

  return 0;
}

Int_t
fill_in_dir_phiL_nuc1_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{

  Int_t    idx,ip;
  Int_t    mode;

  idx = 1;

  mode = abs(nvect->Mode);

  if (( mode == 16 ) || ( mode == 36 )){
	return 0;
  }

  if ( mode == 2 ){
	idx = 2;
  }

  ip = (nvect->PartInfo(idx))->fPID;
  if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
	  ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
	cout << "IP is not nucleon " << ip << endl;
	return -1;
  }
	
  fill_phiL(nvect, idx, h1, weight);

  return 0;
}

Int_t
fill_in_dir_phiL_nuc2_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{

  Int_t    idx,ip;
  Int_t    mode;

  mode = abs(nvect->Mode);
  if ( mode != 2 ){
	return 0;
  }

  idx = 2;

  ip = (nvect->PartInfo(idx))->fPID;
  if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
	  ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
	cout << "IP is not nucleon " << ip << endl;
	return -1;
  }
	
  fill_phiL(nvect, idx, h1, weight);

  return 0;
}

Int_t
fill_in_nucs_opening_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{

  Int_t    idx1,idx2,ip;
  Int_t    mode;

  mode = abs(nvect->Mode);
  if ( mode != 2 ){
	return 0;
  }

  idx1 = 1;
  idx2 = 2;

  fill_opening_angle(nvect, idx1, idx2, h1, weight);

  return 0;
}

Int_t
fill_out_nucs_opening_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{

  Int_t    idx1,idx2,ip;
  Int_t    mode;

  mode = abs(nvect->Mode);
  if ( mode != 2 ){
	return 0;
  }

  idx1 = 4;
  idx2 = 5;

  fill_opening_angle(nvect, idx1, idx2, h1, weight);

  return 0;
}

Int_t
fill_out_dir_costhetaL_nuc1_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{

  Int_t    idx,ip;
  Int_t    mode;

  Double_t e1,e2;

  idx = 3;

  mode = abs(nvect->Mode);

  if (( mode == 16 ) || ( mode == 36 )){
	return 0;
  }

  if ( mode == 2 ){
	idx = 4;
	e1 = (nvect->PartInfo(4))->fP.E();
	e2 = (nvect->PartInfo(5))->fP.E();
	if ( e1 < e2 ){
	  idx = 5;
	}
  }

  ip = (nvect->PartInfo(idx))->fPID;
  if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
	  ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
	cout << "IP is not nucleon " << ip << endl;
	return -1;
  }
	
  fill_costhetaL(nvect, idx, h1, weight);

  return 0;
}

Int_t
fill_out_dir_costhetaL_nuc2_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
  /* only for 2p2h interaction */

  Int_t    idx,ip,mode;

  Double_t e1,e2;

  idx = 5;

  mode = abs(nvect->Mode);

  if ( mode == 2 ){
	e1 = (nvect->PartInfo(4))->fP.E();
	e2 = (nvect->PartInfo(5))->fP.E();
	if ( e1 < e2 ){
	  idx = 4;
	}
  }else{
	return 0;
  }

  ip = (nvect->PartInfo(idx))->fPID;
  if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
	  ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
	cout << "IP is not nucleon " << ip << endl;
	return -1;
  }
	
  fill_costhetaL(nvect, idx, h1, weight);

  return 0;
}

Int_t
fill_out_dir_phiL_nuc1_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{

  Int_t    idx,ip;
  Int_t    mode;

  Double_t e1,e2;

  idx = 3;

  mode = abs(nvect->Mode);

  if (( mode == 16 ) || ( mode == 36 )){
	return 0;
  }

  if ( mode == 2 ){
	idx = 4;
	e1 = (nvect->PartInfo(4))->fP.E();
	e2 = (nvect->PartInfo(5))->fP.E();
	if ( e1 < e2 ){
	  idx = 5;
	}
  }

  ip = (nvect->PartInfo(idx))->fPID;
  if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
	  ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
	cout << "IP is not nucleon " << ip << endl;
	return -1;
  }
	
  fill_phiL(nvect, idx, h1, weight);

  return 0;
}

Int_t
fill_out_dir_phiL_nuc2_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
  /* only for 2p2h interaction */

  Int_t    idx,ip,mode;

  Double_t e1,e2;

  idx = 5;

  mode = abs(nvect->Mode);

  if ( mode == 2 ){
	e1 = (nvect->PartInfo(4))->fP.E();
	e2 = (nvect->PartInfo(5))->fP.E();
	if ( e1 < e2 ){
	  idx = 4;
	}
  }else{
	return 0;
  }

  ip = (nvect->PartInfo(idx))->fPID;
  if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
	  ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
	cout << "IP is not nucleon " << ip << endl;
	return -1;
  }
	
  fill_phiL(nvect, idx, h1, weight);

  return 0;
}

Int_t
fill_rescat_pnuc1_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{

  Int_t    first_idx,ip,i,idx;
  Int_t    mode;

  Double_t e1,e2;

  first_idx = 3;

  mode = abs(nvect->Mode);

  if (( mode == 16 ) || ( mode == 36 )){
	return 0;
  }

  if ( mode == 2 ){
	idx = 4;
  }

  e1 = 0;
  idx = first_idx;
  for ( i = first_idx; i < nvect->Npart(); i++ ){
	if ((nvect->PartInfo(i))->fIsAlive){
	  ip = (nvect->PartInfo(idx))->fPID;
	  if (( ip == 2212 ) || ( ip == 2112 )){
		e2 = (nvect->PartInfo(i))->fP.E();
		if ( e2 > e1 ){
		  e1 = e2;
		  idx = i;
		}
	  }
	}
  }
	
  fill_momentum(nvect, idx, h1, weight);

  return 0;
}


Int_t
fill_histograms(NeutVect *nvect, TH1D *h[][19][6], int idx, int ip_idx,
				double xnorm)
{

  //  0: neutrino energy
  //  1: momentum of outgoing lepton
  //
  //  2: momentum of initial nucleon #1
  //  3: momentum of initial nucleon #2
  //  
  //  4: momentum of scattered nucleon before FSI #1
  //  5: momentum of scattered nucleon before FSI #2 
  //  
  //  6: scattered angle of lepton
  //  7: q2
  //    
  //  8: energy conservation
  //  9: momentum conservation ( x )
  // 10: momentum conservation ( y )
  // 11: momentum conservation ( z )
  //
  // 12: initial nucleon #1 direction in Lab. ( cos \theta_Lab )
  // 13: initial nucleon #2 direction in Lab. ( cos \theta_Lab )
  ///
  // 14: initial nucleon #1 direction in Lab. ( \phi_Lab )
  // 15: initial nucleon #2 direction in Lab. ( \phi_Lab )
  //  
  // 16: outgoing nucleon #1 direction in Lab. ( cos \theta_Lab )
  // 17: outgoing nucleon #2 direction in Lab. ( cos \theta_Lab )
  //
  // 18: outgoing nucleon #1 direction in Lab. ( \phi_Lab )
  // 19: outgoing nucleon #2 direction in Lab. ( \phi_Lab )

  fill_in_enu_hist(nvect,   h[idx][0][ip_idx], xnorm);
  fill_out_plep_hist(nvect, h[idx][1][ip_idx], xnorm);

  fill_in_pnuc1_hist(nvect, h[idx][2][ip_idx], xnorm);
  fill_in_pnuc2_hist(nvect, h[idx][3][ip_idx], xnorm);

  fill_out_pnuc1_hist(nvect, h[idx][4][ip_idx], xnorm);
  fill_out_pnuc2_hist(nvect, h[idx][5][ip_idx], xnorm);

  fill_coslep_hist(nvect, h[idx][6][ip_idx], xnorm);
  fill_q2_hist(nvect,     h[idx][7][ip_idx], xnorm);

  fill_in_dir_costhetaL_nuc1_hist(nvect, h[idx][8][ip_idx], xnorm);
  fill_in_dir_costhetaL_nuc2_hist(nvect, h[idx][9][ip_idx], xnorm);

  fill_in_dir_phiL_nuc1_hist(nvect, h[idx][10][ip_idx], xnorm);
  fill_in_dir_phiL_nuc2_hist(nvect, h[idx][11][ip_idx], xnorm);

  fill_out_dir_costhetaL_nuc1_hist(nvect, h[idx][12][ip_idx], xnorm);
  fill_out_dir_costhetaL_nuc2_hist(nvect, h[idx][13][ip_idx], xnorm);

  fill_out_dir_phiL_nuc1_hist(nvect, h[idx][14][ip_idx], xnorm);
  fill_out_dir_phiL_nuc2_hist(nvect, h[idx][15][ip_idx], xnorm);

  fill_rescat_pnuc1_hist(nvect, h[idx][16][ip_idx], xnorm);

  fill_in_nucs_opening_hist(nvect, h[idx][17][ip_idx], xnorm);
  fill_out_nucs_opening_hist(nvect, h[idx][18][ip_idx], xnorm);

  return 0;
}

Int_t
load_neut_shared_objects()
{
  return 0;
}

Int_t
basic_histos_nonorm(char *fname,char *fname_out)
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

  Int_t nevents;
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
  }
  cout << " flux_sum = " << flux_integ << endl;
  cout << " rate_sum = " << rate_integ << endl;

  rate_norm = 1. ;/*rate_integ/(double)(nevents)*/

  cout << " rate_norm = " << rate_norm << endl;

  TH1D *h_combined[5][19][6];
  TH1D *h_indiv[60][19][6];
  TH1D *h_modes;

  char hist_kind[8][16]={"all\0"    ,"CCall\0"    ,"NCall\0",
						 "CCQE\0"   ,"CCMEC\0"    ,"CC1pi\0",
						 "CCDIS\0"};

  char hist_type[19][16]={"enu\0"          ,"plep\0"       ,"in_nuc1_p\0",
						  "in_nuc2_p\0"    ,"out_nuc1_p\0" ,"out_nuc2_p\0",
						  "coslep\0"       ,"q2\0"         ,"in_nuc1_cosL\0",
						  "in_nuc2_cosL\0","in_nuc1_phiL\0","in_nuc2_phiL\0",
						  "out_nuc1_cosL\0","out_nuc2_cosL\0",
						  "out_nuc1_phiL\0","out_nuc2_phiL\0",
						  "rescat_nuc1_p\0",
						  "in_nucs_open\0", "out_nucs_open\0"};
						  
  char flavor_str[6][16]={"nue\0"  ,"numu\0"    ,"nutau\0",
						  "nue_bar" ,"numu_bar\0","nutau_bar\0"};


  int       h_bins[19]={
	1200, 1200,  100,
	 100,  500,  500, 
	50,   1200,	  50,
	50,     50,   50,
	50,     50  , 
	50,     50  , 
	500,
    50,     50};

  Double_t  h_min[19] ={
	 0.  ,  0.  ,  0.,
	 0.  ,  0.  ,  0.,
	-1.  ,-30.  , -1.,
	-1.  , -3.14, -3.14,
	-1.  , -1.  , 
	 -3.14, -3.14,
     0.  , -1.  , -1.};

  Double_t  h_max[19] ={
	30. , 30.  ,    1.,
	1.  ,  5.  ,    5.,
	1.,    0.  ,    1.,
	1.,    3.14,    3.14, 
	1.,    1.  ,    
	3.14,  3.14,
    5.,    1.  ,    1.};

  char hist_name[128],hist_title[128];

  Int_t i, j, k;

  f_out->cd();

  h_modes = new TH1D("neut_modes","Neut interaction modes",
					 121,-60.5,60.5);

  for ( i = 0 ; i < 7 ; i++ ){
	for ( j = 0 ; j < 19 ; j++ ){ /* histogram type */
	  for ( k = 0 ; k < 6 ; k++ ){ /* flavor */
		snprintf(hist_name,sizeof(hist_name),
				 "h_%s_%s_%s",hist_kind[i],hist_type[j],flavor_str[k]);
		snprintf(hist_title,sizeof(hist_title),"%s %s %s",
				 hist_type[j],hist_kind[i],flavor_str[k]);
		h_combined[i][j][k]
		  =new TH1D(hist_name,hist_title,h_bins[j],h_min[j],h_max[j]);
	  }
	}
  }

  //  for ( i = 0 ; i < 60 ; i++ ){
  //	for ( j = 0 ; j <19 ; j++ ){ /* histogram type */
  //	  for ( k = 0 ; k < 6 ; k++ ){ /* flavor */
  //		snprintf(hist_name,sizeof(hist_name),
  //				 "h_mode_%.2d_%s_%s",i,hist_type[j],flavor_str[k]);
  //		snprintf(hist_title,sizeof(hist_title),"%s (mode=%2d) %s",
  //				 hist_type[i],i,flavor_str[j]);
  //		h_indiv[i][j][k]
  //		  =new TH1D(hist_name,hist_title,h_bins[j],h_min[j],h_max[j]);
  //	  }
  //	}
  //  }

  int nev,iflv,ip,ip_idx,mode;
  const int flavor_id[6]={12,14,16,-12,-14,-16};

  for ( nev = 0 ; nev < nevents ; nev++ ){

	if ((nev % 10000) == 0){
	  cout << "Processing event #" << nev << endl;
	}

	tn->GetEntry(nev);

	ip = (nvect->PartInfo(0))->fPID;
	for ( ip_idx = 0 ; ip_idx < 6 ; ip_idx++ ){
	  if (ip == flavor_id[ip_idx]){
		break;
	  }
	}
	if ( ip_idx == 6 ){
	  cout << 
		"event " << nev << 
		":ip for #1 is not neutrino but "<< ip <<
		endl;
	  return 1;
	}
	
	mode = nvect->Mode;
	h_modes->Fill(double(mode),1.);
	/* all = 0 */
	fill_histograms(nvect,h_combined,0,ip_idx,rate_norm);

	if ( isCC(mode) ){
	  fill_histograms(nvect,h_combined,1,ip_idx,rate_norm);
	}	  
	if ( isNC(mode) ){
	  fill_histograms(nvect,h_combined,2,ip_idx,rate_norm);
	}
	if ( (abs(mode)==1) ){
	  fill_histograms(nvect,h_combined,3,ip_idx,rate_norm);
	}
	if ( (abs(mode)==2) ){
	  fill_histograms(nvect,h_combined,4,ip_idx,rate_norm);
	}
	if ( isCC1pi(mode) ){
	  fill_histograms(nvect,h_combined,5,ip_idx,rate_norm);
	}
	if ( isCCdis(mode) ){
	  fill_histograms(nvect,h_combined,6,ip_idx,rate_norm);
	}
  }
  
  for ( i = 0 ; i < 7 ; i++ ){
	for ( j = 0 ; j < 19 ; j++ ){ /* histogram type */
	  for ( k = 0 ; k < 6 ; k++ ){ /* flavor */
		if ( h_combined[i][j][k]->GetEntries() == 0 ){
		  delete h_combined[i][j][k];
		}
	  }
	}
  }


  f_out->Write();
  f_out->Close();
  return 0;
}
  
	/*
	cout << "Event #        :" << nvect->EventNo << "\n";
	cout << "Target A       :" << nvect->TargetA << "\n";
	cout << "Target Z       :" << nvect->TargetA << "\n";
	cout << "VNuclIni       :" << nvect->VNuclIni << "\n";
	cout << "VNuclFin       :" << nvect->VNuclFin << "\n";
	cout << "PF Surface     :" << nvect->PFSurf   << "\n";
	cout << "PF Maximum     :" << nvect->PFMax    << "\n";
	cout << "Flux ID        :" << nvect->FluxID   << "\n";
	cout << "Intr. mode     :" << nvect->Mode   << "\n";

	cout << "Vertex         =" << nvect->VertexID(i) << "\n";
	cout << "Parent Index   =" << nvect->ParentIdx(i) << "\n";

	cout << "Particle Code  = " << (nvect->PartInfo(i))->fPID   << "\n";
	cout << "Particle Mass  = " << (nvect->PartInfo(i))->fMass   << "\n";
	cout << "Particle Mom.  =(" << (nvect->PartInfo(i))->fP.Px() << ","
	<< (nvect->PartInfo(i))->fP.Py() << "," 
	<< (nvect->PartInfo(i))->fP.Pz() << ","
	<< (nvect->PartInfo(i))->fP.E()  << ")"
	<< "\n";
	cout << "Particle Flag  = " << (nvect->PartInfo(i))->fIsAlive << "\n";
	cout << "Particle Stat. = " << (nvect->PartInfo(i))->fStatus  << "\n";
	cout << "Particle Pos(1)=(" << (nvect->PartInfo(i))->fPosIni.X() << ","
	<< (nvect->PartInfo(i))->fPosIni.Y() << "," 
	<< (nvect->PartInfo(i))->fPosIni.Z() << ","
	<< (nvect->PartInfo(i))->fPosIni.T()  << ")"
	<< "\n";
	  cout << "Particle Pos(2)=(" << (nvect->PartInfo(i))->fPosFin.Px() << ","
	  	   << (nvect->PartInfo(i))->fPosFin.Y() << "," 
		   << (nvect->PartInfo(i))->fPosFin.Z() << ","
		   << (nvect->PartInfo(i))->fPosFin.T()  << ")"
		   << "\n";
	}
	std::cout << "Event #" << nvtx->EventNo << "\n";

	for (i = 0 ; i < nvtx->Nvtx() ; i++){
	  cout << "i=" << i << "\n";
	  
	  cout << "Vertex Pos(1)=(" << (nvtx->Pos(i))->X() << ","
		   << (nvtx->Pos(i))->Y() << "," 
		   << (nvtx->Pos(i))->Z() << ","
		   << (nvtx->Pos(i))->T()  << ")"
		   << "\n";
	}
	*/
  
  
int
main(int argc, char **argv)
{
  if ( argc < 3 ){
	cout << "need input filename and output filename" << endl;
	exit(0);
  }

  basic_histos_nonorm(argv[1],argv[2]);

}
