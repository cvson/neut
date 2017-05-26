void plot_basics_comp3ver(){
    gROOT->ProcessLine(".x rootlogon.C"); 
    gROOT->ProcessLine(".L basicPlotUtil.C");
    TString ipDir = "/home/cvson/disk/nuicise/neut/neut_5.4.0_alpha/src/neutsmpl/";
    /*TFile *ffile = new TFile(ipDir+"basicplot_neut540.root");
    TString vername = "NEUT 5.4.0"; 
  
     TFile *ffile1 = new TFile(ipDir+"basicplot_neut537.root");
    TString vername1 = "NEUT 5.3.7";

    TFile *ffile2 = new TFile(ipDir+"basicplot_neut532.root");
    TString vername2 = "NEUT 5.3.2";
   
   TString savename ="comp_v540_v537_v532";*/

    /*TFile *ffile = new TFile(ipDir+"basicplot_neut540alpha_MDLQE02.root");
    TString vername = "NEUT 5.4.0"; 
  
     TFile *ffile1 = new TFile(ipDir+"basicplot_neut537_MDLQE02.root");
    TString vername1 = "NEUT 5.3.7";

    TFile *ffile2 = new TFile(ipDir+"basicplot_neut532_MDLQE02.root");
    TString vername2 = "NEUT 5.3.2";
   
   TString savename ="comp3_mdlqe02";*/

    TFile *ffile = new TFile(ipDir+"basicplot_neut540alpha_MDLQE402_RS.root");
    TString vername = "NEUT 5.4.0"; 
  
     TFile *ffile1 = new TFile(ipDir+"basicplot_neut537_MDLQE402_RS.root");
    TString vername1 = "NEUT 5.3.7";

    TFile *ffile2 = new TFile(ipDir+"basicplot_neut532_MDLQE402_RS.root");
    TString vername2 = "NEUT 5.3.2";
   
   TString savename ="comp3_mdlqe402_rs";

    /*TFile *ffile = new TFile(ipDir+"basicplot_neut532_common_down5142.root");
    TString vername = "NEUT 5.3.2 RS"; 
  
     TFile *ffile1 = new TFile(ipDir+"basicplot_neut532_common_down5142_paul.root");
    TString vername1 = "NEUT 5.3.2 RS Paul";

    TFile *ffile2 = new TFile(ipDir+"basicplot_neut532_common_down5142_paul_nueff.root");
    TString vername2 = "NEUT 5.3.2 Paul+NuEff";
   
   TString savename ="comp_v532_paul";*/
 
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
		plot3hist_stat(h,vername,h1,vername1,h2,vername2,TString(obj->GetName()),savename+TString(obj->GetName()),false);	
        }
    }
    
    /*for (ii=0; ii<vkeytitle.size(); ii++) {
 *      cout << vkeytitle.at(ii)<<" "<<vkeyclassname.at(ii)<<endl;
 *           }*/
}

