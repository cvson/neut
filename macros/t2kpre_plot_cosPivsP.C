{
    gROOT->ProcessLine(".x /Users/soncao/rootlogon.C");
    gROOT->ProcessLine(".L /Users/soncao/basicPlotUtil.C");
    
    TString neutversion = "NEUT v5.4.0";
    
    /*TString neutversion_s = "neut540_default";
     TString nuclearmodel_s = "GS model";
     TFile *pfile = new TFile("basicplotsv7_neut540_card_5.4.0_nd5_C_1p1hCCQE_default.root","READ");*/
    
    /*TString neutversion_s = "neut540_1piRS";
    TString nuclearmodel_s = "RS model";
    TFile *pfile = new TFile("basicplotsv7_neut540_card_5.4.0_nd5_C_1p1hCCQE_1piRS.root","READ");*/
    
    /*TString neutversion_s = "neut540_1piRS_histat";
    TString nuclearmodel_s = "RS model";
    TFile *pfile = new TFile("basicplotsv8_neut540_card_5.3.6_nd5_C_1p1hCCQE_1piRS.root","READ");*/
    
    TString neutversion_s = "neut540_default_histat";
    TString nuclearmodel_s = "GS model";
    TFile *pfile = new TFile("basicplotsv8_neut540_card_5.3.6_nd5_C_1p1hCCQE_1pi.root","READ");
    
    const int NFLAVOR = 6;
    const int NHIST1D = 33;
    const int NCHANNEL = 11;//12?
    const int NHIST2D = 8;
    
    /*int hist_index = 6;//initPicosvsP
    char *xtitle = "Cos #theta_{#pi,initial}";
    char *ytitle = "Momentum P_{#pi,initial} (GeV)";*/
    
    int hist_index = 7;//initPicosvsP
    char *xtitle = "Cos #theta_{#pi,final}";
    char *ytitle = "Momentum P_{#pi,final} (GeV)";
    
    int chan_index = 5;//cc1pi
    int flavorindex = 1;//for numu beam
    
   
    
    TH2D *h_2d_combined;//3rd is Evsk for in nuclear 4th is coslepvsP, 5th is bindingEvsk
    
    
    char hist_kind[NCHANNEL][16]={"all\0"    ,"CCall\0"    ,"NCall\0",
        "CCQE\0"   ,"CCMEC\0"    ,"CC1pi\0",
        "CCDIS\0","CCCOH\0","CCtopo0pi\0","CCtopo1pi\0","CCtopoNpi\0"};
    char hist_type_2d[NHIST2D][16]={"in_nuc1_p_rad\0","out_nuc1_p_rad\0","in_nuc1_Evsk\0","coslepvsP\0","q3vsq0\0","bindEvsk\0","initPicosvsP\0","finPicosvsP\0"};//newadd
    
    char flavor_str[NFLAVOR][16]={"nue\0"  ,"numu\0"    ,"nutau\0",
        "nue_bar" ,"numu_bar\0","nutau_bar\0"};
    char flavor_strlatex[NFLAVOR][30]={"#nu_e\0"  ,"#nu_{#mu}\0"    ,"#nu_{#tau}\0",
        "#bar{#nu}_e" ,"#bar{#nu}_{#mu}\0","#bar{#nu}_{#tau}\0"};
    
    
    
    
    
    h_2d_combined= (TH2D*)pfile->Get(Form("h_%s_%s_%s",hist_kind[chan_index],hist_type_2d[hist_index],flavor_str[flavorindex]));
    
    
    //to plots
    
    h_2d_combined->GetXaxis()->SetRangeUser(-1,1.);
    h_2d_combined->GetYaxis()->SetRangeUser(0,2.);
    h_2d_combined->GetXaxis()->SetTitle(xtitle);
    h_2d_combined->GetYaxis()->SetTitle(ytitle);
    
    h_2d_combined->SetTitle("");
    new TCanvas;
    titleStyle(h_2d_combined);
    h_2d_combined->Draw("colz");
    TLatex *l1 = new TLatex(0.3, 0.98, Form("%s,%s,%s",neutversion.Data(),flavor_strlatex[flavorindex],nuclearmodel_s.Data()));
    l1->SetNDC();
    l1->SetTextFont(43);
    l1->SetTextSize(20);
    l1->SetTextAlign(13);
    l1->Draw();
    gPad->Print(Form("plots/%s_%s_%s_%s.eps",neutversion_s.Data(),flavor_str[flavorindex],hist_type_2d[hist_index],hist_kind[chan_index]));
    
    
    
    
}
