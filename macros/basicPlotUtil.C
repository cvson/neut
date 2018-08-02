void titleStyle(TH1* h1){
    h1->SetTitle("");
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->CenterTitle();
    h1->GetXaxis()->SetLabelSize(h1->GetXaxis()->GetTitleSize()*1.2);
    h1->GetYaxis()->SetLabelSize(h1->GetYaxis()->GetTitleSize()*1.2);
    h1->GetXaxis()->SetTitleSize(h1->GetXaxis()->GetLabelSize()*1.2);
    h1->GetYaxis()->SetTitleSize(h1->GetYaxis()->GetLabelSize()*1.2);
    h1->GetYaxis()->SetTitleOffset(0.9);
}
void titleStyle(THStack* h1){
    h1->SetTitle("");
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->CenterTitle();
    h1->GetXaxis()->SetLabelSize(h1->GetXaxis()->GetTitleSize()*1.2);
    h1->GetYaxis()->SetLabelSize(h1->GetYaxis()->GetTitleSize()*1.2);
    h1->GetXaxis()->SetTitleSize(h1->GetXaxis()->GetLabelSize()*1.2);
    h1->GetYaxis()->SetTitleSize(h1->GetYaxis()->GetLabelSize()*1.2);
    h1->GetYaxis()->SetTitleOffset(0.9);
}

void titleStyle(TGraph* h1){
    h1->SetTitle("");
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->CenterTitle();
    h1->GetXaxis()->SetLabelSize(h1->GetXaxis()->GetTitleSize()*1.4);
    h1->GetYaxis()->SetLabelSize(h1->GetYaxis()->GetTitleSize()*1.4);
    h1->GetXaxis()->SetTitleSize(h1->GetXaxis()->GetLabelSize()*1.2);
    h1->GetYaxis()->SetTitleSize(h1->GetYaxis()->GetLabelSize()*1.2);
    h1->GetYaxis()->SetTitleOffset(0.9);
}
void titleStyle(TGraphErrors* h1){
    h1->SetTitle("");
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->CenterTitle();
    h1->GetXaxis()->SetLabelSize(h1->GetXaxis()->GetTitleSize()*1.4);
    h1->GetYaxis()->SetLabelSize(h1->GetYaxis()->GetTitleSize()*1.4);
    h1->GetXaxis()->SetTitleSize(h1->GetXaxis()->GetLabelSize()*1.2);
    h1->GetYaxis()->SetTitleSize(h1->GetYaxis()->GetLabelSize()*1.2);
    h1->GetYaxis()->SetTitleOffset(0.9);
}
void titleStyle2D(TH2* h1){
    h1->SetTitle("");
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->CenterTitle();
    h1->GetXaxis()->SetLabelSize(h1->GetXaxis()->GetTitleSize()*1.4);
    h1->GetYaxis()->SetLabelSize(h1->GetYaxis()->GetTitleSize()*1.4);
    h1->GetXaxis()->SetTitleSize(h1->GetXaxis()->GetLabelSize()*1.2);
    h1->GetYaxis()->SetTitleSize(h1->GetYaxis()->GetLabelSize()*1.2);
    h1->GetYaxis()->SetTitleOffset(0.9);
}
void titleStyle2x(TH1* h1){
    h1->SetTitle("");
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->CenterTitle();
    h1->GetXaxis()->SetLabelSize(h1->GetXaxis()->GetLabelSize()*5);
    h1->GetYaxis()->SetLabelSize(h1->GetYaxis()->GetLabelSize()*5);
    h1->GetXaxis()->SetTitleSize(h1->GetXaxis()->GetTitleSize()*5);
    h1->GetYaxis()->SetTitleSize(h1->GetYaxis()->GetTitleSize()*5);
    h1->GetYaxis()->SetTitleOffset(0.25);
    h1->GetXaxis()->SetTitleOffset(0.9);
    h1->GetXaxis()->SetTickSize(0.1);
}
void plotmultiTH1(Int_t nhist, TH1** phist, TString savename){
    new TCanvas;
    phist[0]->Draw();
    for (Int_t ihist=1; ihist<nhist; ++nhist) {
        phist[ihist]->Draw("same");
    }
    gPad->Print("plots/"+savename+".eps");
}
///////////TGraph/////////////////
void plot2graph(TGraph* h1, TString leg1,TGraph* h2, TString leg2, TString savename, Float_t xlegmin=0.4, Float_t ylegmin=0.4 ){
    new TCanvas;
    gStyle->SetOptStat(0);
    gStyle->SetLineWidth(2);
    h1->SetLineWidth(3);
    h2->SetLineWidth(3);
    h1->SetMarkerSize(0.8);
    h2->SetMarkerSize(0.8);
    Int_t ci;
    ci = TColor::GetColor("#0B3861");
    h1->SetLineColor(ci);
    h1->SetMarkerColor(ci);
    
    //UT orange
    ci = TColor::GetColor("#B45F04");
    h2->SetLineColor(ci);
    h2->SetMarkerColor(ci);
    titleStyle(h1);
    h1->Draw("AL*");
    h2->SetMarkerStyle(21);
    h2->Draw("LP same");
    
    TLegend* leg = new TLegend(xlegmin,ylegmin,xlegmin+0.3,ylegmin+0.25);
    leg->SetFillStyle(0);
	leg->SetBorderSize(0);
    leg->SetTextSize(0.06);
    leg->AddEntry(h1, leg1,"lp");
    leg->AddEntry(h2, leg2,"lp");
    leg->Draw();

    
    gPad->Print("plots/"+savename+".eps");
    //gPad->Print("plots/"+savename+".png");
}
///////////TH1////////////////////
void simpleFit(TH1* h1,TString savename="", Bool_t isFitInclude=true, Bool_t isPeakInclude=false, Float_t xmin, Float_t xmax){
    new TCanvas;
    //gStyle->SetOptStat(0);
    gStyle->SetLineWidth(2);
    TGaxis::SetMaxDigits(3);
    titleStyle(h1);
    Int_t ci;
    ci = TColor::GetColor("#0B3861");
    h1->SetTitle("");
    h1->SetLineColor(ci);
    h1->SetLineWidth(3);
    if(h1->GetMinimum()>=0) h1->GetYaxis()->SetRangeUser(0,h1->GetMaximum()*1.2);
    
    else h1->GetYaxis()->SetRangeUser(h1->GetMinimum()*1.2,h1->GetMaximum()*1.2);
    h1->GetXaxis()->SetRangeUser(xmin,xmax);
    h1->Draw();
    if(isFitInclude){
        h1->Fit("gaus");
        TF1 *g = h1->GetFunction("gaus");
        ci = TColor::GetColor("#B45F04");
        g->SetLineColor(ci);
        g->SetLineWidth(3);
        g->Draw("same");
    }
    if (isPeakInclude) {
        //Use TSpectrum to find the peak candidates
        TSpectrum *s = new TSpectrum(2);//maximum peak
        Int_t nfound = s->Search(h1,1,"new");
        Float_t *xpeaks = s->GetPositionX();
        Float_t xp = xpeaks[0];
        TString peakLtex = Form("Peak at %.4g",xp);
        TLatex *tex = new TLatex(0.6,0.5,peakLtex);
        //UT orange
        ci = TColor::GetColor("#B45F04");
        tex->SetTextColor(ci);
        tex->SetTextAlign(1);
        tex->SetNDC();
        tex->SetTextFont(43);
        tex->SetTextSize(31);
        tex->SetLineWidth(2);
        tex->Draw();
        gPad->Update();
    }
    gPad->Print("plots/"+savename+".eps");
    //gPad->Print("plots/"+savename+".png");
}

