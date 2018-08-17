// This macro can be used to analyse the NEUT output file.
// Just run root -l make_histos_standalone_neut540_ccqe_simple.cc("neut_input.root","neut_histo_output.root")
// Check that you have update the path and the file names in the 
// function make_histos_standalone_neut540_ccqe_simple()

#include <iostream>
using namespace std;
//pre-define function
void fill_histos(char *, char *, Double_t );
//in_fname is the input file name you get after run neutroot2
//out_fname is the output file name wher eyou want to put the interesting information
void make_histos_standalone_neut540_ccqe_simple(char *in_fname, char *out_fname){
    //loading needed libraries
    gSystem->Load("/home/t2k/cvson/MCSimulation/neut_5.4.0/src/neutclass/neutnucfsistep.so");
    gSystem->Load("/home/t2k/cvson/MCSimulation/neut_5.4.0/src/neutclass/neutnucfsivert.so");
    gSystem->Load("/home/t2k/cvson/MCSimulation/neut_5.4.0/src/neutclass/neutvtx.so");
    gSystem->Load("/home/t2k/cvson/MCSimulation/neut_5.4.0/src/neutclass/neutpart.so");
    gSystem->Load("/home/t2k/cvson/MCSimulation/neut_5.4.0/src/neutclass/neutfsipart.so");
    gSystem->Load("/home/t2k/cvson/MCSimulation/neut_5.4.0/src/neutclass/neutfsivert.so");
    gSystem->Load("/home/t2k/cvson/MCSimulation/neut_5.4.0/src/neutclass/neutvect.so");
    fill_histos(in_fname,out_fname);
}

