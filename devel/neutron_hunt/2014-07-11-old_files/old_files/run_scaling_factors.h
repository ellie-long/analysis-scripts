// **************************************************************************
//
// This script should take a TChain of data and sort through it in order
// to get the charge and livetime.
//
// In order to run it, first declare the script:
/*
	#include "run_scaling_factors.h"
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
// Edited to add:
//	Spin up & down events and statistical error (2011-02-02)
//
// **************************************************************************


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!! SEE NOTE ABOUT HeChargeScale BELOW !!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void run_scaling_factors(int HeRunNumber, int endHeRunNumber, TChain* chainHe, double& HeChargeScale, double& Helivetime)
{

	const int HeNumOfRuns = endHeRunNumber - HeRunNumber + 5;

//	TString outFileName = "/home/ellie/physics/e05-102/images/run_information/run_info_R2.txt";
//	TString outFileName = "/home/ellie/physics/e05-102/images/run_information/q2_1_nitrogen.txt";
//	TString outFileName = "/home/ellie/physics/e05-102/images/run_information/q2_01_vertical_3he.txt";
	TString outFileName = "/home/ellie/physics/e05-102/images/run_information/q2_05_";
	outFileName += "run_";
	outFileName += HeRunNumber;
	outFileName += ".txt";
	ofstream outFile;
	outFile.open(outFileName, ios::app);
	ifstream inFile (outFileName);

	TString outChargeFileName = "/home/ellie/physics/e05-102/images/run_information/charge_info_R.txt";
	ofstream chargeOutFile;
	chargeOutFile.open(outChargeFileName, ios::app);
	ifstream chargeInFile (outChargeFileName);

// This section will put the 3He root data into doubles so that
// it can be calculated through C++ instead of as histograms
// ****************************************************************************************************************
	int HeNumberOfEvents;
	double HeIsSpinValid;
//	double HeQSquare;
//	double HeNu;
	double HeEvTypeBits;
//	double HeDp;
//	double HeReactZ;
//	double HeTh;
//	double HePh;
//	double He_x_bj;
//	double HeShE;
//	double HePShE;
//	double HeCerAsum;
	double HeRunNum;
	double HeSpin;
	double g0helicity;
	int HeRunNumberForArray;
	double He_u3c;
	double He_u3pp;
	double He_u3pm;
	double He_u3mm;
	double He_u3mp;
	double He_u1c;
	double He_u1pp;
	double He_u1pm;
	double He_u1mm;
	double He_u1mp;
	double He_u10c;
	double He_u10pp;
	double He_u10pm;
	double He_u10mm;
	double He_u10mp;
	double He_d3c;
	double He_d3pp;
	double He_d3pm;
	double He_d3mm;
	double He_d3mp;
	double He_d1c;
	double He_d1pp;
	double He_d1pm;
	double He_d1mm;
	double He_d1mp;
	double He_d10c;
	double He_d10pp;
	double He_d10pm;
	double He_d10mm;
	double He_d10mp;

	double thisRunCharge;
	double thisRunTargetChargeUp;
	double thisRunTargetChargeDown;
	double thisRunBeamChargeUp;
	double thisRunBeamChargeDown;
	double thisRunError;

	HeNumberOfEvents = int(chainHe->GetEntries());
	chainHe->SetBranchAddress("he3R.IsSpinValid", &HeIsSpinValid);
	chainHe->SetBranchAddress("he3R.Spin", &HeSpin);
	chainHe->SetBranchAddress("g0hel.R.helicity", &g0helicity);
//	chainHe->SetBranchAddress("PriKineR.Q2", &HeQSquare);
//	chainHe->SetBranchAddress("PriKineR.nu", &HeNu);
	chainHe->SetBranchAddress("D.evtypebits", &HeEvTypeBits);
//	chainHe->SetBranchAddress("ExTgtCor_R.dp", &HeDp);
//	chainHe->SetBranchAddress("ExTgtCor_R.th", &HeTh);
//	chainHe->SetBranchAddress("ExTgtCor_R.ph", &HePh);
//	chainHe->SetBranchAddress("ReactPt_R.z", &HeReactZ);
//	chainHe->SetBranchAddress("PriKineRHe3.x_bj", &He_x_bj);
//	chainHe->SetBranchAddress("R.sh.e", &HeShE);
//	chainHe->SetBranchAddress("R.ps.e", &HePShE);
//	chainHe->SetBranchAddress("R.cer.asum_c", &HeCerAsum);
	chainHe->SetBranchAddress("g.runnum", &HeRunNum);
	chainHe->SetBranchAddress("evright_u3c", &He_u3c);
	chainHe->SetBranchAddress("evright_u3pp", &He_u3pp);
	chainHe->SetBranchAddress("evright_u3pm", &He_u3pm);
	chainHe->SetBranchAddress("evright_u3mm", &He_u3mm);
	chainHe->SetBranchAddress("evright_u3mp", &He_u3mp);
	chainHe->SetBranchAddress("evright_u1c", &He_u1c);
	chainHe->SetBranchAddress("evright_u1pp", &He_u1pp);
	chainHe->SetBranchAddress("evright_u1pm", &He_u1pm);
	chainHe->SetBranchAddress("evright_u1mm", &He_u1mm);
	chainHe->SetBranchAddress("evright_u1mp", &He_u1mp);
	chainHe->SetBranchAddress("evright_u10c", &He_u10c);
	chainHe->SetBranchAddress("evright_u10pp", &He_u10pp);
	chainHe->SetBranchAddress("evright_u10pm", &He_u10pm);
	chainHe->SetBranchAddress("evright_u10mm", &He_u10mm);
	chainHe->SetBranchAddress("evright_u10mp", &He_u10mp);
	chainHe->SetBranchAddress("evright_d3c", &He_d3c);
	chainHe->SetBranchAddress("evright_d3pp", &He_d3pp);
	chainHe->SetBranchAddress("evright_d3pm", &He_d3pm);
	chainHe->SetBranchAddress("evright_d3mm", &He_d3mm);
	chainHe->SetBranchAddress("evright_d3mp", &He_d3mp);
	chainHe->SetBranchAddress("evright_d1c", &He_d1c);
	chainHe->SetBranchAddress("evright_d1pp", &He_d1pp);
	chainHe->SetBranchAddress("evright_d1pm", &He_d1pm);
	chainHe->SetBranchAddress("evright_d1mm", &He_d1mm);
	chainHe->SetBranchAddress("evright_d1mp", &He_d1mp);
	chainHe->SetBranchAddress("evright_d10c", &He_d10c);
	chainHe->SetBranchAddress("evright_d10pp", &He_d10pp);
	chainHe->SetBranchAddress("evright_d10pm", &He_d10pm);
	chainHe->SetBranchAddress("evright_d10mm", &He_d10mm);
	chainHe->SetBranchAddress("evright_d10mp", &He_d10mp);

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
	int HeTriggersUp = 0;
	int HeTriggersDown = 0;
	int BeamTriggersUp = 0;
	int BeamTriggersDown = 0;
	int HeT2total = 0;
	int HeT2up = 0;
	int HeT2down = 0;
	int BeamT2up = 0;
	int BeamT2down = 0;

//	int HeT2unpolcuts = 0;
//	int thisRunSpinUp = 0;
//	int thisRunSpinDown = 0;
	int thisRunNumber = 0;
	for (int i=0; i<HeNumberOfEvents; i++)
	{
		chainHe->GetEntry(i);

		HeTriggerstotal++;
		if (int(HeSpin)==1)
		{
			HeTriggersUp++;
		}
		if (int(HeSpin)==-1)
		{
			HeTriggersDown++;
		}
		if (int(g0helicity)==1)
		{
			BeamTriggersUp++;
		}
		if (int(g0helicity)==-1)
		{
			BeamTriggersDown++;
		}


		HeRunNumberForArray = int(HeRunNum);
		He_u3c_real_for_event = He_u3c - HePrev_u3c;

		if (i%10000 == 0)
		{
			cout << "Event Number " << i << ", Run Number " << HeRunNumberForArray << endl;
		}
		if ((HeRunNumberForArray > HePrevRunNumber) || (i==(HeNumberOfEvents-1)))
		{
			He_u3c_real = 0;
			He_u3p = 0;
			He_u3m = 0;
			chainHe->GetEntry(i-1);
			HeEndOfRun_u3c = He_u3c;
			HeEndOfRun_u3p = He_u3pp + He_u3pm;
			HeEndOfRun_u3m = He_u3mm + He_u3mp;
			thisRunCharge = HeEndOfRun_u3c;
			thisRunTargetChargeUp = HeEndOfRun_u3p;
			thisRunTargetChargeDown = HeEndOfRun_u3m;
			thisRunBeamChargeUp = He_u3pp + He_u3mp;
			thisRunBeamChargeDown = He_u3mm + He_u3pm;

			double thisHe_u1c = He_u1c;
			double thisHe_u1pp = He_u1pp;
			double thisHe_u1pm = He_u1pm;
			double thisHe_u1mp = He_u1mp;
			double thisHe_u1mm = He_u1mm;
			double thisHe_u3c = He_u3c;
			double thisHe_u3pp = He_u3pp;
			double thisHe_u3pm = He_u3pm;
			double thisHe_u3mp = He_u3mp;
			double thisHe_u3mm = He_u3mm;
			double thisHe_u10c = He_u10c;
			double thisHe_u10pp = He_u10pp;
			double thisHe_u10pm = He_u10pm;
			double thisHe_u10mp = He_u10mp;
			double thisHe_u10mm = He_u10mm;
			double thisHe_d1c = He_d1c;
			double thisHe_d1pp = He_d1pp;
			double thisHe_d1pm = He_d1pm;
			double thisHe_d1mp = He_d1mp;
			double thisHe_d1mm = He_d1mm;
			double thisHe_d3c = He_d3c;
			double thisHe_d3pp = He_d3pp;
			double thisHe_d3pm = He_d3pm;
			double thisHe_d3mp = He_d3mp;
			double thisHe_d3mm = He_d3mm;
			double thisHe_d10c = He_d10c;
			double thisHe_d10pp = He_d10pp;
			double thisHe_d10pm = He_d10pm;
			double thisHe_d10mp = He_d10mp;
			double thisHe_d10mm = He_d10mm;

			thisRunNumber = HePrevRunNumber;
			chainHe->GetEntry(i);
			HeRunNumPlace++;
			HePrevRunNumber = HeRunNumberForArray;
			HeRealNumOfRuns++;
			cout << "thisRunCharge: " << thisRunCharge << ", Event Number: " << i << endl;
			cout << "thisRunTargetChargeUp: " << thisRunTargetChargeUp << ", Event Number: " << i << endl;
			cout << "thisRunTargetChargeDown: " << thisRunTargetChargeDown << ", Event Number: " << i << endl;
			cout << "thisRunBeamChargeUp: " << thisRunBeamChargeUp << ", Event Number: " << i << endl;
			cout << "thisRunBeamChargeDown: " << thisRunBeamChargeDown << ", Event Number: " << i << endl;

		}
// ************ if having problems, change loop above to just if(HeRunNumberForArray > HePrevRunNumber) and add the if loop below
/*		if (i==(HeNumberOfEvents-1))
		{
			chainHe->GetEntry(i-1);
			HeEndOfRun_u3c = He_u3c;
			HeEndOfRun_u3p = He_u3pp + He_u3pm;
			HeEndOfRun_u3m = He_u3mm + He_u3mp;
			thisRunCharge = HeEndOfRun_u3c;
			thisRunNumber = HeRunNumberForArray;
			cout << "thisRunCharge: " << thisRunCharge << ", Event Number: " << i << endl;
		}
*/
//  *******************************************************************************************************************************

		if (int(HeEvTypeBits)==2)
		{
			HeT2total++;
			if (int(HeSpin)==1)
			{
				HeT2up++;
			}
			if (int(HeSpin)==-1)
			{
				HeT2down++;
			}
			if (int(g0helicity)==1)
			{
				BeamT2up++;
			}
			if (int(g0helicity)==-1)
			{
				BeamT2down++;
			}
		}

