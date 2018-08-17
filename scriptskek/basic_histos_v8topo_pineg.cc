#include <TROOT.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TSystem.h>
#include <TMath.h>

#include <iostream>
#include <stdlib.h>

#include "../../include/neutvect.h"
#include "../../include/neutvtx.h"

using namespace std;

const int NFLAVOR = 6;
const int NHIST1D = 34;
const int NCHANNEL = 11;//12?
const int NHIST2D = 8;


bool 
isCC(int mode)
{
    if ( abs(mode) < 30 ){
        return true;
    }
    return false;
    
}

bool 
isNC(int mode)
{
    if ( abs(mode) >= 30 ){
        return true;
    }
    return false;
    
}

bool 
isCC1pi(int mode)
{
    /* CC1pi : 11, 12, 13 , -11, -12, -13 */
    
    if (( abs(mode) > 10 )&&( abs(mode) < 14 )){
        return true;
    }
    return false;
    
}

bool
isCC1pi11(int mode)
{
    /* CC1pi : 11, 12, 13 , -11, -12, -13 */
    
    if ( abs(mode) == 11){
        return true;
    }
    return false;
    
}

bool
isCC1pi12(int mode)
{
    /* CC1pi : 11, 12, 13 , -11, -12, -13 */
    
    if ( abs(mode) == 12){
        return true;
    }
    return false;
    
}

bool
isCC1pi13(int mode)
{
    /* CC1pi : 11, 12, 13 , -11, -12, -13 */
    
    if ( abs(mode) == 13){
        return true;
    }
    return false;
    
}

bool 
isCCdis(int mode)
{
    /* CCDIS : 21(W<2), 26(W>2) */
    
    if (( abs(mode) == 21 )||( abs(mode) == 26  )){
        return true;
    }
    return false;
    
}

bool
isCCdis21(int mode)
{
    /* CCDIS : 21(W<2), 26(W>2) */
    
    if ( abs(mode) == 21 ){
        return true;
    }
    return false;
    
}

bool
isCCdis26(int mode)
{
    /* CCDIS : 21(W<2), 26(W>2) */
    
    if ( abs(mode) == 26 ){
        return true;
    }
    return false;
    
}

bool
isCCcoh(int mode)
{
    /* CCDIS : 21(W<2), 26(W>2) */
    
    if (( abs(mode) == 16 ) ){
        return true;
    }
    return false;
    
}

bool
isCCtopo0pi(int npi, int mode)
{
    if (npi==0 && abs(mode)!=16 ){
        return true;
    }
    return false;
    
}

bool
isCCtopo1pi(int npi, int mode)
{
    if (npi==1 && abs(mode)!=16 ){
        return true;
    }
    return false;
    
}

bool
isCCtopoNpi(int npi, int mode)
{
    if (npi>1 && abs(mode)!=16 ){
        return true;
    }
    return false;
    
}



bool
isLepton(Int_t ip)
{
    
    if ( ( abs(ip) != 11 ) && ( abs(ip) != 13 ) && ( abs(ip) != 15 ) && ( abs(ip) != 12 ) && ( abs(ip) != 14 ) && ( abs(ip) != 16 )){
        cout << "IP is not lepton.. " << ip << endl;
        return false;
    }
    return true;
    
}

bool
isPion(Int_t ip)
{
    
    if (( ip != 211 ) && ( ip != -211 ) && ( ip != 111 ) ){
        return false;
    }
    return true;
    
}

/* generic functions */
Int_t
fill_energy(NeutVect *nvect, Int_t idx, TH1D *h1, Double_t weight)
{
    Double_t energy;
    
    energy = (nvect->PartInfo(idx))->fP.E();
    energy = energy / 1000.;
    h1->Fill(energy,weight);
    
    return 0;
    
}

Int_t
fill_momentum(NeutVect *nvect, Int_t idx, TH1D *h1, Double_t weight)
{
    Double_t p;
    
    p = (nvect->PartInfo(idx))->fP.P();
    p = p / 1000.;
    h1->Fill(p,weight);
    
    return 0;
    
}

Int_t
fill_costhetaL(NeutVect *nvect, Int_t idx, TH1D *h1, Double_t weight)
{
    Double_t costhetaL;
    
    if ( (nvect->PartInfo(idx))->fP.P() > 0 ){
        costhetaL =
        (nvect->PartInfo(idx))->fP.Pz() /
        (nvect->PartInfo(idx))->fP.P();
    }else{
        return 0;
    }
    
    h1->Fill(costhetaL,weight);
    return 0;
    
}

Int_t
fill_phiL(NeutVect *nvect, Int_t idx, TH1D *h1, Double_t weight)
{
    Double_t phiL;
    
    if ( (nvect->PartInfo(idx))->fP.P() > 0 ){
        phiL = TMath::ATan2((nvect->PartInfo(idx))->fP.Py(),
                            (nvect->PartInfo(idx))->fP.Px());
    }else{
        return 0;
    }
    
    h1->Fill(phiL,weight);
    return 0;
    
}

Int_t
fill_opening_angle(NeutVect *nvect, int idx1, int idx2, TH1D *h1, 
                   Double_t weight)
{
    TVector3 p1,p2;
    Double_t costheta;
    
    p1 = (nvect->PartInfo(idx1))->fP.Vect();
    p2 = (nvect->PartInfo(idx2))->fP.Vect();
    
    costheta = cos(p1.Angle(p2));
    
    h1->Fill(costheta,weight);
    
}

Int_t
fill_rad(NeutVect *nvect, int idx1, TH1D *h1, Double_t weight)
{
    //  Int_t vtx_id;
    TVector3 vtx;
    Double_t radius;
    
    //vtx_id = nvect->VertexID(idx1);
    //  vtx = nvtx->Pos(vtx_id)->Vect();
    vtx =( nvect->PartInfo(idx1))->fPosIni.Vect();
    radius = vtx.Mag();
    
    h1->Fill(radius,weight);
    
}

Int_t
fill_rad_momentum(NeutVect *nvect, int idx1, TH2D *h2, Double_t weight)
{
    TVector3 vtx;
    Double_t radius;
    
    Double_t p;
    
    p = (nvect->PartInfo(idx1))->fP.P();
    p = p / 1000.;
    
    vtx =( nvect->PartInfo(idx1))->fPosIni.Vect();
    radius = vtx.Mag();
    
    h2->Fill(radius,p,weight);
    
}
//additional 1D histogram
Int_t
fill_numode_hist(TH1D *h1, Double_t weight, Int_t mode)
{
    h1->Fill(mode,weight);
    return 0;
}

Int_t
fill_nproton_hist(TH1D *h1, Double_t weight, Int_t nproton)
{
    h1->Fill(nproton,weight);
    return 0;
}

Int_t
fill_npion_hist(TH1D *h1, Double_t weight, Int_t npion)
{
    h1->Fill(npion,weight);
    return 0;
}



//newadd
Int_t
fill_Evsk(NeutVect *nvect, int idx1, TH2D *h2, Double_t weight)//index2
{
    TVector3 vtx;
    Double_t radius;
    
    Double_t p, E;
    
    p = (nvect->PartInfo(idx1))->fP.P();
    p = p / 1000.;
    
    E = (nvect->PartInfo(idx1))->fP.E();
    E = E / 1000.;
    
    
    h2->Fill(E,p,weight);
    
}





/////////////////////////////////////////////////////////////////////////
Int_t
fill_in_enu_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    Int_t    ip;
    
    ip = (nvect->PartInfo(0))->fPID;
    if (( abs(ip) != 12 ) && ( abs(ip) != 14 ) && ( abs(ip) != 16 )){
        cout << "IP is not neutrino.. " << ip << endl;
        return -1;
    }
    
    fill_energy(nvect, 0, h1, weight);
    
    return 0;
}

Int_t
fill_out_plep_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    Int_t    idx,ip;
    
    if (abs(nvect->Mode)==2){
        idx = 3;
    }else{
        idx = 2;
    }
    
    ip = (nvect->PartInfo(idx))->fPID;
    if (isLepton(ip)){
        fill_momentum(nvect, idx, h1, weight);
    }else{
        return -1;
    }
    return 0;
}

//pion momentum, if multiple pion, fill the large
Int_t
fill_out_ppiINI_hist(NeutVect *nvect, TH1D *h1, TH1D *h12, TH2D *h2, Double_t weight)
{
    Int_t    ip,mode;
    
    mode = abs(nvect->Mode);
    
    if (( mode < 11 ) || ( mode > 34  )){
        return 0;
    }
    if (( mode > 13 ) && ( mode < 31 )){
        return 0;
    }
    
    ip = abs((nvect->PartInfo(3))->fPID);
    // delta absorption check
    if ((ip == 2224)||( ip == 2214 ) || ( ip == 2114 ) || ( ip == 1114 )){
        return 0;
    }
    ip = abs((nvect->PartInfo(4))->fPID);
    if (!isPion(ip)){
        cout << "IP is not pion " << ip << " mode= " << mode << endl;
        return -1;
    }
    
    Double_t
    ppi = ((nvect->PartInfo(4))->fP.P())/1000.;
    h1->Fill(ppi,weight);
    
    Double_t cospi;
    cospi = (nvect->PartInfo(0))->fP.Vect()*(nvect->PartInfo(4))->fP.Vect();
    cospi = cospi /
    ((nvect->PartInfo(0))->fP.P()*(nvect->PartInfo(4))->fP.P());
    
    h12->Fill(cospi,weight);
    
    h2->Fill(cospi,ppi,weight);
    
    return 0;
}

