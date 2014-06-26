////########  this script is to calculate asym. for each run  and save them  #######

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TApplication.h"
#include "TGClient.h"
#include "TCanvas.h"
#include "TGButton.h"
#include "TGFrame.h"
#include "TControlBar.h"
#include "TChain.h"

#include "/w/work5602/transversity/zhaobo/aytest/rawasym/1passruns/Ayanalysis_1pass.h"

#define Ntot 8
#define Ntrigtype 4
#define Nchargetype 7
#define Ndim 3


void getEachrunAsym_1pass( int inputrun)
{
 
 TFile *outfile = new TFile("asym_eachrun.root", "RECREATE");  
 TTree *asymtree = new TTree("asymtree", "a tree to save each run asym.");

//////////******* start of initializaing tree ****************************

//here only 3 scalars for each leaf: ungated, +, -
 int Runnumber, PASS;
 double t1_all[Ndim], t1_good[Ndim], t1_doublepulse[Ndim], t3_all[Ndim], t3_good[Ndim];
 double clk[Ndim], fclk[Ndim], u1[Ndim], u3[Ndim], u10[Ndim], d1[Ndim], d3[Ndim], d10[Ndim], unser[Ndim];
 double Numevt_tsa[3][Ndim];
 double charge[Ndim], livetime[Ndim];
 double tsa[3], err_tsa[3], dsa[3], err_dsa[3], bsa[3], err_bsa[3]; //overall -- QE -- Elastic
 double Numevt_dsa[3][Ndim], Numevt_bsa[3][Ndim];
 double asym_W[6], err_asym_W[6], NumWbin[6][Ndim];
 double ratio[10]={0}, rationum[10]={0};

 double ExTgtCor_p, ExTgtCor_dp, ExTgtCor_th, ExTgtCor_ph, ExTgtCor_y, tr_tg_x, tr_tg_y;
 double cer_asum_c, ps_e, sh_e, Q2, W2, W2_He3, x_bj, react_z, tr_n;

 TH1F *hXbj[2][2], *hQ2[2][2], *hW2[2][2]; // arm -- sign
 TH1F *hYieldXbj[2][2], *hYieldQ2[2][2], *hYieldW2[2][2];

// asymtree->Branch("PASS", &PASS,"PASS/I");
 asymtree->Branch("Runnumber", &Runnumber,"Runnumber/I");
 asymtree->Branch("t1_all", t1_all,"t1_all[3]/D");
 asymtree->Branch("t1_good", t1_good,"t1_good[3]/D");
 asymtree->Branch("t1_doublepulse", t1_doublepulse,"t1_doublepulse[3]/D");
 asymtree->Branch("t3_all", t3_all,"t3_all[3]/D");
 asymtree->Branch("t3_good", t3_good,"t3_good[3]/D");
 asymtree->Branch("clk", clk,"clk[3]/D");
 asymtree->Branch("fclk", fclk,"fclk[3]/D");
 asymtree->Branch("u1", u1,"u1[3]/D");
 asymtree->Branch("u3", u3,"u3[3]/D");
 asymtree->Branch("u10", u10,"u10[3]/D");
// asymtree->Branch("d1", d1,"d1[3]/D");
// asymtree->Branch("d3", d3,"d3[3]/D");
// asymtree->Branch("d10", d10,"d10[3]/D");
 asymtree->Branch("unser", unser,"unser[3]/D");
 asymtree->Branch("charge", charge,"charge[3]/D");
 asymtree->Branch("livetime", livetime,"livetime[3]/D");
 asymtree->Branch("Numevt_tsa", Numevt_tsa,"Numevt_tsa[3][3]/D");
 asymtree->Branch("Numevt_dsa", Numevt_dsa,"Numevt_dsa[3][3]/D");
 asymtree->Branch("Numevt_bsa", Numevt_bsa,"Numevt_bsa[3][3]/D");
 asymtree->Branch("tsa", tsa,"tsa[3]/D");
 asymtree->Branch("err_tsa", err_tsa,"err_tsa[3]/D");
 asymtree->Branch("bsa", bsa,"bsa[3]/D");
 asymtree->Branch("err_bsa", err_bsa,"err_bsa[3]/D");
 asymtree->Branch("dsa", dsa,"dsa[3]/D");
 asymtree->Branch("err_dsa", err_dsa,"err_dsa[3]/D");
 asymtree->Branch("asym_W", asym_W,"asym_W[6]/D");
 asymtree->Branch("err_asym_W", err_asym_W,"err_asym_W[6]/D");
 asymtree->Branch("rationum", rationum, "rationum[10]/D");

 asymtree->Reset();
//////////******* end of initializaing tree ********************************

 for(int i=0; i<2; i++)
 {
  hXbj[0][i] = new TH1F(Form("hXbj_L_%d", i), "x_bj in L-arm", 400, 0, 4);
  hXbj[1][i] = new TH1F(Form("hXbj_R_%d", i), "x_bj in R-arm", 400, 0, 4);

  hQ2[0][i] = new TH1F(Form("hQ2_L_%d", i), "Q2 in L-arm", 200, 0, 0.2);
  hQ2[1][i] = new TH1F(Form("hQ2_R_%d", i), "Q2 in R-arm", 200, 0, 0.2);

  hW2[0][i] = new TH1F(Form("hW2_L_%d", i), "W2 in L-arm", 400, 0, 2);
  hW2[1][i] = new TH1F(Form("hW2_R_%d", i), "W2 in R-arm", 400, 0, 2);

  hYieldXbj[0][i] = new TH1F(Form("hYieldXbj_L_%d", i), "x_bj yield in L-arm", 400, 0, 4);
  hYieldXbj[1][i] = new TH1F(Form("hYieldXbj_R_%d", i), "x_bj yield in R-arm", 400, 0, 4);

  hYieldQ2[0][i] = new TH1F(Form("hYieldQ2_L_%d", i), "Q2 yield in L-arm", 200, 0, 0.2);
  hYieldQ2[1][i] = new TH1F(Form("hYieldQ2_R_%d", i), "Q2 yield in R-arm", 200, 0, 0.2);

  hYieldW2[0][i] = new TH1F(Form("hYieldW2_L_%d", i), "W2 yield in L-arm", 400, 0, 2);
  hYieldW2[1][i] = new TH1F(Form("hYieldW2_R_%d", i), "W2 yield in R-arm", 400, 0, 2);
 } 


// read the tree from data root file
 double evscalar_type[Ntot] = {0};
 double previous_value[Ntot] = {0};
 double previous_plus_value[Ntot] = {0};
 double previous_minus_value[Ntot] = {0};
 double evvalue[Ntot][Ndim] = {0};

 double adc1_UpADC, adc1_DownADC;
 double evtypebits;
 double TargetSpin, init_TargetSpin, helicity;
 double fastclock = 0;

 double calib[6] = {2101.87, 6464.39, 19718.3, 2147.88, 6645.89, 20952.0};
 double offset[6] = {395.804, 453.4, 770.516, 154.577, 133.319, 293.463};

 int flag_goodevent;

 TTree *T;
 TFile *infile;

 
 string prefix, file;
 stringstream runno;

 prefix += "/work/halla/transversity/disk3/zbRootFiles/physreplay/1passruns/e05102_";
//   prefix += "/work/halla/transversity/disk3/zbRootFiles/physreplay/referruns/e05102_";

// prefix += "/work/halla/transversity/disk3/zbRootFiles/localrun/ROOTfiles/e05102_";
// prefix += "/w/work5602/transversity/zhaobo/aytest/farmreplay/test/ROOTfiles/e05102_scalar_";
// prefix += "/work/halla/transversity/disk3/zbRootFiles/bothscalarclass/e05102_scalar_";

// ifstream RUNLIST("prodrunslist", ios::in);

// RUNLIST >> runno;
// while(!RUNLIST.eof())
 {
  runno << inputrun;
  if(inputrun < 20000) file = prefix + "L_" + runno.str() + ".root";
  if(inputrun > 20000) file = prefix + "R_" + runno.str() + ".root";

  infile = new TFile(file.c_str());

  if(infile->IsZombie())
  {
   cout << " File could not be opened. Exiting" << endl;
   exit(0);
  }

  else
  {
   cout << "analyzing run: " << inputrun << endl;
   Runnumber = inputrun;

   T = (TTree*)infile->Get("T");

   for(int i=0; i++; i<Ndim)
   {
    t1_all[i] = t1_good[i] = t1_doublepulse[i] = t3_all[i] = t3_good[i] = 0;
    clk[i] = fclk[i] = u1[i] = u3[i] = u10[i] = d1[i] = d3[i] = d10[i] = unser[i] = 0;
    charge[i] = livetime[i] = 0;
   }

   double HalfWavePlate = GetHWP(Runnumber);

   if(Runnumber<20000)
   {
    T->SetBranchAddress ("evleft_t1c", &evscalar_type[0]);
    T->SetBranchAddress ("evleft_t3c", &evscalar_type[1]);
    T->SetBranchAddress ("evleft_clkc", &evscalar_type[2]);
    T->SetBranchAddress ("evleft_fclkc", &evscalar_type[3]);
    T->SetBranchAddress ("evleft_u1c", &evscalar_type[4]);
    T->SetBranchAddress ("evleft_u3c", &evscalar_type[5]);
    T->SetBranchAddress ("evleft_u10c", &evscalar_type[6]);
    T->SetBranchAddress ("evleft_unserc", &evscalar_type[7]);

//    T->SetBranchAddress ("evleft_d1c", &evscalar_type[7]);
//    T->SetBranchAddress ("evleft_d3c", &evscalar_type[8]);
//    T->SetBranchAddress ("evleft_d10c", &evscalar_type[9]);

    T->SetBranchAddress ("ExTgtCor_L.p", &ExTgtCor_p);
    T->SetBranchAddress ("ExTgtCor_L.dp", &ExTgtCor_dp);
    T->SetBranchAddress ("ExTgtCor_L.th", &ExTgtCor_th);
    T->SetBranchAddress ("ExTgtCor_L.ph", &ExTgtCor_ph);
    T->SetBranchAddress ("ExTgtCor_L.y", &ExTgtCor_y);
    T->SetBranchAddress ("L.cer.asum_c", &cer_asum_c);
    T->SetBranchAddress ("L.prl1.e", &ps_e);
    T->SetBranchAddress ("L.prl2.e", &sh_e);
    T->SetBranchAddress ("L.tr.n", &tr_n);
    T->SetBranchAddress ("ReactPt_L.z", &react_z);
    T->SetBranchAddress ("PriKineL.Q2", &Q2);
    T->SetBranchAddress ("PriKineL.W2", &W2);
    T->SetBranchAddress ("PriKineL.x_bj", &x_bj);
    T->SetBranchAddress ("PriKineLHe3.W2", &W2_He3);

    T->SetBranchAddress ("he3.ladc1.UpADC", &adc1_UpADC); 
    T->SetBranchAddress ("he3.ladc1.DownADC", &adc1_DownADC); 
    T->SetBranchAddress ("DL.evtypebits", &evtypebits);
    T->SetBranchAddress ("adchel.L.helicity", &helicity); 
   }

   if(Runnumber>20000)   
   {
    T->SetBranchAddress ("evright_t1c", &evscalar_type[0]);
    T->SetBranchAddress ("evright_t3c", &evscalar_type[1]);
    T->SetBranchAddress ("evright_clkc", &evscalar_type[2]);
    T->SetBranchAddress ("evright_fclkc", &evscalar_type[3]);
    T->SetBranchAddress ("evright_u1c", &evscalar_type[4]);
    T->SetBranchAddress ("evright_u3c", &evscalar_type[5]);
    T->SetBranchAddress ("evright_u10c", &evscalar_type[6]);
    T->SetBranchAddress ("evright_unserc", &evscalar_type[7]);

//    T->SetBranchAddress ("evright_d1c", &evscalar_type[7]);
//    T->SetBranchAddress ("evright_d3c", &evscalar_type[8]);
//    T->SetBranchAddress ("evright_d10c", &evscalar_type[9]);

    T->SetBranchAddress ("ExTgtCor_R.p", &ExTgtCor_p);
    T->SetBranchAddress ("ExTgtCor_R.dp", &ExTgtCor_dp);
    T->SetBranchAddress ("ExTgtCor_R.th", &ExTgtCor_th);
    T->SetBranchAddress ("ExTgtCor_R.ph", &ExTgtCor_ph);
    T->SetBranchAddress ("ExTgtCor_R.y", &ExTgtCor_y);
    T->SetBranchAddress ("R.cer.asum_c", &cer_asum_c);
    T->SetBranchAddress ("R.ps.e", &ps_e);
    T->SetBranchAddress ("R.sh.e", &sh_e);
    T->SetBranchAddress ("R.tr.n", &tr_n);
    T->SetBranchAddress ("ReactPt_R.z", &react_z);
    T->SetBranchAddress ("PriKineR.Q2", &Q2);
    T->SetBranchAddress ("PriKineR.W2", &W2);
    T->SetBranchAddress ("PriKineR.x_bj", &x_bj);
    T->SetBranchAddress ("PriKineRHe3.W2", &W2_He3);

    T->SetBranchAddress ("he3R.radc1.UpADC", &adc1_UpADC); 
    T->SetBranchAddress ("he3R.radc1.DownADC", &adc1_DownADC); 
    T->SetBranchAddress ("D.evtypebits", &evtypebits);
    T->SetBranchAddress ("adchel.R.helicity", &helicity); 
   }

//initial previous_value[Ntot][7]
   int Skippedentry = 101;
   T->GetEntry(Skippedentry);
   {
    init_TargetSpin = GetTargetSpin(adc1_UpADC, adc1_DownADC);
    while (fabs(init_TargetSpin)<1e-5)
    {
     Skippedentry = Skippedentry + 100;
     T->GetEntry(Skippedentry);
     init_TargetSpin = GetTargetSpin(adc1_UpADC, adc1_DownADC);
    }     

    for(int i=0; i<Ntot; i++)
    {
     previous_value[i] = evscalar_type[i];
     if(init_TargetSpin>0) { previous_plus_value[i] = evscalar_type[i];  previous_minus_value[i] = 0;}
     if(init_TargetSpin<0) { previous_minus_value[i] = evscalar_type[i];  previous_plus_value[i] = 0;}

     for(int j=0; j<Ndim; j++)
      evvalue[i][j] = 0;
    }
   }

//   for(int l=101; l<100000; l++)
   for(int l=Skippedentry; l<=T->GetEntries()-Skippedentry; l++)
   {
    if(l%100000==0) cout << " " << l << endl;

    T->GetEntry(l);

    flag_goodevent = -1;

    TargetSpin = GetTargetSpin(adc1_UpADC, adc1_DownADC);

///////// *********** start of scalars and charges **********
    if( (evtypebits&(1<<1))==(1<<1) && TargetSpin != 0)
    { 
     t1_good[0]++; //get good T1 to calculate live time
     if(TargetSpin>0) t1_good[1]++;
     if(TargetSpin<0) t1_good[2]++;  
    }

    if( (evtypebits&(1<<3))==(1<<3) && TargetSpin != 0)
    { 
     t3_good[0]++; //get good T3 to calculate live time
     if(TargetSpin>0) t3_good[1]++;
     if(TargetSpin<0) t3_good[2]++;  
    }


    if(fabs(TargetSpin-init_TargetSpin)>1e-5 || l==T->GetEntries()-Skippedentry) //target state change, possible 0 or opposite
    {
     T->GetEntry(l-1); //get scalars for previous target state
     for(int s=0; s<Ntot; s++)
     {
      evvalue[s][0] = evvalue[s][0] + evscalar_type[s] - previous_value[s];      
      if(init_TargetSpin>0) evvalue[s][1] = evvalue[s][1] + evscalar_type[s] - previous_plus_value[s];  
      if(init_TargetSpin<0) evvalue[s][2] = evvalue[s][2] + evscalar_type[s] - previous_minus_value[s];
     }

     while( fabs(TargetSpin)<1e-5 && l<T->GetEntries()-Skippedentry) //target state=0, skip entries until != 0
     {
      l++;
      T->GetEntry(l);
      TargetSpin = GetTargetSpin(adc1_UpADC, adc1_DownADC);
     }

     init_TargetSpin = TargetSpin; //set initial values for new target state
     l = l + 100;
     if(l >  T->GetEntries()-1) l = T->GetEntries()-1;
     T->GetEntry(l);
     for(int s=0; s<Ntot; s++)
     {
      previous_value[s] = evscalar_type[s];
      if(init_TargetSpin>0) previous_plus_value[s] = evscalar_type[s];
      if(init_TargetSpin<0) previous_minus_value[s] = evscalar_type[s];
     }
    }
///////// ****** end of scalars and charges ***********************


/////// ########## start of getting physical events ###########
    if(Runnumber < 20000)
     if(tr_n == 1)
      if((evtypebits&(1<<3))==(1<<3))
       if(cer_asum_c>400)
        if(ps_e>10 && sh_e>10 && ps_e+1.07*sh_e>930 && (ps_e+sh_e)/ExTgtCor_p/1000>0.5)
         if(react_z>-0.13 && react_z<0.14)
          if(LHRS_Rcut(ExTgtCor_dp, ExTgtCor_y, ExTgtCor_th, ExTgtCor_ph) > 0)
            flag_goodevent = 0;

    if(Runnumber > 20000)
     if(tr_n == 1)
      if((evtypebits&(1<<1))==(1<<1))
       if(cer_asum_c>400)
        if(ps_e>10 && sh_e>10 && ps_e+sh_e>800 && (ps_e+sh_e)/ExTgtCor_p/1000>0.5)
         if(react_z>-0.14 && react_z<0.15) //tight cut to select clean events
          if(RHRS_Rcut(ExTgtCor_dp, ExTgtCor_y, ExTgtCor_th, ExTgtCor_ph) > 0)
            flag_goodevent = 1;


    if(flag_goodevent >= 0)
          {       
           if(TargetSpin > 0)
           {
            Numevt_tsa[0][1]++;
            if( sqrt(W2_He3)>2.83 ) Numevt_tsa[1][1]++; //QE region
            if( sqrt(W2_He3) > 2.81 && sqrt(W2_He3)<2.815 ) Numevt_tsa[2][1]++; //Elastic region
            NumWbin[GetWBin(Runnumber, sqrt(W2_He3))][1]++; // 6 W bins
            hXbj[flag_goodevent][0]->Fill(x_bj);
            hQ2[flag_goodevent][0]->Fill(Q2);
            hW2[flag_goodevent][0]->Fill(W2);
           }

           if(TargetSpin < 0)
           {
            Numevt_tsa[0][2]++;
            if( sqrt(W2_He3)>2.83 ) Numevt_tsa[1][2]++; //QE region
            if( sqrt(W2_He3)>2.81 && sqrt(W2_He3)<2.815 ) Numevt_tsa[2][2]++; //Elastic region
            NumWbin[GetWBin(Runnumber, sqrt(W2_He3))][2]++; // 6 W bins
            hXbj[flag_goodevent][1]->Fill(x_bj);
            hQ2[flag_goodevent][1]->Fill(Q2);
            hW2[flag_goodevent][1]->Fill(W2);
           }


           if(helicity*HalfWavePlate > 0) 
           {
            Numevt_bsa[0][1]++;                                                 //overall
            if( sqrt(W2_He3)>2.83 ) Numevt_bsa[1][1]++;                         //QE region
            if( sqrt(W2_He3) > 2.81 && sqrt(W2_He3)<2.815 ) Numevt_bsa[2][1]++; //Elastic region

            if(TargetSpin > 0)
            {
             Numevt_dsa[0][1]++;                                                 //overall
             if( sqrt(W2_He3)>2.83 ) Numevt_dsa[1][1]++;                         //QE region
             if( sqrt(W2_He3) > 2.81 && sqrt(W2_He3)<2.815 ) Numevt_dsa[2][1]++; //Elastic region
            } 

            if(TargetSpin < 0)
            {
             Numevt_dsa[0][2]++;                                                 //overall
             if( sqrt(W2_He3)>2.83 ) Numevt_dsa[1][2]++;                         //QE region
             if( sqrt(W2_He3) > 2.81 && sqrt(W2_He3)<2.815 ) Numevt_dsa[2][2]++; //Elastic region
            } 
           }

           if(helicity*HalfWavePlate < 0) 
           {
            Numevt_bsa[0][2]++;                                                 //overall
            if( sqrt(W2_He3)>2.83 ) Numevt_bsa[1][2]++;                         //QE region
            if( sqrt(W2_He3) > 2.81 && sqrt(W2_He3)<2.815 ) Numevt_bsa[2][2]++; //Elastic region

            if(TargetSpin < 0)
            {
             Numevt_dsa[0][1]++;                                                 //overall
             if( sqrt(W2_He3)>2.83 ) Numevt_dsa[1][1]++;                         //QE region
             if( sqrt(W2_He3) > 2.81 && sqrt(W2_He3)<2.815 ) Numevt_dsa[2][1]++; //Elastic region
            } 

            if(TargetSpin > 0)
            {
             Numevt_dsa[0][2]++;                                                 //overall
             if( sqrt(W2_He3)>2.83 ) Numevt_dsa[1][2]++;                         //QE region
             if( sqrt(W2_He3) > 2.81 && sqrt(W2_He3)<2.815 ) Numevt_dsa[2][2]++; //Elastic region
            } 
           }
          }

/////// ########## enf of the tree to get physical events ###########

   } // tree loop

   for(int j=0; j<Ndim; j++)  // set scalar values and save them into the tree
   {
    t1_all[j] = evvalue[0][j] + 1e-15;
    t3_all[j] = evvalue[1][j] + 1e-15;
    clk[j]    = evvalue[2][j] + 1e-15;
    fclk[j]   = evvalue[3][j] + 1e-15;
    u1[j]     = evvalue[4][j] + 1e-15;
    u3[j]     = evvalue[5][j] + 1e-15;
    u10[j]    = evvalue[6][j] + 1e-15;
    unser[j]  = evvalue[7][j] + 1e-15;
   } 


//select u3 to calculate charge
   charge[0] = (u3[0] - offset[1]*fclk[0]/103.7/1000.0)/calib[1];
   charge[1] = (u3[1] - offset[1]*fclk[1]/103.7/1000.0)/calib[1];
   charge[2] = (u3[2] - offset[1]*fclk[2]/103.7/1000.0)/calib[1];
   
   if(Runnumber > 20000)
   {
    livetime[0] = t1_good[0]/t1_all[0];
    livetime[1] = t1_good[1]/t1_all[1];
    livetime[2] = t1_good[2]/t1_all[2];
   }


   if(Runnumber < 20000)
   {
    livetime[0] = t3_good[0]/t3_all[0];
    livetime[1] = t3_good[1]/t3_all[1];
    livetime[2] = t3_good[2]/t3_all[2];
   }

   for(int i=0; i<2; i++)
    for(int j=0; j<2; j++)
    {
     hYieldXbj[i][j] = addhists(hXbj[i][j], hXbj[i][j], 0, 1/(livetime[j+1] + 1e-15));
     hYieldQ2[i][j] =  addhists(hQ2[i][j], hQ2[i][j], 0, 1/(livetime[j+1] + 1e-15));
     hYieldW2[i][j] =  addhists(hW2[i][j], hW2[i][j], 0, 1/(livetime[j+1] + 1e-15));
    }


   for(int s=0; s<6; s++)
   {
    asym_W[s] = GetAsymmetry(NumWbin[s][1], NumWbin[s][2], charge[1], charge[2], livetime[1], livetime[2]);
    err_asym_W[s] = GetAsymmetryError(NumWbin[s][1], NumWbin[s][2], charge[1], charge[2], livetime[1], livetime[2]);
   }

//tsa, bsa and dsa
   for(int s=0; s<3; s++)
   {
    tsa[s] = GetAsymmetry(Numevt_tsa[s][1], Numevt_tsa[s][2], charge[1], charge[2], livetime[1], livetime[2]);
    err_tsa[s] = GetAsymmetryError(Numevt_tsa[s][1], Numevt_tsa[s][2], charge[1], charge[2], livetime[1], livetime[2]);
    bsa[s] = GetAsymmetry(Numevt_bsa[s][1], Numevt_bsa[s][2], 1, 1, 1, 1);
    err_bsa[s] = GetAsymmetryError(Numevt_bsa[s][1], Numevt_bsa[s][2], 1, 1, 1, 1);
    dsa[s] = GetAsymmetry(Numevt_dsa[s][1], Numevt_dsa[s][2], 1, 1, 1, 1);
    err_dsa[s] = GetAsymmetryError(Numevt_dsa[s][1], Numevt_dsa[s][2], 1, 1, 1, 1);
   } 

   asymtree->Fill();
  }
 
 }

 outfile->Write();

}



