#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <math.h>
#include <iomanip>


void n2_pressurve_curve()
{

	TCanvas *asymCanvas = new TCanvas("asymCanvas","Moller Measurements",540,360); //x,y
        asymCanvas->cd();
        asymCanvas->SetGrid();

/*	TH1F *pcurve = new TH1F("pcurve","pcurve",100000,0,40);
	pcurve->SetMaximum(80000000);
        pcurve->Fill(24.7,50067377.7269297);
        pcurve->Fill(34.703,68537588.0428094);
        pcurve->Fill(34.704,68530394.6571126);
        pcurve->Fill(16.7,37736303.5258363);
        pcurve->Fill(16.701,37947637.2503148);
        pcurve->Fill(34.7,69447455.7310244);
        pcurve->Fill(34.701,69876666.4362371);
        pcurve->Fill(34.702,70001057.5964673);
        pcurve->Fill(2.7,5951150.17387189);
        pcurve->Fill(5.7,12966557.3145014);
        pcurve->Fill(8.7,20030640.2437715);
        pcurve->Fill(11.7,25815542.0304336);
        pcurve->Fill(14.7,30637292.24376);
        pcurve->Fill(17.7,36231450.2466362);
        pcurve->Fill(20.7,42419795.7877001);
        pcurve->Fill(23.7,47316947.9018815);
        pcurve->Fill(26.7,53398337.2954786);
        pcurve->Fill(29.7,58383086.9043787);
        pcurve->Fill(32.7,63911734.4642579);
*/


	cout << "Am I here?" << endl;

	Double_t x[19];
	Double_t y[19];
	Double_t xErr[19];
	Double_t yErr[19];

	cout << "Am I here? 1" << endl;
	y[0] = 50067377.7269297; 
	y[1] = 68537588.0428094; 
	y[2] = 68530394.6571126; 
	y[3] = 37736303.5258363; 
	y[4] = 37947637.2503148; 
	y[5] = 69447455.7310244; 
	y[6] = 69876666.4362371; 
	y[7] = 70001057.5964673; 
	y[8] = 5951150.17387189; 
	y[9] = 12966557.3145014; 
	y[10] = 20030640.2437715; 
	y[11] = 25815542.0304336; 
	y[12] = 30637292.24376; 
	y[13] = 36231450.2466362; 
	y[14] = 42419795.7877001; 
	y[15] = 47316947.9018815; 
	y[16] = 53398337.2954786; 
	y[17] = 58383086.9043787; 
	y[18] = 63911734.4642579; 
	 


	cout << "Am I here? 3" << endl;
	x[0] = 24.7; 
	x[1] = 34.7;
	x[2] = 34.7; 
	x[3] = 16.7; 
	x[4] = 16.7; 
	x[5] = 34.7; 
	x[6] = 34.7; 
	x[7] = 34.7; 
	x[8] = 2.7; 
	x[9] = 5.7; 
	x[10] = 8.7; 
	x[11] = 11.7; 
	x[12] = 14.7; 
	x[13] = 17.7; 
	x[14] = 20.7; 
	x[15] = 23.7; 
	x[16] = 26.7; 
	x[17] = 29.7; 
	x[18] = 32.7; 



	cout << "Am I here? 4" << endl;
/*	yErr[0] = 0;
	yErr[1] = 0;
	yErr[2] = 0;
	yErr[3] = 0;
	yErr[4] = 0;
	yErr[5] = 0;
	yErr[6] = 0;
	yErr[7] = 0;
	yErr[8] = 0;
	yErr[9] = 0;
	yErr[10] = 0;
	yErr[11] = 0;
	yErr[12] = 0;
	yErr[13] = 0;
	yErr[14] = 0;
	yErr[15] = 0;
	yErr[16] = 0;
	yErr[17] = 0;
	yErr[18] = 0;
*/
	cout << "Am I here? 5" << endl;
	asymTestHist = new TH2F("asymTestHist","Moller Measurements",100,0,40,1000,0,80000000);
        asymTestHist->SetStats(kFALSE);
        asymTestHist->Draw();

	cout << "Am I here? 6" << endl;
	asymGraph = new TGraphErrors(18, x, y, xErr, yErr);
        asymGraph->SetMarkerStyle(21);
//      asymGraph->SetMarkerColor(4);
        asymGraph->SetMarkerColor(kBlue);
//      asymGraph->SetLineColor(4);
        asymGraph->SetLineColor(kBlue);

//	asymGraph->Draw();
	asymGraph->Draw("P");
	TF1 *fitAsymGraph = new TF1("fitAsymGraph", "[0]+[1]*x", 0, 40);
	asymGraph->Fit("fitAsymGraph");
	fitAsymGraph->Draw("same");

//	pcurve->Draw();

        asymCanvas->Update();
	cout << "All done!" << endl;
}
