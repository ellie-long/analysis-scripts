// This was a program to chain together different
// root files and look at graphs from them.
// In particular, it will output plots of x=Q2/(2m*nu)
// of 3He and 12C and of 12C/3He to look for short
// range correlation in E05-102 and E08-005.
//
// Elena Long (ellie@jlab.org)
//
// Major updates: 2010-09-13
// Updates to: 
//		Scale with Charge
//		Include Target densities
//		Include livetime
//		Yield is now per nucleon




#include <iostream>
#include <fstream>
using namespace std;

void src_fit2(){

// Use just this group to online look at RHRS runs
// Be sure to changed your xbjCanvas titles
/*	int CRunNumber=1684;
	int endCRunNumber=1684;
	int AyHeRunNumber=1685;
	int endAyHeRunNumber=1685;
// ************************************************
*/

	int CRunNumber=1699;
//	int endCRunNumber=1699;
	int endCRunNumber=1828;
	int AyHeRunNumber=1686;
//	int endAyHeRunNumber=1686;
	int endAyHeRunNumber=1882;
	TString Q2 = "1.0";
	//Range is of the form (bins, start, end)
	//  TString range = "(800,0.5,4.0)";
	double bins = 50;
	double xmin = 0.6;
	double xmax = 1.7;
	TString title = "12C_over_3He_x-Q2_of_";
	title += Q2;
	title += "-C_Runs_";
	title += CRunNumber;
	title += "-";
	title += endCRunNumber;
	title += "_AyHe_Runs_";
	title += AyHeRunNumber;
	title += "-";
	title += endAyHeRunNumber;


// Use just this group to online look at just LHRS runs
// Be sure to changed your xbjCanvas titles
/*	int CRunNumberR=20590;
	int endCRunNumberR=20590;
	int AyHeRunNumberR=20589;
	int endAyHeRunNumberR=20589;
	int eedHeRunNumberR=22392;
	int endeedHeRunNumberR=22392;
// ****************************************************
*/

	int CRunNumberR=20591;
	int endCRunNumberR=22461;
//	int endCRunNumberR=20592;
	int AyHeRunNumberR=20596;
//	int endAyHeRunNumberR=20597;
	int endAyHeRunNumberR=20789;
	int eedHeRunNumberR=22393;
//	int endeedHeRunNumberR=22394;
	int endeedHeRunNumberR=22489;
	TString titleR = "12C_over_3He_x-Q2_of_";
	titleR += Q2;
	titleR += "-C_Runs_";
	titleR += CRunNumberR;
	titleR += "-";
	titleR += endCRunNumberR;
	titleR += "_He_Runs_";
	titleR += AyHeRunNumberR;
	titleR += "-";
	titleR += endeedHeRunNumberR;

// ***** Define densities (# atoms/cm^3) and target thickness (cm) *******
	// The second number (3) in zHe is to scale per nucleon
	double zHe = 32*3;
	// zC is the number of foils since rhoC is actually density*length of 1 foil
	// The second number (12) in zC is to scale per nucleon
	double zC = 5*12;
	double rhoAyHe = 3.972e20;
	double rhoeedHe = 2.910e20;
	double rhoC = 2.394e21;
// *****************************************************************


	TString justAyOutFileName = "output_files/justAy";
	justAyOutFileName += title;
	justAyOutFileName += ".dat";
	ofstream AyOutFile;
	AyOutFile.open(justAyOutFileName);

	TString justeedOutFileName = "output_files/justeed";
	justeedOutFileName += title;
	justeedOutFileName += ".dat";
	ofstream eedOutFile;
	eedOutFile.open(justeedOutFileName);

	TString justAyeedOutFileName = "output_files/justAyeed";
	justAyeedOutFileName += title;
	justAyeedOutFileName += ".dat";
	ofstream AyeedOutFile;
	AyeedOutFile.open(justAyeedOutFileName);



	TString outFileName = "output_files/";
	outFileName += titleR;
	outFileName += ".txt";

	ofstream outFile;
	outFile.open(outFileName);

	TCut cut = "";  
	TCut kinematics = "PriKineL.Q2<10 && GoodElectron==1 && PriKineL.nu<10";
//	TCut eventtype = "DL.evtypebits&(1<<1)>0";
	TCut eventtype = "(DL.evtypebits&8)==8";
	TCut eventtype = "";
//	TCut dp = "ExTgtCor_L.dp>-0.04 && ExTgtCor_L.dp<0.053";
	TCut dp = "ExTgtCor_L.dp>-0.04 && ExTgtCor_L.dp<0.04";
//	TCut dp = "ExTgtCor_L.dp<0.04";
	TCut target = "ReactPt_L.z>-0.15 && ReactPt_L.z<0.17";
        double thhighbound = 0.06;
        double thlowbound = -0.05;
        double phbound = 0.03;
        TString thetaphiRStr = "abs(ExTgtCor_L.ph)<";
        thetaphiRStr += phbound;
        thetaphiRStr += " && ExTgtCor_L.th<";
        thetaphiRStr += thhighbound;
        thetaphiRStr += " && ExTgtCor_L.th>";
        thetaphiRStr += thlowbound;
        TCut thph = thetaphiRStr;
	TCut tracks = "L.tr.n==1 && L.vdc.u1.nhit>3 && L.vdc.u1.nhit<7 && L.vdc.u2.nhit>3 && L.vdc.u2.nhit<7 && L.vdc.v1.nhit>3 && L.vdc.v1.nhit<7 && L.vdc.v2.nhit>3 && L.vdc.v2.nhit<7";
	TCut xbj = "";
        TCut pssh = "(L.prl1.e + L.prl2.e)>900 && L.prl1.e>1 && L.prl2.e>1";
        TCut cerenkov = "L.cer.asum_c>150";

//	TCut cut = "";
//	TCut eventtype = "";
//	TCut target = "";
//	TCut thph = "";
//	TCut dp = "";

	TCut cuts = kinematics && target && thph && dp && eventtype && tracks && xbj && pssh && cerenkov;


	TCut cutR = "";  
	TCut kinematicsR = "PriKineR.Q2<10 && GoodElectron==1 && PriKineR.nu<10";
//	TCut eventtypeR = "D.evtypebits&(1<<1)>0";
	TCut eventtypeR = "(D.evtypebits&2)==2";
//	TCut dpR = "ExTgtCor_R.dp>-0.04 && ExTgtCor_R.dp<0.053";
	TCut dpR = "ExTgtCor_R.dp>-0.04 && ExTgtCor_R.dp<0.04";
//	TCut dpR = "ExTgtCor_R.dp>-0.04";
	TCut tagetR = "ReactPt_R.z>-0.15 && ReactPt_R.z<0.17";
        double thboundR = 0.07;
        double phboundR = 0.03;
        TString thetaphiRStr = "abs(ExTgtCor_R.ph)<";
        thetaphiRStr += phboundR;
        thetaphiRStr += " && abs(ExTgtCor_R.th)<";
        thetaphiRStr += thboundR;
        TCut thphR = thetaphiRStr;
	TCut tracksR = "R.tr.n==1 && R.vdc.u1.nhit>3 && R.vdc.u1.nhit<7 && R.vdc.u2.nhit>3 && R.vdc.u2.nhit<7 && R.vdc.v1.nhit>3 && R.vdc.v1.nhit<7 && R.vdc.v2.nhit>3 && R.vdc.v2.nhit<7";
	TCut xbjR = "";
        TCut psshR = "(R.ps.e + 2*R.sh.e)>900 && R.ps.e>1 && R.sh.e>1";
        TCut cerenkovR = "R.cer.asum_c>150";

//	TCut cutR = "";
//	TCut eventtypeR = "";
//	TCut tagetR = "";
//	TCut thphR = "";
//	TCut dpR = "";

	TCut cutsR = kinematicsR && tagetR && thphR && dpR && eventtypeR && tracksR && xbjR && psshR && cerenkovR;


        const int AyHeNumOfRuns = endAyHeRunNumber - AyHeRunNumber + 5;
        const int AyHeNumVars = 14;
        // AyHeInfoArray[runNum][0] = Run Number
        // AyHeInfoArray[runNum][1] = # of Unpolarized Events past cuts
        // AyHeInfoArray[runNum][2] = # of Spin Up Events past cuts
        // AyHeInfoArray[runNum][3] = # Spin Down Events past cuts
        // AyHeInfoArray[runNum][4] = Event-by-event u3c 
        // AyHeInfoArray[runNum][5] = Event-by-event u3pp + u3pm
        // AyHeInfoArray[runNum][6] = Event-by-event u3mm + u3mp
        // AyHeInfoArray[runNum][7] = Error
        // AyHeInfoArray[runNum][8] = End-of-run u3c
        // AyHeInfoArray[runNum][9] = End-of-run u3pp + u3pm
        // AyHeInfoArray[runNum][10] = End-of-run u3mm + u3mp
        // AyHeInfoArray[runNum][11] = # of total T2 events 
        // AyHeInfoArray[runNum][12] = # of Spin Up T2 events
        // AyHeInfoArray[runNum][13] = # of Spin Down T2 events
        double AyHeInfoArray[AyHeNumOfRuns][AyHeNumVars];
        for (int i=0; i<AyHeNumOfRuns; i++)
        {
                for (int j=0; j<AyHeNumVars; j++)
                {
                        AyHeInfoArray[i][j]=0;
                }
        }

        const int CNumOfRuns = endCRunNumber - CRunNumber + 5;
        const int CNumVars = 14;
        // CInfoArray[runNum][0] = Run Number
        // CInfoArray[runNum][1] = # of Unpolarized Events past cuts
        // CInfoArray[runNum][2] = # of Spin Up Events past cuts
        // CInfoArray[runNum][3] = # Spin Down Events past cuts
        // CInfoArray[runNum][4] = Event-by-event u3c 
        // CInfoArray[runNum][5] = Event-by-event u3pp + u3pm
        // CInfoArray[runNum][6] = Event-by-event u3mm + u3mp
        // CInfoArray[runNum][7] = Error
        // CInfoArray[runNum][8] = End-of-run u3c
        // CInfoArray[runNum][9] = End-of-run u3pp + u3pm
        // CInfoArray[runNum][10] = End-of-run u3mm + u3mp
        // CInfoArray[runNum][11] = # of total T2 events 
        // CInfoArray[runNum][12] = # of Spin Up T2 events
        // CInfoArray[runNum][13] = # of Spin Down T2 events
        double CInfoArray[CNumOfRuns][CNumVars];
        for (int i=0; i<CNumOfRuns; i++)
        {
                for (int j=0; j<CNumVars; j++)
                {
                        CInfoArray[i][j]=0;
                }
        }

        const int AyHeNumOfRunsR = endAyHeRunNumberR - AyHeRunNumberR + 5;
        const int AyHeNumVarsR = 14;
        // AyHeInfoArrayR[runNum][0] = Run NumberR
        // AyHeInfoArrayR[runNum][1] = # of Unpolarized Events past cuts
        // AyHeInfoArrayR[runNum][2] = # of Spin Up Events past cuts
        // AyHeInfoArrayR[runNum][3] = # Spin Down Events past cuts
        // AyHeInfoArrayR[runNum][4] = Event-by-event u3c 
        // AyHeInfoArrayR[runNum][5] = Event-by-event u3pp + u3pm
        // AyHeInfoArrayR[runNum][6] = Event-by-event u3mm + u3mp
        // AyHeInfoArrayR[runNum][7] = Error
        // AyHeInfoArrayR[runNum][8] = End-of-run u3c
        // AyHeInfoArrayR[runNum][9] = End-of-run u3pp + u3pm
        // AyHeInfoArrayR[runNum][10] = End-of-run u3mm + u3mp
        // AyHeInfoArrayR[runNum][11] = # of total T2 events 
        // AyHeInfoArrayR[runNum][12] = # of Spin Up T2 events
        // AyHeInfoArrayR[runNum][13] = # of Spin Down T2 events
        double AyHeInfoArrayR[AyHeNumOfRunsR][AyHeNumVarsR];
        for (int i=0; i<AyHeNumOfRunsR; i++)
        {
                for (int j=0; j<AyHeNumVarsR; j++)
                {
                        AyHeInfoArrayR[i][j]=0;
                }
        }

        const int eedHeNumOfRunsR = endeedHeRunNumberR - eedHeRunNumberR + 5;
        const int eedHeNumVarsR = 14;
        // eedHeInfoArrayR[runNum][0] = Run NumberR
        // eedHeInfoArrayR[runNum][1] = # of Unpolarized Events past cuts
        // eedHeInfoArrayR[runNum][2] = # of Spin Up Events past cuts
        // eedHeInfoArrayR[runNum][3] = # Spin Down Events past cuts
        // eedHeInfoArrayR[runNum][4] = Event-by-event u3c 
        // eedHeInfoArrayR[runNum][5] = Event-by-event u3pp + u3pm
        // eedHeInfoArrayR[runNum][6] = Event-by-event u3mm + u3mp
        // eedHeInfoArrayR[runNum][7] = Error
        // eedHeInfoArrayR[runNum][8] = End-of-run u3c
        // eedHeInfoArrayR[runNum][9] = End-of-run u3pp + u3pm
        // eedHeInfoArrayR[runNum][10] = End-of-run u3mm + u3mp
        // eedHeInfoArrayR[runNum][11] = # of total T2 events 
        // eedHeInfoArrayR[runNum][12] = # of Spin Up T2 events
        // eedHeInfoArrayR[runNum][13] = # of Spin Down T2 events
        double eedHeInfoArrayR[eedHeNumOfRunsR][eedHeNumVarsR];
        for (int i=0; i<eedHeNumOfRunsR; i++)
        {
                for (int j=0; j<eedHeNumVarsR; j++)
                {
                        eedHeInfoArrayR[i][j]=0;
                }
        }



        const int CNumOfRunsR = endCRunNumberR - CRunNumberR + 5;
        const int CNumVarsR = 14;
        // CInfoArrayR[runNum][0] = Run NumberR
        // CInfoArrayR[runNum][1] = # of Unpolarized Events past cuts
        // CInfoArrayR[runNum][2] = # of Spin Up Events past cuts
        // CInfoArrayR[runNum][3] = # Spin Down Events past cuts
        // CInfoArrayR[runNum][4] = Event-by-event u3c 
        // CInfoArrayR[runNum][5] = Event-by-event u3pp + u3pm
        // CInfoArrayR[runNum][6] = Event-by-event u3mm + u3mp
        // CInfoArrayR[runNum][7] = Error
        // CInfoArrayR[runNum][8] = End-of-run u3c
        // CInfoArrayR[runNum][9] = End-of-run u3pp + u3pm
        // CInfoArrayR[runNum][10] = End-of-run u3mm + u3mp
        // CInfoArrayR[runNum][11] = # of total T2 events 
        // CInfoArrayR[runNum][12] = # of Spin Up T2 events
        // CInfoArrayR[runNum][13] = # of Spin Down T2 events
        double CInfoArrayR[CNumOfRunsR][CNumVarsR];
        for (int i=0; i<CNumOfRunsR; i++)
        {
                for (int j=0; j<CNumVarsR; j++)
                {
                        CInfoArrayR[i][j]=0;
                }
        }



	TChain* chainCR = new TChain("T");
	TChain* chainAyHeR = new TChain("T");
	TChain* chaineedHeR = new TChain("T");

	gStyle->SetErrorX(.25);
	gStyle->SetEndErrorSize(.25);
	ifstream inp;
	ofstream out;

	TString filenameCR;
	TString filenameAyHeR;
	TString filenameeedHeR;

	TChain* chainC = new TChain("T");
	TChain* chainAyHe = new TChain("T");

	TString filenameC;
	TString filenameAyHe;


// Below is the loop for adding chains for the Left Carbon runs
	for (int thisCRunNumber=CRunNumber; thisCRunNumber<(endCRunNumber+1); thisCRunNumber++)
	{
		if(thisCRunNumber==1700){thisCRunNumber=1825;}
		if(thisCRunNumber==1829){thisCRunNumber=999999999;}

		for (int t=0; t<1000;t++)
		{
		filenameC = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_L_";
		filenameC += thisCRunNumber;
		if (t!=0)
		{
			filenameC += "_";
			filenameC += t;
		}
		filenameC += ".root";
		ifstream ifileC(filenameC);
		if (ifileC)
		{
			cout << "Adding file to chainC: " << filenameC << endl;
			chainC->Add(filenameC);
		}
		else
		{
			cout << "File " << filenameC << " does not exist. Ending here." << endl;
			t=9999999;
		}

		}
	
// Uncommenting the line below will let the code only go through one run (Good for debugging purposes)
//	thisCRunNumber = 99999999;

	}



// Below is the loop for adding chains for the Left 3He runs

	for (int thisAyHeRunNumber=AyHeRunNumber;thisAyHeRunNumber<(endAyHeRunNumber+1); thisAyHeRunNumber++)
	{
		// Going to next set of Q2 runs
/*		if (Q2=="1.0")
		{
			if(thisAyHeRunNumber=20791){thisAyHeRunNumber=22393;}
		}
*/
		// Skipping Vertical Carbon Runs
		if(thisAyHeRunNumber==1692){thisAyHeRunNumber=1704;}
		if(thisAyHeRunNumber==1825){thisAyHeRunNumber=1832;}
		if(thisAyHeRunNumber==1826){thisAyHeRunNumber=1832;}
		if(thisAyHeRunNumber==1827){thisAyHeRunNumber=1832;}
		if(thisAyHeRunNumber==1828){thisAyHeRunNumber=1832;}

		// Skipping Longitudinal Carbon Runs

		// Skipping Transverse Carbon Runs


		for (int t=0; t<1000;t++)
		{
			filenameAyHe = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_L_";
			filenameAyHe += thisAyHeRunNumber;
			if (t!=0)
			{
				filenameAyHe += "_";
				filenameAyHe += t;
			}
			filenameAyHe += ".root";
			ifstream ifileAyHe(filenameAyHe);
			if (ifileAyHe)
			{
				cout << "Adding file to chainAyHe: " << filenameAyHe << endl;
				chainAyHe->Add(filenameAyHe);
			}
			else
			{
				cout << "File " << filenameAyHe << " does not exist. Ending here." << endl;
				t=9999999;
			}

		}

// Uncommenting the line below will let the code only go through one run (Good for debugging purposes)
//	thisAyHeRunNumber = 999999999;
	}


// Below is the loop for adding chains for the Right Carbon run
	for (int thisCRunNumberR=CRunNumberR; thisCRunNumberR<(endCRunNumberR+1); thisCRunNumberR++)
	{
		if(thisCRunNumberR==20592){thisCRunNumberR=20731;}
		if(thisCRunNumberR==20735){thisCRunNumberR=20762;}
		if(thisCRunNumberR==20765){thisCRunNumberR=22380;}
		if(thisCRunNumberR==22381){thisCRunNumberR=22389;}
		if(thisCRunNumberR==22390){thisCRunNumberR=22425;}
		if(thisCRunNumberR==22427){thisCRunNumberR=22461;}
		if(thisCRunNumberR==22462){thisCRunNumberR=99999;}

		for (int t=0; t<1000;t++)
		{
		filenameCR = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_R_";
		filenameCR += thisCRunNumberR;
		if (t!=0)
		{
			filenameCR += "_";
			filenameCR += t;
		}
		filenameCR += ".root";
		ifstream ifileC(filenameCR);
		if (ifileC)
		{
			cout << "Adding file to chainCR: " << filenameCR << endl;
			chainCR->Add(filenameCR);
		}
		else
		{
			cout << "File " << filenameCR << " does not exist. Ending here." << endl;
			t=9999999;
		}

		}
	
// Uncommenting the line below will let the code only go through one run (Good for debugging purposes)
//	thisCRunNumberR = 99999999;

	}





// Below is the loop for adding chains for the Right 3He Ay runs

	for (int thisAyHeRunNumberR=AyHeRunNumberR;thisAyHeRunNumberR<(endAyHeRunNumberR+1); thisAyHeRunNumberR++)
	{
		// Going to next set of Q2 runs
/*		if (Q2=="1.0")
		{
			if(thisAyHeRunNumberR==20791){thisAyHeRunNumberR=22393;}
		}
*/
		// Skipping Vertical Carbon Runs
		if(thisAyHeRunNumberR==20591){thisAyHeRunNumberR=20596;}
		if(thisAyHeRunNumberR==20731){thisAyHeRunNumberR=20738;}
		if(thisAyHeRunNumberR==20732){thisAyHeRunNumberR=20738;}
		if(thisAyHeRunNumberR==20733){thisAyHeRunNumberR=20738;}
		if(thisAyHeRunNumberR==20734){thisAyHeRunNumberR=20738;}
		if(thisAyHeRunNumberR==20736){thisAyHeRunNumberR=20738;}
		if(thisAyHeRunNumberR==20737){thisAyHeRunNumberR=20738;}
		if(thisAyHeRunNumberR==20762){thisAyHeRunNumberR=20789;}
		if(thisAyHeRunNumberR==20763){thisAyHeRunNumberR=20789;}
		if(thisAyHeRunNumberR==20764){thisAyHeRunNumberR=20789;}
		if(thisAyHeRunNumberR==20791){thisAyHeRunNumberR=22393;}
//		if(thisAyHeRunNumberR==20791){thisAyHeRunNumberR=20814;}
		if(thisAyHeRunNumberR==20792){thisAyHeRunNumberR=20814;}

		// Skipping Longitudinal Carbon Runs
		if(thisAyHeRunNumberR==22380){thisAyHeRunNumberR=22393;}
		if(thisAyHeRunNumberR==22389){thisAyHeRunNumberR=22393;}
		if(thisAyHeRunNumberR==22425){thisAyHeRunNumberR=22436;}
		if(thisAyHeRunNumberR==22426){thisAyHeRunNumberR=22436;}

		// Skipping Transverse Carbon Runs
		if(thisAyHeRunNumberR==22461){thisAyHeRunNumberR=22465;}
		if(thisAyHeRunNumberR==20591){thisAyHeRunNumberR=20596;}
		if(thisAyHeRunNumberR==22397){thisAyHeRunNumberR=22398;}
		for (int t=0; t<1000;t++)
		{
			filenameAyHeR = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_R_";
			filenameAyHeR += thisAyHeRunNumberR;
			if (t!=0)
			{
				filenameAyHeR += "_";
				filenameAyHeR += t;
			}
			filenameAyHeR += ".root";
			ifstream ifileAyHe(filenameAyHeR);
			if (ifileAyHe)
			{
				cout << "Adding file to chainAyHeR: " << filenameAyHeR << endl;
				chainAyHeR->Add(filenameAyHeR);
			}
			else
			{
				cout << "File " << filenameAyHeR << " does not exist. Ending here." << endl;
				t=9999999;
			}

		}

// Uncommenting the line below will let the code only go through one run (Good for debugging purposes)
//	thisAyHeRunNumberR = 999999999;

	}
// Below is the loop for adding chains for the Right 3He eed runs

	for (int thiseedHeRunNumberR=eedHeRunNumberR;thiseedHeRunNumberR<(endeedHeRunNumberR+1); thiseedHeRunNumberR++)
	{
		// Going to next set of Q2 runs
/*		if (Q2=="1.0")
		{
			if(thiseedHeRunNumberR==20791){thiseedHeRunNumberR=22393;}
		}
*/
		// Skipping Vertical Carbon Runs
		if(thiseedHeRunNumberR==20591){thiseedHeRunNumberR=20596;}
		if(thiseedHeRunNumberR==20731){thiseedHeRunNumberR=20738;}
		if(thiseedHeRunNumberR==20732){thiseedHeRunNumberR=20738;}
		if(thiseedHeRunNumberR==20733){thiseedHeRunNumberR=20738;}
		if(thiseedHeRunNumberR==20734){thiseedHeRunNumberR=20738;}
		if(thiseedHeRunNumberR==20736){thiseedHeRunNumberR=20738;}
		if(thiseedHeRunNumberR==20737){thiseedHeRunNumberR=20738;}
		if(thiseedHeRunNumberR==20762){thiseedHeRunNumberR=20789;}
		if(thiseedHeRunNumberR==20763){thiseedHeRunNumberR=20789;}
		if(thiseedHeRunNumberR==20764){thiseedHeRunNumberR=20789;}
		if(thiseedHeRunNumberR==20791){thiseedHeRunNumberR=22393;}
//		if(thiseedHeRunNumberR==20791){thiseedHeRunNumberR=20814;}
		if(thiseedHeRunNumberR==20792){thiseedHeRunNumberR=20814;}

		// Skipping Longitudinal Carbon Runs
		if(thiseedHeRunNumberR==22380){thiseedHeRunNumberR=22393;}
		if(thiseedHeRunNumberR==22389){thiseedHeRunNumberR=22393;}
		if(thiseedHeRunNumberR==22425){thiseedHeRunNumberR=22436;}
		if(thiseedHeRunNumberR==22426){thiseedHeRunNumberR=22436;}

		// Skipping Transverse Carbon Runs
		if(thiseedHeRunNumberR==22461){thiseedHeRunNumberR=22465;}
		if(thiseedHeRunNumberR==20591){thiseedHeRunNumberR=20596;}
		if(thiseedHeRunNumberR==22397){thiseedHeRunNumberR=22398;}
		for (int t=0; t<1000;t++)
		{
			filenameeedHeR = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_R_";
			filenameeedHeR += thiseedHeRunNumberR;
			if (t!=0)
			{
				filenameeedHeR += "_";
				filenameeedHeR += t;
			}
			filenameeedHeR += ".root";
			ifstream ifileeedHe(filenameeedHeR);
			if (ifileeedHe)
			{
				cout << "Adding file to chaineedHeR: " << filenameeedHeR << endl;
				chaineedHeR->Add(filenameeedHeR);
			}
			else
			{
				cout << "File " << filenameeedHeR << " does not exist. Ending here." << endl;
				t=9999999;
			}

		}

// Uncommenting the line below will let the code only go through one run (Good for debugging purposes)
//	thiseedHeRunNumberR = 999999999;

	}


// This section will put the Left 3He root data into doubles so that
// it can be calculated through C++ instead of as histograms
// ****************************************************************************************************************
        int AyHeNumberOfEvents;
        double AyHeIsSpinValid;
        double AyHeQSquare;
        double AyHeNu;
        double AyHeEvTypeBits;
        double AyHeDp;
        double AyHeReactZ;
        double AyHeTh;
        double AyHePh;
        double AyHe_x_bj;
        double AyHeShE;
        double AyHePShE;
        double AyHeCerAsum;
        double AyHeRunNum;
        double AyHeSpin;
        int AyHeRunNumberForArray;
        double AyHe_u3c;
        double AyHe_u3pp;
        double AyHe_u3pm;
        double AyHe_u3mm;
        double AyHe_u3mp;

        AyHeNumberOfEvents = int(chainAyHe->GetEntries());
        chainAyHe->SetBranchAddress("he3.IsSpinValid", &AyHeIsSpinValid);
        chainAyHe->SetBranchAddress("he3.Spin", &AyHeSpin);
        chainAyHe->SetBranchAddress("PriKineL.Q2", &AyHeQSquare);
        chainAyHe->SetBranchAddress("PriKineL.nu", &AyHeNu);
        chainAyHe->SetBranchAddress("DL.evtypebits", &AyHeEvTypeBits);
        chainAyHe->SetBranchAddress("ExTgtCor_L.dp", &AyHeDp);
        chainAyHe->SetBranchAddress("ExTgtCor_L.th", &AyHeTh);
        chainAyHe->SetBranchAddress("ExTgtCor_L.ph", &AyHePh);
        chainAyHe->SetBranchAddress("ReactPt_L.z", &AyHeReactZ);
        chainAyHe->SetBranchAddress("PriKineL.x_bj", &AyHe_x_bj);
        chainAyHe->SetBranchAddress("L.prl2.e", &AyHeShE);
        chainAyHe->SetBranchAddress("L.prl1.e", &AyHePShE);
        chainAyHe->SetBranchAddress("L.cer.asum_c", &AyHeCerAsum);
        chainAyHe->SetBranchAddress("g.runnum", &AyHeRunNum);
        chainAyHe->SetBranchAddress("evleft_u3c", &AyHe_u3c);
        chainAyHe->SetBranchAddress("evleft_u3pp", &AyHe_u3pp);
        chainAyHe->SetBranchAddress("evleft_u3pm", &AyHe_u3pm);
        chainAyHe->SetBranchAddress("evleft_u3mm", &AyHe_u3mm);
        chainAyHe->SetBranchAddress("evleft_u3mp", &AyHe_u3mp);

        cout << "Number of events: " << AyHeNumberOfEvents << endl;
        chainAyHe->GetEntry(1);
        AyHeRunNumberForArray = int(AyHeRunNum);
        int AyHePrevRunNumber = AyHeRunNumberForArray;
        int AyHeRunNumPlace = 0;
        AyHeInfoArray[AyHeRunNumPlace][0] = AyHeRunNumberForArray;
        double AyHePrev_u3c = AyHe_u3c;
        double AyHe_u3p = 0;
        double AyHe_u3m = 0;
        double AyHe_u3c_real = 0;
        double AyHe_u3c_real_for_event = 0;
        double AyHeEndOfRun_u3c = 0;
        double AyHeEndOfRun_u3p = 0;
        double AyHeEndOfRun_u3m = 0;
        int AyHeRealNumOfRuns = 1;
        double AyHeRatio = 1e-15;
	int AyHeFalseRunCounter = 0;
	double AyHeChargeScale = 1e-15;
	int AyHeTriggerstotal = 0;
	int AyHeT8total = 0;
	int AyHeT8unpolcuts = 0;
        for (int i=0; i<AyHeNumberOfEvents; i++)
        {
		AyHeTriggerstotal++;
                chainAyHe->GetEntry(i);
                AyHeRunNumberForArray = int(AyHeRunNum);
                AyHe_u3c_real_for_event = AyHe_u3c - AyHePrev_u3c;

                if (i%10000 == 0)
                {
                        cout << "Event Number " << i << ", Run Number " << AyHeRunNumberForArray << endl;
                        cout << "AyHe_u3c: " << AyHe_u3c << "  AyHe_u3pp: " << AyHe_u3pp << "  AyHe_u3pm: " << AyHe_u3pm << "  AyHe_u3mm: " << AyHe_u3mm << "  AyHe_u3mp: " << AyHe_u3mp << " Error: " << AyHeInfoArray[AyHeRunNumPlace][7] << ", AyHeEvTypeBits = " << AyHeEvTypeBits << endl;
                }
                if (AyHeRunNumberForArray > AyHePrevRunNumber)
                {
                        AyHe_u3c_real = 0;
                        AyHe_u3p = 0;
                        AyHe_u3m = 0;
                        chainAyHe->GetEntry(i-1);
                        AyHeEndOfRun_u3c = AyHe_u3c;
                        AyHeEndOfRun_u3p = AyHe_u3pp + AyHe_u3pm;
                        AyHeEndOfRun_u3m = AyHe_u3mm + AyHe_u3mp;
                        AyHeInfoArray[AyHeRunNumPlace][8] = AyHeEndOfRun_u3c;
                        AyHeInfoArray[AyHeRunNumPlace][9] = AyHeEndOfRun_u3p;
                        AyHeInfoArray[AyHeRunNumPlace][10] = AyHeEndOfRun_u3m;
//                      AyHeInfoArray[AyHeRunNumPlace][7] = 1/(sqrt(AyHeInfoArray[AyHeRunNumPlace][1]));
                        AyHeRatio = ((AyHeInfoArray[AyHeRunNumPlace][12]/(AyHeInfoArray[AyHeRunNumPlace][11] + 1e-15))*AyHeInfoArray[AyHeRunNumPlace][9])/((AyHeInfoArray[AyHeRunNumPlace][13]/(AyHeInfoArray[AyHeRunNumPlace][11] + 1e-15))*AyHeInfoArray[AyHeRunNumPlace][10]+1e-15);
                        AyHeInfoArray[AyHeRunNumPlace][7] = 2*AyHeRatio*sqrt(AyHeInfoArray[AyHeRunNumPlace][2]*AyHeInfoArray[AyHeRunNumPlace][2]*AyHeInfoArray[AyHeRunNumPlace][3]+AyHeInfoArray[AyHeRunNumPlace][3]*AyHeInfoArray[AyHeRunNumPlace][3]*AyHeInfoArray[AyHeRunNumPlace][2])/pow(AyHeInfoArray[AyHeRunNumPlace][2]+AyHeRatio*AyHeInfoArray[AyHeRunNumPlace][3]+1e-15,2);

                        cout << "Ending Run Number " << AyHeInfoArray[AyHeRunNumPlace][0] << ", AyHe_u3c = " << AyHeInfoArray[AyHeRunNumPlace][8] << ", AyHe_u3p = " << AyHeInfoArray[AyHeRunNumPlace][9] << ", AyHe_u3m = " << AyHeInfoArray[AyHeRunNumPlace][10] << ", Error = " << AyHeInfoArray[AyHeRunNumPlace][7] << endl;
                        chainAyHe->GetEntry(i);
                        AyHeRunNumPlace++;
                        AyHePrevRunNumber = AyHeRunNumberForArray;
                        AyHeInfoArray[AyHeRunNumPlace][0] = AyHeRunNumberForArray;
                        AyHeRealNumOfRuns++;
                }
                if (i==(AyHeNumberOfEvents-1))
                {
                        chainAyHe->GetEntry(i-1);
                        AyHeEndOfRun_u3c = AyHe_u3c;
                        AyHeEndOfRun_u3p = AyHe_u3pp + AyHe_u3pm;
                        AyHeEndOfRun_u3m = AyHe_u3mm + AyHe_u3mp;
                        AyHeInfoArray[AyHeRunNumPlace][8] = AyHeEndOfRun_u3c;
                        AyHeInfoArray[AyHeRunNumPlace][9] = AyHeEndOfRun_u3p;
                        AyHeInfoArray[AyHeRunNumPlace][10] = AyHeEndOfRun_u3m;
//                      AyHeInfoArray[AyHeRunNumPlace][7] = 1/(sqrt(AyHeInfoArray[AyHeRunNumPlace][1]));
                        AyHeRatio = ((AyHeInfoArray[AyHeRunNumPlace][12]/(AyHeInfoArray[AyHeRunNumPlace][11] + 1e-15))*AyHeInfoArray[AyHeRunNumPlace][9])/((AyHeInfoArray[AyHeRunNumPlace][13]/(AyHeInfoArray[AyHeRunNumPlace][11] + 1e-15))*AyHeInfoArray[AyHeRunNumPlace][10] + 1e-15);
                        AyHeInfoArray[AyHeRunNumPlace][7] = 2*AyHeRatio*sqrt(AyHeInfoArray[AyHeRunNumPlace][2]*AyHeInfoArray[AyHeRunNumPlace][2]*AyHeInfoArray[AyHeRunNumPlace][3]+AyHeInfoArray[AyHeRunNumPlace][3]*AyHeInfoArray[AyHeRunNumPlace][3]*AyHeInfoArray[AyHeRunNumPlace][2])/pow(AyHeInfoArray[AyHeRunNumPlace][2]+AyHeRatio*AyHeInfoArray[AyHeRunNumPlace][3]+1e-15,2);
                        cout << "Ending Run Number " << AyHeInfoArray[AyHeRunNumPlace][0] << ", AyHe_u3c = " << AyHeInfoArray[AyHeRunNumPlace][8] << ", AyHe_u3p = " << AyHeInfoArray[AyHeRunNumPlace][9] << ", AyHe_u3m = " << AyHeInfoArray[AyHeRunNumPlace][10] << ", Error = " << AyHeInfoArray[AyHeRunNumPlace][7] << endl;
                }
		if (int(AyHeEvTypeBits)==8)
		{
			AyHeT8total++;
		}

                if ((AyHeIsSpinValid==1)&&(AyHeQSquare<10)&&(AyHeNu<10)&&(AyHeDp>-0.04)&&(AyHeDp<0.058)&&(AyHeReactZ>-0.155)&&(AyHeReactZ<0.175)&&(abs(AyHeTh)<0.07)&&(abs(AyHePh)<0.03)&&(AyHe_x_bj<2)&&((AyHePShE+(2*AyHeShE))>900)&&(AyHeCerAsum>400))
                {
                        AyHe_u3c_real = AyHe_u3c_real + AyHe_u3c_real_for_event;
                        AyHeInfoArray[AyHeRunNumPlace][1]++;
                        if (int(AyHeSpin)==1)
                        {
                                AyHeInfoArray[AyHeRunNumPlace][2]++;
                                AyHe_u3p = AyHe_u3p + AyHe_u3c_real_for_event;
                                AyHeInfoArray[AyHeRunNumPlace][5] = AyHe_u3pp + AyHe_u3pm;
                        }
                        if (int(AyHeSpin)==-1)
                        {
                                AyHeInfoArray[AyHeRunNumPlace][3]++;
                                AyHe_u3m = AyHe_u3m + AyHe_u3c_real_for_event;
                                AyHeInfoArray[AyHeRunNumPlace][6] = AyHe_u3mm + AyHe_u3mp;
                        }
                        AyHeInfoArray[AyHeRunNumPlace][4] = AyHe_u3c_real;
                        if (int(AyHeEvTypeBits)==8)
                        {
				AyHeT8unpolcuts++;
                                AyHeInfoArray[AyHeRunNumPlace][11]++;
                                if (int(AyHeSpin)==1){ AyHeInfoArray[AyHeRunNumPlace][12]++;}
                                if (int(AyHeSpin)==-1){ AyHeInfoArray[AyHeRunNumPlace][13]++;}
                        }
                }

                AyHePrev_u3c = AyHe_u3c;
        }
        cout << "Number of AyHe Runs: " << AyHeNumOfRuns << endl;
        outFile << "Possible Number of AyHe Runs: " << AyHeNumOfRuns << endl;
        cout << "Run #  # Unpol   # Spin Up   # Spin Down     Total C         C for up*       C for down*     Error   C for up        C for down      Total T1        # Up T2 # Down T2" << endl;
        outFile << "Run #  # Unpol   # Spin Up   # Spin Down     Total C         C for up*       C for down*     Error   C for up        C for down      Total T1        # Up T2 # Down T2" << endl;
        for (int i=0; i<AyHeNumOfRuns; i++)
        {
		AyHeChargeScale = AyHeChargeScale + AyHeInfoArray[i][8];
		if (AyHeInfoArray[i][0] != 0)
		{
			for (int j=0; j<AyHeNumVars; j++)
			{
				cout << AyHeInfoArray[i][j] << "    ";
				outFile << AyHeInfoArray[i][j] << "    ";
			}
			cout << endl;
			outFile << endl;
		}
		else
		{
			AyHeFalseRunCounter++;
		}
	}
        cout << "* = Done by adding event-by-event, which might not be working" << endl;
        outFile << "* = Done by adding event-by-event, which might not be working" << endl;
	outFile << "Actual number of AyHe runs: " << (AyHeNumOfRuns - AyHeFalseRunCounter) << endl << endl << endl << endl;
// ****************************************************************************************************************


// This section will put the Left 12C root data into doubles so that
// it can be calculated through C++ instead of as histograms
// ****************************************************************************************************************
        int CNumberOfEvents;
        double CIsSpinValid;
        double CQSquare;
        double CNu;
        double CEvTypeBits;
        double CDp;
        double CReactZ;
        double CTh;
        double CPh;
        double C_x_bj;
        double CShE;
        double CPShE;
        double CCerAsum;
        double CRunNum;
        double CSpin;
        int CRunNumberForArray;
        double C_u3c;
        double C_u3pp;
        double C_u3pm;
        double C_u3mm;
        double C_u3mp;

        CNumberOfEvents = int(chainC->GetEntries());
        chainC->SetBranchAddress("he3.IsSpinValid", &CIsSpinValid);
        chainC->SetBranchAddress("he3.Spin", &CSpin);
        chainC->SetBranchAddress("PriKineL.Q2", &CQSquare);
        chainC->SetBranchAddress("PriKineL.nu", &CNu);
        chainC->SetBranchAddress("DL.evtypebits", &CEvTypeBits);
        chainC->SetBranchAddress("ExTgtCor_L.dp", &CDp);
        chainC->SetBranchAddress("ExTgtCor_L.th", &CTh);
        chainC->SetBranchAddress("ExTgtCor_L.ph", &CPh);
        chainC->SetBranchAddress("ReactPt_L.z", &CReactZ);
        chainC->SetBranchAddress("PriKineL.x_bj", &C_x_bj);
        chainC->SetBranchAddress("L.prl2.e", &CShE);
        chainC->SetBranchAddress("L.prl1.e", &CPShE);
        chainC->SetBranchAddress("L.cer.asum_c", &CCerAsum);
        chainC->SetBranchAddress("g.runnum", &CRunNum);
        chainC->SetBranchAddress("evleft_u3c", &C_u3c);
        chainC->SetBranchAddress("evleft_u3pp", &C_u3pp);
        chainC->SetBranchAddress("evleft_u3pm", &C_u3pm);
        chainC->SetBranchAddress("evleft_u3mm", &C_u3mm);
        chainC->SetBranchAddress("evleft_u3mp", &C_u3mp);

        cout << "Number of events: " << CNumberOfEvents << endl;
        chainC->GetEntry(1);
        CRunNumberForArray = int(CRunNum);
        int CPrevRunNumber = CRunNumberForArray;
        int CRunNumPlace = 0;
        CInfoArray[CRunNumPlace][0] = CRunNumberForArray;
        double CPrev_u3c = C_u3c;
        double C_u3p = 0;
        double C_u3m = 0;
        double C_u3c_real = 0;
        double C_u3c_real_for_event = 0;
        double CEndOfRun_u3c = 0;
        double CEndOfRun_u3p = 0;
        double CEndOfRun_u3m = 0;
        int CRealNumOfRuns = 1;
        double CRatio = 1e-15;
	int CFalseRunCounter = 0;
	double CChargeScale = 1e-15;
	int CTriggerstotal = 0;
	int CT8total = 0;
	int CT8unpolcuts = 0;
        for (int i=0; i<CNumberOfEvents; i++)
        {
		CTriggerstotal++;
                chainC->GetEntry(i);
                CRunNumberForArray = int(CRunNum);
                C_u3c_real_for_event = C_u3c - CPrev_u3c;

                if (i%10000 == 0)
                {
                        cout << "Event Number " << i << ", Run Number " << CRunNumberForArray << endl;
                        cout << "C_u3c: " << C_u3c << "  C_u3pp: " << C_u3pp << "  C_u3pm: " << C_u3pm << "  C_u3mm: " << C_u3mm << "  C_u3mp: " << C_u3mp << " Error: " << CInfoArray[CRunNumPlace][7] << ", CEvTypeBits = " << CEvTypeBits << endl;
                }
                if (CRunNumberForArray > CPrevRunNumber)
                {
                        C_u3c_real = 0;
                        C_u3p = 0;
                        C_u3m = 0;
                        chainC->GetEntry(i-1);
                        CEndOfRun_u3c = C_u3c;
                        CEndOfRun_u3p = C_u3pp + C_u3pm;
                        CEndOfRun_u3m = C_u3mm + C_u3mp;
                        CInfoArray[CRunNumPlace][8] = CEndOfRun_u3c;
                        CInfoArray[CRunNumPlace][9] = CEndOfRun_u3p;
                        CInfoArray[CRunNumPlace][10] = CEndOfRun_u3m;
//                      CInfoArray[CRunNumPlace][7] = 1/(sqrt(CInfoArray[CRunNumPlace][1]));
                        CRatio = ((CInfoArray[CRunNumPlace][12]/(CInfoArray[CRunNumPlace][11] + 1e-15))*CInfoArray[CRunNumPlace][9])/((CInfoArray[CRunNumPlace][13]/(CInfoArray[CRunNumPlace][11] + 1e-15))*CInfoArray[CRunNumPlace][10]+1e-15);
                        CInfoArray[CRunNumPlace][7] = 2*CRatio*sqrt(CInfoArray[CRunNumPlace][2]*CInfoArray[CRunNumPlace][2]*CInfoArray[CRunNumPlace][3]+CInfoArray[CRunNumPlace][3]*CInfoArray[CRunNumPlace][3]*CInfoArray[CRunNumPlace][2])/pow(CInfoArray[CRunNumPlace][2]+CRatio*CInfoArray[CRunNumPlace][3]+1e-15,2);

                        cout << "Ending Run Number " << CInfoArray[CRunNumPlace][0] << ", C_u3c = " << CInfoArray[CRunNumPlace][8] << ", C_u3p = " << CInfoArray[CRunNumPlace][9] << ", C_u3m = " << CInfoArray[CRunNumPlace][10] << ", Error = " << CInfoArray[CRunNumPlace][7] << endl;
                        chainC->GetEntry(i);
                        CRunNumPlace++;
                        CPrevRunNumber = CRunNumberForArray;
                        CInfoArray[CRunNumPlace][0] = CRunNumberForArray;
                        CRealNumOfRuns++;
                }
                if (i==(CNumberOfEvents-1))
                {
                        chainC->GetEntry(i-1);
                        CEndOfRun_u3c = C_u3c;
                        CEndOfRun_u3p = C_u3pp + C_u3pm;
                        CEndOfRun_u3m = C_u3mm + C_u3mp;
                        CInfoArray[CRunNumPlace][8] = CEndOfRun_u3c;
                        CInfoArray[CRunNumPlace][9] = CEndOfRun_u3p;
                        CInfoArray[CRunNumPlace][10] = CEndOfRun_u3m;
//                      CInfoArray[CRunNumPlace][7] = 1/(sqrt(CInfoArray[CRunNumPlace][1]));
                        CRatio = ((CInfoArray[CRunNumPlace][12]/(CInfoArray[CRunNumPlace][11] + 1e-15))*CInfoArray[CRunNumPlace][9])/((CInfoArray[CRunNumPlace][13]/(CInfoArray[CRunNumPlace][11] + 1e-15))*CInfoArray[CRunNumPlace][10] + 1e-15);
                        CInfoArray[CRunNumPlace][7] = 2*CRatio*sqrt(CInfoArray[CRunNumPlace][2]*CInfoArray[CRunNumPlace][2]*CInfoArray[CRunNumPlace][3]+CInfoArray[CRunNumPlace][3]*CInfoArray[CRunNumPlace][3]*CInfoArray[CRunNumPlace][2])/pow(CInfoArray[CRunNumPlace][2]+CRatio*CInfoArray[CRunNumPlace][3]+1e-15,2);
                        cout << "Ending Run Number " << CInfoArray[CRunNumPlace][0] << ", C_u3c = " << CInfoArray[CRunNumPlace][8] << ", C_u3p = " << CInfoArray[CRunNumPlace][9] << ", C_u3m = " << CInfoArray[CRunNumPlace][10] << ", Error = " << CInfoArray[CRunNumPlace][7] << endl;
                }
		if (int(CEvTypeBits)==8)
		{
			CT8total++;
		}

                if ((CIsSpinValid==1)&&(CQSquare<10)&&(CNu<10)&&(CDp>-0.04)&&(CDp<0.058)&&(CReactZ>-0.155)&&(CReactZ<0.175)&&(abs(CTh)<0.07)&&(abs(CPh)<0.03)&&(C_x_bj<2)&&((CPShE+(2*CShE))>900)&&(CCerAsum>400))
                {
                        C_u3c_real = C_u3c_real + C_u3c_real_for_event;
                        CInfoArray[CRunNumPlace][1]++;
                        if (int(CSpin)==1)
                        {
                                CInfoArray[CRunNumPlace][2]++;
                                C_u3p = C_u3p + C_u3c_real_for_event;
                                CInfoArray[CRunNumPlace][5] = C_u3pp + C_u3pm;
                        }
                        if (int(CSpin)==-1)
                        {
                                CInfoArray[CRunNumPlace][3]++;
                                C_u3m = C_u3m + C_u3c_real_for_event;
                                CInfoArray[CRunNumPlace][6] = C_u3mm + C_u3mp;
                        }
                        CInfoArray[CRunNumPlace][4] = C_u3c_real;
                        if (int(CEvTypeBits)==8)
                        {
				CT8unpolcuts++;
                                CInfoArray[CRunNumPlace][11]++;
                                if (int(CSpin)==1){ CInfoArray[CRunNumPlace][12]++;}
                                if (int(CSpin)==-1){ CInfoArray[CRunNumPlace][13]++;}
                        }
                }

                CPrev_u3c = C_u3c;
        }
        cout << "Number of C Runs: " << CNumOfRuns << endl;
        outFile << "Possible Number of C Runs: " << CNumOfRuns << endl;
        cout << "Run #  # Unpol   # Spin Up       # Spin Down     Total C         C for up*       C for down*     Error   C for up        C for down      Total T1        # Up T2 # Down T2" << endl;
        outFile << "Run #  # Unpol   # Spin Up       # Spin Down     Total C         C for up*       C for down*     Error   C for up        C for down      Total T1        # Up T2 # Down T2" << endl;
        for (int i=0; i<CNumOfRuns; i++)
        {
		CChargeScale = CChargeScale + CInfoArray[i][8];
		if (CInfoArray[i][0] != 0)
		{
			for (int j=0; j<CNumVars; j++)
			{
				cout << CInfoArray[i][j] << "    ";
				outFile << CInfoArray[i][j] << "    ";
			}
			cout << endl;
			outFile << endl;
		}
		else
		{
			CFalseRunCounter++;
		}
        }
        cout << "* = Done by adding event-by-event, which might not be working" << endl;
        outFile << "* = Done by adding event-by-event, which might not be working" << endl;
	outFile << "Actual number of C runs: " << (CNumOfRuns - CFalseRunCounter) << endl << endl << endl << endl;
// ****************************************************************************************************************





// This section will put the Right 3He Ay root data into doubles so that
// it can be calculated through C++ instead of as histograms
// ****************************************************************************************************************
        int AyHeNumberROfEvents;
        double AyHeIsSpinValidR;
        double AyHeQSquareR;
        double AyHeNuR;
        double AyHeEvTypeBitsR;
        double AyHeDpR;
        double AyHeReactZR;
        double AyHeThR;
        double AyHePhR;
        double AyHe_x_bjR;
        double AyHeShER;
        double AyHePShER;
        double AyHeCerAsumR;
        double AyHeRunNumR;
        double AyHeSpinR;
        int AyHeRunNumberRForArray;
        double AyHe_u3cR;
        double AyHe_u3ppR;
        double AyHe_u3pmR;
        double AyHe_u3mmR;
        double AyHe_u3mpR;

        AyHeNumberROfEvents = int(chainAyHeR->GetEntries());
        chainAyHeR->SetBranchAddress("he3R.IsSpinValid", &AyHeIsSpinValidR);
        chainAyHeR->SetBranchAddress("he3R.Spin", &AyHeSpinR);
        chainAyHeR->SetBranchAddress("PriKineR.Q2", &AyHeQSquareR);
        chainAyHeR->SetBranchAddress("PriKineR.nu", &AyHeNuR);
        chainAyHeR->SetBranchAddress("D.evtypebits", &AyHeEvTypeBitsR);
        chainAyHeR->SetBranchAddress("ExTgtCor_R.dp", &AyHeDpR);
        chainAyHeR->SetBranchAddress("ExTgtCor_R.th", &AyHeThR);
        chainAyHeR->SetBranchAddress("ExTgtCor_R.ph", &AyHePhR);
        chainAyHeR->SetBranchAddress("ReactPt_R.z", &AyHeReactZR);
        chainAyHeR->SetBranchAddress("PriKineRHe3.x_bj", &AyHe_x_bjR);
        chainAyHeR->SetBranchAddress("R.sh.e", &AyHeShER);
        chainAyHeR->SetBranchAddress("R.ps.e", &AyHePShER);
        chainAyHeR->SetBranchAddress("R.cer.asum_c", &AyHeCerAsumR);
        chainAyHeR->SetBranchAddress("g.runnum", &AyHeRunNumR);
        chainAyHeR->SetBranchAddress("evright_u3c", &AyHe_u3cR);
        chainAyHeR->SetBranchAddress("evright_u3pp", &AyHe_u3ppR);
        chainAyHeR->SetBranchAddress("evright_u3pm", &AyHe_u3pmR);
        chainAyHeR->SetBranchAddress("evright_u3mm", &AyHe_u3mmR);
        chainAyHeR->SetBranchAddress("evright_u3mp", &AyHe_u3mpR);

        cout << "NumberR of events: " << AyHeNumberROfEvents << endl;
        chainAyHeR->GetEntry(1);
        AyHeRunNumberRForArray = int(AyHeRunNumR);
        int AyHePrevRunNumberR = AyHeRunNumberRForArray;
        int AyHeRunNumPlaceR = 0;
        AyHeInfoArrayR[AyHeRunNumPlaceR][0] = AyHeRunNumberRForArray;
        double AyHePrev_u3cR = AyHe_u3cR;
        double AyHe_u3pR = 0;
        double AyHe_u3mR = 0;
        double AyHe_u3cR_real = 0;
        double AyHe_u3cR_real_for_event = 0;
        double AyHeEndOfRun_u3cR = 0;
        double AyHeEndOfRun_u3pR = 0;
        double AyHeEndOfRun_u3mR = 0;
        int AyHeRealNumOfRunsR = 1;
        double AyHeRatioR = 1e-15;
	int AyHeFalseRunCounterR = 0;
	double AyHeChargeScaleR = 1e-15;
	int AyHeTriggerstotalR = 0;
	int AyHeT2totalR = 0;
	int AyHeT2unpolcutsR = 0;
        for (int i=0; i<AyHeNumberROfEvents; i++)
        {
		AyHeTriggerstotalR++;
                chainAyHeR->GetEntry(i);
                AyHeRunNumberRForArray = int(AyHeRunNumR);
                AyHe_u3cR_real_for_event = AyHe_u3cR - AyHePrev_u3cR;

                if (i%10000 == 0)
                {
                        cout << "Event NumberR " << i << ", Run NumberR " << AyHeRunNumberRForArray << endl;
                        cout << "AyHe_u3cR: " << AyHe_u3cR << "  AyHe_u3ppR: " << AyHe_u3ppR << "  AyHe_u3pmR: " << AyHe_u3pmR << "  AyHe_u3mmR: " << AyHe_u3mmR << "  AyHe_u3mpR: " << AyHe_u3mpR << " Error: " << AyHeInfoArrayR[AyHeRunNumPlaceR][7] << ", AyHeEvTypeBitsR = " << AyHeEvTypeBitsR << endl;
                }
                if (AyHeRunNumberRForArray > AyHePrevRunNumberR)
                {
                        AyHe_u3cR_real = 0;
                        AyHe_u3pR = 0;
                        AyHe_u3mR = 0;
                        chainAyHeR->GetEntry(i-1);
                        AyHeEndOfRun_u3cR = AyHe_u3cR;
                        AyHeEndOfRun_u3pR = AyHe_u3ppR + AyHe_u3pmR;
                        AyHeEndOfRun_u3mR = AyHe_u3mmR + AyHe_u3mpR;
                        AyHeInfoArrayR[AyHeRunNumPlaceR][8] = AyHeEndOfRun_u3cR;
                        AyHeInfoArrayR[AyHeRunNumPlaceR][9] = AyHeEndOfRun_u3pR;
                        AyHeInfoArrayR[AyHeRunNumPlaceR][10] = AyHeEndOfRun_u3mR;
//                      AyHeInfoArrayR[AyHeRunNumPlaceR][7] = 1/(sqrt(AyHeInfoArrayR[AyHeRunNumPlaceR][1]));
                        AyHeRatioR = ((AyHeInfoArrayR[AyHeRunNumPlaceR][12]/(AyHeInfoArrayR[AyHeRunNumPlaceR][11]+1e-15))*AyHeInfoArrayR[AyHeRunNumPlaceR][9])/((AyHeInfoArrayR[AyHeRunNumPlaceR][13]/(AyHeInfoArrayR[AyHeRunNumPlaceR][11]+1e-15))*AyHeInfoArrayR[AyHeRunNumPlaceR][10]+1e-15);
                        AyHeInfoArrayR[AyHeRunNumPlaceR][7] = 2*AyHeRatioR*sqrt(AyHeInfoArrayR[AyHeRunNumPlaceR][2]*AyHeInfoArrayR[AyHeRunNumPlaceR][2]*AyHeInfoArrayR[AyHeRunNumPlaceR][3]+AyHeInfoArrayR[AyHeRunNumPlaceR][3]*AyHeInfoArrayR[AyHeRunNumPlaceR][3]*AyHeInfoArrayR[AyHeRunNumPlaceR][2])/pow(AyHeInfoArrayR[AyHeRunNumPlaceR][2]+AyHeRatioR*AyHeInfoArrayR[AyHeRunNumPlaceR][3]+1e-15,2);

                        cout << "Ending Run NumberR " << AyHeInfoArrayR[AyHeRunNumPlaceR][0] << ", AyHe_u3cR = " << AyHeInfoArrayR[AyHeRunNumPlaceR][8] << ", AyHe_u3p = " << AyHeInfoArrayR[AyHeRunNumPlaceR][9] << ", AyHe_u3mR = " << AyHeInfoArrayR[AyHeRunNumPlaceR][10] << ", Error = " << AyHeInfoArrayR[AyHeRunNumPlaceR][7] << endl;
                        chainAyHeR->GetEntry(i);
                        AyHeRunNumPlaceR++;
                        AyHePrevRunNumberR = AyHeRunNumberRForArray;
                        AyHeInfoArrayR[AyHeRunNumPlaceR][0] = AyHeRunNumberRForArray;
                        AyHeRealNumOfRunsR++;
                }
                if (i==(AyHeNumberROfEvents-1))
                {
                        chainAyHeR->GetEntry(i-1);
                        AyHeEndOfRun_u3cR = AyHe_u3cR;
                        AyHeEndOfRun_u3pR = AyHe_u3ppR + AyHe_u3pmR;
                        AyHeEndOfRun_u3mR = AyHe_u3mmR + AyHe_u3mpR;
                        AyHeInfoArrayR[AyHeRunNumPlaceR][8] = AyHeEndOfRun_u3cR;
                        AyHeInfoArrayR[AyHeRunNumPlaceR][9] = AyHeEndOfRun_u3pR;
                        AyHeInfoArrayR[AyHeRunNumPlaceR][10] = AyHeEndOfRun_u3mR;
//                      AyHeInfoArrayR[AyHeRunNumPlaceR][7] = 1/(sqrt(AyHeInfoArrayR[AyHeRunNumPlaceR][1]));
                        AyHeRatioR = ((AyHeInfoArrayR[AyHeRunNumPlaceR][12]/(AyHeInfoArrayR[AyHeRunNumPlaceR][11]+1e-15))*AyHeInfoArrayR[AyHeRunNumPlaceR][9])/((AyHeInfoArrayR[AyHeRunNumPlaceR][13]/(AyHeInfoArrayR[AyHeRunNumPlaceR][11]+1e-15))*AyHeInfoArrayR[AyHeRunNumPlaceR][10] + 1e-15);
                        AyHeInfoArrayR[AyHeRunNumPlaceR][7] = 2*AyHeRatioR*sqrt(AyHeInfoArrayR[AyHeRunNumPlaceR][2]*AyHeInfoArrayR[AyHeRunNumPlaceR][2]*AyHeInfoArrayR[AyHeRunNumPlaceR][3]+AyHeInfoArrayR[AyHeRunNumPlaceR][3]*AyHeInfoArrayR[AyHeRunNumPlaceR][3]*AyHeInfoArrayR[AyHeRunNumPlaceR][2])/pow(AyHeInfoArrayR[AyHeRunNumPlaceR][2]+AyHeRatioR*AyHeInfoArrayR[AyHeRunNumPlaceR][3]+1e-15,2);
                        cout << "Ending Run NumberR " << AyHeInfoArrayR[AyHeRunNumPlaceR][0] << ", AyHe_u3cR = " << AyHeInfoArrayR[AyHeRunNumPlaceR][8] << ", AyHe_u3p = " << AyHeInfoArrayR[AyHeRunNumPlaceR][9] << ", AyHe_u3mR = " << AyHeInfoArrayR[AyHeRunNumPlaceR][10] << ", Error = " << AyHeInfoArrayR[AyHeRunNumPlaceR][7] << endl;
                }
		if (int(AyHeEvTypeBitsR)==2)
		{
			AyHeT2totalR++;
		}
                if ((AyHeIsSpinValidR==1)&&(AyHeQSquareR<10)&&(AyHeNuR<10)&&(AyHeDpR>-0.04)&&(AyHeDpR<0.058)&&(AyHeReactZR>-0.155)&&(AyHeReactZR<0.175)&&(abs(AyHeThR)<0.07)&&(abs(AyHePhR)<0.03)&&(AyHe_x_bjR<2)&&((AyHePShER+(2*AyHeShER))>900)&&(AyHeCerAsumR>400))
                {
                        AyHe_u3cR_real = AyHe_u3cR_real + AyHe_u3cR_real_for_event;
                        AyHeInfoArrayR[AyHeRunNumPlaceR][1]++;
                        if (int(AyHeSpinR)==1)
                        {
                                AyHeInfoArrayR[AyHeRunNumPlaceR][2]++;
                                AyHe_u3pR = AyHe_u3pR + AyHe_u3cR_real_for_event;
                                AyHeInfoArrayR[AyHeRunNumPlaceR][5] = AyHe_u3ppR + AyHe_u3pmR;
                        }
                        if (int(AyHeSpinR)==-1)
                        {
                                AyHeInfoArrayR[AyHeRunNumPlaceR][3]++;
                                AyHe_u3mR = AyHe_u3mR + AyHe_u3cR_real_for_event;
                                AyHeInfoArrayR[AyHeRunNumPlaceR][6] = AyHe_u3mmR + AyHe_u3mpR;
                        }
                        AyHeInfoArrayR[AyHeRunNumPlaceR][4] = AyHe_u3cR_real;
                        if (int(AyHeEvTypeBitsR)==2)
                        {
				AyHeT2unpolcutsR++;
                                AyHeInfoArrayR[AyHeRunNumPlaceR][11]++;
                                if (int(AyHeSpinR)==1){ AyHeInfoArrayR[AyHeRunNumPlaceR][12]++;}
                                if (int(AyHeSpinR)==-1){ AyHeInfoArrayR[AyHeRunNumPlaceR][13]++;}
                        }
                }

                AyHePrev_u3cR = AyHe_u3cR;
        }
        cout << "NumberR of AyHe Runs: " << AyHeNumOfRunsR << endl;
        outFile << "Possible NumberR of AyHe Runs: " << AyHeNumOfRunsR << endl;
        cout << "Run #  # Unpol   # Spin Up   # Spin Down     Total C         C for up*       C for down*     Error   C for up        C for down      Total T1        # Up T2 # Down T2" << endl;
        outFile << "Run #  # Unpol   # Spin Up   # Spin Down     Total C         C for up*       C for down*     Error   C for up        C for down      Total T1        # Up T2 # Down T2" << endl;
        for (int i=0; i<AyHeNumOfRunsR; i++)
        {
		AyHeChargeScaleR = AyHeChargeScaleR + AyHeInfoArrayR[i][8];
		if (AyHeInfoArrayR[i][0] != 0)
		{
			for (int j=0; j<AyHeNumVarsR; j++)
			{
				cout << AyHeInfoArrayR[i][j] << "    ";
				outFile << AyHeInfoArrayR[i][j] << "    ";
			}
			cout << endl;
			outFile << endl;
		}
		else
		{
			AyHeFalseRunCounterR++;
		}
	}
        cout << "* = Done by adding event-by-event, which might not be working" << endl;
        outFile << "* = Done by adding event-by-event, which might not be working" << endl;
	outFile << "Actual number of AyHe runs: " << (AyHeNumOfRunsR - AyHeFalseRunCounterR) << endl << endl << endl << endl;
// ****************************************************************************************************************

// This section will put the Right 3He eed root data into doubles so that
// it can be calculated through C++ instead of as histograms
// ****************************************************************************************************************
        int eedHeNumberROfEvents;
        double eedHeIsSpinValidR;
        double eedHeQSquareR;
        double eedHeNuR;
        double eedHeEvTypeBitsR;
        double eedHeDpR;
        double eedHeReactZR;
        double eedHeThR;
        double eedHePhR;
        double eedHe_x_bjR;
        double eedHeShER;
        double eedHePShER;
        double eedHeCerAsumR;
        double eedHeRunNumR;
        double eedHeSpinR;
        int eedHeRunNumberRForArray;
        double eedHe_u3cR;
        double eedHe_u3ppR;
        double eedHe_u3pmR;
        double eedHe_u3mmR;
        double eedHe_u3mpR;

        eedHeNumberROfEvents = int(chaineedHeR->GetEntries());
        chaineedHeR->SetBranchAddress("he3R.IsSpinValid", &eedHeIsSpinValidR);
        chaineedHeR->SetBranchAddress("he3R.Spin", &eedHeSpinR);
        chaineedHeR->SetBranchAddress("PriKineR.Q2", &eedHeQSquareR);
        chaineedHeR->SetBranchAddress("PriKineR.nu", &eedHeNuR);
        chaineedHeR->SetBranchAddress("D.evtypebits", &eedHeEvTypeBitsR);
        chaineedHeR->SetBranchAddress("ExTgtCor_R.dp", &eedHeDpR);
        chaineedHeR->SetBranchAddress("ExTgtCor_R.th", &eedHeThR);
        chaineedHeR->SetBranchAddress("ExTgtCor_R.ph", &eedHePhR);
        chaineedHeR->SetBranchAddress("ReactPt_R.z", &eedHeReactZR);
        chaineedHeR->SetBranchAddress("PriKineRHe3.x_bj", &eedHe_x_bjR);
        chaineedHeR->SetBranchAddress("R.sh.e", &eedHeShER);
        chaineedHeR->SetBranchAddress("R.ps.e", &eedHePShER);
        chaineedHeR->SetBranchAddress("R.cer.asum_c", &eedHeCerAsumR);
        chaineedHeR->SetBranchAddress("g.runnum", &eedHeRunNumR);
        chaineedHeR->SetBranchAddress("evright_u3c", &eedHe_u3cR);
        chaineedHeR->SetBranchAddress("evright_u3pp", &eedHe_u3ppR);
        chaineedHeR->SetBranchAddress("evright_u3pm", &eedHe_u3pmR);
        chaineedHeR->SetBranchAddress("evright_u3mm", &eedHe_u3mmR);
        chaineedHeR->SetBranchAddress("evright_u3mp", &eedHe_u3mpR);

        cout << "NumberR of events: " << eedHeNumberROfEvents << endl;
        chaineedHeR->GetEntry(1);
        eedHeRunNumberRForArray = int(eedHeRunNumR);
        int eedHePrevRunNumberR = eedHeRunNumberRForArray;
        int eedHeRunNumPlaceR = 0;
        eedHeInfoArrayR[eedHeRunNumPlaceR][0] = eedHeRunNumberRForArray;
        double eedHePrev_u3cR = eedHe_u3cR;
        double eedHe_u3pR = 0;
        double eedHe_u3mR = 0;
        double eedHe_u3cR_real = 0;
        double eedHe_u3cR_real_for_event = 0;
        double eedHeEndOfRun_u3cR = 0;
        double eedHeEndOfRun_u3pR = 0;
        double eedHeEndOfRun_u3mR = 0;
        int eedHeRealNumOfRunsR = 1;
        double eedHeRatioR = 1e-15;
	int eedHeFalseRunCounterR = 0;
	double eedHeChargeScaleR = 1e-15;
	int eedHeTriggerstotalR = 0;
	int eedHeT2totalR = 0;
	int eedHeT2unpolcutsR = 0;
        for (int i=0; i<eedHeNumberROfEvents; i++)
        {
		eedHeTriggerstotalR++;
                chaineedHeR->GetEntry(i);
                eedHeRunNumberRForArray = int(eedHeRunNumR);
                eedHe_u3cR_real_for_event = eedHe_u3cR - eedHePrev_u3cR;

                if (i%10000 == 0)
                {
                        cout << "Event NumberR " << i << ", Run NumberR " << eedHeRunNumberRForArray << endl;
                        cout << "eedHe_u3cR: " << eedHe_u3cR << "  eedHe_u3ppR: " << eedHe_u3ppR << "  eedHe_u3pmR: " << eedHe_u3pmR << "  eedHe_u3mmR: " << eedHe_u3mmR << "  eedHe_u3mpR: " << eedHe_u3mpR << " Error: " << eedHeInfoArrayR[eedHeRunNumPlaceR][7] << ", eedHeEvTypeBitsR = " << eedHeEvTypeBitsR << endl;
                }
                if (eedHeRunNumberRForArray > eedHePrevRunNumberR)
                {
                        eedHe_u3cR_real = 0;
                        eedHe_u3pR = 0;
                        eedHe_u3mR = 0;
                        chaineedHeR->GetEntry(i-1);
                        eedHeEndOfRun_u3cR = eedHe_u3cR;
                        eedHeEndOfRun_u3pR = eedHe_u3ppR + eedHe_u3pmR;
                        eedHeEndOfRun_u3mR = eedHe_u3mmR + eedHe_u3mpR;
                        eedHeInfoArrayR[eedHeRunNumPlaceR][8] = eedHeEndOfRun_u3cR;
                        eedHeInfoArrayR[eedHeRunNumPlaceR][9] = eedHeEndOfRun_u3pR;
                        eedHeInfoArrayR[eedHeRunNumPlaceR][10] = eedHeEndOfRun_u3mR;
//                      eedHeInfoArrayR[eedHeRunNumPlaceR][7] = 1/(sqrt(eedHeInfoArrayR[eedHeRunNumPlaceR][1]));
                        eedHeRatioR = ((eedHeInfoArrayR[eedHeRunNumPlaceR][12]/(eedHeInfoArrayR[eedHeRunNumPlaceR][11]+1e-15))*eedHeInfoArrayR[eedHeRunNumPlaceR][9])/((eedHeInfoArrayR[eedHeRunNumPlaceR][13]/(eedHeInfoArrayR[eedHeRunNumPlaceR][11]+1e-15))*eedHeInfoArrayR[eedHeRunNumPlaceR][10]+1e-15);
                        eedHeInfoArrayR[eedHeRunNumPlaceR][7] = 2*eedHeRatioR*sqrt(eedHeInfoArrayR[eedHeRunNumPlaceR][2]*eedHeInfoArrayR[eedHeRunNumPlaceR][2]*eedHeInfoArrayR[eedHeRunNumPlaceR][3]+eedHeInfoArrayR[eedHeRunNumPlaceR][3]*eedHeInfoArrayR[eedHeRunNumPlaceR][3]*eedHeInfoArrayR[eedHeRunNumPlaceR][2])/pow(eedHeInfoArrayR[eedHeRunNumPlaceR][2]+eedHeRatioR*eedHeInfoArrayR[eedHeRunNumPlaceR][3]+1e-15,2);

                        cout << "Ending Run NumberR " << eedHeInfoArrayR[eedHeRunNumPlaceR][0] << ", eedHe_u3cR = " << eedHeInfoArrayR[eedHeRunNumPlaceR][8] << ", eedHe_u3p = " << eedHeInfoArrayR[eedHeRunNumPlaceR][9] << ", eedHe_u3mR = " << eedHeInfoArrayR[eedHeRunNumPlaceR][10] << ", Error = " << eedHeInfoArrayR[eedHeRunNumPlaceR][7] << endl;
                        chaineedHeR->GetEntry(i);
                        eedHeRunNumPlaceR++;
                        eedHePrevRunNumberR = eedHeRunNumberRForArray;
                        eedHeInfoArrayR[eedHeRunNumPlaceR][0] = eedHeRunNumberRForArray;
                        eedHeRealNumOfRunsR++;
                }
                if (i==(eedHeNumberROfEvents-1))
                {
                        chaineedHeR->GetEntry(i-1);
                        eedHeEndOfRun_u3cR = eedHe_u3cR;
                        eedHeEndOfRun_u3pR = eedHe_u3ppR + eedHe_u3pmR;
                        eedHeEndOfRun_u3mR = eedHe_u3mmR + eedHe_u3mpR;
                        eedHeInfoArrayR[eedHeRunNumPlaceR][8] = eedHeEndOfRun_u3cR;
                        eedHeInfoArrayR[eedHeRunNumPlaceR][9] = eedHeEndOfRun_u3pR;
                        eedHeInfoArrayR[eedHeRunNumPlaceR][10] = eedHeEndOfRun_u3mR;
//                      eedHeInfoArrayR[eedHeRunNumPlaceR][7] = 1/(sqrt(eedHeInfoArrayR[eedHeRunNumPlaceR][1]));
                        eedHeRatioR = ((eedHeInfoArrayR[eedHeRunNumPlaceR][12]/(eedHeInfoArrayR[eedHeRunNumPlaceR][11]+1e-15))*eedHeInfoArrayR[eedHeRunNumPlaceR][9])/((eedHeInfoArrayR[eedHeRunNumPlaceR][13]/(eedHeInfoArrayR[eedHeRunNumPlaceR][11]+1e-15))*eedHeInfoArrayR[eedHeRunNumPlaceR][10] + 1e-15);
                        eedHeInfoArrayR[eedHeRunNumPlaceR][7] = 2*eedHeRatioR*sqrt(eedHeInfoArrayR[eedHeRunNumPlaceR][2]*eedHeInfoArrayR[eedHeRunNumPlaceR][2]*eedHeInfoArrayR[eedHeRunNumPlaceR][3]+eedHeInfoArrayR[eedHeRunNumPlaceR][3]*eedHeInfoArrayR[eedHeRunNumPlaceR][3]*eedHeInfoArrayR[eedHeRunNumPlaceR][2])/pow(eedHeInfoArrayR[eedHeRunNumPlaceR][2]+eedHeRatioR*eedHeInfoArrayR[eedHeRunNumPlaceR][3]+1e-15,2);
                        cout << "Ending Run NumberR " << eedHeInfoArrayR[eedHeRunNumPlaceR][0] << ", eedHe_u3cR = " << eedHeInfoArrayR[eedHeRunNumPlaceR][8] << ", eedHe_u3p = " << eedHeInfoArrayR[eedHeRunNumPlaceR][9] << ", eedHe_u3mR = " << eedHeInfoArrayR[eedHeRunNumPlaceR][10] << ", Error = " << eedHeInfoArrayR[eedHeRunNumPlaceR][7] << endl;
                }
		if ((eedHeEvTypeBitsR)==2)
		{
			eedHeT2totalR++;
		}
                if ((eedHeIsSpinValidR==1)&&(eedHeQSquareR<10)&&(eedHeNuR<10)&&(eedHeDpR>-0.04)&&(eedHeDpR<0.058)&&(eedHeReactZR>-0.155)&&(eedHeReactZR<0.175)&&(abs(eedHeThR)<0.07)&&(abs(eedHePhR)<0.03)&&(eedHe_x_bjR<2)&&((eedHePShER+(2*eedHeShER))>900)&&(eedHeCerAsumR>400))
                {
                        eedHe_u3cR_real = eedHe_u3cR_real + eedHe_u3cR_real_for_event;
                        eedHeInfoArrayR[eedHeRunNumPlaceR][1]++;
                        if (int(eedHeSpinR)==1)
                        {
                                eedHeInfoArrayR[eedHeRunNumPlaceR][2]++;
                                eedHe_u3pR = eedHe_u3pR + eedHe_u3cR_real_for_event;
                                eedHeInfoArrayR[eedHeRunNumPlaceR][5] = eedHe_u3ppR + eedHe_u3pmR;
                        }
                        if (int(eedHeSpinR)==-1)
                        {
                                eedHeInfoArrayR[eedHeRunNumPlaceR][3]++;
                                eedHe_u3mR = eedHe_u3mR + eedHe_u3cR_real_for_event;
                                eedHeInfoArrayR[eedHeRunNumPlaceR][6] = eedHe_u3mmR + eedHe_u3mpR;
                        }
                        eedHeInfoArrayR[eedHeRunNumPlaceR][4] = eedHe_u3cR_real;
                        if (int(eedHeEvTypeBitsR)==2)
                        {
				eedHeT2unpolcutsR++;
                                eedHeInfoArrayR[eedHeRunNumPlaceR][11]++;
                                if (int(eedHeSpinR)==1){ eedHeInfoArrayR[eedHeRunNumPlaceR][12]++;}
                                if (int(eedHeSpinR)==-1){ eedHeInfoArrayR[eedHeRunNumPlaceR][13]++;}
                        }
                }

                eedHePrev_u3cR = eedHe_u3cR;
        }
        cout << "NumberR of eedHe Runs: " << eedHeNumOfRunsR << endl;
        outFile << "Possible NumberR of eedHe Runs: " << eedHeNumOfRunsR << endl;
        cout << "Run #  # Unpol   # Spin Up   # Spin Down     Total C         C for up*       C for down*     Error   C for up        C for down      Total T1        # Up T2 # Down T2" << endl;
        outFile << "Run #  # Unpol   # Spin Up   # Spin Down     Total C         C for up*       C for down*     Error   C for up        C for down      Total T1        # Up T2 # Down T2" << endl;
        for (int i=0; i<eedHeNumOfRunsR; i++)
        {
		eedHeChargeScaleR = eedHeChargeScaleR + eedHeInfoArrayR[i][8];
		if (eedHeInfoArrayR[i][0] != 0)
		{
			for (int j=0; j<eedHeNumVarsR; j++)
			{
				cout << eedHeInfoArrayR[i][j] << "    ";
				outFile << eedHeInfoArrayR[i][j] << "    ";
			}
			cout << endl;
			outFile << endl;
		}
		else
		{
			eedHeFalseRunCounterR++;
		}
	}
        cout << "* = Done by adding event-by-event, which might not be working" << endl;
        outFile << "* = Done by adding event-by-event, which might not be working" << endl;
	outFile << "Actual number of eedHe runs: " << (eedHeNumOfRunsR - eedHeFalseRunCounterR) << endl << endl << endl << endl;
// ****************************************************************************************************************


// This section will put the Right 12C root data into doubles so that
// it can be calculated through C++ instead of as histograms
// ****************************************************************************************************************
        int CNumberROfEvents;
        double CIsSpinValidR;
        double CQSquareR;
        double CNuR;
        double CEvTypeBitsR;
        double CDpR;
        double CReactZR;
        double CThR;
        double CPhR;
        double C_x_bjR;
        double CShER;
        double CPShER;
        double CCerAsumR;
        double CRunNumR;
        double CSpinR;
        int CRunNumberRForArray;
        double C_u3cR;
        double Cu3ppR;
        double Cu3pmR;
        double Cu3mmR;
        double Cu3mpR;

        CNumberROfEvents = int(chainCR->GetEntries());
        chainCR->SetBranchAddress("he3R.IsSpinValid", &CIsSpinValidR);
        chainCR->SetBranchAddress("he3R.Spin", &CSpinR);
        chainCR->SetBranchAddress("PriKineR.Q2", &CQSquareR);
        chainCR->SetBranchAddress("PriKineR.nu", &CNuR);
        chainCR->SetBranchAddress("D.evtypebits", &CEvTypeBitsR);
        chainCR->SetBranchAddress("ExTgtCor_R.dp", &CDpR);
        chainCR->SetBranchAddress("ExTgtCor_R.th", &CThR);
        chainCR->SetBranchAddress("ExTgtCor_R.ph", &CPhR);
        chainCR->SetBranchAddress("ReactPt_R.z", &CReactZR);
        chainCR->SetBranchAddress("PriKineRHe3.x_bj", &C_x_bjR);
        chainCR->SetBranchAddress("R.sh.e", &CShER);
        chainCR->SetBranchAddress("R.ps.e", &CPShER);
        chainCR->SetBranchAddress("R.cer.asum_c", &CCerAsumR);
        chainCR->SetBranchAddress("g.runnum", &CRunNumR);
        chainCR->SetBranchAddress("evright_u3c", &C_u3cR);
        chainCR->SetBranchAddress("evright_u3pp", &Cu3ppR);
        chainCR->SetBranchAddress("evright_u3pm", &Cu3pmR);
        chainCR->SetBranchAddress("evright_u3mm", &Cu3mmR);
        chainCR->SetBranchAddress("evright_u3mp", &Cu3mpR);

        cout << "NumberR of events: " << CNumberROfEvents << endl;
        chainCR->GetEntry(1);
        CRunNumberRForArray = int(CRunNumR);
        int CPrevRunNumberR = CRunNumberRForArray;
        int CRunNumPlaceR = 0;
        CInfoArrayR[CRunNumPlaceR][0] = CRunNumberRForArray;
        double CPrev_u3cR = C_u3cR;
        double C_u3pR = 0;
        double C_u3mR = 0;
        double C_u3cR_real = 0;
        double C_u3cR_real_for_event = 0;
        double CEndOfRun_u3cR = 0;
        double CEndOfRun_u3pR = 0;
        double CEndOfRun_u3mR = 0;
        int CRealNumOfRunsR = 1;
        double CRatioR = 1e-15;
	int CFalseRunCounterR = 0;
	double CChargeScaleR = 1e-15;
	int CTriggerstotalR = 0;
	int CT2totalR = 0;
	int CT2unpolcutsR = 0;
        for (int i=0; i<CNumberROfEvents; i++)
        {
		CTriggerstotalR++;
                chainCR->GetEntry(i);
                CRunNumberRForArray = int(CRunNumR);
                C_u3cR_real_for_event = C_u3cR - CPrev_u3cR;

                if (i%10000 == 0)
                {
                        cout << "Event NumberR " << i << ", Run NumberR " << CRunNumberRForArray << endl;
                        cout << "C_u3cR: " << C_u3cR << "  Cu3ppR: " << Cu3ppR << "  Cu3pmR: " << Cu3pmR << "  Cu3mmR: " << Cu3mmR << "  Cu3mpR: " << Cu3mpR << " Error: " << CInfoArrayR[CRunNumPlaceR][7] << ", CEvTypeBitsR = " << CEvTypeBitsR << endl;
                }
                if (CRunNumberRForArray > CPrevRunNumberR)
                {
                        C_u3cR_real = 0;
                        C_u3pR = 0;
                        C_u3mR = 0;
                        chainCR->GetEntry(i-1);
                        CEndOfRun_u3cR = C_u3cR;
                        CEndOfRun_u3pR = Cu3ppR + Cu3pmR;
                        CEndOfRun_u3mR = Cu3mmR + Cu3mpR;
                        CInfoArrayR[CRunNumPlaceR][8] = CEndOfRun_u3cR;
                        CInfoArrayR[CRunNumPlaceR][9] = CEndOfRun_u3pR;
                        CInfoArrayR[CRunNumPlaceR][10] = CEndOfRun_u3mR;
//                      CInfoArrayR[CRunNumPlaceR][7] = 1/(sqrt(CInfoArrayR[CRunNumPlaceR][1]));
                        CRatioR = ((CInfoArrayR[CRunNumPlaceR][12]/(CInfoArrayR[CRunNumPlaceR][11]+1e-15))*CInfoArrayR[CRunNumPlaceR][9])/((CInfoArrayR[CRunNumPlaceR][13]/(CInfoArrayR[CRunNumPlaceR][11]+1e-15))*CInfoArrayR[CRunNumPlaceR][10]+1e-15);
                        CInfoArrayR[CRunNumPlaceR][7] = 2*CRatioR*sqrt(CInfoArrayR[CRunNumPlaceR][2]*CInfoArrayR[CRunNumPlaceR][2]*CInfoArrayR[CRunNumPlaceR][3]+CInfoArrayR[CRunNumPlaceR][3]*CInfoArrayR[CRunNumPlaceR][3]*CInfoArrayR[CRunNumPlaceR][2])/pow(CInfoArrayR[CRunNumPlaceR][2]+CRatioR*CInfoArrayR[CRunNumPlaceR][3]+1e-15,2);

                        cout << "Ending Run NumberR " << CInfoArrayR[CRunNumPlaceR][0] << ", C_u3cR = " << CInfoArrayR[CRunNumPlaceR][8] << ", C_u3pR = " << CInfoArrayR[CRunNumPlaceR][9] << ", C_u3mR = " << CInfoArrayR[CRunNumPlaceR][10] << ", Error = " << CInfoArrayR[CRunNumPlaceR][7] << endl;
                        chainCR->GetEntry(i);
                        CRunNumPlaceR++;
                        CPrevRunNumberR = CRunNumberRForArray;
                        CInfoArrayR[CRunNumPlaceR][0] = CRunNumberRForArray;
                        CRealNumOfRunsR++;
                }
                if (i==(CNumberROfEvents-1))
                {
                        chainCR->GetEntry(i-1);
                        CEndOfRun_u3cR = C_u3cR;
                        CEndOfRun_u3pR = Cu3ppR + Cu3pmR;
                        CEndOfRun_u3mR = Cu3mmR + Cu3mpR;
                        CInfoArrayR[CRunNumPlaceR][8] = CEndOfRun_u3cR;
                        CInfoArrayR[CRunNumPlaceR][9] = CEndOfRun_u3pR;
                        CInfoArrayR[CRunNumPlaceR][10] = CEndOfRun_u3mR;
//                      CInfoArrayR[CRunNumPlaceR][7] = 1/(sqrt(CInfoArrayR[CRunNumPlaceR][1]));
                        CRatioR = ((CInfoArrayR[CRunNumPlaceR][12]/(CInfoArrayR[CRunNumPlaceR][11]+1e-15))*CInfoArrayR[CRunNumPlaceR][9])/((CInfoArrayR[CRunNumPlaceR][13]/(CInfoArrayR[CRunNumPlaceR][11]+1e-15))*CInfoArrayR[CRunNumPlaceR][10] + 1e-15);
                        CInfoArrayR[CRunNumPlaceR][7] = 2*CRatioR*sqrt(CInfoArrayR[CRunNumPlaceR][2]*CInfoArrayR[CRunNumPlaceR][2]*CInfoArrayR[CRunNumPlaceR][3]+CInfoArrayR[CRunNumPlaceR][3]*CInfoArrayR[CRunNumPlaceR][3]*CInfoArrayR[CRunNumPlaceR][2])/pow(CInfoArrayR[CRunNumPlaceR][2]+CRatioR*CInfoArrayR[CRunNumPlaceR][3]+1e-15,2);
                        cout << "Ending Run NumberR " << CInfoArrayR[CRunNumPlaceR][0] << ", C_u3cR = " << CInfoArrayR[CRunNumPlaceR][8] << ", C_u3pR = " << CInfoArrayR[CRunNumPlaceR][9] << ", C_u3mR = " << CInfoArrayR[CRunNumPlaceR][10] << ", Error = " << CInfoArrayR[CRunNumPlaceR][7] << endl;
                }
		if (int(CEvTypeBitsR)==2)
		{
			CT2totalR++;
		}
                if ((CIsSpinValidR==1)&&(CQSquareR<10)&&(CNuR<10)&&(CDpR>-0.04)&&(CDpR<0.058)&&(CReactZR>-0.155)&&(CReactZR<0.175)&&(abs(CThR)<0.07)&&(abs(CPhR)<0.03)&&(C_x_bjR<2)&&((CPShER+(2*CShER))>900)&&(CCerAsumR>400))
                {
                        C_u3cR_real = C_u3cR_real + C_u3cR_real_for_event;
                        CInfoArrayR[CRunNumPlaceR][1]++;
                        if (int(CSpinR)==1)
                        {
                                CInfoArrayR[CRunNumPlaceR][2]++;
                                C_u3pR = C_u3pR + C_u3cR_real_for_event;
                                CInfoArrayR[CRunNumPlaceR][5] = Cu3ppR + Cu3pmR;
                        }
                        if (int(CSpinR)==-1)
                        {
                                CInfoArrayR[CRunNumPlaceR][3]++;
                                C_u3mR = C_u3mR + C_u3cR_real_for_event;
                                CInfoArrayR[CRunNumPlaceR][6] = Cu3mmR + Cu3mpR;
                        }
                        CInfoArrayR[CRunNumPlaceR][4] = C_u3cR_real;
                        if (int(CEvTypeBitsR)==2)
                        {
				CT2unpolcutsR++;
                                CInfoArrayR[CRunNumPlaceR][11]++;
                                if (int(CSpinR)==1){ CInfoArrayR[CRunNumPlaceR][12]++;}
                                if (int(CSpinR)==-1){ CInfoArrayR[CRunNumPlaceR][13]++;}
                        }
                }

                CPrev_u3cR = C_u3cR;
        }
        cout << "NumberR of C Runs: " << CNumOfRunsR << endl;
        outFile << "Possible NumberR of C Runs: " << CNumOfRunsR << endl;
        cout << "Run #  # Unpol   # Spin Up       # Spin Down     Total C         C for up*       C for down*     Error   C for up        C for down      Total T1        # Up T2 # Down T2" << endl;
        outFile << "Run #  # Unpol   # Spin Up       # Spin Down     Total C         C for up*       C for down*     Error   C for up        C for down      Total T1        # Up T2 # Down T2" << endl;
        for (int i=0; i<CNumOfRunsR; i++)
        {
		CChargeScaleR = CChargeScaleR + CInfoArrayR[i][8];
		if (CInfoArrayR[i][0] != 0)
		{
			for (int j=0; j<CNumVarsR; j++)
			{
				cout << CInfoArrayR[i][j] << "    ";
				outFile << CInfoArrayR[i][j] << "    ";
			}
			cout << endl;
			outFile << endl;
		}
		else
		{
			CFalseRunCounterR++;
		}
        }
        cout << "* = Done by adding event-by-event, which might not be working" << endl;
        outFile << "* = Done by adding event-by-event, which might not be working" << endl;
	outFile << "Actual number of C runs: " << (CNumOfRunsR - CFalseRunCounterR) << endl << endl << endl << endl;
// ****************************************************************************************************************





	
	gStyle->SetPalette(1);
	gStyle->SetOptFit(0001);
/*
	// Defines Cuts 1 Canvas
	TCanvas *cutsR1Canvas = new TCanvas("cutsR1Canvas","Cuts 1",1360,800);//x,y
	cutsR1pad01 = new TPad("cutsR1pad01","cutsR1pad01",0.0000,0.5000,0.2500,1.0000,0,0,0);
	cutsR1pad02 = new TPad("cutsR1pad02","cutsR1pad02",0.0000,0.0000,0.2500,0.5000,0,0,0);
	cutsR1pad03 = new TPad("cutsR1pad03","cutsR1pad03",0.2500,0.5000,0.5000,1.0000,0,0,0);
	cutsR1pad04 = new TPad("cutsR1pad04","cutsR1pad04",0.2500,0.0000,0.5000,0.5000,0,0,0);
	cutsR1pad05 = new TPad("cutsR1pad05","cutsR1pad05",0.5000,0.5000,0.7500,1.0000,0,0,0);
	cutsR1pad06 = new TPad("cutsR1pad06","cutsR1pad06",0.5000,0.0000,0.7500,0.5000,0,0,0);
	cutsR1pad07 = new TPad("cutsR1pad07","cutsR1pad07",0.7500,0.5000,1.0000,1.0000,0,0,0);
	cutsR1pad08 = new TPad("cutsR1pad08","cutsR1pad08",0.7500,0.0000,1.0000,0.5000,0,0,0);
	cutsR1pad01->Draw();cutsR1pad02->Draw();cutsR1pad03->Draw();cutsR1pad04->Draw();cutsR1pad05->Draw();cutsR1pad06->Draw();cutsR1pad07->Draw();cutsR1pad08->Draw();

	// Everything below here makes graphs for each section of the canvas

	cutsR1pad01->cd();
	TString titleRdpAyHe = "dp Cut from 3AyHe Runs";
	cout << "Drawing " << titleRdpAyHe << "..." << endl;
	chainAyHeR->Draw("ExTgtCor_R.dp>>AyHedpNoCut(400,-0.08,0.08)", "", "");
	chainAyHeR->Draw("ExTgtCor_R.dp>>AyHedpCut(400,-0.08,0.08)", dpR, "");
	AyHedpNoCut->SetTitle(titleRdpAyHe);
	AyHedpNoCut->Draw();
	AyHedpCut->SetLineColor(kBlack);
	AyHedpCut->SetFillColor(kViolet);
	AyHedpCut->Draw("same");
	cutsR1pad01->Update();

	cutsR1pad02->cd();
	TString titleRdpC = "dp Cut from 12C Runs";
	cout << "Drawing " << titleRdpC << "..." << endl;
	chainCR->Draw("ExTgtCor_R.dp>>CdpNoCut(400,-0.08,0.08)", "", "");
	chainCR->Draw("ExTgtCor_R.dp>>CdpCut(400,-0.08,0.08)", dpR, "");
	CdpNoCut->SetTitle(titleRdpC);
	CdpNoCut->Draw();
	CdpCut->SetLineColor(kBlack);
	CdpCut->SetFillColor(kViolet);
	CdpCut->Draw("same");
	cutsR1pad02->Update();

	cutsR1pad03->cd();
	TString titleRTargetAyHe = "Target Cut for 3AyHe Runs";
	cout << "Drawing " << titleRTargetAyHe << "..." << endl;
	chainAyHeR->Draw("ReactPt_R.z>>AyHeReactZRNoCut(400,-0.3,0.3)", "", "");
	chainAyHeR->Draw("ReactPt_R.z>>AyHeReactZRCut(400,-0.3,0.3)", tagetR, "");
	AyHeReactZRNoCut->SetTitle(titleRTargetAyHe);
	AyHeReactZRNoCut->Draw();
	AyHeReactZRCut->SetLineColor(kBlack);
	AyHeReactZRCut->SetFillColor(kViolet);
	AyHeReactZRCut->Draw("same");
	cutsR1pad03->Update();

	cutsR1pad04->cd();
	TString titleRTargetC = "Target Cut for 12C Runs";
	cout << "Drawing " << titleRTargetC << "..." << endl;
	chainCR->Draw("ReactPt_R.z>>CReactZRNoCut(400,-0.3,0.3)", "", "");
	chainCR->Draw("ReactPt_R.z>>CReactZRCut(400,-0.3,0.3)", tagetR, "");
	CReactZRNoCut->SetTitle(titleRTargetC);
	CReactZRNoCut->Draw();
	CReactZRCut->SetLineColor(kBlack);
	CReactZRCut->SetFillColor(kViolet);
	CReactZRCut->Draw("same");
	cutsR1pad04->Update();

	cutsR1pad05->cd();
        cout << "Drawing 3He Theta and Phi Cut..." << endl;
        TString titleRThetaPhiCut = "3He Theta and Phi";
        TH2F *AyHeThetaPhiCut = new TH2F("AyHeThetaPhiCut",titleRThetaPhiCut,100,-0.05,0.05,100,-0.1,0.1);
        chainAyHeR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>AyHeThetaPhiCut", tagetR, "");
        AyHeThetaPhiCut->SetTitle(titleRThetaPhiCut);
        AyHeThetaPhiCut->SetStats(kFALSE);
        AyHeThetaPhiCut->Draw("COLZ");
        AyHebottom = new TLine(-phboundR,-thboundR,phboundR,-thboundR);
        AyHetop = new TLine(-phboundR,thboundR,phboundR,thboundR);
        AyHeleft = new TLine(-phboundR,-thboundR,-phboundR,thboundR);
        AyHeright = new TLine(phboundR,-thboundR,phboundR,thboundR);
        AyHebottom->SetLineColor(kViolet);
        AyHetop->SetLineColor(kViolet);
        AyHeleft->SetLineColor(kViolet);
        AyHeright->SetLineColor(kViolet);
        AyHebottom->SetLineWidth(3);
        AyHetop->SetLineWidth(3);
        AyHeleft->SetLineWidth(3);
        AyHeright->SetLineWidth(3);
        AyHebottom->Draw("same");
        AyHetop->Draw("same");
        AyHeleft->Draw("same");
        AyHeright->Draw("same");
	cutsR1pad05->Update();

	cutsR1pad06->cd();
        cout << "Drawing 12C Theta and Phi Cut..." << endl;
        TString titleRThetaPhiCut = "12 C Theta and Phi";
        TH2F *CThetaPhiCut = new TH2F("CThetaPhiCut",titleRThetaPhiCut,100,-0.05,0.05,100,-0.1,0.1);
        chainCR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>CThetaPhiCut", tagetR, "");
        CThetaPhiCut->SetTitle(titleRThetaPhiCut);
        CThetaPhiCut->SetStats(kFALSE);
        CThetaPhiCut->Draw("COLZ");
        Cbottom = new TLine(-phboundR,-thboundR,phboundR,-thboundR);
        Ctop = new TLine(-phboundR,thboundR,phboundR,thboundR);
        Cleft = new TLine(-phboundR,-thboundR,-phboundR,thboundR);
        Cright = new TLine(phboundR,-thboundR,phboundR,thboundR);
        Cbottom->SetLineColor(kViolet);
        Ctop->SetLineColor(kViolet);
        Cleft->SetLineColor(kViolet);
        Cright->SetLineColor(kViolet);
        Cbottom->SetLineWidth(3);
        Ctop->SetLineWidth(3);
        Cleft->SetLineWidth(3);
        Cright->SetLineWidth(3);
        Cbottom->Draw("same");
        Ctop->Draw("same");
        Cleft->Draw("same");
        Cright->Draw("same");
	cutsR1pad06->Update();

        cutsR1pad07->cd();
        TString AyHetitleRx = "3He Bjorken x cut";
        AyHetitleRx += " (x=Q^2/[2m*nu])";
        cout << "Drawing " << AyHetitleRx << "..." << endl;
        TH1F *AyHehistx = new TH1F("AyHehistx",AyHetitleRx,bins,xmin,xmax);
        TH1F *AyHehistxcut = new TH1F("AyHehistxcut",AyHetitleRx,bins,xmin,xmax);
        AyHehistx->Sumw2();
        chainAyHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>AyHehistx", cutR && kinematicsR && eventtypeR && dpR && tagetR && thphR && tracksR && cerenkovR && psshR, "E");
        chainAyHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>AyHehistxcut", cutsR, "E");
        AyHehistx->Draw();
        AyHehistxcut->SetFillColor(kViolet);
        AyHehistxcut->Draw("same");
	cutsR1pad07->Update();

	cutsR1pad08->cd();
        TString CtitleRx = "12C Bjorken x cut";
        CtitleRx += " (x=Q^2/[2m*nu])";
        cout << "Drawing " << CtitleRx << "..." << endl;
        TH1F *Chistx = new TH1F("Chistx",CtitleRx,bins,xmin,xmax);
        TH1F *Chistxcut = new TH1F("Chistxcut",CtitleRx,bins,xmin,xmax);
        Chistx->Sumw2();
        chainCR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>Chistx", cutR && kinematicsR && eventtypeR && dpR && tagetR && thphR && tracksR && cerenkovR && psshR, "E");
        chainCR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>Chistxcut", cutsR, "E");
        Chistx->Draw();
        Chistxcut->SetFillColor(kViolet);
        Chistxcut->Draw("same");
	cutsR1pad08->Update();

	TString imagename = "output_files/";
	imagename += titleR;
	imagename += "_cutsR_1.png";
	cutsR1Canvas->Print(imagename);

	// Defines Cuts 2 Canvas
	TCanvas *cutsR2Canvas = new TCanvas("cutsR2Canvas","Cuts 2",1360,800);//x,y
	cutsR2pad01 = new TPad("cutsR2pad01","cutsR2pad01",0.0000,0.5000,0.2500,1.0000,0,0,0);
	cutsR2pad02 = new TPad("cutsR2pad02","cutsR2pad02",0.0000,0.0000,0.2500,0.5000,0,0,0);
	cutsR2pad03 = new TPad("cutsR2pad03","cutsR2pad03",0.2500,0.5000,0.5000,1.0000,0,0,0);
	cutsR2pad04 = new TPad("cutsR2pad04","cutsR2pad04",0.2500,0.0000,0.5000,0.5000,0,0,0);
	cutsR2pad05 = new TPad("cutsR2pad05","cutsR2pad05",0.5000,0.5000,0.7500,1.0000,0,0,0);
	cutsR2pad06 = new TPad("cutsR2pad06","cutsR2pad06",0.5000,0.0000,0.7500,0.5000,0,0,0);
	cutsR2pad07 = new TPad("cutsR2pad07","cutsR2pad07",0.7500,0.5000,1.0000,1.0000,0,0,0);
	cutsR2pad08 = new TPad("cutsR2pad08","cutsR2pad08",0.7500,0.0000,1.0000,0.5000,0,0,0);
	cutsR2pad01->Draw();cutsR2pad02->Draw();cutsR2pad03->Draw();cutsR2pad04->Draw();cutsR2pad05->Draw();cutsR2pad06->Draw();cutsR2pad07->Draw();cutsR2pad08->Draw();

	cutsR2pad01->cd();
	TString titleRQ2WAyHe = "Q2 v. Nu for 3AyHe";
	cout << "Drawing " << titleRQ2WAyHe << "..." << endl;
	chainAyHeR->Draw("PriKineR.Q2:PriKineR.nu>>Q2WAyHe(100,0.3,0.8,400,0,1.6)", cutsR, "");
	Q2WAyHe->SetTitle(titleRQ2WAyHe);
	Q2WAyHe->SetStats(kFALSE);
	Q2WAyHe->Draw("COLZ");
	cutsR2pad01->Update();

	cutsR2pad02->cd();
	TString titleRQ2WC = "Q2 v. Nu for 12C";
	cout << "Drawing " << titleRQ2WC << "..." << endl;
	chainCR->Draw("PriKineR.Q2:PriKineR.nu>>Q2WC(100,0.3,0.8,400,0,1.6,100)", cutsR, "");
	Q2WC->SetTitle(titleRQ2WC);
	Q2WC->SetStats(kFALSE);
	Q2WC->Draw("COLZ");
	cutsR2pad02->Update();

        cutsR2pad03->cd();
        cout << "Drawing 3AyHe Preshower/Shower No Cuts..." << endl;
        TString titleRPsSh = "3AyHe Preshower and Shower - No Cuts";
        TH2F *AyHePsShCut = new TH2F("AyHePsShCut",titleRPsSh,200,1,2500,200,1,1500);
        chainAyHeR->Draw("R.ps.e:R.sh.e>>AyHePsShCut", "", "");
        AyHePsShCut->SetTitle(titleRPsSh);
        AyHePsShCut->SetStats(kFALSE);
        AyHePsShCut->Draw("COLZ");
        AyHepsshcut = new TLine(0,900,450,0);
        AyHepsshcut->SetLineColor(kViolet);
        AyHepsshcut->SetLineWidth(3);
        AyHepsshcut->Draw("same");
	cutsR2pad03->Update();

        cutsR2pad04->cd();
        cout << "Drawing 12C Preshower/Shower No Cuts..." << endl;
        TString CtitleRPsSh = "12C Preshower and Shower - No Cuts";
        TH2F *CPsShCut = new TH2F("CPsShCut",CtitleRPsSh,200,1,2500,200,1,1500);
        chainCR->Draw("R.ps.e:R.sh.e>>CPsShCut", "", "");
        CPsShCut->SetTitle(CtitleRPsSh);
        CPsShCut->SetStats(kFALSE);
        CPsShCut->Draw("COLZ");
        Cpsshcut = new TLine(0,900,450,0);
        Cpsshcut->SetLineColor(kViolet);
        Cpsshcut->SetLineWidth(3);
        Cpsshcut->Draw("same");
	cutsR2pad04->Update();

	cutsR2pad05->cd();
        cout << "Drawing 3AyHe Preshower/Shower with Cuts..." << endl;
        TString AyHetitleRPsSh = "3AyHe Preshower and Shower with cutsR";
        TH2F *AyHePsShCut = new TH2F("AyHePsShCut",AyHetitleRPsSh,200,1,2500,200,1,1500);
        chainAyHeR->Draw("R.ps.e:R.sh.e>>AyHePsShCut", cutsR, "");
        AyHePsShCut->SetTitle(AyHetitleRPsSh);
        AyHePsShCut->SetStats(kFALSE);
        AyHePsShCut->Draw("COLZ");
        AyHepsshcut->Draw("same");
	cutsR2pad05->Update();

	cutsR2pad06->cd();
        cout << "Drawing 12C Preshower/Shower with Cuts..." << endl;
        TString CtitleRPsSh = "12C Preshower and Shower with cutsR";
        TH2F *CPsShCut = new TH2F("CPsShCut",CtitleRPsSh,200,1,2500,200,1,1500);
        chainCR->Draw("R.ps.e:R.sh.e>>CPsShCut", cutsR, "");
        CPsShCut->SetTitle(CtitleRPsSh);
        CPsShCut->SetStats(kFALSE);
        CPsShCut->Draw("COLZ");
        Cpsshcut->Draw("same");
	cutsR2pad06->Update();

	cutsR2pad07->cd();
        TString AyHetitleRcerenkov = "3AyHe Cerenkov Cut";
        cout << "Drawing " << AyHetitleRcerenkov << "..." << endl;
        TH1F *AyHehistcerenkov = new TH1F("AyHehistcerenkov",AyHetitleRcerenkov,200,-25,2000);
        TH1F *AyHehistcerenkovcut = new TH1F("AyHehistcerenkovcut",AyHetitleRcerenkov,200,-25,2000);
        chainAyHeR->Draw("R.cer.asum_c>>AyHehistcerenkov", "", "");
        chainAyHeR->Draw("R.cer.asum_c>>AyHehistcerenkovcut", cerenkovR, "");
        AyHehistcerenkov->SetTitle(AyHetitleRcerenkov);
        AyHehistcerenkov->SetStats(kFALSE);
        AyHehistcerenkovcut->SetFillColor(kViolet);
        AyHehistcerenkov->Draw();
        AyHehistcerenkovcut->Draw("same");
	cutsR2pad07->Update();

	cutsR2pad08->cd();
        TString CtitleRcerenkov = "12C Cerenkov Cut";
        cout << "Drawing " << CtitleRcerenkov << "..." << endl;
        TH1F *Chistcerenkov = new TH1F("Chistcerenkov",CtitleRcerenkov,200,-25,2000);
        TH1F *Chistcerenkovcut = new TH1F("Chistcerenkovcut",CtitleRcerenkov,200,-25,2000);
        chainCR->Draw("R.cer.asum_c>>Chistcerenkov", "", "");
        chainCR->Draw("R.cer.asum_c>>Chistcerenkovcut", cerenkovR, "");
        Chistcerenkov->SetTitle(CtitleRcerenkov);
        Chistcerenkov->SetStats(kFALSE);
        Chistcerenkovcut->SetFillColor(kViolet);
        Chistcerenkov->Draw();
        Chistcerenkovcut->Draw("same");
	cutsR2pad08->Update();

	TString imagename = "output_files/";
	imagename += titleR;
	imagename += "_cutsR_2.png";
	cutsR2Canvas->Print(imagename);
*/


// ***********************************************************************************************************************
	// Defines x_Bj Canvas for just Ay
	TCanvas *xbjCanvasAy = new TCanvas("xbjCanvasAy","x of 12C and 3He for both HRSs for Ay",1360,800);//x,y
//	TCanvas *xbjCanvasAy = new TCanvas("xbjCanvasAy","x of 12C and 3He for Left HRS for Ay",1360,800);//x,y
//	TCanvas *xbjCanvasAy = new TCanvas("xbjCanvasAy","x of 12C and 3He for Right HRS for Ay",1360,800);//x,y
	xbjAypad01 = new TPad("xbjAypad01","xbjAypad01",0.0000,0.5000,0.3333,1.0000,0,0,0);
	xbjAypad02 = new TPad("xbjAypad02","xbjAypad02",0.0000,0.0000,0.3333,0.5000,0,0,0);
	xbjAypad03 = new TPad("xbjAypad03","xbjAypad03",0.3333,0.5000,0.6666,1.0000,0,0,0);
	xbjAypad04 = new TPad("xbjAypad04","xbjAypad04",0.3333,0.0000,0.6666,0.5000,0,0,0);
	xbjAypad05 = new TPad("xbjAypad05","xbjAypad05",0.6666,0.5000,1.0000,1.0000,0,0,0);
	xbjAypad06 = new TPad("xbjAypad06","xbjAypad06",0.6666,0.0000,1.0000,0.5000,0,0,0);
	xbjAypad01->Draw();xbjAypad02->Draw();xbjAypad03->Draw();xbjAypad04->Draw();xbjAypad05->Draw();xbjAypad06->Draw();

	xbjAypad01->cd();
	TString titleC = "x for 12C at Q2 of ";
	titleC += Q2;
	cout << "Drawing " << titleC << "..." << endl;
	TH1F *histCboth = new TH1F("histCboth",titleC,bins,xmin,xmax);
	TH1F *histC = new TH1F("histC",titleC,bins,xmin,xmax);
	histC->Sumw2();
	chainC->Draw("PriKineL.x_bj>>histC", cuts, "E");
	double ClivetimeL;
	ClivetimeL = CT8total/(CTriggerstotal + 1e-15) + 1e-15;
	histC->Scale(1/(CChargeScale*ClivetimeL*rhoC*zC));
//	histC->Draw();

	TString titleRC = "x for 12C at Q2 of ";
	titleRC += Q2;
	cout << "Drawing " << titleRC << "..." << endl;
	TH1F *histCR = new TH1F("histCR",titleRC,bins,xmin,xmax);
	histCR->Sumw2();
	chainCR->Draw("PriKineR.x_bj>>histCR", cutsR, "E");
	double ClivetimeR;
	ClivetimeR = CT2totalR/(CTriggerstotalR+1e-15) + 1e-15;
	cout << "CT2totalR: " << CT2totalR << " CT2unpolcutsR: " << CT2unpolcutsR << endl;
	histCR->Scale(1/(CChargeScaleR*ClivetimeR*rhoC*zC));
//	histCR->Draw();
	histCboth->Add(histC,histCR);
	histCboth->Draw();
	AyOutFile << titleRC << " Linear" << endl;
	AyOutFile << "Bin	Value	Error" << endl;
	for (int i=0; i<bins; i++)
	{
		AyOutFile << histCboth->GetBinCenter(i) << "	";
		AyOutFile << histCboth->GetBinContent(i) << "	";
		AyOutFile << histCboth->GetBinError(i) << endl;
	}


	xbjAypad01->Update();

	xbjAypad02->cd();
	xbjAypad02->SetLogy();
	cout << "Drawing " << titleC << " in log scale..." << endl;
	TH1F *loghistCboth = new TH1F("loghistCboth",titleC,bins,xmin,xmax);
	TH1F *loghistC = new TH1F("loghistC",titleC,bins,xmin,xmax);
	loghistC->Sumw2();
	chainC->Draw("PriKineL.x_bj>>loghistC", cuts, "E");
	loghistC->Scale(1/(CChargeScale*ClivetimeL*rhoC*zC));
//	loghistC->Draw();

	cout << "Drawing " << titleRC << " in log scale..." << endl;
	TH1F *loghistCR = new TH1F("loghistCR",titleRC,bins,xmin,xmax);
	loghistCR->Sumw2();
	chainCR->Draw("PriKineR.x_bj>>loghistCR", cutsR, "E");
	loghistCR->Scale(1/(CChargeScaleR*ClivetimeR*rhoC*zC));
//	loghistCR->Draw();
	loghistCboth->Add(loghistC,loghistCR);
	loghistCboth->Draw();
	xbjAypad02->Update();


	xbjAypad03->cd();
	TString titleAyHe = "x for Ay 3He at Q2 of ";
	titleAyHe += Q2;
	cout << "Drawing " << titleAyHe << "..." << endl;
	TH1F *histAyHeboth = new TH1F("histAyHeboth",titleAyHe,bins,xmin,xmax);
	TH1F *histAyHe = new TH1F("histAyHe",titleAyHe,bins,xmin,xmax);
	histAyHe->Sumw2();
	chainAyHe->Draw("PriKineL.x_bj>>histAyHe", cuts, "E");
	double AyHelivetimeL;
	AyHelivetimeL = AyHeT8total/(AyHeTriggerstotal + 1e-15) + 1e-15;
	cout << "AyHelivetimeL: " << AyHelivetimeL << endl;
	cout << "AyHeT8total: " << AyHeT8total << " AyHeT8unpolcuts: " << AyHeT8unpolcuts << endl;
	histAyHe->Scale(1/(AyHeChargeScale*AyHelivetimeL*rhoAyHe*zHe));
//	histAyHe->Draw();

	TString titleRAyHe = "x for Ay 3He at Q2 of ";
	titleRAyHe += Q2;
	cout << "Drawing " << titleRAyHe << "..." << endl;
	TH1F *histAyHeR = new TH1F("histAyHeR",titleRAyHe,bins,xmin,xmax);
	histAyHeR->Sumw2();
	chainAyHeR->Draw("PriKineR.x_bj>>histAyHeR", cutsR, "E");
	double AyHelivetimeR;
	AyHelivetimeR = AyHeT2totalR/(AyHeTriggerstotalR+1e-15) + 1e-15;
	cout << "AyHeT2totalR: " << AyHeT2totalR << " AyHeT2unpolcutsR: " << AyHeT2unpolcutsR << endl;
	histAyHeR->Scale(1/(AyHeChargeScaleR*AyHelivetimeR*rhoAyHe*zHe));
//	histAyHeR->Draw();
	histAyHeboth->Add(histAyHe,histAyHeR);
//	histAyHeboth->Scale(1/(AyHeChargeScale + AyHeChargeScaleR));
	histAyHeboth->Draw();
	AyOutFile << titleAyHe << " Linear" << endl;
	AyOutFile << "Bin	Value	Error" << endl;
	for (int i=0; i<bins; i++)
	{
		AyOutFile << histAyHeboth->GetBinCenter(i) << "	";
		AyOutFile << histAyHeboth->GetBinContent(i) << "	";
		AyOutFile << histAyHeboth->GetBinError(i) << endl;
	}


	xbjAypad03->Update();


	xbjAypad04->cd();
	xbjAypad04->SetLogy();
	cout << "Drawing " << titleAyHe << " in log scale..." << endl;
	TH1F *loghistAyHeboth = new TH1F("loghistAyHeboth",titleAyHe,bins,xmin,xmax);
	TH1F *loghistAyHe = new TH1F("loghistAyHe",titleAyHe,bins,xmin,xmax);
	loghistAyHe->Sumw2();
	chainAyHe->Draw("PriKineL.x_bj>>loghistAyHe", cuts, "E");
	loghistAyHe->Scale(1/(AyHeChargeScale*AyHelivetimeL*rhoAyHe*zHe));
//	loghistAyHe->Scale(1/AyHeChargeScale);
//	loghistAyHe->Draw();

	cout << "Drawing " << titleRAyHe << " in log scale..." << endl;
	TH1F *loghistAyHeR = new TH1F("loghistAyHeR",titleRAyHe,bins,xmin,xmax);
	loghistAyHeR->Sumw2();
	chainAyHeR->Draw("PriKineR.x_bj>>loghistAyHeR", cutsR, "E");
	loghistAyHeR->Scale(1/(AyHeChargeScaleR*AyHelivetimeR*rhoAyHe*zHe));
//	loghistAyHeR->Scale(1/AyHeChargeScaleR);
//	loghistAyHeR->Draw();
	loghistAyHeboth->Add(loghistAyHe,loghistAyHeR);
//	loghistAyHeboth->Scale(1/(AyHeChargeScale + AyHeChargeScaleR));
	loghistAyHeboth->Draw();
	xbjAypad04->Update();


	xbjAypad05->cd();
	TString titleCoverAyHe = "12C/3He for Q2 of ";
	titleCoverAyHe += Q2;
	cout << "Drawing " << titleCoverAyHe << "..." << endl;
	TH1F *histCoverAyHe = new TH1F("histCoverAyHe",titleCoverAyHe,bins,xmin,xmax);
	histCoverAyHe->Sumw2();
	histCoverAyHe->Divide(histCboth,histAyHeboth);
	histCoverAyHe->Draw("E");
	AyOutFile << titleCoverAyHe << " Linear" << endl;
	AyOutFile << "Bin	Value	Error" << endl;
	for (int i=0; i<bins; i++)
	{
		AyOutFile << histCoverAyHe->GetBinCenter(i) << "	";
		AyOutFile << histCoverAyHe->GetBinContent(i) << "	";
		AyOutFile << histCoverAyHe->GetBinError(i) << endl;
	}

//	TString titleRCoverAyHe = "12C/3He for Q2 of ";
//	titleRCoverAyHe += Q2;
//	cout << "Drawing " << titleRCoverAyHe << "..." << endl;
//	TH1F *histCoverAyHeR = new TH1F("histCoverAyHeR",titleRCoverAyHe,bins,xmin,xmax);
//	histCoverAyHeR->Sumw2();
//	histCoverAyHeR->Divide(histCR,histAyHeR);
//	histCoverAyHeR->Draw("E");
	xbjAypad05->Update();

	xbjAypad06->cd();
	xbjAypad06->SetLogy();
	cout << "Drawing " << titleCoverAyHe << " in log scale..." << endl;
	TH1F *loghistCoverAyHe = new TH1F("loghistCoverAyHe",titleCoverAyHe,bins,xmin,xmax);
	loghistCoverAyHe->Sumw2();
	loghistCoverAyHe->Divide(loghistCboth,loghistAyHeboth);
	loghistCoverAyHe->Draw("E");

//	cout << "Drawing " << titleRCoverAyHe << " in log scale..." << endl;
//	TH1F *loghistCoverAyHeR = new TH1F("loghistCoverAyHeR",titleRCoverAyHe,bins,xmin,xmax);
//	loghistCoverAyHeR->Sumw2();
//	loghistCoverAyHeR->Divide(loghistCR,loghistAyHeR);
//	loghistCoverAyHeR->Draw("E");
	
	AyOutFile << titleCoverAyHe << " Log" << endl;
	AyOutFile << "Bin	Value	Error" << endl;
	for (int i=0; i<bins; i++)
	{
		AyOutFile << loghistCoverAyHe->GetBinCenter(i) << "	";
		AyOutFile << loghistCoverAyHe->GetBinContent(i) << "	";
		AyOutFile << loghistCoverAyHe->GetBinError(i) << endl;
	}

	xbjAypad06->Update();

   
	TString Ayimagename = "output_files/";
	Ayimagename += titleR;
	Ayimagename += "_just_Ay.png";
	xbjCanvasAy->Print(Ayimagename);

// *************************************************************************************

	
// ***********************************************************************************************************************
	// Defines x_Bj Canvas for just eed
	TCanvas *xbjCanvaseed = new TCanvas("xbjCanvaseed","x of 12C and 3He for both HRSs for eed",1360,800);//x,y
//	TCanvas *xbjCanvaseed = new TCanvas("xbjCanvaseed","x of 12C and 3He for just LHRS for eed",1360,800);//x,y
//	TCanvas *xbjCanvaseed = new TCanvas("xbjCanvaseed","x of 12C and 3He for just RHRS for eed",1360,800);//x,y
	xbjeedpad01 = new TPad("xbjeedpad01","xbjeedpad01",0.0000,0.5000,0.3333,1.0000,0,0,0);
	xbjeedpad02 = new TPad("xbjeedpad02","xbjeedpad02",0.0000,0.0000,0.3333,0.5000,0,0,0);
	xbjeedpad03 = new TPad("xbjeedpad03","xbjeedpad03",0.3333,0.5000,0.6666,1.0000,0,0,0);
	xbjeedpad04 = new TPad("xbjeedpad04","xbjeedpad04",0.3333,0.0000,0.6666,0.5000,0,0,0);
	xbjeedpad05 = new TPad("xbjeedpad05","xbjeedpad05",0.6666,0.5000,1.0000,1.0000,0,0,0);
	xbjeedpad06 = new TPad("xbjeedpad06","xbjeedpad06",0.6666,0.0000,1.0000,0.5000,0,0,0);
	xbjeedpad01->Draw();xbjeedpad02->Draw();xbjeedpad03->Draw();xbjeedpad04->Draw();xbjeedpad05->Draw();xbjeedpad06->Draw();

	xbjeedpad01->cd();
	TString titleRC = "x for 12C at Q2 of ";
	titleRC += Q2;
	cout << "Drawing " << titleRC << "..." << endl;
//	TH1F *histCR = new TH1F("histCR",titleRC,bins,xmin,xmax);
//	histCR->Sumw2();
//	chainCR->Draw("PriKineR.x_bj>>histCR", cutsR, "E");
//	histCR->Scale(1/CChargeScaleR);
	histCR->Draw();
	eedOutFile << titleRC << " Linear" << endl;
	eedOutFile << "Bin	Value	Error" << endl;
	for (int i=0; i<bins; i++)
	{
		eedOutFile << histCR->GetBinCenter(i) << "	";
		eedOutFile << histCR->GetBinContent(i) << "	";
		eedOutFile << histCR->GetBinError(i) << endl;
	}


	xbjeedpad01->Update();

	xbjeedpad02->cd();
	xbjeedpad02->SetLogy();
	cout << "Drawing " << titleRC << " in log scale..." << endl;
//	TH1F *loghistCR = new TH1F("loghistCR",titleRC,bins,xmin,xmax);
//	loghistCR->Sumw2();
//	chainCR->Draw("PriKineR.x_bj>>loghistCR", cutsR, "E");
//	loghistCR->Scale(1/CChargeScaleR);
	loghistCR->Draw();
	xbjeedpad02->Update();


	xbjeedpad03->cd();
	TString titleReedHe = "x for 3He eed at Q2 of ";
	titleReedHe += Q2;
	cout << "Drawing " << titleReedHe << "..." << endl;
	TH1F *histeedHeR = new TH1F("histeedHeR",titleReedHe,bins,xmin,xmax);
	histeedHeR->Sumw2();
	chaineedHeR->Draw("PriKineR.x_bj>>histeedHeR", cutsR, "E");
	double eedHelivetimeR;
	eedHelivetimeR = eedHeT2totalR/(eedHeTriggerstotalR + 1e-15) + 1e-15;
	cout << "eedHeT2totalR: " << eedHeT2totalR << " eedHeT2unpolcutsR: " << eedHeT2unpolcutsR << endl;
	histeedHeR->Scale(1/(eedHeChargeScaleR*eedHelivetimeR*rhoeedHe*zHe));
	histeedHeR->Draw();
	eedOutFile << titleReedHe << " Linear" << endl;
	eedOutFile << "Bin	Value	Error" << endl;
	for (int i=0; i<bins; i++)
	{
		eedOutFile << histeedHeR->GetBinCenter(i) << "	";
		eedOutFile << histeedHeR->GetBinContent(i) << "	";
		eedOutFile << histeedHeR->GetBinError(i) << endl;
	}


	xbjeedpad03->Update();


	xbjeedpad04->cd();
	xbjeedpad04->SetLogy();
	cout << "Drawing " << titleReedHe << " in log scale..." << endl;
	TH1F *loghisteedHeR = new TH1F("loghisteedHeR",titleReedHe,bins,xmin,xmax);
	loghisteedHeR->Sumw2();
	chaineedHeR->Draw("PriKineR.x_bj>>loghisteedHeR", cutsR, "E");
	loghisteedHeR->Scale(1/(eedHeChargeScaleR*eedHelivetimeR*rhoeedHe*zHe));
	loghisteedHeR->Draw();
	xbjeedpad04->Update();


	xbjeedpad05->cd();
	TString titleCovereedHe = "12C/3He for Q2 of ";
	titleCovereedHe += Q2;
	cout << "Drawing " << titleCovereedHe << "..." << endl;
	TH1F *histCovereedHe = new TH1F("histCovereedHe",titleCovereedHe,bins,xmin,xmax);
	histCovereedHe->Sumw2();
	histCovereedHe->Divide(histCR,histeedHeR);
	histCovereedHe->Draw("E");
	eedOutFile << titleCovereedHe << " Linear" << endl;
	eedOutFile << "Bin	Value	Error" << endl;
	for (int i=0; i<bins; i++)
	{
		eedOutFile << histCovereedHe->GetBinCenter(i) << "	";
		eedOutFile << histCovereedHe->GetBinContent(i) << "	";
		eedOutFile << histCovereedHe->GetBinError(i) << endl;
	}


	xbjeedpad05->Update();

	xbjeedpad06->cd();
	xbjeedpad06->SetLogy();
	cout << "Drawing " << titleCovereedHe << " in log scale..." << endl;
	TH1F *loghistCovereedHe = new TH1F("loghistCovereedHe",titleCovereedHe,bins,xmin,xmax);
	loghistCovereedHe->Sumw2();
	loghistCovereedHe->Divide(loghistCR,loghisteedHeR);
	loghistCovereedHe->Draw("E");
//	loghistCovereedHeR->Draw("E");
	eedOutFile << titleCovereedHe << " Log" << endl;
	eedOutFile << "Bin	Value	Error" << endl;
	for (int i=0; i<bins; i++)
	{
		eedOutFile << histCovereedHe->GetBinCenter(i) << "	";
		eedOutFile << histCovereedHe->GetBinContent(i) << "	";
		eedOutFile << histCovereedHe->GetBinError(i) << endl;
	}


	xbjeedpad06->Update();

	TString eedimagename = "output_files/";
	eedimagename += titleR;
	eedimagename += "_just_eed.png";
	xbjCanvaseed->Print(eedimagename);

// *******************************************************************************************************

// ***********************************************************************************************************************
	// Defines x_Bj Canvas for Ay and e,e'd
	TCanvas *xbjCanvasAll = new TCanvas("xbjCanvasAll","x of 12C and 3He for both HRSs for All",1360,800);//x,y
//	TCanvas *xbjCanvasAll = new TCanvas("xbjCanvasAll","x of 12C and 3He for LHRS for All",1360,800);//x,y
//	TCanvas *xbjCanvasAll = new TCanvas("xbjCanvasAll","x of 12C and 3He for RHRS for All",1360,800);//x,y
	xbjAllpad01 = new TPad("xbjAllpad01","xbjAllpad01",0.0000,0.5000,0.3333,1.0000,0,0,0);
	xbjAllpad02 = new TPad("xbjAllpad02","xbjAllpad02",0.0000,0.0000,0.3333,0.5000,0,0,0);
	xbjAllpad03 = new TPad("xbjAllpad03","xbjAllpad03",0.3333,0.5000,0.6666,1.0000,0,0,0);
	xbjAllpad04 = new TPad("xbjAllpad04","xbjAllpad04",0.3333,0.0000,0.6666,0.5000,0,0,0);
	xbjAllpad05 = new TPad("xbjAllpad05","xbjAllpad05",0.6666,0.5000,1.0000,1.0000,0,0,0);
	xbjAllpad06 = new TPad("xbjAllpad06","xbjAllpad06",0.6666,0.0000,1.0000,0.5000,0,0,0);
	xbjAllpad01->Draw();xbjAllpad02->Draw();xbjAllpad03->Draw();xbjAllpad04->Draw();xbjAllpad05->Draw();xbjAllpad06->Draw();

	xbjAllpad01->cd();
//	TString titleC = "x for 12C at Q2 of ";
//	titleC += Q2;
	cout << "Drawing " << titleC << "..." << endl;
//	TH1F *histCboth = new TH1F("histCboth",titleC,bins,xmin,xmax);
//	TH1F *histC = new TH1F("histC",titleC,bins,xmin,xmax);
//	histC->Sumw2();
//	chainC->Draw("PriKineL.x_bj>>histC", cuts, "E");
//	histC->Scale(1/CChargeScale);
//	histC->Draw();

//	TString titleRC = "x for 12C at Q2 of ";
//	titleRC += Q2;
//	cout << "Drawing " << titleRC << "..." << endl;
//	TH1F *histCR = new TH1F("histCR",titleRC,bins,xmin,xmax);
//	histCR->Sumw2();
//	chainCR->Draw("PriKineR.x_bj>>histCR", cutsR, "E");
//	histCR->Scale(1/CChargeScaleR);
//	histCR->Draw();
//	histCboth->Add(histC,histCR);
//	histCboth->Scale(1/(CChargeScale + CChargeScaleR));
	histCboth->Draw();
	AyeedOutFile << titleC << " Linear" << endl;
	AyeedOutFile << "Bin	Value	Error" << endl;
	for (int i=0; i<bins; i++)
	{
		AyeedOutFile << histCboth->GetBinCenter(i) << "	";
		AyeedOutFile << histCboth->GetBinContent(i) << "	";
		AyeedOutFile << histCboth->GetBinError(i) << endl;
	}


	xbjAllpad01->Update();

	xbjAllpad02->cd();
	xbjAllpad02->SetLogy();
	cout << "Drawing " << titleC << " in log scale..." << endl;
//	TH1F *loghistCboth = new TH1F("loghistCboth",titleC,bins,xmin,xmax);
//	TH1F *loghistC = new TH1F("loghistC",titleC,bins,xmin,xmax);
//	loghistC->Sumw2();
//	chainC->Draw("PriKineL.x_bj>>loghistC", cuts, "E");
//	loghistC->Scale(1/CChargeScale);
//	loghistC->Draw();

//	cout << "Drawing " << titleRC << " in log scale..." << endl;
//	TH1F *loghistCR = new TH1F("loghistCR",titleRC,bins,xmin,xmax);
//	loghistCR->Sumw2();
//	chainCR->Draw("PriKineR.x_bj>>loghistCR", cutsR, "E");
//	loghistCR->Scale(1/CChargeScaleR);
//	loghistCR->Draw();
//	loghistCboth->Add(loghistC,loghistCR);
//	loghistCboth->Scale(1/(CChargeScale + CChargeScaleR));
	loghistCboth->Draw();
	xbjAllpad02->Update();


	xbjAllpad03->cd();
	TString titleRAllHe = "x for all 3He at Q2 of ";
	titleRAllHe += Q2;
	cout << "Drawing " << titleRAllHe << "..." << endl;
	TH1F *histAllHeR = new TH1F("histAllHeR",titleRAllHe,bins,xmin,xmax);
	TH1F *histAllHeboth = new TH1F("histAllHeR",titleRAllHe,bins,xmin,xmax);
//	histAllHeR->Draw();
	histAllHeR->Add(histAyHeR,histeedHeR);
	histAllHeboth->Add(histAyHe,histAllHeR);
//	histAllHeboth->Scale(1/(AllHeChargeScale + AllHeChargeScaleR));
	histAllHeboth->Draw();
	AyeedOutFile << titleRAllHe << " Linear" << endl;
	AyeedOutFile << "Bin	Value	Error" << endl;
	for (int i=0; i<bins; i++)
	{
		AyeedOutFile << histAllHeboth->GetBinCenter(i) << "	";
		AyeedOutFile << histAllHeboth->GetBinContent(i) << "	";
		AyeedOutFile << histAllHeboth->GetBinError(i) << endl;
	}


	xbjAllpad03->Update();


	xbjAllpad04->cd();
	xbjAllpad04->SetLogy();
	TH1F *loghistAllHeR = new TH1F("loghistAllHeR",titleRAllHe,bins,xmin,xmax);
	TH1F *loghistAllHeboth = new TH1F("loghistAllHeboth",titleRAllHe,bins,xmin,xmax);
	cout << "Drawing " << titleRAllHe << " in log scale..." << endl;
	TH1F *loghistAllHeR = new TH1F("loghistAllHeR",titleRAllHe,bins,xmin,xmax);
	loghistAllHeR->Sumw2();
	loghistAllHeR->Add(loghistAyHeR,loghisteedHeR);
	loghistAllHeboth->Add(loghistAyHe,loghistAllHeR);
//	loghistAllHeboth->Scale(1/(AllHeChargeScale + AllHeChargeScaleR));
	loghistAllHeboth->Draw();
	xbjAllpad04->Update();


	xbjAllpad05->cd();
	TString titleCoverAllHe = "12C/3He for Q2 of ";
	titleCoverAllHe += Q2;
	cout << "Drawing " << titleCoverAllHe << "..." << endl;
	TH1F *histCoverAllHe = new TH1F("histCoverAllHe",titleCoverAllHe,bins,xmin,xmax);
	histCoverAllHe->Sumw2();
	histCoverAllHe->Divide(histCboth,histAllHeboth);
	histCoverAllHe->Draw("E");
	AyeedOutFile << titleCoverAllHe << " Linear" << endl;
	AyeedOutFile << "Bin	Value	Error" << endl;
	for (int i=0; i<bins; i++)
	{
		AyeedOutFile << histCoverAllHe->GetBinCenter(i) << "	";
		AyeedOutFile << histCoverAllHe->GetBinContent(i) << "	";
		AyeedOutFile << histCoverAllHe->GetBinError(i) << endl;
	}


//	TString titleRCoverAllHe = "12C/3He for Q2 of ";
//	titleRCoverAllHe += Q2;
//	cout << "Drawing " << titleRCoverAllHe << "..." << endl;
//	TH1F *histCoverAllHeR = new TH1F("histCoverAllHeR",titleRCoverAllHe,bins,xmin,xmax);
//	histCoverAllHeR->Sumw2();
//	histCoverAllHeR->Divide(histCR,histAllHeR);
//	histCoverAllHeR->Draw("E");
	xbjAllpad05->Update();

	xbjAllpad06->cd();
	xbjAllpad06->SetLogy();
	cout << "Drawing " << titleCoverAllHe << " in log scale..." << endl;
	TH1F *loghistCoverAllHe = new TH1F("loghistCoverAllHe",titleCoverAllHe,bins,xmin,xmax);
	loghistCoverAllHe->Sumw2();
	loghistCoverAllHe->Divide(loghistCboth,loghistAllHeboth);
	loghistCoverAllHe->Draw("E");
	AyeedOutFile << titleCoverAllHe << " Log" << endl;
	AyeedOutFile << "Bin	Value	Error" << endl;
	for (int i=0; i<bins; i++)
	{
		AyeedOutFile << loghistCoverAllHe->GetBinCenter(i) << "	";
		AyeedOutFile << loghistCoverAllHe->GetBinContent(i) << "	";
		AyeedOutFile << loghistCoverAllHe->GetBinError(i) << endl;
	}


//	cout << "Drawing " << titleRCoverAllHe << " in log scale..." << endl;
//	TH1F *loghistCoverAllHeR = new TH1F("loghistCoverAllHeR",titleRCoverAllHe,bins,xmin,xmax);
//	loghistCoverAllHeR->Sumw2();
//	loghistCoverAllHeR->Divide(loghistCR,loghistAllHeR);
//	loghistCoverAllHeR->Draw("E");
	xbjAllpad06->Update();

   
	TString imagename = "output_files/";
	imagename += titleR;
	imagename += "_Ay_and_eed.png";
	xbjCanvasAll->Print(imagename);

// *************************************************************************************




	outFile.close();
	AyOutFile.close();
	eedOutFile.close();
	AyeedOutFile.close();

	cout << "All done!" << endl;


}
