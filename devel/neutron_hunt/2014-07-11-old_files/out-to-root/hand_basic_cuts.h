// *************************************************************************
//
// This script will be used to define the basic cuts that I've been using
// over and over again with regards to the Hall A Neutron Detector. It 
// should allow me to call this header file and run the basic cuts in one 
// line of code instead of having a big chunk of code in each different file
// 
// To run this, first include the header file:
/*
	#include "hand_basic_cuts.h"
*/
//
// Then declare the cut variables:
/*
	TCut cut; TCut kinematics; TCut eventtype; TCut dp; TCut target;
	TCut tracks; TCut thph; TCut xbj; TCut pssh; TCut cerenkov;
	TCut q2nu; TCut basic; TCut cuts;
*/
//
// Be sure to also declare these, although they will change depending on Q^2
// and run number (once I get a better handle on the data, I can include these
// variables in this script and define them based just on run number):
/*
	double numin = 0.3;
	double numax = 0.7;
	double q2min = 0.75;
	double q2max = 1.2;
	int bins = 50;
	double xmin = 0.6;
	double xmax = 3.0;
*/ 
// And be sure to define TString imageCutsTitle. This will be different for each 
// file, but an example (to be changed) is below:
/*
        TString imageCutsTitle = "/home/ellie/physics/e05-102/images/plots_for_hand/left_right_position_test/HAND_plots_Run_Num_";
        imageCutsTitle += HeRunNumber;
        imageCutsTitle += "-";
        imageCutsTitle += endHeRunNumber;
        imageCutsTitle += "_basic_cuts"; 
        if (includeVetos) imageCutsTitle += "_with_vetos";
        if (includeAntivetos) {imageCutsTitle += "_with_antivetos";} 
        if (antivetosAsVetos && includeAntivetos) {imageCutsTitle += "_as_vetos";}
        imageCutsTitle += ".png";
*/
//
// Include a boolean value to decide whether or not you actually want to
// draw the cuts, or just define them:
/*
	bool drawCuts = true;
*/
// Finally, just run the code:
/*
	hand_basic_cuts(cut, kinematics, eventtype, dp, target, tracks, thph, xbj, pssh, cerenkov, q2nu, basic, cuts, imageCutsTitle, HeRunNumber, endHeRunNumber, chainHe, numin, numax, q2min, q2max, bins, xmin, xmax, drawCuts, Q2)
*/
//
// Elena Long
// 2010-12-08
//
// *************************************************************************


