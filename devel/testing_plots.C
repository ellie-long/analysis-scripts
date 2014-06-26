// This program should just show plots of the target with
// different cuts
//
// Elena Long (ellie@jlab.org)



void testing_plots(){

	int CRunNumber=22389;
//	int HeRunNumber=22393;
	int HeRunNumber = 20597;

	TCut dpcut = "ExTgtCor_R.dp>-0.04 && ExTgtCor_R.dp<0.055";
//	TCut dpcut = "";
	TCut target = "ReactPt_R.z>-0.17 && ReactPt_R.z<0.175";
//	TCut target = "";
	TCut q2cut = "PriKineR.Q2>1.3 && PriKineR.Q2<1.4";
//	TCut q2cut = "";
		
	TCut cuts = dpcut && target && q2cut;

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

	c1->cd(3);
/*	chainC->Draw("ExTgtCor_R.dp>>CdpNoCut(400,-0.08,0.08)","");
	chainC->Draw("ExTgtCor_R.dp>>CdpCut(400,-0.08,0.08)","ExTgtCor_R.dp>-0.04&&ExTgtCor_R.dp<0.05");
//	chainC->Draw("ReactPt_R.z>>Ccut2(800,-0.3,0.3)","ReactPt_R.z>-0.1&&ReactPt_R.z<0.075");
//	chainC->Draw("ReactPt_R.z>>Ccut3(800,-0.3,0.3)","ReactPt_R.z>-0.04&&ReactPt_R.z<0.02");
	CdpNoCut->Draw();
	CdpCut->SetLineColor(kBlack);
	CdpCut->SetFillColor(kViolet);
	CdpCut->Draw("same");
	Ccut2->SetLineColor(kGreen);
	Ccut2->SetFillColor(kGreen);
	Ccut2->Draw("same");
	Ccut3->SetLineColor(kBlue);
	Ccut3->SetFillColor(kBlue);
	Ccut3->Draw("same");
*/
	chainHe->Draw("ExTgtCor_R.dp>>HedpNoCut(400,-0.08,0.08)","");
	chainHe->Draw("ExTgtCor_R.dp>>HedpCut(400,-0.08,0.08)",dpcut);
//	chainHe->Draw("ReactPt_R.z>>Hecut2(800,-0.3,0.3)","ReactPt_R.z>-0.1&&ReactPt_R.z<0.075");
//	chainHe->Draw("ReactPt_R.z>>Hecut3(800,-0.3,0.3)","ReactPt_R.z>-0.04&&ReactPt_R.z<0.02");
	HedpNoCut->Draw();
	HedpCut->SetLineColor(kBlack);
	HedpCut->SetFillColor(kViolet);
	HedpCut->Draw("same");


	c1->cd(1);
/*	chainC->Draw("ReactPt_R.z>>CReactZNoCut(400,-0.3,0.3)","");
	chainC->Draw("ReactPt_R.z>>CReactZCut(400,-0.3,0.3)","ReactPt_R.z>-0.1 && ReactPt_R.z<0.08");
//	chainC->Draw("ReactPt_R.z>>CReactZCut2(800,-0.3,0.3)","ReactPt_R.z>-0.1&&ReactPt_R.z<0.075");
//	chainC->Draw("ReactPt_R.z>>Hecut3(800,-0.3,0.3)","ReactPt_R.z>-0.04&&ReactPt_R.z<0.02");
	CReactZNoCut->Draw();
	CReactZCut->SetLineColor(kBlack);
	CReactZCut->SetFillColor(kViolet);
	CReactZCut->Draw("same");
*/
	chainHe->Draw("ReactPt_R.z>>HeReactZNoCut(400,-0.3,0.3)","");
	chainHe->Draw("ReactPt_R.z>>HeReactZCut(400,-0.3,0.3)",target);
//	chainHe->Draw("ReactPt_R.z>>HeReactZCut2(800,-0.3,0.3)","ReactPt_R.z>-0.1&&ReactPt_R.z<0.075");
//	chainHe->Draw("ReactPt_R.z>>Hecut3(800,-0.3,0.3)","ReactPt_R.z>-0.04&&ReactPt_R.z<0.02");
	HeReactZNoCut->Draw();
	HeReactZCut->SetLineColor(kBlack);
	HeReactZCut->SetFillColor(kViolet);
	HeReactZCut->Draw("same");

	c1->cd(2);
/*	chainC->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>CSieveNoCut(100,-0.05,0.05,100,-0.1,0.1)","ReactPt_R.z>-0.04 && ReactPt_R.z<0.02");
	CSieveNoCut->Draw("COLZ");
*/
	chainHe->Draw("PriKineR.Q2>>HeQ2NoCut(400,0,1.6)");
	chainHe->Draw("PriKineR.Q2>>HeQ2Cut(400,0,1.6)",q2cut);
	HeQ2NoCut->Draw();
	HeQ2Cut->SetLineColor(kBlack);
	HeQ2Cut->SetFillColor(kViolet);
	HeQ2Cut->Draw("same");


	c1->cd(4);
/*	chainC->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>CSieveCut(100,-0.05,0.05,100,-0.1,0.1)","ReactPt_R.z>-0.04 && ReactPt_R.z<0.02 && abs(ExTgtCor_R.ph)<0.03 && abs(ExTgtCor_R.th)<0.06");
	CSieveCut->Draw("COLZ");
*/
	chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeSieveCut(100,-0.05,0.05,100,-0.1,0.1)",cuts);
	HeSieveCut->Draw("COLZ");


}
