// This program should just show plots of the target with
// different cuts
//
// Elena Long (ellie@jlab.org)



void draw_cuts(){

	int CRunNumber=22389;
//	int HeRunNumber=22393;
	int HeRunNumber = 20597;

	TChain* chainC = new TChain("T");
	TChain* chainHe = new TChain("T");

	TString filename = "/home/ellie/physics/e05-102/terabyte/ROOTfiles/e05102_R_";
	TString filenameC = filename;
	filenameC += CRunNumber;
	filenameC += ".root";
	TString filenameHe = filename;
	filenameHe += HeRunNumber;
	filenameHe += ".root";
	chainC->Add(filenameC);
	chainHe->Add(filenameHe);

	gStyle->SetPalette(1,0);

	TCanvas *c1 = new TCanvas("c1","Target Cuts",1200,800);
	c1->Divide(2,2);

	c1->cd(1);
	chainC->Draw("ExTgtCor_R.dp>>CdpNoCut(400,-0.08,0.08)","");
	chainC->Draw("ExTgtCor_R.dp>>CdpCut(400,-0.08,0.08)","ExTgtCor_R.dp>-0.04&&ExTgtCor_R.dp<0.05");
//	chainC->Draw("ReactPt_R.z>>Ccut2(800,-0.3,0.3)","ReactPt_R.z>-0.1&&ReactPt_R.z<0.075");
//	chainC->Draw("ReactPt_R.z>>Ccut3(800,-0.3,0.3)","ReactPt_R.z>-0.04&&ReactPt_R.z<0.02");
	CdpNoCut->Draw();
	CdpCut->SetLineColor(kBlack);
	CdpCut->SetFillColor(kViolet);
	CdpCut->Draw("same");
/*	Ccut2->SetLineColor(kGreen);
	Ccut2->SetFillColor(kGreen);
	Ccut2->Draw("same");
	Ccut3->SetLineColor(kBlue);
	Ccut3->SetFillColor(kBlue);
	Ccut3->Draw("same");
*/


	c1->cd(2);
	chainC->Draw("ReactPt_R.z>>CReactZNoCut(400,-0.3,0.3)","");
	chainC->Draw("ReactPt_R.z>>CReactZCut(400,-0.3,0.3)","ReactPt_R.z>-0.1 && ReactPt_R.z<0.08");
//	chainC->Draw("ReactPt_R.z>>CReactZCut2(800,-0.3,0.3)","ReactPt_R.z>-0.1&&ReactPt_R.z<0.075");
//	chainC->Draw("ReactPt_R.z>>Hecut3(800,-0.3,0.3)","ReactPt_R.z>-0.04&&ReactPt_R.z<0.02");
	CReactZNoCut->Draw();
	CReactZCut->SetLineColor(kBlack);
	CReactZCut->SetFillColor(kViolet);
	CReactZCut->Draw("same");
/*	Hecut2->SetLineColor(kGreen);
	Hecut2->SetFillColor(kGreen);
	Hecut2->Draw("same");
	Hecut3->SetLineColor(kBlue);
	Hecut3->SetFillColor(kBlue);
	Hecut3->Draw("same");
*/

	c1->cd(3);
	chainC->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>CSieveNoCut(100,-0.05,0.05,100,-0.1,0.1)","ReactPt_R.z>-0.04 && ReactPt_R.z<0.02");
	CSieveNoCut->Draw("COLZ");

	c1->cd(4);
	chainC->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>CSieveCut(100,-0.05,0.05,100,-0.1,0.1)","ReactPt_R.z>-0.04 && ReactPt_R.z<0.02 && abs(ExTgtCor_R.ph)<0.03 && abs(ExTgtCor_R.th)<0.06");
	CSieveCut->Draw("COLZ");

}
