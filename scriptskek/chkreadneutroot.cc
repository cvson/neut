void
chkreadneutroot(char *fname)
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

  TFile f(fname);
  tn = (TTree *)(f.Get("neuttree"));

  nvtx = new NeutVtx();
  tn->SetBranchAddress("vertexbranch",&nvtx);

  nvect = new NeutVect();
  tn->SetBranchAddress("vectorbranch",&nvect);

  nevents = tn->GetEntries();

  for ( j = 0 ; j < nevents ; j++ ){

	cout << "---------------------------------------------" << "\n";

	tn->GetEntry(j);

	/***************************************************************/
	cout << "Event #        :" << nvect->EventNo << "\n";
	cout << "Target A       :" << nvect->TargetA << "\n";
	cout << "Target Z       :" << nvect->TargetA << "\n";
	cout << "VNuclIni       :" << nvect->VNuclIni << "\n";
	cout << "VNuclFin       :" << nvect->VNuclFin << "\n";
	cout << "PF Surface     :" << nvect->PFSurf   << "\n";
	cout << "PF Maximum     :" << nvect->PFMax    << "\n";
	cout << "Flux ID        :" << nvect->FluxID   << "\n";

	cout << "Intr. mode     :" << nvect->Mode   << "\n";

	for ( i = 0 ; i < nvect->Npart() ; i++ ){
	  cout << "i=" << i << "\n";
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
  }
  exit();
}
  
  
  
