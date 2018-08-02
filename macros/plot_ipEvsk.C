{
    gROOT->ProcessLine(".x /Users/soncao/rootlogon.C");
    gROOT->ProcessLine(".L /Users/soncao/basicPlotUtil.C");
    
    TString neutversion_s = "neut532";
    TString neutversion = "NEUT v5.3.2";//no different in neut_3.6
    
    TFile *pfile = new TFile("basicplotsov3_5.3.6_nd5_C_SFCCQE_v2_cc0pi.root","READ");
    TH2D *NEUT_incnulcEvsk_mode1 = (TH2D*)pfile->Get("NEUT_incnulcEvsk_mode1");
    TH2D *NEUT_incnulcEvsk_mode2 = (TH2D*)pfile->Get("NEUT_incnulcEvsk_mode2");
    
    TLatex *l1 = new TLatex(0.3, 0.98, Form("%s",neutversion.Data()));
    l1->SetNDC();
    l1->SetTextFont(43);
    l1->SetTextSize(20);
    l1->SetTextAlign(13);
    
    
    new TCanvas;
    NEUT_incnulcEvsk_mode1->GetXaxis()->SetRangeUser(0.8,1.5);
    NEUT_incnulcEvsk_mode1->GetYaxis()->SetRangeUser(0,1.2);
    NEUT_incnulcEvsk_mode1->GetYaxis()->SetTitle("Momentum of incoming nucleon (GeV)");
    NEUT_incnulcEvsk_mode1->GetXaxis()->SetTitle("Energy of incoming nucleon (GeV)");
    NEUT_incnulcEvsk_mode1->SetTitle("");
    titleStyle(NEUT_incnulcEvsk_mode1);
    NEUT_incnulcEvsk_mode1->Draw("colz");
    l1->Draw();
    gPad->Print(Form("plots/%s_NEUT_incnulcEvsk_ccqe.eps",neutversion_s.Data()));
    
    
    new TCanvas;
    NEUT_incnulcEvsk_mode2->GetXaxis()->SetRangeUser(0.8,1.5);
    NEUT_incnulcEvsk_mode2->GetYaxis()->SetRangeUser(0,1.2);
    NEUT_incnulcEvsk_mode2->GetYaxis()->SetTitle("Momentum of incoming nucleon (GeV)");
    NEUT_incnulcEvsk_mode2->GetXaxis()->SetTitle("Energy of incoming nucleon (GeV)");
    NEUT_incnulcEvsk_mode2->SetTitle("");
    titleStyle(NEUT_incnulcEvsk_mode2);
    NEUT_incnulcEvsk_mode2->Draw("colz");
    l1->Draw();
    gPad->Print(Form("plots/%s_NEUT_incnulcEvsk_2p2h.eps",neutversion_s.Data()));
    
}