//this is the main function to get information for each event and make plot
void fill_histos(char *in_fname, char *out_fname){  	
    // To check if you really have input file
    TFile *f = new TFile(in_fname,"READ");
    if ( f == NULL ){
        cout << "Failed to open " << in_fname << endl;
        return;
    }
    // Link the branches of the file.
    TTree *tn = (TTree*)(f->Get("neuttree"));
    NeutVtx *nvtx = new NeutVtx();
    tn->SetBranchAddress("vertexbranch",&nvtx);
    NeutVect *nvect = new NeutVect();
    tn->SetBranchAddress("vectorbranch",&nvect);
    
    // Define the histos that will show amazing results (kinematic variables)
    //interation mode
    TH1D *NEUT_mode           = new TH1D("NEUT_mode","NEUT mode",  55,0,55);
    TH1D *NEUT_enu            = new TH1D("NEUT_enu","Neutrino energy",  100,0.,5.);
    //momentum of out-going muon
    TH1D *NEUT_pmu            = new TH1D("NEUT_pmu","muon momentum",  100,0.,5.);
    //scattering angle of out-going muon
    TH1D *NEUT_anglemu        = new TH1D("NEUT_anglemu","muon angle", 180,0.,180.);
    //cosin of scattering angle of out-going muon
    TH1D *NEUT_cosanglemu     = new TH1D("NEUT_cosanglemu","cos muon angle", 100,-1.,1.);
    
    //2D plots
    TH2D *NEUT_mu_pvscosangle = new TH2D("NEUT_mu_pvscosangle"," muon momentum vs. cos(#theta)",100,0.,5.,100,-1.,1.);
    //TH2D *NEUT_q0vsq3;
    //NEUT_q0vsq3= new TH2D("NEUT_q0vsq3_mode"," q0vsq3",120,0.,1.2,120,0.,1.2);
    
    
    //momentum of out-goign muon
    TH1D *NEUT_ppro           = new TH1D("NEUT_ppro","out-nucleon(1) momentum",  100,0,5.);
    //scattering angle of out-going proton
    TH1D *NEUT_anglepro       = new TH1D("NEUT_anglepro","out-nucleon(1) angle", 180,0,180);
    //cosin of scattering angle of out-going proton
    TH1D *NEUT_cosanglepro    = new TH1D("NEUT_cosanglepro","cos out-nucleon(1) angle", 100,-1.,1.);
    
    
    
    //other kinematic variables you want to look at
    /*TH1D *NEUT_Q2      = new TH1D("NEUT_Q2","Q2",              100,0.,0.5);
     TH1D *NEUT_enurec  = new TH1D("NEUT_enurec","enu rec",     180,0.,180.);
     TH1D *NEUT_q2rec   = new TH1D("NEUT_q2rec","q2 rec",       50,0.,1);
     TH1D *NEUT_t       = new TH1D("NEUT_t","t (Mandelstam)",   100,0.,0.25);
     TH1D *NEUT_eta     = new TH1D("NEUT_eta","eta",            200,0.,1.);
     TH1D *NEUT_Wsq     = new TH1D("NEUT_Wsq","W2",            200,0.,2.);*/
    
   
    
    
    // some physics parameter
    double xmn  = 0.939;//GeV nucleon mass
    double xmmu = 0.106;//GeV muon mass
    double eb   =-0.025;//GeV, binding energy
    
    // ***************************************** //
    // ********* Loop over the entries ********* //
    // ***************************************** //
    //total number of event you generate
    Double_t nevents = tn->GetEntries();
    //you can ignore this. It's just to show lively number of events you have processed
    Long64_t iprintProcess;
    iprintProcess = Long64_t(nevents/100.);
    std::cout<<"nevents = "<<nevents<<std::endl;
    
    Int_t nevent_ccqe=0;// to count No. of CCQE you generated
    
    //make a loop over all event you generated
    for ( Int_t j = 0 ; j < nevents ; j++ ){
    //for ( Int_t j = 0 ; j < 1000 ; j++ ){
        tn->GetEntry(j);
        if (j%iprintProcess == 0) cout<<"Processing "<<int(j*100./nevents)<<"% of events"<<endl;
        //we consider CCQE only
        //it Mode is equal to 1
        //for CCQE, particle index is follow: 0 is incoming neutrino, 1 is nucleon, 2 is muon, 3 is proton
        Int_t muon_index = 2;
        Int_t proton_index = 3;
        if (abs(nvect->Mode) == 1){ // select only CCQE
            ++nevent_ccqe;
            //to check if it's really muon
            if((nvect->PartInfo(muon_index))->fPID != 13){ // Oh Look ! There is a muon
                cout<<"Oops, for event "<<j<<" particle w/ index 2 is not muon"<<endl;
            }
            
            //proton
            if((nvect->PartInfo(proton_index))->fPID != 2212){ // And here, it's a proton, this is awesome !
                cout<<"Oops, for event "<<j<<" particle w/ index 3 is not proton"<<endl;
            }
            
            // -----------------------
            // - Fill basic info. -
            // -----------------------
            //fill interaction mode
            NEUT_mode->Fill(nvect->Mode);
            //fill neutrino energy
            double e_nu =(nvect->PartInfo(0))->fP.E()/1000.;
            NEUT_enu->Fill(e_nu);
            
            
            // -----------------------
            // - Fill Muon variables -
            // -----------------------
            double e_mu = (nvect->PartInfo(muon_index))->fP.E()/1000.;    // Muon energy in GeV
            double p_mu = (nvect->PartInfo(muon_index))->fP.P()/1000.;    // Muon momentum in GeV
            NEUT_pmu->Fill(p_mu);
            double angle_mu = (nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(muon_index))->fP.Vect()); // Muon angle
            double angle_mu = angle_mu / 3.1415926535 * 180.;
            NEUT_anglemu->Fill(angle_mu);
            
            double cos_mu = cos((nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(muon_index))->fP.Vect()));
            NEUT_cosanglemu->Fill(cos_mu);
            NEUT_mu_pvscosangle->Fill(p_mu,cos_mu);
            
            // -----------------------
            // - Fill Proton variables -
            // -----------------------
            double epro = (nvect->PartInfo(proton_index))->fP.E()/1000.;
            double ppro = (nvect->PartInfo(proton_index))->fP.P()/1000.;
            double angle_pro = (nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(proton_index))->fP.Vect());
            double angle_pro = angle_pro / 3.1415926535 * 180.;
            double cos_pro = cos((nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(proton_index))->fP.Vect()));
            NEUT_ppro->Fill(ppro);
            NEUT_anglepro->Fill(angle_pro);
            NEUT_cosanglepro->Fill(cos_pro);
            
            
            // ---------------------------------------
            // - Other important kinematic variables -
            // ---------------------------------------
            
            /*double Q2 = abs(( (nvect->PartInfo(0))->fP - (nvect->PartInfo(muon_index))->fP)*( (nvect->PartInfo(0))->fP - (nvect->PartInfo(muon_index))->fP))*1e-6;
             TLorentzVector p4mu = (nvect->PartInfo(muon_index))->fP;
             TLorentzVector p4nu = (nvect->PartInfo(0))->fP;
             TLorentzVector qtransfer = p4nu-p4mu;
             double q0 = abs(qtransfer.E())/1000.;
             double q3 = abs(qtransfer.P())/1000.;
             NEUT_q0vsq3->Fill(q0,q3);*/
            //reconstruct energy
            //double enu_rec =((xmn+eb)*e_mu-(2*xmn*eb+eb*eb+xmmu*xmmu)/2)/(xmn+eb-e_mu+p_mu*cos_mu);
            
            
        }//end if mode
    } // End of Loop over the entries
    
    // Create the output analysed file that will contain all our info
    TFile *f2 = new TFile(out_fname,"RECREATE");
    if ( f2 == NULL ){
        cout << "Failed to (re)create " << out_fname << endl;
        return;
    }
    
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetLabelSize(0.05, "x");
    gStyle->SetLabelSize(0.05, "y");
    
    
    NEUT_mode->Write();
    NEUT_enu->Write();
    
    NEUT_pmu->Write();
    NEUT_anglemu->Write();
    NEUT_cosanglemu->Write();
    NEUT_mu_pvscosangle->Write();
    
    NEUT_ppro->Write();
    NEUT_anglepro->Write();
    NEUT_cosanglepro->Write();
    
    
    // ****************************
    // ***** Retrive info*****
    // ****************************
    TH1D * h_flux  = (TH1D*)f->Get("flux_numu");
    TH1D * h_evtrt = (TH1D*)f->Get("evtrt_numu");
    
    h_flux->Write();
    h_evtrt->Write();
    
    
    
    f2->Write();
    f2->Close();
}
