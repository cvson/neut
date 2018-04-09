{
    gROOT->ProcessLine(".x /Users/soncao/rootlogon.C");
    gROOT->ProcessLine(".L /Users/soncao/basicPlotUtil.C");
    
    TString neutversion = "NEUT v5.4.0";
    const Int_t NMODEL2COMP = 2;
    TFile *pfile[NMODEL2COMP];

     
     TString neutversion_s = "neut540";

    
    pfile[0] = new TFile("basicplotsv8_neut540_card_5.4.0_nd5_C_1p1hCCQE_default_pipos.root","READ");
    pfile[1] = new TFile("basicplotsv8_neut532_card_5.3.6_nd5_C_GFGCCQErpa_pipos.root","READ");
    
    const int NFLAVOR = 6;
    const int NHIST1D = 34;
    const int NCHANNEL = 11;//12?
    const int NHIST2D = 8;
    
    char *model_name[NMODEL2COMP]={"Incoherent" ,"Coherent"};
 
    
    
    
    char flavor_str[NFLAVOR][16]={"nue\0"  ,"numu\0"    ,"nutau\0",
        "nue_bar" ,"numu_bar\0","nutau_bar\0"};
    
    char flavor_strlatex[NFLAVOR][30]={"#nu_e\0"  ,"#nu_{#mu}\0"    ,"#nu_{#tau}\0",
        "#bar{#nu}_e" ,"#bar{#nu}_{#mu}\0","#bar{#nu}_{#tau}\0"};
    
    char hist_kind[NCHANNEL][16]={"all\0"    ,"CCall\0"    ,"NCall\0",
        "CCQE\0"   ,"CCMEC\0"    ,"CC1pi\0",
        "CCDIS\0","CCCOH\0","CCtopo0pi\0","CCtopo1pi\0","CCtopoNpi\0"};
    
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
    const int NVAR2PLOT = 9;
    TH1D *h_1d_comp[NMODEL2COMP][NVAR2PLOT];
    int hist_index[NVAR2PLOT];
    char* xtitle[NVAR2PLOT];
    double xminrange[NVAR2PLOT];
    double xmaxrange[NVAR2PLOT];
    double xlegmin[NVAR2PLOT];
    double ylegmin[NVAR2PLOT];
    double ymaxscale[NVAR2PLOT];
    
    char *ytitle = "Arbitrary unit";
    
    int flavorindex = 1;//for numu beam
    int topoindex = 9;//CC1pi topo
    int cohtopoindex = 7;//cccoh topo
    TH1D *hcoh_1d_comp[NMODEL2COMP][NVAR2PLOT];
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
    
    hist_index[5]= 27;//Wsq
    xtitle[5]= "Primary P_{#pi} (GeV)";
    xminrange[5]= 0.;
    xmaxrange[5]= 1.5;//
    xlegmin[5]= 0.55;
    ylegmin[5]= 0.65;
    ymaxscale[5]= 1.5;
    
    hist_index[6]= 28;//Wsq
    xtitle[6]= "Primary cos(#theta_{#pi})";
    xminrange[6]= -1.;
    xmaxrange[6]= 1.;//
    xlegmin[6]= 0.55;
    ylegmin[6]= 0.65;
    ymaxscale[6]= 1.5;
    
    hist_index[7]= 29;//Wsq
    xtitle[7]= "Final P_{#pi} (GeV)";
    xminrange[7]= 0.;
    xmaxrange[7]= 1.5;//
    xlegmin[7]= 0.55;
    ylegmin[7]= 0.65;
    ymaxscale[7]= 1.5;
    
    
    hist_index[8]= 30;//Wsq
    xtitle[8]= "Final cos(#theta_{#pi})";
    xminrange[8]= -1.;
    xmaxrange[8]= 1.;//
    xlegmin[8]= 0.55;
    ylegmin[8]= 0.65;
    ymaxscale[8]= 1.5;
    
   
    
  
    
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
        for ( int ivar = 0 ; ivar < NVAR2PLOT ; ivar++ ){
            h_1d_comp[ifile][ivar] = (TH1D*)pfile[ifile]->Get(Form("h_%s_%s_%s",hist_kind[topoindex],hist_type[hist_index[ivar]],flavor_str[flavorindex]));
            h_1d_comp[ifile][ivar]->SetLineWidth(2);
            ci = TColor::GetColor(colorcode[ifile]);
            h_1d_comp[ifile][ivar]->SetLineColor(ci);
            
            //take coherent
            hcoh_1d_comp[ifile][ivar] = (TH1D*)pfile[ifile]->Get(Form("h_%s_%s_%s",hist_kind[cohtopoindex],hist_type[hist_index[ivar]],flavor_str[flavorindex]));
            hcoh_1d_comp[ifile][ivar]->SetLineWidth(2);
            hcoh_1d_comp[ifile][ivar]->SetLineColor(ci);
            
        }
    }
    
   
    THStack* fHstach[NMODEL2COMP][NVAR2PLOT];
    for ( int ifile = 0 ; ifile < NMODEL2COMP ; ifile++ ){//change to 11
        for ( int ivar = 0 ; ivar < NVAR2PLOT ; ivar++ ){
            fHstach[ifile][ivar] = new THStack(Form("hstach_%d_%d",ifile,ivar),Form("hstach_%d_%d",ifile,ivar));
            h_1d_comp[ifile][ivar]->SetFillColor(10);
            fHstach[ifile][ivar]->Add(h_1d_comp[ifile][ivar]);
            hcoh_1d_comp[ifile][ivar]->SetFillColor(12);
            fHstach[ifile][ivar]->Add(hcoh_1d_comp[ifile][ivar]);
        }
    }
    cout <<"Finishing stach"<<endl;
    
    /*TLatex *l1 = new TLatex(0.3, 0.98, Form("%s,%s %s",neutversion.Data(),flavor_strlatex[flavorindex],hist_kind[topoindex]));*/
    TLatex *l1 = new TLatex(0.3, 0.98, Form("%s,%s %s",neutversion.Data(),flavor_strlatex[flavorindex],"CC1#pi^{+}"));
    l1->SetNDC();
    l1->SetTextFont(43);
    l1->SetTextSize(20);
    l1->SetTextAlign(13);
    
    TH1D *h_1d_comprat[NMODEL2COMP][NVAR2PLOT];
    
    for ( int ivar = 0 ; ivar < NVAR2PLOT ; ivar++ ){
        //new TCanvas;
        TCanvas *c1 = new TCanvas("c1","c1");
     
        TGaxis::SetMaxDigits(3);
        
        /*h_1d_comp[0][ivar]->GetXaxis()->SetTitle(TString(xtitle[ivar]));
        h_1d_comp[0][ivar]->GetYaxis()->SetTitle(ytitle);
        h_1d_comp[0][ivar]->SetTitle("");
        titleStyle(h_1d_comp[0][ivar]);
        h_1d_comp[0][ivar]->SetMaximum(h_1d_comp[0][ivar]->GetMaximum()*ymaxscale[ivar]);
        h_1d_comp[0][ivar]->SetMinimum(0);
        h_1d_comp[0][ivar]->GetXaxis()->SetRangeUser(xminrange[ivar],xmaxrange[ivar]);
        */
        
        c1->cd();
        
        //TPad *ppad = new TPad("ppad","",0,0,1,1);
        //ppad->Draw();
        //ppad->cd();
        //h_1d_comp[0][ivar]->Draw("");
        fHstach[0][ivar]->Draw();
        fHstach[0][ivar]->GetXaxis()->SetTitle(TString(xtitle[ivar]));
        fHstach[0][ivar]->GetYaxis()->SetTitle(ytitle);
        fHstach[0][ivar]->SetMaximum(fHstach[0][ivar]->GetMaximum()*ymaxscale[ivar]);
        fHstach[0][ivar]->SetMinimum(0);
        fHstach[0][ivar]->GetXaxis()->SetRangeUser(xminrange[ivar],xmaxrange[ivar]);
        titleStyle(fHstach[0][ivar]);
        c1->Modified();
        /*for ( int ifile = 1 ; ifile < NMODEL2COMP ; ifile++ ){//change to 11
            h_1d_comp[ifile][ivar]->Draw("same");
            fHstach[ifile][ivar]->Draw("same");
        }*/
        
        
        l1->Draw();
        TLegend* leg0 = new TLegend(xlegmin[ivar], ylegmin[ivar], xlegmin[ivar]+0.15, ylegmin[ivar]+0.2);
        leg0->SetFillStyle(0);
        leg0->SetBorderSize(0);
        leg0->SetTextSize(18);
        leg0->SetTextFont(43);
        //for (Int_t ifile=0; ifile<NMODEL2COMP; ++ifile) {
            leg0->AddEntry(h_1d_comp[0][ivar],model_name[0],"f");
        leg0->AddEntry(hcoh_1d_comp[0][ivar],model_name[1],"f");
        //}
        leg0->Draw("same");
        
        
       
        c1->Print(Form("plots/%s_%s_%s_%spos_cohincoh.eps",neutversion_s.Data(),flavor_str[flavorindex],hist_type[hist_index[ivar]],hist_kind[topoindex]));
        
        delete leg0;
        delete c1;
        
    }
    
}
