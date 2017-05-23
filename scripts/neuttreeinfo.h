//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue May 23 14:34:31 2017 by ROOT version 5.28/00h
// from TTree neuttree/Neut Tree
// found on file: /disk01/usr3/cvson/nuicise/neut/neut_5.4.0_alpha/src/neutsmpl/neutvect_5.4.0_nd5_C.root
//////////////////////////////////////////////////////////

#ifndef neuttreeinfo_h
#define neuttreeinfo_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class neuttreeinfo {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //NeutVect        *vectorbranch;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           EventNo;
   Int_t           TargetA;
   Int_t           TargetZ;
   Int_t           TargetH;
   Int_t           Ibound;
   Double_t        VNuclIni;
   Double_t        VNuclFin;
   Double_t        PFSurf;
   Double_t        PFMax;
   Int_t           FluxID;
   Int_t           QEModel;
   Int_t           SPIModel;
   Int_t           COHModel;
   Int_t           DISModel;
   Int_t           SPIForm;
   Int_t           RESForm;
   Int_t           SPINRType;
   Int_t           RESNRType;
   Int_t           QEVForm;
   Float_t         QEMA;
   Float_t         SPIMA;
   Float_t         RESMA;
   Float_t         QEMV;
   Float_t         SPIMV;
   Float_t         RESMV;
   Float_t         KAPPA;
   Float_t         COHMA;
   Float_t         COHR0;
   Float_t         COHA1err;
   Float_t         COHb1err;
   Float_t         SPICA5I;
   Float_t         SPIBGScale;
   Int_t           COREVer;
   Int_t           NUCEVer;
   Int_t           NUCCVer;
   Int_t           FrmFlg;
   Int_t           PauFlg;
   Int_t           NefO16;
   Int_t           ModFlg;
   Int_t           SelMod;
   Int_t           FormLen;
   Int_t           IPilessDcy;
   Float_t         RPilessDcy;
   Int_t           NucScat;
   Float_t         NucFac;
   Float_t         NuceffFactorPIQE;
   Float_t         NuceffFactorPIInel;
   Float_t         NuceffFactorPIAbs;
   Float_t         NuceffFactorPIQEH;
   Float_t         NuceffFactorPICX;
   Float_t         NuceffFactorPICXH;
   Float_t         NuceffFactorPICoh;
   Float_t         NuceffFactorPIAll;
   Float_t         NuceffFactorPIQEHKin;
   Float_t         NuceffFactorPIQELKin;
   Float_t         NuceffFactorPICXKin;
   Int_t           Mode;
   Float_t         Totcrs;
   Float_t         CrsEnergy;
   Float_t         DifCrsNE[8];
   Float_t         Crsx;
   Float_t         Crsy;
   Float_t         Crsz;
   Float_t         Crsphi;
   Float_t         Crsq2;
   Float_t         Fsiprob;
   Int_t           fNpart;
   Int_t           fNprimary;
   TArrayI         fVertexID;
   TArrayI         fParentIdx;
   Int_t           fRandomSeed[16];
   Int_t           fNfsiPart;
   Int_t           fNfsiVert;
   Int_t           fNnucFsiVert;
   Int_t           fNnucFsiStep;
 //NeutVtx         *vertexbranch;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           EventNo;
   Int_t           fNvtx;

   // List of branches
   TBranch        *b_vectorbranch_fUniqueID;   //!
   TBranch        *b_vectorbranch_fBits;   //!
   TBranch        *b_vectorbranch_EventNo;   //!
   TBranch        *b_vectorbranch_TargetA;   //!
   TBranch        *b_vectorbranch_TargetZ;   //!
   TBranch        *b_vectorbranch_TargetH;   //!
   TBranch        *b_vectorbranch_Ibound;   //!
   TBranch        *b_vectorbranch_VNuclIni;   //!
   TBranch        *b_vectorbranch_VNuclFin;   //!
   TBranch        *b_vectorbranch_PFSurf;   //!
   TBranch        *b_vectorbranch_PFMax;   //!
   TBranch        *b_vectorbranch_FluxID;   //!
   TBranch        *b_vectorbranch_QEModel;   //!
   TBranch        *b_vectorbranch_SPIModel;   //!
   TBranch        *b_vectorbranch_COHModel;   //!
   TBranch        *b_vectorbranch_DISModel;   //!
   TBranch        *b_vectorbranch_SPIForm;   //!
   TBranch        *b_vectorbranch_RESForm;   //!
   TBranch        *b_vectorbranch_SPINRType;   //!
   TBranch        *b_vectorbranch_RESNRType;   //!
   TBranch        *b_vectorbranch_QEVForm;   //!
   TBranch        *b_vectorbranch_QEMA;   //!
   TBranch        *b_vectorbranch_SPIMA;   //!
   TBranch        *b_vectorbranch_RESMA;   //!
   TBranch        *b_vectorbranch_QEMV;   //!
   TBranch        *b_vectorbranch_SPIMV;   //!
   TBranch        *b_vectorbranch_RESMV;   //!
   TBranch        *b_vectorbranch_KAPPA;   //!
   TBranch        *b_vectorbranch_COHMA;   //!
   TBranch        *b_vectorbranch_COHR0;   //!
   TBranch        *b_vectorbranch_COHA1err;   //!
   TBranch        *b_vectorbranch_COHb1err;   //!
   TBranch        *b_vectorbranch_SPICA5I;   //!
   TBranch        *b_vectorbranch_SPIBGScale;   //!
   TBranch        *b_vectorbranch_COREVer;   //!
   TBranch        *b_vectorbranch_NUCEVer;   //!
   TBranch        *b_vectorbranch_NUCCVer;   //!
   TBranch        *b_vectorbranch_FrmFlg;   //!
   TBranch        *b_vectorbranch_PauFlg;   //!
   TBranch        *b_vectorbranch_NefO16;   //!
   TBranch        *b_vectorbranch_ModFlg;   //!
   TBranch        *b_vectorbranch_SelMod;   //!
   TBranch        *b_vectorbranch_FormLen;   //!
   TBranch        *b_vectorbranch_IPilessDcy;   //!
   TBranch        *b_vectorbranch_RPilessDcy;   //!
   TBranch        *b_vectorbranch_NucScat;   //!
   TBranch        *b_vectorbranch_NucFac;   //!
   TBranch        *b_vectorbranch_NuceffFactorPIQE;   //!
   TBranch        *b_vectorbranch_NuceffFactorPIInel;   //!
   TBranch        *b_vectorbranch_NuceffFactorPIAbs;   //!
   TBranch        *b_vectorbranch_NuceffFactorPIQEH;   //!
   TBranch        *b_vectorbranch_NuceffFactorPICX;   //!
   TBranch        *b_vectorbranch_NuceffFactorPICXH;   //!
   TBranch        *b_vectorbranch_NuceffFactorPICoh;   //!
   TBranch        *b_vectorbranch_NuceffFactorPIAll;   //!
   TBranch        *b_vectorbranch_NuceffFactorPIQEHKin;   //!
   TBranch        *b_vectorbranch_NuceffFactorPIQELKin;   //!
   TBranch        *b_vectorbranch_NuceffFactorPICXKin;   //!
   TBranch        *b_vectorbranch_Mode;   //!
   TBranch        *b_vectorbranch_Totcrs;   //!
   TBranch        *b_vectorbranch_CrsEnergy;   //!
   TBranch        *b_vectorbranch_DifCrsNE;   //!
   TBranch        *b_vectorbranch_Crsx;   //!
   TBranch        *b_vectorbranch_Crsy;   //!
   TBranch        *b_vectorbranch_Crsz;   //!
   TBranch        *b_vectorbranch_Crsphi;   //!
   TBranch        *b_vectorbranch_Crsq2;   //!
   TBranch        *b_vectorbranch_Fsiprob;   //!
   TBranch        *b_vectorbranch_fNpart;   //!
   TBranch        *b_vectorbranch_fNprimary;   //!
   TBranch        *b_vectorbranch_fVertexID;   //!
   TBranch        *b_vectorbranch_fParentIdx;   //!
   TBranch        *b_vectorbranch_fRandomSeed;   //!
   TBranch        *b_vectorbranch_fNfsiPart;   //!
   TBranch        *b_vectorbranch_fNfsiVert;   //!
   TBranch        *b_vectorbranch_fNnucFsiVert;   //!
   TBranch        *b_vectorbranch_fNnucFsiStep;   //!
   TBranch        *b_vertexbranch_fUniqueID;   //!
   TBranch        *b_vertexbranch_fBits;   //!
   TBranch        *b_vertexbranch_EventNo;   //!
   TBranch        *b_vertexbranch_fNvtx;   //!

   neuttreeinfo(TTree *tree=0);
   virtual ~neuttreeinfo();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef neuttreeinfo_cxx
