{
    gROOT->ProcessLine(".x /Users/soncao/rootlogon.C");
    gROOT->ProcessLine(".L /Users/soncao/basicPlotUtil.C");
    
    TString neutversion = "NEUT v5.4.0";
    TString neutversion_s = "neut540";
    const Int_t NMODEL2COMP = 2;
    TFile *pfile[NMODEL2COMP];

    /*pfile[0] = new TFile("basicplotsv8_neut540_card_5.3.6_nd5_C_GFGCCQE_ccqemec.root","READ");
    pfile[1] = new TFile("basicplotsv8_neut540_card_5.3.6_nd5_C_GFGCCQErpa_ccqemec.root","READ");
    char *model_name[NMODEL2COMP]={"RFG wo/ RPA\0", "RFG w/ RPA\0"};
    TString submodelname= "gfgrpa";*/
    
    
    pfile[0] = new TFile("basicplotsv8_neut540_card_5.3.6_nd5_C_1p1hCCQEnorpa_ccqemec.root","READ");
    pfile[1] = new TFile("basicplotsv8_neut540_card_5.3.6_nd5_C_1p1hCCQE_ccqemec.root","READ");
    char *model_name[NMODEL2COMP]={"Nieve 1p1h wo/ RPA\0", "Nieve 1p1h w/ RPA\0"};
    TString submodelname= "1p1hrpa";

   
    
    char flavor_str[6][16]={"nue\0"  ,"numu\0"    ,"nutau\0",
        "nue_bar" ,"numu_bar\0","nutau_bar\0"};
    char flavor_strlatex[6][30]={"#nu_e\0"  ,"#nu_{#mu}\0"    ,"#nu_{#tau}\0",
        "#bar{#nu}_e" ,"#bar{#nu}_{#mu}\0","#bar{#nu}_{#tau}\0"};
    
    char hist_kind[12][16]={"all\0"    ,"CCall\0"    ,"NCall\0",
        "CCQE\0"   ,"CCMEC\0"    ,"CC1pi\0",
        "CCDIS\0","CCCOH\0","CCtopo0pi\0","CCtopo1pi\0","CCtopoNpi\0"};
    
    char hist_type[27][16]={"enu\0"          ,"plep\0"       ,"in_nuc1_p\0",
        "in_nuc2_p\0"    ,"out_nuc1_p\0" ,"out_nuc2_p\0",
        "coslep\0"       ,"q2\0"         ,"in_nuc1_cosL\0",
        "in_nuc2_cosL\0","in_nuc1_phiL\0","in_nuc2_phiL\0",
        "out_nuc1_cosL\0","out_nuc2_cosL\0",
        "out_nuc1_phiL\0","out_nuc2_phiL\0",
        "rescat_nuc1_p\0",
        "in_nucs_open\0", "out_nucs_open\0",
        "intr_pos\0", "numode\0","npro\0","npi\0","tmom\0","wsq\0","recoE\0","enubias\0"
    };
    //to plots
    TH1D *h_1d_comp[NMODEL2COMP];
    int flavorindex = 1;//for numu beam
    int topoindex = 3;//CCQE
    //Q2
    int hist_index = 7;//Q2
    char *xtitle = "Q^{2} (GeV^{2})";
    char *ytitle = "Arbitrary unit";
     double xminrange = 0.;
    double xmaxrange = 2.0;//
    double xlegmin = 0.5;
    double ylegmin = 0.65;
    double ymaxscale = 1.5;
    
    /*int hist_index = 1;//muon momentum
    char *xtitle = "P_{#mu} (GeV)";
    char *ytitle = "Arbitrary unit";
     double xminrange = 0.;
    double xmaxrange = 2.0;//
    double xlegmin = 0.5;
    double ylegmin = 0.65;
    double ymaxscale = 1.2;*/
    
    /*int hist_index = 6;//muon momentum
    char *xtitle = "cos #theta_{#mu}";
    char *ytitle = "Arbitrary unit";
    double xminrange = -1;
    double xmaxrange = 1.;//
    double xlegmin = 0.5;
    double ylegmin = 0.65;
    double ymaxscale = 1.5;*/
    
    
    int       h_bins[27]={
        1200, 1200,  100,
        100,  500,  500,
        50,   1200,      50,
        50,     50,   50,
        50,     50  ,
        50,     50  ,
        500,
        50,     50  ,100,
        110,  10, 5,
        100,  100,    100,    100
    };
    
    Double_t  h_min[27] ={
        0.  ,  0.  ,  0.,
        0.  ,  0.  ,  0.,
        -1.  ,0.  , -1.,
        -1.  , -3.14, -3.14,
        -1.  , -1.  ,
        -3.14, -3.14,
        0.  , -1.  , -1.,
        0.,
        -55, 0,   0,
        0.,   0.,  0., -0.5
    };
    
    Double_t  h_max[27] ={
        30. , 30.  ,    1.,
        1.  ,  5.  ,    5.,
        1.,    30.  ,    1.,
        1.,    3.14,    3.14,
        1.,    1.  ,
        3.14,  3.14,
        5.,    1.  ,    1.,
        10.,
        55,   10, 5,
        0.5,  2.0,    2.0, 0.5
    };
    
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
    
    for ( int ifile = 0 ; ifile < NMODEL2COMP ; ifile++ ){//change to 11
        h_1d_comp[ifile] = (TH1D*)pfile[ifile]->Get(Form("h_%s_%s_%s",hist_kind[topoindex],hist_type[hist_index],flavor_str[flavorindex]));
        h_1d_comp[ifile]->SetLineWidth(2);
        ci = TColor::GetColor(colorcode[ifile]);
        h_1d_comp[ifile]->SetLineColor(ci);
    }
    
    TLegend* leg0 = new TLegend(xlegmin, ylegmin, xlegmin+0.15, ylegmin+0.2);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(18);
    leg0->SetTextFont(43);
    for (Int_t ifile=0; ifile<NMODEL2COMP; ++ifile) {
        leg0->AddEntry(h_1d_comp[ifile],model_name[ifile],"l");
    }
    
    //new TCanvas;
    TCanvas *c1 = new TCanvas("c1","c1");
    TPad*    upperPad = new TPad("upperPad", "upperPad",
                                 .005, .1725, .995, .995);
    TPad*    lowerPad = new TPad("lowerPad", "lowerPad",
                                 .005, .075, .995, .3375);
    
    TGaxis::SetMaxDigits(3);
    
    h_1d_comp[0]->GetXaxis()->SetTitle(xtitle);
    h_1d_comp[0]->GetYaxis()->SetTitle(ytitle);
    h_1d_comp[0]->SetTitle("");
    titleStyle(h_1d_comp[0]);
    h_1d_comp[0]->SetMaximum(h_1d_comp[0]->GetMaximum()*ymaxscale);
    h_1d_comp[0]->GetXaxis()->SetRangeUser(xminrange,xmaxrange);
    
    c1->cd();
    upperPad->Draw();
    lowerPad->Draw();
    upperPad->cd();
    //TPad *ppad = new TPad("ppad","",0,0,1,1);
    //ppad->Draw();
    //ppad->cd();
    h_1d_comp[0]->Draw("");
    for ( int ifile = 1 ; ifile < NMODEL2COMP ; ifile++ ){//change to 11
        h_1d_comp[ifile]->Draw("same");
    }
    
    TLatex *l1 = new TLatex(0.3, 0.98, Form("%s,%s %s",neutversion.Data(),flavor_strlatex[flavorindex],hist_kind[topoindex]));
    l1->SetNDC();
    l1->SetTextFont(43);
    l1->SetTextSize(20);
    l1->SetTextAlign(13);
    l1->Draw();
    leg0->Draw("same");
    
    TH1D *h_1d_comprat[NMODEL2COMP];
    for ( int ifile = 0 ; ifile < NMODEL2COMP ; ifile++ ){
        h_1d_comprat[ifile] = (TH1D*)h_1d_comp[ifile]->Clone(Form("hrat%d",ifile));
    }
    //make a ratio
    
    for (Int_t ibin=1; ibin<=h_1d_comprat[0]->GetXaxis()->GetNbins(); ibin++) {
        double nom = h_1d_comp[0]->GetBinContent(ibin);
        for ( int ifile = 0 ; ifile < NMODEL2COMP ; ifile++ ){
            double icontent = h_1d_comp[ifile]->GetBinContent(ibin);
            if (nom>1e-5) h_1d_comprat[ifile]->SetBinContent(ibin,icontent*1./nom);
            else h_1d_comprat[ifile]->SetBinContent(ibin,0);
        }
    }
    
    lowerPad->cd();
    lowerPad->SetBottomMargin(lowerPad->GetBottomMargin()*2.);
    h_1d_comprat[0]->GetYaxis()->SetTitle("RPA cor.");
    titleStyle2x(h_1d_comprat[0],3.5);
    h_1d_comprat[0]->Draw("hist");
    h_1d_comprat[0]->GetYaxis()->SetRangeUser(0.5,1.5);
    for ( int ifile = 1 ; ifile < NMODEL2COMP ; ifile++ ){
        h_1d_comprat[ifile]->Draw("hist same");
    }
    
    c1->Print(Form("plots/%s_%s_%s_%s_%s.eps",neutversion_s.Data(),flavor_str[flavorindex],hist_type[hist_index],hist_kind[topoindex],submodelname.Data()));
   
    
}
