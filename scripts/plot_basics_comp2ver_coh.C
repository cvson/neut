void plot_basics_comp2ver_coh(){
    gROOT->ProcessLine(".x rootlogon.C"); 
    gROOT->ProcessLine(".L basicPlotUtil.C");
    TString ipDir = "/home/cvson/disk/nuicise/neut/neut_5.4.0_alpha/src/neutsmpl/";
    TString ipDir1 = "/home/cvson/disk/nuicise/neut/neut_5.3.7_INGRID_FIX/src/neutsmpl/";
    TString ipDir2 = "/home/cvson/disk/nuicise/neut/neut_5.3.2/src/neutsmpl/";
    
    /*TFile *ffile = new TFile(ipDir+"basicplot_540alpha_nd2_ch_MDLQE2002_COH.root");
    TString vername = "NEUT 5.4.0, Rein-Seghal"; 
    TFile *ffile2 = new TFile(ipDir+"basicplot_540alpha_nd2_ch_MDLQE2002_COH_BS.root");
    TString vername2 = "NEUT 5.4.0, Berger-Seghal";
    TString savename ="nd2_coh_v540_bsvsrs_";*/


    /*TFile *ffile = new TFile(ipDir+"basicplot_540alpha_nd2_ch_MDLQE2002_COH.root");
    TString vername = "NEUT 5.4.0, Rein-Seghal"; 
    TFile *ffile2 = new TFile(ipDir2+"basicplot_532_nd2_ch_MDLQE402_COH.root");
    TString vername2 = "NEUT 5.3.2, Rein-Seghal";
    TString savename ="nd2_coh_v540_v532_rs";*/

    /*TFile *ffile = new TFile(ipDir1+"basicplot_537_nd2_ch_MDLQE402_COH.root");
    TString vername = "NEUT 5.3.7, Rein-Seghal"; 
    TFile *ffile2 = new TFile(ipDir2+"basicplot_532_nd2_ch_MDLQE402_COH.root");
    TString vername2 = "NEUT 5.3.2, Rein-Seghal";
    TString savename ="nd2_coh_v537_v532_rs";*/

    TFile *ffile = new TFile(ipDir+"basicplot_540alpha_nd2_ch_MDLQE402_COH.root");
    TString vername = "NEUT 5.4.0, Rein-Seghal"; 
    TFile *ffile2 = new TFile(ipDir2+"basicplot_532_nd2_ch_MDLQE402_COH.root");
    TString vername2 = "NEUT 5.3.2, Rein-Seghal";
    TString savename ="nd2_coh_v540_v532_rs_mode402_";


    /*TFile *ffile = new TFile(ipDir1+"basicplot_537_nd2_ch_MDLQE402_COH.root");
    TString vername = "NEUT 5.3.7, RS, Spec. Func."; 
    TFile *ffile2 = new TFile(ipDir1+"basicplot_537_nd2_ch_MDLQE02_COH.root");
    TString vername2 = "NEUT 5.3.7, RS, Fermi Gas.";
    TString savename ="nd2_coh_v537_spec_vs_fermi";*/


 
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
		else if (TString(obj->GetName()).Contains("\_anglemu")) h->GetXaxis()->SetTitle("#theta_{#mu}");
		else if (TString(obj->GetName()).Contains("\_anglepi")) h->GetXaxis()->SetTitle("#theta_{#pi}");
		else if (TString(obj->GetName()).Contains("\_pmu")) h->GetXaxis()->SetTitle("P_{#mu}(GeV)");
                else if (TString(obj->GetName()).Contains("\_ppi")) h->GetXaxis()->SetTitle("P_{#pi}(GeV)");
		else if (TString(obj->GetName()).Contains("\_cosanglemu")) h->GetXaxis()->SetTitle("cos#theta_{#mu}");
		else if (TString(obj->GetName()).Contains("\_cosanglepi")) h->GetXaxis()->SetTitle("cos#theta_{#pi}");
		else if (TString(obj->GetName()).Contains("\_enurec")) h->GetXaxis()->SetTitle("Recontructed E_{#nu} (GeV)");
		else if (TString(obj->GetName()).Contains("\_q2rec")) h->GetXaxis()->SetTitle("Recontructed Q^{2}(GeV^{2})");
		else if (TString(obj->GetName()).Contains("\_t")) h->GetXaxis()->SetTitle("|t|-momentum transfer (GeV^{2})");
		if(TString(obj->GetName()).Contains("\_XS") ) {
		   plot2hist(h,vername,h2,vername2,savename+TString(obj->GetName()),0.5,0.3);
		}
		else if (TString(obj->GetName()).Contains("TotXS") ) plot2hist(h,vername,h2,vername2,savename+TString(obj->GetName()),0.5,0.3); 
		else plot2hist_stat(h,vername,h2,vername2,"",savename+TString(obj->GetName()),false);	
        }
    }
    
    /*for (ii=0; ii<vkeytitle.size(); ii++) {
 *      cout << vkeytitle.at(ii)<<" "<<vkeyclassname.at(ii)<<endl;
 *           }*/
}

