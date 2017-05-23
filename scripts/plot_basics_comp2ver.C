void plot_basics_comp2ver(){
    gROOT->ProcessLine(".x rootlogon.C"); 
    gROOT->ProcessLine(".L basicPlotUtil.C");
    TString ipDir = "/home/cvson/disk/nuicise/neut/neut_5.4.0_alpha/src/neutsmpl/";
    TFile *ffile = new TFile(ipDir+"basicplot_neut540.root");
    TString vername = "NEUT 5.4.0"; 
    TFile *ffile2 = new TFile(ipDir+"basicplot_neut532.root");
    TString vername2 = "NEUT 5.3.2";
    TString savename ="comp_v540_v532_"; 
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
		//plot2hist(h,vername,h2,vername2,savename+TString(obj->GetName()),0.65,0.65);
		plot2hist_stat(h,vername,h2,vername2,TString(obj->GetName()),savename+TString(obj->GetName()),false);	
        }
    }
    
    /*for (ii=0; ii<vkeytitle.size(); ii++) {
 *      cout << vkeytitle.at(ii)<<" "<<vkeyclassname.at(ii)<<endl;
 *           }*/
}

