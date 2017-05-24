void plot_basics_v532(){
    TString ipDir = "/home/cvson/disk/nuicise/neut/neut_5.4.0_alpha/src/neutsmpl/";
    TFile *ffile = new TFile(ipDir+"basic_plot_neutv532.root");
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
            cout<<"plotting "<<obj->GetName()<<endl;
            new TCanvas;
            h->Draw();
            gPad->Print("plots/v532_h1_nd5_ch_"+TString(obj->GetName())+".eps");
        }
    }
    
    /*for (ii=0; ii<vkeytitle.size(); ii++) {
 *      cout << vkeytitle.at(ii)<<" "<<vkeyclassname.at(ii)<<endl;
 *           }*/
}

