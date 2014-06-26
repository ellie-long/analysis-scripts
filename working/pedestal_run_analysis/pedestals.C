// This script should give pedestal information in the
// /ped_data/ folder after telling it the run number.
// It will also display each of the pedestals it finds 
// so that the user can do a sanity check on them.
//
// This script was made while working on the gain matching
// software.
//
// Elena Long (ellie@jlab.org)
// 05/09/09


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

#define RPedMin 0.0
#define RPedMax 2000.0
#define LPedMin 0.0
#define LPedMax 2000.0


// *******************************************************************
// This should change NBars to the number
// of bars in the plane that the program
// is currently looking at. NPlane 0 = Veto, 
// 1 = N1, 2 = N2, 3 = N3, and 4 = N4.
// *******************************************************************
void get_NBars(int NPlane, int *NBARS, int *COLNUM)
{
  if (NPlane == 0)
  {
    *NBARS = 32;
    *COLNUM = 7;
  }
  if (NPlane == 1)
  {
    *NBARS = 30;
    *COLNUM = 6;
  }
  if (NPlane == 2)
  {
    *NBARS = 24;
    *COLNUM = 5;
  }
  if (NPlane == 3)
  {
    *NBARS = 22;
    *COLNUM = 5;
  }
  if (NPlane == 4)
  {
    *NBARS = 12;
    *COLNUM = 3;
  }
}

