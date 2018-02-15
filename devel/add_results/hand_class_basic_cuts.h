// *************************************************************************
//
// This script will be used to define the basic cuts that I've been using
// over and over again with regards to the Hall A Neutron Detector. It 
// should allow me to call this header file and run the basic cuts in one 
// line of code instead of having a big chunk of code in each different file
// 
// To run this, first include the header file:
/*
	#include "hand_class_basic_cuts.h"
*/
//
// Then declare the cut variables:
/*
	TCut isGood; TCut kinematicsGood; TCut eventtypeGood; TCut dpGood; TCut targetGood;
	TCut tracksGood; TCut thphGood; TCut xbjGood; TCut psshGood; TCut cerenkovGood;
	TCut q2nuGood; TCut basicGood; TCut isGoodForAllBasic;
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
	hand_basic_cuts(isGood, kinematicsGood, eventtypeGood, dpGood, targetGood, tracksGood, thphGood, xbjGood, psshGood, cerenkovGood, q2nuGood, basicGood, isGoodForAllBasic, imageCutsTitle, HeRunNumber, endHeRunNumber, chainHe, numin, numax, q2min, q2max, bins, xmin, xmax, drawCuts, Q2)
*/
//
// Elena Long
// 2010-12-08
//
// *************************************************************************


void hand_class_basic_cuts(int HeRunNumber, int endHeRunNumber, bool drawCuts, TString kine, TString filenameHe, TString targ)
{

        TString target;
        if ((targ == "v") || (targ == "l") || (targ == "t") || (targ == "c") || (targ == "h")) { check = true;}
        if (targ == "v") {target="Vertical 3He";}
        if (targ == "l") {target="Longitudinal 3He";}
        if (targ == "t") {target="Transverse 3He";}
        if (targ == "c") {target="Carbon";}
        if (targ == "h") {target="Hydrogen";}


        TFile fileHe(filenameHe);
        TString Q2=kine;
        double xmin=0;
        double xmax=3;



//	cout << "vvvvvvvvvvvvvvvvvvvvvvvvv hand_basic_cuts.h vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;

//	Int_t ientry = LoadTree(jentry);

//	TFile *outputRoot = new TFile(outputRootString,"UPDATE");

/*	bool isGood = true;
	bool kinematicsGood = (PriKineR_Q2<10 && GoodElectron==1 && PriKineR_nu<10);
//	bool eventtypeGood = (D_evtypebits&2)==2;
	bool eventtypeGood = true;
	bool dpGood = (ExTgtCor_R_dp>-0.04 && ExTgtCor_R_dp<0.06);
	bool targetGood = (ReactPt_R_z>-0.15 && ReactPt_R_z<0.17);
	bool tracksGood = (R_tr_n==1 && R_vdc_u1_nhit>3 && R_vdc_u1_nhit<7 && R_vdc_u2_nhit>3 && R_vdc_u2_nhit<7 && R_vdc_v1_nhit>3 && R_vdc_v1_nhit<7 && R_vdc_v2_nhit>3 && R_vdc_v2_nhit<7);
//	tracksGood = ;
//	double thbound = 0.07;
*/	double thboundlow = -0.055;
	double thboundhigh = 0.055;
//	double thboundlow = -0.000;
//	double thboundhigh = 0.010;
//	double phbound = 0.03;
	double phbound = 0.025;
	double phboundlow = -0.025;
	double phboundhigh = 0.025;
/*	TString thetaphiRStr = "abs(ExTgtCor_R.ph)<";
	thetaphiRStr += phbound;
	thetaphiRStr += " && ExTgtCor_R.th<";
	thetaphiRStr += thboundhigh;
	thetaphiRStr += " && ExTgtCor_R.th>";
	thetaphiRStr += thboundlow;
*/
	/*bool thphGood = (ExTgtCor_R_ph<phboundhigh && ExTgtCor_R_ph>phboundlow && ExTgtCor_R_th<thboundhigh && ExTgtCor_R_th>thboundlow);


	bool xbjGood = (PriKineRHe3_x_bj<2.0);
	bool psshGood = ((R_ps_e + 2*R_sh_e)>900 && R_ps_e>1 && R_sh_e>1);
	bool cerenkovGood = (R_cer_asum_c>150);
	bool q2nuGood = true;
//	if (Q2 == "1.0") {q2nuGood = ((PriKineR_Q2 - (2*PriKineR_nu) + 0.1)>0 && (PriKineR_Q2 - (2*PriKineR_nu) + 0.03)<0);}
	if (Q2 == "0.52") {q2nuGood = ((PriKineR_Q2 - (2*PriKineR_nu) + 0.05)>0 && (PriKineR_Q2 - (2*PriKineR_nu) + 0.018)<0);}
	if (Q2 == "0.42") {q2nuGood = ((PriKineR_Q2 - (2*PriKineR_nu) + 0.05)>0 && (PriKineR_Q2 - (2*PriKineR_nu) + 0.018)<0);}

//	xbjGood = "";
//	psshGood = "";
//	cerenkovGood = "";


	bool basicGood = kinematicsGood && eventtypeGood && tracksGood;
	isGoodForAllBasic = isGood && kinematicsGood && eventtypeGood && dpGood && targetGood && thphGood && tracksGood && xbjGood && psshGood && cerenkovGood && q2nuGood;
//	cout << "jentry: " << jentry << ", isGoodForAllBasic: " << isGoodForAllBasic << endl;
*/
// vvvvvvvvvvvvvvvvvv Fill Basic Cut Plots vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// The chunk below will fill all of the Basic Cut Plots
/*	HedpNoCut->Fill(ExTgtCor_R_dp);
	if (dpGood) {HedpCut->Fill(ExTgtCor_R_dp);}
	HeReactZNoCut->Fill(ReactPt_R_z);
	if (targetGood) {HeReactZCut->Fill(ReactPt_R_z);}
//	if (isGoodForAllBasic) {HeThetaPhiCut->Fill(ExTgtCor_R_th,ExTgtCor_R_ph);}
	if (isGoodForAllBasic) {HeThetaPhiCut->Fill(ExTgtCor_R_ph,ExTgtCor_R_th);}
//	HePsShNoCut->Fill(R_ps_e,R_sh_e);
	HePsShNoCut->Fill(R_sh_e,R_ps_e);
//	if (isGoodForAllBasic) {histQ2Nu->Fill(PriKineR_Q2,PriKineR_nu);}
	if (isGoodForAllBasic) {histQ2Nu->Fill(PriKineR_nu,PriKineR_Q2);}
	histcerenkov->Fill(R_cer_asum_c);
	if (cerenkovGood) {histcerenkovcut->Fill(R_cer_asum_c);}
//	if (isGoodForAllBasic) {HePsShCut->Fill(R_ps_e,R_sh_e);}
	if (isGoodForAllBasic) {HePsShCut->Fill(R_sh_e,R_ps_e);}
	histx->Fill(PriKineR_x_bj);
	if (isGoodForAllBasic) {histxcut->Fill(PriKineR_x_bj);}
	if (isGoodForAllBasic) {ToFbasic->Fill(NA_n_tof[0]);}
*/
// ^^^^^^^^^^^^^^^^^^ Fill Basic Cut Plots ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^



//	TString basicCutStr = TString(isGoodForAllBasic);
//	cout << "Basic Cuts: " << basicCutStr << endl;
	
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
		cout << "Drawing " << titledp << "..." << endl;
//		TH1F *HedpNoCut = new TH1F("HedpNoCut",titledp,400,-0.08,0.08);
		TH1F *HedpNoCut = (TH1F*)fileHe.Get("HedpNoCut");
//		TH1F *HedpCut = new TH1F("HedpCut",titledp,400,-0.08,0.08);
		TH1F *HedpCut = (TH1F*)fileHe.Get("HedpCut");
//		chainHe->Draw("ExTgtCor_R.dp>>HedpNoCut", "", "");
//		chainHe->Draw("ExTgtCor_R.dp>>HedpCut", dp, "");
		HedpNoCut->SetTitle(titledp);
//		HedpNoCut->Write();
		HedpNoCut->Draw();
		HedpCut->SetLineColor(kBlack);
		HedpCut->SetFillColor(kViolet);
//		HedpCut->Write();
		HedpCut->Draw("same");
		cutpad1->Update();

		cutpad2->cd();
		cout << "Drawing Target Cut..." << endl;
		TString titleTarget = "Target Cut";
//		TH1F *HeReactZNoCut = new TH1F("HeReactZNoCut",titleTarget,400,-0.3,0.3);
		TH1F *HeReactZNoCut = (TH1F*)fileHe.Get("HeReactZNoCut");
//		TH1F *HeReactZCut = new TH1F("HeReactZCut",titleTarget,400,-0.3,0.3);
		TH1F *HeReactZCut = (TH1F*)fileHe.Get("HeReactZCut");
//		chainHe->Draw("ReactPt_R.z>>HeReactZNoCut", "", "");
//		chainHe->Draw("ReactPt_R.z>>HeReactZCut", targetGood, "");
		HeReactZNoCut->SetTitle(titleTarget);
//		HeReactZNoCut->Write();
		HeReactZNoCut->Draw();
		HeReactZCut->SetLineColor(kBlack);
		HeReactZCut->SetFillColor(kViolet);
//		HeReactZCut->Write();
		HeReactZCut->Draw();
		cutpad2->Update();

		cutpad3->cd();
		cout << "Drawing Theta and Phi Cut..." << endl;
		TString titleThetaPhiCut = "Theta and Phi";
//		TH2F *HeThetaPhiCut = new TH2F("HeThetaPhiCut",titleThetaPhiCut,100,-0.05,0.05,100,-0.1,0.1);
		TH2F *HeThetaPhiCut = (TH2F*)fileHe.Get("HeThetaPhiCut");
//		TH2F *HeThetaPhiCut = new TH2F("HeThetaPhiCut",titleThetaPhiCut,100,-0.05,0.05,100,-0.025,0.025);
//		chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeThetaPhiCut", targetGood, "");
//		chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeThetaPhiCut", isGoodForAllBasic, "");
		HeThetaPhiCut->SetTitle(titleThetaPhiCut);
//		HeThetaPhiCut->SetStats(kFALSE);
//		HeThetaPhiCut->Write();
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
//		TH2F *HePsShNoCut = new TH2F("HePsShNoCut",titlePsSh,200,1,2500,200,1,1500);
		TH2F *HePsShNoCut = (TH2F*)fileHe.Get("HePsShNoCut");
//		chainHe->Draw("R.ps.e:R.sh.e>>HePsShNoCut", "", "");
		HePsShNoCut->SetTitle(titlePsSh);
		HePsShNoCut->SetStats(kFALSE);
//		HePsShNoCut->Write();
		HePsShNoCut->Draw("COLZ");
		psshcut = new TLine(0,900,450,0);
		psshcut->SetLineColor(kViolet);
		psshcut->SetLineWidth(3);
		psshcut->Draw("same");
		cutpad7->Update();

		cutpad4->cd();
		TString titleQ2Nu = "Q2 and Nu";
//		TH2F *histQ2Nu = new TH2F("histQ2Nu",titleQ2Nu,200,numin,numax,200,q2min,q2max);
		TH2F *histQ2Nu = (TH2F*)fileHe.Get("histQ2Nu");
		cout << "Drawing " << titleQ2Nu << "..." << endl;
//		chainHe->Draw("PriKineR.Q2:PriKineR.nu>>histQ2Nu", isGoodForAllBasic, ""); 
		histQ2Nu->SetTitle(titleQ2Nu);
//		histQ2Nu->Write();
		histQ2Nu->Draw("COLZ");
		cutpad4->Update();

		cutpad5->cd();
		TString titlecerenkov = "Cerenkov Cut";
		cout << "Drawing " << titlecerenkov << "..." << endl;
//		TH1F *histcerenkov = new TH1F("histcerenkov",titlecerenkov,200,-25,2000);
		TH1F *histcerenkov = (TH1F*)fileHe.Get("histcerenkov");
//		TH1F *histcerenkovcut = new TH1F("histcerenkovcut",titlecerenkov,200,-25,2000);
		TH1F *histcerenkovcut = (TH1F*)fileHe.Get("histcerenkovcut");
//		chainHe->Draw("R.cer.asum_c>>histcerenkov", "", "");
//		chainHe->Draw("R.cer.asum_c>>histcerenkovcut", cerenkovGood, "");
		histcerenkov->SetTitle(titlecerenkov);
		histcerenkov->SetStats(kFALSE);
		histcerenkovcut->SetFillColor(kViolet);
//		histcerenkov->Write();
		histcerenkov->Draw();
//		histcerenkovcut->Write();
		histcerenkovcut->Draw("same");
		cutpad5->Update();

		cutpad8->cd();
		cout << "Drawing Preshower/Shower with All Cut..." << endl;
		TString titlePsSh = "Preshower and Shower with all cuts";
//		TH2F *HePsShCut = new TH2F("HePsShCut",titlePsSh,200,1,2500,200,1,1500);
		TH2F *HePsShCut = (TH2F*)fileHe.Get("HePsShCut");
//		chainHe->Draw("R.ps.e:R.sh.e>>HePsShCut", isGoodForAllBasic, "");
		HePsShCut->SetTitle(titlePsSh);
		HePsShCut->SetStats(kFALSE);
//		HePsShCut->Write();
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
//		TH1F *histx = new TH1F("histx",titlex,bins,xmin,xmax);
		TH1F *histx = (TH1F*)fileHe.Get("histx");
//		TH1F *histxcut = new TH1F("histxcut",titlex,bins,xmin,xmax);
		TH1F *histxcut = (TH1F*)fileHe.Get("histxcut");
//		histx->Sumw2();
//		chainHe->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histx", isGood && kinematicsGood && eventtypeGood && dpGood && targetGood && thphGood && tracksGood && cerenkovGood && psshGood, "E");
//		chainHe->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histxcut", isGoodForAllBasic, "E");
//		histx->Write();
		histx->Draw();
		histxcut->SetFillColor(kViolet);
//		histxcut->Write();
		histxcut->Draw("same");
		cutpad6->Update();

		cutsCanvas->Print(imageCutsTitle);
	}

//	outputRoot->Close();

	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
}
