// ***************************************************
//
// This script will plot the beam asymmetry with
// neutron cuts included. It will do this by looking
// at the number of unique helicity up(down) events in each
// bar, plotting them, then adding the plots together
// for each bar with a final asymmetry found at the
// end.
//
// 2011-02-07
// Elena Long
//
// Edited to include:
//	2011-02-09
//		Better error analysis
//		Final asymmetry text file
//	2011-06-08
//		Adjusted to process through a single 
//		root file that contains a big chunk 
//		of the data
// ***************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <math.h>
#include <iomanip>
#include "hand_draw.h"
#include "hand_scaling_factors.h"
#include "hand_class_draw_basic.h"
#include "hand_class_veto_cuts.h"
#include "hand_class_draw_bar_by_bar_cuts.h"
#include "hand_class_draw_tof_nu_run_by_run.h"

using namespace std;


// ******************************************************************
// ******************************************************************
// ******************************************************************
// ************************** IMPORTANT *****************************
// ******************************************************************
// ** If this doesn't seem to be working because it's missing a    **
// ** *.root file, make sure that you made it using the add_*.C    **
// ** files in the add_root_files directory above                  **
// ** (neutron_hunt/add_root_files)                                **
// ******************************************************************
// ******************************************************************
// ******************************************************************
// ******************************************************************


// Search for HAND to get to the PMT definitions

