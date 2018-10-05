



Bool_t reject;
double sigMin;
double sigMax;
TString fitType;

Double_t fline(Double_t *x, Double_t *par)
{
	if (reject && x[0] > sigMin && x[0] < sigMax)
	{
		TF1::RejectPoint();
		return 0;
	}
	if (fitType=="quad"){return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];}
	if (fitType=="lin"){return par[0] + par[1]*x[0];}
	if (fitType=="const"){return par[0];}
	if (fitType=="exp"){return exp(par[1]*x[0]+par[0])+par[2];}
}



void hand_class_draw_tof_nu(int HeRunNumber, int endHeRunNumber, TString filenameHe, TString kine, TString targ, TString asymOutFileName, bool includeVetos, const int nuBins, double nuMin, double nuMax, double HeChargeScaleUp, double HeChargeScaleDown, double HelivetimeUp, double HelivetimeDown, TString outputPlotsHere)
{

	cout << "vvvvvvvvvvvvvvvvvvvvvvv hand_class_draw_tof_nu.h vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;

	TString fitTypeHolder;

//	bool forceBG = true;
	bool forceBG = false;

	bool twoSig = true;
	bool fiveSig = false;

//	bool twoSig = false;
//	bool fiveSig = true;



	TString asymOut2FileName = outputPlotsHere;
	asymOut2FileName += "ssa_target_asymmetry_for_runs_";
	asymOut2FileName += HeRunNumber;
	asymOut2FileName += "-";
	asymOut2FileName += endHeRunNumber;
	if (includeVetos) {asymOut2FileName += "_with_vetos";}
	asymOut2FileName += ".txt";

	ofstream asymOutFile;
	ofstream asymOut2File;
	asymOutFile.open(asymOutFileName);
	asymOut2File.open(asymOut2FileName);

	bool check = false;
	bool includeTgtPol = true;
	bool includeBeamPol = false;
	double tgtPolDil = 1;
	double beamPolDil = 1;


	TH1F *nuQEcuts = new TH1F("nuQEcuts","nuQEcuts",nuBins,nuMin,nuMax);
	TH1F *tofWithNuQEBinsUp = new TH1F("tofWithNuQEBinsUp","tofWithNuQEBinsUp",100,200,1300);
	TH1F *tofWithNuQEBinsDown = new TH1F("tofWithNuQEBinsDown","tofWithNuQEBinsDown",100,200,1300);


	TString target;
	if ((targ == "v") || (targ == "l") || (targ == "t") || (targ == "c") || (targ == "h") || (targ == "vh") || (targ == "lth")) { check = true;}
	if (targ == "v") 
	{
		target="Vertical 3He";
		if (kine=="0.1")
		{
			tgtPolDil = 1/(0.58508 * 0.9);
			beamPolDil = 1/(0.8620);
		}
		if (kine=="0.5")
		{
			tgtPolDil = 1/(0.60676 * 0.9);
			beamPolDil = 1/(0.8620);
		}
		if (kine=="1.0")
		{
			tgtPolDil = 1/(0.60756 * 0.9);
			beamPolDil = 1/(0.8620);
		}

	}
	if (targ == "l") 
	{
		target="Longitudinal 3He";
		if (kine=="1.0")
		{
			tgtPolDil = 1/(0.61367 * 0.9);
			beamPolDil = 1/(0.8282);
		}

	}
	if (targ == "t") 
	{
		target="Transverse 3He";
		if (kine=="1.0")
		{
			tgtPolDil = 1/(0.52307 * 0.9);
			beamPolDil = 1/(0.8282);
		}

	}
	if (targ == "c") {target="Carbon";}
	if (targ == "h") {target="Hydrogen";}
	if (targ == "vh") {target="Hydrogen";}
	if (targ == "lth") {target="Hydrogen";}

	int tofBins = 100;
	int tofMin = 200;
	int tofMax = 1300;
	double sigUpMin;
	double sigUpMax;
	double sigDownMin;
	double sigDownMax;
	double bgUpMin;
	double bgUpMax;
	double bgDownMin;
	double bgDownMax;
	int upMinimum;
	int upMaximum;
	int downMinimum;
	int downMaximum;
	double xpos;
	double binSize = (tofMax - tofMin)/tofBins;
	int sigMinBin;
	int sigMaxBin;
	if (kine=="1.0")
	{
		if (targ=="v")
		{
			cout << "Q2=1.0, Vertical 3He" << endl;
			sigUpMin = 600;
			sigUpMax = 750;
			if (includeVetos)
			{
				sigUpMin = 600;
				sigUpMax = 750;
			}
			bgUpMin = 200;
			bgUpMax = 1300;
			sigDownMin = 550;
			sigDownMax = 740;
			bgDownMin = 200;
			bgDownMax = 1300;
//			upMinimum = 80000;
			upMinimum = 0;
			upMaximum = 188000;
//                      downMinimum = 0;
			downMinimum = 90000;
			downMaximum = 110000;
//                      downMaximum = 10000;
//			fitType = "exp";
			fitType = "lin";
//                      fitType = "quad";
//			if (includeVetos) {fitType = "lin";}
//                      fitType = "const";
		}
		if (targ=="h" || targ=="vh" || targ=="lth")
		{
			cout << "Q2=1.0, Hydrogen" << endl;
			sigUpMin = 650;
			sigUpMax = 700;
			if (includeVetos)
			{
				sigUpMin = 650;
				sigUpMax = 700;
			}
			bgUpMin = 200;
			bgUpMax = 1300;
			sigDownMin = 650;
			sigDownMax = 700;
			bgDownMin = 200;
			bgDownMax = 1300;
//			upMinimum = 80000;
			upMinimum = 0;
			upMaximum = 188000;
//                      downMinimum = 0;
			downMinimum = 90000;
			downMaximum = 110000;
//                      downMaximum = 10000;
//			fitType = "exp";
//			fitType = "lin";
//                      fitType = "quad";
//			if (includeVetos) {fitType = "lin";}
			fitType = "const";
		}

	}
	if (kine=="0.5")
	{
		if (targ=="v")
		{
			cout << "Q2=0.5, Vertical 3He" << endl;
			sigUpMin = 600;
			sigUpMax = 750;
			if (includeVetos)
			{
				sigUpMin = 600;
				sigUpMax = 750;
			}
			bgUpMin = 200;
//			bgUpMin = 700;
			bgUpMax = 1300;
//			bgUpMax = 1000;
			sigDownMin = 550;
			sigDownMax = 740;
			bgDownMin = 200;
			bgDownMax = 1300;
//			upMinimum = 80000;
			upMinimum = 0;
			upMaximum = 188000;
//                      downMinimum = 0;
			downMinimum = 90000;
			downMaximum = 110000;
//                      downMaximum = 10000;
//			fitType = "exp";
//			fitType = "lin";
//                      fitType = "quad";
//			if (includeVetos) {fitType = "lin";}
			fitType = "const";
		}
		if (targ=="h")
		{
			cout << "Q2=0.5, Hydrogen" << endl;
			sigUpMin = 300;
			sigUpMax = 400;
			if (includeVetos)
			{
				sigUpMin = 300;
				sigUpMax = 400;
			}
			bgUpMin = 200;
			bgUpMax = 690;
			sigDownMin = 300;
			sigDownMax = 400;
			bgDownMin = 200;
			bgDownMax = 690;
//			upMinimum = 80000;
			upMinimum = 0;
			upMaximum = 188000;
//                      downMinimum = 0;
			downMinimum = 90000;
			downMaximum = 110000;
//                      downMaximum = 10000;
//			fitType = "exp";
//			fitType = "lin";
//                      fitType = "quad";
//			if (includeVetos) {fitType = "lin";}
			fitType = "const";
		}
	}
	if (kine=="0.1")
	{
		if (targ=="v")
		{
			cout << "Q2=0.1, Vertical 3He" << endl;
			sigUpMin = 600;
			sigUpMax = 740;
//			if (includeVetos)
//			{
//				sigUpMin = 625;
/c				sigUpMax = 704;
//			}
			bgUpMin = 200;
//			bgUpMin = 400;
			bgUpMax = 1300;
			sigDownMin = 600;
			sigDownMax = 740;
//			bgDownMin = 200;
			bgDownMin = 400;
			bgDownMax = 1300;
//			upMinimum = 80000;
			upMinimum = 0;
//			upMaximum = 188000;
//                      downMinimum = 0;
			downMinimum = 90000;
//			downMaximum = 110000;
//                      downMaximum = 10000;
			fitType = "exp";
//			fitType = "lin";
//                      fitType = "quad";
//			if (includeVetos) {fitType = "lin";}
//			if (includeVetos) {fitType = "exp";}
//                      fitType = "const";
		}
		if (targ=="h")
		{
			cout << "Q2=0.1, Hydrogen" << endl;
			sigUpMin = 600;
//                      sigUpMax = 675;
			sigUpMax = 678;
//                      sigUpMax = 700;
			bgUpMin = 0;
			bgUpMax = 1300;
//                      sigDownMin = 600;
			sigDownMin = 630;
//                      sigDownMax = 700;
			sigDownMax = 680;
			bgDownMin = 0;
			bgDownMax = 1300;
			upMinimum = 1500;
			upMaximum = 3000;
			downMinimum = 1500;
			downMaximum = 3000;
//                      fitType = "const";
			fitType = "lin";
		}

	}

	TString fitTypeStr = "Background Fit Type: ";
	fitTypeStr += fitType;

	TFile fileHe(filenameHe);
	TString Q2=kine;
	double xmin=0;
	double xmax=3;

	gStyle->SetPalette(1);

	TString ToFCanvasName;
	TString plotToFgoodEventTotal; TString plotToFupTotal; TString plotToFdownTotal; TString plotnuAllCutsTotal;
	TString plotToFgoodEvent; TString plotToFup; TString plotToFdown;
	TString plotnuAllCuts; TString titlenuAllCuts; TString ToFnuOutTitle; TString titleToFup; TString titleToFdown;
	plotToFgoodEventTotal = "ToFgoodEvent_Total"; plotToFupTotal = "ToFup_Total"; plotToFdownTotal = "ToFdown_Total"; plotnuAllCutsTotal = "nuAllCuts_Total";
	titlenuAllCuts = "Target Spin vs. nu for Runs "; titlenuAllCuts += HeRunNumber; titlenuAllCuts += "-"; titlenuAllCuts += endHeRunNumber;
	if (includeVetos) {titlenuAllCuts += " with vetos";}
	else {titlenuAllCuts += " without vetos";}
	TString h3Uptitle; TString bgUpTitle;
        TH1F *ToFgoodEventTotal = (TH1F*)fileHe.Get(plotToFgoodEventTotal);
        TH1F *ToFupTotal = (TH1F*)fileHe.Get(plotToFupTotal);
        TH1F *ToFdownTotal = (TH1F*)fileHe.Get(plotToFdownTotal);
        TH1F *nuAllCutsTotal = (TH1F*)fileHe.Get(plotnuAllCutsTotal);
	TH1F *bgUp; TH1F *h3Up; TH1F *ToFgoodEvent; TH1F *ToFup; TH1F *ToFdown; TH1F *nuAllCuts;
	TF1 *bgFitUp; TF1 *fleftUp; TF1 *frightUp; TF1 *sigFitUp; TF1 *theFitUp;
	TString sigFitUpTitle; TString theFitUpTitle;
	double integralOfPeakUp;
	double fitOffsetUp; double fitTauUp; double fitBackgroundUp;
	double fitOffsetUpErr; double fitTauUpErr; double fitBackgroundUpErr;
	double fitBackgroundUp; double fitLinearUp; double fitQuadraticUp;
	double fitBackgroundUpErr; double fitLinearUpErr; double fitQuadraticUpErr;
	double fitWeightUp; double fitMeanUp; double fitSigmaUp; double fitWeightUpErr; double fitMeanUpErr; double fitSigmaUpErr;
	TString WeightStrUp; TString MeanStrUp; TString SigmaStrUp; TString OffsetStrUp; TString TauStrUp;
	TString BackgroundStrUp; TString LinearStrUp;TString QuadraticStrUp; TString theFitUpStr; TString peakIntUp;
	TText *Up1; TText *Up2; TText *Up3; TText *Up4; TText *Up5; TText *Up6; TText *Up7;
	TText *goodUp;
	TF1 *bgFitDown; TF1 *fleftDown; TF1 *frightDown; TF1 *sigFitDown; TF1 *theFitDown;
	TString sigFitDownTitle; TString theFitDownTitle;
	double integralOfPeakDown;
	double fitOffsetDown; double fitTauDown; double fitBackgroundDown;
	double fitOffsetDownErr; double fitTauDownErr; double fitBackgroundDownErr;
	double fitBackgroundDown; double fitLinearDown; double fitQuadraticDown;
	double fitBackgroundDownErr; double fitLinearDownErr; double fitQuadraticDownErr;
	double fitWeightDown; double fitMeanDown; double fitSigmaDown; double fitWeightDownErr; double fitMeanDownErr; double fitSigmaDownErr;
	TString WeightStrDown; TString MeanStrDown; TString SigmaStrDown; TString OffsetStrDown; TString TauStrDown;
	TString BackgroundStrDown; TString LinearStrDown;TString QuadraticStrDown; TString theFitDownStr; TString peakIntDown;
	TText *Down1; TText *Down2; TText *Down3; TText *Down4; TText *Down5; TText *Down6; TText *Down7;
	TText *goodDown;
	int thisBinContent; int totalGoodEventsUp; int totalGoodEventsDown; int theBiggestBin; int theSmallestBin;
	TH1F *goodEventsUp; TH1F *goodEventsDown;
	TString goodEventsUpTitle; TString goodEventsUpPlot; TString goodEventStr;
	TString goodEventsDownTitle; TString goodEventsDownPlot;
	nuAllCutsTotal->SetTitle(titlenuAllCuts);
	int goodUpEvents[11]; int goodDownEvents[11];
	double bgUpErr[11]; double bgDownErr[11];

	double allBgMin = bgUpMin;
//	double allBgMin = sigUpMax;
	double allBgMax = bgUpMax;
//	double allBgMax = sigUpMin;

	for (int i=0; i<11; i++)
	{
		ToFCanvasName = "ToFCanvas_bin_";
		ToFCanvasName += i;
		titleToFup = "ToFup_bin_";
		titleToFup = i;
		titleToFdown = "ToFdown_bin_";
		titleToFdown = i;
		if (i==0) 
		{
			ToFCanvasName = "ToFCanvas_Total";
			titleToFup = "ToFup_Total";
			titleToFdown = "ToFdown_Total";
		}
		cout << "Making " << ToFCanvasName << endl;
		TCanvas *ToFCanvas = new TCanvas(ToFCanvasName,ToFCanvasName,1360,768); //x,y
/*		tofpad1  =  new  TPad("tofpad1","tofpad1",0.0000,0.6666,0.5000,1.0000,0,0,0);
		tofpad2  =  new  TPad("tofpad2","tofpad2",0.5000,0.6666,1.0000,1.0000,0,0,0);
		tofpad3  =  new  TPad("tofpad3","tofpad3",0.0000,0.3333,0.5000,0.6666,0,0,0);
		tofpad4  =  new  TPad("tofpad4","tofpad4",0.5000,0.3333,1.0000,0.6666,0,0,0);
		tofpad5  =  new  TPad("tofpad5","tofpad5",0.0000,0.0000,0.5000,0.3333,0,0,0);
		tofpad6  =  new  TPad("tofpad6","tofpad6",0.5000,0.0000,1.0000,0.3333,0,0,0);
*/
		tofpad1  =  new  TPad("tofpad1","tofpad1",0.0000,0.7500,0.5000,1.0000,0,0,0);
		tofpad2  =  new  TPad("tofpad2","tofpad2",0.5000,0.7500,1.0000,1.0000,0,0,0);
		tofpad3  =  new  TPad("tofpad3","tofpad3",0.0000,0.5000,0.5000,0.7500,0,0,0);
		tofpad4  =  new  TPad("tofpad4","tofpad4",0.5000,0.5000,1.0000,0.7500,0,0,0);
		tofpad5  =  new  TPad("tofpad5","tofpad5",0.0000,0.2500,0.5000,0.5000,0,0,0);
		tofpad6  =  new  TPad("tofpad6","tofpad6",0.5000,0.2500,1.0000,0.5000,0,0,0);
		tofpad7  =  new  TPad("tofpad7","tofpad7",0.0000,0.0000,0.5000,0.2500,0,0,0);
		tofpad8  =  new  TPad("tofpad8","tofpad8",0.5000,0.0000,1.0000,0.2500,0,0,0);
		tofpad1->Draw(); tofpad2->Draw(); tofpad3->Draw(); tofpad4->Draw(); tofpad5->Draw(); tofpad6->Draw();
		tofpad7->Draw(); tofpad8->Draw();

		plotToFgoodEvent = "ToFgoodEvent_bin_";
		plotToFgoodEvent += i;
		plotToFup = "ToFup_bin_";
		plotToFup += i;
		plotToFdown = "ToFdown_bin_";
		plotToFdown += i;
		plotnuAllCuts = "nuAllCuts_bin_";
		plotnuAllCuts += i;
		if (i==0)
		{
			plotToFgoodEvent = "ToFgoodEvent_Total";
			plotToFup = "ToFup_Total";
			plotToFdown = "ToFdown_Total";
			plotnuAllCuts = "nuAllCuts_Total";
		}
//		TH1F *ToFgoodEvent = (TH1F*)fileHe.Get(plotToFgoodEvent);
//		TH1F *ToFup = (TH1F*)fileHe.Get(plotToFup);
//		TH1F *ToFdown = (TH1F*)fileHe.Get(plotToFdown);
//		TH1F *nuAllCuts = (TH1F*)fileHe.Get(plotnuAllCuts);
	
		ToFgoodEvent = (TH1F*)fileHe.Get(plotToFgoodEvent);
		ToFup = (TH1F*)fileHe.Get(plotToFup);
		ToFdown = (TH1F*)fileHe.Get(plotToFdown);
		nuAllCuts = (TH1F*)fileHe.Get(plotnuAllCuts);
	     
		nuAllCuts->SetTitle(titlenuAllCuts);

		// Everything below here makes graphs for each section of the canvas
		tofpad1->cd();
		nuAllCutsTotal->SetFillColor(kWhite);
		nuAllCutsTotal->SetMinimum(0);
		nuAllCutsTotal->Draw();
		nuAllCuts->SetFillColor(kViolet);
		nuAllCuts->SetMinimum(0);
		nuAllCuts->Draw("same");
		tofpad1->Update();

		tofpad2->cd();
//		tofpad2->SetLogy();
/*		ToFgoodEventTotal->SetFillColor(kWhite);
		ToFgoodEventTotal->SetMinimum(0);
		ToFgoodEventTotal->Draw();
		ToFgoodEvent->SetFillColor(kViolet);
		ToFgoodEvent->SetMinimum(0);
		ToFgoodEvent->Draw("same");
*/		ToFgoodEvent->SetFillColor(kWhite);
		ToFgoodEvent->Draw();
		if (i==0)
		{
//			sigMin = sigUpMin;
//			sigMax = sigUpMax;
			TH1F *h3Total = new TH1F("h3Total","h3Total",tofBins,tofMin,tofMax);
			if (fitType=="const"){TF1 *bgFitTotal = new TF1("bgFitTotal","[0]",bgUpMin,bgUpMax);}
			if (fitType=="lin"){TF1 *bgFitTotal = new TF1("bgFitTotal","[0]+[1]*x",bgUpMin,bgUpMax);}
			if (fitType=="quad"){TF1 *bgFitTotal = new TF1("bgFitTotal","[0]+[1]*x+[2]*x*x",bgUpMin,bgUpMax);}
			if (fitType=="exp"){TF1 *bgFitTotal = new TF1("bgFitTotal","exp([1]*x+[0])+[2]",bgUpMin,bgUpMax);}
//			TF1 *bgFitTotal = new TF1("bgFitTotal",fline,bgUpMin,sigUpMin,3);
// !!!!!!!!!!!!!!!!!!!!!!! TO CHANGE WHAT THE BACKGROUND FITS, CHANGE THE MIN/MAX BELOW !!!!!!!!!!!!!!!!!! bgfit !!!!!!!!!!!!!!!!!!
//			TF1 *bgFitTotal = new TF1("bgFitTotal",fline,bgUpMin,bgUpMax,3);
			TF1 *bgFitTotal = new TF1("bgFitTotal",fline,allBgMin,allBgMax,3);
			bgFitTotal->SetLineColor(kOrange);
			if (fitType=="exp")
			{
				bgFitTotal->SetParameter(0,1);
				bgFitTotal->SetParameter(1,1/1600);
				bgFitTotal->SetParameter(2,85000);
				bgFitTotal->SetParName(0,"Offset");
				bgFitTotal->SetParName(1,"Tau");
				bgFitTotal->SetParName(2,"Background");
			}
			if (fitType!="exp")
			{
				bgFitTotal->SetParameter(0,1);
				bgFitTotal->SetParameter(1,1);
				bgFitTotal->SetParameter(2,1);
				bgFitTotal->SetParName(0,"Background");
				bgFitTotal->SetParName(1,"Linear");
				bgFitTotal->SetParName(2,"Quadratic");
			}
			reject = kTRUE;
			ToFgoodEvent->Fit(bgFitTotal,"R");
			reject = kFALSE;
			TF1 *fleftTotal = new TF1("fleftTotal",fline,bgUpMin,sigUpMin,3);
			fleftTotal->SetLineColor(kOrange);
			fleftTotal->SetParameters(bgFitTotal->GetParameters());
			ToFgoodEvent->GetListOfFunctions()->Add(fleftTotal);
			gROOT->GetListOfFunctions()->Remove(fleftTotal);
			TF1 *frightTotal = new TF1("frightTotal",fline,sigUpMax,bgUpMax,3);
			frightTotal->SetLineColor(kOrange);
			frightTotal->SetParameters(bgFitTotal->GetParameters());
			ToFgoodEvent->GetListOfFunctions()->Add(frightTotal);
			gROOT->GetListOfFunctions()->Remove(frightTotal);
			ToFgoodEvent->Draw();
			if (fitType=="exp")
			{
				double fitOffsetTotal = bgFitTotal->GetParameter(0);
				double fitTauTotal = bgFitTotal->GetParameter(1);
				double fitBackgroundTotal = bgFitTotal->GetParameter(2);
				double fitOffsetTotalErr = bgFitTotal->GetParError(0);
				double fitTauTotalErr = bgFitTotal->GetParError(1);
				double fitBackgroundTotalErr = bgFitTotal->GetParError(2);
			}
			if (fitType!="exp")
			{
				double fitBackgroundTotal = bgFitTotal->GetParameter(0);
				double fitLinearTotal = bgFitTotal->GetParameter(1);
				double fitQuadraticTotal = bgFitTotal->GetParameter(2);
				double fitBackgroundTotalErr = bgFitTotal->GetParError(0);
				double fitLinearTotalErr = bgFitTotal->GetParError(1);
				double fitQuadraticTotalErr = bgFitTotal->GetParError(2);
			}

			TH1F *bgTotal = new TH1F("bgTotal","bgTotal",tofBins,tofMin,tofMax);
			cout << "Number of Bins: " << ToFgoodEvent->GetSize()-2 << endl;
			for (int k=0; k<(ToFgoodEvent->GetSize()-2); k++)
			{
				xpos = k*((tofMax-tofMin)/tofBins)+tofMin;
				if (fitType=="const") {bgTotal->Fill(xpos,fitBackgroundTotal);}
				if (fitType=="lin")   {bgTotal->Fill(xpos,(fitBackgroundTotal + fitLinearTotal*xpos));}
				if (fitType=="quad")  {bgTotal->Fill(xpos,(fitBackgroundTotal + fitLinearTotal*xpos + fitQuadraticTotal*xpos*xpos));}
				if (fitType=="exp")   {bgTotal->Fill(xpos,(exp(fitTauTotal*xpos + fitOffsetTotal) + fitBackgroundTotal));}
			}
			bgTotal->SetLineColor(kBlue);
			bgTotal->Draw("same");
			h3Total->Add(ToFgoodEvent);
			h3Total->Add(bgTotal,-1);
			h3Total->SetLineColor(kRed);
//			h3Total->SetMinimum(upMinimum);
//			h3Total->Draw("same");
			cout << "sigUpMin: " << sigUpMin << ", sigUpMax: " << sigUpMax << endl;
			TF1 *sigFitTotal = new TF1("sigFitTotal","gaus",sigUpMin,sigUpMax);
			sigFitTotal->SetLineColor(kBlue);
			sigFitTotal->SetParameter(0,1000);
			sigFitTotal->SetParameter(1,690);
			sigFitTotal->SetParameter(2,20);
			sigFitTotal->SetParameter(3,1);
			sigFitTotal->SetParName(0,"Weight");
			sigFitTotal->SetParName(1,"Mean");
			sigFitTotal->SetParName(2,"Sigma");
//			h3Total->SetMaximum(upMaximum);
			h3Total->Fit(sigFitTotal,"R");
//			sigFitTotal->Draw("same");
			double fitWeightTotal = sigFitTotal->GetParameter(0);
			double fitMeanTotal = sigFitTotal->GetParameter(1);
			double fitSigmaTotal = sigFitTotal->GetParameter(2);
			double fitWeightTotalErr = sigFitTotal->GetParError(0);
			double fitMeanTotalErr = sigFitTotal->GetParError(1);
			double fitSigmaTotalErr = sigFitTotal->GetParError(2);
			fitResultsTotal = new TPaveText(0.11,0.11,0.35,0.43,"NDC");
			TString WeightStrTotal = "Weight = ";
			WeightStrTotal += fitWeightTotal;
			WeightStrTotal += " ± ";
			WeightStrTotal += fitWeightTotalErr;
			TString MeanStrTotal = "Mean = ";
			MeanStrTotal += fitMeanTotal;
			MeanStrTotal += " ± ";
			MeanStrTotal += fitMeanTotalErr;
			TString SigmaStrTotal = "Sigma = ";
			SigmaStrTotal += sqrt(fitSigmaTotal*fitSigmaTotal);
			SigmaStrTotal += " ± ";
			SigmaStrTotal += fitSigmaTotalErr;
			if (fitType=="exp")
			{
				TString OffsetStrTotal = "Offset = ";
				OffsetStrTotal += fitOffsetTotal;
				OffsetStrTotal += " ± ";
				OffsetStrTotal += fitOffsetTotalErr;
				TString TauStrTotal = "Tau = ";
				TauStrTotal += fitTauTotal;
				TauStrTotal += " ± ";
				TauStrTotal += fitTauTotalErr;
			}
			TString BackgroundStrTotal = "BackgroundConst = ";
			BackgroundStrTotal += fitBackgroundTotal;
			BackgroundStrTotal += " ± ";
			BackgroundStrTotal += fitBackgroundTotalErr;
			if (fitType!="exp"){
				TString LinearStrTotal = "Linear = ";
				LinearStrTotal += fitLinearTotal;
				LinearStrTotal += " ± ";
				LinearStrTotal += fitLinearTotalErr;
				TString QuadraticStrTotal = "Quadratic = ";
				QuadraticStrTotal += fitQuadraticTotal;
				QuadraticStrTotal += " ± ";
				QuadraticStrTotal += fitQuadraticTotalErr;
			}
			TText *Total1 = fitResultsTotal->AddText(WeightStrTotal);
			TText *Total2 = fitResultsTotal->AddText(MeanStrTotal);
			TText *Total3 = fitResultsTotal->AddText(SigmaStrTotal);
			TText *Total4 = fitResultsTotal->AddText(BackgroundStrTotal);
			if (fitType=="exp")
			{
				TText *Total5 = fitResultsTotal->AddText(TauStrTotal);
				TText *Total6 = fitResultsTotal->AddText(OffsetStrTotal);
			}
			if (fitType!="exp")
			{
				TText *Total5 = fitResultsTotal->AddText(LinearStrTotal);
				TText *Total6 = fitResultsTotal->AddText(QuadraticStrTotal);
			}
			TText *Total7 = fitResultsTotal->AddText(fitTypeStr);
//			ToFgoodEvent->Draw("same");
			ToFgoodEvent->Draw();
			TString theFitTotalStr = "(";
			theFitTotalStr += fitWeightTotal;
			theFitTotalStr += "*exp(-0.5*((x-";
			theFitTotalStr += fitMeanTotal;
			theFitTotalStr += ")/";
			theFitTotalStr += fitSigmaTotal;
			theFitTotalStr += ")^2))+";
			theFitTotalStr += fitBackgroundTotal;
			if (fitType=="exp")
			{
				theFitTotalStr += "+exp(";
				theFitTotalStr += fitTauTotal;
				theFitTotalStr += "*x+";
				theFitTotalStr += fitOffsetTotal;
				theFitTotalStr += ")";
			}
			if (fitType=="lin")
			{
				theFitTotalStr += "+x*";
				theFitTotalStr += fitLinearTotal;
			}
			if (fitType=="quad")
			{
				theFitTotalStr += "+x*";
				theFitTotalStr += fitLinearTotal;
				theFitTotalStr += "+x*x*";
				theFitTotalStr += fitQuadraticTotal;
			}


			TF1 *theFitTotal = new TF1("theFitTotal",theFitTotalStr,bgUpMin,bgUpMax);
			theFitTotal->SetLineColor(kMagenta);
			theFitTotal->Draw("same");
			double integralOfPeakTotal;
			integralOfPeakTotal = sigFitTotal->Integral((fitMeanTotal - 3*sqrt(fitSigmaTotal*fitSigmaTotal)),(fitMeanTotal + 3*sqrt(fitSigmaTotal*fitSigmaTotal)));
			TString peakIntTotal = "Integral of Peak: ";
			peakIntTotal +=  integralOfPeakTotal;
			cout << peakIntTotal << endl;
			TText *Total7 = fitResultsTotal->AddText(peakIntTotal);
			fitResultsTotal->Draw("same");

			if (twoSig){
				double lowerSigBound = fitMeanTotal - 2*sqrt(fitSigmaTotal*fitSigmaTotal);
				double upperSigBound = fitMeanTotal + 2*sqrt(fitSigmaTotal*fitSigmaTotal);
			}
			if (fiveSig){
				double lowerSigBound = fitMeanTotal - 5*sqrt(fitSigmaTotal*fitSigmaTotal);
				double upperSigBound = fitMeanTotal + 5*sqrt(fitSigmaTotal*fitSigmaTotal);
			}
			cout << "lowerSigBound = " << lowerSigBound << ", upperSigBound = " << upperSigBound << endl;
			if ((targ=="v") && (kine=="0.1"))
			{
//				2 Sigma
				if (twoSig){
					lowerSigBound = 639.95;
					upperSigBound = 685.512;
				}
// 				5 Sigma
				if(fiveSig){
					lowerSigBound = 605.778;
					upperSigBound = 719.684;
				}
			}
			if ((targ=="v") && (kine=="0.5"))
			{
//				2 Sigma
				if (twoSig){
					lowerSigBound = 651.139;
					upperSigBound = 678.495;
					}
// 				5 Sigma
				if(fiveSig){
					lowerSigBound = 630.622;
					upperSigBound = 799.012;
				}
			}

			if ((targ=="h") && (kine=="0.1"))
			{
//				2 Sigma
				if (twoSig){
					lowerSigBound = 647.307;
					upperSigBound = 673.249;
				}
//				5 Sigma
				if(fiveSig){
					lowerSigBound = 627.851;
					upperSigBound = 692.705;
				}
			}
			if ((targ=="h") && (kine=="0.5"))
			{
//				2 Sigma
				if (twoSig){
					lowerSigBound = 323.574;
					upperSigBound = 358.518;
				}

//				5 Sigma
				if(fiveSig){
					lowerSigBound = 297.366;
					upperSigBound = 384.726;
				}

			}
			if ((targ=="vh") && (kine=="1.0"))
			{
//				2 Sigma
				if (twoSig){
					lowerSigBound = 655.905;
					upperSigBound = 673.695;
				}

//				5 Sigma
				if(fiveSig){
					lowerSigBound = 642.562;
					upperSigBound = 687.037;
				}

			}
			if ((targ=="v") && (kine=="1.0"))
			{
//				2 Sigma
				if (twoSig){
					lowerSigBound = 655.803;
					upperSigBound = 674.456;
				}

//				5 Sigma
				if(fiveSig){
					lowerSigBound = 641.813;
					upperSigBound = 688.445;
				}

			}



			lowerSigBoundLine = new TLine(lowerSigBound,0,lowerSigBound,99999999999);
			upperSigBoundLine = new TLine(upperSigBound,0,upperSigBound,99999999999);
			lowerSigBoundLine->SetLineColor(kRed);
			lowerSigBoundLine->SetLineWidth(3);
			lowerSigBoundLine->Draw("same");
			upperSigBoundLine->SetLineColor(kRed);
			upperSigBoundLine->SetLineWidth(3);
			upperSigBoundLine->Draw("same");

			}
		tofpad2->Update();
		if (i==0)
		{
			TString tofQEpeakTitle = outputPlotsHere;
			tofQEpeakTitle += "qe_tof_peak";
			tofQEpeakTitle += "_for_Runs_";
			tofQEpeakTitle += HeRunNumber;
			tofQEpeakTitle += "-";
			tofQEpeakTitle += endHeRunNumber;
			if (includeVetos) {tofQEpeakTitle += "_with_vetos";}
		//	tofQEpeakTitle += ".eps";
			tofQEpeakTitle += ".pdf";
			tofpad2->Print(tofQEpeakTitle);
		}
		tofpad3->cd();
/*		ToFupTotal->SetFillColor(kWhite);
		ToFupTotal->SetMinimum(0);
		ToFupTotal->Draw();
		ToFup->SetFillColor(kViolet);
		ToFup->SetMinimum(0);
		ToFup->Draw("same");
*/		ToFup->SetFillColor(kWhite);
//		ToFup->SetMinimum(0);
		ToFup->Draw();

		totalGoodEventsUp = 0;
		sigUpMin = lowerSigBound;
		sigUpMax = upperSigBound;
		sigMin = sigUpMin;
		sigMax = sigUpMax;
		sigMinBin = (sigMin - tofMin)/binSize;
		sigMaxBin = (sigMax - tofMin)/binSize;
		h3Uptitle = "h3Up_bin_";
		h3Uptitle += i;
		bgUpTitle = "bgFitUp_bin";
		bgUpTitle += i;
		if (fitType=="const"){bgFitUp = new TF1(bgUpTitle,"[0]",bgUpMin,bgUpMax);}
		if (fitType=="lin"){bgFitUp = new TF1(bgUpTitle,"[0]+[1]*x",bgUpMin,bgUpMax);}
		if (fitType=="quad"){bgFitUp = new TF1(bgUpTitle,"[0]+[1]*x+[2]*x*x",bgUpMin,bgUpMax);}
		if (fitType=="exp"){bgFitUp = new TF1(bgUpTitle,"exp([1]*x+[0])+[2]",bgUpMin,bgUpMax);}
//		bgFitUp = new TF1(bgUpTitle,fline,bgUpMin,sigUpMin,3);
// !!!!!!!!!!!!!!!!!!!!!!! TO CHANGE WHAT THE BACKGROUND FITS, CHANGE THE MIN/MAX BELOW !!!!!!!!!!!!!!!!!! bgfit !!!!!!!!!!!!!!!!!!
		bgFitUp = new TF1(bgUpTitle,fline,allBgMin,allBgMax,3);
		bgFitUp->SetLineColor(kOrange);
		if (fitType=="exp")
		{
			bgFitUp->SetParameter(0,1); bgFitUp->SetParameter(1,1/1600); bgFitUp->SetParameter(2,1);
			bgFitUp->SetParName(0,"Offset"); bgFitUp->SetParName(1,"Tau"); bgFitUp->SetParName(2,"Background");
		}
		if (fitType!="exp")
		{
			bgFitUp->SetParameter(0,1); bgFitUp->SetParameter(1,1); bgFitUp->SetParameter(2,1);
			bgFitUp->SetParName(0,"Background"); bgFitUp->SetParName(1,"Linear"); bgFitUp->SetParName(2,"Quadratic");
		}
		reject = kTRUE;
		ToFup->Fit(bgFitUp,"R");
		reject = kFALSE;
		fleftUp = new TF1("fleftUp",fline,bgUpMin,sigUpMin,3);
		fleftUp->SetLineColor(kOrange);
		fleftUp->SetParameters(bgFitUp->GetParameters());
		ToFup->GetListOfFunctions()->Add(fleftUp);
		gROOT->GetListOfFunctions()->Remove(fleftUp);
		frightUp = new TF1("frightUp",fline,sigUpMax,bgUpMax,3);
		frightUp->SetLineColor(kOrange);
		frightUp->SetParameters(bgFitUp->GetParameters());
		ToFup->GetListOfFunctions()->Add(frightUp);
		gROOT->GetListOfFunctions()->Remove(frightUp);
		ToFup->Draw();
		if (fitType=="exp")
		{
			fitOffsetUp = bgFitUp->GetParameter(0); fitTauUp = bgFitUp->GetParameter(1); fitBackgroundUp = bgFitUp->GetParameter(2);
			fitOffsetUpErr = bgFitUp->GetParError(0); fitTauUpErr = bgFitUp->GetParError(1); fitBackgroundUpErr = bgFitUp->GetParError(2);
		}
		if (fitType!="exp")
		{
			fitBackgroundUp = bgFitUp->GetParameter(0); fitLinearUp = bgFitUp->GetParameter(1); fitQuadraticUp = bgFitUp->GetParameter(2);
			fitBackgroundUpErr = bgFitUp->GetParError(0); fitLinearUpErr = bgFitUp->GetParError(1); fitQuadraticUpErr = bgFitUp->GetParError(2);
		}
		bgUp = new TH1F(bgUpTitle,"bgUp",tofBins,tofMin,tofMax);
		cout << "Number of Bins: " << ToFup->GetSize()-2 << endl;
		for (int j=0; j<(ToFup->GetSize()-2); j++)
		{
			xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
			if (fitType=="const") {bgUp->Fill(xpos,fitBackgroundUp);}
			if (fitType=="lin")   {bgUp->Fill(xpos,(fitBackgroundUp + fitLinearUp*xpos));}
			if (fitType=="quad")  {bgUp->Fill(xpos,(fitBackgroundUp + fitLinearUp*xpos + fitQuadraticUp*xpos*xpos));}
			if (fitType=="exp")  {bgUp->Fill(xpos,(exp(fitTauUp*xpos + fitOffsetUp) + fitBackgroundUp));}
		}
		bgUp->SetLineColor(kBlue);
		bgUp->Draw("same");
		fitResultsUp = new TPaveText(0.6,0.25,0.9,0.55,"NDC");
		if (fitType=="exp")
		{
			OffsetStrUp = "Offset = "; OffsetStrUp += fitOffsetUp; OffsetStrUp += " ± "; OffsetStrUp += fitOffsetUpErr;
			TauStrUp = "Tau = "; TauStrUp += fitTauUp; TauStrUp += " ± "; TauStrUp += fitTauUpErr;
		}
		BackgroundStrUp = "BackgroundConst = "; BackgroundStrUp += fitBackgroundUp; BackgroundStrUp += " ± "; BackgroundStrUp += fitBackgroundUpErr;
		if (fitType!="exp"){
			LinearStrUp = "Linear = "; LinearStrUp += fitLinearUp; LinearStrUp += " ± "; LinearStrUp += fitLinearUpErr;
			QuadraticStrUp = "Quadratic = "; QuadraticStrUp += fitQuadraticUp; QuadraticStrUp += " ± "; QuadraticStrUp += fitQuadraticUpErr;
		}
		Up4 = fitResultsUp->AddText(BackgroundStrUp);
		if (fitType=="exp")
		{
			Up5 = fitResultsUp->AddText(TauStrUp);
			Up6 = fitResultsUp->AddText(OffsetStrUp);
		}
		if (fitType!="exp")
		{
			Up5 = fitResultsUp->AddText(LinearStrUp);
			Up6 = fitResultsUp->AddText(QuadraticStrUp);
		}
		Up7 = fitResultsUp->AddText(fitTypeStr);
		ToFup->Draw("same");
		theFitUpStr = fitBackgroundUp;
		if (fitType=="exp")
		{
			theFitUpStr += "+exp("; theFitUpStr += fitTauUp; theFitUpStr += "*x+"; theFitUpStr += fitOffsetUp; theFitUpStr += ")";
		}
		if (fitType=="lin")
		{
			theFitUpStr += "+x*"; theFitUpStr += fitLinearUp;
		}
		if (fitType=="quad")
		{
			theFitUpStr += "+x*"; theFitUpStr += fitLinearUp; theFitUpStr += "+x*x*"; theFitUpStr += fitQuadraticUp;
		}
		theFitUpTitle = "theFitUp_bin_"; theFitUpTitle += i;
		fitResultsUp->Draw("same");
		fitResultsUp = NULL;
		Up1 = NULL;
		Up2 = NULL;
		Up3 = NULL;
		Up4 = NULL;
		Up5 = NULL;
		Up6 = NULL;
		tofpad3->Update();

		tofpad5->cd();
		h3Up = new TH1F(h3Uptitle,titleToFup,tofBins,tofMin,tofMax);
		h3Up->Add(ToFup);
		h3Up->Add(bgUp,-1);
		h3Up->SetLineColor(kRed);
		goodEventsUpPlot = "goodEventsUp_bin_";
		goodEventsUpPlot += i;
		goodEventsUpTitle = "ToF Spin UP Signal Events for nu bin ";
		goodEventsUpTitle += i;
		if (i==0) {goodEventsUpTitle = "ToF Spin Up Signal Events for All Nu Bins";}
		goodEventsUp = new TH1F(goodEventsUpPlot,goodEventsUpTitle,tofBins,tofMin,tofMax);
		cout << "sigUpMin: " << sigUpMin << ", sigUpMax: " << sigUpMax << endl;
		cout << "ToF Bin Size: " << binSize << ", sigMinBin = " << sigMinBin << ", sigMaxBin = " << sigMaxBin << endl;
		for (int k=sigMinBin; k<=sigMaxBin; k++)
		{
			thisBinContent = 0;
			thisBinContent = h3Up->GetBinContent(k);
			if (theSmallestBin>thisBinContent) {theSmallestBin = thisBinContent;}
			if (thisBinContent < 0) {thisBinContent = 0;}
			if (theBiggestBin<thisBinContent) {theBiggestBin = thisBinContent;}
			totalGoodEventsUp = totalGoodEventsUp + thisBinContent;
			goodEventsUp->Fill((k-1)*binSize + tofMin,thisBinContent);
		}
		cout << "i: " << i << endl;
		goodUpEvents[i] = totalGoodEventsUp;
		goodEventsUp->SetFillColor(kViolet);
		goodEventsUp->SetLineColor(kViolet);
		h3Up->SetMaximum(theBiggestBin + theBiggestBin/10);
		goodEventsUp->SetMinimum(theSmallestBin + theSmallestBin/10);
		goodEventsUp->Draw();
		h3Up->Draw("same");
// **************** TESTING SOMETHING BELOW ******************************************************************
		bgh3UpTitle = "bgFith3Up_bin";
		bgh3UpTitle += i;
		fitTypeHolder = fitType;
		fitType = "const";
		if (fitType=="const"){bgFith3Up = new TF1(bgh3UpTitle,"[0]",bgUpMin,bgUpMax);}
//		bgFith3Up = new TF1(bgh3UpTitle,fline,bgUpMin,sigUpMin,3);
		bgFith3Up = new TF1(bgh3UpTitle,fline,allBgMin,allBgMax,3);
		bgFith3Up->SetLineColor(kOrange);
//		bgFith3Up->SetParameter(0,1);
		bgFith3Up->SetParName(0,"h3Background");
		reject = kTRUE;
		h3Up->Fit(bgFith3Up,"RLL","same");
		reject = kFALSE;
		flefth3Up = new TF1("flefth3Up",fline,bgUpMin,sigUpMin,3);
		flefth3Up->SetLineColor(kOrange);
		flefth3Up->SetParameters(bgFith3Up->GetParameters());
		h3Up->GetListOfFunctions()->Add(flefth3Up);
		gROOT->GetListOfFunctions()->Remove(flefth3Up);
		frighth3Up = new TF1("frighth3Up",fline,sigUpMax,bgUpMax,3);
		frighth3Up->SetLineColor(kOrange);
		frighth3Up->SetParameters(bgFith3Up->GetParameters());
		h3Up->GetListOfFunctions()->Add(frighth3Up);
		gROOT->GetListOfFunctions()->Remove(frighth3Up);
		h3Up->Draw("same");
		fitBackgroundh3Up = bgFith3Up->GetParameter(0);
		fitBackgroundh3UpErr = bgFith3Up->GetParError(0);
		fitType = fitTypeHolder;
// *************** TESTING SOMETHING ABOVE *****************************************************************
		goodUpInfo = new TPaveText(0.6,0.11,0.895,0.3,"NDC");
		TString h3UpbgStr = "bgConst: ";
		h3UpbgStr += fitBackgroundh3Up;
		TString h3UpbgErrStr = "bgConst Error: ";
		h3UpbgErrStr += fitBackgroundh3UpErr;
		goodEventStr = "# of Good Up Events: ";
		goodEventStr += totalGoodEventsUp;
		goodUp = goodUpInfo->AddText(goodEventStr);
		goodUp = goodUpInfo->AddText(h3UpbgStr);
		goodUp = goodUpInfo->AddText(h3UpbgErrStr);
		goodUpInfo->Draw("same");
		tofpad5->Update();

		tofpad7->cd();
		int eventsup;
		TH1F *eventDistUp = new TH1F("eventDistUp","# bins v. # events/bin for spin up",25,-200,200);
		for (int k=0; k<(h3Up->GetSize()-2); k++)
		{
			eventsup = h3Up->GetBinContent(k);
//			if ((h3Up->GetBinCenter(k))<sigMin || (h3Up->GetBinCenter(k))>sigMax) {eventDistUp->Fill(eventsup);}
			if ((h3Up->GetBinCenter(k))<sigMin) {eventDistUp->Fill(eventsup);}
		}
		eventDistUp->Draw();
		TF1 *upfit = new TF1("upfit","gaus",-200,200);
		eventDistUp->Fit(upfit,"R","same");
		bgUpErr[i] = upfit->GetParameter(2);
		cout << "bgUpErr[" << i << "] = " << bgUpErr[i] << endl;
		tofpad7->Update();
		h3Up = NULL;


		tofpad4->cd();
/*		ToFdownTotal->SetFillColor(kWhite);
		ToFdownTotal->SetMinimum(0);
		ToFdownTotal->Draw();
		ToFdown->SetFillColor(kViolet);
		ToFdown->SetMinimum(0);
		ToFdown->Draw("same");
*/		ToFdown->SetFillColor(kWhite);
		ToFdown->Draw();

		totalGoodEventsDown = 0;
		sigDownMin = lowerSigBound;
		sigDownMax = upperSigBound;
		sigMin = sigDownMin;
		sigMax = sigDownMax;
		sigMinBin = (sigMin - tofMin)/binSize;
		sigMaxBin = (sigMax - tofMin)/binSize;
		h3Downtitle = "h3Down_bin_";
		h3Downtitle += i;
		bgDownTitle = "bgFitDown_bin";
		bgDownTitle += i;
		if (fitType=="const"){bgFitDown = new TF1(bgDownTitle,"[0]",bgDownMin,bgDownMax);}
		if (fitType=="lin"){bgFitDown = new TF1(bgDownTitle,"[0]+[1]*x",bgDownMin,bgDownMax);}
		if (fitType=="quad"){bgFitDown = new TF1(bgDownTitle,"[0]+[1]*x+[2]*x*x",bgDownMin,bgDownMax);}
		if (fitType=="exp"){bgFitDown = new TF1(bgDownTitle,"exp([1]*x+[0])+[2]",bgDownMin,bgDownMax);}
// !!!!!!!!!!!!!!!!!!!!!!! TO CHANGE WHAT THE BACKGROUND FITS, CHANGE THE MIN/MAX BELOW !!!!!!!!!!!!!!!!!! bgfit !!!!!!!!!!!!!!!!!!
		bgFitDown = new TF1(bgDownTitle,fline,allBgMin,allBgMax,3);
		bgFitDown->SetLineColor(kOrange);
		if (fitType=="exp")
		{
			bgFitDown->SetParameter(0,1); bgFitDown->SetParameter(1,1/1600); bgFitDown->SetParameter(2,1);
			bgFitDown->SetParName(0,"Offset"); bgFitDown->SetParName(1,"Tau"); bgFitDown->SetParName(2,"Background");
		}
		if (fitType!="exp")
		{
			bgFitDown->SetParameter(0,1); bgFitDown->SetParameter(1,1); bgFitDown->SetParameter(2,1);
			bgFitDown->SetParName(0,"Background"); bgFitDown->SetParName(1,"Linear"); bgFitDown->SetParName(2,"Quadratic");
		}
		reject = kTRUE;
		ToFdown->Fit(bgFitDown,"R");
		reject = kFALSE;
		fleftDown = new TF1("fleftDown",fline,bgDownMin,sigDownMin,3);
		fleftDown->SetLineColor(kOrange);
		fleftDown->SetParameters(bgFitDown->GetParameters());
		ToFdown->GetListOfFunctions()->Add(fleftDown);
		gROOT->GetListOfFunctions()->Remove(fleftDown);
		frightDown = new TF1("frightDown",fline,sigDownMax,bgDownMax,3);
		frightDown->SetLineColor(kOrange);
		frightDown->SetParameters(bgFitDown->GetParameters());
		ToFdown->GetListOfFunctions()->Add(frightDown);
		gROOT->GetListOfFunctions()->Remove(frightDown);
		ToFdown->Draw();
		if (fitType=="exp")
		{
			fitOffsetDown = bgFitDown->GetParameter(0); fitTauDown = bgFitDown->GetParameter(1); fitBackgroundDown = bgFitDown->GetParameter(2);
			fitOffsetDownErr = bgFitDown->GetParError(0); fitTauDownErr = bgFitDown->GetParError(1); fitBackgroundDownErr = bgFitDown->GetParError(2);
		}
		if (fitType!="exp")
		{
			fitBackgroundDown = bgFitDown->GetParameter(0); fitLinearDown = bgFitDown->GetParameter(1); fitQuadraticDown = bgFitDown->GetParameter(2);
			fitBackgroundDownErr = bgFitDown->GetParError(0); fitLinearDownErr = bgFitDown->GetParError(1); fitQuadraticDownErr = bgFitDown->GetParError(2);
		}
		bgDown = new TH1F(bgDownTitle,"bgDown",tofBins,tofMin,tofMax);
		cout << "Number of Bins: " << ToFdown->GetSize()-2 << endl;
		for (int j=0; j<(ToFdown->GetSize()-2); j++)
		{
			xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
			if (fitType=="const") {bgDown->Fill(xpos,fitBackgroundDown);}
			if (fitType=="lin")   {bgDown->Fill(xpos,(fitBackgroundDown + fitLinearDown*xpos));}
			if (fitType=="quad")  {bgDown->Fill(xpos,(fitBackgroundDown + fitLinearDown*xpos + fitQuadraticDown*xpos*xpos));}
			if (fitType=="exp")  {bgDown->Fill(xpos,(exp(fitTauDown*xpos + fitOffsetDown) + fitBackgroundDown));}
		}

		bgDown->SetLineColor(kBlue);
		bgDown->Draw("same");
		fitResultsDown = new TPaveText(0.6,0.25,0.9,0.55,"NDC");
		if (fitType=="exp")
		{
			OffsetStrDown = "Offset = "; OffsetStrDown += fitOffsetDown; OffsetStrDown += " ± "; OffsetStrDown += fitOffsetDownErr;
			TauStrDown = "Tau = "; TauStrDown += fitTauDown; TauStrDown += " ± "; TauStrDown += fitTauDownErr;
		}
		BackgroundStrDown = "BackgroundConst = "; BackgroundStrDown += fitBackgroundDown; BackgroundStrDown += " ± "; BackgroundStrDown += fitBackgroundDownErr;
		if (fitType!="exp"){
			LinearStrDown = "Linear = "; LinearStrDown += fitLinearDown; LinearStrDown += " ± "; LinearStrDown += fitLinearDownErr;
			QuadraticStrDown = "Quadratic = "; QuadraticStrDown += fitQuadraticDown; QuadraticStrDown += " ± "; QuadraticStrDown += fitQuadraticDownErr;
		}
		Down4 = fitResultsDown->AddText(BackgroundStrDown);
		if (fitType=="exp")
		{
			Down5 = fitResultsDown->AddText(TauStrDown);
			Down6 = fitResultsDown->AddText(OffsetStrDown);
		}
		if (fitType!="exp")
		{
			Down5 = fitResultsDown->AddText(LinearStrDown);
			Down6 = fitResultsDown->AddText(QuadraticStrDown);
		}
		Down7 = fitResultsDown->AddText(fitTypeStr);
		ToFdown->Draw("same");
		theFitDownStr = fitBackgroundDown;
		if (fitType=="exp")
		{
			theFitDownStr += "+exp("; theFitDownStr += fitTauDown; theFitDownStr += "*x+"; theFitDownStr += fitOffsetDown; theFitDownStr += ")";
		}
		if (fitType=="lin")
		{
			theFitDownStr += "+x*"; theFitDownStr += fitLinearDown;
		}
		if (fitType=="quad")
		{
			theFitDownStr += "+x*"; theFitDownStr += fitLinearDown; theFitDownStr += "+x*x*"; theFitDownStr += fitQuadraticDown;
		}
		theFitDownTitle = "theFitDown_bin_"; theFitDownTitle += i;
		fitResultsDown->Draw("same");
		fitResultsDown = NULL;
		Down1 = NULL;
		Down2 = NULL;
		Down3 = NULL;
		Down4 = NULL;
		Down5 = NULL;
		Down6 = NULL;
		tofpad4->Update();

		tofpad6->cd();
		h3Down = new TH1F(h3Downtitle,titleToFdown,tofBins,tofMin,tofMax);
		h3Down->Add(ToFdown);
		h3Down->Add(bgDown,-1);
		h3Down->SetLineColor(kRed);
		goodEventsDownPlot = "goodEventsDown_bin_";
		goodEventsDownPlot += i;
		goodEventsDownTitle = "ToF Spin UP Signal Events for nu bin ";
		goodEventsDownTitle += i;
		if (i==0) {goodEventsDownTitle = "ToF Spin Down Signal Events for All Nu Bins";}
		goodEventsDown = new TH1F(goodEventsDownPlot,goodEventsDownTitle,tofBins,tofMin,tofMax);
		cout << "sigDownMin: " << sigDownMin << ", sigDownMax: " << sigDownMax << endl;
		cout << "ToF Bin Size: " << binSize << ", sigMinBin = " << sigMinBin << ", sigMaxBin = " << sigMaxBin << endl;
		for (int k=sigMinBin; k<=sigMaxBin; k++)
		{
			thisBinContent = 0;
			thisBinContent = h3Down->GetBinContent(k);
			if (theSmallestBin>thisBinContent) {theSmallestBin = thisBinContent;}
			if (thisBinContent < 0) {thisBinContent = 0;}
			if (theBiggestBin<thisBinContent) {theBiggestBin = thisBinContent;}
			totalGoodEventsDown = totalGoodEventsDown + thisBinContent;
			goodEventsDown->Fill((k-1)*binSize + tofMin,thisBinContent);
		}
		goodDownEvents[i] = totalGoodEventsDown;
		goodEventsDown->SetFillColor(kViolet);
		goodEventsDown->SetLineColor(kViolet);
//		h3Down->SetMaximum(theBiggestBin + theBiggestBin/10);
		goodEventsDown->SetMinimum(theSmallestBin + theSmallestBin/10);
		goodEventsDown->Draw();
		h3Down->Draw("same");
		goodDownInfo = new TPaveText(0.6,0.11,0.895,0.2,"NDC");
		goodEventStr = "# of Good Down Events: ";
		goodEventStr += totalGoodEventsDown;
		goodDown = goodDownInfo->AddText(goodEventStr);
		goodDownInfo->Draw("same");
		tofpad6->Update();

		tofpad8->cd();
		int eventsdown;
		TH1F *eventDistDown = new TH1F("eventDistDown","# bins v. # events/bin for spin down",25,-200,200);
		for (int k=0; k<(h3Down->GetSize()-2); k++)
		{
			eventsdown = h3Down->GetBinContent(k);
//			if ((h3Down->GetBinCenter(k))<sigMin || (h3Down->GetBinCenter(k))>sigMax) {eventDistDown->Fill(eventsdown);}
			if ((h3Down->GetBinCenter(k))<sigMin) {eventDistDown->Fill(eventsdown);}
		}
		eventDistDown->Draw();
		TF1 *downfit = new TF1("downfit","gaus",-200,200);
		eventDistDown->Fit(downfit,"R","same");
		bgDownErr[i] = downfit->GetParameter(2);
		cout << "bgDownErr[" << i << "] = " << bgDownErr[i] << endl;
		tofpad8->Update();
		h3Down = NULL;


		ToFnuOutTitle = outputPlotsHere;
		ToFnuOutTitle += "tof_and_nu_bin_";
		if (i<10) {ToFnuOutTitle += "0";}
		ToFnuOutTitle += i;
		if (i==0) 
		{
			ToFnuOutTitle = outputPlotsHere;
			ToFnuOutTitle += "tof_and_nu_total";
		}
		ToFnuOutTitle += "_plots_for_Runs_";
		ToFnuOutTitle += HeRunNumber;
		ToFnuOutTitle += "-";
		ToFnuOutTitle += endHeRunNumber;
		if (includeVetos) {ToFnuOutTitle += "_with_vetos";}
		ToFnuOutTitle += ".png";
		ToFCanvas->Print(ToFnuOutTitle);

		if ((kine!="0.1") && ((i==7) || (i==8) || (i==9)))
		{
			nuQEcuts->Add(nuAllCuts);
			tofWithNuQEBinsUp->Add(ToFup);
			tofWithNuQEBinsDown->Add(ToFdown);
		}

		if ((kine=="0.1") && ((i==7) || (i==8) || (i==9)))
		{
			nuQEcuts->Add(nuAllCuts);
			tofWithNuQEBinsUp->Add(ToFup);
			tofWithNuQEBinsDown->Add(ToFdown);
		}


	}

	TCanvas *goodToFCanvas = new TCanvas("goodToFCanvas","ToF on the QE Peak",1360,768); //x,y
	goodtofpad1  =  new  TPad("goodtofpad1","goodtofpad1",0.0000,0.7500,0.5000,1.0000,0,0,0);
	goodtofpad2  =  new  TPad("goodtofpad2","goodtofpad2",0.5000,0.7500,1.0000,1.0000,0,0,0);
	goodtofpad3  =  new  TPad("goodtofpad3","goodtofpad3",0.0000,0.5000,0.5000,0.7500,0,0,0);
	goodtofpad4  =  new  TPad("goodtofpad4","goodtofpad4",0.5000,0.5000,1.0000,0.7500,0,0,0);
	goodtofpad5  =  new  TPad("goodtofpad5","goodtofpad5",0.0000,0.2500,0.5000,0.5000,0,0,0);
	goodtofpad6  =  new  TPad("goodtofpad6","goodtofpad6",0.5000,0.2500,1.0000,0.5000,0,0,0);
	goodtofpad7  =  new  TPad("goodtofpad7","goodtofpad7",0.0000,0.0000,0.5000,0.2500,0,0,0);
	goodtofpad8  =  new  TPad("goodtofpad8","goodtofpad8",0.5000,0.0000,1.0000,0.2500,0,0,0);
	goodtofpad1->Draw(); goodtofpad2->Draw(); goodtofpad3->Draw(); goodtofpad4->Draw(); goodtofpad5->Draw(); goodtofpad6->Draw();
	goodtofpad7->Draw(); goodtofpad8->Draw();


	goodtofpad1->cd();
	nuAllCutsTotal->SetFillColor(kWhite);
	nuAllCutsTotal->SetMinimum(0);
	nuAllCutsTotal->Draw();
	nuQEcuts->SetFillColor(kViolet);
	nuQEcuts->SetMinimum(0);
	nuQEcuts->Draw("same");
	goodtofpad1->Update();


	goodtofpad3->cd();
	tofWithNuQEBinsUp->SetStats(kFALSE);
	tofWithNuQEBinsUp->Draw();

	totalGoodEventsUp = 0;
	sigUpMin = lowerSigBound;
	sigUpMax = upperSigBound;
	sigMin = sigUpMin;
	sigMax = sigUpMax;
	sigMinBin = (sigMin - tofMin)/binSize;
	sigMaxBin = (sigMax - tofMin)/binSize;
	h3Uptitle = "h3Up_bin_";
	h3Uptitle += i;
	bgUpTitle = "bgFitUp_bin";
	bgUpTitle += i;
	if (fitType=="const"){bgFitUp = new TF1(bgUpTitle,"[0]",bgUpMin,bgUpMax);}
	if (fitType=="lin"){bgFitUp = new TF1(bgUpTitle,"[0]+[1]*x",bgUpMin,bgUpMax);}
	if (fitType=="quad"){bgFitUp = new TF1(bgUpTitle,"[0]+[1]*x+[2]*x*x",bgUpMin,bgUpMax);}
	if (fitType=="exp"){bgFitUp = new TF1(bgUpTitle,"exp([1]*x+[0])+[2]",bgUpMin,bgUpMax);}
// !!!!!!!!!!!!!!!!!!!!!!! TO CHANGE WHAT THE BACKGROUND FITS, CHANGE THE MIN/MAX BELOW !!!!!!!!!!!!!!!!!! bgfit !!!!!!!!!!!!!!!!!!
	bgFitUp = new TF1(bgUpTitle,fline,allBgMin,allBgMax,3);
	bgFitUp->SetLineColor(kOrange);
	bgFitUp->SetLineWidth(0);
	if (fitType=="exp")
	{
		bgFitUp->SetParameter(0,1); bgFitUp->SetParameter(1,1/1600); bgFitUp->SetParameter(2,1);
		bgFitUp->SetParName(0,"Offset"); bgFitUp->SetParName(1,"Tau"); bgFitUp->SetParName(2,"Background");
	}
	if (fitType!="exp")
	{
		bgFitUp->SetParameter(0,1); bgFitUp->SetParameter(1,1); bgFitUp->SetParameter(2,1);
		bgFitUp->SetParName(0,"Background"); bgFitUp->SetParName(1,"Linear"); bgFitUp->SetParName(2,"Quadratic");
	}
	reject = kTRUE;
	tofWithNuQEBinsUp->Fit(bgFitUp,"R");
	reject = kFALSE;
	fleftUp = new TF1("fleftUp",fline,bgUpMin,sigUpMin,3);
	fleftUp->SetLineColor(kOrange);
	fleftUp->SetLineWidth(0);
	fleftUp->SetParameters(bgFitUp->GetParameters());
	tofWithNuQEBinsUp->GetListOfFunctions()->Add(fleftUp);
	gROOT->GetListOfFunctions()->Remove(fleftUp);
	frightUp = new TF1("frightUp",fline,sigUpMax,bgUpMax,3);
	frightUp->SetLineColor(kOrange);
	frightUp->SetLineWidth(0);
	frightUp->SetParameters(bgFitUp->GetParameters());
	tofWithNuQEBinsUp->GetListOfFunctions()->Add(frightUp);
	gROOT->GetListOfFunctions()->Remove(frightUp);
	tofWithNuQEBinsUp->Draw();
	if (fitType=="exp")
	{
		fitOffsetUp = bgFitUp->GetParameter(0); fitTauUp = bgFitUp->GetParameter(1); fitBackgroundUp = bgFitUp->GetParameter(2);
		fitOffsetUpErr = bgFitUp->GetParError(0); fitTauUpErr = bgFitUp->GetParError(1); fitBackgroundUpErr = bgFitUp->GetParError(2);
	}
	if (fitType!="exp")
	{
		fitBackgroundUp = bgFitUp->GetParameter(0); fitLinearUp = bgFitUp->GetParameter(1); fitQuadraticUp = bgFitUp->GetParameter(2);
		fitBackgroundUpErr = bgFitUp->GetParError(0); fitLinearUpErr = bgFitUp->GetParError(1); fitQuadraticUpErr = bgFitUp->GetParError(2);
	}
	bgUp = new TH1F(bgUpTitle,"bgUp",tofBins,tofMin,tofMax);
	cout << "Number of Bins: " << tofWithNuQEBinsUp->GetSize()-2 << endl;
	if (!(kine=="0.5" && targ=="v" && forceBG))
	{
		for (int j=0; j<(tofWithNuQEBinsUp->GetSize()-2); j++)
		{
			xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
			if (fitType=="const") {bgUp->Fill(xpos,fitBackgroundUp);}
			if (fitType=="lin")   {bgUp->Fill(xpos,(fitBackgroundUp + fitLinearUp*xpos));}
			if (fitType=="quad")  {bgUp->Fill(xpos,(fitBackgroundUp + fitLinearUp*xpos + fitQuadraticUp*xpos*xpos));}
			if (fitType=="exp")  {bgUp->Fill(xpos,(exp(fitTauUp*xpos + fitOffsetUp) + fitBackgroundUp));}
		}
	}
	if ((kine=="0.5" && targ=="v" && forceBG))
	{
		if (includeVetos)
		{
			for (int j=0; j<((625-tofMin)/((tofMax-tofMin)/tofBins)); j++)
			{
				xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
//				bgUp->Fill(xpos,130544.326); // <--- 3He Data
				bgUp->Fill(xpos,8724.76706); // <--- H2 Data
			}
			for (int j=((625-tofMin)/((tofMax-tofMin)/tofBins)); j<((740-tofMin)/((tofMax-tofMin)/tofBins)); j++)
			{
				xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
//				bgUp->Fill(xpos,(167723.39 - 59.49*xpos)); // <--- 3He Data
				bgUp->Fill(xpos,(43.29*xpos - 18322.515)); // <--- H2 Data
			}
			for (int j=((740-tofMin)/((tofMax-tofMin)/tofBins)); j<(tofWithNuQEBinsUp->GetSize()-2); j++)
			{
				xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
//				bgUp->Fill(xpos,123703.378); // <--- 3He Data
				bgUp->Fill(xpos,13713.307); // <--- H2 Data
			}
		}
		if (!includeVetos)
		{
			for (int j=0; j<((625-tofMin)/((tofMax-tofMin)/tofBins)); j++)
			{
				xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
				bgUp->Fill(xpos,139757.037);
			}
			for (int j=((625-tofMin)/((tofMax-tofMin)/tofBins)); j<((740-tofMin)/((tofMax-tofMin)/tofBins)); j++)
			{
				xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
				bgUp->Fill(xpos,(150941.336 - 17.895*xpos));
			}
			for (int j=((740-tofMin)/((tofMax-tofMin)/tofBins)); j<(tofWithNuQEBinsUp->GetSize()-2); j++)
			{
				xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
				bgUp->Fill(xpos,137699.126);
			}
		}

	}

	bgUp->SetLineColor(kBlue);
	bgUp->SetStats(kFALSE);
	bgUp->Draw("same");
	fitResultsUp = new TPaveText(0.6,0.25,0.9,0.55,"NDC");
	if (fitType=="exp")
	{
		OffsetStrUp = "Offset = "; OffsetStrUp += fitOffsetUp; OffsetStrUp += " ± "; OffsetStrUp += fitOffsetUpErr;
		TauStrUp = "Tau = "; TauStrUp += fitTauUp; TauStrUp += " ± "; TauStrUp += fitTauUpErr;
	}
	BackgroundStrUp = "BackgroundConst = "; BackgroundStrUp += fitBackgroundUp; BackgroundStrUp += " ± "; BackgroundStrUp += fitBackgroundUpErr;
	if (fitType!="exp"){
		LinearStrUp = "Linear = "; LinearStrUp += fitLinearUp; LinearStrUp += " ± "; LinearStrUp += fitLinearUpErr;
		QuadraticStrUp = "Quadratic = "; QuadraticStrUp += fitQuadraticUp; QuadraticStrUp += " ± "; QuadraticStrUp += fitQuadraticUpErr;
		if (fitType=="lin") {QuadraticStrUp = "";}
	}
	Up4 = fitResultsUp->AddText(BackgroundStrUp);
	if (fitType=="exp")
	{
		Up5 = fitResultsUp->AddText(TauStrUp);
		Up6 = fitResultsUp->AddText(OffsetStrUp);
	}
	if (fitType!="exp")
	{
		Up5 = fitResultsUp->AddText(LinearStrUp);
		Up6 = fitResultsUp->AddText(QuadraticStrUp);
	}
	Up7 = fitResultsUp->AddText(fitTypeStr);
	tofWithNuQEBinsUp->Draw("same");
	theFitUpStr = fitBackgroundUp;
	if (fitType=="exp")
	{
		theFitUpStr += "+exp("; theFitUpStr += fitTauUp; theFitUpStr += "*x+"; theFitUpStr += fitOffsetUp; theFitUpStr += ")";
	}
	if (fitType=="lin")
	{
		theFitUpStr += "+x*"; theFitUpStr += fitLinearUp;
	}
	if (fitType=="quad")
	{
		theFitUpStr += "+x*"; theFitUpStr += fitLinearUp; theFitUpStr += "+x*x*"; theFitUpStr += fitQuadraticUp;
	}
	theFitUpTitle = "theFitUp_bin_"; theFitUpTitle += i;
//	fitResultsUp->SetStats(kFALSE);
	fitResultsUp->Draw("same");
	goodtofpad3->Update();
	TString tofQEupTitle = outputPlotsHere;
	tofQEupTitle += "qe_tof_and_nu_up";
	tofQEupTitle += "_for_Runs_";
	tofQEupTitle += HeRunNumber;
	tofQEupTitle += "-";
	tofQEupTitle += endHeRunNumber;
	if (includeVetos) {tofQEupTitle += "_with_vetos";}
//	tofQEupTitle += ".eps";
	tofQEupTitle += ".pdf";
	goodtofpad3->Print(tofQEupTitle);
	fitResultsUp = NULL;
	Up1 = NULL;
	Up2 = NULL;
	Up3 = NULL;
	Up4 = NULL;
	Up5 = NULL;
	Up6 = NULL;


	goodtofpad5->cd();
	h3Up = new TH1F(h3Uptitle,titleToFup,tofBins,tofMin,tofMax);
	h3Up->Add(tofWithNuQEBinsUp);
	h3Up->Add(bgUp,-1);
	h3Up->SetLineColor(kRed);
	h3Up->SetStats(kFALSE);
//	h3Up->Draw();
	goodEventsUpPlot = "goodEventsUp_QE";
	goodEventsUpTitle = "ToF Spin Up Signal Events for QE Peak";
	goodEventsUp = new TH1F(goodEventsUpPlot,goodEventsUpTitle,tofBins,tofMin,tofMax);
	cout << "sigUpMin: " << sigUpMin << ", sigUpMax: " << sigUpMax << endl;
	cout << "ToF Bin Size: " << binSize << ", sigMinBin = " << sigMinBin << ", sigMaxBin = " << sigMaxBin << endl;
	for (int k=sigMinBin; k<=sigMaxBin; k++)
	{
		thisBinContent = 0;
		thisBinContent = h3Up->GetBinContent(k);
		if (theSmallestBin>thisBinContent) {theSmallestBin = thisBinContent;}
		if (thisBinContent < 0) {thisBinContent = 0;}
		if (theBiggestBin<thisBinContent) {theBiggestBin = thisBinContent;}
		totalGoodEventsUp = totalGoodEventsUp + thisBinContent;
		goodEventsUp->Fill((k-1)*binSize + tofMin,thisBinContent);
	}
	goodEventsUp->SetFillColor(kViolet);
	goodEventsUp->SetLineColor(kViolet);
//	h3Up->SetMaximum(theBiggestBin + theBiggestBin/10);
	goodEventsUp->SetMaximum(theBiggestBin + theBiggestBin/10);
/*	if (kine=="0.1") 
	{
		if (includeVetos) {goodEventsUp->SetMaximum(200);}
		else {goodEventsUp->SetMaximum(4500);}
	}
	if (kine=="0.5") {goodEventsUp->SetMaximum(105000);}
	if (kine=="1.0") {goodEventsUp->SetMaximum(800000);}
*/
//	goodEventsUp->SetMinimum(theSmallestBin + theSmallestBin/10);
	goodEventsUp->SetMinimum(0);
	goodEventsUp->SetStats(kFALSE);
	goodEventsUp->Draw();
	h3Up->Draw("same");

// **************** TESTING SOMETHING BELOW ******************************************************************
	bgh3UpTitle = "bgFith3Up_bin";
	bgh3UpTitle += i;
	fitTypeHolder = fitType;
	fitType = "const";
	if (fitType=="const"){bgFith3Up = new TF1(bgh3UpTitle,"[0]", allBgMin,allBgMax);}
//	bgFith3Up = new TF1(bgh3UpTitle,fline,bgUpMin,sigUpMin,3);
	bgFith3Up = new TF1(bgh3UpTitle,fline,allBgMin,allBgMax,3);
	bgFith3Up->SetLineColor(kOrange);
//		bgFith3Up->SetParameter(0,1);
	bgFith3Up->SetParName(0,"h3Background");
	reject = kTRUE;
	h3Up->Fit(bgFith3Up,"RLL","same");
	reject = kFALSE;
	flefth3Up = new TF1("flefth3Up",fline,bgUpMin,sigUpMin,3);
	flefth3Up->SetLineColor(kOrange);
	flefth3Up->SetParameters(bgFith3Up->GetParameters());
	h3Up->GetListOfFunctions()->Add(flefth3Up);
	gROOT->GetListOfFunctions()->Remove(flefth3Up);
	frighth3Up = new TF1("frighth3Up",fline,sigUpMax,bgUpMax,3);
	frighth3Up->SetLineColor(kOrange);
	frighth3Up->SetParameters(bgFith3Up->GetParameters());
	h3Up->GetListOfFunctions()->Add(frighth3Up);
	gROOT->GetListOfFunctions()->Remove(frighth3Up);
	h3Up->Draw("same");
	fitBackgroundh3Up = bgFith3Up->GetParameter(0);
	fitBackgroundh3UpErr = bgFith3Up->GetParError(0);
	fitType = fitTypeHolder;
// *************** TESTING SOMETHING ABOVE *****************************************************************
	goodUpInfo = new TPaveText(0.6,0.11,0.895,0.3,"NDC");
	TString h3UpbgStr = "bgConst: ";
	h3UpbgStr += fitBackgroundh3Up;
	TString h3UpbgErrStr = "bgConst Error: ";
	h3UpbgErrStr += fitBackgroundh3UpErr;
	goodEventStr = "# of Good Up Events: ";
	goodEventStr += totalGoodEventsUp;
	goodUp = goodUpInfo->AddText(goodEventStr);
//	goodUp = goodUpInfo->AddText(h3UpbgStr);
//	goodUp = goodUpInfo->AddText(h3UpbgErrStr);
	goodUpInfo->Draw("same");
	goodtofpad5->Update();

	TString tofQEupBgSubTitle = outputPlotsHere;
	tofQEupBgSubTitle += "qe_tof_and_nu_up_bgsub";
	tofQEupBgSubTitle += "_for_Runs_";
	tofQEupBgSubTitle += HeRunNumber;
	tofQEupBgSubTitle += "-";
	tofQEupBgSubTitle += endHeRunNumber;
	if (includeVetos) {tofQEupBgSubTitle += "_with_vetos";}
//	tofQEupBgSubTitle += ".eps";
	tofQEupBgSubTitle += ".svg";
	goodtofpad5->Print(tofQEupBgSubTitle);

	goodtofpad7->cd();
//	TH1F *eventQEDistUp = new TH1F("eventQEDistUp","# bins v. # events/bin for spin up",50,-4000,4000);
	TH1F *eventQEDistUp = new TH1F("eventQEDistUp","# bins v. # events/bin for spin up",50,-200,200);
	for (int k=0; k<(h3Up->GetSize()-2); k++)
	{
		eventsup = h3Up->GetBinContent(k);
//		if ((h3Up->GetBinCenter(k))<sigMin || (h3Up->GetBinCenter(k))>sigMax) {eventQEDistUp->Fill(eventsup);}
		if ((h3Up->GetBinCenter(k))<sigMin) {eventQEDistUp->Fill(eventsup);}
	}
	eventQEDistUp->SetStats(kFALSE);
	eventQEDistUp->Draw();
	goodtofpad7->Update();
	TString tofQEupBgSubErrorTitle = outputPlotsHere;
	tofQEupBgSubErrorTitle += "qe_tof_and_nu_up_bgsub_err";
	tofQEupBgSubErrorTitle += "_for_Runs_";
	tofQEupBgSubErrorTitle += HeRunNumber;
	tofQEupBgSubErrorTitle += "-";
	tofQEupBgSubErrorTitle += endHeRunNumber;
	if (includeVetos) {tofQEupBgSubErrorTitle += "_with_vetos";}
//	tofQEupBgSubErrorTitle += ".eps";
	tofQEupBgSubErrorTitle += ".svg";
	goodtofpad7->Print(tofQEupBgSubErrorTitle);


	TF1 *upfit = new TF1("upfit","gaus",-200,200);
	eventQEDistUp->Fit(upfit,"R","same");
	cout << "bgUpErr[" << i << "] = " << bgUpErr[i] << endl;
	goodtofpad7->Update();


	h3Up = NULL;



	goodtofpad4->cd();
	tofWithNuQEBinsDown->SetStats(kFALSE);
	tofWithNuQEBinsDown->Draw();
	totalGoodEventsDown = 0;
	sigDownMin = lowerSigBound;
	sigDownMax = upperSigBound;
	sigMin = sigDownMin;
	sigMax = sigDownMax;
	sigMinBin = (sigMin - tofMin)/binSize;
	sigMaxBin = (sigMax - tofMin)/binSize;
	h3Downtitle = "h3Down_bin_";
	h3Downtitle += i;
	bgDownTitle = "bgFitDown_bin";
	bgDownTitle += i;
	if (fitType=="const"){bgFitDown = new TF1(bgDownTitle,"[0]",bgDownMin,bgDownMax);}
	if (fitType=="lin"){bgFitDown = new TF1(bgDownTitle,"[0]+[1]*x",bgDownMin,bgDownMax);}
	if (fitType=="quad"){bgFitDown = new TF1(bgDownTitle,"[0]+[1]*x+[2]*x*x",bgDownMin,bgDownMax);}
	if (fitType=="exp"){bgFitDown = new TF1(bgDownTitle,"exp([1]*x+[0])+[2]",bgDownMin,bgDownMax);}
// !!!!!!!!!!!!!!!!!!!!!!! TO CHANGE WHAT THE BACKGROUND FITS, CHANGE THE MIN/MAX BELOW !!!!!!!!!!!!!!!!!! bgfit !!!!!!!!!!!!!!!!!!
	bgFitDown = new TF1(bgDownTitle,fline,allBgMin,allBgMax,3);
	bgFitDown->SetLineColor(kOrange);
	bgFitDown->SetLineWidth(0);
	if (fitType=="exp")
	{
		bgFitDown->SetParameter(0,1); bgFitDown->SetParameter(1,1/1600); bgFitDown->SetParameter(2,1);
		bgFitDown->SetParName(0,"Offset"); bgFitDown->SetParName(1,"Tau"); bgFitDown->SetParName(2,"Background");
	}
	if (fitType!="exp")
	{
		bgFitDown->SetParameter(0,1); bgFitDown->SetParameter(1,1); bgFitDown->SetParameter(2,1);
		bgFitDown->SetParName(0,"Background"); bgFitDown->SetParName(1,"Linear"); bgFitDown->SetParName(2,"Quadratic");
	}
	reject = kTRUE;
	tofWithNuQEBinsDown->Fit(bgFitDown,"R");
	reject = kFALSE;
	fleftDown = new TF1("fleftDown",fline,bgDownMin,sigDownMin,3);
	fleftDown->SetLineColor(kOrange);
	fleftDown->SetLineWidth(0);
	fleftDown->SetParameters(bgFitDown->GetParameters());
	tofWithNuQEBinsDown->GetListOfFunctions()->Add(fleftDown);
	gROOT->GetListOfFunctions()->Remove(fleftDown);
	frightDown = new TF1("frightDown",fline,sigDownMax,bgDownMax,3);
	frightDown->SetLineColor(kOrange);
	frightDown->SetLineWidth(0);
	frightDown->SetParameters(bgFitDown->GetParameters());
	tofWithNuQEBinsDown->GetListOfFunctions()->Add(frightDown);
	gROOT->GetListOfFunctions()->Remove(frightDown);
	tofWithNuQEBinsDown->Draw();
	if (fitType=="exp")
	{
		fitOffsetDown = bgFitDown->GetParameter(0); fitTauDown = bgFitDown->GetParameter(1); fitBackgroundDown = bgFitDown->GetParameter(2);
		fitOffsetDownErr = bgFitDown->GetParError(0); fitTauDownErr = bgFitDown->GetParError(1); fitBackgroundDownErr = bgFitDown->GetParError(2);
	}
	if (fitType!="exp")
	{
		fitBackgroundDown = bgFitDown->GetParameter(0); fitLinearDown = bgFitDown->GetParameter(1); fitQuadraticDown = bgFitDown->GetParameter(2);
		fitBackgroundDownErr = bgFitDown->GetParError(0); fitLinearDownErr = bgFitDown->GetParError(1); fitQuadraticDownErr = bgFitDown->GetParError(2);
	}
	bgDown = new TH1F(bgDownTitle,"bgDown",tofBins,tofMin,tofMax);
	cout << "Number of Bins: " << tofWithNuQEBinsDown->GetSize()-2 << endl;
	for (int j=0; j<(tofWithNuQEBinsDown->GetSize()-2); j++)
	{
		xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
		if (fitType=="const") {bgDown->Fill(xpos,fitBackgroundDown);}
		if (fitType=="lin")   {bgDown->Fill(xpos,(fitBackgroundDown + fitLinearDown*xpos));}
		if (fitType=="quad")  {bgDown->Fill(xpos,(fitBackgroundDown + fitLinearDown*xpos + fitQuadraticDown*xpos*xpos));}
		if (fitType=="exp")  {bgDown->Fill(xpos,(exp(fitTauDown*xpos + fitOffsetDown) + fitBackgroundDown));}
	}

/*	if (!(kine=="0.5" && targ=="v" && forceBG))
	{
		for (int j=0; j<(tofWithNuQEBinsDown->GetSize()-2); j++)
		{
			xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
			if (fitType=="const") {bgDown->Fill(xpos,fitBackgroundDown);}
			if (fitType=="lin")   {bgDown->Fill(xpos,(fitBackgroundDown + fitLinearDown*xpos));}
			if (fitType=="quad")  {bgDown->Fill(xpos,(fitBackgroundDown + fitLinearDown*xpos + fitQuadraticDown*xpos*xpos));}
			if (fitType=="exp")  {bgDown->Fill(xpos,(exp(fitTauDown*xpos + fitOffsetDown) + fitBackgroundDown));}
		}
	}
	if ((kine=="0.5" && targ=="v" && forceBG))
	{
		if (includeVetos)
		{
			for (int j=0; j<((625-tofMin)/((tofMax-tofMin)/tofBins)); j++)
			{
				xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
//				bgDown->Fill(xpos,142524.412); // <--- 3He Data
				bgDown->Fill(xpos,9514.96831); // <--- H2 Data
			}
			for (int j=((625-tofMin)/((tofMax-tofMin)/tofBins)); j<((740-tofMin)/((tofMax-tofMin)/tofBins)); j++)
			{
				xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
//				bgDown->Fill(xpos,(183463.26 - 65.5*xpos)); // <--- 3He Data
				bgDown->Fill(xpos,(47.005*xpos - 19862.902)); // <--- H2 Data
			}
			for (int j=((740-tofMin)/((tofMax-tofMin)/tofBins)); j<(tofWithNuQEBinsDown->GetSize()-2); j++)
			{
				xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
//				bgDown->Fill(xpos,134991.664); // <--- 3He Data
				bgDown->Fill(xpos,14920.4964); // <--- H2 Data
			}
		}
		if (!includeVetos)
		{
			for (int j=0; j<((625-tofMin)/((tofMax-tofMin)/tofBins)); j++)
			{
				xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
				bgDown->Fill(xpos,152556.867);
			}
			for (int j=((625-tofMin)/((tofMax-tofMin)/tofBins)); j<((740-tofMin)/((tofMax-tofMin)/tofBins)); j++)
			{
				xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
				bgDown->Fill(xpos,(164649.345 - 19.348*xpos));
			}
			for (int j=((740-tofMin)/((tofMax-tofMin)/tofBins)); j<(tofWithNuQEBinsDown->GetSize()-2); j++)
			{
				xpos = j*((tofMax-tofMin)/tofBins)+tofMin;
				bgDown->Fill(xpos,150331.851);
			}
		}
	}
*/

	bgDown->SetLineColor(kBlue);
	bgDown->SetStats(kFALSE);
	bgDown->Draw("same");
	fitResultsDown = new TPaveText(0.6,0.25,0.9,0.55,"NDC");
	if (fitType=="exp")
	{
		OffsetStrDown = "Offset = "; OffsetStrDown += fitOffsetDown; OffsetStrDown += " ± "; OffsetStrDown += fitOffsetDownErr;
		TauStrDown = "Tau = "; TauStrDown += fitTauDown; TauStrDown += " ± "; TauStrDown += fitTauDownErr;
	}
	BackgroundStrDown = "BackgroundConst = "; BackgroundStrDown += fitBackgroundDown; BackgroundStrDown += " ± "; BackgroundStrDown += fitBackgroundDownErr;
	if (fitType!="exp"){
		LinearStrDown = "Linear = "; LinearStrDown += fitLinearDown; LinearStrDown += " ± "; LinearStrDown += fitLinearDownErr;
		QuadraticStrDown = "Quadratic = "; QuadraticStrDown += fitQuadraticDown; QuadraticStrDown += " ± "; QuadraticStrDown += fitQuadraticDownErr;
		if (fitType=="lin") {QuadraticStrDown = "";}
	}
	Down4 = fitResultsDown->AddText(BackgroundStrDown);
	if (fitType=="exp")
	{
		Down5 = fitResultsDown->AddText(TauStrDown);
		Down6 = fitResultsDown->AddText(OffsetStrDown);
	}
	if (fitType!="exp")
	{
		Down5 = fitResultsDown->AddText(LinearStrDown);
		Down6 = fitResultsDown->AddText(QuadraticStrDown);
	}
	Down7 = fitResultsDown->AddText(fitTypeStr);
	tofWithNuQEBinsDown->Draw("same");
	theFitDownStr = fitBackgroundDown;
	if (fitType=="exp")
	{
		theFitDownStr += "+exp("; theFitDownStr += fitTauDown; theFitDownStr += "*x+"; theFitDownStr += fitOffsetDown; theFitDownStr += ")";
	}
	if (fitType=="lin")
	{
		theFitDownStr += "+x*"; theFitDownStr += fitLinearDown;
	}
	if (fitType=="quad")
	{
		theFitDownStr += "+x*"; theFitDownStr += fitLinearDown; theFitDownStr += "+x*x*"; theFitDownStr += fitQuadraticDown;
	}
	theFitDownTitle = "theFitDown_bin_"; theFitDownTitle += i;
//	fitResultsDown->SetStats(kFALSE);
	fitResultsDown->Draw("same");
	goodtofpad4->Update();


cout << "1" << endl;
/*	TString tofQEdownTitle = outputPlotsHere;
	tofQEdownTitle += "qe_tof_and_nu_down";
	tofQEdownTitle += "_for_Runs_";
	tofQEdownTitle += HeRunNumber;
	tofQEdownTitle += "-";
	tofQEdownTitle += endHeRunNumber;
	if (includeVetos) {tofQEdownTitle += "_with_vetos";}
//	tofQEdownTitle += ".eps";
	tofQEdownTitle += ".pdf";
	goodtofpad4->Print(tofQEdownTitle);
*/
cout << "2" << endl;
	fitResultsDown = NULL;
	Down1 = NULL;
	Down2 = NULL;
	Down3 = NULL;
	Down4 = NULL;
	Down5 = NULL;
	Down6 = NULL;

cout << "3" << endl;
	goodtofpad6->cd();
cout << "4" << endl;
	h3Down = new TH1F(h3Downtitle,titleToFdown,tofBins,tofMin,tofMax);
	h3Down->Add(tofWithNuQEBinsDown);
	h3Down->Add(bgDown,-1);
	h3Down->SetLineColor(kRed);
	goodEventsDownPlot = "goodEventsDown_QE";
	goodEventsDownTitle = "ToF Spin Down Signal Events for QE Peak";
	goodEventsDown = new TH1F(goodEventsDownPlot,goodEventsDownTitle,tofBins,tofMin,tofMax);
	cout << "sigDownMin: " << sigDownMin << ", sigDownMax: " << sigDownMax << endl;
	cout << "ToF Bin Size: " << binSize << ", sigMinBin = " << sigMinBin << ", sigMaxBin = " << sigMaxBin << endl;
	for (int k=sigMinBin; k<=sigMaxBin; k++)
	{
		thisBinContent = 0;
		thisBinContent = h3Down->GetBinContent(k);
		if (theSmallestBin>thisBinContent) {theSmallestBin = thisBinContent;}
		if (thisBinContent < 0) {thisBinContent = 0;}
		if (theBiggestBin<thisBinContent) {theBiggestBin = thisBinContent;}
		totalGoodEventsDown = totalGoodEventsDown + thisBinContent;
		goodEventsDown->Fill((k-1)*binSize + tofMin,thisBinContent);
	}
	goodEventsDown->SetFillColor(kViolet);
	goodEventsDown->SetLineColor(kViolet);
//	h3Down->SetMaximum(theBiggestBin + theBiggestBin/10);
//	if (kine=="0.1") 
//	{
//		if (includeVetos) {goodEventsDown->SetMaximum(200);}
//		else {goodEventsDown->SetMaximum(4500);}
//	}

//	if (kine=="0.5") {goodEventsDown->SetMaximum(105000);}
//	if (kine=="1.0") {goodEventsDown->SetMaximum(800000);}

//	goodEventsDown->SetMinimum(theSmallestBin + theSmallestBin/10);
	goodEventsDown->SetMinimum(0);
	goodEventsDown->SetStats(kFALSE);
	goodEventsDown->Draw();
	h3Down->SetStats(kFALSE);
	h3Down->Draw("same");
	goodDownInfo = new TPaveText(0.6,0.11,0.895,0.2,"NDC");
	goodEventStr = "# of Good Down Events: ";
	goodEventStr += totalGoodEventsDown;
	goodDown = goodDownInfo->AddText(goodEventStr);
	goodDownInfo->Draw("same");
	goodtofpad6->Update();

	TString tofQEdownBgSubTitle = outputPlotsHere;
	tofQEdownBgSubTitle += "qe_tof_and_nu_down_bgsub";
	tofQEdownBgSubTitle += "_for_Runs_";
	tofQEdownBgSubTitle += HeRunNumber;
	tofQEdownBgSubTitle += "-";
	tofQEdownBgSubTitle += endHeRunNumber;
	if (includeVetos) {tofQEdownBgSubTitle += "_with_vetos";}
//	tofQEdownBgSubTitle += ".eps";
	tofQEdownBgSubTitle += ".svg";
	goodtofpad6->Print(tofQEdownBgSubTitle);

	goodtofpad8->cd();
//	TH1F *eventQEDistDown = new TH1F("eventQEDistDown","# bins v. # events/bin for spin down",50,-4000,4000);
	TH1F *eventQEDistDown = new TH1F("eventQEDistDown","# bins v. # events/bin for spin down",50,-200,200);
	for (int k=0; k<(h3Down->GetSize()-2); k++)
	{
		eventsup = h3Down->GetBinContent(k);
//		if ((h3Down->GetBinCenter(k))<sigMin || (h3Down->GetBinCenter(k))>sigMax) {eventQEDistDown->Fill(eventsup);}
		if ((h3Down->GetBinCenter(k))<sigMin) {eventQEDistDown->Fill(eventsup);}
	}
	eventQEDistDown->SetStats(kFALSE);
	eventQEDistDown->Draw();
	goodtofpad8->Update();
	TString tofQEdownBgSubErrorTitle = outputPlotsHere;
	tofQEdownBgSubErrorTitle += "qe_tof_and_nu_down_bgsub_err";
	tofQEdownBgSubErrorTitle += "_for_Runs_";
	tofQEdownBgSubErrorTitle += HeRunNumber;
	tofQEdownBgSubErrorTitle += "-";
	tofQEdownBgSubErrorTitle += endHeRunNumber;
	if (includeVetos) {tofQEdownBgSubErrorTitle += "_with_vetos";}
//	tofQEdownBgSubErrorTitle += ".eps";
	tofQEdownBgSubErrorTitle += ".svg";
	goodtofpad8->Print(tofQEdownBgSubErrorTitle);


	TF1 *upfit = new TF1("upfit","gaus",-200,200);
	eventQEDistDown->Fit(upfit,"R","same");
	cout << "bgDownErr[" << i << "] = " << bgDownErr[i] << endl;
	goodtofpad8->Update();
	h3Down = NULL;



	TString asymTitle = "Target Asymmetry for Runs ";
	asymTitle += HeRunNumber;
	asymTitle += "-";
	asymTitle += endHeRunNumber;
	if (includeTgtPol || includeBeamPol || includeVetos) {asymTitle += " with ";}
	if (includeTgtPol) {asymTitle += "Tgt Pol ";}
	if (includeBeamPol) {asymTitle += "Beam Pol ";}
	if (includeVetos) {asymTitle += "Vetos ";}
	TCanvas *asymCanvas = new TCanvas("asymCanvas",asymTitle,1400,730); //x,y
	asymCanvas->cd();
	asymCanvas->SetGrid();
	Double_t x[nuBins], y[nuBins], errorx[nuBins], errory[nuBins];
	Double_t xbasic[nuBins], errorxbasic[nuBins];
	Double_t ybasic[nuBins], errorybasic[nuBins];
	Double_t statErrory[nuBins], statErrorybasic[nuBins];
	double minError;
	double maxError;
	double posStuff;
	double negStuff;
	double UpEvents;
	double DownEvents;
	if ((targ == "v") || (targ == "l") || (targ == "t") || (targ == "c") || (targ == "h") || (targ == "vh") || (targ == "lth") ) { check = true;}
	if (targ == "v") 
	{
		asymOutFile << "Dataset:	Vertical 3He, Q2=" << kine << endl; cout << "Dataset:	Vertical 3He, Q2=" << kine << endl;
		asymOut2File << "Dataset:	Vertical 3He, Q2=" << kine << endl; cout << "Dataset:	Vertical 3He, Q2=" << kine << endl;
	}
	if (targ == "l") 
	{
		asymOutFile << "Dataset:	Longitudinal 3He, Q2=" << kine << endl; cout << "Dataset:	Longitudinal 3He, Q2=" << kine << endl;
		asymOut2File << "Dataset:	Longitudinal 3He, Q2=" << kine << endl; cout << "Dataset:	Longitudinal 3He, Q2=" << kine << endl;
	}
	if (targ == "t") 
	{
		asymOutFile << "Dataset:	Transverse 3He, Q2=" << kine << endl; cout << "Dataset: Transverse 3He, Q2=" << kine << endl;
		asymOut2File << "Dataset:	Transverse 3He, Q2=" << kine << endl; cout << "Dataset: Transverse 3He, Q2=" << kine << endl;
	}
	if (targ == "c") 
	{
		asymOutFile << "Dataset:	Carbon, Q2=" << kine << endl; cout << "Dataset: Carbon, Q2=" << kine << endl;
		asymOut2File << "Dataset:	Carbon, Q2=" << kine << endl; cout << "Dataset: Carbon, Q2=" << kine << endl;
	}
	if ((targ == "h") || (targ=="vh") || (targ=="lth")) 
	{
		asymOutFile << "Dataset:	Hydrogen, Q2=" << kine << endl; cout << "Dataset:	Hydrogen, Q2=" << kine << endl;
		asymOut2File << "Dataset:	Hydrogen, Q2=" << kine << endl; cout << "Dataset:	Hydrogen, Q2=" << kine << endl;
	}
	asymOutFile << "Runs:	" << HeRunNumber << "-" << endHeRunNumber << endl;
	asymOut2File << "Runs:	" << HeRunNumber << "-" << endHeRunNumber << endl;
	cout << "Runs:	" << HeRunNumber << "-" << endHeRunNumber << endl;
	asymOutFile << "Omega	Raw Asym	Stat. Error	# HePos Events	HePos Charge	PosHe LT	 # Neg Events	HeNeg Charge	NegHe LT" << endl;
	asymOut2File << "Omega	Raw Asym	Stat. Error	He+Evts	He+ Charge	He+ LT	He-Evts	He- Charge	He- LT	PhysAsym	NewErr";
	if (includeTgtPol) {asymOut2File << "	TgtPolDil";}
	if (includeBeamPol) {asymOut2File << "	BeamPolDil";}
	asymOut2File << endl;
	cout << "xBj	Raw Asym	Stat. Error	# HePos Events	HePos Charge	PosHe LT	 # Neg Events	HeNeg Charge	NegHe LT" << endl;
	for (int i=0; i<nuBins; i++)
	{ 
		UpEvents = goodUpEvents[i+1];
		DownEvents = goodDownEvents[i+1];
		x[i] = nuMin + i*((nuMax-nuMin)/nuBins) + ((nuMax-nuMin)/nuBins)/2;
		xbasic[i] = x[i] - ((nuMax-nuMin)/nuBins)/8;
		posStuff = UpEvents/(HeChargeScaleUp * HelivetimeUp + 1e-15);
		negStuff = DownEvents/(HeChargeScaleDown * HelivetimeDown + 1e-15);
		y[i] = ((posStuff - negStuff)/(posStuff + negStuff + 1e-15));
		ybasic[i] = ((posStuff - negStuff)/(posStuff + negStuff + 1e-15));
		errorybasic[i] = 2*(DownEvents*sqrt(UpEvents) + UpEvents*sqrt(DownEvents))/((HeChargeScaleUp*HelivetimeUp)*(HeChargeScaleDown*HelivetimeDown)*pow((UpEvents/(HeChargeScaleUp*HelivetimeUp + 1e-25)) + (DownEvents/(HeChargeScaleDown*HelivetimeDown + 1e-25)),2) + 1e-15);
		errory[i] = errorybasic[i];
		statErrorybasic[i] = 2*(DownEvents*(sqrt(UpEvents)+bgUpErr[i+1]) + UpEvents*(sqrt(DownEvents)+bgDownErr[i+1]))/((HeChargeScaleUp*HelivetimeUp)*(HeChargeScaleDown*HelivetimeDown)*pow((UpEvents/(HeChargeScaleUp*HelivetimeUp + 1e-25)) + (DownEvents/(HeChargeScaleDown*HelivetimeDown + 1e-25)),2) + 1e-15);
//		statErrorybasic[i] = 2*(DownEvents*(sqrt(UpEvents)+100) + UpEvents*(sqrt(DownEvents)+100))/((HeChargeScaleUp*HelivetimeUp)*(HeChargeScaleDown*HelivetimeDown)*pow((UpEvents/(HeChargeScaleUp*HelivetimeUp + 1e-25)) + (DownEvents/(HeChargeScaleDown*HelivetimeDown + 1e-25)),2) + 1e-15);
		statErrory[i] = statErrorybasic[i];
		if (includeTgtPol) 
		{
			y[i] = y[i]*tgtPolDil;
			errory[i] = errory[i]*tgtPolDil;
			statErrory[i] = statErrory[i]*tgtPolDil;
		}
		if (includeBeamPol) 
		{
			y[i] = y[i]*beamPolDil;
			errory[i] = errory[i]*beamPolDil;
			statErrory[i] = statErrory[i]*beamPolDil;
		}
		if ((UpEvents == 0) || (DownEvents == 0)) { errory[i] = 1;}
		if ((UpEvents == 0) || (DownEvents == 0)) { y[i] = NULL;}
		if (i==0)
		{
			minError = 0;
			maxError = 0;
//			minError = y[i] - 2*errory[i];
//			maxError = y[i] + 2*errory[i];
		}
/*		if ((y[i] - 2*errory[i]) < minError) { minError = y[i] - 2*errory[i];}
		if ((y[i] + 2*errory[i]) > maxError) { maxError = y[i] + 2*errory[i];}
*/		if (((y[i] - 2*errory[i]) < minError) && errory[i]<1) { minError = y[i] - 2*errory[i];}
//		if (((y[i] + 2*errory[i]) > maxError) && errory[i]<1) { maxError = y[i] + 2*errory[i] + 0.1;}
		if (((y[i] + 2*errory[i]) > maxError) && errory[i]<1) { maxError = y[i] + 2*errory[i];}

		errorx[i] = ((nuMax - nuMin)/nuBins)/2;
		errorxbasic[i] = 0;
		asymOutFile << x[i] << "	 " << ybasic[i] << "	" << errorybasic[i] << "	" << UpEvents << "	" << HeChargeScaleUp << "	" << HelivetimeUp << "	" << DownEvents << "	" << HeChargeScaleDown << "	" << HelivetimeDown << endl;
		asymOut2File << x[i] << "	 " << ybasic[i] << "	" << errorybasic[i] << "	" << UpEvents << "	" << HeChargeScaleUp << "	" << HelivetimeUp << "	" << DownEvents << "	" << HeChargeScaleDown << "	" << HelivetimeDown << "	" << y[i] << "	" << errory[i];
		if (includeTgtPol) {asymOut2File << "	" << tgtPolDil;}
		if (includeBeamPol) {asymOut2File << "	" << beamPolDil;}	
		asymOut2File << endl;
		cout << x[i] << "	" << ybasic[i] << "	" << errorybasic[i] << "	" << UpEvents << "	" << HeChargeScaleUp << "	" << HelivetimeUp << "	" << DownEvents << "	" << HeChargeScaleDown << "	" << HelivetimeDown << endl;
	}
	cout << "x error: " << ((nuMax - nuMin)/nuBins)/2 << ", nuMin: " << nuMin << ", nuMax: " << nuMax << ", nuBins: " << nuBins << endl;
	cout << "minError = " << minError << ", maxError = " << maxError << endl;
	asymGraph = new TGraphErrors(nuBins, x, y, errorx, errory);
	asymGraph->SetMarkerStyle(21);
//	asymGraph->SetMarkerColor(4);
	asymGraph->SetMarkerColor(kBlue);
//	asymGraph->SetLineColor(4);
	asymGraph->SetLineColor(kBlue);
	asymGraph->SetTitle(asymTitle);
	asymBasicGraph = new TGraphErrors(nuBins, xbasic, ybasic, errorxbasic, errorybasic);
	asymStatErrGraph = new TGraphErrors(nuBins, x, y, errorx, statErrory);
	asymStatErrBasicGraph = new TGraphErrors(nuBins, xbasic, ybasic, errorxbasic, statErrorybasic);
//	asymBasicGraph->SetMarkerStyle(22);
	asymBasicGraph->SetMarkerStyle(2);
	asymBasicGraph->SetMarkerColor(6);
	asymBasicGraph->SetLineColor(kMagenta);
	asymBasicGraph->SetTitle(asymTitle);

	asymStatErrGraph->SetMarkerStyle(21);
	asymStatErrGraph->SetMarkerColor(kBlue);
	asymStatErrGraph->SetLineColor(kBlue+1);
	asymStatErrGraph->SetTitle(asymTitle);
	asymStatErrBasicGraph->SetMarkerStyle(2);
	asymStatErrBasicGraph->SetMarkerColor(6);
	asymStatErrBasicGraph->SetLineColor(kMagenta+1);
	asymStatErrBasicGraph->SetTitle(asymTitle);

	asymTestHist = new TH2F("asymTestHist",asymTitle,nuBins,nuMin,nuMax,100,minError,maxError);
	asymTestHist->SetStats(kFALSE);
	asymTestHist->Draw();
	cout << "Fit min = " << nuMin << "; Fit max = " << nuMax << endl;
	TF1 *fitAsymGraph = new TF1("fitAsymGraph", "[0]", nuMin, nuMax);
	asymStatErrGraph->Draw("P");
	asymStatErrBasicGraph->Draw("P");
	asymGraph->Draw("P");
	asymBasicGraph->Draw("P");
	fitAsymGraph->SetLineColor(kBlue);
	asymGraph->Fit("fitAsymGraph","R");
	asymCanvas->Update();

	asymOutFile.close();
	asymOut2File.close();

	TString asymOutTitle = outputPlotsHere;
	asymOutTitle += "asym_plots_for_Runs_";
	asymOutTitle += HeRunNumber;
	asymOutTitle += "-";
	asymOutTitle += endHeRunNumber;
	if (includeVetos) {asymOutTitle += "_with_vetos";}
	asymOutTitle += ".png";
	asymCanvas->Print(asymOutTitle);

/*	for (int i=0; i<11; i++)
	{
		cout << "bgUpErr[" << i << "] = " << bgUpErr[i] << endl;
		cout << "bgDownErr[" << i << "] = " << bgDownErr[i] << endl;
	}
*/
	cout << "^^^^^^^^^^^^^^^^^^^^^^^ hand_class_draw_tof_nu.h ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
}
