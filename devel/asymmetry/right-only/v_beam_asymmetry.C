


void v_beam_asymmetry(){

	TString Q2 = "1.0";

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

	TChain* chainHeR = new TChain("T");

	TString filenameHeR;

	for (int thisHeRunNumberR=HeRunNumberR; thisHeRunNumberR<(endHeRunNumberR+1); thisHeRunNumberR++)
	{
		// Skipping Vertical Carbon Runs
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

		// Skipping Vertical Deuterium Runs

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
	chainHeR->Draw("ExTgtCor_R.dp>>HedpNoCut(400,-0.08,0.08)", "", "");
	chainHeR->Draw("ExTgtCor_R.dp>>HedpCut(400,-0.08,0.08)", goldR, "");
	HedpNoCut->SetTitle(titledp);
	HedpNoCut->Draw();
	HedpCut->SetLineColor(kBlack);
	HedpCut->SetFillColor(kViolet);
	HedpCut->Draw("same");

	pad2->cd();
	cout << "Drawing Target Cut..." << endl;
	chainHeR->Draw("ReactPt_R.z>>HeReactZNoCut(400,-0.3,0.3)", "", "");
	chainHeR->Draw("ReactPt_R.z>>HeReactZCut(400,-0.3,0.3)", targetR, "");
	HeReactZNoCut->SetTitle("Target Cut");
	HeReactZNoCut->Draw();
	HeReactZCut->SetLineColor(kBlack);
	HeReactZCut->SetFillColor(kViolet);
	HeReactZCut->Draw("same");

	pad3->cd();
	cout << "Drawing Theta and Phi..." << endl;
	chainHeR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeSieveNoCut(100,-0.05,0.05,100,-0.1,0.1)", targetR, "");
	HeSieveNoCut->SetTitle("Theta and Phi, No Cut");
	HeSieveNoCut->SetStats(kFALSE);
	HeSieveNoCut->Draw("COLZ");

	pad4->cd();
	cout << "Drawing Theta and Phi Cut..." << endl;
	chainHeR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeSieveCut(100,-0.05,0.05,100,-0.1,0.1)", targetR && thetaphiR, "");
	HeSieveCut->SetTitle("Theta and Phi Cut");
	HeSieveCut->SetStats(kFALSE);
	HeSieveCut->Draw("COLZ");

	pad5->cd();
	TString titleQ2 = "Q2";
	cout << "Drawing " << titleQ2 << "..." << endl;
	chainHeR->Draw("PriKineR.Q2>>histQ2(400,0,1.6)", cutsR, "");
	histQ2->SetTitle(titleQ2);
	histQ2->SetStats(kFALSE);
	histQ2->Draw();

	pad6->cd();
	TString titleNu = "Nu";
	cout << "Drawing " << titleNu << "..." << endl;
	chainHeR->Draw("PriKineR.nu>>histNu(100,0.3,0.8)", cutsR, "");
	histNu->SetTitle(titleNu);
	histNu->SetStats(kFALSE);
	histNu->Draw();

	pad7->cd();
	TString titleHel = "Helicity vs. Bjorken x";
	cout << "Drawing " << titleHel << "..." << endl;
	TH2F *histHel = new TH2F("histHel",titleHel,bins,xmin,xmax,7,-2,2);
	chainHeR->Draw("g0hel.R.helicity:(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histHel", cutsR, "");
	histHel->Draw("COLZ");


	// Note: For all plots below, Positive Helicity is defined as g0hel.R.helicity==1 when the BHWP is In
	// and g0hel.R.helicity==-1 when the BHWP is Out
	pad8->cd();
	TString titlePosHelx = "# of Positive Helicity Events vs. Bjorken x";
	cout << "Drawing " << titlePosHelx << "..." << endl;
	TH1F *histPosHelxIn = new TH1F("histPosHelxIn1",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxIn = new TH1F("histPosHelxIn2",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxIn = new TH1F("histPosHelxIn",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxOut = new TH1F("histPosHelxOut1",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxOut = new TH1F("histPosHelxOut2",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelxOut = new TH1F("histPosHelxOut",titlePosHelx,bins,xmin,xmax);
	TH1F *histPosHelx = new TH1F("histPosHelx",titlePosHelx,bins,xmin,xmax);
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histPosHelxIn1", cutsR && "g0hel.R.helicity==1" && "fEvtHdr.fRun>20576" && "fEvtHdr.fRun<20684", "");
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histPosHelxIn2", cutsR && "g0hel.R.helicity==1" && "fEvtHdr.fRun>20728" && "fEvtHdr.fRun<20813", "");
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histPosHelxOut1", cutsR && "g0hel.R.helicity==-1" && "fEvtHdr.fRun>20683" && "fEvtHdr.fRun<20728", "");
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histPosHelxOut2", cutsR && "g0hel.R.helicity==-1" && "fEvtHdr.fRun>20813" && "fEvtHdr.fRun<20879", "");
	histPosHelxIn->Add(histPosHelxIn1,histPosHelxIn2);
	histPosHelxOut->Add(histPosHelxOut1,histPosHelxOut2);
	histPosHelx->Add(histPosHelxIn,histPosHelxOut);
	histPosHelx->Draw();

	pad9->cd();
	TString titleNegHelx = "# of Negative Helicity Events vs. Bjorken x";
	cout << "Drawing " << titleNegHelx << "..." << endl;
	TH1F *histNegHelxIn = new TH1F("histNegHelxIn1",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxIn = new TH1F("histNegHelxIn2",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxIn = new TH1F("histNegHelxIn",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxOut = new TH1F("histNegHelxOut1",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxOut = new TH1F("histNegHelxOut2",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelxOut = new TH1F("histNegHelxOut",titleNegHelx,bins,xmin,xmax);
	TH1F *histNegHelx = new TH1F("histNegHelx",titleNegHelx,bins,xmin,xmax);
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histNegHelxIn1", cutsR && "g0hel.R.helicity==-1" && "fEvtHdr.fRun>20576" && "fEvtHdr.fRun<20684", "");
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histNegHelxIn2", cutsR && "g0hel.R.helicity==-1" && "fEvtHdr.fRun>20728" && "fEvtHdr.fRun<20813", "");
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histNegHelxOut1", cutsR && "g0hel.R.helicity==1" && "fEvtHdr.fRun>20683" && "fEvtHdr.fRun<20728", "");
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histNegHelxOut2", cutsR && "g0hel.R.helicity==1" && "fEvtHdr.fRun>20813" && "fEvtHdr.fRun<20879", "");
	histNegHelxIn->Add(histNegHelxIn1,histNegHelxIn2);
	histNegHelxOut->Add(histNegHelxOut1,histNegHelxOut2);
	histNegHelx->Add(histNegHelxIn,histNegHelxOut);
	histNegHelx->Draw();
	
	pad10->cd();
	TString titlex = "Bjorken x ";
	titlex += " (x=Q^2/[2m*nu])";
	cout << "Drawing " << titlex << "..." << endl;
	TH1F *histx = new TH1F("histx",titlex,bins,xmin,xmax);
	histx->Sumw2();
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histx", cutsR, "E");
	histx->Draw();


	// Note: Asymmetry is defined as (Pos - Neg)/(Pos + Neg)
	pad11->cd();
	TString titleAsym = "Beam Asymmetry (%) vs. Bjorken x for Q2 of ";
	titleAsym += Q2;
	cout << "Drawing " << titleAsym << "..." << endl;
//	TH1F *histPosHelIn = new TH1F("histPosHelIn",titleAsym,bins,xmin,xmax);
//	TH1F *histPosHelOut = new TH1F("histPosHelOut",titleAsym,bins,xmin,xmax);
//	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histPosHelIn", cutsR && "g0hel.R.helicity==1" && "fEvtHdr.fRun<22413", "");
//	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histPosHelOut", cutsR && "g0hel.R.helicity==-1" && "fEvtHdr.fRun>22412", "");
//	histPosHelIn->Sumw2();
//	histPosHelOut->Sumw2();
//	histPosHel->Add(histPosHelIn,histPosHelOut);
//	TH1F *histNegHelIn = new TH1F("histNegHelIn","Negative Helicity",bins,xmin,xmax);
//	TH1F *histNegHelOut = new TH1F("histNegHelOut","Negative Helicity",bins,xmin,xmax);
//	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histNegHelIn", cutsR && "g0hel.R.helicity==-1" && "fEvt.fRun<22413", "");
//	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histNegHelOut", cutsR && "g0hel.R.helicity==1" && "fEvt.fRun>22412", "");
//	histNegHelIn->Sumw2();
//	histNegHelOut->Sumw2();
//	histNegHel->Add(histNegHelIn,histNegHelOut);
//	histPosHelx->SetStats(kFALSE);
//	histNegHelx->SetStats(kFALSE);
//	histPosHelx->Sumw2();
//	histNegHelx->Sumw2();
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












