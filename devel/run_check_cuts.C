


void run_check_cuts(int RunNumber){

	TString Q2 = "1.0";

	int HeRunNumber = RunNumber;
	int endHeRunNumber = RunNumber;
	double bins = 50;
	double xmin = 0;
	double xmax = 3.5;

	TCut cut = "";
	TCut kinematics = "PriKineR.Q2<10 && GoodElectron==1 && PriKineR.omega<10";
	TCut eventtype = "(D.evtypebits&2)==2";
	TCut gold = "ExTgtCor_R.dp>-0.04 && ExTgtCor_R.dp<0.053";
	TCut target = "ReactPt_R.z>-0.15 && ReactPt_R.z<0.17";
	TCut target1 = "ReactPt_R.z>-0.3 && ReactPt_R.z<-0.175";
	TCut target2 = "ReactPt_R.z>0.19 && ReactPt_R.z<0.3";
//	TCut sieve = "abs(ExTgtCor_R.ph)<0.02 && abs(ExTgtCor_R.th)<0.04";
	TCut sieve = "";
	TCut tracks = "R.tr.n==1 && R.vdc.u1.nhit>3 && R.vdc.u1.nhit<7 && R.vdc.u2.nhit>3 && R.vdc.u2.nhit<7 && R.vdc.v1.nhit>3 && R.vdc.v1.nhit<7 && R.vdc.v2.nhit>3 && R.vdc.v2.nhit<7";
	TCut cuts = cut && kinematics && eventtype && gold && target && sieve && tracks;

	TChain* chainHe = new TChain("T");

	TString filenameHe;

	for (int thisHeRunNumber=HeRunNumber; thisHeRunNumber<(endHeRunNumber+1); thisHeRunNumber++)
	{
/*		// Skipping Vertical Carbon Runs
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
*/

		for (int t=0; t<1000; t++)
		{
			filenameHe = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_replay_R_";
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

	TCanvas *c1 = new TCanvas("c1","Run Check",1400,810); //x,y

	pad1  =  new  TPad("pad1","pad1",0.00,0.50,0.25,1.00,0,0,0);
	pad2  =  new  TPad("pad2","pad2",0.25,0.50,0.50,1.00,0,0,0);
	pad3  =  new  TPad("pad3","pad3",0.50,0.50,0.75,1.00,0,0,0);
	pad4  =  new  TPad("pad4","pad4",0.75,0.50,1.00,1.00,0,0,0);
	pad5  =  new  TPad("pad5","pad5",0.00,0.00,0.25,0.50,0,0,0);
	pad6  =  new  TPad("pad6","pad6",0.25,0.00,0.50,0.50,0,0,0);
	pad7  =  new  TPad("pad7","pad7",0.50,0.00,0.75,0.50,0,0,0);
	pad8  =  new  TPad("pad8","pad8",0.75,0.00,1.00,0.50,0,0,0);
	pad1->Draw();pad2->Draw();pad3->Draw();pad4->Draw();pad5->Draw();pad6->Draw();pad7->Draw();pad8->Draw();

	pad1->cd();
	TString titleTarget = "Target for Run # ";
	titleTarget += RunNumber;
	cout << "Drawing Target..." << endl;
	chainHe->Draw("ReactPt_R.z>>HeReactZNoCut(400,-0.3,0.3)", eventtype && tracks, "");
	HeReactZNoCut->SetTitle(titleTarget);
	HeReactZNoCut->Draw();
	chainHe->Draw("ReactPt_R.z>>HeReactZCut(400,-0.3,0.3)",target && eventtype && tracks,"same");
	HeReactZCut->SetFillColor(kViolet);
	HeReactZCut->Draw("same");

/*	chainHe->Draw("ReactPt_R.z>>HeReactZCut1(400,-0.3,0.3)",target1 && eventtype && tracks,"same");
	chainHe->Draw("ReactPt_R.z>>HeReactZCut2(400,-0.3,0.3)",target2 && eventtype && tracks,"same");
	HeReactZCut1->SetFillColor(kViolet);
	HeReactZCut1->Draw("same");
	HeReactZCut2->SetFillColor(kViolet);
	HeReactZCut2->Draw("same");
*/
	pad2->cd();
	TString titleQ2 = "Q2 for Run # ";
	titleQ2 += RunNumber;
	cout << "Drawing " << titleQ2 << "..." << endl;
	chainHe->Draw("PriKineR.Q2>>histQ2(400,0,1.6)", eventtype && tracks, "");
	histQ2->SetTitle(titleQ2);
//	histQ2->SetStats(kFALSE);
	histQ2->Draw();

	pad3->cd();
	TString titleNu = "Nu for Run # ";
	titleNu += RunNumber;
	cout << "Drawing " << titleNu << "..." << endl;
	chainHe->Draw("PriKineR.nu>>histNu(100,0.0,0.8)", eventtype && tracks, "");
	histNu->SetTitle(titleNu);
//	histNu->SetStats(kFALSE);
	histNu->Draw();

	pad4->cd();
	TString titledp = "dp for Run # ";
	titledp += RunNumber;
	cout << "Drawing " << titledp << "..." << endl;
	chainHe->Draw("ExTgtCor_R.dp>>HedpNoCut(400,-0.08,0.08)", gold && target && eventtype && tracks, "");
	HedpNoCut->SetTitle(titledp);
	HedpNoCut->Draw();

	pad5->cd();
	TString titleScat = "Scattering Angle vs. Phi";
	cout << "Drawing " << titleScat << "..." << endl;
	TH2F *HeScat = new TH2F("HeScat",titleScat,300,-0.02,0.02,300,14,20);
/*	chainHe->Draw("ScaAngle:ExTgtCor_R.ph>>HeScat1(300,-0.02,0.02,300,14,20)",gold && target1 && eventtype && tracks,"");
	chainHe->Draw("ScaAngle:ExTgtCor_R.ph>>HeScat2(300,-0.02,0.02,300,14,20)",gold && target2 && eventtype && tracks,"");
	HeScat->Add(HeScat1,HeScat2);
*/
	chainHe->Draw("ScaAngle:ExTgtCor_R.ph>>HeScat",gold && target && eventtype && tracks,"");
	HeScat->Draw("COLZ");

	pad6->cd();
//	TString titleThetaPhi = "Theta and Phi (No Cut) for Run # ";
	TString titleThetaPhi = "R.tr.d_th and R.tr.d_ph for Run # ";
	titleThetaPhi += RunNumber;
	cout << "Drawing " << titleThetaPhi << "..."  << endl;
	TH2F *HeSieveNoCut = new TH2F("HeSieveNoCut",titleThetaPhi,100,-0.05,0.05,100,-0.1,0.1);
/*	TH2F *HeSieveNoCut1 = new TH2F("HeSieveNoCut1",titleThetaPhi,100,-0.05,0.05,100,-0.1,0.1);
	TH2F *HeSieveNoCut2 = new TH2F("HeSieveNoCut2",titleThetaPhi,100,-0.05,0.05,100,-0.1,0.1);

	chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeSieveNoCut1", target1 && eventtype && tracks, "");
	chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeSieveNoCut2", target2 && eventtype && tracks, "");
	HeSieveNoCut->Add(HeSieveNoCut1,HeSieveNoCut2);
*/
//	chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeSieveNoCut", target && eventtype && tracks, "");
	chainHe->Draw("R.tr.d_th:R.tr.d_ph>>HeSieveNoCut", target && eventtype && tracks, "");
	HeSieveNoCut->SetStats(kFALSE);
	HeSieveNoCut->Draw("COLZ");

	pad7->cd();
//	TString titleThetaPhi = "Theta and Phi (Cut) for Run # ";
	TString titleThetaPhi = "R.tr.r_th and R.tr.r_ph for Run # ";
	titleThetaPhi += RunNumber;
	cout << "Drawing " << titleThetaPhi << "..."  << endl;
	TH2F *HeSieveCut = new TH2F("HeSieveCut",titleThetaPhi,100,-0.05,0.05,100,-0.1,0.1);
/*	TH2F *HeSieveCut1 = new TH2F("HeSieveCut1",titleThetaPhi,100,-0.05,0.05,100,-0.1,0.1);
	TH2F *HeSieveCut2 = new TH2F("HeSieveCut2",titleThetaPhi,100,-0.05,0.05,100,-0.1,0.1);
	chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeSieveCut1", target1 && sieve && eventtype && tracks, "");
	chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeSieveCut2", target2 && sieve && eventtype && tracks, "");
	HeSieveCut->Add(HeSieveCut1,HeSieveCut2);
*/
//	chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeSieveCut", target && sieve && eventtype && tracks, "");
	chainHe->Draw("R.tr.r_th:R.tr.r_ph>>HeSieveCut", target && sieve && eventtype && tracks, "");
	HeSieveCut->SetStats(kFALSE);
	HeSieveCut->Draw("COLZ");


	pad8->cd();
	pad8->SetLogy();
	TString titlex = "Bjorken x ";
	titlex += " (x=Q^2/[2m*nu]) for Run # ";
	titlex += RunNumber;
	cout << "Drawing " << titlex << "..." << endl;
	TH1F *histx = new TH1F("histx",titlex,bins,xmin,xmax);
	TH1F *histx1 = new TH1F("histx1",titlex,bins,xmin,xmax);
	TH1F *histx2 = new TH1F("histx2",titlex,bins,xmin,xmax);
	histx1->Sumw2();
	histx2->Sumw2();
	histx->Sumw2();
/*	chainHe->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histx1", target1 && eventtype && tracks, "E");
	chainHe->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histx2", target2 && eventtype && tracks, "E");
	histx->Add(histx1,histx2);
*/	
	
	chainHe->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histx", target, "E");
	histx->Draw();


//	histx2->Draw();	
//	TString imagename = "/home/ellie/physics/e05-102/terabyte/Run_Checks/Run_Check_for_Run_";
//	imagename += RunNumber;
//	imagename += ".png";
//	c1->Print(imagename);


	cout << "All done!" << endl;


}