void plot1hist(TH1* h1,TString savename=""){
    new TCanvas;
    gStyle->SetLineWidth(2);
    TGaxis::SetMaxDigits(3);
    titleStyle(h1);
    Int_t ci;
    ci = TColor::GetColor("#0B3861");
    h1->SetTitle("");
    h1->SetLineColor(ci);
    h1->SetLineWidth(3);
    if(h1->GetMinimum()>=0) h1->GetYaxis()->SetRangeUser(0,h1->GetMaximum()*1.2);
    
    else h1->GetYaxis()->SetRangeUser(h1->GetMinimum()*1.2,h1->GetMaximum()*1.2);
    h1->Draw();
    gPad->Print("plots/"+savename+".eps");
    //gPad->Print("plots/"+savename+".png");
}

void plot1hist_stat(TH1* h1,TString savename="",Bool_t isNeedTitleSetup){
    new TCanvas;
    gStyle->SetOptStat(1111);
    gStyle->SetLineWidth(2);
    TGaxis::SetMaxDigits(3);
    if (isNeedTitleSetup) titleStyle(h1);
    Int_t ci;
    ci = TColor::GetColor("#0B3861");
    //h1->SetTitle("");
    h1->SetLineColor(ci);
    h1->SetLineWidth(3);
    if(h1->GetMinimum()>=0) h1->GetYaxis()->SetRangeUser(0,h1->GetMaximum()*1.2);
    
    else h1->GetYaxis()->SetRangeUser(h1->GetMinimum()*1.2,h1->GetMaximum()*1.2);
    h1->Draw();
    
    gPad->Update();
    TPaveStats *st1 = (TPaveStats*)h1->GetListOfFunctions()->FindObject("stats");
    st1->SetX1NDC(0.65);
    st1->SetX2NDC(0.85);
    st1->SetY1NDC(0.65);
    st1->SetY2NDC(0.85);
    //navy blue
    ci = TColor::GetColor("#0B3861");
    st1->SetTextColor(ci);
    
    gPad->Print("plots/"+savename+".eps");
    //gPad->Print("plots/"+savename+".png");
}

