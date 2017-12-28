void plot_basics_comp2ver_ccnpi(){
    gROOT->ProcessLine(".x rootlogon.C"); 
    gROOT->ProcessLine(".L basicPlotUtil.C");
    TString ipDir = "/home/cvson/disk/nuicise/neut/neut_5.4.0_alpha/src/neutsmpl/";
    TString ipDir1 = "/home/cvson/disk/nuicise/neut/neut_5.3.7_INGRID_FIX/src/neutsmpl/";
    TString ipDir2 = "/home/cvson/disk/nuicise/neut/neut_5.3.2/src/neutsmpl/";
    TString ipDir4 = "/home/cvson/disk/nuicise/neut/neut_5.4.0/src/neutsmpl/";    

    /*TFile *ffile = new TFile(ipDir4+"basicplotso_5.3.6_nd5_C_GFGCCQE_ccnpi.root");
    TString vername = "Global Fermi gas"; 
    TFile *ffile2 = new TFile(ipDir4+"basicplotso_5.3.6_nd5_C_SFCCQE_ccnpi.root");
    TString vername2 = "Spectral function";
    TString savename ="neut540_nd5_ccnpi_comp2_gfg_vs_sf";*/

    TFile *ffile = new TFile(ipDir4+"basicplotso_5.3.6_nd5_C_GFGCCQE_ccnpi.root");
    TString vername = "NEUT 5.4.0"; 
    TFile *ffile2 = new TFile(ipDir1+"basicplotso_5.3.6_nd5_C_GFGCCQE_ccnpi.root");
    TString vername2 = "NEUT 5.3.6";
    TString savename ="nd5_ccnpi_comp2_gfg";

    /*TFile *ffile = new TFile(ipDir4+"basicplotso_5.3.6_nd5_C_SFCCQE_ccnpi.root");
    TString vername = "NEUT 5.4.0"; 
    TFile *ffile2 = new TFile(ipDir1+"basicplotso_5.3.6_nd5_C_SFCCQE_ccnpi.root");
    TString vername2 = "NEUT 5.3.6";
    TString savename ="nd5_ccnpi_comp2_sf";*/

    /*TFile *ffile = new TFile(ipDir4+"basicplotso_5.4.0_nd5_C_CC1pi_RS.root");
    TString vername = "Rein-Seghal"; 
    TFile *ffile2 = new TFile(ipDir4+"basicplotso_5.4.0_nd5_C_CC1pi_RS_20piless.root");
    TString vername2 = "RS + 20% #pi-less #Delta";
    TString savename ="neut540_nd5_cc1pi_comp2_rspiless_";
    */
 
    TIter next(ffile->GetListOfKeys());
    TKey *key;
    Int_t nhist=0;
    vector<char*> vkeyclassname;
    vector<char*> vkeytitle;
    while ((key = (TKey*)next())) {
        nhist++;
        cout << "Key " << nhist << endl;
        cout << " Classname " <<key->GetClassName() << endl;
        cout << " Title " <<key->GetTitle() << endl;
        TObject *obj = (TObject*)key->ReadObj();
        vkeyclassname.push_back(key->GetClassName());
        vkeytitle.push_back(obj->GetName());
        TClass *cl = gROOT->GetClass(key->GetClassName());
        if (cl->InheritsFrom("TH1D")) {
            TH1D *h = (TH1D*)ffile->Get(obj->GetName());
		TH1D *h2 = (TH1D*)ffile2->Get(obj->GetName());
            cout<<"plotting "<<obj->GetName()<<endl;
		if(TString(obj->GetName()).Contains("\_Q2")) h->GetXaxis()->SetTitle("Q^{2}(GeV^{2})");
		else if (TString(obj->GetName()).Contains("\_mode")) h->GetXaxis()->SetTitle("NEUT mode");
		else if (TString(obj->GetName()).Contains("\_W2")) h->GetXaxis()->SetTitle("W^{2}(GeV^{2})");
		else if (TString(obj->GetName()).Contains("\_npi")) h->GetXaxis()->SetTitle("No. of pions");
		else if (TString(obj->GetName()).Contains("\_anglemu")) h->GetXaxis()->SetTitle("#theta_{#mu}");
		else if (TString(obj->GetName()).Contains("\_anglepi")) h->GetXaxis()->SetTitle("#theta_{#pi}");
		else if (TString(obj->GetName()).Contains("\_angleneu\_in")) h->GetXaxis()->SetTitle("Incoming #theta_{nucleon}");
		else if (TString(obj->GetName()).Contains("\_pmu")) h->GetXaxis()->SetTitle("P_{#mu}(GeV)");
                else if (TString(obj->GetName()).Contains("\_ppi")) h->GetXaxis()->SetTitle("P_{#pi}(GeV)");
		else if (TString(obj->GetName()).Contains("\_pneu\_in")) h->GetXaxis()->SetTitle("Incoming P_{nucleon}(GeV)");
		else if (TString(obj->GetName()).Contains("\_cosanglemu")) h->GetXaxis()->SetTitle("cos#theta_{#mu}");
		else if (TString(obj->GetName()).Contains("\_cosanglepi")) h->GetXaxis()->SetTitle("cos#theta_{#pi}");
		else if (TString(obj->GetName()).Contains("\_cosangleneu\_in")) h->GetXaxis()->SetTitle("Incoming cos#theta_{nucleon}");
		else if (TString(obj->GetName()).Contains("\_enurec")) h->GetXaxis()->SetTitle("Recontructed E_{#nu} (GeV)");
		else if (TString(obj->GetName()).Contains("\_q2rec")) h->GetXaxis()->SetTitle("Recontructed Q^{2}(GeV^{2})");
		else if (TString(obj->GetName()).Contains("\_t")) h->GetXaxis()->SetTitle("|t|-momentum transfer (GeV^{2})");
		if(TString(obj->GetName()).Contains("\_XS") ) {
		   plot2hist(h,vername,h2,vername2,savename+TString(obj->GetName()),0.6,0.6);
		}
		else if (TString(obj->GetName()).Contains("TotXS") ){ 
		h->GetXaxis()->SetRangeUser(0,10);
		plot2hist(h,vername,h2,vername2,savename+TString(obj->GetName()),0.18,0.67); 
		}
		else if (TString(obj->GetName()).Contains("flux\_numu") ){ 
                h->GetXaxis()->SetRangeUser(0,10);
                plot2hist(h,vername,h2,vername2,savename+TString(obj->GetName()),0.6,0.6);
                }
		else plot2hist_stat(h,vername,h2,vername2,"",savename+TString(obj->GetName()),false);	
        }
    }
    
    /*for (ii=0; ii<vkeytitle.size(); ii++) {
 *      cout << vkeytitle.at(ii)<<" "<<vkeyclassname.at(ii)<<endl;
 *           }*/
}

