


void find_elastic_peak_dp()
{

	int HeRunNumber = 20487;
	int endHeRunNumber = 20487;
	TChain* chainHe = new TChain("T");
	TString filenameHe;

	for (int thisHeRunNumber=HeRunNumber; thisHeRunNumber<(endHeRunNumber+1); thisHeRunNumber++)
	{
		for (int t=0; t<1000; t++)
		{
			filenameHe = "/home/ellie/physics/e05-102/ellana/ROOTfiles/q2_01_vert/e05102_R_";
//			filenameHe = "./e05102_R_";
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
	gStyle->SetOptFit(1111);

	TH1F *hist1 = new TH1F("hist1","dp Elastic Peak Fit", 100, -0.08, 0.08);
	chainHe->Draw("ExTgtCor_R.dp>>hist1");
	hist1->Draw();

	TF1 *fit1 = new TF1("fit1","gaus",0.032,0.039);
	hist1->Fit(fit1,"R");
	fit1->Draw("same");
	double fitMean = fit1->GetParameter(1);
	double fitSigma = fit1->GetParameter(2);
	cout << "fitMean: " << fitMean << ", fitSigma: " << fitSigma << endl;

	double diffFromMean = 3*fitSigma;
	lowerbound1 = new TLine((fitMean - diffFromMean),0,(fitMean - diffFromMean),200000);
	upperbound1 = new TLine((fitMean + diffFromMean),0,(fitMean + diffFromMean),200000);
	lowerbound1->SetLineColor(kBlue);
	upperbound1->SetLineColor(kBlue);
	lowerbound1->Draw("same");
	upperbound1->Draw("same");

	diffFromMean = 2*fitSigma;
	lowerbound2 = new TLine((fitMean - diffFromMean),0,(fitMean - diffFromMean),200000);
	upperbound2 = new TLine((fitMean + diffFromMean),0,(fitMean + diffFromMean),200000);
	lowerbound2->SetLineColor(kViolet);
	upperbound2->SetLineColor(kViolet);
	lowerbound2->Draw("same");
	upperbound2->Draw("same");

	diffFromMean = fitSigma;
	lowerbound3 = new TLine((fitMean - diffFromMean),0,(fitMean - diffFromMean),200000);
	upperbound3 = new TLine((fitMean + diffFromMean),0,(fitMean + diffFromMean),200000);
	lowerbound3->SetLineColor(kRed);
	upperbound3->SetLineColor(kRed);
	lowerbound3->Draw("same");
	upperbound3->Draw("same");


	plotInfo = new TPaveText(0.11,0.69,0.4,0.89,"NDC");
	plotInfo->AddText("Red = mean ± sigma");
	plotInfo->AddText("Violet = mean ± 2*sigma");
	plotInfo->AddText("Blue = mean ± 3*sigma");
	TString lowerBoundText = "Redlower: ";
	lowerBoundText += (fitMean - diffFromMean);
	TString upperBoundText = "Redupper: ";
	upperBoundText += (fitMean + diffFromMean);
	plotInfo->AddText(lowerBoundText);
	plotInfo->AddText(upperBoundText);
	plotInfo->Draw("same");


}