Int_t
fill_out_cohpi_hist(NeutVect *nvect, TH1D *h1, TH1D *h12, TH2D *h2, Double_t weight)
{
    Int_t    ip,mode;
    
    mode = abs(nvect->Mode);
    
    //selec coherent only
    if (( mode != 16 ) && ( mode != 36 )){
        return 0;
    }
    //check if index 4 is pion
    ip = abs((nvect->PartInfo(4))->fPID);
    if (!isPion(ip)){
        cout << "IP is not pion " << ip << " mode= " << mode << endl;
        return -1;
    }
    
    Double_t
    ppi = ((nvect->PartInfo(4))->fP.P())/1000.;
    h1->Fill(ppi,weight);
    
    Double_t cospi;
    cospi = (nvect->PartInfo(0))->fP.Vect()*(nvect->PartInfo(4))->fP.Vect();
    cospi = cospi /
    ((nvect->PartInfo(0))->fP.P()*(nvect->PartInfo(4))->fP.P());
    
    h12->Fill(cospi,weight);
    
    h2->Fill(cospi,ppi,weight);
    
    return 0;
}

Int_t
fill_out_dispiINI_hist(NeutVect *nvect, TH1D *h1, TH1D *h12, TH1D *h13,TH2D *h2, Double_t weight)
{
    Int_t    ip,mode;
    mode = abs(nvect->Mode);
    //selec DIS/multipion only
    if (( mode != 21 ) && ( mode != 26 ) && ( mode != 41 ) && (mode != 46) ){
        return 0;
    }
    
    TVector3 p1,p0;
    Int_t npi = 0;
    Int_t idx = -1;
    Double_t cospi = 1.;
    Double_t ppi   = 0;
    for ( int i = 2 ; i < nvect->Nprimary() ; i++ ){
        ip = abs((nvect->PartInfo(i))->fPID);
        if (isPion(ip)){
            npi = npi + 1.;
            //highest momentum
            if ( ppi < (nvect->PartInfo(i))->fP.P()/1000. ){
                ppi = ((nvect->PartInfo(i))->fP.P())/1000.;
                p0 = (nvect->PartInfo(0))->fP.Vect();//nu
                p1 = (nvect->PartInfo(i))->fP.Vect();
                cospi = cos(p0.Angle(p1));
                
                idx = i;
            }
        }
    }//end for
    if ( idx >= 0 ){
        h1->Fill(ppi,weight);//highest pi mom
        h12->Fill(cospi,weight); //cos highest pi
        h13->Fill(npi,weight);
        h2->Fill(cospi,ppi,weight);//2D
        
    }
    
    return 0;
}


Int_t
fill_out_dispiFSI_hist(NeutVect *nvect, TH1D *h1, TH1D *h12, TH2D *h2, Double_t weight)
{
    Int_t    ip,mode;
    mode = abs(nvect->Mode);
    //selec DIS/multipion only
    if (( mode != 21 ) && ( mode != 26 ) && ( mode != 41 ) && (mode != 46) ){
        return 0;
    }
    
    TVector3 p1,p0;
    Int_t npi = 0;
    Int_t idx = -1;
    Double_t cospi = 1.;
    Double_t ppi   = 0;
    for ( int i = 2 ; i < nvect->Npart() ; i++ ){
        if ((nvect->PartInfo(i))->fIsAlive){
            ip = abs((nvect->PartInfo(i))->fPID);
            if (isPion(ip)){
                npi = npi + 1.;
                //highest momentum
                if ( ppi < (nvect->PartInfo(i))->fP.P()/1000. ){
                    ppi = ((nvect->PartInfo(i))->fP.P())/1000.;
                    p0 = (nvect->PartInfo(0))->fP.Vect();//nu
                    p1 = (nvect->PartInfo(i))->fP.Vect();
                    cospi = cos(p0.Angle(p1));
                    
                    idx = i;
                }
            }
        }
    }//end for
    if ( idx >= 0 ){
        h1->Fill(ppi,weight);//highest pi mom
        h12->Fill(cospi,weight); //cos highest pi
        h2->Fill(cospi,ppi,weight);//2D
        
    }
    
    return 0;
}


//pion momentum, if multiple pion, fill the large
Int_t
fill_out_ppiFSI_hist(NeutVect *nvect, TH1D *h1, TH1D *h12, TH1D *h13, TH1D *h14, TH2D *h2, Double_t weight)
{
    Int_t    ip,mode;
    
    mode = abs(nvect->Mode);
    
    if (( mode < 11 ) || ( mode > 34  )){
        return 0;
    }
    if (( mode > 13 ) && ( mode < 31 )){
        return 0;
    }
    
    ip = abs((nvect->PartInfo(3))->fPID);
    // delta absorption check
    if ((ip == 2224)||( ip == 2214 ) || ( ip == 2114 ) || ( ip == 1114 )){
        return 0;
    }
    ip = abs((nvect->PartInfo(4))->fPID);
    if (!isPion(ip)){
        cout << "IP is not pion " << ip << " mode= " << mode << endl;
        return -1;
    }
    
    TVector3 p1,p2,p0;
    Int_t npi = 0;
    Int_t idx = -1;
    Double_t cospi = 1.;
    Double_t cospifin = 1.;
    Double_t ppi   = 0;
    //for ( int i = nvect->Nprimary() ; i < nvect->Npart() ; i++ ){
    for ( int i = 2 ; i < nvect->Npart() ; i++ ){
        if ((nvect->PartInfo(i))->fIsAlive){
            ip = abs((nvect->PartInfo(i))->fPID);
            if (isPion(ip)){
                npi = npi + 1.;
                //highest momentum
                if ( ppi < (nvect->PartInfo(i))->fP.P()/1000. ){
                    ppi = ((nvect->PartInfo(i))->fP.P())/1000.;
                    p0 = (nvect->PartInfo(0))->fP.Vect();//nu
                    p1 = (nvect->PartInfo(4))->fP.Vect();
                    p2 = (nvect->PartInfo(i))->fP.Vect();
                    cospi = cos(p1.Angle(p2));
                    cospifin = cos(p0.Angle(p2));
                    
                    idx = i;
                }
            }
        }
    }//end for
    if ( idx >= 0 ){
        h1->Fill(ppi,weight);//highest pi mom
        h12->Fill(cospifin,weight); //cos highest pi
        h13->Fill(ppi-((nvect->PartInfo(4))->fP.P())/1000.,weight);//diff pion mom
        h14->Fill(cospi,weight);
        h2->Fill(cospifin,ppi,weight);//2D
        
    }
    
    return 0;
}




Int_t
fill_in_pnuc1_hist(NeutVect *nvect, TH1D *h1,  Double_t weight)
{
    Int_t    ip,mode;
    
    mode = abs(nvect->Mode);
    
    if (( mode == 16 ) || ( mode == 36 )){
        return 0;
    }
    
    ip = (nvect->PartInfo(1))->fPID;
    if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
        ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
        cout << "IP is not nucleon " << ip << " mode= " << mode << endl;
        return -1;
    }
    
    fill_momentum(nvect, 1, h1, weight);
    
    return 0;
}

Int_t
fill_in_pnuc2_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    /* only for 2p2h interaction */
    
    Int_t    ip,mode;
    
    mode = abs(nvect->Mode);
    
    if ( mode != 2 ){
        return 0;
    }
    
    ip = (nvect->PartInfo(2))->fPID;
    if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
        ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
        cout << "IP is not nucleon " << ip << endl;
        return -1;
    }
    
    fill_momentum(nvect, 2, h1, weight);
    
    return 0;
}

Int_t
fill_out_pnuc1_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    
    Int_t    idx,ip;
    Int_t    mode;
    
    Double_t e1,e2;
    
    idx = 3;
    
    mode = abs(nvect->Mode);
    
    if (( mode == 16 ) || ( mode == 36 )){
        return 0;
    }
    
    if ( mode == 2 ){
        idx = 4;
        e1 = (nvect->PartInfo(4))->fP.E();
        e2 = (nvect->PartInfo(5))->fP.E();
        if ( e1 < e2 ){
            idx = 5;
        }
    }
    
    ip = (nvect->PartInfo(idx))->fPID;
    if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
        ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
        cout << "IP is not nucleon " << ip << endl;
        return -1;
    }
    
    fill_momentum(nvect, idx, h1, weight);
    
    return 0;
}

