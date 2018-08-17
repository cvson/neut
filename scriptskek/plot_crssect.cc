#include <TFile.h>
#include <TTree.h>

int
openinputfiles(char *fname1, char *fname2, TFile **f1, TFile **f2)
{
  
  *f1 = new TFile(fname1);
  *f2 = new TFile(fname2);

  if ( (*f1)->IsZombie() ){
	return -1;
  }
  if ( (*f2)->IsZombie() ){
	return -2;
  }

}

int
openoutputfiles(char *fname_out, TFile **fout)
{

  *fout = new TFile(fname_out,RECREATE);
  if ( *fout->Zombie() ){
	return;
  }

}  

int
getcrstrees(TFile *f1, TFile *f2, TTree **t1, TTree **t2)
{

  *t1 = ( TTree * )f1->Get("crssect");
  *t2 = ( TTree * )f2->Get("crssect");

  if ( *t1 == 0 ){
	return -1;
  }
	
  if ( *t2 == 0 ){
	return -2;
  }  

  return 0;
}

int
getcrsbranches(TTree *t, TBranch **b_enu, TBranch **b_crs)
{
  
  *b_enu = t->GetBranch("enu");
  if ( *b_enu == 0 ){
	return -1;
  }

  *b_crs = t->GetBranch("crssect");
  if ( *b_crs == 0 ){
	return -2;
  }

  return 0;
}

int
setcrsbranchaddrs(TBranch *b_enu, TBranch *b_crs, 
				  Float_t *Enu,   Float_t *crssect[6][60])
{
  
  b_enu->SetAddress(Enu);

  b_crs->SetAddress(crssect);

  return 0;
}

int
makenewcrstree(TTree **t, 
			   Float_t *Enu, Float_t *crssect[2][6][60])
{
  *t = new TTree("crssect","Cross section table");
  if (*t == 0){
	return -1;
  }

  t->Branch("enu",Enu,"Enu");
  t->Branch("crssect",crssect,"crssect[2][6][60]");
  
  return 0;

}

TH2F *
adjust_axis(TH2F *h2f)
{

  TH2F *h2f_ret;
  Float_t xmin,xmax,ymin,ymax;

  //  xmin = h2f->GetXaxis()->GetXmin();
  xmax = h2f->GetXaxis()->GetXmax();
  //  ymin = h2f->GetYaxis()->GetXmin();
  ymax = h2f->GetYaxis()->GetXmax();

  h2f_ret = new TH2F("test","frame",1,0,xmax,1,0,ymax);
  h2f_ret->SetStats(kFALSE);

  return h2f_ret;
}


