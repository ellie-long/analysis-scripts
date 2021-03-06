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

void single_run_add_class_targ_asymmetry_vs_nu(){

	TString targ;
	TString kine;
	TString veto;
	TString barbybar;
	bool check = false;

	bool left = true;
//	bool left = false;

//	bool fullBG = true;
	bool fullBG = false;

	cout << "Which target do you want to look at? (v=vertical 3He, l=longitudinal 3He, t=transverse 3He, c=All Carbon, h=All Hydrogen, n=All Nitrogen, vc=Vertish Carbon, ltc=Longtransish Carbon, vh=Vertish Hydrogen, lth=Longtransish Hydrogen, ltn=Longtransish Nitrogen)" << endl;
	cin >> targ;
	if ((targ == "v") || (targ == "l") || (targ == "t") || (targ == "c") || (targ == "vc") || (targ == "ltc") || (targ == "h") || (targ == "vh") || (targ == "lth") || (targ == "n") || (targ == "ltn")) { check = true;}
	if (!check) {cout << "Not a valid entry. Exiting..." << endl; return 0;} 
	check = false;
	cout << "What Q2 do you want to look at? (1.0, 0.5, 0.42, 0.1)" << endl;
	cin >> kine;
	if ((kine == "1.0") || (kine == "0.5") || (kine == "0.42") || (kine == "0.1")) { check = true;}
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

	int HeRunNumber;
	int endHeRunNumber;
	if (kine == "1.0")
	{
//		if (targ == "v") {HeRunNumber = 20579; endHeRunNumber = 20789;}
		if (targ == "v") {HeRunNumber = 20596; endHeRunNumber = 20789;}
//		if (targ == "v") {HeRunNumber = 20751; endHeRunNumber = 20760;}
//		if (targ == "v") {HeRunNumber = 20751; endHeRunNumber = 20760;}
		if (targ == "l") {HeRunNumber = 22393; endHeRunNumber = 22438;}
		if (targ == "t") {HeRunNumber = 22447; endHeRunNumber = 22489;}
		if (targ == "vc") {HeRunNumber = 20591; endHeRunNumber = 20734;}
		if (targ == "ltc") {HeRunNumber = 22380; endHeRunNumber = 22461;}
		if (targ == "vh") {HeRunNumber = 20791; endHeRunNumber = 20792;}
		if (targ == "lth") {HeRunNumber = 22441; endHeRunNumber = 22441;}
		if (targ == "ltn") {HeRunNumber = 22442; endHeRunNumber = 22442;}
		double nuMax = 0.65;
		double nuMin = 0.35;
	}
	if (kine == "0.5")
	{
		if (targ == "v") {HeRunNumber = 20890; endHeRunNumber = 21006;}
		if (targ == "h") {HeRunNumber = 21383; endHeRunNumber = 21387;}
		double nuMax = 0.425;
		double nuMin = 0.125;
	}
	if (kine == "0.1")
	{
		if (targ == "v") {HeRunNumber = 20487; endHeRunNumber = 20511;}
//		if (targ == "v") {HeRunNumber = 20498; endHeRunNumber = 20511;}
//		if (targ == "v") {HeRunNumber = 20533; endHeRunNumber = 20538;}
		if (targ == "h") {HeRunNumber = 20404; endHeRunNumber = 20407;}
//		if (targ == "v") {HeRunNumber = 20487; endHeRunNumber = 20538;}
		double nuMin = 0;
		double nuMax = 0.13;
	}
	
	TString outputPlotsHere = "/home/ellie/physics/e05-102/images/plots_for_hand/add_class_targ_asymmetry_vs_nu/";

	const int nuBins = 10;

	TChain* chainHe = new TChain("T");
	TString filenameHe;
	TString outFileName;

	char inputRunNumberStr [256];
	cout << "What Run Number?" << endl;
	cin >> inputRunNumberStr;

	int inputRunNumber = atoi (inputRunNumberStr);

	cout << "Using Run Number: " << inputRunNumber << endl;

	HeRunNumber = inputRunNumber;
	endHeRunNumber = inputRunNumber;

	int HeStartRunNumber = HeRunNumber;
	int endHeStartRunNumber = endHeRunNumber;
	TString runInfo = "Run #	#UpEvents	UpBG	UpBGErr	#DownEvents	DownBG	DownBGErr\n";

	for (int k=HeStartRunNumber; k<(endHeStartRunNumber+1); k++)
	{
		bool runExists=false;
		while (!runExists)
		{
			HeRunNumber = k;
			endHeRunNumber = k;

	
	//		filenameHe = "/home/ellie/physics/e05-102/analysis-scripts/devel/neutron_hunt/results/targ_ssa/";
			filenameHe = "/work/halla/e05102/disk1/ellie/results/";
			if (veto == "w") {filenameHe += "with_vetos/";}			
			if (veto == "wo") {filenameHe += "without_vetos/";}			
			if (kine == "1.0") {filenameHe += "q2_1_";}
			if (kine == "0.5") {filenameHe += "q2_05_";}
			if (kine == "0.1") {filenameHe += "q2_01_";}
			if (kine == "0.42") {filenameHe += "q2_042_";}
			if (targ == "v") {filenameHe += "vert_3he/";}
			if (targ == "l") {filenameHe += "long_3he/";}
			if (targ == "t") {filenameHe += "trans_3he/";}
			if (targ == "c") {filenameHe += "carbon/";}
			if (targ == "vc") {filenameHe += "v_carbon/";}
			if (targ == "ltc") {filenameHe += "lt_carbon/";}
			if (targ == "h") {filenameHe += "hydrogen/";}
			if (targ == "vh") {filenameHe += "v_hydrogen/";}
			if (targ == "lth") {filenameHe += "lt_hydrogen/";}
			if (targ == "n") {filenameHe += "nitrogen/";}
			if (targ == "ltn") {filenameHe += "lt_nitrogen/";}
			filenameHe += "hand_target_asym_vs_nu_for_run_";
			filenameHe += HeRunNumber;
			outFileName = "hand_target_asym_vs_nu_for_run_";
			outFileName += HeRunNumber;
			filenameHe += ".root";
		
		        ifstream ifileHe(filenameHe);
			if (ifileHe)
			{
				runExists = true;
			}
			else
			{
				runExists = false;
				k = k +1;
		//              If this loop is causing you problems, read the IMPORTANT note above
			}
		}	


		TString asymOutFileName = outFileName;
		asymOutFileName += "_ssa_target_asymmetry_runs_";
		asymOutFileName += HeRunNumber;
		asymOutFileName += "-";
		asymOutFileName += endHeRunNumber;
		asymOutFileName += ".txt";
	//	ofstream asymOutFile;
	//	asymOutFile.open(asymOutFileName);
	//
	//	ifstream ifileHe(filenameHe);
	//	if (ifileHe)
	//	{
	//		cout << "Adding file to chainHe: " << filenameHe << endl;
	//		chainHe->Add(filenameHe);
	//	}
	//	else
	//	{
	//		cout << "File " << filenameHe << " does not exist. Exiting..." << endl;
	//		return 0;
	//		If this loop is causing you problems, read the IMPORTANT note above
	//	}
	
		TFile fileHe(filenameHe);

		gStyle->SetPalette(1);
		

	// **********************************************************************************************
		gStyle->SetOptFit(1111);
		TString allVetos = "";
		int maxbars = 0;
	//	TString veto1plane = "";
	//	TString veto1bar = "";
	//	TString veto2plane = "";
	//	TString veto2bar = "";
	//	TString veto3plane = "";
	//	TString veto3bar = "";
	//	TString veto4plane = "";
	//	TString veto4bar = "";
	//	TString veto5plane = "";
	//	TString veto5bar = "";
	//	TString veto6plane = "";
	//	TString veto6bar = "";
	//	TString antiveto1plane = ""; 
	//	TString antiveto1bar = "";
	//	TString antiveto2plane = "";
	//	TString antiveto2bar = "";
	//	TString antiveto3plane = "";
	//	TString antiveto3bar = "";
	//	TString allAntivetos = "";
	//	TString vetoTDCslSt = "";
	//	TString vetoTDCsrSt = "";
	//	TCut vetoTDCsl = "";
	//	TCut vetoTDCsr = "";
	//	TCut vetoTDCs = "";
	//	TString antivetosTDCslSt = ""; 
	//	TString antivetosTDCsrSt = "";
	//	int vetoplane = 0;
	//	int padBins = 0;
	//	double padMin = 0;
	//	double padMax = 0;
	//
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

		hand_class_draw_tof_nu_run_by_run(HeRunNumber, endHeRunNumber, filenameHe, kine, targ, asymOutFileName, includeVetos, nuBins, nuMin, nuMax, HeChargeScaleUp, HeChargeScaleDown, HelivetimeUp, HelivetimeDown, outputPlotsHere, runInfo, left, fullBG);

	}


	cout << runInfo << endl;

	TString runInfoFileName = "/home/ellie/physics/e05-102/images/bg_info/";
	if (left && !fullBG) {runInfoFileName += "left_";}
	if (!left && !fullBG) {runInfoFileName += "right_";}
	if (fullBG) {runInfoFileName += "fullbg_";}
	runInfoFileName += "bg_info_for_runs_";
	runInfoFileName += HeStartRunNumber;
	runInfoFileName += "-";
	runInfoFileName += endHeStartRunNumber;
	runInfoFileName += "_";
	runInfoFileName += veto;
	runInfoFileName += "_vetos";
	runInfoFileName += ".txt";
	ofstream runInfoFile;
//	runInfoFile.open(runInfoFileName);
//	runInfoFile << runInfo;
	

	TString exitst;
	cout << "Are you ready to finish?" << endl;
	cin >> exitst;


	cout << "All done!" << endl;

}







































