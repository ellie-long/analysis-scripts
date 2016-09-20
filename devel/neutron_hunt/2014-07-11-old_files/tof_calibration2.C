// ***************************************************
//
// This script should make cuts to show neutrons appearing
// in isolated bars.
//
// 05-10-10
// Elena Long
//
// ***************************************************

#include <iostream>
#include <string>
#include <string.h>
#include "hand_define_vetos.h"
#include "hand_draw.h"

// Search for HAND to get to the PMT definitions

void tof_calibration2(){

	bool includeVetos;
// 	If includeVetos = false, then only good bars will be displayed. If 
//	includeVetos = true, then veto bars will be shown along with the good bars.
//	includeVetos = true;
	includeVetos = false;

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

	TString Q2 = "1.0";
/*	int HeRunNumber = 22441;
	int endHeRunNumber = 22441;
	int ToFbins = 700;
	double ToFmin = 0;
	double ToFmax = 700;
	int TDCbins = 100;
	double TDCmin = 700;
	double TDCmax = 800;
	double goodTDCleftcutmin = 735;
	double goodTDCleftcutmax = 775;
	double goodTDCrightcutmin = 735;
	double goodTDCrightcutmax = 780;

*/
	int HeRunNumber = 21383;
	int endHeRunNumber = 21383;
	int ToFbins = 1600;
	double ToFmin = 0;
	double ToFmax = 1600;
	int TDCbins = 100;
	double TDCmin = 0;
	double TDCmax = 1600;
	double goodTDCleftcutmin = 1385;
	double goodTDCleftcutmax = 1415;
	double goodTDCrightcutmin = 1385;
	double goodTDCrightcutmax = 1415;


	int ADCbins = 200;
	double ADCmin = 1;
	double ADCmax = 3100;
	double q2min = 0.75;
	double q2max = 1.2;
	double numin = 0.3;
	double numax = 0.7;
	double xmin = 0.6;
	double xmax = 3.0;

	bool leadwall;
//	If leadwall = true, then the lead wall was in. If false, out.
	if ((HeRunNumber>20578 && HeRunNumber<20788) || (HeRunNumber>22320)) {leadwall=true;}
	else {leadwall = false;}

	int bins = 50;

//	The vetoTDCcutmin/max determine where the cuts are put on the veto
//	TDCs. 
	double vetoTDCcutmin = 750;
	double vetoTDCcutmax = 785;
//	double vetoTDCcutmin = 1385;
//	double vetoTDCcutmax = 1415;

	TCut cut = "";
	TCut kinematics = "PriKineR.Q2<10 && GoodElectron==1 && PriKineR.nu<10";
//	TCut eventtype = "(D.evtypebits&2)==2";
	TCut eventtype = "";
	TCut dp = "ExTgtCor_R.dp>-0.04 && ExTgtCor_R.dp<0.06";
	TCut target = "ReactPt_R.z>-0.15 && ReactPt_R.z<0.17";
	TCut tracks = "R.tr.n==1 && R.vdc.u1.nhit>3 && R.vdc.u1.nhit<7 && R.vdc.u2.nhit>3 && R.vdc.u2.nhit<7 && R.vdc.v1.nhit>3 && R.vdc.v1.nhit<7 && R.vdc.v2.nhit>3 && R.vdc.v2.nhit<7";
//	TCut tracks = "";
//	double thbound = 0.07;
	double thbound = 0.055;
//	double phbound = 0.03;
	double phbound = 0.025;
	TString thetaphiRStr = "abs(ExTgtCor_R.ph)<";
	thetaphiRStr += phbound;
	thetaphiRStr += " && abs(ExTgtCor_R.th)<";
	thetaphiRStr += thbound;
	TCut thph = thetaphiRStr;
	TCut xbj = "PriKineRHe3.x_bj<3.0";
	TCut pssh = "(R.ps.e + 2*R.sh.e)>900 && R.ps.e>1 && R.sh.e>1";
	TCut cerenkov = "R.cer.asum_c>150";
	TCut q2nu = "(PriKineR.Q2 - (2*PriKineR.nu) + 0.1)>0 && (PriKineR.Q2 - (2*PriKineR.nu) + 0.03)<0";
	// Although declared here, the goodTDCcut is actually made down below where  it can be included
	// in the loop so that it is easy to have it change for each good bar when done one at a time.
	// However, the left and right min and max TDC values are defined here
	TCut goodTDCcut = "";

//	xbj = "";
//	pssh = "";
//	cerenkov = "";


	TCut basic = kinematics && eventtype && tracks;
	TCut cuts = cut && kinematics && eventtype && dp && target && thph && tracks && xbj && pssh && cerenkov && q2nu;



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


// The section below plots the basic cuts used throughout the HAND plots
// **********************************************************************************************
	// Defines Canvas
	TCanvas *cutsCanvas = new TCanvas("cutsCanvas","Cuts",1360,768); //x,y
	cutpad1  =  new  TPad("cutpad1","cutpad1",0.0000,0.5000,0.2500,1.0000,0,0,0);
	cutpad2  =  new  TPad("cutpad2","cutpad2",0.2500,0.5000,0.5000,1.0000,0,0,0);
	cutpad3  =  new  TPad("cutpad3","cutpad3",0.5000,0.5000,0.7500,1.0000,0,0,0);
	cutpad4  =  new  TPad("cutpad4","cutpad4",0.7500,0.5000,1.0000,1.0000,0,0,0);
	cutpad5  =  new  TPad("cutpad5","cutpad5",0.0000,0.0000,0.2500,0.5000,0,0,0);
	cutpad6  =  new  TPad("cutpad6","cutpad6",0.2500,0.0000,0.5000,0.5000,0,0,0);
	cutpad7  =  new  TPad("cutpad7","cutpad7",0.5000,0.0000,0.7500,0.5000,0,0,0);
	cutpad8  =  new  TPad("cutpad8","cutpad8",0.7500,0.0000,1.0000,0.5000,0,0,0);
	cutpad1->Draw();cutpad2->Draw();cutpad3->Draw();cutpad4->Draw();cutpad5->Draw();cutpad6->Draw();cutpad7->Draw();cutpad8->Draw();
	
	// Everything below here makes graphs for each section of the canvas

	cutpad1->cd();
	TString titledp = "dp Cut, Runs ";
	titledp += HeRunNumber;
	titledp += " - ";
	titledp += endHeRunNumber;
	cout << "Drawing " << titledp << "..." << endl;
	TH1F *HedpNoCut = new TH1F("HedpNoCut",titledp,400,-0.08,0.08);
	TH1F *HedpCut = new TH1F("HedpCut",titledp,400,-0.08,0.08);
	chainHe->Draw("ExTgtCor_R.dp>>HedpNoCut", "", "");
	chainHe->Draw("ExTgtCor_R.dp>>HedpCut", dp, "");
	HedpNoCut->SetTitle(titledp);
	HedpNoCut->Draw();
	HedpCut->SetLineColor(kBlack);
	HedpCut->SetFillColor(kViolet);
	HedpCut->Draw("same");
	cutpad1->Update();

	cutpad2->cd();
	cout << "Drawing Target Cut..." << endl;
	TString titleTarget = "Target Cut";
	TH1F *HeReactZNoCut = new TH1F("HeReactZNoCut",titleTarget,400,-0.3,0.3);
	TH1F *HeReactZCut = new TH1F("HeReactZCut",titleTarget,400,-0.3,0.3);
	chainHe->Draw("ReactPt_R.z>>HeReactZNoCut", "", "");
	chainHe->Draw("ReactPt_R.z>>HeReactZCut", target, "");
	HeReactZNoCut->SetTitle(titleTarget);
	HeReactZNoCut->Draw();
	HeReactZCut->SetLineColor(kBlack);
	HeReactZCut->SetFillColor(kViolet);
	HeReactZCut->Draw("same");
	cutpad2->Update();

	cutpad3->cd();
	cout << "Drawing Theta and Phi Cut..." << endl;
	TString titleThetaPhiNoCut = "Theta and Phi";
	TH2F *HeThetaPhiNoCut = new TH2F("HeThetaPhiNoCut",titleThetaPhiNoCut,100,-0.05,0.05,100,-0.1,0.1);
	chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeThetaPhiNoCut", target, "");
	HeThetaPhiNoCut->SetTitle(titleThetaPhiNoCut);
	HeThetaPhiNoCut->SetStats(kFALSE);
	HeThetaPhiNoCut->Draw("COLZ");
	bottom = new TLine(-phbound,-thbound,phbound,-thbound);
	top = new TLine(-phbound,thbound,phbound,thbound);
	left = new TLine(-phbound,-thbound,-phbound,thbound);
	right = new TLine(phbound,-thbound,phbound,thbound);
	bottom->SetLineColor(kViolet);
	top->SetLineColor(kViolet);
	left->SetLineColor(kViolet);
	right->SetLineColor(kViolet);
	bottom->SetLineWidth(3);
	top->SetLineWidth(3);
	left->SetLineWidth(3);
	right->SetLineWidth(3);
	bottom->Draw("same");
	top->Draw("same");
	left->Draw("same");
	right->Draw("same");
	cutpad3->Update();

	cutpad7->cd();
	cout << "Drawing Preshower/Shower Cut..." << endl;
	TString titlePsSh = "Preshower and Shower";
	TH2F *HePsShCut = new TH2F("HePsShCut",titlePsSh,200,1,2500,200,1,1500);
	chainHe->Draw("R.ps.e:R.sh.e>>HePsShCut", "", "");
//	chainHe->Draw("R.ps.e:R.sh.e>>HePsShCut", cutsR && cerenkov, "");
	HePsShCut->SetTitle(titlePsSh);
	HePsShCut->SetStats(kFALSE);
	HePsShCut->Draw("COLZ");
	psshcut = new TLine(0,900,450,0);
	psshcut->SetLineColor(kViolet);
	psshcut->SetLineWidth(3);
	psshcut->Draw("same");
	cutpad7->Update();

	cutpad4->cd();
	TString titleQ2Nu = "Q2 and Nu";
	TH2F *histQ2Nu = new TH2F("histQ2Nu",titleQ2Nu,200,numin,numax,200,q2min,q2max);
	cout << "Drawing " << titleQ2Nu << "..." << endl;
	chainHe->Draw("PriKineR.Q2:PriKineR.nu>>histQ2Nu", cuts, "");
	histQ2Nu->SetTitle(titleQ2Nu);
//	histQ2Nu->SetStats(kFALSE);
	histQ2Nu->Draw("COLZ");
	cutpad4->Update();

	cutpad5->cd();
	TString titlecerenkov = "Cerenkov Cut";
	cout << "Drawing " << titlecerenkov << "..." << endl;
	TH1F *histcerenkov = new TH1F("histcerenkov",titlecerenkov,200,-25,2000);
	TH1F *histcerenkovcut = new TH1F("histcerenkovcut",titlecerenkov,200,-25,2000);
	chainHe->Draw("R.cer.asum_c>>histcerenkov", "", "");
	chainHe->Draw("R.cer.asum_c>>histcerenkovcut", cerenkov, "");
	histcerenkov->SetTitle(titlecerenkov);
	histcerenkov->SetStats(kFALSE);
	histcerenkovcut->SetFillColor(kViolet);
	histcerenkov->Draw();
	histcerenkovcut->Draw("same");
	cutpad5->Update();

	cutpad8->cd();
	cout << "Drawing Preshower/Shower with All Cut..." << endl;
	TString titlePsSh = "Preshower and Shower with all cuts";
	TH2F *HePsShCut = new TH2F("HePsShCut",titlePsSh,200,1,2500,200,1,1500);
//	chainHe->Draw("R.ps.e:R.sh.e>>HePsShCut", "", "");
	chainHe->Draw("R.ps.e:R.sh.e>>HePsShCut", cuts, "");
	HePsShCut->SetTitle(titlePsSh);
	HePsShCut->SetStats(kFALSE);
	HePsShCut->Draw("COLZ");
	psshcut = new TLine(0,900,450,0);
	psshcut->SetLineColor(kViolet);
	psshcut->SetLineWidth(3);
	psshcut->Draw("same");
	cutpad8->Update();

	cutpad6->cd();
	TString titlex = "Bjorken x ";
	titlex += " (x=Q^2/[2m*nu])";
	cout << "Drawing " << titlex << "..." << endl;
	TH1F *histx = new TH1F("histx",titlex,bins,xmin,xmax);
	TH1F *histxcut = new TH1F("histxcut",titlex,bins,xmin,xmax);
	histx->Sumw2();
	chainHe->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histx", cut && kinematics && eventtype && dp && target && thph && tracks && cerenkov && pssh, "E");
	chainHe->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histxcut", cuts, "E");
	histx->Draw();
	histxcut->SetFillColor(kViolet);
	histxcut->Draw("same");
	cutpad6->Update();

	TString imageCutsTitle = "/home/ellie/physics/e05-102/images/plots_for_hand/tof_calibration/HAND_plots_Run_Num_";
	imageCutsTitle += HeRunNumber;
	imageCutsTitle += "-";
	imageCutsTitle += endHeRunNumber;
	imageCutsTitle += "_basic_cuts";
	if (includeVetos) imageCutsTitle += "_with_vetos_and_";
	else imageCutsTitle += "_without_vetos_and_";
	if (antivetosAsVetos) {imageCutsTitle += "with_antivetos_as_vetos";}
	else {imageCutsTitle += "with_antivetos";}
	imageCutsTitle += ".png";
	cutsCanvas->Print(imageCutsTitle);


/*
	TCanvas *testCanvas = new TCanvas("testCanvas","Test Canvas",1600,600); //x,y
	testpad01 =  new TPad("testpad01","testpad01",0.0000,0.0000,0.5000,1.0000,0,0,0);
	testpad02 =  new TPad("testpad02","testpad02",0.5000,0.0000,1.0000,1.0000,0,0,0);
	testpad01->Draw(); testpad02->Draw();
	testpad01->cd();
	TH2F *testPlot = new TH2F("testPlot","Plane 3, PMT 09R - TDC v. ADC",ADCbins,ADCmin,ADCmax,TDCbins,TDCmin,TDCmax);
	if (includeVetos) chainHe->Draw("NA.nd.p3.rt_c[9]:NA.nd.p3.ra_c[9]>>testPlot",cuts && "(NA.nd.p2.rt_c[10]<1250 || NA.nd.p2.rt_c[10]>1750)","");
	else chainHe->Draw("NA.nd.p3.rt_c[9]:NA.nd.p3.ra_c[9]>>testPlot",cuts,"");
	testPlot->Draw("LEGO2");
	testpad01->Update();
	testpad02->cd();
	testPlot->Draw("COLZ");
	testpad02->Update();
	TString imageTestTitle = "plots_for_hand/TDC_and_ADC/HAND_test_bar_Run_Num_";
	imageTestTitle += HeRunNumber;
	imageTestTitle += "-";
	imageTestTitle += endHeRunNumber;
	if (includeVetos) imageTestTitle += "_with_vetos";
	else imageTestTitle += "_without_vetos";
	imageTestTitle += ".png";
	testCanvas->Print(imageTestTitle);
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
        TString vetoTDCslSt;
        TString vetoTDCsrSt;
        TCut vetoTDCsl;
        TCut vetoTDCsr;
        TCut vetoTDCs;
        TString antivetosTDCslSt;
        TString antivetosTDCsrSt;
	int maxbars;
	int vetoplane;
	int padBins;
	double padMin;
	double padMax;


// The section below plots the HAND data
// **********************************************************************************************
//	for (int nplane=0; nplane<5; nplane++)
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
//		for (int thisbar=0; thisbar<maxbars; thisbar++)
		if (SingleBar) {whichbar = singlebar; maxbars = singlebar + 1;}
		for (int thisbar=whichbar; thisbar<maxbars; thisbar++)
		{

			TString goodPlane = nplane;
			TString goodPMT = thisbar;
			hand_define_vetos(includeVetos, antivetosAsVetos, nplane, thisbar, veto1plane, veto2plane, veto3plane, veto4plane, veto5plane, veto6plane, veto1bar, veto2bar, veto3bar, veto4bar, veto5bar, veto6bar, antiveto1plane, antiveto2plane, antiveto3plane, antiveto1bar, antiveto2bar, antiveto3bar, allVetos, allAntivetos, vetoTDCslSt, vetoTDCsrSt, vetoTDCsl, vetoTDCsr, vetoTDCs, vetoTDCcutmin, vetoTDCcutmax, antivetosTDCslSt, antivetosTDCsrSt);


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

//			TCanvas *handCanvas = new TCanvas(canvasName,canvasTitle,1400,770); //x,y
//			handpad01 =  new TPad("handpad01","handpad01",0.0000,0.0000,0.1000,1.0000,0,0,0);
//			handpad02 =  new TPad("handpad02","handpad02",0.1000,0.5000,0.3500,1.0000,0,0,0);
//			handpad03 =  new TPad("handpad03","handpad03",0.1000,0.0000,0.3500,0.5000,0,0,0);
//			handpad04 =  new TPad("handpad04","handpad04",0.1000,0.0000,1.0000,0.5000,0,0,0);
//			handpad05 =  new TPad("handpad05","handpad05",0.1000,0.0000,1.0000,0.5000,0,0,0);
//			handpad06 =  new TPad("handpad06","handpad06",0.1000,0.0000,1.0000,0.5000,0,0,0);
//			handpad07 =  new TPad("handpad07","handpad07",0.1000,0.0000,1.0000,0.5000,0,0,0);
//			handpad08 =  new TPad("handpad08","handpad08",0.1000,0.0000,1.0000,0.5000,0,0,0);
//			handpad01->Draw(); handpad02->Draw(); handpad03->Draw(); handpad04->Draw();



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
			TH1F *HANDleft = new TH1F(plotHANDleft,titleHANDleft,TDCbins,TDCmin,TDCmax);
			TH1F *HANDleftcut = new TH1F(plotHANDleftcut,titleHANDleft,TDCbins,TDCmin,TDCmax);
			TString HANDleftTDC = goodTDCl;
			HANDleftTDC += ">>";
			HANDleftTDC += plotHANDleft;
			TString HANDleftTDCcut = goodTDCl;
			HANDleftTDCcut += ">>";
			HANDleftTDCcut += plotHANDleftcut;
			chainHe->Draw(HANDleftTDC, cuts && vetoTDCs,"");
			HANDleft->Draw();
			chainHe->Draw(HANDleftTDCcut, cuts && vetoTDCs && goodTDCleftcut,"same");
			HANDleftcut->SetFillColor(kViolet);
			HANDleftcut->Draw("same");
//			TF1 *leftFit = new TF1("leftFit","gaus",TDCmin,TDCmax);
//			HANDleft->Fit(leftFit, "R");
//			leftFit->Draw("same");
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
			HANDright->Draw();
			chainHe->Draw(HANDrightTDCcut, cuts && vetoTDCs && goodTDCrightcut,"same");
			HANDrightcut->SetFillColor(kViolet);
			HANDrightcut->Draw("same");
//			TF1 *rightFit = new TF1("rightFit","gaus",TDCmin,TDCmax);
//			HANDright->Fit(rightFit, "R");
//			rightFit->Draw("same");
			handpad03->Update();


			handpad04->cd();
			TString titleToF = "Time of Flight for Plane #";
			titleToF += nplane;
			titleToF += ", Bar # ";
			titleToF += thisbar;
			if (includeVetos) titleToF += " with vetos";
			else titleToF += " without vetos";
			cout << "Drawing " << titleToF << "..." << endl;
			TString plotToF = "ToF_p";
			plotToF += nplane;
			TString plotToFcut = plotToF;
			plotToFcut += "_cut";
			TH1F *histToF = new TH1F(plotToF, titleToF, ToFbins, ToFmin, ToFmax);
			TH1F *histToFcut = new TH1F(plotToFcut, titleToF, ToFbins, ToFmin, ToFmax);
			cout << "For plane " << nplane << ", bar " << thisbar << ", the veto cut was " << vetoTDCslSt << " and " << vetoTDCsrSt << endl;
			TString thisplaneandbar = "NA.n.plane==";
			thisplaneandbar += nplane-1;
			thisplaneandbar += " && NA.n.pad==";
			thisplaneandbar += thisbar;
			TCut thisplaneandbarcut = thisplaneandbar;
			TString ToFplots = "NA.n.tof>>";
			ToFplots += plotToF;
			TString ToFplotscut = "NA.n.tof>>";
			ToFplotscut += plotToFcut;
			chainHe->Draw(ToFplots, cuts && thisplaneandbarcut && vetoTDCs, "");
			histToF->Draw();
			chainHe->Draw(ToFplotscut, cuts && thisplaneandbarcut && vetoTDCs && goodTDCcut, "same");
			histToFcut->SetFillColor(kViolet);
			histToFcut->Draw("same");
			handpad04->Update();



			TString imageTitle = "/home/ellie/physics/e05-102/images/plots_for_hand/tof_calibration/TDC_plots_Run_Num_";
			imageTitle += HeRunNumber;
			imageTitle += "-";
			imageTitle += endHeRunNumber;
			imageTitle += "_p";
			imageTitle += nplane;
			imageTitle += "_b";
			imageTitle += thisbar;
			if (includeVetos) {imageTitle += "_with_vetos_and_";}
			else {imageTitle += "_without_vetos_and_";}
			if (antivetosAsVetos) {imageTitle += "with_antivetos_as_vetos";}
			else {imageTitle += "with_antivetos";}
			imageTitle+= ".png";
			handCanvas->Print(imageTitle);



// *********************************************************************************************************
// This section below will plot the "anti-vetos," that is, the bars immediately behind the Good Bar.
// It will also let me trace where sections of the good bar appear in purple according to the goodTDCcut

			TString antivetoCanvasName = "antiveto_for_p";
			antivetoCanvasName += nplane;
			antivetoCanvasName += "b";
			antivetoCanvasName += thisbar;
			TString antivetoCanvasTitle = "Anti-Vetos for - Plane ";
			antivetoCanvasTitle += nplane;
			antivetoCanvasTitle += ", Bar ";
			antivetoCanvasTitle += thisbar;
			TCanvas *antivetoCanvas = new TCanvas(antivetoCanvasName,antivetoCanvasTitle,1400,770); //x,y
			antivetopad01 =  new TPad("antivetopad01","antivetopad01",0.0000,0.5000,0.3333,1.0000,0,0,0);
			antivetopad02 =  new TPad("antivetopad02","antivetopad02",0.0000,0.0000,0.3333,0.5000,0,0,0);
			antivetopad03 =  new TPad("antivetopad03","antivetopad03",0.3333,0.5000,0.6666,1.0000,0,0,0);
			antivetopad04 =  new TPad("antivetopad04","antivetopad04",0.3333,0.0000,0.6666,0.5000,0,0,0);
			antivetopad05 =  new TPad("antivetopad05","antivetopad05",0.6666,0.5000,1.0000,1.0000,0,0,0);
			antivetopad06 =  new TPad("antivetopad06","antivetopad06",0.6666,0.0000,1.0000,0.5000,0,0,0);
			antivetopad01->Draw(); antivetopad02->Draw(); antivetopad03->Draw();
			antivetopad04->Draw(); antivetopad05->Draw(); antivetopad06->Draw();

			antivetopad01->cd();
			antivetopad01->SetLogy();
			TString titleantiveto1left = "Antiveto 1 - Left TDC for NA.";
			titleantiveto1left += antiveto1plane;
			titleantiveto1left += ".b";
			titleantiveto1left += antiveto1bar;
			if (includeVetos) {titleantiveto1left += " with vetos -  Runs ";}
			else {titleantiveto1left += " without vetos - Runs ";}
			titleantiveto1left += HeRunNumber;
			titleantiveto1left += "-";
			titleantiveto1left += endHeRunNumber;
			cout << "Drawing " << titleantiveto1left << "..." << endl;
			TString plotantiveto1left = "antiveto1left_";
			plotantiveto1left += veto1plane;
			plotantiveto1left += ".b";
			plotantiveto1left += veto1bar;
			TString plotantiveto1leftcut = plotantiveto1left;
			plotantiveto1leftcut += "_cut";
			TH1F *antiveto1left = new TH1F(plotantiveto1left,titleantiveto1left,TDCbins,TDCmin,TDCmax);
			TH1F *antiveto1leftcut = new TH1F(plotantiveto1leftcut,titleantiveto1left,TDCbins,TDCmin,TDCmax);
			TString antiveto1leftTDC = "NA.";
			antiveto1leftTDC += antiveto1plane;
			antiveto1leftTDC += ".lt_c[";
			antiveto1leftTDC += antiveto1bar;
			antiveto1leftTDC += "]>>";
			antiveto1leftTDC += plotantiveto1left;
			TString antiveto1leftTDCcut = "NA.";
			antiveto1leftTDCcut += antiveto1plane;
			antiveto1leftTDCcut += ".lt_c[";
			antiveto1leftTDCcut += antiveto1bar;
			antiveto1leftTDCcut += "]>>";
			antiveto1leftTDCcut += plotantiveto1leftcut;
			if (includeVetos)
			{
				chainHe->Draw(antiveto1leftTDC, cuts && vetoTDCs,"");
				chainHe->Draw(antiveto1leftTDCcut, cuts && goodTDCcut && vetoTDCs,"same");
			}
			else
			{
				chainHe->Draw(antiveto1leftTDC, cuts,"");
				chainHe->Draw(antiveto1leftTDCcut, cuts && goodTDCcut,"same");
			}
			antiveto1leftcut->SetFillColor(kViolet);
			antiveto1left->Draw();
			antiveto1leftcut->Draw("same");
			antivetopad01->Update();

			antivetopad02->cd();
			antivetopad02->SetLogy();
			TString titleantiveto1right = "Antiveto 1 - Right TDC for NA.";
			titleantiveto1right += antiveto1plane;
			titleantiveto1right += ".b";
			titleantiveto1right += antiveto1bar;
			if (includeVetos) {titleantiveto1right += " with vetos";}
			else {titleantiveto1right += " without vetos";}
			cout << "Drawing " << titleantiveto1right << "..." << endl;
			TString plotantiveto1right = "antiveto1right_";
			plotantiveto1right += veto1plane;
			plotantiveto1right += ".b";
			plotantiveto1right += veto1bar;
			TString plotantiveto1rightcut = plotantiveto1right;
			plotantiveto1rightcut += "_cut";
			TH1F *antiveto1right = new TH1F(plotantiveto1right,titleantiveto1right,TDCbins,TDCmin,TDCmax);
			TH1F *antiveto1rightcut = new TH1F(plotantiveto1rightcut,titleantiveto1right,TDCbins,TDCmin,TDCmax);
			TString antiveto1rightTDC = "NA.";
			antiveto1rightTDC += antiveto1plane;
			antiveto1rightTDC += ".rt_c[";
			antiveto1rightTDC += antiveto1bar;
			antiveto1rightTDC += "]>>";
			antiveto1rightTDC += plotantiveto1right;
			TString antiveto1rightTDCcut = "NA.";
			antiveto1rightTDCcut += antiveto1plane;
			antiveto1rightTDCcut += ".rt_c[";
			antiveto1rightTDCcut += antiveto1bar;
			antiveto1rightTDCcut += "]>>";
			antiveto1rightTDCcut += plotantiveto1rightcut;
			if (includeVetos)
			{
				chainHe->Draw(antiveto1rightTDC, cuts && vetoTDCs,"");
				chainHe->Draw(antiveto1rightTDCcut, cuts && goodTDCcut && vetoTDCs,"same");
			}
			else
			{
				chainHe->Draw(antiveto1rightTDC, cuts,"");
				chainHe->Draw(antiveto1rightTDCcut, cuts && goodTDCcut,"same");
			}
			antiveto1right->Draw();
			antiveto1rightcut->SetFillColor(kViolet);
			antiveto1rightcut->Draw("same");
			antivetopad02->Update();

			antivetopad03->cd();
			antivetopad03->SetLogy();
			TString titleantiveto2left = "Antiveto 2 - Left TDC for NA.";
			titleantiveto2left += antiveto2plane;
			titleantiveto2left += ".b";
			titleantiveto2left += antiveto2bar;
			if (includeVetos) {titleantiveto2left += " with vetos";}
			else {titleantiveto2left += " without vetos";}
			cout << "Drawing " << titleantiveto2left << "..." << endl;
			TString plotantiveto2left = "antiveto2left_";
			plotantiveto2left += veto2plane;
			plotantiveto2left += ".b";
			plotantiveto2left += veto2bar;
			TString plotantiveto2leftcut = plotantiveto2left;
			plotantiveto2leftcut += "_cut";
			TH1F *antiveto2left = new TH1F(plotantiveto2left,titleantiveto2left,TDCbins,TDCmin,TDCmax);
			TH1F *antiveto2leftcut = new TH1F(plotantiveto2leftcut,titleantiveto2left,TDCbins,TDCmin,TDCmax);
			TString antiveto2leftTDC = "NA.";
			antiveto2leftTDC += antiveto2plane;
			antiveto2leftTDC += ".lt_c[";
			antiveto2leftTDC += antiveto2bar;
			antiveto2leftTDC += "]>>";
			antiveto2leftTDC += plotantiveto2left;
			TString antiveto2leftTDCcut = "NA.";
			antiveto2leftTDCcut += antiveto2plane;
			antiveto2leftTDCcut += ".lt_c[";
			antiveto2leftTDCcut += antiveto2bar;
			antiveto2leftTDCcut += "]>>";
			antiveto2leftTDCcut += plotantiveto2leftcut;
			if (includeVetos) {
				chainHe->Draw(antiveto2leftTDC, cuts && vetoTDCs,"");
				chainHe->Draw(antiveto2leftTDCcut, cuts && goodTDCcut && vetoTDCs, "same");
			}
			else
			{
				chainHe->Draw(antiveto2leftTDC, cuts,"");
				chainHe->Draw(antiveto2leftTDCcut, cuts && goodTDCcut,"same");
			}
			antiveto2left->Draw();
			antiveto2leftcut->SetFillColor(kViolet);
			antiveto2leftcut->Draw("same");
			antivetopad03->Update();

			antivetopad04->cd();
			antivetopad04->SetLogy();
			TString titleantiveto2right = "Antiveto 2 - Right TDC for NA.";
			titleantiveto2right += antiveto2plane;
			titleantiveto2right += ".b";
			titleantiveto2right += antiveto2bar;
			if (includeVetos) {titleantiveto2right += " with vetos";}
			else {titleantiveto2right += " without vetos";}
			cout << "Drawing " << titleantiveto2right << "..." << endl;
			TString plotantiveto2right = "antiveto2right_";
			plotantiveto2right += veto2plane;
			plotantiveto2right += ".b";
			plotantiveto2right += veto2bar;
			TString plotantiveto2rightcut = plotantiveto2right;
			plotantiveto2rightcut += "_cut";
			TH1F *antiveto2right = new TH1F(plotantiveto2right,titleantiveto2right,TDCbins,TDCmin,TDCmax);
			TH1F *antiveto2rightcut = new TH1F(plotantiveto2rightcut,titleantiveto2right,TDCbins,TDCmin,TDCmax);
			TString antiveto2rightTDC = "NA.";
			antiveto2rightTDC += antiveto2plane;
			antiveto2rightTDC += ".rt_c[";
			antiveto2rightTDC += antiveto2bar;
			antiveto2rightTDC += "]>>";
			antiveto2rightTDC += plotantiveto2right;
			TString antiveto2rightTDCcut = "NA.";
			antiveto2rightTDCcut += antiveto2plane;
			antiveto2rightTDCcut += ".rt_c[";
			antiveto2rightTDCcut += antiveto2bar;
			antiveto2rightTDCcut += "]>>";
			antiveto2rightTDCcut += plotantiveto2rightcut;
			if (includeVetos)
			{
				chainHe->Draw(antiveto2rightTDC, cuts && vetoTDCs,"");
				chainHe->Draw(antiveto2rightTDCcut, cuts && goodTDCcut && vetoTDCs,"same");
			}
			else
			{
				chainHe->Draw(antiveto2rightTDC, cuts,"");
				chainHe->Draw(antiveto2rightTDCcut, cuts && goodTDCcut,"same");
			}
			antiveto2right->Draw();
			antiveto2rightcut->SetFillColor(kViolet);
			antiveto2rightcut->Draw("same");
			antivetopad04->Update();

			antivetopad05->cd();
			antivetopad05->SetLogy();
			TString titleantiveto3left = "Antiveto 3 - Left TDC for NA.";
			titleantiveto3left += antiveto3plane;
			titleantiveto3left += ".b";
			titleantiveto3left += antiveto3bar;
			if (includeVetos) {titleantiveto3left += " with vetos";}
			else {titleantiveto3left += " without vetos";}
			cout << "Drawing " << titleantiveto3left << "..." << endl;
			TString plotantiveto3left = "antiveto3left_";
			plotantiveto3left += veto3plane;
			plotantiveto3left += ".b";
			plotantiveto3left += veto3bar;
			TString plotantiveto3leftcut = plotantiveto3left;
			plotantiveto3leftcut += "_cut";
			TH1F *antiveto3left = new TH1F(plotantiveto3left,titleantiveto3left,TDCbins,TDCmin,TDCmax);
			TH1F *antiveto3leftcut = new TH1F(plotantiveto3leftcut,titleantiveto3left,TDCbins,TDCmin,TDCmax);
			TString antiveto3leftTDC = "NA.";
			antiveto3leftTDC += antiveto3plane;
			antiveto3leftTDC += ".lt_c[";
			antiveto3leftTDC += antiveto3bar;
			antiveto3leftTDC += "]>>";
			antiveto3leftTDC += plotantiveto3left;
			TString antiveto3leftTDCcut = "NA.";
			antiveto3leftTDCcut += antiveto3plane;
			antiveto3leftTDCcut += ".lt_c[";
			antiveto3leftTDCcut += antiveto3bar;
			antiveto3leftTDCcut += "]>>";
			antiveto3leftTDCcut += plotantiveto3leftcut;
			if (includeVetos)
			{
				chainHe->Draw(antiveto3leftTDC, cuts && vetoTDCs,"");
				chainHe->Draw(antiveto3leftTDCcut, cuts && goodTDCcut && vetoTDCs,"same");
			}
			else
			{
				chainHe->Draw(antiveto3leftTDC, cuts,"");
				chainHe->Draw(antiveto3leftTDCcut, cuts && goodTDCcut,"same");
			}
			antiveto3left->Draw();
			antiveto3leftcut->SetFillColor(kViolet);
			antiveto3leftcut->Draw("same");
			antivetopad05->Update();

			antivetopad06->cd();
			antivetopad06->SetLogy();
			TString titleantiveto3right = "Antiveto 3 - Right TDC for NA.";
			titleantiveto3right += antiveto3plane;
			titleantiveto3right += ".b";
			titleantiveto3right += antiveto3bar;
			if (includeVetos) {titleantiveto3right += " with vetos";}
			else {titleantiveto3right += " without vetos";}
			cout << "Drawing " << titleantiveto3right << "..." << endl;
			TString plotantiveto3right = "antiveto3right_";
			plotantiveto3right += veto3plane;
			plotantiveto3right += ".b";
			plotantiveto3right += veto3bar;
			TString plotantiveto3rightcut = plotantiveto3right;
			plotantiveto3rightcut += "_cut";
			TH1F *antiveto3right = new TH1F(plotantiveto3right,titleantiveto3right,TDCbins,TDCmin,TDCmax);
			TH1F *antiveto3rightcut = new TH1F(plotantiveto3rightcut,titleantiveto3right,TDCbins,TDCmin,TDCmax);
			TString antiveto3rightTDC = "NA.";
			antiveto3rightTDC += antiveto3plane;
			antiveto3rightTDC += ".rt_c[";
			antiveto3rightTDC += antiveto3bar;
			antiveto3rightTDC += "]>>";
			antiveto3rightTDC += plotantiveto3right;
			TString antiveto3rightTDCcut = "NA.";
			antiveto3rightTDCcut += antiveto3plane;
			antiveto3rightTDCcut += ".rt_c[";
			antiveto3rightTDCcut += antiveto3bar;
			antiveto3rightTDCcut += "]>>";
			antiveto3rightTDCcut += plotantiveto3rightcut;
			if (includeVetos)
			{
				chainHe->Draw(antiveto3rightTDC, cuts && vetoTDCs,"");
				chainHe->Draw(antiveto3rightTDCcut, cuts && goodTDCcut && vetoTDCs,"same");
			}
			else
			{
				chainHe->Draw(antiveto3rightTDC, cuts,"");
				chainHe->Draw(antiveto3rightTDCcut, cuts && goodTDCcut,"same");
			}
			antiveto3right->Draw();
			antiveto3rightcut->SetFillColor(kViolet);
			antiveto3rightcut->Draw("same");
			antivetopad06->Update();

			TString imageAntivetosTitle = "/home/ellie/physics/e05-102/images/plots_for_hand/tof_calibration/antivetos_for_Run_Num_";
			imageAntivetosTitle += HeRunNumber;
			imageAntivetosTitle += "-";
			imageAntivetosTitle += endHeRunNumber;
			imageAntivetosTitle += "_p";
			imageAntivetosTitle += nplane;
			imageAntivetosTitle += "_b";
			imageAntivetosTitle += thisbar;
			if (includeVetos) {imageAntivetosTitle += "_with_vetos_and_";}
			else {imageAntivetosTitle += "_without_vetos_and_";}
			if (antivetosAsVetos) {imageAntivetosTitle += "with_antivetos_as_vetos";}
			else {imageAntivetosTitle += "with_antivetos";}
			imageAntivetosTitle += ".png";
			antivetoCanvas->Print(imageAntivetosTitle);




// *********************************************************************************************************
// The section below will plot the bars used for vetos for the previous canvas. It will consist of two
// canvases, one without the veto cuts made and one with to show the different.

			TString veto1canvasName = "vetonovetop";
			veto1canvasName += nplane;
			veto1canvasName += "b";
			veto1canvasName += thisbar;
			TString veto1canvasTitle = "Veto TDCs around Plane ";
			veto1canvasTitle += nplane;
			veto1canvasTitle += ", Bar ";
			veto1canvasTitle += thisbar;
			TCanvas *veto1Canvas = new TCanvas(veto1canvasName,veto1canvasTitle,1400,770); //x,y
		//	TCanvas *hand = new TCanvas("hand","Neutron Data",1400,770); //x,y
			veto1pad01 =  new TPad("veto1pad01","veto1pad01",0.0000,0.7500,0.3333,1.0000,0,0,0);
			veto1pad02 =  new TPad("veto1pad02","veto1pad02",0.0000,0.5000,0.3333,0.7500,0,0,0);
			veto1pad03 =  new TPad("veto1pad03","veto1pad03",0.3333,0.7500,0.6666,1.0000,0,0,0);
			veto1pad04 =  new TPad("veto1pad04","veto1pad04",0.3333,0.5000,0.6666,0.7500,0,0,0);
			veto1pad05 =  new TPad("veto1pad05","veto1pad05",0.6666,0.7500,1.0000,1.0000,0,0,0);
			veto1pad06 =  new TPad("veto1pad06","veto1pad06",0.6666,0.5000,1.0000,0.7500,0,0,0);
			veto1pad07 =  new TPad("veto1pad07","veto1pad07",0.0000,0.2500,0.3333,0.5000,0,0,0);
			veto1pad08 =  new TPad("veto1pad08","veto1pad08",0.0000,0.0000,0.3333,0.2500,0,0,0);
			veto1pad09 =  new TPad("veto1pad09","veto1pad09",0.3333,0.2500,0.6666,0.5000,0,0,0);
			veto1pad10 =  new TPad("veto1pad10","veto1pad10",0.3333,0.0000,0.6666,0.2500,0,0,0);
			veto1pad11 =  new TPad("veto1pad11","veto1pad11",0.6666,0.2500,1.0000,0.5000,0,0,0);
			veto1pad12 =  new TPad("veto1pad12","veto1pad12",0.6666,0.0000,1.0000,0.2500,0,0,0);
			veto1pad01->Draw(); veto1pad02->Draw(); veto1pad03->Draw(); veto1pad04->Draw();
			veto1pad05->Draw(); veto1pad06->Draw(); veto1pad07->Draw(); veto1pad08->Draw();
			veto1pad09->Draw(); veto1pad10->Draw(); veto1pad11->Draw(); veto1pad12->Draw();

			veto1pad01->cd();
			TString titleVeto1left = "Left TDC for Veto 1 (NA";
			titleVeto1left += veto1plane;
			titleVeto1left += ".b";
			titleVeto1left += veto1bar;
//			titleVeto1left += " with vetos";
			titleVeto1left += ") without vetos - Runs ";
			titleVeto1left += HeRunNumber;
			titleVeto1left += " - ";
			titleVeto1left += endHeRunNumber;
			cout << "Drawing " << titleVeto1left << "..." << endl;
			TString plotVeto1left = "veto1nocutleft_for_p";
			plotVeto1left += veto1plane;
			plotVeto1left += "_b";
			plotVeto1left += veto1bar;
			TH1F *veto1left = new TH1F(plotVeto1left,titleVeto1left,TDCbins,TDCmin,TDCmax);
			TString veto1leftTDC = "NA.";
			veto1leftTDC += veto1plane;
			veto1leftTDC += ".lt_c[";
			veto1leftTDC += veto1bar;
			veto1leftTDC += "]>>";
			veto1leftTDC += plotVeto1left;
//			chainHe->Draw(veto1leftTDC, cuts && vetoTDCs,"");
			chainHe->Draw(veto1leftTDC, cuts,"");
			veto1left->Draw();
			veto1pad01->Update();

			veto1pad02->cd();
			TString titleVeto1right = "Right TDC for Veto 1 (NA.";
			titleVeto1right += veto1plane;
			titleVeto1right += ".b";
			titleVeto1right += veto1bar;
			titleVeto1right += ") without vetos";
			TString plotVeto1right = "veto1nocutright_p";
			plotVeto1right += veto1plane;
			plotVeto1right += "_b";
			plotVeto1right += veto1bar;
			cout << "Drawing " << titleVeto1right << "..." << endl;
			TH1F *Veto1right = new TH1F(plotVeto1right,titleVeto1right,TDCbins,TDCmin,TDCmax);
			TString Veto1rightTDC = "NA.";
			Veto1rightTDC += veto1plane;
			Veto1rightTDC += ".rt_c[";
			Veto1rightTDC += veto1bar;
			Veto1rightTDC += "]>>";
			Veto1rightTDC += plotVeto1right;
//			chainHe->Draw(Veto1rightTDC, cuts && vetoTDCs,"");
			chainHe->Draw(Veto1rightTDC, cuts,"");
			Veto1right->Draw();
			veto1pad02->Update();

			veto1pad03->cd();
			TString titleVeto2left = "Left TDC for Veto 2 (NA.";
			titleVeto2left += veto2plane;
			titleVeto2left += ".b";
			titleVeto2left += veto2bar;
//			titleVeto2left += " with vetos";
			titleVeto2left += ") without vetos";
			cout << "Drawing " << titleVeto2left << "..." << endl;
			TString plotVeto2left = "veto2nocutleft_for_p";
			plotVeto2left += veto2plane;
			plotVeto2left += "_b";
			plotVeto2left += veto2bar;
			TH1F *veto2left = new TH1F(plotVeto2left,titleVeto2left,TDCbins,TDCmin,TDCmax);
			TString veto2leftTDC = "NA.";
			veto2leftTDC += veto2plane;
			veto2leftTDC += ".lt_c[";
			veto2leftTDC += veto2bar;
			veto2leftTDC += "]>>";
			veto2leftTDC += plotVeto2left;
//			chainHe->Draw(veto2leftTDC, cuts && vetoTDCs,"");
			chainHe->Draw(veto2leftTDC, cuts,"");
			veto2left->Draw();
			veto1pad03->Update();

			veto1pad04->cd();
			TString titleVeto2right = "Right TDC for Veto 2 (NA.";
			titleVeto2right += veto2plane;
			titleVeto2right += ".b";
			titleVeto2right += veto2bar;
			titleVeto2right += ") without vetos";
			TString plotVeto2right = "veto2nocutright_p";
			plotVeto2right += veto2plane;
			plotVeto2right += "_b";
			plotVeto2right += veto2bar;
			cout << "Drawing " << titleVeto2right << "..." << endl;
			TH1F *Veto2right = new TH1F(plotVeto2right,titleVeto2right,TDCbins,TDCmin,TDCmax);
			TString Veto2rightTDC = "NA.";
			Veto2rightTDC += veto2plane;
			Veto2rightTDC += ".rt_c[";
			Veto2rightTDC += veto2bar;
			Veto2rightTDC += "]>>";
			Veto2rightTDC += plotVeto2right;
//			chainHe->Draw(Veto2rightTDC, cuts && vetoTDCs,"");
			chainHe->Draw(Veto2rightTDC, cuts,"");
			Veto2right->Draw();
			veto1pad04->Update();

			veto1pad05->cd();
			TString titleVeto3left = "Left TDC for Veto 3 (NA";
			titleVeto3left += veto3plane;
			titleVeto3left += ".b";
			titleVeto3left += veto3bar;
//			titleVeto3left += " with vetos";
			titleVeto3left += ") without vetos";
			cout << "Drawing " << titleVeto3left << "..." << endl;
			TString plotVeto3left = "veto3nocutleft_for_p";
			plotVeto3left += veto3plane;
			plotVeto3left += "_b";
			plotVeto3left += veto3bar;
			TH1F *veto3left = new TH1F(plotVeto3left,titleVeto3left,TDCbins,TDCmin,TDCmax);
			TString veto3leftTDC = "NA.";
			veto3leftTDC += veto3plane;
			veto3leftTDC += ".lt_c[";
			veto3leftTDC += veto3bar;
			veto3leftTDC += "]>>";
			veto3leftTDC += plotVeto3left;
//			chainHe->Draw(veto3leftTDC, cuts && vetoTDCs,"");
			chainHe->Draw(veto3leftTDC, cuts,"");
			veto3left->Draw();
			veto1pad05->Update();

			veto1pad06->cd();
			TString titleVeto3right = "Right TDC for Veto 3 (NA";
			titleVeto3right += veto3plane;
			titleVeto3right += ".b";
			titleVeto3right += veto3bar;
			titleVeto3right += ") without vetos";
			TString plotVeto3right = "veto3nocutright_p";
			plotVeto3right += veto3plane;
			plotVeto3right += "_b";
			plotVeto3right += veto3bar;
			cout << "Drawing " << titleVeto3right << "..." << endl;
			TH1F *Veto3right = new TH1F(plotVeto3right,titleVeto3right,TDCbins,TDCmin,TDCmax);
			TString Veto3rightTDC = "NA.";
			Veto3rightTDC += veto3plane;
			Veto3rightTDC += ".rt_c[";
			Veto3rightTDC += veto3bar;
			Veto3rightTDC += "]>>";
			Veto3rightTDC += plotVeto3right;
//			chainHe->Draw(Veto3rightTDC, cuts && vetoTDCs,"");
			chainHe->Draw(Veto3rightTDC, cuts,"");
			Veto3right->Draw();
			veto1pad06->Update();

			veto1pad07->cd();
			TString titleVeto4left = "Left TDC for Veto 4 (NA.";
			titleVeto4left += veto4plane;
			titleVeto4left += ".b";
			titleVeto4left += veto4bar;
//			titleVeto4left += " with vetos";
			titleVeto4left += ") without vetos";
			cout << "Drawing " << titleVeto4left << "..." << endl;
			TString plotVeto4left = "veto4nocutleft_for_p";
			plotVeto4left += veto4plane;
			plotVeto4left += "_b";
			plotVeto4left += veto4bar;
			TH1F *veto4left = new TH1F(plotVeto4left,titleVeto4left,TDCbins,TDCmin,TDCmax);
			TString veto4leftTDC = "NA.";
			veto4leftTDC += veto4plane;
			veto4leftTDC += ".lt_c[";
			veto4leftTDC += veto4bar;
			veto4leftTDC += "]>>";
			veto4leftTDC += plotVeto4left;
//			chainHe->Draw(veto4leftTDC, cuts && vetoTDCs,"");
			chainHe->Draw(veto4leftTDC, cuts,"");
			veto4left->Draw();
			veto1pad07->Update();

			veto1pad08->cd();
			TString titleVeto4right = "Right TDC for Veto 4 (NA.";
			titleVeto4right += veto4plane;
			titleVeto4right += ".b";
			titleVeto4right += veto4bar;
			titleVeto4right += ") without vetos";
			TString plotVeto4right = "veto4nocutright_p";
			plotVeto4right += veto4plane;
			plotVeto4right += "_b";
			plotVeto4right += veto4bar;
			cout << "Drawing " << titleVeto4right << "..." << endl;
			TH1F *Veto4right = new TH1F(plotVeto4right,titleVeto4right,TDCbins,TDCmin,TDCmax);
			TString Veto4rightTDC = "NA.";
			Veto4rightTDC += veto4plane;
			Veto4rightTDC += ".rt_c[";
			Veto4rightTDC += veto4bar;
			Veto4rightTDC += "]>>";
			Veto4rightTDC += plotVeto4right;
//			chainHe->Draw(Veto4rightTDC, cuts && vetoTDCs,"");
			chainHe->Draw(Veto4rightTDC, cuts,"");
			Veto4right->Draw();
			veto1pad08->Update();

			veto1pad09->cd();
			TString titleVeto5left = "Left TDC for Veto 5 (NA.";
			titleVeto5left += veto5plane;
			titleVeto5left += ".b";
			titleVeto5left += veto5bar;
//			titleVeto5left += " with vetos";
			titleVeto5left += ") without vetos";
			cout << "Drawing " << titleVeto5left << "..." << endl;
			TString plotVeto5left = "veto5nocutleft_for_p";
			plotVeto5left += veto5plane;
			plotVeto5left += "_b";
			plotVeto5left += veto5bar;
			TH1F *veto5left = new TH1F(plotVeto5left,titleVeto5left,TDCbins,TDCmin,TDCmax);
			TString veto5leftTDC = "NA.";
			veto5leftTDC += veto5plane;
			veto5leftTDC += ".lt_c[";
			veto5leftTDC += veto5bar;
			veto5leftTDC += "]>>";
			veto5leftTDC += plotVeto5left;
//			chainHe->Draw(veto5leftTDC, cuts && vetoTDCs,"");
			chainHe->Draw(veto5leftTDC, cuts,"");
			veto5left->Draw();
			veto1pad09->Update();

			veto1pad10->cd();
			TString titleVeto5right = "Right TDC for Veto 5 (NA.";
			titleVeto5right += veto5plane;
			titleVeto5right += ".b";
			titleVeto5right += veto5bar;
			titleVeto5right += ") without vetos";
			TString plotVeto5right = "veto5nocutright_p";
			plotVeto5right += veto5plane;
			plotVeto5right += "_b";
			plotVeto5right += veto5bar;
			cout << "Drawing " << titleVeto5right << "..." << endl;
			TH1F *Veto5right = new TH1F(plotVeto5right,titleVeto5right,TDCbins,TDCmin,TDCmax);
			TString Veto5rightTDC = "NA.";
			Veto5rightTDC += veto5plane;
			Veto5rightTDC += ".rt_c[";
			Veto5rightTDC += veto5bar;
			Veto5rightTDC += "]>>";
			Veto5rightTDC += plotVeto5right;
//			chainHe->Draw(Veto5rightTDC, cuts && vetoTDCs,"");
			chainHe->Draw(Veto5rightTDC, cuts,"");
			Veto5right->Draw();
			veto1pad10->Update();

			veto1pad11->cd();
			TString titleVeto6left = "Left TDC for Veto 6 (NA.";
			titleVeto6left += veto6plane;
			titleVeto6left += ".b";
			titleVeto6left += veto6bar;
//			titleVeto6left += " with vetos";
			titleVeto6left += ") without vetos";
			cout << "Drawing " << titleVeto6left << "..." << endl;
			TString plotVeto6left = "veto6nocutleft_for_p";
			plotVeto6left += veto6plane;
			plotVeto6left += "_b";
			plotVeto6left += veto6bar;
			TH1F *veto6left = new TH1F(plotVeto6left,titleVeto6left,TDCbins,TDCmin,TDCmax);
			TString veto6leftTDC = "NA.";
			veto6leftTDC += veto6plane;
			veto6leftTDC += ".lt_c[";
			veto6leftTDC += veto6bar;
			veto6leftTDC += "]>>";
			veto6leftTDC += plotVeto6left;
//			chainHe->Draw(veto6leftTDC, cuts && vetoTDCs,"");
			chainHe->Draw(veto6leftTDC, cuts,"");
			veto6left->Draw();
			veto1pad11->Update();

			veto1pad12->cd();
			TString titleVeto6right = "Right TDC for Veto 6 (NA.";
			titleVeto6right += veto6plane;
			titleVeto6right += ".b";
			titleVeto6right += veto6bar;
			titleVeto6right += ") without vetos";
			TString plotVeto6right = "veto6nocutright_p";
			plotVeto6right += veto6plane;
			plotVeto6right += "_b";
			plotVeto6right += veto6bar;
			cout << "Drawing " << titleVeto6right << "..." << endl;
			TH1F *Veto6right = new TH1F(plotVeto6right,titleVeto6right,TDCbins,TDCmin,TDCmax);
			TString Veto6rightTDC = "NA.";
			Veto6rightTDC += veto6plane;
			Veto6rightTDC += ".rt_c[";
			Veto6rightTDC += veto6bar;
			Veto6rightTDC += "]>>";
			Veto6rightTDC += plotVeto6right;
//			chainHe->Draw(Veto6rightTDC, cuts && vetoTDCs,"");
			chainHe->Draw(Veto6rightTDC, cuts,"");
			Veto6right->Draw();
			veto1pad12->Update();


			TString imageVetosWithoutVetosTitle = "/home/ellie/physics/e05-102/images/plots_for_hand/tof_calibration/vetos_without_veto_cut_for_Run_Num_";
			imageVetosWithoutVetosTitle += HeRunNumber;
			imageVetosWithoutVetosTitle += "-";
			imageVetosWithoutVetosTitle += endHeRunNumber;
			imageVetosWithoutVetosTitle += "_p";
			imageVetosWithoutVetosTitle += nplane;
			imageVetosWithoutVetosTitle += "_b";
			imageVetosWithoutVetosTitle += thisbar;
			if (includeVetos) {imageVetosWithoutVetosTitle += "_with_vetos_and_";}
			else {imageVetosWithoutVetosTitle += "_without_vetos_and_";}
			if (antivetosAsVetos) {imageVetosWithoutVetosTitle += "with_antivetos_as_vetos";}
			else {imageVetosWithoutVetosTitle += "with_antivetos";}
			imageVetosWithoutVetosTitle+= ".png";
			veto1Canvas->Print(imageVetosWithoutVetosTitle);


// *********************************************************************************************************
// The section below will plot the bars used for vetos for the previous canvas. It will consist of two
// canvases, one without the veto cuts made and one with to show the different.

			TString veto2canvasName = "vetowithvetos";
			veto2canvasName += nplane;
			veto2canvasName += "b";
			veto2canvasName += thisbar;
			TString veto2canvasTitle = "Veto TDCs around Plane ";
			veto2canvasTitle += nplane;
			veto2canvasTitle += ", Bar ";
			veto2canvasTitle += thisbar;
			veto2canvasTitle += " with vetos";
			TCanvas *veto2Canvas = new TCanvas(veto2canvasName,veto2canvasTitle,1400,770); //x,y
		//	TCanvas *hand = new TCanvas("hand","Neutron Data",1400,770); //x,y
			veto2pad01 =  new TPad("veto2pad01","veto2pad01",0.0000,0.7500,0.3333,1.0000,0,0,0);
			veto2pad02 =  new TPad("veto2pad02","veto2pad02",0.0000,0.5000,0.3333,0.7500,0,0,0);
			veto2pad03 =  new TPad("veto2pad03","veto2pad03",0.3333,0.7500,0.6666,1.0000,0,0,0);
			veto2pad04 =  new TPad("veto2pad04","veto2pad04",0.3333,0.5000,0.6666,0.7500,0,0,0);
			veto2pad05 =  new TPad("veto2pad05","veto2pad05",0.6666,0.7500,1.0000,1.0000,0,0,0);
			veto2pad06 =  new TPad("veto2pad06","veto2pad06",0.6666,0.5000,1.0000,0.7500,0,0,0);
			veto2pad07 =  new TPad("veto2pad07","veto2pad07",0.0000,0.2500,0.3333,0.5000,0,0,0);
			veto2pad08 =  new TPad("veto2pad08","veto2pad08",0.0000,0.0000,0.3333,0.2500,0,0,0);
			veto2pad09 =  new TPad("veto2pad09","veto2pad09",0.3333,0.2500,0.6666,0.5000,0,0,0);
			veto2pad10 =  new TPad("veto2pad10","veto2pad10",0.3333,0.0000,0.6666,0.2500,0,0,0);
			veto2pad11 =  new TPad("veto2pad11","veto2pad11",0.6666,0.2500,1.0000,0.5000,0,0,0);
			veto2pad12 =  new TPad("veto2pad12","veto2pad12",0.6666,0.0000,1.0000,0.2500,0,0,0);
			veto2pad01->Draw(); veto2pad02->Draw(); veto2pad03->Draw(); veto2pad04->Draw();
			veto2pad05->Draw(); veto2pad06->Draw(); veto2pad07->Draw(); veto2pad08->Draw();
			veto2pad09->Draw(); veto2pad10->Draw(); veto2pad11->Draw(); veto2pad12->Draw();

			veto2pad01->cd();
			TString titleVeto1left = "Left TDC for Veto 1 (NA";
			titleVeto1left += veto1plane;
			titleVeto1left += ".b";
			titleVeto1left += veto1bar;
//			titleVeto1left += " with vetos";
			titleVeto1left += ") with vetos - Runs ";
			titleVeto1left += HeRunNumber;
			titleVeto1left += " - ";
			titleVeto1left += endHeRunNumber;
			cout << "Drawing " << titleVeto1left << "..." << endl;
			TString plotVeto1left = "veto1cutleft_for_p";
			plotVeto1left += veto1plane;
			plotVeto1left += "_b";
			plotVeto1left += veto1bar;
			TH1F *veto1left = new TH1F(plotVeto1left,titleVeto1left,TDCbins,TDCmin,TDCmax);
			TString veto1leftTDC = "NA.";
			veto1leftTDC += veto1plane;
			veto1leftTDC += ".lt_c[";
			veto1leftTDC += veto1bar;
			veto1leftTDC += "]>>";
			veto1leftTDC += plotVeto1left;
			chainHe->Draw(veto1leftTDC, cuts && vetoTDCs,"");
//			chainHe->Draw(veto1leftTDC, cuts,"");
			veto1left->Draw();
			veto2pad01->Update();

			veto2pad02->cd();
			TString titleVeto1right = "Right TDC for Veto 1 (NA.";
			titleVeto1right += veto1plane;
			titleVeto1right += ".b";
			titleVeto1right += veto1bar;
			titleVeto1right += ") with vetos";
			TString plotVeto1right = "veto1cutright_p";
			plotVeto1right += veto1plane;
			plotVeto1right += "_b";
			plotVeto1right += veto1bar;
			cout << "Drawing " << titleVeto1right << "..." << endl;
			TH1F *Veto1right = new TH1F(plotVeto1right,titleVeto1right,TDCbins,TDCmin,TDCmax);
			TString Veto1rightTDC = "NA.";
			Veto1rightTDC += veto1plane;
			Veto1rightTDC += ".rt_c[";
			Veto1rightTDC += veto1bar;
			Veto1rightTDC += "]>>";
			Veto1rightTDC += plotVeto1right;
			chainHe->Draw(Veto1rightTDC, cuts && vetoTDCs,"");
//			chainHe->Draw(Veto1rightTDC, cuts,"");
			Veto1right->Draw();
			veto2pad02->Update();

			veto2pad03->cd();
			TString titleVeto2left = "Left TDC for Veto 2 (NA.";
			titleVeto2left += veto2plane;
			titleVeto2left += ".b";
			titleVeto2left += veto2bar;
//			titleVeto2left += " with vetos";
			titleVeto2left += ") with vetos";
			cout << "Drawing " << titleVeto2left << "..." << endl;
			TString plotVeto2left = "veto2cutleft_for_p";
			plotVeto2left += veto2plane;
			plotVeto2left += "_b";
			plotVeto2left += veto2bar;
			TH1F *veto2left = new TH1F(plotVeto2left,titleVeto2left,TDCbins,TDCmin,TDCmax);
			TString veto2leftTDC = "NA.";
			veto2leftTDC += veto2plane;
			veto2leftTDC += ".lt_c[";
			veto2leftTDC += veto2bar;
			veto2leftTDC += "]>>";
			veto2leftTDC += plotVeto2left;
			chainHe->Draw(veto2leftTDC, cuts && vetoTDCs,"");
//			chainHe->Draw(veto2leftTDC, cuts,"");
			veto2left->Draw();
			veto2pad03->Update();

			veto2pad04->cd();
			TString titleVeto2right = "Right TDC for Veto 2 (NA.";
			titleVeto2right += veto2plane;
			titleVeto2right += ".b";
			titleVeto2right += veto2bar;
			titleVeto2right += ") with vetos";
			TString plotVeto2right = "veto2cutright_p";
			plotVeto2right += veto2plane;
			plotVeto2right += "_b";
			plotVeto2right += veto2bar;
			cout << "Drawing " << titleVeto2right << "..." << endl;
			TH1F *Veto2right = new TH1F(plotVeto2right,titleVeto2right,TDCbins,TDCmin,TDCmax);
			TString Veto2rightTDC = "NA.";
			Veto2rightTDC += veto2plane;
			Veto2rightTDC += ".rt_c[";
			Veto2rightTDC += veto2bar;
			Veto2rightTDC += "]>>";
			Veto2rightTDC += plotVeto2right;
			chainHe->Draw(Veto2rightTDC, cuts && vetoTDCs,"");
//			chainHe->Draw(Veto2rightTDC, cuts,"");
			Veto2right->Draw();
			veto2pad04->Update();

			veto2pad05->cd();
			TString titleVeto3left = "Left TDC for Veto 3 (NA";
			titleVeto3left += veto3plane;
			titleVeto3left += ".b";
			titleVeto3left += veto3bar;
//			titleVeto3left += " with vetos";
			titleVeto3left += ") with vetos";
			cout << "Drawing " << titleVeto3left << "..." << endl;
			TString plotVeto3left = "veto3cutleft_for_p";
			plotVeto3left += veto3plane;
			plotVeto3left += "_b";
			plotVeto3left += veto3bar;
			TH1F *veto3left = new TH1F(plotVeto3left,titleVeto3left,TDCbins,TDCmin,TDCmax);
			TString veto3leftTDC = "NA.";
			veto3leftTDC += veto3plane;
			veto3leftTDC += ".lt_c[";
			veto3leftTDC += veto3bar;
			veto3leftTDC += "]>>";
			veto3leftTDC += plotVeto3left;
			chainHe->Draw(veto3leftTDC, cuts && vetoTDCs,"");
//			chainHe->Draw(veto3leftTDC, cuts,"");
			veto3left->Draw();
			veto2pad05->Update();

			veto2pad06->cd();
			TString titleVeto3right = "Right TDC for Veto 3 (NA";
			titleVeto3right += veto3plane;
			titleVeto3right += ".b";
			titleVeto3right += veto3bar;
			titleVeto3right += ") with vetos";
			TString plotVeto3right = "veto3cutright_p";
			plotVeto3right += veto3plane;
			plotVeto3right += "_b";
			plotVeto3right += veto3bar;
			cout << "Drawing " << titleVeto3right << "..." << endl;
			TH1F *Veto3right = new TH1F(plotVeto3right,titleVeto3right,TDCbins,TDCmin,TDCmax);
			TString Veto3rightTDC = "NA.";
			Veto3rightTDC += veto3plane;
			Veto3rightTDC += ".rt_c[";
			Veto3rightTDC += veto3bar;
			Veto3rightTDC += "]>>";
			Veto3rightTDC += plotVeto3right;
			chainHe->Draw(Veto3rightTDC, cuts && vetoTDCs,"");
//			chainHe->Draw(Veto3rightTDC, cuts,"");
			Veto3right->Draw();
			veto2pad06->Update();

			veto2pad07->cd();
			TString titleVeto4left = "Left TDC for Veto 4 (NA.";
			titleVeto4left += veto4plane;
			titleVeto4left += ".b";
			titleVeto4left += veto4bar;
//			titleVeto4left += " with vetos";
			titleVeto4left += ") with vetos";
			cout << "Drawing " << titleVeto4left << "..." << endl;
			TString plotVeto4left = "veto4cutleft_for_p";
			plotVeto4left += veto4plane;
			plotVeto4left += "_b";
			plotVeto4left += veto4bar;
			TH1F *veto4left = new TH1F(plotVeto4left,titleVeto4left,TDCbins,TDCmin,TDCmax);
			TString veto4leftTDC = "NA.";
			veto4leftTDC += veto4plane;
			veto4leftTDC += ".lt_c[";
			veto4leftTDC += veto4bar;
			veto4leftTDC += "]>>";
			veto4leftTDC += plotVeto4left;
			chainHe->Draw(veto4leftTDC, cuts && vetoTDCs,"");
//			chainHe->Draw(veto4leftTDC, cuts,"");
			veto4left->Draw();
			veto2pad07->Update();

			veto2pad08->cd();
			TString titleVeto4right = "Right TDC for Veto 4 (NA.";
			titleVeto4right += veto4plane;
			titleVeto4right += ".b";
			titleVeto4right += veto4bar;
			titleVeto4right += ") with vetos";
			TString plotVeto4right = "veto4cutright_p";
			plotVeto4right += veto4plane;
			plotVeto4right += "_b";
			plotVeto4right += veto4bar;
			cout << "Drawing " << titleVeto4right << "..." << endl;
			TH1F *Veto4right = new TH1F(plotVeto4right,titleVeto4right,TDCbins,TDCmin,TDCmax);
			TString Veto4rightTDC = "NA.";
			Veto4rightTDC += veto4plane;
			Veto4rightTDC += ".rt_c[";
			Veto4rightTDC += veto4bar;
			Veto4rightTDC += "]>>";
			Veto4rightTDC += plotVeto4right;
			chainHe->Draw(Veto4rightTDC, cuts && vetoTDCs,"");
//			chainHe->Draw(Veto4rightTDC, cuts,"");
			Veto4right->Draw();
			veto2pad08->Update();

			veto2pad09->cd();
			TString titleVeto5left = "Left TDC for Veto 5 (NA.";
			titleVeto5left += veto5plane;
			titleVeto5left += ".b";
			titleVeto5left += veto5bar;
//			titleVeto5left += " with vetos";
			titleVeto5left += ") with vetos";
			cout << "Drawing " << titleVeto5left << "..." << endl;
			TString plotVeto5left = "veto5cutleft_for_p";
			plotVeto5left += veto5plane;
			plotVeto5left += "_b";
			plotVeto5left += veto5bar;
			TH1F *veto5left = new TH1F(plotVeto5left,titleVeto5left,TDCbins,TDCmin,TDCmax);
			TString veto5leftTDC = "NA.";
			veto5leftTDC += veto5plane;
			veto5leftTDC += ".lt_c[";
			veto5leftTDC += veto5bar;
			veto5leftTDC += "]>>";
			veto5leftTDC += plotVeto5left;
			chainHe->Draw(veto5leftTDC, cuts && vetoTDCs,"");
//			chainHe->Draw(veto5leftTDC, cuts,"");
			veto5left->Draw();
			veto2pad09->Update();

			veto2pad10->cd();
			TString titleVeto5right = "Right TDC for Veto 5 (NA.";
			titleVeto5right += veto5plane;
			titleVeto5right += ".b";
			titleVeto5right += veto5bar;
			titleVeto5right += ") with vetos";
			TString plotVeto5right = "veto5cutright_p";
			plotVeto5right += veto5plane;
			plotVeto5right += "_b";
			plotVeto5right += veto5bar;
			cout << "Drawing " << titleVeto5right << "..." << endl;
			TH1F *Veto5right = new TH1F(plotVeto5right,titleVeto5right,TDCbins,TDCmin,TDCmax);
			TString Veto5rightTDC = "NA.";
			Veto5rightTDC += veto5plane;
			Veto5rightTDC += ".rt_c[";
			Veto5rightTDC += veto5bar;
			Veto5rightTDC += "]>>";
			Veto5rightTDC += plotVeto5right;
			chainHe->Draw(Veto5rightTDC, cuts && vetoTDCs,"");
			Veto5right->Draw();
			veto2pad10->Update();

			veto2pad11->cd();
			TString titleVeto6left = "Left TDC for Veto 6 (NA.";
			titleVeto6left += veto6plane;
			titleVeto6left += ".b";
			titleVeto6left += veto6bar;
//			titleVeto6left += " with vetos";
			titleVeto6left += ") with vetos";
			cout << "Drawing " << titleVeto6left << "..." << endl;
			TString plotVeto6left = "veto6cutleft_for_p";
			plotVeto6left += veto6plane;
			plotVeto6left += "_b";
			plotVeto6left += veto6bar;
			TH1F *veto6left = new TH1F(plotVeto6left,titleVeto6left,TDCbins,TDCmin,TDCmax);
			TString veto6leftTDC = "NA.";
			veto6leftTDC += veto6plane;
			veto6leftTDC += ".lt_c[";
			veto6leftTDC += veto6bar;
			veto6leftTDC += "]>>";
			veto6leftTDC += plotVeto6left;
			chainHe->Draw(veto6leftTDC, cuts && vetoTDCs,"");
			veto6left->Draw();
			veto2pad11->Update();

			veto2pad12->cd();
			TString titleVeto6right = "Right TDC for Veto 6 (NA.";
			titleVeto6right += veto6plane;
			titleVeto6right += ".b";
			titleVeto6right += veto6bar;
			titleVeto6right += ") with vetos";
			TString plotVeto6right = "veto6cutright_p";
			plotVeto6right += veto6plane;
			plotVeto6right += "_b";
			plotVeto6right += veto6bar;
			cout << "Drawing " << titleVeto6right << "..." << endl;
			TH1F *Veto6right = new TH1F(plotVeto6right,titleVeto6right,TDCbins,TDCmin,TDCmax);
			TString Veto6rightTDC = "NA.";
			Veto6rightTDC += veto6plane;
			Veto6rightTDC += ".rt_c[";
			Veto6rightTDC += veto6bar;
			Veto6rightTDC += "]>>";
			Veto6rightTDC += plotVeto6right;
			chainHe->Draw(Veto6rightTDC, cuts && vetoTDCs,"");
			Veto6right->Draw();
			veto2pad12->Update();


			TString imageVetosWithVetosTitle = "/home/ellie/physics/e05-102/images/plots_for_hand/tof_calibration/vetos_with_veto_cut_for_Run_Num_";
			imageVetosWithVetosTitle += HeRunNumber;
			imageVetosWithVetosTitle += "-";
			imageVetosWithVetosTitle += endHeRunNumber;
			imageVetosWithVetosTitle += "_p";
			imageVetosWithVetosTitle += nplane;
			imageVetosWithVetosTitle += "_b";
			imageVetosWithVetosTitle += thisbar;
			if (includeVetos) {imageVetosWithVetosTitle += "_with_vetos_and_";}
			else {imageVetosWithVetosTitle += "_without_vetos_and_";}
			if (antivetosAsVetos) {imageVetosWithVetosTitle += "with_antivetos_as_vetos";}
			else {imageVetosWithVetosTitle += "with_antivetos";}
			imageVetosWithVetosTitle+= ".png";
			veto2Canvas->Print(imageVetosWithVetosTitle);


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
			bottom->Draw("same");
			top->Draw("same");
			left->Draw("same");
			right->Draw("same");
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
			psshcut->Draw("same");
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
			psshcut->Draw("same");
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


			TString imageKinematicsTitle = "/home/ellie/physics/e05-102/images/plots_for_hand/tof_calibration/kinematics_for_Run_Num_";
			imageKinematicsTitle += HeRunNumber;
			imageKinematicsTitle += "-";
			imageKinematicsTitle += endHeRunNumber;
			imageKinematicsTitle += "_p";
			imageKinematicsTitle += nplane;
			imageKinematicsTitle += "_b";
			imageKinematicsTitle += thisbar;
			if (includeVetos) {imageKinematicsTitle += "_with_vetos_and_";}
			else {imageKinematicsTitle += "_without_vetos_and_";}
			if (antivetosAsVetos) {imageKinematicsTitle += "with_antivetos_as_vetos";}
			else {imageKinematicsTitle += "with_antivetos";}
			imageKinematicsTitle+= ".png";
			kinematicsCanvas->Print(imageKinematicsTitle);




		}
	}



	cout << "All done!" << endl;



}







































