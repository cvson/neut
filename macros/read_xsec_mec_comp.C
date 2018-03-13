//
//  read_xsec_mec_comp.C
////////////////////////////////////////////////////
//
//  To compute 2p2h/ccqe ration with different model: global fermi gas, local fermigas, spectral fuction, Nieve 1p1h
//
///////////////////////////////////////////////////

void read_xsec_mec_comp(){
    gROOT->ProcessLine(".x rootlogon.C");
    gROOT->ProcessLine(".L basicPlotUtil.C");
    const Int_t NMODE4COMP = 3;
    TFile *pfile[NMODE4COMP];
    pfile[0] = new TFile("test_neut540kek_1p1hccqe_default.root","READ");
    pfile[1] = new TFile("test_neut540kek_gfgccqe.root","READ");
    pfile[2] = new TFile("test_neut540kek_sfccqe.root","READ");
    TString neutversion_s = "neut540";
    TString neutversion = "NEUT v5.4.0";
    TString subname = "comp3modemec";
    
    char *modestr[NMODE4COMP]={"Nieve 1p1h","Relativistic FG", "Spectral Function"};
    
    const int NCHANNEL = 27;//from neut 5.3.2 npnh included
    TH1D *hxsec[NMODE4COMP][NCHANNEL];
    char *namechan[NCHANNEL]={"tot","ccqe","ccppip","ccppi0","ccnpip","cccoh","ccgam","ccmpi","cceta","cck","ccdis","ncnpi0","ncppi0","ncppim","ncnpip","nccoh","ncngam","ncpgam","ncmpi","ncneta","ncpeta","nck0","nckp","ncdis","ncqep","ncqen","npnh"};
    
     char *namechan_tex[NCHANNEL]={"Total","#nu_{l}+ n #rightarrow l^{-} + p","#nu_{l}+ p #rightarrow l^{-}+ p +#pi^{+}","#nu_{l}+ n #rightarrow l^{-}+ p+ #pi^{0}"," #nu_{l}+ n #rightarrow l^{-}+ n+ #pi^{+}","#nu_{l}+ ^{12}C #rightarrow l^{-}+ ^{12}C+ #pi^{+}","#nu_{l}+ n #rightarrow l^{-}+ p+ #gamma","#nu_{l}+ N #rightarrow l^{-}+ N'+ multi-#pi","#nu_{l}+ n #rightarrow l^{-}+ p+ #eta","#nu_{l}+ n #rightarrow l^{-}+ #Lambda+ K^{+}","nu_{l}+ N #rightarrow l^{-}+ N' +mesons","#nu_{l}+ n #rightarrow #nu_{l}+ n+ #pi^{0}","#nu_{l}+ p #rightarrow #nu_{l}+ p+ #pi^{0}","nu_{l}+ n #rightarrow #nu_{l}+ p+ #pi^{-}","nu_{l}+ p #rightarrow #nu_{l}+ n +#pi^{+}","#nu_{l}+ ^{12}C #rightarrow #nu_{l}+ ^{12}C+ #pi^{0}","#nu_{l}+ n #rightarrow #nu_{l}+ n+ #gamma","#nu_{l}+ p #rightarrow #nu_{l}+ p+ #gamma","#nu_{l}+ N #rightarrow #nu_{l}+ N+ multi-#pi","#nu_{l}+ n #rightarrow #nu_{l}+ n+ #eta","#nu_{l}+ p #rightarrow #nu_{l}+ p+ #eta","#nu_{l}+ n #rightarrow #nu_{l}+ #Lambda +K^{0}","#nu_{l}+ n #rightarrow #nu_{l}+ #Lambda+ K^{+}","#nu_{l}+ N #rightarrow #nu_{l}+ N'+ mesons","#nu_{l}+ p #rightarrow #nu_{l}+ p","#nu_{l}+ n #rightarrow #nu_{l}+ n","np-nh"};
    
    //color for histogram
    const char *colorcode[] = {
        "#000000",
        "#0072B2",
        "#D55E00",
        "#CC79A7",
        "#E69F00",
        "#009E73"
    };
    Int_t ci;
    
    for (Int_t imode=0; imode<NMODE4COMP; ++imode) {
        for (Int_t ichan=0; ichan<NCHANNEL; ++ichan) {
            hxsec[imode][ichan] = (TH1D*)pfile[imode]->Get(Form("neut_xsec_numu_%s",namechan[ichan]));
            cout<<"channel "<<ichan<<" inte "<<hxsec[imode][ichan]->Integral()<<endl;
            ci = TColor::GetColor(colorcode[imode]);
            hxsec[imode][ichan]->SetLineColor(ci);
            hxsec[imode][ichan]->SetLineWidth(2);
        }
    }
    
    //group by event topologies
    const int NCHAN4SHOW = 2;
    char *namechan4show[NCHAN4SHOW] = {"2p-2h/CCQE", "2p-2h/(2p-2h + CCQE)"};
    char *namechan4show_s[NCHAN4SHOW] = {"2p2hOccqe", "2p2hOcc0pi"};
    TH1D *hxsec4show[NMODE4COMP][NCHAN4SHOW];
    double rat1, rat2;
    for (Int_t imode=0; imode<NMODE4COMP; ++imode) {
        hxsec4show[imode][0] = (TH1D*)hxsec[imode][26]->Clone(Form("hrat1_mode%d",imode));
        hxsec4show[imode][1] = (TH1D*)hxsec[imode][26]->Clone(Form("hrat2_mode%d",imode));
        for (Int_t ibin=0; ibin<hxsec4show[imode][0]->GetNbinsX(); ++ibin) {
            if((hxsec[imode][1]->GetBinContent(ibin+1))!=0) rat1 = (hxsec[imode][26]->GetBinContent(ibin+1))/(hxsec[imode][1]->GetBinContent(ibin+1));
	    else rat1 =0;
            hxsec4show[imode][0]->SetBinContent(ibin+1,rat1*100);
            if((hxsec[imode][1]->GetBinContent(ibin+1) + hxsec[imode][26]->GetBinContent(ibin+1))!=0) rat2 = (hxsec[imode][26]->GetBinContent(ibin+1))/(hxsec[imode][1]->GetBinContent(ibin+1) + hxsec[imode][26]->GetBinContent(ibin+1));
		else rat2 =0;
            hxsec4show[imode][1]->SetBinContent(ibin+1,rat2*100);
	cout<<"mode "<<imode<<" rat "<<rat1 <<" rat2 "<<rat2<<endl;
        }
    }
    cout <<"Go to add color "<<endl;
    //color for the histogram
    for (Int_t imode=0; imode<NMODE4COMP; ++imode) {
        for (Int_t ichan=0; ichan<NCHAN4SHOW; ++ichan) {
            hxsec4show[imode][ichan]->SetLineWidth(2);//increase line widht, default is 1
            ci = TColor::GetColor(colorcode[imode]);
            hxsec4show[imode][ichan]->SetLineColor(ci);
        }
    }
    
    //to add legend to the plot
    TLegend* leg0 = new TLegend(.52, .3, 0.9, .5);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(18);
    leg0->SetTextFont(43);
    for (Int_t imode=0; imode<NMODE4COMP; ++imode) {
        leg0->AddEntry(hxsec4show[imode][0],modestr[imode],"l");
    }
    

    

    cout <<"Go to plots"<<endl;
    
    for (Int_t ichan=0; ichan<NCHAN4SHOW; ++ichan) {
        new TCanvas;
        gStyle->SetOptStat(0);
        hxsec4show[0][ichan]->GetXaxis()->SetRangeUser(0,5);//check from 0-5 GeV
        hxsec4show[0][ichan]->GetYaxis()->SetRangeUser(0,35);
        hxsec4show[0][ichan]->SetTitle("");
        if(ichan==0) hxsec4show[0][ichan]->GetYaxis()->SetTitle("#sigma(2p-2h)/#sigma(CCQE) [%]");
        else hxsec4show[0][ichan]->GetYaxis()->SetTitle("#sigma(2p-2h)/(#sigma(CCQE) + #sigma(2p-2h)) [%]");
        titleStyle(hxsec4show[0][ichan]);
        hxsec4show[0][ichan]->Draw("hist");
        for (Int_t imode=1; imode<NMODE4COMP; ++imode) {
            hxsec4show[imode][ichan]->Draw("hist same");
        }
        leg0->Draw();
        
        TLatex *l1 = new TLatex(0.3, 0.98, Form("%s, %s",neutversion.Data(),namechan4show[ichan]));
        l1->SetNDC();
        l1->SetTextFont(43);
        l1->SetTextSize(20);
        l1->SetTextAlign(13);
        l1->Draw();
        gPad->Print(Form("plots/%s_%s_%s.eps",neutversion_s.Data(),subname.Data(),namechan4show_s[ichan]));
        //gPad->Print(Form("test_%d.eps",ichan));
    }
    
    
    
    
    
}
