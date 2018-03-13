{
    gROOT->ProcessLine(".x /Users/soncao/rootlogon.C");
    gROOT->ProcessLine(".L /Users/soncao/basicPlotUtil.C");
    
    TString neutversion = "NEUT v5.4.0";
    
    //for CC 1pion coherent
    /*TString neutversion_s = "neut540_cohRS";
    TString nuclearmodel_s = "RS model";
    TFile *pfile = new TFile("basicplotsv8add_neut540_card_5.3.6_nd5_C_1p1hCCQE_coh.root","READ");*/
    
    TString neutversion_s = "neut540_cohBS";
    TString nuclearmodel_s = "BS model";
    TFile *pfile = new TFile("basicplotsv8add_neut540_card_5.3.6_nd5_C_1p1hCCQE_cohBS.root","READ");
    
    
    const int NFLAVOR = 6;
    const int NHIST1D = 34;
    const int NCHANNEL = 11;//12?
    const int NHIST2D = 8;
    
    TH2D *h_2d_combined[NCHANNEL][NHIST2D][NFLAVOR];//3rd is Evsk for in nuclear 4th is coslepvsP, 5th is bindingEvsk
    
    char hist_kind[NCHANNEL][16]={"all\0"    ,"CCall\0"    ,"NCall\0",
        "dis21\0"   ,"dis26\0"    ,"CC1pi\0",
        "CCDIS\0","CCCOH\0","res11\0","res12\0","res13\0"};
    
    
    char hist_type_2d[NHIST2D][16]={"in_nuc1_p_rad\0","out_nuc1_p_rad\0","in_nuc1_Evsk\0","coslepvsP\0","q3vsq0\0","bindEvsk\0","initPicosvsP\0","finPicosvsP\0"};
    
    char flavor_str[NFLAVOR][16]={"nue\0"  ,"numu\0"    ,"nutau\0",
        "nue_bar" ,"numu_bar\0","nutau_bar\0"};
    char flavor_strlatex[NFLAVOR][30]={"#nu_e\0"  ,"#nu_{#mu}\0"    ,"#nu_{#tau}\0",
        "#bar{#nu}_e" ,"#bar{#nu}_{#mu}\0","#bar{#nu}_{#tau}\0"};
    
    int flavorindex = 1;//for numu beam
    
    
    
    for ( int i = 7 ; i < 8 ; i++ ){//COH only
        for ( int j = 0 ; j < NHIST2D ; j++ ){
            h_2d_combined[i][j][flavorindex] = (TH2D*)pfile->Get(Form("h_%s_%s_%s",hist_kind[i],hist_type_2d[j],flavor_str[flavorindex]));
            
        }
    }
    
    //to plots
    int hist_index = 3;//lepton kinemtics
    for ( int i = 7 ; i < 8 ; i++ ){//change to 11
        //h_2d_combined[i][hist_index][flavorindex]->GetXaxis()->SetRangeUser(0,1.2);
        //h_2d_combined[i][hist_index][flavorindex]->GetYaxis()->SetRangeUser(0,1.2);
        h_2d_combined[i][hist_index][flavorindex]->GetYaxis()->SetTitle("cos #theta_{#mu}");
        h_2d_combined[i][hist_index][flavorindex]->GetXaxis()->SetTitle("Momentum P_{#mu} (GeV)");
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
    
    
    hist_index = 6;//initial pion
    for ( int i = 7 ; i < 8 ; i++ ){//change to 11
        //h_2d_combined[i][hist_index][flavorindex]->GetXaxis()->SetRangeUser(0,1.2);
        //h_2d_combined[i][hist_index][flavorindex]->GetYaxis()->SetRangeUser(0,1.2);
        h_2d_combined[i][hist_index][flavorindex]->GetYaxis()->SetTitle("cos #theta_{#pi}");
        h_2d_combined[i][hist_index][flavorindex]->GetXaxis()->SetTitle("Momentum P_{#pi} (GeV)");
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
