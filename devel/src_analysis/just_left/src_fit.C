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
//		Work with the LHRS

#include <iostream>
#include <fstream>
#include <exception>
using namespace std;

void src_fit(){

	int CRunNumber=1699;
//	int endCRunNumber=1699;
	int endCRunNumber=1828;
	int HeRunNumber=1686;
	int endHeRunNumber=1689;
//	int endHeRunNumber=1882;
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

	TString outFileName = "output_files/";
	outFileName += title;
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



	TChain* chainC = new TChain("T");
	TChain* chainHe = new TChain("T");

	gStyle->SetErrorX(.25);
	gStyle->SetEndErrorSize(.25);
	ifstream inp;
	ofstream out;

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





	
	gStyle->SetPalette(1);
	gStyle->SetOptFit(0001);
/*
	// Defines Cuts 1 Canvas
	TCanvas *cuts1Canvas = new TCanvas("cuts1Canvas","Cuts 1",1360,800);//x,y
	cuts1pad01 = new TPad("cuts1pad01","cuts1pad01",0.0000,0.5000,0.2500,1.0000,0,0,0);
	cuts1pad02 = new TPad("cuts1pad02","cuts1pad02",0.0000,0.0000,0.2500,0.5000,0,0,0);
	cuts1pad03 = new TPad("cuts1pad03","cuts1pad03",0.2500,0.5000,0.5000,1.0000,0,0,0);
	cuts1pad04 = new TPad("cuts1pad04","cuts1pad04",0.2500,0.0000,0.5000,0.5000,0,0,0);
	cuts1pad05 = new TPad("cuts1pad05","cuts1pad05",0.5000,0.5000,0.7500,1.0000,0,0,0);
	cuts1pad06 = new TPad("cuts1pad06","cuts1pad06",0.5000,0.0000,0.7500,0.5000,0,0,0);
	cuts1pad07 = new TPad("cuts1pad07","cuts1pad07",0.7500,0.5000,1.0000,1.0000,0,0,0);
	cuts1pad08 = new TPad("cuts1pad08","cuts1pad08",0.7500,0.0000,1.0000,0.5000,0,0,0);
	cuts1pad01->Draw();cuts1pad02->Draw();cuts1pad03->Draw();cuts1pad04->Draw();cuts1pad05->Draw();cuts1pad06->Draw();cuts1pad07->Draw();cuts1pad08->Draw();

	// Everything below here makes graphs for each section of the canvas

	cuts1pad01->cd();
	TString titledpHe = "dp Cut from 3He Runs";
	cout << "Drawing " << titledpHe << "..." << endl;
	chainHe->Draw("ExTgtCor_L.dp>>HedpNoCut(400,-0.08,0.08)", "", "");
	chainHe->Draw("ExTgtCor_L.dp>>HedpCut(400,-0.08,0.08)", dp, "");
	HedpNoCut->SetTitle(titledpHe);
	HedpNoCut->Draw();
	HedpCut->SetLineColor(kBlack);
	HedpCut->SetFillColor(kViolet);
	HedpCut->Draw("same");
	cuts1pad01->Update();

	cuts1pad02->cd();
	TString titledpC = "dp Cut from 12C Runs";
	cout << "Drawing " << titledpC << "..." << endl;
	chainC->Draw("ExTgtCor_L.dp>>CdpNoCut(400,-0.08,0.08)", "", "");
	chainC->Draw("ExTgtCor_L.dp>>CdpCut(400,-0.08,0.08)", dp, "");
	CdpNoCut->SetTitle(titledpC);
	CdpNoCut->Draw();
	CdpCut->SetLineColor(kBlack);
	CdpCut->SetFillColor(kViolet);
	CdpCut->Draw("same");
	cuts1pad02->Update();

	cuts1pad03->cd();
	TString titleTargetHe = "Target Cut for 3He Runs";
	cout << "Drawing " << titleTargetHe << "..." << endl;
	chainHe->Draw("ReactPt_L.z>>HeReactZNoCut(400,-0.3,0.3)", "", "");
	chainHe->Draw("ReactPt_L.z>>HeReactZCut(400,-0.3,0.3)", target, "");
	HeReactZNoCut->SetTitle(titleTargetHe);
	HeReactZNoCut->Draw();
	HeReactZCut->SetLineColor(kBlack);
	HeReactZCut->SetFillColor(kViolet);
	HeReactZCut->Draw("same");
	cuts1pad03->Update();

	cuts1pad04->cd();
	TString titleTargetC = "Target Cut for 12C Runs";
	cout << "Drawing " << titleTargetC << "..." << endl;
	chainC->Draw("ReactPt_L.z>>CReactZNoCut(400,-0.3,0.3)", "", "");
	chainC->Draw("ReactPt_L.z>>CReactZCut(400,-0.3,0.3)", target, "");
	CReactZNoCut->SetTitle(titleTargetC);
	CReactZNoCut->Draw();
	CReactZCut->SetLineColor(kBlack);
	CReactZCut->SetFillColor(kViolet);
	CReactZCut->Draw("same");
	cuts1pad04->Update();

	cuts1pad05->cd();
        cout << "Drawing 3He Theta and Phi Cut..." << endl;
        TString titleThetaPhiCut = "3He Theta and Phi";
        TH2F *HeThetaPhiCut = new TH2F("HeThetaPhiCut",titleThetaPhiCut,100,-0.05,0.05,100,-0.1,0.1);
        chainHe->Draw("ExTgtCor_L.th:ExTgtCor_L.ph>>HeThetaPhiCut", target, "");
        HeThetaPhiCut->SetTitle(titleThetaPhiCut);
        HeThetaPhiCut->SetStats(kFALSE);
        HeThetaPhiCut->Draw("COLZ");
        Hebottom = new TLine(-phbound,thlowbound,phbound,thlowbound);
        Hetop = new TLine(-phbound,thhighbound,phbound,thhighbound);
        Heleft = new TLine(-phbound,thlowbound,-phbound,thhighbound);
        Heright = new TLine(phbound,thlowbound,phbound,thhighbound);
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
	cuts1pad05->Update();

	cuts1pad06->cd();
        cout << "Drawing 12C Theta and Phi Cut..." << endl;
        TString titleThetaPhiCut = "12 C Theta and Phi";
        TH2F *CThetaPhiCut = new TH2F("CThetaPhiCut",titleThetaPhiCut,100,-0.05,0.05,100,-0.1,0.1);
        chainC->Draw("ExTgtCor_L.th:ExTgtCor_L.ph>>CThetaPhiCut", target, "");
        CThetaPhiCut->SetTitle(titleThetaPhiCut);
        CThetaPhiCut->SetStats(kFALSE);
        CThetaPhiCut->Draw("COLZ");
        Cbottom = new TLine(-phbound,thlowbound,phbound,thlowbound);
        Ctop = new TLine(-phbound,thhighbound,phbound,thhighbound);
        Cleft = new TLine(-phbound,thlowbound,-phbound,thhighbound);
        Cright = new TLine(phbound,thlowbound,phbound,thhighbound);
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
	cuts1pad06->Update();

        cuts1pad07->cd();
        TString Hetitlex = "3He Bjorken x cut";
        Hetitlex += " (x=Q^2/[2m*nu])";
        cout << "Drawing " << Hetitlex << "..." << endl;
        TH1F *Hehistx = new TH1F("Hehistx",Hetitlex,bins,xmin,xmax);
        TH1F *Hehistxcut = new TH1F("Hehistxcut",Hetitlex,bins,xmin,xmax);
        Hehistx->Sumw2();
        chainHe->Draw("(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>Hehistx", cut && kinematics && eventtype && dp && target && thph && tracks && cerenkov && pssh, "E");
        chainHe->Draw("(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>Hehistxcut", cuts, "E");
        Hehistx->Draw();
        Hehistxcut->SetFillColor(kViolet);
        Hehistxcut->Draw("same");
	cuts1pad07->Update();

	cuts1pad08->cd();
        TString Ctitlex = "12C Bjorken x cut";
        Ctitlex += " (x=Q^2/[2m*nu])";
        cout << "Drawing " << Ctitlex << "..." << endl;
        TH1F *Chistx = new TH1F("Chistx",Ctitlex,bins,xmin,xmax);
        TH1F *Chistxcut = new TH1F("Chistxcut",Ctitlex,bins,xmin,xmax);
        Chistx->Sumw2();
        chainC->Draw("(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>Chistx", cut && kinematics && eventtype && dp && target && thph && tracks && cerenkov && pssh, "E");
        chainC->Draw("(PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315))>>Chistxcut", cuts, "E");
        Chistx->Draw();
        Chistxcut->SetFillColor(kViolet);
        Chistxcut->Draw("same");
	cuts1pad08->Update();

/*	// Defines Cuts 2 Canvas
	TCanvas *cuts2Canvas = new TCanvas("cuts2Canvas","Cuts 2",1360,800);//x,y
	cuts2pad01 = new TPad("cuts2pad01","cuts2pad01",0.0000,0.5000,0.2500,1.0000,0,0,0);
	cuts2pad02 = new TPad("cuts2pad02","cuts2pad02",0.0000,0.0000,0.2500,0.5000,0,0,0);
	cuts2pad03 = new TPad("cuts2pad03","cuts2pad03",0.2500,0.5000,0.5000,1.0000,0,0,0);
	cuts2pad04 = new TPad("cuts2pad04","cuts2pad04",0.2500,0.0000,0.5000,0.5000,0,0,0);
	cuts2pad05 = new TPad("cuts2pad05","cuts2pad05",0.5000,0.5000,0.7500,1.0000,0,0,0);
	cuts2pad06 = new TPad("cuts2pad06","cuts2pad06",0.5000,0.0000,0.7500,0.5000,0,0,0);
	cuts2pad07 = new TPad("cuts2pad07","cuts2pad07",0.7500,0.5000,1.0000,1.0000,0,0,0);
	cuts2pad08 = new TPad("cuts2pad08","cuts2pad08",0.7500,0.0000,1.0000,0.5000,0,0,0);
	cuts2pad01->Draw();cuts2pad02->Draw();cuts2pad03->Draw();cuts2pad04->Draw();cuts2pad05->Draw();cuts2pad06->Draw();cuts2pad07->Draw();cuts2pad08->Draw();

	cuts2pad01->cd();
	TString titleQ2WHe = "Q2 v. Nu for 3He";
	cout << "Drawing " << titleQ2WHe << "..." << endl;
	chainHe->Draw("PriKineL.Q2:PriKineL.nu>>Q2WHe(100,0.3,0.8,400,0,1.6)", cuts, "");
	Q2WHe->SetTitle(titleQ2WHe);
	Q2WHe->SetStats(kFALSE);
	Q2WHe->Draw("COLZ");
	cuts2pad01->Update();

	cuts2pad02->cd();
	TString titleQ2WC = "Q2 v. Nu for 12C";
	cout << "Drawing " << titleQ2WC << "..." << endl;
	chainC->Draw("PriKineL.Q2:PriKineL.nu>>Q2WC(100,0.3,0.8,400,0,1.6,100)", cuts, "");
	Q2WC->SetTitle(titleQ2WC);
	Q2WC->SetStats(kFALSE);
	Q2WC->Draw("COLZ");
	cuts2pad02->Update();

        cuts2pad03->cd();
        cout << "Drawing 3He Pion Rejector 1/Pion Rejector 2 No Cuts..." << endl;
        TString titlePsSh = "3He Pion Rejector 1 and Pion Rejector 2 - No Cuts";
	cout << "I made it here!" << endl;;
        TH2F *HePsShCut = new TH2F("HePsShCut",titlePsSh,200,1,2500,200,1,1500);
	cout << "And here" << endl;
        chainHe->Draw("L.prl1.e:L.prl2.e>>HePsShCut");
	cout << "But did I make it here?" << endl;
        HePsShCut->SetTitle(titlePsSh);
	cout << "What about here?" << endl;;
        HePsShCut->SetStats(kFALSE);
	cout << "here maybe?" << endl;;
        HePsShCut->Draw("COLZ");
	cout << "I hope I made it at least here." << endl;
        Hepsshcut = new TLine(0,900,900,0);
	cout << "Cuz then I'm almost done." << endl;
        Hepsshcut->SetLineColor(kViolet);
	cout << "Here it comes!" << endl;
        Hepsshcut->SetLineWidth(3);
	cout << "Awww...." << endl;
        Hepsshcut->Draw("same");
	cout << "Almost...." << endl;
	cuts2pad03->Update();
	cout << "finished!!" << endl;

        cuts2pad04->cd();
        cout << "Drawing 12C Pion Rejector 1/Pion Rejector 2 No Cuts..." << endl;
        TString CtitlePsSh = "12C Pion Rejector 1 and Pion Rejector 2 - No Cuts";
        TH2F *CPsShCut = new TH2F("CPsShCut",CtitlePsSh,200,1,2500,200,1,1500);
        chainC->Draw("L.prl1.e:L.prl2.e>>CPsShCut");
        CPsShCut->SetTitle(CtitlePsSh);
        CPsShCut->SetStats(kFALSE);
        CPsShCut->Draw("COLZ");
        Cpsshcut = new TLine(0,900,900,0);
        Cpsshcut->SetLineColor(kViolet);
        Cpsshcut->SetLineWidth(3);
        Cpsshcut->Draw("same");
	cuts2pad04->Update();

	cuts2pad05->cd();
        cout << "Drawing 3He Pion Rejector 1/Pion Rejector 2 with Cuts..." << endl;
        TString HetitlePsSh = "3He Pion Rejector 1 and Pion Rejector 2 with cuts";
        TH2F *HePsShCut = new TH2F("HePsShCut",HetitlePsSh,200,1,2500,200,1,1500);
        chainHe->Draw("L.prl1.e:L.prl2.e>>HePsShCut", cuts);
        HePsShCut->SetTitle(HetitlePsSh);
        HePsShCut->SetStats(kFALSE);
        HePsShCut->Draw("COLZ");
        Hepsshcut->Draw("same");
	cuts2pad05->Update();

	cuts2pad06->cd();
        cout << "Drawing 12C Pion Rejector 1/Pion Rejector 2 with Cuts..." << endl;
        TString CtitlePsSh = "12C Pion Rejector 1 and Pion Rejector 2 with cuts";
        TH2F *CPsShCut = new TH2F("CPsShCut",CtitlePsSh,200,1,2500,200,1,1500);
        chainC->Draw("L.prl1.e:L.prl2.e>>CPsShCut", cuts);
        CPsShCut->SetTitle(CtitlePsSh);
        CPsShCut->SetStats(kFALSE);
        CPsShCut->Draw("COLZ");
        Cpsshcut->Draw("same");
	cuts2pad06->Update();

	cuts2pad07->cd();
        TString Hetitlecerenkov = "3He Cerenkov Cut";
        cout << "Drawing " << Hetitlecerenkov << "..." << endl;
        TH1F *Hehistcerenkov = new TH1F("Hehistcerenkov",Hetitlecerenkov,200,-25,4000);
        TH1F *Hehistcerenkovcut = new TH1F("Hehistcerenkovcut",Hetitlecerenkov,200,-25,4000);
        chainHe->Draw("L.cer.asum_c>>Hehistcerenkov", "", "");
        chainHe->Draw("L.cer.asum_c>>Hehistcerenkovcut", cerenkov, "");
        Hehistcerenkov->SetTitle(Hetitlecerenkov);
        Hehistcerenkov->SetStats(kFALSE);
        Hehistcerenkovcut->SetFillColor(kViolet);
        Hehistcerenkov->Draw();
        Hehistcerenkovcut->Draw("same");
	cuts2pad07->Update();

	cuts2pad08->cd();
        TString Ctitlecerenkov = "12C Cerenkov Cut";
        cout << "Drawing " << Ctitlecerenkov << "..." << endl;
        TH1F *Chistcerenkov = new TH1F("Chistcerenkov",Ctitlecerenkov,200,-25,4000);
        TH1F *Chistcerenkovcut = new TH1F("Chistcerenkovcut",Ctitlecerenkov,200,-25,4000);
        chainC->Draw("L.cer.asum_c>>Chistcerenkov", "", "");
        chainC->Draw("L.cer.asum_c>>Chistcerenkovcut", cerenkov, "");
        Chistcerenkov->SetTitle(Ctitlecerenkov);
        Chistcerenkov->SetStats(kFALSE);
        Chistcerenkovcut->SetFillColor(kViolet);
        Chistcerenkov->Draw();
        Chistcerenkovcut->Draw("same");
	cuts2pad08->Update();
*/
	// Defines x_Bj Canvas
	TCanvas *xbjCanvas = new TCanvas("xbjCanvas","x of 12C and 3He",1360,800);//x,y
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
	TH1F *histC = new TH1F("histC",titleC,bins,xmin,xmax);
	histC->Sumw2();
	chainC->Draw("PriKineL.x_bj>>histC", cuts, "E");
	histC->Scale(1/CChargeScale);
	histC->Draw();
	TF1 *fitC1 = new TF1("fitC1","[0]*exp(-x*[1])",1.45,1.6);
//	fitC1->SetParNames("C Red p1","C Red p2");
//	fitC1->SetLineColor(kRed);
//	TF1 *fitC2 = new TF1("fitC2","[0]*exp(-x*[1])",1.6,1.8);
//	fitC2->SetParNames("C Blue p1","C Blue p2");
//	fitC2->SetLineColor(kBlue);
//	TF1 *fitC3 = new TF1("fitC3","[0]*exp(-x*[1])",1.35,1.45);
//	fitC3->SetParNames("C Green p1","C Green p2");
//	fitC3->SetLineColor(kGreen);
//	histC->Fit("fitC2","R");
//	histC->Fit("fitC3","R+");
//	histC->Fit("fitC1","R+");
//	Double_t fitC1const = fitC1->GetParameter(0);
//	Double_t fitC1expconst = fitC1->GetParameter(1);
//	Double_t fitC1consterror = fitC1->GetParError(0);
//	Double_t fitC1expconsterror = fitC1->GetParError(1);
//	Double_t fitC2const = fitC2->GetParameter(0);
//	Double_t fitC2expconst = fitC2->GetParameter(1);
//	Double_t fitC2consterror = fitC2->GetParError(0);
//	Double_t fitC2expconsterror = fitC2->GetParError(1);
//	Double_t fitC3const = fitC3->GetParameter(0);
//	Double_t fitC3expconst = fitC3->GetParameter(1);
//	Double_t fitC3consterror = fitC3->GetParError(0);
//	Double_t fitC3expconsterror = fitC3->GetParError(1);
//	histC->Fit("fitC2","R");
//	histC->Fit("fitC3","R+");
//	histC->Fit("fitC1","R+");
//	outFile << "C1 range: 1.46-1.60		C2 range: 1.60-1.80		C3 range: 1.35-1.45" << endl;
//	outFile << "C1:" << fitC1const << " | C1 error: " << fitC1consterror << " | Log C1: " << fitC1expconst << " | Log C1 error: " << fitC1expconsterror << endl;
//	outFile << "C2:" << fitC2const << " | C2 error: " << fitC2consterror << " | Log C2: " << fitC2expconst << " | Log C2 error: " << fitC2expconsterror << endl;
//	outFile << "C3:" << fitC3const << " | C3 error: " << fitC3consterror << " | Log C3: " << fitC3expconst << " | Log C3 error: " << fitC3expconsterror << endl << endl << endl;
	xbjpad01->Update();

	xbjpad02->cd();
	xbjpad02->SetLogy();
	cout << "Drawing " << titleC << " in log scale..." << endl;
	TH1F *loghistC = new TH1F("loghistC",titleC,bins,xmin,xmax);
	loghistC->Sumw2();
	chainC->Draw("PriKineL.x_bj>>loghistC", cuts, "E");
	loghistC->Scale(1/CChargeScale);
	loghistC->Draw();
//	fitC1->SetParNames("C Red p1","C Red p2");
//	fitC1->SetLineColor(kRed);
//	fitC2->SetParNames("C Blue p1","C Blue p2");
//	fitC2->SetLineColor(kBlue);
//	fitC3->SetParNames("C Green p1","C Green p2");
//	fitC3->SetLineColor(kGreen);
//	loghistC->Fit("fitC1","R");
//	loghistC->Fit("fitC3","R+");
//	loghistC->Fit("fitC2","R+");
//	Double_t fitC1const = fitC1->GetParameter(0);
//	Double_t fitC1expconst = fitC1->GetParameter(1);
//	Double_t fitC1consterror = fitC1->GetParError(0);
//	Double_t fitC1expconsterror = fitC1->GetParError(1);
//	Double_t fitC2const = fitC2->GetParameter(0);
//	Double_t fitC2expconst = fitC2->GetParameter(1);
//	Double_t fitC2consterror = fitC2->GetParError(0);
//	Double_t fitC2expconsterror = fitC2->GetParError(1);
//	Double_t fitC3const = fitC3->GetParameter(0);
//	Double_t fitC3expconst = fitC3->GetParameter(1);
//	Double_t fitC3consterror = fitC3->GetParError(0);
//	Double_t fitC3expconsterror = fitC3->GetParError(1);
//	outFile << "Log C1 range: 1.46-1.60		Log C2 range: 1.60-1.80		Log C3 range: 1.35-1.45" << endl;
//	outFile << "C1:" << fitC1const << " | C1 error: " << fitC1consterror << " | Log C1: " << fitC1expconst << " | Log C1 error: " << fitC1expconsterror << endl;
//	outFile << "C2:" << fitC2const << " | C2 error: " << fitC2consterror << " | Log C2: " << fitC2expconst << " | Log C2 error: " << fitC2expconsterror << endl;
//	outFile << "C3:" << fitC3const << " | C3 error: " << fitC3consterror << " | Log C3: " << fitC3expconst << " | Log C3 error: " << fitC3expconsterror << endl << endl << endl;
	xbjpad02->Update();


	xbjpad03->cd();
	TString titleHe = "x for 3He at Q2 of ";
	titleHe += Q2;
	cout << "Drawing " << titleHe << "..." << endl;
	TH1F *histHe = new TH1F("histHe",titleHe,bins,xmin,xmax);
	histHe->Sumw2();
	chainHe->Draw("PriKineL.x_bj>>histHe", cuts, "E");
	histHe->Scale(1/HeChargeScale);
	histHe->Draw();
//	TF1 *fitHe1 = new TF1("fitHe1","[0]*exp(-x*[1])",1.45,1.6);
//	fitHe1->SetParNames("He Red p1", "He Red p2");
//	fitHe1->SetLineColor(kRed);
//	TF1 *fitHe2 = new TF1("fitHe2","[0]*exp(-x*[1])",1.6,1.8);
//	fitHe2->SetParNames("He Blue p1","He Blue p2");
//	fitHe2->SetLineColor(kBlue);
//	TF1 *fitHe3 = new TF1("fitHe3","[0]*exp(-x*[1])",1.35,1.45);
//	fitHe3->SetParNames("He Green p1","He Green p2");
//	fitHe3->SetLineColor(kGreen);
//	histHe->Fit("fitHe2","R+");
//	histHe->Fit("fitHe3","R+");
//	histHe->Fit("fitHe1","R+");
//	Double_t fitHe1const = fitHe1->GetParameter(0);
//	Double_t fitHe1expconst = fitHe1->GetParameter(1);
//	Double_t fitHe1consterror = fitHe1->GetParError(0);
//	Double_t fitHe1expconsterror = fitHe1->GetParError(1);
//	Double_t fitHe2const = fitHe2->GetParameter(0);
//	Double_t fitHe2expconst = fitHe2->GetParameter(1);
//	Double_t fitHe2consterror = fitHe2->GetParError(0);
//	Double_t fitHe2expconsterror = fitHe2->GetParError(1);
//	Double_t fitHe3const = fitHe3->GetParameter(0);
//	Double_t fitHe3expconst = fitHe3->GetParameter(1);
//	Double_t fitHe3consterror = fitHe3->GetParError(0);
//	Double_t fitHe3expconsterror = fitHe3->GetParError(1);
//	outFile << "He1 range: 1.46-1.60		He2 range: 1.60-1.80		He3 range: 1.35-1.45" << endl;
//	outFile << "He1:" << fitHe1const << " | He1 error: " << fitHe1consterror << " | Log He1: " << fitHe1expconst << " | Log He1 error: " << fitHe1expconsterror << endl;
//	outFile << "He2:" << fitHe2const << " | He2 error: " << fitHe2consterror << " | Log He2: " << fitHe2expconst << " | Log He2 error: " << fitHe2expconsterror << endl;
//	outFile << "He3:" << fitHe3const << " | He3 error: " << fitHe3consterror << " | Log He3: " << fitHe3expconst << " | Log He3 error: " << fitHe3expconsterror << endl << endl << endl;
	xbjpad03->Update();


	xbjpad04->cd();
	xbjpad04->SetLogy();
	cout << "Drawing " << titleHe << " in log scale..." << endl;
	TH1F *loghistHe = new TH1F("loghistHe",titleHe,bins,xmin,xmax);
	loghistHe->Sumw2();
	chainHe->Draw("PriKineL.x_bj>>loghistHe", cuts, "E");
	loghistHe->Scale(1/HeChargeScale);
	loghistHe->Draw();
//	TF1 *fitHe1 = new TF1("fitHe1","[0]*exp(-x*[1])",1.45,1.6);
//	fitHe1->SetParNames("He Red p1", "He Red p2");
//	fitHe1->SetLineColor(kRed);
//	TF1 *fitHe2 = new TF1("fitHe2","[0]*exp(-x*[1])",1.6,1.8);
//	fitHe2->SetParNames("He Blue p1","He Blue p2");
//	fitHe2->SetLineColor(kBlue);
//	TF1 *fitHe3 = new TF1("fitHe3","[0]*exp(-x*[1])",1.35,1.45);
//	fitHe3->SetParNames("He Green p1","He Green p2");
//	fitHe3->SetLineColor(kGreen);
//	loghistHe->Fit("fitHe1","R+");
//	loghistHe->Fit("fitHe3","R+");
//	loghistHe->Fit("fitHe2","R+");
//	Double_t fitHe1const = fitHe1->GetParameter(0);
//	Double_t fitHe1expconst = fitHe1->GetParameter(1);
//	Double_t fitHe1consterror = fitHe1->GetParError(0);
//	Double_t fitHe1expconsterror = fitHe1->GetParError(1);
//	Double_t fitHe2const = fitHe2->GetParameter(0);
//	Double_t fitHe2expconst = fitHe2->GetParameter(1);
//	Double_t fitHe2consterror = fitHe2->GetParError(0);
//	Double_t fitHe2expconsterror = fitHe2->GetParError(1);
//	Double_t fitHe3const = fitHe3->GetParameter(0);
//	Double_t fitHe3expconst = fitHe3->GetParameter(1);
//	Double_t fitHe3consterror = fitHe3->GetParError(0);
//	Double_t fitHe3expconsterror = fitHe3->GetParError(1);
//	outFile << "Log He1 range: 1.46-1.60		Log He2 range: 1.60-1.80		Log He3 range: 1.35-1.45" << endl;
//	outFile << "He1:" << fitHe1const << " | He1 error: " << fitHe1consterror << " | Log He1: " << fitHe1expconst << " | Log He1 error: " << fitHe1expconsterror << endl;
//	outFile << "He2:" << fitHe2const << " | He2 error: " << fitHe2consterror << " | Log He2: " << fitHe2expconst << " | Log He2 error: " << fitHe2expconsterror << endl;
//	outFile << "He3:" << fitHe3const << " | He3 error: " << fitHe3consterror << " | Log He3: " << fitHe3expconst << " | Log He3 error: " << fitHe3expconsterror << endl << endl << endl;
	xbjpad04->Update();


	xbjpad05->cd();
	TString titleCoverHe = "12C/3He for Q2 of ";
	titleCoverHe += Q2;
	cout << "Drawing " << titleCoverHe << "..." << endl;
	TH1F *histCoverHe = new TH1F("histCoverHe",titleCoverHe,bins,xmin,xmax);
	histCoverHe->Sumw2();
//	histCoverHe->Divide(histC,histHe,1,0.0918143);
	histCoverHe->Divide(histC,histHe);
	histCoverHe->Draw("E");
	xbjpad05->Update();

	xbjpad06->cd();
	xbjpad06->SetLogy();
	cout << "Drawing " << titleCoverHe << " in log scale..." << endl;
	TH1F *loghistCoverHe = new TH1F("loghistCoverHe",titleCoverHe,bins,xmin,xmax);
	loghistCoverHe->Sumw2();
//	histCoverHe->Divide(histC,histHe,1,0.0918143);
	loghistCoverHe->Divide(loghistC,loghistHe);
	loghistCoverHe->Draw("E");
	xbjpad06->Update();

   
	TString imagename = "output_files/";
	imagename += title;
	imagename += "_cuts_1.png";
	cuts1Canvas->Print(imagename);
	TString imagename = "output_files/";
	imagename += title;
	imagename += "_cuts_2.png";
	cuts2Canvas->Print(imagename);
	TString imagename = "output_files/";
	imagename += title;
	imagename += ".png";
	xbjCanvas->Print(imagename);
	
	outFile.close();

	cout << "All done!" << endl;


}
