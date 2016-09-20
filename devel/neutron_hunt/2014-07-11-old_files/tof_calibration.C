// ***************************************************
//
// This script should show the time of flight spectra
// so that we are better able to find the neutrons.
//
// 10-18-10
// Elena Long
//
// ***************************************************

#include <iostream>
#include <string>
#include <string.h>

// Search for HAND to get to the PMT definitions

void tof_calibration(){

	bool includeVetos;
// 	If includeVetos = false, then only good bars will be displayed. If 
//	includeVetos = true, then veto bars will be shown along with the good bars.
	includeVetos = true;
//	includeVetos = false;

	TString Q2 = "1.0";
	int HeRunNumber = 20791;
	int endHeRunNumber = 20792;
//	int HeRunNumber = 22463;
//	int endHeRunNumber = 22463;
	int ToFbins = 1600;
	double ToFmin = -50;
	double ToFmax = 1600;
	int TDCbins = 100;
	double TDCmin = 1;
	double TDCmax = 1600;
	int ADCbins = 200;
	double ADCmin = 1;
	double ADCmax = 3100;
	double q2min = 0.08;
	double q2max = 1.6;
	double numin = 0.02;
	double numax = 0.8;
	double xmin = 0.6;
	double xmax = 3.0;



/*	TString Q2 = "0.5";
	int HeRunNumber = 21383;
	int endHeRunNumber = 21387;
	int TDCbins = 100;
	double TDCmin = 1;
//	double HANDmax = 1800;
	double TDCmax = 1600;
	int ADCbins = 200;
	double ADCmin = 1;
	double ADCmax = 3100;
	double q2min = 0.08;
	double q2max = 0.80;
	double numin = 0.02;
	double numax = 0.4;
	double xmin = 0.6;
	double xmax = 3.0;
*/

	bool leadwall;
//	If leadwall = true, then the lead wall was in. If false, out.
	if (HeRunNumber>20578 && HeRunNumber<20788) leadwall=true;
	else leadwall = false;

	int bins = 50;

	TCut cut = "";
	TCut kinematics = "PriKineR.Q2<10 && GoodElectron==1 && PriKineR.nu<10";
//	TCut eventtype = "(D.evtypebits&2)==2";
	TCut eventtype = "";
	TCut dp = "ExTgtCor_R.dp>-0.04 && ExTgtCor_R.dp<0.06";
	TCut target = "ReactPt_R.z>-0.15 && ReactPt_R.z<0.17";
	TCut tracks = "R.tr.n==1 && R.vdc.u1.nhit>3 && R.vdc.u1.nhit<7 && R.vdc.u2.nhit>3 && R.vdc.u2.nhit<7 && R.vdc.v1.nhit>3 && R.vdc.v1.nhit<7 && R.vdc.v2.nhit>3 && R.vdc.v2.nhit<7";
//	TCut tracks = "";
	double thbound = 0.07;
	double phbound = 0.03;
	TString thetaphiRStr = "abs(ExTgtCor_R.ph)<";
	thetaphiRStr += phbound;
	thetaphiRStr += " && abs(ExTgtCor_R.th)<";
	thetaphiRStr += thbound;
	TCut thph = thetaphiRStr;
	TCut xbj = "PriKineRHe3.x_bj<3.0";
	TCut pssh = "(R.ps.e + 2*R.sh.e)>900 && R.ps.e>1 && R.sh.e>1";
	TCut cerenkov = "R.cer.asum_c>150";
//	xbj = "";
//	pssh = "";
//	cerenkov = "";


	TCut basic = kinematics && eventtype && tracks;
	TCut cuts = cut && kinematics && eventtype && dp && target && thph && tracks && xbj && pssh && cerenkov;

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
	TString titledp = "dp Cut";
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

/*	TString imageCutsTitle = "plots_for_hand/TDC_and_ADC/HAND_plots_Run_Num_";
	imageCutsTitle += HeRunNumber;
	imageCutsTitle += "-";
	imageCutsTitle += endHeRunNumber;
	imageCutsTitle += "_cuts";
	if (includeVetos) imageCutsTitle += "_with_vetos";
	else imageCutsTitle += "_without_vetos";
	imageCutsTitle += ".png";
	cutsCanvas->Print(imageCutsTitle);
*/

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
	int vetoplane;
	int padBins;
	double padMin;
	double padMax;


// The section below plots the HAND data
// **********************************************************************************************
//	for (int nplane=0; nplane<5; nplane++)
//	for (int nplane=1; nplane<5; nplane++)
	for (int nplane=2; nplane<3; nplane++)
	{
		if (nplane==0)
		{
			maxbars=32;
			vetoplane=-1;
			padBins=32;
			padMin=0;
			padMax=32;
		}
		if (nplane==1)
		{
			maxbars=30;
			vetoplane=0;
			padBins=30;
			padMin=0;
			padMax=30;
		}
		if (nplane==2)
		{
			maxbars=24;
			vetoplane=1;
			padBins=24;
			padMin=0;
			padMax=24;
		}
		if (nplane==3)
		{
			maxbars=22;
			vetoplane=2;
			padBins=22;
			padMin=0;
			padMax=22;
		}
		if (nplane==4)
		{
			maxbars=12;
			vetoplane=3;
			padBins=12;
			padMin=0;
			padMax=12;
		}

		// This allVetos is going to be used when drawing the
		// image of the HAND as a searchable string to find
		// out if any particular bar is a veto bar or not.
		// Similarly with goodBar;
		// **************************************************
			TString allVetos = "nd.p";
			allVetos += vetoplane;


			TString goodPlane = "nd.p";
			goodPlane += nplane;
			cout << "Good Plane: " << goodPlane << endl;
		// **************************************************


		// Below are the  veto cuts. They're split apart because I want
		// to be able to put this in a loop eventually to automize
		// the flow of data to histograms
			TString vetoTDCslSt = "NA.";
			vetoTDCslSt += vetoplane;
			vetoTDCslSt += ".lt<1";
			TCut vetoTDCsl = vetoTDCslSt;

			TString vetoTDCsrSt = "NA.";
			vetoTDCsrSt += vetoplane;
			vetoTDCsrSt += ".rt<1";
			TCut vetoTDCsr = vetoTDCsrSt;

			TCut vetoTDCs = vetoTDCsl && vetoTDCsr;

		
			
			TString canvasName = "handp";
			canvasName += nplane;
			TString canvasTitle = "HAND - Plane ";
			canvasTitle += nplane;
			TCanvas *handCanvas = new TCanvas(canvasName,canvasTitle,1400,770); //x,y
		//	TCanvas *hand = new TCanvas("hand","Neutron Data",1400,770); //x,y

			handpad01 =  new TPad("handpad01","handpad01",0.0000,0.0000,0.1000,1.0000,0,0,0);
			handpad02 =  new TPad("handpad02","handpad02",0.1000,0.0000,1.0000,1.0000,0,0,0);
			handpad01->Draw(); handpad02->Draw();
	

/*			handpad01 =  new TPad("handpad01","handpad01",0.0000,0.0000,0.1000,1.0000,0,0,0);
			handpad02 =  new TPad("handpad02","handpad02",0.1000,0.5000,0.4000,1.0000,0,0,0);
			handpad03 =  new TPad("handpad03","handpad03",0.4000,0.5000,0.7000,1.0000,0,0,0);
			handpad04 =  new TPad("handpad04","handpad04",0.1000,0.0000,0.4000,0.5000,0,0,0);
			handpad05 =  new TPad("handpad05","handpad05",0.4000,0.0000,0.7000,0.5000,0,0,0);
			handpad06 =  new TPad("handpad06","handpad06",0.7000,0.5000,1.0000,1.0000,0,0,0);
			handpad07 =  new TPad("handpad07","handpad07",0.7000,0.0000,1.0000,0.5000,0,0,0);
//			handpad06 =  new TPad("handpad06","handpad06",0.4000,0.3333,0.7000,0.6666,0,0,0);
//			handpad07 =  new TPad("handpad07","handpad07",0.7000,0.3333,1.0000,0.6666,0,0,0);
//			handpad08 =  new TPad("handpad08","handpad08",0.1000,0.0000,0.4000,0.3333,0,0,0);
//			handpad09 =  new TPad("handpad09","handpad09",0.4000,0.0000,0.7000,0.3333,0,0,0);
//			handpad10 =  new TPad("handpad10","handpad10",0.7000,0.0000,1.0000,0.3333,0,0,0);
			handpad01->Draw(); handpad02->Draw(); handpad03->Draw(); handpad04->Draw(); handpad05->Draw();
			handpad06->Draw(); handpad07->Draw(); 
//			handpad08->Draw(); handpad09->Draw(); handpad10->Draw();
*/
			// This huge block is to draw the HAND. Data follows well below here.
			handpad01->cd();
			TString theBigTitle = "Runs # ";
			theBigTitle += HeRunNumber;
			theBigTitle += " - ";
			theBigTitle += endHeRunNumber;
			TPaveLabel *bigTitle = new TPaveLabel(0.0535,0.9600,0.9150,0.9950,theBigTitle);
			bigTitle->Draw();

			// This will draw the lead wall if it was on during run HeRunNumber.
			if (leadwall)
			{
				TPaveLabel *pbwall = new TPaveLabel(0.0235,0.0500,0.1435,0.9500,"");
				pbwall->SetFillColor(kRed + 2);
				pbwall->Draw();
			}

			// This set is for Plane Veto
			TPaveLabel *p0b10 = new TPaveLabel(0.1835,0.6650,0.2165,0.6980,"10");
			p0b10->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b10->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b10->SetFillColor(3); 
			p0b10->Draw();
			TPaveLabel *p0b11 = new TPaveLabel(0.1835,0.6320,0.2165,0.6650,"11");
			p0b11->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b11->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b11->SetFillColor(3); 
			p0b11->Draw();
			TPaveLabel *p0b12 = new TPaveLabel(0.1835,0.5990,0.2165,0.6320,"12");
			p0b12->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b12->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b12->SetFillColor(3); 
			p0b12->Draw();
			TPaveLabel *p0b13 = new TPaveLabel(0.1835,0.5660,0.2165,0.5990,"13");
			p0b13->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b13->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b13->SetFillColor(3); 
			p0b13->Draw();
			TPaveLabel *p0b14 = new TPaveLabel(0.1835,0.5330,0.2165,0.5660,"14");
			p0b14->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b14->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b14->SetFillColor(3); 
			p0b14->Draw();
			TPaveLabel *p0b15 = new TPaveLabel(0.1835,0.5000,0.2165,0.5330,"15");
			p0b15->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b15->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b15->SetFillColor(3); 
			p0b15->Draw();
			TPaveLabel *p0b16 = new TPaveLabel(0.1835,0.4670,0.2165,0.5000,"16");
			p0b16->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b16->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b16->SetFillColor(3); 
			p0b16->Draw();
			TPaveLabel *p0b17 = new TPaveLabel(0.1835,0.4340,0.2165,0.4670,"17");
			p0b17->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b17->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b17->SetFillColor(3); 
			p0b17->Draw();
			TPaveLabel *p0b18 = new TPaveLabel(0.1835,0.4010,0.2165,0.4340,"18");
			p0b18->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b18->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b18->SetFillColor(3); 
			p0b18->Draw();
			TPaveLabel *p0b19 = new TPaveLabel(0.1835,0.3680,0.2165,0.4010,"19");
			p0b19->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b19->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b19->SetFillColor(3); 
			p0b19->Draw();
			TPaveLabel *p0b20 = new TPaveLabel(0.1835,0.3350,0.2165,0.3680,"20");
			p0b20->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b20->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b20->SetFillColor(3); 
			p0b20->Draw();
			TPaveLabel *p0b21 = new TPaveLabel(0.1835,0.3020,0.2165,0.3350,"21");
			p0b21->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b21->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b21->SetFillColor(3); 
			p0b21->Draw();
			TPaveLabel *p0b00 = new TPaveLabel(0.2165,0.9170,0.2495,0.9500,"00");
			p0b00->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b00->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b00->SetFillColor(3); 
			p0b00->Draw();
			TPaveLabel *p0b01 = new TPaveLabel(0.2165,0.8840,0.2495,0.9170,"01");
			p0b01->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b01->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b01->SetFillColor(3); 
			p0b01->Draw();
			TPaveLabel *p0b02 = new TPaveLabel(0.2165,0.8510,0.2495,0.8840,"02");
			p0b02->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b02->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b02->SetFillColor(3); 
			p0b02->Draw();
			TPaveLabel *p0b03 = new TPaveLabel(0.2165,0.8180,0.2495,0.8510,"03");
			p0b03->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b03->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b03->SetFillColor(3); 
			p0b03->Draw();
			TPaveLabel *p0b04 = new TPaveLabel(0.2165,0.7850,0.2495,0.8180,"04");
			p0b04->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b04->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b04->SetFillColor(3); 
			p0b04->Draw();
			TPaveLabel *p0b05 = new TPaveLabel(0.2165,0.7520,0.2495,0.7850,"05");
			p0b05->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b05->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b05->SetFillColor(3); 
			p0b05->Draw();
			TPaveLabel *p0b06 = new TPaveLabel(0.2165,0.7190,0.2495,0.7520,"06");
			p0b06->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b06->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b06->SetFillColor(3); 
			p0b06->Draw();
			TPaveLabel *p0b07 = new TPaveLabel(0.2165,0.6860,0.2495,0.7190,"07");
			p0b07->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b07->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b07->SetFillColor(3); 
			p0b07->Draw();
			TPaveLabel *p0b08 = new TPaveLabel(0.2165,0.6530,0.2495,0.6860,"08");
			p0b08->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b08->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b08->SetFillColor(3); 
			p0b08->Draw();
			TPaveLabel *p0b09 = new TPaveLabel(0.2165,0.6200,0.2495,0.6530,"09");
			p0b09->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b09->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b09->SetFillColor(3); 
			p0b09->Draw();
			TPaveLabel *p0b22 = new TPaveLabel(0.2165,0.3470,0.2495,0.3800,"22");
			p0b22->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b22->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b22->SetFillColor(3); 
			p0b22->Draw();
			TPaveLabel *p0b23 = new TPaveLabel(0.2165,0.3140,0.2495,0.3470,"23");
			p0b23->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b23->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b23->SetFillColor(3); 
			p0b23->Draw();
			TPaveLabel *p0b24 = new TPaveLabel(0.2165,0.2810,0.2495,0.3140,"24");
			p0b24->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b24->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b24->SetFillColor(3); 
			p0b24->Draw();
			TPaveLabel *p0b25 = new TPaveLabel(0.2165,0.2480,0.2495,0.2810,"25");
			p0b25->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b25->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b25->SetFillColor(3); 
			p0b25->Draw();
			TPaveLabel *p0b26 = new TPaveLabel(0.2165,0.2150,0.2495,0.2480,"26");
			p0b26->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b26->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b26->SetFillColor(3); 
			p0b26->Draw();
			TPaveLabel *p0b27 = new TPaveLabel(0.2165,0.1820,0.2495,0.2150,"27");
			p0b27->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b27->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b27->SetFillColor(3); 
			p0b27->Draw();
			TPaveLabel *p0b28 = new TPaveLabel(0.2165,0.1490,0.2495,0.1820,"28");
			p0b28->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b28->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b28->SetFillColor(3); 
			p0b28->Draw();
			TPaveLabel *p0b29 = new TPaveLabel(0.2165,0.1160,0.2495,0.1490,"29");
			p0b29->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b29->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b29->SetFillColor(3); 
			p0b29->Draw();
			TPaveLabel *p0b30 = new TPaveLabel(0.2165,0.0830,0.2495,0.1160,"29");
			p0b30->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b30->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b30->SetFillColor(3); 
			p0b30->Draw();
			TPaveLabel *p0b31 = new TPaveLabel(0.2165,0.0500,0.2495,0.0830,"31");
			p0b31->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p0")) p0b31->SetFillColor(2); 
			if (goodPlane.Contains("nd.p0")) p0b31->SetFillColor(3); 
			p0b31->Draw();

			// This set is for Plane 1
			TPaveLabel *p1b00 = new TPaveLabel(0.2525,0.9200,0.4175,0.9500,"00");
			p1b00->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b00->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b00->SetFillColor(3);
			p1b00->Draw();
			TPaveLabel *p1b01 = new TPaveLabel(0.2525,0.8900,0.4175,0.9200,"01");
			p1b01->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b01->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b01->SetFillColor(3);
			p1b01->Draw();
			TPaveLabel *p1b02 = new TPaveLabel(0.2525,0.8600,0.4175,0.8900,"02");
			p1b02->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b02->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b02->SetFillColor(3);
			p1b02->Draw();
			TPaveLabel *p1b03 = new TPaveLabel(0.2525,0.8300,0.4175,0.8600,"03");
			p1b03->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b03->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b03->SetFillColor(3);
			p1b03->Draw();
			TPaveLabel *p1b04 = new TPaveLabel(0.2525,0.8000,0.4175,0.8300,"04");
			p1b04->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b04->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b04->SetFillColor(3);
			p1b04->Draw();
			TPaveLabel *p1b05 = new TPaveLabel(0.2525,0.7700,0.4175,0.8000,"05");
			p1b05->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b05->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b05->SetFillColor(3);
			p1b05->Draw();
			TPaveLabel *p1b06 = new TPaveLabel(0.2525,0.7400,0.4175,0.7700,"06");
			p1b06->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b06->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b06->SetFillColor(3);
			p1b06->Draw();
			TPaveLabel *p1b07 = new TPaveLabel(0.2525,0.7100,0.4175,0.7400,"07");
			p1b07->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b07->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b07->SetFillColor(3);
			p1b07->Draw();
			TPaveLabel *p1b08 = new TPaveLabel(0.2525,0.6800,0.4175,0.7100,"08");
			p1b08->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b08->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b08->SetFillColor(3);
			p1b08->Draw();
			TPaveLabel *p1b09 = new TPaveLabel(0.2525,0.6500,0.4175,0.6800,"09");
			p1b09->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b09->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b09->SetFillColor(3);
			p1b09->Draw();
			TPaveLabel *p1b10 = new TPaveLabel(0.2525,0.6200,0.4175,0.6500,"10");
			p1b10->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b10->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b10->SetFillColor(3);
			p1b10->Draw();
			TPaveLabel *p1b11 = new TPaveLabel(0.2525,0.5900,0.4175,0.6200,"11");
			p1b11->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b11->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b11->SetFillColor(3);
			p1b11->Draw();
			TPaveLabel *p1b12 = new TPaveLabel(0.2525,0.5600,0.4175,0.5900,"12");
			p1b12->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b12->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b12->SetFillColor(3);
			p1b12->Draw();
			TPaveLabel *p1b13 = new TPaveLabel(0.2525,0.5300,0.4175,0.5600,"13");
			p1b13->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b13->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b13->SetFillColor(3);
			p1b13->Draw();
			TPaveLabel *p1b14 = new TPaveLabel(0.2525,0.5000,0.4175,0.5300,"14");
			p1b14->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b14->SetFillColor(2); 
			if (goodPlane.Contains("nd.p1")) p1b14->SetFillColor(3); 
			p1b14->Draw();
			TPaveLabel *p1b15 = new TPaveLabel(0.2525,0.4700,0.4175,0.5000,"15");
			p1b15->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b15->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b15->SetFillColor(3);
			p1b15->Draw();
			TPaveLabel *p1b16 = new TPaveLabel(0.2525,0.4400,0.4175,0.4700,"16");
			p1b16->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b16->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b16->SetFillColor(3);
			p1b16->Draw();
			TPaveLabel *p1b17 = new TPaveLabel(0.2525,0.4100,0.4175,0.4400,"17");
			p1b17->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b17->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b17->SetFillColor(3);
			p1b17->Draw();
			TPaveLabel *p1b18 = new TPaveLabel(0.2525,0.3800,0.4175,0.4100,"18");
			p1b18->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b18->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b18->SetFillColor(3);
			p1b18->Draw();
			TPaveLabel *p1b19 = new TPaveLabel(0.2525,0.3500,0.4175,0.3800,"19");
			p1b19->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b19->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b19->SetFillColor(3);
			p1b19->Draw();
			TPaveLabel *p1b20 = new TPaveLabel(0.2525,0.3200,0.4175,0.3500,"20");
			p1b20->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b20->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b20->SetFillColor(3);
			p1b20->Draw();
			TPaveLabel *p1b21 = new TPaveLabel(0.2525,0.2900,0.4175,0.3200,"21");
			p1b21->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b21->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b21->SetFillColor(3);
			p1b21->Draw();
			TPaveLabel *p1b22 = new TPaveLabel(0.2525,0.2600,0.4175,0.2900,"22");
			p1b22->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b22->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b22->SetFillColor(3);
			p1b22->Draw();
			TPaveLabel *p1b23 = new TPaveLabel(0.2525,0.2300,0.4175,0.2600,"23");
			p1b23->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b23->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b23->SetFillColor(3);
			p1b23->Draw();
			TPaveLabel *p1b24 = new TPaveLabel(0.2525,0.2000,0.4175,0.2300,"24");
			p1b24->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b24->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b24->SetFillColor(3);
			p1b24->Draw();
			TPaveLabel *p1b25 = new TPaveLabel(0.2525,0.1700,0.4175,0.2000,"25");
			p1b25->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b25->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b25->SetFillColor(3);
			p1b25->Draw();
			TPaveLabel *p1b26 = new TPaveLabel(0.2525,0.1400,0.4175,0.1700,"26");
			p1b26->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b26->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b26->SetFillColor(3);
			p1b26->Draw();
			TPaveLabel *p1b27 = new TPaveLabel(0.2525,0.1100,0.4175,0.1400,"27");
			p1b27->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b27->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b27->SetFillColor(3);
			p1b27->Draw();
			TPaveLabel *p1b28 = new TPaveLabel(0.2525,0.0800,0.4175,0.1100,"28");
			p1b28->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b28->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b28->SetFillColor(3);
			p1b28->Draw();
			TPaveLabel *p1b29 = new TPaveLabel(0.2525,0.0500,0.4175,0.0800,"29");
			p1b29->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p1")) p1b29->SetFillColor(2);
			if (goodPlane.Contains("nd.p1")) p1b29->SetFillColor(3);
			p1b29->Draw();

			// This set is for Plane 2
			TPaveLabel *p2b00 = new TPaveLabel(0.4200,0.9125,0.5850,0.9500,"00");
			p2b00->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b00->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b00->SetFillColor(3);
			p2b00->Draw();
			TPaveLabel *p2b01 = new TPaveLabel(0.4200,0.8750,0.5850,0.9125,"01");
			p2b01->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b01->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b01->SetFillColor(3);
			p2b01->Draw();
			TPaveLabel *p2b02 = new TPaveLabel(0.4200,0.8375,0.5850,0.8750,"02");
			p2b02->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b02->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b02->SetFillColor(3);
			p2b02->Draw();
			TPaveLabel *p2b03 = new TPaveLabel(0.4200,0.8000,0.5850,0.8375,"03");
			p2b03->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b03->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b03->SetFillColor(3);
			p2b03->Draw();
			TPaveLabel *p2b04 = new TPaveLabel(0.4200,0.7625,0.5850,0.8000,"04");
			p2b04->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b04->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b04->SetFillColor(3);
			p2b04->Draw();
			TPaveLabel *p2b05 = new TPaveLabel(0.4200,0.7250,0.5850,0.7625,"05");
			p2b05->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b05->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b05->SetFillColor(3);
			p2b05->Draw();
			TPaveLabel *p2b06 = new TPaveLabel(0.4200,0.6875,0.5850,0.7250,"06");
			p2b06->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b06->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b06->SetFillColor(3);
			p2b06->Draw();
			TPaveLabel *p2b07 = new TPaveLabel(0.4200,0.6500,0.5850,0.6875,"07");
			p2b07->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b07->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b07->SetFillColor(3);
			p2b07->Draw();
			TPaveLabel *p2b08 = new TPaveLabel(0.4200,0.6125,0.5850,0.6500,"08");
			p2b08->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b08->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b08->SetFillColor(3);
			p2b08->Draw();
			TPaveLabel *p2b09 = new TPaveLabel(0.4200,0.5750,0.5850,0.6125,"09");
			p2b09->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b09->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b09->SetFillColor(3);
			p2b09->Draw();
			TPaveLabel *p2b10 = new TPaveLabel(0.4200,0.5375,0.5850,0.5750,"10");
			p2b10->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b10->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b10->SetFillColor(3);
			p2b10->Draw();
			TPaveLabel *p2b11 = new TPaveLabel(0.4200,0.5000,0.5850,0.5375,"11");
			p2b11->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b11->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b11->SetFillColor(3);
			p2b11->Draw();
			TPaveLabel *p2b12 = new TPaveLabel(0.4200,0.4625,0.5850,0.5000,"12");
			p2b12->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b12->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b12->SetFillColor(3);
			p2b12->Draw();
			TPaveLabel *p2b13 = new TPaveLabel(0.4200,0.4250,0.5850,0.4625,"13");
			p2b13->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b13->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b13->SetFillColor(3);
			p2b13->Draw();
			TPaveLabel *p2b14 = new TPaveLabel(0.4200,0.3875,0.5850,0.4250,"14");
			p2b14->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b14->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b14->SetFillColor(3);
			p2b14->Draw();
			TPaveLabel *p2b15 = new TPaveLabel(0.4200,0.3500,0.5850,0.3875,"15");
			p2b15->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b15->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b15->SetFillColor(3);
			p2b15->Draw();
			TPaveLabel *p2b16 = new TPaveLabel(0.4200,0.3125,0.5850,0.3500,"16");
			p2b16->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b16->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b16->SetFillColor(3);
			p2b16->Draw();
			TPaveLabel *p2b17 = new TPaveLabel(0.4200,0.2750,0.5850,0.3125,"17");
			p2b17->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b17->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b17->SetFillColor(3);
			p2b17->Draw();
			TPaveLabel *p2b18 = new TPaveLabel(0.4200,0.2375,0.5850,0.2750,"18");
			p2b18->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b18->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b18->SetFillColor(3);
			p2b18->Draw();
			TPaveLabel *p2b19 = new TPaveLabel(0.4200,0.2000,0.5850,0.2375,"19");
			p2b19->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b19->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b19->SetFillColor(3);
			p2b19->Draw();
			TPaveLabel *p2b20 = new TPaveLabel(0.4200,0.1625,0.5850,0.2000,"20");
			p2b20->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b20->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b20->SetFillColor(3);
			p2b20->Draw();
			TPaveLabel *p2b21 = new TPaveLabel(0.4200,0.1250,0.5850,0.1625,"21");
			p2b21->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b21->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b21->SetFillColor(3);
			p2b21->Draw();
			TPaveLabel *p2b22 = new TPaveLabel(0.4200,0.0875,0.5850,0.1250,"22");
			p2b22->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b22->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b22->SetFillColor(3);
			p2b22->Draw();
			TPaveLabel *p2b23 = new TPaveLabel(0.4200,0.0500,0.5850,0.0875,"23");
			p2b23->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p2")) p2b23->SetFillColor(2);
			if ( goodPlane.Contains("nd.p2")) p2b23->SetFillColor(3);
			p2b23->Draw();
			
			// This set is for Plane 3
			TPaveLabel *p3b00 = new TPaveLabel(0.5850,0.9050,0.7500,0.9500,"00");
			p3b00->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b00->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b00->SetFillColor(3);
			p3b00->Draw();
			TPaveLabel *p3b01 = new TPaveLabel(0.5850,0.8600,0.7500,0.9050,"01");
			p3b01->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b01->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b01->SetFillColor(3);
			p3b01->Draw();
			TPaveLabel *p3b02 = new TPaveLabel(0.5850,0.8150,0.7500,0.8600,"02");
			p3b02->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b02->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b02->SetFillColor(3);
			p3b02->Draw();
			TPaveLabel *p3b03 = new TPaveLabel(0.5850,0.7700,0.7500,0.8150,"03");
			p3b03->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b03->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b03->SetFillColor(3);
			p3b03->Draw();
			TPaveLabel *p3b04 = new TPaveLabel(0.5850,0.7250,0.7500,0.7700,"04");
			p3b04->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b04->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b04->SetFillColor(3);
			p3b04->Draw();
			TPaveLabel *p3b05 = new TPaveLabel(0.5850,0.6800,0.7500,0.7250,"05");
			p3b05->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b05->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b05->SetFillColor(3);
			p3b05->Draw();
			TPaveLabel *p3b06 = new TPaveLabel(0.5850,0.6425,0.7500,0.6800,"06");
			p3b06->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b06->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b06->SetFillColor(3);
			p3b06->Draw();
			TPaveLabel *p3b07 = new TPaveLabel(0.5850,0.6050,0.7500,0.6425,"07");
			p3b07->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b07->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b07->SetFillColor(3);
			p3b07->Draw();
			TPaveLabel *p3b08 = new TPaveLabel(0.5850,0.5675,0.7500,0.6050,"08");
			p3b08->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b08->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b08->SetFillColor(3);
			p3b08->Draw();
			TPaveLabel *p3b09 = new TPaveLabel(0.5850,0.5300,0.7500,0.5675,"09");
			p3b09->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b09->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b09->SetFillColor(3);
			p3b09->Draw();
			TPaveLabel *p3b10 = new TPaveLabel(0.5850,0.5000,0.7500,0.5300,"10");
			p3b10->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b10->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b10->SetFillColor(3);
			p3b10->Draw();
			TPaveLabel *p3b11 = new TPaveLabel(0.5850,0.4700,0.7500,0.5000,"11");
			p3b11->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b11->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b11->SetFillColor(3);
			p3b11->Draw();
			TPaveLabel *p3b12 = new TPaveLabel(0.5850,0.4325,0.7500,0.4700,"12");
			p3b12->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b12->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b12->SetFillColor(3);
			p3b12->Draw();
			TPaveLabel *p3b13 = new TPaveLabel(0.5850,0.3950,0.7500,0.4325,"13");
			p3b13->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b13->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b13->SetFillColor(3);
			p3b13->Draw();
			TPaveLabel *p3b14 = new TPaveLabel(0.5850,0.3575,0.7500,0.3950,"14");
			p3b14->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b14->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b14->SetFillColor(3);
			p3b14->Draw();
			TPaveLabel *p3b15 = new TPaveLabel(0.5850,0.3200,0.7500,0.3575,"15");
			p3b15->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b15->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b15->SetFillColor(3);
			p3b15->Draw();
			TPaveLabel *p3b16 = new TPaveLabel(0.5850,0.2750,0.7500,0.3200,"16");
			p3b16->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b16->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b16->SetFillColor(3);
			p3b16->Draw();
			TPaveLabel *p3b17 = new TPaveLabel(0.5850,0.2300,0.7500,0.2750,"17");
			p3b17->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b17->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b17->SetFillColor(3);
			p3b17->Draw();
			TPaveLabel *p3b18 = new TPaveLabel(0.5850,0.1850,0.7500,0.2300,"18");
			p3b18->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b18->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b18->SetFillColor(3);
			p3b18->Draw();
			TPaveLabel *p3b19 = new TPaveLabel(0.5850,0.1400,0.7500,0.1850,"19");
			p3b19->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b19->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b19->SetFillColor(3);
			p3b19->Draw();
			TPaveLabel *p3b20 = new TPaveLabel(0.5850,0.0950,0.7500,0.1400,"20");
			p3b20->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b20->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b20->SetFillColor(3);
			p3b20->Draw();
			TPaveLabel *p3b21 = new TPaveLabel(0.5850,0.0500,0.7500,0.0950,"21");
			p3b21->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p3")) p3b21->SetFillColor(2);
			if ( goodPlane.Contains("nd.p3")) p3b21->SetFillColor(3);
			p3b21->Draw();

			// This set is for Plane 4
			TPaveLabel *p4b00 = new TPaveLabel(0.7500,0.8750,0.9150,0.9500,"00");
			p4b00->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p4")) p4b00->SetFillColor(2);
			if ( goodPlane.Contains("nd.p4")) p4b00->SetFillColor(3);
			p4b00->Draw();
			TPaveLabel *p4b01 = new TPaveLabel(0.7500,0.8000,0.9150,0.8750,"01");
			p4b01->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p4")) p4b01->SetFillColor(2);
			if ( goodPlane.Contains("nd.p4")) p4b01->SetFillColor(3);
			p4b01->Draw();
			TPaveLabel *p4b02 = new TPaveLabel(0.7500,0.7250,0.9150,0.8000,"02");
			p4b02->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p4")) p4b02->SetFillColor(2);
			if ( goodPlane.Contains("nd.p4")) p4b02->SetFillColor(3);
			p4b02->Draw();
			TPaveLabel *p4b03 = new TPaveLabel(0.7500,0.6500,0.9150,0.7250,"03");
			p4b03->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p4")) p4b03->SetFillColor(2);
			if ( goodPlane.Contains("nd.p4")) p4b03->SetFillColor(3);
			p4b03->Draw();
			TPaveLabel *p4b04 = new TPaveLabel(0.7500,0.5750,0.9150,0.6500,"04");
			p4b04->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p4")) p4b04->SetFillColor(2);
			if ( goodPlane.Contains("nd.p4")) p4b04->SetFillColor(3);
			p4b04->Draw();
			TPaveLabel *p4b05 = new TPaveLabel(0.7500,0.5000,0.9150,0.5750,"05");
			p4b05->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p4")) p4b05->SetFillColor(2);
			if ( goodPlane.Contains("nd.p4")) p4b05->SetFillColor(3);
			p4b05->Draw();
			TPaveLabel *p4b06 = new TPaveLabel(0.7500,0.4250,0.9150,0.5000,"06");
			p4b06->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p4")) p4b06->SetFillColor(2);
			if ( goodPlane.Contains("nd.p4")) p4b06->SetFillColor(3);
			p4b06->Draw();
			TPaveLabel *p4b07 = new TPaveLabel(0.7500,0.3500,0.9150,0.4250,"07");
			p4b07->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p4")) p4b07->SetFillColor(2);
			if ( goodPlane.Contains("nd.p4")) p4b07->SetFillColor(3);
			p4b07->Draw();
			TPaveLabel *p4b08 = new TPaveLabel(0.7500,0.2750,0.9150,0.3500,"08");
			p4b08->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p4")) p4b08->SetFillColor(2);
			if ( goodPlane.Contains("nd.p4")) p4b08->SetFillColor(3);
			p4b08->Draw();
			TPaveLabel *p4b09 = new TPaveLabel(0.7500,0.2000,0.9150,0.2750,"09");
			p4b09->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p4")) p4b09->SetFillColor(2);
			if ( goodPlane.Contains("nd.p4")) p4b09->SetFillColor(3);
			p4b09->Draw();
			TPaveLabel *p4b10 = new TPaveLabel(0.7500,0.1250,0.9150,0.2000,"10");
			p4b10->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p4")) p4b10->SetFillColor(2);
			if ( goodPlane.Contains("nd.p4")) p4b10->SetFillColor(3);
			p4b10->Draw();
			TPaveLabel *p4b11 = new TPaveLabel(0.7500,0.0500,0.9150,0.1250,"11");
			p4b11->SetFillColor(38);
			if (includeVetos && allVetos.Contains("nd.p4")) p4b11->SetFillColor(2);
			if ( goodPlane.Contains("nd.p4")) p4b11->SetFillColor(3);
			p4b11->Draw();
			
			handpad01->Update();

			handpad02->cd();
			TString titleToF = "Time of Flight for Plane #";
//			TString titleToF = "Time of Flight v. Beta for Plane #";
			titleToF += nplane;
			titleToF += ", Bar # 11";
			if (includeVetos) titleToF += " with vetos";
			else titleToF += " without vetos";
			cout << "Drawing " << titleToF << "..." << endl;
			TString plotToF = "ToF_p";
			plotToF += nplane;
			TH1F *histToF = new TH1F(plotToF, titleToF, ToFbins, ToFmin, ToFmax);
//			TH2F *histToF = new TH2F(plotToF, titleToF, 100,0.007,0.04,150,650,800);
			if (includeVetos)
			{
				TString vetocut = "";
				if (nplane==1)
				{
					vetocut = "(NA.veto.lt_c<1400 || NA.veto.lt_c>1600) && (NA.veto.rt_c<1400 || NA.veto.rt_c>1600)";
				}
				if (nplane > 1)
				{
					vetocut = "(NA.nd.p";
					vetocut += nplane-1;
					vetocut += ".lt_c<1350 || NA.nd.p";
					vetocut += nplane-1;
					vetocut += ".lt_c>1450) && (NA.nd.p";
					vetocut += nplane-1;
					vetocut += ".rt_c<1350 || NA.nd.p";
					vetocut += nplane-1;
					vetocut += ".rt_c>1450)";

/*					vetocut =  "(NA.nd.p1.lt_c[13]<1350 || NA.nd.p1.lt_c[13]>1450) && (NA.nd.p1.rt_c[13]>1350 || NA.nd.p1.rt_c[13]>1450) &&";
					vetocut += "(NA.nd.p1.lt_c[14]<1350 || NA.nd.p1.lt_c[14]>1450) && (NA.nd.p1.rt_c[14]>1350 || NA.nd.p1.rt_c[14]>1450) &&";
					vetocut += "(NA.nd.p1.lt_c[15]<1350 || NA.nd.p1.lt_c[15]>1450) && (NA.nd.p1.rt_c[15]>1350 || NA.nd.p1.rt_c[15]>1450)";


					vetocut += "(NA.nd.p2.lt_c[10]<1350 || NA.nd.p2.lt_c[10]>1450) && (NA.nd.p2.rt_c[10]>1350 || NA.nd.p2.rt_c[10]>1450) &&";
					vetocut += "(NA.nd.p2.lt_c[12]<1350 || NA.nd.p2.lt_c[12]>1450) && (NA.nd.p2.rt_c[12]>1350 || NA.nd.p2.rt_c[12]>1450)";
*/

				}
				TCut vetoscut = vetocut;
				cout << "For plane " << nplane << " the veto cut was " << vetocut << endl;
			}
			else TCut vetoscut = "";
			TString thisplane = "NA.n.plane==";
			thisplane += nplane-1;
			thisplane += " && NA.n.pad==11";
			TCut thisplanecut = thisplane;
//			TString ToFplots = "NA.n.tof:R.tr.beta>>";
			TString ToFplots = "NA.n.tof>>";
			ToFplots += plotToF;
			chainHe->Draw(ToFplots, cuts && thisplanecut && vetoscut, "");
//			histToF->Draw("COLZ");
			histToF->Draw();
			handpad02->Update();

/*			TString titleTDCleftNoVetos = "Left TDC for Plane #";
			titleTDCleftNoVetos += nplane;
			if (includeVetos) titleTDCleftNoVetos += " with vetos";
			else titleTDCleftNoVetos += " without vetos";
			cout << "Drawing " << titleTDCleftNoVetos << "..." << endl;
			TString plotTDCleftNoVetos = "TDCleftNoVetos_p";
			plotTDCleftNoVetos += nplane;
			TH2F *TDCleftNoVetos = new TH2F(plotTDCleftNoVetos,titleTDCleftNoVetos,TDCbins,TDCmin,TDCmax,padBins,padMin,padMax);
			TString TDCleftNoVetosTDC = "NA.n.pad:NA.nd.p";
			TDCleftNoVetosTDC += nplane;
			TDCleftNoVetosTDC += ".lt_c[NA.n.pad]>>";
			if (goodPlane=="nd.p0") TDCleftNoVetosTDC = "NA.n.pad:NA.veto.lt[NA.n.pad]_c>>";
			TDCleftNoVetosTDC += plotTDCleftNoVetos;
			TString TDCvetoCutL = "NA.nd.p";
			TDCvetoCutL += vetoplane;
			TDCvetoCutL += ".lt_c<1";
			TString lADCcutForTDC = "NA.nd.p";
			lADCcutForTDC += nplane;
			if (nplane==0) lADCcutForTDC = "NA.veto"; 
			lADCcutForTDC += ".la_c[NA.n.pad]>150";
			TCut lADCforTDC = lADCcutForTDC;
			if (vetoplane==0) lADCcutForTDC = "NA.veto.la[NA.n.pad]>150";
			if (vetoplane==0) TDCvetoCutL="NA.veto.lt_c<1";
			if (vetoplane==-1) TDCvetoCutL="";
			TCut TDCvetoL = TDCvetoCutL;
			if (includeVetos) chainHe->Draw(TDCleftNoVetosTDC, cuts && TDCvetoL && lADCforTDC,"");
			else chainHe->Draw(TDCleftNoVetosTDC, cuts && lADCforTDC,"");
			TDCleftNoVetos->Draw("COLZ");
			handpad02->Update();


			handpad03->cd();
			TString titleTDCrightNoVetos = "Right TDC for Plane #";
			titleTDCrightNoVetos += nplane;
			if (includeVetos) titleTDCrightNoVetos += " with vetos";
			else titleTDCrightNoVetos += " without vetos";
			cout << "Drawing " << titleTDCrightNoVetos << "..." << endl;
			TString plotTDCrightNoVetos = "TDCrightNoVetos_p";
			plotTDCrightNoVetos += nplane;
			TH2F *TDCrightNoVetos = new TH2F(plotTDCrightNoVetos,titleTDCrightNoVetos,TDCbins,TDCmin,TDCmax,padBins,padMin,padMax);
			TString TDCrightNoVetosTDC = "NA.n.pad:NA.nd.p";
			TDCrightNoVetosTDC += nplane;
			TDCrightNoVetosTDC += ".rt_c[NA.n.pad]>>";
			if (goodPlane=="nd.p0") TDCrightNoVetosTDC = "NA.n.pad:NA.veto.rt_c[NA.n.pad]>>";
			TDCrightNoVetosTDC += plotTDCrightNoVetos;
			TString TDCvetoCutR = "NA.nd.p";
			TDCvetoCutR += vetoplane;
			TDCvetoCutR += ".rt_c<1";
			if (vetoplane==0) TDCvetoCutR="NA.veto.rt_c<1";
			if (vetoplane==-1) TDCvetoCutR="";
			TCut TDCvetoR = TDCvetoCutR;
			TString rADCcutForTDC = "NA.nd.p";
			rADCcutForTDC += nplane;
			if (nplane==0) rADCcutForTDC = "NA.veto"; 
			rADCcutForTDC += ".ra_c[NA.n.pad]>150";
			TCut rADCforTDC = rADCcutForTDC;
			if (includeVetos) chainHe->Draw(TDCrightNoVetosTDC, cuts && TDCvetoR && rADCforTDC,"");
			else chainHe->Draw(TDCrightNoVetosTDC,rADCforTDC && cuts,"");
			TDCrightNoVetos->Draw("COLZ");
			handpad03->Update();

			handpad06->cd();
			TString titleTDCsNoVetos = "Right TDC - Left TDC for Plane #";
			titleTDCsNoVetos += nplane;
			if (includeVetos) titleTDCsNoVetos += " with vetos";
			else titleTDCsNoVetos += " without vetos";
			cout << "Drawing " << titleTDCsNoVetos << "..." << endl;
			TString plotTDCsNoVetos = "TDCsNoVetos_p";
			plotTDCsNoVetos += nplane;
			TH2F *TDCsNoVetos = new TH2F(plotTDCsNoVetos,titleTDCsNoVetos,80,-40,40,padBins,padMin,padMax);
			TString TDCsNoVetosTDC = "NA.n.pad:(NA.nd.p";
			TDCsNoVetosTDC += nplane;
			TDCsNoVetosTDC += ".rt_c[NA.n.pad] - NA.nd.p";
			TDCsNoVetosTDC += nplane;
			TDCsNoVetosTDC += ".lt_c[NA.n.pad])>>";
			if (goodPlane=="nd.p0") TDCsNoVetosTDC = "NA.n.pad:(NA.veto.rt_c[NA.n.pad] - NA.veto.lt_c[NA.n.pad])>>";
			TDCsNoVetosTDC += plotTDCsNoVetos;
			if (includeVetos) chainHe->Draw(TDCsNoVetosTDC, cuts && TDCvetoR && TDCvetoL && rADCforTDC && lADCforTDC,"");
			else chainHe->Draw(TDCsNoVetosTDC,rADCforTDC && cuts && lADCforTDC,"");
			TDCsNoVetos->Draw("COLZ");
			handpad06->Update();

			handpad04->cd();
			TString titleADCleftNoVetos = "Left ADC for Plane #";
			titleADCleftNoVetos += nplane;
			if (includeVetos) titleADCleftNoVetos += " with vetos";
			else titleADCleftNoVetos += " without vetos";
			cout << "Drawing " << titleADCleftNoVetos << "..." << endl;
			TString plotADCleftNoVetos = "ADCleftNoVetos_p";
			plotADCleftNoVetos += nplane;
			TH2F *ADCleftNoVetos = new TH2F(plotADCleftNoVetos,titleADCleftNoVetos,ADCbins,ADCmin,ADCmax,padBins,padMin,padMax);
			TString ADCleftNoVetosADC = "NA.n.pad:NA.nd.p";
			ADCleftNoVetosADC += nplane;
			ADCleftNoVetosADC += ".la_c[NA.n.pad]>>";
			if (goodPlane=="nd.p0") ADCleftNoVetosADC = "NA.n.pad:NA.veto.la_c[NA.n.pad]>>";
			ADCleftNoVetosADC += plotADCleftNoVetos;
			TString ADCvetoCutL = "NA.nd.p";
			ADCvetoCutL += vetoplane;
			ADCvetoCutL += ".la_c<1";
			if (vetoplane==0) ADCvetoCutL="NA.veto.la_c<1";
			if (vetoplane==-1) ADCvetoCutL="";
			TCut ADCvetoL = ADCvetoCutL;
			if (includeVetos) chainHe->Draw(ADCleftNoVetosADC, cuts && ADCvetoL && lADCforTDC,"");
			else chainHe->Draw(ADCleftNoVetosADC, cuts && lADCforTDC,"");
			ADCleftNoVetos->Draw("COLZ");
			handpad04->Update();


			handpad05->cd();
			TString titleADCrightNoVetos = "Right ADC for Plane #";
			titleADCrightNoVetos += nplane;
			if (includeVetos) titleADCrightNoVetos += " with vetos";
			else titleADCrightNoVetos += " without vetos";
			cout << "Drawing " << titleADCrightNoVetos << "..." << endl;
			TString plotADCrightNoVetos = "ADCrightNoVetos_p";
			plotADCrightNoVetos += nplane;
			TH2F *ADCrightNoVetos = new TH2F(plotADCrightNoVetos,titleADCrightNoVetos,ADCbins,ADCmin,ADCmax,padBins,padMin,padMax);
			TString ADCrightNoVetosADC = "NA.n.pad:NA.nd.p";
			ADCrightNoVetosADC += nplane;
			ADCrightNoVetosADC += ".ra_c[NA.n.pad]>>";
			if (goodPlane=="nd.p0") ADCrightNoVetosADC = "NA.n.pad:NA.veto.ra_c[NA.n.pad]>>";
			ADCrightNoVetosADC += plotADCrightNoVetos;
			TString ADCvetoCutR = "NA.nd.p";
			ADCvetoCutR += vetoplane;
			ADCvetoCutR += ".ra_c<1";
			if (vetoplane==0) ADCvetoCutR="NA.veto.ra_c<1";
			if (vetoplane==-1) ADCvetoCutR="";
			TCut ADCvetoR = ADCvetoCutR;
			if (includeVetos) chainHe->Draw(ADCrightNoVetosADC, cuts && ADCvetoR && rADCforTDC,"");
			else chainHe->Draw(ADCrightNoVetosADC, cuts && rADCforTDC,"");
			ADCrightNoVetos->Draw("COLZ");
			handpad05->Update();

			handpad07->cd();
			TString titleADCsNoVetos = "Right ADC - Left ADC for Plane #";
			titleADCsNoVetos += nplane;
			if (includeVetos) titleADCsNoVetos += " with vetos";
			else titleADCsNoVetos += " without vetos";
			cout << "Drawing " << titleADCsNoVetos << "..." << endl;
			TString plotADCsNoVetos = "ADCsNoVetos_p";
			plotADCsNoVetos += nplane;
			TH2F *ADCsNoVetos = new TH2F(plotADCsNoVetos,titleADCsNoVetos,80,-40,40,padBins,padMin,padMax);
			TString ADCsNoVetosADC = "NA.n.pad:(NA.nd.p";
			ADCsNoVetosADC += nplane;
			ADCsNoVetosADC += ".ra_c[NA.n.pad] - NA.nd.p";
			ADCsNoVetosADC += nplane;
			ADCsNoVetosADC += ".la_c[NA.n.pad])>>";
			if (goodPlane=="nd.p0") ADCsNoVetosADC = "NA.n.pad:(NA.veto.ra_c[NA.n.pad] - NA.veto.la_c[NA.n.pad])>>";
			ADCsNoVetosADC += plotADCsNoVetos;
			if (includeVetos) chainHe->Draw(ADCsNoVetosADC, cuts && ADCvetoL && ADCvetoR && lADCforTDC && rADCforTDC,"");
			else chainHe->Draw(ADCsNoVetosADC,cuts && lADCforTDC && rADCforTDC,"");
			ADCsNoVetos->Draw("COLZ");
			handpad07->Update();



			TString imageTitle = "plots_for_hand/TDC_and_ADC/HAND_plots_Run_Num_";
			imageTitle += HeRunNumber;
			imageTitle += "-";
			imageTitle += endHeRunNumber;
			imageTitle += "_p";
			imageTitle += nplane;
			if (includeVetos) imageTitle += "_with_vetos";
			else imageTitle += "_without_vetos";
			imageTitle += ".png";
//			imageTitle += "_b";
//			imageTitle += thisbar;
			handCanvas->Print(imageTitle);
*/
	}



	cout << "All done!" << endl;



}







