Int_t
fill_out_pnuc2_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    /* only for 2p2h interaction */
    
    Int_t    idx,ip,mode;
    
    Double_t e1,e2;
    
    idx = 5;
    
    mode = abs(nvect->Mode);
    
    if ( mode == 2 ){
        e1 = (nvect->PartInfo(4))->fP.E();
        e2 = (nvect->PartInfo(5))->fP.E();
        if ( e1 < e2 ){
            idx = 4;
        }
    }else{
        return 0;
    }
    
    ip = (nvect->PartInfo(idx))->fPID;
    if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
        ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
        cout << "IP is not nucleon " << ip << endl;
        return -1;
    }
    
    fill_momentum(nvect, idx, h1, weight);
    
    return 0;
}

Int_t
fill_coslep_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    Int_t    idx,ip,mode;
    Double_t coslep;
    
    idx = 2;
    
    mode = abs(nvect->Mode);
    
    if ( mode == 2 ){
        idx = 3;
    }
    
    ip = abs((nvect->PartInfo(idx))->fPID);
    if (isLepton(ip)){
        coslep = (nvect->PartInfo(0))->fP.Vect()*(nvect->PartInfo(idx))->fP.Vect();
        coslep = coslep /
        ((nvect->PartInfo(0))->fP.P()*(nvect->PartInfo(idx))->fP.P());
        h1->Fill(coslep,weight);
    }else{
        return -1;
    }
    return 0;
}

Int_t
fill_coslepvsP_hist(NeutVect *nvect, TH2D *h2, Double_t weight)//index 3
{
    Int_t    idx,ip,mode;
    Double_t coslep, pL;
    
    idx = 2;
    
    mode = abs(nvect->Mode);
    
    if ( mode == 2 ){
        idx = 3;
    }
    
    ip = abs((nvect->PartInfo(idx))->fPID);
    if (isLepton(ip)){
        coslep = (nvect->PartInfo(0))->fP.Vect()*(nvect->PartInfo(idx))->fP.Vect();
        coslep = coslep /
        ((nvect->PartInfo(0))->fP.P()*(nvect->PartInfo(idx))->fP.P());
        pL = nvect->PartInfo(idx)->fP.P();
        pL = pL/1000.;//
        h2->Fill(coslep,pL,weight);//newadd
    }else{
        return -1;
    }
    return 0;
}

Int_t
fill_bindingEvsk_hist(NeutVect *nvect, TH2D *h2, Double_t weight)//index 3
{
    Int_t    idx,ip,mode;
    Double_t bindE, bindk;
    TLorentzVector q4;
    idx = 2;
    
    mode = abs(nvect->Mode);
    
    if ( mode == 2 ){
        idx = 3;
    }
    
    ip = abs((nvect->PartInfo(idx))->fPID);
    if (isLepton(ip)){
        if(mode !=2) q4 =  (nvect->PartInfo(idx))->fP + (nvect->PartInfo(3))->fP  - (nvect->PartInfo(0))->fP - (nvect->PartInfo(1))->fP;
        else q4 = (nvect->PartInfo(idx))->fP + (nvect->PartInfo(4))->fP + (nvect->PartInfo(5))->fP  - (nvect->PartInfo(0))->fP - (nvect->PartInfo(1))->fP - (nvect->PartInfo(2))->fP;
        bindE = abs(q4.E())/1000.;
        bindk = abs((nvect->PartInfo(1))->fP.P())/1000.;
        h2->Fill(bindk,bindE,weight);//newadd
    }else{
        return -1;
    }
    return 0;
}


Int_t
fill_q2_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    Int_t    idx,ip,mode;
    TLorentzVector q4;
    Double_t q2;
    
    idx = 2;
    
    mode = abs(nvect->Mode);
    
    if ( mode == 2 ){
        idx = 3;
    }
    
    ip = abs((nvect->PartInfo(idx))->fPID);
    if (isLepton(ip)){
        q4 =  (nvect->PartInfo(idx))->fP - (nvect->PartInfo(0))->fP;
        q2 = q4 * q4;
        q2 = q2 / 1000. / 1000.;
        h1->Fill(abs(q2),weight);
    }else{
        return -1;
    }
    return 0;
}

//double t = abs(((nvect->PartInfo(pion_nbr))->fP -( (nvect->PartInfo(0))->fP - (nvect->PartInfo(muon_nbr))->fP ))*((nvect->PartInfo(pion_nbr))->fP -( (nvect->PartInfo(0))->fP - (nvect->PartInfo(muon_nbr))->fP )))*1e-6;
//for coherent
Int_t
fill_tmomtrans_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    Int_t    idx,ip,mode, idxpi, npi;
    TLorentzVector q4;
    Double_t tmomtrans;
    idx = 2;
    mode = abs(nvect->Mode);
    if ( mode == 2 ){
        idx = 3;
    }
    ip = abs((nvect->PartInfo(idx))->fPID);
    npi =0;
    for ( Int_t i = 2 ; i < nvect->Npart() ; i++ ){
        if ((nvect->PartInfo(i))->fIsAlive){
            if(abs((nvect->PartInfo(i))->fPID) == 211 || (nvect->PartInfo(i))->fPID == 111){
                idxpi = i;//index for pion
                ++npi;
            }
        }
    }
    if (isLepton(ip) && npi==1){//dedicate for coherent and single pion
        q4 =  (nvect->PartInfo(idxpi))->fP +(nvect->PartInfo(idx))->fP - (nvect->PartInfo(0))->fP;
        tmomtrans = abs(q4 * q4);
        tmomtrans = tmomtrans / 1000. / 1000.;
        h1->Fill(tmomtrans,weight);
    }else{
        return -1;
    }
    return 0;
}


Int_t
fill_wsq_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    Int_t    idx,ip,mode;
    TLorentzVector q4;
    Double_t wsq;
    idx = 2;
    mode = abs(nvect->Mode);
    if ( mode == 2 ){
        idx = 3;
    }
    ip = abs((nvect->PartInfo(idx))->fPID);
    
    for ( Int_t i = 2 ; i < nvect->Npart() ; i++ ){
        if ((nvect->PartInfo(i))->fIsAlive){
            if ((nvect->Mode ==2 && i>3) || (nvect->Mode !=2 && i>2)) {
                TLorentzVector vecpith = (nvect->PartInfo(i))->fP;
                q4 += vecpith;
            }
        }
    }
    if (isLepton(ip)){//for CC
        wsq = abs(q4.Mag2())/1.e6;
        h1->Fill(wsq,weight);
    }else{
        return -1;
    }
    return 0;
}

Int_t
fill_wres_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    Int_t    ip,mode;
    TLorentzVector q4;
    Double_t wres;
    mode = abs(nvect->Mode);
    
    if (( mode < 11 ) || ( mode > 34  )){
        return 0;
    }
    if (( mode > 13 ) && ( mode < 31 )){
        return 0;
    }
    
    ip = abs((nvect->PartInfo(3))->fPID);
    /* delta absorption check */
    if ((ip == 2224)||( ip == 2214 ) || ( ip == 2114 ) || ( ip == 1114 )){
        return 0;
    }
    q4 = (nvect->PartInfo(3))->fP + (nvect->PartInfo(4))->fP;
    
    wres = sqrt(q4.E() * q4.E() - q4.P()*q4.P());
    
    ip = abs((nvect->PartInfo(4))->fPID);
    if (isPion(ip)){
        h1->Fill(wres/1000.,weight);
    }
    else{
        cout << "IP is not pion " << ip << " mode= " << mode << endl;
        return -1;
    }
    
    return 0;
}

Int_t
fill_wdis_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    Int_t    ip,mode;
    TLorentzVector q4;
    Double_t wdis;
    mode = abs(nvect->Mode);
    
    if (( mode != 21 ) && ( mode != 26 ) && ( mode != 41 ) && (mode != 46) ){
        return 0;
    }
    ip = abs((nvect->PartInfo(3))->fPID);
    /* delta absorption check */
    if ((ip == 2224)||( ip == 2214 ) || ( ip == 2114 ) || ( ip == 1114 )){
        return 0;
    }
    
    for ( int i = 3 ; i < nvect->Nprimary() ; i++ ){
        q4 += (nvect->PartInfo(i))->fP;//
    }
    
    wdis = sqrt(q4.E() * q4.E() - q4.P()*q4.P());
    h1->Fill(wdis/1000.,weight);
    return 0;
}


Int_t
fill_enureco_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    Int_t    idx,ip,mode;
    Double_t enureco;
    idx = 2;
    mode = abs(nvect->Mode);
    if ( mode == 2 ){
        idx = 3;
    }
    ip = abs((nvect->PartInfo(idx))->fPID);
    
    Double_t xmn  = 0.939;
    Double_t xmmu = 0.106;
    Double_t eb   =-0.025;
    Double_t e_mu = (nvect->PartInfo(idx))->fP.E()/1000.;
    Double_t p_mu = (nvect->PartInfo(idx))->fP.P()/1000.;
    Double_t cos_mu = cos((nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(idx))->fP.Vect()));
    
    if (isLepton(ip)){//for CC
        enureco = ((xmn+eb)*e_mu-(2*xmn*eb+eb*eb+xmmu*xmmu)/2)/(xmn+eb-e_mu+p_mu*cos_mu);
        h1->Fill(enureco,weight);
    }else{
        return -1;
    }
    return 0;
}