void add_class_targ_asymmetry_vs_runnum(){

	TString targ;
	TString kine;
	TString veto;
	TString barbybar;
	bool check = false;

	cout << "Which target do you want to look at? (v=vertical 3He, l=longitudinal 3He, t=transverse 3He, c=All Carbon, h=All Hydrogen, n=All Nitrogen, vc=Vertish Carbon, ltc=Longtransish Carbon, vh=Vertish Hydrogen, lth=Longtransish Hydrogen, ltn=Longtransish Nitrogen)" << endl;
	cin >> targ;
	if ((targ == "v") || (targ == "l") || (targ == "t") || (targ == "c") || (targ == "vc") || (targ == "ltc") || (targ == "h") || (targ == "vh") || (targ == "lth") || (targ == "n") || (targ == "ltn")) { check = true;}
	if (!check) {cout << "Not a valid entry. Exiting..." << endl; return 0;} 
	check = false;
	cout << "What Q2 do you want to look at? (1.0, 0.5, 0.42, 0.4, 0.1)" << endl;
	cin >> kine;
	if ((kine == "1.0") || (kine == "0.5") || (kine == "0.42") || (kine == "0.4") || (kine == "0.1")) { check = true;}
	if (!check) {cout << "Not a valid entry. Exiting..." << endl; return 0;}
	check = false;
	cout << "Do you want data with vetos or without vetos? (w, wo)" << endl;
	cin >> veto;
	if ((veto == "w") || (veto == "wo")) { check = true;}
	if (!check) { cout << "Not a valid entry. Exiting..." << endl; return 0;}
	check = false;
	cout << "Do you want to include bar-by-bar cuts? (y, n)" << endl;
	cin >> barbybar;
	if ((barbybar == "y") || (barbybar == "n")) { check = true;}
	if (!check) { cout << "Not a valid entry. Exiting..." << endl; return 0;}

	cout << "Did I make it here?" << endl;

	bool drawCuts = true;
//	bool drawCuts = false;

	bool includeVetos;
	if (veto == "w") {includeVetos = true;}
	if (veto == "wo") {includeVetos = false;}

        int HeStartRunNumber;
        int HeRunNumber;
        int endHeStartRunNumber;
        int endHeRunNumber;
        TString outputPlotsHere;
        const int nuBins = 10;
        TString filenameHe;
        TString outFileName;
        bool fileExists;
        int totesUpEvents;
        int totesDownEvents;
        double totesPosStuff;
        double totesNegStuff;
        double totesAsym;
        double totesError;


	if (kine == "1.0")
	{
//		if (targ == "v") {HeStartRunNumber = 20579; endHeStartRunNumber = 20789;}
		if (targ == "v") {HeStartRunNumber = 20596; endHeStartRunNumber = 20789;}
//		if (targ == "v") {HeStartRunNumber = 20751; endHeStartRunNumber = 20760;}
//		if (targ == "v") {HeStartRunNumber = 20751; endHeStartRunNumber = 20760;}
		if (targ == "l") {HeStartRunNumber = 22393; endHeStartRunNumber = 22437;}
		if (targ == "t") {HeStartRunNumber = 22447; endHeStartRunNumber = 22489;}
		if (targ == "vc") {HeStartRunNumber = 20591; endHeStartRunNumber = 20734;}
		if (targ == "ltc") {HeStartRunNumber = 22380; endHeStartRunNumber = 22461;}
		if (targ == "vh") {HeStartRunNumber = 20791; endHeStartRunNumber = 20792;}
		if (targ == "lth") {HeStartRunNumber = 22441; endHeStartRunNumber = 22441;}
		if (targ == "ltn") {HeStartRunNumber = 22442; endHeStartRunNumber = 22442;}
//		double nuMax = 0.65;
//		double nuMin = 0.35;
		double nuMax = 0.7;
		double nuMin = 0.3;
	}
	if (kine == "0.5")
	{
		if (targ == "v") {HeStartRunNumber = 20890; endHeStartRunNumber = 21006;}
//		if (targ == "v") {HeStartRunNumber = 20922; endHeStartRunNumber = 20922;}
		if (targ == "h") {HeStartRunNumber = 21383; endHeStartRunNumber = 21387;}
		double nuMax = 0.35;
		double nuMin = 0.1;
	}
	if (kine == "0.4")
	{
		if (targ == "l") {HeStartRunNumber = 21813; endHeStartRunNumber = 22138;}
		if (targ == "t") {HeStartRunNumber = 21693; endHeStartRunNumber = 22312;}
		double nuMax = 0.4;
		double nuMin = 0.1;
	}

	if (kine == "0.1")
	{
		if (targ == "v") {HeStartRunNumber = 20487; endHeStartRunNumber = 20511;}
//		if (targ == "v") {HeStartRunNumber = 20498; endHeStartRunNumber = 20511;}
//		if (targ == "v") {HeStartRunNumber = 20533; endHeStartRunNumber = 20538;}
		if (targ == "h") {HeStartRunNumber = 20404; endHeStartRunNumber = 20407;}
//		if (targ == "v") {HeStartRunNumber = 20487; endHeStartRunNumber = 20538;}
		double nuMin = 0.01;
		double nuMax = 0.13;
	}
	
	TString outputPlotsHere = "/home/ellie/physics/e05-102/images/plots_for_hand/add_class_targ_asymmetry_vs_runnum/";

	const int nuBins = 10;

	TChain* chainHe = new TChain("T");
	TString filenameHe;
	TString outFileName;

	filenameHe = "/home/ellie/physics/e05-102/analysis-scripts/devel/neutron_hunt/results/targ_ssa/";
	if (veto == "w") {filenameHe += "with_vetos/";}			
	if (veto == "wo") {filenameHe += "without_vetos/";}			
	if (targ == "v") {filenameHe += "vert_3he_";}
	if (targ == "l") {filenameHe += "long_3he_";}
	if (targ == "t") {filenameHe += "trans_3he_";}
	if (targ == "c") {filenameHe += "carbon_";}
	if (targ == "vc") {filenameHe += "v_carbon_";}
	if (targ == "ltc") {filenameHe += "lt_carbon_";}
	if (targ == "h") {filenameHe += "hydrogen_";}
	if (targ == "vh") {filenameHe += "v_hydrogen_";}
	if (targ == "lth") {filenameHe += "lt_hydrogen_";}
	if (targ == "n") {filenameHe += "nitrogen_";}
	if (targ == "ltn") {filenameHe += "lt_nitrogen_";}
	if (kine == "1.0") {filenameHe += "q2_1";}
	if (kine == "0.5") {filenameHe += "q2_05";}
	if (kine == "0.1") {filenameHe += "q2_01";}
	if (kine == "0.42") {filenameHe += "q2_042";}
	if (kine == "0.4") {filenameHe += "q2_04";}
	outFileName = filenameHe;
	filenameHe += ".root";

	TString asymOutFileName = outFileName;
	asymOutFileName += "_asym_v_runnum_for_runs_";
	asymOutFileName += HeStartRunNumber;
	asymOutFileName += "-";
	asymOutFileName += endHeStartRunNumber;
	asymOutFileName += ".txt";
	ofstream asymOutFile;
	asymOutFile.open(asymOutFileName);
	cout << "The output root file is located at " << filenameHe << endl;
	cout << "The output txt file is located at " << asymOutFileName << endl;

        if ((targ == "v") || (targ == "l") || (targ == "t") || (targ == "c") || (targ == "h")) { check = true;}
        if (targ == "v") {asymOutFile << "Dataset:      Vertical 3He, Q2=" << kine << endl; cout << "Dataset:   Vertical 3He, Q2=" << kine << endl;}
        if (targ == "l") {asymOutFile << "Dataset:      Longitudinal 3He, Q2=" << kine << endl; cout << "Dataset:       Longitudinal 3He, Q2=" << kine << endl;}
        if (targ == "t") {asymOutFile << "Dataset:      Transverse 3He, Q2=" << kine << endl; cout << "Dataset: Transverse 3He, Q2=" << kine << endl;}
        if (targ == "c") {asymOutFile << "Dataset:      Carbon, Q2=" << kine << endl; cout << "Dataset: Carbon, Q2=" << kine << endl;}
        if (targ == "h") {asymOutFile << "Dataset:      Hydrogen, Q2=" << kine << endl; cout << "Dataset:       Hydrogen, Q2=" << kine << endl;}
        asymOutFile << "Runs:   " << HeStartRunNumber << "-" << endHeStartRunNumber << endl;
//        asymOutFile << "Run #   Asymmetry       Stat. Error     # HePos Events  HePos Charge    PosHe LT        # Neg Events    HeNeg Charge    NegHe LT" << endl;
//        asymOutFile << "Run #	Raw Asym	Stat Err	# Pos Event	HePos	Charge	PosHe LT	# Neg Events	HeNeg	Charge    NegHe LT" << endl;
//		asymOutFile << "Run #	TotalUp	TotalDown	Bin1Up	Bin1Down	Bin2Up	Bin2Down	Bin3Up	Bin3Down	Bin4Up	Bin4Down" << endl;
		asymOutFile << "Run #	Bin3Up	Bin3Down	Tup	Tdn	BGLup	BGLdn	BGRup	BGRdn	RSup	RSdn	RBG" << endl;
		TString asymOutFileText;
        for (int k=HeStartRunNumber; k<(endHeStartRunNumber+1); k++)
        {
                totesPosStuff = 0;
                totesNegStuff = 0;
                totesUpEvents = 0;
                totesDownEvents = 0;
                HeRunNumber = k;
                endHeRunNumber = k;
                outputPlotsHere = "/home/ellie/physics/e05-102/images/plots_for_hand/add_class_targ_asymmetry_vs_runnum/";

//                filenameHe = "/work/halla/e05102/disk1/ellie/results/";
                filenameHe = "/home/ellie/physics/e05-102/results/";
                if (kine == "1.0") {filenameHe += "q2_1_";}
                if (kine == "0.5") {filenameHe += "q2_05_";}
                if (kine == "0.1") {filenameHe += "q2_01_";}
                if (kine == "0.4") {filenameHe += "q2_04_";}
                if (targ == "v") {filenameHe += "vert_3he/";}
                if (targ == "l") {filenameHe += "long_3he/";}
                if (targ == "t") {filenameHe += "trans_3he/";}
                if (targ == "c") {filenameHe += "carbon/";}
                if (targ == "vc") {filenameHe += "carbon/";}
                if (targ == "ltc") {filenameHe += "carbon/";}
                if (targ == "h") {filenameHe += "hydrogen/";}
                if (targ == "vh") {filenameHe += "hydrogen/";}
                if (targ == "lth") {filenameHe += "hydrogen/";}
                if (targ == "n") {filenameHe += "nitrogen/";}
                if (targ == "ltn") {filenameHe += "nitrogen/";}
                if (veto == "w") {filenameHe += "neutron_cuts-";}
                if (veto == "wo") {filenameHe += "no_vetos-";}
                filenameHe += "hand_target_asym_vs_nu_for_run_";
                filenameHe += k;
                filenameHe += ".root";

                cout << "Using filenameHe: " << filenameHe << endl;

		ifstream ifileHe(filenameHe);
                if (ifileHe)
                {
                        cout << "Processing Run " << filenameHe << endl;
                        fileExists = true;
                }
                else
                {
                        cout << "Run " << filenameHe << " does not exist." << endl;
                        fileExists = false;
		}

	if (fileExists)
	{

	TFile fileHe(filenameHe);
	cout << "fileHe: " << filenameHe << endl;
	gStyle->SetPalette(1);

// **********************************************************************************************
	gStyle->SetOptFit(1111);
	TString allVetos = "";
	int maxbars = 0;

// **********************************************************************************************
// This bit of code should set the charge and livetime scaling factors
	double HeChargeScale; double Helivetime;
	double HeChargeScaleUp; double HelivetimeUp;
	double HeChargeScaleDown; double HelivetimeDown;
	double BeamChargeScaleUp; double BeamlivetimeUp;
	double BeamChargeScaleDown; double BeamlivetimeDown;
	hand_scaling_factors(HeRunNumber, endHeRunNumber, HeChargeScale, Helivetime, HeChargeScaleUp, HelivetimeUp, HeChargeScaleDown, HelivetimeDown, BeamChargeScaleUp, BeamlivetimeUp, BeamChargeScaleDown, BeamlivetimeDown, kine, targ);
	HeChargeScale = 0.00001 * int(HeChargeScale * 100000.0 + 0.5);
	HeChargeScaleUp = 0.00001 * int(HeChargeScaleUp * 100000.0 + 0.5);
	HeChargeScaleDown = 0.00001 * int(HeChargeScaleDown * 100000.0 + 0.5);
	BeamChargeScaleUp = 0.00001 * int(BeamChargeScaleUp * 100000.0 + 0.5);
	BeamChargeScaleDown = 0.00001 * int(BeamChargeScaleDown * 100000.0 + 0.5);
	Helivetime = 0.0001 * int(Helivetime * 10000.0 + 0.5);
	HelivetimeUp = 0.0001 * int(HelivetimeUp * 10000.0 + 0.5);
	HelivetimeDown = 0.0001 * int(HelivetimeDown * 10000.0 + 0.5);
	BeamlivetimeUp = 0.0001 * int(BeamlivetimeUp * 10000.0 + 0.5);
	BeamlivetimeDown = 0.0001 * int(BeamlivetimeDown * 10000.0 + 0.5);
	cout << "HeChargeScale: " << HeChargeScale << "C, Helivetime: " << Helivetime << endl;
	cout << "HeChargeScaleUp: " << HeChargeScaleUp << "C, HelivetimeUp: " << HelivetimeUp << endl;
	cout << "HeChargeScaleDown: " << HeChargeScaleDown << "C, HelivetimeDown: " << HelivetimeDown << endl;
	cout << "BeamChargeScaleUp: " << BeamChargeScaleUp << "C, BeamlivetimeUp: " << BeamlivetimeUp << endl;
	cout << "BeamChargeScaleDown: " << BeamChargeScaleDown << "C, BeamlivetimeDown: " << BeamlivetimeDown << endl;

// **********************************************************************************************

// The section below plots the HAND data
// **********************************************************************************************
	hand_class_draw_basic(HeRunNumber, endHeRunNumber, drawCuts, kine, filenameHe, targ, outputPlotsHere);
//	int whichplane = 0;
	int whichplane = 1;
	int endplane = 5;
	int whichbar=0;
//	int whichbar=11;
	for (int nplane=whichplane; nplane<endplane; nplane++)
	{
		if (nplane==0) maxbars=32;
		if (nplane==1) maxbars=30;
		if (nplane==2) maxbars=24;
		if (nplane==3) maxbars=22;
		if (nplane==4) maxbars=12;
		for (int thisbar=whichbar; thisbar<maxbars; thisbar++)
		{
			hand_class_veto_cuts(includeVetos, nplane, thisbar, allVetos);
			
			if (barbybar=="y") {hand_class_draw_bar_by_bar_cuts(HeRunNumber, endHeRunNumber, nplane, thisbar, allVetos ,filenameHe, kine, targ, outputPlotsHere, includeVetos);}
		}
	}

	hand_class_draw_tof_nu(HeRunNumber, endHeRunNumber, filenameHe, kine, targ, asymOutFileText, includeVetos, nuBins, nuMin, nuMax, HeChargeScaleUp, HeChargeScaleDown, HelivetimeUp, HelivetimeDown, outputPlotsHere);
        asymOutFile << asymOutFileText << endl;
	} 

/*	TString exitst;
	cout << "Are you ready to finish?" << endl;
	cin >> exitst;
*/	}

	cout << "The output root file is located at " << filenameHe << endl;
	cout << "The output txt file is located at " << asymOutFileName << endl;



	asymOutFile.close();
	cout << "All done!" << endl;

}







