void get_peds(int runnumber, int NPlane, int NBARS, int COLNUM)
{
  const int CANVAS_SIZE_X = 1200;
  const int CANVAS_SIZE_Y = 800;

  TChain *t1 = new TChain("T");
  TString filename = "../../../ellana/ROOTfiles/e05102_R_";
  filename+=runnumber;
  filename+=".root";
  t1->Add(filename.Data());
  assert(t1);

  int num = t1->GetEntries();
  cout << "The Number of Events is: " << num << endl;

  Double_t NA_nd_LA[NBARS];
  Double_t NA_nd_RA[NBARS];
  Double_t evtype;

  TString leftname;
  TString rightname;

  if (NPlane == 0)
  {
    leftname = "NA.veto.la";
    rightname = "NA.veto.ra";
  }
  else
  {
    leftname = "NA.nd.p";
    leftname +=  NPlane;
    leftname += ".la";
    rightname = "NA.nd.p";
    rightname += NPlane;
    rightname += ".ra";
  }
  t1->SetBranchAddress(leftname, &NA_nd_LA);
  t1->SetBranchAddress(rightname, &NA_nd_RA);
  t1->SetBranchAddress("D.evtype", &evtype);

// ********* Histograms without cut ******************

  TH1F *Histograms_NA_nd_LA[NBARS];
  TH1F *Histograms_NA_nd_RA[NBARS];
  TString imagename;
  TString ime1;
  TString ime2;
  TString ime3;
  TString ime4;
  TString title="";

  double Right_max[NBARS];
  double Right_min[NBARS];
  double Left_max[NBARS];
  double Left_min[NBARS];

  for (int j=0; j<NBARS; j++)
  {
    Right_min[j] = RPedMin;
    Right_max[j] = RPedMax;
    Left_min[j] = LPedMin;
    Left_max[j] = LPedMax;
  }

  for (int i=0; i<NBARS; i++)
  {
    title = "Pedestal_Run_#";
    title += runnumber;
    title += " -> Paddle #";
    title += i+1;

    if (NPlane == 0)
    {
      ime3 = "NA_nd_veto_LA";
      ime4 = "NA_nd_veto_RA";
    }
    else
    {
      ime3 = "NA_nd_n";
      ime3 += NPlane;
      ime3 += "_LA";
      ime4 = "NA_nd_n";
      ime4 += NPlane;
      ime4 += "_RA";
    }
    ime3 += i;
    ime4 += i;
    cout << "Data3: " << ime3.Data() << endl;
    cout << "Data4: " << ime4.Data() << endl;

    Histograms_NA_nd_LA[i] = new TH1F(ime3, title, int (Left_max[i]-Left_min[i]), Left_min[i], Left_max[i]);
    Histograms_NA_nd_RA[i] = new TH1F(ime4, title, int (Right_max[i]-Right_min[i]), Right_min[i], Right_max[i]);
  }

  cout << "************" << endl;

  for (int i=0; i<num; i++)
  {
    t1->GetEntry(i);
    if ((i%1000==0) && (i>0)) cout << i <<endl;
    for (int j=0; j<NBARS; j++) Histograms_NA_nd_LA[j]->Fill(NA_nd_LA[j]);
    for (int j=0; j<NBARS; j++) Histograms_NA_nd_RA[j]->Fill(NA_nd_RA[j]);
  }

// ******** 1D - ADC - Right Side Spectra ************

  TF1 *fitsR[NBARS];
  TCanvas *R_ADCHistograms;
  ofstream ERout;
  TString R_ADCHistogramName;
  TString wheretomakefile;
  if (NPlane == 0)
  {
    ERout.open("ped_data/more_ped_info/ND_nv_R_pedestals.dat");
    R_ADCHistogramName = "Veto_R_ADC_pedestal_fits";
  }
  else
  {
    wheretomakefile = "ped_data/more_ped_info/ND_n";
    wheretomakefile += NPlane;
    wheretomakefile += "_R_pedestals.dat";
    ERout.open(wheretomakefile);
    R_ADCHistogramName = "N";
    R_ADCHistogramName += NPlane;
    R_ADCHistogramName += "_R_ADC_pedestal_fits";
  }

  R_ADCHistograms = new TCanvas(R_ADCHistogramName, R_ADCHistogramName, CANVAS_SIZE_X, CANVAS_SIZE_Y);
  R_ADCHistograms->Divide(5,COLNUM);

  for (int k=0; k<NBARS; k++)
  {
    R_ADCHistograms->cd(k+1);
    Histograms_NA_nd_RA[k]->SetLineColor(kGreen);
    Histograms_NA_nd_RA[k]->Draw();
    R_ADCHistograms->Update();

    TString fitFuncName = "fit";
    fitFuncName += k;
    fitsR[k] = new TF1(fitFuncName, "gaus", Right_min[k], Right_max[k]);
    fitsR[k]->SetLineColor(kBlue);
    fitsR[k]->SetLineWidth(1);
    Histograms_NA_nd_RA[k]->Fit(fitsR[k],"RV");
    ERout << k << "  " << fitsR[k]->GetParameter(0) << "  " << fitsR[k]->GetParameter(1) << "  " << fitsR[k]->GetParameter(2) << endl;

    if (NPlane == 0)
    {
      imagename = "ped_data/ped_fit_pics/ND_nv_ADC_R_pedestal_fits.png";
    }
    else
    {
      imagename = "ped_data/ped_fit_pics/ND_n";
      imagename += NPlane;
      imagename += "_ADC_R_pedestal_fits.png";
    }
    R_ADCHistograms->Print(imagename);
  }
  ERout.close();


// ******** 1D - ADC - Left Side Spectra ************

  TF1 *fitsL[NBARS];
  TCanvas *L_ADCHistograms;
  ofstream ELout;
  TString L_ADCHistogramName;
  if (NPlane == 0)
  {
    ELout.open("ped_data/more_ped_info/ND_nv_L_pedestals.dat");
    L_ADCHistogramName = "Veto_L_ADC_pedestal_fits";
  }
  else
  {
    wheretomakefile = "ped_data/more_ped_info/ND_n";
    wheretomakefile += NPlane;
    wheretomakefile += "_L_pedestals.dat";
    ELout.open(wheretomakefile);
    L_ADCHistogramName = "N";
    L_ADCHistogramName += NPlane;
    L_ADCHistogramName += "_L_ADC_pedestal_fits";
  }

  L_ADCHistograms = new TCanvas(L_ADCHistogramName, L_ADCHistogramName, CANVAS_SIZE_X, CANVAS_SIZE_Y);
  L_ADCHistograms->Divide(5,COLNUM);

  for (int k=0; k<NBARS; k++)
  {
    L_ADCHistograms->cd(k+1);
    Histograms_NA_nd_LA[k]->SetLineColor(kGreen);
    Histograms_NA_nd_LA[k]->Draw();
    L_ADCHistograms->Update();

    TString fitFuncName = "fit";
    fitFuncName += k;
    fitsL[k] = new TF1(fitFuncName, "gaus", Left_min[k], Left_max[k]);
    fitsL[k]->SetLineColor(kBlue);
    fitsL[k]->SetLineWidth(1);
    Histograms_NA_nd_LA[k]->Fit(fitsL[k],"RV");
    ELout << k << "  " << fitsL[k]->GetParameter(0) << "  " << fitsL[k]->GetParameter(1) << "  " << fitsL[k]->GetParameter(2) << endl;

    if (NPlane == 0)
    {
      imagename = "ped_data/ped_fit_pics/ND_nv_ADC_L_pedestal_fits.png";
    }
    else
    {
      imagename = "ped_data/ped_fit_pics/ND_n";
      imagename += NPlane;
      imagename += "_ADC_L_pedestal_fits.png";
    }
    L_ADCHistograms->Print(imagename);
  }
  ELout.close();




// *************** Pedestal Output to Single File ***************************
// If this is working, it should put the mean position for both the left and
// right sides into a single *.dat file that will be easily transferred into
// the neutron detector database.

  ofstream Eout;
  TString wheretoputfile;
  if (NPlane == 0){
    wheretoputfile = "ped_data/ND_nv_pedestals.dat";
  }
  else
  {
    wheretoputfile = "ped_data/ND_n";
    wheretoputfile += NPlane;
    wheretoputfile += "_pedestals.dat";
  }
  Eout.open(wheretoputfile);

  for (int k=0; k<NBARS; k++)
  {
    int LMean = int(fitsL[k]->GetParameter(1));
    int RMean = int(fitsR[k]->GetParameter(1));

    Eout << "     " << LMean << "     " << RMean << "                            " << "- Paddle" << (k+1) << "   (Left/Right)" << endl;
  }
  Eout.close();

}



