//////////////////////////////////////////////////////////////////////////
//
// Transversity Scalar Replay Script
//
//////////////////////////////////////////////////////////////////////////
//  
// Nov 2008 : Jin Huang : Init the script with ref to detector replays
//
//////////////////////////////////////////////////////////////////////////



#include "def.h"

using namespace std;


void replay_scalar(Int_t runnumber=0, Int_t all=0,Int_t fstEvt=0)
{
  ////////////////////////////////////////
  //   Beams
  ////////////////////////////////////////

  cout<<"replay: Adding Idea Beam"<< endl;

  THaApparatus* B = new THaIdealBeam("B","Idea Beam, for Test Only");
  gHaApps->Add( B );
  
  
  ////////////////////////////////////////
  //   Scalars
  ////////////////////////////////////////
  // add scalers
  

  cout<<"replay: Adding Decoder Data ..."<<endl;
  if (runnumber<20000) { 


     cout<<"replay: Adding L-arm Helicity"<< endl;
     B->AddDetector( new THaADCHelicity("adchel.L","Beam helicity L-arm") );
     B->AddDetector( new THaADCHelicity("adchel2.L","Beam helicity-2 L-arm") );
     B->AddDetector( new THaG0Helicity("g0hel.L","Left arm G0 helicity") );  


     cout<<"replay: Adding Scalar ..."<<endl;
     gHaScalers->Add(new THaScalerGroup("Left"));
     gHaScalers->Add(new THaScalerGroup("evLeft"));

     
    cout<<"replay: Adding Target ..."<<endl;
    THaHe3Target* pT=new THaHe3Target("he3","Hall A Polarized he3 target");
    gHaApps->Add(pT); 


    gHaApps->Add(new THaDecData("DL","Misc. Decoder Data")); 
    char buff[1000]="";
    sprintf(buff,"./summaryfiles/NormAna%d.log",runnumber); 
    cout<<"replay: Adding NormAna & saving result to "<<buff<<endl;
    NormAna* norm = new NormAna("N","Normalization Analysis",buff,8); 
    gHaPhysics->Add(norm);

  
  } else if (runnumber>20000) { 


    B->AddDetector( new THaADCHelicity("adchel.R","Beam helicity R-arm") );
    B->AddDetector( new THaG0Helicity("g0hel.R","Right arm G0 helicity") );  
   

    cout<<"replay: Adding Scalar ..."<<endl;
    gHaScalers->Add(new THaScalerGroup("Right"));
    gHaScalers->Add(new THaScalerGroup("evRight"));


    cout<<"replay: Adding Target ..."<<endl;
    THaHe3Target* pT=new THaHe3Target("he3R","Hall A Polarized he3 target");
    gHaApps->Add(pT); 


    gHaApps->Add(new THaDecData("D","Misc. Decoder Data")); 
    char buff[1000]="";
    sprintf(buff,"./summaryfiles/NormAna%d.log",runnumber); 
    cout<<"replay: Adding NormAna & saving result to "<<buff<<endl;
    NormAna_R* norm = new NormAna_R("N","Normalization Analysis",buff,8); 
    gHaPhysics->Add(norm);

  
  }
  


  
  ////////////////////////////////////////
  //   BB Norm Ana
  ////////////////////////////////////////

/*
  cout<<"replay: Adding A Quick Hack Code to Extract t3[0] ..."<<endl;
  THaApparatus* DL1 = new THaIdealBeam("DL1","Base Apparatus for extract t3[0]");
  gHaApps->Add( DL1 );
  DL1->AddDetector(new THaADCHe3Spin("t3","copy of DL.t3[0], for .odef file",DL1));
*/

  ////////////////////////////////////////
  //   Do replay
  ////////////////////////////////////////
  THaAnalyzer* analyzer = THaAnalyzer::GetInstance();
  if( !analyzer ) {
  analyzer = new THaAnalyzer;
  }

//This is only for Right arm. Comment it out if you replay scalars from BBite
if (runnumber<20000)
 analyzer->SetCrateMapFileName("cratemap");
else if(runnumber>20000)
  analyzer->SetCrateMapFileName("cratemap_R");


  analyzer->EnableBenchmarks();
  analyzer->EnableHelicity();
  analyzer->EnableScalers();
  analyzer->EnableSlowControl();
  analyzer->SetMarkInterval(20000);
  
  ReplayCore(
      runnumber,            //run #
      all,                  //-1=replay all;0=ask for a number
      -1,                   //defaut replay event num
      "%s/e05102_scalar_%d.root", //output file format
      "replay_scalar.odef",      //out define
      "replay_test.cdef",      //empty cut define
      kTRUE,                   //replay scalar?p
      fstEvt          //First Event To Replay
      );

  analyzer->SetMarkInterval(1000);

  analyzer->SetCrateMapFileName("cratemap");
}
