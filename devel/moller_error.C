#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <math.h>
#include <iomanip>


void moller_error()
{

	TCanvas *asymCanvas = new TCanvas("asymCanvas","Moller Measurements",1400,730); //x,y
        asymCanvas->cd();
        asymCanvas->SetGrid();

	cout << "Am I here?" << endl;

	Double_t x[5];
	Double_t y[5];
	Double_t xErr[5];
	Double_t yErr[5];

	cout << "Am I here? 1" << endl;
	y[0] = 88.3;
	y[1] = 84.1;
	y[2] = 83.38;
	y[3] = 78.68;
	y[4] = 87.815;

	cout << "Am I here? 3" << endl;
	x[0] = 1;
	x[1] = 2;
	x[2] = 3;
	x[3] = 4;
	x[4] = 5;
//	x[5] = 6;

	cout << "Am I here? 4" << endl;
	yErr[0] = 2.00997512422;
	yErr[1] = 2.00997512422;
	yErr[2] = 2.00997512422;
	yErr[3] = 2.00997512422;
	yErr[4] = 2.00997512422;
//	yErr[5] = 2.00997512422;

	cout << "Am I here? 5" << endl;
	asymTestHist = new TH2F("asymTestHist","Moller Measurements",7,0,6,100,70,100);
        asymTestHist->SetStats(kFALSE);
        asymTestHist->Draw();

	cout << "Am I here? 6" << endl;
	asymGraph = new TGraphErrors(5, x, y, xErr, yErr);
        asymGraph->SetMarkerStyle(21);
//      asymGraph->SetMarkerColor(4);
        asymGraph->SetMarkerColor(kBlue);
//      asymGraph->SetLineColor(4);
        asymGraph->SetLineColor(kBlue);

	asymGraph->Draw("P");
	TF1 *fitAsymGraph = new TF1("fitAsymGraph", "[0]", 1, 5);
//	asymGraph->Fit("fitAsymGraph");
        asymCanvas->Update();
	cout << "All done!" << endl;
}
