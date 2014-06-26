// Pedestal Analysis for the Neutron Detector
// Plane 4
// Original code for BB swiped from Miha (miham@jlab.org)
// ellie@jlab.org
// 04/23/09

#include "Riostream.h"
#include "TDatime.h"
#include "TPolyMarker.h"
#include "TPolyLine.h"
#include "TLine.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TH1.h"
#include "TH2.h"
#include "TLegend.h"  
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TChain.h"
#include "TMarker.h"
#include "TROOT.h"
#include "TF1.h"
#include "TProfile.h"

#define NBARS 12
#define RMIN 0.0
#define RMAX 1000.0
#define LMIN 0.0
#define LMAX 600.0
#define COLNUM 3

void HallA_style() {
  gROOT->SetStyle("Plain");
  gStyle->SetPaperSize(TStyle::kUSLetter);
  gStyle->SetPaperSize(18,22);
  gStyle->SetOptFit(1111);
  gStyle->SetPalette(1);
  gStyle->SetNdivisions(505);
  
  gStyle->SetCanvasColor(10);
  gStyle->SetPadTopMargin(.05);
  gStyle->SetPadLeftMargin(.1);
  gStyle->SetPadRightMargin(.1);
  gStyle->SetPadBottomMargin(.10);
  gStyle->SetTitleYOffset(1.3);
  gStyle->SetLabelFont(42,"X");
  gStyle->SetLabelFont(42,"Y");

  // prepare gStyle to be useful
  //   1 = solid
  //   2 = long dash (30 10)
  //   3 = dotted (4 8)
  //   4 = dash-dot (15 12 4 12)
  //   5 = short dash ( 15 15 )
  //   6 = dash-dot-dot 
  gStyle->SetLineStyleString(1,"[]");
  gStyle->SetLineStyleString(2,"[30 10]");
  gStyle->SetLineStyleString(3,"[4 8]");
  gStyle->SetLineStyleString(4,"[15 12 4 12]");
  gStyle->SetLineStyleString(5,"[15 15]");
  gStyle->SetLineStyleString(6,"[15 12 4 12 4 12]");
  gStyle->SetLabelSize(0.045,"X");
  gStyle->SetTitleOffset(1.3,"X");
  gStyle->SetLabelSize(0.045,"Y");
  gStyle->SetTitleOffset(1.3,"Y");
  gStyle->SetNdivisions(505,"Y");
  gStyle->SetOptDate(0);
  gStyle->SetDateY(.98);
  gStyle->SetStripDecimals(kFALSE);
  gStyle->SetEndErrorSize(7);
}



void DetermineMaximumInterval(TH1F *h, double x1, double x2, int *IMAX, double  *XMAX, double *YMAX)
{
    int NMin = h->FindBin(x1);
    int NMax = h->FindBin(x2);
    int imax = -10;
    double Ymax = -100000;
    for(int i=NMin; i< NMax; i++)
    { 
      if (h->GetBinContent(i)>Ymax)
      {
        Ymax = h->GetBinContent(i);
        imax = i;
      }
    }

    *IMAX = imax;
    *YMAX = Ymax;
    *XMAX = h->GetBinCenter(imax); 
}


Double_t fitGauss(Double_t *x, Double_t *par)
{
  Double_t k = par[0];
  Double_t n = par[1];
  return k*x[0] + n; 
}