///////////TH1////////////////////
void muonFrequency(TH1* h1,TString savename="", Float_t xmin, Float_t xmax){
    new TCanvas;
    gStyle->SetOptStat(0);
    gStyle->SetLineWidth(2);
    TGaxis::SetMaxDigits(3);
    titleStyle(h1);
    Int_t ci;
    ci = TColor::GetColor("#0B3861");
    h1->SetTitle("");
    h1->SetLineColor(ci);
    h1->SetLineWidth(3);
    if(h1->GetMinimum()>=0) h1->GetYaxis()->SetRangeUser(0,h1->GetMaximum()*1.2);
    
    else h1->GetYaxis()->SetRangeUser(h1->GetMinimum()*1.2,h1->GetMaximum()*1.2);
    h1->GetXaxis()->SetRangeUser(xmin,xmax);
    h1->Draw();
    TLine *meanFreq = new TLine(xmin,0.038,xmax,0.038);
    // UT orange
    ci = TColor::GetColor("#B45F04");
    meanFreq->SetLineColor(ci);
    meanFreq->SetLineWidth(3);
    meanFreq->Draw();
    
    
    gPad->Print("plots/"+savename+".eps");
    //gPad->Print("plots/"+savename+".png");
}
//
void ratio2TH1(TH1* h1, TH1* h2, TString savename="", Float_t xmin, Float_t xmax){
    TH1* hratio = (TH1*)h1->Clone("hratio");
    for (int ibin=0; ibin<hratio->GetXaxis()->GetNbins(); ibin++) {
        float numerator = h1->GetBinContent(ibin);
        float denominator = h2->GetBinContent(ibin);
        float result =0;
        if (denominator!=0) {
            result = numerator/denominator;
            hratio->SetBinContent(ibin,result);
        }
        else hratio->SetBinContent(ibin,result);
    }
    
    new TCanvas;
    gStyle->SetOptStat(0);
    gStyle->SetLineWidth(2);
    TGaxis::SetMaxDigits(3);
    titleStyle(hratio);
    Int_t ci;
    ci = TColor::GetColor("#0B3861");
    hratio->SetTitle("");
    hratio->SetLineColor(ci);
    hratio->SetLineWidth(3);
    hratio->Draw();
    /*if(hratio->GetMinimum()>=0) hratio->GetYaxis()->SetRangeUser(0,hratio->GetMaximum()*1.2);
    
    else hratio->GetYaxis()->SetRangeUser(hratio->GetMinimum()*1.2,hratio->GetMaximum()*1.2);*/
    hratio->GetYaxis()->SetRangeUser(0,10);
    hratio->GetXaxis()->SetRangeUser(xmin,xmax);
    hratio->Draw();

    gPad->Print("plots/"+savename+".eps");
    //gPad->Print("plots/"+savename+".png");
}

//plot three plots with different legend
void plot2hist(TH1* h1, TString leg1, TH1* h2, TString leg2, TString savename="", Float_t xlegmin=0.4, Float_t ylegmin=0.4 ){
    new TCanvas;
    gStyle->SetOptStat(0);
    
    titleStyle(h1);
    Int_t ci;
    //navy blue
    ci = TColor::GetColor("#0B3861");
    h1->SetLineColor(ci);
    h1->SetFillColor(32);
    h1->SetFillStyle(1001);
    h1->SetLineWidth(3);
    //area normalization
    //h1->Scale(1./h1->Integral());
     //h2->Scale(1./h2->Integral());
    
    double maxY = TMath::Max(h1->GetMaximum(),h2->GetMaximum());
    h1->GetYaxis()->SetRangeUser(0, maxY*1.2);
    h1->DrawCopy("hist");
    
    
    // UT orange
    ci = TColor::GetColor("#B45F04");
    h2->SetLineColor(ci);
    h2->SetFillColor(42);
    h2->SetFillStyle(3554);
    h2->SetLineWidth(3);
    h2->DrawCopy("histsames");
    //h1->DrawCopy("same");//newadd
    
    TLegend* leg = new TLegend(xlegmin,ylegmin,xlegmin+0.3,ylegmin+0.25);
    leg->SetFillStyle(0);
	leg->SetBorderSize(0);
    leg->SetTextSize(0.045);
    leg->AddEntry(h1, leg1);
    leg->AddEntry(h2, leg2);
    leg->Draw();
    
    gPad->Print("plots/"+savename+".eps");
    //gPad->Print("plots/"+savename+".png");
    
}
void plot2hist_stat(TH1* h1, TString leg1, TH1* h2, TString leg2, TString savename="" ){
    new TCanvas;
    gStyle->SetOptStat(1111);
    
    titleStyle(h1);
    Int_t ci;
    //navy blue
    ci = TColor::GetColor("#006633");
    h1->SetLineColor(ci);
    h1->SetLineWidth(3);
    //area normalization
    //h1->Scale(1./h1->Integral());
    //h2->Scale(1./h2->Integral());
    
    double maxY = TMath::Max(h1->GetMaximum(),h2->GetMaximum());
    h1->GetYaxis()->SetRangeUser(0, maxY*1.6);
    h1->SetName(leg1);
    h1->Draw();
    
    // UT orange
    ci = TColor::GetColor("#B45F04");
    h2->SetLineColor(ci);
    h2->SetLineWidth(3);
    h2->SetName(leg2);
    
    h2->Draw("sames");
    
    gPad->Update();
    TPaveStats *st1 = (TPaveStats*)h1->GetListOfFunctions()->FindObject("stats");
    st1->SetX1NDC(0.65);
    st1->SetX2NDC(0.85);
    //st1->SetY1NDC(0.65);
    //st1->SetY2NDC(0.85);
    //navy blue
    ci = TColor::GetColor("#006633");
    st1->SetTextColor(ci);
    

    TPaveStats *st = (TPaveStats*)h2->GetListOfFunctions()->FindObject("stats");
    st->SetX1NDC(0.2);
    st->SetX2NDC(0.4);
    // UT orange
    ci = TColor::GetColor("#B45F04");
    st->SetTextColor(ci);
    
    gPad->Update();
    
    //h1->DrawCopy("same");//newadd
    
    /*TLegend* leg = new TLegend(xlegmin,ylegmin,xlegmin+0.3,ylegmin+0.25);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.045);
    leg->AddEntry(h1, leg1,"l");
    leg->AddEntry(h2, leg2,"l");
    leg->Draw();*/
    
    gPad->Print("plots/"+savename+".eps");
    //gPad->Print("plots/"+savename+".png");
    
}

