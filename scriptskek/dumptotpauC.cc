#include <iostream>  
#include <cstdlib>
#include <math.h>

#include "TFile.h"
#include "TH1D.h"
#include "TString.h"

#include "neutmodesCPP.h"
#include "necardC.h"

// Purpose:
//    Creates cross section histograms (total and each mode)
//    for water in SK (or whatever is specified in neut.card
//    but make sure you change labels below)
// 
// Options: 
//
// -o Output file containing all the histograms
//

int getArgs(int argc, char* argv[]);
TString  outputFile        = "neut_xsecs.root";

extern "C" {
  void necrsmode_(int* nu_in,int* mode);
  float fntotpau_(int* nu_in,float* e_in);
  void necard_();
}


int main(int argc, char *argv[]){

 // process the arguments
  int args = getArgs(argc, argv);
  if(args != 0){
    std::cerr << "Usage " << std::endl;
    return 0;
  }

  necard_();

  // Now make cross section histograms
  Int_t  enuLow = 0;  // GeV
  Int_t enuHigh = 30;
  Double_t binWidth = 0.05;
  Int_t nBins = (enuHigh-enuLow)/binWidth;

  TFile *theOutputFile = new TFile(outputFile,"RECREATE");

  TH1D *h_xsec[4][kNneutModes];

  for (int inu=0; inu<4; inu++) {
      
    for (int imode=0; imode<kNneutModes; imode++) {

      h_xsec[inu][imode] = new TH1D(Form("neut_xsec_%s_%s",nuName[inu],neutModeName[imode]),Form("#sigma %s;True E_{%s} (GeV);#sigma (cm^{2}/nucleon)",neutModeTitle[imode],nuTitle[inu]),nBins,enuLow,enuHigh);

      necrsmode_(&nuID[inu], &neutModeID[imode]);
      
      for (float enu=enuLow+binWidth/2; enu<enuHigh; enu+=binWidth) {
	//h_xsec[inu][imode]->Fill(enu,(neuttarget_.numatom+neuttarget_.numfrep)*fntotpau_(&nuID[inu], &enu)*pow(10,-38));
	h_xsec[inu][imode]->Fill(enu,fntotpau_(&nuID[inu], &enu)*pow(10,-38));  // Per nucleon
      } 
    }
  }
  theOutputFile->Write();

  std::cout << "Output file = " << outputFile.Data() << std::endl;

  theOutputFile->Close();

  return 0;
  
}


int getArgs(int argc, char* argv[]){

  while( (argc > 1) && (argv[1][0] == '-') ){

    switch(argv[1][1]){

    case 'o': 
      outputFile = argv[2];
      ++argv; --argc;
      break;

    }
    ++argv; --argc;
  }
  return 0;
  
}
