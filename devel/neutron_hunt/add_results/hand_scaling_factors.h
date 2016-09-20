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
	double HeChargeScaleUp; double HelivetimeUp;
	double HeChargeScaleDown; double HelivetimeDown;
	double BeamChargeScaleUp; double BeamlivetimeUp;
	double BeamChargeScaleDown; double BeamlivetimeDown;
	hand_scaling_factors(HeRunNumber, endHeRunNumber, HeChargeScale, Helivetime, HeChargeScaleUp, HelivetimeUp, HeChargeScaleDown, HelivetimeDown, BeamChargeScaleUp, BeamlivetimeUp, BeamChargeScaleDown, BeamlivetimeDown);
*/
//
//
// Elena Long
// 2011-01-03
//
// Edited to add:
//	2011-03-11	Beam Infortmaion (charge & livetime)
// **************************************************************************


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!! SEE NOTE ABOUT HeChargeScale BELOW !!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

void hand_scaling_factors(int HeRunNumber, int endHeRunNumber, double& HeChargeScale, double& Helivetime, double& HeChargeScaleUp, double& HelivetimeUp, double& HeChargeScaleDown, double& HelivetimeDown, double& BeamChargeScaleUp, double& BeamlivetimeUp, double& BeamChargeScaleDown, double& BeamlivetimeDown, TString kine, TString targ)
{
	cout << "vvvvvvvvvvvvvvvvvvvvvvvvv hand_scaling_factors.h vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
//	TString fileName = "/home/ellie/physics/e05-102/images/run_information/charge_and_livetime_R2.txt";
//	TString fileName = "/home/ellie/physics/e05-102/images/run_information/run_info_R.txt";
//	TString fileName = "/home/ellie/physics/e05-102/images/run_information/temp_q2_1_vert_3he_run_info.txt";

//	TString fileName = "/home/ellie/physics/e05-102/images/";
	TString fileName = "/u/home/ellie/";
	cout << "targ: " << targ << ", kine: " << kine << endl;
	if (kine == "1.0")
	{
		if (targ == "v") {fileName += "run_information/q2_1_vert_3he_run_info.txt";}
		if (targ == "l") {fileName += "run_information/q2_1_long_3he_run_info.txt";}
		if (targ == "t") {fileName += "run_information/q2_1_trans_3he_run_info.txt";}
		if (targ == "c") {fileName += "run_information/q2_1_carbon_run_info.txt";}
		if (targ == "vc") {fileName += "run_information/q2_1_v_carbon_run_info.txt";}
		if (targ == "ltc") {fileName += "run_information/q2_1_lt_carbon_run_info.txt";}
		if (targ == "h") {fileName += "run_information/q2_1_hydrogen_run_info.txt";}
		if (targ == "vh") {fileName += "run_information/q2_1_v_hydrogen_run_info.txt";}
		if (targ == "lth") {fileName += "run_information/q2_1_lt_hydrogen_run_info.txt";}
		if (targ == "n") {fileName += "run_information/q2_1_nitrogen_run_info.txt";}
		if (targ == "ltn") {fileName += "run_information/q2_1_lt_nitrogen_run_info.txt";}
	}
	if (kine == "0.5")
	{
		if (targ == "v") {fileName += "run_information/q2_05_vert_3he_run_info.txt";}
		if (targ == "h") {fileName += "run_information/q2_05_hydrogen_run_info.txt";}
	}
	if (kine == "0.4")
	{
		if (targ == "l") {fileName += "run_information/q2_04_long_3he_run_info.txt";}
		if (targ == "t") {fileName += "run_information/q2_04_trans_3he_run_info.txt";}
	}
	if (kine == "0.1")
	{
		if (targ == "v") {fileName += "run_information/q2_01_vert_3he_run_info.txt";}
		if (targ == "h") {fileName += "run_information/q2_01_hydrogen_run_info.txt";}
	}


//	ifstream inFile (fileName);
	std::string HeRunNumberString;
	std::stringstream out;
	string line;
	int offset;
	double thisRunCharge = 0;
	double thisRunChargeUp = 0;
	double thisRunChargeDown = 0;
	double thisRunBeamChargeUp = 0;
	double thisRunBeamChargeDown = 0;
	double thisRunT2 = 0;
	double thisRunT2up = 0;
	double thisRunT2down = 0;
	double thisRunBeamT2up = 0;
	double thisRunBeamT2down = 0;
	double thisRunTriggersTotal = 0;
	double thisRunTriggersUp = 0;
	double thisRunTriggersDown = 0;
	double thisRunBeamTriggersUp = 0;
	double thisRunBeamTriggersDown = 0;
	double HeT2total = 0;
	double HeT2totalUp = 0;
	double HeT2totalDown = 0;
	double BeamT2totalUp = 0;
	double BeamT2totalDown = 0;
	double HeTriggersTotal = 0;
	double HeTriggersTotalUp = 0;
	double HeTriggersTotalDown = 0;
	double BeamTriggersTotalUp = 0;
	double BeamTriggersTotalDown = 0;
	bool isFound = false;
	int lineCounter = 0;
	for (int i = HeRunNumber; i < (endHeRunNumber + 1); i++)
	{
		out.str("");
//		inFile.open(fileName);
		ifstream inFile (fileName);
		out << i;
		HeRunNumberString = "Run ";
		HeRunNumberString += out.str();
		cout << "Looking for charge and livetime for " << HeRunNumberString << "..." << endl;
		isFound = false;
		while(!inFile.eof() && !isFound)
		{
//			cout << "In while loop at line " << lineCounter << endl;
			getline(inFile, line);
			lineCounter++;
			if ((offset = line.find(HeRunNumberString, 0)) != string::npos)
			{
//				cout << "In if loop" << endl;
				cout << "Found " << HeRunNumberString << endl;
				getline(inFile, line);
				thisRunCharge = atof(line.c_str());
				getline(inFile, line);
				thisRunT2 = atof(line.c_str());
				getline(inFile, line);
				thisRunTriggersTotal = atof(line.c_str());

				getline(inFile, line);
				thisRunChargeUp = atof(line.c_str());
				getline(inFile, line);
				thisRunT2up = atof(line.c_str());
				getline(inFile, line);
				thisRunTriggersUp = atof(line.c_str());

				getline(inFile, line);
				thisRunChargeDown = atof(line.c_str());
				getline(inFile, line);
				thisRunT2down = atof(line.c_str());
				getline(inFile, line);
				thisRunTriggersDown = atof(line.c_str());

				getline(inFile, line);
				thisRunBeamChargeUp = atof(line.c_str());
				getline(inFile, line);
				thisRunBeamT2up = atof(line.c_str());
				getline(inFile, line);
				thisRunBeamTriggersUp = atof(line.c_str());

				getline(inFile, line);
				thisRunBeamChargeDown = atof(line.c_str());
				getline(inFile, line);
				thisRunBeamT2down = atof(line.c_str());
				getline(inFile, line);
				thisRunBeamTriggersDown = atof(line.c_str());

				cout << "Charge: " << thisRunCharge << ", T2: " << thisRunT2 << ", Total Triggers: " << thisRunTriggersTotal << endl;
				cout << "TargetChargeUp: " << thisRunChargeUp << ", Target T2 Up: " << thisRunT2up << ", Up Target Triggers: " << thisRunTriggersUp << endl;
				cout << "TargetChargeDown: " << thisRunChargeDown << ", Target T2 Down: " << thisRunT2down << ", Down Target Triggers: " << thisRunTriggersDown << endl;
				cout << "BeamChargeUp: " << thisRunBeamChargeUp << ", Beam T2 Up: " << thisRunBeamT2up << ", Up Beam Triggers: " << thisRunBeamTriggersUp << endl;
				cout << "BeamChargeDown: " << thisRunBeamChargeDown << ", Beam T2 Down: " << thisRunBeamT2down << ", Down Beam Triggers: " << thisRunBeamTriggersDown << endl;
				HeChargeScale = HeChargeScale + thisRunCharge;
				HeChargeScaleUp = HeChargeScaleUp + thisRunChargeUp;
				HeChargeScaleDown = HeChargeScaleDown + thisRunChargeDown;
				BeamChargeScaleUp = BeamChargeScaleUp + thisRunBeamChargeUp;
				BeamChargeScaleDown = BeamChargeScaleDown + thisRunBeamChargeDown;
				HeT2total = HeT2total + thisRunT2;
				HeT2totalUp = HeT2totalUp + thisRunT2up;
				HeT2totalDown = HeT2totalDown + thisRunT2down;
				BeamT2totalUp = BeamT2totalUp + thisRunBeamT2up;
				BeamT2totalDown = BeamT2totalDown + thisRunBeamT2down;
				HeTriggersTotal = HeTriggersTotal + thisRunTriggersTotal;
				HeTriggersTotalUp = HeTriggersTotalUp + thisRunTriggersUp;
				HeTriggersTotalDown = HeTriggersTotalDown + thisRunTriggersDown;
				BeamTriggersTotalUp = BeamTriggersTotalUp + thisRunBeamTriggersUp;
				BeamTriggersTotalDown = BeamTriggersTotalDown + thisRunBeamTriggersDown;
				cout << "So far, we have a total charge of " << HeChargeScale << ", T2 of " << HeT2total << ", and Triggers of " << HeTriggersTotal << endl;
				cout << "              target charge up of " << HeChargeScaleUp << ", T2Targetup of " << HeT2totalUp << ", and Up Target Triggers of " << HeTriggersTotalUp << endl;
				cout << "            target charge down of " << HeChargeScaleDown << ", T2Targetdown of " << HeT2totalDown << ", and Down Target Triggers of " << HeTriggersTotalDown << endl;
				cout << "              beam charge up of " << BeamChargeScaleUp << ", T2Beamup of " << BeamT2totalUp << ", and Up Beam Triggers of " << BeamTriggersTotalUp << endl;
				cout << "            beam charge down of " << BeamChargeScaleDown << ", T2Beamdown of " << BeamT2totalDown << ", and Down Beam Triggers of " << BeamTriggersTotalDown << endl;
				isFound = true;
				thisRunCharge = 0;
				thisRunChargeUp = 0;
				thisRunChargeDown = 0;
				thisRunBeamChargeUp = 0;
				thisRunBeamChargeDown = 0;
				thisRunT2 = 0;
				thisRunT2up = 0;
				thisRunT2down = 0;
				thisRunBeamT2up = 0;
				thisRunBeamT2down = 0;
				thisRunTriggersTotal = 0;
				thisRunTriggersUp = 0;
				thisRunTriggersDown = 0;
				thisRunBeamTriggersUp = 0;
				thisRunBeamTriggersDown = 0;
			}
//			else{ cout << "Working in else loop..." << endl;}

		}
		inFile.close();
	}
//	cout << "Number of He runs: " << HeRunCounter << endl << endl << endl << endl;
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
	HeChargeScaleUp = HeChargeScaleUp * 1.5577e-10;
	HeChargeScaleDown = HeChargeScaleDown * 1.5577e-10;
	BeamChargeScaleUp = BeamChargeScaleUp * 1.5577e-10;
	BeamChargeScaleDown = BeamChargeScaleDown * 1.5577e-10;
	cout << "Total Charge in Coulombs: " << HeChargeScale << " C" << endl;	
	cout << "Total Target Up Charge in Coulombs: " << HeChargeScaleUp << " C" << endl;	
	cout << "Total Target Down Charge in Coulombs: " << HeChargeScaleDown << " C" << endl;	
	cout << "Total Beam Up Charge in Coulombs: " << BeamChargeScaleUp << " C" << endl;	
	cout << "Total Beam Down Charge in Coulombs: " << BeamChargeScaleDown << " C" << endl;	
	Helivetime = HeT2total/(HeTriggersTotal+1e-15) + 1e-15;
	cout << "HeT2total: " << HeT2total << " Helivetime: " << Helivetime << endl;
	HelivetimeUp = HeT2totalUp/(HeTriggersTotalUp+1e-15) + 1e-15;
	cout << "HeT2totalUp: " << HeT2totalUp << " HelivetimeUp: " << HelivetimeUp << endl;
	HelivetimeDown = HeT2totalDown/(HeTriggersTotalDown+1e-15) + 1e-15;
	cout << "HeT2totalDown: " << HeT2totalDown << " HelivetimeDown: " << HelivetimeDown << endl;
	BeamlivetimeUp = BeamT2totalUp/(BeamTriggersTotalUp+1e-15) + 1e-15;
	cout << "BeamT2totalUp: " << BeamT2totalUp << " BeamlivetimeUp: " << BeamlivetimeUp << endl;
	BeamlivetimeDown = BeamT2totalDown/(BeamTriggersTotalDown+1e-15) + 1e-15;
	cout << "BeamT2totalDown: " << BeamT2totalDown << " BeamlivetimeDown: " << BeamlivetimeDown << endl;

	inFile.close();

	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;;
}