void plot2hist_2nd(TH1* h1, TString leg1, TH1* h2, TString leg2, TString savename="", Float_t xlegmin=0.4, Float_t ylegmin=0.4 ){
    new TCanvas;
    gStyle->SetOptStat(0);
    
    //titleStyle(h1);
    Int_t ci;
    //navy blue
    ci = TColor::GetColor("#006633");
    h1->SetLineColor(ci);
    h1->SetLineWidth(3);
    //area normalization
    //h1->Scale(1./h1->Integral());
    //h2->Scale(1./h2->Integral());
    
    double maxY = TMath::Max(h1->GetMaximum(),h2->GetMaximum());
    h1->GetYaxis()->SetRangeUser(0, maxY*1.2);
    h1->DrawCopy();
    
    
    // UT orange
    ci = TColor::GetColor("#B45F04");
    h2->SetLineColor(ci);
    h2->SetLineWidth(3);
    h2->DrawCopy("sames");
    //h1->DrawCopy("same");//newadd
    
    TLegend* leg = new TLegend(xlegmin,ylegmin,xlegmin+0.3,ylegmin+0.25);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.045);
    leg->AddEntry(h1, leg1,"l");
    leg->AddEntry(h2, leg2,"l");
    leg->Draw();
    
    gPad->Print("plots/"+savename+".eps");
    //gPad->Print("plots/"+savename+".png");
    
}
//plot three plots with different legend
void plot2histdata(TH1* h1, TString leg1, TH1* h2, TString leg2, TString savename="", Float_t xlegmin=0.4, Float_t ylegmin=0.4 ){
    new TCanvas;
    gStyle->SetOptStat(0);
    
    titleStyle(h1);
    Int_t ci;
    // UT orange
    ci = TColor::GetColor("#B45F04");
    
    h1->SetLineColor(ci);
    h1->SetLineWidth(3);
    double maxY = TMath::Max(h1->GetMaximum(),h2->GetMaximum());
    h1->GetYaxis()->SetRangeUser(0, maxY*1.2);
    h1->DrawCopy();
    
    
    //navy blue
    ci = TColor::GetColor("#0B3861");
    h2->SetLineColor(ci);
    h2->SetMarkerColor(ci);
    h2->SetMarkerStyle(8);
    h2->SetMarkerSize(1.);
    h2->SetLineWidth(3);
    //h2->Sumw2();
    h2->DrawCopy("same pe");
    
    TLegend* leg = new TLegend(xlegmin,ylegmin,xlegmin+0.3,ylegmin+0.25);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.045);
    leg->AddEntry(h1, leg1,"l");
    leg->AddEntry(h2, leg2,"l");
    leg->Draw();
    
    gPad->Print("plots/"+savename+".eps");
    //gPad->Print("plots/"+savename+".png");
    
}