Int_t
fill_enubias_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    Int_t    idx,ip,mode;
    Double_t enureco;
    idx = 2;
    mode = abs(nvect->Mode);
    if ( mode == 2 ){
        idx = 3;
    }
    ip = abs((nvect->PartInfo(idx))->fPID);
    
    Double_t xmn  = 0.939;
    Double_t xmmu = 0.106;
    Double_t eb   =-0.025;
    Double_t e_mu;
    Double_t p_mu;
    Double_t cos_mu;
    Double_t e_nu;
    Double_t enubias;
    
    if (isLepton(ip)){//for CC
        e_mu = (nvect->PartInfo(idx))->fP.E()/1000.;
        p_mu = (nvect->PartInfo(idx))->fP.P()/1000.;
        cos_mu = cos((nvect->PartInfo(0))->fP.Angle((nvect->PartInfo(idx))->fP.Vect()));
        enureco = ((xmn+eb)*e_mu-(2*xmn*eb+eb*eb+xmmu*xmmu)/2)/(xmn+eb-e_mu+p_mu*cos_mu);
        e_nu = (nvect->PartInfo(0))->fP.E()/1000.;
        enubias = enureco - e_nu;
        h1->Fill(enubias,weight);
    }else{
        return -1;
    }
    return 0;
}



Int_t
fill_q3vsq0_hist(NeutVect *nvect, TH2D *h2, Double_t weight)//index5
{
    Int_t    idx,ip,mode;
    TLorentzVector q4;
    Double_t q0, q3;
    
    idx = 2;
    
    mode = abs(nvect->Mode);
    
    if ( mode == 2 ){
        idx = 3;
    }
    
    ip = abs((nvect->PartInfo(idx))->fPID);
    if (isLepton(ip)){
        q4 =  (nvect->PartInfo(0))->fP - (nvect->PartInfo(idx))->fP;
        q0 = abs(q4.E())/1000.;
        q3 = abs(q4.P())/1000.;
        h2->Fill(q3,q0,weight);
    }else{
        return -1;
    }
    return 0;
}

Int_t
fill_intr_rad(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    int idx, mode, ret;
    
    idx = 2;
    
    mode = abs(nvect->Mode);
    
    if ( mode == 2 ){
        idx = 3;
    }
    
    ret = fill_rad(nvect,idx,h1,weight);
    
}

Int_t
fill_rad_in_pnuc1_mom_hist(NeutVect *nvect, TH2D *h2, TH2D*h22, Double_t weight)
{
    Int_t    ip,mode;
    
    mode = abs(nvect->Mode);
    
    if (( mode == 16 ) || ( mode == 36 )){
        return 0;
    }
    
    ip = (nvect->PartInfo(1))->fPID;
    if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
        ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
        cout << "IP is not nucleon " << ip << " mode= " << mode << endl;
        return -1;
    }
    
    fill_rad_momentum(nvect, 1, h2, weight);
    fill_Evsk(nvect, 1, h22, weight);
    
    return 0;
}

Int_t
fill_rad_out_pnuc1_mom_hist(NeutVect *nvect, TH2D *h2, Double_t weight)
{
    Int_t    idx,ip,mode;
    
    mode = abs(nvect->Mode);
    
    if (( mode == 16 ) || ( mode == 36 )){
        return 0;
    }
    
    if ( abs(mode)==2 ){
        idx = 4;
    }else{
        idx = 3;
    }
    
    ip = (nvect->PartInfo(idx))->fPID;
    if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
        ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
        cout << "IP is not nucleon " << ip << " mode= " << mode << endl;
        return -1;
    }
    
    fill_rad_momentum(nvect, idx, h2, weight);
    
    return 0;
}


////////////////////////////////////////////////////////////////////////////

Int_t
fill_in_dir_costhetaL_nuc1_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    
    Int_t    idx,ip;
    Int_t    mode;
    
    idx = 1;
    
    mode = abs(nvect->Mode);
    
    if (( mode == 16 ) || ( mode == 36 )){
        return 0;
    }
    
    if ( mode == 2 ){
        idx = 2;
    }
    
    ip = (nvect->PartInfo(idx))->fPID;
    if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
        ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
        cout << "IP is not nucleon " << ip << endl;
        return -1;
    }
    
    fill_costhetaL(nvect, idx, h1, weight);
    
    return 0;
}

Int_t
fill_in_dir_costhetaL_nuc2_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    
    Int_t    idx,ip;
    Int_t    mode;
    
    mode = abs(nvect->Mode);
    if ( mode != 2 ){
        return 0;
    }
    
    idx = 2;
    
    ip = (nvect->PartInfo(idx))->fPID;
    if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
        ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
        cout << "IP is not nucleon " << ip << endl;
        return -1;
    }
    
    fill_costhetaL(nvect, idx, h1, weight);
    
    return 0;
}

Int_t
fill_in_dir_phiL_nuc1_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    
    Int_t    idx,ip;
    Int_t    mode;
    
    idx = 1;
    
    mode = abs(nvect->Mode);
    
    if (( mode == 16 ) || ( mode == 36 )){
        return 0;
    }
    
    if ( mode == 2 ){
        idx = 2;
    }
    
    ip = (nvect->PartInfo(idx))->fPID;
    if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
        ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
        cout << "IP is not nucleon " << ip << endl;
        return -1;
    }
    
    fill_phiL(nvect, idx, h1, weight);
    
    return 0;
}

Int_t
fill_in_dir_phiL_nuc2_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    
    Int_t    idx,ip;
    Int_t    mode;
    
    mode = abs(nvect->Mode);
    if ( mode != 2 ){
        return 0;
    }
    
    idx = 2;
    
    ip = (nvect->PartInfo(idx))->fPID;
    if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
        ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
        cout << "IP is not nucleon " << ip << endl;
        return -1;
    }
    
    fill_phiL(nvect, idx, h1, weight);
    
    return 0;
}

Int_t
fill_in_nucs_opening_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    
    Int_t    idx1,idx2,ip;
    Int_t    mode;
    
    mode = abs(nvect->Mode);
    if ( mode != 2 ){
        return 0;
    }
    
    idx1 = 1;
    idx2 = 2;
    
    fill_opening_angle(nvect, idx1, idx2, h1, weight);
    
    return 0;
}

Int_t
fill_out_nucs_opening_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    
    Int_t    idx1,idx2,ip;
    Int_t    mode;
    
    mode = abs(nvect->Mode);
    if ( mode != 2 ){
        return 0;
    }
    
    idx1 = 4;
    idx2 = 5;
    
    fill_opening_angle(nvect, idx1, idx2, h1, weight);
    
    return 0;
}

Int_t
fill_out_dir_costhetaL_nuc1_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    
    Int_t    idx,ip;
    Int_t    mode;
    
    Double_t e1,e2;
    
    idx = 3;
    
    mode = abs(nvect->Mode);
    
    if (( mode == 16 ) || ( mode == 36 )){
        return 0;
    }
    
    if ( mode == 2 ){
        idx = 4;
        e1 = (nvect->PartInfo(4))->fP.E();
        e2 = (nvect->PartInfo(5))->fP.E();
        if ( e1 < e2 ){
            idx = 5;
        }
    }
    
    ip = (nvect->PartInfo(idx))->fPID;
    if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
        ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
        cout << "IP is not nucleon " << ip << endl;
        return -1;
    }
    
    fill_costhetaL(nvect, idx, h1, weight);
    
    return 0;
}

Int_t
fill_out_dir_costhetaL_nuc2_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    /* only for 2p2h interaction */
    
    Int_t    idx,ip,mode;
    
    Double_t e1,e2;
    
    idx = 5;
    
    mode = abs(nvect->Mode);
    
    if ( mode == 2 ){
        e1 = (nvect->PartInfo(4))->fP.E();
        e2 = (nvect->PartInfo(5))->fP.E();
        if ( e1 < e2 ){
            idx = 4;
        }
    }else{
        return 0;
    }
    
    ip = (nvect->PartInfo(idx))->fPID;
    if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
        ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
        cout << "IP is not nucleon " << ip << endl;
        return -1;
    }
    
    fill_costhetaL(nvect, idx, h1, weight);
    
    return 0;
}

Int_t
fill_out_dir_phiL_nuc1_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    
    Int_t    idx,ip;
    Int_t    mode;
    
    Double_t e1,e2;
    
    idx = 3;
    
    mode = abs(nvect->Mode);
    
    if (( mode == 16 ) || ( mode == 36 )){
        return 0;
    }
    
    if ( mode == 2 ){
        idx = 4;
        e1 = (nvect->PartInfo(4))->fP.E();
        e2 = (nvect->PartInfo(5))->fP.E();
        if ( e1 < e2 ){
            idx = 5;
        }
    }
    
    ip = (nvect->PartInfo(idx))->fPID;
    if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
        ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
        cout << "IP is not nucleon " << ip << endl;
        return -1;
    }
    
    fill_phiL(nvect, idx, h1, weight);
    
    return 0;
}

