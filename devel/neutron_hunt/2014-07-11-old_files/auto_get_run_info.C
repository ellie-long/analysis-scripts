// ***************************************************
//
// This script is a test to make sure that I understand
// what is happening when I take the Left TDC and subtract
// the Right TDC from it and how both of these work
// when the veto bars are defined.
//
// 2010-12-08
// Elena Long
//
// ***************************************************

#include <iostream>
#include <string>
#include <string.h>
#include <math.h>
#include <iomanip>
#include "hand_define_vetos.h"
#include "hand_draw.h"
#include "hand_basic_cuts.h"
#include "hand_draw_vetos.h"
#include "hand_draw_antivetos.h"
#include "run_scaling_factors.h"

// Search for HAND to get to the PMT definitions

void auto_get_run_info(){
	
	int beginRun = 20507;
	int endRun = 20512;

	for (int i=beginRun; i<endRun+1; i++)
	{

		int HeRunNumber = i;
		int endHeRunNumber = i;
		TChain* chainHe = new TChain("T");
		TString filenameHe;
		for (int thisHeRunNumber=HeRunNumber; thisHeRunNumber<(endHeRunNumber+1); thisHeRunNumber++)
		{
			// Skipping Vertical Carbon Runs
			if(thisHeRunNumber==20591){thisHeRunNumber=20596;}
			if(thisHeRunNumber==20731){thisHeRunNumber=20738;}
			if(thisHeRunNumber==20732){thisHeRunNumber=20738;}
			if(thisHeRunNumber==20733){thisHeRunNumber=20738;}
			if(thisHeRunNumber==20734){thisHeRunNumber=20738;}
			if(thisHeRunNumber==20736){thisHeRunNumber=20738;}
			if(thisHeRunNumber==20737){thisHeRunNumber=20738;}
			if(thisHeRunNumber==20762){thisHeRunNumber=20789;}
			if(thisHeRunNumber==20763){thisHeRunNumber=20789;}
			if(thisHeRunNumber==20764){thisHeRunNumber=20789;}
			if(thisHeRunNumber==20791){thisHeRunNumber=20814;}
			if(thisHeRunNumber==20792){thisHeRunNumber=20814;}

			// Skipping Longitudinal Carbon Runs
			if(thisHeRunNumber==22380){thisHeRunNumber=22393;}
			if(thisHeRunNumber==22389){thisHeRunNumber=22393;}
			if(thisHeRunNumber==22425){thisHeRunNumber=22436;}
			if(thisHeRunNumber==22426){thisHeRunNumber=22436;}

			// Skipping Transverse Carbon Runs
			if(thisHeRunNumber==22461){thisHeRunNumber=22465;}


			for (int t=0; t<1000; t++)
			{
//				filenameHe = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_R_";
				filenameHe = "/home/ellie/physics/e05-102/ellana/ROOTfiles/q2_01_vert/e05102_R_";
	//			filenameHe = "/home/ellie/physics/e05-102/backupROOTfiles/e05102_R_";
				filenameHe += thisHeRunNumber;
				if (t != 0)
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
					t=999999999;
				}
				TFile fileHe(filenameHe);
			}
		}

// **********************************************************************************************
// This bit of code should set the charge and livetime scaling factors
		double HeChargeScale;
		double Helivetime;
		run_scaling_factors(HeRunNumber, endHeRunNumber, chainHe, HeChargeScale, Helivetime);
// **********************************************************************************************
	}
	cout << "All done!" << endl;



}







































