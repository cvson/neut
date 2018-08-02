//
//  read_xsec_coh_comp.C
////////////////////////////////////////////////////
//
//  To compare ccqe cross section with different model: global fermi gas, local fermigas, spectral fuction, Nieve 1p1h
//
///////////////////////////////////////////////////

void t2kpre_read_xsec_coh_comp(){
    gROOT->ProcessLine(".x rootlogon.C");
    gROOT->ProcessLine(".L basicPlotUtil.C");
    const Int_t NMODE4COMP = 2;
    TFile *pfile[NMODE4COMP];
    pfile[0] = new TFile("test_neut540kek_1p1hccqe_cohBS.root","READ");
    pfile[1] = new TFile("test_neut540kek_1p1hccqe_cohRS.root","READ");
    TString neutversion_s = "neut540";
    TString neutversion = "NEUT v5.4.0";
    TString subname = "comp2cohmodel";
    
    char *modestr[NMODE4COMP]={"Berger-Seghal","Rein-Seghal"};
    
    const int NCHANNEL = 27;//from neut 5.3.6 npnh included
    TH1D *hxsec[NMODE4COMP][NCHANNEL];
    char *namechan[NCHANNEL]={"tot","ccqe","ccppip","ccppi0","ccnpip","cccoh","ccgam","ccmpi","cceta","cck","ccdis","ncnpi0","ncppi0","ncppim","ncnpip","nccoh","ncngam","ncpgam","ncmpi","ncneta","ncpeta","nck0","nckp","ncdis","ncqep","ncqen","npnh"};
    
     char *namechan_tex[NCHANNEL]={"Total","#nu_{l}+ n #rightarrow l^{-} + p","#nu_{l}+ p #rightarrow l^{-}+ p +#pi^{+}","#nu_{l}+ n #rightarrow l^{-}+ p+ #pi^{0}"," #nu_{l}+ n #rightarrow l^{-}+ n+ #pi^{+}","#nu_{l}+ ^{12}C #rightarrow l^{-}+ ^{12}C+ #pi^{+}","#nu_{l}+ n #rightarrow l^{-}+ p+ #gamma","#nu_{l}+ N #rightarrow l^{-}+ N'+ multi-#pi","#nu_{l}+ n #rightarrow l^{-}+ p+ #eta","#nu_{l}+ n #rightarrow l^{-}+ #Lambda+ K^{+}","nu_{l}+ N #rightarrow l^{-}+ N' +mesons","#nu_{l}+ n #rightarrow #nu_{l}+ n+ #pi^{0}","#nu_{l}+ p #rightarrow #nu_{l}+ p+ #pi^{0}","nu_{l}+ n #rightarrow #nu_{l}+ p+ #pi^{-}","nu_{l}+ p #rightarrow #nu_{l}+ n +#pi^{+}","#nu_{l}+ ^{12}C #rightarrow #nu_{l}+ ^{12}C+ #pi^{0}","#nu_{l}+ n #rightarrow #nu_{l}+ n+ #gamma","#nu_{l}+ p #rightarrow #nu_{l}+ p+ #gamma","#nu_{l}+ N #rightarrow #nu_{l}+ N+ multi-#pi","#nu_{l}+ n #rightarrow #nu_{l}+ n+ #eta","#nu_{l}+ p #rightarrow #nu_{l}+ p+ #eta","#nu_{l}+ n #rightarrow #nu_{l}+ #Lambda +K^{0}","#nu_{l}+ n #rightarrow #nu_{l}+ #Lambda+ K^{+}","#nu_{l}+ N #rightarrow #nu_{l}+ N'+ mesons","#nu_{l}+ p #rightarrow #nu_{l}+ p","#nu_{l}+ n #rightarrow #nu_{l}+ n","np-nh"};
    
    //color for histogram
    const char *colorcode[] = {
        "#0072B2",
        "#D55E00",
        "#CC79A7",
        "#E69F00",
        "#009E73"
    };
    Int_t ci;
    
    for (Int_t imode=0; imode<NMODE4COMP; ++imode) {
        for (Int_t ichan=0; ichan<NCHANNEL; ++ichan) {
            hxsec[imode][ichan] = (TH1D*)pfile[imode]->Get(Form("neut_xsec_numu_%s",namechan[ichan]));
            cout<<"channel "<<ichan<<" inte "<<hxsec[imode][ichan]->Integral()<<endl;
            ci = TColor::GetColor(colorcode[imode]);
            hxsec[imode][ichan]->SetLineColor(ci);
            hxsec[imode][ichan]->SetLineWidth(2);
        }
    }
    
    TLegend* leg0 = new TLegend(.2, .72, 0.5, .9);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(18);
    leg0->SetTextFont(43);
    for (Int_t imode=0; imode<NMODE4COMP; ++imode) {
        leg0->AddEntry(hxsec[imode][0],modestr[imode],"l");
    }
    

    
    //plots for individual channel
    for (Int_t ichan=0; ichan<NCHANNEL; ++ichan) {
        if(ichan==5 || ichan==15) {new TCanvas;
        gStyle->SetOptStat(0);
        hxsec[0][ichan]->GetXaxis()->SetRangeUser(0,5);//check from 0-5 GeV
            hxsec[0][ichan]->GetYaxis()->SetRangeUser(0,0.65e-39);
        hxsec[0][ichan]->SetTitle("");
        titleStyle(hxsec[0][ichan]);
        hxsec[0][ichan]->Draw("hist");
        for (Int_t imode=1; imode<NMODE4COMP; ++imode) {
            hxsec[imode][ichan]->Draw("hist same");
        }
        leg0->Draw();
        //NEUT version text
        TLatex *l1 = new TLatex(0.3, 0.98, Form("%s, %s",neutversion.Data(),namechan_tex[ichan]));
        l1->SetNDC();
        l1->SetTextFont(43);
        l1->SetTextSize(20);
        l1->SetTextAlign(13);
        l1->Draw();
        gPad->Print(Form("plots/%s_xsec_numu_%s_channel_%s.eps",neutversion_s.Data(),subname.Data(),namechan[ichan]));
    }
    }
    
    
    
    
}
