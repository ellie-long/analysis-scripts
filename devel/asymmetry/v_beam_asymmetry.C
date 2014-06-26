


void v_beam_asymmetry(){

	TString Q2 = "1.0";

	int HeRunNumberL = 1686;
	int endHeRunNumberL = 1958;
	int HeRunNumberR = 20596;
	int endHeRunNumberR = 20789;
// NOTE: There is a problem with the charge scalar in runs 20812-20879. When this is fixed,
// uncomment the line below. Until then, we stop at run 20789.
//	int endHeRunNumberR = 20879;
	
	double bins = 50;
	double xmin = 0.6;
	double xmax = 1.6;

	// Defines Right Arm Cuts
	TCut cutR = "";
	TCut kinematicsR = "PriKineR.Q2<10 && GoodElectron==1 && PriKineR.nu<10";
	TCut eventtypeR = "(D.evtypebits&2)==2";
	TCut goldR = "ExTgtCor_R.dp>-0.04 && ExTgtCor_R.dp<0.053";
	TCut targetR = "ReactPt_R.z>-0.17 && ReactPt_R.z<0.175";
	TCut thetaphiR = "abs(ExTgtCor_R.ph)<0.03 && abs(ExTgtCor_R.th)<0.06";

	TCut cutsR = cutR && kinematicsR && eventtypeR && goldR && targetR && thetaphiR;

	// Defines Left Arm Cuts
	TCut cutL = "";
	TCut kinematicsL = "PriKineL.Q2<10 && GoodElectron==1 && PriKineL.nu<10";
//	TCut eventtypeL = "(D.evtypebits&2)==2";
	TCut eventtypeL = "";
	TCut goldL = "ExTgtCor_L.dp>-0.04 && ExTgtCor_L.dp<0.053";
	TCut targetL = "ReactPt_L.z>-0.17 && ReactPt_L.z<0.175";
	TCut thetaphiL = "abs(ExTgtCor_L.ph)<0.03 && abs(ExTgtCor_L.th)<0.06";

	TCut cutsL = cutL && kinematicsL && eventtypeL && goldL && targetL && thetaphiL;


	TChain* chainHeR = new TChain("T");
	TChain* chainHeL = new TChain("T");

	TString filenameHeR;
	TString filenameHeL;

// ******************* The section below adds files to the Right arm chain from the RHRS ********************
	for (int thisHeRunNumberR=HeRunNumberR; thisHeRunNumberR<(endHeRunNumberR+1); thisHeRunNumberR++)
	{
		// Skipping Vertical Carbon & Deuterium Runs
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
			filenameHeR = "/home/ellie/physics/e05-102/terabyte/ROOTfiles/e05102_R_";
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
		// Skipping Vertical Carbon and Deuterium Runs
		if(thisHeRunNumberL==1699){thisHeRunNumberL=1705;}
		if(thisHeRunNumberL==1825){thisHeRunNumberL=1832;}
		if(thisHeRunNumberL==1826){thisHeRunNumberL=1832;}
		if(thisHeRunNumberL==1827){thisHeRunNumberL=1832;}
		if(thisHeRunNumberL==1828){thisHeRunNumberL=1832;}
		if(thisHeRunNumberL==1830){thisHeRunNumberL=1832;}
		if(thisHeRunNumberL==1831){thisHeRunNumberL=1832;}
		if(thisHeRunNumberL==1884){thisHeRunNumberL=1905;}
		if(thisHeRunNumberL==1885){thisHeRunNumberL=1905;}

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
			filenameHeL = "/home/ellie/physics/e05-102/terabyte/ROOTfiles/e05102_L_";
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

	pad6->cd();
	TString titleNu = "Nu";
	cout << "Drawing " << titleNu << "..." << endl;
	TH1F *histNu = new TH1F("histNu",titleNu,100,0.3,0.8);
	chainHeR->Draw("PriKineR.nu>>histNuR(100,0.3,0.8)", cutsR, "");
	chainHeL->Draw("PriKineL.nu>>histNuL(100,0.3,0.8)", cutsL, "");
	histNu->Add(histNuR,histNuL);
	histNu->SetTitle(titleNu);
	histNu->SetStats(kFALSE);
	histNu->Draw();

	pad7->cd();
	TString titleHel = "Helicity vs. Bjorken x";
	cout << "Drawing " << titleHel << "..." << endl;
	TH2F *histHelR = new TH2F("histHelR",titleHel,bins,xmin,xmax,7,-2,2);
	TH2F *histHelL = new TH2F("histHelL",titleHel,bins,xmin,xmax,7,-2,2);
	TH2F *histHel = new TH2F("histHel",titleHel,bins,xmin,xmax,7,-2,2);
	chainHeR->Draw("g0hel.R.helicity:(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histHelR", cutsR, "");
	chainHeL->Draw("g0hel.L.helicity:(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>histHelL", cutsL, "");
	histHel->Add(histHelR,histHelL);
	histHel->Draw("COLZ");


	// Note: For all plots below, Positive Helicity is defined as g0hel.R.helicity==1 when the BHWP is In
	// and g0hel.R.helicity==-1 when the BHWP is Out
	pad8->cd();
	TString titlePosHelx = "# of Positive Helicity Events vs. Bjorken x";
	cout << "Drawing " << titlePosHelx << "..." << endl;
	TH1F *histPosHelxIn1R = new TH1F("histPosHelxIn1R",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxIn2R = new TH1F("histPosHelxIn2R",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxInR = new TH1F("histPosHelxInR",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxOut1R = new TH1F("histPosHelxOut1R",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxOut2R = new TH1F("histPosHelxOut2R",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxOutR = new TH1F("histPosHelxOutR",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxIn1L = new TH1F("histPosHelxIn1L",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxIn2L = new TH1F("histPosHelxIn2L",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxInL = new TH1F("histPosHelxInL",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxOut1L = new TH1F("histPosHelxOut1L",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxOut2L = new TH1F("histPosHelxOut2L",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxOutL = new TH1F("histPosHelxOutL",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxR = new TH1F("histPosHelxL",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxL = new TH1F("histPosHelxR",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelx = new TH1F("histPosHelx",titlePosHelx,bins,xmin,xmax);
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histPosHelxIn1R", cutsR && "g0hel.R.helicity==1" && "fEvtHdr.fRun>20576" && "fEvtHdr.fRun<20684", "");
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histPosHelxIn2R", cutsR && "g0hel.R.helicity==1" && "fEvtHdr.fRun>20728" && "fEvtHdr.fRun<20813", "");
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histPosHelxOut1R", cutsR && "g0hel.R.helicity==-1" && "fEvtHdr.fRun>20683" && "fEvtHdr.fRun<20728", "");
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histPosHelxOut2R", cutsR && "g0hel.R.helicity==-1" && "fEvtHdr.fRun>20813" && "fEvtHdr.fRun<20879", "");
	chainHeL->Draw("(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>histPosHelxIn1L", cutsL && "g0hel.L.helicity==1" && "fEvtHdr.fRun>1685" && "fEvtHdr.fRun<1778", "");
	chainHeL->Draw("(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>histPosHelxIn2L", cutsL && "g0hel.L.helicity==1" && "fEvtHdr.fRun>1822" && "fEvtHdr.fRun<1905", "");
	chainHeL->Draw("(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>histPosHelxOut1L", cutsL && "g0hel.L.helicity==-1" && "fEvtHdr.fRun>1777" && "fEvtHdr.fRun<1823", "");
	chainHeL->Draw("(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>histPosHelxOut2L", cutsL && "g0hel.L.helicity==-1" && "fEvtHdr.fRun>1905" && "fEvtHdr.fRun<1960", "");
	histPosHelxInR->Add(histPosHelxIn1R,histPosHelxIn2R);
	histPosHelxOutR->Add(histPosHelxOut1R,histPosHelxOut2R);
	histPosHelxR->Add(histPosHelxInR,histPosHelxOutR);
	histPosHelxInL->Add(histPosHelxIn1L,histPosHelxIn2L);
	histPosHelxOutL->Add(histPosHelxOut1L,histPosHelxOut2L);
	histPosHelxL->Add(histPosHelxInL,histPosHelxOutL);
	histPosHelx->Add(histPosHelxR,histPosHelxL);
	histPosHelx->Draw();

	pad9->cd();
	TString titleNegHelx = "# of Negative Helicity Events vs. Bjorken x";
	cout << "Drawing " << titleNegHelx << "..." << endl;
	TH1F *histNegHelxIn1R = new TH1F("histNegHelxIn1R",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxIn2R = new TH1F("histNegHelxIn2R",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxInR = new TH1F("histNegHelxInR",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxOut1R = new TH1F("histNegHelxOut1R",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxOut2R = new TH1F("histNegHelxOut2R",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxOutR = new TH1F("histNegHelxOutR",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxR = new TH1F("histNegHelxR",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxIn1L = new TH1F("histNegHelxIn1L",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxIn2L = new TH1F("histNegHelxIn2L",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxInL = new TH1F("histNegHelxInL",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxOut1L = new TH1F("histNegHelxOut1L",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxOut2L = new TH1F("histNegHelxOut2L",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxOutL = new TH1F("histNegHelxOutL",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxL = new TH1F("histNegHelxL",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelx = new TH1F("histNegHelx",titleNegHelx,bins,xmin,xmax);
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histNegHelxIn1R", cutsR && "g0hel.R.helicity==-1" && "fEvtHdr.fRun>20576" && "fEvtHdr.fRun<20684", "");
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histNegHelxIn2R", cutsR && "g0hel.R.helicity==-1" && "fEvtHdr.fRun>20728" && "fEvtHdr.fRun<20813", "");
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histNegHelxOut1R", cutsR && "g0hel.R.helicity==1" && "fEvtHdr.fRun>20683" && "fEvtHdr.fRun<20728", "");
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histNegHelxOut2R", cutsR && "g0hel.R.helicity==1" && "fEvtHdr.fRun>20813" && "fEvtHdr.fRun<20879", "");
	chainHeL->Draw("(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>histNegHelxIn1L", cutsL && "g0hel.L.helicity==-1" && "fEvtHdr.fRun>1685" && "fEvtHdr.fRun<1778", "");
	chainHeL->Draw("(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>histNegHelxIn2L", cutsL && "g0hel.L.helicity==-1" && "fEvtHdr.fRun>1822" && "fEvtHdr.fRun<1905", "");
	chainHeL->Draw("(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>histNegHelxOut1L", cutsL && "g0hel.L.helicity==1" && "fEvtHdr.fRun>1777" && "fEvtHdr.fRun<1823", "");
	chainHeL->Draw("(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>histNegHelxOut2L", cutsL && "g0hel.L.helicity==1" && "fEvtHdr.fRun>1905" && "fEvtHdr.fRun<1960", "");
	histNegHelxInR->Add(histNegHelxIn1R,histNegHelxIn2R);
	histNegHelxInL->Add(histNegHelxIn1L,histNegHelxIn2L);
	histNegHelxOutR->Add(histNegHelxOut1R,histNegHelxOut2R);
	histNegHelxOutL->Add(histNegHelxOut1L,histNegHelxOut2L);
	histNegHelxR->Add(histNegHelxInR,histNegHelxOutR);
	histNegHelxL->Add(histNegHelxInL,histNegHelxOutL);
	histNegHelx->Add(histNegHelxR,histNegHelxL);
	histNegHelx->Draw();

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


	// Note: Asymmetry is defined as (Pos - Neg)/(Pos + Neg)
	pad11->cd();
	TString titleAsym = "Beam Asymmetry (%) vs. Bjorken x for Q2 of ";
	titleAsym += Q2;
	cout << "Drawing " << titleAsym << "..." << endl;
	histAsym = histPosHelx->GetAsymmetry(histNegHelx);
	histAsym->Scale(100);
	histAsym->SetTitle(titleAsym);
	histAsym->Draw();

	TString imagename = "Asymmetries/Vertical_Beam_Asymmetry_for_Q2_of_";
	imagename += Q2;
	imagename += ".png";
	c1->Print(imagename);


	cout << "All done!" << endl;


}












