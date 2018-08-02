void feynman_nu_ncqe()
{
    //Draw Feynman diagrams
    // To see the output of this macro, click begin_html <a href="gif/feynman.gif">here</a>. end_html
    //Author: Otto Schaile
    
    TCanvas *c1 = new TCanvas("c1", "A canvas", 10,10, 600, 400);
    c1->Range(5, 0, 55, 100);
    Int_t linsav = gStyle->GetLineWidth();
    gStyle->SetLineWidth(3);
    TLatex t;
    t.SetTextAlign(22);
    t.SetTextSize(0.1);
    TArrow * l;
    double arrowsize = 0.03;
    l = new TArrow(15, 10, 30, 30, arrowsize,"-|>-"); l->Draw();
    l = new TArrow(15, 80, 30, 60, arrowsize,"-|>-"); l->Draw();
   
    t.DrawLatex(12,6,"p/n");
    t.DrawLatex(12,80,"#nu_{l}");
    
    TCurlyLine *gamma = new TCurlyLine(30, 30, 30, 60);
    gamma->SetWavy();
    gamma->Draw();
    t.DrawLatex(34,45,"Z");
    
    
    
    l = new TArrow(45, 10, 30, 30, arrowsize,"-<|-"); l->Draw();
    l = new TArrow(45, 80, 30, 60, arrowsize,"-<|-"); l->Draw();
    
    
    t.DrawLatex(48,80,"#nu_{l}");
    t.DrawLatex(48,6,"p/n");
    c1->Update();
    gStyle->SetLineWidth(linsav);
    c1->Print("plots/fm_nu_ncqe.eps");
}
