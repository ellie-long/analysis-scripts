


void t_beam_asymmetry_vs_runs(){

	TString Q2 = "1.0";

	int HeRunNumber = 22447;
	int endHeRunNumber = 22488;

	double bins = 41;
	double xmin = 22447;
	double xmax = 22488;

	// Defines Cuts
	TCut cut = "";
	TCut kinematics = "PriKineR.Q2<10 && GoodElectron==1 && PriKineR.omega<10";
	TCut eventtype = "(D.evtypebits&2)==2";
	TCut gold = "R.gold.dp>-0.04 && R.gold.dp<0.053";
	TCut target = "ReactPt_R.z>-0.17 && ReactPt_R.z<0.175";
	TCut sieve = "abs(R_sv_y)<0.03 && abs(R_sv_x)<0.06";

	TCut cuts = cut && kinematics && eventtype && gold && target && sieve;

	TChain* chainHe = new TChain("T");

	TString filenameHe;

	for (int thisHeRunNumber=HeRunNumber; thisHeRunNumber<(endHeRunNumber+1); thisHeRunNumber++)
	{
		// Skipping Vertical Carbon Runs
		if(thisHeRunNumber==20591){thisHeRunNumber=20596;}
		if(thisHeRunNumber==20731){thisHeRunNumber=20738;}
		if(thisHeRunNumber==20732){thisHeRunNumber=20738;}
		if(thisHeRunNumber==20733){thisHeRunNumber=20738;}
		if(thisHeRunNumber==20734){thisHeRunNumber=20738;}
		if(thisHeRunNumber==20736){thisHeRunNumber=20738;}
		if(thisHeRunNumber==20737){thisHeRunNumber=20738;}
		if(thisHeRunNumber==20762){thisHeRunNumber=20789;}
		if(thisHeRunNumber==20763){thisHeRunNumber=20789;}
		if(thisHeRunNumber==20764){thisHeRunNumber=20789;}
		if(thisHeRunNumber==20791){thisHeRunNumber=20814;}
		if(thisHeRunNumber==20792){thisHeRunNumber=20814;}

		// Skipping Longitudinal Carbon Runs
		if(thisHeRunNumber==22380){thisHeRunNumber=22393;}
		if(thisHeRunNumber==22389){thisHeRunNumber=22393;}
		if(thisHeRunNumber==22425){thisHeRunNumber=22436;}
		if(thisHeRunNumber==22426){thisHeRunNumber=22436;}

		// Skipping Transverse Carbon Runs
		if(thisHeRunNumber==22461){thisHeRunNumber=22465;}

		// Adds runs to the chain
		for (int t=0; t<1000; t++)
		{
			filenameHe = "/home/ellie/physics/e05-102/terabyte/ROOTfiles/e05102_R_";
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
		}
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
	chainHe->Draw("R.gold.dp>>HedpNoCut(400,-0.08,0.08)", "", "");
	chainHe->Draw("R.gold.dp>>HedpCut(400,-0.08,0.08)", gold, "");
	HedpNoCut->SetTitle(titledp);
	HedpNoCut->Draw();
	HedpCut->SetLineColor(kBlack);
	HedpCut->SetFillColor(kViolet);
	HedpCut->Draw("same");

	pad2->cd();
	cout << "Drawing Target Cut..." << endl;
	chainHe->Draw("ReactPt_R.z>>HeReactZNoCut(400,-0.3,0.3)", "", "");
	chainHe->Draw("ReactPt_R.z>>HeReactZCut(400,-0.3,0.3)", target, "");
	HeReactZNoCut->SetTitle("Target Cut");
	HeReactZNoCut->Draw();
	HeReactZCut->SetLineColor(kBlack);
	HeReactZCut->SetFillColor(kViolet);
	HeReactZCut->Draw("same");

	pad3->cd();
	cout << "Drawing Theta and Phi..." << endl;
	chainHe->Draw("R_sv_x:R_sv_y>>HeSieveNoCut(100,-0.05,0.05,100,-0.1,0.1)", target, "");
	HeSieveNoCut->SetTitle("Theta and Phi, No Cut");
	HeSieveNoCut->SetStats(kFALSE);
	HeSieveNoCut->Draw("COLZ");

	pad4->cd();
	cout << "Drawing Theta and Phi Cut..." << endl;
	chainHe->Draw("R_sv_x:R_sv_y>>HeSieveCut(100,-0.05,0.05,100,-0.1,0.1)", target && sieve, "");
	HeSieveCut->SetTitle("Theta and Phi Cut");
	HeSieveCut->SetStats(kFALSE);
	HeSieveCut->Draw("COLZ");

	pad5->cd();
	TString titleQ2 = "Q2";
	cout << "Drawing " << titleQ2 << "..." << endl;
	chainHe->Draw("PriKineR.Q2>>histQ2(400,0,1.6)", cuts, "");
	histQ2->SetTitle(titleQ2);
	histQ2->SetStats(kFALSE);
	histQ2->Draw();

	pad6->cd();
	TString titleOmega = "Omega";
	cout << "Drawing " << titleOmega << "..." << endl;
	chainHe->Draw("PriKineR.omega>>histOmega(100,0.3,0.8)", cuts, "");
	histOmega->SetTitle(titleOmega);
	histOmega->SetStats(kFALSE);
	histOmega->Draw();

	pad7->cd();
	TString titleHel = "Helicity vs. Bjorken x";
	cout << "Drawing " << titleHel << "..." << endl;
	TH2F *histHel = new TH2F("histHel",titleHel,bins,xmin,xmax,7,-2,2);
	chainHe->Draw("g0hel.R.helicity:(PriKineR.Q2 / (PriKineR.omega * 2 * 0.9315))>>histHel", cuts, "");
	histHel->Draw("COLZ");


	pad8->cd();
	TString titlePosHelx = "# of Positive Helicity Events vs. Run #";
	cout << "Drawing " << titlePosHelx << "..." << endl;
	TH1F *histPosHelx = new TH1F("histPosHelx",titlePosHelx,bins,xmin,xmax);
	chainHe->Draw("fEvtHdr.fRun>>histPosHelx", cuts && "g0hel.R.helicity==1", "");
	histPosHelx->Draw();

	pad9->cd();
	TString titleNegHelx = "# of Negative Helicity Events vs. Bjorken x";
	cout << "Drawing " << titleNegHelx << "..." << endl;
	TH1F *histNegHelx = new TH1F("histNegHelx",titleNegHelx,bins,xmin,xmax);
	chainHe->Draw("fEvtHdr.fRun>>histNegHelx", cuts && "g0hel.R.helicity==-1", "");
	histNegHelx->Draw();
	
	pad10->cd();
	TString titlex = "Bjorken x ";
	titlex += " (x=Q^2/[2m*omega])";
	cout << "Drawing " << titlex << "..." << endl;
	TH1F *histx = new TH1F("histx",titlex,bins,xmin,xmax);
	histx->Sumw2();
	chainHe->Draw("(PriKineR.Q2 / (PriKineR.omega * 2 * 0.9315))>>histx", cuts, "E");
	histx->Draw();


	// Note: Asymmetry is defined as (Pos - Neg)/(Pos + Neg)
	pad11->cd();
	TString titleAsym = "Beam Asymmetry (%) vs. Run # for Q2 of ";
	titleAsym += Q2;
	cout << "Drawing " << titleAsym << "..." << endl;
//	TH1F *histPosHelIn = new TH1F("histPosHelIn",titleAsym,bins,xmin,xmax);
//	TH1F *histPosHelOut = new TH1F("histPosHelOut",titleAsym,bins,xmin,xmax);
//	chainHe->Draw("(PriKineR.Q2 / (PriKineR.omega * 2 * 0.9315))>>histPosHelIn", cuts && "g0hel.R.helicity==1" && "fEvtHdr.fRun<22413", "");
//	chainHe->Draw("(PriKineR.Q2 / (PriKineR.omega * 2 * 0.9315))>>histPosHelOut", cuts && "g0hel.R.helicity==-1" && "fEvtHdr.fRun>22412", "");
//	histPosHelIn->Sumw2();
//	histPosHelOut->Sumw2();
//	histPosHel->Add(histPosHelIn,histPosHelOut);
//	TH1F *histNegHelIn = new TH1F("histNegHelIn","Negative Helicity",bins,xmin,xmax);
//	TH1F *histNegHelOut = new TH1F("histNegHelOut","Negative Helicity",bins,xmin,xmax);
//	chainHe->Draw("(PriKineR.Q2 / (PriKineR.omega * 2 * 0.9315))>>histNegHelIn", cuts && "g0hel.R.helicity==-1" && "fEvt.fRun<22413", "");
//	chainHe->Draw("(PriKineR.Q2 / (PriKineR.omega * 2 * 0.9315))>>histNegHelOut", cuts && "g0hel.R.helicity==1" && "fEvt.fRun>22412", "");
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

	TString imagename = "Asymmetries/Transverse_Beam_Asymmetry_vs_Run_Number_for_Q2_of_";
	imagename += Q2;
	imagename += ".png";
	c1->Print(imagename);


	cout << "All done!" << endl;


}












