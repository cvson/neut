void plot_basics_comp2ver_norm(){
    gROOT->ProcessLine(".x rootlogon.C"); 
    gROOT->ProcessLine(".L basicPlotUtil.C");
    TString ipDir = "/home/cvson/disk/nuicise/neut/neut_5.4.0_alpha/src/neutsmpl/";
    /*TFile *ffile = new TFile(ipDir+"basicplot_neut540.root");
    TString vername = "NEUT 5.4.0"; 
    TFile *ffile2 = new TFile(ipDir+"basicplot_neut532.root");
    TString vername2 = "NEUT 5.3.2";
    TString savename ="comp_v540_v532_";*/

    /* TFile *ffile = new TFile(ipDir+"basicplot_neut540.root");
    TString vername = "NEUT 5.4.0, Spec. Func."; 
    TFile *ffile2 = new TFile(ipDir+"basicplot_neut540alpha_MDLQE02.root");
    TString vername2 = "NEUT 5.4.0, Fermi G.";
    TString savename ="v540_mdlqe402_vs02_";*/

    /*TFile *ffile = new TFile(ipDir+"basicplot_neut540.root");
    TString vername = "NEUT 5.4.0, Graczyk-Sobczyk"; 
    TFile *ffile2 = new TFile(ipDir+"basicplot_neut540alpha_MDLQE402_RS.root");
    TString vername2 = "NEUT 5.4.0, Rein-Seghal";
    TString savename ="v540_mdlqe402_gsvsrs_";*/

    /*TFile *ffile = new TFile(ipDir+"basicplot_neut532.root");
    TString vername = "NEUT 5.3.2, Graczyk-Sobczyk"; 
    TFile *ffile2 = new TFile(ipDir+"basicplot_neut532_MDLQE402_RS.root");
    TString vername2 = "NEUT 5.3.2, Rein-Seghal";
    TString savename ="v532_mdlqe402_gsvsrs_";*/

    /*TFile *ffile = new TFile(ipDir+"basicplot_neut5142_common.root");
    TString vername = "NEUT 5.1.4.2"; 
    TFile *ffile2 = new TFile(ipDir+"basicplot_neut532_common.root");
    TString vername2 = "NEUT 5.3.2";
    TString savename ="comp_v5142_v532_common_";*/
  
    /*TFile *ffile = new TFile(ipDir+"basicplot_neut5142_common.root");
    TString vername = "NEUT 5.1.4.2"; 
    TFile *ffile2 = new TFile(ipDir+"basicplot_neut532_common_down5142.root");
    TString vername2 = "NEUT 5.3.2, RS";
    TString savename ="comp_v5142_v532down_common_";*/


    /*TFile *ffile = new TFile(ipDir+"basicplot_neut532_common.root");
    TString vername = "NEUT 5.3.2 BS, no piless"; 
    TFile *ffile2 = new TFile(ipDir+"basicplot_neut532_common_down5142.root");
    TString vername2 = "NEUT 5.3.2 RS";
    TString savename ="comp_v532_common_";*/

    /*TFile *ffile = new TFile(ipDir+"basicplot_norm_540_nd2_ch_MDLQE402_ALL.root");
    TString vername = "NEUT 5.4.0, Spec. Func."; 
    TFile *ffile2 = new TFile(ipDir+"basicplot_norm_540_nd2_ch_MDLQE02_ALL.root");
    TString vername2 = "NEUT 5.4.0, Fermi G.";
    TString savename ="nd2_v540norm_mdlqe402_vs02_";
	*/
   /* TFile *ffile = new TFile(ipDir+"basicplot_norm_540_nd2_ch_MDLQE402_ALL.root");
    TString vername = "NEUT 5.4.0, Graczyk-Sobczyk"; 
    TFile *ffile2 = new TFile(ipDir+"basicplot_norm_540_nd2_ch_MDLQE402_RS4pi_ALL.root");
    TString vername2 = "NEUT 5.4.0, Rein-Seghal";
    TString savename ="nd2_v540norm_mdlqe402_gsvsrs_";*/
 
TFile *ffile = new TFile(ipDir+"basicplot_norm_540_nd2_ch_MDLQE402_RS4pi_ALL.root");
    TString vername = "NEUT 5.4.0, Rein-Seghal"; 
    TFile *ffile2 = new TFile(ipDir+"basicplot_norm_540_nd2_ch_MDLQE402_RS4pi20piless_ALL.root");
    TString vername2 = "NEUT 5.4.0, Rein-Seghal, 20%PDD";
    TString savename ="nd2_v540norm_mdlqe402_RS4pi_piless_";

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
		if(TString(obj->GetName()).Contains("\_plep")) h->GetXaxis()->SetRangeUser(0,1);
		else if (TString(obj->GetName()).Contains("\_q2")) h->GetXaxis()->SetRangeUser(-1,0);
		else if (TString(obj->GetName()).Contains("\_rescat")) h->GetXaxis()->SetRangeUser(0,2);
		else if (TString(obj->GetName()).Contains("\_enu")) h->GetXaxis()->SetRangeUser(0,5);
		//plot2hist(h,vername,h2,vername2,savename+TString(obj->GetName()),0.65,0.65);
		plot2hist_stat(h,vername,h2,vername2,TString(obj->GetName()),savename+TString(obj->GetName()),false);	
        }
    }
    
    /*for (ii=0; ii<vkeytitle.size(); ii++) {
 *      cout << vkeytitle.at(ii)<<" "<<vkeyclassname.at(ii)<<endl;
 *           }*/
}

