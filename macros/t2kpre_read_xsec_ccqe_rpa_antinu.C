//
//  read_xsec_ccqe_comp.C
////////////////////////////////////////////////////
//
//  To compare ccqe cross section with different model: global fermi gas, local fermigas, spectral fuction, Nieve 1p1h
//
///////////////////////////////////////////////////

void t2kpre_read_xsec_ccqe_rpa_antinu(){
    gROOT->ProcessLine(".x rootlogon.C");
    gROOT->ProcessLine(".L basicPlotUtil.C");
    const Int_t NMODE4COMP = 2;
    TFile *pfile[NMODE4COMP];
    TString neutversion_s = "neut540";
    TString neutversion = "NEUT v5.4.0";
    
    pfile[0] = new TFile("test_neut540kek_1p1hccqe_default.root","READ");
    pfile[1] = new TFile("test_neut540kek_1p1hccqe_norpa.root","READ");
    TString subname = "1p1h_rpaeff";
    char *modestr[NMODE4COMP]={"Nieve 1p1h w/ RPA","Nieve 1p1h wo/ RPA"};
    
    /*pfile[0] = new TFile("test_neut540kek_gfgccqe_rpa.root","READ");
    pfile[1] = new TFile("test_neut540kek_gfgccqe.root","READ");
    TString subname = "gfg_rpaeff";
    char *modestr[NMODE4COMP]={"RFG w/ RPA","RFG wo/ RPA"};*/
    
    const int NCHANNEL = 27;//from neut 5.3.6 npnh included
    TH1D *hxsec[NMODE4COMP][NCHANNEL];
    char *namechan[NCHANNEL]={"tot","ccqe","ccppip","ccppi0","ccnpip","cccoh","ccgam","ccmpi","cceta","cck","ccdis","ncnpi0","ncppi0","ncppim","ncnpip","nccoh","ncngam","ncpgam","ncmpi","ncneta","ncpeta","nck0","nckp","ncdis","ncqep","ncqen","npnh"};
    
    char *namechan_tex[NCHANNEL]={"Total",
        "#bar{#nu}_{l}+ p #rightarrow l^{+} + n",
        "#bar{#nu}_{l}+ n #rightarrow l^{+}+ n +#pi^{-}",
        "#bar{#nu}_{l}+ p #rightarrow l^{+}+ n+ #pi^{0}",
        "#bar{#nu}_{l}+ p #rightarrow l^{+}+ p+ #pi^{-}",
        "#bar{#nu}_{l}+ ^{12}C #rightarrow l^{+}+ ^{12}C+ #pi^{-}",
        "#bar{#nu}_{l}+ p #rightarrow l^{+}+ n+ #gamma",
        "#bar{#nu}_{l}+ N #rightarrow l^{+}+ N'+ multi-#pi",
        "#bar{#nu}_{l}+ p #rightarrow l^{+}+ n + #eta",
        "#bar{#nu}_{l}+ p #rightarrow l^{+}+ #Lambda+ K^{+}",
        "#bar{#nu}_{l}+ N #rightarrow l^{+}+ N' +mesons",
        "#bar{#nu}_{l}+ n #rightarrow #bar{#nu}_{l}+ n+ #pi^{0}",
        "#bar{#nu}_{l}+ p #rightarrow #bar{#nu}_{l}+ p+ #pi^{0}",
        "#bar{#nu}_{l}+ n #rightarrow #bar{#nu}_{l}+ p+ #pi^{-}",
        "#bar{#nu}_{l}+ p #rightarrow #bar{#nu}_{l}+ n +#pi^{+}",
        "#bar{#nu}_{l}+ ^{12}C #rightarrow #bar{#nu}_{l}+ ^{12}C+ #pi^{0}",
        "#bar{#nu}_{l}+ n #rightarrow #bar{#nu}_{l}+ n+ #gamma",
        "#bar{#nu}_{l}+ p #rightarrow #bar{#nu}_{l}+ p+ #gamma",
        "#bar{#nu}_{l}+ N #rightarrow #bar{#nu}_{l}+ N+ multi-#pi",
        "#bar{#nu}_{l}+ n #rightarrow #bar{#nu}_{l}+ n+ #eta",
        "#bar{#nu}_{l}+ p #rightarrow #bar{#nu}_{l}+ p+ #eta",
        "#bar{#nu}_{l}+ n #rightarrow #bar{#nu}_{l}+ #Lambda +K^{0}",
        "#bar{#nu}_{l}+ n #rightarrow #bar{#nu}_{l}+ #Lambda+ K^{+}",
        "#bar{#nu}_{l}+ N #rightarrow #bar{#nu}_{l}+ N'+ mesons",
        "#bar{#nu}_{l}+ p #rightarrow #bar{#nu}_{l}+ p",
        "#bar{#nu}_{l}+ n #rightarrow #bar{#nu}_{l}+ n",
        "np-nh"
    };
    
    //color for histogram
    const char *colorcode[] = {
        "#000000",
        "#0072B2",
        "#D55E00",
        "#CC79A7",
        "#E69F00",
        "#009E73"
    };
    Int_t ci;
    
    for (Int_t imode=0; imode<NMODE4COMP; ++imode) {
        for (Int_t ichan=0; ichan<NCHANNEL; ++ichan) {
            hxsec[imode][ichan] = (TH1D*)pfile[imode]->Get(Form("neut_xsec_numub_%s",namechan[ichan]));
            cout<<"channel "<<ichan<<" inte "<<hxsec[imode][ichan]->Integral()<<endl;
            ci = TColor::GetColor(colorcode[imode]);
            hxsec[imode][ichan]->SetLineColor(ci);
            hxsec[imode][ichan]->SetLineWidth(2);
        }
    }
    
    //group by event topologies
    const int NCHAN4SHOW = 6;
    char *namechan4show[NCHAN4SHOW] = {"Total", "CC0#pi","CC1#pi","CC coherent","CC other","NC"};
    char *namechan4show_s[NCHAN4SHOW] = {"Total", "CC0pi","CC1pi","CCcoherent","CCother","NC_s"};
    TH1D *hxsec4show[NMODE4COMP][NCHAN4SHOW];
    for (Int_t imode=0; imode<NMODE4COMP; ++imode) {
        hxsec4show[imode][0] = (TH1D*)hxsec[imode][0]->Clone(Form("htotal_mode%d",imode));
        hxsec4show[imode][1] = (TH1D*)hxsec[imode][1]->Clone(Form("hccqe_mode%d",imode));
        hxsec4show[imode][1]->Add(hxsec[imode][26]);//npnh
        
        hxsec4show[imode][2] = (TH1D*)hxsec[imode][2]->Clone(Form("hcc1pi%d",imode));
        hxsec4show[imode][2]->Add(hxsec[imode][3]);
        hxsec4show[imode][2]->Add(hxsec[imode][4]);
        
        hxsec4show[imode][3] = (TH1D*)hxsec[imode][5]->Clone(Form("hcccoh%d",imode));
        hxsec4show[imode][4] = (TH1D*)hxsec[imode][6]->Clone(Form("hccother%d",imode));
        for (Int_t ichan=7; ichan<11; ++ichan) {
            hxsec4show[imode][4]->Add(hxsec[imode][ichan]);
        }
        
        hxsec4show[imode][5] = (TH1D*)hxsec[imode][11]->Clone(Form("hnc%d",imode));
        for (Int_t ichan=12; ichan<26; ++ichan) {
            hxsec4show[imode][5]->Add(hxsec[imode][ichan]);
        }
    }
    
    //color for the histogram
    for (Int_t imode=0; imode<NMODE4COMP; ++imode) {
        for (Int_t ichan=0; ichan<NCHAN4SHOW; ++ichan) {
            hxsec4show[imode][ichan]->SetLineWidth(2);//increase line widht, default is 1
            ci = TColor::GetColor(colorcode[imode]);
            hxsec4show[imode][ichan]->SetLineColor(ci);
        }
    }
    
    //to add legend to the plot
    TLegend* leg0 = new TLegend(.52, .2, 0.85, .5);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(18);
    leg0->SetTextFont(43);
    for (Int_t imode=0; imode<NMODE4COMP; ++imode) {
        leg0->AddEntry(hxsec4show[imode][0],modestr[imode],"l");
    }
    

    
    //plots for individual channel
    for (Int_t ichan=0; ichan<NCHANNEL; ++ichan) {
        new TCanvas;
        gStyle->SetOptStat(0);
        hxsec[0][ichan]->GetXaxis()->SetRangeUser(0,5);//check from 0-5 GeV
        hxsec[0][ichan]->SetTitle("");
        titleStyle(hxsec[0][ichan]);
        hxsec[0][ichan]->Draw("hist");
        hxsec[0][ichan]->SetMaximum(hxsec[0][ichan]->GetMaximum()*1.5);
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
        gPad->Print(Form("plots/%s_xsec_numub_%s_channel_%s.eps",neutversion_s.Data(),subname.Data(),namechan[ichan]));
    }
    
    
    for (Int_t ichan=0; ichan<NCHAN4SHOW; ++ichan) {
        new TCanvas;
        gStyle->SetOptStat(0);
        hxsec4show[0][ichan]->GetXaxis()->SetRangeUser(0,5);//check from 0-5 GeV
        hxsec4show[0][ichan]->SetTitle("");
        titleStyle(hxsec4show[0][ichan]);
        hxsec4show[0][ichan]->Draw("hist");
        for (Int_t imode=1; imode<NMODE4COMP; ++imode) {
            hxsec4show[imode][ichan]->Draw("hist same");
        }
        leg0->Draw();
        
        TLatex *l1 = new TLatex(0.3, 0.98, Form("%s, %s",neutversion.Data(),namechan4show[ichan]));
        l1->SetNDC();
        l1->SetTextFont(43);
        l1->SetTextSize(20);
        l1->SetTextAlign(13);
        l1->Draw();
        gPad->Print(Form("plots/%s_xsec_numub_%s_channel_%s.eps",neutversion_s.Data(),subname.Data(),namechan4show_s[ichan]));
    }
    
    
    
    
    
}
