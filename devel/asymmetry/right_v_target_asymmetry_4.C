// #include "AyAnalysis.h"
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;
// Created 07/15/10

void right_v_target_asymmetry_4(){

// Below are for 1st pass, Q2=0.13
/*	TString Q2 = "0.13";
	double q2max = 0.2;
	double q2min = 0.08;
	double numin = 0.02;
	double numax = 0.2;
	int HeRunNumberR = 20460; 
	int endHeRunNumberR = 20511;
*/

/*	TString Q2 = "0.13-test";
	double q2min = 0.08;
	double q2max = 0.2;
	double numin = 0.02;
	double numax = 0.13;
	const int HeRunNumberR = 20475;
	const int endHeRunNumberR = 20489;
*/

// Below are for 3rd pass, Q2=1.0
	TString filename = "Asymmetries/Pions-1-Right_Arm_Vertical_Target_Asymmetry_for_Q2_of_";
	TString Q2 = "1.0";
	filename += Q2;
	TString asymFileName = filename;
	asymFileName += ".txt";
	double q2min = 0.08;
	double q2max = 1.6;
	double numin = 0.02;
	double numax = 0.8;
	int HeRunNumberR = 20579;
//	int endHeRunNumberR = 20582;
	int endHeRunNumberR = 20759;
// NOTE: There is a problem with the charge scalar in runs 20812-20879. When this is fixed,
// uncomment the line below. Until then, we stop at run 20789.
//	int endHeRunNumberR = 20879;


	double bins = 50;
	double xmin = 0.4;
	double xmax = 3.0;
	
	ofstream asymFile;
	asymFile.open(asymFileName);

	const int numOfRuns = endHeRunNumberR - HeRunNumberR;
	const int numVars = 14;
	// infoArray[runNum][0] = Run Number
	// infoArray[runNum][1] = # of Unpolarized Events past cuts
	// infoArray[runNum][2] = # of Spin Up Events past cuts
	// infoArray[runNum][3] = # Spin Down Events past cuts
	// infoArray[runNum][4] = Event-by-event u3c 
	// infoArray[runNum][5] = Event-by-event u3pp + u3pm
	// infoArray[runNum][6] = Event-by-event u3mm + u3mp
	// infoArray[runNum][7] = Error
	// infoArray[runNum][8] = End-of-run u3c
	// infoArray[runNum][9] = End-of-run u3pp + u3pm
	// infoArray[runNum][10] = End-of-run u3mm + u3mp
	// infoArray[runNum][11] = # of total T2 events 
	// infoArray[runNum][12] = # of Spin Up T2 events
	// infoArray[runNum][13] = # of Spin Down T2 events
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
	TCut targetR = "ReactPt_R.z>-0.155 && ReactPt_R.z<0.175";
	double thbound = 0.07;
	double phbound = 0.03;
	TString thetaphiRStr = "abs(ExTgtCor_R.ph)<";
	thetaphiRStr += phbound;
	thetaphiRStr += " && abs(ExTgtCor_R.th)<";
	thetaphiRStr += thbound;
	TCut thetaphiR = thetaphiRStr;
	TCut xbj = "PriKineRHe3.x_bj<2";
	TCut pssh = "(R.ps.e + 2*R.sh.e)<900 && R.ps.e>1 && R.sh.e>1";
	TCut cerenkov = "R.cer.asum_c>150";

/*	TCut cutR = "he3R.IsSpinValid==1";
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
		if(thisHeRunNumberR==20589){thisHeRunNumberR=20596;}
		if(thisHeRunNumberR==20590){thisHeRunNumberR=20596;}
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
	double isSpinValid;
	double qsquare;
	double nu;
	double evtypebits;
	double dp;
	double reactz;
	double th;
	double ph;
	double x_bj;
	double she;
	double pse;
	double cerasum;
	double runNum;
	double spin;
	int runNumber;
	double u3c;
	double u3pp;
	double u3pm;
	double u3mm;
	double u3mp;

/*	numberOfEvents = int(chainHeR->GetEntries());
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

	cout << "Number of events: " << numberOfEvents << endl;
	chainHeR->GetEntry(1);
	runNumber = int(runNum);
	int prevRunNumber = runNumber;
	int runNumPlace = 0;
	infoArray[runNumPlace][0] = runNumber;
	double prevu3c = u3c;
	double u3p = 0;
	double u3m = 0;
	double u3c_real = 0;
	double u3c_real_for_event = 0;
	double endOfRunu3c = 0;
	double endOfRunu3p = 0;
	double endOfRunu3m = 0;
	int realNumOfRuns = 1;
	double thisNp = 0;
	double thisNm = 0;
	double thisCp = 0;
	double thisCm = 0;
	double thisLTp = 0;
	double thisLTm = 0;
	for (int i=0; i<numberOfEvents; i++)
	{
		chainHeR->GetEntry(i);
		runNumber = int(runNum);
		u3c_real_for_event = u3c - prevu3c;

		if (i%10000 == 0)
		{
			cout << "Event Number " << i << ", Run Number " << runNumber << endl;
			cout << "u3c: " << u3c << "  u3pp: " << u3pp << "  u3pm: " << u3pm << "  u3mm: " << u3mm << "  u3mp: " << u3mp << " Error: " << infoArray[runNumPlace][7] << ", evtypebits = " << evtypebits << endl;
		}
		if (runNumber > prevRunNumber)
		{
			u3c_real = 0;
			u3p = 0;
			u3m = 0;
			chainHeR->GetEntry(i-1);
			endOfRunu3c = u3c;
			endOfRunu3p = u3pp + u3pm;
			endOfRunu3m = u3mm + u3mp;
			infoArray[runNumPlace][8] = endOfRunu3c;
			infoArray[runNumPlace][9] = endOfRunu3p;
			infoArray[runNumPlace][10] = endOfRunu3m;

			thisNp = infoArray[runNumPlace][2];
			thisNm = infoArray[runNumPlace][3];
			thisCp = infoArray[runNumPlace][9];
			thisCm = infoArray[runNumPlace][10];
			thisLTp = infoArray[runNumPlace][12]/(infoArray[runNumPlace][11] + 1e-15);
			thisLTm = infoArray[runNumPlace][13]/(infoArray[runNumPlace][11] + 1e-15);
			
			// Error = 2*(Nm*sqrt(Np) + Np*sqrt(Nm))/((Cp*Lp)*(Cm*Lm)*(Np/(Cp*Lp)+Nm/(Cm*Lm))^2)
			infoArray[runNumPlace][7] = 2*(thisNm*sqrt(thisNp) + thisNp*sqrt(thisNm))/((thisCp*thisLTp)*(thisCm*thisLTm)*pow(thisNp/(thisCp*thisLTp)+thisNm/(thisCm*thisLTm),2));
			// Error = (2*Nm/((Cp*Lp)*(Cm*Lm)*(Np/(Cp*Lp)+Nm/(Cm*Lm))^2))*errNp + (2*Np/((Cp*Lp)*(Cm*Lm)*(Np/(Cp*Lp)+Nm/(Cm*Lm))^2))*errNm
//			infoArray[runNumPlace][7] = (2*infoArray[runNumPlace][3]/((infoArray[runNumPlace][9]*thisLTp)*(infoArray[runNumPlace][10]*thisLTm)*pow(infoArray[runNumPlace][2]/(infoArray[runNumPlace][9]*thisLTp)+infoArray[runNumPlace][3]/(infoArray[runNumPlace][10]*thisLTm),2)))*sqrt(infoArray[runNumPlace][2]) + (2*infoArray[runNumPlace][2]/((infoArray[runNumPlace][9]*thisLTp)*(infoArray[runNumPlace][10]*thisLTm)*pow(infoArray[runNumPlace][2]/(infoArray[runNumPlace][9]*thisLTp)+infoArray[runNumPlace][3]/(infoArray[runNumPlace][10]*thisLTm),2)))*sqrt(infoArray[runNumPlace][3]);
			

//			infoArray[runNumPlace][7] = 1/(sqrt(infoArray[runNumPlace][1]));
			
//			ratio = ((infoArray[runNumPlace][12]/infoArray[runNumPlace][11])*infoArray[runNumPlace][9])/((infoArray[runNumPlace][13]/infoArray[runNumPlace][11])*infoArray[runNumPlace][10]+1e-15);
//			infoArray[runNumPlace][7] = 2*ratio*sqrt(infoArray[runNumPlace][2]*infoArray[runNumPlace][2]*infoArray[runNumPlace][3]+infoArray[runNumPlace][3]*infoArray[runNumPlace][3]*infoArray[runNumPlace][2])/pow(infoArray[runNumPlace][2]+ratio*infoArray[runNumPlace][3]+1e-15,2);

			cout << "Ending Run Number " << infoArray[runNumPlace][0] << ", u3c = " << infoArray[runNumPlace][8] << ", u3p = " << infoArray[runNumPlace][9] << ", u3m = " << infoArray[runNumPlace][10] << ", Error = " << infoArray[runNumPlace][7] << endl;
			chainHeR->GetEntry(i);
			runNumPlace++;
			prevRunNumber = runNumber;
			infoArray[runNumPlace][0] = runNumber;
			realNumOfRuns++;
		}
		if (i==(numberOfEvents-1))
		{
			chainHeR->GetEntry(i-1);
			endOfRunu3c = u3c;
			endOfRunu3p = u3pp + u3pm;
			endOfRunu3m = u3mm + u3mp;
			infoArray[runNumPlace][8] = endOfRunu3c;
			infoArray[runNumPlace][9] = endOfRunu3p;
			infoArray[runNumPlace][10] = endOfRunu3m;

			thisNp = infoArray[runNumPlace][2];
			thisNm = infoArray[runNumPlace][3];
			thisCp = infoArray[runNumPlace][9];
			thisCm = infoArray[runNumPlace][10];
			thisLTp = infoArray[runNumPlace][12]/(infoArray[runNumPlace][11] + 1e-15);
			thisLTm = infoArray[runNumPlace][13]/(infoArray[runNumPlace][11] + 1e-15);
			
			// Error = 2*(Nm*sqrt(Np) + Np*sqrt(Nm))/((Cp*Lp)*(Cm*Lm)*(Np/(Cp*Lp)+Nm/(Cm*Lm))^2)
			infoArray[runNumPlace][7] = 2*(thisNm*sqrt(thisNp) + thisNp*sqrt(thisNm))/((thisCp*thisLTp)*(thisCm*thisLTm)*pow(thisNp/(thisCp*thisLTp)+thisNm/(thisCm*thisLTm),2));

			// Error = (2*Nm/((Cp*Lp)*(Cm*Lm)*(Np/(Cp*Lp)+Nm/(Cm*Lm))^2))*errNp + (2*Np/((Cp*Lp)*(Cm*Lm)*(Np/(Cp*Lp)+Nm/(Cm*Lm))^2))*errNm
//			infoArray[runNumPlace][7] = (2*infoArray[runNumPlace][3]/((infoArray[runNumPlace][9]*thisLTp)*(infoArray[runNumPlace][10]*thisLTm)*pow(infoArray[runNumPlace][2]/(infoArray[runNumPlace][9]*thisLTp)+infoArray[runNumPlace][3]/(infoArray[runNumPlace][10]*thisLTm),2)))*sqrt(infoArray[runNumPlace][2]) + (2*infoArray[runNumPlace][2]/((infoArray[runNumPlace][9]*thisLTp)*(infoArray[runNumPlace][10]*thisLTm)*pow(infoArray[runNumPlace][2]/(infoArray[runNumPlace][9]*thisLTp)+infoArray[runNumPlace][3]/(infoArray[runNumPlace][10]*thisLTm),2)))*sqrt(infoArray[runNumPlace][3]);
			
//			infoArray[runNumPlace][7] = 1/(sqrt(infoArray[runNumPlace][1]));
//			ratio = ((infoArray[runNumPlace][12]/infoArray[runNumPlace][11])*infoArray[runNumPlace][9])/((infoArray[runNumPlace][13]/infoArray[runNumPlace][11])*infoArray[runNumPlace][10] + 1e-15);
//			infoArray[runNumPlace][7] = 2*ratio*sqrt(infoArray[runNumPlace][2]*infoArray[runNumPlace][2]*infoArray[runNumPlace][3]+infoArray[runNumPlace][3]*infoArray[runNumPlace][3]*infoArray[runNumPlace][2])/pow(infoArray[runNumPlace][2]+ratio*infoArray[runNumPlace][3]+1e-15,2);
			cout << "Ending Run Number " << infoArray[runNumPlace][0] << ", u3c = " << infoArray[runNumPlace][8] << ", u3p = " << infoArray[runNumPlace][9] << ", u3m = " << infoArray[runNumPlace][10] << ", Error = " << infoArray[runNumPlace][7] << endl;
		}


		if ((isSpinValid==1)&&(qsquare<10)&&(nu<10)&&(dp>-0.04)&&(dp<0.058)&&(reactz>-0.155)&&(reactz<0.175)&&(abs(th)<0.07)&&(abs(ph)<0.03)&&(x_bj<2)&&((pse+(2*she))<900)&&(pse>1)&&(she>1)&&(cerasum>150))
		{
			u3c_real = u3c_real + u3c_real_for_event;
			infoArray[runNumPlace][1]++;
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
			if (int(evtypebits)==2)
			{
				infoArray[runNumPlace][11]++;
				if (int(spin)==1){ infoArray[runNumPlace][12]++;}
				if (int(spin)==-1){ infoArray[runNumPlace][13]++;}
			}
		}

		prevu3c = u3c;
	}
	cout << "Number of Runs: " << numOfRuns << endl;
	cout << "Run #	# Unpolarized	# Spin Up	# Spin Down	Total C		C for up*	C for down*	Error	C for up	C for down	Total T1	# Up T2	# Down T2" << endl;
	for (int i=0; i<numOfRuns; i++)
	{
		for (int j=0; j<numVars; j++)
		{
			cout << infoArray[i][j] << "	";
		}
		cout << endl;
	}
	cout << "* = Done by adding event-by-event, which might not be working" << endl;
// ****************************************************************************************************************

	gStyle->SetPalette(1);
	gStyle->SetOptFit(0001);

	const int theRealNumOfRuns = realNumOfRuns;
	TCanvas *asymCanvas = new TCanvas("asymCanvas","Right Arm Asymmetry",800,600); //x,y
	asymCanvas->cd();
	asymCanvas->SetGrid();
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
		if (infoArray[i][9] != 0)
		{
			if(infoArray[i][10] != 0)
			{
				if(infoArray[i][11] !=0)
				{
					posStuff = (infoArray[i][2] / (infoArray[i][9] * (infoArray[i][12]/infoArray[i][11])));
					negStuff = (infoArray[i][3] / (infoArray[i][10] * (infoArray[i][13]/infoArray[i][11])));
					y[i] = ((posStuff - negStuff) / (posStuff + negStuff));
				}
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
		cout << "Run Number: " << infoArray[i][0] << " , # Spin Up Events: " << infoArray[i][2] << " , # Spin Down Events: " << infoArray[i][3] << ", Asymmetry = " << y[i] << " , Error = " << errory[i] << endl;
		asymFile << "Run Number: ";
		asymFile << infoArray[i][0];
		asymFile << ", # Spin Up Events: ";
		asymFile << infoArray[i][2];
		asymFile << ", # Spin Down Events: ";
		asymFile << infoArray[i][3];
		asymFile << " , Asymmetry = ";
		asymFile << y[i];
		asymFile << " , Error = ";
		asymFile << errory[i];
		asymFile << "\n";
	}
	asymGraph = new TGraphErrors(numOfRuns, x, y, errorx, errory);
	asymGraph->SetMarkerStyle(21);
	asymGraph->SetMarkerColor(4);
	asymGraph->SetTitle("Raw Target SSA");
	asymTestHist = new TH2F("asymTestHist","Asymmetry Test",realNumOfRuns,HeRunNumberR-1,endHeRunNumberR+1,100,minError,maxError);
//	asymTestHist = new TH2F("asymTestHist","Asymmetry Test",realNumOfRuns,HeRunNumberR-1,endHeRunNumberR+1,100,-0.006,0.003);
	asymTestHist->SetStats(kFALSE);
	asymTestHist->Draw();
	cout << "Fit min = " << infoArray[0][0] << "; Fit max = " << infoArray[realNumOfRuns - 1][0] << endl;
	TF1 *fitAsymGraph = new TF1("fitAsymGraph", "[0]", infoArray[0][0], infoArray[realNumOfRuns - 1][0]);
	asymGraph->Draw("P");
	fitAsymGraph->SetLineColor(kBlue);
	asymGraph->Fit("fitAsymGraph","R");
	asymCanvas->Update();
*/

	// Defines Canvas
	TCanvas *cutsCanvas = new TCanvas("cutsCanvas","Asymmetry Cuts",1360,768); //x,y
	pad1  =  new  TPad("pad1","pad1",0.0000,0.5000,0.2500,1.0000,0,0,0);
	pad2  =  new  TPad("pad2","pad2",0.2500,0.5000,0.5000,1.0000,0,0,0);
	pad3  =  new  TPad("pad3","pad3",0.5000,0.5000,0.7500,1.0000,0,0,0);
	pad4  =  new  TPad("pad4","pad4",0.7500,0.5000,1.0000,1.0000,0,0,0);
	pad5  =  new  TPad("pad5","pad5",0.0000,0.0000,0.2500,0.5000,0,0,0);
	pad6  =  new  TPad("pad6","pad6",0.2500,0.0000,0.5000,0.5000,0,0,0);
	pad7  =  new  TPad("pad7","pad7",0.5000,0.0000,0.7500,0.5000,0,0,0);
	pad8  =  new  TPad("pad8","pad8",0.7500,0.0000,1.0000,0.5000,0,0,0);
	pad1->Draw();pad2->Draw();pad3->Draw();pad4->Draw();pad5->Draw();pad6->Draw();pad7->Draw();pad8->Draw();
	
	// Defines Canvas
/*	TCanvas *cutsCanvas = new TCanvas("cutsCanvas","Asymmetry",1360,768); //x,y
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
*/


	// Everything below here makes graphs for each section of the canvas
/*
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
//	chainHeR->Draw("R.ps.e:R.sh.e>>HePsShCut", cutsR && cerenkov, "");
	HePsShCut->SetTitle(titlePsSh);
	HePsShCut->SetStats(kFALSE);
	HePsShCut->Draw("COLZ");
	psshcut = new TLine(0,900,450,0);
	psshcut->SetLineColor(kViolet);
	psshcut->SetLineWidth(3);
	psshcut->Draw("same");
	pad7->Update();

	pad4->cd();
	TString titleQ2Nu = "Q2 and Nu";
	TH2F *histQ2Nu = new TH2F("histQ2Nu",titleQ2Nu,200,numin,numax,200,q2min,q2max);
	cout << "Drawing " << titleQ2Nu << "..." << endl;
	chainHeR->Draw("PriKineR.Q2:PriKineR.nu>>histQ2Nu", allcutsR, "");
	histQ2Nu->SetTitle(titleQ2Nu);
	histQ2Nu->SetStats(kFALSE);
	histQ2Nu->Draw("COLZ");
	pad4->Update();

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
	pad5->Update();

	pad8->cd();
	cout << "Drawing Preshower/Shower with All Cut..." << endl;
	TString titlePsSh = "Preshower and Shower with all cuts";
	TH2F *HePsShCut = new TH2F("HePsShCut",titlePsSh,200,1,2500,200,1,1500);
//	chainHeR->Draw("R.ps.e:R.sh.e>>HePsShCut", "", "");
	chainHeR->Draw("R.ps.e:R.sh.e>>HePsShCut", allcutsR, "");
	HePsShCut->SetTitle(titlePsSh);
	HePsShCut->SetStats(kFALSE);
	HePsShCut->Draw("COLZ");
	psshcut = new TLine(0,900,450,0);
	psshcut->SetLineColor(kViolet);
	psshcut->SetLineWidth(3);
	psshcut->Draw("same");
	pad8->Update();

	pad6->cd();
	TString titlex = "Bjorken x ";
	titlex += " (x=Q^2/[2m*nu])";
	cout << "Drawing " << titlex << "..." << endl;
	TH1F *histx = new TH1F("histx",titlex,bins,xmin,xmax);
	TH1F *histxcut = new TH1F("histxcut",titlex,bins,xmin,xmax);
	histx->Sumw2();
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histx", cutR && kinematicsR && eventtypeR && goldR && targetR && thetaphiR && cerenkov && pssh, "E");
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histxcut", allcutsR, "E");
	histx->Draw();
	histxcut->SetFillColor(kViolet);
	histxcut->Draw("same");
	pad6->Update();
*/

// Everything below here makes graphs for each section of the canvas. These are set
// to include all cuts for all plots to look at the weird behavior in the Pion plots
	gStyle->SetPalette(1);
	gStyle->SetOptFit(0001);


	pad1->cd();
	TString titledp = "dp, All Cuts";
	cout << "Drawing " << titledp << "..." << endl;
	TH1F *HedpCut = new TH1F("HedpCut",titledp,400,-0.1,0.1);
	chainHeR->Draw("ExTgtCor_R.dp>>HedpCut", allcutsR, "");
	HedpCut->SetLineColor(kBlack);
	HedpCut->SetFillColor(kViolet);
	HedpCut->Draw();
	pad1->Update();

	pad2->cd();
/*	cout << "Drawing Target Cut..." << endl;
	TString titleTarget = "Target, All Cuts";
	chainHeR->Draw("ReactPt_R.z>>HeReactZCut", allcutsR, "");
	HeReactZCut->SetLineColor(kBlack);
	HeReactZCut->SetFillColor(kViolet);
	HeReactZCut->Draw();
	pad2->Update();
*/	cout << "Drawing Beta..." << endl;
	TString titleTarget = "Beta, All Cuts";
	TH1F *HeReactZCut = new TH1F("HeReactZCut",titleTarget,100,0,0.2);
	chainHeR->Draw("R.tr.beta>>HeReactZCut", allcutsR, "");
	HeReactZCut->SetLineColor(kBlack);
	HeReactZCut->SetFillColor(kViolet);
	HeReactZCut->Draw();
	pad2->Update();


	pad3->cd();
	cout << "Drawing Theta and Phi Cut..." << endl;
	TString titleThetaPhiNoCut = "Theta and Phi, All Cuts";
	TH2F *HeThetaPhiNoCut = new TH2F("HeThetaPhiNoCut",titleThetaPhiNoCut,100,-0.05,0.05,100,-0.1,0.1);
	chainHeR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeThetaPhiNoCut", allcutsR, "");
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
	TString titlePsSh = "Preshower and Shower, No Cuts";
	TH2F *HePsShCut = new TH2F("HePsShCut",titlePsSh,200,1,2500,200,1,1500);
	chainHeR->Draw("R.ps.e:R.sh.e>>HePsShCut", "", "");
//	chainHeR->Draw("R.ps.e:R.sh.e>>HePsShCut", allcutsR, "");
	HePsShCut->SetTitle(titlePsSh);
	HePsShCut->SetStats(kFALSE);
	HePsShCut->Draw("COLZ");
	psshcut = new TLine(0,900,450,0);
	psshcut->SetLineColor(kViolet);
	psshcut->SetLineWidth(3);
	psshcut->Draw();
	pad7->Update();

	pad4->cd();
	TString titleQ2Nu = "Q2 and Nu";
	TH2F *histQ2Nu = new TH2F("histQ2Nu",titleQ2Nu,200,numin,numax,200,q2min,q2max);
	cout << "Drawing " << titleQ2Nu << "..." << endl;
	chainHeR->Draw("PriKineR.Q2:PriKineR.nu>>histQ2Nu", allcutsR, "");
	histQ2Nu->SetTitle(titleQ2Nu);
	histQ2Nu->SetStats(kFALSE);
	histQ2Nu->Draw("COLZ");
	pad4->Update();

	pad5->cd();
	TString titlecerenkov = "Cerenkov, All Cuts";
	cout << "Drawing " << titlecerenkov << "..." << endl;
	TH1F *histcerenkovcut = new TH1F("histcerenkovcut",titlecerenkov,200,-25,2000);
	chainHeR->Draw("R.cer.asum_c>>histcerenkovcut", allcutsR, "");
	histcerenkovcut->SetFillColor(kViolet);
	histcerenkovcut->Draw();
	pad5->Update();

	pad8->cd();
	cout << "Drawing Preshower/Shower with All Cuts..." << endl;
	TString titlePsSh = "Preshower and Shower with all cuts";
	TH2F *HePsShCut = new TH2F("HePsShCut",titlePsSh,200,1,2500,200,1,1500);
//	chainHeR->Draw("R.ps.e:R.sh.e>>HePsShCut", "", "");
	chainHeR->Draw("R.ps.e:R.sh.e>>HePsShCut", allcutsR, "");
	HePsShCut->SetTitle(titlePsSh);
	HePsShCut->SetStats(kFALSE);
	HePsShCut->Draw("COLZ");
	psshcut = new TLine(0,900,450,0);
	psshcut->SetLineColor(kViolet);
	psshcut->SetLineWidth(3);
	psshcut->Draw("same");
	pad8->Update();

	pad6->cd();
	TString titlex = "Bjorken x ";
	titlex += " (x=Q^2/[2m*nu])";
	cout << "Drawing " << titlex << "..." << endl;
	TH1F *histxcut = new TH1F("histxcut",titlex,bins,xmin,xmax);
//	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histx", cutR && kinematicsR && eventtypeR && goldR && targetR && thetaphiR && cerenkov && pssh, "E");
	chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>histxcut", allcutsR, "E");
	histxcut->SetFillColor(kViolet);
	histxcut->Draw();
	pad6->Update();


/*



	TString imagename = filename;
	imagename += ".png";
	asymCanvas->Print(imagename);
	TString cutsimagename = filename;
	cutsimagename += Q2;
	cutsimagename += "_cuts.png";
	cutsCanvas->Print(cutsimagename);
	asymFile.close();
*/
	cout << "All done!" << endl;


}












