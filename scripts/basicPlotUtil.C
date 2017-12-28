#include "TMath.h"
void titleStyle(TH1* h1){
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->CenterTitle();
    h1->GetXaxis()->SetLabelSize(h1->GetXaxis()->GetTitleSize()*1.2);
    h1->GetYaxis()->SetLabelSize(h1->GetYaxis()->GetTitleSize()*1.2);
    h1->GetXaxis()->SetTitleSize(h1->GetXaxis()->GetLabelSize()*1.2);
    h1->GetYaxis()->SetTitleSize(h1->GetYaxis()->GetLabelSize()*1.2);
    h1->GetYaxis()->SetTitleOffset(1.1);
}
void plot2hist(TH1* h1, TString leg1, TH1* h2, TString leg2, TString savename="", Float_t xlegmin=0.4, Float_t ylegmin=0.4 ){
    new TCanvas;
    gStyle->SetOptStat(0);

    titleStyle(h1);
    Int_t ci;
    ci = TColor::GetColor("#0072B2");
    h1->SetLineColor(ci);
    h1->SetFillColor(ci);
    h1->SetFillStyle(1001);
    h1->SetLineWidth(3);

    double maxY = TMath::Max(h1->GetMaximum(),h2->GetMaximum());
    //h1->SetMaximum(maxY *1.2);
    h1->GetYaxis()->SetRangeUser(0, maxY*1.3);
	h1->DrawCopy("hist");


    ci = TColor::GetColor("#D55E00");
    h2->SetLineColor(ci);
    h2->SetFillColor(ci);
    h2->SetFillStyle(3554);
    h2->SetLineWidth(3);
    h2->DrawCopy("histsames");

    TLegend* leg = new TLegend(xlegmin,ylegmin,xlegmin+0.3,ylegmin+0.25);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.045);
    leg->AddEntry(h1, leg1);
    leg->AddEntry(h2, leg2);
    leg->Draw();

    gPad->Print("plots/"+savename+".eps");

}

void plot3hist(TH1* h1, TString leg1, TH1* h2, TString leg2, TH1* h3, TString leg3, TString savename="", Float_t xlegmin=0.4, Float_t ylegmin=0.4 ){
    new TCanvas;
    gStyle->SetOptStat(0);

    titleStyle(h1);
    Int_t ci;
    ci = TColor::GetColor("#0072B2");
    h1->SetLineColor(ci);
    h1->SetFillColor(ci);
    h1->SetFillStyle(1001);
    h1->SetLineWidth(3);

    double maxY = TMath::Max(h1->GetMaximum(),h2->GetMaximum());
    maxY = TMath::Max(maxY,h3->GetMaximum());
    h1->GetYaxis()->SetRangeUser(0,maxY*1.3);
	h1->DrawCopy("hist");


    ci = TColor::GetColor("#D55E00");
    h2->SetLineColor(ci);
    h2->SetFillColor(ci);
    h2->SetFillStyle(3554);
    h2->SetLineWidth(3);
    h2->DrawCopy("histsames");

    ci = TColor::GetColor("#000000");
    h3->SetLineColor(ci);
    //h3->SetFillColor(ci);
    //h3->SetFillStyle(3554);
    h3->SetLineWidth(3);
    h3->DrawCopy("histsames");

    TLegend* leg = new TLegend(xlegmin,ylegmin,xlegmin+0.3,ylegmin+0.25);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.045);
    leg->AddEntry(h1, leg1);
    leg->AddEntry(h2, leg2);
    leg->AddEntry(h3, leg3);
    leg->Draw();

    gPad->Print("plots/"+savename+".eps");

}

