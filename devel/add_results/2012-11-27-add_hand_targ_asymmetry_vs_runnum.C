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
#include "hand_define_vetos.h"
#include "hand_draw.h"
#include "hand_basic_cuts.h"
#include "hand_draw_vetos.h"
#include "hand_draw_antivetos.h"
#include "hand_scaling_factors.h"

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

void add_hand_targ_asymmetry_vs_runnum(){

	TString targ;
	TString kine;
	TString veto;
	bool check = false;

	cout << "Which target do you want to look at? (v=vertical 3He, l=longitudinal 3He, t=transverse 3He, c=All Carbon, h=All Hydrogen, n=All Nitrogen, vc=Vertish Carbon, ltc=Longtransish Carbon, vh=Vertish Hydrogen, lth=Longtransish Hydrogen, ltn=Longtransish Nitrogen)" << endl;
	cin >> targ;
	if ((targ == "v") || (targ == "l") || (targ == "t") || (targ == "c") || (targ == "vc") || (targ == "ltc") || (targ == "h") || (targ == "vh") || (targ == "lth") || (targ == "n") || (targ == "ltn")) { check = true;}
	if (!check) {cout << "Not a valid entry. Exiting..." << endl; return 0;} 
	check = false;
	cout << "What Q2 do you want to look at? (1.0, 0.5, 0.42)" << endl;
	cin >> kine;
	if ((kine == "1.0") || (kine == "0.5") || (kine == "0.42") || (kine == "0.1")) { check = true;}
	if (!check) {cout << "Not a valid entry. Exiting..." << endl; return 0;}
	check = false;
	cout << "Do you want data with vetos or without vetos? (w, wo)" << endl;
	cin >> veto;
	if ((veto == "w") || (veto == "wo")) { check = true;}
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
		if (targ == "v") {HeStartRunNumber = 20596; endHeStartRunNumber = 20789;}
//		if (targ == "v") {HeStartRunNumber = 20596; endHeStartRunNumber = 20598;}
//		if (targ == "v") {HeStartRunNumber = 20596; endHeStartRunNumber = 20760;}
//		if (targ == "v") {HeStartRunNumber = 20751; endHeStartRunNumber = 20760;}
//		if (targ == "v") {HeStartRunNumber = 20751; endHeStartRunNumber = 20760;}
		if (targ == "l") {HeStartRunNumber = 22393; endHeStartRunNumber = 22438;}
		if (targ == "t") {HeStartRunNumber = 22447; endHeStartRunNumber = 22489;}
		if (targ == "vc") {HeStartRunNumber = 20591; endHeStartRunNumber = 20734;}
		if (targ == "ltc") {HeStartRunNumber = 22380; endHeStartRunNumber = 22461;}
		if (targ == "vh") {HeStartRunNumber = 20791; endHeStartRunNumber = 20792;}
		if (targ == "lth") {HeStartRunNumber = 22441; endHeStartRunNumber = 22441;}
		if (targ == "ltn") {HeStartRunNumber = 22442; endHeStartRunNumber = 22442;}
		double nuMin = 0.35;
		double nuMax = 0.65;
	}
	if (kine == "0.5")
	{
		if (targ == "v") {HeStartRunNumber = 20890; endHeStartRunNumber = 21005;}
		double nuMin = 0.125;
		double nuMax = 0.425;
	}
	if (kine == "0.1")
	{
		if (targ == "v") {HeStartRunNumber = 20487; endHeStartRunNumber = 20538;}
		double nuMin = 0;
		double nuMax = 0.13;
	}


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
	outFileName = filenameHe;
	filenameHe += "_test.root";

	TString asymOutFileName = outFileName;
	asymOutFileName += "_ssa_target_asymmetry_v_runs_";
	asymOutFileName += HeStartRunNumber;
	asymOutFileName += "-";
	asymOutFileName += endHeStartRunNumber;
	asymOutFileName += ".txt";
	ofstream asymOutFile;
	asymOutFile.open(asymOutFileName);



	if ((targ == "v") || (targ == "l") || (targ == "t") || (targ == "c") || (targ == "h")) { check = true;}
	if (targ == "v") {asymOutFile << "Dataset:	Vertical 3He, Q2=" << kine << endl; cout << "Dataset:	Vertical 3He, Q2=" << kine << endl;}
	if (targ == "l") {asymOutFile << "Dataset:	Longitudinal 3He, Q2=" << kine << endl; cout << "Dataset:	Longitudinal 3He, Q2=" << kine << endl;}
	if (targ == "t") {asymOutFile << "Dataset:	Transverse 3He, Q2=" << kine << endl; cout << "Dataset:	Transverse 3He, Q2=" << kine << endl;}
	if (targ == "c") {asymOutFile << "Dataset:	Carbon, Q2=" << kine << endl; cout << "Dataset:	Carbon, Q2=" << kine << endl;}
	if (targ == "h") {asymOutFile << "Dataset:	Hydrogen, Q2=" << kine << endl; cout << "Dataset:	Hydrogen, Q2=" << kine << endl;}
	asymOutFile << "Runs:	" << HeStartRunNumber << "-" << endHeStartRunNumber << endl;
	asymOutFile << "Run #	Asymmetry	Stat. Error	# HePos Events	HePos Charge	PosHe LT	# Neg Events	HeNeg Charge	NegHe LT" << endl;


	for (int k=HeStartRunNumber; k<(endHeStartRunNumber+1); k++)
	{
		totesPosStuff = 0;
		totesNegStuff = 0;
		totesUpEvents = 0;
		totesDownEvents = 0;
		HeRunNumber = k;
		endHeRunNumber = k;
		outputPlotsHere = "/home/ellie/physics/e05-102/images/plots_for_hand/hand_beam_asymmetry_vs_nu/";

		TChain* chainHe = new TChain("T");

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
		if (targ == "vc") {filenameHe += "carbon/";}
		if (targ == "ltc") {filenameHe += "carbon/";}
		if (targ == "h") {filenameHe += "hydrogen/";}
		if (targ == "vh") {filenameHe += "hydrogen/";}
		if (targ == "lth") {filenameHe += "hydrogen/";}
		if (targ == "n") {filenameHe += "nitrogen/";}
		if (targ == "ltn") {filenameHe += "nitrogen/";}
		filenameHe += "hand_target_asym_vs_nu_for_run_";
		filenameHe += k;
		filenameHe += ".root";

		cout << "Using filenameHe: " << filenameHe << endl;

		ifstream ifileHe(filenameHe);
		if (ifileHe)
		{
			cout << "Adding file to chainHe: " << filenameHe << endl;
			chainHe->Add(filenameHe);
			fileExists = true;
		}
		else
		{
			fileExists = false;
/*			while (!fileExists)
			{
				ifstream ifileHe(filenameHe);	
				if (ifileHe)
				{
					cout << "Adding file to chainHe: " << filenameHe << endl;
					chainHe->Add(filenameHe);
					fileExists = true;
				}

				k++;
				cout << "File " << filenameHe << " does not exist. Trying " << k << "..." << endl;
				HeRunNumber = k;
				endHeRunNumber = k;
				filenameHe = "/work/halla/e05102/disk1/ellie/results/";
				if (veto == "w") {filenameHe += "with_vetos/";}
				if (veto == "wo") {filenameHe += "without_vetos/";}
				if (kine == "1.0") {filenameHe += "q2_1_";}
				if (kine == "0.5") {filenameHe += "q2_05_";}
				if (kine == "0.42") {filenameHe += "q2_042_";}
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
				filenameHe += "hand_target_asym_vs_nu_for_run_";
				filenameHe += k;
				filenameHe += ".root";
			}

*/
//			return 0;
//			If this loop is causing you problems, read the IMPORTANT note above
		}

		if (fileExists)
		{
		
			TFile fileHe(filenameHe);
			cout << "fileHe: " << filenameHe << endl;
			gStyle->SetPalette(1);

		//	hand_basic_cuts(cut, kinematics, eventtype, dp, target, tracks, thph, xbj, pssh, cerenkov, q2nu, basic, cuts, imageCutsTitle, HeRunNumber, endHeRunNumber, chainHe, numin, numax, q2min, q2max, bins, xmin, xmax, drawCuts, Q2);
		// **********************************************************************************************
			gStyle->SetOptFit(1111);
			TString veto1plane = "";
			TString veto1bar = "";
			TString veto2plane = "";
			TString veto2bar = "";
			TString veto3plane = "";
			TString veto3bar = "";
			TString veto4plane = "";
			TString veto4bar = "";
			TString veto5plane = "";
			TString veto5bar = "";
			TString veto6plane = "";
			TString veto6bar = "";
			TString antiveto1plane = ""; 
			TString antiveto1bar = "";
			TString antiveto2plane = "";
			TString antiveto2bar = "";
			TString antiveto3plane = "";
			TString antiveto3bar = "";
			TString allVetos = "";
			TString allAntivetos = "";
			TString vetoTDCslSt = "";
			TString vetoTDCsrSt = "";
			TCut vetoTDCsl = "";
			TCut vetoTDCsr = "";
			TCut vetoTDCs = "";
			TString antivetosTDCslSt = ""; 
			TString antivetosTDCsrSt = "";
			int maxbars = 0;
			int vetoplane = 0;
			int padBins = 0;
			double padMin = 0;
			double padMax = 0;

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
		//	int whichplane = 0;
//			int whichplane = 1;
//			int endplane = 5;
//			int whichbar=0;

			int whichplane = 1;
			int endplane = 3;
			int whichbar=12;
			TString titleTotalSpinUpx = "Total Target Spin Up vs. Omega";
			if (includeVetos) {titleTotalSpinUpx += " with vetos";}
			else {titleTotalSpinUpx += " without vetos";}
			titleTotalSpinUpx += " with goodTDC cuts";
			cout << "Drawing " << titleTotalSpinUpx << "..." << endl;
			TString plotTotalSpinUpx = "newHANDTotalSpinUpx";
			TH1F *newHANDTotalSpinUpx = new TH1F(plotTotalSpinUpx,titleTotalSpinUpx,nuBins,nuMin,nuMax);
			TString titleTotalSpinDownx = "Total Spin Down vs. Omega";
			if (includeVetos) {titleTotalSpinDownx += " with vetos";}
			else {titleTotalSpinDownx += " without vetos";}
			titleTotalSpinDownx += " with goodTDC cuts";
			cout << "Drawing " << titleTotalSpinDownx << "..." << endl;
			TString plotTotalSpinDownx = "newHANDTotalSpinDownx";
			TH1F *newHANDTotalSpinDownx = new TH1F(plotTotalSpinDownx,titleTotalSpinDownx,nuBins,nuMin,nuMax);

			for (int nplane=whichplane; nplane<endplane; nplane++)
			{
				if (nplane==0) maxbars=32;
//				if (nplane==1) maxbars=30;
//				if (nplane==2) maxbars=24;
				if (nplane==3) maxbars=22;
				if (nplane==4) maxbars=12;

				if (nplane==1) {maxbars=19;}
				if (nplane==2) {maxbars=15;}
//				if (nplane==1) {whichbar=12; maxbars=19;}
//				if (nplane==2) {whichbar=8; maxbars=15;}
				for (int thisbar=whichbar; thisbar<maxbars; thisbar++)
				{

					TString goodPlane = nplane;
					TString goodPMT = thisbar;
		//			hand_define_vetos(includeVetos, includeAntivetos, antivetosAsVetos, nplane, thisbar, veto1plane, veto2plane, veto3plane, veto4plane, veto5plane, veto6plane, veto1bar, veto2bar, veto3bar, veto4bar, veto5bar, veto6bar, antiveto1plane, antiveto2plane, antiveto3plane, antiveto1bar, antiveto2bar, antiveto3bar, allVetos, allAntivetos, vetoTDCslSt, vetoTDCsrSt, vetoTDCsl, vetoTDCsr, vetoTDCs, vetoTDCcutmin, vetoTDCcutmax, antivetosTDCslSt, antivetosTDCsrSt);
					hand_define_vetos(includeVetos, false, false, nplane, thisbar, veto1plane, veto2plane, veto3plane, veto4plane, veto5plane, veto6plane, veto1bar, veto2bar, veto3bar, veto4bar, veto5bar, veto6bar, antiveto1plane, antiveto2plane, antiveto3plane, antiveto1bar, antiveto2bar, antiveto3bar, allVetos, allAntivetos, vetoTDCslSt, vetoTDCsrSt, vetoTDCsl, vetoTDCsr, vetoTDCs, 745, 755, antivetosTDCslSt, antivetosTDCsrSt);
					
					TString goodBar = "nd.p";
					goodBar += nplane;
					goodBar += ".";
					goodBar += thisbar;
					goodBar += " ";
					cout << "Good Bar: " << goodBar << endl;

					TString canvasName = "handp";
					canvasName += nplane;
					canvasName += "b";
					canvasName += thisbar;
					TString canvasTitle = "HAND - Plane ";
					canvasTitle += nplane;
					canvasTitle += ", Bar ";
					canvasTitle += thisbar;
					TCanvas *handCanvas = new TCanvas(canvasName,canvasTitle,1400,730); //x,y
					handpad01 =  new TPad("handpad01","handpad01",0.0000,0.0000,0.1000,1.0000,0,0,0);
					handpad02 =  new TPad("handpad02","handpad02",0.1000,0.6666,0.5500,1.0000,0,0,0);
					handpad03 =  new TPad("handpad03","handpad03",0.5500,0.6666,1.0000,1.0000,0,0,0);
					handpad04 =  new TPad("handpad04","handpad04",0.1000,0.3333,0.5500,0.6666,0,0,0);
					handpad05 =  new TPad("handpad05","handpad05",0.5500,0.3333,1.0000,0.6666,0,0,0);
					handpad06 =  new TPad("handpad06","handpad06",0.1000,0.0000,0.5500,0.3333,0,0,0);
					handpad07 =  new TPad("handpad07","handpad07",0.5500,0.0000,1.0000,0.3333,0,0,0);
					handpad01->Draw(); handpad02->Draw(); handpad03->Draw(); handpad04->Draw(); handpad05->Draw();
					handpad06->Draw(); handpad07->Draw();

					// This section will run hand_draw.h which will draw the HAND in handpad01.
					handpad01->cd();
		//			hand_draw(HeRunNumber, endHeRunNumber, antivetosAsVetos, allVetos, goodBar, allAntivetos);
					hand_draw(HeRunNumber, endHeRunNumber, false, allVetos, goodBar, allAntivetos);
					handpad01->Update();

					handpad02->cd();
					TString titleHANDleft = "Left TDC for Plane #";
					titleHANDleft += nplane;
					titleHANDleft += ", PMT # ";
					titleHANDleft += thisbar;
					if (includeVetos) {titleHANDleft += " with vetos";}
					else {titleHANDleft += " without vetos";}
					cout << "Drawing " << titleHANDleft << "..." << endl;
					TString plotHANDleft = "HANDleft_p";
					plotHANDleft += nplane;
					plotHANDleft += "_b";
					plotHANDleft += thisbar;
					TString plotHANDleftcut = plotHANDleft;
					plotHANDleftcut += "_cut";
					TH1F *HANDleft = (TH1F*)fileHe.Get(plotHANDleft);
					HANDleft->SetMinimum(0);
					HANDleft->Draw();
		//			HANDleftcut->Scale(1/(HeChargeScale*Helivetime));
					TH1F *HANDleftcut = (TH1F*)fileHe.Get(plotHANDleftcut);
					HANDleftcut->SetMinimum(0);
					HANDleftcut->Draw("same");
					// ********************************************************************************
					// This section below gathers and prints some statistics on the plot
					double numHANDleftcutEvents = 0;
					for (int i=0; i<(HANDleft->GetSize()); i++){ numHANDleftcutEvents = numHANDleftcutEvents + HANDleftcut->GetBinContent(i);}
					TString HANDleftFactorsString = "Total Charge for Runs: ";
					HANDleftFactorsString += HeChargeScale;
					HANDleftFactorsString += " C";
					TString HANDleftFactorsString1 = "Total Livetime for Runs: ";
					HANDleftFactorsString1 += Helivetime;
					TString HANDleftFactorsString2 = "# of Cut (Purple) Events: ";
					HANDleftFactorsString2 += numHANDleftcutEvents;
					HANDleftFactors = new TPaveText(0.11,0.69,0.4,0.89,"NDC");
					TText *t1 = HANDleftFactors->AddText(HANDleftFactorsString);
					TText *t2 = HANDleftFactors->AddText(HANDleftFactorsString1);
					TText *t2 = HANDleftFactors->AddText(HANDleftFactorsString2);
					HANDleftFactors->Draw("same");
					// ********************************************************************************
					handpad02->Update();

					handpad03->cd();
					TString titleHANDright = "Right TDC for Plane #";
					titleHANDright += nplane;
					titleHANDright += ", PMT # ";
					titleHANDright += thisbar;
					if (includeVetos) {titleHANDright += " with vetos";}
					else {titleHANDright += " without vetos";}
					TString plotHANDright = "HANDright_p";
					plotHANDright += nplane;
					plotHANDright += "_b";
					plotHANDright += thisbar;
					TString plotHANDrightcut = plotHANDright;
					plotHANDrightcut += "_cut";
					cout << "Drawing " << titleHANDright << "..." << endl;
					TH1F *HANDright = (TH1F*)fileHe.Get(plotHANDright);
					HANDright->SetMinimum(0);
					TH1F *HANDrightcut = (TH1F*)fileHe.Get(plotHANDrightcut);
					HANDrightcut->SetMinimum(0);
		//			HANDright->Scale(1/(HeChargeScale*Helivetime));
					HANDright->Draw();
					HANDrightcut->SetFillColor(kViolet);
		//			HANDrightcut->Scale(1/(HeChargeScale*Helivetime));
					HANDrightcut->Draw("same");
					// ********************************************************************************
					// This section below gathers and prints some statistics on the plot
					double numHANDrightcutEvents = 0;
					for (int i=0; i<(HANDright->GetSize()); i++){ numHANDrightcutEvents = numHANDrightcutEvents + HANDrightcut->GetBinContent(i);}
					TString HANDrightFactorsString = "Total Charge for Runs: ";
					HANDrightFactorsString += HeChargeScale;
					HANDrightFactorsString += " C";
					TString HANDrightFactorsString1 = "Total Livetime for Runs: ";
					HANDrightFactorsString1 += Helivetime;
					TString HANDrightFactorsString2 = "# of Cut (Purple) Events: ";
					HANDrightFactorsString2 += numHANDrightcutEvents;
					HANDrightFactors = new TPaveText(0.11,0.69,0.4,0.89,"NDC");
					TText *t1 = HANDrightFactors->AddText(HANDrightFactorsString);
					TText *t2 = HANDrightFactors->AddText(HANDrightFactorsString1);
					TText *t2 = HANDrightFactors->AddText(HANDrightFactorsString2);
					HANDrightFactors->Draw("same");
					// ********************************************************************************
					handpad03->Update();

					handpad04->cd();
					cout << "Drawing Helicity Up vs. xBj..." << endl;
					TString titleSpinUpx = "Helicity Up vs. xBj for Plane #";
					titleSpinUpx += nplane;
					titleSpinUpx += ", PMT # ";
					titleSpinUpx += thisbar;
					if (includeVetos) {titleSpinUpx += " with vetos";}
					else {titleSpinUpx += " without vetos";}
					TString titleSpinUpxcut = titleSpinUpx;
					titleSpinUpxcut += " with goodTDC cuts";
					cout << "Drawing " << titleSpinUpx << "..." << endl;
					TString plotSpinUpx = "HANDSpinUpx_p";
					plotSpinUpx += nplane;
					plotSpinUpx += "_b";
					plotSpinUpx += thisbar;
					TH1F *HANDSpinUpx = (TH1F*)fileHe.Get(plotSpinUpx);
					HANDSpinUpx->SetMinimum(0);
					HANDSpinUpx->Draw();
					handpad04->Update();

					handpad05->cd();
					cout << "Drawing Helicity Down vs. xBj..." << endl;
					TString titleSpinDownx = "Helicity Down vs. xBj for Plane #";
					titleSpinDownx += nplane;
					titleSpinDownx += ", PMT # ";
					titleSpinDownx += thisbar;
					if (includeVetos) {titleSpinDownx += " with vetos";}
					else {titleSpinDownx += " without vetos";}
					TString titleSpinDownxcut = titleSpinDownx;
					titleSpinDownxcut += " with goodTDC cuts";
					cout << "Drawing " << titleSpinDownx << "..." << endl;
					TString plotSpinDownx = "HANDSpinDownx_p";
					plotSpinDownx += nplane;
					plotSpinDownx += "_b";
					plotSpinDownx += thisbar;
					TH1F *HANDSpinDownx = (TH1F*)fileHe.Get(plotSpinDownx);
					HANDSpinDownx->SetMinimum(0);
					HANDSpinDownx->Draw();
					handpad05->Update();

					handpad06->cd();
					cout << "Drawing Total Helicity Up vs. xBj..." << endl;
		//			TString titleTotalSpinUpx = "Total Spin Up vs. xBj";
		//			if (includeVetos) {titleTotalSpinUpx += " with vetos";}
		//			else {titleTotalSpinUpx += " without vetos";}
		//			titleTotalSpinUpx += " with goodTDC cuts";
		//			cout << "Drawing " << titleTotalSpinUpx << "..." << endl;
		//			TString plotTotalSpinUpx = "HANDTotalSpinUpx";
		//			TH1F *HANDTotalSpinUpx = new TH1F(plotTotalSpinUpx,titleTotalSpinUpx,nuBins,nuMin,nuMax);
					newHANDTotalSpinUpx->Add(HANDSpinUpx);
					newHANDTotalSpinUpx->SetMinimum(0);
					newHANDTotalSpinUpx->Draw();
					handpad06->Update();

					handpad07->cd();
					cout << "Drawing Total Helicity Down vs. xBj..." << endl;
		//			TString titleTotalSpinDownx = "Total Spin Down vs. xBj";
		//			if (includeVetos) {titleTotalSpinDownx += " with vetos";}
		//			else {titleTotalSpinDownx += " without vetos";}
		//			titleTotalSpinDownx += " with goodTDC cuts";
		//			cout << "Drawing " << titleTotalSpinDownx << "..." << endl;
		//			TString plotTotalSpinDownx = "HANDTotalSpinDownx";
		//			TH1F *HANDTotalSpinDownx = new TH1F(plotTotalSpinDownx,titleTotalSpinDownx,nuBins,nuMin,nuMax);
					newHANDTotalSpinDownx->Add(HANDSpinDownx);
					newHANDTotalSpinDownx->SetMinimum(0);
					newHANDTotalSpinDownx->Draw();
					handpad07->Update();




		//			if (includeAntivetos) {hand_draw_antivetos(antiveto1plane, antiveto1bar, antiveto2plane, antiveto2bar, antiveto3plane, antiveto3bar, HeRunNumber, endHeRunNumber, chainHe, TDCbins, TDCmin, TDCmax, cuts, goodTDCcut, vetoTDCs, imageAntivetosTitle, nplane, thisbar, includeVetos, includeAntivetos, antivetosAsVetos, veto1plane, veto1bar, veto2plane, veto2bar, veto3plane, veto3bar, veto4plane, veto4bar, veto5plane, veto5bar, veto6plane, veto6bar, allVetos, allAntivetos);}

		// *********************************************************************************************************
		// The section below will plot the bars used for vetos for the previous canvas. It will consist of two
		// canvases, one without the veto cuts made and one with to show the different.
		//			if (includeVetos) {hand_draw_vetos(veto1plane, veto2plane, veto3plane, veto4plane, veto5plane, veto6plane,veto1bar, veto2bar, veto3bar, veto4bar, veto5bar, veto6bar, imageVetosWithoutVetosTitle, imageVetosWithVetosTitle, HeRunNumber, endHeRunNumber, chainHe, nplane, thisbar, TDCbins, TDCmin, TDCmax, cuts, vetoTDCs, antivetosAsVetos, allVetos, allAntivetos);}

		//		if ((nplane==1) && (thisbar==15)) { nplane = 2; thisbar = 7;}
		//		if ((nplane==2) && (thisbar==12)) { nplane = 3; thisbar = 6;}
		//		if ((nplane==3) && (thisbar==11)) { nplane = 4; thisbar = 3;}
		//		if ((nplane==4) && (thisbar==7))  { nplane = 4; thisbar = 99;}


				}
			}

			TString canvasTotalSpinTest = "TotalSpinTest";
			TString canvasTitleTotalSpinTest = "HAND - Total Spin (Not Scaled)";
			TCanvas *totalSpinTestCanvas = new TCanvas(canvasTotalSpinTest,canvasTitleTotalSpinTest,1400,730); //x,y
			totalspintestpad01 =  new TPad("totalspintestpad01","totalspintestpad01",0.0000,0.5000,0.5000,1.0000,0,0,0);
			totalspintestpad02 =  new TPad("totalspintestpad02","totalspintestpad02",0.5000,0.5000,1.0000,1.0000,0,0,0);
			totalspintestpad03 =  new TPad("totalspintestpad03","totalspintestpad03",0.0000,0.0000,1.0000,0.5000,0,0,0);
			totalspintestpad01->Draw(); totalspintestpad02->Draw(); totalspintestpad03->Draw();

			totalspintestpad01->cd();
			newHANDTotalSpinUpx->SetTitle("Total Spin Up (Not Scaled)");
			newHANDTotalSpinUpx->Draw();
			totalspintestpad01->Update();

			totalspintestpad02->cd();
			newHANDTotalSpinDownx->SetTitle("Total Spin Down (Not Scaled)");
			newHANDTotalSpinDownx->Draw();
			totalspintestpad02->Update();

			totalspintestpad03->cd();
			TF1 *fitasymtest = new TF1("fitasymtest","[0]",nuMin,nuMax);
			HANDAsymTest = newHANDTotalSpinUpx->GetAsymmetry(newHANDTotalSpinDownx);
			TString AsymTestTitle = "Target Asymmerty with Neutron Cuts vs. xBj for runs ";
			AsymTestTitle += HeRunNumber;
			AsymTestTitle += "-";
			AsymTestTitle += endHeRunNumber;
			HANDAsymTest->SetTitle(AsymTestTitle);
			HANDAsymTest->Draw();
			fitasymtest->SetLineColor(kBlue);
			HANDAsymTest->Fit("fitasymtest","R");
			totalspintestpad03->Update();


			TString asymTitle = "Target Asymmetry for Runs ";
			asymTitle += HeRunNumber;
			asymTitle += "-";
			asymTitle += endHeRunNumber;
			TCanvas *asymCanvas = new TCanvas("asymCanvas",asymTitle,1400,730); //x,y
			asymCanvas->cd();
			asymCanvas->SetGrid();
			Double_t x[nuBins], y[nuBins], errorx[nuBins], errory[nuBins];
			double minError;
			double maxError;
			double posStuff;
			double negStuff;
			double UpEvents;
			double DownEvents;
			if ((targ == "v") || (targ == "l") || (targ == "t") || (targ == "c") || (targ == "h")) { check = true;}
	//		if (targ == "v") {asymOutFile << "Dataset:	Vertical 3He, Q2=" << kine << endl; cout << "Dataset:	Vertical 3He, Q2=" << kine << endl;}
	//		if (targ == "l") {asymOutFile << "Dataset:	Longitudinal 3He, Q2=" << kine << endl; cout << "Dataset:	Longitudinal 3He, Q2=" << kine << endl;}
	//		if (targ == "t") {asymOutFile << "Dataset:	Transverse 3He, Q2=" << kine << endl; cout << "Dataset:	Transverse 3He, Q2=" << kine << endl;}
	//		if (targ == "c") {asymOutFile << "Dataset:	Carbon, Q2=" << kine << endl; cout << "Dataset:	Carbon, Q2=" << kine << endl;}
	//		if (targ == "h") {asymOutFile << "Dataset:	Hydrogen, Q2=" << kine << endl; cout << "Dataset:	Hydrogen, Q2=" << kine << endl;}
	//		asymOutFile << "Runs:	" << HeRunNumber << "-" << endHeRunNumber << endl;
			cout << "Runs:	" << HeRunNumber << "-" << endHeRunNumber << endl;
	//		asymOutFile << "Omega	Asymmetry	Stat. Error	# HePos Events	HePos Charge	PosHe LT	# Neg Events	HeNeg Charge	NegHe LT" << endl;
			cout << "xBj	Asymmetry	Stat. Error	# HePos Events	HePos Charge	PosHe LT	# Neg Events	HeNeg Charge	NegHe LT" << endl;
			for (int i=0; i<nuBins; i++)
			{	
				UpEvents = newHANDTotalSpinUpx->GetBinContent(i);
				DownEvents = newHANDTotalSpinDownx->GetBinContent(i);
				x[i] = newHANDTotalSpinUpx->GetBinCenter(i);
				if (x[i] != (newHANDTotalSpinDownx->GetBinCenter(i))) { cout << endl << endl << "!!!!!!!!!!!!!!!!!!!!!!!!!! STOP! THERE'S A PROBLEM!!!!!!!!!!!!!!!!!!!!!!" << endl << endl << endl;}
				posStuff = UpEvents/(HeChargeScaleUp * HelivetimeUp + 1e-15);
				negStuff = DownEvents/(HeChargeScaleDown * HelivetimeDown + 1e-15);
				y[i] = ((posStuff - negStuff)/(posStuff + negStuff + 1e-15));
				errory[i] = 2*(DownEvents*sqrt(UpEvents) + UpEvents*sqrt(DownEvents))/((HeChargeScaleUp*HelivetimeUp)*(HeChargeScaleDown*HelivetimeDown)*pow((UpEvents/(HeChargeScaleUp*HelivetimeUp + 1e-25)) + (DownEvents/(HeChargeScaleDown*HelivetimeDown + 1e-25)),2) + 1e-15);
				if ((UpEvents == 0) || (DownEvents == 0)) { errory[i] = 1;}
				if ((UpEvents == 0) || (DownEvents == 0)) { y[i] = NULL;}
				if (i==0)
				{
					minError = y[i] - 2*errory[i];
					maxError = y[i] + 2*errory[i];
				}
				if ((y[i] - 2*errory[i]) < minError) { minError = y[i] - 2*errory[i];}
				if ((y[i] + 2*errory[i]) > maxError) { maxError = y[i] + 2*errory[i];}
				errorx[i] = ((nuMax - nuMin)/nuBins)/2;
	//			asymOutFile << x[i] << "	" << y[i] << "	" << errory[i] << "	" << UpEvents << "	" << HeChargeScaleUp << "	" << HelivetimeUp << "	" << DownEvents << "	" << HeChargeScaleDown << "	" << HelivetimeDown << endl;
				cout << x[i] << "	" << y[i] << "	" << errory[i] << "	" << UpEvents << "	" << HeChargeScaleUp << "	" << HelivetimeUp << "	" << DownEvents << "	" << HeChargeScaleDown << "	" << HelivetimeDown << endl;
				if ((i>3) && (i<9))
				{
					totesUpEvents = totesUpEvents + UpEvents;
					totesDownEvents = totesDownEvents + DownEvents;
				}
			}
			totesPosStuff = totesUpEvents/(HeChargeScaleUp * HelivetimeUp + 1e-15);
			totesNegStuff = totesDownEvents/(HeChargeScaleDown * HelivetimeDown + 1e-15);
			totesAsym = ((totesPosStuff - totesNegStuff)/(totesPosStuff + totesNegStuff + 1e-15));
			totesError = 2*(totesDownEvents*sqrt(totesUpEvents) + totesUpEvents*sqrt(totesDownEvents))/((HeChargeScaleUp*HelivetimeUp)*(HeChargeScaleDown*HelivetimeDown)*pow((totesUpEvents/(HeChargeScaleUp*HelivetimeUp + 1e-25)) + (totesDownEvents/(HeChargeScaleDown*HelivetimeDown + 1e-25)),2) + 1e-15);
			asymOutFile << k << "	" << totesAsym << "	" << totesError << "	" << totesUpEvents << "	" << HeChargeScaleUp << "	" << HelivetimeUp << "	" << totesDownEvents << "	" << HeChargeScaleDown << "	" << HelivetimeDown << endl;


			asymGraph = new TGraphErrors(nuBins, x, y, errorx, errory);
			asymGraph->SetMarkerStyle(21);
			asymGraph->SetMarkerColor(4);
			asymGraph->SetTitle(asymTitle);
			asymTestHist = new TH2F("asymTestHist",asymTitle,nuBins,nuMin,nuMax,100,minError,maxError);
			asymTestHist->SetStats(kFALSE);
			asymTestHist->Draw();
			cout << "Fit min = " << nuMin << "; Fit max = " << nuMax << endl;
			TF1 *fitAsymGraph = new TF1("fitAsymGraph", "[0]", nuMin, nuMax);
			asymGraph->Draw("P");
			fitAsymGraph->SetLineColor(kBlue);
			asymGraph->Fit("fitAsymGraph","R");
			asymCanvas->Update();
		/*
			TString TotalAsymOutTitle = outputPlotsHere;
			TotalAsymOutTitle += "target_asymmetry_good_for_Run_Num_";
			TotalAsymOutTitle += HeRunNumber;
			TotalAsymOutTitle += "-";
			TotalAsymOutTitle += endHeRunNumber;
			if (includeVetos) {TotalAsymOutTitle += "_with_vetos";}
			if (includeAntivetos) {TotalAsymOutTitle += "_with_antivetos";}
			if (antivetosAsVetos && includeAntivetos) {TotalAsymOutTitle += "_as_vetos";}
			TotalAsymOutTitle += ".png";
			asymCanvas->Print(TotalAsymOutTitle);
		*/


			TString canvasTotalSpin = "TotalSpin";
			TString canvasTitleTotalSpin = "HAND - Total Spin";
			TCanvas *totalSpinCanvas = new TCanvas(canvasTotalSpin,canvasTitleTotalSpin,1400,730); //x,y
			totalspinpad01 =  new TPad("totalspinpad01","totalspinpad01",0.0000,0.5000,0.5000,1.0000,0,0,0);
			totalspinpad02 =  new TPad("totalspinpad02","totalspinpad02",0.5000,0.5000,1.0000,1.0000,0,0,0);
			totalspinpad03 =  new TPad("totalspinpad03","totalspinpad03",0.0000,0.0000,1.0000,0.5000,0,0,0);
			totalspinpad01->Draw(); totalspinpad02->Draw(); totalspinpad03->Draw();

			totalspinpad01->cd();
			cout << "HeChargeScaleUp: " << HeChargeScaleUp << "   HelivetimeUp: " << HelivetimeUp << endl;
			newHANDTotalSpinUpx->Scale(1/(HeChargeScaleUp * HelivetimeUp + 1e-25));
			newHANDTotalSpinUpx->SetTitle("Total Spin Up (Scaled by Charge, LT)");
			newHANDTotalSpinUpx->Draw();
			// ********************************************************************************
			// This section below gathers and prints some statistics on the plot
			TString HANDUpFactorsString = "Total Positive Charge for Runs: ";
			HANDUpFactorsString += HeChargeScaleUp;
			HANDUpFactorsString += " C";
			TString HANDUpFactorsString1 = "Total Positive Livetime for Runs: ";
			HANDUpFactorsString1 += HelivetimeUp;
			HANDUpFactors = new TPaveText(0.11,0.69,0.4,0.89,"NDC");
			TText *t1 = HANDUpFactors->AddText(HANDUpFactorsString);
			TText *t2 = HANDUpFactors->AddText(HANDUpFactorsString1);
			HANDUpFactors->Draw("same");
			// ********************************************************************************
			totalspinpad01->Update();

			totalspinpad02->cd();
			cout << "HeChargeScaleDown: " << HeChargeScaleDown << "   HelivetimeDown: " << HelivetimeDown << endl;
			newHANDTotalSpinDownx->Scale(1/(HeChargeScaleDown * HelivetimeDown + 1e-25));
			newHANDTotalSpinDownx->SetTitle("Total Spin Down (Scaled by Charge, LT)");
			newHANDTotalSpinDownx->Draw();
			// ********************************************************************************
			// This section below gathers and prints some statistics on the plot
			TString HANDDownFactorsString = "Total Negative Charge for Runs: ";
			HANDDownFactorsString += HeChargeScaleDown;
			HANDDownFactorsString += " C";
			TString HANDDownFactorsString1 = "Total Negative Livetime for Runs: ";
			HANDDownFactorsString1 += HelivetimeDown;
			HANDDownFactors = new TPaveText(0.11,0.69,0.4,0.89,"NDC");
			TText *t1 = HANDDownFactors->AddText(HANDDownFactorsString);
			TText *t2 = HANDDownFactors->AddText(HANDDownFactorsString1);
			HANDDownFactors->Draw("same");
			// ********************************************************************************
			totalspinpad02->Update();

			totalspinpad03->cd();
			TF1 *fitasym = new TF1("fitasym","[0]",nuMin,nuMax);
			HANDAsym = newHANDTotalSpinUpx->GetAsymmetry(newHANDTotalSpinDownx);
			TString AsymTitle = "Target Asymmerty with Neutron Cuts vs. xBj for runs ";
			AsymTitle += HeRunNumber;
			AsymTitle += "-";
			AsymTitle += endHeRunNumber;
			HANDAsym->SetTitle(AsymTitle);
			HANDAsym->Draw();
			fitasym->SetLineColor(kBlue);
			HANDAsym->Fit("fitasym","R");
			totalspinpad03->Update();
		/*
			TString TotalSpinOutTitle = outputPlotsHere;
			TotalSpinOutTitle += "target_asymmetry_for_Run_Num_";
			TotalSpinOutTitle += HeRunNumber;
			TotalSpinOutTitle += "-";
			TotalSpinOutTitle += endHeRunNumber;
			if (includeVetos) {TotalSpinOutTitle += "_with_vetos";}
			TotalSpinOutTitle += ".png";
			totalSpinCanvas->Print(TotalSpinOutTitle);
		*/
		}
	}
	asymOutFile.close();

	TString exitst;
	cout << "Are you ready to finish?" << endl;
	cin >> exitst;

	cout << "All done!" << endl;

}







































