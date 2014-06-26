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

	int CRunNumber=20591;
	int endCRunNumber=22461;
	int AyHeRunNumber=20596;
//	int endAyHeRunNumber=20789;
	int endAyHeRunNumber=22489;
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
	title += "_AyHe_Runs_";
	title += AyHeRunNumber;
	title += "-";
	title += endAyHeRunNumber;

	TString outFileName = "output_files/";
	outFileName += title;
	outFileName += ".txt";

	ofstream outFile;
	outFile.open(outFileName);


	TCut cut = "";  
	TCut kinematics = "PriKineR.Q2<10 && GoodElectron==1 && PriKineR.nu<10";
//	TCut eventtype = "D.evtypebits&(1<<1)>0";
	TCut eventtype = "(D.evtypebits&2)==2";
	TCut dp = "ExTgtCor_R.dp>-0.04 && ExTgtCor_R.dp<0.053";
	TCut target = "ReactPt_R.z>-0.15 && ReactPt_R.z<0.17";
        double thbound = 0.07;
        double phbound = 0.03;
        TString thetaphiRStr = "abs(ExTgtCor_R.ph)<";
        thetaphiRStr += phbound;
        thetaphiRStr += " && abs(ExTgtCor_R.th)<";
        thetaphiRStr += thbound;
        TCut thph = thetaphiRStr;
	TCut tracks = "R.tr.n==1 && R.vdc.u1.nhit>3 && R.vdc.u1.nhit<7 && R.vdc.u2.nhit>3 && R.vdc.u2.nhit<7 && R.vdc.v1.nhit>3 && R.vdc.v1.nhit<7 && R.vdc.v2.nhit>3 && R.vdc.v2.nhit<7";
	TCut xbj = "";
        TCut pssh = "(R.ps.e + 2*R.sh.e)>900 && R.ps.e>1 && R.sh.e>1";
        TCut cerenkov = "R.cer.asum_c>150";

//	TCut cut = "";
//	TCut eventtype = "";
//	TCut target = "";
//	TCut thph = "";
//	TCut dp = "";

	TCut cuts = kinematics && target && thph && dp && eventtype && tracks && xbj && pssh && cerenkov;


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



	TChain* chainC = new TChain("T");
	TChain* chainAyHe = new TChain("T");

	gStyle->SetErrorX(.25);
	gStyle->SetEndErrorSize(.25);
	ifstream inp;
	ofstream out;

	TString filenameC;
	TString filenameAyHe;


