// **************************************************************************
//
// This script should take a TChain of data and sort through it in order
// to get the charge and livetime.
//
// In order to run it, first declare the script:
/*
	#include "hand_scaling_factors.h"
*/
// Then run the following:
/*
	double HeChargeScale; double Helivetime;
	hand_scaling_factors(HeRunNumber, endHeRunNumber, chainHe, HeChargeScale, Helivetime);
*/
//
//
// Elena Long
// 2011-01-03
//
// **************************************************************************


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!! MAKE SURE YOU ADD THE OUTFILE EVENTUALLY !!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void hand_scaling_factors(int HeRunNumber, int endHeRunNumber, TChain* chainHe, double& HeChargeScale, double& Helivetime)
{


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
	chainHe->SetBranchAddress("he3R.IsSpinValid", &HeIsSpinValid);
	chainHe->SetBranchAddress("he3R.Spin", &HeSpin);
	chainHe->SetBranchAddress("PriKineR.Q2", &HeQSquare);
	chainHe->SetBranchAddress("PriKineR.nu", &HeNu);
	chainHe->SetBranchAddress("D.evtypebits", &HeEvTypeBits);
	chainHe->SetBranchAddress("ExTgtCor_R.dp", &HeDp);
	chainHe->SetBranchAddress("ExTgtCor_R.th", &HeTh);
	chainHe->SetBranchAddress("ExTgtCor_R.ph", &HePh);
	chainHe->SetBranchAddress("ReactPt_R.z", &HeReactZ);
	chainHe->SetBranchAddress("PriKineRHe3.x_bj", &He_x_bj);
	chainHe->SetBranchAddress("R.sh.e", &HeShE);
	chainHe->SetBranchAddress("R.ps.e", &HePShE);
	chainHe->SetBranchAddress("R.cer.asum_c", &HeCerAsum);
	chainHe->SetBranchAddress("g.runnum", &HeRunNum);
	chainHe->SetBranchAddress("evright_u3c", &He_u3c);
	chainHe->SetBranchAddress("evright_u3pp", &He_u3pp);
	chainHe->SetBranchAddress("evright_u3pm", &He_u3pm);
	chainHe->SetBranchAddress("evright_u3mm", &He_u3mm);
	chainHe->SetBranchAddress("evright_u3mp", &He_u3mp);

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
        int HeTriggerstotal = 0;
        int HeT2total = 0;
        int HeT2unpolcuts = 0;
	for (int i=0; i<HeNumberOfEvents; i++)
	{
		HeTriggerstotal++;
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
			HeRatio = ((HeInfoArray[HeRunNumPlace][12]/HeInfoArray[HeRunNumPlace][11])*HeInfoArray[HeRunNumPlace][9])/((HeInfoArray[HeRunNumPlace][13]/HeInfoArray[HeRunNumPlace][11])*HeInfoArray[HeRunNumPlace][10]+1e-15);
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
			HeRatio = ((HeInfoArray[HeRunNumPlace][12]/HeInfoArray[HeRunNumPlace][11])*HeInfoArray[HeRunNumPlace][9])/((HeInfoArray[HeRunNumPlace][13]/HeInfoArray[HeRunNumPlace][11])*HeInfoArray[HeRunNumPlace][10] + 1e-15);
			HeInfoArray[HeRunNumPlace][7] = 2*HeRatio*sqrt(HeInfoArray[HeRunNumPlace][2]*HeInfoArray[HeRunNumPlace][2]*HeInfoArray[HeRunNumPlace][3]+HeInfoArray[HeRunNumPlace][3]*HeInfoArray[HeRunNumPlace][3]*HeInfoArray[HeRunNumPlace][2])/pow(HeInfoArray[HeRunNumPlace][2]+HeRatio*HeInfoArray[HeRunNumPlace][3]+1e-15,2);
			cout << "Ending Run Number " << HeInfoArray[HeRunNumPlace][0] << ", He_u3c = " << HeInfoArray[HeRunNumPlace][8] << ", He_u3p = " << HeInfoArray[HeRunNumPlace][9] << ", He_u3m = " << HeInfoArray[HeRunNumPlace][10] << ", Error = " << HeInfoArray[HeRunNumPlace][7] << endl;
		}
		if (int(HeEvTypeBits)==2)
		{
			HeT2total++;
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
				HeT2unpolcuts++;
				HeInfoArray[HeRunNumPlace][11]++;
				if (int(HeSpin)==1){ HeInfoArray[HeRunNumPlace][12]++;}
				if (int(HeSpin)==-1){ HeInfoArray[HeRunNumPlace][13]++;}
			}
		}

		HePrev_u3c = He_u3c;
	}
	cout << "Number of He Runs: " << HeNumOfRuns << endl;
//	outFile << "Possible Number of He Runs: " << HeNumOfRuns << endl;
	cout << "Run #  # Unpol   # Spin Up   # Spin Down     Total C         C for up*       C for down*     Error   C for up        C for down      Total T1        # Up T2 # Down T2" << endl;
//	outFile << "Run #  # Unpol   # Spin Up   # Spin Down     Total C         C for up*       C for down*     Error   C for up        C for down      Total T1        # Up T2 # Down T2" << endl;
	for (int i=0; i<HeNumOfRuns; i++)
	{
		HeChargeScale = HeChargeScale + HeInfoArray[i][8];
		if (HeInfoArray[i][0] != 0)
		{
			for (int j=0; j<HeNumVars; j++)
			{
				cout << HeInfoArray[i][j] << "    ";
//				outFile << HeInfoArray[i][j] << "    ";
			}
			cout << endl;
//			outFile << endl;
		}
		else
		{
			HeFalseRunCounter++;
		}
	}
	cout << "* = Done by adding event-by-event, which might not be working" << endl;
//	outFile << "* = Done by adding event-by-event, which might not be working" << endl;
//	outFile << "Actual number of He runs: " << (HeNumOfRuns - HeFalseRunCounter) << endl << endl << endl << endl;
// ****************************************************************************************************************

	Helivetime = HeT2total/(HeTriggerstotal+1e-15) + 1e-15;
	cout << "HeT2total: " << HeT2total << " HeT2unpolcuts: " << HeT2unpolcuts << endl;




}