void plot2hist_stat(TH1* h1, TString leg1, TH1* h2, TString leg2, TString tagname="", TString savename="", Bool_t isAreaNormalization ){
    new TCanvas;
    gStyle->SetOptStat(1111);

    titleStyle(h1);
    Int_t ci;
    ci = TColor::GetColor("#0072B2");
    h1->SetLineColor(ci);
    h1->SetLineWidth(3);
    h1->Sumw2();
    h2->Sumw2();
    if(isAreaNormalization==true){
        h1->GetYaxis()->SetTitle("Area normalization");
        h1->Scale(1./h1->Integral());
        h2->Scale(1./h2->Integral());
    }
    else h1->GetYaxis()->SetTitle("Number of Events");
    h1->Sumw2();
    h2->Sumw2();
    double maxY = TMath::Max(h1->GetMaximum(),h2->GetMaximum());
    h1->GetYaxis()->SetRangeUser(0, maxY*1.6);
    h1->SetName(leg1);
    h1->Draw("hist");

    ci = TColor::GetColor("#D55E00");
    h2->SetLineColor(ci);
    h2->SetMarkerColor(ci);
    h2->SetLineWidth(3);
    h2->SetName(leg2);

    h2->Draw("hist sames");

    gPad->Update();
    TPaveStats *st1 = (TPaveStats*)h1->GetListOfFunctions()->FindObject("stats");
    st1->SetX1NDC(0.65);
    st1->SetX2NDC(0.85);
    ci = TColor::GetColor("#0072B2");
    st1->SetTextColor(ci);


    TPaveStats *st = (TPaveStats*)h2->GetListOfFunctions()->FindObject("stats");
    st->SetX1NDC(0.2);
    st->SetX2NDC(0.4);
    ci = TColor::GetColor("#D55E00");
    st->SetTextColor(ci);

    double ypos = 0.05;
    double xpos =0.09;
    TLatex *   text2kpre = new TLatex(xpos,ypos,tagname);
    text2kpre->SetTextAlign(11);
    text2kpre->SetNDC(kTRUE);
    ci = TColor::GetColor("#000000");
    text2kpre->SetTextColor(ci);
    text2kpre->SetTextFont(43);
    text2kpre->SetTextSize(24);
    text2kpre->SetLineWidth(3);
    text2kpre->Draw();

    gPad->Update();
    if(isAreaNormalization) {
        gPad->Print("plots/"+savename+"_areanom.eps");
        gPad->Print("plots/"+savename+"_areanom.C");
    }
    else {
        gPad->Print("plots/"+savename+".eps");
        gPad->Print("plots/"+savename+".C");
    }

}

 void plot3hist_stat(TH1* h1, TString leg1, TH1* h2, TString leg2, TH1* h3, TString leg3, TString tagname="", TString savename="", Bool_t isAreaNormalization ){
        new TCanvas;
        gStyle->SetOptStat(1111);
        
        titleStyle(h1);
        Int_t ci;
        ci = TColor::GetColor("#0072B2");
        h1->SetLineColor(ci);
        h1->SetLineWidth(3);
        h1->Sumw2();
        h2->Sumw2();
        h3->Sumw2();
        if(isAreaNormalization==true){
            h1->GetYaxis()->SetTitle("Area normalization");
            h1->Scale(1./h1->Integral());
            h2->Scale(1./h2->Integral());
            h3->Scale(1./h3->Integral());
        }
        else h1->GetYaxis()->SetTitle("Number of Events");
        h1->Sumw2();
        h2->Sumw2();
        double maxY = TMath::Max(h1->GetMaximum(),h2->GetMaximum());
        maxY = TMath::Max(maxY,h3->GetMaximum());
        h1->GetYaxis()->SetRangeUser(0, maxY*1.6);
        h1->SetName(leg1);
        h1->Draw("hist");
        
        ci = TColor::GetColor("#D55E00");
        h2->SetLineColor(ci);
        h2->SetMarkerColor(ci);
        h2->SetLineWidth(3);
        h2->SetName(leg2);
        
        h2->Draw("hist sames");
        
        ci = TColor::GetColor("#000000");
        h3->SetLineColor(ci);
        h3->SetMarkerColor(ci);
        h3->SetLineWidth(3);
        h3->SetName(leg3);
        
        h3->Draw("hist sames");
        
        gPad->Update();
        TPaveStats *st1 = (TPaveStats*)h1->GetListOfFunctions()->FindObject("stats");
        st1->SetX1NDC(0.65);
        st1->SetX2NDC(0.85);
        ci = TColor::GetColor("#0072B2");
        st1->SetTextColor(ci);
        
        
        TPaveStats *st = (TPaveStats*)h2->GetListOfFunctions()->FindObject("stats");
        st->SetX1NDC(0.42);
        st->SetX2NDC(0.62);
        ci = TColor::GetColor("#D55E00");
        st->SetTextColor(ci);
        
        TPaveStats *st2 = (TPaveStats*)h3->GetListOfFunctions()->FindObject("stats");
        st2->SetX1NDC(0.2);
        st2->SetX2NDC(0.4);
        ci = TColor::GetColor("#000000");
        st2->SetTextColor(ci);
        
        double ypos = 0.05;
        double xpos =0.09;
        TLatex *   text2kpre = new TLatex(xpos,ypos,tagname);
        text2kpre->SetTextAlign(11);
        text2kpre->SetNDC(kTRUE);
        ci = TColor::GetColor("#000000");
        text2kpre->SetTextColor(ci);
        text2kpre->SetTextFont(43);
        text2kpre->SetTextSize(24);
        text2kpre->SetLineWidth(3);
        text2kpre->Draw();
        
        gPad->Update();
        if(isAreaNormalization) {
            gPad->Print("plots/"+savename+"_areanom.eps");
            gPad->Print("plots/"+savename+"_areanom.C");
        }
        else {
            gPad->Print("plots/"+savename+".eps");
            gPad->Print("plots/"+savename+".C");
        }
        
    }