// ************ This bit below is not really necessary and once things are working should be taken out **********************
/*		if ((HeIsSpinValid==1)&&(HeQSquare<10)&&(HeNu<10)&&(HeDp>-0.04)&&(HeDp<0.058)&&(HeReactZ>-0.155)&&(HeReactZ<0.175)&&(abs(HeTh)<0.07)&&(abs(HePh)<0.03)&&(He_x_bj<2)&&((HePShE+(2*HeShE))>900)&&(HeCerAsum>400))
		{
			if (int(HeEvTypeBits)==2)
			{
				HeT2unpolcuts++;

				if (int(HeSpin)==1)
				{
					thisRunSpinUp++;
				}
				if (int(HeSpin)==-1)
				{
					thisRunSpinDown++;
				}
		  

			}
		}
*/
// **************************************************************************************************************************

		HePrev_u3c = He_u3c;
		HeChargeScale = HeChargeScale + thisRunCharge;
		if (thisRunCharge != 0) {	
			HeTrueRunCounter++;
			cout << "HeTrueRunCounter: " << HeTrueRunCounter << ", Event Number: " << i << endl;


	/*		int chargeOffset;
			string chargeLine;
			std::string chargeHeRunNumberString;
			std::stringstream chargeOut;
			chargeOut << thisRunNumber;
			chargeHeRunNumberString = "Run ";
			chargeHeRunNumberString += chargeOut.str();
			bool chargeIsFound = false;
			chargeInFile.open(outChargeFileName);
			while (!chargeInFile.eof()){
				getline(chargeInFile, chargeLine);
				if ((chargeOffset = chargeLine.find(chargeHeRunNumberString, 0)) != string::npos)
				{
					cout << "Found " << chargeHeRunNumberString << endl;
					chargeIsFound = true;
				}
			}
			if (!chargeIsFound)
			{
				cout << "Run Number " << HePrevRunNumber << " not found in " << outChargeFileName << ". Adding now..." << endl;
				chargeOutFile << chargeHeRunNumberString << "\n" << thisHe_u1c << "\n" << thisHe_u1pp << "\n" << thisHe_u1pm << "\n" << thisHe_u1mp << "\n" << thisHe_u1mm << "\n" << thisHe_u3c << "\n" << thisHe_u3pp << "\n" << thisHe_u3pm << "\n" << thisHe_u3mp << "\n" << thisHe_u3mm << "\n" << thisHe_u10c << "\n" << thisHe_u10pp << "\n" << thisHe_u10pm << "\n" << thisHe_u10mp << "\n" << thisHe_u10mm << "\n" << thisHe_d1c << "\n" << thisHe_d1pp << "\n" << thisHe_d1pm << "\n" << thisHe_d1mp << "\n" << thisHe_d1mm << "\n" << thisHe_d3c << "\n" << thisHe_d3pp << "\n" << thisHe_d3pm << "\n" << thisHe_d3mp << "\n" << thisHe_d3mm << "\n" << thisHe_d10c << "\n" << thisHe_d10pp << "\n" << thisHe_d10pm << "\n" << thisHe_d10mp << "\n" << thisHe_d10mm << "\n\n";
			}
*/

			int offset;
			string line;
			std::string HeRunNumberString;
			std::stringstream out;
			out << thisRunNumber;
			HeRunNumberString = "Run ";
			HeRunNumberString += out.str();
			cout << "thisRunNumber: " << thisRunNumber << "     HeRunNumberString: " << HeRunNumberString << endl;
			bool isFound = false;
			inFile.open(outFileName);
			while (!inFile.eof()){
				getline(inFile, line);
				if ((offset = line.find(HeRunNumberString, 0)) != string::npos)
				{
					cout << "Found " << HeRunNumberString << endl;
					isFound = true;
				}
			}
			if (!isFound)
			{
				cout << "Run Number " << string(HeRunNumberString) << " not found in " << outFileName << ". Adding now..." << endl;
				outFile << HeRunNumberString << "\n" << thisRunCharge << "\n" << HeT2total << "\n" << HeTriggerstotal << "\n" << thisRunTargetChargeUp << "\n" << HeT2up << "\n" << HeTriggersUp << "\n" << thisRunTargetChargeDown << "\n" << HeT2down << "\n" << HeTriggersDown << "\n" << thisRunBeamChargeUp << "\n" << BeamT2up << "\n" << BeamTriggersUp << "\n" << thisRunBeamChargeDown << "\n" << BeamT2down << "\n" << BeamTriggersDown << "\n\n";

				HeT2total = 0;
				HeT2up = 0;
				HeT2down = 0;
				BeamT2up = 0;
				BeamT2down = 0;
				HeTriggerstotal = 0;
				HeTriggersUp = 0;
				HeTriggersDown = 0;
				BeamTriggersUp = 0;
				BeamTriggersDown = 0;
			}	
		}
		thisRunCharge = 0;
		thisRunTargetChargeUp = 0;
		thisRunTargetChargeDown = 0;
		inFile.close();
		chargeInFile.close();
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
	cout << "HeT2total: " << HeT2total << " HeTriggerstotal: " << HeTriggerstotal << endl;

	outFile.close();
	chargeOutFile.close();

}