// *******************************************************************
// This does the Gain Calculation
// *******************************************************************
void gain_calculation()
{
  double ped;
  double ADCunmod;
  double ADCold;
  double Vold;
  double ADCnew = 2000;
  double Vnew;

    cout << "Where is the pedestal?" << endl;
    cin >> ped;
    cout << "What channel is the current ADC peak on?" << endl;
    cin >> ADCunmod;
    cout << "What is the current HV?" << endl;
    cin >> Vold;
    ADCold = ADCunmod - ped;

    Vnew=(Vold)*pow(ADCnew/ADCold,(1.0/12.0));

    cout << "The HV you should use is: " << Vnew << endl;
}



// *******************************************************************
// This should set the styling for the GUI outputs and histograms
// *******************************************************************
void HallA_Style()
{
  gROOT->SetStyle("Plain");
  gStyle->SetPaperSize(TStyle::kUSLetter);
  gStyle->SetPaperSize(18,22);
  gStyle->SetOptFit(1111);
  gStyle->SetPalette(1);
  gStyle->SetNdivisions(505);
  gStyle->SetCanvasColor(kMagenta-10);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadLeftMargin(0.1);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadBottomMargin(0.1);
  gStyle->SetTitleYOffset(1.3);
  gStyle->SetLabelFont(42,"X");
  gStyle->SetLabelFont(42,"Y");

  // A quite gStyle Map:
  //  1 = solid
  //  2 = long dash (30 10)
  //  3 = dotted (4 8)
  //  4 = dash dot (15 12 4 12)
  //  5 = short dash (15 15)
  //  6 = dash dot dot (15 12 4 12 4 12)

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
  gStyle->SetDateY(0.98);
  gStyle->SetStripDecimals(kFALSE);
  gStyle->SetEndErrorSize(7);
}


// *******************************************************************
// This is the Main Script, it runs the subscripts
// *******************************************************************
void pedestals()
{
  int runnumber;
  cout << endl << "Good morning!"<< endl << "I would like to help you look at your data." << endl << "Please enter a run number so that I may happily chomp my way through your pretty data: " << endl;
  cin >> runnumber;

  HallA_Style();

  int NBARS;
  int COLNUM;

  for (int NPlane=0; NPlane < 5; NPlane++){
    get_NBars(NPlane, &NBARS, &COLNUM);
    get_peds(runnumber, NPlane, NBARS, COLNUM);
  }
//  gain_calculation();

  cout << "We've reached the end! That data sure was delicious..." << endl;
}


