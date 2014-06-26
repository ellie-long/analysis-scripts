// Once this is all set up, what I'm hoping it will do is take in
// a run number and then apply cuts from all of the surrounding bars
// along with the pedestal corrected ADC being greater than 30 
// This should eliminate nearly everything except for the neutrons
// that deposited their energy in any given scintillator bar.
//
// Elena Long (ellie@jlab.org)
// 05/14/09


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
#define RPedMax 1600.0
#define LPedMin 0.0
#define LPedMax 1600.0

// *******************************************************************
// This should change NBars to the number
// of bars in the plane that the program
// is currently looking at. NPlane 0 = Veto, 
// 1 = N1, 2 = N2, 3 = N3, and 4 = N4.
// *******************************************************************
void get_NBars(int NPlane, int &NBARS, int &COLNUM)
{
  if (NPlane == 0)
  {
    NBARS = 32;
    COLNUM = 7;
  }
  if (NPlane == 1)
  {
    NBARS = 30;
    COLNUM = 6;
  }
  if (NPlane == 2)
  {
    NBARS = 24;
    COLNUM = 5;
  }
  if (NPlane == 3)
  {
    NBARS = 22;
    COLNUM = 5;
  }
  if (NPlane == 4)
  {
    NBARS = 12;
    COLNUM = 3;
  }
}




// ********************************************************************
// get_peds is a remake of the pedestal analysis software from that was
// swiped from Miha awhile ago and alterted so that it would work for
// the HAND instead of BB
// ********************************************************************
void apply_cuts(int runnumber, int NPlane, const int NBARS, int COLNUM)
{
  const int CANVAS_SIZE_X = 1200;
  const int CANVAS_SIZE_Y = 800;

  TChain *t1 = new TChain("T");
  TString filename = "/home/ellie/physics/terabyte/ROOTfiles/e05102_R_";
  filename+=runnumber;
  filename+=".root";
  t1->Add(filename.Data());
  assert(t1);

  int num = t1->GetEntries();

// The following commetend out Things are for testing only:

  cout << "For Testing Purposes Only, Comment this out when things are working." << endl << "We're on Plane " << NPlane << endl <<"How many events would you like to analyze?" << endl;
  cin >>  num;

// Comment out above once things are working


  cout << "The Number of Events is: " << num << endl;

  Double_t NA_nd_LT[NBARS];
  Double_t NA_nd_RT[NBARS];
  Double_t evtype;

  TString leftname;
  TString rightname;

  if (NPlane == 0)
  {
    leftname = "NA.veto.lt";
    rightname = "NA.veto.rt";
  }
  else
  {
    leftname = "NA.nd.p";
    leftname +=  NPlane;
    leftname += ".lt";
    rightname = "NA.nd.p";
    rightname += NPlane;
    rightname += ".rt";
  }
  t1->SetBranchAddress(leftname, &NA_nd_LT);
  t1->SetBranchAddress(rightname, &NA_nd_RT);
  t1->SetBranchAddress("D.evtype", &evtype);

// ********* Histograms without cut ******************

  TH1F *Histograms_NA_nd_LT[NBARS];
  TH1F *Histograms_NA_nd_RT[NBARS];
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
    title = "Run #";
    title += runnumber;
    title += " -> Paddle #";
    title += i+1;

    if (NPlane == 0)
    {
      ime3 = "NA_nd_veto_LT";
      ime4 = "NA_nd_veto_RT";
    }
    else
    {
      ime3 = "NA_nd_n";
      ime3 += NPlane;
      ime3 += "_LT";
      ime4 = "NA_nd_n";
      ime4 += NPlane;
      ime4 += "_RT";
    }
    ime3 += i;
    ime4 += i;
    cout << "Data3: " << ime3.Data() << endl;
    cout << "Data4: " << ime4.Data() << endl;

    Histograms_NA_nd_LT[i] = new TH1F(ime3, title, int (Left_max[i]-Left_min[i]), Left_min[i], Left_max[i]);
    Histograms_NA_nd_RT[i] = new TH1F(ime4, title, int (Right_max[i]-Right_min[i]), Right_min[i], Right_max[i]);
  }

  cout << "************" << endl;

  for (int i=0; i<num; i++)
  {
    t1->GetEntry(i);
    if ((i%1000==0) && (i>0)) cout << i <<endl;
    for (int j=0; j<NBARS; j++) Histograms_NA_nd_LT[j]->Fill(NA_nd_LT[j]);
    for (int j=0; j<NBARS; j++) Histograms_NA_nd_RT[j]->Fill(NA_nd_RT[j]);
  }

// ******** 1D - TDC - Right Side Spectra ************

  TF1 *fitsR[NBARS];
  TCanvas *R_TDCHistograms;
//  ofstream ERout;
  TString R_TDCHistogramName;
//  TString wheretomakefile;
  if (NPlane == 0)
  {
//    ERout.open("ped_data/more_ped_info/ND_nv_R_pedestals.dat");
    R_TDCHistogramName = "Veto_R_TDC_pedestal_fits";
  }
  else
  {
//    wheretomakefile = "ped_data/more_ped_info/ND_n";
//    wheretomakefile += NPlane;
//    wheretomakefile += "_R_pedestals.dat";
//    ERout.open(wheretomakefile);
    R_TDCHistogramName = "N";
    R_TDCHistogramName += NPlane;
    R_TDCHistogramName += "_R_TDC_pedestal_fits";
  }

  cout << "R_TDCHistogramName: " << R_TDCHistogramName << endl;
  R_TDCHistograms = new TCanvas(R_TDCHistogramName, R_TDCHistogramName, CANVAS_SIZE_X, CANVAS_SIZE_Y);
  R_TDCHistograms->Divide(5,COLNUM);
