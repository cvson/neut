{
    gROOT->ProcessLine(".x /Users/soncao/rootlogon.C");
    gROOT->ProcessLine(".L /Users/soncao/basicPlotUtil.C");
    
    TString neutversion = "NEUT v5.4.0";
    
    //for CC 1pion resonance
    /*TString neutversion_s = "neut540_1piGS";
    TString nuclearmodel_s = "GS model";
    TFile *pfile = new TFile("basicplotsv7_neut540_card_5.4.0_nd5_C_1p1hCCQE_default.root","READ");*/
    /*TString neutversion_s = "neut540_1piGS_histat";
    TString nuclearmodel_s = "GS model";
    TFile *pfile = new TFile("basicplotsv8_neut540_card_5.3.6_nd5_C_1p1hCCQE_1pi.root","READ");*/
    
    
    /*TString neutversion_s = "neut540_1piRS";
    TString nuclearmodel_s = "RS model";
    TFile *pfile = new TFile("basicplotsv7_neut540_card_5.4.0_nd5_C_1p1hCCQE_1piRS.root","READ");*/
    
    /*TString neutversion_s = "neut540_1piRS_histat";
    TString nuclearmodel_s = "RS model";
    TFile *pfile = new TFile("basicplotsv8_neut540_card_5.3.6_nd5_C_1p1hCCQE_1piRS.root","READ");*/
    
    /*TString neutversion_s = "neut540_1p1h_histat";
    TString nuclearmodel_s = "2p2h";
    //TString nuclearmodel_s = "Nieve 1p1h";
    TFile *pfile = new TFile("basicplotsv8_neut540_card_5.3.6_nd5_C_1p1hCCQE_ccqemec.root","READ");
    int channelindex = 4;//5 cc1pi*/
    
    TString neutversion_s = "wagasci_neut540_default";
    TString nuclearmodel_s = "Nieves 1p1h";
    TFile *pfile = new TFile("basicplotsv9_neut540_card_5.3.6_wagasci_C_1p1hCCQE_ccqemec.root","READ");
    
    /*TString neutversion = "NEUT v5.3.2";
    TString neutversion_s = "neut532_rfgrpa";
    TString nuclearmodel_s = "(RFG+RPA CCQE, GS CC1#pi)";
    TFile *pfile = new TFile("basicplotsv8_neut532_card_5.3.6_nd5_C_GFGCCQErpa.root","READ");*/
    
    int channelindex = 3;//5 cc1pi 4 mec 3 ccqe cc0pi 8
    
     int hist_index = 4;//q3vsq0
    
    const Int_t NCHANNEL = 11;
    
    TH2D *h_2d_combined[12][6][6];//3rd is Evsk for in nuclear 4th is coslepvsP, 5th is bindingEvsk
    
    char hist_kind[NCHANNEL][16]={"all\0"    ,"CCall\0"    ,"CCQE\0",
        "MEC\0"   ,"CCtopo0pi\0"    ,"CCtopo0pi0\0",
        "CCtopo0pi1\0","CCtopo0pi2\0","CCtopo0pi3\0","CCtopo0pi4\0","CCtopo0pi5\0"};
    
    
    char hist_type_2d[6][16]={"in_nuc1_p_rad\0","out_nuc1_p_rad\0","in_nuc1_Evsk\0","coslepvsP\0","q3vsq0\0","bindEvsk\0"};//newadd
    
    char flavor_str[6][16]={"nue\0"  ,"numu\0"    ,"nutau\0",
        "nue_bar" ,"numu_bar\0","nutau_bar\0"};
    char flavor_strlatex[6][30]={"#nu_e\0"  ,"#nu_{#mu}\0"    ,"#nu_{#tau}\0",
        "#bar{#nu}_e" ,"#bar{#nu}_{#mu}\0","#bar{#nu}_{#tau}\0"};
    
    int flavorindex = 1;//for numu beam
    
    
    
    for ( int i = 0 ; i < 11 ; i++ ){//change to 11
        for ( int j = 0 ; j < 6 ; j++ ){//newadd
            if(i==channelindex){h_2d_combined[i][j][flavorindex] = (TH2D*)pfile->Get(Form("h_%s_%s_%s",hist_kind[i],hist_type_2d[j],flavor_str[flavorindex]));
            }
            
        }
    }
    
    //to plots
   
    for ( int i = 0 ; i < 11 ; i++ ){//change to 11
        if(i==channelindex){//for CCresonance only
        h_2d_combined[i][hist_index][flavorindex]->GetXaxis()->SetRangeUser(0,1.2);
        h_2d_combined[i][hist_index][flavorindex]->GetYaxis()->SetRangeUser(0,1.2);
        h_2d_combined[i][hist_index][flavorindex]->GetYaxis()->SetTitle("True energy transfer (GeV)");
        h_2d_combined[i][hist_index][flavorindex]->GetXaxis()->SetTitle("q3=|q3| true three momentum transfer (GeV)");
        h_2d_combined[i][hist_index][flavorindex]->SetTitle("");
        new TCanvas;
        titleStyle(h_2d_combined[i][hist_index][flavorindex]);
        h_2d_combined[i][hist_index][flavorindex]->Draw("colz");
        TLatex *l1 = new TLatex(0.3, 0.98, Form("%s,%s %s,%s",neutversion.Data(),flavor_strlatex[flavorindex],hist_kind[i],nuclearmodel_s.Data()));
        l1->SetNDC();
        l1->SetTextFont(43);
        l1->SetTextSize(20);
        l1->SetTextAlign(13);
        l1->Draw();
        gPad->Print(Form("plots/%s_%s_%s_%s.eps",neutversion_s.Data(),flavor_str[flavorindex],hist_type_2d[hist_index],hist_kind[i]));
        }
    }
    
    
   
    
}
