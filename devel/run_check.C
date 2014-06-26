


void run_check(int RunNumber){

	TString Q2 = "1.0";

	int HeRunNumber = RunNumber;
	int endHeRunNumber = RunNumber;
	double bins = 50;
	double xmin = 0;
	double xmax = 3.5;
/*
	TCut cut = "";
	TCut kinematics = "PriKineR.Q2<10 && GoodElectron==1 && PriKineR.omega<10";
	TCut eventtype = "(D.evtypebits&2)==2";
	TCut gold = "R.gold.dp>-0.04 && R.gold.dp<0.053";
	TCut target = "ReactPt_R.z>-0.1 && ReactPt_R.z<0.08";
	TCut sieve = "abs(R_sv_y)<0.03 && abs(R_sv_x)<0.06";

	TCut cuts = cut && kinematics && eventtype && gold && target && sieve;
*/
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
			TFile fileHe(filenameHe);
		}
	}





	gStyle->SetPalette(1);

	TCanvas *c1 = new TCanvas("c1","Run Check",1360,810); //x,y

	pad1  =  new  TPad("pad1","pad1",0.0000,0.5000,0.3333,1.0000,0,0,0);
	pad2  =  new  TPad("pad2","pad2",0.3333,0.5000,0.6666,1.0000,0,0,0);
	pad3  =  new  TPad("pad3","pad3",0.6666,0.5000,1.0000,1.0000,0,0,0);
	pad4  =  new  TPad("pad4","pad4",0.0000,0.0000,0.3333,0.5000,0,0,0);
	pad5  =  new  TPad("pad5","pad5",0.3333,0.0000,0.6666,0.5000,0,0,0);
	pad6  =  new  TPad("pad6","pad6",0.6666,0.0000,1.0000,0.5000,0,0,0);
	pad1->Draw();pad2->Draw();pad3->Draw();pad4->Draw();pad5->Draw();pad6->Draw();

	pad1->cd();
	TString titleTarget = "Target for Run # ";
	titleTarget += RunNumber;
	cout << "Drawing Target..." << endl;
	chainHe->Draw("ReactPt_R.z>>HeReactZNoCut(400,-0.3,0.3)", "", "");
	HeReactZNoCut->SetTitle(titleTarget);
	HeReactZNoCut->Draw();

	pad2->cd();
	TString titleQ2 = "Q2 for Run # ";
	titleQ2 += RunNumber;
	cout << "Drawing " << titleQ2 << "..." << endl;
	chainHe->Draw("PriKineR.Q2>>histQ2(400,0,1.6)", "", "");
	histQ2->SetTitle(titleQ2);
//	histQ2->SetStats(kFALSE);
	histQ2->Draw();

	pad3->cd();
	TString titleNu = "Nu for Run # ";
	titleNu += RunNumber;
	cout << "Drawing " << titleNu << "..." << endl;
	chainHe->Draw("PriKineR.nu>>histNu(100,0.0,0.8)", "", "");
	histNu->SetTitle(titleNu);
//	histNu->SetStats(kFALSE);
	histNu->Draw();

	pad4->cd();
	TString titledp = "dp for Run # ";
	titledp += RunNumber;
	cout << "Drawing " << titledp << "..." << endl;
	chainHe->Draw("ExTgtCor_R.dp>>HedpNoCut(400,-0.08,0.08)", "", "");
	HedpNoCut->SetTitle(titledp);
	HedpNoCut->Draw();

	pad5->cd();
	TString titleThetaPhi = "Theta and Phi for Run # ";
	titleThetaPhi += RunNumber;
	cout << "Drawing " << titleThetaPhi << "..."  << endl;
	chainHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeSieveNoCut(100,-0.05,0.05,100,-0.1,0.1)", "", "");
	HeSieveNoCut->SetTitle(titleThetaPhi);
	HeSieveNoCut->SetStats(kFALSE);
	HeSieveNoCut->Draw("COLZ");

	pad6->cd();
	pad6->SetLogy();
	TString titlex = "Bjorken x ";
	titlex += " (x=Q^2/[2m*nu]) for Run # ";
	titlex += RunNumber;
	cout << "Drawing " << titlex << "..." << endl;
	TH1F *histx = new TH1F("histx",titlex,bins,xmin,xmax);
	histx->Sumw2();
	chainHe->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histx", "", "E");
	histx->Draw();
	
	TString imagename = "/home/ellie/physics/e05-102/terabyte/Run_Checks/Run_Check_for_Run_";
	imagename += RunNumber;
	imagename += ".png";
	c1->Print(imagename);


	cout << "All done!" << endl;


}












