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

void add_hand_targ_asymmetry_vs_nu_with_tof_analysis_just_tof_spectra(){

	TString targ;
	TString kine;
	TString veto;
	bool check = false;

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
//		if (targ == "v") {HeRunNumber = 20596; endHeRunNumber = 20789;}
		if (targ == "v") {HeRunNumber = 20596; endHeRunNumber = 20760;}
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
		if (targ == "v") {HeRunNumber = 20890; endHeRunNumber = 21005;}
		double nuMax = 0.125;
		double nuMin = 0.425;
	}
	if (kine == "0.1")
	{
		if (targ == "v") {HeRunNumber = 20487; endHeRunNumber = 20538;}
//		if (targ == "v") {HeRunNumber = 20487; endHeRunNumber = 20532;}
//		if (targ == "v") {HeRunNumber = 20487; endHeRunNumber = 20511;}
//		if (targ == "v") {HeRunNumber = 20533; endHeRunNumber = 20538;}
		double nuMin = 0;
		double nuMax = 0.13;
	}
	
	TString outputPlotsHere = "/home/ellie/physics/e05-102/images/plots_for_hand/hand_beam_asymmetry_vs_nu/";

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
	outFileName = filenameHe;
	filenameHe += ".root";

	TString asymOutFileName = outFileName;
	asymOutFileName += "_ssa_target_asymmetry_runs_";
	asymOutFileName += HeRunNumber;
	asymOutFileName += "-";
	asymOutFileName += endHeRunNumber;
	asymOutFileName += ".txt";
	ofstream asymOutFile;
	asymOutFile.open(asymOutFileName);

	ifstream ifileHe(filenameHe);
	if (ifileHe)
	{
		cout << "Adding file to chainHe: " << filenameHe << endl;
		chainHe->Add(filenameHe);
	}
	else
	{
		cout << "File " << filenameHe << " does not exist. Exiting..." << endl;
		return 0;
//		If this loop is causing you problems, read the IMPORTANT note above
	}

	TFile fileHe(filenameHe);

	gStyle->SetPalette(1);

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


// The section below will plot the ToF spectra
// **********************************************************************************************
	int tofBins = 100;
	int tofMin = 0;
	int tofMax = 1600;

	hand_basic_cuts(HeRunNumber, endHeRunNumber, drawCuts, kine, filenameHe, targ);

	TString ToFOCanvasName = "tofOcanvas";
	TString ToFOCanvasTitle = "Time of Flight[0]";
	TCanvas *handCanvas = new TCanvas(ToFOCanvasName,ToFOCanvasTitle,1400,770); //x,y
	tofOpad01 =  new TPad("tofOpad01","tofOpad01",0.0000,0.0000,0.3333,1.0000,0,0,0);
	tofOpad02 =  new TPad("tofOpad02","tofOpad02",0.3333,0.0000,0.6666,1.0000,0,0,0);
	tofOpad03 =  new TPad("tofOpad03","tofOpad03",0.6666,0.0000,1.0000,1.0000,0,0,0);
	tofOpad01->Draw(); tofOpad02->Draw(); tofOpad03->Draw();

	tofOpad01->cd();
	TString titleToFO = "ToF[0] with basic cuts for Runs ";
	titleToFO += HeRunNumber;
	titleToFO += "-";
	titleToFO += endHeRunNumber;
	cout << titleToFO << "..." << endl;
	cout << "Drawing " << titleToFO << "..." << endl;
	TString plotToFO = "HANDToFO";
//	TH1F *HANDToFO = new TH1F(plotToFO,titleToFO,tofBins,tofMin,tofMax);
//	TString HANDToFOString = "NA.n.tof[0]";
//	HANDToFOString += ">>";
//	HANDToFOString += plotToFO;
//	chainHe->Draw(HANDToFOString, cuts,"");
	TH1F *HANDToFO = (TH1F*)fileHe.Get(plotToFO);
	HANDToFO->SetTitle(titleToFO);
