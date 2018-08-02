void nucleus(Int_t nProtons  = 6,Int_t  nNeutrons = 6){
    //TCanvas *c1 = new TCanvas("c1","",200,10,600,600);
    TCanvas *c1 = new TCanvas("c1","pi",800,800);
    c1->Range(-200,-200,200,200);
    
    Double_t NeutronRadius = 15,
    ProtonRadius = 15,
    NucleusRadius,
    distance = 20;
    Double_t vol = nProtons + nNeutrons;
    
    NucleusRadius = distance * 8;
    cout<<"Nucleus radius "<<NucleusRadius<<endl;
    TEllipse *pnucleus = new TEllipse(0.0, 0.0, NucleusRadius,NucleusRadius);
    pnucleus->Draw();
    
    Double_t xpos_p[] = {-100, -90, -50, 10,  60,  100} ;
    Double_t ypos_p[] = {-50,   20, 100, -100, -30, 60};
    
    Double_t xpos_n[] = {-90, -80, -40, 10,  50,  90} ;
    Double_t ypos_n[] = {-30,   35, 90, 5, -60, 50};
    
    
    //Double_t *xpos_n[] = {};
    //Double_t *ypos_n[] = {};
    

    for (Int_t ipro=0; ipro<nProtons; ++ipro) {
        TEllipse *pproton = new TEllipse(xpos_p[ipro], ypos_p[ipro], ProtonRadius,ProtonRadius);
        pproton->SetFillColor(kRed);
        pproton->Draw("same");
    }
    
    for (Int_t ineu=0; ineu<nNeutrons; ++ineu) {
        TEllipse *pneutron = new TEllipse(xpos_n[ineu], ypos_n[ineu], NeutronRadius,NeutronRadius);
        pneutron->SetFillColor(kBlue);
        pneutron->Draw("same");
    }
    
    
   /* Int_t seed = 2018;
    gRandom->SetSeed(seed);
    
    Double_t x, y, z, dummy;
    Int_t i = 0;
    while ( i<  nProtons) {
        x = gRandom->Uniform(0, 1);
        y = gRandom->Uniform(0, 1);
        if ( TMath::Sqrt(x*x + y*y ) < 1) {
            x = (2 * x - 1) * (NucleusRadius-ProtonRadius*3);
            y = (2 * y - 1) * (NucleusRadius-ProtonRadius*3);
            TEllipse *pproton = new TEllipse(x, y, ProtonRadius,ProtonRadius);
            pproton->SetFillColor(kRed);
            pproton->Draw("same");
            i++;
        }
    }
    i = 0;
    while ( i <  nNeutrons) {
        x = gRandom->Uniform(0, 1);
        y = gRandom->Uniform(0, 1);
        if ( TMath::Sqrt(x*x + y*y ) < 1) {
            x = (2 * x - 1) * (NucleusRadius - NeutronRadius*3);
            y = (2 * y - 1) * (NucleusRadius - NeutronRadius*3);
            TEllipse *pneutron = new TEllipse(x, y, NeutronRadius,NeutronRadius);
            pneutron->SetFillColor(kBlue);
            pneutron->Draw("same");
            i++;
        }
    }*/
    
    
    c1->Print("plots/nucleus.eps");
    
    //   cout << "NucleusRadius: " << NucleusRadius << endl;
    
    /*TGeoManager * geom = new TGeoManager("nucleus", "Model of a nucleus");
    geom->SetNsegments(40);
    TGeoMaterial *matEmptySpace = new TGeoMaterial("EmptySpace", 0, 0, 0);
    TGeoMaterial *matProton     = new TGeoMaterial("Proton"    , .938, 1., 10000.);
    TGeoMaterial *matNeutron    = new TGeoMaterial("Neutron"   , .935, 0., 10000.);
    
    TGeoMedium *EmptySpace = new TGeoMedium("Empty", 1, matEmptySpace);
    TGeoMedium *Proton     = new TGeoMedium("Proton", 1, matProton);
    TGeoMedium *Neutron    = new TGeoMedium("Neutron",1, matNeutron);
    
    //  the space where the nucleus lives (top container volume)
    
    Double_t worldx = 200.;
    Double_t worldy = 200.;
    Double_t worldz = 200.;
    
    TGeoVolume *top = geom->MakeBox("WORLD", EmptySpace, worldx, worldy, worldz);
    geom->SetTopVolume(top);
    
    TGeoVolume * proton  = geom->MakeSphere("proton",  Proton,  0., ProtonRadius);
    TGeoVolume * neutron = geom->MakeSphere("neutron", Neutron, 0., NeutronRadius);
    proton->SetLineColor(kRed);
    neutron->SetLineColor(kBlue);
    
    Double_t x, y, z, dummy;
    Int_t i = 0;
    while ( i<  nProtons) {
        gRandom->Rannor(x, y);
        gRandom->Rannor(z,dummy);
        if ( TMath::Sqrt(x*x + y*y + z*z) < 1) {
            x = (2 * x - 1) * NucleusRadius;
            y = (2 * y - 1) * NucleusRadius;
            z = (2 * z - 1) * NucleusRadius;
            top->AddNode(proton, i, new TGeoTranslation(x, y, z));
            i++;
        }
    }
    i = 0;
    while ( i <  nNeutrons) {
        gRandom->Rannor(x, y);
        gRandom->Rannor(z,dummy);
        if ( TMath::Sqrt(x*x + y*y + z*z) < 1) {
            x = (2 * x - 1) * NucleusRadius;
            y = (2 * y - 1) * NucleusRadius;
            z = (2 * z - 1) * NucleusRadius;
            top->AddNode(neutron, i + nProtons, new TGeoTranslation(x, y, z));
            i++;
        }
    }
    geom->CloseGeometry();
    geom->SetVisLevel(4);
    top->Draw("ogl");*/
}
