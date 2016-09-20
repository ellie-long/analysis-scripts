// **********************************************************
// This will draw the "antiveto" bars (the bars immediately
// behind the good bar). It will also show tracking information
// if desired.
//
// To run, be sure to include the header file:
/* 
	#include "hand_draw_antivetos.h"
*/
// Be sure to run hand_basic_cuts.h and hand_define_vetos.h
// before running this script
// Make sure to include a goodTDCcut (or leave blank) and
// define a place to put the output plots. For example,
/*
                        TString imageAntivetosTitle = "/home/ellie/physics/e05-102/images/plots_for_hand/left_right_position_test/antivetos_for_Run_Num_";
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
*/
// Then run this line:
/*
	hand_draw_antivetos(antiveto1plane, antiveto1bar, antiveto2plane, antiveto2bar, antiveto3plane, antiveto3bar, HeRunNumber, endHeRunNumber, chainHe, TDCbins, TDCmin, TDCmax, cuts, goodTDCcut, vetoTDCs, imageAntivetosTitle, nplane, thisbar, includeVetos, includeAntivetos, antivetosAsVetos, veto1plane, veto1bar, veto2plane, veto2bar, veto3plane, veto3bar, veto4plane, veto4bar, veto5plane, veto5bar, veto6plane, veto6bar, allVetos, allAntivetos);
*/
//
// Elena Long
// 2010-12-09
// **********************************************************

#include "hand_draw.h"

void hand_draw_antivetos(TString antiveto1plane, TString antiveto1bar, TString antiveto2plane, TString antiveto2bar, TString antiveto3plane, TString antiveto3bar, int HeRunNumber, int endHeRunNumber, TChain* chainHe, int TDCbins, double TDCmin, double TDCmax, TCut cuts, TCut goodTDCcut, TCut vetoTDCs, TString imageAntivetosTitle, int nplane, int thisbar, bool includeVetos, bool includeAntivetos, bool antivetosAsVetos, TString veto1plane, TString veto1bar, TString veto2plane, TString veto2bar, TString veto3plane, TString veto3bar, TString veto4plane, TString veto4bar, TString veto5plane, TString veto5bar, TString veto6plane, TString veto6bar, TString allVetos, TString allAntivetos){

	cout << "vvvvvvvvvvvvvvvvvvvvvvvvv hand_draw_antivetos.h vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;



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
	antivetopad01 =  new TPad("antivetopad01","antivetopad01",0.1000,0.5000,0.4000,1.0000,0,0,0);
	antivetopad02 =  new TPad("antivetopad02","antivetopad02",0.1000,0.0000,0.4000,0.5000,0,0,0);
	antivetopad03 =  new TPad("antivetopad03","antivetopad03",0.4000,0.5000,0.7000,1.0000,0,0,0);
	antivetopad04 =  new TPad("antivetopad04","antivetopad04",0.4000,0.0000,0.7000,0.5000,0,0,0);
	antivetopad05 =  new TPad("antivetopad05","antivetopad05",0.7000,0.5000,1.0000,1.0000,0,0,0);
	antivetopad06 =  new TPad("antivetopad06","antivetopad06",0.7000,0.0000,1.0000,0.5000,0,0,0);
	antivetopad07 =  new TPad("antivetopad07","antivetopad07",0.0000,0.0000,0.1000,1.0000,0,0,0);
	antivetopad01->Draw(); antivetopad02->Draw(); antivetopad03->Draw();
	antivetopad04->Draw(); antivetopad05->Draw(); antivetopad06->Draw();
	antivetopad07->Draw();

	antivetopad07->cd();
	TString goodBar = "nd.p";
	goodBar += nplane;
	goodBar += ".";
	goodBar += thisbar;
	goodBar += " ";
	hand_draw(HeRunNumber, endHeRunNumber, antivetosAsVetos, allVetos, goodBar, allAntivetos);
	antivetopad07->Update();

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
										
	antivetoCanvas->Print(imageAntivetosTitle);



	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
} 
