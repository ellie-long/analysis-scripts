// ***************************************************
//
// This script is a test to make sure that I understand
// what is happening when I take the Left TDC and subtract
// the Right TDC from it and how both of these work
// when the veto bars are defined.
//
// 2010-12-08
// Elena Long
//
// ***************************************************

#include <iostream>
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

// Search for HAND to get to the PMT definitions

void left_right_position_test2(){

	bool includeVetos;
// 	If includeVetos = false, then only good bars will be displayed. If 
//	includeVetos = true, then veto bars will be shown along with the good bars.
//	includeVetos = true;
	includeVetos = false;

	bool includeAntivetos;
// 	If includeAntivetos = false, then only good bars will be displayed. If 
//	includeAntivetos = true, then antiveto bars will be shown along with the good bars.
	includeAntivetos = true;
//	includeAntivetos = false;

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
	SinglePlane = true;
	singleplane = 2;
//	SinglePlane = false;
	SingleBar = true;
	singlebar = 10;
//	SingleBar = false;
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
	double goodTDCleftcutmin = 752;
	double goodTDCleftcutmax = 775;
	double goodTDCrightcutmin = 752;
	double goodTDCrightcutmax = 775;
	double vetoTDCcutmin = 750;
	double vetoTDCcutmax = 785;
*/
/*
	int HeRunNumber = 20791;
	int endHeRunNumber = 20792;
	TString Q2 = "1.0";
	double q2min = 0.75;
	double q2max = 1.2;
	double numin = 0.3;
	double numax = 0.7;
	int Positionbins = 30;
	double Positionmin = -30;
	double Positionmax = 30;
	int TDCbins = 100;
	double TDCmin = 1300;
	double TDCmax = 1500;
	double goodTDCleftcutmin = 1385;
	double goodTDCleftcutmax = 1415;
	double goodTDCrightcutmin = 1385;
	double goodTDCrightcutmax = 1415;
	double vetoTDCcutmin = 1385;
	double vetoTDCcutmax = 1415;
*/

	int HeRunNumber = 21383;
	int endHeRunNumber = 21383;
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
	double goodTDCleftcutmin = 730;
	double goodTDCleftcutmax = 770;
	double goodTDCrightcutmin = 740;
	double goodTDCrightcutmax = 780;
	double vetoTDCcutmin = 730;
	double vetoTDCcutmax = 770;

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
	double goodTDCleftcutmin = 730;
	double goodTDCleftcutmax = 770;
	double goodTDCrightcutmin = 740;
	double goodTDCrightcutmax = 780;
	double vetoTDCcutmin = 730;
	double vetoTDCcutmax = 770;
*/
	int ADCbins = 200;
	double ADCmin = 1;
	double ADCmax = 3100;
	double xmin = 0.6;
	double xmax = 3.0;

	int bins = 50;

	TString outputPlotsHere = "/home/ellie/physics/e05-102/images/plots_for_hand/left_right_position_test2/";

	// Although declared here, the goodTDCcut is actually made down below where  it can be included
	// in the loop so that it is easy to have it change for each good bar when done one at a time.
	// However, the left and right min and max TDC values are defined here
	TCut goodTDCcut = "";

	TChain* chainHe = new TChain("T");
	TString filenameHe;

	for (int thisHeRunNumber=HeRunNumber; thisHeRunNumber<(endHeRunNumber+1); thisHeRunNumber++)
	{
/*		// Skipping Vertical Carbon Runs
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

		// Skipping Longitudinal Carbon Runs
		if(thisHeRunNumber==22380){thisHeRunNumber=22393;}
		if(thisHeRunNumber==22389){thisHeRunNumber=22393;}
		if(thisHeRunNumber==22425){thisHeRunNumber=22436;}
		if(thisHeRunNumber==22426){thisHeRunNumber=22436;}

		// Skipping Transverse Carbon Runs
		if(thisHeRunNumber==22461){thisHeRunNumber=22465;}
*/

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
	double HeChargeScale = 0; double Helivetime = 0;
	double HeChargeScaleUp = 0; double HelivetimeUp = 0;
	double HeChargeScaleDown = 0; double HelivetimeDown = 0;
	hand_scaling_factors(HeRunNumber, endHeRunNumber, HeChargeScale, Helivetime, HeChargeScaleUp, HelivetimeUp, HeChargeScaleDown, HelivetimeDown);
	HeChargeScale = 0.00001 * int(HeChargeScale * 100000.0 + 0.5);
	HeChargeScaleUp = 0.00001 * int(HeChargeScaleUp * 100000.0 + 0.5);
	HeChargeScaleDown = 0.00001 * int(HeChargeScaleDown * 100000.0 + 0.5);
	Helivetime = 0.0001 * int(Helivetime * 10000.0 + 0.5);
	HelivetimeUp = 0.0001 * int(HelivetimeUp * 10000.0 + 0.5);
	HelivetimeDown = 0.0001 * int(HelivetimeDown * 10000.0 + 0.5);
	cout << "HeChargeScale: " << HeChargeScale << "C, Helivetime: " << Helivetime << endl;
	cout << "HeChargeScaleUp: " << HeChargeScaleUp << "C, HelivetimeUp: " << HelivetimeUp << endl;
	cout << "HeChargeScaleDown: " << HeChargeScaleDown << "C, HelivetimeDown: " << HelivetimeDown << endl;
// **********************************************************************************************

// The section below plots the HAND data
// **********************************************************************************************
	int whichplane = 0;
	int endplane = 5;
	if (SinglePlane) {whichplane = singleplane; endplane = singleplane+1;}
	int whichbar=0;
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
			handpad02 =  new TPad("handpad02","handpad02",0.1000,0.5000,0.5500,1.0000,0,0,0);
			handpad03 =  new TPad("handpad03","handpad03",0.5500,0.5000,1.0000,1.0000,0,0,0);
			handpad04 =  new TPad("handpad04","handpad04",0.1000,0.0000,1.0000,0.5000,0,0,0);
			handpad01->Draw(); handpad02->Draw(); handpad03->Draw(); handpad04->Draw();

			// This section will run hand_draw.h which will draw the HAND in handpad01.
			handpad01->cd();
			hand_draw(HeRunNumber, endHeRunNumber, antivetosAsVetos, allVetos, goodBar, allAntivetos);
			handpad01->Update();

			TString goodTDCleftcutString = "(NA.nd.p";
			goodTDCleftcutString += nplane;
			goodTDCleftcutString += ".lt_c[";
			goodTDCleftcutString += thisbar;
			goodTDCleftcutString += "]>";
			goodTDCleftcutString += goodTDCleftcutmin;
			goodTDCleftcutString += " && NA.nd.p";
			goodTDCleftcutString += nplane;
			goodTDCleftcutString += ".lt_c[";
			goodTDCleftcutString += thisbar;
			goodTDCleftcutString += "]<";
			goodTDCleftcutString += goodTDCleftcutmax;
			goodTDCleftcutString += ")";
			cout << "goodTDCleftcutString = " << goodTDCleftcutString << endl;
			TCut goodTDCleftcut = goodTDCleftcutString;
	
			TString goodTDCrightcutString = "(NA.nd.p";
			goodTDCrightcutString += nplane;
			goodTDCrightcutString += ".rt_c[";
			goodTDCrightcutString += thisbar;
			goodTDCrightcutString += "]>";
			goodTDCrightcutString += goodTDCrightcutmin;
			goodTDCrightcutString += " && NA.nd.p";
			goodTDCrightcutString += nplane;
			goodTDCrightcutString += ".rt_c[";
			goodTDCrightcutString += thisbar;
			goodTDCrightcutString += "]<";
			goodTDCrightcutString += goodTDCrightcutmax;
			goodTDCrightcutString += ")";
			cout << "goodTDCrightcutString = " << goodTDCrightcutString << endl;
			TCut goodTDCrightcut = goodTDCrightcutString;
			
			goodTDCcut = (goodTDCleftcut || goodTDCrightcut);

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
cout << "1" << endl;
			TH1F *HANDleftcut = new TH1F(plotHANDleftcut,titleHANDleft,TDCbins,TDCmin,TDCmax);
cout << "2" << endl;
			TString HANDleftTDC = goodTDCl;
			HANDleftTDC += ">>";
			HANDleftTDC += plotHANDleft;
cout << "3" << endl;
			TString HANDleftTDCcut = goodTDCl;
			HANDleftTDCcut += ">>";
			HANDleftTDCcut += plotHANDleftcut;
cout << "4" << endl;
			chainHe->Draw(HANDleftTDC, cuts && vetoTDCs,"");
//			chainHe->Draw(HANDleftTDC, vetoTDCs,"");
cout << "5" << endl;
//			HANDleft->Scale(1/(HeChargeScale*Helivetime));
			HANDleft->Draw();
cout << "6" << endl;
			chainHe->Draw(HANDleftTDCcut, cuts && vetoTDCs && goodTDCleftcut,"same");
//			chainHe->Draw(HANDleftTDCcut, vetoTDCs && goodTDCleftcut,"same");
cout << "7" << endl;
			HANDleftcut->SetFillColor(kViolet);
//			HANDleftcut->Scale(1/(HeChargeScale*Helivetime));
cout << "8" << endl;
			HANDleftcut->Draw("same");
			// ********************************************************************************
			// This section below gathers and prints some statistics on the plot
			double numHANDleftcutEvents = 0;
			for (int i; i<TDCbins; i++){ numHANDleftcutEvents = numHANDleftcutEvents + HANDleftcut->GetBinContent(i);}
			TString HANDleftFactorsString = "Total Charge for Runs: ";
			HANDleftFactorsString += HeChargeScale;
			HANDleftFactorsString += " C";
			TString HANDleftFactorsString1 = "Total Livetime for Runs: ";
			HANDleftFactorsString1 += Helivetime;
			TString HANDleftFactorsString2 = "# of Cut (Purple) Events: ";
			HANDleftFactorsString2 += numHANDleftcutEvents;
			HANDleftFactors = new TPaveText(0.11,0.79,0.4,0.89,"NDC");
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
			TH1F *HANDrightcut = new TH1F(plotHANDrightcut,titleHANDright,TDCbins,TDCmin,TDCmax);
			TString HANDrightTDC = goodTDCr;
			HANDrightTDC += ">>";
			HANDrightTDC += plotHANDright;
			TString HANDrightTDCcut = goodTDCr;
			HANDrightTDCcut += ">>";
			HANDrightTDCcut += plotHANDrightcut;
			chainHe->Draw(HANDrightTDC, cuts && vetoTDCs,"");
//			HANDright->Scale(1/(HeChargeScale*Helivetime));
			HANDright->Draw();
			chainHe->Draw(HANDrightTDCcut, cuts && vetoTDCs && goodTDCrightcut,"same");
			HANDrightcut->SetFillColor(kViolet);
//			HANDrightcut->Scale(1/(HeChargeScale*Helivetime));
			HANDrightcut->Draw("same");
			// ********************************************************************************
			// This section below gathers and prints some statistics on the plot
			double numHANDrightcutEvents = 0;
			for (int j; j<TDCbins; j++){ numHANDrightcutEvents = numHANDrightcutEvents + HANDrightcut->GetBinContent(j);}
			TString HANDrightFactorsString = "Total Charge for Runs: ";
			HANDrightFactorsString += HeChargeScale;
			HANDrightFactorsString += " C";
			TString HANDrightFactorsString1 = "Total Livetime for Runs: ";
			HANDrightFactorsString1 += Helivetime;
			TString HANDrightFactorsString2 = "# of Cut (Purple) Events: ";
			HANDrightFactorsString2 += numHANDrightcutEvents;
			HANDrightFactors = new TPaveText(0.11,0.79,0.4,0.89,"NDC");
			TText *t1 = HANDrightFactors->AddText(HANDrightFactorsString);
			TText *t2 = HANDrightFactors->AddText(HANDrightFactorsString1);
			TText *t2 = HANDrightFactors->AddText(HANDrightFactorsString2);
			HANDrightFactors->Draw("same");
			// ********************************************************************************
			handpad03->Update();


			handpad04->cd();
			TString titlePosition = "Left TDC - Right TDC for Plane #";
			titlePosition += nplane;
			titlePosition += ", Bar # ";
			titlePosition += thisbar;
			if (includeVetos) titlePosition += " with vetos";
			else titlePosition += " without vetos";
			cout << "Drawing " << titlePosition << "..." << endl;
			TString plotPosition = "Position_p";
			plotPosition += nplane;
cout << "1" << endl;
			TString plotPositioncut = plotPosition;
			plotPositioncut += "_cut";
cout << "2" << endl;
			TH1F *histPosition = new TH1F(plotPosition, titlePosition, Positionbins, Positionmin, Positionmax);
cout << "3" << endl;
			TH1F *histPositioncut = new TH1F(plotPositioncut, titlePosition, Positionbins, Positionmin, Positionmax);
//			cout << "For plane " << nplane << ", bar " << thisbar << ", the veto cut was " << vetoTDCslSt << " and " << vetoTDCsrSt << endl;
			TString thisplaneandbar = "NA.n.plane==";
			thisplaneandbar += nplane-1;
			thisplaneandbar += " && NA.n.pad==";
			thisplaneandbar += thisbar;
cout << "4" << endl;
			TCut thisplaneandbarcut = thisplaneandbar;
cout << "5" << endl;
			TString Positionplots = "(";
			Positionplots += goodTDCl;
			Positionplots += " - ";
			Positionplots += goodTDCr;
			Positionplots += ")>>";
			Positionplots += plotPosition;
cout << "6" << endl;
			TString Positionplotscut = Positionplots;
			Positionplotscut += "_cut";
cout << "7" << endl;
//			chainHe->Draw(Positionplots, cuts && thisplaneandbarcut && vetoTDCs, "");
			chainHe->Draw(Positionplots, thisplaneandbarcut && vetoTDCs, "");
cout << "8" << endl;
			histPosition->Draw();
//			histPosition->Scale(1/(HeChargeScale*Helivetime));
cout << "9" << endl;
			chainHe->Draw(Positionplotscut, cuts && thisplaneandbarcut && vetoTDCs && goodTDCcut, "same");
cout << "10" << endl;
			histPositioncut->SetFillColor(kViolet);
cout << "11" << endl;
//			histPositioncut->Scale(1/(HeChargeScale*Helivetime));
			histPositioncut->Draw("same");
cout << "12" << endl;
			handpad04->Update();

			TString imageTitle = outputPlotsHere;
			imageTitle += "TDC_plots_Run_Num_";
			imageTitle += HeRunNumber;
			imageTitle += "-";
			imageTitle += endHeRunNumber;
			imageTitle += "_p";
			imageTitle += nplane;
			imageTitle += "_b";
			imageTitle += thisbar;
			if (includeVetos) {imageTitle += "_with_vetos";}
			if (includeAntivetos) {imageTitle += "_with_antivetos";}
			if (antivetosAsVetos && includeAntivetos) {imageTitle += "_as_vetos";}
			imageTitle+= ".png";
			handCanvas->Print(imageTitle);

			TString imageAntivetosTitle = outputPlotsHere;
			imageAntivetosTitle += "antivetos_for_Run_Num_";
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
			imageVetosWithoutVetosTitle += "vetos_without_veto_cut_for_Run_Num_";
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
			imageVetosWithVetosTitle += "vetos_with_veto_cut_for_Run_Num_";
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

			if (includeVetos) {hand_draw_vetos(veto1plane, veto2plane, veto3plane, veto4plane, veto5plane, veto6plane,veto1bar, veto2bar, veto3bar, veto4bar, veto5bar, veto6bar, imageVetosWithoutVetosTitle, imageVetosWithVetosTitle, HeRunNumber, endHeRunNumber, chainHe, nplane, thisbar, TDCbins, TDCmin, TDCmax, cuts, vetoTDCs, antivetosAsVetos, allVetos, allAntivetos);}


// The section below plots various kinematics using the veto cuts and any good TDC cuts
// to try and figure out where different sections of data are coming from 
// **********************************************************************************************
			// Defines Canvas
			TCanvas *kinematicsCanvas = new TCanvas("kinematicsCanvas","Kinematics from Veto & TDC cuts",1360,768); //x,y
			kinematicspad1  =  new  TPad("kinematicspad1","kinematicspad1",0.0000,0.5000,0.2500,1.0000,0,0,0);
			kinematicspad2  =  new  TPad("kinematicspad2","kinematicspad2",0.2500,0.5000,0.5000,1.0000,0,0,0);
			kinematicspad3  =  new  TPad("kinematicspad3","kinematicspad3",0.5000,0.5000,0.7500,1.0000,0,0,0);
			kinematicspad4  =  new  TPad("kinematicspad4","kinematicspad4",0.7500,0.5000,1.0000,1.0000,0,0,0);
			kinematicspad5  =  new  TPad("kinematicspad5","kinematicspad5",0.0000,0.0000,0.2500,0.5000,0,0,0);
			kinematicspad6  =  new  TPad("kinematicspad6","kinematicspad6",0.2500,0.0000,0.5000,0.5000,0,0,0);
			kinematicspad7  =  new  TPad("kinematicspad7","kinematicspad7",0.5000,0.0000,0.7500,0.5000,0,0,0);
			kinematicspad8  =  new  TPad("kinematicspad8","kinematicspad8",0.7500,0.0000,1.0000,0.5000,0,0,0);
			kinematicspad1->Draw();kinematicspad2->Draw();kinematicspad3->Draw();kinematicspad4->Draw();kinematicspad5->Draw();kinematicspad6->Draw();kinematicspad7->Draw();kinematicspad8->Draw();
			
			// Everything below here makes graphs for each section of the canvas

			kinematicspad1->cd();
			kinematicspad1->SetLogy();
			TString kinematicstitledp = "dp kinematics - Runs ";
			kinematicstitledp += HeRunNumber;
			kinematicstitledp += " - ";
			kinematicstitledp += endHeRunNumber;
			cout << "Drawing " << kinematicstitledp << "..." << endl;
			TH1F *HedpNokinematics = new TH1F("HedpNokinematics",kinematicstitledp,400,-0.08,0.08);
			TH1F *Hedpkinematics = new TH1F("Hedpkinematics",kinematicstitledp,400,-0.08,0.08);
			chainHe->Draw("ExTgtCor_R.dp>>HedpNokinematics", "", "");
			chainHe->Draw("ExTgtCor_R.dp>>Hedpkinematics", cuts && goodTDCcut && vetoTDCs, "");
			HedpNokinematics->SetTitle(kinematicstitledp);
			HedpNokinematics->Draw();
			Hedpkinematics->SetLineColor(kBlack);
			Hedpkinematics->SetFillColor(kViolet);
			Hedpkinematics->Draw("same");
			kinematicspad1->Update();

			kinematicspad2->cd();
			kinematicspad2->SetLogy();
			cout << "Drawing Target kinematics..." << endl;
			TString kinematicstitleTarget = "Target kinematics";
			TH1F *HeReactZNokinematics = new TH1F("HeReactZNokinematics",kinematicstitleTarget,400,-0.3,0.3);
			TH1F *HeReactZkinematics = new TH1F("HeReactZkinematics",kinematicstitleTarget,400,-0.3,0.3);
			chainHe->Draw("ReactPt_R.z>>HeReactZNokinematics", "", "");
			chainHe->Draw("ReactPt_R.z>>HeReactZkinematics", cuts && goodTDCcut && vetoTDCs, "");
			HeReactZNokinematics->SetTitle(kinematicstitleTarget);
			HeReactZNokinematics->Draw();
			HeReactZkinematics->SetLineColor(kBlack);
			HeReactZkinematics->SetFillColor(kViolet);
			HeReactZkinematics->Draw("same");
			kinematicspad2->Update();

			kinematicspad3->cd();
			cout << "Drawing Theta and Phi kinematics..." << endl;
			TString kinematicstitleThetaPhiNokinematics = "Theta and Phi";
			TH2F *HeThetaPhiNokinematics = new TH2F("HeThetaPhiNokinematics",kinematicstitleThetaPhiNokinematics,100,-0.05,0.05,100,-0.1,0.1);
			chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeThetaPhiNokinematics", cuts && goodTDCcut && vetoTDCs, "");
			HeThetaPhiNokinematics->SetTitle(kinematicstitleThetaPhiNokinematics);
			HeThetaPhiNokinematics->SetStats(kFALSE);
			HeThetaPhiNokinematics->Draw("COLZ");
//			bottom->Draw("same");
//			top->Draw("same");
//			left->Draw("same");
//			right->Draw("same");
			kinematicspad3->Update();

			kinematicspad7->cd();
			cout << "Drawing Preshower/Shower kinematics..." << endl;
			TString kinematicstitlePsSh = "Preshower and Shower";
			TH2F *HePsShkinematics = new TH2F("HePsShkinematics",kinematicstitlePsSh,200,1,2500,200,1,1500);
			chainHe->Draw("R.ps.e:R.sh.e>>HePsShkinematics", "", "");
		//	chainHe->Draw("R.ps.e:R.sh.e>>HePsShkinematics", cutsR && cerenkov, "");
			HePsShkinematics->SetTitle(kinematicstitlePsSh);
			HePsShkinematics->SetStats(kFALSE);
			HePsShkinematics->Draw("COLZ");
//			psshcut->Draw("same");
			kinematicspad7->Update();

			kinematicspad4->cd();
			TString kinematicstitleQ2Nu = "Q2 and Nu";
			TH2F *histQ2Nukinematics = new TH2F("histQ2Nukinematics",kinematicstitleQ2Nu,200,numin,numax,200,q2min,q2max);
			cout << "Drawing " << kinematicstitleQ2Nu << "..." << endl;
			chainHe->Draw("PriKineR.Q2:PriKineR.nu>>histQ2Nukinematics", cuts && goodTDCcut && vetoTDCs, "");
			histQ2Nukinematics->SetTitle(kinematicstitleQ2Nu);
		//	histQ2Nukinematics->SetStats(kFALSE);
			histQ2Nukinematics->Draw("COLZ");
			kinematicspad4->Update();

			kinematicspad5->cd();
			kinematicspad5->SetLogy();
			TString kinematicstitlecerenkov = "Cerenkov kinematics";
			cout << "Drawing " << kinematicstitlecerenkov << "..." << endl;
			TH1F *histcerenkovnokinematics = new TH1F("histcerenkovnokinematics",kinematicstitlecerenkov,200,-25,2000);
			TH1F *histcerenkovkinematics = new TH1F("histcerenkovkinematics",kinematicstitlecerenkov,200,-25,2000);
			chainHe->Draw("R.cer.asum_c>>histcerenkovnokinematics", "", "");
			chainHe->Draw("R.cer.asum_c>>histcerenkovkinematics", cuts && goodTDCcut && vetoTDCs, "");
			histcerenkovnokinematics->SetTitle(kinematicstitlecerenkov);
			histcerenkovnokinematics->SetStats(kFALSE);
			histcerenkovkinematics->SetFillColor(kViolet);
			histcerenkovnokinematics->Draw();
			histcerenkovkinematics->Draw("same");
			kinematicspad5->Update();

			kinematicspad8->cd();
			cout << "Drawing Preshower/Shower with All kinematics..." << endl;
			TString kinematicstitlePsSh = "Preshower and Shower with all cuts";
			TH2F *HePsShkinematics = new TH2F("HePsShkinematics",kinematicstitlePsSh,200,1,2500,200,1,1500);
		//	chainHe->Draw("R.ps.e:R.sh.e>>HePsShkinematics", "", "");
			chainHe->Draw("R.ps.e:R.sh.e>>HePsShkinematics", cuts && goodTDCcut && vetoTDCs, "");
			HePsShkinematics->SetTitle(kinematicstitlePsSh);
			HePsShkinematics->SetStats(kFALSE);
			HePsShkinematics->Draw("COLZ");
//			psshcut->Draw("same");
			kinematicspad8->Update();

			kinematicspad6->cd();
			kinematicspad6->SetLogy();
			TString kinematicstitlex = "Bjorken x ";
			kinematicstitlex += " (x=Q^2/[2m*nu])";
			cout << "Drawing " << kinematicstitlex << "..." << endl;
			TH1F *histxnokinematics = new TH1F("histxnokinematics",kinematicstitlex,bins,xmin,xmax);
			TH1F *histxkinematics = new TH1F("histxkinematics",kinematicstitlex,bins,xmin,xmax);
			histxnokinematics->Sumw2();
			chainHe->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histxnokinematics", cut && kinematics && eventtype && dp && target && thph && tracks && cerenkov && pssh, "E");
			chainHe->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histxkinematics", cuts && goodTDCcut && vetoTDCs, "E");
			histxnokinematics->Draw();
			histxkinematics->SetFillColor(kViolet);
			histxkinematics->Draw("same");
			kinematicspad6->Update();


			TString imageKinematicsTitle = outputPlotsHere;
			imageKinematicsTitle += "kinematics_for_Run_Num_";
			imageKinematicsTitle += HeRunNumber;
			imageKinematicsTitle += "-";
			imageKinematicsTitle += endHeRunNumber;
			imageKinematicsTitle += "_p";
			imageKinematicsTitle += nplane;
			imageKinematicsTitle += "_b";
			imageKinematicsTitle += thisbar;
			if (includeVetos) {imageKinematicsTitle += "_with_vetos";}
			if (includeAntivetos) {imageKinematicsTitle += "_with_antivetos";}
			if (antivetosAsVetos && includeAntivetos) {imageKinematicsTitle += "_as_vetos";}
			imageKinematicsTitle+= ".png";
			kinematicsCanvas->Print(imageKinematicsTitle);




		}
	}



	cout << "All done!" << endl;



}







