//plot three plots with different legend
void plot3hist(Bool_t isAreaNormalization=false,TH1* h1, TString leg1, TH1* h2, TString leg2, TH1* h3, TString leg3, TString savename="", Float_t xlegmin=0.4, Float_t ylegmin=0.4 ){
    savename +=isAreaNormalization?"_areanom":"";
    new TCanvas;
    gStyle->SetOptStat(0);
    
    titleStyle(h1);
    if(isAreaNormalization){
        h1->Scale(1./h1->Integral());
        h2->Scale(1./h2->Integral());
        h3->Scale(1./h3->Integral());
        h1->GetYaxis()->SetTitle("Area Normalization");
    }
    h1->SetLineWidth(3);
    double maxY = TMath::Max(h1->GetMaximum(),h2->GetMaximum());
    maxY = TMath::Max(maxY,h3->GetMaximum());
    h1->GetYaxis()->SetRangeUser(0, maxY*1.2);
    h1->DrawCopy("hist");
    
    Int_t ci;
    //navy blue
    ci = TColor::GetColor("#006633");
    h2->SetLineColor(ci);
    h2->SetLineWidth(3);
    h2->DrawCopy("histsame");
    
    // UT orange
    ci = TColor::GetColor("#B45F04");
    h3->SetLineColor(ci);
    h3->SetLineWidth(3);
    h3->DrawCopy("histsame");
    
    TLegend* leg = new TLegend(xlegmin,ylegmin,xlegmin+0.3,ylegmin+0.25);
    leg->SetFillStyle(0);
	leg->SetBorderSize(0);
    leg->SetTextSize(0.045);
    leg->AddEntry(h1, leg1,"l");
    leg->AddEntry(h2, leg2,"l");
    leg->AddEntry(h3, leg3,"l");
    leg->Draw();
    
    gPad->Print("plots/"+savename+".eps");
    //gPad->Print("plots/"+savename+".png");
    
}
void plot3histStyle1(Bool_t isAreaNormalization=false,TH1* h1, TString leg1, TH1* h2, TString leg2, TH1* h3, TString leg3, TString savename="", Float_t xlegmin=0.4, Float_t ylegmin=0.4 ){
    savename +=isAreaNormalization?"_areanom":"";
    new TCanvas;
    gStyle->SetOptStat(0);
    
    titleStyle(h1);
    if(isAreaNormalization){
        h1->Scale(1./h1->Integral());
        h2->Scale(1./h2->Integral());
        h3->Scale(1./h3->Integral());
        h1->GetYaxis()->SetTitle("Area Normalization");
    }
    h1->SetLineWidth(3);
    double maxY = TMath::Max(h1->GetMaximum(),h2->GetMaximum());
    maxY = TMath::Max(maxY,h3->GetMaximum());
    h1->GetYaxis()->SetRangeUser(0, maxY*1.2);
    h1->SetFillColor(16);
    h1->DrawCopy("hist");
    
    Int_t ci;
    //navy blue
    ci = TColor::GetColor("#006633");
    h2->SetLineColor(ci);
    h2->SetFillStyle(0);
    h2->SetLineWidth(3);
    h2->DrawCopy("histsame");
    
    // UT orange
    ci = TColor::GetColor("#B45F04");
    h3->SetLineColor(ci);
    h3->SetFillStyle(0);
    h3->SetLineWidth(3);
    h3->DrawCopy("histsame");

    gPad->RedrawAxis();
    TLegend* leg = new TLegend(xlegmin,ylegmin,xlegmin+0.3,ylegmin+0.25);
    leg->SetFillStyle(0);
	leg->SetBorderSize(0);
    leg->SetTextSize(0.045);
    leg->AddEntry(h1, leg1);
    leg->AddEntry(h2, leg2,"l");
    leg->AddEntry(h3, leg3,"l");
    leg->Draw();
    
    gPad->Print("plots/"+savename+".eps");
    //gPad->Print("plots/"+savename+".png");
    
}


//Plot 2D plot with TProfile
void plot2d(TH2* h1,TString savename=""){
    new TCanvas;
    gStyle->SetOptStat(0);
    gStyle->SetLineWidth(2);
    TGaxis::SetMaxDigits(3);
    titleStyle2D(h1);
    //Int_t ci;
    //ci = TColor::GetColor("#0B3861");
    //h1->SetMarkerColor(ci);
    //h1->SetMarkerStyle(8);
    //h1->SetMarkerSize(0.3);
    h1->Draw();
    //gPad->Print("plots/"+savename+".png");
    gPad->Print("plots/"+savename+".eps");
}

void plot2dcolz(TH2* h1,TString savename=""){
    new TCanvas;
    gStyle->SetOptStat(0);
    gStyle->SetLineWidth(2);
    TGaxis::SetMaxDigits(3);
    titleStyle2D(h1);
    h1->Draw("colz");
    //gPad->Print("plots/"+savename+".png");
    gPad->Print("plots/"+savename+".eps");
}

void plot2dhist(TH2* h1, TString savename){
    new TCanvas;
    titleStyle2D(h1);
    h1->Draw("colz");
    TProfile *hprofile = (TProfile*)h1->ProfileX();
    hprofile->SetLineWidth(3);
    hprofile->SetLineColor(kRed);
    hprofile->Draw("same");
    gPad->Print("plots/"+savename+"2D.eps");
    //gPad->Print("plots/"+savename+"2D.png");
}

