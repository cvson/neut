#define NAtomic 12
#define RAtomic 1.25 //+-0.2 fm
Double_t globalFG(Double_t *x, Double_t *par)
{
    Float_t xx =x[0];
    Double_t Rnuclear = 1.25*pow(12,1/3.);//
    Double_t f = 246*(xx<Rnuclear) +par[0];
    return f;
}
//https://ac.els-cdn.com/S0092640X74800021/1-s2.0-S0092640X74800021-main.pdf?_tid=17b98f66-df1b-11e7-899c-00000aab0f02&acdnat=1513069491_db7e53771a6ce1a6dd2ffe50626e603f
Double_t localFG(Double_t *x, Double_t *par)
{
    Float_t xx =x[0];
    Double_t Rnuclear = 1.25*pow(12,1/3.);//
    Double_t f = 246*(xx<Rnuclear) +par[0];
    return f;
}

void plot_fermi_momentum(){
    TF1 *f1 = new TF1("globalFG",globalFG,0,8,1);
    f1->SetParameters(1,0);
    f1->SetParNames("tmp");
    f1->SetTitle("");
    f1->GetXaxis()->SetTitle("Distance from nucleus center [fm]");
    f1->GetYaxis()->SetTitle("Fermi momentum [MeV/c]");
    
    f1->Draw();
    f1->SetLineColor(1);
    gPad->Update();
    gPad->Print("plots/fermi_mom_fg_vs_sf.eps");
}
