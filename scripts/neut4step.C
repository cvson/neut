void neut4step() {
    // An example with basic graphics illustrating the Object Oriented
    // User Interface of ROOT. The begin_html <a href="gif/framework.gif">picture</a> end_html
    // produced is the one shown in begin_html<a href="../../Mission.html">Mission Statement.</a> end_html
    //Author: Rene Brun
    
    TCanvas *c1 = new TCanvas("c1","The ROOT Framework",200,10,900,200);
    c1->Range(0,0,22,20);

    
    TPavesText *eventg = new TPavesText(0.99,17,4,19,1,"tr");
    eventg->SetFillColor(38);
    eventg->AddText("Step 1");
    eventg->Draw();
    TLatex *linput = new TLatex();
    linput->SetTextAlign(12);
    linput->SetTextSize(0.07);
    linput->DrawLatex(0.5,15,"Fixed E_{#nu}");

    
    //
    TPavesText *eventg01 = new TPavesText(15.5,1,20.7,19.5,1,"tr");
    eventg01->SetFillColor(0);
    eventg01->Draw();
    
    TPavesText *eventg = new TPavesText(16,17,20,19,1,"tr");
    eventg->SetFillColor(46);
    eventg->AddText("Step 4");
    eventg->Draw();
    
    TLatex *loutput = new TLatex();
    loutput->SetTextAlign(12);
    loutput->SetTextSize(0.07);
    loutput->DrawLatex(15.7,15,"Simulate secondary interactions");
  
    
    TArrow *ar1 = new TArrow(5.5,10,7.,10,0.03,"|>");
    //ar1->SetAngle(0);
    ar1->SetLineWidth(15);
    ar1->SetLineColor(38);
    ar1->SetFillColor(38);
    ar1->Draw();
    
    TArrow *ar2 = new TArrow(13.5,10,15,10,0.03,"|>");
    //ar2->SetAngle(0);
    ar2->SetLineWidth(15);
    ar2->SetLineColor(46);
    ar2->SetFillColor(46);
    ar2->Draw();
    
    
    //
    /*TPavesText *simul = new TPavesText(3.62,2.71,6.15,7.96,7,"tr");
     simul->SetFillColor(41);
     simul->AddText("Detector");
     simul->AddText("Simulation");
     simul->Draw();
     //
     TPavesText *recon = new TPavesText(6.56,2.69,10.07,10.15,11,"tr");
     recon->SetFillColor(48);
     recon->AddText("Event");
     recon->AddText("Reconstruction");
     recon->Draw();
     //
     TPavesText *daq = new TPavesText(10.43,2.74,14.0,10.81,11,"tr");
     daq->AddText("Data");
     daq->AddText("Acquisition");
     daq->Draw();
     //
     TPavesText *anal = new TPavesText(14.55,2.72,17.9,10.31,11,"tr");
     anal->SetFillColor(42);
     anal->AddText("Data");
     anal->AddText("Analysis");
     anal->Draw();*/
    
    c1->Update();
    c1->Print("plots/neut4step.eps");
}