//Plot graph
void plotgrapherrors(TGraphErrors *h1, TString savename){
    new TCanvas;
    TGaxis::SetMaxDigits(3);
    titleStyle(h1);
    h1->SetMarkerColor(4);
    h1->SetMarkerStyle(21);
    h1->Draw("ALP");
    gPad->Print("plots/"+savename+".eps");
    //gPad->Print("plots/"+savename+".png");
    
}
//Plot graph
void plotgrapherrorsandfit(TGraphErrors *h1, TString savename){
    new TCanvas;
    TGaxis::SetMaxDigits(3);
    titleStyle(h1);
    h1->SetMarkerColor(4);
    h1->SetMarkerStyle(21);
    h1->Draw("ALP");
     //TF1 *ffit = new TF1("ffit", "[0]+[1]*(x*x+[2])*pow(sin(x*[3]),2)", 0.5, 6.5);
    TF1 *ffit = new TF1("ffit", "[0]+[1]*x+[2]*x*x+[3]*pow(x,3)+4*pow(x,4)", 0.5, 6.5);
    h1->Fit(ffit);
    ffit = h1->GetFunction("ffit");
    ffit->SetLineColor(kRed);
    ffit->SetLineWidth(3);
    cout<<"Maximum at "<<ffit->GetMaximumX()<<endl;
    ffit->Draw("same");
    gPad->Print("plots/"+savename+"_fit.eps");
    //gPad->Print("plots/"+savename+"_fit.png");
    
}
void plotComposition(TH1* hcccoh, TH1* hccqe, TH1* hccother, TH1* hnc, TH1* hbar, TH1* hwall, TH1* hingrid, TString savename)
{
    //check composition
    Float_t ncccoh = hcccoh->Integral();
    Float_t nccqe = hccqe->Integral();
    Float_t nccother = hccother->Integral();
    Float_t nnc = hnc->Integral();
    Float_t nbar = hbar->Integral();
    Float_t nwall = hwall->Integral();
    Float_t ningrid = hingrid->Integral();
    Float_t ntotal = ncccoh+ nccqe + nccother + nnc + nbar + nwall + ningrid;
    cout<<"ccoh "<<ncccoh<<" i.e "<<ncccoh*100./ntotal<<endl;
    cout<<"ccqe "<<nccqe<<" i.e "<<nccqe*100./ntotal<<endl;
    cout<<"ccother "<<nccother<<" i.e "<<nccother*100./ntotal<<endl;
    cout<<"nc "<<nnc<<" i.e "<<nnc*100./ntotal<<endl;
    cout<<"bar "<<nbar<<" i.e "<<nbar*100./ntotal<<endl;
    cout<<"wall "<<nwall<<" i.e "<<nwall*100./ntotal<<endl;
    cout<<"ingrid "<<ningrid<<" i.e "<<ningrid*100./ntotal<<endl;

    new TCanvas;
    TGaxis::SetMaxDigits(3);

    THStack* fHstach    = new THStack("fHstach","fHstach");
    TH1F *hbkg_all = (TH1F*)hwall->Clone();
    hbkg_all->Add(hingrid);
    hbkg_all->SetFillColor(12);
    hbkg_all->SetLineColor(12);
    fHstach->Add(hbkg_all);
    //hbar->SetFillStyle(3005);
    hbar->SetFillColor(22);
    hbar->SetLineColor(22);
    fHstach->Add(hbar);
    
    hnc->SetFillColor(31);
    hnc->SetLineColor(31);
    fHstach->Add(hnc);
    
    hccother->SetFillColor(41);
    hccother->SetFillStyle(3004);
    hccother->SetLineColor(41);
    hccother->SetMarkerSize(1.2);
    fHstach->Add(hccother);
    
    hccqe->SetFillColor(40);
    hccqe->SetLineColor(40);
    fHstach->Add(hccqe);
    
    //hcccoh->SetFillStyle(3002);
    hcccoh->SetFillColor(45);
    hcccoh->SetLineColor(45);
    fHstach->Add(hcccoh);

    //fHstach->GetYaxis()->CenterTitle();
    //fHstach->GetXaxis()->CenterTitle();
    //titleStyle(fHstach);
    fHstach->Draw();
    fHstach->GetXaxis()->SetTitle("True Neutrino Energy (GeV)");
    fHstach->GetYaxis()->SetTitle("Number of Events");
    fHstach->GetXaxis()->SetRangeUser(0,10);
    fHstach->SetMaximum(fHstach->GetMaximum()*1.2);
    titleStyle(fHstach);
    
    TLegend *pleg = new TLegend(0.5,0.5,0.75,0.8);
    pleg->SetFillStyle(0);
    pleg->SetBorderSize(0);
    pleg->SetTextFont(43);
    pleg->SetTextSize(23);
    //pleg->SetTextSize(0.04);
    pleg->AddEntry(hcccoh,"#nu_{#mu} CC coherent #pi","f");
    pleg->AddEntry(hccqe,"#nu_{#mu} CCQE","f");
    pleg->AddEntry(hccother,"#nu_{#mu} CC other","f");
    pleg->AddEntry(hnc,"#nu_{#mu} NC","f");
    pleg->AddEntry(hbar,"#bar{#nu}_{#mu} + #nu_{e}","f");
    pleg->AddEntry(hbkg_all,"B.G. from outside","f");
    pleg->Draw();
    

    gPad->Print("plots/"+savename+".eps");
    //gPad->Print("plots/"+savename+".png");
}

