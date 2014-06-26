#include "hand_scaling_factors.h"

void nitrogen_tail_matching_vert_01()
{

//	bool zoomed = false;
	bool zoomed = true;

	int thisHeRunNumber = 20487;
//	int thisNitroRunNumber = 22294;
	TString filenameHe;
	TString filenameNitro;
	TChain* chainHe = new TChain("T");
	TChain* chainNitro = new TChain("T");
	int HeRunNumber = thisHeRunNumber;
	int endHeRunNumber = thisHeRunNumber;
	int NitroRunNumber = 20372;
	int endNitroRunNumber = 20410;

// **********************************************************************************************
// This bit of code should set the charge and livetime scaling factors
/*        double HeChargeScale = 0; double Helivetime = 0;
        double HeChargeScaleUp = 0; double HelivetimeUp = 0;
        double HeChargeScaleDown = 0; double HelivetimeDown = 0;
        hand_scaling_factors(HeRunNumber, endHeRunNumber, HeChargeScale, Helivetime, HeChargeScaleUp, HelivetimeUp, HeChargeScaleDown, HelivetimeDown);
*/
        double HeChargeScale; double Helivetime;
        double HeChargeScaleUp; double HelivetimeUp;
        double HeChargeScaleDown; double HelivetimeDown;
        double HeBeamChargeScaleUp; double HeBeamlivetimeUp;
        double HeBeamChargeScaleDown; double HeBeamlivetimeDown;
        hand_scaling_factors(HeRunNumber, endHeRunNumber, HeChargeScale, Helivetime, HeChargeScaleUp, HelivetimeUp, HeChargeScaleDown, HelivetimeDown, HeBeamChargeScaleUp, HeBeamlivetimeUp, HeBeamChargeScaleDown, HeBeamlivetimeDown);

        HeChargeScale = 0.00001 * int(HeChargeScale * 100000.0 + 0.5);
        HeChargeScaleUp = 0.00001 * int(HeChargeScaleUp * 100000.0 + 0.5);
        HeChargeScaleDown = 0.00001 * int(HeChargeScaleDown * 100000.0 + 0.5);
        Helivetime = 0.0001 * int(Helivetime * 10000.0 + 0.5);
        HelivetimeUp = 0.0001 * int(HelivetimeUp * 10000.0 + 0.5);
        HelivetimeDown = 0.0001 * int(HelivetimeDown * 10000.0 + 0.5);
        cout << "HeChargeScale: " << HeChargeScale << "C, Helivetime: " << Helivetime << endl;
        cout << "HeChargeScaleUp: " << HeChargeScaleUp << "C, HelivetimeUp: " << HelivetimeUp << endl;
        cout << "HeChargeScaleDown: " << HeChargeScaleDown << "C, HelivetimeDown: " << HelivetimeDown << endl;
// **********************************************************************************************

// **********************************************************************************************
// This bit of code should set the charge and livetime scaling factors
/*        double NitroChargeScale = 0; double Nitrolivetime = 0;
        double NitroChargeScaleUp = 0; double NitrolivetimeUp = 0;
        double NitroChargeScaleDown = 0; double NitrolivetimeDown = 0;
        hand_scaling_factors(NitroRunNumber, endNitroRunNumber, NitroChargeScale, Nitrolivetime, NitroChargeScaleUp, NitrolivetimeUp, NitroChargeScaleDown, NitrolivetimeDown);
*/
        double NitroChargeScale; double Nitrolivetime;
        double NitroChargeScaleUp; double NitrolivetimeUp;
        double NitroChargeScaleDown; double NitrolivetimeDown;
        double NitroBeamChargeScaleUp; double NitroBeamlivetimeUp;
        double NitroBeamChargeScaleDown; double NitroBeamlivetimeDown;
        hand_scaling_factors(NitroRunNumber, endNitroRunNumber, NitroChargeScale, Nitrolivetime, NitroChargeScaleUp, NitrolivetimeUp, NitroChargeScaleDown, NitrolivetimeDown, NitroBeamChargeScaleUp, NitroBeamlivetimeUp, NitroBeamChargeScaleDown, NitroBeamlivetimeDown);

        NitroChargeScale = 0.00001 * int(NitroChargeScale * 100000.0 + 0.5);
        NitroChargeScaleUp = 0.00001 * int(NitroChargeScaleUp * 100000.0 + 0.5);
        NitroChargeScaleDown = 0.00001 * int(NitroChargeScaleDown * 100000.0 + 0.5);
        Nitrolivetime = 0.0001 * int(Nitrolivetime * 10000.0 + 0.5);
        NitrolivetimeUp = 0.0001 * int(NitrolivetimeUp * 10000.0 + 0.5);
        NitrolivetimeDown = 0.0001 * int(NitrolivetimeDown * 10000.0 + 0.5);
        cout << "NitroChargeScale: " << NitroChargeScale << "C, Nitrolivetime: " << Nitrolivetime << endl;
        cout << "NitroChargeScaleUp: " << NitroChargeScaleUp << "C, NitrolivetimeUp: " << NitrolivetimeUp << endl;
        cout << "NitroChargeScaleDown: " << NitroChargeScaleDown << "C, NitrolivetimeDown: " << NitrolivetimeDown << endl;
// **********************************************************************************************



	// Adds runs to the chain
//	for (int t=0; t<1; t++)
	for (int t=0; t<1000; t++)
	{
//		filenameHe = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_R_";
		filenameHe = "/home/ellie/physics/e05-102/ellana/ROOTfiles/q2_01_vert/e05102_R_";
//		filenameHe = "/home/ellie/physics/e05-102/ellana/ROOTfiles/q2_04_transverse-1/e05102_R_";
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
	}


	// Adds runs to the chain
	for (int thisNitroRunNumber=NitroRunNumber; thisNitroRunNumber<(endNitroRunNumber+1); thisNitroRunNumber++)
	{
		for (int t=0; t<1000; t++)
		{
	//		filenameNitro = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_R_";
			filenameNitro = "/home/ellie/physics/e05-102/ellana/ROOTfiles/nitrogen_runs/e05102_R_";
			filenameNitro += thisNitroRunNumber;
			if (t != 0)
			{
				filenameNitro += "_";
				filenameNitro += t;
			}
			filenameNitro += ".root";
			ifstream ifileNitro(filenameNitro);
			if (ifileNitro)
			{
				cout << "Adding file to chainNitro: " << filenameNitro << endl;
				chainNitro->Add(filenameNitro);
			}
			else
			{
				cout << "File " << filenameNitro << " does not exist. Ending here." << endl;
				t=999999999;
			}
		}
	}

        TCanvas *c1 = new TCanvas("c1","Nitrogen Dilution",1360,768); //x,y
        pad1  =  new  TPad("pad1","pad1",0.0000,0.5000,0.2500,1.0000,0,0,0);
        pad2  =  new  TPad("pad2","pad2",0.0000,0.0000,0.2500,0.5000,0,0,0);
        pad3  =  new  TPad("pad3","pad3",0.2500,0.5000,0.5000,1.0000,0,0,0);
        pad4  =  new  TPad("pad4","pad4",0.2500,0.0000,0.5000,0.5000,0,0,0);
        pad5  =  new  TPad("pad5","pad5",0.5000,0.5000,0.7500,1.0000,0,0,0);
        pad6  =  new  TPad("pad6","pad6",0.5000,0.0000,0.7500,0.5000,0,0,0);
        pad7  =  new  TPad("pad7","pad6",0.7500,0.5000,1.0000,1.0000,0,0,0);
        pad8  =  new  TPad("pad8","pad6",0.7500,0.0000,1.0000,0.5000,0,0,0);
        pad1->Draw();pad2->Draw();pad3->Draw();pad4->Draw();pad5->Draw();pad6->Draw();pad7->Draw();pad8->Draw();

	pad1->cd();
	cout << "Drawing pad1" << endl;
	TH1F *hex = new TH1F("hex","hex",200,0,10);
	TH1F *nitrox = new TH1F("nitrox","nitrox",200,0,10);
	chainHe->Draw("PriKineR.x_bj>>hex","ReactPt_R.z>-0.15 && ReactPt_R.z<0.17");
//	chainHe->Draw("PriKineR.x_bj>>hex");
	chainNitro->Draw("PriKineR.x_bj>>nitrox","ReactPt_R.z>-0.15 && ReactPt_R.z<0.17");
//	chainNitro->Draw("PriKineR.x_bj>>nitrox");
	hex->Scale(1/(HeChargeScale*Helivetime));
	hex->SetTitle("C, LT Normalized xBj");
	hex->Draw();
	nitrox->Scale(1/(NitroChargeScale*Nitrolivetime));
	nitrox->SetLineColor(kBlue);
	nitrox->Draw("same");
//	nitrox->SetLogy();
	pad1->SetLogy();
	pad1->Update();

	pad7->cd();
	hex->Divide(nitrox);
	hex->SetTitle("3He/N2 xBj");
	hex->Draw();
	pad7->SetLogy();
	pad7->Update();

/*	pad5->cd();
	chainHe->Draw("PriKineR.x_bj>>hex");
	chainNitro->Draw("PriKineR.x_bj>>nitrox");
	hex->Scale(1/(HeChargeScale*Helivetime));
	nitrox->Scale(1/(NitroChargeScale*Nitrolivetime));

	nitrox->Divide(hex);
	nitrox->SetTitle("N2/3He xBj");
	nitrox->Draw();
	pad5->SetLogy();
	pad5->Update();
*/
	pad2->cd();
	cout << "Drawing pad1" << endl;
	TH1F *hexscaled = new TH1F("hexscaled","hexscaled",100,0,10);
	TH1F *nitroxscaled = new TH1F("nitroxscaled","nitroxscaled",100,0,10);
	chainHe->Draw("PriKineR.x_bj>>hexscaled","ReactPt_R.z>-0.15 && ReactPt_R.z<0.17");
//	chainHe->Draw("PriKineR.x_bj>>hexscaled");
	chainNitro->Draw("PriKineR.x_bj>>nitroxscaled","ReactPt_R.z>-0.15 && ReactPt_R.z<0.17");
//	chainNitro->Draw("PriKineR.x_bj>>nitroxscaled");
	hexscaled->Scale(1/(HeChargeScale*Helivetime));
	hexscaled->SetTitle("Scaled xBj");
	hexscaled->Draw();
	nitroxscaled->Scale((1/(NitroChargeScale*Nitrolivetime))*0.06);
//	nitroxscaled->Scale((1/(NitroChargeScale*Nitrolivetime)));
	nitroxscaled->SetLineColor(kBlue);
	nitroxscaled->Draw("same");
//	nitroxscaled->SetLogy();
	pad2->SetLogy();
	pad2->Update();

	pad3->cd();
	cout << "Drawing pad1" << endl;
	TH1F *hexscaled = new TH1F("hexscaled","hexscaled",100,0,10);
	TH1F *nitroxscaled = new TH1F("nitroxscaled","nitroxscaled",100,0,10);
	chainHe->Draw("PriKineR.x_bj>>hexscaled","ReactPt_R.z>-0.15 && ReactPt_R.z<0.17");
//	chainHe->Draw("PriKineR.x_bj>>hexscaled");
	chainNitro->Draw("PriKineR.x_bj>>nitroxscaled","ReactPt_R.z>-0.15 && ReactPt_R.z<0.17");
//	chainNitro->Draw("PriKineR.x_bj>>nitroxscaled");
	hexscaled->Scale(1/(HeChargeScale*Helivetime));
	nitroxscaled->Scale((1/(NitroChargeScale*Nitrolivetime))*0.06);
//	nitroxscaled->Scale((1/(NitroChargeScale*Nitrolivetime)));
	nitroxscaled->Divide(hexscaled);
	nitroxscaled->SetTitle("Scaled N2/3He xBj");
	nitroxscaled->Draw();
	pad3->SetLogy();
	pad3->Update();


	pad4->cd();
	cout << "Drawing pad1" << endl;
	TH1F *hexscaled = new TH1F("hexscaled","hexscaled",10,0,2);
	TH1F *nitroxscaled = new TH1F("nitroxscaled","nitroxscaled",10,0,2);
	chainHe->Draw("PriKineR.x_bj>>hexscaled","ReactPt_R.z>-0.15 && ReactPt_R.z<0.17");
//	chainHe->Draw("PriKineR.x_bj>>hexscaled");
	chainNitro->Draw("PriKineR.x_bj>>nitroxscaled","ReactPt_R.z>-0.15 && ReactPt_R.z<0.17");
//	chainNitro->Draw("PriKineR.x_bj>>nitroxscaled");
	hexscaled->Scale(1/(HeChargeScale*Helivetime));
	hexscaled->SetTitle("Scaled xBj");
	hexscaled->Draw();
	nitroxscaled->Scale((1/(NitroChargeScale*Nitrolivetime))*0.06);
//	nitroxscaled->Scale((1/(NitroChargeScale*Nitrolivetime)));
	nitroxscaled->SetLineColor(kBlue);
	nitroxscaled->Draw("same");
//	nitroxscaled->SetLogy();
	pad4->SetLogy();
	pad4->Update();


	pad8->cd();
//	TH1F *rawratio = new TH1F("rawratio","rawratio",10,0,2);
//	rawratio = hexscaled->Divide(nitroxscaled);
//	rawratio->Draw();

	hexscaled->Divide(nitroxscaled);
	hexscaled->SetTitle("Scaled 3He/N2 xBj");
	hexscaled->Draw();
	pad8->SetLogy();
	pad8->Update();
	
	pad5->cd();
	chainHe->Draw("PriKineR.x_bj>>hexscaled","ReactPt_R.z>-0.15 && ReactPt_R.z<0.17");
//	chainHe->Draw("PriKineR.x_bj>>hexscaled");
	chainNitro->Draw("PriKineR.x_bj>>nitroxscaled","ReactPt_R.z>-0.15 && ReactPt_R.z<0.17");
//	chainNitro->Draw("PriKineR.x_bj>>nitroxscaled");
	hexscaled->Scale(1/(HeChargeScale*Helivetime));
	nitroxscaled->Scale((1/(NitroChargeScale*Nitrolivetime))*0.06);
//	nitroxscaled->Scale((1/(NitroChargeScale*Nitrolivetime)));

	nitroxscaled->Divide(hexscaled);
	nitroxscaled->SetTitle("Scaled N2/3He xBj");
	nitroxscaled->Draw();
	pad5->SetLogy();
	pad5->Update();

	pad6->cd();
	TH1F *const1 = new TH1F("conts1","const1",10,0,2);
	for (i=0; i<10; i++)
	{
		const1->Fill(i*0.2);
	}
	const1->Draw();
	nitroxscaled->Scale(-1);
	nitroxscaled->Add(const1);
	nitroxscaled->SetTitle("Dilution Factor");
//	nitroxscaled->SetMinimum(0);
	nitroxscaled->Draw();
	pad6->Update();
	cout << "All done!" << endl;

}
