#include <TROOT.h>
#include <TTree.h>
#include <TH1D.h>
#include <TFile.h>
#include <TSystem.h>
#include <TMath.h>

#include <iostream>
#include <stdlib.h>

using namespace std;

extern "C" {
  float fnrawcrs_( int *, int *, float * );
  float fntotpau_( int *, float * );
  void necard_();
  void _gfortran_set_args(int, char **);
}


Int_t
cross_section_histos(char *fname_out)
{

  gSystem->Load("../neutclass/neutvtx.so");
  gSystem->Load("../neutclass/neutpart.so");
  gSystem->Load("../neutclass/neutfsipart.so");
  gSystem->Load("../neutclass/neutfsivert.so");
  gSystem->Load("../neutclass/neutnucfsistep.so");
  gSystem->Load("../neutclass/neutnucfsivert.so");
  gSystem->Load("../neutclass/neutvect.so");
  
  TFile *f_out;
  f_out = new TFile(fname_out,"RECREATE");
  if (f_out->IsZombie()){
	cout << "Failed to open " << fname_out << "." << endl;
	return 0;
  }

  f_out->cd();

  TTree  *tn;

  const Int_t mode_tbl[28]={
	01, 11, 12, 13, 21, 31, 32, 33, 34, 41,
	51, 52, 16, 36, 22, 42, 43, 23, 44, 45, 
	26, 46, 17, 38, 39,  2, 15, 35};

  const Int_t flv_tbl[6]={12,14,16,-12,-14,-16};

  Float_t Enu;
  Float_t crssect[6][60];

  tn = new TTree("crssect","Cross section table");
  tn->Branch("enu",&Enu,"Enu");
  tn->Branch("crssect",&crssect,"crssect[6][60]");

  Int_t i, j, k;
  Int_t mode, flv;
  float e;

  for ( i = 0 ; i < 6 ; i++ ){
	for ( j = 0 ; j < 60 ; j++ ){
	  crssect[i][j]=-1.;
	}
  }

  for ( k = 1 ; k < 380 ; k++ ){
	if ( k < 200 ){
	  e = (float)k * 0.05;
	}else{
	  e = (float)(k-200) * 0.5 + 10.;
	}

	Enu = e;

	for ( i = 0 ; i < 6 ; i++ ){
	  flv = flv_tbl[i];
	  for ( j = 0 ; j < 28 ; j++ ){
		mode = mode_tbl[j];
		if ( flv < 0 ){
		  mode = mode * -1;
		}
		crssect[i][abs(mode)] = fnrawcrs_(&flv, &mode, &e);
	  }
	  crssect[i][0] = fntotpau_(&flv, &e);	  
	}
	if ( crssect[3][0] > 0 ){
	  cout << 
		"nuebar Enu = " << 
		e <<
		" : CCQE = " << 
		crssect[3][1] <<
		" TOTAL = " << 
		crssect[3][0] <<
		" Ratio = " << 
		crssect[3][1]/crssect[3][0] <<
		endl;
	}
	tn->Fill();
  }  

  f_out->Write();
  f_out->Close();
  return 0;
}
  
int
main(int argc, char **argv)
{
  if ( argc < 3 ){
	cout << "need card filename and output filename" << endl;
	exit(0);
  }

#ifdef gFortran
  _gfortran_set_args(argc, argv);
#else
  f_setarg(argc, argv);
#endif

  necard_();
  cross_section_histos(argv[2]);

}
