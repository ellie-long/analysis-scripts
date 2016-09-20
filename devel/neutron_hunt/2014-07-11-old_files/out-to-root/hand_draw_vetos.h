// ***************************************************
// This script should plot two sets of plots. One will
// have the veto bar TDCs without the veto cuts and 
// one will have the veto bar TDCs with the veto cuts.
// 
// To run this, first include the header file:
/*
	#include "hand_draw_vetos.h"
*/ 
//
// Then make sure you run hand_define_vetos.h and then
// run:
/*
	hand_draw_vetos(veto1plane, veto2plane, veto3plane, veto4plane, veto5plane, veto6plane,veto1bar, veto2bar, veto3bar, veto4bar, veto5bar, veto6bar, imageVetosWithoutVetosTitle, imageVetosWithVetosTitle, HeRunNumber, endHeRunNumber, chainHe, nplane, thisbar, TDCbins, TDCmin, TDCmax, cuts, vetoTDCs, antivetosAsVetos, allVetos, allAntivetos);
*/
//
//
// ***************************************************

#include "hand_draw.h"

void hand_draw_vetos(TString veto1plane, TString veto2plane, TString veto3plane, TString veto4plane, TString veto5plane, TString veto6plane,TString veto1bar, TString veto2bar, TString veto3bar, TString veto4bar, TString veto5bar, TString veto6bar, TString imageVetosWithoutVetosTitle, TString imageVetosWithVetosTitle, int HeRunNumber, int endHeRunNumber, TChain* chainHe, int nplane, int thisbar, int TDCbins, double TDCmin, double TDCmax, TCut cuts, TCut vetoTDCs, bool antivetosAsVetos, TString allVetos, TString allAntivetos){

	cout << "vvvvvvvvvvvvvvvvvvvvvvvvv hand_draw_vetos.h vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;

	TString goodBar = "nd.p";
	goodBar += nplane;
	goodBar += ".";
	goodBar += thisbar;
	goodBar += " ";


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
	veto1pad01 =  new TPad("veto1pad01","veto1pad01",0.1000,0.7500,0.4000,1.0000,0,0,0);
	veto1pad02 =  new TPad("veto1pad02","veto1pad02",0.1000,0.5000,0.4000,0.7500,0,0,0);
	veto1pad03 =  new TPad("veto1pad03","veto1pad03",0.4000,0.7500,0.7000,1.0000,0,0,0);
	veto1pad04 =  new TPad("veto1pad04","veto1pad04",0.4000,0.5000,0.7000,0.7500,0,0,0);
	veto1pad05 =  new TPad("veto1pad05","veto1pad05",0.7000,0.7500,1.0000,1.0000,0,0,0);
	veto1pad06 =  new TPad("veto1pad06","veto1pad06",0.7000,0.5000,1.0000,0.7500,0,0,0);
	veto1pad07 =  new TPad("veto1pad07","veto1pad07",0.1000,0.2500,0.4000,0.5000,0,0,0);
	veto1pad08 =  new TPad("veto1pad08","veto1pad08",0.1000,0.0000,0.4000,0.2500,0,0,0);
	veto1pad09 =  new TPad("veto1pad09","veto1pad09",0.4000,0.2500,0.7000,0.5000,0,0,0);
	veto1pad10 =  new TPad("veto1pad10","veto1pad10",0.4000,0.0000,0.7000,0.2500,0,0,0);
	veto1pad11 =  new TPad("veto1pad11","veto1pad11",0.7000,0.2500,1.0000,0.5000,0,0,0);
	veto1pad12 =  new TPad("veto1pad12","veto1pad12",0.7000,0.0000,1.0000,0.2500,0,0,0);
	veto1pad13 =  new TPad("veto1pad13","veto1pad13",0.0000,0.0000,0.1000,1.0000,0,0,0);
	veto1pad01->Draw(); veto1pad02->Draw(); veto1pad03->Draw(); veto1pad04->Draw();
	veto1pad05->Draw(); veto1pad06->Draw(); veto1pad07->Draw(); veto1pad08->Draw();
	veto1pad09->Draw(); veto1pad10->Draw(); veto1pad11->Draw(); veto1pad12->Draw();
	veto1pad13->Draw();

	veto1pad13->cd();
	hand_draw(HeRunNumber, endHeRunNumber, antivetosAsVetos, allVetos, goodBar, allAntivetos);
	veto1pad13->Update();

	veto1pad01->cd();
	TString titleVeto1left = "Left TDC for Veto 1 (NA.";
	titleVeto1left += veto1plane;
	titleVeto1left += ".b";
	titleVeto1left += veto1bar;
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
	chainHe->Draw(Veto1rightTDC, cuts,"");
	Veto1right->Draw();
	veto1pad02->Update();

	veto1pad03->cd();
	TString titleVeto2left = "Left TDC for Veto 2 (NA.";
	titleVeto2left += veto2plane;
	titleVeto2left += ".b";
	titleVeto2left += veto2bar;
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
	chainHe->Draw(Veto2rightTDC, cuts,"");
	Veto2right->Draw();
	veto1pad04->Update();

	veto1pad05->cd();
	TString titleVeto3left = "Left TDC for Veto 3 (NA.";
	titleVeto3left += veto3plane;
	titleVeto3left += ".b";
	titleVeto3left += veto3bar;
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
	chainHe->Draw(Veto3rightTDC, cuts,"");
	Veto3right->Draw();
	veto1pad06->Update();

	veto1pad07->cd();
	TString titleVeto4left = "Left TDC for Veto 4 (NA.";
	titleVeto4left += veto4plane;
	titleVeto4left += ".b";
	titleVeto4left += veto4bar;
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
	chainHe->Draw(Veto4rightTDC, cuts,"");
	Veto4right->Draw();
	veto1pad08->Update();

	veto1pad09->cd();
	TString titleVeto5left = "Left TDC for Veto 5 (NA.";
	titleVeto5left += veto5plane;
	titleVeto5left += ".b";
	titleVeto5left += veto5bar;
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
	chainHe->Draw(Veto5rightTDC, cuts,"");
	Veto5right->Draw();
	veto1pad10->Update();

	veto1pad11->cd();
	TString titleVeto6left = "Left TDC for Veto 6 (NA.";
	titleVeto6left += veto6plane;
	titleVeto6left += ".b";
	titleVeto6left += veto6bar;
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
	chainHe->Draw(Veto6rightTDC, cuts,"");
	Veto6right->Draw();
	veto1pad12->Update();


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
	veto2pad01 =  new TPad("veto2pad01","veto2pad01",0.1000,0.7500,0.4000,1.0000,0,0,0);
	veto2pad02 =  new TPad("veto2pad02","veto2pad02",0.1000,0.5000,0.4000,0.7500,0,0,0);
	veto2pad03 =  new TPad("veto2pad03","veto2pad03",0.4000,0.7500,0.7000,1.0000,0,0,0);
	veto2pad04 =  new TPad("veto2pad04","veto2pad04",0.4000,0.5000,0.7000,0.7500,0,0,0);
	veto2pad05 =  new TPad("veto2pad05","veto2pad05",0.7000,0.7500,1.0000,1.0000,0,0,0);
	veto2pad06 =  new TPad("veto2pad06","veto2pad06",0.7000,0.5000,1.0000,0.7500,0,0,0);
	veto2pad07 =  new TPad("veto2pad07","veto2pad07",0.1000,0.2500,0.4000,0.5000,0,0,0);
	veto2pad08 =  new TPad("veto2pad08","veto2pad08",0.1000,0.0000,0.4000,0.2500,0,0,0);
	veto2pad09 =  new TPad("veto2pad09","veto2pad09",0.4000,0.2500,0.7000,0.5000,0,0,0);
	veto2pad10 =  new TPad("veto2pad10","veto2pad10",0.4000,0.0000,0.7000,0.2500,0,0,0);
	veto2pad11 =  new TPad("veto2pad11","veto2pad11",0.7000,0.2500,1.0000,0.5000,0,0,0);
	veto2pad12 =  new TPad("veto2pad12","veto2pad12",0.7000,0.0000,1.0000,0.2500,0,0,0);
	veto2pad13 =  new TPad("veto2pad13","veto2pad13",0.0000,0.0000,0.1000,1.0000,0,0,0);
	veto2pad01->Draw(); veto2pad02->Draw(); veto2pad03->Draw(); veto2pad04->Draw();
	veto2pad05->Draw(); veto2pad06->Draw(); veto2pad07->Draw(); veto2pad08->Draw();
	veto2pad09->Draw(); veto2pad10->Draw(); veto2pad11->Draw(); veto2pad12->Draw();
	veto2pad13->Draw();

	veto2pad13->cd();
	hand_draw(HeRunNumber, endHeRunNumber, antivetosAsVetos, allVetos, goodBar, allAntivetos);
	veto2pad13->Update();


	veto2pad01->cd();
	TString titleVeto1left = "Left TDC for Veto 1 (NA.";
	titleVeto1left += veto1plane;
	titleVeto1left += ".b";
	titleVeto1left += veto1bar;
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
	Veto1right->Draw();
	veto2pad02->Update();

	veto2pad03->cd();
	TString titleVeto2left = "Left TDC for Veto 2 (NA.";
	titleVeto2left += veto2plane;
	titleVeto2left += ".b";
	titleVeto2left += veto2bar;
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
	Veto2right->Draw();
	veto2pad04->Update();

	veto2pad05->cd();
	TString titleVeto3left = "Left TDC for Veto 3 (NA.";
	titleVeto3left += veto3plane;
	titleVeto3left += ".b";
	titleVeto3left += veto3bar;
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
	Veto3right->Draw();
	veto2pad06->Update();

	veto2pad07->cd();
	TString titleVeto4left = "Left TDC for Veto 4 (NA.";
	titleVeto4left += veto4plane;
	titleVeto4left += ".b";
	titleVeto4left += veto4bar;
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
	Veto4right->Draw();
	veto2pad08->Update();

	veto2pad09->cd();
	TString titleVeto5left = "Left TDC for Veto 5 (NA.";
	titleVeto5left += veto5plane;
	titleVeto5left += ".b";
	titleVeto5left += veto5bar;
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

	veto2Canvas->Print(imageVetosWithVetosTitle);



	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
}
