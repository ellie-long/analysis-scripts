// **************************************************************************
//
// This script will search through the images/run_information/*.txt files
// and output the run number and charge info into a text file so that I
// can add it to my Run Info # database easily.
//
// Elena Long
// 2011-06-23
//
// **************************************************************************


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

void output_run_charge()
{
	cout << "vvvvvvvvvvvvvvvvvvvvvvvvv output_run_charge.C vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
	TString fileName;
	TString outFileName;
	ofstream outFile;
	ifstream inFile;
	string line;
	string runNum;
	string charge;

	for (int i=0; i<7; i++)
	{
		if (i==0)
		{
			fileName = "/home/ellie/physics/e05-102/images/run_information/q2_1_vert_3he_run_info.txt";
			outFileName = "/home/ellie/physics/e05-102/images/run_information/run_and_charge_for_q2_1_vert_3he.txt";
		}
		if (i==1)
		{
			fileName = "/home/ellie/physics/e05-102/images/run_information/q2_1_long_3he_run_info.txt";
			outFileName = "/home/ellie/physics/e05-102/images/run_information/run_and_charge_for_q2_1_long_3he.txt";
		}
		if (i==2)
		{
			fileName = "/home/ellie/physics/e05-102/images/run_information/q2_1_trans_3he_run_info.txt";
			outFileName = "/home/ellie/physics/e05-102/images/run_information/run_and_charge_for_q2_1_trans_3he.txt";
		}
		if (i==3)
		{
			fileName = "/home/ellie/physics/e05-102/images/run_information/q2_1_carbon_run_info.txt";
			outFileName = "/home/ellie/physics/e05-102/images/run_information/run_and_charge_for_q2_1_carbon.txt";
		}
		if (i==4)
		{
			fileName = "/home/ellie/physics/e05-102/images/run_information/q2_1_hydrogen_run_info.txt";
			outFileName = "/home/ellie/physics/e05-102/images/run_information/run_and_charge_for_q2_1_hydrogen.txt";
		}
		if (i==5)
		{
			fileName = "/home/ellie/physics/e05-102/images/run_information/q2_05_vert_3he_run_info.txt";
			outFileName = "/home/ellie/physics/e05-102/images/run_information/run_and_charge_for_q2_05_vert_3he.txt";
		}
		if (i==6)
		{
			fileName = "/home/ellie/physics/e05-102/images/run_information/q2_01_vert_3he_run_info.txt";
			outFileName = "/home/ellie/physics/e05-102/images/run_information/run_and_charge_for_q2_01_vert_3he.txt";
		}
	

//		outFile.open(outFileName, ios::app);
		outFile.open(outFileName);
		

		inFile.open(fileName);
		cout << "inFile: " << fileName << endl;
		cout << "outFile: " << outFileName << endl;
		while (!inFile.eof())
		{
			getline(inFile,line);
			runNum = line;

			getline(inFile,line);
			charge = line;

			getline(inFile,line);
			getline(inFile,line);
			getline(inFile,line);
			getline(inFile,line);
			getline(inFile,line);
			getline(inFile,line);
			getline(inFile,line);
			getline(inFile,line);
			getline(inFile,line);
			getline(inFile,line);
			getline(inFile,line);
			getline(inFile,line);
			getline(inFile,line);
			getline(inFile,line);
			getline(inFile,line);

			outFile << runNum << "	" << charge << "\n";
			cout << runNum << "	" << charge << endl;
		}
		cout << endl << endl << endl;






		inFile.close();
		outFile.close();
	}

	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;;
}



