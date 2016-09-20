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

// Search for HAND to get to the PMT definitions

void tdc_offset_calibration(){

	TString Q2 = "1.0";
//	int HeRunNumber = 20791;
//	int endHeRunNumber = 20792;

// 	These variables define the size of the HAND plots
	int HANDbins = 100;
//	double HANDmin = 650;
//	double HANDmax = 900;
	double HANDmin = 0;
	double HANDmax = 1500;
	double fitMin = 650;
	double fitMax = 900;

	int HeRunNumber = 21383;
	int endHeRunNumber = 21383;
	
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
//			filenameHe = "/home/ellie/physics/e05-102/ellana/ROOTfiles/q2_01_vert/e05102_R_";
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

	TString imageCutsTitle = "plots_for_hand/TDC/HAND_plots_Run_Num_";
	imageCutsTitle += HeRunNumber;
	imageCutsTitle += "_cuts";
	imageCutsTitle+= ".png";
	cutscanvas->Print(imageCutsTitle);
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
	int maxbars;


// The section below plots the HAND data
// **********************************************************************************************
	for (int nplane=0; nplane<5; nplane++)
	{
		if (nplane==0) maxbars=32;
		if (nplane==1) maxbars=30;
		if (nplane==2) maxbars=24;
		if (nplane==3) maxbars=22;
		if (nplane==4) maxbars=12;
		for (int thisbar=0; thisbar<maxbars; thisbar++)
		{

			TString goodPlane = nplane;
			TString goodPMT = thisbar;

			// This huge set of if statements defines the vetos for each good bar we're
			// going to look at. So far the Good Bar with the most vetos has 6 vetos.
			// Most of the bars do not, in which case the last different veto is repeated 
			// in the remaining veto spaves so that extra bars aren't counted.
			// Hopefully this works.
	/*		if (nplane==2){
				if (thisbar==0){
				veto1plane = "nd.p1"; veto1bar = "0";
				veto2plane = "nd.p1"; veto2bar = "1";
				veto3plane = "nd.p2"; veto3bar = "1";
				veto4plane = "nd.p2"; veto4bar = "1";
				veto5plane = "nd.p2"; veto5bar = "1";
				veto6plane = "nd.p2"; veto6bar = "1";
				}
				if (thisbar==1){
				veto1plane = "nd.p1"; veto1bar = "1";
				veto2plane = "nd.p1"; veto2bar = "2";
				veto3plane = "nd.p2"; veto3bar = "0";
				veto4plane = "nd.p2"; veto4bar = "2";
				veto5plane = "nd.p2"; veto5bar = "2";
				veto6plane = "nd.p2"; veto6bar = "2";
				}
				if (thisbar==2){
				veto1plane = "nd.p1"; veto1bar = "2";
				veto2plane = "nd.p1"; veto2bar = "3";
				veto3plane = "nd.p2"; veto3bar = "1";
				veto4plane = "nd.p2"; veto4bar = "3";
				veto5plane = "nd.p2"; veto5bar = "3";
				veto6plane = "nd.p2"; veto6bar = "3";
				}
				if (thisbar==3){
				veto1plane = "nd.p1"; veto1bar = "3";
				veto2plane = "nd.p1"; veto2bar = "4";
				veto3plane = "nd.p1"; veto3bar = "5";
				veto4plane = "nd.p2"; veto4bar = "2";
				veto5plane = "nd.p2"; veto5bar = "4";
				veto6plane = "nd.p2"; veto6bar = "4";
				}
				if (thisbar==4){
				veto1plane = "nd.p1"; veto1bar = "4";
				veto2plane = "nd.p1"; veto2bar = "5";
				veto3plane = "nd.p1"; veto3bar = "6";
				veto4plane = "nd.p2"; veto4bar = "3";
				veto5plane = "nd.p2"; veto5bar = "5";
				veto6plane = "nd.p2"; veto6bar = "5";
				}
				if (thisbar==5){
				veto1plane = "nd.p1"; veto1bar = "6";
				veto2plane = "nd.p1"; veto2bar = "7";
				veto3plane = "nd.p2"; veto3bar = "4";
				veto4plane = "nd.p2"; veto4bar = "6";
				veto5plane = "nd.p2"; veto5bar = "6";
				veto6plane = "nd.p2"; veto6bar = "6";
				}
				if (thisbar==6){
				veto1plane = "nd.p1"; veto1bar = "7";
				veto2plane = "nd.p1"; veto2bar = "8";
				veto3plane = "nd.p2"; veto3bar = "5";
				veto4plane = "nd.p2"; veto4bar = "7";
				veto5plane = "nd.p2"; veto5bar = "7";
				veto6plane = "nd.p2"; veto6bar = "7";
				}
				if (thisbar==7){
				veto1plane = "nd.p1"; veto1bar = "8";
				veto2plane = "nd.p1"; veto2bar = "9";
				veto3plane = "nd.p1"; veto3bar = "10";
				veto4plane = "nd.p2"; veto4bar = "6";
				veto5plane = "nd.p2"; veto5bar = "8";
				veto6plane = "nd.p2"; veto6bar = "8";
				}
				if (thisbar==8){
				veto1plane = "nd.p1"; veto1bar = "9";
				veto2plane = "nd.p1"; veto2bar = "10";
				veto3plane = "nd.p1"; veto3bar = "11";
				veto4plane = "nd.p2"; veto4bar = "7";
				veto5plane = "nd.p2"; veto5bar = "9";
				veto6plane = "nd.p2"; veto6bar = "9";
				}
				if (thisbar==9){
				veto1plane = "nd.p1"; veto1bar = "11";
				veto2plane = "nd.p1"; veto2bar = "12";
				veto3plane = "nd.p2"; veto3bar = "8";
				veto4plane = "nd.p2"; veto4bar = "10";
				veto5plane = "nd.p2"; veto5bar = "10";
				veto6plane = "nd.p2"; veto6bar = "10";
				}
				if (thisbar==10){
				veto1plane = "nd.p1"; veto1bar = "12";
				veto2plane = "nd.p1"; veto2bar = "13";
				veto3plane = "nd.p2"; veto3bar = "9";
				veto4plane = "nd.p2"; veto4bar = "11";
				veto5plane = "nd.p2"; veto5bar = "11";
				veto6plane = "nd.p2"; veto6bar = "11";
				}
				if (thisbar==11){
				veto1plane = "nd.p1"; veto1bar = "13";
				veto2plane = "nd.p1"; veto2bar = "14";
				veto3plane = "nd.p1"; veto3bar = "15";
				veto4plane = "nd.p2"; veto4bar = "10";
				veto5plane = "nd.p2"; veto5bar = "12";
				veto6plane = "nd.p2"; veto6bar = "12";
				}
				if (thisbar==12){
				veto1plane = "nd.p1"; veto1bar = "14";
				veto2plane = "nd.p1"; veto2bar = "15";
				veto3plane = "nd.p1"; veto3bar = "16";
				veto4plane = "nd.p2"; veto4bar = "11";
				veto5plane = "nd.p2"; veto5bar = "13";
				veto6plane = "nd.p2"; veto6bar = "13";
				}
				if (thisbar==13){
				veto1plane = "nd.p1"; veto1bar = "16";
				veto2plane = "nd.p1"; veto2bar = "17";
				veto3plane = "nd.p2"; veto3bar = "12";
				veto4plane = "nd.p2"; veto4bar = "14";
				veto5plane = "nd.p2"; veto5bar = "14";
				veto6plane = "nd.p2"; veto6bar = "14";
				}
				if (thisbar==14){
				veto1plane = "nd.p1"; veto1bar = "17";
				veto2plane = "nd.p1"; veto2bar = "18";
				veto3plane = "nd.p2"; veto3bar = "13";
				veto4plane = "nd.p2"; veto4bar = "15";
				veto5plane = "nd.p2"; veto5bar = "15";
				veto6plane = "nd.p2"; veto6bar = "15";
				}
				if (thisbar==15){
				veto1plane = "nd.p1"; veto1bar = "18";
				veto2plane = "nd.p1"; veto2bar = "19";
				veto3plane = "nd.p1"; veto3bar = "20";
				veto4plane = "nd.p2"; veto4bar = "14";
				veto5plane = "nd.p2"; veto5bar = "16";
				veto6plane = "nd.p2"; veto6bar = "16";
				}
				if (thisbar==16){
				veto1plane = "nd.p1"; veto1bar = "19";
				veto2plane = "nd.p1"; veto2bar = "20";
				veto3plane = "nd.p1"; veto3bar = "21";
				veto4plane = "nd.p2"; veto4bar = "15";
				veto5plane = "nd.p2"; veto5bar = "17";
				veto6plane = "nd.p2"; veto6bar = "17";
				}
				if (thisbar==17){
				veto1plane = "nd.p1"; veto1bar = "21";
				veto2plane = "nd.p1"; veto2bar = "22";
				veto3plane = "nd.p2"; veto3bar = "16";
				veto4plane = "nd.p2"; veto4bar = "18";
				veto5plane = "nd.p2"; veto5bar = "18";
				veto6plane = "nd.p2"; veto6bar = "18";
				}
				if (thisbar==18){
				veto1plane = "nd.p1"; veto1bar = "22";
				veto2plane = "nd.p1"; veto2bar = "23";
				veto3plane = "nd.p1"; veto3bar = "23";
				veto4plane = "nd.p2"; veto4bar = "17";
				veto5plane = "nd.p2"; veto5bar = "19";
				veto6plane = "nd.p2"; veto6bar = "19";
				}
				if (thisbar==19){
				veto1plane = "nd.p1"; veto1bar = "23";
				veto2plane = "nd.p1"; veto2bar = "24";
				veto3plane = "nd.p1"; veto3bar = "25";
				veto4plane = "nd.p2"; veto4bar = "18";
				veto5plane = "nd.p2"; veto5bar = "20";
				veto6plane = "nd.p2"; veto6bar = "20";
				}
				if (thisbar==20){
				veto1plane = "nd.p1"; veto1bar = "24";
				veto2plane = "nd.p1"; veto2bar = "25";
				veto3plane = "nd.p1"; veto3bar = "26";
				veto4plane = "nd.p2"; veto4bar = "19";
				veto5plane = "nd.p2"; veto5bar = "21";
				veto6plane = "nd.p2"; veto6bar = "21";
				}
				if (thisbar==21){
				veto1plane = "nd.p1"; veto1bar = "26";
				veto2plane = "nd.p1"; veto2bar = "27";
				veto3plane = "nd.p1"; veto3bar = "27";
				veto4plane = "nd.p2"; veto4bar = "20";
				veto5plane = "nd.p2"; veto5bar = "22";
				veto6plane = "nd.p2"; veto6bar = "22";
				}
				if (thisbar==22){
				veto1plane = "nd.p1"; veto1bar = "27";
				veto2plane = "nd.p1"; veto2bar = "28";
				veto3plane = "nd.p1"; veto3bar = "28";
				veto4plane = "nd.p2"; veto4bar = "21";
				veto5plane = "nd.p2"; veto5bar = "23";
				veto6plane = "nd.p2"; veto6bar = "23";
				}
				if (thisbar==23){
				veto1plane = "nd.p1"; veto1bar = "28";
				veto2plane = "nd.p1"; veto2bar = "29";
				veto3plane = "nd.p1"; veto3bar = "29";
				veto4plane = "nd.p2"; veto4bar = "22";
				veto5plane = "nd.p2"; veto5bar = "22";
				veto6plane = "nd.p2"; veto6bar = "22";
				}
			}
			if (nplane==3){
				if (thisbar==0){
				veto1plane = "nd.p2"; veto1bar = "0";
				veto2plane = "nd.p2"; veto2bar = "1";
				veto3plane = "nd.p2"; veto3bar = "1";
				veto4plane = "nd.p2"; veto4bar = "1";
				veto5plane = "nd.p3"; veto5bar = "1";
				veto6plane = "nd.p3"; veto6bar = "1";
				}
				if (thisbar==1){
				veto1plane = "nd.p2"; veto1bar = "1";
				veto2plane = "nd.p2"; veto2bar = "2";
				veto3plane = "nd.p2"; veto3bar = "2";
				veto4plane = "nd.p2"; veto4bar = "2";
				veto5plane = "nd.p3"; veto5bar = "0";
				veto6plane = "nd.p3"; veto6bar = "2";
				}
				if (thisbar==2){
				veto1plane = "nd.p2"; veto1bar = "2";
				veto2plane = "nd.p2"; veto2bar = "3";
				veto3plane = "nd.p2"; veto3bar = "3";
				veto4plane = "nd.p2"; veto4bar = "3";
				veto5plane = "nd.p3"; veto5bar = "1";
				veto6plane = "nd.p3"; veto6bar = "3";
				}
				if (thisbar==3){
				veto1plane = "nd.p2"; veto1bar = "3";
				veto2plane = "nd.p2"; veto2bar = "4";
				veto3plane = "nd.p2"; veto3bar = "4";
				veto4plane = "nd.p2"; veto4bar = "4";
				veto5plane = "nd.p3"; veto5bar = "2";
				veto6plane = "nd.p3"; veto6bar = "4";
				}
				if (thisbar==4){
				veto1plane = "nd.p2"; veto1bar = "4";
				veto2plane = "nd.p2"; veto2bar = "5";
				veto3plane = "nd.p2"; veto3bar = "6";
				veto4plane = "nd.p2"; veto4bar = "6";
				veto5plane = "nd.p3"; veto5bar = "3";
				veto6plane = "nd.p3"; veto6bar = "5";
				}
				if (thisbar==5){
				veto1plane = "nd.p2"; veto1bar = "5";
				veto2plane = "nd.p2"; veto2bar = "6";
				veto3plane = "nd.p2"; veto3bar = "7";
				veto4plane = "nd.p2"; veto4bar = "7";
				veto5plane = "nd.p3"; veto5bar = "4";
				veto6plane = "nd.p3"; veto6bar = "6";
				}
				if (thisbar==6){
				veto1plane = "nd.p2"; veto1bar = "7";
				veto2plane = "nd.p2"; veto2bar = "8";
				veto3plane = "nd.p2"; veto3bar = "8";
				veto4plane = "nd.p2"; veto4bar = "8";
				veto5plane = "nd.p3"; veto5bar = "5";
				veto6plane = "nd.p3"; veto6bar = "7";
				}
				if (thisbar==7){
				veto1plane = "nd.p2"; veto1bar = "8";
				veto2plane = "nd.p2"; veto2bar = "9";
				veto3plane = "nd.p2"; veto3bar = "9";
				veto4plane = "nd.p2"; veto4bar = "9";
				veto5plane = "nd.p3"; veto5bar = "6";
				veto6plane = "nd.p3"; veto6bar = "8";
				}
				if (thisbar==8){
				veto1plane = "nd.p2"; veto1bar = "9";
				veto2plane = "nd.p2"; veto2bar = "10";
				veto3plane = "nd.p2"; veto3bar = "10";
				veto4plane = "nd.p2"; veto4bar = "10";
				veto5plane = "nd.p3"; veto5bar = "7";
				veto6plane = "nd.p3"; veto6bar = "9";
				}
				if (thisbar==9){
				veto1plane = "nd.p2"; veto1bar = "10";
				veto2plane = "nd.p2"; veto2bar = "11";
				veto3plane = "nd.p2"; veto3bar = "11";
				veto4plane = "nd.p2"; veto4bar = "11";
				veto5plane = "nd.p3"; veto5bar = "8";
				veto6plane = "nd.p3"; veto6bar = "10";
				}
				if (thisbar==10){
				veto1plane = "nd.p2"; veto1bar = "11";
				veto2plane = "nd.p2"; veto2bar = "12";
				veto3plane = "nd.p2"; veto3bar = "12";
				veto4plane = "nd.p2"; veto4bar = "12";
				veto5plane = "nd.p3"; veto5bar = "9";
				veto6plane = "nd.p3"; veto6bar = "11";
				}
				if (thisbar==11){
				veto1plane = "nd.p2"; veto1bar = "11";
				veto2plane = "nd.p2"; veto2bar = "12";
				veto3plane = "nd.p2"; veto3bar = "12";
				veto4plane = "nd.p2"; veto4bar = "12";
				veto5plane = "nd.p3"; veto5bar = "10";
				veto6plane = "nd.p3"; veto6bar = "12";
				}
				if (thisbar==12){
				veto1plane = "nd.p2"; veto1bar = "12";
				veto2plane = "nd.p2"; veto2bar = "13";
				veto3plane = "nd.p2"; veto3bar = "13";
				veto4plane = "nd.p2"; veto4bar = "13";
				veto5plane = "nd.p3"; veto5bar = "11";
				veto6plane = "nd.p3"; veto6bar = "13";
				}
				if (thisbar==13){
				veto1plane = "nd.p2"; veto1bar = "13";
				veto2plane = "nd.p2"; veto2bar = "14";
				veto3plane = "nd.p2"; veto3bar = "14";
				veto4plane = "nd.p2"; veto4bar = "14";
				veto5plane = "nd.p3"; veto5bar = "12";
				veto6plane = "nd.p3"; veto6bar = "14";
				}
				if (thisbar==14){
				veto1plane = "nd.p2"; veto1bar = "14";
				veto2plane = "nd.p2"; veto2bar = "15";
				veto3plane = "nd.p2"; veto3bar = "15";
				veto4plane = "nd.p2"; veto4bar = "15";
				veto5plane = "nd.p3"; veto5bar = "13";
				veto6plane = "nd.p3"; veto6bar = "15";
				}
				if (thisbar==15){
				veto1plane = "nd.p2"; veto1bar = "15";
				veto2plane = "nd.p2"; veto2bar = "16";
				veto3plane = "nd.p2"; veto3bar = "16";
				veto4plane = "nd.p2"; veto4bar = "16";
				veto5plane = "nd.p3"; veto5bar = "14";
				veto6plane = "nd.p3"; veto6bar = "16";
				}
				if (thisbar==16){
				veto1plane = "nd.p2"; veto1bar = "16";
				veto2plane = "nd.p2"; veto2bar = "17";
				veto3plane = "nd.p2"; veto3bar = "18";
				veto4plane = "nd.p2"; veto4bar = "18";
				veto5plane = "nd.p3"; veto5bar = "15";
				veto6plane = "nd.p3"; veto6bar = "17";
				}
				if (thisbar==17){
				veto1plane = "nd.p2"; veto1bar = "17";
				veto2plane = "nd.p2"; veto2bar = "18";
				veto3plane = "nd.p2"; veto3bar = "19";
				veto4plane = "nd.p2"; veto4bar = "19";
				veto5plane = "nd.p3"; veto5bar = "16";
				veto6plane = "nd.p3"; veto6bar = "18";
				}
				if (thisbar==18){
				veto1plane = "nd.p2"; veto1bar = "19";
				veto2plane = "nd.p2"; veto2bar = "20";
				veto3plane = "nd.p2"; veto3bar = "20";
				veto4plane = "nd.p2"; veto4bar = "20";
				veto5plane = "nd.p3"; veto5bar = "17";
				veto6plane = "nd.p3"; veto6bar = "19";
				}
				if (thisbar==19){
				veto1plane = "nd.p2"; veto1bar = "20";
				veto2plane = "nd.p2"; veto2bar = "21";
				veto3plane = "nd.p2"; veto3bar = "21";
				veto4plane = "nd.p2"; veto4bar = "21";
				veto5plane = "nd.p3"; veto5bar = "18";
				veto6plane = "nd.p3"; veto6bar = "20";
				}
				if (thisbar==20){
				veto1plane = "nd.p2"; veto1bar = "21";
				veto2plane = "nd.p2"; veto2bar = "22";
				veto3plane = "nd.p2"; veto3bar = "22";
				veto4plane = "nd.p2"; veto4bar = "22";
				veto5plane = "nd.p3"; veto5bar = "19";
				veto6plane = "nd.p3"; veto6bar = "21";
				}
				if (thisbar==21){
				veto1plane = "nd.p2"; veto1bar = "22";
				veto2plane = "nd.p2"; veto2bar = "23";
				veto3plane = "nd.p2"; veto3bar = "23";
				veto4plane = "nd.p2"; veto4bar = "23";
				veto5plane = "nd.p3"; veto5bar = "20";
				veto6plane = "nd.p3"; veto6bar = "20";
				}
			}	
			if (nplane==4){
				if (thisbar==0){
				veto1plane = "nd.p3"; veto1bar = "0";
				veto2plane = "nd.p3"; veto2bar = "1";
				veto3plane = "nd.p3"; veto3bar = "1";
				veto4plane = "nd.p3"; veto4bar = "1";
				veto5plane = "nd.p4"; veto5bar = "1";
				veto6plane = "nd.p4"; veto6bar = "1";
				}
				if (thisbar==1){
				veto1plane = "nd.p3"; veto1bar = "1";
				veto2plane = "nd.p3"; veto2bar = "2";
				veto3plane = "nd.p3"; veto3bar = "3";
				veto4plane = "nd.p3"; veto4bar = "3";
				veto5plane = "nd.p4"; veto5bar = "0";
				veto6plane = "nd.p4"; veto6bar = "2";
				}
				if (thisbar==2){
				veto1plane = "nd.p3"; veto1bar = "3";
				veto2plane = "nd.p3"; veto2bar = "4";
				veto3plane = "nd.p3"; veto3bar = "5";
				veto4plane = "nd.p3"; veto4bar = "5";
				veto5plane = "nd.p4"; veto5bar = "1";
				veto6plane = "nd.p4"; veto6bar = "3";
				}
				if (thisbar==3){
				veto1plane = "nd.p3"; veto1bar = "4";
				veto2plane = "nd.p3"; veto2bar = "5";
				veto3plane = "nd.p3"; veto3bar = "6";
				veto4plane = "nd.p3"; veto4bar = "6";
				veto5plane = "nd.p4"; veto5bar = "2";
				veto6plane = "nd.p4"; veto6bar = "4";
				}
				if (thisbar==4){
				veto1plane = "nd.p3"; veto1bar = "6";
				veto2plane = "nd.p3"; veto2bar = "7";
				veto3plane = "nd.p3"; veto3bar = "8";
				veto4plane = "nd.p3"; veto4bar = "8";
				veto5plane = "nd.p4"; veto5bar = "3";
				veto6plane = "nd.p4"; veto6bar = "5";
				}
				if (thisbar==5){
				veto1plane = "nd.p3"; veto1bar = "8";
				veto2plane = "nd.p3"; veto2bar = "9";
				veto3plane = "nd.p3"; veto3bar = "10";
				veto4plane = "nd.p3"; veto4bar = "11";
				veto5plane = "nd.p4"; veto5bar = "4";
				veto6plane = "nd.p4"; veto6bar = "6";
				}
				if (thisbar==6){
				veto1plane = "nd.p3"; veto1bar = "10";
				veto2plane = "nd.p3"; veto2bar = "11";
				veto3plane = "nd.p3"; veto3bar = "12";
				veto4plane = "nd.p3"; veto4bar = "13";
				veto5plane = "nd.p4"; veto5bar = "5";
				veto6plane = "nd.p4"; veto6bar = "7";
				}
				if (thisbar==7){
				veto1plane = "nd.p3"; veto1bar = "13";
				veto2plane = "nd.p3"; veto2bar = "14";
				veto3plane = "nd.p3"; veto3bar = "15";
				veto4plane = "nd.p3"; veto4bar = "15";
				veto5plane = "nd.p4"; veto5bar = "6";
				veto6plane = "nd.p4"; veto6bar = "8";
				}
				if (thisbar==8){
				veto1plane = "nd.p3"; veto1bar = "15";
				veto2plane = "nd.p3"; veto2bar = "16";
				veto3plane = "nd.p3"; veto3bar = "17";
				veto4plane = "nd.p3"; veto4bar = "17";
				veto5plane = "nd.p4"; veto5bar = "7";
				veto6plane = "nd.p4"; veto6bar = "9";
				}
				if (thisbar==9){
				veto1plane = "nd.p3"; veto1bar = "16";
				veto2plane = "nd.p3"; veto2bar = "17";
				veto3plane = "nd.p3"; veto3bar = "18";
				veto4plane = "nd.p3"; veto4bar = "18";
				veto5plane = "nd.p4"; veto5bar = "8";
				veto6plane = "nd.p4"; veto6bar = "10";
				}
				if (thisbar==10){
				veto1plane = "nd.p3"; veto1bar = "18";
				veto2plane = "nd.p3"; veto2bar = "19";
				veto3plane = "nd.p3"; veto3bar = "20";
				veto4plane = "nd.p3"; veto4bar = "20";
				veto5plane = "nd.p4"; veto5bar = "9";
				veto6plane = "nd.p4"; veto6bar = "11";
				}
				if (thisbar==11){
				veto1plane = "nd.p3"; veto1bar = "20";
				veto2plane = "nd.p3"; veto2bar = "21";
				veto3plane = "nd.p3"; veto3bar = "21";
				veto4plane = "nd.p3"; veto4bar = "21";
				veto5plane = "nd.p4"; veto5bar = "10";
				veto6plane = "nd.p4"; veto6bar = "10";
				}
			}
*/

		// This allVetos is going to be used when drawing the
		// image of the HAND as a searchable string to find
		// out if any particular bar is a veto bar or not.
		// Similarly with goodBar;
		// **************************************************
			TString allVetos = veto1plane;
			allVetos += ".";
			allVetos += veto1bar;
			allVetos += " ";
			allVetos += veto2plane;
			allVetos += ".";
			allVetos += veto2bar;
			allVetos += " ";
			allVetos += veto3plane;
			allVetos += ".";
			allVetos += veto3bar;
			allVetos += " ";
			allVetos += veto4plane;
			allVetos += ".";
			allVetos += veto4bar;
			allVetos += " ";
			allVetos += veto5plane;
			allVetos += ".";
			allVetos += veto5bar;
			allVetos += " ";
			allVetos += veto6plane;
			allVetos += ".";
			allVetos += veto6bar;
			allVetos += " ";


			TString goodBar = "nd.p";
			goodBar += nplane;
			goodBar += ".";
			goodBar += thisbar;
			goodBar += " ";
			cout << "Good Bar: " << goodBar << endl;
		// **************************************************


		// Below are the  veto cuts. They're split apart because I want
		// to be able to put this in a loop eventually to automize
		// the flow of data to histograms
			TString vetoTDCslSt = "NA.";
			vetoTDCslSt += veto1plane;
			vetoTDCslSt += ".lt_c[";
			vetoTDCslSt += veto1bar;
			vetoTDCslSt += "]<1 && NA.";
			vetoTDCslSt += veto2plane;
			vetoTDCslSt += ".lt_c[";
			vetoTDCslSt += veto2bar;
			vetoTDCslSt += "]<1 && NA.";
			vetoTDCslSt += veto3plane;
			vetoTDCslSt += ".lt_c[";
			vetoTDCslSt += veto3bar;
			vetoTDCslSt += "]<1 && NA.";
			vetoTDCslSt += veto4plane;
			vetoTDCslSt += ".lt_c[";
			vetoTDCslSt += veto4bar;
			vetoTDCslSt += "]<1 && NA.";
			vetoTDCslSt += veto5plane;
			vetoTDCslSt += ".lt_c[";
			vetoTDCslSt += veto5bar;
			vetoTDCslSt += "]<1 && NA.";
			vetoTDCslSt += veto6plane;
			vetoTDCslSt += ".lt_c[";
			vetoTDCslSt += veto6bar;
			vetoTDCslSt += "]<1";
			TCut vetoTDCsl = vetoTDCslSt;

			TString vetoTDCsrSt = "NA.";
			vetoTDCsrSt += veto1plane;
			vetoTDCsrSt += ".rt_c[";
			vetoTDCsrSt += veto1bar;
			vetoTDCsrSt += "]<1 && NA.";
			vetoTDCsrSt += veto2plane;
			vetoTDCsrSt += ".rt_c[";
			vetoTDCsrSt += veto2bar;
			vetoTDCsrSt += "]<1 && NA.";
			vetoTDCsrSt += veto3plane;
			vetoTDCsrSt += ".rt_c[";
			vetoTDCsrSt += veto3bar;
			vetoTDCsrSt += "]<1 && NA.";
			vetoTDCsrSt += veto4plane;
			vetoTDCsrSt += ".rt_c[";
			vetoTDCsrSt += veto4bar;
			vetoTDCsrSt += "]<1 && NA.";
			vetoTDCsrSt += veto5plane;
			vetoTDCsrSt += ".rt_c[";
			vetoTDCsrSt += veto5bar;
			vetoTDCsrSt += "]<1 && NA.";
			vetoTDCsrSt += veto6plane;
			vetoTDCsrSt += ".rt_c[";
			vetoTDCsrSt += veto6bar;
			vetoTDCsrSt += "]<1";
			TCut vetoTDCsr = vetoTDCsrSt;

			TCut vetoTDCs = vetoTDCsl && vetoTDCsr;

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
		//	TCanvas *hand = new TCanvas("hand","Neutron Data",1400,770); //x,y
			handpad01 =  new TPad("handpad01","handpad01",0.0000,0.0000,0.1000,1.0000,0,0,0);
			handpad02 =  new TPad("handpad02","handpad02",0.1000,0.5000,1.0000,1.0000,0,0,0);
			handpad03 =  new TPad("handpad03","handpad03",0.1000,0.0000,1.0000,0.5000,0,0,0);
//			handpad04 =  new TPad("handpad04","handpad04",0.4000,0.5000,0.7000,1.0000,0,0,0);
//			handpad05 =  new TPad("handpad05","handpad05",0.7000,0.5000,1.0000,1.0000,0,0,0);
//			handpad06 =  new TPad("handpad06","handpad06",0.4000,0.0000,0.7000,0.5000,0,0,0);
//			handpad07 =  new TPad("handpad07","handpad07",0.7000,0.0000,1.0000,0.5000,0,0,0);
			handpad01->Draw(); handpad02->Draw(); handpad03->Draw();
//			 handpad04->Draw(); handpad05->Draw();
//			handpad06->Draw(); handpad07->Draw();

			// This huge block is to draw the HAND. Data follows well below here.
			handpad01->cd();
			TString theBigTitle = "Run # ";
			theBigTitle += HeRunNumber;
			TPaveLabel *bigTitle = new TPaveLabel(0.2165,0.9600,0.9150,0.9900,theBigTitle);
			bigTitle->Draw();
			// This set is for Plane Veto
			TPaveLabel *p0b10 = new TPaveLabel(0.1835,0.6650,0.2165,0.6980,"10");
			p0b10->SetFillColor(38);
			if (allVetos.Contains("veto.10")) p0b10->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.10")) p0b10->SetFillColor(3); 
			p0b10->Draw();
			TPaveLabel *p0b11 = new TPaveLabel(0.1835,0.6320,0.2165,0.6650,"11");
			p0b11->SetFillColor(38);
			if (allVetos.Contains("veto.11")) p0b11->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.11")) p0b11->SetFillColor(3); 
			p0b11->Draw();
			TPaveLabel *p0b12 = new TPaveLabel(0.1835,0.5990,0.2165,0.6320,"12");
			p0b12->SetFillColor(38);
			if (allVetos.Contains("veto.12")) p0b12->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.12")) p0b12->SetFillColor(3); 
			p0b12->Draw();
			TPaveLabel *p0b13 = new TPaveLabel(0.1835,0.5660,0.2165,0.5990,"13");
			p0b13->SetFillColor(38);
			if (allVetos.Contains("veto.13")) p0b13->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.13")) p0b13->SetFillColor(3); 
			p0b13->Draw();
			TPaveLabel *p0b14 = new TPaveLabel(0.1835,0.5330,0.2165,0.5660,"14");
			p0b14->SetFillColor(38);
			if (allVetos.Contains("veto.14")) p0b14->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.14")) p0b14->SetFillColor(3); 
			p0b14->Draw();
			TPaveLabel *p0b15 = new TPaveLabel(0.1835,0.5000,0.2165,0.5330,"15");
			p0b15->SetFillColor(38);
			if (allVetos.Contains("veto.15")) p0b15->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.15")) p0b15->SetFillColor(3); 
			p0b15->Draw();
			TPaveLabel *p0b16 = new TPaveLabel(0.1835,0.4670,0.2165,0.5000,"16");
			p0b16->SetFillColor(38);
			if (allVetos.Contains("veto.16")) p0b16->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.16")) p0b16->SetFillColor(3); 
			p0b16->Draw();
			TPaveLabel *p0b17 = new TPaveLabel(0.1835,0.4340,0.2165,0.4670,"17");
			p0b17->SetFillColor(38);
			if (allVetos.Contains("veto.17")) p0b17->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.17")) p0b17->SetFillColor(3); 
			p0b17->Draw();
			TPaveLabel *p0b18 = new TPaveLabel(0.1835,0.4010,0.2165,0.4340,"18");
			p0b18->SetFillColor(38);
			if (allVetos.Contains("veto.18")) p0b18->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.18")) p0b18->SetFillColor(3); 
			p0b18->Draw();
			TPaveLabel *p0b19 = new TPaveLabel(0.1835,0.3680,0.2165,0.4010,"19");
			p0b19->SetFillColor(38);
			if (allVetos.Contains("veto.19")) p0b19->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.19")) p0b19->SetFillColor(3); 
			p0b19->Draw();
			TPaveLabel *p0b20 = new TPaveLabel(0.1835,0.3350,0.2165,0.3680,"20");
			p0b20->SetFillColor(38);
			if (allVetos.Contains("veto.20")) p0b20->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.20")) p0b20->SetFillColor(3); 
			p0b20->Draw();
			TPaveLabel *p0b21 = new TPaveLabel(0.1835,0.3020,0.2165,0.3350,"21");
			p0b21->SetFillColor(38);
			if (allVetos.Contains("veto.21")) p0b21->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.21")) p0b21->SetFillColor(3); 
			p0b21->Draw();
			TPaveLabel *p0b00 = new TPaveLabel(0.2165,0.9170,0.2495,0.9500,"00");
			p0b00->SetFillColor(38);
			if (allVetos.Contains("veto.0")) p0b00->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.0")) p0b00->SetFillColor(3); 
			p0b00->Draw();
			TPaveLabel *p0b01 = new TPaveLabel(0.2165,0.8840,0.2495,0.9170,"01");
			p0b01->SetFillColor(38);
			if (allVetos.Contains("veto.1 ")) p0b01->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.1 ")) p0b01->SetFillColor(3); 
			p0b01->Draw();
			TPaveLabel *p0b02 = new TPaveLabel(0.2165,0.8510,0.2495,0.8840,"02");
			p0b02->SetFillColor(38);
			if (allVetos.Contains("veto.2 ")) p0b02->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.2 ")) p0b02->SetFillColor(3); 
			p0b02->Draw();
			TPaveLabel *p0b03 = new TPaveLabel(0.2165,0.8180,0.2495,0.8510,"03");
			p0b03->SetFillColor(38);
			if (allVetos.Contains("veto.3 ")) p0b03->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.3 ")) p0b03->SetFillColor(3); 
			p0b03->Draw();
			TPaveLabel *p0b04 = new TPaveLabel(0.2165,0.7850,0.2495,0.8180,"04");
			p0b04->SetFillColor(38);
			if (allVetos.Contains("veto.4")) p0b04->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.4")) p0b04->SetFillColor(3); 
			p0b04->Draw();
			TPaveLabel *p0b05 = new TPaveLabel(0.2165,0.7520,0.2495,0.7850,"05");
			p0b05->SetFillColor(38);
			if (allVetos.Contains("veto.5")) p0b105->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.5")) p0b05->SetFillColor(3); 
			p0b05->Draw();
			TPaveLabel *p0b06 = new TPaveLabel(0.2165,0.7190,0.2495,0.7520,"06");
			p0b06->SetFillColor(38);
			if (allVetos.Contains("veto.6")) p0b06->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.6")) p0b06->SetFillColor(3); 
			p0b06->Draw();
			TPaveLabel *p0b07 = new TPaveLabel(0.2165,0.6860,0.2495,0.7190,"07");
			p0b07->SetFillColor(38);
			if (allVetos.Contains("veto.7")) p0b07->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.7")) p0b07->SetFillColor(3); 
			p0b07->Draw();
			TPaveLabel *p0b08 = new TPaveLabel(0.2165,0.6530,0.2495,0.6860,"08");
			p0b08->SetFillColor(38);
			if (allVetos.Contains("veto.8")) p0b08->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.8")) p0b08->SetFillColor(3); 
			p0b08->Draw();
			TPaveLabel *p0b09 = new TPaveLabel(0.2165,0.6200,0.2495,0.6530,"09");
			p0b09->SetFillColor(38);
			if (allVetos.Contains("veto.9")) p0b09->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.9")) p0b09->SetFillColor(3); 
			p0b09->Draw();
			TPaveLabel *p0b22 = new TPaveLabel(0.2165,0.3470,0.2495,0.3800,"22");
			p0b22->SetFillColor(38);
			if (allVetos.Contains("veto.22")) p0b22->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.22")) p0b22->SetFillColor(3); 
			p0b22->Draw();
			TPaveLabel *p0b23 = new TPaveLabel(0.2165,0.3140,0.2495,0.3470,"23");
			p0b23->SetFillColor(38);
			if (allVetos.Contains("veto.23")) p0b23->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.23")) p0b23->SetFillColor(3); 
			p0b23->Draw();
			TPaveLabel *p0b24 = new TPaveLabel(0.2165,0.2810,0.2495,0.3140,"24");
			p0b24->SetFillColor(38);
			if (allVetos.Contains("veto.24")) p0b24->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.24")) p0b24->SetFillColor(3); 
			p0b24->Draw();
			TPaveLabel *p0b25 = new TPaveLabel(0.2165,0.2480,0.2495,0.2810,"25");
			p0b25->SetFillColor(38);
			if (allVetos.Contains("veto.25")) p0b25->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.25")) p0b25->SetFillColor(3); 
			p0b25->Draw();
			TPaveLabel *p0b26 = new TPaveLabel(0.2165,0.2150,0.2495,0.2480,"26");
			p0b26->SetFillColor(38);
			if (allVetos.Contains("veto.26")) p0b26->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.26")) p0b26->SetFillColor(3); 
			p0b26->Draw();
			TPaveLabel *p0b27 = new TPaveLabel(0.2165,0.1820,0.2495,0.2150,"27");
			p0b27->SetFillColor(38);
			if (allVetos.Contains("veto.27")) p0b27->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.27")) p0b27->SetFillColor(3); 
			p0b27->Draw();
			TPaveLabel *p0b28 = new TPaveLabel(0.2165,0.1490,0.2495,0.1820,"28");
			p0b28->SetFillColor(38);
			if (allVetos.Contains("veto.28")) p0b28->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.28")) p0b28->SetFillColor(3); 
			p0b28->Draw();
			TPaveLabel *p0b29 = new TPaveLabel(0.2165,0.1160,0.2495,0.1490,"29");
			p0b29->SetFillColor(38);
			if (allVetos.Contains("veto.29")) p0b29->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.29")) p0b29->SetFillColor(3); 
			p0b29->Draw();
			TPaveLabel *p0b30 = new TPaveLabel(0.2165,0.0830,0.2495,0.1160,"29");
			p0b30->SetFillColor(38);
			if (allVetos.Contains("veto.30")) p0b30->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.30")) p0b30->SetFillColor(3); 
			p0b30->Draw();
			TPaveLabel *p0b31 = new TPaveLabel(0.2165,0.0500,0.2495,0.0830,"31");
			p0b31->SetFillColor(38);
			if (allVetos.Contains("veto.31")) p0b31->SetFillColor(2); 
			if (goodBar.Contains("nd.p0.31")) p0b31->SetFillColor(3); 
			p0b31->Draw();

			// This set is for Plane 1
			TPaveLabel *p1b00 = new TPaveLabel(0.2525,0.9200,0.4175,0.9500,"00");
			p1b00->SetFillColor(38);
			if (allVetos.Contains("nd.p1.0")) p1b00->SetFillColor(2);
			if (goodBar.Contains("nd.p1.0")) p1b00->SetFillColor(3);
			p1b00->Draw();
			TPaveLabel *p1b01 = new TPaveLabel(0.2525,0.8900,0.4175,0.9200,"01");
			p1b01->SetFillColor(38);
			if (allVetos.Contains("nd.p1.1 ")) p1b01->SetFillColor(2);
			if (goodBar.Contains("nd.p1.1 ")) p1b01->SetFillColor(3);
			p1b01->Draw();
			TPaveLabel *p1b02 = new TPaveLabel(0.2525,0.8600,0.4175,0.8900,"02");
			p1b02->SetFillColor(38);
			if (allVetos.Contains("nd.p1.2 ")) p1b02->SetFillColor(2);
			if (goodBar.Contains("nd.p1.2 ")) p1b02->SetFillColor(3);
			p1b02->Draw();
			TPaveLabel *p1b03 = new TPaveLabel(0.2525,0.8300,0.4175,0.8600,"03");
			p1b03->SetFillColor(38);
			if (allVetos.Contains("nd.p1.3 ")) p1b03->SetFillColor(2);
			if (goodBar.Contains("nd.p1.3 ")) p1b03->SetFillColor(3);
			p1b03->Draw();
			TPaveLabel *p1b04 = new TPaveLabel(0.2525,0.8000,0.4175,0.8300,"04");
			p1b04->SetFillColor(38);
			if (allVetos.Contains("nd.p1.4 ")) p1b04->SetFillColor(2);
			if (goodBar.Contains("nd.p1.4 ")) p1b04->SetFillColor(3);
			p1b04->Draw();
			TPaveLabel *p1b05 = new TPaveLabel(0.2525,0.7700,0.4175,0.8000,"05");
			p1b05->SetFillColor(38);
			if (allVetos.Contains("nd.p1.5 ")) p1b05->SetFillColor(2);
			if (goodBar.Contains("nd.p1.5 ")) p1b05->SetFillColor(3);
			p1b05->Draw();
			TPaveLabel *p1b06 = new TPaveLabel(0.2525,0.7400,0.4175,0.7700,"06");
			p1b06->SetFillColor(38);
			if (allVetos.Contains("nd.p1.6 ")) p1b06->SetFillColor(2);
			if (goodBar.Contains("nd.p1.6 ")) p1b06->SetFillColor(3);
			p1b06->Draw();
			TPaveLabel *p1b07 = new TPaveLabel(0.2525,0.7100,0.4175,0.7400,"07");
			p1b07->SetFillColor(38);
			if (allVetos.Contains("nd.p1.7 ")) p1b07->SetFillColor(2);
			if (goodBar.Contains("nd.p1.7 ")) p1b07->SetFillColor(3);
			p1b07->Draw();
			TPaveLabel *p1b08 = new TPaveLabel(0.2525,0.6800,0.4175,0.7100,"08");
			p1b08->SetFillColor(38);
			if (allVetos.Contains("nd.p1.8 ")) p1b08->SetFillColor(2);
			if (goodBar.Contains("nd.p1.8 ")) p1b08->SetFillColor(3);
			p1b08->Draw();
			TPaveLabel *p1b09 = new TPaveLabel(0.2525,0.6500,0.4175,0.6800,"09");
			p1b09->SetFillColor(38);
			if (allVetos.Contains("nd.p1.9 ")) p1b09->SetFillColor(2);
			if (goodBar.Contains("nd.p1.9 ")) p1b09->SetFillColor(3);
			p1b09->Draw();
			TPaveLabel *p1b10 = new TPaveLabel(0.2525,0.6200,0.4175,0.6500,"10");
			p1b10->SetFillColor(38);
			if (allVetos.Contains("nd.p1.10")) p1b10->SetFillColor(2);
			if (goodBar.Contains("nd.p1.10")) p1b10->SetFillColor(3);
			p1b10->Draw();
			TPaveLabel *p1b11 = new TPaveLabel(0.2525,0.5900,0.4175,0.6200,"11");
			p1b11->SetFillColor(38);
			if (allVetos.Contains("nd.p1.11")) p1b11->SetFillColor(2);
			if (goodBar.Contains("nd.p1.11")) p1b11->SetFillColor(3);
			p1b11->Draw();
			TPaveLabel *p1b12 = new TPaveLabel(0.2525,0.5600,0.4175,0.5900,"12");
			p1b12->SetFillColor(38);
			if (allVetos.Contains("nd.p1.12")) p1b12->SetFillColor(2);
			if (goodBar.Contains("nd.p1.12")) p1b12->SetFillColor(3);
			p1b12->Draw();
			TPaveLabel *p1b13 = new TPaveLabel(0.2525,0.5300,0.4175,0.5600,"13");
			p1b13->SetFillColor(38);
			if (allVetos.Contains("nd.p1.13")) p1b13->SetFillColor(2);
			if (goodBar.Contains("nd.p1.13")) p1b13->SetFillColor(3);
			p1b13->Draw();
			TPaveLabel *p1b14 = new TPaveLabel(0.2525,0.5000,0.4175,0.5300,"14");
			p1b14->SetFillColor(38);
			if (allVetos.Contains("nd.p1.14")) p1b14->SetFillColor(2); 
			if (goodBar.Contains("nd.p1.14")) p1b14->SetFillColor(3); 
			p1b14->Draw();
			TPaveLabel *p1b15 = new TPaveLabel(0.2525,0.4700,0.4175,0.5000,"15");
			p1b15->SetFillColor(38);
			if (allVetos.Contains("nd.p1.15")) p1b15->SetFillColor(2);
			if (goodBar.Contains("nd.p1.15")) p1b15->SetFillColor(3);
			p1b15->Draw();
			TPaveLabel *p1b16 = new TPaveLabel(0.2525,0.4400,0.4175,0.4700,"16");
			p1b16->SetFillColor(38);
			if (allVetos.Contains("nd.p1.16")) p1b16->SetFillColor(2);
			if (goodBar.Contains("nd.p1.16")) p1b16->SetFillColor(3);
			p1b16->Draw();
			TPaveLabel *p1b17 = new TPaveLabel(0.2525,0.4100,0.4175,0.4400,"17");
			p1b17->SetFillColor(38);
			if (allVetos.Contains("nd.p1.17")) p1b17->SetFillColor(2);
			if (goodBar.Contains("nd.p1.17")) p1b17->SetFillColor(3);
			p1b17->Draw();
			TPaveLabel *p1b18 = new TPaveLabel(0.2525,0.3800,0.4175,0.4100,"18");
			p1b18->SetFillColor(38);
			if (allVetos.Contains("nd.p1.18")) p1b18->SetFillColor(2);
			if (goodBar.Contains("nd.p1.18")) p1b18->SetFillColor(3);
			p1b18->Draw();
			TPaveLabel *p1b19 = new TPaveLabel(0.2525,0.3500,0.4175,0.3800,"19");
			p1b19->SetFillColor(38);
			if (allVetos.Contains("nd.p1.19")) p1b19->SetFillColor(2);
			if (goodBar.Contains("nd.p1.19")) p1b19->SetFillColor(3);
			p1b19->Draw();
			TPaveLabel *p1b20 = new TPaveLabel(0.2525,0.3200,0.4175,0.3500,"20");
			p1b20->SetFillColor(38);
			if (allVetos.Contains("nd.p1.20")) p1b20->SetFillColor(2);
			if (goodBar.Contains("nd.p1.20")) p1b20->SetFillColor(3);
			p1b20->Draw();
			TPaveLabel *p1b21 = new TPaveLabel(0.2525,0.2900,0.4175,0.3200,"21");
			p1b21->SetFillColor(38);
			if (allVetos.Contains("nd.p1.21")) p1b21->SetFillColor(2);
			if (goodBar.Contains("nd.p1.21")) p1b21->SetFillColor(3);
			p1b21->Draw();
			TPaveLabel *p1b22 = new TPaveLabel(0.2525,0.2600,0.4175,0.2900,"22");
			p1b22->SetFillColor(38);
			if (allVetos.Contains("nd.p1.22")) p1b22->SetFillColor(2);
			if (goodBar.Contains("nd.p1.22")) p1b22->SetFillColor(3);
			p1b22->Draw();
			TPaveLabel *p1b23 = new TPaveLabel(0.2525,0.2300,0.4175,0.2600,"23");
			p1b23->SetFillColor(38);
			if (allVetos.Contains("nd.p1.23")) p1b23->SetFillColor(2);
			if (goodBar.Contains("nd.p1.23")) p1b23->SetFillColor(3);
			p1b23->Draw();
			TPaveLabel *p1b24 = new TPaveLabel(0.2525,0.2000,0.4175,0.2300,"24");
			p1b24->SetFillColor(38);
			if (allVetos.Contains("nd.p1.24")) p1b24->SetFillColor(2);
			if (goodBar.Contains("nd.p1.24")) p1b24->SetFillColor(3);
			p1b24->Draw();
			TPaveLabel *p1b25 = new TPaveLabel(0.2525,0.1700,0.4175,0.2000,"25");
			p1b25->SetFillColor(38);
			if (allVetos.Contains("nd.p1.25")) p1b25->SetFillColor(2);
			if (goodBar.Contains("nd.p1.25")) p1b25->SetFillColor(3);
			p1b25->Draw();
			TPaveLabel *p1b26 = new TPaveLabel(0.2525,0.1400,0.4175,0.1700,"26");
			p1b26->SetFillColor(38);
			if (allVetos.Contains("nd.p1.26")) p1b26->SetFillColor(2);
			if (goodBar.Contains("nd.p1.26")) p1b26->SetFillColor(3);
			p1b26->Draw();
			TPaveLabel *p1b27 = new TPaveLabel(0.2525,0.1100,0.4175,0.1400,"27");
			p1b27->SetFillColor(38);
			if (allVetos.Contains("nd.p1.27")) p1b27->SetFillColor(2);
			if (goodBar.Contains("nd.p1.27")) p1b27->SetFillColor(3);
			p1b27->Draw();
			TPaveLabel *p1b28 = new TPaveLabel(0.2525,0.0800,0.4175,0.1100,"28");
			p1b28->SetFillColor(38);
			if (allVetos.Contains("nd.p1.28")) p1b28->SetFillColor(2);
			if (goodBar.Contains("nd.p1.28")) p1b28->SetFillColor(3);
			p1b28->Draw();
			TPaveLabel *p1b29 = new TPaveLabel(0.2525,0.0500,0.4175,0.0800,"29");
			p1b29->SetFillColor(38);
			if (allVetos.Contains("nd.p1.29")) p1b29->SetFillColor(2);
			if (goodBar.Contains("nd.p1.29")) p1b29->SetFillColor(3);
			p1b29->Draw();

			// This set is for Plane 2
			TPaveLabel *p2b00 = new TPaveLabel(0.4200,0.9125,0.5850,0.9500,"00");
			p2b00->SetFillColor(38);
			if (allVetos.Contains("nd.p2.0 ")) p2b00->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.0 ")) p2b00->SetFillColor(3);
			p2b00->Draw();
			TPaveLabel *p2b01 = new TPaveLabel(0.4200,0.8750,0.5850,0.9125,"01");
			p2b01->SetFillColor(38);
			if (allVetos.Contains("nd.p2.1 ")) p2b01->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.1 ")) p2b01->SetFillColor(3);
			p2b01->Draw();
			TPaveLabel *p2b02 = new TPaveLabel(0.4200,0.8375,0.5850,0.8750,"02");
			p2b02->SetFillColor(38);
			if (allVetos.Contains("nd.p2.2 ")) p2b02->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.2 ")) p2b02->SetFillColor(3);
			p2b02->Draw();
			TPaveLabel *p2b03 = new TPaveLabel(0.4200,0.8000,0.5850,0.8375,"03");
			p2b03->SetFillColor(38);
			if (allVetos.Contains("nd.p2.3 ")) p2b03->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.3 ")) p2b03->SetFillColor(3);
			p2b03->Draw();
			TPaveLabel *p2b04 = new TPaveLabel(0.4200,0.7625,0.5850,0.8000,"04");
			p2b04->SetFillColor(38);
			if (allVetos.Contains("nd.p2.4 ")) p2b04->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.4 ")) p2b04->SetFillColor(3);
			p2b04->Draw();
			TPaveLabel *p2b05 = new TPaveLabel(0.4200,0.7250,0.5850,0.7625,"05");
			p2b05->SetFillColor(38);
			if (allVetos.Contains("nd.p2.5 ")) p2b05->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.5 ")) p2b05->SetFillColor(3);
			p2b05->Draw();
			TPaveLabel *p2b06 = new TPaveLabel(0.4200,0.6875,0.5850,0.7250,"06");
			p2b06->SetFillColor(38);
			if (allVetos.Contains("nd.p2.6 ")) p2b06->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.6 ")) p2b06->SetFillColor(3);
			p2b06->Draw();
			TPaveLabel *p2b07 = new TPaveLabel(0.4200,0.6500,0.5850,0.6875,"07");
			p2b07->SetFillColor(38);
			if (allVetos.Contains("nd.p2.7 ")) p2b07->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.7 ")) p2b07->SetFillColor(3);
			p2b07->Draw();
			TPaveLabel *p2b08 = new TPaveLabel(0.4200,0.6125,0.5850,0.6500,"08");
			p2b08->SetFillColor(38);
			if (allVetos.Contains("nd.p2.8 ")) p2b08->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.8 ")) p2b08->SetFillColor(3);
			p2b08->Draw();
			TPaveLabel *p2b09 = new TPaveLabel(0.4200,0.5750,0.5850,0.6125,"09");
			p2b09->SetFillColor(38);
			if (allVetos.Contains("nd.p2.9 ")) p2b09->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.9 ")) p2b09->SetFillColor(3);
			p2b09->Draw();
			TPaveLabel *p2b10 = new TPaveLabel(0.4200,0.5375,0.5850,0.5750,"10");
			p2b10->SetFillColor(38);
			if (allVetos.Contains("nd.p2.10")) p2b10->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.10")) p2b10->SetFillColor(3);
			p2b10->Draw();
			TPaveLabel *p2b11 = new TPaveLabel(0.4200,0.5000,0.5850,0.5375,"11");
			p2b11->SetFillColor(38);
			if (allVetos.Contains("nd.p2.11")) p2b11->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.11")) p2b11->SetFillColor(3);
			p2b11->Draw();
			TPaveLabel *p2b12 = new TPaveLabel(0.4200,0.4625,0.5850,0.5000,"12");
			p2b12->SetFillColor(38);
			if (allVetos.Contains("nd.p2.12")) p2b12->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.12")) p2b12->SetFillColor(3);
			p2b12->Draw();
			TPaveLabel *p2b13 = new TPaveLabel(0.4200,0.4250,0.5850,0.4625,"13");
			p2b13->SetFillColor(38);
			if (allVetos.Contains("nd.p2.13")) p2b13->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.13")) p2b13->SetFillColor(3);
			p2b13->Draw();
			TPaveLabel *p2b14 = new TPaveLabel(0.4200,0.3875,0.5850,0.4250,"14");
			p2b14->SetFillColor(38);
			if (allVetos.Contains("nd.p2.14")) p2b14->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.14")) p2b14->SetFillColor(3);
			p2b14->Draw();
			TPaveLabel *p2b15 = new TPaveLabel(0.4200,0.3500,0.5850,0.3875,"15");
			p2b15->SetFillColor(38);
			if (allVetos.Contains("nd.p2.15")) p2b15->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.15")) p2b15->SetFillColor(3);
			p2b15->Draw();
			TPaveLabel *p2b16 = new TPaveLabel(0.4200,0.3125,0.5850,0.3500,"16");
			p2b16->SetFillColor(38);
			if (allVetos.Contains("nd.p2.16")) p2b16->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.16")) p2b16->SetFillColor(3);
			p2b16->Draw();
			TPaveLabel *p2b17 = new TPaveLabel(0.4200,0.2750,0.5850,0.3125,"17");
			p2b17->SetFillColor(38);
			if (allVetos.Contains("nd.p2.17")) p2b17->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.17")) p2b17->SetFillColor(3);
			p2b17->Draw();
			TPaveLabel *p2b18 = new TPaveLabel(0.4200,0.2375,0.5850,0.2750,"18");
			p2b18->SetFillColor(38);
			if (allVetos.Contains("nd.p2.18")) p2b18->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.18")) p2b18->SetFillColor(3);
			p2b18->Draw();
			TPaveLabel *p2b19 = new TPaveLabel(0.4200,0.2000,0.5850,0.2375,"19");
			p2b19->SetFillColor(38);
			if (allVetos.Contains("nd.p2.19")) p2b19->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.19")) p2b19->SetFillColor(3);
			p2b19->Draw();
			TPaveLabel *p2b20 = new TPaveLabel(0.4200,0.1625,0.5850,0.2000,"20");
			p2b20->SetFillColor(38);
			if (allVetos.Contains("nd.p2.20")) p2b20->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.20")) p2b20->SetFillColor(3);
			p2b20->Draw();
			TPaveLabel *p2b21 = new TPaveLabel(0.4200,0.1250,0.5850,0.1625,"21");
			p2b21->SetFillColor(38);
			if (allVetos.Contains("nd.p2.21")) p2b21->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.21")) p2b21->SetFillColor(3);
			p2b21->Draw();
			TPaveLabel *p2b22 = new TPaveLabel(0.4200,0.0875,0.5850,0.1250,"22");
			p2b22->SetFillColor(38);
			if (allVetos.Contains("nd.p2.22")) p2b22->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.22")) p2b22->SetFillColor(3);
			p2b22->Draw();
			TPaveLabel *p2b23 = new TPaveLabel(0.4200,0.0500,0.5850,0.0875,"23");
			p2b23->SetFillColor(38);
			if (allVetos.Contains("nd.p2.23")) p2b23->SetFillColor(2);
			if ( goodBar.Contains("nd.p2.23")) p2b23->SetFillColor(3);
			p2b23->Draw();
			
			// This set is for Plane 3
			TPaveLabel *p3b00 = new TPaveLabel(0.5850,0.9050,0.7500,0.9500,"00");
			p3b00->SetFillColor(38);
			if (allVetos.Contains("nd.p3.0 ")) p3b00->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.0 ")) p3b00->SetFillColor(3);
			p3b00->Draw();
			TPaveLabel *p3b01 = new TPaveLabel(0.5850,0.8600,0.7500,0.9050,"01");
			p3b01->SetFillColor(38);
			if (allVetos.Contains("nd.p3.1 ")) p3b01->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.1 ")) p3b01->SetFillColor(3);
			p3b01->Draw();
			TPaveLabel *p3b02 = new TPaveLabel(0.5850,0.8150,0.7500,0.8600,"02");
			p3b02->SetFillColor(38);
			if (allVetos.Contains("nd.p3.2 ")) p3b02->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.2 ")) p3b02->SetFillColor(3);
			p3b02->Draw();
			TPaveLabel *p3b03 = new TPaveLabel(0.5850,0.7700,0.7500,0.8150,"03");
			p3b03->SetFillColor(38);
			if (allVetos.Contains("nd.p3.3 ")) p3b03->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.3 ")) p3b03->SetFillColor(3);
			p3b03->Draw();
			TPaveLabel *p3b04 = new TPaveLabel(0.5850,0.7250,0.7500,0.7700,"04");
			p3b04->SetFillColor(38);
			if (allVetos.Contains("nd.p3.4 ")) p3b04->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.4 ")) p3b04->SetFillColor(3);
			p3b04->Draw();
			TPaveLabel *p3b05 = new TPaveLabel(0.5850,0.6800,0.7500,0.7250,"05");
			p3b05->SetFillColor(38);
			if (allVetos.Contains("nd.p3.5 ")) p3b05->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.5 ")) p3b05->SetFillColor(3);
			p3b05->Draw();
			TPaveLabel *p3b06 = new TPaveLabel(0.5850,0.6425,0.7500,0.6800,"06");
			p3b06->SetFillColor(38);
			if (allVetos.Contains("nd.p3.6 ")) p3b06->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.6 ")) p3b06->SetFillColor(3);
			p3b06->Draw();
			TPaveLabel *p3b07 = new TPaveLabel(0.5850,0.6050,0.7500,0.6425,"07");
			p3b07->SetFillColor(38);
			if (allVetos.Contains("nd.p3.7 ")) p3b07->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.7 ")) p3b07->SetFillColor(3);
			p3b07->Draw();
			TPaveLabel *p3b08 = new TPaveLabel(0.5850,0.5675,0.7500,0.6050,"08");
			p3b08->SetFillColor(38);
			if (allVetos.Contains("nd.p3.8 ")) p3b08->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.8 ")) p3b08->SetFillColor(3);
			p3b08->Draw();
			TPaveLabel *p3b09 = new TPaveLabel(0.5850,0.5300,0.7500,0.5675,"09");
			p3b09->SetFillColor(38);
			if (allVetos.Contains("nd.p3.9 ")) p3b09->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.9 ")) p3b09->SetFillColor(3);
			p3b09->Draw();
			TPaveLabel *p3b10 = new TPaveLabel(0.5850,0.5000,0.7500,0.5300,"10");
			p3b10->SetFillColor(38);
			if (allVetos.Contains("nd.p3.10")) p3b10->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.10")) p3b10->SetFillColor(3);
			p3b10->Draw();
			TPaveLabel *p3b11 = new TPaveLabel(0.5850,0.4700,0.7500,0.5000,"11");
			p3b11->SetFillColor(38);
			if (allVetos.Contains("nd.p3.11")) p3b11->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.11")) p3b11->SetFillColor(3);
			p3b11->Draw();
			TPaveLabel *p3b12 = new TPaveLabel(0.5850,0.4325,0.7500,0.4700,"12");
			p3b12->SetFillColor(38);
			if (allVetos.Contains("nd.p3.12")) p3b12->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.12")) p3b12->SetFillColor(3);
			p3b12->Draw();
			TPaveLabel *p3b13 = new TPaveLabel(0.5850,0.3950,0.7500,0.4325,"13");
			p3b13->SetFillColor(38);
			if (allVetos.Contains("nd.p3.13")) p3b13->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.13")) p3b13->SetFillColor(3);
			p3b13->Draw();
			TPaveLabel *p3b14 = new TPaveLabel(0.5850,0.3575,0.7500,0.3950,"14");
			p3b14->SetFillColor(38);
			if (allVetos.Contains("nd.p3.14")) p3b14->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.14")) p3b14->SetFillColor(3);
			p3b14->Draw();
			TPaveLabel *p3b15 = new TPaveLabel(0.5850,0.3200,0.7500,0.3575,"15");
			p3b15->SetFillColor(38);
			if (allVetos.Contains("nd.p3.15")) p3b15->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.15")) p3b15->SetFillColor(3);
			p3b15->Draw();
			TPaveLabel *p3b16 = new TPaveLabel(0.5850,0.2750,0.7500,0.3200,"16");
			p3b16->SetFillColor(38);
			if (allVetos.Contains("nd.p3.16")) p3b16->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.16")) p3b16->SetFillColor(3);
			p3b16->Draw();
			TPaveLabel *p3b17 = new TPaveLabel(0.5850,0.2300,0.7500,0.2750,"17");
			p3b17->SetFillColor(38);
			if (allVetos.Contains("nd.p3.17")) p3b17->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.17")) p3b17->SetFillColor(3);
			p3b17->Draw();
			TPaveLabel *p3b18 = new TPaveLabel(0.5850,0.1850,0.7500,0.2300,"18");
			p3b18->SetFillColor(38);
			if (allVetos.Contains("nd.p3.18")) p3b18->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.18")) p3b18->SetFillColor(3);
			p3b18->Draw();
			TPaveLabel *p3b19 = new TPaveLabel(0.5850,0.1400,0.7500,0.1850,"19");
			p3b19->SetFillColor(38);
			if (allVetos.Contains("nd.p3.19")) p3b19->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.19")) p3b19->SetFillColor(3);
			p3b19->Draw();
			TPaveLabel *p3b20 = new TPaveLabel(0.5850,0.0950,0.7500,0.1400,"20");
			p3b20->SetFillColor(38);
			if (allVetos.Contains("nd.p3.20")) p3b20->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.20")) p3b20->SetFillColor(3);
			p3b20->Draw();
			TPaveLabel *p3b21 = new TPaveLabel(0.5850,0.0500,0.7500,0.0950,"21");
			p3b21->SetFillColor(38);
			if (allVetos.Contains("nd.p3.21")) p3b21->SetFillColor(2);
			if ( goodBar.Contains("nd.p3.21")) p3b21->SetFillColor(3);
			p3b21->Draw();

			// This set is for Plane 4
			TPaveLabel *p4b00 = new TPaveLabel(0.7500,0.8750,0.9150,0.9500,"00");
			p4b00->SetFillColor(38);
			if (allVetos.Contains("nd.p4.0 ")) p4b00->SetFillColor(2);
			if ( goodBar.Contains("nd.p4.0 ")) p4b00->SetFillColor(3);
			p4b00->Draw();
			TPaveLabel *p4b01 = new TPaveLabel(0.7500,0.8000,0.9150,0.8750,"01");
			p4b01->SetFillColor(38);
			if (allVetos.Contains("nd.p4.1 ")) p4b01->SetFillColor(2);
			if ( goodBar.Contains("nd.p4.1 ")) p4b01->SetFillColor(3);
			p4b01->Draw();
			TPaveLabel *p4b02 = new TPaveLabel(0.7500,0.7250,0.9150,0.8000,"02");
			p4b02->SetFillColor(38);
			if (allVetos.Contains("nd.p4.2 ")) p4b02->SetFillColor(2);
			if ( goodBar.Contains("nd.p4.2 ")) p4b02->SetFillColor(3);
			p4b02->Draw();
			TPaveLabel *p4b03 = new TPaveLabel(0.7500,0.6500,0.9150,0.7250,"03");
			p4b03->SetFillColor(38);
			if (allVetos.Contains("nd.p4.3 ")) p4b03->SetFillColor(2);
			if ( goodBar.Contains("nd.p4.3 ")) p4b03->SetFillColor(3);
			p4b03->Draw();
			TPaveLabel *p4b04 = new TPaveLabel(0.7500,0.5750,0.9150,0.6500,"04");
			p4b04->SetFillColor(38);
			if (allVetos.Contains("nd.p4.4 ")) p4b04->SetFillColor(2);
			if ( goodBar.Contains("nd.p4.4 ")) p4b04->SetFillColor(3);
			p4b04->Draw();
			TPaveLabel *p4b05 = new TPaveLabel(0.7500,0.5000,0.9150,0.5750,"05");
			p4b05->SetFillColor(38);
			if (allVetos.Contains("nd.p4.5 ")) p4b05->SetFillColor(2);
			if ( goodBar.Contains("nd.p4.5 ")) p4b05->SetFillColor(3);
			p4b05->Draw();
			TPaveLabel *p4b06 = new TPaveLabel(0.7500,0.4250,0.9150,0.5000,"06");
			p4b06->SetFillColor(38);
			if (allVetos.Contains("nd.p4.6 ")) p4b06->SetFillColor(2);
			if ( goodBar.Contains("nd.p4.6 ")) p4b06->SetFillColor(3);
			p4b06->Draw();
			TPaveLabel *p4b07 = new TPaveLabel(0.7500,0.3500,0.9150,0.4250,"07");
			p4b07->SetFillColor(38);
			if (allVetos.Contains("nd.p4.7 ")) p4b07->SetFillColor(2);
			if ( goodBar.Contains("nd.p4.7 ")) p4b07->SetFillColor(3);
			p4b07->Draw();
			TPaveLabel *p4b08 = new TPaveLabel(0.7500,0.2750,0.9150,0.3500,"08");
			p4b08->SetFillColor(38);
			if (allVetos.Contains("nd.p4.8 ")) p4b08->SetFillColor(2);
			if ( goodBar.Contains("nd.p4.8 ")) p4b08->SetFillColor(3);
			p4b08->Draw();
			TPaveLabel *p4b09 = new TPaveLabel(0.7500,0.2000,0.9150,0.2750,"09");
			p4b09->SetFillColor(38);
			if (allVetos.Contains("nd.p4.9 ")) p4b09->SetFillColor(2);
			if ( goodBar.Contains("nd.p4.9 ")) p4b09->SetFillColor(3);
			p4b09->Draw();
			TPaveLabel *p4b10 = new TPaveLabel(0.7500,0.1250,0.9150,0.2000,"10");
			p4b10->SetFillColor(38);
			if (allVetos.Contains("nd.p4.10")) p4b10->SetFillColor(2);
			if ( goodBar.Contains("nd.p4.10")) p4b10->SetFillColor(3);
			p4b10->Draw();
			TPaveLabel *p4b11 = new TPaveLabel(0.7500,0.0500,0.9150,0.1250,"11");
			p4b11->SetFillColor(38);
			if (allVetos.Contains("nd.p4.11")) p4b11->SetFillColor(2);
			if ( goodBar.Contains("nd.p4.11")) p4b11->SetFillColor(3);
			p4b11->Draw();
			
			handpad01->Update();

			handpad02->cd();
			TString titleHANDleftNoVetos = "Left TDC for Plane #";
			titleHANDleftNoVetos += nplane;
			titleHANDleftNoVetos += ", PMT # ";
			titleHANDleftNoVetos += thisbar;
			titleHANDleftNoVetos += " without vetos";
			cout << "Drawing " << titleHANDleftNoVetos << "..." << endl;
			TString plotHANDleftNoVetos = "HANDleftNoVetos_p";
			plotHANDleftNoVetos += nplane;
			plotHANDleftNoVetos += "_b";
			plotHANDleftNoVetos += thisbar;
			TH1F *HANDleftNoVetos = new TH1F(plotHANDleftNoVetos,titleHANDleftNoVetos,HANDbins,HANDmin,HANDmax);
			TString HANDleftNoVetosTDC = goodTDCl;
			HANDleftNoVetosTDC += ">>";
			HANDleftNoVetosTDC += plotHANDleftNoVetos;
			chainHe->Draw(HANDleftNoVetosTDC, cuts,"");
			HANDleftNoVetos->Draw();
//			TF1 *leftFit = new TF1("leftFit","gaus",fitMin,fitMax);
// "([0]*exp(-0.5*((x-[1])/[2])^2))+[3]";
			TF1 *leftFit = new TF1("leftFit","([0]*exp(-0.5*((x-[1])/[2])^2))+[3]",fitMin,fitMax);
			leftFit->SetParameter(0,20); leftFit->SetParameter(1,750); leftFit->SetParameter(2,30); leftFit->SetParameter(3,20);
			leftFit->SetParName(0,"Peak Scale"); leftFit->SetParName(1,"Peak Mean"); leftFit->SetParName(2,"Peak Sigma"); leftFit->SetParName(3,"Background");
			HANDleftNoVetos->Fit(leftFit, "R");
			leftFit->Draw("same");
			handpad02->Update();

			handpad03->cd();
			TString titleHANDrightNoVetos = "Right TDC for Plane #";
			titleHANDrightNoVetos += nplane;
			titleHANDrightNoVetos += ", PMT # ";
			titleHANDrightNoVetos += thisbar;
			titleHANDrightNoVetos += " without vetos";
			TString plotHANDrightNoVetos = "HANDrightNoVetos_p";
			plotHANDrightNoVetos += nplane;
			plotHANDrightNoVetos += "_b";
			plotHANDrightNoVetos += thisbar;
			cout << "Drawing " << titleHANDrightNoVetos << "..." << endl;
			TH1F *HANDrightNoVetos = new TH1F(plotHANDrightNoVetos,titleHANDrightNoVetos,HANDbins,HANDmin,HANDmax);
			TString HANDrightNoVetosTDC = goodTDCr;
			HANDrightNoVetosTDC += ">>";
			HANDrightNoVetosTDC += plotHANDrightNoVetos;
			chainHe->Draw(HANDrightNoVetosTDC, cuts,"");
			HANDrightNoVetos->Draw();
//			TF1 *rightFit = new TF1("rightFit","gaus",fitMin,fitMax);
			TF1 *rightFit = new TF1("rightFit","([0]*exp(-0.5*((x-[1])/[2])^2))+[3]",fitMin,fitMax);
			rightFit->SetParameter(0,20); rightFit->SetParameter(1,750); rightFit->SetParameter(2,30); rightFit->SetParameter(3,20);
			rightFit->SetParName(0,"Peak Scale"); rightFit->SetParName(1,"Peak Mean"); rightFit->SetParName(2,"Peak Sigma"); rightFit->SetParName(3,"Background");
			HANDrightNoVetos->Fit(rightFit, "R");
			rightFit->Draw("same");
			handpad03->Update();

/*
			handpad04->cd();
			TString titleHANDleft = "Left TDC for Plane #";
			titleHANDleft += nplane;
			titleHANDleft += ", PMT # ";
			titleHANDleft += thisbar;
			titleHANDleft += " with vetos";
			cout << "Drawing " << titleHANDleft << "..." << endl;
			TString plotHANDleft = "HANDleft_p";
			plotHANDleft += nplane;
			plotHANDleft += "_b";
			plotHANDleft += thisbar;
			TH1F *HANDleft = new TH1F(plotHANDleft,titleHANDleft,HANDbins,HANDmin,HANDmax);
			TString HANDleftTDC = goodTDCl;
			HANDleftTDC += ">>";
			HANDleftTDC += plotHANDleft;
			chainHe->Draw(HANDleftTDC, cuts && vetoTDCs,"");
			HANDleft->Draw();
			handpad04->Update();

			handpad05->cd();
			TString titleHANDright = "Right TDC for Plane #";
			titleHANDright += nplane;
			titleHANDright += ", PMT # ";
			titleHANDright += thisbar;
			titleHANDright += " with vetos";
			cout << "Drawing " << titleHANDright << "..." << endl;
			TString plotHANDright = "HANDright_p";
			plotHANDright += nplane;
			plotHANDright += "_b";
			plotHANDright += thisbar;
			TH1F *HANDright = new TH1F(plotHANDright,titleHANDright,HANDbins,HANDmin,HANDmax);
			TString HANDrightTDC = goodTDCr;
			HANDrightTDC += ">>";
			HANDrightTDC += plotHANDright;
			chainHe->Draw(HANDrightTDC, cuts && vetoTDCs,"");
			HANDright->Draw();
			handpad05->Update();

			handpad06->cd();
			TString titleHAND = "Left & Right TDCs for Plane #";
			titleHAND += nplane;
			titleHAND += ", PMT # ";
			titleHAND += thisbar;
			titleHAND += " with vetos";
			cout << "Drawing " << titleHAND << "..." << endl;
			TString plotHAND = "HAND_p";
			plotHAND += nplane;
			plotHAND += "_b";
			plotHAND += thisbar;
			TH2F *HAND = new TH2F(plotHAND,titleHAND,HANDbins,HANDmin,HANDmax,HANDbins,HANDmin,HANDmax);
			TString HANDTDC = goodTDCl;
			HANDTDC += ":";
			HANDTDC += goodTDCr;
			HANDTDC += ">>";
			HANDTDC += plotHAND;
			chainHe->Draw(HANDTDC, cuts && vetoTDCs,"");
			HAND->SetStats(kFALSE);
			HAND->Draw("COLZ");
			handpad06->Update();

			handpad07->cd();
			TString titleHANDlego = "Left & Right TDCs for Plane #";
			titleHANDlego += nplane;
			titleHANDlego += ", PMT # ";
			titleHANDlego += thisbar;
			titleHANDlego += " with vetos";
			cout << "Drawing " << titleHANDlego << "..." << endl;
			TString plotHANDlego = "HANDlego_p";
			plotHANDlego += nplane;
			plotHANDlego += "_b";
			plotHANDlego += thisbar;
			TH2F *HANDlego = new TH2F(plotHANDlego,titleHANDlego,HANDbins,HANDmin,HANDmax,HANDbins,HANDmin,HANDmax);
			TString HANDlegoTDC = goodTDCl;
			HANDlegoTDC += ":";
			HANDlegoTDC += goodTDCr;
			HANDlegoTDC += ">>";
			HANDlegoTDC += plotHANDlego;
			chainHe->Draw(HANDlegoTDC, cuts && vetoTDCs,"");
			HANDlego->Draw("LEGO2");
			handpad07->Update();

*/
			TString imageTitle = "plots_for_hand/TDC_Calibration/Try_3_TDC_plots_Run_Num_";
			imageTitle += HeRunNumber;
			imageTitle += "_p";
			imageTitle += nplane;
			imageTitle += "_b";
			imageTitle += thisbar;
			imageTitle+= ".png";
			handCanvas->Print(imageTitle);

		}
	}



	cout << "All done!" << endl;



}







































