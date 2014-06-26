// #include "AyAnalysis.h"


void asym_with_neutrons(){

// Below are for 1st pass, Q2=0.13
/*	TString Q2 = "0.13-test";
	double q2min = 0.08;
	double q2max = 0.2;
	double numin = 0.02;
	double numax = 0.13;
	const int HeRunNumberR = 20475;
//	const int endHeRunNumberR = 20477;
	const int endHeRunNumberR = 20489;
*/


// Below are for 3rd pass, Q2=1.0
	TString Q2 = "1.0";
	double q2min = 0.08;
	double q2max = 1.6;
	double numin = 0.02;
	double numax = 0.8;
	int HeRunNumberR = 20579;
	int endHeRunNumberR = 20581;
// NOTE: There is a problem with the charge scalar in runs 20812-20879. When this is fixed,
// uncomment the line below. Until then, we stop at run 20789.
//	int endHeRunNumberR = 20879;
	double chargeScalePosR = 1/1.202242;
	double chargeScaleNegR = 1/1.167498;


	double xbjbins = 50;
	double xbjmin = 0.4;
	double xbjmax = 3.0;

	const int numOfRuns = endHeRunNumberR - HeRunNumberR + 5;
	const int numVars = 8;
	double infoArray[numOfRuns][numVars];
	for (int i=0; i<numOfRuns; i++)
	{
		for (int j=0; j<numVars; j++)
		{
			infoArray[i][j]=0;
		}
	}

	// Defines Right Arm Cuts
	TCut cutR = "he3R.IsSpinValid==1";
	TCut kinematicsR = "PriKineR.Q2<10 && PriKineR.nu<10";
//	TCut eventtypeR = "(D.evtypebits&2)==2";
	TCut eventtypeR = "";
//	TCut goldR = "ExTgtCor_R.dp>-0.04 && ExTgtCor_R.dp<0.058";
	TCut goldR = "";
	TCut targetR = "ReactPt_R.z>-0.17 && ReactPt_R.z<0.17";
	double thbound = 0.07;
	double phbound = 0.03;
	TString thetaphiRStr = "abs(ExTgtCor_R.ph)<";
	thetaphiRStr += phbound;
	thetaphiRStr += " && abs(ExTgtCor_R.th)<";
	thetaphiRStr += thbound;
	TCut thetaphiR = thetaphiRStr;
	TCut xbj = "PriKineRHe3.x_bj<2";
	TCut pssh = "(R.ps.e + 2*R.sh.e)>900";
	if (Q2=="1.0")
	{
		pssh = "(R.ps.e + 2*R.sh.e)>1600 && R.ps.e>200";
		TString psshtest = pssh;
		cout << "Q2=1.0, ps/sh cut = " << psshtest << endl;
	}
	TCut cerenkov = "R.cer.asum_c>400";

/*	TCut cutR = "";
	TCut kinematicsR = "";
	TCut eventtypeR = "";
	TCut goldR = "";
	TCut targetR = "";
	TCut thetaphiR = "";
*/
	TCut cutsR = cutR && kinematicsR && eventtypeR && goldR && targetR && thetaphiR && xbj && pssh;
	TCut allcutsR = cutsR && cerenkov;

	TChain* chainHeR = new TChain("T");

	TString filenameHeR;

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
		if(thisHeRunNumberR==20476){thisHeRunNumberR=20477;}

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
// ****************************************************************************************************************


// This section will put the root data into doubles so that
// it can be calculated through C++ instead of as histograms
// ****************************************************************************************************************
	int numberOfEvents;
	Double_t isSpinValid;
	Double_t qsquare;
	Double_t nu;
	Double_t evtypebits;
	Double_t dp;
	Double_t reactz;
	Double_t th;
	Double_t ph;
	Double_t x_bj;
	Double_t she;
	Double_t pse;
	Double_t cerasum;
	Double_t runNum;
	Double_t spin;
	int runNumber;
	Double_t u3c;
	Double_t u3pp;
	Double_t u3pm;
	Double_t u3mm;
	Double_t u3mp;
	Double_t p1l;
	Double_t p2l;
	Double_t p1r;
	Double_t p2r;



	numberOfEvents = int(chainHeR->GetEntries());
	chainHeR->SetBranchAddress("he3R.IsSpinValid", &isSpinValid);
	chainHeR->SetBranchAddress("he3R.Spin", &spin);
	chainHeR->SetBranchAddress("PriKineR.Q2", &qsquare);
	chainHeR->SetBranchAddress("PriKineR.nu", &nu);
	chainHeR->SetBranchAddress("D.evtypebits", &evtypebits);
	chainHeR->SetBranchAddress("ExTgtCor_R.dp", &dp);
	chainHeR->SetBranchAddress("ExTgtCor_R.th", &th);
	chainHeR->SetBranchAddress("ExTgtCor_R.ph", &ph);
	chainHeR->SetBranchAddress("ReactPt_R.z", &reactz);
	chainHeR->SetBranchAddress("PriKineRHe3.x_bj", &x_bj);
	chainHeR->SetBranchAddress("R.sh.e", &she);
	chainHeR->SetBranchAddress("R.ps.e", &pse);
	chainHeR->SetBranchAddress("R.cer.asum_c", &cerasum);
	chainHeR->SetBranchAddress("g.runnum", &runNum);
	chainHeR->SetBranchAddress("evright_u3c", &u3c);
	chainHeR->SetBranchAddress("evright_u3pp", &u3pp);
	chainHeR->SetBranchAddress("evright_u3pm", &u3pm);
	chainHeR->SetBranchAddress("evright_u3mm", &u3mm);
	chainHeR->SetBranchAddress("evright_u3mp", &u3mp);
/*	chainHeR->SetBranchAddress("NA.nd.p1.lt", &p1l);
	chainHeR->SetBranchAddress("NA.nd.p2.lt", &p2l);
	chainHeR->SetBranchAddress("NA.nd.p1.rt", &p1r);
	chainHeR->SetBranchAddress("NA.nd.p2.rt", &p2r);
*/

	cout << "Number of events: " << numberOfEvents << endl;
	chainHeR->GetEntry(1);
	runNumber = int(runNum);
	int prevRunNumber = runNumber;
	int runNumPlace = 0;
	infoArray[runNumPlace][0] = runNumber;
	int prevu3c = u3c;
	cout << "prevu3c = " << prevu3c << endl;
	int u3p = 0;
	int u3m = 0;
	int u3c_real = 0;
	int u3c_real_for_event = 0;
	int realNumOfRuns = 1;
	for (int i=0; i<numberOfEvents; i++)
	{
		chainHeR->GetEntry(i);
		runNumber = int(runNum);
		u3c_real_for_event = u3c - prevu3c;
		cout << "u3c_real_for_event = " << u3c_real_for_event << endl;
		cout << "Event # " << i << ", Run # " << runNumber << ", prevu3c = " << prevu3c << ", u3c = " << u3c << ", u3c_real_for_event = " << u3c_real_for_event << endl;
		if (i%10000 == 0)
		{
			cout << "Event Number " << i << ", Run Number " << runNumber << endl;
			cout << "u3c: " << u3c << "  u3pp: " << u3pp << "  u3pm: " << u3pm << "  u3mm: " << u3mm << "  u3mp: " << u3mp << " Error: " << infoArray[runNumPlace][7] << endl;
		}

		if ((isSpinValid==1)&&(qsquare<10)&&(nu<10)&&(dp>-0.04)&&(dp<0.058)&&(reactz>-0.155)&&(reactz<0.175)&&(abs(th)<0.07)&&(abs(ph)<0.03)&&(x_bj<2)&&((pse+(2*she))>900)&&(cerasum>400))
		{
			if (runNumber > prevRunNumber)
			{
				runNumPlace++;
				infoArray[runNumPlace][0] = runNumber;
				prevRunNumber = runNumber;
				prevu3c = 0;
				u3c_real = 0;
				u3p = 0;
				u3m = 0;
				realNumOfRuns++;
			}
			u3c_real = u3c_real + u3c_real_for_event;
			infoArray[runNumPlace][1]++;
			if (u3c_real != 0) {infoArray[runNumPlace][7] = sqrt(infoArray[runNumPlace][1]/u3c_real);}
			if (int(spin)==1) 
			{
				infoArray[runNumPlace][2]++;
				u3p = u3p + u3c_real_for_event;
				infoArray[runNumPlace][5] = u3pp + u3pm;
			}
			if (int(spin)==-1)
			{
				infoArray[runNumPlace][3]++;
				u3m = u3m + u3c_real_for_event;
				infoArray[runNumPlace][6] = u3mm + u3mp;
			}	
			infoArray[runNumPlace][4] = u3c_real;
		}

/*		if (Q2 == "1.0")
		{
			if ((isSpinValid==1)&&(qsquare<10)&&(nu<10)&&(reactz>-0.17)&&(reactz<0.17)&&(abs(th)<0.07)&&(abs(ph)<0.03)&&(x_bj<2)&&((pse+(2*she))>1600)&&(pse>200)&&(cerasum>400))
			{
				if ((p2l[11]>1)&&(p2[11]<3100)&&(p2r[11]>1)&&(p2r[11]<3100))
				{
					if ((p1l[13]==0)&&(p1r[13]==0)&&(p1l[14]==0)&&(p1r[14]==0)&&(p1l[15]==0)&&(p1r[15]==0)&&(p2l[10]==0)&&(p2r[10]==0)&&(p2l[12]==0)&&(p2r[12]==0))
					{
						if (runNumber > prevRunNumber)
						{
							runNumPlace++;
							infoArray[runNumPlace][0] = runNumber;
							prevRunNumber = runNumber;
							prevu3c = u3c;
							u3c_real = 0;
							u3p = 0;
							u3m = 0;
							realNumOfRuns++;
						}
						u3c_real = u3c_real + u3c_real_for_event;
						infoArray[runNumPlace][1]++;
						if (u3c_real != 0) {infoArray[runNumPlace][7] = sqrt(infoArray[runNumPlace][1]/u3c_real);}
						if (int(spin)==1) 
						{
							infoArray[runNumPlace][2]++;
							u3p = u3p + u3c_real_for_event;
							infoArray[runNumPlace][5] = u3pp + u3pm;
						}
						if (int(spin)==-1)
						{
							infoArray[runNumPlace][3]++;
							u3m = u3m + u3c_real_for_event;
							infoArray[runNumPlace][6] = u3mm + u3mp;
						}	
						infoArray[runNumPlace][4] = u3c_real;
					}
				}
			}
		}
*/
	
	prevu3c = u3c;
	}
	cout << "Number of Runs: " << numOfRuns << endl;
	cout << "Run #	# Unpolarized	# Spin Up	# Spin Down	Total C		C for up	C for down	Error" << endl;
	for (int i=0; i<numOfRuns; i++)
	{
		for (int j=0; j<numVars; j++)
		{
			cout << infoArray[i][j] << "	";
		}
		cout << endl;
	}
// ****************************************************************************************************************

	gStyle->SetPalette(1);
	gStyle->SetOptFit(0001);

	const int theRealNumOfRuns = realNumOfRuns;
	TCanvas *test = new TCanvas("test","Right Arm Asymmetry Test",800,600); //x,y
	test->cd();
	test->SetGrid();
	Double_t x[theRealNumOfRuns], y[theRealNumOfRuns], errory[theRealNumOfRuns], errorx[theRealNumOfRuns];
	Double_t posStuff;
	Double_t negStuff;
	double minError;
	double maxError;
	cout << "Real Number of Runs: " << realNumOfRuns << endl;
	for (Int_t i=0; i < (realNumOfRuns); i++)
	{
		x[i] = infoArray[i][0];
		y[i] = 10;
		if (infoArray[i][5] != 0)
		{
			if(infoArray[i][6] != 0)
			{
				posStuff = (infoArray[i][2] / infoArray[i][5]);
				negStuff = (infoArray[i][3] / infoArray[i][6]);
				y[i] = ((posStuff - negStuff) / (posStuff + negStuff));
			}
		}
		errory[i] = infoArray[i][7];
		if (i==0)
		{
			minError = y[i] - (2 * errory[i]);
			maxError = y[i] + (2 * errory[i]);
		}
		if ((y[i] - (2 * errory[i])) < minError)
		{
			minError = y[i] - (2 * errory[i]);
		}
		if ((y[i] + (2 * errory[i])) > maxError)
		{
			maxError = y[i] + (2 * errory[i]);
		}
			
		errorx[i] = 0;
		cout << "Run Number: " << infoArray[i][0] << " , Asymmetry = " << y[i] << " , Error = " << errory[i] << endl;
	}
	asymGraph = new TGraphErrors(numOfRuns, x, y, errorx, errory);
	asymGraph->SetMarkerStyle(21);
	asymGraph->SetMarkerColor(4);
	asymGraph->SetTitle("Raw Target SSA");
	asymTestHist = new TH2F("asymTestHist","Asymmetry Test",realNumOfRuns,HeRunNumberR-1,endHeRunNumberR+1,10,minError,maxError);
	asymTestHist->SetStats(kFALSE);
	asymTestHist->Draw();
	cout << "Fit min = " << infoArray[0][0] << "; Fit max = " << infoArray[realNumOfRuns - 1][0] << endl;
	TF1 *fitAsymGraph = new TF1("fitAsymGraph", "[0]", infoArray[0][0], infoArray[realNumOfRuns - 1][0]);
	asymGraph->Draw("P");
	fitAsymGraph->SetLineColor(kBlue);
	asymGraph->Fit("fitAsymGraph","R");
	test->Update();


	// Defines Canvas
	TCanvas *c1 = new TCanvas("c1","Asymmetry Cuts",1360,768); //x,y
	pad1  =  new  TPad("pad1","pad1",0.0000,0.5000,0.2500,1.0000,0,0,0);
	pad2  =  new  TPad("pad2","pad2",0.2500,0.5000,0.5000,1.0000,0,0,0);
	pad3  =  new  TPad("pad3","pad3",0.5000,0.5000,0.7500,1.0000,0,0,0);
	pad4  =  new  TPad("pad4","pad4",0.7500,0.5000,1.0000,1.0000,0,0,0);
	pad5  =  new  TPad("pad5","pad5",0.0000,0.0000,0.2500,0.5000,0,0,0);
	pad6  =  new  TPad("pad6","pad6",0.2500,0.0000,0.5000,0.5000,0,0,0);
	pad7  =  new  TPad("pad7","pad7",0.5000,0.0000,0.7500,0.5000,0,0,0);
	pad8  =  new  TPad("pad8","pad8",0.7500,0.0000,1.0000,0.5000,0,0,0);
	pad1->Draw();pad2->Draw();pad3->Draw();pad4->Draw();pad5->Draw();pad6->Draw();pad7->Draw();pad8->Draw();
	
	// Everything below here makes graphs for each section of the canvas

	pad1->cd();
	TString titledp = "dp Cut";
	cout << "Drawing " << titledp << "..." << endl;
	TH1F *HedpNoCut = new TH1F("HedpNoCut",titledp,400,-0.08,0.08);
	TH1F *HedpCut = new TH1F("HedpCut",titledp,400,-0.08,0.08);
	chainHeR->Draw("ExTgtCor_R.dp>>HedpNoCut", "", "");
	chainHeR->Draw("ExTgtCor_R.dp>>HedpCut", goldR, "");
	HedpNoCut->SetTitle(titledp);
	HedpNoCut->Draw();
	HedpCut->SetLineColor(kBlack);
	HedpCut->SetFillColor(kViolet);
	HedpCut->Draw("same");
	pad1->Update();

	pad2->cd();
	cout << "Drawing Target Cut..." << endl;
	TString titleTarget = "Target Cut";
	TH1F *HeReactZNoCut = new TH1F("HeReactZNoCut",titleTarget,400,-0.3,0.3);
	TH1F *HeReactZCut = new TH1F("HeReactZCut",titleTarget,400,-0.3,0.3);
	chainHeR->Draw("ReactPt_R.z>>HeReactZNoCut", "", "");
	chainHeR->Draw("ReactPt_R.z>>HeReactZCut", targetR, "");
	HeReactZNoCut->SetTitle(titleTarget);
	HeReactZNoCut->Draw();
	HeReactZCut->SetLineColor(kBlack);
	HeReactZCut->SetFillColor(kViolet);
	HeReactZCut->Draw("same");
	pad2->Update();

	pad3->cd();
	cout << "Drawing Theta and Phi Cut..." << endl;
	TString titleThetaPhiNoCut = "Theta and Phi";
	TH2F *HeThetaPhiNoCut = new TH2F("HeThetaPhiNoCut",titleThetaPhiNoCut,100,-0.05,0.05,100,-0.1,0.1);
	chainHeR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeThetaPhiNoCut", targetR, "");
	HeThetaPhiNoCut->SetTitle(titleThetaPhiNoCut);
	HeThetaPhiNoCut->SetStats(kFALSE);
	HeThetaPhiNoCut->Draw("COLZ");
	bottom = new TLine(-phbound,-thbound,phbound,-thbound);
	top = new TLine(-phbound,thbound,phbound,thbound);
	left = new TLine(-phbound,-thbound,-phbound,thbound);
	right = new TLine(phbound,-thbound,phbound,thbound);
	bottom->SetLineColor(kViolet);
	top->SetLineColor(kViolet);
	left->SetLineColor(kViolet);
	right->SetLineColor(kViolet);
	bottom->SetLineWidth(3);
	top->SetLineWidth(3);
	left->SetLineWidth(3);
	right->SetLineWidth(3);
	bottom->Draw("same");
	top->Draw("same");
	left->Draw("same");
	right->Draw("same");
	pad3->Update();

	pad7->cd();
	cout << "Drawing Preshower/Shower Cut..." << endl;
	TString titlePsSh = "Preshower and Shower";
	TH2F *HePsShCut = new TH2F("HePsShCut",titlePsSh,200,1,2500,200,1,1500);
	chainHeR->Draw("R.ps.e:R.sh.e>>HePsShCut", "", "");
	HePsShCut->SetTitle(titlePsSh);
	HePsShCut->SetStats(kFALSE);
	HePsShCut->Draw("COLZ");
	psshcut = new TLine(0,900,450,0);
	psshcut->SetLineColor(kViolet);
	psshcut->SetLineWidth(3);
	psshcut->Draw("same");
	pad4->Update();

	pad4->cd();
	TString titleQ2Nu = "Q2 and Nu";
	TH2F *histQ2Nu = new TH2F("histQ2Nu",titleQ2Nu,200,numin,numax,200,q2min,q2max);
	cout << "Drawing " << titleQ2Nu << "..." << endl;
	chainHeR->Draw("PriKineR.Q2:PriKineR.nu>>histQ2Nu", allcutsR, "");
	histQ2Nu->SetTitle(titleQ2Nu);
	histQ2Nu->SetStats(kFALSE);
	histQ2Nu->Draw("COLZ");
	pad5->Update();

	pad5->cd();
	TString titlecerenkov = "Cerenkov Cut";
	cout << "Drawing " << titlecerenkov << "..." << endl;
	TH1F *histcerenkov = new TH1F("histcerenkov",titlecerenkov,200,-25,2000);
	TH1F *histcerenkovcut = new TH1F("histcerenkovcut",titlecerenkov,200,-25,2000);
	chainHeR->Draw("R.cer.asum_c>>histcerenkov", "", "");
	chainHeR->Draw("R.cer.asum_c>>histcerenkovcut", cerenkov, "");
	histcerenkov->SetTitle(titlecerenkov);
	histcerenkov->SetStats(kFALSE);
	histcerenkovcut->SetFillColor(kViolet);
	histcerenkov->Draw();
	histcerenkovcut->Draw("same");
	pad6->Update();

	pad8->cd();
	cout << "Drawing Preshower/Shower with All Cut..." << endl;
	TString titlePsSh = "Preshower and Shower with all cuts";
	TH2F *HePsShCut = new TH2F("HePsShCut",titlePsSh,200,1,2500,200,1,1500);
	chainHeR->Draw("R.ps.e:R.sh.e>>HePsShCut", allcutsR, "");
	HePsShCut->SetTitle(titlePsSh);
	HePsShCut->SetStats(kFALSE);
	HePsShCut->Draw("COLZ");
	psshcut = new TLine(0,900,450,0);
	psshcut->SetLineColor(kViolet);
	psshcut->SetLineWidth(3);
	psshcut->Draw("same");
	pad4->Update();

	pad6->cd();
	TString titlex = "Bjorken x ";
	titlex += " (x=Q^2/[2m*nu])";
	cout << "Drawing " << titlex << "..." << endl;
	TH1F *histx = new TH1F("histx",titlex,xbjbins,xbjmin,xbjmax);
	TH1F *histxcut = new TH1F("histxcut",titlex,xbjbins,xbjmin,xbjmax);
	histx->Sumw2();
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histx", cutR && kinematicsR && eventtypeR && goldR && targetR && thetaphiR && cerenkov && pssh, "E");
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histxcut", allcutsR, "E");
	histx->Draw();
	histxcut->SetFillColor(kViolet);
	histxcut->Draw("same");
	pad10->Update();

/*	TString imagename = "Asymmetries/Vertical_Target_Asymmetry_for_Q2_of_";
//	TString imagename = "Asymmetries/Left_Only_Vertical_Target_Asymmetry_for_Q2_of_";
	imagename += Q2;
	imagename += ".png";
	c1->Print(imagename);
*/

	cout << "All done!" << endl;


}












