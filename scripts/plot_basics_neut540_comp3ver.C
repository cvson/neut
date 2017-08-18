void plot_basics_neut540_comp3ver(){
    gROOT->ProcessLine(".x rootlogon.C"); 
    gROOT->ProcessLine(".L basicPlotUtil.C");
    TString ipDir = "/home/cvson/disk/nuicise/neut/neut_5.4.0/src/neutsmpl/";

    TFile *ffile = new TFile(ipDir+"basicplot_5.4.0_600MeV_C_CCQE_MDLQE2002.root");
    TString vername = "Nieve 1p1h"; 
  
     TFile *ffile1 = new TFile(ipDir+"basicplot_5.4.0_600MeV_C_CCQE_MDLQE402.root");
    TString vername1 = "Spectral func.";

    TFile *ffile2 = new TFile(ipDir+"basicplot_5.4.0_600MeV_C_CCQE_MDLQE02.root");
    TString vername2 = "Fermi gas";
   
     TString savename ="neut540_comp3_600mev_ccqe";
	

   /*TFile *ffile = new TFile(ipDir+"basicplot_5.4.0_600MeV_C_CC0pi_MDLQE2002.root");
    TString vername = "Nieve 1p1h"; 
  
     TFile *ffile1 = new TFile(ipDir+"basicplot_5.4.0_600MeV_C_CC0pi_MDLQE402.root");
    TString vername1 = "Spectral func.";

    TFile *ffile2 = new TFile(ipDir+"basicplot_5.4.0_600MeV_C_CC0pi_MDLQE02.root");
    TString vername2 = "Fermi gas";
   
   TString savename ="neut540_comp3_600mev_cc0pi";
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
            TH1D *h1 = (TH1D*)ffile1->Get(obj->GetName());
		TH1D *h2 = (TH1D*)ffile2->Get(obj->GetName());
            cout<<"plotting "<<obj->GetName()<<endl;

		//to narrow the range
		if(TString(obj->GetName()).Contains("\_plep")) h->GetXaxis()->SetRangeUser(0,1);
		else if (TString(obj->GetName()).Contains("\_q2")) h->GetXaxis()->SetRangeUser(-1,0);
		else if (TString(obj->GetName()).Contains("\_rescat")) h->GetXaxis()->SetRangeUser(0,2);
		else if (TString(obj->GetName()).Contains("\_enu")) h->GetXaxis()->SetRangeUser(0,5); 
		//plot2hist(h,vername,h2,vername2,savename+TString(obj->GetName()),0.65,0.65);
		 if(TString(obj->GetName()).Contains("\_q2")) h->GetXaxis()->SetTitle("Q^{2}(GeV^{2})");
                else if (TString(obj->GetName()).Contains("\_plep")) h->GetXaxis()->SetTitle("P_{#mu} (GeV)");
                else if (TString(obj->GetName()).Contains("\_coslep")) h->GetXaxis()->SetTitle("Cos(#theta_{#mu})");
                else if (TString(obj->GetName()).Contains("\_enu")) h->GetXaxis()->SetTitle("E_{#nu}(GeV)");
                else if (TString(obj->GetName()).Contains("\_in\_nuc1\_p")) h->GetXaxis()->SetTitle("In-nucleon(1) P (GeV)");
                else if (TString(obj->GetName()).Contains("\_in\_nuc2\_p")) h->GetXaxis()->SetTitle("In-nucleon(2) P (GeV)");
                else if (TString(obj->GetName()).Contains("\_out\_nuc1\_p")) h->GetXaxis()->SetTitle("Out-nucleon(1) P (GeV)");
                else if (TString(obj->GetName()).Contains("\_out\_nuc2\_p")) h->GetXaxis()->SetTitle("Out-nucleon(2) P (GeV)");
                else if (TString(obj->GetName()).Contains("\_in\_nuc1\_cosL")) h->GetXaxis()->SetTitle("In-nucleon(1) Cos(#theta)");
		else if (TString(obj->GetName()).Contains("\_in\_nuc2\_cosL")) h->GetXaxis()->SetTitle("In-nucleon(2) Cos(#theta)");
		else if (TString(obj->GetName()).Contains("\_out\_nuc1\_cosL")) h->GetXaxis()->SetTitle("Out-nucleon(1) Cos(#theta)");
                else if (TString(obj->GetName()).Contains("\_out\_nuc2\_cosL")) h->GetXaxis()->SetTitle("Out-nucleon(2) Cos(#theta)");
                else if (TString(obj->GetName()).Contains("in\_nucs\_open")) h->GetXaxis()->SetTitle("In-nucleon opening angle");
                else if (TString(obj->GetName()).Contains("out\_nucs\_open")) h->GetXaxis()->SetTitle("Out-nucleon opening angle");
		
		else if (TString(obj->GetName()).Contains("\_intr\_pos")) h->GetXaxis()->SetTitle("Interaction pos. in nucleus");
		else if (TString(obj->GetName()).Contains("\_rescat\_nuc1\_p")) h->GetXaxis()->SetTitle("Out-nucleon(1) P after FSI");
                if(TString(obj->GetName()).Contains("\_XS") ) {
                   plot3hist(h,vername,h1,vername1,h2,vername2,savename+TString(obj->GetName()),0.5,0.3);
                }
                else if (TString(obj->GetName()).Contains("TotXS") ) plot3hist(h,vername,h1,vername1,h2,vername2,savename+TString(obj->GetName()),0.5,0.3);
                else plot3hist_stat(h,vername,h1,vername1,h2,vername2,"",savename+TString(obj->GetName()),false);
		//plot3hist_stat(h,vername,h1,vername1,h2,vername2,TString(obj->GetName()),savename+TString(obj->GetName()),false);	
        }
    }
    
    /*for (ii=0; ii<vkeytitle.size(); ii++) {
 *      cout << vkeytitle.at(ii)<<" "<<vkeyclassname.at(ii)<<endl;
 *           }*/
}

