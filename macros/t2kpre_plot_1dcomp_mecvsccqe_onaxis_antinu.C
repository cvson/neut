{
    gROOT->ProcessLine(".x /Users/soncao/rootlogon.C");
    gROOT->ProcessLine(".L /Users/soncao/basicPlotUtil.C");
    
    TString neutversion = "NEUT v5.4.0, On-axis";
    TString neutversion_s = "neut540_onaxis";
    const Int_t NCHAN2COMP = 3;
    TFile *pfile;
    pfile = new TFile("basicplotsv8_neut540_antinu_card_5.3.6_nd2_C_1p1hCCQE_ccqemec.root","READ");
    
    const int NFLAVOR = 6;
    const int NHIST1D = 34;
    const int NCHANNEL = 11;
    const int NHIST2D = 8;
    
    char *model_name[NCHAN2COMP]={"All \0","2p2h \0","CCQE \0" };
    int flavorindex = 4;//for numubar beam
    int topoindex[NCHAN2COMP] = {1,4,3};//DIS and multi pion
    
    
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
    const int NVAR2PLOT = 15;
    TH1D *h_1d_comp[NCHAN2COMP][NVAR2PLOT];
    int hist_index[NVAR2PLOT];
    char* xtitle[NVAR2PLOT];
    double xminrange[NVAR2PLOT];
    double xmaxrange[NVAR2PLOT];
    double xlegmin[NVAR2PLOT];
    double ylegmin[NVAR2PLOT];
    double ymaxscale[NVAR2PLOT];
    double yratscale[NVAR2PLOT];
    
    char *ytitle = "Arbitrary unit";
    
    
    hist_index[0] = 0;//Q2
    xtitle[0]= "E_{#nu} (GeV)";
    xminrange[0]= 0.;
    xmaxrange[0]= 2.0;//
    xlegmin[0]= 0.55;
    ylegmin[0]= 0.65;
    ymaxscale[0]= 1.5;
    yratscale[0] = 2;
    
    hist_index[1] = 7;//Q2
    xtitle[1]= "Q^{2} (GeV^{2})";
    xminrange[1]= 0.;
    xmaxrange[1]= 2.0;//
    xlegmin[1]= 0.55;
    ylegmin[1]= 0.65;
    ymaxscale[1]= 1.5;
    yratscale[1] = 2;
    
    hist_index[2]= 1;//muon momentum
    xtitle[2]= "P_{#mu} (GeV)";
    xminrange[2]= 0.;
    xmaxrange[2]= 2.0;//
    xlegmin[2]= 0.55;
    ylegmin[2]= 0.65;
    ymaxscale[2]= 1.5;
    yratscale[2] = 2;
    
    hist_index[3]= 6;//muon momentum
    xtitle[3]= "cos #theta_{#mu}";
    xminrange[3]= -1;
    xmaxrange[3]= 1.;//
    xlegmin[3]= 0.55;
    ylegmin[3]= 0.65;
    ymaxscale[3]= 1.5;
    yratscale[3] = 2;
    
    hist_index[4]= 2;//muon momentum
    xtitle[4]= "Incoming nucleon P_{n} (GeV)";
    xminrange[4]= 0.;
    xmaxrange[4]= 0.5;//
    xlegmin[4]= 0.55;
    ylegmin[4]= 0.65;
    ymaxscale[4]= 3.;
    yratscale[4] = 4;
    
    hist_index[5]= 4;//muon momentum
    xtitle[5]= "Outgoing nucleon P_{n} (GeV)";
    xminrange[5]= 0.;
    xmaxrange[5]= 2.;//
    xlegmin[5]= 0.55;
    ylegmin[5]= 0.65;
    ymaxscale[5]= 1.5;
    yratscale[5] = 2;
    
    hist_index[6]= 8;//muon momentum
    xtitle[6]= "Incoming nucleon cos #theta_{n}";
    xminrange[6]= -1;
    xmaxrange[6]= 1;//
    xlegmin[6]= 0.55;
    ylegmin[6]= 0.45;
    ymaxscale[6]= 1.5;
    yratscale[6] = 2;
    
    hist_index[7]= 10;//muon momentum
    xtitle[7]= "Outgoing nucleon cos #theta_{n}";
    xminrange[7]= -1;
    xmaxrange[7]= 1;//
    xlegmin[7]= 0.55;
    ylegmin[7]= 0.45;
    ymaxscale[7]= 1.5;
    yratscale[7] = 2;
    
    hist_index[8]= 16;//muon momentum
    xtitle[8]= "Rescattering nucleon (FSI) P_{n} (GeV)";
    xminrange[8]= 0;
    xmaxrange[8]= 2;//
    xlegmin[8]= 0.55;
    ylegmin[8]= 0.45;
    ymaxscale[8]= 1.5;
    yratscale[8] = 2;
    
    hist_index[9]= 19;//muon momentum
    xtitle[9]= "Interaction position (radius) in nucleus";
    xminrange[9]= 0;
    xmaxrange[9]= 6;//
    xlegmin[9]= 0.6;
    ylegmin[9]= 0.45;
    ymaxscale[9]= 1.5;
    yratscale[9] = 2;
    
    
    hist_index[10]= 21;//muon momentum
    xtitle[10]= "No. of protons (FSI)";
    xminrange[10]= 0;
    xmaxrange[10]= 10;//
    xlegmin[10]= 0.55;
    ylegmin[10]= 0.45;
    ymaxscale[10]= 1.5;
    yratscale[10] = 2;
    
    hist_index[11]= 12;//muon momentum
    xtitle[11]= "Incoming nucleon cos #theta_{n}";
    xminrange[11]= -1;
    xmaxrange[11]= 1;//
    xlegmin[11]= 0.45;
    ylegmin[11]= 0.45;
    ymaxscale[11]= 1.5;
    yratscale[11] = 2;
    
    hist_index[12]= 26;//muon momentum
    xtitle[12]= "E_{reco,CCQE}-E_{true} [GeV]";
    xminrange[12]= -0.5;
    xmaxrange[12]= 0.5;//
    xlegmin[12]= 0.65;
    ylegmin[12]= 0.45;
    ymaxscale[12]= 1.2;
    yratscale[12] = 2;
    
    //the opening angle is for MEC only
    hist_index[13]= 17;//muon momentum
    xtitle[13]= "Opening angle btw two incoming nucleons";
    xminrange[13]= -1;
    xmaxrange[13]= 1;//
    xlegmin[13]= 0.55;
    ylegmin[13]= 0.45;
    ymaxscale[13]= 1.5;
    yratscale[13] = 2;
    
    hist_index[14]= 18;//muon momentum
    xtitle[14]= "Opening angle btw two outgoing nucleons";
    xminrange[14]= -1;
    xmaxrange[14]= 1;//
    xlegmin[14]= 0.55;
    ylegmin[14]= 0.45;
    ymaxscale[14]= 1.5;
    yratscale[14] = 2;
    
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
            //ignore opening angle of nucleons for CCQE
            if(!(ichan==2 && (ivar==13 || ivar==14)) ){
                h_1d_comp[ichan][ivar] = (TH1D*)pfile->Get(Form("h_%s_%s_%s",hist_kind[topoindex[ichan]],hist_type[hist_index[ivar]],flavor_str[flavorindex]));
                h_1d_comp[ichan][ivar]->SetLineWidth(2);
                ci = TColor::GetColor(colorcode[ichan]);
                h_1d_comp[ichan][ivar]->SetLineColor(ci);
            }
        }
    }
    
    cout<<"finish get plots"<<endl;
    
    TLatex *l1 = new TLatex(0.3, 0.98, Form("%s,%s",neutversion.Data(),flavor_strlatex[flavorindex]));
    l1->SetNDC();
    l1->SetTextFont(43);
    l1->SetTextSize(20);
    l1->SetTextAlign(13);
    
    TLatex *l12 = new TLatex(0.3, 0.98, Form("%s,%s, 2p2h",neutversion.Data(),flavor_strlatex[flavorindex]));
    l12->SetNDC();
    l12->SetTextFont(43);
    l12->SetTextSize(20);
    l12->SetTextAlign(13);
    
    TH1D *h_1d_comprat[NCHAN2COMP][NVAR2PLOT];
    
    for ( int ivar = 0 ; ivar < NVAR2PLOT ; ivar++ ){
        //new TCanvas;
        if(!(ivar==13 || ivar==14)){
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
            h_1d_comprat[0][ivar]->GetYaxis()->SetTitle("MC/all");
            titleStyle2x(h_1d_comprat[0][ivar],3.);
            h_1d_comprat[0][ivar]->Draw("hist");
            h_1d_comprat[0][ivar]->GetYaxis()->SetRangeUser(0,yratscale[ivar]);
            for ( int ichan = 1 ; ichan < NCHAN2COMP ; ichan++ ){
                h_1d_comprat[ichan][ivar]->Draw("hist same");
            }
            //zoom for bias energy reconstruction
            if(ivar==12){
                upperPad->cd();
                Double_t xlow = 0.1;
                Double_t xhigh = 1.0 - 0.5;
                Double_t ylow = 0.5;
                Double_t yhigh = 0.95;
                TPad *ppadcp = new TPad("padcp","",xlow+0.005,ylow,xhigh+0.005,yhigh);
                ppadcp->SetFillStyle(4000);
                
                TH1D* h0_clone    = (TH1D*)h_1d_comp[0][ivar]->Clone("clone");
                h0_clone->GetXaxis()->SetTitle("");
                h0_clone->GetYaxis()->SetTitle("");
                h0_clone->GetXaxis()->SetRangeUser(-0.5,0.5);
                h0_clone->SetMaximum(h0_clone->GetMaximum()/5.0);
                ppadcp->Range(0.1,0.0,0.9,h0_clone->GetMaximum()/5.0);
                ppadcp->Draw();
                ppadcp->cd();
                h0_clone->Draw();
                TH1D* h0_clone1    = (TH1D*)h_1d_comp[1][ivar]->Clone("clone_1");
                h0_clone1->Draw("hist same");
                TH1D* h0_clone2    = (TH1D*)h_1d_comp[2][ivar]->Clone("clone_1");
                h0_clone2->Draw("hist same");
                
            }
            
            c1->Print(Form("plots/%s_histat_%s_%s_mecvsccqe.eps",neutversion_s.Data(),flavor_str[flavorindex],hist_type[hist_index[ivar]]));
            
            delete leg0;
            delete c1;
        }//end ivar !=13 !=14
        else
        {
            TCanvas *c1 = new TCanvas("c1","c1");
            TGaxis::SetMaxDigits(3);
            
            h_1d_comp[1][ivar]->GetXaxis()->SetTitle(TString(xtitle[ivar]));
            h_1d_comp[1][ivar]->GetYaxis()->SetTitle(ytitle);
            h_1d_comp[1][ivar]->SetTitle("");
            titleStyle(h_1d_comp[0][ivar]);
            h_1d_comp[1][ivar]->SetMaximum(h_1d_comp[1][ivar]->GetMaximum()*ymaxscale[ivar]);
            h_1d_comp[1][ivar]->GetXaxis()->SetRangeUser(xminrange[ivar],xmaxrange[ivar]);
            c1->cd();
            h_1d_comp[1][ivar]->SetMinimum(0);
            h_1d_comp[1][ivar]->Draw("");
            l12->Draw();
            c1->Print(Form("plots/%s_histat_%s_%s_meconly.eps",neutversion_s.Data(),flavor_str[flavorindex],hist_type[hist_index[ivar]]));
            delete c1;
        }
        
    }//end ivar
    
}
