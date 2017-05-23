void createMakeClass(char* filename="",char* treename="", char* classname=""){
    TFile *pfile = new TFile(filename);
    TTree *ptree = (TTree*)pfile->Get(treename);
    ptree->MakeClass(classname);
    
}
