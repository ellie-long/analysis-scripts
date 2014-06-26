// This program should just show plots of the target with
// different cuts
//
// Elena Long (ellie@jlab.org)



void t_He_draw_cuts(){

	int CRunNumber=22389;
	int HeRunNumber=22450;

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
	chainHe->Draw("R.gold.dp>>HedpNoCut(400,-0.08,0.08)","");
	chainHe->Draw("R.gold.dp>>HedpCut(400,-0.08,0.08)","R.gold.dp>-0.04&&R.gold.dp<0.053");
//	chainC->Draw("ReactPt_R.z>>Ccut2(800,-0.3,0.3)","ReactPt_R.z>-0.1&&ReactPt_R.z<0.075");
//	chainC->Draw("ReactPt_R.z>>Ccut3(800,-0.3,0.3)","ReactPt_R.z>-0.04&&ReactPt_R.z<0.02");
	HedpNoCut->Draw();
	HedpCut->SetLineColor(kBlack);
	HedpCut->SetFillColor(kViolet);
	HedpCut->Draw("same");
/*	Ccut2->SetLineColor(kGreen);
	Ccut2->SetFillColor(kGreen);
	Ccut2->Draw("same");
	Ccut3->SetLineColor(kBlue);
	Ccut3->SetFillColor(kBlue);
	Ccut3->Draw("same");
*/


	c1->cd(2);
	chainHe->Draw("ReactPt_R.z>>HeReactZNoCut(400,-0.3,0.3)","");
	chainHe->Draw("ReactPt_R.z>>HeReactZCut(400,-0.3,0.3)","ReactPt_R.z>-0.1 && ReactPt_R.z<0.08");
//	chainC->Draw("ReactPt_R.z>>CReactZCut2(800,-0.3,0.3)","ReactPt_R.z>-0.1&&ReactPt_R.z<0.075");
//	chainC->Draw("ReactPt_R.z>>Hecut3(800,-0.3,0.3)","ReactPt_R.z>-0.04&&ReactPt_R.z<0.02");
	HeReactZNoCut->Draw();
	HeReactZCut->SetLineColor(kBlack);
	HeReactZCut->SetFillColor(kViolet);
	HeReactZCut->Draw("same");
/*	Hecut2->SetLineColor(kGreen);
	Hecut2->SetFillColor(kGreen);
	Hecut2->Draw("same");
	Hecut3->SetLineColor(kBlue);
	Hecut3->SetFillColor(kBlue);
	Hecut3->Draw("same");
*/

	c1->cd(3);
	chainHe->Draw("R_sv_x:R_sv_y>>HeSieveNoCut(100,-0.05,0.05,100,-0.1,0.1)","ReactPt_R.z>-0.04 && ReactPt_R.z<0.02");
	HeSieveNoCut->Draw("COLZ");

	c1->cd(4);
	chainHe->Draw("R_sv_x:R_sv_y>>HeSieveCut(100,-0.05,0.05,100,-0.1,0.1)","ReactPt_R.z>-0.04 && ReactPt_R.z<0.02 && abs(R_sv_y)<0.03 && abs(R_sv_x)<0.06");
	HeSieveCut->Draw("COLZ");

}