neuttreeinfo::neuttreeinfo(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/disk01/usr3/cvson/nuicise/neut/neut_5.4.0_alpha/src/neutsmpl/neutvect_5.4.0_nd5_C.root");
      if (!f) {
         f = new TFile("/disk01/usr3/cvson/nuicise/neut/neut_5.4.0_alpha/src/neutsmpl/neutvect_5.4.0_nd5_C.root");
      }
      tree = (TTree*)gDirectory->Get("neuttree");

   }
   Init(tree);
}

neuttreeinfo::~neuttreeinfo()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t neuttreeinfo::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t neuttreeinfo::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void neuttreeinfo::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_vectorbranch_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_vectorbranch_fBits);
   fChain->SetBranchAddress("EventNo", &EventNo, &b_vectorbranch_EventNo);
   fChain->SetBranchAddress("TargetA", &TargetA, &b_vectorbranch_TargetA);
   fChain->SetBranchAddress("TargetZ", &TargetZ, &b_vectorbranch_TargetZ);
   fChain->SetBranchAddress("TargetH", &TargetH, &b_vectorbranch_TargetH);
   fChain->SetBranchAddress("Ibound", &Ibound, &b_vectorbranch_Ibound);
   fChain->SetBranchAddress("VNuclIni", &VNuclIni, &b_vectorbranch_VNuclIni);
   fChain->SetBranchAddress("VNuclFin", &VNuclFin, &b_vectorbranch_VNuclFin);
   fChain->SetBranchAddress("PFSurf", &PFSurf, &b_vectorbranch_PFSurf);
   fChain->SetBranchAddress("PFMax", &PFMax, &b_vectorbranch_PFMax);
   fChain->SetBranchAddress("FluxID", &FluxID, &b_vectorbranch_FluxID);
   fChain->SetBranchAddress("QEModel", &QEModel, &b_vectorbranch_QEModel);
   fChain->SetBranchAddress("SPIModel", &SPIModel, &b_vectorbranch_SPIModel);
   fChain->SetBranchAddress("COHModel", &COHModel, &b_vectorbranch_COHModel);
   fChain->SetBranchAddress("DISModel", &DISModel, &b_vectorbranch_DISModel);
   fChain->SetBranchAddress("SPIForm", &SPIForm, &b_vectorbranch_SPIForm);
   fChain->SetBranchAddress("RESForm", &RESForm, &b_vectorbranch_RESForm);
   fChain->SetBranchAddress("SPINRType", &SPINRType, &b_vectorbranch_SPINRType);
   fChain->SetBranchAddress("RESNRType", &RESNRType, &b_vectorbranch_RESNRType);
   fChain->SetBranchAddress("QEVForm", &QEVForm, &b_vectorbranch_QEVForm);
   fChain->SetBranchAddress("QEMA", &QEMA, &b_vectorbranch_QEMA);
   fChain->SetBranchAddress("SPIMA", &SPIMA, &b_vectorbranch_SPIMA);
   fChain->SetBranchAddress("RESMA", &RESMA, &b_vectorbranch_RESMA);
   fChain->SetBranchAddress("QEMV", &QEMV, &b_vectorbranch_QEMV);
   fChain->SetBranchAddress("SPIMV", &SPIMV, &b_vectorbranch_SPIMV);
   fChain->SetBranchAddress("RESMV", &RESMV, &b_vectorbranch_RESMV);
   fChain->SetBranchAddress("KAPPA", &KAPPA, &b_vectorbranch_KAPPA);
   fChain->SetBranchAddress("COHMA", &COHMA, &b_vectorbranch_COHMA);
   fChain->SetBranchAddress("COHR0", &COHR0, &b_vectorbranch_COHR0);
   fChain->SetBranchAddress("COHA1err", &COHA1err, &b_vectorbranch_COHA1err);
   fChain->SetBranchAddress("COHb1err", &COHb1err, &b_vectorbranch_COHb1err);
   fChain->SetBranchAddress("SPICA5I", &SPICA5I, &b_vectorbranch_SPICA5I);
   fChain->SetBranchAddress("SPIBGScale", &SPIBGScale, &b_vectorbranch_SPIBGScale);
   fChain->SetBranchAddress("COREVer", &COREVer, &b_vectorbranch_COREVer);
   fChain->SetBranchAddress("NUCEVer", &NUCEVer, &b_vectorbranch_NUCEVer);
   fChain->SetBranchAddress("NUCCVer", &NUCCVer, &b_vectorbranch_NUCCVer);
   fChain->SetBranchAddress("FrmFlg", &FrmFlg, &b_vectorbranch_FrmFlg);
   fChain->SetBranchAddress("PauFlg", &PauFlg, &b_vectorbranch_PauFlg);
   fChain->SetBranchAddress("NefO16", &NefO16, &b_vectorbranch_NefO16);
   fChain->SetBranchAddress("ModFlg", &ModFlg, &b_vectorbranch_ModFlg);
   fChain->SetBranchAddress("SelMod", &SelMod, &b_vectorbranch_SelMod);
   fChain->SetBranchAddress("FormLen", &FormLen, &b_vectorbranch_FormLen);
   fChain->SetBranchAddress("IPilessDcy", &IPilessDcy, &b_vectorbranch_IPilessDcy);
   fChain->SetBranchAddress("RPilessDcy", &RPilessDcy, &b_vectorbranch_RPilessDcy);
   fChain->SetBranchAddress("NucScat", &NucScat, &b_vectorbranch_NucScat);
   fChain->SetBranchAddress("NucFac", &NucFac, &b_vectorbranch_NucFac);
   fChain->SetBranchAddress("NuceffFactorPIQE", &NuceffFactorPIQE, &b_vectorbranch_NuceffFactorPIQE);
   fChain->SetBranchAddress("NuceffFactorPIInel", &NuceffFactorPIInel, &b_vectorbranch_NuceffFactorPIInel);
   fChain->SetBranchAddress("NuceffFactorPIAbs", &NuceffFactorPIAbs, &b_vectorbranch_NuceffFactorPIAbs);
   fChain->SetBranchAddress("NuceffFactorPIQEH", &NuceffFactorPIQEH, &b_vectorbranch_NuceffFactorPIQEH);
   fChain->SetBranchAddress("NuceffFactorPICX", &NuceffFactorPICX, &b_vectorbranch_NuceffFactorPICX);
   fChain->SetBranchAddress("NuceffFactorPICXH", &NuceffFactorPICXH, &b_vectorbranch_NuceffFactorPICXH);
   fChain->SetBranchAddress("NuceffFactorPICoh", &NuceffFactorPICoh, &b_vectorbranch_NuceffFactorPICoh);
   fChain->SetBranchAddress("NuceffFactorPIAll", &NuceffFactorPIAll, &b_vectorbranch_NuceffFactorPIAll);
   fChain->SetBranchAddress("NuceffFactorPIQEHKin", &NuceffFactorPIQEHKin, &b_vectorbranch_NuceffFactorPIQEHKin);
   fChain->SetBranchAddress("NuceffFactorPIQELKin", &NuceffFactorPIQELKin, &b_vectorbranch_NuceffFactorPIQELKin);
   fChain->SetBranchAddress("NuceffFactorPICXKin", &NuceffFactorPICXKin, &b_vectorbranch_NuceffFactorPICXKin);
   fChain->SetBranchAddress("Mode", &Mode, &b_vectorbranch_Mode);
   fChain->SetBranchAddress("Totcrs", &Totcrs, &b_vectorbranch_Totcrs);
   fChain->SetBranchAddress("CrsEnergy", &CrsEnergy, &b_vectorbranch_CrsEnergy);
   fChain->SetBranchAddress("DifCrsNE[8]", DifCrsNE, &b_vectorbranch_DifCrsNE);
   fChain->SetBranchAddress("Crsx", &Crsx, &b_vectorbranch_Crsx);
   fChain->SetBranchAddress("Crsy", &Crsy, &b_vectorbranch_Crsy);
   fChain->SetBranchAddress("Crsz", &Crsz, &b_vectorbranch_Crsz);
   fChain->SetBranchAddress("Crsphi", &Crsphi, &b_vectorbranch_Crsphi);
   fChain->SetBranchAddress("Crsq2", &Crsq2, &b_vectorbranch_Crsq2);
   fChain->SetBranchAddress("Fsiprob", &Fsiprob, &b_vectorbranch_Fsiprob);
   fChain->SetBranchAddress("fNpart", &fNpart, &b_vectorbranch_fNpart);
   fChain->SetBranchAddress("fNprimary", &fNprimary, &b_vectorbranch_fNprimary);
   fChain->SetBranchAddress("fVertexID", &fVertexID, &b_vectorbranch_fVertexID);
   fChain->SetBranchAddress("fParentIdx", &fParentIdx, &b_vectorbranch_fParentIdx);
   fChain->SetBranchAddress("fRandomSeed[16]", fRandomSeed, &b_vectorbranch_fRandomSeed);
   fChain->SetBranchAddress("fNfsiPart", &fNfsiPart, &b_vectorbranch_fNfsiPart);
   fChain->SetBranchAddress("fNfsiVert", &fNfsiVert, &b_vectorbranch_fNfsiVert);
   fChain->SetBranchAddress("fNnucFsiVert", &fNnucFsiVert, &b_vectorbranch_fNnucFsiVert);
   fChain->SetBranchAddress("fNnucFsiStep", &fNnucFsiStep, &b_vectorbranch_fNnucFsiStep);
   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_vertexbranch_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_vertexbranch_fBits);
   fChain->SetBranchAddress("EventNo", &EventNo, &b_vertexbranch_EventNo);
   fChain->SetBranchAddress("fNvtx", &fNvtx, &b_vertexbranch_fNvtx);
   Notify();
}

Bool_t neuttreeinfo::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void neuttreeinfo::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t neuttreeinfo::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef neuttreeinfo_cxx