//	HANDToFO->Scale(1/HeChargeScale*Helivetime+1e-15);
//	HANDToFO->SetMinimum(115000);
//	HANDToFO->Write();
	HANDToFO->Draw();
	tofOpad01->Update();

	tofOpad02->cd();
	TString titleToFOUp = "ToF[0] with basic cuts and spin Up";
	cout << titleToFOUp << "..." << endl;
	cout << "Drawing " << titleToFOUp << "..." << endl;
	TString plotToFOUp = "HANDToFOUp";
//	TH1F *HANDToFOUp = new TH1F(plotToFOUp,titleToFOUp,tofBins,tofMin,tofMax);
//	TString HANDToFOUpString = "NA.n.tof[0]";
//	HANDToFOUpString += ">>";
//	HANDToFOUpString += plotToFOUp;
//	chainHe->Draw(HANDToFOUpString, cuts && "he3R.Spin==1 && he3R.IsSpinValid==1","");
	TH1F *HANDToFOUp = (TH1F*)fileHe.Get(plotToFOUp);
//	HANDToFOUp->Scale(1/HeChargeScaleUp*HelivetimeUp+1e-15);
//	HANDToFOUp->SetMinimum(115000);
//	HANDToFOUp->Write();
	HANDToFOUp->Draw();
	tofOpad02->Update();

	tofOpad03->cd();
	TString titleToFODown = "ToF[0] with basic cuts and spin Down";
	cout << titleToFODown << "..." << endl;
	cout << "Drawing " << titleToFODown << "..." << endl;
	TString plotToFODown = "HANDToFODown";
//	TH1F *HANDToFODown = new TH1F(plotToFODown,titleToFODown,tofBins,tofMin,tofMax);
//	TString HANDToFODownString = "NA.n.tof[0]";
//	HANDToFODownString += ">>";
//	HANDToFODownString += plotToFODown;
//	chainHe->Draw(HANDToFODownString, cuts && "he3R.Spin==-1 && he3R.IsSpinValid==1","");
	TH1F *HANDToFODown = (TH1F*)fileHe.Get(plotToFODown);
//	HANDToFODown->Scale(1/HeChargeScaleDown*HelivetimeDown+1e-15);
//	HANDToFODown->SetMinimum(115000);
//	HANDToFODown->Write();
	HANDToFODown->Draw();
	tofOpad03->Update();