void plotcc1pedatavsmc(TH1* hdt, TH1* hcccoh, TH1* hccqe, TH1* hccother, TH1* hnc, TH1* hbar, TH1* hwall, TH1* hingrid, TString xtitle, TString savename,Float_t xmin, Float_t xmax, Float_t xlegshift=0.0, Float_t ylegshift=0.0)
{
    //scaling
    float npot = 6.04193507503274721e20;
    int   nmc  = 3950;
    float mcpotreweight = npot/(nmc*1e21);
    hcccoh->Scale(mcpotreweight);
    hccqe->Scale(mcpotreweight);
    hccother->Scale(mcpotreweight);
    hnc->Scale(mcpotreweight);
    hbar->Scale(mcpotreweight);
    hwall->Scale(mcpotreweight);
    hingrid->Scale(mcpotreweight);
    
    //check composition
    Float_t ndata = hdt->Integral();
    Float_t ncccoh = hcccoh->Integral();
    Float_t nccqe = hccqe->Integral();
    Float_t nccother = hccother->Integral();
    Float_t nnc = hnc->Integral();
    Float_t nbar = hbar->Integral();
    Float_t nwall = hwall->Integral();
    Float_t ningrid = hingrid->Integral();
    Float_t ntotal = ncccoh+ nccqe + nccother + nnc + nbar + nwall + ningrid;
    cout<<"data "<<ndata<<endl;
    cout<<"background "<<ntotal-ncccoh<<endl;
    cout<<"ccoh "<<ncccoh<<" i.e "<<ncccoh*100./ntotal<<endl;
    cout<<"ccqe "<<nccqe<<" i.e "<<nccqe*100./ntotal<<endl;
    cout<<"ccother "<<nccother<<" i.e "<<nccother*100./ntotal<<endl;
    cout<<"nc "<<nnc<<" i.e "<<nnc*100./ntotal<<endl;
    cout<<"bar "<<nbar<<" i.e "<<nbar*100./ntotal<<endl;
    cout<<"wall "<<nwall<<" i.e "<<nwall*100./ntotal<<endl;
    cout<<"ingrid "<<ningrid<<" i.e "<<ningrid*100./ntotal<<endl;
    //quick cross-section calculation
    Float_t mcxsecNEUT = 3.21553e-39;//cm^2/nucleus
    Float_t mcxsecGENIE = 1.37455e-39;//cm^2/nucleus
    Float_t xsec = (ndata-(ntotal-ncccoh))*mcxsecNEUT*1e39/ncccoh;
    Float_t xsecerr = sqrt(ndata)*mcxsecNEUT*1e39/ncccoh;
    cout<<"Crossection  "<<xsec<<"+/-"<<xsecerr<<"x 10^{-39}"<<endl;
    new TCanvas;
    TGaxis::SetMaxDigits(3);
    
    THStack* fHstach    = new THStack("fHstach","fHstach");
    TH1F *hbkg_all = (TH1F*)hwall->Clone();
    hbkg_all->Add(hingrid);
    hbkg_all->SetFillColor(12);
    hbkg_all->SetLineColor(12);
    fHstach->Add(hbkg_all);
    //hbar->SetFillStyle(3005);
    hbar->SetFillColor(22);
    hbar->SetLineColor(22);
    fHstach->Add(hbar);
    
    hnc->SetFillColor(31);
    hnc->SetLineColor(31);
    fHstach->Add(hnc);
    
    hccother->SetFillColor(41);
    hccother->SetFillStyle(3004);
    hccother->SetLineColor(41);
    hccother->SetMarkerSize(1.2);
    fHstach->Add(hccother);
    
    hccqe->SetFillColor(40);
    hccqe->SetLineColor(40);
    fHstach->Add(hccqe);
    
    //hcccoh->SetFillStyle(3002);
    hcccoh->SetFillColor(45);
    hcccoh->SetLineColor(45);
    fHstach->Add(hcccoh);
    
    //fHstach->GetYaxis()->CenterTitle();
    //fHstach->GetXaxis()->CenterTitle();
    //titleStyle(fHstach);
    fHstach->Draw();
    fHstach->GetXaxis()->SetTitle(xtitle);
    fHstach->GetYaxis()->SetTitle("Number of Events");
    fHstach->SetMaximum(fHstach->GetMaximum()*1.2);
    fHstach->GetXaxis()->SetRangeUser(xmin,xmax);
    titleStyle(fHstach);
    hdt->SetMarkerStyle(8);
    hdt->SetMarkerSize(1.2);
    hdt->SetLineWidth(2);
    hdt->Draw("e same");
    TLegend *pleg = new TLegend(0.5+xlegshift,0.5+ylegshift,0.75+xlegshift,0.85+ylegshift);
    pleg->SetFillStyle(0);
    pleg->SetBorderSize(0);
    pleg->SetTextFont(43);
    pleg->SetTextSize(23);
    //pleg->SetTextSize(0.04);
    pleg->AddEntry(hdt,"Data","lep");
    pleg->AddEntry(hcccoh,"#nu_{#mu} CC coherent #pi","f");
    pleg->AddEntry(hccqe,"#nu_{#mu} CCQE","f");
    pleg->AddEntry(hccother,"#nu_{#mu} CC other","f");
    pleg->AddEntry(hnc,"#nu_{#mu} NC","f");
    pleg->AddEntry(hbar,"#bar{#nu}_{#mu} + #nu_{e}","f");
    pleg->AddEntry(hbkg_all,"B.G. from outside","f");
    pleg->Draw();
    
    gPad->Print("plots/"+savename+".eps");
    //gPad->Print("plots/"+savename+".png");
    
    //make a ratio
    new TCanvas;
    TGaxis::SetMaxDigits(3);
    TH1F* hpredNoCoh = (TH1F*)hccqe->Clone("hpredNoCoh");
    hpredNoCoh->Add(hccother);
    hpredNoCoh->Add(hnc);
    hpredNoCoh->Add(hbar);
    hpredNoCoh->Add(hbkg_all);
    
    TH1F* hpredAll = (TH1F*)hpredNoCoh->Clone("hpredAll");
    hpredAll->Add(hcccoh);
    TH1F* hratio1 = (TH1F*)hdt->Clone("hratio1");
    hratio1->Sumw2();
    hratio1->Divide(hpredNoCoh);
    
    TH1F* hratio2 = (TH1F*)hdt->Clone("hratio2");
    hratio2->Sumw2();
    hratio2->Divide(hpredAll);
    
    for (Int_t ibin=1; ibin<=hratio1->GetXaxis()->GetNbins(); ibin++) {
        Float_t err1;
        if (hpredNoCoh->GetBinContent(ibin)!=0) {
            err1 = sqrt(hdt->GetBinContent(ibin))/hpredNoCoh->GetBinContent(ibin);
            hratio1->SetBinError(ibin,err1);
        }
        Float_t err2;
        if (hpredAll->GetBinContent(ibin)!=0) {
            err2 = sqrt(hdt->GetBinContent(ibin))/hpredAll->GetBinContent(ibin);
            hratio2->SetBinError(ibin,err2);

        }
    }
    hratio1->GetXaxis()->SetTitle(xtitle);
    hratio1->GetYaxis()->SetTitle("Data / Prediction");
    titleStyle(hratio1);
    hratio1->GetXaxis()->SetRangeUser(xmin,xmax);
    hratio1->GetYaxis()->SetRangeUser(0,3);
    //navy blue
    Int_t ci;
    ci = TColor::GetColor("#0B3861");
    hratio1->SetLineColor(ci);
    hratio1->SetMarkerColor(ci);
    
    // UT orange
    ci = TColor::GetColor("#B45F04");
    hratio2->SetLineColor(ci);
    hratio2->SetMarkerColor(ci);
    
    hratio1->Draw("ep");
    hratio2->Draw("ep same");
    TLine *plineone = new TLine(xmin,1,xmax,1);
    plineone->SetLineWidth(3);
    
    ci = TColor::GetColor("#333333");
    plineone->SetLineColor(ci);
    plineone->Draw();
    
    TLegend *pleg2 = new TLegend(0.45,0.75,0.7,0.9);
    pleg2->SetFillStyle(0);
    pleg2->SetBorderSize(0);
    pleg2->SetTextFont(43);
    pleg2->SetTextSize(23);
    pleg2->AddEntry(hratio1,"Data / All background","lep");
    pleg2->AddEntry(hratio2,"Data / Prediction","lep");
    pleg2->Draw();
    gPad->Print("plots/"+savename+"_ratio.eps");
    //gPad->Print("plots/"+savename+"_ratio.png");
}