// Below is the loop for adding chains for the Carbon run
	for (int thisCRunNumber=CRunNumber; thisCRunNumber<(endCRunNumber+1); thisCRunNumber++)
	{
		if(thisCRunNumber==20592){thisCRunNumber=20731;}
		if(thisCRunNumber==20735){thisCRunNumber=20762;}
		if(thisCRunNumber==20765){thisCRunNumber=22380;}
		if(thisCRunNumber==22381){thisCRunNumber=22389;}
		if(thisCRunNumber==22390){thisCRunNumber=22425;}
		if(thisCRunNumber==22427){thisCRunNumber=22461;}
		if(thisCRunNumber==22462){thisCRunNumber=99999;}

		for (int t=0; t<1000;t++)
		{
		filenameC = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_R_";
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

	for (int thisAyHeRunNumber=AyHeRunNumber;thisAyHeRunNumber<(endAyHeRunNumber+1); thisAyHeRunNumber++)
	{
		// Going to next set of Q2 runs
/*		if (Q2=="1.0")
		{
			if(thisAyHeRunNumber==20791){thisAyHeRunNumber=22393;}
		}
*/
		// Skipping Vertical Carbon Runs
		if(thisAyHeRunNumber==20591){thisAyHeRunNumber=20596;}
		if(thisAyHeRunNumber==20731){thisAyHeRunNumber=20738;}
		if(thisAyHeRunNumber==20732){thisAyHeRunNumber=20738;}
		if(thisAyHeRunNumber==20733){thisAyHeRunNumber=20738;}
		if(thisAyHeRunNumber==20734){thisAyHeRunNumber=20738;}
		if(thisAyHeRunNumber==20736){thisAyHeRunNumber=20738;}
		if(thisAyHeRunNumber==20737){thisAyHeRunNumber=20738;}
		if(thisAyHeRunNumber==20762){thisAyHeRunNumber=20789;}
		if(thisAyHeRunNumber==20763){thisAyHeRunNumber=20789;}
		if(thisAyHeRunNumber==20764){thisAyHeRunNumber=20789;}
		if(thisAyHeRunNumber==20791){thisAyHeRunNumber=22393;}
//		if(thisAyHeRunNumber==20791){thisAyHeRunNumber=20814;}
		if(thisAyHeRunNumber==20792){thisAyHeRunNumber=20814;}

		// Skipping Longitudinal Carbon Runs
		if(thisAyHeRunNumber==22380){thisAyHeRunNumber=22393;}
		if(thisAyHeRunNumber==22389){thisAyHeRunNumber=22393;}
		if(thisAyHeRunNumber==22425){thisAyHeRunNumber=22436;}
		if(thisAyHeRunNumber==22426){thisAyHeRunNumber=22436;}

		// Skipping Transverse Carbon Runs
		if(thisAyHeRunNumber==22461){thisAyHeRunNumber=22465;}
		if(thisAyHeRunNumber==20591){thisAyHeRunNumber=20596;}
		if(thisAyHeRunNumber==22397){thisAyHeRunNumber=22398;}
		for (int t=0; t<1000;t++)
		{
			filenameAyHe = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_R_";
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



// This section will put the 3He root data into doubles so that
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
        chainAyHe->SetBranchAddress("he3R.IsSpinValid", &AyHeIsSpinValid);
        chainAyHe->SetBranchAddress("he3R.Spin", &AyHeSpin);
        chainAyHe->SetBranchAddress("PriKineR.Q2", &AyHeQSquare);
        chainAyHe->SetBranchAddress("PriKineR.nu", &AyHeNu);
        chainAyHe->SetBranchAddress("D.evtypebits", &AyHeEvTypeBits);
        chainAyHe->SetBranchAddress("ExTgtCor_R.dp", &AyHeDp);
        chainAyHe->SetBranchAddress("ExTgtCor_R.th", &AyHeTh);
        chainAyHe->SetBranchAddress("ExTgtCor_R.ph", &AyHePh);
        chainAyHe->SetBranchAddress("ReactPt_R.z", &AyHeReactZ);
        chainAyHe->SetBranchAddress("PriKineRHe3.x_bj", &AyHe_x_bj);
        chainAyHe->SetBranchAddress("R.sh.e", &AyHeShE);
        chainAyHe->SetBranchAddress("R.ps.e", &AyHePShE);
        chainAyHe->SetBranchAddress("R.cer.asum_c", &AyHeCerAsum);
        chainAyHe->SetBranchAddress("g.runnum", &AyHeRunNum);
        chainAyHe->SetBranchAddress("evright_u3c", &AyHe_u3c);
        chainAyHe->SetBranchAddress("evright_u3pp", &AyHe_u3pp);
        chainAyHe->SetBranchAddress("evright_u3pm", &AyHe_u3pm);
        chainAyHe->SetBranchAddress("evright_u3mm", &AyHe_u3mm);
        chainAyHe->SetBranchAddress("evright_u3mp", &AyHe_u3mp);

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
        for (int i=0; i<AyHeNumberOfEvents; i++)
        {
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
                        AyHeRatio = ((AyHeInfoArray[AyHeRunNumPlace][12]/AyHeInfoArray[AyHeRunNumPlace][11])*AyHeInfoArray[AyHeRunNumPlace][9])/((AyHeInfoArray[AyHeRunNumPlace][13]/AyHeInfoArray[AyHeRunNumPlace][11])*AyHeInfoArray[AyHeRunNumPlace][10]+1e-15);
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
                        AyHeRatio = ((AyHeInfoArray[AyHeRunNumPlace][12]/AyHeInfoArray[AyHeRunNumPlace][11])*AyHeInfoArray[AyHeRunNumPlace][9])/((AyHeInfoArray[AyHeRunNumPlace][13]/AyHeInfoArray[AyHeRunNumPlace][11])*AyHeInfoArray[AyHeRunNumPlace][10] + 1e-15);
                        AyHeInfoArray[AyHeRunNumPlace][7] = 2*AyHeRatio*sqrt(AyHeInfoArray[AyHeRunNumPlace][2]*AyHeInfoArray[AyHeRunNumPlace][2]*AyHeInfoArray[AyHeRunNumPlace][3]+AyHeInfoArray[AyHeRunNumPlace][3]*AyHeInfoArray[AyHeRunNumPlace][3]*AyHeInfoArray[AyHeRunNumPlace][2])/pow(AyHeInfoArray[AyHeRunNumPlace][2]+AyHeRatio*AyHeInfoArray[AyHeRunNumPlace][3]+1e-15,2);
                        cout << "Ending Run Number " << AyHeInfoArray[AyHeRunNumPlace][0] << ", AyHe_u3c = " << AyHeInfoArray[AyHeRunNumPlace][8] << ", AyHe_u3p = " << AyHeInfoArray[AyHeRunNumPlace][9] << ", AyHe_u3m = " << AyHeInfoArray[AyHeRunNumPlace][10] << ", Error = " << AyHeInfoArray[AyHeRunNumPlace][7] << endl;
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
                        if (int(AyHeEvTypeBits)==2)
                        {
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
        chainC->SetBranchAddress("he3R.IsSpinValid", &CIsSpinValid);
        chainC->SetBranchAddress("he3R.Spin", &CSpin);
        chainC->SetBranchAddress("PriKineR.Q2", &CQSquare);
        chainC->SetBranchAddress("PriKineR.nu", &CNu);
        chainC->SetBranchAddress("D.evtypebits", &CEvTypeBits);
        chainC->SetBranchAddress("ExTgtCor_R.dp", &CDp);
        chainC->SetBranchAddress("ExTgtCor_R.th", &CTh);
        chainC->SetBranchAddress("ExTgtCor_R.ph", &CPh);
        chainC->SetBranchAddress("ReactPt_R.z", &CReactZ);
        chainC->SetBranchAddress("PriKineRHe3.x_bj", &C_x_bj);
        chainC->SetBranchAddress("R.sh.e", &CShE);
        chainC->SetBranchAddress("R.ps.e", &CPShE);
        chainC->SetBranchAddress("R.cer.asum_c", &CCerAsum);
        chainC->SetBranchAddress("g.runnum", &CRunNum);
        chainC->SetBranchAddress("evright_u3c", &C_u3c);
        chainC->SetBranchAddress("evright_u3pp", &C_u3pp);
        chainC->SetBranchAddress("evright_u3pm", &C_u3pm);
        chainC->SetBranchAddress("evright_u3mm", &C_u3mm);
        chainC->SetBranchAddress("evright_u3mp", &C_u3mp);

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
                        CRatio = ((CInfoArray[CRunNumPlace][12]/CInfoArray[CRunNumPlace][11])*CInfoArray[CRunNumPlace][9])/((CInfoArray[CRunNumPlace][13]/CInfoArray[CRunNumPlace][11])*CInfoArray[CRunNumPlace][10]+1e-15);
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
                        CRatio = ((CInfoArray[CRunNumPlace][12]/CInfoArray[CRunNumPlace][11])*CInfoArray[CRunNumPlace][9])/((CInfoArray[CRunNumPlace][13]/CInfoArray[CRunNumPlace][11])*CInfoArray[CRunNumPlace][10] + 1e-15);
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

/*	// Defines Cuts 1 Canvas
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
	TString titledpAyHe = "dp Cut from 3AyHe Runs";
	cout << "Drawing " << titledpAyHe << "..." << endl;
	chainAyHe->Draw("ExTgtCor_R.dp>>AyHedpNoCut(400,-0.08,0.08)", "", "");
	chainAyHe->Draw("ExTgtCor_R.dp>>AyHedpCut(400,-0.08,0.08)", dp, "");
	AyHedpNoCut->SetTitle(titledpAyHe);
	AyHedpNoCut->Draw();
	AyHedpCut->SetLineColor(kBlack);
	AyHedpCut->SetFillColor(kViolet);
	AyHedpCut->Draw("same");
	cuts1pad01->Update();

	cuts1pad02->cd();
	TString titledpC = "dp Cut from 12C Runs";
	cout << "Drawing " << titledpC << "..." << endl;
	chainC->Draw("ExTgtCor_R.dp>>CdpNoCut(400,-0.08,0.08)", "", "");
	chainC->Draw("ExTgtCor_R.dp>>CdpCut(400,-0.08,0.08)", dp, "");
	CdpNoCut->SetTitle(titledpC);
	CdpNoCut->Draw();
	CdpCut->SetLineColor(kBlack);
	CdpCut->SetFillColor(kViolet);
	CdpCut->Draw("same");
	cuts1pad02->Update();

	cuts1pad03->cd();
	TString titleTargetAyHe = "Target Cut for 3AyHe Runs";
	cout << "Drawing " << titleTargetAyHe << "..." << endl;
	chainAyHe->Draw("ReactPt_R.z>>AyHeReactZNoCut(400,-0.3,0.3)", "", "");
	chainAyHe->Draw("ReactPt_R.z>>AyHeReactZCut(400,-0.3,0.3)", target, "");
	AyHeReactZNoCut->SetTitle(titleTargetAyHe);
	AyHeReactZNoCut->Draw();
	AyHeReactZCut->SetLineColor(kBlack);
	AyHeReactZCut->SetFillColor(kViolet);
	AyHeReactZCut->Draw("same");
	cuts1pad03->Update();

	cuts1pad04->cd();
	TString titleTargetC = "Target Cut for 12C Runs";
	cout << "Drawing " << titleTargetC << "..." << endl;
	chainC->Draw("ReactPt_R.z>>CReactZNoCut(400,-0.3,0.3)", "", "");
	chainC->Draw("ReactPt_R.z>>CReactZCut(400,-0.3,0.3)", target, "");
	CReactZNoCut->SetTitle(titleTargetC);
	CReactZNoCut->Draw();
	CReactZCut->SetLineColor(kBlack);
	CReactZCut->SetFillColor(kViolet);
	CReactZCut->Draw("same");
	cuts1pad04->Update();

	cuts1pad05->cd();
        cout << "Drawing 3AyHe Theta and Phi Cut..." << endl;
        TString titleThetaPhiCut = "3AyHe Theta and Phi";
        TH2F *AyHeThetaPhiCut = new TH2F("AyHeThetaPhiCut",titleThetaPhiCut,100,-0.05,0.05,100,-0.1,0.1);
        chainAyHe->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>AyHeThetaPhiCut", target, "");
        AyHeThetaPhiCut->SetTitle(titleThetaPhiCut);
        AyHeThetaPhiCut->SetStats(kFALSE);
        AyHeThetaPhiCut->Draw("COLZ");
        AyHebottom = new TLine(-phbound,-thbound,phbound,-thbound);
        AyHetop = new TLine(-phbound,thbound,phbound,thbound);
        AyHeleft = new TLine(-phbound,-thbound,-phbound,thbound);
        AyHeright = new TLine(phbound,-thbound,phbound,thbound);
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
	cuts1pad05->Update();

	cuts1pad06->cd();
        cout << "Drawing 12C Theta and Phi Cut..." << endl;
        TString titleThetaPhiCut = "12 C Theta and Phi";
        TH2F *CThetaPhiCut = new TH2F("CThetaPhiCut",titleThetaPhiCut,100,-0.05,0.05,100,-0.1,0.1);
        chainC->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>CThetaPhiCut", target, "");
        CThetaPhiCut->SetTitle(titleThetaPhiCut);
        CThetaPhiCut->SetStats(kFALSE);
        CThetaPhiCut->Draw("COLZ");
        Cbottom = new TLine(-phbound,-thbound,phbound,-thbound);
        Ctop = new TLine(-phbound,thbound,phbound,thbound);
        Cleft = new TLine(-phbound,-thbound,-phbound,thbound);
        Cright = new TLine(phbound,-thbound,phbound,thbound);
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
        TString AyHetitlex = "3AyHe Bjorken x cut";
        AyHetitlex += " (x=Q^2/[2m*nu])";
        cout << "Drawing " << AyHetitlex << "..." << endl;
        TH1F *AyHehistx = new TH1F("AyHehistx",AyHetitlex,bins,xmin,xmax);
        TH1F *AyHehistxcut = new TH1F("AyHehistxcut",AyHetitlex,bins,xmin,xmax);
        AyHehistx->Sumw2();
        chainAyHe->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>AyHehistx", cut && kinematics && eventtype && dp && target && thph && tracks && cerenkov && pssh, "E");
        chainAyHe->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>AyHehistxcut", cuts, "E");
        AyHehistx->Draw();
        AyHehistxcut->SetFillColor(kViolet);
        AyHehistxcut->Draw("same");
	cuts1pad07->Update();

	cuts1pad08->cd();
        TString Ctitlex = "12C Bjorken x cut";
        Ctitlex += " (x=Q^2/[2m*nu])";
        cout << "Drawing " << Ctitlex << "..." << endl;
        TH1F *Chistx = new TH1F("Chistx",Ctitlex,bins,xmin,xmax);
        TH1F *Chistxcut = new TH1F("Chistxcut",Ctitlex,bins,xmin,xmax);
        Chistx->Sumw2();
        chainC->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>Chistx", cut && kinematics && eventtype && dp && target && thph && tracks && cerenkov && pssh, "E");
        chainC->Draw("(PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315))>>Chistxcut", cuts, "E");
        Chistx->Draw();
        Chistxcut->SetFillColor(kViolet);
        Chistxcut->Draw("same");
	cuts1pad08->Update();

	// Defines Cuts 2 Canvas
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
	TString titleQ2WAyHe = "Q2 v. Nu for 3AyHe";
	cout << "Drawing " << titleQ2WAyHe << "..." << endl;
	chainAyHe->Draw("PriKineR.Q2:PriKineR.nu>>Q2WAyHe(100,0.3,0.8,400,0,1.6)", cuts, "");
	Q2WAyHe->SetTitle(titleQ2WAyHe);
	Q2WAyHe->SetStats(kFALSE);
	Q2WAyHe->Draw("COLZ");
	cuts2pad01->Update();

	cuts2pad02->cd();
	TString titleQ2WC = "Q2 v. Nu for 12C";
	cout << "Drawing " << titleQ2WC << "..." << endl;
	chainC->Draw("PriKineR.Q2:PriKineR.nu>>Q2WC(100,0.3,0.8,400,0,1.6,100)", cuts, "");
	Q2WC->SetTitle(titleQ2WC);
	Q2WC->SetStats(kFALSE);
	Q2WC->Draw("COLZ");
	cuts2pad02->Update();

        cuts2pad03->cd();
        cout << "Drawing 3AyHe Preshower/Shower No Cuts..." << endl;
        TString titlePsSh = "3AyHe Preshower and Shower - No Cuts";
        TH2F *AyHePsShCut = new TH2F("AyHePsShCut",titlePsSh,200,1,2500,200,1,1500);
        chainAyHe->Draw("R.ps.e:R.sh.e>>AyHePsShCut", "", "");
        AyHePsShCut->SetTitle(titlePsSh);
        AyHePsShCut->SetStats(kFALSE);
        AyHePsShCut->Draw("COLZ");
        AyHepsshcut = new TLine(0,900,450,0);
        AyHepsshcut->SetLineColor(kViolet);
        AyHepsshcut->SetLineWidth(3);
        AyHepsshcut->Draw("same");
	cuts2pad03->Update();

        cuts2pad04->cd();
        cout << "Drawing 12C Preshower/Shower No Cuts..." << endl;
        TString CtitlePsSh = "12C Preshower and Shower - No Cuts";
        TH2F *CPsShCut = new TH2F("CPsShCut",CtitlePsSh,200,1,2500,200,1,1500);
        chainC->Draw("R.ps.e:R.sh.e>>CPsShCut", "", "");
        CPsShCut->SetTitle(CtitlePsSh);
        CPsShCut->SetStats(kFALSE);
        CPsShCut->Draw("COLZ");
        Cpsshcut = new TLine(0,900,450,0);
        Cpsshcut->SetLineColor(kViolet);
        Cpsshcut->SetLineWidth(3);
        Cpsshcut->Draw("same");
	cuts2pad04->Update();

	cuts2pad05->cd();
        cout << "Drawing 3AyHe Preshower/Shower with Cuts..." << endl;
        TString AyHetitlePsSh = "3AyHe Preshower and Shower with cuts";
        TH2F *AyHePsShCut = new TH2F("AyHePsShCut",AyHetitlePsSh,200,1,2500,200,1,1500);
        chainAyHe->Draw("R.ps.e:R.sh.e>>AyHePsShCut", cuts, "");
        AyHePsShCut->SetTitle(AyHetitlePsSh);
        AyHePsShCut->SetStats(kFALSE);
        AyHePsShCut->Draw("COLZ");
        AyHepsshcut->Draw("same");
	cuts2pad05->Update();

	cuts2pad06->cd();
        cout << "Drawing 12C Preshower/Shower with Cuts..." << endl;
        TString CtitlePsSh = "12C Preshower and Shower with cuts";
        TH2F *CPsShCut = new TH2F("CPsShCut",CtitlePsSh,200,1,2500,200,1,1500);
        chainC->Draw("R.ps.e:R.sh.e>>CPsShCut", cuts, "");
        CPsShCut->SetTitle(CtitlePsSh);
        CPsShCut->SetStats(kFALSE);
        CPsShCut->Draw("COLZ");
        Cpsshcut->Draw("same");
	cuts2pad06->Update();

	cuts2pad07->cd();
        TString AyHetitlecerenkov = "3AyHe Cerenkov Cut";
        cout << "Drawing " << AyHetitlecerenkov << "..." << endl;
        TH1F *AyHehistcerenkov = new TH1F("AyHehistcerenkov",AyHetitlecerenkov,200,-25,2000);
        TH1F *AyHehistcerenkovcut = new TH1F("AyHehistcerenkovcut",AyHetitlecerenkov,200,-25,2000);
        chainAyHe->Draw("R.cer.asum_c>>AyHehistcerenkov", "", "");
        chainAyHe->Draw("R.cer.asum_c>>AyHehistcerenkovcut", cerenkov, "");
        AyHehistcerenkov->SetTitle(AyHetitlecerenkov);
        AyHehistcerenkov->SetStats(kFALSE);
        AyHehistcerenkovcut->SetFillColor(kViolet);
        AyHehistcerenkov->Draw();
        AyHehistcerenkovcut->Draw("same");
	cuts2pad07->Update();

	cuts2pad08->cd();
        TString Ctitlecerenkov = "12C Cerenkov Cut";
        cout << "Drawing " << Ctitlecerenkov << "..." << endl;
        TH1F *Chistcerenkov = new TH1F("Chistcerenkov",Ctitlecerenkov,200,-25,2000);
        TH1F *Chistcerenkovcut = new TH1F("Chistcerenkovcut",Ctitlecerenkov,200,-25,2000);
        chainC->Draw("R.cer.asum_c>>Chistcerenkov", "", "");
        chainC->Draw("R.cer.asum_c>>Chistcerenkovcut", cerenkov, "");
        Chistcerenkov->SetTitle(Ctitlecerenkov);
        Chistcerenkov->SetStats(kFALSE);
        Chistcerenkovcut->SetFillColor(kViolet);
        Chistcerenkov->Draw();
        Chistcerenkovcut->Draw("same");
	cuts2pad08->Update();
*/
	// Defines x_Bj Canvas
	TCanvas *xbjCanvas = new TCanvas("xbjCanvas","x of 12C and 3AyHe",1360,800);//x,y
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
	chainC->Draw("PriKineR.x_bj>>histC", cuts, "E");
	histC->Scale(1/CChargeScale);
	histC->Draw();
/*	TF1 *fitC1 = new TF1("fitC1","[0]*exp(-x*[1])",1.45,1.6);
	fitC1->SetParNames("C Red p1","C Red p2");
	fitC1->SetLineColor(kRed);
	TF1 *fitC2 = new TF1("fitC2","[0]*exp(-x*[1])",1.6,1.8);
	fitC2->SetParNames("C Blue p1","C Blue p2");
	fitC2->SetLineColor(kBlue);
	TF1 *fitC3 = new TF1("fitC3","[0]*exp(-x*[1])",1.35,1.45);
	fitC3->SetParNames("C Green p1","C Green p2");
	fitC3->SetLineColor(kGreen);
	histC->Fit("fitC2","R");
	histC->Fit("fitC3","R+");
	histC->Fit("fitC1","R+");
	Double_t fitC1const = fitC1->GetParameter(0);
	Double_t fitC1expconst = fitC1->GetParameter(1);
	Double_t fitC1consterror = fitC1->GetParError(0);
	Double_t fitC1expconsterror = fitC1->GetParError(1);
	Double_t fitC2const = fitC2->GetParameter(0);
	Double_t fitC2expconst = fitC2->GetParameter(1);
	Double_t fitC2consterror = fitC2->GetParError(0);
	Double_t fitC2expconsterror = fitC2->GetParError(1);
	Double_t fitC3const = fitC3->GetParameter(0);
	Double_t fitC3expconst = fitC3->GetParameter(1);
	Double_t fitC3consterror = fitC3->GetParError(0);
	Double_t fitC3expconsterror = fitC3->GetParError(1);
//	histC->Fit("fitC2","R");
//	histC->Fit("fitC3","R+");
//	histC->Fit("fitC1","R+");
	outFile << "C1 range: 1.46-1.60		C2 range: 1.60-1.80		C3 range: 1.35-1.45" << endl;
	outFile << "C1:" << fitC1const << " | C1 error: " << fitC1consterror << " | Log C1: " << fitC1expconst << " | Log C1 error: " << fitC1expconsterror << endl;
	outFile << "C2:" << fitC2const << " | C2 error: " << fitC2consterror << " | Log C2: " << fitC2expconst << " | Log C2 error: " << fitC2expconsterror << endl;
	outFile << "C3:" << fitC3const << " | C3 error: " << fitC3consterror << " | Log C3: " << fitC3expconst << " | Log C3 error: " << fitC3expconsterror << endl << endl << endl;
*/	xbjpad01->Update();

	xbjpad02->cd();
	xbjpad02->SetLogy();
	cout << "Drawing " << titleC << " in log scale..." << endl;
	TH1F *loghistC = new TH1F("loghistC",titleC,bins,xmin,xmax);
	loghistC->Sumw2();
	chainC->Draw("PriKineR.x_bj>>loghistC", cuts, "E");
	loghistC->Scale(1/CChargeScale);
	loghistC->Draw();
/*	fitC1->SetParNames("C Red p1","C Red p2");
	fitC1->SetLineColor(kRed);
	fitC2->SetParNames("C Blue p1","C Blue p2");
	fitC2->SetLineColor(kBlue);
	fitC3->SetParNames("C Green p1","C Green p2");
	fitC3->SetLineColor(kGreen);
	loghistC->Fit("fitC1","R");
	loghistC->Fit("fitC3","R+");
	loghistC->Fit("fitC2","R+");
	Double_t fitC1const = fitC1->GetParameter(0);
	Double_t fitC1expconst = fitC1->GetParameter(1);
	Double_t fitC1consterror = fitC1->GetParError(0);
	Double_t fitC1expconsterror = fitC1->GetParError(1);
	Double_t fitC2const = fitC2->GetParameter(0);
	Double_t fitC2expconst = fitC2->GetParameter(1);
	Double_t fitC2consterror = fitC2->GetParError(0);
	Double_t fitC2expconsterror = fitC2->GetParError(1);
	Double_t fitC3const = fitC3->GetParameter(0);
	Double_t fitC3expconst = fitC3->GetParameter(1);
	Double_t fitC3consterror = fitC3->GetParError(0);
	Double_t fitC3expconsterror = fitC3->GetParError(1);
	outFile << "Log C1 range: 1.46-1.60		Log C2 range: 1.60-1.80		Log C3 range: 1.35-1.45" << endl;
	outFile << "C1:" << fitC1const << " | C1 error: " << fitC1consterror << " | Log C1: " << fitC1expconst << " | Log C1 error: " << fitC1expconsterror << endl;
	outFile << "C2:" << fitC2const << " | C2 error: " << fitC2consterror << " | Log C2: " << fitC2expconst << " | Log C2 error: " << fitC2expconsterror << endl;
	outFile << "C3:" << fitC3const << " | C3 error: " << fitC3consterror << " | Log C3: " << fitC3expconst << " | Log C3 error: " << fitC3expconsterror << endl << endl << endl;
*/	xbjpad02->Update();


	xbjpad03->cd();
	TString titleAyHe = "x for 3AyHe at Q2 of ";
	titleAyHe += Q2;
	cout << "Drawing " << titleAyHe << "..." << endl;
	TH1F *histAyHe = new TH1F("histAyHe",titleAyHe,bins,xmin,xmax);
	histAyHe->Sumw2();
	chainAyHe->Draw("PriKineR.x_bj>>histAyHe", cuts, "E");
	histAyHe->Scale(1/AyHeChargeScale);
	histAyHe->Draw();
/*	TF1 *fitAyHe1 = new TF1("fitAyHe1","[0]*exp(-x*[1])",1.45,1.6);
	fitAyHe1->SetParNames("AyHe Red p1", "AyHe Red p2");
	fitAyHe1->SetLineColor(kRed);
	TF1 *fitAyHe2 = new TF1("fitAyHe2","[0]*exp(-x*[1])",1.6,1.8);
	fitAyHe2->SetParNames("AyHe Blue p1","AyHe Blue p2");
	fitAyHe2->SetLineColor(kBlue);
	TF1 *fitAyHe3 = new TF1("fitAyHe3","[0]*exp(-x*[1])",1.35,1.45);
	fitAyHe3->SetParNames("AyHe Green p1","AyHe Green p2");
	fitAyHe3->SetLineColor(kGreen);
	histAyHe->Fit("fitAyHe2","R+");
	histAyHe->Fit("fitAyHe3","R+");
	histAyHe->Fit("fitAyHe1","R+");
	Double_t fitAyHe1const = fitAyHe1->GetParameter(0);
	Double_t fitAyHe1expconst = fitAyHe1->GetParameter(1);
	Double_t fitAyHe1consterror = fitAyHe1->GetParError(0);
	Double_t fitAyHe1expconsterror = fitAyHe1->GetParError(1);
	Double_t fitAyHe2const = fitAyHe2->GetParameter(0);
	Double_t fitAyHe2expconst = fitAyHe2->GetParameter(1);
	Double_t fitAyHe2consterror = fitAyHe2->GetParError(0);
	Double_t fitAyHe2expconsterror = fitAyHe2->GetParError(1);
	Double_t fitAyHe3const = fitAyHe3->GetParameter(0);
	Double_t fitAyHe3expconst = fitAyHe3->GetParameter(1);
	Double_t fitAyHe3consterror = fitAyHe3->GetParError(0);
	Double_t fitAyHe3expconsterror = fitAyHe3->GetParError(1);
	outFile << "AyHe1 range: 1.46-1.60		AyHe2 range: 1.60-1.80		AyHe3 range: 1.35-1.45" << endl;
	outFile << "AyHe1:" << fitAyHe1const << " | AyHe1 error: " << fitAyHe1consterror << " | Log AyHe1: " << fitAyHe1expconst << " | Log AyHe1 error: " << fitAyHe1expconsterror << endl;
	outFile << "AyHe2:" << fitAyHe2const << " | AyHe2 error: " << fitAyHe2consterror << " | Log AyHe2: " << fitAyHe2expconst << " | Log AyHe2 error: " << fitAyHe2expconsterror << endl;
	outFile << "AyHe3:" << fitAyHe3const << " | AyHe3 error: " << fitAyHe3consterror << " | Log AyHe3: " << fitAyHe3expconst << " | Log AyHe3 error: " << fitAyHe3expconsterror << endl << endl << endl;
*/	xbjpad03->Update();


	xbjpad04->cd();
	xbjpad04->SetLogy();
	cout << "Drawing " << titleAyHe << " in log scale..." << endl;
	TH1F *loghistAyHe = new TH1F("loghistAyHe",titleAyHe,bins,xmin,xmax);
	loghistAyHe->Sumw2();
	chainAyHe->Draw("PriKineR.x_bj>>loghistAyHe", cuts, "E");
	loghistAyHe->Scale(1/AyHeChargeScale);
	loghistAyHe->Draw();
/*	TF1 *fitAyHe1 = new TF1("fitAyHe1","[0]*exp(-x*[1])",1.45,1.6);
	fitAyHe1->SetParNames("AyHe Red p1", "AyHe Red p2");
	fitAyHe1->SetLineColor(kRed);
	TF1 *fitAyHe2 = new TF1("fitAyHe2","[0]*exp(-x*[1])",1.6,1.8);
	fitAyHe2->SetParNames("AyHe Blue p1","AyHe Blue p2");
	fitAyHe2->SetLineColor(kBlue);
	TF1 *fitAyHe3 = new TF1("fitAyHe3","[0]*exp(-x*[1])",1.35,1.45);
	fitAyHe3->SetParNames("AyHe Green p1","AyHe Green p2");
	fitAyHe3->SetLineColor(kGreen);
	loghistAyHe->Fit("fitAyHe1","R+");
	loghistAyHe->Fit("fitAyHe3","R+");
	loghistAyHe->Fit("fitAyHe2","R+");
	Double_t fitAyHe1const = fitAyHe1->GetParameter(0);
	Double_t fitAyHe1expconst = fitAyHe1->GetParameter(1);
	Double_t fitAyHe1consterror = fitAyHe1->GetParError(0);
	Double_t fitAyHe1expconsterror = fitAyHe1->GetParError(1);
	Double_t fitAyHe2const = fitAyHe2->GetParameter(0);
	Double_t fitAyHe2expconst = fitAyHe2->GetParameter(1);
	Double_t fitAyHe2consterror = fitAyHe2->GetParError(0);
	Double_t fitAyHe2expconsterror = fitAyHe2->GetParError(1);
	Double_t fitAyHe3const = fitAyHe3->GetParameter(0);
	Double_t fitAyHe3expconst = fitAyHe3->GetParameter(1);
	Double_t fitAyHe3consterror = fitAyHe3->GetParError(0);
	Double_t fitAyHe3expconsterror = fitAyHe3->GetParError(1);
	outFile << "Log AyHe1 range: 1.46-1.60		Log AyHe2 range: 1.60-1.80		Log AyHe3 range: 1.35-1.45" << endl;
	outFile << "AyHe1:" << fitAyHe1const << " | AyHe1 error: " << fitAyHe1consterror << " | Log AyHe1: " << fitAyHe1expconst << " | Log AyHe1 error: " << fitAyHe1expconsterror << endl;
	outFile << "AyHe2:" << fitAyHe2const << " | AyHe2 error: " << fitAyHe2consterror << " | Log AyHe2: " << fitAyHe2expconst << " | Log AyHe2 error: " << fitAyHe2expconsterror << endl;
	outFile << "AyHe3:" << fitAyHe3const << " | AyHe3 error: " << fitAyHe3consterror << " | Log AyHe3: " << fitAyHe3expconst << " | Log AyHe3 error: " << fitAyHe3expconsterror << endl << endl << endl;
*/	xbjpad04->Update();


	xbjpad05->cd();
	TString titleCoverAyHe = "12C/3AyHe for Q2 of ";
	titleCoverAyHe += Q2;
	cout << "Drawing " << titleCoverAyHe << "..." << endl;
	TH1F *histCoverAyHe = new TH1F("histCoverAyHe",titleCoverAyHe,bins,xmin,xmax);
	histCoverAyHe->Sumw2();
//	histCoverAyHe->Divide(histC,histAyHe,1,0.0918143);
	histCoverAyHe->Divide(histC,histAyHe);
	histCoverAyHe->Draw("E");
	xbjpad05->Update();

	xbjpad06->cd();
	xbjpad06->SetLogy();
	cout << "Drawing " << titleCoverAyHe << " in log scale..." << endl;
	TH1F *loghistCoverAyHe = new TH1F("loghistCoverAyHe",titleCoverAyHe,bins,xmin,xmax);
	loghistCoverAyHe->Sumw2();
//	histCoverAyHe->Divide(histC,histAyHe,1,0.0918143);
	loghistCoverAyHe->Divide(loghistC,loghistAyHe);
	loghistCoverAyHe->Draw("E");
	xbjpad06->Update();

   
/*	TString imagename = "output_files/";
	imagename += title;
	imagename += "_cuts_1.png";
	cuts1Canvas->Print(imagename);
	TString imagename = "output_files/";
	imagename += title;
	imagename += "_cuts_2.png";
	cuts2Canvas->Print(imagename);
*/	TString imagename = "output_files/";
	imagename += title;
	imagename += ".png";
	xbjCanvas->Print(imagename);
	
	outFile.close();

	cout << "All done!" << endl;


}