void 
make_plots(TTree *t1)
{
  TCanvas *c1;
  TPad    *p;
  TH2F    *h2f;
  TFrame  *fr;

  int flv_tbl[6]={12,14,16,-12,-14,-16};
  int iflv = 1; // 0 : nue , 1 : numu , 2 : nutau, 3.. anti 
  int imode;

  c1 = new TCanvas("cross-section");
  c1->Divide(2,2);

  for ( imode = 1 ; imode < 3 ; imode++ ){
	for ( iflv = 0 ; iflv < 6 ; iflv++ ){
	
	  char title[256];
	  char varexp1[256], varexp2[256];
	  char selection[256];
	
	  snprintf(title,sizeof(title),"flavor %d mode %d",
			   flv_tbl[iflv],imode);
	
	  //////////////////////
	
	  p = (TPad *)c1->cd(1);
	
	  snprintf(varexp1,  sizeof(varexp1),  "crssect[%d][%d]:Enu",
			   iflv, imode);
	  snprintf(varexp2,  sizeof(varexp2),  "T2.%s", varexp1);
	
	  snprintf(selection,sizeof(selection),"(Enu<10)&&(Enu>0.1)");
	
	  t1->SetLineColor(kRed);
	  t1->Draw(varexp1,selection,"LINE");
	
	  t1->SetLineColor(kBlue);
	  t1->Draw(varexp2,selection,"LINE,SAME");
	
	  h2f = (TH2F *)p->GetPrimitive("htemp");
	  h2f->SetTitle(title);
	  h2f->GetXaxis()->SetTitle("E_{#nu}");
	  h2f->GetYaxis()->SetTitle("cross-section (10^{-38}cm^{2})");
	
	  c1->Update();
	
	  //////////////////////
	
	  p = (TPad *)c1->cd(2);
	
	  snprintf(varexp1,  sizeof(varexp1),  "crssect[%d][%d]:Enu",
			   iflv, imode);
	  snprintf(varexp2,  sizeof(varexp2),  "T2.%s", varexp1);
	
	  snprintf(selection,sizeof(selection),"(Enu<1.)&&(Enu>0.1)");
	
	  t1->SetLineColor(kRed);
	  t1->Draw(varexp1,selection,"LINE");
	
	  h2f =adjust_axis((TH2F *)(p->GetPrimitive("htemp")));
	  h2f->SetTitle(title);
	  h2f->GetXaxis()->SetTitle("E_{#nu}");
	  h2f->GetYaxis()->SetTitle("cross-section (10^{-38}cm^{2})");
	
	  h2f->Draw();
	
	  t1->SetLineColor(kRed);
	  t1->Draw(varexp1,selection,"LINE,SAME");
	
	  t1->SetLineColor(kBlue);
	  t1->Draw(varexp2,selection,"LINE,SAME");
	  c1->Update();
	
	  //////////////////////
	
	
	  p = (TPad *)c1->cd(3);
	
	  snprintf(varexp1,  sizeof(varexp1),  
			   "T2.crssect[%d][%d]/crssect[%d][%d]:Enu",
			   iflv, imode, iflv, imode);
	
	  snprintf(selection,sizeof(selection),"(Enu<10.)&&(Enu>0.1)");
	
	  t1->SetLineColor(kBlack);  
	  t1->Draw(varexp1, selection, "LINE");
	
	  h2f = (TH2F *)p->GetPrimitive("htemp");
	  h2f->SetTitle(title);
	  h2f->GetXaxis()->SetTitle("E_{#nu}");
	  h2f->GetYaxis()->SetTitle("cross-section ratio");
	
	  c1->Update();
	
	  //////////////////////
	
	  p = (TPad *)c1->cd(4);
	
	  snprintf(varexp1,  sizeof(varexp1),  
			   "T2.crssect[%d][%d]/crssect[%d][%d]:Enu",
			   iflv, imode, iflv, imode);
	
	  snprintf(selection,sizeof(selection),"(Enu<1.)&&(Enu>0.1)");
	
	  t1->SetLineColor(kBlack);  
	  t1->Draw(varexp1, selection, "LINE");
	
	  h2f =adjust_axis((TH2F *)(p->GetPrimitive("htemp")));
	  h2f->SetTitle(title);
	  h2f->GetXaxis()->SetTitle("E_{#nu}");
	  h2f->GetYaxis()->SetTitle("cross-section ratio");
	
	  c1->Update();
	
	  //  c1->ls();
	
	  //////////////////////
	  char fname[1024];
	  snprintf(fname,sizeof(fname),"flavor_%2d_mode_%.2d.png",
			   flv_tbl[iflv],imode);
	  c1->Print(fname);
	
	}
  }
  return;
}

/*
void
plot_crssect(char *fname1, char *fname2, char *fname_out)
*/
void
plot_crssect(char *fname1, char *fname2)
{
  int retval;

  TFile *f1, *f2;

  retval = openinputfiles(fname1,fname2,&f1,&f2);
  if (retval < 0 ){
	return retval;
  }

  TTree *t1, *t2;
  retval = getcrstrees(f1,f2,&t1,&t2);
  if (retval < 0 ){
	return retval;
  }

  t1->AddFriend(t2,"T2");

  make_plots(t1);

}




/*
  TBranch *b1_enu,*b1_crs;
  TBranch *b2_enu,*b2_crs;

  retval = getcrsbranches(t1,&b1_enu,&b1_crs);
  if (retval < 0 ){
	return retval;
  }
  retval = getcrsbranches(t2,&b2_enu,&b2_crs);
  if (retval < 0 ){
	return retval;
  }
	
  Float_t Enu1,crssect1[6][60];
  Float_t Enu2,crssect2[6][60];

  setcrsbranchaddrs(b1_enu, b1_crs, &Enu1, &crssect1);
  setcrsbranchaddrs(b2_enu, b2_crs, &Enu2, &crssect2);

  ////////////////////////////////////////
  TFile *f_out;
  retval = openoutputfiles(fname_out,&f_out);
  if (retval < 0 ){
	return retval;
  }

  f_out->cd();

  TTree *t_out;
  Float_t Enu, crssect[2][6][60];
  TBranch *bout_enu, *bout_crs1, *bout_crs2;

  retval = makenewcrstree(&t_out, &Enu, &crssect);
  if (retval < 0 ){
	return retval;
  }

  Int_t nentries;

  nentries = (Int_t)t1->GetEntries();

  Int_t i;
  for ( i = 0 ; i < nentries ; i++ ){
	t1->GetEntry(i);
	t2->GetEntry(i);
	for ( j = 0 ; j < 6 ; j++ ){
	  for ( k = 0 ; k < 60 ; k++ ){
		crssect[0][j][k] = crssect1[j][k];
		crssect[1][j][k] = crssect2[j][k];
	  }
	}
	if (( Enu1 != Enu2 )||( Enu1 < 0 )||( Enu2 < 0 )){
	  cout << "Enu1 ( " << Enu1 << ") != Enu2 ( "  << Enu2 << ")" << endl;
	}
	t_out->Fill();
  }

  f_out->Write();
  f_out->Close();

*/


