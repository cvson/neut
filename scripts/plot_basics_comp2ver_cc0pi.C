void plot_basics_comp2ver_cc0pi(){
    gROOT->ProcessLine(".x rootlogon.C"); 
    gROOT->ProcessLine(".L basicPlotUtil.C");
    TString ipDir = "/home/cvson/disk/nuicise/neut/neut_5.4.0_alpha/src/neutsmpl/";
    TString ipDir1 = "/home/cvson/disk/nuicise/neut/neut_5.3.7_INGRID_FIX/src/neutsmpl/";
    TString ipDir2 = "/home/cvson/disk/nuicise/neut/neut_5.3.2/src/neutsmpl/";
    TString ipDir4 = "/home/cvson/disk/nuicise/neut/neut_5.4.0/src/neutsmpl/";    

    /*TFile *ffile = new TFile(ipDir4+"basicplotso_5.3.6_nd5_C_GFGCCQE_cc0pi.root");
    TString vername = "NEUT 5.4.0"; 
    TFile *ffile2 = new TFile(ipDir1+"basicplotso_5.3.6_nd5_C_GFGCCQE_cc0pi.root");
    TString vername2 = "NEUT 5.3.6";
    TString savename ="nd5_cc0pi_gfg_neut540vs536_";*/
 
    TFile *ffile = new TFile(ipDir4+"basicplotso_5.3.6_nd5_C_SFCCQE_cc0pi.root");
    TString vername = "NEUT 5.4.0"; 
    TFile *ffile2 = new TFile(ipDir1+"basicplotso_5.3.6_nd5_C_SFCCQE_cc0pi.root");
    TString vername2 = "NEUT 5.3.6";
    TString savename ="nd5_cc0pi_sf_neut540vs536_";
	
 
    TIter next(ffile->GetListOfKeys());
    TKey *key;
    Int_t nhist=0;
    vector<char*> vkeyclassname;
    vector<char*> vkeytitle;
    while ((key = (TKey*)next())) {
        nhist++;
        cout << "Key " << nhist << endl;
        cout << " Classname " <<key->GetClassName() << endl;
        cout << " Title " <<key->GetTitle() << endl;
        TObject *obj = (TObject*)key->ReadObj();
        vkeyclassname.push_back(key->GetClassName());
        vkeytitle.push_back(obj->GetName());
        TClass *cl = gROOT->GetClass(key->GetClassName());
        if (cl->InheritsFrom("TH1D")) {
            TH1D *h = (TH1D*)ffile->Get(obj->GetName());
		TH1D *h2 = (TH1D*)ffile2->Get(obj->GetName());
		//TH1D *h1 = (TH1D*)ffile1->Get(obj->GetName());
            cout<<"plotting "<<obj->GetName()<<endl;
		if(TString(obj->GetName()).Contains("\_Q2")) h->GetXaxis()->SetTitle("Q^{2}(GeV^{2})");
		else if (TString(obj->GetName()).Contains("\_mode")) h->GetXaxis()->SetTitle("NEUT modes");
		else if (TString(obj->GetName()).Contains("\_anglemu")) h->GetXaxis()->SetTitle("#theta_{#mu}");
		else if (TString(obj->GetName()).Contains("\_anglepro2")) h->GetXaxis()->SetTitle("Outgoing nucleon #theta_{p2}");
		else if (TString(obj->GetName()).Contains("\_anglepro")) h->GetXaxis()->SetTitle("Outgoing nucleon #theta_{p1}");
		else if (TString(obj->GetName()).Contains("\_angleneu\_in2")) h->GetXaxis()->SetTitle("Incoming nucleon #theta_{n2}");
		else if (TString(obj->GetName()).Contains("\_angleneu\_in")) h->GetXaxis()->SetTitle("Incoming nucleon #theta_{n1}");
		else if (TString(obj->GetName()).Contains("\_pmu")) h->GetXaxis()->SetTitle("P_{#mu}(GeV)");
                else if (TString(obj->GetName()).Contains("\_npro")) h->GetXaxis()->SetTitle("No. of protons");
		else if (TString(obj->GetName()).Contains("\_ppro2")) h->GetXaxis()->SetTitle("Outgoing nucleon P_{p2}(GeV)");
		else if (TString(obj->GetName()).Contains("\_ppro")) h->GetXaxis()->SetTitle("Outgoing nucleon P_{p1}(GeV)");
		else if (TString(obj->GetName()).Contains("\_pneu\_in2")) h->GetXaxis()->SetTitle("Incoming nucleon P_{n2}(GeV)");
		else if (TString(obj->GetName()).Contains("\_pneu\_in")) h->GetXaxis()->SetTitle("Incoming nucleon P_{n1}(GeV)");
		else if (TString(obj->GetName()).Contains("\_cosanglemu")) h->GetXaxis()->SetTitle("cos#theta_{#mu}");
		else if (TString(obj->GetName()).Contains("\_cosanglepro2")) h->GetXaxis()->SetTitle("Outgoing nucleon cos#theta_{p2}");
		else if (TString(obj->GetName()).Contains("\_cosanglepro")) h->GetXaxis()->SetTitle("Outgoing nucleon cos#theta_{p1}");
		else if (TString(obj->GetName()).Contains("\_cosangleneu\_in2")) h->GetXaxis()->SetTitle("Incoming nucleon cos#theta_{n2}");
		else if (TString(obj->GetName()).Contains("\_cosangleneu\_in")) h->GetXaxis()->SetTitle("Incoming nucleon cos#theta_{n1}");
		else if (TString(obj->GetName()).Contains("\_enurec")) h->GetXaxis()->SetTitle("Recontructed E_{#nu} (GeV)");
		else if (TString(obj->GetName()).Contains("\_q2rec")) h->GetXaxis()->SetTitle("Recontructed Q^{2}(GeV^{2})");
		else if (TString(obj->GetName()).Contains("\_t")) h->GetXaxis()->SetTitle("|t|-momentum transfer (GeV^{2})");
		else if (TString(obj->GetName()).Contains("\_cosopenanglemuproccqe")) h->GetXaxis()->SetTitle("cos opening angle (#mu-p1)(CCQE)");
		else if (TString(obj->GetName()).Contains("\_cosopenanglemupromec")) h->GetXaxis()->SetTitle("cos opening angle (#mu-p1)(2p2h)");
		else if (TString(obj->GetName()).Contains("\_cosopenanglemupro")) h->GetXaxis()->SetTitle("cos opening angle (#mu-p1)");
		else if (TString(obj->GetName()).Contains("\_cosopenangle2pro")) h->GetXaxis()->SetTitle("cos opening angle (p2-p1)");
		if(TString(obj->GetName()).Contains("\_XS") ) {
		   plot2hist(h,vername,h2,vername2,savename+TString(obj->GetName()),0.6,0.6);
		    //plot3hist(h,vername,h1,vername1,h2,vername2,savename+TString(obj->GetName()),0.6,0.6);
		}
		else if (TString(obj->GetName()).Contains("TotXS") ){ 
		h->GetXaxis()->SetRangeUser(0,10);
		plot2hist(h,vername,h2,vername2,savename+TString(obj->GetName()),0.18,0.67); 
		 //plot3hist(h,vername,h1,vername1,h2,vername2,savename+TString(obj->GetName()),0.18,0.76);
		}
		else if (TString(obj->GetName()).Contains("flux\_numu") ){ 
                h->GetXaxis()->SetRangeUser(0,10);
                plot2hist(h,vername,h2,vername2,savename+TString(obj->GetName()),0.6,0.6);
                //plot3hist(h,vername,h1,vername1,h2,vername2,savename+TString(obj->GetName()),0.6,0.6);
		}
		else plot2hist_stat(h,vername,h2,vername2,"",savename+TString(obj->GetName()),false);
		//else plot3hist_stat(h,vername,h1,vername1,h2,vername2,"",savename+TString(obj->GetName()),false);	
        }
    }
    
    /*for (ii=0; ii<vkeytitle.size(); ii++) {
 *      cout << vkeytitle.at(ii)<<" "<<vkeyclassname.at(ii)<<endl;
 *           }*/
}

