// This macro can be used to analyse the NEUT output file.
// Just run root -l make_histos_standalone_neut540_cc0pi_v3.cc("neut_input.root","neut_histo_output.root")
// Check that you have update the path and the file names in the 
// function make_histos_standalone_neut540_cc0pi_v3()
//to have E/k of incoming nucleon for separting SF and Fermigas model

#include <iostream>
using namespace std;

void fill_histos(char *, char *, Double_t );

void make_histos_standalone_neut540_cc0pi_v3(char *in_fname, char *out_fname){
    //in 5.3.2 there is no neutnucfsivert.so and neutnucfsistep.so
     gSystem->Load("/home/t2k/cvson/MCSimulation/neut_5.4.0/src/neutclass/neutnucfsistep.so");
    gSystem->Load("/home/t2k/cvson/MCSimulation/neut_5.4.0/src/neutclass/neutnucfsivert.so");
    gSystem->Load("/home/t2k/cvson/MCSimulation/neut_5.4.0/src/neutclass/neutvtx.so");
    gSystem->Load("/home/t2k/cvson/MCSimulation/neut_5.4.0/src/neutclass/neutpart.so");
    gSystem->Load("/home/t2k/cvson/MCSimulation/neut_5.4.0/src/neutclass/neutfsipart.so");
    gSystem->Load("/home/t2k/cvson/MCSimulation/neut_5.4.0/src/neutclass/neutfsivert.so");
    gSystem->Load("/home/t2k/cvson/MCSimulation/neut_5.4.0/src/neutclass/neutvect.so");
    fill_histos(in_fname,out_fname);
}

