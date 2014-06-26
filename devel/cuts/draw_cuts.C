// This script will take a cut and overlay the cut part in red
// overtop of the original plot in black
//
// Elena Long (ellie@jlab.org) 07-28-2009

void draw_cuts(int runnumber) {
	TString cutvar = "ReactPt_R.z";
	TCut cut = "abs(ReactPt_R.z)<0.15";
	double bcutmin = -0.3;
	double bcutmax = 0.3;

	TString filename;
	for (int t=0;t<1000;t++)
	{
		filename = "../../ellana/ROOTfiles/e05102_R_";
		filename += runnumber;
		if (t!=0)
		{
			filename += "_";
			filename += t;
		}
		filename += ".root";
	}
	TFile *_file0 = TFile::Open("filename");

	TCanvas *c1 = new TCanvas("c1","Cut in Red, Original in Black",600,400);
	//create, fill, and draw h1
	gStyle->SetOptStat(kFALSE);
	TH1F *h1 = new TH1F("h1","Without Cut",500,bcutmin,bcutmax);
	h1->Fill(cutvar);
	h1->Draw();
	c1->Update();

	TH1F *h2 = new TH1F("h2","With Cut",500,bcutmin,bcutmax);
	h2->Fill(cutvar,cut);
	h2->SetLineColor("kRed");
	h2->Draw("same");

}
