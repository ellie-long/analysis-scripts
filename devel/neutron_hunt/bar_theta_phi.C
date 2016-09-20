// ***************************************************
//
// Based off of tdc_calibration.C, this script should
// plot each bar with a correlation plot between
// the bar's Left TDC (y axis) and Right TDC (x axis).
// If all goes according to plan, each plot should
// make a nice tight line.
//
// 11/17/10
// Updated 9/20/2016
// Elena Long
//
// ***************************************************

#include <iostream>
#include <string>
#include <string.h>
#include "hand_define_vetos.h"
#include "hand_draw.h"

// Search for HAND to get to the PMT definitions

void bar_theta_phi(){

	bool includeVetos;
// 	If includeVetos = false, then only good bars will be displayed. If 
//	includeVetos = true, then veto bars will be shown along with the good bars.
	includeVetos = true;
//	includeVetos = false;

	bool includeAntiVetos;
// 	If includeAntiVetos = false, then only good bars will be displayed. If 
//	includeAntiVetos = true, then antiveto bars will be shown along with the good bars.
//	includeAntiVetos = true;
	includeAntiVetos = false;

	bool antivetosAsVetos;
//	If antivetosAsVetos = false, then the antivetos will not be included in the veto cut
//	If antivetosAsVetos = true, then the antivetos will be included in the veto cut
//	Discusses elsewhere, antivetos are the bars immediately following a goodBar
//	antivetosAsVetos = true;
	antivetosAsVetos = false;


	gROOT->ProcessLine(".L hand_draw.C");

	TString Q2 = "1.0";

	int HeRunNumber = 20404;
	int endHeRunNumber = 20407;

//	int HeRunNumber = 21383;
//	int endHeRunNumber = 21387;

//	int HeRunNumber = 20791;
//	int endHeRunNumber = 20792;

	double vetoTDCcutmin = 1385;
	double vetoTDCcutmax = 1415;
	int HANDbins = 60;
	double HANDmin = -30;
	double HANDmax = 30;
	int TDCcutmin = -30;
	int TDCcutmax = 30;
/*	int HeRunNumber = 22441;
	int endHeRunNumber = 22441;
	double vetoTDCcutmin = 750;
	double vetoTDCcutmax = 850;
	int HANDbins = 1500;
	double HANDmax = 1500;
*/
	
//	When using Asymmetries, these define the size of asym plots
	int bins = 50;
	double xmin = 0.6;
	double xmax = 1.6;

	TCut cut = "";
	TCut kinematics = "PriKineR.Q2<10 && GoodElectron==1 && PriKineR.nu<10";
//	TCut eventtype = "(D.evtypebits&2)==2";
	TCut eventtype = "";
	TCut dp = "ExTgtCor_R.dp>-0.04 && ExTgtCor_R.dp<0.053";
	TCut target = "ReactPt_R.z>-0.15 && ReactPt_R.z<0.17";
	TCut thph = "abs(ExTgtCor_R.ph)<0.03 && abs(ExTgtCor_R.th)<0.07";
	TCut tracks = "R.tr.n==1 && R.vdc.u1.nhit>3 && R.vdc.u1.nhit<7 && R.vdc.u2.nhit>3 && R.vdc.u2.nhit<7 && R.vdc.v1.nhit>3 && R.vdc.v1.nhit<7 && R.vdc.v2.nhit>3 && R.vdc.v2.nhit<7";
	TCut basic = kinematics && eventtype && tracks;
	TCut cuts = cut && kinematics && eventtype && dp && target && thph && tracks;

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
/*

// The section below plots the basic cuts used throughout the HAND plots
// **********************************************************************************************
	TCanvas *cutscanvas = new TCanvas("cutscanvas","Basic Cuts",1000,400); //x,y
	cutpad01 =  new TPad("cutpad01","cutpad01",0.0000,0.5000,0.3333,1.0000,0,0,0);
	cutpad02 =  new TPad("cutpad02","cutpad02",0.3333,0.5000,0.6666,1.0000,0,0,0);
	cutpad04 =  new TPad("cutpad04","cutpad04",0.3333,0.0000,0.6666,0.5000,0,0,0);
	cutpad05 =  new TPad("cutpad05","cutpad05",0.6666,0.5000,1.0000,1.0000,0,0,0);
	cutpad03 =  new TPad("cutpad03","cutpad03",0.0000,0.0000,0.3333,0.5000,0,0,0);
	cutpad06 =  new TPad("cutpad06","cutpad06",0.6666,0.0000,1.0000,0.5000,0,0,0);
	cutpad01->Draw();cutpad02->Draw();cutpad03->Draw();cutpad04->Draw();cutpad05->Draw();cutpad06->Draw();

	cutpad01->cd();
	TString titledpHe = "dp Cut";
	cout << "Drawing " << titledpHe << "..." << endl;
	TH1F *HedpNoCut = new TH1F("HedpNoCut",titledpHe,400,-0.08,0.08);
	TH1F *HedpCut = new TH1F("HedpCut",titledpHe,400,-0.08,0.08);
	chainHe->Draw("ExTgtCor_R.dp>>HedpNoCut", basic, "");
	cout << "Hello?" << endl;
	chainHe->Draw("ExTgtCor_R.dp>>HedpCut", basic && dp, "");
	cout << "Is anybody there?" << endl;
	HedpNoCut->Draw();
	cout << "No?" << endl;
	HedpCut->SetFillColor(kViolet);
	cout << "I don't know what's happening!" << endl;
	HedpCut->Draw("same");
	cout << "Please help me." << endl;
	cutscanvas->Update();

	cutpad02->cd();
	TString titleTarget = "Target Cut";
	cout << "Drawing " << titleTarget << "..." << endl;
	TH1F *HeReactZNoCut = new TH1F("HeReactZNoCut",titleTarget,400,-0.3,0.3);
	TH1F *HeReactZCut = new TH1F("HeReactZCut",titleTarget,400,-0.3,0.3);
	chainHe->Draw("ReactPt_R.z>>HeReactZNoCut", basic && dp, "");
	chainHe->Draw("ReactPt_R.z>>HeReactZCut", basic && dp && target, ""); 
	HeReactZNoCut->Draw();
	HeReactZCut->SetFillColor(kViolet);
	HeReactZCut->Draw("same");
	cutscanvas->Update();

	cutpad03->cd();
	TString titleThetaPhi = "Theta and Phi, No Cut";
	cout << "Drawing " << titleThetaPhi << "..." << endl;
	TH2F *HeThetaPhiNoCut = new TH2F("HeThetaPhiNoCut",titleThetaPhi,100,-0.05,0.05,100,-0.1,0.1);
	chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeThetaPhiNoCut", basic && dp && target, "");
	HeThetaPhiNoCut->SetStats(kFALSE);
	HeThetaPhiNoCut->Draw("COLZ");
	cutscanvas->Update();

	cutpad04->cd();	
	TString titleThetaCut = "Theta and Phi Cut";
	cout << "Drawing " << titleThetaCut << "..." << endl;
	TH2F *HeThetaPhiCut = new TH2F("HeThetaPhiCut",titleThetaCut,100,-0.05,0.05,100,-0.1,0.1);
	chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeThetaPhiCut", basic && dp && target && thph, "");
	HeThetaPhiCut->SetStats(kFALSE);
	HeThetaPhiCut->Draw("COLZ");
	cutscanvas->Update();

	cutpad05->cd();
	TString titleQ2 = "Q2";
	TH1F *histQ2 = new TH1F("histQ2",titleQ2,400,0,1.6);
	cout << "Drawing " << titleQ2 << "..." << endl;
	chainHe->Draw("PriKineR.Q2>>histQ2", cuts, "");
	histQ2->SetFillColor(kViolet);
	histQ2->Draw();
	cutscanvas->Update();
	
	cutpad06->cd();
	TString titleNu = "Nu";
	cout << "Drawing " << titleNu << "..." << endl;
	TH1F *histNu = new TH1F("histNu",titleNu,100,0,0.8);
	chainHe->Draw("PriKineR.nu>>histNu", cuts, "");
	histNu->SetStats(kFALSE);
	histNu->SetFillColor(kViolet);
	histNu->Draw();
	cutscanvas->Update();

	TString imageCutsTitle = "/home/ellie/physics/e05-102/images/plots_for_hand/tdc_correlation_check/HAND_plots_Run_Num_";
	imageCutsTitle += HeRunNumber;
	imageCutsTitle += "-";
	imageCutsTitle += endHeRunNumber;
	imageCutsTitle += "_cuts";
	imageCutsTitle+= ".png";
	cutscanvas->Print(imageCutsTitle);
*/

// **********************************************************************************************

	gStyle->SetOptFit(1111);
	TString veto1plane;
	TString veto1bar;
	TString veto2plane;
	TString veto2bar;
	TString veto3plane;
	TString veto3bar;
	TString veto4plane;
	TString veto4bar;
	TString veto5plane;
	TString veto5bar;
	TString veto6plane;
	TString veto6bar;
	TString antiveto1plane;
	TString antiveto1bar;
	TString antiveto2plane;
	TString antiveto2bar;
	TString antiveto3plane;
	TString antiveto3bar;
	TString allVetos;
	TString allAntivetos;
	TString definethevetos;
	TString vetoTDCslSt;
	TString vetoTDCsrSt;
	TCut vetoTDCsl;
	TCut vetoTDCsr;
	TCut vetoTDCs;
    TString antivetosTDCslSt;
    TString antivetosTDCsrSt;
	int maxbars;
	TString allAntivetos = "";

// The section below plots the HAND data
// **********************************************************************************************
//	for (int nplane=2; nplane<5; nplane++)
	for (int nplane=2; nplane<3; nplane++)
	{
		if (nplane==0) maxbars=32;
		if (nplane==1) maxbars=30;
		if (nplane==2) maxbars=24;
		if (nplane==3) maxbars=22;
		if (nplane==4) maxbars=12;
//		for (int thisbar=0; thisbar<maxbars; thisbar++)
		for (int thisbar=10; thisbar<11; thisbar++)
		{

			TString goodPlane = nplane;
			TString goodPMT = thisbar;

			hand_define_vetos(includeVetos, includeAntiVetos, antivetosAsVetos, nplane, thisbar, veto1plane, veto2plane, veto3plane, veto4plane, veto5plane, veto6plane, veto1bar, veto2bar, veto3bar, veto4bar, veto5bar, veto6bar, antiveto1plane, antiveto2plane, antiveto3plane, antiveto1bar, antiveto2bar, antiveto3bar, allVetos, allAntivetos, vetoTDCslSt, vetoTDCsrSt, vetoTDCsl, vetoTDCsr, vetoTDCs, vetoTDCcutmin, vetoTDCcutmax, antivetosTDCslSt, antivetosTDCsrSt);
//			hand_define_vetos(includeVetos, false, false, nplane, thisbar, veto1plane, veto2plane, veto3plane, veto4plane, veto5plane, veto6plane, veto1bar, veto2bar, veto3bar, veto4bar, veto5bar, veto6bar, antiveto1plane, antiveto2plane, antiveto3plane, antiveto1bar, antiveto2bar, antiveto3bar, allVetos, allAntivetos, vetoTDCslSt, vetoTDCsrSt, vetoTDCsl, vetoTDCsr, vetoTDCs, vetoTDCcutmin, vetoTDCcutmax, antivetosTDCslSt, antivetosTDCsrSt);
			// This allVetos is going to be used when drawing the
			// image of the HAND as a searchable string to find
			// out if any particular bar is a veto bar or not.
			// Similarly with goodBar;
			// **************************************************
			TString goodBar = "nd.p";
			goodBar += nplane;
			goodBar += ".";
			goodBar += thisbar;
			goodBar += " ";
			cout << "Good Bar: " << goodBar << endl;
			// **************************************************

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
			if ((nplane==4) && (thisbar==6)) {goodTDCs = "NA.nd.p4.lt_c[7]:NA.nd.p4.rt_c[6]";}
			if ((nplane==4) && (thisbar==7)) {goodTDCs = "NA.nd.p4.lt_c[6]:NA.nd.p4.rt_c[7]";}
			TString goodTDCposition = "(";
			goodTDCposition += goodTDCl;
			goodTDCposition += " - ";
			goodTDCposition += goodTDCr;
			goodTDCposition += ")";
			if ((nplane==4) && (thisbar==6)) {goodTDCposition = "(NA.nd.p4.lt_c[7] - NA.nd.p4.rt_c[6])";}
			if ((nplane==4) && (thisbar==7)) {goodTDCposition = "(NA.nd.p4.lt_c[6] - NA.nd.p4.rt_c[7])";}
			
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
			handpad02 =  new TPad("handpad02","handpad02",0.1000,0.0000,0.5500,1.0000,0,0,0);
			handpad03 =  new TPad("handpad03","handpad03",0.5500,0.0000,1.0000,1.0000,0,0,0);
			handpad01->Draw(); handpad02->Draw(); handpad03->Draw();

			handpad01->cd();
			hand_draw(HeRunNumber, endHeRunNumber, antivetosAsVetos, allVetos, goodBar, allAntivetos);
			handpad01->Update();

			TString goodTDCcutstring = goodTDCposition;
			goodTDCcutstring += ">";
			goodTDCcutstring += TDCcutmin;
			goodTDCcutstring += " && ";
			goodTDCcutstring += goodTDCposition;
			goodTDCcutstring += "<";
			goodTDCcutstring += TDCcutmax;
			cout << "goodTDCcutstring: " << goodTDCcutstring << endl;
			TCut goodTDCcut = goodTDCcutstring;

			TString basicTDCcutstring = goodTDCl;
			basicTDCcutstring += ">1 && ";
			basicTDCcutstring += goodTDCr;
			basicTDCcutstring += ">1";
			cout << "basicTDCcutstring: " << basicTDCcutstring << endl;
			TCut basicTDCcut = basicTDCcutstring;


			TString thisplaneandbar = "NA.n.plane==";
			thisplaneandbar += nplane-1;
			thisplaneandbar += " && NA.n.pad==";
			thisplaneandbar += thisbar;
			TCut thisplaneandbarcut = thisplaneandbar;

			handpad02->cd();
			handpad02->SetLogy();
			TString titleHANDleftNoVetos = "Left TDC - Right TDC for Plane #";
			titleHANDleftNoVetos += nplane;
			titleHANDleftNoVetos += ", PMT # ";
			titleHANDleftNoVetos += thisbar;
			titleHANDleftNoVetos += " without vetos";
			cout << "Drawing " << titleHANDleftNoVetos << "..." << endl;
			TString plotHANDleftNoVetos = "thph_p";
			plotHANDleftNoVetos += nplane;
			plotHANDleftNoVetos += "_b";
			plotHANDleftNoVetos += thisbar;
			TString plotHANDleftNoVetoscut = plotHANDleftNoVetos;
			plotHANDleftNoVetoscut += "_cut";
			TString cutstring = cuts;
			cout << "goodTDCposition: " << goodTDCposition << ">>" << plotHANDleftNoVetos << endl << "Cuts: " << cutstring << endl;
			TH1F *HANDleftNoVetos = new TH1F(plotHANDleftNoVetos,titleHANDleftNoVetos,HANDbins,HANDmin,HANDmax);
			TH1F *HANDleftNoVetoscut = new TH1F(plotHANDleftNoVetoscut,titleHANDleftNoVetos,HANDbins,HANDmin,HANDmax);
			TString HANDleftNoVetosTDC = goodTDCposition;
			HANDleftNoVetosTDC += ">>";
			HANDleftNoVetosTDC += plotHANDleftNoVetos;
			TString HANDleftNoVetosTDCcut = goodTDCposition;
			HANDleftNoVetosTDCcut += ">>";
			HANDleftNoVetosTDCcut += plotHANDleftNoVetoscut;
			chainHe->Draw(HANDleftNoVetosTDC, cuts && vetoTDCs && basicTDCcut,"");
			HANDleftNoVetos->Draw();
			chainHe->Draw(HANDleftNoVetosTDCcut, cuts && vetoTDCs && goodTDCcut && basicTDCcut,"same");
			HANDleftNoVetoscut->SetFillColor(kViolet);
			HANDleftNoVetoscut->Draw("same");
			handpad02->Update();

			handpad03->cd();
                        cout << "Drawing Theta and Phi kinematics..." << endl;
                        TString kinematicstitleThetaPhiNokinematics = "Theta and Phi";
                        TH2F *HeThetaPhiNokinematics = new TH2F("HeThetaPhiNokinematics",kinematicstitleThetaPhiNokinematics,100,-0.05,0.05,100,-0.1,0.1);
                        chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeThetaPhiNokinematics", cuts && basicTDCcut && goodTDCcut && vetoTDCs && thisplaneandbar, "");
                        HeThetaPhiNokinematics->SetTitle(kinematicstitleThetaPhiNokinematics);
                        HeThetaPhiNokinematics->SetStats(kFALSE);
                        HeThetaPhiNokinematics->Draw("COLZ");
			handpad03->Update();

			TString imageTitle = "/home/ellie/physics/e05-102/images/plots_for_hand/bar_theta_phi/Run_Num_";
			imageTitle += HeRunNumber;
			imageTitle += "-";
			imageTitle += endHeRunNumber;
			imageTitle += "/plane_";
			imageTitle += nplane;
			imageTitle += "_bar_";
			if (thisbar<10) {imageTitle += "0";}
			imageTitle += thisbar;
//			imageTitle += "/bar_thph_plots_";
			if (includeVetos) {imageTitle += "_with_vetos_";}
			if (antivetosAsVetos) {imageTitle += "_with_antivetos_as_vetos_";}
			imageTitle += "tdcpositioncut_";
			if (TDCcutmin>-1 && TDCcutmin<10) {imageTitle += "0";}
			if (TDCcutmin>-10 && TDCcutmin<0) 
				{
				imageTitle += "-0";
				TDCcutmin = -1 * TDCcutmin;
				}
			imageTitle += TDCcutmin;
			imageTitle += "_";
			if (TDCcutmax>-1 && TDCcutmax<10) {imageTitle += "0";}
			if (TDCcutmax>-10 && TDCcutmax<0) 
				{
				imageTitle += "-0";
				TDCcutmax = -1 * TDCcutmax;
				}
			imageTitle += TDCcutmax;
			imageTitle += ".png";
			handCanvas->Print(imageTitle);
			cout << "File printed to " << imageTitle << endl;

		}
	}



	cout << "All done!" << endl;



}







































