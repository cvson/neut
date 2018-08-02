//
//  read_xsec_cc1pi_comp.C
////////////////////////////////////////////////////
//
//  To compare ccqe cross section with different model: global fermi gas, local fermigas, spectral fuction, Nieve 1p1h
//
///////////////////////////////////////////////////

void read_xsec_cc1pibar_comp(){
    gROOT->ProcessLine(".x rootlogon.C");
    gROOT->ProcessLine(".L basicPlotUtil.C");
    const Int_t NMODE4COMP = 2;
    TFile *pfile[NMODE4COMP];
    pfile[0] = new TFile("xsecE_neut540_card_5.3.6_nd5_C_1p1hCCQE.root","READ");
    pfile[1] = new TFile("xsecE_neut540_card_5.3.6_nd5_C_1p1hCCQE_1piRS.root","READ");
    //pfile[2] = new TFile("/home/cvson/nuicise/neut/neut_5.3.6/src/neutsmpl/test_xsec_cc1pi_rs_nd5_gfg.root","READ");
    TString neutversion_s = "neut540";
    TString neutversion = "NEUT v5.4.0";//no different in neut_3.6
    //TString neutversion = "NEUT";
    //placeholder for Minoo's model
    TString subname = "comp3modecc1pi";
    
    char *modestr[NMODE4COMP]={"Graczyk-Sobczyk","Rein-Seghal"};
    
    const int NCHANNEL = 27;//from neut 5.3.6 npnh included
    TH1D *hxsec[NMODE4COMP][NCHANNEL];
    char *namechan[NCHANNEL]={"tot","ccqe","ccppip","ccppi0","ccnpip","cccoh","ccgam","ccmpi","cceta","cck","ccdis","ncnpi0","ncppi0","ncppim","ncnpip","nccoh","ncngam","ncpgam","ncmpi","ncneta","ncpeta","nck0","nckp","ncdis","ncqep","ncqen","npnh"};
    
     /*char *namechan_tex[NCHANNEL]={"Total","#nu_{l}+ n #rightarrow l^{-} + p","#nu_{l}+ p #rightarrow l^{-}+ p +#pi^{+}","#nu_{l}+ n #rightarrow l^{-}+ p+ #pi^{0}"," #nu_{l}+ n #rightarrow l^{-}+ n+ #pi^{+}","#nu_{l}+ ^{12}C #rightarrow l^{-}+ ^{12}C+ #pi^{+}","#nu_{l}+ n #rightarrow l^{-}+ p+ #gamma","#nu_{l}+ N #rightarrow l^{-}+ N'+ multi-#pi","#nu_{l}+ n #rightarrow l^{-}+ p+ #eta","#nu_{l}+ n #rightarrow l^{-}+ #Lambda+ K^{+}","nu_{l}+ N #rightarrow l^{-}+ N' +mesons","#nu_{l}+ n #rightarrow #nu_{l}+ n+ #pi^{0}","#nu_{l}+ p #rightarrow #nu_{l}+ p+ #pi^{0}","nu_{l}+ n #rightarrow #nu_{l}+ p+ #pi^{-}","nu_{l}+ p #rightarrow #nu_{l}+ n +#pi^{+}","#nu_{l}+ ^{12}C #rightarrow #nu_{l}+ ^{12}C+ #pi^{0}","#nu_{l}+ n #rightarrow #nu_{l}+ n+ #gamma","#nu_{l}+ p #rightarrow #nu_{l}+ p+ #gamma","#nu_{l}+ N #rightarrow #nu_{l}+ N+ multi-#pi","#nu_{l}+ n #rightarrow #nu_{l}+ n+ #eta","#nu_{l}+ p #rightarrow #nu_{l}+ p+ #eta","#nu_{l}+ n #rightarrow #nu_{l}+ #Lambda +K^{0}","#nu_{l}+ n #rightarrow #nu_{l}+ #Lambda+ K^{+}","#nu_{l}+ N #rightarrow #nu_{l}+ N'+ mesons","#nu_{l}+ p #rightarrow #nu_{l}+ p","#nu_{l}+ n #rightarrow #nu_{l}+ n","np-nh"};*/
    
    //for antineutrino
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
        new TCanvas;
        gStyle->SetOptStat(0);
        hxsec[0][ichan]->GetXaxis()->SetRangeUser(0,5);//check from 0-5 GeV
        hxsec[0][ichan]->SetTitle("");
        double ymax = TMath::Max(hxsec[0][ichan]->GetMaximum(), hxsec[1][ichan]->GetMaximum());
        hxsec[0][ichan]->GetYaxis()->SetRangeUser(0, ymax*1.2);
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
        gPad->Print(Form("plots/%s_xsec_numub_%s_channel_%s.eps",neutversion_s.Data(),subname.Data(),namechan[ichan]));
    
    }
    
    //group by event topologies
    const int NCHAN4SHOW = 2;
    char *namechan4show[NCHAN4SHOW] = {"CC single #pi","NC single #pi"};
    char *namechan4show_s[NCHAN4SHOW] = {"cc1pi", "nc1pi"};
    TH1D *hxsec4show[NMODE4COMP][NCHAN4SHOW];
    for (Int_t imode=0; imode<NMODE4COMP; ++imode) {
        hxsec4show[imode][0] = (TH1D*)hxsec[imode][2]->Clone(Form("hcc1pi_mode%d",imode));
        hxsec4show[imode][0]->Add(hxsec[imode][3]);
        hxsec4show[imode][0]->Add(hxsec[imode][4]);
        
        hxsec4show[imode][1] = (TH1D*)hxsec[imode][11]->Clone(Form("hcc1pi_mode%d",imode));
       
        for (Int_t ichan=12; ichan<15; ++ichan) {
            hxsec4show[imode][1]->Add(hxsec[imode][ichan]);
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
    
    for (Int_t ichan=0; ichan<NCHAN4SHOW; ++ichan) {
        new TCanvas;
        gStyle->SetOptStat(0);
        hxsec4show[0][ichan]->GetXaxis()->SetRangeUser(0,5);//check from 0-5 GeV
        double ymax = TMath::Max(hxsec4show[0][ichan]->GetMaximum(), hxsec4show[1][ichan]->GetMaximum());
        hxsec4show[0][ichan]->GetYaxis()->SetRangeUser(0, ymax*1.2);
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
