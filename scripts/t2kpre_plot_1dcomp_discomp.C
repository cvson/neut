{
    gROOT->ProcessLine(".x /Users/soncao/rootlogon.C");
    gROOT->ProcessLine(".L /Users/soncao/basicPlotUtil.C");
    
    TString neutversion = "NEUT v5.4.0";
    TString neutversion_s = "neut540";
    const Int_t NCHAN2COMP = 2;
    TFile *pfile;
    pfile = new TFile("basicplotsv7add_neut540_card_5.4.0_nd5_C_1p1hCCQE_default.root","READ");
    
    const int NFLAVOR = 6;
    const int NHIST1D = 34;
    const int NCHANNEL = 11;
    const int NHIST2D = 8;
    
    char *model_name[NCHAN2COMP]={"Low W multi #pi\0","DIS\0" };
    int flavorindex = 1;//for numu beam
    int topoindex[NCHAN2COMP] = {9,10};//DIS and multi pion
    
    
    
    
    char flavor_str[NFLAVOR][16]={"nue\0"  ,"numu\0"    ,"nutau\0",
        "nue_bar" ,"numu_bar\0","nutau_bar\0"};
    
    char flavor_strlatex[NFLAVOR][30]={"#nu_e\0"  ,"#nu_{#mu}\0"    ,"#nu_{#tau}\0",
        "#bar{#nu}_e" ,"#bar{#nu}_{#mu}\0","#bar{#nu}_{#tau}\0"};
    
    char hist_kind[NCHANNEL][16]={"all\0"    ,"CCall\0"    ,"NCall\0",
        "CCQE\0"   ,"CCMEC\0"    ,"CC1pi\0",
        "res11\0","res12\0","res13\0","dis21\0","dis26\0"};
    
    char hist_type[NHIST1D][16]={"enu\0"          ,"plep\0"       ,"in_nuc1_p\0",
        "in_nuc2_p\0"    ,"out_nuc1_p\0" ,"out_nuc2_p\0",
        "coslep\0"       ,"q2\0"         ,"in_nuc1_cosL\0",
        "in_nuc2_cosL\0","in_nuc1_phiL\0","in_nuc2_phiL\0",
        "out_nuc1_cosL\0","out_nuc2_cosL\0",
        "out_nuc1_phiL\0","out_nuc2_phiL\0",
        "rescat_nuc1_p\0",
        "in_nucs_open\0", "out_nucs_open\0",
        "intr_pos\0", "numode\0","npro\0","npi\0","tmom\0","wsq\0","recoE\0","enubias\0",
        "iniPiP\0","iniPicos\0","finPiP\0","finPicos\0","finPiPdiff\0","finPicosdiff\0","wres\0"
    };
    //to plots
    const int NVAR2PLOT = 5;
    TH1D *h_1d_comp[NCHAN2COMP][NVAR2PLOT];
    int hist_index[NVAR2PLOT];
    char* xtitle[NVAR2PLOT];
    double xminrange[NVAR2PLOT];
    double xmaxrange[NVAR2PLOT];
    double xlegmin[NVAR2PLOT];
    double ylegmin[NVAR2PLOT];
    double ymaxscale[NVAR2PLOT];
    
    char *ytitle = "Arbitrary unit";
    
    
    //no of pion
    
    hist_index[0] = 22;
    xtitle[0] = "No. of #pi";
    xminrange[0]= 0.;
    xmaxrange[0]= 7.;//
    xlegmin[0]= 0.55;
    ylegmin[0]= 0.65;
    ymaxscale[0]= 1.5;
    
    hist_index[1] = 7;//Q2
    xtitle[1]= "Q^{2} (GeV^{2})";
    xminrange[1]= 0.;
    xmaxrange[1]= 2.0;//
    xlegmin[1]= 0.55;
    ylegmin[1]= 0.65;
    ymaxscale[1]= 1.5;
    
    hist_index[2]= 1;//muon momentum
    xtitle[2]= "P_{#mu} (GeV)";
    xminrange[2]= 0.;
    xmaxrange[2]= 2.0;//
    xlegmin[2]= 0.55;
    ylegmin[2]= 0.65;
    ymaxscale[2]= 1.2;
    
    hist_index[3]= 6;//muon momentum
    xtitle[3]= "cos #theta_{#mu}";
    xminrange[3]= -1;
    xmaxrange[3]= 1.;//
    xlegmin[3]= 0.55;
    ylegmin[3]= 0.65;
    ymaxscale[3]= 1.5;
    
    hist_index[4]= 24;//Wsq
    xtitle[4]= "W^{2} (GeV^{2})";
    xminrange[4]= 1.;
    xmaxrange[4]= 4.;//
    xlegmin[4]= 0.55;
    ylegmin[4]= 0.65;
    ymaxscale[4]= 1.5;
    
    
    
    /*hist_index[5]= 33;//Wsq
    xtitle[5]= "Hadronic invariant mass W (GeV)";
    xminrange[5]= 1.;
    xmaxrange[5]= 2.;//
    xlegmin[5]= 0.55;
    ylegmin[5]= 0.65;
    ymaxscale[5]= 1.5;*/
    
  
    
    const char *colorcode[] = {
        "#000000",
        "#0072B2",
        "#D55E00",
        "#CC79A7",
        "#E69F00",
        "#009E73",
        "#56B4E9",
        "#F0E442"
    };
    Int_t ci;
    
    for ( int ichan = 0 ; ichan < NCHAN2COMP ; ichan++ ){//change to 11
        for ( int ivar = 0 ; ivar < NVAR2PLOT ; ivar++ ){
            h_1d_comp[ichan][ivar] = (TH1D*)pfile->Get(Form("h_%s_%s_%s",hist_kind[topoindex[ichan]],hist_type[hist_index[ivar]],flavor_str[flavorindex]));
            h_1d_comp[ichan][ivar]->SetLineWidth(2);
            ci = TColor::GetColor(colorcode[ichan]);
            h_1d_comp[ichan][ivar]->SetLineColor(ci);
        }
    }
    
    cout<<"finish get plots"<<endl;
    
    TLatex *l1 = new TLatex(0.3, 0.98, Form("%s,%s",neutversion.Data(),flavor_strlatex[flavorindex]));
    l1->SetNDC();
    l1->SetTextFont(43);
    l1->SetTextSize(20);
    l1->SetTextAlign(13);
    
    TH1D *h_1d_comprat[NCHAN2COMP][NVAR2PLOT];
    
    for ( int ivar = 0 ; ivar < NVAR2PLOT ; ivar++ ){
        //new TCanvas;
        TCanvas *c1 = new TCanvas("c1","c1");
        TPad*    upperPad = new TPad("upperPad", "upperPad",
                                     .005, .1725, .995, .995);
        TPad*    lowerPad = new TPad("lowerPad", "lowerPad",
                                     .005, .075, .995, .3375);
        
        TGaxis::SetMaxDigits(3);
        
        h_1d_comp[0][ivar]->GetXaxis()->SetTitle(TString(xtitle[ivar]));
        h_1d_comp[0][ivar]->GetYaxis()->SetTitle(ytitle);
        h_1d_comp[0][ivar]->SetTitle("");
        titleStyle(h_1d_comp[0][ivar]);
        h_1d_comp[0][ivar]->SetMaximum(h_1d_comp[0][ivar]->GetMaximum()*ymaxscale[ivar]);
        h_1d_comp[0][ivar]->GetXaxis()->SetRangeUser(xminrange[ivar],xmaxrange[ivar]);
        
        c1->cd();
        upperPad->Draw();
        lowerPad->Draw();
        upperPad->cd();
        //TPad *ppad = new TPad("ppad","",0,0,1,1);
        //ppad->Draw();
        //ppad->cd();
        h_1d_comp[0][ivar]->SetMinimum(0);
        h_1d_comp[0][ivar]->Draw("");
        for ( int ichan = 1 ; ichan < NCHAN2COMP ; ichan++ ){//change to 11
            h_1d_comp[ichan][ivar]->Draw("same");
        }
        
        
        l1->Draw();
        TLegend* leg0 = new TLegend(xlegmin[ivar], ylegmin[ivar], xlegmin[ivar]+0.15, ylegmin[ivar]+0.2);
        leg0->SetFillStyle(0);
        leg0->SetBorderSize(0);
        leg0->SetTextSize(18);
        leg0->SetTextFont(43);
        for (Int_t ichan=0; ichan<NCHAN2COMP; ++ichan) {
            leg0->AddEntry(h_1d_comp[ichan][ivar],model_name[ichan],"l");
        }
        leg0->Draw("same");
        
        
        for ( int ichan = 0 ; ichan < NCHAN2COMP ; ichan++ ){
            h_1d_comprat[ichan][ivar] = (TH1D*)h_1d_comp[ichan][ivar]->Clone(Form("hrat%d_var%d",ichan,ivar));
        }
        //make a ratio
        
        for (Int_t ibin=1; ibin<=h_1d_comprat[0][ivar]->GetXaxis()->GetNbins(); ibin++) {
            double nom = h_1d_comp[0][ivar]->GetBinContent(ibin);
            for ( int ichan = 0 ; ichan < NCHAN2COMP ; ichan++ ){
                double icontent = h_1d_comp[ichan][ivar]->GetBinContent(ibin);
                if (nom>1e-5) h_1d_comprat[ichan][ivar]->SetBinContent(ibin,icontent*1./nom);
                else h_1d_comprat[ichan][ivar]->SetBinContent(ibin,0);
            }
        }
        
        lowerPad->cd();
        lowerPad->SetBottomMargin(lowerPad->GetBottomMargin()*2.);
        h_1d_comprat[0][ivar]->GetYaxis()->SetTitle("MC/GS");
        titleStyle2x(h_1d_comprat[0][ivar],3.);
        h_1d_comprat[0][ivar]->Draw("hist");
        h_1d_comprat[0][ivar]->GetYaxis()->SetRangeUser(0,2);
        for ( int ichan = 1 ; ichan < NCHAN2COMP ; ichan++ ){
            h_1d_comprat[ichan][ivar]->Draw("hist same");
        }
        
        c1->Print(Form("plots/%s_%s_%s_dis_comp.eps",neutversion_s.Data(),flavor_str[flavorindex],hist_type[hist_index[ivar]]));
        
        delete leg0;
        delete c1;
        
    }
    
}
