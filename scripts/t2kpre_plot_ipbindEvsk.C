{
    gROOT->ProcessLine(".x /Users/soncao/rootlogon.C");
    gROOT->ProcessLine(".L /Users/soncao/basicPlotUtil.C");
    
    //TString neutversion_s = "neut540_antinu";
    TString neutversion_s = "neut540";
    TString neutversion = "NEUT v5.4.0, CCQE";//no different in neut_3.6
    
    
    TString hisname = "h_CCQE_bindEvsk_numu";
    //TString hisname = "h_CCQE_bindEvsk_numu_bar";
    char *modelname[3]={"GFG","LFG","SF"};
    TFile *pfile = new TFile("basicplotsv7_neut540_card_5.4.0_nd5_C_GFGCCQE.root","READ");
    TFile *pfile_2 = new TFile("basicplotsv8_neut540_card_5.4.0_nd5_C_1p1hCCQE_default.root","READ");
    TFile *pfile_3 = new TFile("basicplotsv8_neut540_card_5.3.6_nd5_C_SFCCQE.root","READ");
    double bindingMax = 0.05;//
    double momMax = 0.3;
    

    

    TH2D *NEUT_bindEvsk_mode1 = (TH2D*)pfile->Get(hisname);
    TH2D *NEUT_bindEvsk_mode1_2 = (TH2D*)pfile_2->Get(hisname);
    TH2D *NEUT_bindEvsk_mode1_3 = (TH2D*)pfile_3->Get(hisname);
    
    TLatex *l1 = new TLatex(0.3, 0.98, Form("%s",neutversion.Data()));
    l1->SetNDC();
    l1->SetTextFont(43);
    l1->SetTextSize(20);
    l1->SetTextAlign(13);
    
    Int_t ci;
    
    new TCanvas;
    NEUT_bindEvsk_mode1->GetXaxis()->SetRangeUser(0,momMax);
    NEUT_bindEvsk_mode1->GetYaxis()->SetRangeUser(0,bindingMax);
    NEUT_bindEvsk_mode1->GetZaxis()->SetRangeUser(0,5e11);
    NEUT_bindEvsk_mode1->GetXaxis()->SetTitle("Momentum of incoming nucleon (GeV)");
    NEUT_bindEvsk_mode1->GetYaxis()->SetTitle("Binding Energy (GeV)");
    NEUT_bindEvsk_mode1->SetTitle("");
    titleStyle(NEUT_bindEvsk_mode1);
    
    ci = TColor::GetColor("#D55E00");
    NEUT_bindEvsk_mode1->SetFillColor(ci);
    //NEUT_bindEvsk_mode1->Draw("LEGO1 0");
    
    
    
    
    NEUT_bindEvsk_mode1_2->SetMarkerSize(0.2);
    NEUT_bindEvsk_mode1_2->GetXaxis()->SetRangeUser(0,momMax);
    NEUT_bindEvsk_mode1_2->GetYaxis()->SetRangeUser(0,bindingMax);
    NEUT_bindEvsk_mode1_2->GetZaxis()->SetRangeUser(0,5e11);
    
    ci = TColor::GetColor("#0072B2");
    NEUT_bindEvsk_mode1_2->SetFillColor(ci);
    //NEUT_bindEvsk_mode1_2->Draw("LEGO1 SAME");
    THStack *a = new THStack("a","Stacked 2D histograms");
    a->Add(NEUT_bindEvsk_mode1);
    a->Add(NEUT_bindEvsk_mode1_2);
    
    a->Draw("lego1 0");
    a->GetXaxis()->SetRangeUser(0,momMax);
    a->GetYaxis()->SetRangeUser(0,bindingMax);
    a->GetXaxis()->SetTitle("Momentum of incoming nucleon (GeV)");
    a->GetYaxis()->SetTitle("Binding Energy (GeV)");
    a->GetXaxis()->SetTitleOffset(1.8);
    a->GetYaxis()->SetTitleOffset(1.8);
    a->SetTitle();
    a->Draw("lego1 0");
    
    TLegend* leg0 = new TLegend(.65, .75, 0.85, .9);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(18);
    leg0->SetTextFont(43);
    leg0->AddEntry(NEUT_bindEvsk_mode1,modelname[0],"f");
    leg0->AddEntry(NEUT_bindEvsk_mode1_2,modelname[1],"f");
    leg0->Draw("same");
    l1->Draw();
    
    gPad->Print(Form("plots/%s_bindEvsk_%svs%s_ccqe.eps",neutversion_s.Data(),modelname[0],modelname[1]));

    //for SF
    new TCanvas;
    NEUT_bindEvsk_mode1_3->GetXaxis()->SetRangeUser(0,0.5);
    NEUT_bindEvsk_mode1_3->GetYaxis()->SetRangeUser(0,0.2);
    NEUT_bindEvsk_mode1_3->GetXaxis()->SetTitle("Momentum of incoming nucleon (GeV)");
    NEUT_bindEvsk_mode1_3->GetYaxis()->SetTitle("Binding Energy (GeV)");
    NEUT_bindEvsk_mode1_3->SetTitle("");
    titleStyle(NEUT_bindEvsk_mode1_3);
    ci = TColor::GetColor("#D55E00");
    NEUT_bindEvsk_mode1_3->SetFillColor(ci);
    NEUT_bindEvsk_mode1_3->Draw("lego1 0");
    NEUT_bindEvsk_mode1_3->GetYaxis()->SetTitleOffset(1.8);
    TLegend* leg0 = new TLegend(.65, .75, 0.85, .9);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(18);
    leg0->SetTextFont(43);
    leg0->AddEntry(NEUT_bindEvsk_mode1_3,modelname[2],"f");
    leg0->Draw("same");
    l1->Draw();
    gPad->Print(Form("plots/%s_bindEvsk_%s_ccqe.eps",neutversion_s.Data(),modelname[2]));
    
}
