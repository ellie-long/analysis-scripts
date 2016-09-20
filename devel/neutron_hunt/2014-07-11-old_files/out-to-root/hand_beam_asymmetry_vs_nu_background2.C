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

// Search for HAND to get to the PMT definitions

void hand_beam_asymmetry_vs_nu_background2(){

	bool includeVetos;
// 	If includeVetos = false, then only good bars will be displayed. If 
//	includeVetos = true, then veto bars will be shown along with the good bars.
	includeVetos = true;
//	includeVetos = false;

	bool includeAntivetos;
// 	If includeAntivetos = false, then only good bars will be displayed. If 
//	includeAntivetos = true, then antiveto bars will be shown along with the good bars.
//	includeAntivetos = true;
	includeAntivetos = false;

	bool antivetosAsVetos;
//	If antivetosAsVetos = false, then the antivetos will not be included in the veto cut
//	If antivetosAsVetos = true, then the antivetos will be included in the veto cut
//	Discusses elsewhere, antivetos are the bars immediately following a goodBar
	antivetosAsVetos = false;
//	antivetosAsVetos = true;

//	bool drawCuts = true;
	bool drawCuts = false;

// 	The SinglePlane and SingleBar booleans skip the loop that goes over
// 	ever bar into just a single plane and/or a single bar.
	bool SinglePlane;
	bool SingleBar;
	int singleplane;
	int singlebar;
//	SinglePlane = true;
	SinglePlane = false;
	singleplane = 2;
//	SingleBar = true;
	SingleBar = false;
	singlebar = 10;
/*
	int HeRunNumber = 22441;
	int endHeRunNumber = 22441;
	TString Q2 = "1.0";
	double q2min = 0.75;
	double q2max = 1.2;
	double numin = 0.3;
	double numax = 0.7;
	int Positionbins = 30;
	double Positionmin = -30;
	double Positionmax = 30;
	int TDCbins = 100;
	double TDCmin = 700;
	double TDCmax = 800;
	int ADCbins = 700;
	double ADCmin = -100;
	double ADCmax = 11100;
	double goodTDCleftcutmin = 752;
	double goodTDCleftcutmax = 775;
	double goodTDCrightcutmin = 752;
	double goodTDCrightcutmax = 775;
	double vetoTDCcutmin = 750;
	double vetoTDCcutmax = 785;
*/
/*
// ********* Vertical, Q2=1.0 *******************
	int HeRunNumber = 20596;
	int endHeRunNumber = 20683;
	TString Q2 = "1.0";
	double q2min = 0.75;
	double q2max = 1.2;
	double numin = 0.3;
	double numax = 0.7;
	int Positionbins = 30;
	double Positionmin = -30;
	double Positionmax = 30;
	int TDCbins = 200;
	double TDCmin = 1300;
	double TDCmax = 1700;
	int ADCbins = 700;
	double ADCmin = -100;
	double ADCmax = 11100;
	double goodTDCleftcutmin = 1385;
	double goodTDCleftcutmax = 1415;
	double goodTDCrightcutmin = 1385;
	double goodTDCrightcutmax = 1415;
	double vetoTDCcutmin = 1385;
	double vetoTDCcutmax = 1415;
*/
/*
// ********* Vertical, Q2=0.5 *******************
	int HeRunNumber = 20890;
	int endHeRunNumber = 20890;
	TString Q2 = "0.5";
	double q2min = 0.3;
	double q2max = 0.6;
	double numin = 0.1;
	double numax = 0.35;
	int Positionbins = 30;
	double Positionmin = -30;
	double Positionmax = 30;
	int TDCbins = 75;
	double TDCmin = 1300;
	double TDCmax = 1500;
	int ADCbins = 700;
	double ADCmin = -100;
	double ADCmax = 11100;
	double goodTDCleftcutmin = 1385;
	double goodTDCleftcutmax = 1415;
	double goodTDCrightcutmin = 1385;
	double goodTDCrightcutmax = 1415;
	double vetoTDCcutmin = 1385;
	double vetoTDCcutmax = 1415;
*/

/*
// ********* Vertical, Q2=0.42 *******************
	int HeRunNumber = 21383;
	int endHeRunNumber = 21387;
	TString Q2 = "0.42";
	double q2min = 0.33;
	double q2max = 0.51;
	double numin = 0.17;
	double numax = 0.3;
	int Positionbins = 30;
	double Positionmin = -30;
	double Positionmax = 30;
	int TDCbins = 50;
	double TDCmin = 700;
	double TDCmax = 800;
	int ADCbins = 700;
	double ADCmin = -100;
	double ADCmax = 11100;
	double goodTDCleftcutmin = 730;
	double goodTDCleftcutmax = 770;
	double goodTDCrightcutmin = 740;
	double goodTDCrightcutmax = 780;
	double vetoTDCcutmin = 730;
	double vetoTDCcutmax = 770;
*/
/*
	int HeRunNumber = 21714;
	int endHeRunNumber = 22248;
	TString Q2 = "0.52";
	double q2min = 0.33;
	double q2max = 0.62;
	double numin = 0.17;
	double numax = 0.35;
	int Positionbins = 30;
	double Positionmin = -30;
	double Positionmax = 30;
	int TDCbins = 50;
	double TDCmin = 700;
	double TDCmax = 800;
	int ADCbins = 700;
	double ADCmin = -100;
	double ADCmax = 11100;
	double goodTDCleftcutmin = 730;
	double goodTDCleftcutmax = 770;
	double goodTDCrightcutmin = 740;
	double goodTDCrightcutmax = 780;
	double vetoTDCcutmin = 730;
	double vetoTDCcutmax = 770;
*/

// ********* Transverse, Q2=1.0 *******************
	int HeRunNumber = 22450;
//	int endHeRunNumber = 22450;
	int endHeRunNumber = 22489;
	TString Q2 = "1.0";
	double q2min = 0.75;
	double q2max = 1.2;
	double numin = 0.3;
	double numax = 0.7;
	int Positionbins = 30;
	double Positionmin = -30;
	double Positionmax = 30;
	int TDCbins = 100;
	double TDCmin = 650;
	double TDCmax = 850;

	int TDCbins = 300;
	double TDCmin = 0;
	double TDCmax = 1600;

/*
	int ADCbins = 700;
	double ADCmin = -100;
	double ADCmax = 11100;
*/
/*
	double goodTDCleftcutmin = 745;
	double goodTDCleftcutmax = 775;
	double goodTDCrightcutmin = 750;
	double goodTDCrightcutmax = 780;
*/
	double goodTDCleftcutmin = 645;
	double goodTDCleftcutmax = 880;
	double goodTDCrightcutmin = 645;
	double goodTDCrightcutmax = 880;

/*	double goodTDCleftcutmin = 1;
	double goodTDCleftcutmax = 1600;
	double goodTDCrightcutmin = 1;
	double goodTDCrightcutmax = 1600;
*/


	double vetoTDCcutmin = 745;
	double vetoTDCcutmax = 780;



//	const int nuBins = 50;
	const int nuBins = 10;
	double nuMin = 0.35;
	double nuMax = 0.65;

	double xmin = 0.6;
	double xmax = 3.0;

	int bins = 50;

	TString outputPlotsHere = "/home/ellie/physics/e05-102/images/plots_for_hand/hand_beam_asymmetry_vs_nu_background/";

	TString asymOutFileName = outputPlotsHere;
	asymOutFileName += "target_asymmetry_for_runs_";
	asymOutFileName += HeRunNumber;
	asymOutFileName += "-";
	asymOutFileName += endHeRunNumber;
	if (includeVetos) asymOutFileName += "-with-vetos";
	asymOutFileName += ".txt";
	ofstream asymOutFile;
	asymOutFile.open(asymOutFileName);

	// Although declared here, the goodTDCcut is actually made down below where  it can be included
	// in the loop so that it is easy to have it change for each good bar when done one at a time.
	// However, the left and right min and max TDC values are defined here
	TCut goodTDCcut = "";

	TChain* chainHe = new TChain("T");
	TString filenameHe;

	for (int thisHeRunNumber=HeRunNumber; thisHeRunNumber<(endHeRunNumber+1); thisHeRunNumber++)
	{
		// Skipping Vertical Non-Production Runs
		if(thisHeRunNumber==20591){thisHeRunNumber=20596;}
		if(thisHeRunNumber==20731){thisHeRunNumber=20738;}
		if(thisHeRunNumber==20732){thisHeRunNumber=20738;}
		if(thisHeRunNumber==20733){thisHeRunNumber=20738;}
		if(thisHeRunNumber==20734){thisHeRunNumber=20738;}
		if(thisHeRunNumber==20736){thisHeRunNumber=20738;}
		if(thisHeRunNumber==20737){thisHeRunNumber=20738;}
		if(thisHeRunNumber==20762){thisHeRunNumber=20789;}
		if(thisHeRunNumber==20763){thisHeRunNumber=20789;}
		if(thisHeRunNumber==20764){thisHeRunNumber=20789;}
		if(thisHeRunNumber==20791){thisHeRunNumber=20814;}
		if(thisHeRunNumber==20792){thisHeRunNumber=20814;}

		// Skipping Longitudinal Non-Production Runs
		if(thisHeRunNumber==22380){thisHeRunNumber=22393;}
		if(thisHeRunNumber==22389){thisHeRunNumber=22393;}
		if(thisHeRunNumber==22425){thisHeRunNumber=22436;}
		if(thisHeRunNumber==22426){thisHeRunNumber=22436;}

		// Skipping Transverse Non-Production Runs
		if(thisHeRunNumber==22461){thisHeRunNumber=22465;}


		for (int t=0; t<1000; t++)
		{
			filenameHe = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_R_";
			filenameHe += thisHeRunNumber;
			if (t != 0)
			{
				filenameHe += "_";
				filenameHe += t;
			}
			filenameHe += ".root";
			ifstream ifileHe(filenameHe);
			if (ifileHe)
			{
				cout << "Adding file to chainHe: " << filenameHe << endl;
				chainHe->Add(filenameHe);
			}
			else
			{
				cout << "File " << filenameHe << " does not exist. Ending here." << endl;
				t=999999999;
			}
			TFile fileHe(filenameHe);
		}
	}

	gStyle->SetPalette(1);

	TCut cut = ""; TCut kinematics = ""; TCut eventtype = ""; TCut dp = ""; TCut target = "";
	TCut tracks = ""; TCut thph = ""; TCut xbj = ""; TCut pssh = ""; TCut cerenkov = "";
	TCut q2nu = ""; TCut basic = ""; TCut cuts = "";

	TString imageCutsTitle = outputPlotsHere;
	imageCutsTitle += "HAND_plots_Run_Num_";
	imageCutsTitle += HeRunNumber;
	imageCutsTitle += "-";
	imageCutsTitle += endHeRunNumber;
	imageCutsTitle += "_basic_cuts";
	if (includeVetos) imageCutsTitle += "_with_vetos";
	if (includeAntivetos) {imageCutsTitle += "_with_antivetos";}
	if (antivetosAsVetos && includeAntivetos) {imageCutsTitle += "_as_vetos";}
	imageCutsTitle += ".png";

	hand_basic_cuts(cut, kinematics, eventtype, dp, target, tracks, thph, xbj, pssh, cerenkov, q2nu, basic, cuts, imageCutsTitle, HeRunNumber, endHeRunNumber, chainHe, numin, numax, q2min, q2max, bins, xmin, xmax, drawCuts, Q2);
	TString cutstring = TString(cuts);
	cout << "Cuts: " << cutstring << endl;
// **********************************************************************************************
	gStyle->SetOptFit(1111);
//	gStyle->SetOptFit(0001);
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
        hand_scaling_factors(HeRunNumber, endHeRunNumber, HeChargeScale, Helivetime, HeChargeScaleUp, HelivetimeUp, HeChargeScaleDown, HelivetimeDown, BeamChargeScaleUp, BeamlivetimeUp, BeamChargeScaleDown, BeamlivetimeDown);
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
	int whichplane = 1;
	int endplane = 5;
	if (SinglePlane) {whichplane = singleplane; endplane = singleplane+1;}
	int whichbar=0;
//	int whichbar=11;
	TString titleTotalSpinUpx = "Total Helicity Up vs. xBj";
	if (includeVetos) {titleTotalSpinUpx += " with vetos";}
	else {titleTotalSpinUpx += " without vetos";}
	titleTotalSpinUpx += " with goodTDC cuts";
	cout << "Drawing " << titleTotalSpinUpx << "..." << endl;
	TString plotTotalSpinUpx = "HANDTotalSpinUpx";
	TH1F *HANDTotalSpinUpx = new TH1F(plotTotalSpinUpx,titleTotalSpinUpx,nuBins,nuMin,nuMax);
	TString titleTotalSpinDownx = "Total Spin Down vs. xBj";
	if (includeVetos) {titleTotalSpinDownx += " with vetos";}
	else {titleTotalSpinDownx += " without vetos";}
	titleTotalSpinDownx += " with goodTDC cuts";
	cout << "Drawing " << titleTotalSpinDownx << "..." << endl;
	TString plotTotalSpinDownx = "HANDTotalSpinDownx";
	TH1F *HANDTotalSpinDownx = new TH1F(plotTotalSpinDownx,titleTotalSpinDownx,nuBins,nuMin,nuMax);
	TString titleTDCupTotal = "Total (TDCl + TDCr) Spin Up";
	if (includeVetos) {titleTDCupTotal += " with vetos";}
	else {titleTDCupTotal += " without vetos";}
	titleTDCupTotal += " with goodTDC cuts";
	cout << "Drawing " << titleTDCupTotal << "..." << endl;
	TString plotTDCupTotal = "TDCupTotal";
	TH1F *TDCupTotal = new TH1F(plotTDCupTotal,titleTDCupTotal,TDCbins,TDCmin,TDCmax);
	TString titleTDCdownTotal = "Total (TDCl + TDCr) Spin Down";
	if (includeVetos) {titleTDCdownTotal += " with vetos";}
	else {titleTDCdownTotal += " without vetos";}
	titleTDCdownTotal += " with goodTDC cuts";
	cout << "Drawing " << titleTDCdownTotal << "..." << endl;
	TString plotTDCdownTotal = "TDCdownTotal";
	TH1F *TDCdownTotal = new TH1F(plotTDCdownTotal,titleTDCdownTotal,TDCbins,TDCmin,TDCmax);

	for (int nplane=whichplane; nplane<endplane; nplane++)
	{
		if (nplane==0) maxbars=32;
		if (nplane==1) maxbars=30;
		if (nplane==2) maxbars=24;
		if (nplane==3) maxbars=22;
		if (nplane==4) maxbars=12;
		if (SingleBar) {whichbar = singlebar; maxbars = singlebar + 1;}
		for (int thisbar=whichbar; thisbar<maxbars; thisbar++)
		{

			TString goodPlane = nplane;
			TString goodPMT = thisbar;
			hand_define_vetos(includeVetos, includeAntivetos, antivetosAsVetos, nplane, thisbar, veto1plane, veto2plane, veto3plane, veto4plane, veto5plane, veto6plane, veto1bar, veto2bar, veto3bar, veto4bar, veto5bar, veto6bar, antiveto1plane, antiveto2plane, antiveto3plane, antiveto1bar, antiveto2bar, antiveto3bar, allVetos, allAntivetos, vetoTDCslSt, vetoTDCsrSt, vetoTDCsl, vetoTDCsr, vetoTDCs, vetoTDCcutmin, vetoTDCcutmax, antivetosTDCslSt, antivetosTDCsrSt);
			
			TString goodBar = "nd.p";
			goodBar += nplane;
			goodBar += ".";
			goodBar += thisbar;
			goodBar += " ";
			cout << "Good Bar: " << goodBar << endl;

			TString goodTDCl = "NA.nd.p";
			goodTDCl += nplane;
			if (nplane == 0) goodTDCl = "NA.veto";
			goodTDCl += ".lt_c[";
			goodTDCl += thisbar;
			goodTDCl += "]";
			TString goodTDCr = "NA.nd.p";
			goodTDCr += nplane;
			if (nplane == 0) goodTDCr = "NA.veto";
			goodTDCr += ".rt_c[";
			goodTDCr += thisbar;
			goodTDCr += "]";
			TString goodTDCs = goodTDCl;
			goodTDCs += ":";
			goodTDCs += goodTDCr;
		
                        TString goodADCl = "NA.nd.p";
                        goodADCl += nplane;
                        if (nplane == 0) goodADCl = "NA.veto";
                        goodADCl += ".la_c[";
                        goodADCl += thisbar;
                        goodADCl += "]";
                        TString goodADCr = "NA.nd.p";
                        goodADCr += nplane;
                        if (nplane == 0) goodADCr = "NA.veto";
                        goodADCr += ".ra_c[";
                        goodADCr += thisbar;
                        goodADCr += "]";
                        TString goodADCs = goodADCl;
                        goodADCs += ":";
                        goodADCs += goodADCr;
	
			TString canvasName = "handp";
			canvasName += nplane;
			canvasName += "b";
			canvasName += thisbar;
			TString canvasTitle = "HAND - Plane ";
			canvasTitle += nplane;
			canvasTitle += ", Bar ";
			canvasTitle += thisbar;
			TCanvas *handCanvas = new TCanvas(canvasName,canvasTitle,1400,770); //x,y
			handpad01 =  new TPad("handpad01","handpad01",0.0000,0.0000,0.1000,1.0000,0,0,0);
			handpad02 =  new TPad("handpad02","handpad02",0.1000,0.8000,0.5500,1.0000,0,0,0);
			handpad03 =  new TPad("handpad03","handpad03",0.5500,0.8000,1.0000,1.0000,0,0,0);
			handpad04 =  new TPad("handpad04","handpad04",0.1000,0.2000,0.5500,0.4000,0,0,0);
			handpad05 =  new TPad("handpad05","handpad05",0.5500,0.2000,1.0000,0.4000,0,0,0);
			handpad06 =  new TPad("handpad06","handpad06",0.1000,0.0000,0.5500,0.2000,0,0,0);
			handpad07 =  new TPad("handpad07","handpad07",0.5500,0.0000,1.0000,0.2000,0,0,0);
			handpad08 =  new TPad("handpad08","handpad08",0.1000,0.6000,0.3250,0.8000,0,0,0);
			handpad09 =  new TPad("handpad09","handpad09",0.3250,0.6000,0.5500,0.8000,0,0,0);
			handpad10 =  new TPad("handpad10","handpad10",0.5500,0.6000,0.7750,0.8000,0,0,0);
			handpad11 =  new TPad("handpad11","handpad11",0.7750,0.6000,1.0000,0.8000,0,0,0);
			handpad12 =  new TPad("handpad12","handpad12",0.1000,0.4000,0.5500,0.6000,0,0,0);
			handpad13 =  new TPad("handpad13","handpad13",0.5500,0.4000,1.0000,0.6000,0,0,0);
			handpad01->Draw(); handpad02->Draw(); handpad03->Draw(); handpad04->Draw(); handpad05->Draw();
			handpad06->Draw(); handpad07->Draw(); handpad08->Draw(); handpad09->Draw(); handpad10->Draw();
			handpad11->Draw(); handpad12->Draw(); handpad13->Draw();

			// This section will run hand_draw.h which will draw the HAND in handpad01.
			handpad01->cd();
			hand_draw(HeRunNumber, endHeRunNumber, antivetosAsVetos, allVetos, goodBar, allAntivetos);
			handpad01->Update();

			TString goodTDCleftcutString = "(NA.nd.p";
			goodTDCleftcutString += nplane;
			if (nplane == 0) {goodTDCleftcutString = "(NA.veto";}
			goodTDCleftcutString += ".lt_c[";
			goodTDCleftcutString += thisbar;
			goodTDCleftcutString += "]<";
			goodTDCleftcutString += goodTDCleftcutmin;
			if (nplane > 0)
			{
				goodTDCleftcutString += " || NA.nd.p";
				goodTDCleftcutString += nplane;
			}
			if (nplane == 0) {goodTDCleftcutString += " || NA.veto";}
			goodTDCleftcutString += ".lt_c[";
			goodTDCleftcutString += thisbar;
			goodTDCleftcutString += "]>";
			goodTDCleftcutString += goodTDCleftcutmax;
			goodTDCleftcutString += ")";
			cout << "goodTDCleftcutString = " << goodTDCleftcutString << endl;
			TCut goodTDCleftcut = goodTDCleftcutString;
	
			TString goodTDCrightcutString = "(NA.nd.p";
			goodTDCrightcutString += nplane;
			if (nplane == 0) {goodTDCrightcutString = "(NA.veto";}
			goodTDCrightcutString += ".rt_c[";
			goodTDCrightcutString += thisbar;
			goodTDCrightcutString += "]<";
			goodTDCrightcutString += goodTDCrightcutmin;
			if (nplane > 0)
			{
				goodTDCrightcutString += " || NA.nd.p";
				goodTDCrightcutString += nplane;
			}
			if (nplane == 0) {goodTDCrightcutString += " || NA.veto";}
			goodTDCrightcutString += ".rt_c[";
			goodTDCrightcutString += thisbar;
			goodTDCrightcutString += "]>";
			goodTDCrightcutString += goodTDCrightcutmax;
			goodTDCrightcutString += ")";
			cout << "goodTDCrightcutString = " << goodTDCrightcutString << endl;
			TCut goodTDCrightcut = goodTDCrightcutString;
		
			TString firstTrackString = "NA.n.plane[0]==";
			firstTrackString += (nplane - 1);
			firstTrackString += " && NA.n.pad[0]==";
			firstTrackString += thisbar;
			TCut firstTrack = firstTrackString;

	
			goodTDCcut = (goodTDCleftcut && goodTDCrightcut);

//			cout << "Cuts: " << cutstring << endl;
			TString vetoCutString = TString(vetoTDCs);
//			cout << "Veto Cuts: " << vetoCutString << endl; 

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
//			cout << "plotHANDleft: " << plotHANDleft << ", plotHANDleftcut: " << plotHANDleftcut << endl;
			cout << "goodTDCl: " << goodTDCl << endl;
			TH1F *HANDleft = new TH1F(plotHANDleft,titleHANDleft,TDCbins,TDCmin,TDCmax);
			HANDleft->SetMinimum(0);
			TH1F *HANDleftcut = new TH1F(plotHANDleftcut,titleHANDleft,TDCbins,TDCmin,TDCmax);
			HANDleftcut->SetMinimum(0);
			TString HANDleftTDC = goodTDCl;
			HANDleftTDC += ">>";
			HANDleftTDC += plotHANDleft;
			TString HANDleftTDCcut = goodTDCl;
			HANDleftTDCcut += ">>";
			HANDleftTDCcut += plotHANDleftcut;
			chainHe->Draw(HANDleftTDC, cuts && vetoTDCs && firstTrack,"");
//			chainHe->Draw(HANDleftTDC, vetoTDCs,"");
//			HANDleft->Scale(1/(HeChargeScale*Helivetime));
			HANDleft->Draw();
			if (!includeVetos) {chainHe->Draw(HANDleftTDCcut, cuts && goodTDCleftcut&& firstTrack,"same");}
			if (includeVetos) {chainHe->Draw(HANDleftTDCcut, cuts && vetoTDCs && goodTDCleftcut && firstTrack,"same");}
			HANDleftcut->SetFillColor(kViolet);
//			HANDleftcut->Scale(1/(HeChargeScale*Helivetime));
			HANDleftcut->Draw("same");
			// ********************************************************************************
			// This section below gathers and prints some statistics on the plot
			double numHANDleftcutEvents = 0;
			for (int i=0; i<TDCbins; i++){ numHANDleftcutEvents = numHANDleftcutEvents + HANDleftcut->GetBinContent(i);}
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
			TH1F *HANDright = new TH1F(plotHANDright,titleHANDright,TDCbins,TDCmin,TDCmax);
			HANDright->SetMinimum(0);
			TH1F *HANDrightcut = new TH1F(plotHANDrightcut,titleHANDright,TDCbins,TDCmin,TDCmax);
			HANDrightcut->SetMinimum(0);
			TString HANDrightTDC = goodTDCr;
			HANDrightTDC += ">>";
			HANDrightTDC += plotHANDright;
			TString HANDrightTDCcut = goodTDCr;
			HANDrightTDCcut += ">>";
			HANDrightTDCcut += plotHANDrightcut;
			chainHe->Draw(HANDrightTDC, cuts && vetoTDCs && firstTrack,"");
//			HANDright->Scale(1/(HeChargeScale*Helivetime));
			HANDright->Draw();
			if (!includeVetos) {chainHe->Draw(HANDrightTDCcut, cuts && firstTrack && goodTDCrightcut,"same");}
			if (includeVetos) {chainHe->Draw(HANDrightTDCcut, cuts && vetoTDCs && goodTDCrightcut && firstTrack,"same");}
			HANDrightcut->SetFillColor(kViolet);
//			HANDrightcut->Scale(1/(HeChargeScale*Helivetime));
			HANDrightcut->Draw("same");
			// ********************************************************************************
			// This section below gathers and prints some statistics on the plot
			double numHANDrightcutEvents = 0;
			for (int j=0; j<TDCbins; j++){ numHANDrightcutEvents = numHANDrightcutEvents + HANDrightcut->GetBinContent(j);}
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


			handpad08->cd();
			TString titleTDClup = "TDCl Spin Up for Plane #";
			titleTDClup += nplane;
			titleTDClup += ", PMT # ";
			titleTDClup += thisbar;
			cout << "Drawing " << titleTDClup << "..." << endl;
			TString plotTDClup = "TDClup_p";
			plotTDClup += nplane;
			plotTDClup += "_b";
			plotTDClup += thisbar;
			TString TDClupevents = "(";
			TDClupevents += goodTDCl;
			TDClupevents += ")>>";
			TDClupevents += plotTDClup;
			TH1F *TDClup = new TH1F(plotTDClup,titleTDClup,TDCbins,TDCmin,TDCmax);
			chainHe->Draw(TDClupevents, cuts && vetoTDCs && firstTrack && goodTDCcut &&"((g0hel.R.helicity==1 && g.runnum<22467) || (g0hel.R.helicity==-1 && g.runnum>22468))","");
			TDClup->SetMinimum(0);
			TDClup->Draw();
			TDClupFactors = new TPaveText(0.11,0.65,0.5,0.89,"NDC");
			TString TDClupFactorsString = "Total # of channels: ";
			TDClupFactorsString += (TDCmax-TDCmin);
			TString TDClupFactorsString1 = "# Channels Cut: ";
			TDClupFactorsString1 += (goodTDCleftcutmax - goodTDCleftcutmin);
			TString TDClupFactorsString2 = "# Channels Used: ";
			TDClupFactorsString2 += ((TDCmax-TDCmin) - (goodTDCleftcutmax - goodTDCleftcutmin));
			TText *t1 = TDClupFactors->AddText(TDClupFactorsString);
			TText *t2 = TDClupFactors->AddText(TDClupFactorsString1);
			TText *t3 = TDClupFactors->AddText(TDClupFactorsString2);
			TDClupFactors->Draw("same");
			handpad08->Update();

			handpad09->cd();
			TString titleTDCldown = "TDCl Spin Down for Plane #";
			titleTDCldown += nplane;
			titleTDCldown += ", PMT # ";
			titleTDCldown += thisbar;
			cout << "Drawing " << titleTDCldown << "..." << endl;
			TString plotTDCldown = "TDCldown_p";
			plotTDCldown += nplane;
			plotTDCldown += "_b";
			plotTDCldown += thisbar;
			TString TDCldownevents = "(";
			TDCldownevents += goodTDCl;
			TDCldownevents += ")>>";
			TDCldownevents += plotTDCldown;
			TH1F *TDCldown = new TH1F(plotTDCldown,titleTDCldown,TDCbins,TDCmin,TDCmax);
			chainHe->Draw(TDCldownevents, cuts && vetoTDCs && firstTrack && goodTDCcut &&"((g0hel.R.helicity==-1 && g.runnum<22467) || (g0hel.R.helicity==1 && g.runnum>22468))","");
			TDCldown->SetMinimum(0);
			TDCldown->Draw();
			handpad09->Update();

			handpad10->cd();
			TString titleTDCrup = "TDCr Spin Up for Plane #";
			titleTDCrup += nplane;
			titleTDCrup += ", PMT # ";
			titleTDCrup += thisbar;
			cout << "Drawing " << titleTDCrup << "..." << endl;
			TString plotTDCrup = "TDCrup_p";
			plotTDCrup += nplane;
			plotTDCrup += "_b";
			plotTDCrup += thisbar;
			TString TDCrupevents = "(";
			TDCrupevents += goodTDCr;
			TDCrupevents += ")>>";
			TDCrupevents += plotTDCrup;
			TH1F *TDCrup = new TH1F(plotTDCrup,titleTDCrup,TDCbins,TDCmin,TDCmax);
			chainHe->Draw(TDCrupevents, cuts && vetoTDCs && firstTrack && goodTDCcut &&"((g0hel.R.helicity==1 && g.runnum<22467) || (g0hel.R.helicity==-1 && g.runnum>22468))","");
			TDCrup->SetMinimum(0);
			TDCrup->Draw();
			TDCrupFactors = new TPaveText(0.11,0.65,0.5,0.89,"NDC");
			TString TDCrupFactorsString = "Total # of channels: ";
			TDCrupFactorsString += (TDCmax-TDCmin);
			TString TDCrupFactorsString1 = "# Channels Cut: ";
			TDCrupFactorsString1 += (goodTDCrightcutmax - goodTDCrightcutmin);
			TString TDCrupFactorsString2 = "# Channels Used: ";
			TDCrupFactorsString2 += ((TDCmax-TDCmin) - (goodTDCrightcutmax - goodTDCrightcutmin));
			TDCrupFactorsString2 += ", bins = ";
			TDCrupFactorsString2 += TDCbins;
			TText *t1 = TDCrupFactors->AddText(TDCrupFactorsString);
			TText *t2 = TDCrupFactors->AddText(TDCrupFactorsString1);
			TText *t3 = TDCrupFactors->AddText(TDCrupFactorsString2);
			TDCrupFactors->Draw("same");
			handpad10->Update();

			handpad11->cd();
			TString titleTDCrdown = "TDCr Spin Down for Plane #";
			titleTDCrdown += nplane;
			titleTDCrdown += ", PMT # ";
			titleTDCrdown += thisbar;
			cout << "Drawing " << titleTDCrdown << "..." << endl;
			TString plotTDCrdown = "TDCrdown_p";
			plotTDCrdown += nplane;
			plotTDCrdown += "_b";
			plotTDCrdown += thisbar;
			TString TDCrdownevents = "(";
			TDCrdownevents += goodTDCr;
			TDCrdownevents += ")>>";
			TDCrdownevents += plotTDCrdown;
			TH1F *TDCrdown = new TH1F(plotTDCrdown,titleTDCrdown,TDCbins,TDCmin,TDCmax);
			chainHe->Draw(TDCrdownevents, cuts && vetoTDCs && firstTrack && goodTDCcut &&"((g0hel.R.helicity==-1 && g.runnum<22467) || (g0hel.R.helicity==1 && g.runnum>22468))","");
			TDCrdown->SetMinimum(0);
			TDCrdown->Draw();
			handpad11->Update();

			handpad12->cd();
			TDCupTotal->Add(TDClup);
			TDCupTotal->Add(TDCrup);
			TDCupTotal->SetMinimum(0);
			TDCupTotal->Draw();
			TString fitTDCupminstring = "fitTDCupmin_p";
			fitTDCupminstring += nplane;
			fitTDCupminstring += "_b";
			fitTDCupminstring += thisbar;
			TString fitTDCupmaxstring = "fitTDCupmax_p";
			fitTDCupmaxstring += nplane;
			fitTDCupmaxstring += "_b";
			fitTDCupmaxstring += thisbar;
			TString fitTDCupfullstring = "fitTDCupfull_p";
			fitTDCupfullstring += nplane;
			fitTDCupfullstring += "_b";
			fitTDCupfullstring += thisbar;
			TF1 *fitTDCupmin = new TF1(fitTDCupminstring,"[0]",TDCmin,goodTDCleftcutmin);
			TF1 *fitTDCupmax = new TF1(fitTDCupmaxstring,"[0]",goodTDCleftcutmax,TDCmax-100);
			TF1 *fitTDCupfull = new TF1(fitTDCupfullstring,"[0]",TDCmin,TDCmax-100);
			fitTDCupmin->SetParNames("upsmall");
			fitTDCupmax->SetParNames("upbig");
			fitTDCupfull->SetParNames("upfull");
			fitTDCupmin->SetLineColor(kBlue);
			fitTDCupmax->SetLineColor(kBlue);
			fitTDCupfull->SetLineColor(kRed);
			TDCupTotal->Fit(fitTDCupmin,"R");
			TDCupTotal->Fit(fitTDCupmax,"R+");
			TDCupTotal->Fit(fitTDCupfull,"R+");
		        double fitTDCupminconst = fitTDCupmin->GetParameter(0);
		        double fitTDCupmaxconst = fitTDCupmax->GetParameter(0);
		        double fitTDCupfullconst = fitTDCupfull->GetParameter(0);
		        double fitTDCupminerr = fitTDCupmin->GetParError(0);
		        double fitTDCupmaxerr = fitTDCupmax->GetParError(0);
		        double fitTDCupfullerr = fitTDCupfull->GetParError(0);
			TDCupFactors = new TPaveText(0.11,0.69,0.4,0.89,"NDC");
			TString fitTDCupminstring = "upsmall = ";
			fitTDCupminstring += fitTDCupminconst;
			fitTDCupminstring += " ± ";
			fitTDCupminstring += fitTDCupminerr;
			TString fitTDCupmaxstring = "upbig = ";
			fitTDCupmaxstring += fitTDCupmaxconst;
			fitTDCupmaxstring += " ± ";
			fitTDCupmaxstring += fitTDCupmaxerr;
			TString fitTDCupfullstring = "upfull = ";
			fitTDCupfullstring += fitTDCupfullconst;
			fitTDCupfullstring += " ± ";
			fitTDCupfullstring += fitTDCupfullerr;
			TText *t1 = TDCupFactors->AddText(fitTDCupminstring);
			TText *t2 = TDCupFactors->AddText(fitTDCupmaxstring);
			TText *t3 = TDCupFactors->AddText(fitTDCupfullstring);
			TDCupFactors->Draw("same");
			handpad12->Update();

			handpad13->cd();
			TDCdownTotal->Add(TDCldown);
			TDCdownTotal->Add(TDCrdown);
			TDCdownTotal->SetMinimum(0);
			TDCdownTotal->Draw();
			TString fitTDCdownminstring = "fitTDCdownmin_p";
			fitTDCdownminstring += nplane;
			fitTDCdownminstring += "_b";
			fitTDCdownminstring += thisbar;
			TString fitTDCdownmaxstring = "fitTDCdownmax_p";
			fitTDCdownmaxstring += nplane;
			fitTDCdownmaxstring += "_b";
			fitTDCdownmaxstring += thisbar;
			TString fitTDCdownfullstring = "fitTDCdownfull_p";
			fitTDCdownfullstring += nplane;
			fitTDCdownfullstring += "_b";
			fitTDCdownfullstring += thisbar;
			TF1 *fitTDCdownmin = new TF1(fitTDCdownminstring,"[0]",TDCmin,goodTDCleftcutmin);
			TF1 *fitTDCdownmax = new TF1(fitTDCdownmaxstring,"[0]",goodTDCleftcutmax,TDCmax-100);
			TF1 *fitTDCdownfull = new TF1(fitTDCdownfullstring,"[0]",TDCmin,TDCmax-100);
			fitTDCdownmin->SetParNames("downsmall");
			fitTDCdownmax->SetParNames("downbig");
			fitTDCdownfull->SetParNames("downfull");
			fitTDCdownmin->SetLineColor(kBlue);
			fitTDCdownmax->SetLineColor(kBlue);
			fitTDCdownfull->SetLineColor(kRed);
			TDCdownTotal->Fit(fitTDCdownmin,"R");
			TDCdownTotal->Fit(fitTDCdownmax,"R+");
			TDCdownTotal->Fit(fitTDCdownfull,"R+");
		        double fitTDCdownminconst = fitTDCdownmin->GetParameter(0);
		        double fitTDCdownmaxconst = fitTDCdownmax->GetParameter(0);
		        double fitTDCdownfullconst = fitTDCdownfull->GetParameter(0);
		        double fitTDCdownminerr = fitTDCdownmin->GetParError(0);
		        double fitTDCdownmaxerr = fitTDCdownmax->GetParError(0);
		        double fitTDCdownfullerr = fitTDCdownfull->GetParError(0);
			TDCdownFactors = new TPaveText(0.11,0.69,0.4,0.89,"NDC");
			TString fitTDCdownminstring = "downsmall = ";
			fitTDCdownminstring += fitTDCdownminconst;
			fitTDCdownminstring += " ± ";
			fitTDCdownminstring += fitTDCdownminerr;
			TString fitTDCdownmaxstring = "downbig = ";
			fitTDCdownmaxstring += fitTDCdownmaxconst;
			fitTDCdownmaxstring += " ± ";
			fitTDCdownmaxstring += fitTDCdownmaxerr;
			TString fitTDCdownfullstring = "downfull = ";
			fitTDCdownfullstring += fitTDCdownfullconst;
			fitTDCdownfullstring += " ± ";
			fitTDCdownfullstring += fitTDCdownfullerr;
			TText *t1 = TDCdownFactors->AddText(fitTDCdownminstring);
			TText *t2 = TDCdownFactors->AddText(fitTDCdownmaxstring);
			TText *t3 = TDCdownFactors->AddText(fitTDCdownfullstring);
			TDCdownFactors->Draw("same");
			handpad13->Update();

/*			TDClupFactors = new TPaveText(0.11,0.69,0.4,0.89,"NDC");
			TString TDClupFactorsString = "Total # of channels: ";
			TDClupFactorsString += (TDClmax-TDClmin);
			TString TDClupFactorsString1 = "# Channels Cut: ";
			TDClupFactorsString1 += (goodTDCleftcutmax - goodTDCleftcutmin);
			TString TDClupFactorsString2 = "# Channels Used: ";
			TDClupFactorsString2 += ((TDCmax-TDCmin) - (goodTDCleftcutmax - goodTDCleftcutmin));
			TText *t1 = TDClupFactors->AddText(TDClupFactorsString);
			TText *t2 = TDClupFactors->AddText(TDClupFactorsString1);
			TText *t3 = TDClupFactors->AddText(TDClupFactorsString2);
			TDClupFactors->Draw("same");
			handpad08->Update();

			handpad09->cd();
			TDCupTotal->Add(TDCup);
			TDCupTotal->SetMinimum(0);
			TDCupTotal->Draw();
			handpad09->Update();

			handpad10->cd();
			TString titleTDCdown = "(TDCl + TDCr) Spin Down for Plane #";
			titleTDCdown += nplane;
			titleTDCdown += ", PMT # ";
			titleTDCdown += thisbar;
			cout << "Drawing " << titleTDCdown << "..." << endl;
			TString plotTDCdown = "TDCdown_p";
			plotTDCdown += nplane;
			plotTDCdown += "_b";
			plotTDCdown += thisbar;
			TString TDCdownevents = "(";
			TDCdownevents += goodTDCl;
			TDCdownevents += " + ";
			TDCdownevents += goodTDCr;
			TDCdownevents += ")>>";
			TDCdownevents += plotTDCdown;
			TH1F *TDCdown = new TH1F(plotTDCdown,titleTDCdown,TDCbins,TDCmin,TDCmax);
			chainHe->Draw(TDCdownevents, cuts && vetoTDCs && firstTrack && goodTDCcut &&"((g0hel.R.helicity==-1 && g.runnum<22467) || (g0hel.R.helicity==1 && g.runnum>22468))","");
			TDCdown->SetMinimum(0);
			TDCdown->Draw();
			TDCdownFactors = new TPaveText(0.11,0.69,0.4,0.89,"NDC");
			TString TDCdownFactorsString = "Total # of channels: ";
			TDCdownFactorsString += (TDCmax-TDCmin);
			TString TDCdownFactorsString1 = "# Channels Cut: ";
			TDCdownFactorsString1 += (goodTDCleftcutmax - goodTDCleftcutmin);
			TString TDCdownFactorsString2 = "# Channels Used: ";
			TDCdownFactorsString2 += ((TDCmax-TDCmin) - (goodTDCleftcutmax - goodTDCleftcutmin));
			TText *t1 = TDCdownFactors->AddText(TDCdownFactorsString);
			TText *t2 = TDCdownFactors->AddText(TDCdownFactorsString1);
			TText *t3 = TDCdownFactors->AddText(TDCdownFactorsString2);
			TDCdownFactors->Draw("same");
			handpad10->Update();

			handpad11->cd();
			TDCdownTotal->Add(TDCdown);
			TDCdownTotal->SetMinimum(0);
			TDCdownTotal->Draw();
			handpad11->Update();
*/


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
			TH1F *HANDSpinUpx = new TH1F(plotSpinUpx,titleSpinUpxcut,nuBins,nuMin,nuMax);
			TString HANDSpinUpxString = "PriKineR.nu";
			HANDSpinUpxString += ">>";
			HANDSpinUpxString += plotSpinUpx;
			if (includeVetos) {chainHe->Draw(HANDSpinUpxString, cuts && vetoTDCs && goodTDCcut && firstTrack && "((g0hel.R.helicity==1 && g.runnum<22467) || (g0hel.R.helicity==-1 && g.runnum>22468))","");}
			if (!includeVetos) {chainHe->Draw(HANDSpinUpxString, cuts && firstTrack && goodTDCcut && "((g0hel.R.helicity==1 && g.runnum<22467) || (g0hel.R.helicity==-1 && g.runnum>22468))","");}
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
			TH1F *HANDSpinDownx = new TH1F(plotSpinDownx,titleSpinDownxcut,nuBins,nuMin,nuMax);
			TString HANDSpinDownxString = "PriKineR.nu";
			HANDSpinDownxString += ">>";
			HANDSpinDownxString += plotSpinDownx;
			if (includeVetos) {chainHe->Draw(HANDSpinDownxString, cuts && vetoTDCs && goodTDCcut && firstTrack && "((g0hel.R.helicity==-1 && g.runnum<22467) || (g0hel.R.helicity==1 && g.runnum>22468))","");}
			if (!includeVetos) {chainHe->Draw(HANDSpinDownxString, cuts && firstTrack && goodTDCcut && "((g0hel.R.helicity==-1 && g.runnum<22467) || (g0hel.R.helicity==1 && g.runnum>22468))","");}
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
			HANDTotalSpinUpx->Add(HANDSpinUpx);
			HANDTotalSpinUpx->SetMinimum(0);
			HANDTotalSpinUpx->Draw();
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
			HANDTotalSpinDownx->Add(HANDSpinDownx);
			HANDTotalSpinDownx->SetMinimum(0);
			HANDTotalSpinDownx->Draw();
			handpad07->Update();




			TString imageTitle = outputPlotsHere;
			imageTitle += "TDC_plots_for_beam_asym_Run_Num_";
			imageTitle += HeRunNumber;
			imageTitle += "-";
			imageTitle += endHeRunNumber;
			imageTitle += "_p";
			imageTitle += nplane;
			imageTitle += "_b";
			if (thisbar < 10) {imageTitle += "0";}
			imageTitle += thisbar;
			if (includeVetos) {imageTitle += "_with_vetos";}
			if (includeAntivetos) {imageTitle += "_with_antivetos";}
			if (antivetosAsVetos && includeAntivetos) {imageTitle += "_as_vetos";}
			imageTitle+= ".png";
			handCanvas->Print(imageTitle);

			TString imageAntivetosTitle = outputPlotsHere;
			imageAntivetosTitle += "antivetos_for_beam_asym_for_Run_Num_";
			imageAntivetosTitle += HeRunNumber;
			imageAntivetosTitle += "-";
			imageAntivetosTitle += endHeRunNumber;
			imageAntivetosTitle += "_p";
			imageAntivetosTitle += nplane;
			imageAntivetosTitle += "_b";
			imageAntivetosTitle += thisbar;
			if (includeVetos) {imageAntivetosTitle += "_with_vetos";}
			if (includeAntivetos) {imageAntivetosTitle += "_with_antivetos";}
			if (antivetosAsVetos && includeAntivetos) {imageAntivetosTitle += "_as_vetos";}
			imageAntivetosTitle += ".png";
			if (includeAntivetos) {hand_draw_antivetos(antiveto1plane, antiveto1bar, antiveto2plane, antiveto2bar, antiveto3plane, antiveto3bar, HeRunNumber, endHeRunNumber, chainHe, TDCbins, TDCmin, TDCmax, cuts, goodTDCcut, vetoTDCs, imageAntivetosTitle, nplane, thisbar, includeVetos, includeAntivetos, antivetosAsVetos, veto1plane, veto1bar, veto2plane, veto2bar, veto3plane, veto3bar, veto4plane, veto4bar, veto5plane, veto5bar, veto6plane, veto6bar, allVetos, allAntivetos);}

// *********************************************************************************************************
// The section below will plot the bars used for vetos for the previous canvas. It will consist of two
// canvases, one without the veto cuts made and one with to show the different.
			TString imageVetosWithoutVetosTitle = outputPlotsHere;
			imageVetosWithoutVetosTitle += "vetos_without_veto_cut_for_beam_asym_for_Run_Num_";
			imageVetosWithoutVetosTitle += HeRunNumber;
			imageVetosWithoutVetosTitle += "-";
			imageVetosWithoutVetosTitle += endHeRunNumber;
			imageVetosWithoutVetosTitle += "_p";
			imageVetosWithoutVetosTitle += nplane;
			imageVetosWithoutVetosTitle += "_b";
			imageVetosWithoutVetosTitle += thisbar;
			if (includeVetos) {imageVetosWithoutVetosTitle += "_with_vetos";}
			if (includeAntivetos) {imageVetosWithoutVetosTitle += "_with_antivetos";}
			if (antivetosAsVetos && includeAntivetos) {imageVetosWithoutVetosTitle += "_as_vetos";}
			imageVetosWithoutVetosTitle+= ".png";

			TString imageVetosWithVetosTitle = outputPlotsHere;
			imageVetosWithVetosTitle += "vetos_with_veto_cut_for_beam_asym_Run_Num_";
			imageVetosWithVetosTitle += HeRunNumber;
			imageVetosWithVetosTitle += "-";
			imageVetosWithVetosTitle += endHeRunNumber;
			imageVetosWithVetosTitle += "_p";
			imageVetosWithVetosTitle += nplane;
			imageVetosWithVetosTitle += "_b";
			imageVetosWithVetosTitle += thisbar;
			if (includeVetos) {imageVetosWithVetosTitle += "_with_vetos";}
			if (includeAntivetos) {imageVetosWithVetosTitle += "_with_antivetos";}
			if (antivetosAsVetos && includeAntivetos) {imageVetosWithVetosTitle += "_as_vetos";}
			imageVetosWithVetosTitle+= ".png";

//			if (includeVetos) {hand_draw_vetos(veto1plane, veto2plane, veto3plane, veto4plane, veto5plane, veto6plane,veto1bar, veto2bar, veto3bar, veto4bar, veto5bar, veto6bar, imageVetosWithoutVetosTitle, imageVetosWithVetosTitle, HeRunNumber, endHeRunNumber, chainHe, nplane, thisbar, TDCbins, TDCmin, TDCmax, cuts, vetoTDCs, antivetosAsVetos, allVetos, allAntivetos);}

//		if ((nplane==1) && (thisbar==15)) { nplane = 2; thisbar = 7;}
//		if ((nplane==2) && (thisbar==12)) { nplane = 3; thisbar = 6;}
//		if ((nplane==3) && (thisbar==11)) { nplane = 4; thisbar = 3;}
//		if ((nplane==4) && (thisbar==7))  { nplane = 4; thisbar = 99;}


		}
	}


//	The block below will let me find out how well my background fit works
//	*******************************************************************************
	TCanvas *eventDistCanvas = new TCanvas("eventDistCanvas","eventDistCanvas",1400,770); 
	eventDistpad01 = new TPad("eventDistpad01","eventDistpad01",0.0000,0.0000,0.5000,1.0000);
	eventDistpad02 = new TPad("eventDistpad02","eventDistpad02",0.5000,0.0000,1.0000,1.0000);
	eventDistpad01->Draw(); eventDistpad02->Draw();
	int eventsup;
	int eventsdown;
	int eventsupmin;
	int eventsupmax;
	int eventsdownmin;
	int eventsdownmax;
	for (i=0; i<TDCbins; i++)
	{
		eventsup = TDCupTotal->GetBinContent(i);
		eventsdown = TDCdownTotal->GetBinContent(i);
		if (eventsupmin > eventsup) {eventsupmin = eventsup; cout << "eventsupmin = " << eventsupmin << "; i = " << i << endl;}
		if (eventsupmax < eventsup) {eventsupmax = eventsup; cout << "eventsupmax = "  << eventsupmax << "; i = " << i << endl;}
		if (eventsdownmin > eventsdown) {eventsdownmin = eventsdown; cout << "eventsdownmin = " << eventsdownmin << "; i = " << i << endl;}
		if (eventsdownmax < eventsdown) {eventsdownmax = eventsdown; cout << "eventsdownmax = " << eventsdownmax << "; i = " << i << endl;}
	}
	TH1F *eventDistUp = new TH1F("eventDistUp","# bins v. # events/bin for spin up",eventsupmax - eventsupmin,eventsupmin,eventsupmax);
	TH1F *eventDistDown = new TH1F("eventDistDown","# bins v. # events/bin for spin down",eventsdownmax - eventsdownmin,eventsdownmin,eventsdownmax);
	for (i=0; i<TDCbins; i++)
	{
		eventsup = TDCupTotal->GetBinContent(i);
		eventsdown = TDCdownTotal->GetBinContent(i);
		eventDistUp->Fill(eventsup);
		eventDistDown->Fill(eventsdown);
	}
	TH1F *eventDistUpRebin = (TH1F*)eventDistUp->Rebin(500,"eventDistUpRebin");
	TH1F *eventDistDownRebin = (TH1F*)eventDistDown->Rebin(500,"eventDistDownRebin");
	eventDistpad01->cd();
	eventDistUpRebin->Draw();
	TF1 *upfit = new TF1("upfit","gaus",10000,eventsupmax);
	eventDistUpRebin->Fit(upfit,"R");
	eventDistpad01->Update();

	eventDistpad02->cd();
	eventDistDownRebin->Draw();
	TF1 *downfit = new TF1("downfit","gaus",10000,eventsupmax);
	eventDistDownRebin->Fit(downfit,"R");
	eventDistpad02->Update();
//	*******************************************************************************



	TString canvasTotalSpinTest = "TotalSpinTest";
	TString canvasTitleTotalSpinTest = "HAND - Total Spin (Not Scaled)";
	TCanvas *totalSpinTestCanvas = new TCanvas(canvasTotalSpinTest,canvasTitleTotalSpinTest,1400,770); //x,y
	totalspintestpad01 =  new TPad("totalspintestpad01","totalspintestpad01",0.0000,0.5000,0.5000,1.0000,0,0,0);
	totalspintestpad02 =  new TPad("totalspintestpad02","totalspintestpad02",0.5000,0.5000,1.0000,1.0000,0,0,0);
	totalspintestpad03 =  new TPad("totalspintestpad03","totalspintestpad03",0.0000,0.0000,1.0000,0.5000,0,0,0);
	totalspintestpad01->Draw(); totalspintestpad02->Draw(); totalspintestpad03->Draw();

	totalspintestpad01->cd();
	HANDTotalSpinUpx->SetTitle("Total Spin Up (Not Scaled)");
	HANDTotalSpinUpx->Draw();
	totalspintestpad01->Update();

	totalspintestpad02->cd();
	HANDTotalSpinDownx->SetTitle("Total Spin Down (Not Scaled)");
	HANDTotalSpinDownx->Draw();
	totalspintestpad02->Update();

	totalspintestpad03->cd();
        TF1 *fitasymtest = new TF1("fitasymtest","[0]",nuMin,nuMax);
	HANDAsymTest = HANDTotalSpinUpx->GetAsymmetry(HANDTotalSpinDownx);
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
	TCanvas *asymCanvas = new TCanvas("asymCanvas",asymTitle,1400,770); //x,y
	asymCanvas->cd();
	asymCanvas->SetGrid();
	Double_t x[nuBins], y[nuBins], errorx[nuBins], errory[nuBins];
	double minError;
	double maxError;
	double posStuff;
	double negStuff;
	double UpEvents;
	double DownEvents;
	asymOutFile << "Runs " << HeRunNumber << "-" << endHeRunNumber << endl;
	cout << "Runs " << HeRunNumber << "-" << endHeRunNumber << endl;
	asymOutFile << "xBj	Asymmetry	Stat. Error	# BeamPos Events	BeamPos Charge	PosBeam LT	# Neg Events	BeamNeg Charge	NegBeam LT" << endl;
	cout << "xBj	Asymmetry	Stat. Error	# BeamPos Events	BeamPos Charge	PosBeam LT	# Neg Events	BeamNeg Charge	NegBeam LT" << endl;
	for (int i=0; i<nuBins; i++)
	{	
		UpEvents = HANDTotalSpinUpx->GetBinContent(i);
		DownEvents = HANDTotalSpinDownx->GetBinContent(i);
		x[i] = HANDTotalSpinUpx->GetBinCenter(i);
		if (x[i] != (HANDTotalSpinDownx->GetBinCenter(i))) { cout << endl << endl << "!!!!!!!!!!!!!!!!!!!!!!!!!! STOP! THERE'S A PROBLEM!!!!!!!!!!!!!!!!!!!!!!" << endl << endl << endl;}
		posStuff = UpEvents/(BeamChargeScaleUp * BeamlivetimeUp + 1e-15);
		negStuff = DownEvents/(BeamChargeScaleDown * BeamlivetimeDown + 1e-15);
		y[i] = ((posStuff - negStuff)/(posStuff + negStuff + 1e-15));
		errory[i] = 2*(DownEvents*sqrt(UpEvents) + UpEvents*sqrt(DownEvents))/((BeamChargeScaleUp*BeamlivetimeUp)*(BeamChargeScaleDown*BeamlivetimeDown)*pow((UpEvents/(BeamChargeScaleUp*BeamlivetimeUp)) + (DownEvents/(BeamChargeScaleDown*BeamlivetimeDown)),2) + 1e-15);
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
		asymOutFile << x[i] << "	" << y[i] << "	" << errory[i] << "	" << UpEvents << "	" << BeamChargeScaleUp << "	" << BeamlivetimeUp << "	" << DownEvents << "	" << BeamChargeScaleDown << "	" << BeamlivetimeDown << endl;
		cout << x[i] << "	" << y[i] << "	" << errory[i] << "	" << UpEvents << "	" << BeamChargeScaleUp << "	" << BeamlivetimeUp << "	" << DownEvents << "	" << BeamChargeScaleDown << "	" << BeamlivetimeDown << endl;
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



	TString canvasTotalSpin = "TotalSpin";
	TString canvasTitleTotalSpin = "HAND - Total Spin";
	TCanvas *totalSpinCanvas = new TCanvas(canvasTotalSpin,canvasTitleTotalSpin,1400,770); //x,y
	totalspinpad01 =  new TPad("totalspinpad01","totalspinpad01",0.0000,0.5000,0.5000,1.0000,0,0,0);
	totalspinpad02 =  new TPad("totalspinpad02","totalspinpad02",0.5000,0.5000,1.0000,1.0000,0,0,0);
	totalspinpad03 =  new TPad("totalspinpad03","totalspinpad03",0.0000,0.0000,1.0000,0.5000,0,0,0);
	totalspinpad01->Draw(); totalspinpad02->Draw(); totalspinpad03->Draw();

	totalspinpad01->cd();
	cout << "HeChargeScaleUp: " << HeChargeScaleUp << "   HelivetimeUp: " << HelivetimeUp << endl;
	HANDTotalSpinUpx->Scale(1/(BeamChargeScaleUp * BeamlivetimeUp));
	HANDTotalSpinUpx->SetTitle("Total Spin Up (Scaled by Charge, LT)");
	HANDTotalSpinUpx->Draw();
	// ********************************************************************************
	// This section below gathers and prints some statistics on the plot
	TString HANDUpFactorsString = "Total Positive Charge for Runs: ";
	HANDUpFactorsString += BeamChargeScaleUp;
	HANDUpFactorsString += " C";
	TString HANDUpFactorsString1 = "Total Positive Livetime for Runs: ";
	HANDUpFactorsString1 += BeamlivetimeUp;
	HANDUpFactors = new TPaveText(0.11,0.69,0.4,0.89,"NDC");
	TText *t1 = HANDUpFactors->AddText(HANDUpFactorsString);
	TText *t2 = HANDUpFactors->AddText(HANDUpFactorsString1);
	HANDUpFactors->Draw("same");
	// ********************************************************************************
	totalspinpad01->Update();

	totalspinpad02->cd();
	cout << "HeChargeScaleDown: " << HeChargeScaleDown << "   HelivetimeDown: " << HelivetimeDown << endl;
	HANDTotalSpinDownx->Scale(1/(BeamChargeScaleDown * BeamlivetimeDown));
	HANDTotalSpinDownx->SetTitle("Total Spin Down (Scaled by Charge, LT)");
	HANDTotalSpinDownx->Draw();
	// ********************************************************************************
	// This section below gathers and prints some statistics on the plot
	TString HANDDownFactorsString = "Total Negative Charge for Runs: ";
	HANDDownFactorsString += BeamChargeScaleDown;
	HANDDownFactorsString += " C";
	TString HANDDownFactorsString1 = "Total Negative Livetime for Runs: ";
	HANDDownFactorsString1 += BeamlivetimeDown;
	HANDDownFactors = new TPaveText(0.11,0.69,0.4,0.89,"NDC");
	TText *t1 = HANDDownFactors->AddText(HANDDownFactorsString);
	TText *t2 = HANDDownFactors->AddText(HANDDownFactorsString1);
	HANDDownFactors->Draw("same");
	// ********************************************************************************
	totalspinpad02->Update();

	totalspinpad03->cd();
        TF1 *fitasym = new TF1("fitasym","[0]",nuMin,nuMax);
	HANDAsym = HANDTotalSpinUpx->GetAsymmetry(HANDTotalSpinDownx);
	TString AsymTitle = "Target Asymmerty with Neutron Cuts vs. xBj for runs ";
	AsymTitle += HeRunNumber;
	AsymTitle += "-";
	AsymTitle += endHeRunNumber;
	HANDAsym->SetTitle(AsymTitle);
	HANDAsym->Draw();
        fitasym->SetLineColor(kBlue);
        HANDAsym->Fit("fitasym","R");
	totalspinpad03->Update();

	TString TotalSpinOutTitle = outputPlotsHere;
	TotalSpinOutTitle += "target_asymmetry_for_Run_Num_";
	TotalSpinOutTitle += HeRunNumber;
	TotalSpinOutTitle += "-";
	TotalSpinOutTitle += endHeRunNumber;
	if (includeVetos) {TotalSpinOutTitle += "_with_vetos";}
	if (includeAntivetos) {TotalSpinOutTitle += "_with_antivetos";}
	if (antivetosAsVetos && includeAntivetos) {TotalSpinOutTitle += "_as_vetos";}
	TotalSpinOutTitle += ".png";
	totalSpinCanvas->Print(TotalSpinOutTitle);


	asymOutFile.close();

	cout << "All done!" << endl;



}







