void plotcc1pedatavsmc(TH1* hdt, TH1* hsignal, TH1* hbackground, TString savename)
{
    float npot = 6.04193507503274721e20;
    int   nmc  = 3950;
    float mcpotreweight = npot/(nmc*1e21);
    hsignal->Scale(mcpotreweight);
    hbackground->Scale(mcpotreweight);
    
    new TCanvas;
    TGaxis::SetMaxDigits(3);
    THStack* fHstach    = new THStack("fHstach","fHstach");
    
    hbackground->SetFillColor(41);
    hbackground->SetFillStyle(3004);
    hbackground->SetLineColor(41);
    hbackground->SetMarkerSize(1.2);
    fHstach->Add(hbackground);
    
    hsignal->SetFillColor(45);
    hsignal->SetLineColor(45);
    fHstach->Add(hsignal);
    
    fHstach->Draw();
    fHstach->GetXaxis()->SetTitle("CC 1 #pi coherent PID");
    fHstach->GetYaxis()->SetTitle("Number of Events");
    fHstach->SetMaximum(fHstach->GetMaximum()*1.2);
    fHstach->GetXaxis()->SetRangeUser(-1,0.3);
    titleStyle(fHstach);
    hdt->SetMarkerStyle(8);
    hdt->SetMarkerSize(1.1);
    hdt->SetLineWidth(2);
    hdt->Draw("e same");
    TLegend *pleg = new TLegend(0.2,0.5,0.4,0.85);
    pleg->SetFillStyle(0);
    pleg->SetBorderSize(0);
    pleg->SetTextFont(43);
    pleg->SetTextSize(23);
    //pleg->SetTextSize(0.04);
    pleg->AddEntry(hdt,"Data","lep");
    pleg->AddEntry(hsignal,"#nu_{#mu} CC coherent #pi","f");
    pleg->AddEntry(hbackground,"Background","f");
    pleg->Draw();
    
    
    gPad->Print("plots/"+savename+".eps");
    //gPad->Print("plots/"+savename+".png");
    
    fHstach->SetMinimum(1);
    gPad->SetLogy();
    gPad->Update();
    gPad->Print("plots/"+savename+"_log.eps");
    //gPad->Print("plots/"+savename+"_log.png");
    
    gPad->SetLogy(false);
    

    
}