// Below is a bunch of if loops to figure out what plane we're in and then
// using a bunch of for loops to make a cuts on every bar in every plane
// except for the current NPlane


  TCut cuts1;
  TCut cuts2;
  TString cutstring = "";
  TString cutstring2 = "";

  if (NPlane!=0)
  {
    for (int v=0; v<=31; v++)
    {
      cutstring += "NA.veto.rt[";
      cutstring += v;
      cutstring += "]&&";
    }
    cout << "Made it through the veto cuts" << endl;
  }

  if (NPlane!=1)
  {
    for (int n1=0; n1<29; n1++)
    {
      cutstring += "NA.nd.p1.rt[";
      cutstring += n1;
      cutstring += "]&&";
    }
    cout << "Made it through the Plane 1 cuts" << endl;
  }

  if (NPlane!=2)
  {
    for (int n2=0; n2<=23; n2++)
    {
      cutstring += "NA.nd.p2.rt[";
      cutstring += n2;
      cutstring += "]&&";
    }
    cout << "Made it through the Plane 2 cuts" << endl;
  }

  if (NPlane!=3)
  {
    for (int n3=0; n3<=21; n3++)
    {
      cutstring += "NA.nd.p3.rt[";
      cutstring += n3;
      if (NPlane==4 && n3==21)
      {
        cutstring += "]";
      }
      else
      {
        cutstring += "]&&";
      }
    }
    cout << "Made it through the Plane 3 cuts" << endl;
  }

  if (NPlane!=4)
  {
    for (int n4=0; n4<=11; n4++)
    {
      cutstring += "NA.nd.p4.rt[";
      cutstring += n4;
      if (n4==11)
      {
        cutstring += "]";
      }
      else
      {
        cutstring += "]&&";
      }
    }
    cout << "Made it through the Plane 4 cuts" << endl;
  }

  if (NPlane==0)
  {
    cutstring = "";
    cout << "Veto Plane has no cuts" << endl;
  }

  for (int k=0; k<NBARS; k++)
  {
    if (NPlane!=0)
    {
      cout << "NBARS: " << NBARS << endl;
      for (int n=0; n<=NBARS; n++)
      {
        if (k != n)
        {
          cout << "Making cut on Plane " << NPlane << ", Bar " << n+1 << endl;
          cutstring2 += "NA.nd.p";
          cutstring2 += NPlane;
          cutstring2 += ".rt[";
          cutstring2 += n;
          if (n == NBARS-1)
          {
            cutstring2 += "]";
          }
          else
          {
            cutstring2 += "]&&";
          }
        }
      }
      cout << "Made it past the Plane " << NPlane << " cuts" << endl;
    }


    R_TDCHistograms->cd(k+1);
    cout << "About to apply cutstrings to cuts..." << endl;
    cuts1 = cutstring;
    cuts2 = cutstring2;
    cout << "Applied cutstrings to cuts." << endl;
    Histograms_NA_nd_RT[k]->SetLineColor(kGreen);
    TString currentbar = "NA.nd.p";
    currentbar += NPlane;
    currentbar += ".rt[";
    currentbar += k;
    currentbar += "]";
    Histograms_NA_nd_RT[k]->Draw();
    R_TDCHistograms->Update();

//    TString fitFuncName = "fit";
//    fitFuncName += k;
//    fitsR[k] = new TF1(fitFuncName, "gaus", Right_min[k], Right_max[k]);
//    fitsR[k]->SetLineColor(kBlue);
//    fitsR[k]->SetLineWidth(1);
//    Histograms_NA_nd_RT[k]->Fit(fitsR[k],"RV");
//    ERout << k << "  " << fitsR[k]->GetParameter(0) << "  " << fitsR[k]->GetParameter(1) << "  " << fitsR[k]->GetParameter(2) << endl;


    if (NPlane == 0)
    {
      imagename = "ped_data/ped_fit_pics/ND_nv_TDC_R_pedestal_fits.png";
    }
    else
    {
      imagename = "ped_data/ped_fit_pics/ND_n";
      imagename += NPlane;
      imagename += "_TDC_R_pedestal_fits.png";
    }
 //   R_TDCHistograms->Print(imagename);
  }


//  ERout.close();


// ******** 1D - ADC - Left Side Spectra ************
/*
  TF1 *fitsL[NBARS];
   *L_ADCHistograms;
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

  L_ADCHistograms = new (L_ADCHistogramName, L_ADCHistogramName, CANVAS_SIZE_X, CANVAS_SIZE_Y);
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
*/



// *************** Pedestal Output to Single File ***************************
// If this is working, it should put the mean position for both the left and
// right sides into a single *.dat file that will be easily transferred into
// the neutron detector database.
/*
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
    peaks_left[k] = LMean;
    peaks_right[k] = RMean;
    Eout << "     " << LMean << "     " << RMean << "                             " << "- Paddle" << (k+1) << "   (Left/Right)" << endl;
  }
  Eout.close();
*/
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
void hunt_for_neutrons()
{
  int runnumber;
  cout << endl << "Good morning!"<< endl << "I would like to help you look at your data." << endl << "Please enter a run number so that I may happily chomp my way through your pretty data: " << endl;
  cin >> runnumber;

  HallA_Style();
  int NBARS;
  int COLNUM;

  for (int NPlane=1; NPlane < 5; NPlane++)
  {
    get_NBars(NPlane, NBARS, COLNUM);
    apply_cuts(runnumber, NPlane, NBARS, COLNUM);
  }

  cout << "We've reached the end! That data sure was delicious..." << endl;

  cout << "Just so you know, we didn't include the veto layer in all of that. Just sayin'." << endl;
}


