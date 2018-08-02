{
    gROOT->ProcessLine(".x /Users/soncao/rootlogon.C");
    gROOT->ProcessLine(".L /Users/soncao/basicPlotUtil.C");
    
    TString neutversion = "NEUT v5.4.0";
    
    TString neutversion_s = "neut540_default";
    TString nuclearmodel_s = "1p1h Nieve";
    TFile *pfile = new TFile("basicplotsv7_neut_5.3.6_nd5_C_1p1hCCQE.root","READ");
    
    /*TString neutversion_s = "neut540_sf";
     TString nuclearmodel_s = "SF";
    TFile *pfile = new TFile("basicplotsv7_neut_5.3.6_nd5_C_SFCCQE.root","READ");*/
    
    /*TString neutversion_s = "neut540_lfg";
     TString nuclearmodel_s = "LFG";
    TFile *pfile = new TFile("basicplotv7_neut540_card_5.4.0_nd5_C_LFGCCQE.root","READ");*/
    
   /* TString neutversion_s = "neut540_lfgrpa";
     TString nuclearmodel_s = "LFG + RPA";
    TFile *pfile = new TFile("basicplotv7_neut540_card_5.4.0_nd5_C_LFGCCQE_RPA.root","READ");
    */
    
    TH2D *h_2d_combined[12][6][6];//3rd is Evsk for in nuclear 4th is coslepvsP, 5th is bindingEvsk
    
    
    char hist_kind[12][16]={"all\0"    ,"CCall\0"    ,"NCall\0",
        "CCQE\0"   ,"CCMEC\0"    ,"CC1pi\0",
        "CCDIS\0","CCCOH\0","CCtopo0pi\0","CCtopo1pi\0","CCtopoNpi\0"};
    char hist_type_2d[6][16]={"in_nuc1_p_rad\0","out_nuc1_p_rad\0","in_nuc1_Evsk\0","coslepvsP\0","q3vsq0\0","bindEvsk\0"};//newadd
    
    char flavor_str[6][16]={"nue\0"  ,"numu\0"    ,"nutau\0",
        "nue_bar" ,"numu_bar\0","nutau_bar\0"};
    char flavor_strlatex[6][30]={"#nu_e\0"  ,"#nu_{#mu}\0"    ,"#nu_{#tau}\0",
        "#bar{#nu}_e" ,"#bar{#nu}_{#mu}\0","#bar{#nu}_{#tau}\0"};
    
    int flavorindex = 1;//for numu beam
    
    
    
    for ( int i = 0 ; i < 11 ; i++ ){//change to 11
        for ( int j = 0 ; j < 6 ; j++ ){//newadd
            h_2d_combined[i][j][flavorindex] = (TH2D*)pfile->Get(Form("h_%s_%s_%s",hist_kind[i],hist_type_2d[j],flavor_str[flavorindex]));
            
        }
    }
    
    //to plots
    int hist_index = 3;//q3vsq0
    for ( int i = 0 ; i < 11 ; i++ ){//change to 11
        h_2d_combined[i][hist_index][flavorindex]->GetXaxis()->SetRangeUser(-1,1.);
        h_2d_combined[i][hist_index][flavorindex]->GetYaxis()->SetRangeUser(0,2.);
        h_2d_combined[i][hist_index][flavorindex]->GetXaxis()->SetTitle("Cos #theta_{#ell}");
        h_2d_combined[i][hist_index][flavorindex]->GetYaxis()->SetTitle("Momentum P_{#ell} (GeV)");
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
