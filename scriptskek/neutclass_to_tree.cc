#include <TROOT.h>
#include <TTree.h>
#include <TH1D.h>
#include <TFile.h>
#include <TSystem.h>
#include <TMath.h>

#include <iostream>
#include <stdlib.h>

#include "neworkC.h"
#include "vcworkC.h"
#include "vcvrtxC.h"
#include "neutparamsC.h"
#include "posinnucC.h"
#include "neutmodelC.h"
#include "necardC.h"
#include "nrcardC.h"
#include "nefillverC.h"
#include "neutcrsC.h"
#include "posinnucC.h"
#include "fsihistC.h"
#include "nucleonfsihistC.h"
#include "neutcrsC.h"

#include "../../include/neutvect.h"
#include "../../include/neutvtx.h"

using namespace std;

void
copy_back(NeutVect *nv)
{
  int i;

  neuttarget_.numatom = nv->TargetA  ;
  neuttarget_.numbndp = nv->TargetZ  ;
  neuttarget_.numfrep = nv->TargetH  ;
  nenupr_.vnuini 	  = nv->VNuclIni ;
  nenupr_.vnufin 	  = nv->VNuclFin ;
  nenupr_.pfsurf 	  = nv->PFSurf   ;
  nenupr_.pfmax 	  = nv->PFMax    ;
  posinnuc_.ibound    = nv->Ibound   ;
  
  /****************************************************/
  // interaction model and some parameters
  nemdls_.mdlqe 	= nv->QEModel  ;
  nemdls_.mdlspi    = nv->SPIModel ;
                      
  nemdls_.mdlcoh    = nv->COHModel ;
  nemdls_.mdldis    = nv->DISModel ;
                      
  nemdls_.mdlqeaf   = nv->QEVForm  ;
  nemdls_.xmaqe 	= nv->QEMA     ;
                      
  neut1pi_.neiff    = nv->SPIForm  ;
                      
  neut1pi_.nenrtype = nv->SPINRType;

  nv->SPICA5I  = neut1pi_.rneca5i  ;
  nv->SPIBGScale= neut1pi_.rnebgscl;

  nemdls_.xmaspi= nv->SPIMA    ;
  nemdls_.xmvspi= nv->SPIMV    ;
                   
  nemdls_.xmares= nv->RESMA    ;
  nemdls_.xmvres= nv->RESMV    ;
                   
  nemdls_.xmvqe = nv->QEMV     ;
                   
  nemdls_.kapp 	= nv->KAPPA    ;
                   
  nemdls_.xmacoh= nv->COHMA    ;
  nemdls_.rad0nu= nv->COHR0    ;
  nemdls_.fa1coh= nv->COHA1err ;
  nemdls_.fb1coh= nv->COHb1err ;

  // neut verion
  neutversion_.corev=nv->COREVer  ;
  neutversion_.nucev=nv->NUCEVer  ;
  neutversion_.nuccv=nv->NUCCVer  ;
  // neut card
  neutcard_.nefrmflg=nv->FrmFlg;
  neutcard_.nepauflg=nv->PauFlg;
  neutcard_.nenefo16=nv->NefO16;
  neutcard_.nemodflg=nv->ModFlg;
  neutcard_.neselmod=nv->SelMod;
  nenupr_.iformlen  =nv->FormLen;

  neutpiless_.ipilessdcy = nv->IPilessDcy;
  neutpiless_.rpilessdcy = nv->RPilessDcy;
  nucres_.nucrescat 	 = nv->NucScat;
  nucres_.xnucfact       = nv->NucFac;


  neffpr_.fefqe  = nv->NuceffFactorPIQE   ;
  neffpr_.fefinel= nv->NuceffFactorPIInel ;    
  neffpr_.fefabs = nv->NuceffFactorPIAbs  ;   
  neffpr_.fefqeh = nv->NuceffFactorPIQEH  ; 
  neffpr_.fefcx  = nv->NuceffFactorPICX   ; 
  neffpr_.fefcxh = nv->NuceffFactorPICXH  ;  
  neffpr_.fefcoh = nv->NuceffFactorPICoh  ; 
  neffpr_.fefqehf= nv->NuceffFactorPIQEHKin;  	  
  neffpr_.fefcohf= nv->NuceffFactorPIQELKin; 
  neffpr_.fefcxhf= nv->NuceffFactorPICXKin;   
  neffpr_.fefall = nv->NuceffFactorPIAll  ; 

  /****************************************************/
  nework_.modene       = nv->Mode;
  neutcrscom_.totcrsne = nv->Totcrs;

  neutcrscom_.crsenergy= nv->CrsEnergy;
  
  for ( i = 0 ; i < 8 ; i++ ){
	neutcrscom_.difcrsne[i] = nv->DifCrsNE[i];
  }
  neutcrscom_.crsx = nv->Crsx;
  neutcrscom_.crsy = nv->Crsy;
  neutcrscom_.crsz = nv->Crsz;
  neutcrscom_.crsphi=nv->Crsphi;
  neutcrscom_.crsq2 =nv->Crsq2;

  vcwork_.nvc   = nv->Npart();

  nework_.numne = nv->Nprimary();

  for ( i = 0 ; i < vcwork_.nvc ; i++ ){
	Double_t mass;
	NeutPart pinfo;
	
	vcwork_.ivtivc[i] = nv->VertexID(i);

	vcwork_.iorgvc[i] = nv->ParentIdx(i);
	  
	vcwork_.ipvc[i]   = nv->PartInfo(i)->fPID;
	vcwork_.amasvc[i] = nv->PartInfo(i)->fMass;

	vcwork_.icrnvc[i] = nv->PartInfo(i)->fIsAlive;
	vcwork_.iflgvc[i] = nv->PartInfo(i)->fStatus;

	vcwork_.pvc[i][0] = nv->PartInfo(i)->fP.Px();
	vcwork_.pvc[i][1] = nv->PartInfo(i)->fP.Py();
	vcwork_.pvc[i][2] = nv->PartInfo(i)->fP.Pz();

	posinnuc_.posnuc[i][0] = nv->PartInfo(i)->fPosIni.X();
	posinnuc_.posnuc[i][1] = nv->PartInfo(i)->fPosIni.Y();
	posinnuc_.posnuc[i][2] = nv->PartInfo(i)->fPosIni.Z();

  }
  
}