Int_t
fill_out_dir_phiL_nuc2_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    /* only for 2p2h interaction */
    
    Int_t    idx,ip,mode;
    
    Double_t e1,e2;
    
    idx = 5;
    
    mode = abs(nvect->Mode);
    
    if ( mode == 2 ){
        e1 = (nvect->PartInfo(4))->fP.E();
        e2 = (nvect->PartInfo(5))->fP.E();
        if ( e1 < e2 ){
            idx = 4;
        }
    }else{
        return 0;
    }
    
    ip = (nvect->PartInfo(idx))->fPID;
    if (( ip != 2212 ) && ( ip != 2112 ) && ( ip != 3122 ) &&
        ( ip != 2224 ) && ( ip != 2114 ) && ( ip != 1114 )){
        cout << "IP is not nucleon " << ip << endl;
        return -1;
    }
    
    fill_phiL(nvect, idx, h1, weight);
    
    return 0;
}

Int_t
fill_rescat_pnuc1_hist(NeutVect *nvect, TH1D *h1, Double_t weight)
{
    
    Int_t    first_idx,ip,i,idx;
    Int_t    mode;
    
    Double_t e1,e2;
    
    first_idx = 3;
    
    mode = abs(nvect->Mode);
    
    if (( mode == 16 ) || ( mode == 36 )){
        return 0;
    }
    
    if ( mode == 2 ){
        idx = 4;
    }
    
    e1 = 0;
    idx = first_idx;
    for ( i = first_idx; i < nvect->Npart(); i++ ){
        if ((nvect->PartInfo(i))->fIsAlive){
            ip = (nvect->PartInfo(idx))->fPID;
            if (( ip == 2212 ) || ( ip == 2112 )){
                e2 = (nvect->PartInfo(i))->fP.E();
                if ( e2 > e1 ){
                    e1 = e2;
                    idx = i;
                }
            }
        }
    }
    
    fill_momentum(nvect, idx, h1, weight);
    
    return 0;
}


Int_t
fill_histograms(NeutVect *nvect, TH1D *h[][NHIST1D][NFLAVOR], int idx, int ip_idx,
                double xnorm)
{
    
    //  0: neutrino energy
    //  1: momentum of outgoing lepton
    //
    //  2: momentum of initial nucleon #1
    //  3: momentum of initial nucleon #2
    //
    //  4: momentum of scattered nucleon before FSI #1
    //  5: momentum of scattered nucleon before FSI #2
    //
    //  6: scattered angle of lepton
    //  7: q2
    //
    //  8: initial nucleon #1 direction in Lab. ( cos \theta_Lab )
    //  9: initial nucleon #2 direction in Lab. ( cos \theta_Lab )
    ///
    // 10: initial nucleon #1 direction in Lab. ( \phi_Lab )
    // 11: initial nucleon #2 direction in Lab. ( \phi_Lab )
    //
    // 12: outgoing nucleon #1 direction in Lab. ( cos \theta_Lab )
    // 13: outgoing nucleon #2 direction in Lab. ( cos \theta_Lab )
    //
    // 14: outgoing nucleon #1 direction in Lab. ( \phi_Lab )
    // 15: outgoing nucleon #2 direction in Lab. ( \phi_Lab )
    //
    // 16: outgoing nucleon #1 momentum after FSI
    //
    // 17: opening angle of 2 incoming nucleons
    // 18: opening angle of 2 outgoing nucleons
    //
    // 19: interaction position (radius) in nucleus.
    //20: Mode index, useful for topology
    // 21: No of proton
    // 22: No of pion
    //23: t-momentum transfer
    //24: W invariant mass
    //25: reconstruct Energy with CCQE assumed
    //26 Enureco -Enutrue
    
    fill_in_enu_hist(nvect,   h[idx][0][ip_idx], xnorm);
    fill_out_plep_hist(nvect, h[idx][1][ip_idx], xnorm);
    
    fill_in_pnuc1_hist(nvect, h[idx][2][ip_idx], xnorm);
    fill_in_pnuc2_hist(nvect, h[idx][3][ip_idx], xnorm);
    
    fill_out_pnuc1_hist(nvect, h[idx][4][ip_idx], xnorm);
    fill_out_pnuc2_hist(nvect, h[idx][5][ip_idx], xnorm);
    
    fill_coslep_hist(nvect, h[idx][6][ip_idx], xnorm);//need to modify here
    fill_q2_hist(nvect,     h[idx][7][ip_idx], xnorm);
    
    fill_in_dir_costhetaL_nuc1_hist(nvect, h[idx][8][ip_idx], xnorm);
    fill_in_dir_costhetaL_nuc2_hist(nvect, h[idx][9][ip_idx], xnorm);
    
    fill_in_dir_phiL_nuc1_hist(nvect, h[idx][10][ip_idx], xnorm);
    fill_in_dir_phiL_nuc2_hist(nvect, h[idx][11][ip_idx], xnorm);
    
    fill_out_dir_costhetaL_nuc1_hist(nvect, h[idx][12][ip_idx], xnorm);
    fill_out_dir_costhetaL_nuc2_hist(nvect, h[idx][13][ip_idx], xnorm);
    
    fill_out_dir_phiL_nuc1_hist(nvect, h[idx][14][ip_idx], xnorm);
    fill_out_dir_phiL_nuc2_hist(nvect, h[idx][15][ip_idx], xnorm);
    
    fill_rescat_pnuc1_hist(nvect, h[idx][16][ip_idx], xnorm);
    
    fill_in_nucs_opening_hist(nvect, h[idx][17][ip_idx], xnorm);
    fill_out_nucs_opening_hist(nvect, h[idx][18][ip_idx], xnorm);
    
    fill_intr_rad(nvect, h[idx][19][ip_idx], xnorm);
    
    fill_tmomtrans_hist(nvect,  h[idx][23][ip_idx], xnorm);
    fill_wsq_hist(nvect,    h[idx][24][ip_idx], xnorm);
    fill_enureco_hist(nvect,    h[idx][25][ip_idx], xnorm);
    fill_enubias_hist(nvect,    h[idx][26][ip_idx], xnorm);
    
    if(idx!=6)fill_wres_hist(nvect,    h[idx][33][ip_idx], xnorm);
    else fill_wdis_hist(nvect,    h[idx][33][ip_idx], xnorm);//for DIS fill separately
    
    return 0;
}

Int_t
fill_2d_histograms(NeutVect *nvect, TH2D *h[][NHIST2D][NFLAVOR], int idx, int ip_idx,
                   double xnorm)
{
    fill_rad_in_pnuc1_mom_hist(nvect, h[idx][0][ip_idx], h[idx][2][ip_idx], xnorm);
    fill_rad_out_pnuc1_mom_hist(nvect, h[idx][1][ip_idx], xnorm);
    fill_coslepvsP_hist(nvect,h[idx][3][ip_idx], xnorm);
    fill_q3vsq0_hist(nvect,h[idx][4][ip_idx], xnorm);//newadd
    fill_bindingEvsk_hist(nvect,h[idx][5][ip_idx], xnorm);
}


Int_t
load_neut_shared_objects()
{
    return 0;
}