/*
	TString ToFlCanvasName = "toflcanvas";
	TString ToFlCanvasTitle = "Time of Flight[1]";
	TCanvas *handCanvas = new TCanvas(ToFlCanvasName,ToFlCanvasTitle,1400,770); //x,y
	toflpad01 =  new TPad("toflpad01","toflpad01",0.0000,0.0000,0.3333,1.0000,0,0,0);
	toflpad02 =  new TPad("toflpad02","toflpad02",0.3333,0.0000,0.6666,1.0000,0,0,0);
	toflpad03 =  new TPad("toflpad03","toflpad03",0.6666,0.0000,1.0000,1.0000,0,0,0);
	toflpad01->Draw(); toflpad02->Draw(); toflpad03->Draw();

	toflpad01->cd();
	TString titleToFl = "ToF[1] with basic cuts";
	cout << titleToFl << "..." << endl;
	cout << "Drawing " << titleToFl << "..." << endl;
	TString plotToFl = "HANDToFl";
//	TH1F *HANDToFl = new TH1F(plotToFl,titleToFl,tofBins,tofMin,tofMax);
//	TString HANDToFlString = "NA.n.tof[1]";
//	HANDToFlString += ">>";
//	HANDToFlString += plotToFl;
//	chainHe->Draw(HANDToFlString, cuts,"");
	TH1F *HANDToFl = (TH1F*)fileHe.Get(plotToFl);
//	HANDToFl->Scale(1/HeChargeScale*Helivetime+1e-15);
	HANDToFl->SetMinimum(75000);
//	HANDToFl->Write();
	HANDToFl->Draw();
	toflpad01->Update();

	toflpad02->cd();
	TString titleToFlUp = "ToF[1] with basic cuts and spin Up";
	cout << titleToFlUp << "..." << endl;
	cout << "Drawing " << titleToFlUp << "..." << endl;
	TString plotToFlUp = "HANDToFlUp";
//	TH1F *HANDToFlUp = new TH1F(plotToFlUp,titleToFlUp,tofBins,tofMin,tofMax);
//	TString HANDToFlUpString = "NA.n.tof[1]";
//	HANDToFlUpString += ">>";
//	HANDToFlUpString += plotToFlUp;
//	chainHe->Draw(HANDToFlUpString, cuts && "he3R.Spin==1 && he3R.IsSpinValid==1","");
	TH1F *HANDToFlUp = (TH1F*)fileHe.Get(plotToFlUp);
//	HANDToFlUp->Scale(1/HeChargeScaleUp*HelivetimeUp+1e-15);
	HANDToFlUp->SetMinimum(75000);
//	HANDToFlUp->Write();
	HANDToFlUp->Draw();
	toflpad02->Update();

	toflpad03->cd();
	TString titleToFlDown = "ToF[1] with basic cuts and spin Down";
	cout << titleToFlDown << "..." << endl;
	cout << "Drawing " << titleToFlDown << "..." << endl;
	TString plotToFlDown = "HANDToFlDown";
//	TH1F *HANDToFlDown = new TH1F(plotToFlDown,titleToFlDown,tofBins,tofMin,tofMax);
//	TString HANDToFlDownString = "NA.n.tof[1]";
//	HANDToFlDownString += ">>";
//	HANDToFlDownString += plotToFlDown;
//	chainHe->Draw(HANDToFlDownString, cuts && "he3R.Spin==-1 && he3R.IsSpinValid==1","");
	TH1F *HANDToFlDown = (TH1F*)fileHe.Get(plotToFlDown);
//	HANDToFlDown->Scale(1/HeChargeScaleDown*HelivetimeDown+1e-15);
	HANDToFlDown->SetMinimum(75000);
//	HANDToFlDown->Write();
	HANDToFlDown->Draw();
	toflpad03->Update();







// The section below plots the HAND data
// **********************************************************************************************
//	int whichplane = 0;
//	int whichplane = 1;
//	int endplane = 5;
//	int whichbar=0;

	int whichplane = 1;
	int endplane = 3;
	int whichbar=10;
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

	TString titleTotalToF = "Total ToF";
	if (includeVetos) {titleTotalToF += " with vetos";}
	else {titleTotalToF += " without vetos";}
	titleTotalToF += " with goodTDC cuts";
	cout << "Drawing " << titleTotalToF << "..." << endl;
	TString plotTotalToF = "newHANDTotalToF";
	TH1F *newHANDTotalToF = new TH1F(plotTotalToF,titleTotalToF,tofBins,tofMin,tofMax);
	TString titleTotalToFUp = "Total Target Spin Up ToF";
	if (includeVetos) {titleTotalToFUp += " with vetos";}
	else {titleTotalToFUp += " without vetos";}
	titleTotalToFUp += " with goodTDC cuts";
	cout << "Drawing " << titleTotalToFUp << "..." << endl;
	TString plotTotalToFUp = "newHANDTotalToFUp";
	TH1F *newHANDTotalToFUp = new TH1F(plotTotalToFUp,titleTotalToFUp,tofBins,tofMin,tofMax);
	TString titleTotalToFDown = "Total Spin Down ToF";
	if (includeVetos) {titleTotalToFDown += " with vetos";}
	else {titleTotalToFDown += " without vetos";}
	titleTotalToFDown += " with goodTDC cuts";
	cout << "Drawing " << titleTotalToFDown << "..." << endl;
	TString plotTotalToFDown = "newHANDTotalToFDown";
	TH1F *newHANDTotalToFDown = new TH1F(plotTotalToFDown,titleTotalToFDown,tofBins,tofMin,tofMax);


	for (int nplane=whichplane; nplane<endplane; nplane++)
	{
//		if (nplane==0) maxbars=32;
//		if (nplane==1) maxbars=30;
//		if (nplane==2) maxbars=24;
//		if (nplane==3) maxbars=20;
//		if (nplane==4) maxbars=12;

		if (nplane==1) maxbars=20;
		if (nplane==2) {whichbar=8; maxbars=16;}
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
			handpad02 =  new TPad("handpad02","handpad02",0.1000,0.7500,0.4375,1.0000,0,0,0);
			handpad03 =  new TPad("handpad03","handpad03",0.4375,0.7500,0.7750,1.0000,0,0,0);
			handpad04 =  new TPad("handpad04","handpad04",0.1000,0.5000,0.3250,0.7500,0,0,0);
			handpad05 =  new TPad("handpad05","handpad05",0.3250,0.5000,0.5500,0.7500,0,0,0);
			handpad06 =  new TPad("handpad06","handpad06",0.5500,0.5000,0.7750,0.7500,0,0,0);
			handpad07 =  new TPad("handpad07","handpad07",0.1000,0.2500,0.3250,0.5000,0,0,0);
			handpad09 =  new TPad("handpad09","handpad09",0.3250,0.2500,0.5500,0.5000,0,0,0);
			handpad11 =  new TPad("handpad11","handpad11",0.5500,0.2500,0.7750,0.5000,0,0,0);
			handpad08 =  new TPad("handpad08","handpad08",0.1000,0.0000,0.3250,0.2500,0,0,0);
			handpad10 =  new TPad("handpad10","handpad10",0.3250,0.0000,0.5500,0.2500,0,0,0);
			handpad12 =  new TPad("handpad12","handpad12",0.5500,0.0000,0.7750,0.2500,0,0,0);
			handpad13 =  new TPad("handpad13","handpad13",0.7750,0.7500,1.0000,1.0000,0,0,0);
			handpad14 =  new TPad("handpad14","handpad14",0.7750,0.5000,1.0000,0.7500,0,0,0);
			handpad15 =  new TPad("handpad15","handpad15",0.7750,0.2500,1.0000,0.5000,0,0,0);
			handpad16 =  new TPad("handpad16","handpad16",0.7750,0.0000,1.0000,0.2500,0,0,0);
			handpad01->Draw(); handpad02->Draw(); handpad03->Draw(); handpad04->Draw(); handpad05->Draw();
			handpad06->Draw(); handpad07->Draw(); handpad08->Draw(); handpad09->Draw(); handpad10->Draw();
			handpad11->Draw(); handpad12->Draw(); handpad13->Draw(); handpad14->Draw(); handpad15->Draw(); 
			handpad16->Draw();
 
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
			TString plotHANDleft = "HANDleft_p";
			plotHANDleft += nplane;
			plotHANDleft += "_b";
			plotHANDleft += thisbar;
			TString plotHANDleftcut = plotHANDleft;
			plotHANDleftcut += "_cut";
			cout << "Drawing " << titleHANDleft << "..." << endl;
			TH1F *HANDleft = (TH1F*)fileHe.Get(plotHANDleft);
			HANDleft->SetMinimum(0);
			TH1F *HANDleftcut = (TH1F*)fileHe.Get(plotHANDleftcut);
			HANDleftcut->SetMinimum(0);
//			HANDleft->Scale(1/(HeChargeScale*Helivetime));
			HANDleft->Draw();
			HANDleftcut->SetFillColor(kViolet);
//			HANDleftcut->Scale(1/(HeChargeScale*Helivetime));
			HANDleftcut->Draw("same");
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
			handpad03->Update();

			handpad04->cd();
			cout << "Drawing Theta..." << endl;
			TString titleThetaCut = "Theta for plane ";
			titleThetaCut += nplane;
			titleThetaCut += ", bar ";
			titleThetaCut += thisbar;
			TString plotThetaCut = "th_p";
			plotThetaCut += nplane;
			plotThetaCut += "_b";
			plotThetaCut += thisbar;
			TH1F *HeThetaCut = (TH1F*)fileHe.Get(plotThetaCut);
			HeThetaCut->Draw();
			handpad04->Update();

			handpad05->cd();
			TString titleThetaPhiCut = "Theta & Phi for Plane ";
			titleThetaPhiCut += nplane;
			titleThetaPhiCut += ", Bar ";
			titleThetaPhiCut += thisbar;
			cout << "Drawing " << titleThetaPhiCut << "..." << endl;
			TString plotThetaPhiCut = "thph_p";
			plotThetaPhiCut += nplane;
			plotThetaPhiCut += "_b";
			plotThetaPhiCut += thisbar;
			TH2F *HeThetaPhiCut = (TH2F*)fileHe.Get(plotThetaPhiCut);
			HeThetaPhiCut->Draw("COLZ");
			handpad05->Update();

			handpad06->cd();
			TString titlePhiCut = "Phi for plane ";
			titlePhiCut += nplane;
			titlePhiCut += ", bar ";
			titlePhiCut += thisbar;
			cout << "Drawing " << titlePhiCut << "..." << endl;
			TString plotPhiCut = "ph_p";
			plotPhiCut += nplane;
			plotPhiCut += "_b";
			plotPhiCut += thisbar;
			TH1F *HePhiCut = (TH1F*)fileHe.Get(plotPhiCut);
			HePhiCut->Draw();
			handpad06->Update();

			handpad07->cd();
			TString titleToF = "ToF with basic cuts";
			cout << titleToF << "..." << endl;
			cout << "Drawing " << titleToF << "..." << endl;
			TString plotToF = "HANDToF_p";
			plotToF += nplane;
			plotToF += "_b";
			plotToF += thisbar;
			TH1F *HANDToF = (TH1F*)fileHe.Get(plotToF);
//			HANDToF->Scale(1/HeChargeScale*Helivetime+1e-15);
//			HANDToF->SetMinimum(115000);
			HANDToF->Draw();
			handpad07->Update();

			handpad08->cd();
			cout << "Drawing ToF..." << endl;
			newHANDTotalToF->Add(HANDToF);
			newHANDTotalToF->SetMinimum(0);
			newHANDTotalToF->Draw();
			handpad08->Update();

			handpad09->cd();
			TString titleToFUp = "ToF with basic cuts and spin Up";
			cout << titleToFUp << "..." << endl;
			cout << "Drawing " << titleToFUp << "..." << endl;
			TString plotToFUp = "HANDToFUp_p";
			plotToFUp += nplane;
			plotToFUp += "_b";
			plotToFUp += thisbar;
			TH1F *HANDToFUp = (TH1F*)fileHe.Get(plotToFUp);
//			HANDToFUp->Scale(1/HeChargeScaleUp*HelivetimeUp+1e-15);
//			HANDToFUp->SetMinimum(115000);
			HANDToFUp->Draw();
			handpad09->Update();

			handpad10->cd();
			cout << "Drawing ToFUp..." << endl;
			newHANDTotalToFUp->Add(HANDToFUp);
			newHANDTotalToFUp->SetMinimum(0);
			newHANDTotalToFUp->Draw();
			handpad10->Update();

			handpad11->cd();
			TString titleToFDown = "ToF with basic cuts and spin Down";
			cout << titleToFDown << "..." << endl;
			cout << "Drawing " << titleToFDown << "..." << endl;
			TString plotToFDown = "HANDToFDown_p";
			plotToFDown += nplane;
			plotToFDown += "_b";
			plotToFDown += thisbar;
			TH1F *HANDToFDown = (TH1F*)fileHe.Get(plotToFDown);
//			HANDToFDown->Scale(1/HeChargeScaleDown*HelivetimeDown+1e-15);
//			HANDToFDown->SetMinimum(115000);
			HANDToFDown->Draw();
			handpad11->Update();

			handpad12->cd();
			cout << "Drawing ToFDown..." << endl;
			newHANDTotalToFDown->Add(HANDToFDown);
			newHANDTotalToFDown->SetMinimum(0);
			newHANDTotalToFDown->Draw();
			handpad12->Update();

			handpad13->cd();
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
			handpad13->Update();

			handpad14->cd();
			cout << "Drawing Total Helicity Up vs. xBj..." << endl;
			newHANDTotalSpinUpx->Add(HANDSpinUpx);
			newHANDTotalSpinUpx->SetMinimum(0);
			newHANDTotalSpinUpx->Draw();
			handpad14->Update();

			handpad15->cd();
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
			handpad15->Update();

			handpad16->cd();
			cout << "Drawing Total Helicity Down vs. xBj..." << endl;
			newHANDTotalSpinDownx->Add(HANDSpinDownx);
			newHANDTotalSpinDownx->SetMinimum(0);
			newHANDTotalSpinDownx->Draw();
			handpad16->Update();





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
	if (targ == "v") {asymOutFile << "Dataset:	Vertical 3He, Q2=" << kine << endl; cout << "Dataset:	Vertical 3He, Q2=" << kine << endl;}
	if (targ == "l") {asymOutFile << "Dataset:	Longitudinal 3He, Q2=" << kine << endl; cout << "Dataset:	Longitudinal 3He, Q2=" << kine << endl;}
	if (targ == "t") {asymOutFile << "Dataset:	Transverse 3He, Q2=" << kine << endl; cout << "Dataset:	Transverse 3He, Q2=" << kine << endl;}
	if (targ == "c") {asymOutFile << "Dataset:	Carbon, Q2=" << kine << endl; cout << "Dataset:	Carbon, Q2=" << kine << endl;}
	if (targ == "h") {asymOutFile << "Dataset:	Hydrogen, Q2=" << kine << endl; cout << "Dataset:	Hydrogen, Q2=" << kine << endl;}
	asymOutFile << "Runs:	" << HeRunNumber << "-" << endHeRunNumber << endl;
	cout << "Runs:	" << HeRunNumber << "-" << endHeRunNumber << endl;
	asymOutFile << "Omega	Asymmetry	Stat. Error	# HePos Events	HePos Charge	PosHe LT	# Neg Events	HeNeg Charge	NegHe LT" << endl;
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
		asymOutFile << x[i] << "	" << y[i] << "	" << errory[i] << "	" << UpEvents << "	" << HeChargeScaleUp << "	" << HelivetimeUp << "	" << DownEvents << "	" << HeChargeScaleDown << "	" << HelivetimeDown << endl;
		cout << x[i] << "	" << y[i] << "	" << errory[i] << "	" << UpEvents << "	" << HeChargeScaleUp << "	" << HelivetimeUp << "	" << DownEvents << "	" << HeChargeScaleDown << "	" << HelivetimeDown << endl;
	}
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

//	TString TotalAsymOutTitle = outputPlotsHere;
//	TotalAsymOutTitle += "target_asymmetry_good_for_Run_Num_";
//	TotalAsymOutTitle += HeRunNumber;
//	TotalAsymOutTitle += "-";
//	TotalAsymOutTitle += endHeRunNumber;
//	if (includeVetos) {TotalAsymOutTitle += "_with_vetos";}
//	if (includeAntivetos) {TotalAsymOutTitle += "_with_antivetos";}
//	if (antivetosAsVetos && includeAntivetos) {TotalAsymOutTitle += "_as_vetos";}
//	TotalAsymOutTitle += ".png";
//	asymCanvas->Print(TotalAsymOutTitle);



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

//	TString TotalSpinOutTitle = outputPlotsHere;
//	TotalSpinOutTitle += "target_asymmetry_for_Run_Num_";
//	TotalSpinOutTitle += HeRunNumber;
//	TotalSpinOutTitle += "-";
//	TotalSpinOutTitle += endHeRunNumber;
//	if (includeVetos) {TotalSpinOutTitle += "_with_vetos";}
//	TotalSpinOutTitle += ".png";
//	totalSpinCanvas->Print(TotalSpinOutTitle);

*/
	asymOutFile.close();

	TString exitst;
	cout << "Are you ready to finish?" << endl;
	cin >> exitst;

	cout << "All done!" << endl;

}







