Int_t
neutclass_to_tree(char *fname,char *fname_out)
{
  int nev;

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
  NeutVtx   *nvtx;
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
  }else{
	rate_integ = (double)(nevents);
  }
  cout << " flux_sum = " << flux_integ << endl;
  cout << " rate_sum = " << rate_integ << endl;

  rate_norm = rate_integ/(double)(nevents);

  cout << " rate_norm = " << rate_norm << endl;

  ///////////////////////////////////////////////////////////////////
  TTree *neut_tree;

  f_out->cd();
  neut_tree = new TTree("neut_tree",  "neut tree");

  neut_tree->Branch("vcwork",&vcwork_.nvc,
				 "nvc/I:posvc[3]/F:ipvc[100]/I:amasvc[100]/F:pvc[100][3]/F:iorgvc[100]/I:iflgvc[100]/I:icrnvc[100]/I:timvc[100]/F:posivc[100][3]/F:ivtivc[100]/I:posfvc[100][3]/F:ivtfvc[100]/I");

  neut_tree->Branch("nework",&nework_.modene,
				 "modene/I:numne/I:ipne[100]/I:pne[100][3]/F:iorgne[100]/I:iflgne[100]/I:icrnne[100]/I");

  neut_tree->Branch("posinnuc",&posinnuc_.ibound,
				 "ibound/I:posnuc[100][3]/F");

  for ( nev = 0 ; nev < nevents ; nev++ ){

	if ((nev % 10000) == 0){
	  cout << "Processing event #" << nev << endl;
	}

	tn->GetEntry(nev);
	copy_back(nvect);
	neut_tree->Fill();
  }

  neut_tree->Write();
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

  neutclass_to_tree(argv[1],argv[2]);

}