void hand_basic_cuts(TCut& cut, TCut& kinematics, TCut& eventtype, TCut& dp, TCut& target, TCut& tracks, TCut& thph, TCut& xbj, TCut& pssh, TCut& cerenkov, TCut& q2nu, TCut& basic, TCut& cuts, TString imageCutsTitle, int HeRunNumber, int endHeRunNumber, TChain* chainHe, double numin, double numax, double q2min, double q2max, int bins, double xmin, double xmax, bool drawCuts, TString Q2, TString outputRootString){


	cout << "vvvvvvvvvvvvvvvvvvvvvvvvv hand_basic_cuts.h vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;

	TFile *outputRoot = new TFile(outputRootString,"UPDATE");

	cut = "";
	kinematics = "PriKineR.Q2<10 && GoodElectron==1 && PriKineR.nu<10";
//	eventtype = "(D.evtypebits&2)==2";
	eventtype = "";
	dp = "ExTgtCor_R.dp>-0.04 && ExTgtCor_R.dp<0.06";
	target = "ReactPt_R.z>-0.15 && ReactPt_R.z<0.17";
	tracks = "R.tr.n==1 && R.vdc.u1.nhit>3 && R.vdc.u1.nhit<7 && R.vdc.u2.nhit>3 && R.vdc.u2.nhit<7 && R.vdc.v1.nhit>3 && R.vdc.v1.nhit<7 && R.vdc.v2.nhit>3 && R.vdc.v2.nhit<7";
//	tracks = "";
//	double thbound = 0.07;
	double thboundlow = -0.055;
	double thboundhigh = 0.055;
//	double thboundlow = -0.000;
//	double thboundhigh = 0.010;
//	double phbound = 0.03;
	double phbound = 0.025;
	TString thetaphiRStr = "abs(ExTgtCor_R.ph)<";
	thetaphiRStr += phbound;
	thetaphiRStr += " && ExTgtCor_R.th<";
	thetaphiRStr += thboundhigh;
	thetaphiRStr += " && ExTgtCor_R.th>";
	thetaphiRStr += thboundlow;

	thph = thetaphiRStr;
	xbj = "PriKineRHe3.x_bj<3.0";
	pssh = "(R.ps.e + 2*R.sh.e)>900 && R.ps.e>1 && R.sh.e>1";
	cerenkov = "R.cer.asum_c>150";
//	if (Q2 == "1.0") {q2nu = "(PriKineR.Q2 - (2*PriKineR.nu) + 0.1)>0 && (PriKineR.Q2 - (2*PriKineR.nu) + 0.03)<0";}
	if (Q2 == "0.52") {q2nu = "(PriKineR.Q2 - (2*PriKineR.nu) + 0.05)>0 && (PriKineR.Q2 - (2*PriKineR.nu) + 0.018)<0";}
	if (Q2 == "0.42") {q2nu = "(PriKineR.Q2 - (2*PriKineR.nu) + 0.05)>0 && (PriKineR.Q2 - (2*PriKineR.nu) + 0.018)<0";}

//	xbj = "";
//	pssh = "";
//	cerenkov = "";


	basic = kinematics && eventtype && tracks;
	cuts = cut && kinematics && eventtype && dp && target && thph && tracks && xbj && pssh && cerenkov && q2nu;

	TString basicCutStr = TString(cuts);
	cout << "Basic Cuts: " << basicCutStr << endl;
	
	if (drawCuts){
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
		HedpNoCut->Write();
		HedpNoCut->Draw();
		HedpCut->SetLineColor(kBlack);
		HedpCut->SetFillColor(kViolet);
		HedpCut->Write();
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
		HeReactZNoCut->Write();
		HeReactZNoCut->Draw();
		HeReactZCut->SetLineColor(kBlack);
		HeReactZCut->SetFillColor(kViolet);
		HeReactZCut->Write();
		HeReactZCut->Draw();
		cutpad2->Update();

		cutpad3->cd();
		cout << "Drawing Theta and Phi Cut..." << endl;
		TString titleThetaPhiCut = "Theta and Phi";
		TH2F *HeThetaPhiCut = new TH2F("HeThetaPhiCut",titleThetaPhiCut,100,-0.05,0.05,100,-0.1,0.1);
//		TH2F *HeThetaPhiCut = new TH2F("HeThetaPhiCut",titleThetaPhiCut,100,-0.05,0.05,100,-0.025,0.025);
//		chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeThetaPhiCut", target, "");
		chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeThetaPhiCut", cuts, "");
		HeThetaPhiCut->SetTitle(titleThetaPhiCut);
//		HeThetaPhiCut->SetStats(kFALSE);
		HeThetaPhiCut->Write();
		HeThetaPhiCut->Draw("COLZ");
		bottom = new TLine(-phbound,thboundlow,phbound,thboundlow);
		top = new TLine(-phbound,thboundhigh,phbound,thboundhigh);
		left = new TLine(-phbound,thboundlow,-phbound,thboundhigh);
		right = new TLine(phbound,thboundlow,phbound,thboundhigh);
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
		cout << "Drawing Preshower/Shower, No Cut..." << endl;
		TString titlePsSh = "Preshower and Shower";
		TH2F *HePsShNoCut = new TH2F("HePsShNoCut",titlePsSh,200,1,2500,200,1,1500);
		chainHe->Draw("R.ps.e:R.sh.e>>HePsShNoCut", "", "");
		HePsShNoCut->SetTitle(titlePsSh);
		HePsShNoCut->SetStats(kFALSE);
		HePsShNoCut->Write();
		HePsShNoCut->Draw("COLZ");
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
		histQ2Nu->Write();
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
		histcerenkov->Write();
		histcerenkov->Draw();
		histcerenkovcut->Write();
		histcerenkovcut->Draw("same");
		cutpad5->Update();

		cutpad8->cd();
		cout << "Drawing Preshower/Shower with All Cut..." << endl;
		TString titlePsSh = "Preshower and Shower with all cuts";
		TH2F *HePsShCut = new TH2F("HePsShCut",titlePsSh,200,1,2500,200,1,1500);
		chainHe->Draw("R.ps.e:R.sh.e>>HePsShCut", cuts, "");
		HePsShCut->SetTitle(titlePsSh);
		HePsShCut->SetStats(kFALSE);
		HePsShCut->Write();
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
		histx->Write();
		histx->Draw();
		histxcut->SetFillColor(kViolet);
		histxcut->Write();
		histxcut->Draw("same");
		cutpad6->Update();

		cutsCanvas->Print(imageCutsTitle);
	}

	outputRoot->Close();
	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
}
