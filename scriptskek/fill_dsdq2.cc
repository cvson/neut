#include <iostream>

using namespace std;

#include <NeutRootHandlers.h>

#include "neutvect.h"
#include "neutvtx.h"

#include "neworkC.h"
#include "vcworkC.h"
#include "vcvrtxC.h"
#include "neutparamsC.h"
#include "posinnucC.h"
#include "neutmodelC.h"
#include "necardC.h"
#include "nrcardC.h"
#include "nefillverC.h"
#include "neutcrsC.h"
#include "posinnucC.h"
#include "fsihistC.h"

#include <string.h>
extern "C"
{
  int neutfilldsdq2_(char * /* filename */, char * /* treename */,
					char * /* Branch name */, int , int, int);

  int neutfilldsdq2(char * /* filename */, char * /* treename */,
				   char * /* Branch name */);

  extern double dnelsq2_(double *, int *, double *);
};



int
neutfilldsdq2_(char *filename, char *treename, char *branchname,
			   int len_fname,int len_tname, int len_bname)
{
  NeutRootHandlers nrh;  

  nrh.nulltermstr(filename,   len_fname);
  nrh.nulltermstr(treename,   len_tname);
  nrh.nulltermstr(branchname, len_bname);

  return neutfilldsdq2(filename, treename, branchname);
}

int
neutfilldsdq2(char *filename, char *treename, char *branchname)
{


  NeutRootHandlers nrh;

  static TTree   *t   = NULL;
  static struct _kvars{
	Double_t enu;
	Double_t coslep;
	Double_t plep;
	Double_t elep;
	Double_t q2;
	Double_t dsdq2;
	Int_t    ipnu;
	Int_t    iplep;
	Int_t    mode;
  } kvars;

  int i,j,lepIndex;
  Double_t enu2, plep2;
  Double_t xmlep;

  if (t == NULL){
	t = nrh.maketree(filename, treename, "Neut Kinematics Tree");
	if (t == NULL) return -1;

	t->Branch("NeutKineInfo",&kvars,
			   "enu/D:coslep/D:plep/D:elep/D:q2/D:dsdq2/D:ipnu/I:iplep/I:mode/I");
  }
  
  memset(&kvars, 0,sizeof(kvars));
  enu2  = 0;
  plep2 = 0;

  if(nework_.modene==2){lepIndex=3;}
  else {lepIndex=2;}

  for ( i = 0 ; i < 3 ; i++ ){
	enu2   += ( nework_.pne[0][i] *nework_.pne[0][i] );
	plep2  += ( nework_.pne[lepIndex][i] *nework_.pne[lepIndex][i] );
	kvars.coslep += ( nework_.pne[0][i] *nework_.pne[lepIndex][i] );
  }

  kvars.enu    = sqrt(enu2);
  kvars.plep   = sqrt(plep2);
  kvars.coslep = kvars.coslep / kvars.enu / kvars.plep;

  switch (abs(nework_.ipne[lepIndex])){
	case 12:
	case 14:
	case 16:
	  xmlep = 0;
	  break;
	case 11:
	  xmlep = 0.000511;
	  break;
	case 13:
	  xmlep = 0.105658;
	  break;
	case 15:
	  xmlep = 1.77699;
	  break;
	default:
	  cout << "Unknown lepton PID "
		   << abs(nework_.ipne[lepIndex])
		   << " for outgoing lepton"
		   << endl;
	  exit(2);
  }
  kvars.elep = sqrt(xmlep * xmlep + plep2);
  kvars.q2 
	= (kvars.elep - kvars.enu)*(kvars.elep - kvars.enu)
	- ((nework_.pne[lepIndex][0] - nework_.pne[0][0])
	   *(nework_.pne[lepIndex][0] - nework_.pne[0][0]))
	- ((nework_.pne[lepIndex][1] - nework_.pne[0][1])
	   *(nework_.pne[lepIndex][1] - nework_.pne[0][1]))
	- ((nework_.pne[lepIndex][2] - nework_.pne[0][2])
	   *(nework_.pne[lepIndex][2] - nework_.pne[0][2]));
  kvars.q2 *= -1;

  kvars.ipnu  = nework_.ipne[0];
  kvars.iplep = nework_.ipne[lepIndex];
  kvars.mode  = nework_.modene;
  kvars.dsdq2 = dnelsq2_(&(kvars.enu),&(kvars.ipnu),&(kvars.q2));


  t->Fill();
  return 0;
}
