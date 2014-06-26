


void v_target_asymmetry(){

// Below are for 1st pass, Q2=0.13
/*	TString Q2 = "0.13";
	int HeRunNumberL = 1589;
	int endHeRunNumberL = 1638;
	int HeRunNumberR = 20460; 
	int endHeRunNumberR = 20511;
	double chargeScalePosL = 1/0.23648446;
	double chargeScaleNegL = 1/0.2395559;
	double chargeScalePosR = 1/0.23116767;
	double chargeScaleNegR = 1/0.23312222;
*/
	TString Q2 = "0.13-test";
	int HeRunNumberL = 1600;
	int endHeRunNumberL = 1619;
	int HeRunNumberR = 20471;
	int endHeRunNumberR = 20489;
	double chargeScalePosL = 1/0.051266;
	double chargeScaleNegL = 1/0.056143;
	double chargeScalePosR = 1/0.051269;
	double chargeScaleNegR = 1/0.056188;


// Below are for 3rd pass, Q2=1.0
/*
	TString Q2 = "1.0";
	int HeRunNumberL = 1686;
	int endHeRunNumberL = 1882;
//	int endHeRunNumberL = 1958;
	int HeRunNumberR = 20579;
	int endHeRunNumberR = 20789;
// NOTE: There is a problem with the charge scalar in runs 20812-20879. When this is fixed,
// uncomment the line below. Until then, we stop at run 20789.
//	int endHeRunNumberR = 20879;
	double chargeScalePosL = 1/1.202086;
	double chargeScaleNegL = 1/1.165871;
	double chargeScalePosR = 1/1.202242;
	double chargeScaleNegR = 1/1.167498;
*/

	double bins = 50;
	double xmin = 0.6;
	double xmax = 1.6;

	// Defines Right Arm Cuts
	TCut cutR = "he3R.IsSpinValid==1";
	TCut kinematicsR = "PriKineR.Q2<10 && GoodElectron==1 && PriKineR.nu<10";
	TCut eventtypeR = "(D.evtypebits&2)==2";
	TCut goldR = "ExTgtCor_R.dp>-0.04 && ExTgtCor_R.dp<0.058";
	TCut targetR = "ReactPt_R.z>-0.155 && ReactPt_R.z<0.175";
	TCut thetaphiR = "abs(ExTgtCor_R.ph)<0.03 && abs(ExTgtCor_R.th)<0.06";

	TCut cutsR = cutR && kinematicsR && eventtypeR && goldR && targetR && thetaphiR;

	// Defines Left Arm Cuts
	TCut cutL = "he3.IsSpinValid==1";
	TCut kinematicsL = "PriKineL.Q2<10 && GoodElectron==1 && PriKineL.nu<10";
//	TCut eventtypeL = "(D.evtypebits&2)==2";
	TCut eventtypeL = "";
	TCut goldL = "ExTgtCor_L.dp>-0.04 && ExTgtCor_L.dp<0.058";
	TCut targetL = "ReactPt_L.z>-0.155 && ReactPt_L.z<0.175";
	TCut thetaphiL = "abs(ExTgtCor_L.ph)<0.03 && abs(ExTgtCor_L.th)<0.06";

	TCut cutsL = cutL && kinematicsL && eventtypeL && goldL && targetL && thetaphiL;


	TChain* chainHeR = new TChain("T");
	TChain* chainHeL = new TChain("T");

	TString filenameHeR;
	TString filenameHeL;

// ******************* The section below adds files to the Right arm chain from the RHRS ********************
	for (int thisHeRunNumberR=HeRunNumberR; thisHeRunNumberR<(endHeRunNumberR+1); thisHeRunNumberR++)
	{


		// Skipping Vertical Carbon & Deuterium Runs & Bad Runs
		if(thisHeRunNumberR==20591){thisHeRunNumberR=20596;}
		if(thisHeRunNumberR==20731){thisHeRunNumberR=20738;}
		if(thisHeRunNumberR==20732){thisHeRunNumberR=20738;}
		if(thisHeRunNumberR==20733){thisHeRunNumberR=20738;}
		if(thisHeRunNumberR==20734){thisHeRunNumberR=20738;}
		if(thisHeRunNumberR==20736){thisHeRunNumberR=20738;}
		if(thisHeRunNumberR==20737){thisHeRunNumberR=20738;}
		if(thisHeRunNumberR==20762){thisHeRunNumberR=20789;}
		if(thisHeRunNumberR==20763){thisHeRunNumberR=20789;}
		if(thisHeRunNumberR==20764){thisHeRunNumberR=20789;}
		if(thisHeRunNumberR==20791){thisHeRunNumberR=20814;}
		if(thisHeRunNumberR==20792){thisHeRunNumberR=20814;}
		if(thisHeRunNumberR==20472){thisHeRunNumberR=20475;}
		if(thisHeRunNumberR==20473){thisHeRunNumberR=20475;}

		// Skipping Longitudinal Carbon Runs
		if(thisHeRunNumberR==22380){thisHeRunNumberR=22393;}
		if(thisHeRunNumberR==22389){thisHeRunNumberR=22393;}
		if(thisHeRunNumberR==22425){thisHeRunNumberR=22436;}
		if(thisHeRunNumberR==22426){thisHeRunNumberR=22436;}

		// Skipping Transverse Carbon Runs
		if(thisHeRunNumberR==22461){thisHeRunNumberR=22465;}

		// Adds runs to the chain
		for (int t=0; t<1000; t++)
		{
			filenameHeR = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_R_";
			filenameHeR += thisHeRunNumberR;
			if (t != 0)
			{
				filenameHeR += "_";
				filenameHeR += t;
			}
			filenameHeR += ".root";
			ifstream ifileHeR(filenameHeR);
			if (ifileHeR)
			{
				cout << "Adding file to chainHeR: " << filenameHeR << endl;
				chainHeR->Add(filenameHeR);
			}
			else
			{
				cout << "File " << filenameHeR << " does not exist. Ending here." << endl;
				t=999999999;
			}
		}
//		 Use the line below only for debugging purposes. It will only add the first file.
//		 thisHeRunNumberR=999999;
	}
// ***********************************************************************************************************

// ************************** The section below adds files to the Left arm chain from the LHRS ***************
	for (int thisHeRunNumberL=HeRunNumberL; thisHeRunNumberL<(endHeRunNumberL+1); thisHeRunNumberL++)
	{
		// Skipping Vertical Carbon and Deuterium Runs & Bad Runs
		if(thisHeRunNumberL==1699){thisHeRunNumberL=1705;}
		if(thisHeRunNumberL==1825){thisHeRunNumberL=1832;}
		if(thisHeRunNumberL==1826){thisHeRunNumberL=1832;}
		if(thisHeRunNumberL==1827){thisHeRunNumberL=1832;}
		if(thisHeRunNumberL==1828){thisHeRunNumberL=1832;}
		if(thisHeRunNumberL==1830){thisHeRunNumberL=1832;}
		if(thisHeRunNumberL==1831){thisHeRunNumberL=1832;}
		if(thisHeRunNumberL==1884){thisHeRunNumberL=1905;}
		if(thisHeRunNumberL==1885){thisHeRunNumberL=1905;}
		if(thisHeRunNumberL==1603){thisHeRunNumberL=1605;}


		// Skipping Longitudinal Carbon Runs
		if(thisHeRunNumberL==22380){thisHeRunNumberL=22393;}
		if(thisHeRunNumberL==22389){thisHeRunNumberL=22393;}
		if(thisHeRunNumberL==22425){thisHeRunNumberL=22436;}
		if(thisHeRunNumberL==22426){thisHeRunNumberL=22436;}

		// Skipping Transverse Carbon Runs
		if(thisHeRunNumberL==22461){thisHeRunNumberL=22465;}

		// Adds runs to the chain
		for (int t=0; t<1000; t++)
		{
			filenameHeL = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_L_";
			filenameHeL += thisHeRunNumberL;
			if (t != 0)
			{
				filenameHeL += "_";
				filenameHeL += t;
			}
			filenameHeL += ".root";
			ifstream ifileHeL(filenameHeL);
			if (ifileHeL)
			{
				cout << "Adding file to chainHeL: " << filenameHeL << endl;
				chainHeL->Add(filenameHeL);
			}
			else
			{
				cout << "File " << filenameHeL << " does not exist. Ending here." << endl;
				t=999999999;
			}
		}
//		 Use the line below only for debugging purposes. It will only add the first file.
//		 thisHeRunNumberL=999999;
	}
// ****************************************************************************************************************




	gStyle->SetPalette(1);
	
	// Defines Canvas
	TCanvas *c1 = new TCanvas("c1","Asymmetry",1360,810); //x,y
	pad1  =  new  TPad("pad1","pad1",0.0000,0.6666,0.2500,1.0000,0,0,0);
	pad2  =  new  TPad("pad2","pad2",0.2500,0.6666,0.5000,1.0000,0,0,0);
	pad3  =  new  TPad("pad3","pad3",0.5000,0.6666,0.7500,1.0000,0,0,0);
	pad4  =  new  TPad("pad4","pad4",0.7500,0.6666,1.0000,1.0000,0,0,0);
	pad5  =  new  TPad("pad5","pad5",0.0000,0.3333,0.2000,0.6666,0,0,0);
	pad6  =  new  TPad("pad6","pad6",0.2000,0.3333,0.4000,0.6666,0,0,0);
	pad7  =  new  TPad("pad7","pad7",0.4000,0.3333,0.6000,0.6666,0,0,0);
	pad8  =  new  TPad("pad8","pad8",0.6000,0.3333,0.8000,0.6666,0,0,0);
	pad9  =  new  TPad("pad9","pad9",0.8000,0.3333,1.0000,0.6666,0,0,0);
	pad10 = new TPad("pad10","pad10",0.0000,0.0000,0.5000,0.3333,0,0,0);
	pad11 = new TPad("pad11","pad11",0.5000,0.0000,1.0000,0.3333,0,0,0);
	pad1->Draw();pad2->Draw();pad3->Draw();pad4->Draw();pad5->Draw();pad6->Draw();pad7->Draw();pad8->Draw();pad9->Draw();pad10->Draw();pad11->Draw();



	// Everything below here makes graphs for each section of the canvas

	pad1->cd();
	TString titledp = "dp Cut";
	cout << "Drawing " << titledp << "..." << endl;
	TH1F *HedpNoCut = new TH1F("HedpNoCut",titledp,400,-0.08,0.08);
	TH1F *HedpCut = new TH1F("HedpCut",titledp,400,-0.08,0.08);
	chainHeR->Draw("ExTgtCor_R.dp>>HedpNoCutR(400,-0.08,0.08)", "", "");
	chainHeR->Draw("ExTgtCor_R.dp>>HedpCutR(400,-0.08,0.08)", goldR, "");
	chainHeL->Draw("ExTgtCor_L.dp>>HedpNoCutL(400,-0.08,0.08)", "", "");
	chainHeL->Draw("ExTgtCor_L.dp>>HedpCutL(400,-0.08,0.08)", goldL, "");
	HedpNoCut->Add(HedpNoCutR,HedpNoCutL);
	HedpNoCut->SetTitle(titledp);
	HedpNoCut->Draw();
	HedpCut->Add(HedpCutR,HedpCutL);
	HedpCut->SetLineColor(kBlack);
	HedpCut->SetFillColor(kViolet);
	HedpCut->Draw("same");
	pad1->Update();

	pad2->cd();
	cout << "Drawing Target Cut..." << endl;
	TString titleTarget = "Target Cut";
	TH1F *HeReactZNoCut = new TH1F("HeReactZNoCut",titleTarget,400,-0.3,0.3);
	TH1F *HeReactZCut = new TH1F("HeReactZCut",titleTarget,400,-0.3,0.3);
	chainHeR->Draw("ReactPt_R.z>>HeReactZNoCutR(400,-0.3,0.3)", "", "");
	chainHeR->Draw("ReactPt_R.z>>HeReactZCutR(400,-0.3,0.3)", targetR, "");
	chainHeL->Draw("ReactPt_L.z>>HeReactZNoCutL(400,-0.3,0.3)", "", "");
	chainHeL->Draw("ReactPt_L.z>>HeReactZCutL(400,-0.3,0.3)", targetL, "");
	HeReactZNoCut->Add(HeReactZNoCutR,HeReactZNoCutL);
	HeReactZNoCut->SetTitle(titleTarget);
	HeReactZNoCut->Draw();
	HeReactZCut->Add(HeReactZCutR,HeReactZCutL);
	HeReactZCut->SetLineColor(kBlack);
	HeReactZCut->SetFillColor(kViolet);
	HeReactZCut->Draw("same");
	pad2->Update();

	pad3->cd();
	cout << "Drawing Theta and Phi..." << endl;
	TString titleThetaPhiNoCut = "Theta and Phi, No Cut";
	TH2F *HeThetaPhiNoCut = new TH2F("HeThetaPhiNoCut",titleThetaPhiNoCut,100,-0.05,0.05,100,-0.1,0.1);
	chainHeR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeThetaPhiNoCutR(100,-0.05,0.05,100,-0.1,0.1)", targetR, "");
	chainHeL->Draw("ExTgtCor_L.th:ExTgtCor_L.ph>>HeThetaPhiNoCutL(100,-0.05,0.05,100,-0.1,0.1)", targetL, "");
	HeThetaPhiNoCut->Add(HeThetaPhiNoCutR,HeThetaPhiNoCutL);
	HeThetaPhiNoCut->SetTitle(titleThetaPhiNoCut);
	HeThetaPhiNoCut->SetStats(kFALSE);
	HeThetaPhiNoCut->Draw("COLZ");
	pad3->Update();

	pad4->cd();
	cout << "Drawing Theta and Phi Cut..." << endl;
	TString titleThetaPhi = "Theta and Phi Cut";
	TH2F *HeThetaPhiCut = new TH2F("HeThetaPhiCut",titleThetaPhi,100,-0.05,0.05,100,-0.1,0.1);
	chainHeR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeThetaPhiCutR(100,-0.05,0.05,100,-0.1,0.1)", targetR && thetaphiR, "");
	chainHeL->Draw("ExTgtCor_L.th:ExTgtCor_L.ph>>HeThetaPhiCutL(100,-0.05,0.05,100,-0.1,0.1)", targetL && thetaphiL, "");
	HeThetaPhiCut->Add(HeThetaPhiCutR,HeThetaPhiCutL);
	HeThetaPhiCut->SetTitle(titleThetaPhi);
	HeThetaPhiCut->SetStats(kFALSE);
	HeThetaPhiCut->Draw("COLZ");
	pad4->Update();

	pad5->cd();
	TString titleQ2 = "Q2";
	TH1F *histQ2 = new TH1F("histQ2",titleQ2,400,0,1.6);
	cout << "Drawing " << titleQ2 << "..." << endl;
	chainHeR->Draw("PriKineR.Q2>>histQ2R(400,0,1.6)", cutsR, "");	
	chainHeL->Draw("PriKineL.Q2>>histQ2L(400,0,1.6)", cutsL, "");
	histQ2->Add(histQ2R,histQ2L);
	histQ2->SetTitle(titleQ2);
	histQ2->SetStats(kFALSE);
	histQ2->Draw();
	pad5->Update();

	pad6->cd();
	TString titleNu = "Nu";
	cout << "Drawing " << titleNu << "..." << endl;
	TH1F *histNu = new TH1F("histNu",titleNu,100,0,0.8);
	chainHeR->Draw("PriKineR.nu>>histNuR(100,0,0.8)", cutsR, "");
	chainHeL->Draw("PriKineL.nu>>histNuL(100,0,0.8)", cutsL, "");
	histNu->Add(histNuR,histNuL);
	histNu->SetTitle(titleNu);
	histNu->SetStats(kFALSE);
	histNu->Draw();
	pad6->Update();

	pad7->cd();
	TString titleHel = "Target Helicity vs. Bjorken x";
	cout << "Drawing " << titleHel << "..." << endl;
	TH2F *histHelR = new TH2F("histHelR",titleHel,bins,xmin,xmax,7,-2,2);
	TH2F *histHelL = new TH2F("histHelL",titleHel,bins,xmin,xmax,7,-2,2);
	TH2F *histHel = new TH2F("histHel",titleHel,bins,xmin,xmax,7,-2,2);
	chainHeR->Draw("he3R.Spin:(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histHelR", cutsR, "");
	chainHeL->Draw("he3.Spin:(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>histHelL", cutsL, "");
	histHel->Add(histHelR,histHelL);
	histHel->Draw("COLZ");
	pad7->Update();


	// Note: For all plots below, Positive Target Helicity is defined as Spin==1
	pad8->cd();
	TString titlePosHelx = "# of Positive Target Helicity Events vs. Bjorken x";
	cout << "Drawing " << titlePosHelx << "..." << endl;
	TH1F *histPosHelxR = new TH1F("histPosHelxL",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxL = new TH1F("histPosHelxR",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelx = new TH1F("histPosHelx",titlePosHelx,bins,xmin,xmax);
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histPosHelxR", cutsR && "he3R.Spin==1", "");
	chainHeL->Draw("(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>histPosHelxL", cutsL && "he3.Spin==1", "");
	histPosHelxR->Scale(chargeScalePosR);
	histPosHelxL->Scale(chargeScalePosL);
	histPosHelx->Add(histPosHelxR,histPosHelxL);
	histPosHelx->Draw();
	pad8->Update();

	pad9->cd();
	TString titleNegHelx = "# of Negative Target Helicity Events vs. Bjorken x";
	cout << "Drawing " << titleNegHelx << "..." << endl;
	TH1F *histNegHelxR = new TH1F("histNegHelxR",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxL = new TH1F("histNegHelxL",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelx = new TH1F("histNegHelx",titleNegHelx,bins,xmin,xmax);
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histNegHelxR", cutsR && "he3R.Spin==-1", "");
	chainHeL->Draw("(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>histNegHelxL", cutsL && "he3.Spin==-1", "");
	histNegHelxR->Scale(chargeScaleNegR);
	histNegHelxL->Scale(chargeScaleNegL);
	histNegHelx->Add(histNegHelxR,histNegHelxL);
	histNegHelx->Draw();
	pad9->Update();

	pad10->cd();
	TString titlex = "Bjorken x ";
	titlex += " (x=Q^2/[2m*nu])";
	cout << "Drawing " << titlex << "..." << endl;
	TH1F *histxR = new TH1F("histxR",titlex,bins,xmin,xmax);
	TH1F *histxL = new TH1F("histxL",titlex,bins,xmin,xmax);
	TH1F *histx = new TH1F("histx",titlex,bins,xmin,xmax);
	histx->Sumw2();
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histxR", cutsR, "E");
	chainHeL->Draw("(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>histxL", cutsL, "E");
	histx->Add(histxR,histxL);
	histx->Draw();
	pad10->Update();


	// Note: Asymmetry is defined as (Pos - Neg)/(Pos + Neg)
	pad11->cd();
	TString titleAsym = "Target Asymmetry (%) vs. Bjorken x for Q2 of ";
	titleAsym += Q2;
	cout << "Drawing " << titleAsym << "..." << endl;
	histAsym = histPosHelx->GetAsymmetry(histNegHelx);
	histAsym->Scale(100);
	histAsym->SetTitle(titleAsym);
	histAsym->Draw();
	pad11->Update();

	TString imagename = "Asymmetries/Vertical_Target_Asymmetry_for_Q2_of_";
//	TString imagename = "Asymmetries/Left_Only_Vertical_Target_Asymmetry_for_Q2_of_";
	imagename += Q2;
	imagename += ".png";
	c1->Print(imagename);


	cout << "All done!" << endl;


}












