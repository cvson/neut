//
//  read_xsec_dis_sf540vs532.C
////////////////////////////////////////////////////
//
//  To compare 1ph1h and sf for vaious channels
//
///////////////////////////////////////////////////
//  Created by S. Cao, cvson@utexas.edu
//  KEY: TH1D	neut_xsec_numu_tot;1	#sigma Total
//  KEY: TH1D	neut_xsec_numu_ccqe;1	#sigma CCQE: #nu_{l} n #rightarrow l^{-} p
//  KEY: TH1D	neut_xsec_numu_npnh;1	#sigma Nieves np-nh
//  KEY: TH1D	neut_xsec_numu_ccppip;1	#sigma CC 1#pi: #nu_{l} p #rightarrow l^{-} p #pi^{+}
//  KEY: TH1D	neut_xsec_numu_ccppi0;1	#sigma CC 1#pi: #nu_{l} n #rightarrow l^{-} p #pi^{0}
//  KEY: TH1D	neut_xsec_numu_ccnpip;1	#sigma CC 1#pi: #nu_{l} n #rightarrow l^{-} n #pi^{+}
//  KEY: TH1D	neut_xsec_numu_cccoh;1	#sigma CC coherent-#pi: #nu_{l} ^{16}O #rightarrow l^{-} ^{16}O #pi^{+}
//  KEY: TH1D	neut_xsec_numu_ccgam;1	#sigma 1#gamma from #Delta: #nu_{l} n #rightarrow l^{-} p #gamma
//  KEY: TH1D	neut_xsec_numu_ccmpi;1	#sigma CC (1.3 < W < 2 GeV): #nu_{l} N #rightarrow l^{-} N' multi-#pi
//  KEY: TH1D	neut_xsec_numu_cceta;1	#sigma CC 1#eta: #nu_{l} n #rightarrow l^{-} p #eta
//  KEY: TH1D	neut_xsec_numu_cck;1	#sigma CC 1K: #nu_{l} n #rightarrow l^{-} #Lambda K^{+}
//  KEY: TH1D	neut_xsec_numu_ccdis;1	#sigma CC DIS (2 GeV < W): #nu_{l} N #rightarrow l^{-} N' mesons
//  KEY: TH1D	neut_xsec_numu_ncnpi0;1	#sigma NC 1#pi: #nu_{l} n #rightarrow #nu_{l} n #pi^{0}
//  KEY: TH1D	neut_xsec_numu_ncppi0;1	#sigma NC 1#pi: #nu_{l} p #rightarrow #nu_{l} p #pi^{0}
//  KEY: TH1D	neut_xsec_numu_ncppim;1	#sigma NC 1#pi: #nu_{l} n #rightarrow #nu_{l} p #pi^{-}
//  KEY: TH1D	neut_xsec_numu_ncnpip;1	#sigma NC 1#pi: #nu_{l} p #rightarrow #nu_{l} n #pi^{+}
//  KEY: TH1D	neut_xsec_numu_nccoh;1	#sigma NC coherent-#pi: #nu_{l} ^{16}O #rightarrow #nu_{l} ^{16}O #pi^{0}
//  KEY: TH1D	neut_xsec_numu_ncngam;1	#sigma 1#gamma from #Delta: #nu_{l} n #rightarrow #nu_{l} n #gamma
//  KEY: TH1D	neut_xsec_numu_ncpgam;1	#sigma 1#gamma from #Delta: #nu_{l} p #rightarrow #nu_{l} p #gamma
//  KEY: TH1D	neut_xsec_numu_ncmpi;1	#sigma NC (1.3 < W < 2 GeV): #nu_{l} N #rightarrow #nu_{l} N multi-#pi
//  KEY: TH1D	neut_xsec_numu_ncneta;1	#sigma NC 1#eta: #nu_{l} n #rightarrow #nu_{l} n #eta
//  KEY: TH1D	neut_xsec_numu_ncpeta;1	#sigma NC 1#eta: #nu_{l} p #rightarrow #nu_{l} p #eta
//  KEY: TH1D	neut_xsec_numu_nck0;1	#sigma NC 1K: #nu_{l} n #rightarrow #nu_{l} #Lambda K^{0}
//  KEY: TH1D	neut_xsec_numu_nckp;1	#sigma NC 1K: #nu_{l} n #rightarrow #nu_{l} #Lambda K^{+}
//  KEY: TH1D	neut_xsec_numu_ncdis;1	#sigma NC DIS (2 GeV < W): #nu_{l} N #rightarrow #nu_{l} N' mesons
//  KEY: TH1D	neut_xsec_numu_ncqep;1	#sigma NC elastic: #nu_{l} p #rightarrow #nu_{l} p
//  KEY: TH1D	neut_xsec_numu_ncqen;1	#sigma NC elastic: #nu_{l} n #rightarrow #nu_{l} n
void t2kpre_read_xsec_dis_v540vs532(){
    gROOT->ProcessLine(".x rootlogon.C");
    gROOT->ProcessLine(".L basicPlotUtil.C");
    
    /*TFile *pfile = new TFile("test_neut540kek_gfgccqe.root","READ");
    TFile *p2file = new TFile("v532_xsecE_card_5.3.6_nd5_C_GFGCCQE.root","READ");
    TString subname = "gfg540vs532";*/
    
    TFile *pfile = new TFile("test_neut540kek_card_5.3.6_nd5_C_GFGCCQE_RS1pi_20piless.root","READ");
    TFile *p2file = new TFile("v532_xsecE_card_5.3.6_nd5_C_GFGCCQE_RS1pi_20piless.root","READ");
    TString subname = "gfg540vs532dis";
    TString neutversion = "NEUT";
    TString neutversion_s = "comp";
    
    
    const int NCHANNEL = 27;//from neut 5.3.6 npnh included
    TH1D *hxsec[NCHANNEL];
    TH1D *h2xsec[NCHANNEL];
    char *namechan[NCHANNEL]={"tot","ccqe","ccppip","ccppi0","ccnpip","cccoh","ccgam","ccmpi","cceta","cck","ccdis","ncnpi0","ncppi0","ncppim","ncnpip","nccoh","ncngam","ncpgam","ncmpi","ncneta","ncpeta","nck0","nckp","ncdis","ncqep","ncqen","ccqe"};
    for (Int_t ichan=0; ichan<NCHANNEL; ++ichan) {
        //This is for interaction of muon neutrino on Carbon, a.k.a C
        //hxsec[ichan] = (TH1D*)pfile->Get(Form("C_xsec_numu_%s",namechan[ichan]));
        hxsec[ichan] = (TH1D*)pfile->Get(Form("neut_xsec_numu_%s",namechan[ichan]));
        h2xsec[ichan] = (TH1D*)p2file->Get(Form("neut_xsec_numu_%s",namechan[ichan]));
        cout<<"channel "<<ichan<<", "<<namechan[ichan]<<" inte "<<hxsec[ichan]->Integral()<<" file2 "<<h2xsec[ichan]->Integral()<<endl;
    }
    const int NCHAN4SHOWCC = 8;
    //char *namechan4show[NCHAN4SHOWCC] = {"CCQE", "2p-2h","CC1#pi^{+}","CC1#pi^{0}","CC Multi #pi, 1.3<W<2.0 GeV","CC DIS W>2.0 GeV","CC others","CC coherent^{*}"};
    char *namechan4show[NCHAN4SHOWCC] = {"CCQE", "2p-2h","CC1#pi^{+}","CC1#pi^{0}","CC Multi #pi","CC DIS ","CC others","CC coherent^{*}"};
    TH1D *hxsec4show[NCHAN4SHOWCC];
    TH1D *h2xsec4show[NCHAN4SHOWCC];
    
    const int NCHAN4SHOWNC = 8;
    //char *namechan4show_nc[NCHAN4SHOWNC] = {"NCEL","NC1#pi^{+}","NC1#pi^{-}","NC1#pi^{0}","NC Multi #pi, 1.3<W<2.0 GeV","NC DIS W>2.0 GeV","NC others","NC coherent^{*}"};
    char *namechan4show_nc[NCHAN4SHOWNC] = {"NCEL","NC1#pi^{+}","NC1#pi^{-}","NC1#pi^{0}","NC Multi #pi","NC DIS","NC others","NC coherent^{*}"};
    TH1D *hxsec4show_nc[NCHAN4SHOWCC];
    TH1D *h2xsec4show_nc[NCHAN4SHOWCC];
    
    hxsec4show[0] = (TH1D*)hxsec[1]->Clone("hccqe");
    hxsec4show_nc[0] = (TH1D*)hxsec[24]->Clone("hncqe");
    hxsec4show_nc[0]->Add(hxsec[25]);
    
    hxsec4show[1] = (TH1D*)hxsec[26]->Clone("npnh");// this is not available in v532
    
    hxsec4show[2] = (TH1D*)hxsec[2]->Clone("hcc1pi");
    hxsec4show[2]->Add(hxsec[4]);
    
    hxsec4show_nc[1] = (TH1D*)hxsec[14]->Clone("hncpiplus");
    hxsec4show_nc[2] = (TH1D*)hxsec[13]->Clone("hncpiminus");
    
    //hxsec4show[2]->Scale(0.5);//average of nucleon
    
    hxsec4show[3] = (TH1D*)hxsec[3]->Clone("hcc1pi0");
    hxsec4show_nc[3] = (TH1D*)hxsec[11]->Clone("hncpi0");
    hxsec4show_nc[3]->Add(hxsec[12]);
    
    hxsec4show[4] = (TH1D*)hxsec[7]->Clone("hccmpi");
    hxsec4show_nc[4] = (TH1D*)hxsec[18]->Clone("hncmultipi");
    
    hxsec4show[5] = (TH1D*)hxsec[10]->Clone("hccdis");
    hxsec4show_nc[5] = (TH1D*)hxsec[23]->Clone("hncdis");
    
    hxsec4show[6] = (TH1D*)hxsec[6]->Clone("hccother");
    hxsec4show[6]->Add(hxsec[8]);
    hxsec4show[6]->Add(hxsec[9]);
    
    hxsec4show_nc[6] = (TH1D*)hxsec[16]->Clone("hncother");
    hxsec4show_nc[6]->Add(hxsec[17]);
    hxsec4show_nc[6]->Add(hxsec[19]);
    hxsec4show_nc[6]->Add(hxsec[20]);
    hxsec4show_nc[6]->Add(hxsec[21]);
    hxsec4show_nc[6]->Add(hxsec[22]);
    
    hxsec4show[7] = (TH1D*)hxsec[5]->Clone("hcccoh");
    hxsec4show_nc[7] = (TH1D*)hxsec[15]->Clone("hnccoh");
    //for 2nd files
    h2xsec4show[0] = (TH1D*)h2xsec[1]->Clone("hccqe");
    h2xsec4show_nc[0] = (TH1D*)h2xsec[24]->Clone("hncqe");
    h2xsec4show_nc[0]->Add(h2xsec[25]);
    
    h2xsec4show[1] = (TH1D*)h2xsec[26]->Clone("npnh");
    
    h2xsec4show[2] = (TH1D*)h2xsec[2]->Clone("hcc1pi");
    h2xsec4show[2]->Add(h2xsec[4]);
    
    h2xsec4show_nc[1] = (TH1D*)h2xsec[14]->Clone("hncpiplus");
    h2xsec4show_nc[2] = (TH1D*)h2xsec[13]->Clone("hncpiminus");
    
    //h2xsec4show[2]->Scale(0.5);//average of nucleon
    
    h2xsec4show[3] = (TH1D*)h2xsec[3]->Clone("hcc1pi0");
    h2xsec4show_nc[3] = (TH1D*)h2xsec[11]->Clone("hncpi0");
    h2xsec4show_nc[3]->Add(h2xsec[12]);
    
    h2xsec4show[4] = (TH1D*)h2xsec[7]->Clone("hccmpi");
    h2xsec4show_nc[4] = (TH1D*)h2xsec[18]->Clone("hncmultipi");
    
    h2xsec4show[5] = (TH1D*)h2xsec[10]->Clone("hccdis");
    h2xsec4show_nc[5] = (TH1D*)h2xsec[23]->Clone("hncdis");
    
    h2xsec4show[6] = (TH1D*)h2xsec[6]->Clone("hccother");
    h2xsec4show[6]->Add(h2xsec[8]);
    h2xsec4show[6]->Add(h2xsec[9]);
    
    h2xsec4show_nc[6] = (TH1D*)h2xsec[16]->Clone("hncother");
    h2xsec4show_nc[6]->Add(h2xsec[17]);
    h2xsec4show_nc[6]->Add(h2xsec[19]);
    h2xsec4show_nc[6]->Add(h2xsec[20]);
    h2xsec4show_nc[6]->Add(h2xsec[21]);
    h2xsec4show_nc[6]->Add(h2xsec[22]);
    
    h2xsec4show[7] = (TH1D*)h2xsec[5]->Clone("hcccoh");
    h2xsec4show_nc[7] = (TH1D*)h2xsec[15]->Clone("hnccoh");
    
    //color for histogram
    const char *colorcode[] = {
        "#000000",
        "#0072B2",
        "#D55E00",
        "#CC79A7",
        "#E69F00",
        "#009E73",
        "#56B4E9",
        "#F0E442"
    };
    
    Int_t ci;
    for (Int_t ichan=0; ichan<NCHAN4SHOWCC; ++ichan) {
        hxsec4show[ichan]->SetLineWidth(2);//increase line widht, default is 1
        h2xsec4show[ichan]->SetLineWidth(2);
        ci = TColor::GetColor(colorcode[ichan]);
        if(ichan==4) ci = TColor::GetColor(colorcode[0]);
        if(ichan==5) ci = TColor::GetColor(colorcode[1]);
        hxsec4show[ichan]->SetLineColor(ci);
        h2xsec4show[ichan]->SetLineColor(ci);
        h2xsec4show[ichan]->SetLineStyle(7);
    }
    
    for (Int_t ichan=0; ichan<NCHAN4SHOWNC; ++ichan) {
        hxsec4show_nc[ichan]->SetLineWidth(2);//increase line widht, default is 1
        h2xsec4show_nc[ichan]->SetLineWidth(2);
        ci = TColor::GetColor(colorcode[ichan]);
        if(ichan==4) ci = TColor::GetColor(colorcode[0]);
        if(ichan==5) ci = TColor::GetColor(colorcode[1]);
        hxsec4show_nc[ichan]->SetLineColor(ci);
        h2xsec4show_nc[ichan]->SetLineColor(ci);
        h2xsec4show_nc[ichan]->SetLineStyle(7);
    }
    
    //to plot DIS only index 4,5
    new TCanvas;
    gStyle->SetOptStat(0);
    hxsec4show[4]->GetXaxis()->SetRangeUser(0,5);//check from 0-5 GeV
    hxsec4show[4]->GetYaxis()->SetRangeUser(0,10.0e-39);
    hxsec4show[4]->SetTitle("");
    titleStyle(hxsec4show[4]);
    hxsec4show[4]->Draw("hist");
    hxsec4show[5]->Draw("hist same");
    h2xsec4show[4]->Draw("hist same");
    h2xsec4show[5]->Draw("hist same");
    //to add legend to the plot
    TLegend* leg0 = new TLegend(.22, .65, 0.5, .9);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(18);
    leg0->SetTextFont(43);
    for (Int_t ichan=0; ichan<NCHAN4SHOWCC; ++ichan) {
        if(ichan==4 || ichan==5)leg0->AddEntry(hxsec4show[ichan],namechan4show[ichan],"l");//remove 2p2h
    }
    leg0->Draw();
    
    
    
    TLegend* leg1 = new TLegend(.45, .7, 0.58, .9);
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetTextSize(18);
    leg1->SetTextFont(43);
    leg1->AddEntry(hxsec4show[0],"v5.4.0","l");
    leg1->AddEntry(h2xsec4show[0],"v5.3.2","l");
    leg1->Draw("same");
    
    TLatex *l1 = new TLatex(0.9, 0.98, Form("%s, Charge Current",neutversion.Data()));
    l1->SetNDC();
    l1->SetTextFont(43);
    l1->SetTextSize(20);
    l1->SetTextAlign(33);
    l1->Draw();
    gPad->Print("plots/"+neutversion_s+"_xsec_numu_"+subname+"_cc.eps");
    
    
    //for DIS only, index 4, 5
    new TCanvas;
    gStyle->SetOptStat(0);
    hxsec4show_nc[4]->GetXaxis()->SetRangeUser(0,5);//check from 0-5 GeV
    hxsec4show_nc[4]->GetYaxis()->SetRangeUser(0,5.0e-39);
    hxsec4show_nc[4]->SetTitle("");
    titleStyle(hxsec4show_nc[4]);
    hxsec4show_nc[4]->Draw("hist");
    hxsec4show_nc[5]->Draw("hist same");
    h2xsec4show_nc[4]->Draw("hist same");
    h2xsec4show_nc[5]->Draw("hist same");
    
    //to add legend to the plot
    TLegend* leg0 = new TLegend(.22, .65, 0.5, .92);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(18);
    leg0->SetTextFont(43);
    for (Int_t ichan=0; ichan<NCHAN4SHOWCC; ++ichan) {
        if(ichan==4 || ichan==5)leg0->AddEntry(hxsec4show_nc[ichan],namechan4show_nc[ichan],"l");
    }
    leg0->Draw();
    leg1->Draw("same");
    TLatex *l2 = new TLatex(0.9, 0.98, Form("%s, Neutral Current",neutversion.Data()));
    l2->SetNDC();
    l2->SetTextFont(43);
    l2->SetTextSize(20);
    l2->SetTextAlign(33);
    l2->Draw();
    gPad->Print("plots/"+neutversion_s+"_xsec_numu_"+subname+"_nc.eps");
    
    //most important comparison
    //new TCanvas;
    //gStyle->SetOptStat(0);
    
    //hxsec4show[0]->Draw("hist");
    
}
