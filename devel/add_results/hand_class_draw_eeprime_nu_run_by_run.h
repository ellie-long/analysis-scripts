// ************************************************************
//
// This code will plot nuUp and nuDown on a run-by-run basis so
// that the 3He(e,e') Ay asymmetry can be derived from it.
//
// 4/8/2013
// Elena Long
// ellie@jlab.org
// 
// ************************************************************

#include <iostream>
#include <fstream>


//void hand_class_draw_nu(int HeRunNumber, TString filenameHe, TString kine, TString targ, TString& asymOutFile, const int nuBins, double nuMin, double nuMax, TString outputPlotsHere)
void draw_nu(int HeRunNumber, TString filenameHe, TString& asymOutFileText)
{

	cout << "vvvvvvvvvvvvvvvvvv hand_class_eeprime_draw_nu_run_by_run.h vvvvvvvvvvvvvvvvvvvvv" << endl;

	gStyle->SetPalette(1);

	TFile fileHe(filenameHe);

	TH1F *nuUp0 = (TH1F*)fileHe.Get("nuUpAllCuts_Total");
	TH1F *nuUp1 = (TH1F*)fileHe.Get("nuUpAllCuts_bin_1");
	TH1F *nuUp2 = (TH1F*)fileHe.Get("nuUpAllCuts_bin_2");
	TH1F *nuUp3 = (TH1F*)fileHe.Get("nuUpAllCuts_bin_3");
	TH1F *nuUp4 = (TH1F*)fileHe.Get("nuUpAllCuts_bin_4");
	TH1F *nuDown0 = (TH1F*)fileHe.Get("nuDownAllCuts_Total");
	TH1F *nuDown1 = (TH1F*)fileHe.Get("nuDownAllCuts_bin_1");
	TH1F *nuDown2 = (TH1F*)fileHe.Get("nuDownAllCuts_bin_2");
	TH1F *nuDown3 = (TH1F*)fileHe.Get("nuDownAllCuts_bin_3");
	TH1F *nuDown4 = (TH1F*)fileHe.Get("nuDownAllCuts_bin_4");

	int upEvents[5];
	int downEvents[5];

	TString nuCanvasName = "nuCanvas_";
	nuCanvasName += HeRunNumber;
	TCanvas *nuCanvas = new TCanvas(nuCanvasName,"nu Bins",1000,1000); //x,y
	nuPad0u = new TPad("nuPad0u","nuPad0u",0.0,0.8,0.5,1.0,0,0,0);
	nuPad1u = new TPad("nuPad1u","nuPad1u",0.0,0.6,0.5,0.8,0,0,0);
	nuPad2u = new TPad("nuPad2u","nuPad2u",0.0,0.4,0.5,0.6,0,0,0);
	nuPad3u = new TPad("nuPad3u","nuPad3u",0.0,0.2,0.5,0.4,0,0,0);
	nuPad4u = new TPad("nuPad4u","nuPad4u",0.0,0.0,0.5,0.2,0,0,0);
	nuPad0d = new TPad("nuPad0d","nuPad0d",0.5,0.8,1.0,1.0,0,0,0);
	nuPad1d = new TPad("nuPad1d","nuPad1d",0.5,0.6,1.0,0.8,0,0,0);
	nuPad2d = new TPad("nuPad2d","nuPad2d",0.5,0.4,1.0,0.6,0,0,0);
	nuPad3d = new TPad("nuPad3d","nuPad3d",0.5,0.2,1.0,0.4,0,0,0);
	nuPad4d = new TPad("nuPad4d","nuPad4d",0.5,0.0,1.0,0.2,0,0,0);
	nuPad0u->Draw(); nuPad1u->Draw(); nuPad2u->Draw(); nuPad3u->Draw(); nuPad4u->Draw();
	nuPad0d->Draw(); nuPad1d->Draw(); nuPad2d->Draw(); nuPad3d->Draw(); nuPad4d->Draw();

	nuPad0u->cd();
	nuUp0->Draw();
	upEvents[0] = nuUp0->GetEntries();
	nuPad0u->Update();

	nuPad1u->cd();
	nuUp1->Draw();
	upEvents[1] = nuUp1->GetEntries();
	nuPad1u->Update();

	nuPad2u->cd();
	nuUp2->Draw();
	upEvents[2] = nuUp2->GetEntries();
	nuPad2u->Update();

	nuPad3u->cd();
	nuUp3->Draw();
	upEvents[3] = nuUp3->GetEntries();
	nuPad3u->Update();

	nuPad4u->cd();
	nuUp4->Draw();
	upEvents[4] = nuUp4->GetEntries();
	nuPad4u->Update();

	nuPad0d->cd();
	nuDown0->Draw();
	downEvents[0] = nuDown0->GetEntries();
	nuPad0d->Update();

	nuPad1d->cd();
	nuDown1->Draw();
	downEvents[1] = nuDown1->GetEntries();
	nuPad1d->Update();

	nuPad2d->cd();
	nuDown2->Draw();
	downEvents[2] = nuDown2->GetEntries();
	nuPad2d->Update();

	nuPad3d->cd();
	nuDown3->Draw();
	downEvents[3] = nuDown3->GetEntries();
	nuPad3d->Update();

	nuPad4d->cd();
	nuDown4->Draw();
	downEvents[4] = nuDown4->GetEntries();
	nuPad4d->Update();

	asymOutFileText = "";
	asymOutFileText += HeRunNumber;
	for (int i=0; i<5; i++)
	{
		asymOutFileText += " ";
		asymOutFileText += upEvents[i];
		asymOutFileText += " ";
		asymOutFileText += downEvents[i];
	}

	cout << "Run #   TotalUp TotalDown   Bin1Up  Bin1Down    Bin2Up  Bin2Down    Bin3Up  Bin3Down    Bin4Up  Bin4Down" << endl;	
	cout << asymOutFileText << endl;

/*
	TString exitst;
	cout << "Are you ready to finish?" << endl;
	cin >> exitst;
*/
	cout << "^^^^^^^^^^^^^^^^^^ hand_class_eeprime_draw_nu_run_by_run.h ^^^^^^^^^^^^^^^^^^^^^" << endl;
}

