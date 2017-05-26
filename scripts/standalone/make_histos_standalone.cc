// This macro can be used to analyse the NEUT output file.
// Just run root -l make_histos_standalone.cc
// Check that you have update the path and the file names in the 
// function make_histos_standalone() 

#include <iostream>
using namespace std;

void fill_histos(char *, char *, Double_t );

void make_histos_standalone(){
  	gSystem->Load("path/to/NEUT/neut_5.3.3/src/neutclass/neutvtx.so");
  	gSystem->Load("path/to/NEUT/neut_5.3.3/src/neutclass/neutpart.so");
  	gSystem->Load("path/to/NEUT/neut_5.3.3/src/neutclass/neutfsipart.so");
  	gSystem->Load("path/to/NEUT/neut_5.3.3/src/neutclass/neutfsivert.so");
  	gSystem->Load("path/to/NEUT/neut_5.3.3/src/neutclass/neutvect.so");
	fill_histos("neut_output.root","analysed_output.root");	
}

void fill_histos(char *in_fname, char *out_fname){  	
  	// Open the file created by the ./neutroot2 neut.card command.
	TFile *f = new TFile(in_fname,"READ");
  	if ( f == NULL ){
		cout << "Failed to open " << in_fname << endl;
		return;
  	}
  	// Link the branches of the file.
  	TTree *tn = (TTree *)(f.Get("neuttree"));
  	NeutVtx *nvtx = new NeutVtx();
  	tn->SetBranchAddress("vertexbranch",&nvtx);
  	NeutVect *nvect = new NeutVect();
  	tn->SetBranchAddress("vectorbranch",&nvect);

  	// Define the histos that will show amazing results (kinematic variables)
	TH1D *NEUT_pmu        = new TH1D("NEUT_pmu","muon momentum",  100,0.,2.);
   	TH1D *NEUT_anglemu    = new TH1D("NEUT_anglemu","muon angle", 180,0.,180.);
   	TH1D *NEUT_cosanglemu = new TH1D("NEUT_cosanglemu","cos muon angle", 50,-1.,1.);

   	TH1D *NEUT_ppi           = new TH1D("NEUT_ppi","pion momentum",  100,0,2);
   	TH1D *NEUT_anglepi       = new TH1D("NEUT_anglepi","pion angle", 180,0,180);
   	TH1D *NEUT_cosanglepi    = new TH1D("NEUT_cosanglepi","cos pion angle", 50,-1.,1.);

  	TH1D *NEUT_Q2      = new TH1D("NEUT_Q2","Q2",              100,0.,0.5);
  	TH1D *NEUT_enurec  = new TH1D("NEUT_enurec","enu rec",     180,0.,180.);
   	TH1D *NEUT_q2rec   = new TH1D("NEUT_q2rec","q2 rec",       50,0.,1);
  	TH1D *NEUT_t       = new TH1D("NEUT_t","t (Mandelstam)",   100,0.,0.25);
  	TH1D *NEUT_eta     = new TH1D("NEUT_eta","eta",            200,0.,1.);

  	// stuffs
   	double xmn  = 0.939;
	double xmmu = 0.106;
	double eb   =-0.025;

	// ***************************************** //
	// ********* Loop over the entries ********* //
	// ***************************************** //

  	Double_t nevents = tn->GetEntries();
  	std::cout<<"nevents = "<<nevents<<std::endl;
  	for ( Int_t j = 0 ; j < nevents ; j++ ){
		tn->GetEntry(j);
		if (nvect->Mode == 16){ // select only CC1pi coherent interaction
			for ( Int_t i = 2 ; i < nvect->Npart() ; i++ ){ // Loop over all outgoing particles in the event
				if((nvect->PartInfo(i))->fPID == 13){ // Oh Look ! There is a muon
					double muon_nbr = i;
				}
				else if((nvect->PartInfo(i))->fPID == 211){ // And here, it's a pion, this is awesome !
					double pion_nbr = i;
				}
			}

			// -----------------------
			// - Fill Muon variables -
			// -----------------------
			double e_mu = (nvect->PartInfo(muon_nbr))->fP.E()/1000.;    // Muon energy in GeV
	  		double p_mu = (nvect->PartInfo(muon_nbr))->fP.P()/1000.;    // Muon momentum in GeV
			double angle_mu = (nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(muon_nbr))->fP.Vect()); // Muon angle
			double angle_mu = angle_mu / 3.1415926535 * 180.;
			double cos_mu = cos((nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(muon_nbr))->fP.Vect()));
			NEUT_pmu->Fill(p_mu);
			NEUT_anglemu->Fill(angle_mu);
			NEUT_cosanglemu->Fill(cos_mu);

			// -----------------------
			// - Fill Pion variables -
			// -----------------------
			double epi = (nvect->PartInfo(pion_nbr))->fP.E()/1000.;
	  		double ppi = (nvect->PartInfo(pion_nbr))->fP.P()/1000.;
	  		double angle_pi = (nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(pion_nbr))->fP.Vect());
	  		double angle_pi = angle_pi / 3.1415926535 * 180.;
	  		double cos_pi = cos((nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(pion_nbr))->fP.Vect()));
			NEUT_ppi->Fill(epi);
			NEUT_anglepi->Fill(angle_pi);
			NEUT_cosanglepi->Fill(cos_pi);

			// ---------------------------------------
			// - Other important kinematic variables -
			// ---------------------------------------
			double Q2 = 2*0.938*(nvect->Crsx)*(nvect->Crsy)*((nvect->PartInfo(0))->fP.E()/1000);
			double t = abs(((nvect->PartInfo(pion_nbr))->fP -( (nvect->PartInfo(0))->fP - (nvect->PartInfo(muon_nbr))->fP ))
	  				  *((nvect->PartInfo(pion_nbr))->fP -( (nvect->PartInfo(0))->fP - (nvect->PartInfo(muon_nbr))->fP )))*1e-6;
			double enu_rec =((xmn+eb)*e_mu-(2*xmn*eb+eb*eb+xmmu*xmmu)/2)/(xmn+eb-e_mu+p_mu*cos_mu);
			double q2_rec = (2*enu_rec*(e_mu - p_mu*cos_mu)-xmmu*xmmu);
			double eta = epi*(1-cos_pi);

			NEUT_Q2->Fill(Q2);
			NEUT_t->Fill(t);
			NEUT_enurec->Fill(enu_rec);
			NEUT_q2rec->Fill(q2_rec);
			NEUT_eta->Fill(eta);
		}
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

	h_flux->Write();
  	h_evtrt->SetName("TotXS"); 
  	h_evtrt->GetYaxis()->SetTitle("Integrated XS (x10^{-38}cm^{2})");
  	h_evtrt->GetYaxis()->CenterTitle();
  	h_evtrt->Divide(h_flux); // integrated XS per nucleons = event rate / flux
  	h_evtrt->Scale(12); // x12 because C has 12 nucleons 
  	h_evtrt->Write();

	// XS normalisation of NEUT for pion mom 
	TH1F * NEUT_pmu_XS  = (TH1F*)NEUT_pmu->Clone("NEUT_pmu_XS");
	NEUT_pmu_XS->Scale(norm_rate*50/nevents); // x50 because of binning
	NEUT_pmu_XS->GetYaxis()->SetTitle("#frac{d#sigma}{dp_{#mu^{-}}} (x10^{-38} cm^{2}.GeV^{-1})");
	NEUT_pmu_XS->GetYaxis()->CenterTitle();
	NEUT_pmu_XS->GetXaxis()->SetTitle("p_{#mu^{-}} (GeV)");
	NEUT_pmu_XS->GetXaxis()->CenterTitle();

	// XS normalisation of NEUT for pion angle
	TH1F * NEUT_anglemu_XS  = (TH1F*)NEUT_anglemu->Clone("NEUT_anglemu_XS");
	NEUT_anglemu_XS->Scale(norm_rate*1/nevents); // x1 because of binning
	NEUT_anglemu_XS->GetYaxis()->SetTitle("#frac{d#sigma}{d#theta_{#mu^{-}}} (x10^{-38} cm^{2}.deg^{-1})");
	NEUT_anglemu_XS->GetYaxis()->CenterTitle();
	NEUT_anglemu_XS->GetXaxis()->SetTitle("#theta_{#mu^{-}} (deg)");
	NEUT_anglemu_XS->GetXaxis()->CenterTitle();

	// XS normalisation of NEUT for pion mom 
	TH1F * NEUT_ppi_XS  = (TH1F*)NEUT_ppi->Clone("NEUT_ppi_XS");
	NEUT_ppi_XS->Scale(norm_rate*50/nevents); // x50 because of binning
	NEUT_ppi_XS->GetYaxis()->SetTitle("#frac{d#sigma}{dp_{#pi^{+}}} (x10^{-38} cm^{2}.GeV^{-1})");
	NEUT_ppi_XS->GetYaxis()->CenterTitle();
	NEUT_ppi_XS->GetXaxis()->SetTitle("p_{#pi^{+}} (GeV)");
	NEUT_ppi_XS->GetXaxis()->CenterTitle();

	// XS normalisation of NEUT for pion angle
	TH1F * NEUT_anglepi_XS  = (TH1F*)NEUT_anglepi->Clone("NEUT_anglepi_XS");
	NEUT_anglepi_XS->Scale(norm_rate*1/nevents); // x1 because of binning
	NEUT_anglepi_XS->GetYaxis()->SetTitle("#frac{d#sigma}{d#theta_{#pi^{+}}} (x10^{-38} cm^{2}.deg^{-1})");
	NEUT_anglepi_XS->GetYaxis()->CenterTitle();
	NEUT_anglepi_XS->GetXaxis()->SetTitle("#theta_{#pi^{+}} (deg)");
	NEUT_anglepi_XS->GetXaxis()->CenterTitle();

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

	// Write everything in the output file and close it
	f2->Write();
  	f2->Close();
}
