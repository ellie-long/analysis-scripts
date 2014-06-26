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

#include <iostream>
#include <fstream>
using namespace std;

void src_fit(){

	int CRunNumber=1699;
//	int endCRunNumber=1699;
	int endCRunNumber=1828;
	int HeRunNumber=1686;
//	int endHeRunNumber=1687;
	int endHeRunNumber=1882;
	TString Q2 = "1.0";
	//Range is of the form (bins, start, end)
	//  TString range = "(800,0.5,4.0)";
	double bins = 50;
	double xmin = 0.5;
	double xmax = 2.0;
	TString title = "12C_over_3He_x-Q2_of_";
	title += Q2;
	title += "-C_Runs_";
	title += CRunNumber;
	title += "-";
	title += endCRunNumber;
	title += "_He_Runs_";
	title += HeRunNumber;
	title += "-";
	title += endHeRunNumber;

	int CRunNumberR=20591;
	int endCRunNumberR=22461;
//	int endCRunNumberR=20592;
	int HeRunNumberR=20596;
//	int endHeRunNumberR=20597;
	int endHeRunNumberR=22489;
	TString titleR = "12C_over_3He_x-Q2_of_";
	titleR += Q2;
	titleR += "-C_Runs_";
	titleR += CRunNumberR;
	titleR += "-";
	titleR += endCRunNumberR;
	titleR += "_He_Runs_";
	titleR += HeRunNumberR;
	titleR += "-";
	titleR += endHeRunNumberR;

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
	TCut dp = "ExTgtCor_L.dp>-0.04 && ExTgtCor_L.dp<0.053";
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
	TCut dpR = "ExTgtCor_R.dp>-0.04 && ExTgtCor_R.dp<0.053";
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


        const int HeNumOfRuns = endHeRunNumber - HeRunNumber + 5;
        const int HeNumVars = 14;
        // HeInfoArray[runNum][0] = Run Number
        // HeInfoArray[runNum][1] = # of Unpolarized Events past cuts
        // HeInfoArray[runNum][2] = # of Spin Up Events past cuts
        // HeInfoArray[runNum][3] = # Spin Down Events past cuts
        // HeInfoArray[runNum][4] = Event-by-event u3c 
        // HeInfoArray[runNum][5] = Event-by-event u3pp + u3pm
        // HeInfoArray[runNum][6] = Event-by-event u3mm + u3mp
        // HeInfoArray[runNum][7] = Error
        // HeInfoArray[runNum][8] = End-of-run u3c
        // HeInfoArray[runNum][9] = End-of-run u3pp + u3pm
        // HeInfoArray[runNum][10] = End-of-run u3mm + u3mp
        // HeInfoArray[runNum][11] = # of total T2 events 
        // HeInfoArray[runNum][12] = # of Spin Up T2 events
        // HeInfoArray[runNum][13] = # of Spin Down T2 events
        double HeInfoArray[HeNumOfRuns][HeNumVars];
        for (int i=0; i<HeNumOfRuns; i++)
        {
                for (int j=0; j<HeNumVars; j++)
                {
                        HeInfoArray[i][j]=0;
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
        const int HeNumOfRunsR = endHeRunNumberR - HeRunNumberR + 5;
        const int HeNumVarsR = 14;
        // HeInfoArrayR[runNum][0] = Run NumberR
        // HeInfoArrayR[runNum][1] = # of Unpolarized Events past cuts
        // HeInfoArrayR[runNum][2] = # of Spin Up Events past cuts
        // HeInfoArrayR[runNum][3] = # Spin Down Events past cuts
        // HeInfoArrayR[runNum][4] = Event-by-event u3c 
        // HeInfoArrayR[runNum][5] = Event-by-event u3pp + u3pm
        // HeInfoArrayR[runNum][6] = Event-by-event u3mm + u3mp
        // HeInfoArrayR[runNum][7] = Error
        // HeInfoArrayR[runNum][8] = End-of-run u3c
        // HeInfoArrayR[runNum][9] = End-of-run u3pp + u3pm
        // HeInfoArrayR[runNum][10] = End-of-run u3mm + u3mp
        // HeInfoArrayR[runNum][11] = # of total T2 events 
        // HeInfoArrayR[runNum][12] = # of Spin Up T2 events
        // HeInfoArrayR[runNum][13] = # of Spin Down T2 events
        double HeInfoArrayR[HeNumOfRunsR][HeNumVarsR];
        for (int i=0; i<HeNumOfRunsR; i++)
        {
                for (int j=0; j<HeNumVarsR; j++)
                {
                        HeInfoArrayR[i][j]=0;
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
	TChain* chainHeR = new TChain("T");

	gStyle->SetErrorX(.25);
	gStyle->SetEndErrorSize(.25);
	ifstream inp;
	ofstream out;

	TString filenameCR;
	TString filenameHeR;

	TChain* chainC = new TChain("T");
	TChain* chainHe = new TChain("T");

	TString filenameC;
	TString filenameHe;


// Below is the loop for adding chains for the Carbon run
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



// Below is the loop for adding chains for the 3He run

	for (int thisHeRunNumber=HeRunNumber;thisHeRunNumber<(endHeRunNumber+1); thisHeRunNumber++)
	{
		// Going to next set of Q2 runs
/*		if (Q2=="1.0")
		{
			if(thisHeRunNumber=20791){thisHeRunNumber=22393;}
		}
*/
		// Skipping Vertical Carbon Runs
		if(thisHeRunNumber==1692){thisHeRunNumber=1704;}
		if(thisHeRunNumber==1825){thisHeRunNumber=1832;}
		if(thisHeRunNumber==1826){thisHeRunNumber=1832;}
		if(thisHeRunNumber==1827){thisHeRunNumber=1832;}
		if(thisHeRunNumber==1828){thisHeRunNumber=1832;}

		// Skipping Longitudinal Carbon Runs

		// Skipping Transverse Carbon Runs


		for (int t=0; t<1000;t++)
		{
			filenameHe = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_L_";
			filenameHe += thisHeRunNumber;
			if (t!=0)
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
				t=9999999;
			}

		}

// Uncommenting the line below will let the code only go through one run (Good for debugging purposes)
//	thisHeRunNumber = 999999999;
	}


// Below is the loop for adding chains for the Carbon run
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





// Below is the loop for adding chains for the 3He run

	for (int thisHeRunNumberR=HeRunNumberR;thisHeRunNumberR<(endHeRunNumberR+1); thisHeRunNumberR++)
	{
		// Going to next set of Q2 runs
/*		if (Q2=="1.0")
		{
			if(thisHeRunNumberR==20791){thisHeRunNumberR=22393;}
		}
*/
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
		if(thisHeRunNumberR==20791){thisHeRunNumberR=22393;}
//		if(thisHeRunNumberR==20791){thisHeRunNumberR=20814;}
		if(thisHeRunNumberR==20792){thisHeRunNumberR=20814;}

		// Skipping Longitudinal Carbon Runs
		if(thisHeRunNumberR==22380){thisHeRunNumberR=22393;}
		if(thisHeRunNumberR==22389){thisHeRunNumberR=22393;}
		if(thisHeRunNumberR==22425){thisHeRunNumberR=22436;}
		if(thisHeRunNumberR==22426){thisHeRunNumberR=22436;}

		// Skipping Transverse Carbon Runs
		if(thisHeRunNumberR==22461){thisHeRunNumberR=22465;}
		if(thisHeRunNumberR==20591){thisHeRunNumberR=20596;}
		if(thisHeRunNumberR==22397){thisHeRunNumberR=22398;}
		for (int t=0; t<1000;t++)
		{
			filenameHeR = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_R_";
			filenameHeR += thisHeRunNumberR;
			if (t!=0)
			{
				filenameHeR += "_";
				filenameHeR += t;
			}
			filenameHeR += ".root";
			ifstream ifileHe(filenameHeR);
			if (ifileHe)
			{
				cout << "Adding file to chainHeR: " << filenameHeR << endl;
				chainHeR->Add(filenameHeR);
			}
			else
			{
				cout << "File " << filenameHeR << " does not exist. Ending here." << endl;
				t=9999999;
			}

		}

// Uncommenting the line below will let the code only go through one run (Good for debugging purposes)
//	thisHeRunNumberR = 999999999;

	}

// This section will put the 3He root data into doubles so that
// it can be calculated through C++ instead of as histograms
// ****************************************************************************************************************
        int HeNumberOfEvents;
        double HeIsSpinValid;
        double HeQSquare;
        double HeNu;
        double HeEvTypeBits;
        double HeDp;
        double HeReactZ;
        double HeTh;
        double HePh;
        double He_x_bj;
        double HeShE;
        double HePShE;
        double HeCerAsum;
        double HeRunNum;
        double HeSpin;
        int HeRunNumberForArray;
        double He_u3c;
        double He_u3pp;
        double He_u3pm;
        double He_u3mm;
        double He_u3mp;

        HeNumberOfEvents = int(chainHe->GetEntries());
        chainHe->SetBranchAddress("he3.IsSpinValid", &HeIsSpinValid);
        chainHe->SetBranchAddress("he3.Spin", &HeSpin);
        chainHe->SetBranchAddress("PriKineL.Q2", &HeQSquare);
        chainHe->SetBranchAddress("PriKineL.nu", &HeNu);
        chainHe->SetBranchAddress("DL.evtypebits", &HeEvTypeBits);
        chainHe->SetBranchAddress("ExTgtCor_L.dp", &HeDp);
        chainHe->SetBranchAddress("ExTgtCor_L.th", &HeTh);
        chainHe->SetBranchAddress("ExTgtCor_L.ph", &HePh);
        chainHe->SetBranchAddress("ReactPt_L.z", &HeReactZ);
        chainHe->SetBranchAddress("PriKineL.x_bj", &He_x_bj);
        chainHe->SetBranchAddress("L.prl2.e", &HeShE);
        chainHe->SetBranchAddress("L.prl1.e", &HePShE);
        chainHe->SetBranchAddress("L.cer.asum_c", &HeCerAsum);
        chainHe->SetBranchAddress("g.runnum", &HeRunNum);
        chainHe->SetBranchAddress("evleft_u3c", &He_u3c);
        chainHe->SetBranchAddress("evleft_u3pp", &He_u3pp);
        chainHe->SetBranchAddress("evleft_u3pm", &He_u3pm);
        chainHe->SetBranchAddress("evleft_u3mm", &He_u3mm);
        chainHe->SetBranchAddress("evleft_u3mp", &He_u3mp);

        cout << "Number of events: " << HeNumberOfEvents << endl;
        chainHe->GetEntry(1);
        HeRunNumberForArray = int(HeRunNum);
        int HePrevRunNumber = HeRunNumberForArray;
        int HeRunNumPlace = 0;
        HeInfoArray[HeRunNumPlace][0] = HeRunNumberForArray;
        double HePrev_u3c = He_u3c;
        double He_u3p = 0;
        double He_u3m = 0;
        double He_u3c_real = 0;
        double He_u3c_real_for_event = 0;
        double HeEndOfRun_u3c = 0;
        double HeEndOfRun_u3p = 0;
        double HeEndOfRun_u3m = 0;
        int HeRealNumOfRuns = 1;
        double HeRatio = 1e-15;
	int HeFalseRunCounter = 0;
	double HeChargeScale = 1e-15;
        for (int i=0; i<HeNumberOfEvents; i++)
        {
                chainHe->GetEntry(i);
                HeRunNumberForArray = int(HeRunNum);
                He_u3c_real_for_event = He_u3c - HePrev_u3c;

                if (i%10000 == 0)
                {
                        cout << "Event Number " << i << ", Run Number " << HeRunNumberForArray << endl;
                        cout << "He_u3c: " << He_u3c << "  He_u3pp: " << He_u3pp << "  He_u3pm: " << He_u3pm << "  He_u3mm: " << He_u3mm << "  He_u3mp: " << He_u3mp << " Error: " << HeInfoArray[HeRunNumPlace][7] << ", HeEvTypeBits = " << HeEvTypeBits << endl;
                }
                if (HeRunNumberForArray > HePrevRunNumber)
                {
                        He_u3c_real = 0;
                        He_u3p = 0;
                        He_u3m = 0;
                        chainHe->GetEntry(i-1);
                        HeEndOfRun_u3c = He_u3c;
                        HeEndOfRun_u3p = He_u3pp + He_u3pm;
                        HeEndOfRun_u3m = He_u3mm + He_u3mp;
                        HeInfoArray[HeRunNumPlace][8] = HeEndOfRun_u3c;
                        HeInfoArray[HeRunNumPlace][9] = HeEndOfRun_u3p;
                        HeInfoArray[HeRunNumPlace][10] = HeEndOfRun_u3m;
//                      HeInfoArray[HeRunNumPlace][7] = 1/(sqrt(HeInfoArray[HeRunNumPlace][1]));
                        HeRatio = ((HeInfoArray[HeRunNumPlace][12]/(HeInfoArray[HeRunNumPlace][11] + 1e-15))*HeInfoArray[HeRunNumPlace][9])/((HeInfoArray[HeRunNumPlace][13]/(HeInfoArray[HeRunNumPlace][11] + 1e-15))*HeInfoArray[HeRunNumPlace][10]+1e-15);
                        HeInfoArray[HeRunNumPlace][7] = 2*HeRatio*sqrt(HeInfoArray[HeRunNumPlace][2]*HeInfoArray[HeRunNumPlace][2]*HeInfoArray[HeRunNumPlace][3]+HeInfoArray[HeRunNumPlace][3]*HeInfoArray[HeRunNumPlace][3]*HeInfoArray[HeRunNumPlace][2])/pow(HeInfoArray[HeRunNumPlace][2]+HeRatio*HeInfoArray[HeRunNumPlace][3]+1e-15,2);

                        cout << "Ending Run Number " << HeInfoArray[HeRunNumPlace][0] << ", He_u3c = " << HeInfoArray[HeRunNumPlace][8] << ", He_u3p = " << HeInfoArray[HeRunNumPlace][9] << ", He_u3m = " << HeInfoArray[HeRunNumPlace][10] << ", Error = " << HeInfoArray[HeRunNumPlace][7] << endl;
                        chainHe->GetEntry(i);
                        HeRunNumPlace++;
                        HePrevRunNumber = HeRunNumberForArray;
                        HeInfoArray[HeRunNumPlace][0] = HeRunNumberForArray;
                        HeRealNumOfRuns++;
                }
                if (i==(HeNumberOfEvents-1))
                {
                        chainHe->GetEntry(i-1);
                        HeEndOfRun_u3c = He_u3c;
                        HeEndOfRun_u3p = He_u3pp + He_u3pm;
                        HeEndOfRun_u3m = He_u3mm + He_u3mp;
                        HeInfoArray[HeRunNumPlace][8] = HeEndOfRun_u3c;
                        HeInfoArray[HeRunNumPlace][9] = HeEndOfRun_u3p;
                        HeInfoArray[HeRunNumPlace][10] = HeEndOfRun_u3m;
//                      HeInfoArray[HeRunNumPlace][7] = 1/(sqrt(HeInfoArray[HeRunNumPlace][1]));
                        HeRatio = ((HeInfoArray[HeRunNumPlace][12]/(HeInfoArray[HeRunNumPlace][11] + 1e-15))*HeInfoArray[HeRunNumPlace][9])/((HeInfoArray[HeRunNumPlace][13]/(HeInfoArray[HeRunNumPlace][11] + 1e-15))*HeInfoArray[HeRunNumPlace][10] + 1e-15);
                        HeInfoArray[HeRunNumPlace][7] = 2*HeRatio*sqrt(HeInfoArray[HeRunNumPlace][2]*HeInfoArray[HeRunNumPlace][2]*HeInfoArray[HeRunNumPlace][3]+HeInfoArray[HeRunNumPlace][3]*HeInfoArray[HeRunNumPlace][3]*HeInfoArray[HeRunNumPlace][2])/pow(HeInfoArray[HeRunNumPlace][2]+HeRatio*HeInfoArray[HeRunNumPlace][3]+1e-15,2);
                        cout << "Ending Run Number " << HeInfoArray[HeRunNumPlace][0] << ", He_u3c = " << HeInfoArray[HeRunNumPlace][8] << ", He_u3p = " << HeInfoArray[HeRunNumPlace][9] << ", He_u3m = " << HeInfoArray[HeRunNumPlace][10] << ", Error = " << HeInfoArray[HeRunNumPlace][7] << endl;
                }
                if ((HeIsSpinValid==1)&&(HeQSquare<10)&&(HeNu<10)&&(HeDp>-0.04)&&(HeDp<0.058)&&(HeReactZ>-0.155)&&(HeReactZ<0.175)&&(abs(HeTh)<0.07)&&(abs(HePh)<0.03)&&(He_x_bj<2)&&((HePShE+(2*HeShE))>900)&&(HeCerAsum>400))
                {
                        He_u3c_real = He_u3c_real + He_u3c_real_for_event;
                        HeInfoArray[HeRunNumPlace][1]++;
                        if (int(HeSpin)==1)
                        {
                                HeInfoArray[HeRunNumPlace][2]++;
                                He_u3p = He_u3p + He_u3c_real_for_event;
                                HeInfoArray[HeRunNumPlace][5] = He_u3pp + He_u3pm;
                        }
                        if (int(HeSpin)==-1)
                        {
                                HeInfoArray[HeRunNumPlace][3]++;
                                He_u3m = He_u3m + He_u3c_real_for_event;
                                HeInfoArray[HeRunNumPlace][6] = He_u3mm + He_u3mp;
                        }
                        HeInfoArray[HeRunNumPlace][4] = He_u3c_real;
                        if (int(HeEvTypeBits)==2)
                        {
                                HeInfoArray[HeRunNumPlace][11]++;
                                if (int(HeSpin)==1){ HeInfoArray[HeRunNumPlace][12]++;}
                                if (int(HeSpin)==-1){ HeInfoArray[HeRunNumPlace][13]++;}
                        }
                }

                HePrev_u3c = He_u3c;
        }
        cout << "Number of He Runs: " << HeNumOfRuns << endl;
        outFile << "Possible Number of He Runs: " << HeNumOfRuns << endl;
        cout << "Run #  # Unpol   # Spin Up   # Spin Down     Total C         C for up*       C for down*     Error   C for up        C for down      Total T1        # Up T2 # Down T2" << endl;
        outFile << "Run #  # Unpol   # Spin Up   # Spin Down     Total C         C for up*       C for down*     Error   C for up        C for down      Total T1        # Up T2 # Down T2" << endl;
        for (int i=0; i<HeNumOfRuns; i++)
        {
		HeChargeScale = HeChargeScale + HeInfoArray[i][8];
		if (HeInfoArray[i][0] != 0)
		{
			for (int j=0; j<HeNumVars; j++)
			{
				cout << HeInfoArray[i][j] << "    ";
				outFile << HeInfoArray[i][j] << "    ";
			}
			cout << endl;
			outFile << endl;
		}
		else
		{
			HeFalseRunCounter++;
		}
	}
        cout << "* = Done by adding event-by-event, which might not be working" << endl;
        outFile << "* = Done by adding event-by-event, which might not be working" << endl;
	outFile << "Actual number of He runs: " << (HeNumOfRuns - HeFalseRunCounter) << endl << endl << endl << endl;
// ****************************************************************************************************************


// This section will put the 12C root data into doubles so that
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
        for (int i=0; i<CNumberOfEvents; i++)
        {
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
                        if (int(CEvTypeBits)==2)
                        {
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





// This section will put the 3He root data into doubles so that
// it can be calculated through C++ instead of as histograms
// ****************************************************************************************************************
        int HeNumberROfEvents;
        double HeIsSpinValidR;
        double HeQSquareR;
        double HeNuR;
        double HeEvTypeBitsR;
        double HeDpR;
        double HeReactZR;
        double HeThR;
        double HePhR;
        double He_x_bjR;
        double HeShER;
        double HePShER;
        double HeCerAsumR;
        double HeRunNumR;
        double HeSpinR;
        int HeRunNumberRForArray;
        double He_u3cR;
        double He_u3ppR;
        double He_u3pmR;
        double He_u3mmR;
        double He_u3mpR;

        HeNumberROfEvents = int(chainHeR->GetEntries());
        chainHeR->SetBranchAddress("he3R.IsSpinValid", &HeIsSpinValidR);
        chainHeR->SetBranchAddress("he3R.Spin", &HeSpinR);
        chainHeR->SetBranchAddress("PriKineR.Q2", &HeQSquareR);
        chainHeR->SetBranchAddress("PriKineR.nu", &HeNuR);
        chainHeR->SetBranchAddress("D.evtypebits", &HeEvTypeBitsR);
        chainHeR->SetBranchAddress("ExTgtCor_R.dp", &HeDpR);
        chainHeR->SetBranchAddress("ExTgtCor_R.th", &HeThR);
        chainHeR->SetBranchAddress("ExTgtCor_R.ph", &HePhR);
        chainHeR->SetBranchAddress("ReactPt_R.z", &HeReactZR);
        chainHeR->SetBranchAddress("PriKineRHe3.x_bj", &He_x_bjR);
        chainHeR->SetBranchAddress("R.sh.e", &HeShER);
        chainHeR->SetBranchAddress("R.ps.e", &HePShER);
        chainHeR->SetBranchAddress("R.cer.asum_c", &HeCerAsumR);
        chainHeR->SetBranchAddress("g.runnum", &HeRunNumR);
        chainHeR->SetBranchAddress("evright_u3c", &He_u3cR);
        chainHeR->SetBranchAddress("evright_u3pp", &He_u3ppR);
        chainHeR->SetBranchAddress("evright_u3pm", &He_u3pmR);
        chainHeR->SetBranchAddress("evright_u3mm", &He_u3mmR);
        chainHeR->SetBranchAddress("evright_u3mp", &He_u3mpR);

        cout << "NumberR of events: " << HeNumberROfEvents << endl;
        chainHeR->GetEntry(1);
        HeRunNumberRForArray = int(HeRunNumR);
        int HePrevRunNumberR = HeRunNumberRForArray;
        int HeRunNumPlaceR = 0;
        HeInfoArrayR[HeRunNumPlaceR][0] = HeRunNumberRForArray;
        double HePrev_u3cR = He_u3cR;
        double He_u3pR = 0;
        double He_u3mR = 0;
        double He_u3cR_real = 0;
        double He_u3cR_real_for_event = 0;
        double HeEndOfRun_u3cR = 0;
        double HeEndOfRun_u3pR = 0;
        double HeEndOfRun_u3mR = 0;
        int HeRealNumOfRunsR = 1;
        double HeRatioR = 1e-15;
	int HeFalseRunCounterR = 0;
	double HeChargeScaleR = 1e-15;
        for (int i=0; i<HeNumberROfEvents; i++)
        {
                chainHeR->GetEntry(i);
                HeRunNumberRForArray = int(HeRunNumR);
                He_u3cR_real_for_event = He_u3cR - HePrev_u3cR;

                if (i%10000 == 0)
                {
                        cout << "Event NumberR " << i << ", Run NumberR " << HeRunNumberRForArray << endl;
                        cout << "He_u3cR: " << He_u3cR << "  He_u3ppR: " << He_u3ppR << "  He_u3pmR: " << He_u3pmR << "  He_u3mmR: " << He_u3mmR << "  He_u3mpR: " << He_u3mpR << " Error: " << HeInfoArrayR[HeRunNumPlaceR][7] << ", HeEvTypeBitsR = " << HeEvTypeBitsR << endl;
                }
                if (HeRunNumberRForArray > HePrevRunNumberR)
                {
                        He_u3cR_real = 0;
                        He_u3pR = 0;
                        He_u3mR = 0;
                        chainHeR->GetEntry(i-1);
                        HeEndOfRun_u3cR = He_u3cR;
                        HeEndOfRun_u3pR = He_u3ppR + He_u3pmR;
                        HeEndOfRun_u3mR = He_u3mmR + He_u3mpR;
                        HeInfoArrayR[HeRunNumPlaceR][8] = HeEndOfRun_u3cR;
                        HeInfoArrayR[HeRunNumPlaceR][9] = HeEndOfRun_u3pR;
                        HeInfoArrayR[HeRunNumPlaceR][10] = HeEndOfRun_u3mR;
//                      HeInfoArrayR[HeRunNumPlaceR][7] = 1/(sqrt(HeInfoArrayR[HeRunNumPlaceR][1]));
                        HeRatioR = ((HeInfoArrayR[HeRunNumPlaceR][12]/HeInfoArrayR[HeRunNumPlaceR][11])*HeInfoArrayR[HeRunNumPlaceR][9])/((HeInfoArrayR[HeRunNumPlaceR][13]/HeInfoArrayR[HeRunNumPlaceR][11])*HeInfoArrayR[HeRunNumPlaceR][10]+1e-15);
                        HeInfoArrayR[HeRunNumPlaceR][7] = 2*HeRatioR*sqrt(HeInfoArrayR[HeRunNumPlaceR][2]*HeInfoArrayR[HeRunNumPlaceR][2]*HeInfoArrayR[HeRunNumPlaceR][3]+HeInfoArrayR[HeRunNumPlaceR][3]*HeInfoArrayR[HeRunNumPlaceR][3]*HeInfoArrayR[HeRunNumPlaceR][2])/pow(HeInfoArrayR[HeRunNumPlaceR][2]+HeRatioR*HeInfoArrayR[HeRunNumPlaceR][3]+1e-15,2);

                        cout << "Ending Run NumberR " << HeInfoArrayR[HeRunNumPlaceR][0] << ", He_u3cR = " << HeInfoArrayR[HeRunNumPlaceR][8] << ", He_u3p = " << HeInfoArrayR[HeRunNumPlaceR][9] << ", He_u3mR = " << HeInfoArrayR[HeRunNumPlaceR][10] << ", Error = " << HeInfoArrayR[HeRunNumPlaceR][7] << endl;
                        chainHeR->GetEntry(i);
                        HeRunNumPlaceR++;
                        HePrevRunNumberR = HeRunNumberRForArray;
                        HeInfoArrayR[HeRunNumPlaceR][0] = HeRunNumberRForArray;
                        HeRealNumOfRunsR++;
                }
                if (i==(HeNumberROfEvents-1))
                {
                        chainHeR->GetEntry(i-1);
                        HeEndOfRun_u3cR = He_u3cR;
                        HeEndOfRun_u3pR = He_u3ppR + He_u3pmR;
                        HeEndOfRun_u3mR = He_u3mmR + He_u3mpR;
                        HeInfoArrayR[HeRunNumPlaceR][8] = HeEndOfRun_u3cR;
                        HeInfoArrayR[HeRunNumPlaceR][9] = HeEndOfRun_u3pR;
                        HeInfoArrayR[HeRunNumPlaceR][10] = HeEndOfRun_u3mR;
//                      HeInfoArrayR[HeRunNumPlaceR][7] = 1/(sqrt(HeInfoArrayR[HeRunNumPlaceR][1]));
                        HeRatioR = ((HeInfoArrayR[HeRunNumPlaceR][12]/HeInfoArrayR[HeRunNumPlaceR][11])*HeInfoArrayR[HeRunNumPlaceR][9])/((HeInfoArrayR[HeRunNumPlaceR][13]/HeInfoArrayR[HeRunNumPlaceR][11])*HeInfoArrayR[HeRunNumPlaceR][10] + 1e-15);
                        HeInfoArrayR[HeRunNumPlaceR][7] = 2*HeRatioR*sqrt(HeInfoArrayR[HeRunNumPlaceR][2]*HeInfoArrayR[HeRunNumPlaceR][2]*HeInfoArrayR[HeRunNumPlaceR][3]+HeInfoArrayR[HeRunNumPlaceR][3]*HeInfoArrayR[HeRunNumPlaceR][3]*HeInfoArrayR[HeRunNumPlaceR][2])/pow(HeInfoArrayR[HeRunNumPlaceR][2]+HeRatioR*HeInfoArrayR[HeRunNumPlaceR][3]+1e-15,2);
                        cout << "Ending Run NumberR " << HeInfoArrayR[HeRunNumPlaceR][0] << ", He_u3cR = " << HeInfoArrayR[HeRunNumPlaceR][8] << ", He_u3p = " << HeInfoArrayR[HeRunNumPlaceR][9] << ", He_u3mR = " << HeInfoArrayR[HeRunNumPlaceR][10] << ", Error = " << HeInfoArrayR[HeRunNumPlaceR][7] << endl;
                }
                if ((HeIsSpinValidR==1)&&(HeQSquareR<10)&&(HeNuR<10)&&(HeDpR>-0.04)&&(HeDpR<0.058)&&(HeReactZR>-0.155)&&(HeReactZR<0.175)&&(abs(HeThR)<0.07)&&(abs(HePhR)<0.03)&&(He_x_bjR<2)&&((HePShER+(2*HeShER))>900)&&(HeCerAsumR>400))
                {
                        He_u3cR_real = He_u3cR_real + He_u3cR_real_for_event;
                        HeInfoArrayR[HeRunNumPlaceR][1]++;
                        if (int(HeSpinR)==1)
                        {
                                HeInfoArrayR[HeRunNumPlaceR][2]++;
                                He_u3pR = He_u3pR + He_u3cR_real_for_event;
                                HeInfoArrayR[HeRunNumPlaceR][5] = He_u3ppR + He_u3pmR;
                        }
                        if (int(HeSpinR)==-1)
                        {
                                HeInfoArrayR[HeRunNumPlaceR][3]++;
                                He_u3mR = He_u3mR + He_u3cR_real_for_event;
                                HeInfoArrayR[HeRunNumPlaceR][6] = He_u3mmR + He_u3mpR;
                        }
                        HeInfoArrayR[HeRunNumPlaceR][4] = He_u3cR_real;
                        if (int(HeEvTypeBitsR)==2)
                        {
                                HeInfoArrayR[HeRunNumPlaceR][11]++;
                                if (int(HeSpinR)==1){ HeInfoArrayR[HeRunNumPlaceR][12]++;}
                                if (int(HeSpinR)==-1){ HeInfoArrayR[HeRunNumPlaceR][13]++;}
                        }
                }

                HePrev_u3cR = He_u3cR;
        }
        cout << "NumberR of He Runs: " << HeNumOfRunsR << endl;
        outFile << "Possible NumberR of He Runs: " << HeNumOfRunsR << endl;
        cout << "Run #  # Unpol   # Spin Up   # Spin Down     Total C         C for up*       C for down*     Error   C for up        C for down      Total T1        # Up T2 # Down T2" << endl;
        outFile << "Run #  # Unpol   # Spin Up   # Spin Down     Total C         C for up*       C for down*     Error   C for up        C for down      Total T1        # Up T2 # Down T2" << endl;
        for (int i=0; i<HeNumOfRunsR; i++)
        {
		HeChargeScaleR = HeChargeScaleR + HeInfoArrayR[i][8];
		if (HeInfoArrayR[i][0] != 0)
		{
			for (int j=0; j<HeNumVarsR; j++)
			{
				cout << HeInfoArrayR[i][j] << "    ";
				outFile << HeInfoArrayR[i][j] << "    ";
			}
			cout << endl;
			outFile << endl;
		}
		else
		{
			HeFalseRunCounterR++;
		}
	}
        cout << "* = Done by adding event-by-event, which might not be working" << endl;
        outFile << "* = Done by adding event-by-event, which might not be working" << endl;
	outFile << "Actual number of He runs: " << (HeNumOfRunsR - HeFalseRunCounterR) << endl << endl << endl << endl;
// ****************************************************************************************************************


// This section will put the 12C root data into doubles so that
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
        for (int i=0; i<CNumberROfEvents; i++)
        {
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
                        CRatioR = ((CInfoArrayR[CRunNumPlaceR][12]/CInfoArrayR[CRunNumPlaceR][11])*CInfoArrayR[CRunNumPlaceR][9])/((CInfoArrayR[CRunNumPlaceR][13]/CInfoArrayR[CRunNumPlaceR][11])*CInfoArrayR[CRunNumPlaceR][10]+1e-15);
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
                        CRatioR = ((CInfoArrayR[CRunNumPlaceR][12]/CInfoArrayR[CRunNumPlaceR][11])*CInfoArrayR[CRunNumPlaceR][9])/((CInfoArrayR[CRunNumPlaceR][13]/CInfoArrayR[CRunNumPlaceR][11])*CInfoArrayR[CRunNumPlaceR][10] + 1e-15);
                        CInfoArrayR[CRunNumPlaceR][7] = 2*CRatioR*sqrt(CInfoArrayR[CRunNumPlaceR][2]*CInfoArrayR[CRunNumPlaceR][2]*CInfoArrayR[CRunNumPlaceR][3]+CInfoArrayR[CRunNumPlaceR][3]*CInfoArrayR[CRunNumPlaceR][3]*CInfoArrayR[CRunNumPlaceR][2])/pow(CInfoArrayR[CRunNumPlaceR][2]+CRatioR*CInfoArrayR[CRunNumPlaceR][3]+1e-15,2);
                        cout << "Ending Run NumberR " << CInfoArrayR[CRunNumPlaceR][0] << ", C_u3cR = " << CInfoArrayR[CRunNumPlaceR][8] << ", C_u3pR = " << CInfoArrayR[CRunNumPlaceR][9] << ", C_u3mR = " << CInfoArrayR[CRunNumPlaceR][10] << ", Error = " << CInfoArrayR[CRunNumPlaceR][7] << endl;
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
	TString titleRdpHe = "dp Cut from 3He Runs";
	cout << "Drawing " << titleRdpHe << "..." << endl;
	chainHeR->Draw("ExTgtCor_R.dp>>HedpNoCut(400,-0.08,0.08)", "", "");
	chainHeR->Draw("ExTgtCor_R.dp>>HedpCut(400,-0.08,0.08)", dpR, "");
	HedpNoCut->SetTitle(titleRdpHe);
	HedpNoCut->Draw();
	HedpCut->SetLineColor(kBlack);
	HedpCut->SetFillColor(kViolet);
	HedpCut->Draw("same");
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
	TString titleRTargetHe = "Target Cut for 3He Runs";
	cout << "Drawing " << titleRTargetHe << "..." << endl;
	chainHeR->Draw("ReactPt_R.z>>HeReactZRNoCut(400,-0.3,0.3)", "", "");
	chainHeR->Draw("ReactPt_R.z>>HeReactZRCut(400,-0.3,0.3)", tagetR, "");
	HeReactZRNoCut->SetTitle(titleRTargetHe);
	HeReactZRNoCut->Draw();
	HeReactZRCut->SetLineColor(kBlack);
	HeReactZRCut->SetFillColor(kViolet);
	HeReactZRCut->Draw("same");
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
        TH2F *HeThetaPhiCut = new TH2F("HeThetaPhiCut",titleRThetaPhiCut,100,-0.05,0.05,100,-0.1,0.1);
        chainHeR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeThetaPhiCut", tagetR, "");
        HeThetaPhiCut->SetTitle(titleRThetaPhiCut);
        HeThetaPhiCut->SetStats(kFALSE);
        HeThetaPhiCut->Draw("COLZ");
        Hebottom = new TLine(-phboundR,-thboundR,phboundR,-thboundR);
        Hetop = new TLine(-phboundR,thboundR,phboundR,thboundR);
        Heleft = new TLine(-phboundR,-thboundR,-phboundR,thboundR);
        Heright = new TLine(phboundR,-thboundR,phboundR,thboundR);
        Hebottom->SetLineColor(kViolet);
        Hetop->SetLineColor(kViolet);
        Heleft->SetLineColor(kViolet);
        Heright->SetLineColor(kViolet);
        Hebottom->SetLineWidth(3);
        Hetop->SetLineWidth(3);
        Heleft->SetLineWidth(3);
        Heright->SetLineWidth(3);
        Hebottom->Draw("same");
        Hetop->Draw("same");
        Heleft->Draw("same");
        Heright->Draw("same");
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
        TString HetitleRx = "3He Bjorken x cut";
        HetitleRx += " (x=Q^2/[2m*nu])";
        cout << "Drawing " << HetitleRx << "..." << endl;
        TH1F *Hehistx = new TH1F("Hehistx",HetitleRx,bins,xmin,xmax);
        TH1F *Hehistxcut = new TH1F("Hehistxcut",HetitleRx,bins,xmin,xmax);
        Hehistx->Sumw2();
        chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>Hehistx", cutR && kinematicsR && eventtypeR && dpR && tagetR && thphR && tracksR && cerenkovR && psshR, "E");
        chainHeR->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>Hehistxcut", cutsR, "E");
        Hehistx->Draw();
        Hehistxcut->SetFillColor(kViolet);
        Hehistxcut->Draw("same");
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
	TString titleRQ2WHe = "Q2 v. Nu for 3He";
	cout << "Drawing " << titleRQ2WHe << "..." << endl;
	chainHeR->Draw("PriKineR.Q2:PriKineR.nu>>Q2WHe(100,0.3,0.8,400,0,1.6)", cutsR, "");
	Q2WHe->SetTitle(titleRQ2WHe);
	Q2WHe->SetStats(kFALSE);
	Q2WHe->Draw("COLZ");
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
        cout << "Drawing 3He Preshower/Shower No Cuts..." << endl;
        TString titleRPsSh = "3He Preshower and Shower - No Cuts";
        TH2F *HePsShCut = new TH2F("HePsShCut",titleRPsSh,200,1,2500,200,1,1500);
        chainHeR->Draw("R.ps.e:R.sh.e>>HePsShCut", "", "");
        HePsShCut->SetTitle(titleRPsSh);
        HePsShCut->SetStats(kFALSE);
        HePsShCut->Draw("COLZ");
        Hepsshcut = new TLine(0,900,450,0);
        Hepsshcut->SetLineColor(kViolet);
        Hepsshcut->SetLineWidth(3);
        Hepsshcut->Draw("same");
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
        cout << "Drawing 3He Preshower/Shower with Cuts..." << endl;
        TString HetitleRPsSh = "3He Preshower and Shower with cutsR";
        TH2F *HePsShCut = new TH2F("HePsShCut",HetitleRPsSh,200,1,2500,200,1,1500);
        chainHeR->Draw("R.ps.e:R.sh.e>>HePsShCut", cutsR, "");
        HePsShCut->SetTitle(HetitleRPsSh);
        HePsShCut->SetStats(kFALSE);
        HePsShCut->Draw("COLZ");
        Hepsshcut->Draw("same");
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
        TString HetitleRcerenkov = "3He Cerenkov Cut";
        cout << "Drawing " << HetitleRcerenkov << "..." << endl;
        TH1F *Hehistcerenkov = new TH1F("Hehistcerenkov",HetitleRcerenkov,200,-25,2000);
        TH1F *Hehistcerenkovcut = new TH1F("Hehistcerenkovcut",HetitleRcerenkov,200,-25,2000);
        chainHeR->Draw("R.cer.asum_c>>Hehistcerenkov", "", "");
        chainHeR->Draw("R.cer.asum_c>>Hehistcerenkovcut", cerenkovR, "");
        Hehistcerenkov->SetTitle(HetitleRcerenkov);
        Hehistcerenkov->SetStats(kFALSE);
        Hehistcerenkovcut->SetFillColor(kViolet);
        Hehistcerenkov->Draw();
        Hehistcerenkovcut->Draw("same");
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
	// Defines x_Bj Canvas
	TCanvas *xbjCanvas = new TCanvas("xbjCanvas","x of 12C and 3He for both HRSs",1360,800);//x,y
	xbjpad01 = new TPad("xbjpad01","xbjpad01",0.0000,0.5000,0.3333,1.0000,0,0,0);
	xbjpad02 = new TPad("xbjpad02","xbjpad02",0.0000,0.0000,0.3333,0.5000,0,0,0);
	xbjpad03 = new TPad("xbjpad03","xbjpad03",0.3333,0.5000,0.6666,1.0000,0,0,0);
	xbjpad04 = new TPad("xbjpad04","xbjpad04",0.3333,0.0000,0.6666,0.5000,0,0,0);
	xbjpad05 = new TPad("xbjpad05","xbjpad05",0.6666,0.5000,1.0000,1.0000,0,0,0);
	xbjpad06 = new TPad("xbjpad06","xbjpad06",0.6666,0.0000,1.0000,0.5000,0,0,0);
	xbjpad01->Draw();xbjpad02->Draw();xbjpad03->Draw();xbjpad04->Draw();xbjpad05->Draw();xbjpad06->Draw();

	xbjpad01->cd();
	TString titleC = "x for 12C at Q2 of ";
	titleC += Q2;
	cout << "Drawing " << titleC << "..." << endl;
	TH1F *histCboth = new TH1F("histCboth",titleC,bins,xmin,xmax);
	TH1F *histC = new TH1F("histC",titleC,bins,xmin,xmax);
	histC->Sumw2();
	chainC->Draw("PriKineL.x_bj>>histC", cuts, "E");
//	histC->Scale(1/CChargeScale);
//	histC->Draw();

	TString titleRC = "x for 12C at Q2 of ";
	titleRC += Q2;
	cout << "Drawing " << titleRC << "..." << endl;
	TH1F *histCR = new TH1F("histCR",titleRC,bins,xmin,xmax);
	histCR->Sumw2();
	chainCR->Draw("PriKineR.x_bj>>histCR", cutsR, "E");
//	histCR->Scale(1/CChargeScaleR);
//	histCR->Draw();
	histCboth->Add(histC,histCR);
	histCboth->Scale(1/(CChargeScale + CChargeScaleR));
	histCboth->Draw();
	xbjpad01->Update();

	xbjpad02->cd();
	xbjpad02->SetLogy();
	cout << "Drawing " << titleC << " in log scale..." << endl;
	TH1F *loghistCboth = new TH1F("loghistCboth",titleC,bins,xmin,xmax);
	TH1F *loghistC = new TH1F("loghistC",titleC,bins,xmin,xmax);
	loghistC->Sumw2();
	chainC->Draw("PriKineL.x_bj>>loghistC", cuts, "E");
//	loghistC->Scale(1/CChargeScale);
//	loghistC->Draw();

	cout << "Drawing " << titleRC << " in log scale..." << endl;
	TH1F *loghistCR = new TH1F("loghistCR",titleRC,bins,xmin,xmax);
	loghistCR->Sumw2();
	chainCR->Draw("PriKineR.x_bj>>loghistCR", cutsR, "E");
//	loghistCR->Scale(1/CChargeScaleR);
//	loghistCR->Draw();
	loghistCboth->Add(loghistC,loghistCR);
	loghistCboth->Scale(1/(CChargeScale + CChargeScaleR));
	loghistCboth->Draw();
	xbjpad02->Update();


	xbjpad03->cd();
	TString titleHe = "x for 3He at Q2 of ";
	titleHe += Q2;
	cout << "Drawing " << titleHe << "..." << endl;
	TH1F *histHeboth = new TH1F("histHeboth",titleHe,bins,xmin,xmax);
	TH1F *histHe = new TH1F("histHe",titleHe,bins,xmin,xmax);
	histHe->Sumw2();
	chainHe->Draw("PriKineL.x_bj>>histHe", cuts, "E");
//	histHe->Scale(1/HeChargeScale);
//	histHe->Draw();

	TString titleRHe = "x for 3He at Q2 of ";
	titleRHe += Q2;
	cout << "Drawing " << titleRHe << "..." << endl;
	TH1F *histHeR = new TH1F("histHeR",titleRHe,bins,xmin,xmax);
	histHeR->Sumw2();
	chainHeR->Draw("PriKineR.x_bj>>histHeR", cutsR, "E");
//	histHeR->Scale(1/HeChargeScaleR);
//	histHeR->Draw();
	histHeboth->Add(histHe,histHeR);
	histHeboth->Scale(1/(HeChargeScale + HeChargeScaleR));
	histHeboth->Draw();
	xbjpad03->Update();


	xbjpad04->cd();
	xbjpad04->SetLogy();
	cout << "Drawing " << titleHe << " in log scale..." << endl;
	TH1F *loghistHeboth = new TH1F("loghistHeboth",titleHe,bins,xmin,xmax);
	TH1F *loghistHe = new TH1F("loghistHe",titleHe,bins,xmin,xmax);
	loghistHe->Sumw2();
	chainHe->Draw("PriKineL.x_bj>>loghistHe", cuts, "E");
//	loghistHe->Scale(1/HeChargeScale);
//	loghistHe->Draw();

	cout << "Drawing " << titleRHe << " in log scale..." << endl;
	TH1F *loghistHeR = new TH1F("loghistHeR",titleRHe,bins,xmin,xmax);
	loghistHeR->Sumw2();
	chainHeR->Draw("PriKineR.x_bj>>loghistHeR", cutsR, "E");
//	loghistHeR->Scale(1/HeChargeScaleR);
//	loghistHeR->Draw();
	loghistHeboth->Add(loghistHe,loghistHeR);
	loghistHeboth->Scale(1/(HeChargeScale + HeChargeScaleR));
	loghistHeboth->Draw();
	xbjpad04->Update();


	xbjpad05->cd();
	TString titleCoverHe = "12C/3He for Q2 of ";
	titleCoverHe += Q2;
	cout << "Drawing " << titleCoverHe << "..." << endl;
	TH1F *histCoverHe = new TH1F("histCoverHe",titleCoverHe,bins,xmin,xmax);
	histCoverHe->Sumw2();
	histCoverHe->Divide(histCboth,histHeboth);
	histCoverHe->Draw("E");

//	TString titleRCoverHe = "12C/3He for Q2 of ";
//	titleRCoverHe += Q2;
//	cout << "Drawing " << titleRCoverHe << "..." << endl;
//	TH1F *histCoverHeR = new TH1F("histCoverHeR",titleRCoverHe,bins,xmin,xmax);
//	histCoverHeR->Sumw2();
//	histCoverHeR->Divide(histCR,histHeR);
//	histCoverHeR->Draw("E");
	xbjpad05->Update();

	xbjpad06->cd();
	xbjpad06->SetLogy();
	cout << "Drawing " << titleCoverHe << " in log scale..." << endl;
	TH1F *loghistCoverHe = new TH1F("loghistCoverHe",titleCoverHe,bins,xmin,xmax);
	loghistCoverHe->Sumw2();
	loghistCoverHe->Divide(loghistCboth,loghistHeboth);
	loghistCoverHe->Draw("E");

//	cout << "Drawing " << titleRCoverHe << " in log scale..." << endl;
//	TH1F *loghistCoverHeR = new TH1F("loghistCoverHeR",titleRCoverHe,bins,xmin,xmax);
//	loghistCoverHeR->Sumw2();
//	loghistCoverHeR->Divide(loghistCR,loghistHeR);
//	loghistCoverHeR->Draw("E");
	xbjpad06->Update();

   
	TString imagename = "output_files/";
	imagename += titleR;
	imagename += ".png";
	xbjCanvas->Print(imagename);
	
	outFile.close();

	cout << "All done!" << endl;


}
