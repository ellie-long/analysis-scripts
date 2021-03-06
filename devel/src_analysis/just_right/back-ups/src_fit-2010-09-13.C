// This was a program to chain together different
// root files and look at graphs from them.
// In particular, it will output plots of x=Q2/(2m*nu)
// of 3He and 12C and of 12C/3He to look for short
// range correlation in E05-102 and E08-005.
//
// Elena Long (ellie@jlab.org)



void src_fit(){

  int CRunNumber=20591;
  int endCRunNumber=22461;
  int HeRunNumber=20596;
  int endHeRunNumber=20598;
//  int endHeRunNumber=22488;

  TString Q2 = "1.0";
  TString vartodraw = "PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315)";
//Range is of the form (bins, start, end)
//  TString range = "(800,0.5,4.0)";
  double bins = 50;
  double plotmin = 0.5;
  double plotmax = 2.0;
  TString title = "12C/3He x with Target cut, Run # ";
  title += CRunNumber;
  title += " & ";
  title += HeRunNumber;

	TCut cut = "";  
	TCut kinematics = "PriKineR.Q2<10 && GoodElectron==1 && PriKineR.nu<10";
//	TCut eventtype = "D.evtypebits&(1<<1)>0";
	TCut eventtype = "(D.evtypebits&2)==2";
	TCut gold = "R.gold.dp>-0.04 && R.gold.dp<0.055";
	TCut target = "ReactPt_R.z>-0.172 && ReactPt_R.z<0.175";
	TCut sieve = "abs(R_sv_y)<0.03 && abs(R_sv_x)<0.06";

//	TCut cut = "";
//	TCut eventtype = "";
//	TCut target = "";
//	TCut sieve = "";
//	TCut gold = "";

  TCut cuts = kinematics && target && sieve && gold && eventtype;

  TString whattodraw = vartodraw;
//  whattodraw += ">>";
//  whattodraw += title;
//  whattodraw += range;
  TString whattodrawC = whattodraw;
  whattodrawC += ">>histC";
  TString whattodrawHe = whattodraw;
  whattodrawHe += ">>histHe";
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
 		if(thisCRunNumber==20592){thisCRunNumber=20731;}
		if(thisCRunNumber==20735){thisCRunNumber=20762;}
		if(thisCRunNumber==20765){thisCRunNumber=22380;}
		if(thisCRunNumber==22381){thisCRunNumber=22389;}
		if(thisCRunNumber==22390){thisCRunNumber=22425;}
		if(thisCRunNumber==22427){thisCRunNumber=22461;}
		if(thisCRunNumber==22462){thisCRunNumber=99999;}

   for (int t=0; t<1000;t++)
    {
      filenameC = "/home/ellie/physics/e05-102/terabyte/ROOTfiles/e05102_R_";
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
	if(thisHeRunNumber==20591){thisHeRunNumber=20596;}

   if(thisHeRunNumber==22397){thisHeRunNumber=22398;}
    for (int t=0; t<1000;t++)
    {
      filenameHe = "/home/ellie/physics/e05-102/terabyte/ROOTfiles/e05102_R_";
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


	
	gStyle->SetPalette(1);
	gStyle->SetOptFit(0001);

	// Defines Canvas
	TCanvas *c1 = new TCanvas("c1","x of 12C and 3He",1360,800);//x,y
	pad01 = new TPad("pad01","pad01",0.0000,0.8333,0.2000,1.0000,0,0,0);
	pad02 = new TPad("pad02","pad02",0.2000,0.8333,0.4000,1.0000,0,0,0);
	pad03 = new TPad("pad03","pad03",0.4000,0.8333,0.6000,1.0000,0,0,0);
	pad04 = new TPad("pad04","pad04",0.6000,0.8333,0.8000,1.0000,0,0,0);
	pad05 = new TPad("pad05","pad05",0.0000,0.6666,0.2000,0.8333,0,0,0);
	pad06 = new TPad("pad06","pad06",0.2000,0.6666,0.4000,0.8333,0,0,0);
	pad07 = new TPad("pad07","pad07",0.4000,0.6666,0.6000,0.8333,0,0,0);
	pad08 = new TPad("pad08","pad08",0.6000,0.6666,0.8000,0.8333,0,0,0);
	pad09 = new TPad("pad09","pad09",0.0000,0.3333,0.3333,0.6666,0,0,0);
	pad10 = new TPad("pad10","pad10",0.3333,0.3333,0.6666,0.6666,0,0,0);
	pad11 = new TPad("pad11","pad11",0.6666,0.3333,1.0000,0.6666,0,0,0);
	pad12 = new TPad("pad12","pad12",0.0000,0.0000,0.3333,0.3333,0,0,0);
	pad13 = new TPad("pad13","pad13",0.3333,0.0000,0.6666,0.3333,0,0,0);
	pad14 = new TPad("pad14","pad14",0.6666,0.0000,1.0000,0.3333,0,0,0);
	pad15 = new TPad("pad15","pad15",0.8000,0.8333,1.0000,1.0000,0,0,0);
	pad16 = new TPad("pad16","pad16",0.8000,0.6666,1.0000,0.8333,0,0,0);
	pad01->Draw();pad02->Draw();pad03->Draw();pad04->Draw();pad05->Draw();pad06->Draw();pad07->Draw();pad08->Draw();pad09->Draw();pad10->Draw();pad11->Draw();pad12->Draw();pad13->Draw();pad14->Draw();pad15->Draw();pad16->Draw();

	// Everything below here makes graphs for each section of the canvas

	pad01->cd();
	TString titledpHe = "dp Cut from 3He Runs";
	cout << "Drawing " << titledpHe << "..." << endl;
	chainHe->Draw("R.gold.dp>>HedpNoCut(400,-0.08,0.08)", "", "");
	chainHe->Draw("R.gold.dp>>HedpCut(400,-0.08,0.08)", gold, "");
	HedpNoCut->SetTitle(titledpHe);
	HedpNoCut->Draw();
	HedpCut->SetLineColor(kBlack);
	HedpCut->SetFillColor(kViolet);
	HedpCut->Draw("same");

	pad05->cd();
	TString titledpC = "dp Cut from 12C Runs";
	cout << "Drawing " << titledpC << "..." << endl;
	chainC->Draw("R.gold.dp>>CdpNoCut(400,-0.08,0.08)", "", "");
	chainC->Draw("R.gold.dp>>CdpCut(400,-0.08,0.08)", gold, "");
	CdpNoCut->SetTitle(titledpC);
	CdpNoCut->Draw();
	CdpCut->SetLineColor(kBlack);
	CdpCut->SetFillColor(kViolet);
	CdpCut->Draw("same");

	pad02->cd();
	TString titleTargetHe = "Target Cut for 3He Runs";
	cout << "Drawing " << titleTargetHe << "..." << endl;
	chainHe->Draw("ReactPt_R.z>>HeReactZNoCut(400,-0.3,0.3)", "", "");
	chainHe->Draw("ReactPt_R.z>>HeReactZCut(400,-0.3,0.3)", target, "");
	HeReactZNoCut->SetTitle(titleTargetHe);
	HeReactZNoCut->Draw();
	HeReactZCut->SetLineColor(kBlack);
	HeReactZCut->SetFillColor(kViolet);
	HeReactZCut->Draw("same");

	pad06->cd();
	TString titleTargetC = "Target Cut for 12C Runs";
	cout << "Drawing " << titleTargetC << "..." << endl;
	chainC->Draw("ReactPt_R.z>>CReactZNoCut(400,-0.3,0.3)", "", "");
	chainC->Draw("ReactPt_R.z>>CReactZCut(400,-0.3,0.3)", target, "");
	CReactZNoCut->SetTitle(titleTargetC);
	CReactZNoCut->Draw();
	CReactZCut->SetLineColor(kBlack);
	CReactZCut->SetFillColor(kViolet);
	CReactZCut->Draw("same");

	pad03->cd();
	TString titleThetaPhiHe = "Theta and Phi, No Cut, for 3He";
	cout << "Drawing " << titleThetaPhiHe << "..." << endl;
	chainHe->Draw("R_sv_x:R_sv_y>>HeSieveNoCut(100,-0.05,0.05,100,-0.1,0.1)", target, "");
	HeSieveNoCut->SetTitle(titleThetaPhiHe);
	HeSieveNoCut->SetStats(kFALSE);
	HeSieveNoCut->Draw("COLZ");

	pad07->cd();
	TString titleThetaPhiC = "Theta and Phi, No Cut, for 12C";
	cout << "Drawing " << titleThetaPhiC << "..." << endl;
	chainC->Draw("R_sv_x:R_sv_y>>CSieveNoCut(100,-0.05,0.05,100,-0.1,0.1)", target, "");
	CSieveNoCut->SetTitle(titleThetaPhiC);
	CSieveNoCut->SetStats(kFALSE);
	CSieveNoCut->Draw("COLZ");

	pad04->cd();
	TString titleThetaCutHe = "Theta and Phi Cut for 3He";
	cout << "Drawing " << titleThetaCutHe << "..." << endl;
	chainHe->Draw("R_sv_x:R_sv_y>>HeSieveCut(100,-0.05,0.05,100,-0.1,0.1)", target && sieve, "");
	HeSieveCut->SetTitle(titleThetaCutHe);
	HeSieveCut->SetStats(kFALSE);
	HeSieveCut->Draw("COLZ");

	pad08->cd();
	TString titleThetaCutC = "Theta and Phi Cut for 12C";
	cout << "Drawing " << titleThetaCutC << "..." << endl;
	chainC->Draw("R_sv_x:R_sv_y>>CSieveCut(100,-0.05,0.05,100,-0.1,0.1)", target && sieve, "");
	CSieveCut->SetTitle(titleThetaCutC);
	CSieveCut->SetStats(kFALSE);
	CSieveCut->Draw("COLZ");

	pad15->cd();
	TString titleQ2WHe = "Q2 v. Nu for 3He";
	cout << "Drawing " << titleQ2WHe << "..." << endl;
	chainHe->Draw("PriKineR.Q2:PriKineR.nu>>Q2WHe(100,0.3,0.8,400,0,1.6)", cuts, "");
	Q2WHe->SetTitle(titleQ2WHe);
	Q2WHe->SetStats(kFALSE);
	Q2WHe->Draw("COLZ");

	pad16->cd();
	TString titleQ2WC = "Q2 v. Nu for 12C";
	cout << "Drawing " << titleQ2WC << "..." << endl;
	chainC->Draw("PriKineR.Q2:PriKineR.nu>>Q2WC(100,0.3,0.8,400,0,1.6,100)", cuts, "");
	Q2WC->SetTitle(titleQ2WC);
	Q2WC->SetStats(kFALSE);
	Q2WC->Draw("COLZ");


	pad09->cd();
	TString titleC = "x for 12C at Q2 of ";
	titleC += Q2;
//	titleC += " and Target Cut of ";
//	titleC += target;
	cout << "Drawing " << titleC << "..." << endl;
	TH1F *histC = new TH1F("histC",titleC,bins,plotmin,plotmax);
	histC->Sumw2();
	chainC->Draw(whattodrawC, cuts, "E");
	histC->Scale(1/0.0161297);
	histC->Draw();
	TF1 *fitC1 = new TF1("fitC1","[0]*exp(-x*[1])",1.45,1.6);
	fitC1->SetParNames("C Red p1","C Red p2");
	Double_t fitC1const = fitC1->GetParameter(0);
	Double_t fitC1expconst = fitC1->GetParameter(1);
//	Double_t fitC1exp = fitC1->GetParameter(2);
	Double_t fitC1consterror = fitC1->GetParError(0);
	Double_t fitC1expconsterror = fitC1->GetParError(1);
//	Double_t fitC1experror = fitC1->GetParError(2);
	fitC1->SetLineColor(kRed);
	TF1 *fit2 = new TF1("fitC2","[0]*exp(-x*[1])",1.6,1.8);
	fitC2->SetParNames("C Blue p1","C Blue p2");
	Double_t fitC2const = fitC2->GetParameter(0);
	Double_t fitC2expconst = fitC2->GetParameter(1);
//	Double_t fitC2exp = fitC2->GetParameter(2);
	Double_t fitC2consterror = fitC2->GetParError(0);
	Double_t fitC2expconsterror = fitC2->GetParError(1);
//	Double_t fitC2experror = fitC2->GetParError(2);
	fitC2->SetLineColor(kBlue);
	TF1 *fitC3 = new TF1("fitC3","[0]*exp(-x*[1])",1.35,1.45);
	fitC3->SetParNames("C Green p1","C Green p2");
	Double_t fitC3const = fitC3->GetParameter(0);
	Double_t fitC3expconst = fitC3->GetParameter(1);
//	Double_t fitC3exp = fitC3->GetParameter(2);
	Double_t fitC3consterror = fitC3->GetParError(0);
	Double_t fitC3expconsterror = fitC3->GetParError(1);
//	Double_t fitC3experror = fitC3->GetParError(2);
	fitC3->SetLineColor(kGreen);

	histC->Fit("fitC2","R");
	histC->Fit("fitC3","R+");
	histC->Fit("fitC1","R+");
	

	pad12->cd();
	pad12->SetLogy();
	cout << "Drawing " << titleC << " in log scale..." << endl;
	TH1F *histC = new TH1F("histC",titleC,bins,plotmin,plotmax);
	histC->Sumw2();
	chainC->Draw(whattodrawC, cuts, "E");
	histC->Draw();
	histC->Fit("fitC1","R");
	histC->Fit("fitC3","R+");
	histC->Fit("fitC2","R+");

	pad10->cd();
	TString titleHe = "x for 3He at Q2 of ";
	titleHe += Q2;
//	titleHe += " and Target Cut of ";
//	titleHe += target;
	cout << "Drawing " << titleHe << "..." << endl;
	TH1F *histHe = new TH1F("histHe",titleHe,bins,plotmin,plotmax);
	histHe->Sumw2();
	chainHe->Draw(whattodrawHe, cuts, "E");
	histHe->Scale(1/3.69904);
	histHe->Draw();
	TF1 *fitHe1 = new TF1("fitHe1","[0]*exp(-x*[1])",1.45,1.6);
	fitHe1->SetParNames("He Red p1", "He Red p2");
	Double_t fitHe1const = fitHe1->GetParameter(0);
	Double_t fitHe1expconst = fitHe1->GetParameter(1);
//	Double_t fitHe1exp = fitHe1->GetParameter(2);
	Double_t fitHe1consterror = fitHe1->GetParError(0);
	Double_t fitHe1expconsterror = fitHe1->GetParError(1);
//	Double_t fitHe1experror = fitHe1->GetParError(2);
	fitHe1->SetLineColor(kRed);
	TF1 *fitHe2 = new TF1("fitHe2","[0]*exp(-x*[1])",1.6,1.8);
	fitHe2->SetParNames("He Blue p1","He Blue p2");
	Double_t fitHe2const = fitHe2->GetParameter(0);
	Double_t fitHe2expconst = fitHe2->GetParameter(1);
//	Double_t fitHe2exp = fitHe2->GetParameter(2);
	Double_t fitHe2consterror = fitHe2->GetParError(0);
	Double_t fitHe2expconsterror = fitHe2->GetParError(1);
//	Double_t fitHe2experror = fitHe2->GetParError(2);
	fitHe2->SetLineColor(kBlue);
	TF1 *fitHe3 = new TF1("fitHe3","[0]*exp(-x*[1])",1.35,1.45);
	fitHe3->SetParNames("He Green p1","He Green p2");
	Double_t fitHe3const = fitHe3->GetParameter(0);
	Double_t fitHe3expconst = fitHe3->GetParameter(1);
//	Double_t fitHe3exp = fitHe3->GetParameter(2);
	Double_t fitHe3consterror = fitHe3->GetParError(0);
	Double_t fitHe3expconsterror = fitHe3->GetParError(1);
//	Double_t fitHe3experror = fitHe3->GetParError(2);
	fitHe3->SetLineColor(kGreen);

	histHe->Fit("fitHe2","R+");
	histHe->Fit("fitHe3","R+");
	histHe->Fit("fitHe1","R+");
	
	pad13->cd();
	pad13->SetLogy();
	cout << "Drawing " << titleHe << " in log scale..." << endl;
	TH1F *histHe = new TH1F("histHe",titleHe,bins,plotmin,plotmax);
	histHe->Sumw2();
	chainHe->Draw(whattodrawHe, cuts, "E");
	histHe->Draw();
	histHe->Fit("fitHe1","R+");
	histHe->Fit("fitHe3","R+");
	histHe->Fit("fitHe2","R+");

	pad11->cd();
	TString titleCoverHe = "12C/3He for Q2 of ";
	titleCoverHe += Q2;
//	titleCoverHe += " and Target Cut of ";
//	titleCoverHe += target;
	cout << "Drawing " << titleCoverHe << "..." << endl;
	TH1F *histCoverHe = new TH1F("histCoverHe",titleCoverHe,bins,plotmin,plotmax);
	histCoverHe->Sumw2();
	histCoverHe->Divide(histC,histHe,1,0.0918143);
	histCoverHe->Draw("E");

	pad14->cd();
	pad14->SetLogy();
	cout << "Drawing " << titleCoverHe << " in log scale..." << endl;
	TH1F *histCoverHe = new TH1F("histCoverHe",titleCoverHe,bins,plotmin,plotmax);
	histCoverHe->Sumw2();
	histCoverHe->Divide(histC,histHe,1,0.0918143);
	histCoverHe->Draw("E");

   
	TString imagename = "xbj_scaling_plots/xbj_scaling_plots_all_at_Q2_of_";
	imagename += Q2;
	imagename += ".png";
	c1->Print(imagename);

	cout << "All done!" << endl;


}