Int_t
basic_histos(char *fname,char *fname_out)
{
    
    gSystem->Load("../neutclass/neutvtx.so");
    gSystem->Load("../neutclass/neutpart.so");
    gSystem->Load("../neutclass/neutfsipart.so");
    gSystem->Load("../neutclass/neutfsivert.so");
    gSystem->Load("../neutclass/neutnucfsistep.so");
    gSystem->Load("../neutclass/neutnucfsivert.so");
    gSystem->Load("../neutclass/neutvect.so");
    
    TFile *f;
    f = new TFile(fname);
    if (f->IsZombie()){
        cout << "Failed to open " << fname << "." << endl;
        return 0;
    }
    
    TFile *f_out;
    f_out = new TFile(fname_out,"RECREATE");
    if (f->IsZombie()){
        cout << "Failed to open " << fname << "." << endl;
        return 0;
    }
    
    TTree  *tn;
    NeutVtx *nvtx;
    NeutVect *nvect;
    
    tn = (TTree *)(f->Get("neuttree"));
    if (tn == 0){
        cout << "Failed to find neut tree in file " << fname << "." << endl;
        return 0;
    }
    
    nvtx = new NeutVtx();
    tn->SetBranchAddress("vertexbranch",&nvtx);
    nvect = new NeutVect();
    tn->SetBranchAddress("vectorbranch",&nvect);
    
    Int_t nevents;
    nevents = tn->GetEntries();
    
    TH1D  *h_flux, *h_rate;
    double flux_integ, rate_integ, rate_norm;
    h_flux = (TH1D *)(f->Get("fluxhisto"));
    if ( h_flux != 0 ){
        flux_integ = h_flux->GetSumOfWeights();
    }
    h_rate = (TH1D *)(f->Get("ratehisto"));
    if ( h_rate != 0 ){
        rate_integ = h_rate->GetSumOfWeights();
    }else{
        rate_integ = (double)(nevents);
    }
    cout << " flux_sum = " << flux_integ << endl;
    cout << " rate_sum = " << rate_integ << endl;
    
    rate_norm = rate_integ/(double)(nevents);
    
    cout << " rate_norm = " << rate_norm << endl;
    //const int NFLAVOR = 6;
    //const int NHIST1D = 27;
    //const int NCHANNEL = 11;//12?
    TH1D *h_combined[NCHANNEL][NHIST1D][NFLAVOR];//20to27
    //const int NHIST2D = 8;
    TH2D *h_2d_combined[12][NHIST2D][NFLAVOR];//2nd index: 3rd is Evsk for in nuclear 4th is coslepvsP, 5th is bindingEvsk; 6 is iniPion cosvsP, 7 finalPion cosvsP
    TH1D *h_indiv[60][20][NFLAVOR];
    TH1D *h_modes;
    //9 is CCCoh, 10 topo0pi, 11 topo1pi, 12 topoNpi
    char hist_kind[NCHANNEL][16]={"all\0"    ,"CCall\0"    ,"NCall\0",
        "CCQE\0"   ,"CCMEC\0"    ,"CC1pi\0",
        "CCDIS\0","CCCOH\0","CCtopo0pi\0","CCtopo1pi\0","CCtopoNpi\0"/*,"res11\0","res12\0","res13\0","dis21\0","dis26\0"*/};
    //20to25
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
    
    char hist_type_2d[NHIST2D][16]={"in_nuc1_p_rad\0","out_nuc1_p_rad\0","in_nuc1_Evsk\0","coslepvsP\0","q3vsq0\0","bindEvsk\0","initPicosvsP\0","finPicosvsP\0"};//newadd
    
    char flavor_str[NFLAVOR][16]={"nue\0"  ,"numu\0"    ,"nutau\0",
        "nue_bar" ,"numu_bar\0","nutau_bar\0"};
    //3 is innucleonEvsk, 4 is coslepvsP, 5 is q3vsq0
    int h_bins_2d_1[NHIST2D]={100,100,100,100,100,100,100,100};
    int h_bins_2d_2[NHIST2D]={100,500,100,100,100,100,100,100};
    Double_t h_min_2d_1[NHIST2D] ={ 0., 0.,0.,-1.0,0.,0.,-1.,-1.};
    Double_t h_max_2d_1[NHIST2D] ={10.,10.,2.,1.0,1.2,1.0,1.,1.};
    Double_t h_min_2d_2[NHIST2D] ={ 0., 0.,0.,0.,0.,0.,0.,0.};
    Double_t h_max_2d_2[NHIST2D] ={ 1., 5.,2.,2.,1.2,0.5,2.,2.};
    
    int       h_bins[NHIST1D]={
        1200, 1200,  100,
        100,  500,  500,
        50,   1200,	  50,
        50,     50,   50,
        50,     50  ,
        50,     50  ,
        500,
        50,     50  ,100,
        110,  10, 10,
        100,  500,    100,    100,
        100, 100, 100, 100, 100, 100,500
    };
    
    Double_t  h_min[NHIST1D] ={
        0.  ,  0.  ,  0.,
        0.  ,  0.  ,  0.,
        -1.  ,0.  , -1.,
        -1.  , -3.14, -3.14,
        -1.  , -1.  ,
        -3.14, -3.14,
        0.  , -1.  , -1.,
        0.,
        -55, 0,   0,
        0.,   0.,  0., -0.5,
        0., -1., 0., -1., -1., -1.,0.
    };
    
    Double_t  h_max[NHIST1D] ={
        30. , 30.  ,    1.,
        1.  ,  5.  ,    5.,
        1.,    30.  ,    1.,
        1.,    3.14,    3.14,
        1.,    1.  ,
        3.14,  3.14,
        5.,    1.  ,    1.,
        10.,
        55,   10, 10,
        0.5,  10.0,    2.0, 0.5,
        2., 1., 2., 1., 1., 1., 5.
    };
    
    char hist_name[128],hist_title[128];
    
    Int_t i, j, k;
    
    f_out->cd();
    h_flux->Write();//newadd
    h_rate->Write();//newadd
    h_modes = new TH1D("neut_modes","Neut interaction modes",
                       121,-60.5,60.5);
    
    for ( i = 0 ; i < NCHANNEL ; i++ ){//change to 11
        for ( j = 0 ; j < NHIST1D ; j++ ){ /* histogram type */
            for ( k = 0 ; k < NFLAVOR ; k++ ){ /* flavor */
                snprintf(hist_name,sizeof(hist_name),
                         "h_%s_%s_%s",hist_kind[i],hist_type[j],flavor_str[k]);
                snprintf(hist_title,sizeof(hist_title),"%s %s %s",
                         hist_type[j],hist_kind[i],flavor_str[k]);
                h_combined[i][j][k]
                =new TH1D(hist_name,hist_title,h_bins[j],h_min[j],h_max[j]);
            }
        }
        for ( j = 0 ; j < NHIST2D ; j++ ){//newadd
            for ( k = 0 ; k < NFLAVOR ; k++ ){ /* flavor */
                snprintf(hist_name,sizeof(hist_name),
                         "h_%s_%s_%s",hist_kind[i],hist_type_2d[j],flavor_str[k]);
                snprintf(hist_title,sizeof(hist_title),"%s %s %s",
                         hist_type_2d[j],hist_kind[i],flavor_str[k]);
                h_2d_combined[i][j][k]
                =new TH2D(hist_name,hist_title,
                          h_bins_2d_1[j],h_min_2d_1[j],h_max_2d_1[j],
                          h_bins_2d_2[j],h_min_2d_2[j],h_max_2d_2[j]);
            }
        }
    }
    
    //  for ( i = 0 ; i < 60 ; i++ ){
    //	for ( j = 0 ; j <19 ; j++ ){ /* histogram type */
    //	  for ( k = 0 ; k < 6 ; k++ ){ /* flavor */
    //		snprintf(hist_name,sizeof(hist_name),
    //				 "h_mode_%.2d_%s_%s",i,hist_type[j],flavor_str[k]);
    //		snprintf(hist_title,sizeof(hist_title),"%s (mode=%2d) %s",
    //				 hist_type[i],i,flavor_str[j]);
    //		h_indiv[i][j][k]
    //		  =new TH1D(hist_name,hist_title,h_bins[j],h_min[j],h_max[j]);
    //	  }
    //	}
    //  }
    
    int nev,iflv,ip,ip_idx,mode, npion, npionany, nproton;
    const int flavor_id[NFLAVOR]={12,14,16,-12,-14,-16};
    
    for ( nev = 0 ; nev < nevents ; nev++ ){
        
        if ((nev % 10000) == 0){
            cout << "Processing event #" << nev << endl;
        }
        
        tn->GetEntry(nev);
        
        ip = (nvect->PartInfo(0))->fPID;
        for ( ip_idx = 0 ; ip_idx < 6 ; ip_idx++ ){
            if (ip == flavor_id[ip_idx]){
                break;
            }
        }
        if ( ip_idx == 6 ){
            cout <<
            "event " << nev <<
            ":ip for #1 is not neutrino but "<< ip <<
            endl;
            return 1;
        }
        
        mode = nvect->Mode;
        //to count No of pion for CC.
        npion = 0;
	npionany = 0;
        nproton = 0;
        //if (abs(nvect->Mode) <30){
        if (abs(nvect->Mode) <30){
            //for ( Int_t i = nvect->Nprimary() ; i < nvect->Npart() ; i++ ){
            for ( Int_t i = 2 ; i < nvect->Npart() ; i++ ){
                if ((nvect->PartInfo(i))->fIsAlive){
                    //if(abs((nvect->PartInfo(i))->fPID) == 211 || (nvect->PartInfo(i))->fPID == 111){ // And here, it's a pion,
                   if(abs((nvect->PartInfo(i))->fPID) == 211 || (nvect->PartInfo(i))->fPID == 111){
			npionany +=1;} 
		   if((nvect->PartInfo(i))->fPID == -211){//pi minus for antinu run
			    npion +=1;//check number of pion
                    }
                    if((nvect->PartInfo(i))->fPID == 2212){ // And here, it's a proton, this is awesome !
                        nproton +=1;//check number of proton
                    }
                }
            }
            
        }
        else {
            npion = -1;//for NC
            nproton = -1;
        }
        
        
        
        h_modes->Fill(double(mode),1.);
        /* all = 0 */
        fill_histograms(nvect,h_combined,0,ip_idx,rate_norm);
        fill_2d_histograms(nvect,h_2d_combined,0,ip_idx,rate_norm);
        fill_numode_hist(h_combined[0][20][ip_idx],rate_norm,mode);
        fill_nproton_hist(h_combined[0][21][ip_idx],rate_norm,nproton);
        fill_npion_hist(h_combined[0][22][ip_idx],rate_norm,npion);
        fill_out_ppiINI_hist(nvect,h_combined[0][27][ip_idx],h_combined[0][28][ip_idx],h_2d_combined[0][6][ip_idx],rate_norm);
        fill_out_ppiFSI_hist(nvect,h_combined[0][29][ip_idx],h_combined[0][30][ip_idx],h_combined[0][31][ip_idx],h_combined[0][32][ip_idx],h_2d_combined[0][7][ip_idx],rate_norm);
        if ( isCC(mode) ){
            fill_histograms(nvect,h_combined,1,ip_idx,rate_norm);
            fill_2d_histograms(nvect,h_2d_combined,1,ip_idx,rate_norm);
            fill_numode_hist(h_combined[1][20][ip_idx],rate_norm,mode);
            fill_nproton_hist(h_combined[1][21][ip_idx],rate_norm,nproton);
            fill_npion_hist(h_combined[1][22][ip_idx],rate_norm,npion);
            fill_out_ppiINI_hist(nvect,h_combined[1][27][ip_idx],h_combined[1][28][ip_idx],h_2d_combined[1][6][ip_idx],rate_norm);
            fill_out_ppiFSI_hist(nvect,h_combined[1][29][ip_idx],h_combined[1][30][ip_idx],h_combined[1][31][ip_idx],h_combined[1][32][ip_idx],h_2d_combined[1][7][ip_idx],rate_norm);
        }
        if ( isNC(mode) ){
            fill_histograms(nvect,h_combined,2,ip_idx,rate_norm);
            fill_2d_histograms(nvect,h_2d_combined,2,ip_idx,rate_norm);
            fill_numode_hist(h_combined[2][20][ip_idx],rate_norm,mode);
            fill_nproton_hist(h_combined[2][21][ip_idx],rate_norm,nproton);
            fill_npion_hist(h_combined[2][22][ip_idx],rate_norm,npion);
            fill_out_ppiINI_hist(nvect,h_combined[2][27][ip_idx],h_combined[2][28][ip_idx],h_2d_combined[2][6][ip_idx],rate_norm);
            fill_out_ppiFSI_hist(nvect,h_combined[2][29][ip_idx],h_combined[2][30][ip_idx],h_combined[2][31][ip_idx],h_combined[2][32][ip_idx],h_2d_combined[2][7][ip_idx],rate_norm);
        }
        if ( (abs(mode)==1) ){
            fill_histograms(nvect,h_combined,3,ip_idx,rate_norm);
            fill_2d_histograms(nvect,h_2d_combined,3,ip_idx,rate_norm);
            fill_numode_hist(h_combined[3][20][ip_idx],rate_norm,mode);
            fill_nproton_hist(h_combined[3][21][ip_idx],rate_norm,nproton);
            fill_npion_hist(h_combined[3][22][ip_idx],rate_norm,npion);
            fill_out_ppiINI_hist(nvect,h_combined[3][27][ip_idx],h_combined[3][28][ip_idx],h_2d_combined[3][6][ip_idx],rate_norm);
            fill_out_ppiFSI_hist(nvect,h_combined[3][29][ip_idx],h_combined[3][30][ip_idx],h_combined[3][31][ip_idx],h_combined[3][32][ip_idx],h_2d_combined[3][7][ip_idx],rate_norm);
        }
        if ( (abs(mode)==2) ){
            fill_histograms(nvect,h_combined,4,ip_idx,rate_norm);
            fill_2d_histograms(nvect,h_2d_combined,4,ip_idx,rate_norm);
            fill_numode_hist(h_combined[4][20][ip_idx],rate_norm,mode);
            fill_nproton_hist(h_combined[4][21][ip_idx],rate_norm,nproton);
            fill_npion_hist(h_combined[4][22][ip_idx],rate_norm,npion);
            fill_out_ppiINI_hist(nvect,h_combined[4][27][ip_idx],h_combined[4][28][ip_idx],h_2d_combined[4][6][ip_idx],rate_norm);
            fill_out_ppiFSI_hist(nvect,h_combined[4][29][ip_idx],h_combined[4][30][ip_idx],h_combined[4][31][ip_idx],h_combined[4][32][ip_idx],h_2d_combined[4][7][ip_idx],rate_norm);
        }
        if ( isCC1pi(mode) ){
            fill_histograms(nvect,h_combined,5,ip_idx,rate_norm);
            fill_2d_histograms(nvect,h_2d_combined,5,ip_idx,rate_norm);
            fill_numode_hist(h_combined[5][20][ip_idx],rate_norm,mode);
            fill_nproton_hist(h_combined[5][21][ip_idx],rate_norm,nproton);
            fill_npion_hist(h_combined[5][22][ip_idx],rate_norm,npion);
            fill_out_ppiINI_hist(nvect,h_combined[5][27][ip_idx],h_combined[5][28][ip_idx],h_2d_combined[5][6][ip_idx],rate_norm);
            fill_out_ppiFSI_hist(nvect,h_combined[5][29][ip_idx],h_combined[5][30][ip_idx],h_combined[5][31][ip_idx],h_combined[5][32][ip_idx],h_2d_combined[5][7][ip_idx],rate_norm);
        }
        if ( isCCdis(mode) ){
            fill_histograms(nvect,h_combined,6,ip_idx,rate_norm);
            fill_2d_histograms(nvect,h_2d_combined,6,ip_idx,rate_norm);
            fill_numode_hist(h_combined[6][20][ip_idx],rate_norm,mode);
            //fill_nproton_hist(h_combined[6][21][ip_idx],rate_norm,nproton); //For DIS, nproton is replaced with No. of primary pion
            fill_npion_hist(h_combined[6][22][ip_idx],rate_norm,npion);
            fill_out_dispiINI_hist(nvect,h_combined[6][27][ip_idx],h_combined[6][28][ip_idx],h_combined[6][21][ip_idx],h_2d_combined[6][6][ip_idx],rate_norm);
            //ingore 31 32 index for TH1
            fill_out_dispiFSI_hist(nvect,h_combined[6][29][ip_idx],h_combined[6][30][ip_idx],h_2d_combined[6][7][ip_idx],rate_norm);
        }
        //newadd
        if ( isCCcoh(mode) ){
            fill_histograms(nvect,h_combined,7,ip_idx,rate_norm);
            fill_2d_histograms(nvect,h_2d_combined,7,ip_idx,rate_norm);
            fill_numode_hist(h_combined[7][20][ip_idx],rate_norm,mode);
            fill_nproton_hist(h_combined[7][21][ip_idx],rate_norm,nproton);
            fill_npion_hist(h_combined[7][22][ip_idx],rate_norm,npion);
            //for coherent pion primary is similar to pion FSI
            fill_out_cohpi_hist(nvect,h_combined[7][27][ip_idx],h_combined[7][28][ip_idx],h_2d_combined[7][6][ip_idx],rate_norm);
            //ignore 31 32 index for TH1
            fill_out_cohpi_hist(nvect,h_combined[7][29][ip_idx],h_combined[7][30][ip_idx],h_2d_combined[7][7][ip_idx],rate_norm);
        }
        
        //if ( isCCtopo0pi(npion,mode) ){
	if ( isCCtopo0pi(npionany,mode) ){
            fill_histograms(nvect,h_combined,8,ip_idx,rate_norm);
            fill_2d_histograms(nvect,h_2d_combined,8,ip_idx,rate_norm);
            fill_numode_hist(h_combined[8][20][ip_idx],rate_norm,mode);
            fill_nproton_hist(h_combined[8][21][ip_idx],rate_norm,nproton);
            fill_npion_hist(h_combined[8][22][ip_idx],rate_norm,npion);
            fill_out_ppiINI_hist(nvect,h_combined[8][27][ip_idx],h_combined[8][28][ip_idx],h_2d_combined[8][6][ip_idx],rate_norm);
            fill_out_ppiFSI_hist(nvect,h_combined[8][29][ip_idx],h_combined[8][30][ip_idx],h_combined[8][31][ip_idx],h_combined[8][32][ip_idx],h_2d_combined[8][7][ip_idx],rate_norm);
        }
        
        if ( isCCtopo1pi(npion,mode) ){
            fill_histograms(nvect,h_combined,9,ip_idx,rate_norm);
            fill_2d_histograms(nvect,h_2d_combined,9,ip_idx,rate_norm);
            fill_numode_hist(h_combined[9][20][ip_idx],rate_norm,mode);
            fill_nproton_hist(h_combined[9][21][ip_idx],rate_norm,nproton);
            fill_npion_hist(h_combined[9][22][ip_idx],rate_norm,npion);
            fill_out_ppiINI_hist(nvect,h_combined[9][27][ip_idx],h_combined[9][28][ip_idx],h_2d_combined[9][6][ip_idx],rate_norm);
            fill_out_ppiFSI_hist(nvect,h_combined[9][29][ip_idx],h_combined[9][30][ip_idx],h_combined[9][31][ip_idx],h_combined[9][32][ip_idx],h_2d_combined[9][7][ip_idx],rate_norm);
         }
        
        if ( isCCtopoNpi(npion,mode) ){
            fill_histograms(nvect,h_combined,10,ip_idx,rate_norm);
            fill_2d_histograms(nvect,h_2d_combined,10,ip_idx,rate_norm);
            fill_numode_hist(h_combined[10][20][ip_idx],rate_norm,mode);
            fill_nproton_hist(h_combined[10][21][ip_idx],rate_norm,nproton);
            fill_npion_hist(h_combined[10][22][ip_idx],rate_norm,npion);
            fill_out_ppiINI_hist(nvect,h_combined[10][27][ip_idx],h_combined[10][28][ip_idx],h_2d_combined[10][6][ip_idx],rate_norm);
            fill_out_ppiFSI_hist(nvect,h_combined[10][29][ip_idx],h_combined[10][30][ip_idx],h_combined[10][31][ip_idx],h_combined[10][32][ip_idx],h_2d_combined[10][7][ip_idx],rate_norm);
        }
        
        /*if ( isCC1pi11(mode) ){
         fill_histograms(nvect,h_combined,11,ip_idx,rate_norm);
         fill_2d_histograms(nvect,h_2d_combined,11,ip_idx,rate_norm);
         fill_numode_hist(h_combined[11][20][ip_idx],rate_norm,mode);
         fill_nproton_hist(h_combined[11][21][ip_idx],rate_norm,nproton);
         fill_npion_hist(h_combined[11][22][ip_idx],rate_norm,npion);
         fill_out_ppiINI_hist(nvect,h_combined[11][27][ip_idx],h_combined[11][28][ip_idx],h_2d_combined[11][6][ip_idx],rate_norm);
         fill_out_ppiFSI_hist(nvect,h_combined[11][29][ip_idx],h_combined[11][30][ip_idx],h_combined[11][31][ip_idx],h_combined[11][32][ip_idx],h_2d_combined[11][7][ip_idx],rate_norm);
         }
         
         if ( isCC1pi12(mode) ){
         fill_histograms(nvect,h_combined,12,ip_idx,rate_norm);
         fill_2d_histograms(nvect,h_2d_combined,12,ip_idx,rate_norm);
         fill_numode_hist(h_combined[12][20][ip_idx],rate_norm,mode);
         fill_nproton_hist(h_combined[12][21][ip_idx],rate_norm,nproton);
         fill_npion_hist(h_combined[12][22][ip_idx],rate_norm,npion);
         fill_out_ppiINI_hist(nvect,h_combined[12][27][ip_idx],h_combined[12][28][ip_idx],h_2d_combined[12][6][ip_idx],rate_norm);
         fill_out_ppiFSI_hist(nvect,h_combined[12][29][ip_idx],h_combined[12][30][ip_idx],h_combined[12][31][ip_idx],h_combined[12][32][ip_idx],h_2d_combined[12][7][ip_idx],rate_norm);
         }
         
         if ( isCC1pi13(mode) ){
         fill_histograms(nvect,h_combined,13,ip_idx,rate_norm);
         fill_2d_histograms(nvect,h_2d_combined,13,ip_idx,rate_norm);
         fill_numode_hist(h_combined[13][20][ip_idx],rate_norm,mode);
         fill_nproton_hist(h_combined[13][21][ip_idx],rate_norm,nproton);
         fill_npion_hist(h_combined[13][22][ip_idx],rate_norm,npion);
         fill_out_ppiINI_hist(nvect,h_combined[13][27][ip_idx],h_combined[13][28][ip_idx],h_2d_combined[13][6][ip_idx],rate_norm);
         fill_out_ppiFSI_hist(nvect,h_combined[13][29][ip_idx],h_combined[13][30][ip_idx],h_combined[13][31][ip_idx],h_combined[13][32][ip_idx],h_2d_combined[13][7][ip_idx],rate_norm);
         }
         
         if ( isCCdis21(mode) ){
         fill_histograms(nvect,h_combined,14,ip_idx,rate_norm);
         fill_2d_histograms(nvect,h_2d_combined,14,ip_idx,rate_norm);
         fill_numode_hist(h_combined[14][20][ip_idx],rate_norm,mode);
         fill_nproton_hist(h_combined[14][21][ip_idx],rate_norm,nproton);
         fill_npion_hist(h_combined[14][22][ip_idx],rate_norm,npion);
         fill_out_ppiINI_hist(nvect,h_combined[14][27][ip_idx],h_combined[14][28][ip_idx],h_2d_combined[14][6][ip_idx],rate_norm);
         fill_out_ppiFSI_hist(nvect,h_combined[14][29][ip_idx],h_combined[14][30][ip_idx],h_combined[14][31][ip_idx],h_combined[14][32][ip_idx],h_2d_combined[14][7][ip_idx],rate_norm);
         }
         
         if ( isCCdis26(mode) ){
         fill_histograms(nvect,h_combined,15,ip_idx,rate_norm);
         fill_2d_histograms(nvect,h_2d_combined,15,ip_idx,rate_norm);
         fill_numode_hist(h_combined[15][20][ip_idx],rate_norm,mode);
         fill_nproton_hist(h_combined[15][21][ip_idx],rate_norm,nproton);
         fill_npion_hist(h_combined[15][22][ip_idx],rate_norm,npion);
         fill_out_ppiINI_hist(nvect,h_combined[15][27][ip_idx],h_combined[15][28][ip_idx],h_2d_combined[15][6][ip_idx],rate_norm);
         fill_out_ppiFSI_hist(nvect,h_combined[15][29][ip_idx],h_combined[15][30][ip_idx],h_combined[15][31][ip_idx],h_combined[15][32][ip_idx],h_2d_combined[15][7][ip_idx],rate_norm);
         }*/
        
        /*for ( i = 0 ; i < 11 ; i++ ){//change to 11
         for ( k = 0 ; k < 6 ; k++ ){ //flavor
         fill_numode_hist(nvect,h_combined[i][19][k]);
         }
         }*/
        
        
    }
    
    for ( i = 0 ; i < NCHANNEL ; i++ ){
        for ( j = 0 ; j < NHIST1D ; j++ ){ /* histogram type */
            for ( k = 0 ; k < NFLAVOR ; k++ ){ /* flavor */
                if ( h_combined[i][j][k]->GetEntries() == 0 ){
                    delete h_combined[i][j][k];
                }
            }
        }
        for ( j = 0 ; j < NHIST2D ; j++ ){ /* histogram type *///newadd
            for ( k = 0 ; k < NFLAVOR ; k++ ){ /* flavor */
                if ( h_2d_combined[i][j][k]->GetEntries() == 0 ){
                    delete h_2d_combined[i][j][k];
                }
            }
        }
    }
    
    
    f_out->Write();
    f_out->Close();
    return 0;
}

