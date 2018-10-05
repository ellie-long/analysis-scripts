



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

	ofstream asymOutFile;
	asymOutFile.open(asymOutFileName);

	bool check = false;;

	TString target;
	if ((targ == "v") || (targ == "l") || (targ == "t") || (targ == "c") || (targ == "h")) { check = true;}
	if (targ == "v") {target="Vertical 3He";}
	if (targ == "l") {target="Longitudinal 3He";}
	if (targ == "t") {target="Transverse 3He";}
	if (targ == "c") {target="Carbon";}
	if (targ == "h") {target="Hydrogen";}

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
	if (kine="0.1")
	{
		if (targ=="v")
		{
			cout << "Q2=0.1, Vertical 3He" << endl;
			sigUpMin = 600;
			sigUpMax = 740;
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
			fitType = "exp";
//                      fitType = "quad";
//                      fitType = "lin";
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
	int thisBinContent; int totalGoodEventsUp; int totalGoodEventsDown; int theBiggestBin; int theSmallestBin;
	TH1F *goodEventsUp; TH1F *goodEventsDown;
	TString goodEventsUpTitle; TString goodEventsUpPlot; TString goodEventStr;
	nuAllCutsTotal->SetTitle(titlenuAllCuts);

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
		tofpad1  =  new  TPad("tofpad1","tofpad1",0.0000,0.6666,0.5000,1.0000,0,0,0);
		tofpad2  =  new  TPad("tofpad2","tofpad2",0.5000,0.6666,1.0000,1.0000,0,0,0);
		tofpad3  =  new  TPad("tofpad3","tofpad3",0.0000,0.3333,0.5000,0.6666,0,0,0);
		tofpad4  =  new  TPad("tofpad4","tofpad4",0.5000,0.3333,1.0000,0.6666,0,0,0);
		tofpad5  =  new  TPad("tofpad5","tofpad5",0.0000,0.0000,0.5000,0.3333,0,0,0);
		tofpad6  =  new  TPad("tofpad6","tofpad6",0.5000,0.0000,1.0000,0.3333,0,0,0);
		tofpad1->Draw();tofpad2->Draw(); tofpad3->Draw(); tofpad4->Draw(); tofpad5->Draw(); tofpad6->Draw();

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
/*		ToFgoodEventTotal->SetFillColor(kWhite);
		ToFgoodEventTotal->SetMinimum(0);
		ToFgoodEventTotal->Draw();
		ToFgoodEvent->SetFillColor(kViolet);
		ToFgoodEvent->SetMinimum(0);
		ToFgoodEvent->Draw("same");
*/		ToFgoodEvent->SetFillColor(kWhite);
		ToFgoodEvent->Draw();
		tofpad2->Update();

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
		sigMin = sigUpMin;
		sigMax = sigUpMax;
		sigMinBin = (sigMin - tofMin)/binSize;
		sigMaxBin = (sigMax - tofMin)/binSize;
		h3Uptitle = "h3Up_bin_";
		h3Uptitle += i;
		bgUpTitle = "bgFitUp_bin";
		bgUpTitle += i;
//		h3Up = new TH1F(h3Uptitle,titleToFup,tofBins,tofMin,tofMax);
		if (fitType=="const"){bgFitUp = new TF1(bgUpTitle,"[0]",bgUpMin,bgUpMax);}
		if (fitType=="lin"){bgFitUp = new TF1(bgUpTitle,"[0]+[1]*x",bgUpMin,bgUpMax);}
		if (fitType=="quad"){bgFitUp = new TF1(bgUpTitle,"[0]+[1]*x+[2]*x*x",bgUpMin,bgUpMax);}
		if (fitType=="exp"){bgFitUp = new TF1(bgUpTitle,"exp([1]*x+[0])+[2]",bgUpMin,bgUpMax);}
		bgFitUp = new TF1(bgUpTitle,fline,bgUpMin,sigUpMin,3);
		bgFitUp->SetLineColor(kOrange);
		if (fitType=="exp")
		{
			bgFitUp->SetParameter(0,1);
			bgFitUp->SetParameter(1,1/1600);
			bgFitUp->SetParameter(2,1);
			bgFitUp->SetParName(0,"Offset");
			bgFitUp->SetParName(1,"Tau");
			bgFitUp->SetParName(2,"Background");
		}
		if (fitType!="exp")
		{
			bgFitUp->SetParameter(0,1);
			bgFitUp->SetParameter(1,1);
			bgFitUp->SetParameter(2,1);
			bgFitUp->SetParName(0,"Background");
			bgFitUp->SetParName(1,"Linear");
			bgFitUp->SetParName(2,"Quadratic");
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
			fitOffsetUp = bgFitUp->GetParameter(0);
			fitTauUp = bgFitUp->GetParameter(1);
			fitBackgroundUp = bgFitUp->GetParameter(2);
			fitOffsetUpErr = bgFitUp->GetParError(0);
			fitTauUpErr = bgFitUp->GetParError(1);
			fitBackgroundUpErr = bgFitUp->GetParError(2);
		}
		if (fitType!="exp")
		{
			fitBackgroundUp = bgFitUp->GetParameter(0);
			fitLinearUp = bgFitUp->GetParameter(1);
			fitQuadraticUp = bgFitUp->GetParameter(2);
			fitBackgroundUpErr = bgFitUp->GetParError(0);
			fitLinearUpErr = bgFitUp->GetParError(1);
			fitQuadraticUpErr = bgFitUp->GetParError(2);
		}

		bgUp = new TH1F(bgUpTitle,"bgUp",tofBins,tofMin,tofMax);
		cout << "Number of Bins: " << ToFup->GetSize()-2 << endl;;
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
/*		WeightStrUp = "Weight = ";
		WeightStrUp += fitWeightUp;
		WeightStrUp += " ± ";
		WeightStrUp += fitWeightUpErr;
		MeanStrUp = "Mean = ";
		MeanStrUp += fitMeanUp;
		MeanStrUp += " ± ";
		MeanStrUp += fitMeanUpErr;
		SigmaStrUp = "Sigma = ";
		SigmaStrUp += sqrt(fitSigmaUp*fitSigmaUp);
		SigmaStrUp += " ± ";
		SigmaStrUp += fitSigmaUpErr;
*/
		if (fitType=="exp")
		{
			OffsetStrUp = "Offset = ";
			OffsetStrUp += fitOffsetUp;
			OffsetStrUp += " ± ";
			OffsetStrUp += fitOffsetUpErr;
			TauStrUp = "Tau = ";
			TauStrUp += fitTauUp;
			TauStrUp += " ± ";
			TauStrUp += fitTauUpErr;
		}
		BackgroundStrUp = "BackgroundConst = ";
		BackgroundStrUp += fitBackgroundUp;
		BackgroundStrUp += " ± ";
		BackgroundStrUp += fitBackgroundUpErr;
		if (fitType!="exp"){
			LinearStrUp = "Linear = ";
			LinearStrUp += fitLinearUp;
			LinearStrUp += " ± ";
			LinearStrUp += fitLinearUpErr;
			QuadraticStrUp = "Quadratic = ";
			QuadraticStrUp += fitQuadraticUp;
			QuadraticStrUp += " ± ";
			QuadraticStrUp += fitQuadraticUpErr;
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
			theFitUpStr += "+exp(";
			theFitUpStr += fitTauUp;
			theFitUpStr += "*x+";
			theFitUpStr += fitOffsetUp;
			theFitUpStr += ")";
		}
		if (fitType=="lin")
		{
			theFitUpStr += "+x*";
			theFitUpStr += fitLinearUp;
		}
		if (fitType=="quad")
		{
			theFitUpStr += "+x*";
			theFitUpStr += fitLinearUp;
			theFitUpStr += "+x*x*";
			theFitUpStr += fitQuadraticUp;
		}
		theFitUpTitle = "theFitUp_bin_";
		theFitUpTitle += i;
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
		goodEventsUp->SetFillColor(kViolet);
		h3Up->SetMaximum(theBiggestBin + theBiggestBin/10);
		goodEventsUp->SetMinimum(theSmallestBin + theSmallestBin/10);
		goodEventsUp->Draw();
		h3Up->Draw("same");
		goodUpInfo = new TPaveText(0.6,0.11,0.895,0.2,"NDC");
		goodEventStr = "# of Good Up Events: ";
		goodEventStr += totalGoodEventsUp;
		goodUp = goodUpInfo->AddText(goodEventStr);
		goodUpInfo->Draw("same");
		tofpad5->Update();
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
		tofpad4->Update();

		ToFnuOutTitle = outputPlotsHere;
		ToFnuOutTitle += "tof_and_nu_bin_";
		ToFnuOutTitle += i;
		if (i==0) {ToFnuOutTitle = "tof_and_nu_total";}
		ToFnuOutTitle += "_plots_for_Runs_";
		ToFnuOutTitle += HeRunNumber;
		ToFnuOutTitle += "-";
		ToFnuOutTitle += endHeRunNumber;
		if (includeVetos) {ToFnuOutTitle += "_with_vetos";}
		ToFnuOutTitle += ".png";
		ToFCanvas->Print(ToFnuOutTitle);
	}















/*
        TString titleToFbasic = "ToFbasic for Runs ";
	titleToFbasic += HeRunNumber;
	titleToFbasic += "-";
	titleToFbasic += endHeRunNumber;
        if (includeVetos) {titleToFbasic += " with vetos";}
        else {titleToFbasic += " without vetos";}
        TString plotToFbasic = "ToFbasic";
        TH1F *ToFbasic = (TH1F*)fileHe.Get(plotToFbasic);
	ToFbasic->SetTitle(titleToFbasic);
        TString titleToFgoodEvent = "ToFgoodEvent";
        TString plotToFgoodEvent = "ToFgoodEvent";
        TH1F *ToFgoodEvent = (TH1F*)fileHe.Get(plotToFgoodEvent);
        TString titleToFcut = "ToFcut";
        TString plotToFcut = "ToFcut";
        TH1F *ToFcut = (TH1F*)fileHe.Get(plotToFcut);

        TString titlenuAllCuts = "Target Spin vs. nu for Runs ";
	titlenuAllCuts += HeRunNumber;
	titlenuAllCuts += "-";
	titlenuAllCuts += endHeRunNumber;
        if (includeVetos) {titlenuAllCuts += " with vetos";}
        else {titlenuAllCuts += " without vetos";}
        TString plotnuAllCuts = "nuAllCuts";
        TH1F *nuAllCuts = (TH1F*)fileHe.Get(plotnuAllCuts);
        TString titlenuUpAllCuts = "Target Spin Up vs. nu";
        if (includeVetos) {titlenuUpAllCuts += " with vetos";}
        else {titlenuUpAllCuts += " without vetos";}
        TString plotnuUpAllCuts = "nuUpAllCuts";
        TH1F *nuUpAllCuts = (TH1F*)fileHe.Get(plotnuUpAllCuts);
        TString titlenuDownAllCuts = "Target Spin Down vs. nu";
        if (includeVetos) {titlenuDownAllCuts += " with vetos";}
        else {titlenuDownAllCuts += " without vetos";}
        TString plotnuDownAllCuts = "nuDownAllCuts";
        TH1F *nuDownAllCuts = (TH1F*)fileHe.Get(plotnuDownAllCuts);

	nuAllCuts->SetTitle(titlenuAllCuts);
	nuUpAllCuts->SetTitle(titlenuUpAllCuts);
	nuDownAllCuts->SetTitle(titlenuDownAllCuts);


	// The section below plots the ToF plots
	// **********************************************************************************************
	// Defines Canvas
	TCanvas *ToFCanvas = new TCanvas("ToFCanvas","ToF",1360,768); //x,y
	tofpad1  =  new  TPad("tofpad1","tofpad1",0.0000,0.5000,0.5000,1.0000,0,0,0);
	tofpad2  =  new  TPad("tofpad2","tofpad2",0.5000,0.5000,1.0000,1.0000,0,0,0);
	tofpad3  =  new  TPad("tofpad3","tofpad3",0.0000,0.0000,0.5000,0.5000,0,0,0);
	tofpad4  =  new  TPad("tofpad4","tofpad4",0.5000,0.0000,1.0000,0.5000,0,0,0);
	tofpad1->Draw();tofpad2->Draw(); tofpad3->Draw();tofpad4->Draw();

	// Everything below here makes graphs for each section of the canvas
	tofpad1->cd();
	ToFbasic->Draw();
	tofpad1->Update();

	tofpad2->cd();
	ToFgoodEvent->Draw();
	ToFcut->SetFillColor(kViolet);
	ToFcut->Draw("same");
	tofpad2->Update();

	tofpad3->cd();
	ToFup->Draw();
	tofpad3->Update();

	tofpad4->cd();
	ToFdown->Draw();
	tofpad4->Update();

	TString tofOutTitle = outputPlotsHere;
	tofOutTitle += "tof_cut_plots_for_Runs_";
	tofOutTitle += HeRunNumber;
	tofOutTitle += "-";
	tofOutTitle += endHeRunNumber;
	if (includeVetos) {tofOutTitle += "_with_vetos";}
	tofOutTitle += ".png";
	ToFCanvas->Print(tofOutTitle);


	// The section below plots the nu plots
	// **********************************************************************************************
	// Defines Canvas
	TCanvas *nuCanvas = new TCanvas("nuCanvas","nu",1360,768); //x,y
	nupad1  =  new  TPad("nupad1","nupad1",0.0000,0.0000,0.3333,1.0000,0,0,0);
	nupad2  =  new  TPad("nupad2","nupad2",0.3333,0.0000,0.6666,1.0000,0,0,0);
	nupad3  =  new  TPad("nupad2","nupad2",0.6666,0.0000,1.0000,1.0000,0,0,0);
	nupad1->Draw();nupad2->Draw();nupad3->Draw();

	// Everything below here makes graphs for each section of the canvas
	nupad1->cd();
	nuAllCuts->Draw();
	nupad1->Update();

	nupad2->cd();
	nuUpAllCuts->Draw();
	nupad2->Update();

	nupad3->cd();
	nuDownAllCuts->Draw();
	nupad3->Update();

	TString nuOutTitle = outputPlotsHere;
	nuOutTitle += "nu_cut_plots_for_Runs_";
	nuOutTitle += HeRunNumber;
	nuOutTitle += "-";
	nuOutTitle += endHeRunNumber;
	if (includeVetos) {nuOutTitle += "_with_vetos";}
	nuOutTitle += ".png";
	nuCanvas->Print(nuOutTitle);

	TString asymTitle = "Target Asymmetry for Runs ";
	asymTitle += HeRunNumber;
	asymTitle += "-";
	asymTitle += endHeRunNumber;
	TCanvas *asymCanvas = new TCanvas("asymCanvas",asymTitle,1400,730); //x,y
	asymCanvas->cd();
	asymCanvas->SetGrid();
	Double_t x[nuBins], y[nuBins], errorx[nuBins], errory[nuBins];
	double minError;
	double maxError;
	double posStuff;
	double negStuff;
	double UpEvents;
	double DownEvents;
	if ((targ == "v") || (targ == "l") || (targ == "t") || (targ == "c") || (targ == "h")) { check = true;}
	if (targ == "v") {asymOutFile << "Dataset:	Vertical 3He, Q2=" << kine << endl; cout << "Dataset:	Vertical 3He, Q2=" << kine << endl;}
	if (targ == "l") {asymOutFile << "Dataset:	Longitudinal 3He, Q2=" << kine << endl; cout << "Dataset:	Longitudinal 3He, Q2=" << kine << endl;}
	if (targ == "t") {asymOutFile << "Dataset:	Transverse 3He, Q2=" << kine << endl; cout << "Dataset: Transverse 3He, Q2=" << kine << endl;}
	if (targ == "c") {asymOutFile << "Dataset:	Carbon, Q2=" << kine << endl; cout << "Dataset: Carbon, Q2=" << kine << endl;}
	if (targ == "h") {asymOutFile << "Dataset:	Hydrogen, Q2=" << kine << endl; cout << "Dataset:	Hydrogen, Q2=" << kine << endl;}
	asymOutFile << "Runs:	" << HeRunNumber << "-" << endHeRunNumber << endl;
	cout << "Runs:	" << HeRunNumber << "-" << endHeRunNumber << endl;
	asymOutFile << "Omega	Asymmetry	Stat. Error	# HePos Events	HePos Charge	PosHe LT	 # Neg Events	HeNeg Charge	NegHe LT" << endl;
	cout << "xBj	Asymmetry	Stat. Error	# HePos Events	HePos Charge	PosHe LT	 # Neg Events	HeNeg Charge	NegHe LT" << endl;
	for (int i=0; i<nuBins; i++)
	{ 
		UpEvents = nuUpAllCuts->GetBinContent(i);
		DownEvents = nuDownAllCuts->GetBinContent(i);
		x[i] = nuUpAllCuts->GetBinCenter(i);
		if (x[i] != (nuDownAllCuts->GetBinCenter(i))) { cout << endl << endl << "!!!!!!!!!!!!!!!!!!!!!!!!!! STOP! THERE'S A PROBLEM!!!!!!!!!!!!!!!!!!!!!!" << endl << endl << endl;}
		posStuff = UpEvents/(HeChargeScaleUp * HelivetimeUp + 1e-15);
		negStuff = DownEvents/(HeChargeScaleDown * HelivetimeDown + 1e-15);
		y[i] = ((posStuff - negStuff)/(posStuff + negStuff + 1e-15));
		errory[i] = 2*(DownEvents*sqrt(UpEvents) + UpEvents*sqrt(DownEvents))/((HeChargeScaleUp*HelivetimeUp)*(HeChargeScaleDown*HelivetimeDown)*pow((UpEvents/(HeChargeScaleUp*HelivetimeUp + 1e-25)) + (DownEvents/(HeChargeScaleDown*HelivetimeDown + 1e-25)),2) + 1e-15);
		if ((UpEvents == 0) || (DownEvents == 0)) { errory[i] = 1;}
		if ((UpEvents == 0) || (DownEvents == 0)) { y[i] = NULL;}
		if (i==0)
		{
			minError = y[i] - 2*errory[i];
			maxError = y[i] + 2*errory[i];
		}
		if ((y[i] - 2*errory[i]) < minError) { minError = y[i] - 2*errory[i];}
		if ((y[i] + 2*errory[i]) > maxError) { maxError = y[i] + 2*errory[i];}
		errorx[i] = ((nuMax - nuMin)/nuBins)/2;
		asymOutFile << x[i] << "	 " << y[i] << "	" << errory[i] << "	" << UpEvents << "	" << HeChargeScaleUp << "	" << HelivetimeUp << "	" << DownEvents << "	" << HeChargeScaleDown << "	" << HelivetimeDown << endl;
		cout << x[i] << "	" << y[i] << "	" << errory[i] << "	" << UpEvents << "	" << HeChargeScaleUp << "	" << HelivetimeUp << "	" << DownEvents << "	" << HeChargeScaleDown << "	" << HelivetimeDown << endl;
	}
	asymGraph = new TGraphErrors(nuBins, x, y, errorx, errory);
	asymGraph->SetMarkerStyle(21);
	asymGraph->SetMarkerColor(4);
	asymGraph->SetTitle(asymTitle);
	asymTestHist = new TH2F("asymTestHist",asymTitle,nuBins,nuMin,nuMax,100,minError,maxError);
	asymTestHist->SetStats(kFALSE);
	asymTestHist->Draw();
	cout << "Fit min = " << nuMin << "; Fit max = " << nuMax << endl;
	TF1 *fitAsymGraph = new TF1("fitAsymGraph", "[0]", nuMin, nuMax);
	asymGraph->Draw("P");
	fitAsymGraph->SetLineColor(kBlue);
	asymGraph->Fit("fitAsymGraph","R");
	asymCanvas->Update();

	asymOutFile.close();

	TString asymOutTitle = outputPlotsHere;
	asymOutTitle += "asym_plots_for_Runs_";
	asymOutTitle += HeRunNumber;
	asymOutTitle += "-";
	asymOutTitle += endHeRunNumber;
	if (includeVetos) {asymOutTitle += "_with_vetos";}
	asymOutTitle += ".png";
	asymCanvas->Print(asymOutTitle);

*/


	cout << "^^^^^^^^^^^^^^^^^^^^^^^ hand_class_draw_tof_nu.h ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
}
