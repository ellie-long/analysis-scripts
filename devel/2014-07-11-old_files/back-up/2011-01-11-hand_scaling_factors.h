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
// !!!!!! SEE NOTE ABOUT HeChargeScale BELOW !!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


void hand_scaling_factors(int HeRunNumber, int endHeRunNumber, TChain* chainHe, double& HeChargeScale, double& Helivetime)
{

	int HeNumOfRuns = endHeRunNumber - HeRunNumber + 5;

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
	double thisRunCharge;

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
	int HeTrueRunCounter = 0;
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
			thisRunCharge = HeEndOfRun_u3c;
			chainHe->GetEntry(i);
			HeRunNumPlace++;
			HePrevRunNumber = HeRunNumberForArray;
			HeRealNumOfRuns++;
			cout << "thisRunCharge: " << thisRunCharge << ", Event Number: " << i << endl;
		}
		if (i==(HeNumberOfEvents-1))
		{
			chainHe->GetEntry(i-1);
			HeEndOfRun_u3c = He_u3c;
			HeEndOfRun_u3p = He_u3pp + He_u3pm;
			HeEndOfRun_u3m = He_u3mm + He_u3mp;
			thisRunCharge = HeEndOfRun_u3c;
			cout << "thisRunCharge: " << thisRunCharge << ", Event Number: " << i << endl;
		}
		if (int(HeEvTypeBits)==2)
		{
			HeT2total++;
		}
		if ((HeIsSpinValid==1)&&(HeQSquare<10)&&(HeNu<10)&&(HeDp>-0.04)&&(HeDp<0.058)&&(HeReactZ>-0.155)&&(HeReactZ<0.175)&&(abs(HeTh)<0.07)&&(abs(HePh)<0.03)&&(He_x_bj<2)&&((HePShE+(2*HeShE))>900)&&(HeCerAsum>400))
		{
			if (int(HeEvTypeBits)==2)
			{
				HeT2unpolcuts++;
			}
		}

		HePrev_u3c = He_u3c;
		HeChargeScale = HeChargeScale + thisRunCharge;
		if (thisRunCharge != 0) {HeTrueRunCounter++; cout << "HeTrueRunCounter: " << HeTrueRunCounter << ", Event Number: " << i << endl;}
		thisRunCharge = 0;
	}
	cout << "Possible number of He Runs: " << HeNumOfRuns << endl;
	cout << "Actual number of He runs: " << HeTrueRunCounter << endl << endl << endl << endl;
// ****************************************************************************************************************

	// The 1.5577e-10 term is a scaling factor that will convert the 
	// charge events into Coulombs. THIS NUMBER MAY NOT BE CORRECT.
	// It comes from dividing the number of charge events by what
	// the HALog end-of-run file said the charge should be. This number
	// does not seem to change from the beginning to the end of the
	// experiment.
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!! TALK TO VINCE TO UNDERSTAND THIS TERM BETTER!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	HeChargeScale = HeChargeScale * 1.5577e-10;
	
	double Helivetime;
	Helivetime = HeT2total/(HeTriggerstotal+1e-15) + 1e-15;
	cout << "HeT2total: " << HeT2total << " HeT2unpolcuts: " << HeT2unpolcuts << endl;




}



