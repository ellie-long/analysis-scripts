// ********************************************************
//
// This will serve as an example for when I need to fit a 
// Gaussian function on top of a constant background.
//
//
// Elena Long
// 2011-09-09
//
// ********************************************************

#include "TH1.h"
#include "TF1.h"
#include "TList.h"

Bool_t reject;
double sigMin;
double sigMax;
Double_t fline(Double_t *x, Double_t *par)
{
	if (reject && x[0] > sigMin && x[0] < sigMax) {
	TF1::RejectPoint();
	return 0;
}
//	return par[0] + par[1]*exp(par[2]*x[0]);
//	return exp(par[1]*x[0]+par[0])+par[2];
	return par[0] + par[1]*x[0];
//	return par[0];
}


void fitGausExample()
{
	int bins = 100;
	int min = 0;
	int max = 1600;
	sigMin = 500;
	sigMax = 800;
	double bgMin = 100;
	double bgMax = 1300;
	double xpos;
	
	TCanvas *testCanvas = new TCanvas("testCanvas","testCanvas",600,400); //x,y
	pad1  =  new  TPad("pad1","pad1",0.0000,0.0000,1.0000,1.0000,0,0,0);
	pad1->Draw();

	pad1->cd();
	TH1F *h1 = new TH1F("h1","Fitting Example",bins,min,max);	
	TH1F *h2 = new TH1F("h2","h2",bins,min,max);	
	TH1F *h3 = new TH1F("h3","Fitting Example",bins,min,max);	
	TH1F *bg = new TH1F("bg","bg",bins,min,max);	

	// The section below will fill h1 with a guassian
	// function with a mean of 670 and a sigma of 20
	// and fill h2 with a "uniform" random background
	// from bgMin<x<bgMax
	for (int i=0; i<10000000; i++)
	{
//		h1->Fill(gRandom->Uniform(10,1400));
		h1->Fill(gRandom->Uniform(0,1600));
		h1->Fill(gRandom->Exp(1400));
	}
	for (int i=0; i<100000; i++)
	{
//		h1->Fill(gRandom->Uniform(1400,1500));
	}
	for (int i=0; i<50000; i++)
	{
		h1->Fill(gRandom->Gaus(670,20));
	}
	for (int i=0; i<bins; i++)
	{
//		xpos = i*((max-min)/bins)+min;
//		cout << "xpos: " << xpos << endl;
//		h1->Fill(xpos,100*exp((-1)*xpos));
//		h2->Fill(i*((max-min)/bins)+min,i*500);
	}



//	h1->Add(h2,-1);
	h1->SetMinimum(0);
	h1->SetMaximum(300000);
	h1->Draw();

	TF1 *bgFit = new TF1("bgFit","[0]+[1]*x",bgMin,bgMax);
//	TF1 *bgFit = new TF1("bgFit","expo",bgMin,bgMax);
//	TF1 *bgFit = new TF1("bgFit","exp([1]*x+[0])+[2]",bgMin,bgMax);
	TF1 *bgFit = new TF1("bgFit",fline,bgMin,sigMin,3);
	bgFit->SetLineColor(kOrange);
	bgFit->SetParameter(0,1);
	bgFit->SetParameter(1,1/1600);
	bgFit->SetParameter(2,1);
	bgFit->SetParName(0,"Offset");
	bgFit->SetParName(1,"Tau");
	bgFit->SetParName(2,"Background");
	reject = kTRUE;
	h1->Fit(bgFit,"R");
	reject = kFALSE;
	TF1 *fleft = new TF1("fleft",fline,bgMin,sigMin,3);
	fleft->SetLineColor(kOrange);
	fleft->SetParameters(bgFit->GetParameters());
	h1->GetListOfFunctions()->Add(fleft);
	gROOT->GetListOfFunctions()->Remove(fleft);
	TF1 *fright = new TF1("fright",fline,sigMax,bgMax,3);
	fright->SetLineColor(kOrange);
	fright->SetParameters(bgFit->GetParameters());
	h1->GetListOfFunctions()->Add(fright);
	gROOT->GetListOfFunctions()->Remove(fright);
//	h1->SetMaximum(300000);
	h1->Draw();

	double fitOffset = bgFit->GetParameter(0);
	double fitTau = bgFit->GetParameter(1);
//	double fitBackground = bgFit->GetParameter(2);
	double fitOffsetErr = bgFit->GetParError(0);
	double fitTauErr = bgFit->GetParError(1);
//	double fitBackgroundErr = bgFit->GetParError(2);

	cout << "Number of Bins: " << h1->GetSize()-2 << endl;;
	cout << "fitOffset: " << fitOffset << endl;;
	cout << "fitTau: " << fitTau << endl;;
	for (int i=0; i<(h1->GetSize()-2); i++)
	{
		xpos = i*((max-min)/bins)+min;
//		h2->Fill(xpos,i*500);
		bg->Fill(xpos,(fitOffset + fitTau*xpos));
//		bg->Fill(xpos,(exp(fitTau*xpos + fitOffset) + fitBackground));
	}
	bg->SetLineColor(kBlue);
	bg->Draw("same");

	h3->Add(h1);
	h3->Add(bg,-1);
	h3->SetLineColor(kRed);
	h3->SetMinimum(0);
	h3->Draw("same");


	cout << "sigMin: " << sigMin << ", sigMax: " << sigMax << endl;
	TF1 *sigFit = new TF1("sigFit","gaus",sigMin,sigMax);
	sigFit->SetLineColor(kBlue);
	sigFit->SetParameter(0,1000);
	sigFit->SetParameter(1,690);
	sigFit->SetParameter(2,20);
	sigFit->SetParameter(3,1);
	sigFit->SetParName(0,"Weight");
	sigFit->SetParName(1,"Mean");
	sigFit->SetParName(2,"Sigma");
//	sigFit->SetParName(3,"Background");
	h3->SetMaximum(300000);
	h3->Fit(sigFit,"R");
	sigFit->Draw("same");	
	

	double fitWeight = sigFit->GetParameter(0);
	double fitMean = sigFit->GetParameter(1);
	double fitSigma = sigFit->GetParameter(2);
	double fitWeightErr = sigFit->GetParError(0);
	double fitMeanErr = sigFit->GetParError(1);
	double fitSigmaErr = sigFit->GetParError(2);
	fitResults = new TPaveText(0.11,0.70,0.4,0.89,"NDC");
	TString WeightStr = "Weight = ";
	WeightStr += fitWeight;
	WeightStr += " ± ";
	WeightStr += fitWeightErr;
	TString MeanStr = "Mean = ";
	MeanStr += fitMean;
	MeanStr += " ± ";
	MeanStr += fitMeanErr;  
	TString SigmaStr = "Sigma = ";
	SigmaStr += sqrt(fitSigma*fitSigma);
	SigmaStr += " ± ";
	SigmaStr += fitSigmaErr; 
	TString OffsetStr = "Offset = ";
	OffsetStr += fitOffset;
	OffsetStr += " ± ";
	OffsetStr += fitOffsetErr; 
	TString TauStr = "Tau = ";
	TauStr += fitTau;
	TauStr += " ± ";
	TauStr += fitTauErr; 
	TString BackgroundStr = "BackgroundConst = ";
	BackgroundStr += fitBackground;
	BackgroundStr += " ± ";
	BackgroundStr += fitBackgroundErr; 
	TText *t1 = fitResults->AddText(WeightStr);
	TText *t2 = fitResults->AddText(MeanStr);
	TText *t3 = fitResults->AddText(SigmaStr);
	TText *t4 = fitResults->AddText(BackgroundStr);
	TText *t5 = fitResults->AddText(TauStr);
	TText *t6 = fitResults->AddText(OffsetStr);

	h1->Draw("same");
	TString theFitStr = "(";
	theFitStr += fitWeight;
	theFitStr += "*exp(-0.5*((x-";
	theFitStr += fitMean;
	theFitStr += ")/";
	theFitStr += fitSigma;
	theFitStr += ")^2))+";
	theFitStr += fitBackground;
	theFitStr += "+exp(";
	theFitStr += fitTau;
	theFitStr += "*x+";
	theFitStr += fitOffset;
	theFitStr += ")";
	TF1 *theFit = new TF1("theFit",theFitStr,bgMin,bgMax);
	theFit->SetLineColor(kMagenta);
	theFit->Draw("same");

        double integralOfPeak;
        integralOfPeak = sigFit->Integral((fitMean - 3*sqrt(fitSigma*fitSigma)),(fitMean + 3*sqrt(fitSigma*fitSigma)));
        TString peakInt = "Integral of Peak: ";
        peakInt +=  integralOfPeak;
        cout << peakInt << endl;
        TText *t7 = fitResults->AddText(peakInt);

	pad1->Update();

	TString outputPlotsHere = "/home/ellie/physics/e05-102/analysis-scripts/devel/test_stuff/";
        TString testOutTitle = outputPlotsHere;
        testOutTitle += "test_out_step_1";
	testOutTitle += ".svg";


	fitResults->Draw("same");

}











