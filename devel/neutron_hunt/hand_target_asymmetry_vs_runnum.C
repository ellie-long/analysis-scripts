// ***************************************************
//
// This script will plot the target asymmetry with
// neutron cuts included. It will do this by looking
// at the number of unique spin up(down) events in each
// bar, plotting them, then adding the plots together
// for each bar with a final asymmetry found at the
// end.
//
// 2011-02-07
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

void hand_target_asymmetry_vs_runnum(){

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
	singleplane = 2;
	SinglePlane = false;
//	SingleBar = true;
	singlebar = 10;
	SingleBar = false;
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

	int HeRunNumber = 20579;
	int endHeRunNumber = 20583;
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
	double goodTDCleftcutmin = 1484;
	double goodTDCleftcutmax = 1504;
	double goodTDCrightcutmin = 1486;
	double goodTDCrightcutmax = 1506;
	double vetoTDCcutmin = 1484;
	double vetoTDCcutmax = 1506;

/*
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
	int runBins = (endHeRunNumber - HeRunNumber + 2);
	double runMin = HeRunNumber - 1;
	double runMax = endHeRunNumber + 1;

	double xmin = 0.6;
	double xmax = 3.0;

	int bins = 50;

	TString outputPlotsHere = "/home/ellie/physics/e05-102/images/plots_for_hand/hand_target_asymmetry/";

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
	imageCutsTitle += "HAND_plots_vs_runnum_for_Run_Num_";
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
//	int whichplane = 0;
	int whichplane = 1;
	int endplane = 5;
	if (SinglePlane) {whichplane = singleplane; endplane = singleplane+1;}
	int whichbar=0;
//	int whichbar=11;
	TString titleTotalSpinUpx = "Total Spin Up vs. Run Number";
	if (includeVetos) {titleTotalSpinUpx += " with vetos";}
	else {titleTotalSpinUpx += " without vetos";}
	titleTotalSpinUpx += " with goodTDC cuts";
	cout << "Drawing " << titleTotalSpinUpx << "..." << endl;
	TString plotTotalSpinUpx = "HANDTotalSpinUpx";
	TH1F *HANDTotalSpinUpx = new TH1F(plotTotalSpinUpx,titleTotalSpinUpx,runBins,runMin,runMax);
	TString titleTotalSpinDownx = "Total Spin Down vs. Run Number";
	if (includeVetos) {titleTotalSpinDownx += " with vetos";}
	else {titleTotalSpinDownx += " without vetos";}
	titleTotalSpinDownx += " with goodTDC cuts";
	cout << "Drawing " << titleTotalSpinDownx << "..." << endl;
	TString plotTotalSpinDownx = "HANDTotalSpinDownx";
	TH1F *HANDTotalSpinDownx = new TH1F(plotTotalSpinDownx,titleTotalSpinDownx,runBins,runMin,runMax);

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
			hand_draw(HeRunNumber, endHeRunNumber, antivetosAsVetos, allVetos, goodBar, allAntivetos);
			handpad01->Update();

			TString goodTDCleftcutString = "(NA.nd.p";
			goodTDCleftcutString += nplane;
			if (nplane == 0) {goodTDCleftcutString = "(NA.veto";}
			goodTDCleftcutString += ".lt_c[";
			goodTDCleftcutString += thisbar;
			goodTDCleftcutString += "]>";
			goodTDCleftcutString += goodTDCleftcutmin;
			if (nplane > 0)
			{
				goodTDCleftcutString += " && NA.nd.p";
				goodTDCleftcutString += nplane;
			}
			if (nplane == 0) {goodTDCleftcutString += " && NA.veto";}
			goodTDCleftcutString += ".lt_c[";
			goodTDCleftcutString += thisbar;
			goodTDCleftcutString += "]<";
			goodTDCleftcutString += goodTDCleftcutmax;
			goodTDCleftcutString += ")";
			cout << "goodTDCleftcutString = " << goodTDCleftcutString << endl;
			TCut goodTDCleftcut = goodTDCleftcutString;
	
			TString goodTDCrightcutString = "(NA.nd.p";
			goodTDCrightcutString += nplane;
			if (nplane == 0) {goodTDCrightcutString = "(NA.veto";}
			goodTDCrightcutString += ".rt_c[";
			goodTDCrightcutString += thisbar;
			goodTDCrightcutString += "]>";
			goodTDCrightcutString += goodTDCrightcutmin;
			if (nplane > 0)
			{
				goodTDCrightcutString += " && NA.nd.p";
				goodTDCrightcutString += nplane;
			}
			if (nplane == 0) {goodTDCrightcutString += " && NA.veto";}
			goodTDCrightcutString += ".rt_c[";
			goodTDCrightcutString += thisbar;
			goodTDCrightcutString += "]<";
			goodTDCrightcutString += goodTDCrightcutmax;
			goodTDCrightcutString += ")";
			cout << "goodTDCrightcutString = " << goodTDCrightcutString << endl;
			TCut goodTDCrightcut = goodTDCrightcutString;
		
			TString firstTrackString = "NA.tr.firstplane==";
			firstTrackString += (nplane - 1);
			firstTrackString += " && NA.tr.firstpad==";
			firstTrackString += thisbar;
			TCut firstTrack = firstTrackString;

	
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
			HANDleft->SetMinimum(0);
			TH1F *HANDleftcut = new TH1F(plotHANDleftcut,titleHANDleft,TDCbins,TDCmin,TDCmax);
			HANDleftcut->SetMinimum(0);
			TString HANDleftTDC = goodTDCl;
			HANDleftTDC += ">>";
			HANDleftTDC += plotHANDleft;
			TString HANDleftTDCcut = goodTDCl;
			HANDleftTDCcut += ">>";
			HANDleftTDCcut += plotHANDleftcut;
			chainHe->Draw(HANDleftTDC, cuts && vetoTDCs,"");
//			chainHe->Draw(HANDleftTDC, vetoTDCs,"");
//			HANDleft->Scale(1/(HeChargeScale*Helivetime));
			HANDleft->Draw();
			chainHe->Draw(HANDleftTDCcut, cuts && vetoTDCs && goodTDCleftcut && firstTrack,"same");
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
			chainHe->Draw(HANDrightTDC, cuts && vetoTDCs,"");
//			HANDright->Scale(1/(HeChargeScale*Helivetime));
			HANDright->Draw();
			chainHe->Draw(HANDrightTDCcut, cuts && vetoTDCs && goodTDCrightcut && firstTrack,"same");
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

			handpad04->cd();
			cout << "Drawing Spin Up vs. Run Number..." << endl;
			TString titleSpinUpx = "Spin Up vs. Run Number for Plane #";
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
			TH1F *HANDSpinUpx = new TH1F(plotSpinUpx,titleSpinUpxcut,runBins,runMin,runMax);
			TString HANDSpinUpxString = "g.runnum";
			HANDSpinUpxString += ">>";
			HANDSpinUpxString += plotSpinUpx;
			chainHe->Draw(HANDSpinUpxString, cuts && goodTDCcut && firstTrack && "he3R.Spin==1","");
			HANDSpinUpx->SetMinimum(0);
			HANDSpinUpx->Draw();
			handpad04->Update();

			handpad05->cd();
			cout << "Drawing Spin Down vs. Run Number..." << endl;
			TString titleSpinDownx = "Spin Down vs. Run Number for Plane #";
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
			TH1F *HANDSpinDownx = new TH1F(plotSpinDownx,titleSpinDownxcut,runBins,runMin,runMax);
			TString HANDSpinDownxString = "g.runnum";
			HANDSpinDownxString += ">>";
			HANDSpinDownxString += plotSpinDownx;
			chainHe->Draw(HANDSpinDownxString, cuts && goodTDCcut && firstTrack && "he3R.Spin==-1","");
			HANDSpinDownx->SetMinimum(0);
			HANDSpinDownx->Draw();
			handpad05->Update();

			handpad06->cd();
			cout << "Drawing Total Spin Up vs. Run Number..." << endl;
//			TString titleTotalSpinUpx = "Total Spin Up vs. Run Number";
//			if (includeVetos) {titleTotalSpinUpx += " with vetos";}
//			else {titleTotalSpinUpx += " without vetos";}
//			titleTotalSpinUpx += " with goodTDC cuts";
//			cout << "Drawing " << titleTotalSpinUpx << "..." << endl;
//			TString plotTotalSpinUpx = "HANDTotalSpinUpx";
//			TH1F *HANDTotalSpinUpx = new TH1F(plotTotalSpinUpx,titleTotalSpinUpx,runBins,runMin,runMax);
			HANDTotalSpinUpx->Add(HANDSpinUpx);
			HANDTotalSpinUpx->SetMinimum(0);
			HANDTotalSpinUpx->Draw();
			handpad06->Update();

			handpad07->cd();
			cout << "Drawing Total Spin Down vs. Run Number..." << endl;
//			TString titleTotalSpinDownx = "Total Spin Down vs. Run Number";
//			if (includeVetos) {titleTotalSpinDownx += " with vetos";}
//			else {titleTotalSpinDownx += " without vetos";}
//			titleTotalSpinDownx += " with goodTDC cuts";
//			cout << "Drawing " << titleTotalSpinDownx << "..." << endl;
//			TString plotTotalSpinDownx = "HANDTotalSpinDownx";
//			TH1F *HANDTotalSpinDownx = new TH1F(plotTotalSpinDownx,titleTotalSpinDownx,runBins,runMin,runMax);
			HANDTotalSpinDownx->Add(HANDSpinDownx);
			HANDTotalSpinDownx->SetMinimum(0);
			HANDTotalSpinDownx->Draw();
			handpad07->Update();




			TString imageTitle = outputPlotsHere;
			imageTitle += "plots_vs_runnum_for_Run_Num_";
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

//			if (includeVetos) {hand_draw_vetos(veto1plane, veto2plane, veto3plane, veto4plane, veto5plane, veto6plane,veto1bar, veto2bar, veto3bar, veto4bar, veto5bar, veto6bar, imageVetosWithoutVetosTitle, imageVetosWithVetosTitle, HeRunNumber, endHeRunNumber, chainHe, nplane, thisbar, TDCbins, TDCmin, TDCmax, cuts, vetoTDCs, antivetosAsVetos, allVetos, allAntivetos);}

/*		if ((nplane==1) && (thisbar==15)) { nplane = 2; thisbar = 7;}
		if ((nplane==2) && (thisbar==12)) { nplane = 3; thisbar = 6;}
		if ((nplane==3) && (thisbar==11)) { nplane = 4; thisbar = 3;}
		if ((nplane==4) && (thisbar==7))  { nplane = 4; thisbar = 99;}
*/

		}
	}
	TString canvasTotalSpin = "TotalSpin";
	TString canvasTitleTotalSpin = "HAND - Total Spin";
	TCanvas *totalSpinCanvas = new TCanvas(canvasTotalSpin,canvasTitleTotalSpin,1400,770); //x,y
	totalspinpad01 =  new TPad("totalspinpad01","totalspinpad01",0.0000,0.5000,0.5000,1.0000,0,0,0);
	totalspinpad02 =  new TPad("totalspinpad02","totalspinpad02",0.5000,0.5000,1.0000,1.0000,0,0,0);
	totalspinpad03 =  new TPad("totalspinpad03","totalspinpad03",0.0000,0.0000,1.0000,0.5000,0,0,0);
	totalspinpad01->Draw(); totalspinpad02->Draw(); totalspinpad03->Draw();

	totalspinpad01->cd();
	HANDTotalSpinUpx->Scale(1/(HeChargeScaleUp * HelivetimeUp));
	HANDTotalSpinUpx->SetMinimum(0);
	HANDTotalSpinUpx->SetTitle("Total Spin Up (Scaled by Charge, LT)");
	HANDTotalSpinUpx->Draw();
	totalspinpad01->Update();

	totalspinpad02->cd();
	HANDTotalSpinDownx->Scale(1/(HeChargeScaleDown * HelivetimeDown));
	HANDTotalSpinDownx->SetMinimum(0);
	HANDTotalSpinDownx->SetTitle("Total Spin Down (Scaled by Charge, LT)");
	HANDTotalSpinDownx->Draw();
	totalspinpad02->Update();

	totalspinpad03->cd();
        TF1 *fitasym = new TF1("fitasym","[0]",runMin,runMax);
	HANDAsym = HANDTotalSpinUpx->GetAsymmetry(HANDTotalSpinDownx);
	TString AsymTitle = "Target Asymmerty with Neutron Cuts vs. Run Number for runs ";
	AsymTitle += HeRunNumber;
	AsymTitle += "-";
	AsymTitle += endHeRunNumber;
	HANDAsym->SetTitle(AsymTitle);
	HANDAsym->Draw();
        fitasym->SetLineColor(kBlue);
        HANDAsym->Fit("fitasym","R");
	totalspinpad03->Update();

	TString TotalSpinOutTitle = outputPlotsHere;
	TotalSpinOutTitle += "target_asymmetry_vs_runnum_for_Run_Num_";
	TotalSpinOutTitle += HeRunNumber;
	TotalSpinOutTitle += "-";
	TotalSpinOutTitle += endHeRunNumber;
	if (includeVetos) {TotalSpinOutTitle += "_with_vetos";}
	if (includeAntivetos) {TotalSpinOutTitle += "_with_antivetos";}
	if (antivetosAsVetos && includeAntivetos) {TotalSpinOutTitle += "_as_vetos";}
	TotalSpinOutTitle += ".png";
	totalSpinCanvas->Print(TotalSpinOutTitle);

	cout << "All done!" << endl;



}







