// Racunaj means "calculate"
void racunaj_n4()
{

  const int MAX_RANGE = 500;
  const int MIN_RANGE = 100;
  const int TDC_MIN_RANGE = -1100;
  const int TDC_MAX_RANGE = -1000;
  
  const int CANVAS_SIZE_X = 1200;
  const int CANVAS_SIZE_Y = 800;

  //TString Image_Ext = ".png";
  //TString Image_Ext = ".pdf";
  
  cout << " " << endl; 
  cout << "Good morning!"<< endl;
  cout<< "I would like to help you look at the pedestals in your data." << endl << "Please enter a run number so that I may happily work my way through your pretty data:  "<<endl;
  int runnumber;
  cin>>runnumber;
  


  TChain *t1 =new TChain("T");

  TString filename="../../onlana/ROOTfiles/e05102_R_";
  filename+=runnumber;
  filename+=".root";
  

  t1->Add(filename.Data());

  assert(t1);
  // Now we count how many entries in the given run
  int num =  t1->GetEntries();
  cout<<"Number of events is : "<<num<<endl;
  
  Double_t BB_tp_e_LA[NBARS];  
  Double_t BB_tp_e_RA[NBARS];
    
  Double_t evtype;  
 
  t1->SetBranchAddress( "NA.nd.p4.la", &BB_tp_e_LA);
  t1->SetBranchAddress( "NA.nd.p4.ra", &BB_tp_e_RA);
  
  t1->SetBranchAddress( "D.evtype", &evtype);

//________________ Histograms without cut____________________________

  TH1F *Histograms_BB_tp_e_LA[NBARS];
  TH1F *Histograms_BB_tp_e_RA[NBARS];

  TLegend *leg[NBARS];
  TString imagename;

  TString ime1;
  TString ime2;
  TString ime3;
  TString ime4;
  
  TString oznaka="";
  
  double Right_max[NBARS];
  double Right_min[NBARS];
  
  double Left_max[NBARS];
  double Left_min[NBARS];  
  
// **** RIGHT SIDE    
// Need to set each pedestal on it's own since the pedestals
// are in a different place for each PMT (Don't Automate It)


for(int j=0; j<NBARS; j++)
{
  Right_min[j] = RMIN;
  Right_max[j] = RMAX;
} 


/*
Right_min[0] = 0.0;
Right_max[0] = 300.0;

Right_min[1] = 150.0;
Right_max[1] = 450.0;

Right_min[2] = 0.0;
Right_max[2] = 300.0;

Right_min[3] = 25.0;
Right_max[3] = 325.0;

Right_min[4] = 250.0;
Right_max[4] = 550.0;

Right_min[5] = 300.0;
Right_max[5] = 600.0;

Right_min[6] = 300.0;
Right_max[6] = 600.0;

Right_min[7] = 100.0;
Right_max[7] = 400.0;

Right_min[8] = 425.0;
Right_max[8] = 725.0;

Right_min[9] = 425.0;
Right_max[9] = 725.0;

Right_min[10] = 200.0;
Right_max[10] = 650.0;

Right_min[11] = 325.0;
Right_max[11] = 625.0;
*/


 
// **** LEFT SIDE 
// So, unfortunately it looks like I'm going to have to put
// in each graph individually because the pedestals are 
// coming out in different places for each PMT 


for(int j=0; j<NBARS; j++)
{
  Left_min[j] = LMIN;
  Left_max[j] = LMAX;
}


/*

Left_min[0] = 50.0;
Left_max[0] = 350.0;

Left_min[1] = 125.0;
Left_max[1] = 425.0;

Left_min[2] = 100.0;
Left_max[2] = 400.0;

Left_min[3] = 150.0;
Left_max[3] = 450.0;

Left_min[4] = 250.0;
Left_max[4] = 550.0;

Left_min[5] = 100.0;
Left_max[5] = 400.0;

Left_min[6] = 75.0;
Left_max[6] = 375.0;

Left_min[7] = 100.0;
Left_max[7] = 400.0;

Left_min[8] = 350.0;
Left_max[8] = 650.0;

Left_min[9] = 250.0;
Left_max[9] = 550.0;

Left_min[10] = 250.0;
Left_max[10] = 550.0;

Left_min[11] = 200.0;
Left_max[11] = 500.0;
*/



// Create histograms for the ADCs
  for (int i=0; i<NBARS; i++)
  {
    oznaka="Pedestal_Run_#";
    oznaka+=runnumber;
    oznaka+=" -> paddle #";
    oznaka+=i+1;
 
    ime3="NA_nd_n4_LA";
    ime4="NA_nd_n4_RA";
    ime3 += i;
    ime4 += i;
    cout<<"Data3: "<<ime3.Data()<<endl;
    cout<<"Data4: "<<ime4.Data()<<endl; 

    Histograms_BB_tp_e_LA[i] = new TH1F(ime3,oznaka, (Left_max[i]-Left_min[i]), Left_min[i] , Left_max[i]);
    Histograms_BB_tp_e_RA[i] = new TH1F(ime4,oznaka, (Right_max[i]-Right_min[i]), Right_min[i] , Right_max[i]);

  }
  
  
  
  cout<<"*******"<<endl;
  
  
  // num
  for (int i=0; i<num; i++)
  { 
     t1-> GetEntry(i);
     if ((i%1000==0) && (i>0)) cout<<i<<endl;

     for (int j = 0; j<NBARS; j++) Histograms_BB_tp_e_LA[j]->Fill(BB_tp_e_LA[j]); 
     for (int j = 0; j<NBARS; j++) Histograms_BB_tp_e_RA[j]->Fill(BB_tp_e_RA[j]);

  }

// ************* 1D - ADC - right side spectra ************************

  TF1 *fitsR[NBARS];

  TCanvas *R_ADCHistograms;
  
  ofstream ERout;
  ERout.open("ped_data/more_ped_info/ND_n4_R_pedestals.dat");
 
  TString R_ADCHistogramName = "N4_R_ADC_pedestal_fits";
  R_ADCHistograms = new TCanvas(R_ADCHistogramName, R_ADCHistogramName,CANVAS_SIZE_X,CANVAS_SIZE_Y);
  R_ADCHistograms->Divide(5,COLNUM);

  for (int k = 0; k<NBARS; k++) {
    R_ADCHistograms->cd(k+1);
    Histograms_BB_tp_e_RA[k]->SetLineColor(kGreen);
    Histograms_BB_tp_e_RA[k]->Draw(); 
    R_ADCHistograms->Update();
    
    TString fitFuncName = "fit";
    fitFuncName +=k;
    fitsR[k] = new TF1(fitFuncName,"gaus",Right_min[k],Right_max[k]);
    fitsR[k]->SetLineColor(kBlue);
    fitsR[k]->SetLineWidth(1);
    Histograms_BB_tp_e_RA[k]->Fit(fitsR[k],"RV");  
    ERout<<k<<"  "<<fitsR[k]->GetParameter(0)<<"  "<<fitsR[k]->GetParameter(1)<<"  "<<fitsR[k]->GetParameter(2)<<endl;

    
    imagename="ped_data/ped_fit_pics/ND_n4_ADC_R_pedestal_fits.png";
    R_ADCHistograms->Print(imagename);
  }
  ERout.close();








// ************* 1D - ADC - left side spectra ************************

  TF1 *fitsL[NBARS];

  TCanvas *L_ADCHistograms;
  
  ofstream ELout;
  ELout.open("ped_data/more_ped_info/ND_n4_L_pedestals.dat");
 
  TString L_ADCHistogramName = "N4_L_ADC_pedestal_fits";
  L_ADCHistograms = new TCanvas(L_ADCHistogramName, L_ADCHistogramName,CANVAS_SIZE_X,CANVAS_SIZE_Y);
  L_ADCHistograms->Divide(5,COLNUM);

  for (int k = 0; k<NBARS; k++) {
    L_ADCHistograms->cd(k+1);
    Histograms_BB_tp_e_LA[k]->SetLineColor(kGreen);
    Histograms_BB_tp_e_LA[k]->Draw(); 
    L_ADCHistograms->Update();
    
    TString fitFuncName = "fit";
    fitFuncName +=k;
    fitsL[k] = new TF1(fitFuncName,"gaus",Left_min[k],Left_max[k]);
    fitsL[k]->SetLineColor(kBlue);
    fitsL[k]->SetLineWidth(1);
    Histograms_BB_tp_e_LA[k]->Fit(fitsL[k],"LV");  
    ELout<<k<<"  "<<fitsL[k]->GetParameter(0)<<"  "<<fitsL[k]->GetParameter(1)<<"  "<<fitsL[k]->GetParameter(2)<<endl;

    

    imagename="ped_data/ped_fit_pics/ND_n4_ADC_L_pedestal_fits.png";
    L_ADCHistograms->Print(imagename);
  }
  ELout.close();

// Pedestal Output to Single File
// If this does what I hope it will, it should put the mean position for
// both the left and right sides into a single *.dat file that will be easily
// transferred into the neutron detector database

  ofstream Eout;
  Eout.open("ped_data/ND_n4_pedestals.dat");

  for (int k = 0; k<NBARS; k++) {
    int LMean = int(fitsL[k]->GetParameter(1));
    int RMean = int(fitsR[k]->GetParameter(1));

    Eout<<"     "<<LMean<<"     "<<RMean<<"                            "<<"- Paddle"<<(k+1)<<"   (Left/Right)"<<endl;

  }
  Eout.close();

}

void ND_n4_pedestals()
{
  HallA_style();
  racunaj_n4();  

  cout << "You've reached the end! Huzzah!" << endl;
}


