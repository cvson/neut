{
    gROOT->ProcessLine(".x /Users/soncao/rootlogon.C");
    gROOT->ProcessLine(".L /Users/soncao/basicPlotUtil.C");
    
    TString neutversion_s = "neut540_1p1h";
    TString neutversion1 = "NEUT v5.4.0, Nieve 1p1h,#bar{#nu}_{#mu}";//no different in neut_3.6
    TString neutversion2 = "NEUT v5.4.0, 2p2h, #bar{#nu}_{#mu}";
    
    TFile *pfile = new TFile("basicplotsv8_neut540_antinu_card_5.3.6_nd5_C_1p1hCCQE_ccqemec.root","READ");
    TH2D *NEUT_mu_cosanglevsp_mode1 = (TH2D*)pfile->Get("h_CCQE_coslepvsP_numu_bar");
    TH2D *NEUT_mu_cosanglevsp_mode2 = (TH2D*)pfile->Get("h_CCMEC_coslepvsP_numu_bar");
    
    TLatex *l1 = new TLatex(0.3, 0.98, Form("%s",neutversion1.Data()));
    l1->SetNDC();
    l1->SetTextFont(43);
    l1->SetTextSize(20);
    l1->SetTextAlign(13);
    
    TLatex *l2 = new TLatex(0.3, 0.98, Form("%s",neutversion2.Data()));
    l2->SetNDC();
    l2->SetTextFont(43);
    l2->SetTextSize(20);
    l2->SetTextAlign(13);
    
    
    new TCanvas;
    //NEUT_mu_cosanglevsp_mode1->GetXaxis()->SetRangeUser(0,1.2);
    //NEUT_mu_cosanglevsp_mode1->GetYaxis()->SetRangeUser(0,1.2);
    NEUT_mu_cosanglevsp_mode1->GetYaxis()->SetTitle("P_{#mu} [GeV]");
    NEUT_mu_cosanglevsp_mode1->GetXaxis()->SetTitle("cos #theta_{#mu}");
    NEUT_mu_cosanglevsp_mode1->SetTitle("");
    titleStyle(NEUT_mu_cosanglevsp_mode1);
    NEUT_mu_cosanglevsp_mode1->Draw("colz");
    l1->Draw();
    gPad->Print(Form("plots/%s_numu_bar_cosanglevsp_CCQE.eps",neutversion_s.Data()));
    
    
    new TCanvas;
    //NEUT_mu_cosanglevsp_mode2->GetXaxis()->SetRangeUser(0,1.2);
    //NEUT_mu_cosanglevsp_mode2->GetYaxis()->SetRangeUser(0,1.2);
    NEUT_mu_cosanglevsp_mode2->GetYaxis()->SetTitle("P_{#mu} [GeV]");
    NEUT_mu_cosanglevsp_mode2->GetXaxis()->SetTitle("cos #theta_{#mu}");
    NEUT_mu_cosanglevsp_mode2->SetTitle("");
    titleStyle(NEUT_mu_cosanglevsp_mode2);
    NEUT_mu_cosanglevsp_mode2->Draw("colz");
    l2->Draw();
    gPad->Print(Form("plots/%s_numu_bar_cosanglevsp_CCMEC.eps",neutversion_s.Data()));
    
}