void fill_histos(char *in_fname, char *out_fname){  	
    // Open the file created by the ./neutroot2 neut.card command.
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
    TH1D *NEUT_mode           = new TH1D("NEUT_mode","NEUT mode",  55,0,55);
    TH1D *NEUT_pmu            = new TH1D("NEUT_pmu","muon momentum",  100,0.,2.);
    TH1D *NEUT_anglemu        = new TH1D("NEUT_anglemu","muon angle", 180,0.,180.);
    TH1D *NEUT_cosanglemu     = new TH1D("NEUT_cosanglemu","cos muon angle", 50,-1.,1.);
    
    TH1D *NEUT_npro           = new TH1D("NEUT_npro","No. of protons",  10,0,10);
    TH1D *NEUT_ppro           = new TH1D("NEUT_ppro","out-nucleon(1) momentum",  100,0,2);
    TH1D *NEUT_anglepro       = new TH1D("NEUT_anglepro","out-nucleon(1) angle", 180,0,180);
    TH1D *NEUT_cosanglepro    = new TH1D("NEUT_cosanglepro","cos out-nucleon(1) angle", 50,-1.,1.);
    
    TH1D *NEUT_cosopenanglemupro        = new TH1D("NEUT_cosopenanglemupro","cos opening angle (muon-nucleon(1))", 50,-1.,1.);
    TH1D *NEUT_cosopenanglemuproccqe    = new TH1D("NEUT_cosopenanglemuproccqe","cos opening angle (muon-nucleon(1))", 50,-1.,1.);
    TH1D *NEUT_cosopenanglemupromec     = new TH1D("NEUT_cosopenanglemupromec","cos opening angle (muon-nucleon(1))", 50,-1.,1.);
    //for MEC
    TH1D *NEUT_ppro2           = new TH1D("NEUT_ppro2","out-nucleon(2) momentum",  100,0,2);
    TH1D *NEUT_anglepro2       = new TH1D("NEUT_anglepro2","out-nucleon(2) angle", 180,0,180);
    TH1D *NEUT_cosanglepro2    = new TH1D("NEUT_cosanglepro2","cos out-nucleon(2) angle", 50,-1.,1.);
    TH1D *NEUT_cosopenangle2pro    = new TH1D("NEUT_cosopenangle2pro","cos opening angle of two nucleons", 50,-1.,1.);
    
    
    TH1D *NEUT_pneu_in           = new TH1D("NEUT_pneu_in","in-nucleon(1) momentum",  100,0,2);
    TH1D *NEUT_angleneu_in       = new TH1D("NEUT_angleneu_in","in-nucleon(1) angle", 180,0,180);
    TH1D *NEUT_cosangleneu_in    = new TH1D("NEUT_cosangleneu_in","cos in-nucleon(1) angle", 50,-1.,1.);
    
    //for MEC
    TH1D *NEUT_pneu_in2           = new TH1D("NEUT_pneu_in2","in-nucleon(2) momentum",  100,0,2);
    TH1D *NEUT_angleneu_in2       = new TH1D("NEUT_angleneu_in2","in-nucleon(2) angle", 180,0,180);
    TH1D *NEUT_cosangleneu_in2    = new TH1D("NEUT_cosangleneu_in2","cos in-nucleon(2) angle", 50,-1.,1.);
    
    
    
    TH1D *NEUT_Q2      = new TH1D("NEUT_Q2","Q2",              100,0.,0.5);
    TH1D *NEUT_enurec  = new TH1D("NEUT_enurec","enu rec",     180,0.,180.);
    TH1D *NEUT_q2rec   = new TH1D("NEUT_q2rec","q2 rec",       50,0.,1);
    TH1D *NEUT_t       = new TH1D("NEUT_t","t (Mandelstam)",   100,0.,0.25);
    TH1D *NEUT_eta     = new TH1D("NEUT_eta","eta",            200,0.,1.);
    
    TH1D *NEUT_Wsq     = new TH1D("NEUT_Wsq","W2",            200,0.,2.);
    
    //2D plots
    const int NMODE2PLOT = 4;//0 for all, 1 for CCQE, 2 for 2p2ph, 3 for others
    TH2D *NEUT_mu_pvscosangle[NMODE2PLOT];
    TH2D *NEUT_mu_cosanglevsp[NMODE2PLOT];
    TH2D *NEUT_q0vsq3[NMODE2PLOT];
    TH2D *NEUT_q3vsq0[NMODE2PLOT];
    TH2D *NEUT_incnulcEvsk[NMODE2PLOT];
    for (Int_t imode=0; imode<NMODE2PLOT; ++imode) {
        NEUT_mu_pvscosangle[imode] = new TH2D(Form("NEUT_mu_pvscosangle_mode%d",imode)," muon momentum vs. cos(angle)",100,0.,2.,100,-1.,1.);
        NEUT_mu_cosanglevsp[imode] = new TH2D(Form("NEUT_mu_cosanglevsp_mode%d",imode)," cos(angle) vs. muon momentum",100,-1.,1.,100,0.,2.);
        NEUT_q0vsq3[imode]= new TH2D(Form("NEUT_q0vsq3_mode%d",imode)," q0vsq3",120,0.,1.2,120,0.,1.2);
        NEUT_q3vsq0[imode]= new TH2D(Form("NEUT_q3vsq0_mode%d",imode)," q3vsq0",120,0.,1.2,120,0.,1.2);
        //incoming Evske for CCQE only
        NEUT_incnulcEvsk[imode]= new TH2D(Form("NEUT_incnulcEvsk_mode%d",imode)," incoming nucleon E vs. k",100,0,2,100,0,2);
    }
    
    
    // stuffs
    double xmn  = 0.939;
    double xmmu = 0.106;
    double eb   =-0.025;
    
    // ***************************************** //
    // ********* Loop over the entries ********* //
    // ***************************************** //
    
    Double_t nevents = tn->GetEntries();
    Long64_t iprintProcess;
    iprintProcess = Long64_t(nevents/100.);
    std::cout<<"nevents = "<<nevents<<std::endl;
    int npion;
    int nproton;
    int NEVENTMODE=nevents;//all event
    int NEVENTMODE_SEL=0;//after cut
    double Wsq_tmp;
    for ( Int_t j = 0 ; j < nevents ; j++ ){
        tn->GetEntry(j);
        if (j%iprintProcess == 0) cout<<"Processing "<<int(j*100./nevents)<<"% of events"<<endl;
        nproton = 0;//reset
        npion = 0;
        if (abs(nvect->Mode) <30){ // select  all CC interaction
            ++NEVENTMODE_SEL;
            for ( Int_t i = 2 ; i < nvect->Npart() ; i++ ){ // Loop over all outgoing particles in the event
                nproton = 0;
                if((nvect->PartInfo(i))->fPID == 13){ // Oh Look ! There is a muon
                    double muon_nbr = i;
                }
                //check no of pion
                else if((nvect->PartInfo(i))->fPID == 211 || (nvect->PartInfo(i))->fPID == 111){ // And here, it's a pion, this is awesome !
                    npion +=1;//check number of pion
                }
                //proton
                else if((nvect->PartInfo(i))->fPID == 2212){ // And here, it's a proton, this is awesome !
                    nproton +=1;//check number of proton
                }
                //to calculate the Wsq, sum of all final states except lepton
                //if MEC lepton index is 3, and all final particle is with index larger than 3
                //if normal, then all final particle is with index larger than 2
                TLorentzVector vec_wsq;//initial zero
                if ((nvect->Mode ==2 && i>3) || (nvect->Mode !=2 && i>2)) {
                    TLorentzVector vecpith = (nvect->PartInfo(i))->fP;
                    vec_wsq += vecpith;
                }
                Wsq_tmp = abs(vec_wsq.Mag2())/1.e6;//v*v
            }
            double proton_nbr = 3;//not mec
            double proton_nbr2 = 5;//if mec
            if (nvect->Mode ==2) { //if MEC, lepton index is 3, and outgoing nucleon is 4 and 5
                proton_nbr = 4;
                double e1 = (nvect->PartInfo(4))->fP.E();
                double e2 = (nvect->PartInfo(5))->fP.E();
                if ( e1 < e2 ){
                    proton_nbr = 5;
                    proton_nbr2 = 4;
                }
            }
            
            /*Int_t ip = (nvect->PartInfo(proton_nbr))->fPID;
             if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
             ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
             cout << "IP is not nucleon " << ip << " mode= " << mode << endl;
             }*/
            
            double neuin_nbr = 1;//incoming neutron
            double neuin_nbr2 = 2;//2nd nucleon if mec
            //if (nproton>1) cout<<"warning number of proton "<<nproton<<endl;
            
            // -----------------------
            // - Fill Muon variables -
            // -----------------------
            if(npion==0){
                NEUT_mode->Fill(nvect->Mode);
                double e_mu = (nvect->PartInfo(muon_nbr))->fP.E()/1000.;    // Muon energy in GeV
                double p_mu = (nvect->PartInfo(muon_nbr))->fP.P()/1000.;    // Muon momentum in GeV
                double angle_mu = (nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(muon_nbr))->fP.Vect()); // Muon angle
                double angle_mu = angle_mu / 3.1415926535 * 180.;
                double cos_mu = cos((nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(muon_nbr))->fP.Vect()));
                NEUT_pmu->Fill(p_mu);
                NEUT_anglemu->Fill(angle_mu);
                NEUT_cosanglemu->Fill(cos_mu);
                NEUT_mu_pvscosangle[0]->Fill(p_mu,cos_mu);//newadd
                if(abs(nvect->Mode)==1)NEUT_mu_pvscosangle[1]->Fill(p_mu,cos_mu);
                else if (abs(nvect->Mode)==2)NEUT_mu_pvscosangle[2]->Fill(p_mu,cos_mu);
                else NEUT_mu_pvscosangle[3]->Fill(p_mu,cos_mu);
                
                NEUT_mu_cosanglevsp[0]->Fill(cos_mu,p_mu);//newadd
                if(abs(nvect->Mode)==1)NEUT_mu_cosanglevsp[1]->Fill(cos_mu,p_mu);
                else if (abs(nvect->Mode)==2)NEUT_mu_cosanglevsp[2]->Fill(cos_mu,p_mu);
                else NEUT_mu_cosanglevsp[3]->Fill(cos_mu,p_mu);
                
                // -----------------------
                // - Fill Proton variables -
                // -----------------------
                NEUT_npro->Fill(nproton);
                double epro = (nvect->PartInfo(proton_nbr))->fP.E()/1000.;
                double ppro = (nvect->PartInfo(proton_nbr))->fP.P()/1000.;
                double angle_pro = (nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(proton_nbr))->fP.Vect());
                double angle_pro = angle_pro / 3.1415926535 * 180.;
                double cos_pro = cos((nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(proton_nbr))->fP.Vect()));
                NEUT_ppro->Fill(ppro);
                NEUT_anglepro->Fill(angle_pro);
                NEUT_cosanglepro->Fill(cos_pro);
                TVector3 vecmu,vecpro;
                vecmu = (nvect->PartInfo(muon_nbr))->fP.Vect();
                vecpro = (nvect->PartInfo(proton_nbr))->fP.Vect();
                double openanglemupro = cos(vecmu.Angle(vecpro));
                NEUT_cosopenanglemupro->Fill(openanglemupro);
                if(nvect->Mode ==1) NEUT_cosopenanglemuproccqe->Fill(openanglemupro);
                else if(nvect->Mode ==2) NEUT_cosopenanglemupromec->Fill(openanglemupro);
                if(nvect->Mode ==2){
                    double epro2 = (nvect->PartInfo(proton_nbr2))->fP.E()/1000.;
                    double ppro2 = (nvect->PartInfo(proton_nbr2))->fP.P()/1000.;
                    double angle_pro2 = (nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(proton_nbr2))->fP.Vect());
                    double angle_pro2 = angle_pro2 / 3.1415926535 * 180.;
                    double cos_pro2 = cos((nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(proton_nbr2))->fP.Vect()));
                    NEUT_ppro2->Fill(ppro2);
                    NEUT_anglepro2->Fill(angle_pro2);
                    NEUT_cosanglepro2->Fill(cos_pro2);
                    
                    TVector3 vecpro2;
                    vecpro2 = (nvect->PartInfo(proton_nbr2))->fP.Vect();
                    double openangle2pro = cos(vecpro.Angle(vecpro2));
                    NEUT_cosopenangle2pro->Fill(openangle2pro);
                }
                // -----------------------
                // - Fill incoming neutron variables -
                // -----------------------
                double eneu_in = (nvect->PartInfo(neuin_nbr))->fP.E()/1000.;
                double pneu_in = (nvect->PartInfo(neuin_nbr))->fP.P()/1000.;
                 NEUT_incnulcEvsk[0]->Fill(eneu_in,pneu_in);
                if(abs(nvect->Mode)==1)NEUT_incnulcEvsk[1]->Fill(eneu_in,pneu_in);
                else if (abs(nvect->Mode)==2)NEUT_incnulcEvsk[2]->Fill(eneu_in,pneu_in);
                else NEUT_incnulcEvsk[3]->Fill(eneu_in,pneu_in);
                
                double angle_neu_in = (nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(neuin_nbr))->fP.Vect());
                double angle_neu_in = angle_neu_in / 3.1415926535 * 180.;
                double cos_neu_in = cos((nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(neuin_nbr))->fP.Vect()));
                NEUT_pneu_in->Fill(pneu_in);
                NEUT_angleneu_in->Fill(angle_neu_in);
                NEUT_cosangleneu_in->Fill(cos_neu_in);
                if(nvect->Mode ==2){
                    double eneu_in2 = (nvect->PartInfo(neuin_nbr2))->fP.E()/1000.;
                    double pneu_in2 = (nvect->PartInfo(neuin_nbr2))->fP.P()/1000.;
                    double angle_neu_in2 = (nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(neuin_nbr2))->fP.Vect());
                    double angle_neu_in2 = angle_neu_in2 / 3.1415926535 * 180.;
                    double cos_neu_in2 = cos((nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(neuin_nbr2))->fP.Vect()));
                    NEUT_pneu_in2->Fill(pneu_in2);
                    NEUT_angleneu_in2->Fill(angle_neu_in2);
                    NEUT_cosangleneu_in2->Fill(cos_neu_in2);
                }
                // ---------------------------------------
                // - Other important kinematic variables -
                // ---------------------------------------
                // for coherent
                //double Q2 = 2*0.938*(nvect->Crsx)*(nvect->Crsy)*((nvect->PartInfo(0))->fP.E()/1000);
                //for cc1pro
                double Q2 = abs(( (nvect->PartInfo(0))->fP - (nvect->PartInfo(muon_nbr))->fP)*( (nvect->PartInfo(0))->fP - (nvect->PartInfo(muon_nbr))->fP))*1e-6;
                TLorentzVector p4mu = (nvect->PartInfo(muon_nbr))->fP;
                TLorentzVector p4nu = (nvect->PartInfo(0))->fP;
                TLorentzVector qtransfer = p4nu-p4mu;
                double q0 = abs(qtransfer.E())/1000.;
                double q3 = abs(qtransfer.P())/1000.;
                NEUT_q0vsq3[0]->Fill(q0,q3);
                if(abs(nvect->Mode)==1)NEUT_q0vsq3[1]->Fill(q0,q3);
                else if (abs(nvect->Mode)==2)NEUT_q0vsq3[2]->Fill(q0,q3);
                else NEUT_q0vsq3[3]->Fill(q0,q3);
                
                NEUT_q3vsq0[0]->Fill(q3,q0);
                if(abs(nvect->Mode)==1)NEUT_q3vsq0[1]->Fill(q3,q0);
                else if (abs(nvect->Mode)==2)NEUT_q3vsq0[2]->Fill(q3,q0);
                else NEUT_q3vsq0[3]->Fill(q3,q0);
                
                double t = 0;//abs(((nvect->PartInfo(proton_nbr))->fP -( (nvect->PartInfo(0))->fP - (nvect->PartInfo(muon_nbr))->fP ))
                //  *((nvect->PartInfo(proton_nbr))->fP -( (nvect->PartInfo(0))->fP - (nvect->PartInfo(muon_nbr))->fP )))*1e-6;
                double enu_rec =((xmn+eb)*e_mu-(2*xmn*eb+eb*eb+xmmu*xmmu)/2)/(xmn+eb-e_mu+p_mu*cos_mu);
                double q2_rec = (2*enu_rec*(e_mu - p_mu*cos_mu)-xmmu*xmmu);
                double eta = 0;//epro*(1-cos_pro);
                
                NEUT_Q2->Fill(Q2);
                NEUT_t->Fill(t);
                NEUT_enurec->Fill(enu_rec);
                NEUT_q2rec->Fill(q2_rec);
                NEUT_eta->Fill(eta);
                NEUT_Wsq->Fill(Wsq_tmp);
            }//nend npion
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
    NEUT_pmu->Write();
    NEUT_anglemu->Write();
    NEUT_cosanglemu->Write();
    
    NEUT_npro->Write();
    NEUT_ppro->Write();
    NEUT_anglepro->Write();
    NEUT_cosanglepro->Write();
    NEUT_cosopenanglemupro->Write();
    NEUT_cosopenanglemuproccqe->Write();
    NEUT_cosopenanglemupromec->Write();
    
    NEUT_ppro2->Write();
    NEUT_anglepro2->Write();
    NEUT_cosanglepro2->Write();
    NEUT_cosopenangle2pro->Write();
    
    
    NEUT_pneu_in->Write();
    NEUT_angleneu_in->Write();
    NEUT_cosangleneu_in->Write();
    
    NEUT_pneu_in2->Write();
    NEUT_angleneu_in2->Write();
    NEUT_cosangleneu_in2->Write();
    
    NEUT_Q2->Write();
    NEUT_enurec->Write();
    NEUT_q2rec->Write();
    NEUT_t->Write();
    NEUT_eta->Write();
    NEUT_Wsq->Write();
    
    //2D
    for (Int_t imode=0; imode<NMODE2PLOT; ++imode) {
        NEUT_mu_pvscosangle[imode]->Write();
        NEUT_mu_cosanglevsp[imode]->Write();
        NEUT_q0vsq3[imode]->Write();
        NEUT_q3vsq0[imode]->Write();
        NEUT_incnulcEvsk[imode]->Write();
    }
    
    // ****************************
    // ***** XS NORMALISATION *****
    // ****************************
    // Renormalized histos in order to have a diff XS instead of a distrubution function of the number of events
    TH1D * h_flux  = (TH1D*)f->Get("flux_numu");
    TH1D * h_evtrt = (TH1D*)f->Get("evtrt_numu");
    double flux_numu   = h_flux->GetSumOfWeights();
    double evtrt_numu  = h_evtrt->GetSumOfWeights();
    
    // Calculate the normalisation factor. (12 because it's a carbon target)
    double norm_rate = 12 * evtrt_numu/flux_numu;
    
    //copy flux and event rate
    h_flux->Write();
    h_evtrt->Write();
    
    //cross section of selected mode
    TH1D * h_xsecsel = (TH1D*) h_evtrt->Clone("h_xsecsel");
    h_xsecsel->SetName("TotXS");
    h_xsecsel->GetYaxis()->SetTitle("Integrated XS (x10^{-38}cm^{2})");
    h_xsecsel->GetYaxis()->CenterTitle();
    h_xsecsel->Divide(h_flux); // integrated XS per nucleons = event rate / flux
    h_xsecsel->Scale(NEVENTMODE_SEL*1.0/NEVENTMODE);//scale by selected event
    h_xsecsel->Scale(12); // x12 because C has 12 nucleons
    h_xsecsel->Write();
    
    // XS normalisation of NEUT for proton mom
    TH1F * NEUT_pmu_XS  = (TH1F*)NEUT_pmu->Clone("NEUT_pmu_XS");
    NEUT_pmu_XS->Scale(norm_rate*50/nevents); // x50 because of binning
    NEUT_pmu_XS->GetYaxis()->SetTitle("#frac{d#sigma}{dp_{#mu^{-}}} (x10^{-38} cm^{2}.GeV^{-1})");
    NEUT_pmu_XS->GetYaxis()->CenterTitle();
    NEUT_pmu_XS->GetXaxis()->SetTitle("p_{#mu^{-}} (GeV)");
    NEUT_pmu_XS->GetXaxis()->CenterTitle();
    
    // XS normalisation of NEUT for proton angle
    TH1F * NEUT_anglemu_XS  = (TH1F*)NEUT_anglemu->Clone("NEUT_anglemu_XS");
    NEUT_anglemu_XS->Scale(norm_rate*1/nevents); // x1 because of binning
    NEUT_anglemu_XS->GetYaxis()->SetTitle("#frac{d#sigma}{d#theta_{#mu^{-}}} (x10^{-38} cm^{2}.deg^{-1})");
    NEUT_anglemu_XS->GetYaxis()->CenterTitle();
    NEUT_anglemu_XS->GetXaxis()->SetTitle("#theta_{#mu^{-}} (deg)");
    NEUT_anglemu_XS->GetXaxis()->CenterTitle();
    
    // XS normalisation of NEUT for proton mom
    TH1F * NEUT_ppro_XS  = (TH1F*)NEUT_ppro->Clone("NEUT_ppro_XS");
    NEUT_ppro_XS->Scale(norm_rate*50/nevents); // x50 because of binning
    NEUT_ppro_XS->GetYaxis()->SetTitle("#frac{d#sigma}{dp_{p}} (x10^{-38} cm^{2}.GeV^{-1})");
    NEUT_ppro_XS->GetYaxis()->CenterTitle();
    NEUT_ppro_XS->GetXaxis()->SetTitle("p_{p} (GeV)");
    NEUT_ppro_XS->GetXaxis()->CenterTitle();
    
    // XS normalisation of NEUT for proton angle
    TH1F * NEUT_anglepro_XS  = (TH1F*)NEUT_anglepro->Clone("NEUT_anglepro_XS");
    NEUT_anglepro_XS->Scale(norm_rate*1/nevents); // x1 because of binning
    NEUT_anglepro_XS->GetYaxis()->SetTitle("#frac{d#sigma}{d#theta_{p}} (x10^{-38} cm^{2}.deg^{-1})");
    NEUT_anglepro_XS->GetYaxis()->CenterTitle();
    NEUT_anglepro_XS->GetXaxis()->SetTitle("#theta_{p} (deg)");
    NEUT_anglepro_XS->GetXaxis()->CenterTitle();
    
    // XS normalisation of NEUT for Q2
    TH1F * NEUT_Q2_XS  = (TH1F*)NEUT_Q2->Clone("NEUT_Q2_XS");
    NEUT_Q2_XS->Scale(norm_rate*200/nevents); // x200 because of binning
    NEUT_Q2_XS->GetYaxis()->SetTitle("#frac{d#sigma}{dQ^{2}} (x10^{-38} cm^{2}.GeV^{-2})");
    NEUT_Q2_XS->GetYaxis()->CenterTitle();
    NEUT_Q2_XS->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
    NEUT_Q2_XS->GetXaxis()->CenterTitle();
    
    // XS normalisation of NEUT for Q2
    TH1F * NEUT_t_XS  = (TH1F*)NEUT_t->Clone("NEUT_t_XS");
    NEUT_t_XS->Scale(norm_rate*400/nevents); // x400 because of binning
    NEUT_t_XS->GetYaxis()->SetTitle("#frac{d#sigma}{dt} (x10^{-38} cm^{2}.GeV^{-2})");
    NEUT_t_XS->GetYaxis()->CenterTitle();
    NEUT_t_XS->GetXaxis()->SetTitle("t (GeV^{2})");
    NEUT_t_XS->GetXaxis()->CenterTitle();
    TH2D *NEUT_mu_pvscosangle_XS[NMODE2PLOT];
    TH2D *NEUT_mu_cosanglevsp_XS[NMODE2PLOT];
    TH2D *NEUT_q0vsq3_XS[NMODE2PLOT];
    TH2D *NEUT_q3vsq0_XS[NMODE2PLOT];
    
    for (Int_t imode=0; imode<NMODE2PLOT; ++imode) {
        NEUT_mu_pvscosangle_XS[imode] = (TH2D*)NEUT_mu_pvscosangle[imode]->Clone(Form("NEUT_mu_pvscosangle_mode%d_XS",imode));
        NEUT_mu_pvscosangle_XS[imode]->Scale(norm_rate*50*50/nevents);
        
        NEUT_mu_cosanglevsp_XS[imode] = (TH2D*)NEUT_mu_cosanglevsp[imode]->Clone(Form("NEUT_mu_cosanglevsp_mode%d_XS",imode));
        NEUT_mu_cosanglevsp_XS[imode]->Scale(norm_rate*50*50/nevents);
        
        NEUT_q0vsq3_XS[imode] = (TH2D*)NEUT_q0vsq3[imode]->Clone(Form("NEUT_q0vsq3_mode%d_XS"));
        NEUT_q0vsq3_XS[imode]->Scale(norm_rate*100*100/nevents);
        
        NEUT_q3vsq0_XS[imode] = (TH2D*)NEUT_q3vsq0[imode]->Clone(Form("NEUT_q3vsq0_mode%d_XS"));
        NEUT_q3vsq0_XS[imode]->Scale(norm_rate*100*100/nevents);
        
    }
    
    
    
    // Write everything in the output file and close it
    f2->Write();
    f2->Close();
}
