


#include "hand_draw.h"

void hand_class_draw_bar_by_bar_cuts(int HeRunNumber, int endHeRunNumber, int nplane, int thisbar, TString allVetos, TString filenameHe, TString kine, TString targ, TString outputPlotsHere, bool includeVetos)
{
//	cout << "vvvvvvvvvvvvvvvvv hand_class_draw_bar_by_bar_cuts.h vvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;

	bool check;
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

	// The bit below is for the Left TDC
	TString plotHANDleft = "HANDleft_p"; plotHANDleft += nplane; plotHANDleft += "_b"; plotHANDleft += thisbar;
	TString plotHANDleftcut = plotHANDleft; plotHANDleftcut += "_cut";
	TString titleHANDleft = "Left TDC for Plane #"; titleHANDleft += nplane; titleHANDleft += ", PMT # "; titleHANDleft += thisbar;
	TString titleHANDleftcut = titleHANDleft; titleHANDleftcut += " cut";
	TH1F *HANDleft = (TH1F*)fileHe.Get(plotHANDleft);
	TH1F *HANDleftcut = (TH1F*)fileHe.Get(plotHANDleftcut);

	// The bit below is for the Right TDC           
	TString plotHANDright = "HANDright_p"; plotHANDright += nplane; plotHANDright += "_b"; plotHANDright += thisbar;
	TString plotHANDrightcut = plotHANDright; plotHANDrightcut += "_cut";
	TString titleHANDright = "Right TDC for Plane #"; titleHANDright += nplane; titleHANDright += ", PMT # "; titleHANDright += thisbar;
	TString titleHANDrightcut = titleHANDright; titleHANDrightcut += " cut";
	TH1F *HANDright = (TH1F*)fileHe.Get(plotHANDright);
	TH1F *HANDrightcut = (TH1F*)fileHe.Get(plotHANDrightcut);

	// The bit below is for the bar-by-bar Theta cuts
	TString titleThetaCut = "Theta for plane "; titleThetaCut += nplane; titleThetaCut += ", bar "; titleThetaCut += thisbar;
	TString plotThetaCut = "th_p"; plotThetaCut += nplane; plotThetaCut += "_b"; plotThetaCut += thisbar;
	TH1F *HeThetaCut = (TH1F*)fileHe.Get(plotThetaCut);

	// The bit below is for the bar-by-bar Phi cuts
	TString titlePhiCut = "Phi plane "; titlePhiCut += nplane; titlePhiCut += ", bar "; titlePhiCut += thisbar;
	TString plotPhiCut = "ph_p"; plotPhiCut += nplane; plotPhiCut += "_b"; plotPhiCut += thisbar;
	TH1F *HePhiCut = (TH1F*)fileHe.Get(plotPhiCut);

	// The bit below is for the bar-by-bar Th:Ph cuts
	TString titleThetaPhiCut = "Theta & Phi for Plane "; titleThetaPhiCut += nplane; titleThetaPhiCut += ", Bar "; titleThetaPhiCut += thisbar;
	TString plotThetaPhiCut = "thph_p"; plotThetaPhiCut += nplane; plotThetaPhiCut += "_b"; plotThetaPhiCut += thisbar;
	TH2F *HeThPhBar = (TH2F*)fileHe.Get(plotThetaPhiCut);

	gStyle->SetPalette(1);
//	cout << "allVetos: " << allVetos << endl;
	TString goodBar = "nd.p";
	goodBar += nplane;
	goodBar += ".";
	goodBar += thisbar;
	goodBar += " ";

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
	handpad04 =  new TPad("handpad04","handpad04",0.1000,0.0000,0.4000,0.5000,0,0,0);
	handpad05 =  new TPad("handpad05","handpad05",0.4000,0.0000,0.7000,0.5000,0,0,0);
	handpad06 =  new TPad("handpad06","handpad06",0.7000,0.0000,1.0000,0.5000,0,0,0);
	handpad01->Draw(); handpad02->Draw(); handpad03->Draw(); handpad04->Draw(); 
	handpad05->Draw(); handpad06->Draw();

	// This section will run hand_draw.h which will draw the HAND in handpad01.
	handpad01->cd();
	hand_draw(HeRunNumber, endHeRunNumber, false, allVetos, goodBar, "");
	handpad01->Update();
	if (nplane==2 && thisbar==11)
	{
		TString qeHANDTitle = outputPlotsHere;
		qeHANDTitle += "qe_hand";
		qeHANDTitle += "_for_Runs_";
		qeHANDTitle += HeRunNumber;
		qeHANDTitle += "-";
		qeHANDTitle += endHeRunNumber;
		if (includeVetos) {qeHANDTitle += "_with_vetos";}
	//      qeHANDTitle += ".eps";
		qeHANDTitle += ".pdf";
		handpad01->Print(qeHANDTitle);
	}

	handpad02->cd();
	HANDleft->Draw();
	HANDleftcut->SetFillColor(kViolet);
	HANDleftcut->Draw("same");
	handpad02->Update();
	if (nplane==2 && thisbar==11)
	{
		TString qelTDCTitle = outputPlotsHere;
		qelTDCTitle += "qe_l_tdc";
		qelTDCTitle += "_for_Runs_";
		qelTDCTitle += HeRunNumber;
		qelTDCTitle += "-";
		qelTDCTitle += endHeRunNumber;
		if (includeVetos) {qelTDCTitle += "_with_vetos";}
	//      qelTDCTitle += ".eps";
		qelTDCTitle += ".svg";
		handpad02->Print(qelTDCTitle);
	}


	handpad03->cd();
	HANDright->Draw();
	HANDrightcut->SetFillColor(kViolet);
	HANDrightcut->Draw("same");
	handpad03->Update();
	if (nplane==2 && thisbar==11)
	{
		TString qerTDCTitle = outputPlotsHere;
		qerTDCTitle += "qe_r_tdc";
		qerTDCTitle += "_for_Runs_";
		qerTDCTitle += HeRunNumber;
		qerTDCTitle += "-";
		qerTDCTitle += endHeRunNumber;
		if (includeVetos) {qerTDCTitle += "_with_vetos";}
	//      qerTDCTitle += ".eps";
		qerTDCTitle += ".svg";
		handpad03->Print(qerTDCTitle);
	}


	handpad04->cd();
	HeThetaCut->Draw();
	handpad04->Update();

	handpad05->cd();
	HeThPhBar->Draw("COLZ");
	handpad05->Update();

	handpad06->cd();
	HePhiCut->Draw();
	handpad06->Update();

	TString barByBarOutTitle = outputPlotsHere;
	barByBarOutTitle += "bar_by_bar_plots_for_Run_Num_";
	barByBarOutTitle += HeRunNumber;
	barByBarOutTitle += "-";
	barByBarOutTitle += endHeRunNumber;
	barByBarOutTitle += "_and_p";
	barByBarOutTitle += nplane;
	barByBarOutTitle += "b";
	if (thisbar<10) {barByBarOutTitle += "0";}
	barByBarOutTitle += thisbar;
	if (includeVetos) {barByBarOutTitle += "_with_vetos";}
	barByBarOutTitle += ".png";
	handCanvas->Print(barByBarOutTitle);



//	cout << "^^^^^^^^^^^^^^^^^ hand_class_draw_bar_by_bar_cuts.h ^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
}
