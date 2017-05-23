void
chkreadneutroot()
{

  Int_t i, j;
  Int_t nevents;

  gSystem->Load("../neutclass/neutvtx.so");
  gSystem->Load("../neutclass/neutpart.so");
  gSystem->Load("../neutclass/neutfsipart.so");
  gSystem->Load("../neutclass/neutfsivert.so");
  gSystem->Load("../neutclass/neutnucfsistep.so");
  gSystem->Load("../neutclass/neutnucfsivert.so");
  gSystem->Load("../neutclass/neutvect.so");
  
  TTree  *tn;
  NeutVtx *nvtx;
  NeutVect *nvect;

  TFile f("neutvect.root");
  tn = (TTree *)(f.Get("neuttree"));

  nvtx = new NeutVtx();
  tn->SetBranchAddress("vertexbranch",&nvtx);

  nvect = new NeutVect();
  tn->SetBranchAddress("vectorbranch",&nvect);

  nevents = tn->GetEntries();

  cout << nevents << endl;


  TH1D* HEhist = new TH1D("HEhist","",50,0,1500);
  TH1D* LEhist = new TH1D("LEhist","",50,0,1500);
  TH1D* ALLhist = new TH1D("ALLhist","",50,0,1500);
  for ( j = 0 ; j < nevents ; j++ ){

	cout << "---------------------------------------------" << "\n";

	tn->GetEntry(j);

  /*
	/ *************************************************************** /
	cout << "Event #        :" << nvect->EventNo << "\n";
	cout << "Target A       :" << nvect->TargetA << "\n";
	cout << "Target Z       :" << nvect->TargetA << "\n";
	cout << "VNuclIni       :" << nvect->VNuclIni << "\n";
	cout << "VNuclFin       :" << nvect->VNuclFin << "\n";
	cout << "PF Surface     :" << nvect->PFSurf   << "\n";
	cout << "PF Maximum     :" << nvect->PFMax    << "\n";
	cout << "Flux ID        :" << nvect->FluxID   << "\n";

	cout << "Intr. mode     :" << nvect->Mode   << "\n";
*/

// Momentum of highest energy outgoing particle
  double mom1 = sqrt(pow(nvect->PartInfo(3)->fP.Px(),2)+pow(nvect->PartInfo(3)->fP.Py(),2)+pow(nvect->PartInfo(3)->fP.Pz(),2));
  double mom2 = 0;//sqrt(pow(nvect->PartInfo(5)->fP.Px(),2)+pow(nvect->PartInfo(5)->fP.Py(),2)+pow(nvect->PartInfo(5)->fP.Pz(),2));
  double mom3=0;
  

  double temp = mom1;
  if(mom2>mom1){
    mom1 = mom2;
    mom2=temp;
  }

  HEhist->Fill(mom1);
  LEhist->Fill(mom2); 

  

	for ( i = 3 ; i < nvect->Npart() ; i++ ){
         if((nvect->PartInfo(i))->fIsAlive==1&&(nvect->PartInfo(i))->fPID>1000){ 
		mom3 = sqrt(pow(nvect->PartInfo(i)->fP.Px(),2)+pow(nvect->PartInfo(i)->fP.Py(),2)+pow(nvect->PartInfo(i)->fP.Pz(),2));   
          ALLhist->Fill(mom3); 
          }
          continue;
	  
	  cout << "i=" << i << "\n";
	  cout << "Vertex         =" << nvect->VertexID(i) << "\n";
	  cout << "Parent Index   =" << nvect->ParentIdx(i) << "\n";

	  cout << "Particle Code  = " << (nvect->PartInfo(i))->fPID   << "\n";
	  cout << "Particle Mass  = " << (nvect->PartInfo(i))->fMass   << "\n";
	  cout << "Particle Mom.  =(" << (nvect->PartInfo(i))->fP.Px() << ","
	  	   << (nvect->PartInfo(i))->fP.Py() << "," 
		   << (nvect->PartInfo(i))->fP.Pz() << ","
		   << (nvect->PartInfo(i))->fP.E() << "," <<mom3<< ")" 
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
  }

  TCanvas *c = new TCanvas();
  HEhist->Draw();
  c->Print("HEhist.eps");
  TCanvas *c0 = new TCanvas();
  LEhist->Draw();
  c0->Print("LEhist.eps");
   TCanvas *c1 = new TCanvas();
  ALLhist->Draw();
  c1->Print("ALLhist.eps");  

  exit();
}
  
  
  