/*
 cout << "Event #        :" << nvect->EventNo << "\n";
 cout << "Target A       :" << nvect->TargetA << "\n";
 cout << "Target Z       :" << nvect->TargetA << "\n";
 cout << "VNuclIni       :" << nvect->VNuclIni << "\n";
 cout << "VNuclFin       :" << nvect->VNuclFin << "\n";
 cout << "PF Surface     :" << nvect->PFSurf   << "\n";
 cout << "PF Maximum     :" << nvect->PFMax    << "\n";
 cout << "Flux ID        :" << nvect->FluxID   << "\n";
 cout << "Intr. mode     :" << nvect->Mode   << "\n";
 
 cout << "Vertex         =" << nvect->VertexID(i) << "\n";
 cout << "Parent Index   =" << nvect->ParentIdx(i) << "\n";
 
 cout << "Particle Code  = " << (nvect->PartInfo(i))->fPID   << "\n";
 cout << "Particle Mass  = " << (nvect->PartInfo(i))->fMass   << "\n";
 cout << "Particle Mom.  =(" << (nvect->PartInfo(i))->fP.Px() << ","
 << (nvect->PartInfo(i))->fP.Py() << ","
 << (nvect->PartInfo(i))->fP.Pz() << ","
 << (nvect->PartInfo(i))->fP.E()  << ")"
 << "\n";
 cout << "Particle Flag  = " << (nvect->PartInfo(i))->fIsAlive << "\n";
 cout << "Particle Stat. = " << (nvect->PartInfo(i))->fStatus  << "\n";
 cout << "Particle Pos(1)=(" << (nvect->PartInfo(i))->fPosIni.X() << ","
 << (nvect->PartInfo(i))->fPosIni.Y() << ","
 << (nvect->PartInfo(i))->fPosIni.Z() << ","
 << (nvect->PartInfo(i))->fPosIni.T()  << ")"
 << "\n";
 cout << "Particle Pos(2)=(" << (nvect->PartInfo(i))->fPosFin.Px() << ","
 << (nvect->PartInfo(i))->fPosFin.Y() << ","
 << (nvect->PartInfo(i))->fPosFin.Z() << ","
 << (nvect->PartInfo(i))->fPosFin.T()  << ")"
 << "\n";
 }
 std::cout << "Event #" << nvtx->EventNo << "\n";
 
 for (i = 0 ; i < nvtx->Nvtx() ; i++){
 cout << "i=" << i << "\n";
 
 cout << "Vertex Pos(1)=(" << (nvtx->Pos(i))->X() << ","
 << (nvtx->Pos(i))->Y() << ","
 << (nvtx->Pos(i))->Z() << ","
 << (nvtx->Pos(i))->T()  << ")"
 << "\n";
 }
 */


int
main(int argc, char **argv)
{
    if ( argc < 3 ){
        cout << "need input filename and output filename" << endl;
        exit(0);
    }
    
    basic_histos(argv[1],argv[2]);
    
}
