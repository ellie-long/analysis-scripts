// This was a program to chain together different
// root files and look at graphs from them.
// In particular, it will output plots of x=Q2/(2m*nu)
// of 3He and 12C and of 12C/3He to look for short
// range correlation in E05-102 and E08-005.
//
// This one is updated (04/10) to work with both left and right
// HRS runs.
//
// Elena Long (ellie@jlab.org)



void v_src_fit(){

/*  int CRunNumberR=20602;
  int endCRunNumberR=20603;
  int HeRunNumberR=999999;
  int endHeRunNumberR=999999;
*/
  int CRunNumberR=20591;
  int endCRunNumberR=22462;
  int CRunNumberL=1699;
  int endCRunNumberL=1829;
  int HeRunNumberR=20579;
  int endHeRunNumberR=20790;
  int HeRunNumberL=1686;
  int endHeRunNumberL=1883;
// NOTE: There is a problem with the BCM values. When fixed, swap below and above lines.
//  int endHeRunNumberR=20879;
//  int endHeRunNumberL=1958;

  TString Q2 = "1.0";
  double bins = 50;
  double plotmin = 0.5;
  double plotmax = 2.0;
  TString title = "12C/3He x with Target cut, Run # ";
  title += CRunNumberR;
  title += " & ";
  title += HeRunNumberR;

	// Defines Right Arm Cuts
	TCut cutR = "";  
	TCut kinematicsR = "PriKineR.Q2<10 && GoodElectron==1 && PriKineR.nu<10";
//	TCut eventtypeR = "D.evtypebits&(1<<1)>0";
	TCut eventtypeR = "(D.evtypebits&2)==2";
	TCut goldR = "ExTgtCor_R.dp>-0.04 && ExTgtCor_R.dp<0.058";
	TCut targetR = "ReactPt_R.z>-0.155 && ReactPt_R.z<0.175";
	TCut sieveR = "abs(ExTgtCor_R.ph)<0.03 && abs(ExTgtCor_R.th)<0.06";

	TCut cutsR = kinematicsR && targetR && sieveR && goldR && eventtypeR;


	// Defines Left Arm Cuts
	TCut cutL = "";  
	TCut kinematicsL = "PriKineL.Q2<10 && GoodElectron==1 && PriKineL.nu<10";
//	TCut eventtypeL = "D.evtypebits&(1<<1)>0";
//	TCut eventtypeL = "(D.evtypebits&2)==2";
	TCut eventtypeL = "";
	TCut goldL = "ExTgtCor_L.dp>-0.04 && ExTgtCor_L.dp<0.058";
	TCut targetL = "ReactPt_L.z>-0.155 && ReactPt_L.z<0.175";
	TCut sieveL = "abs(ExTgtCor_L.ph)<0.03 && abs(ExTgtCor_L.th)<0.06";

	TCut cutsL = kinematicsL && targetL && sieveL && goldL && eventtypeL;



  // Makes right and left chains that will contain all the data
  TChain* chainCR = new TChain("T");
  TChain* chainHeR = new TChain("T");
  TChain* chainCL = new TChain("T");
  TChain* chainHeL = new TChain("T");

  gStyle->SetErrorX(.25);
  gStyle->SetEndErrorSize(.25);
  ifstream inp;
  ofstream out;

  TString filenameCR;
  TString filenameHeR;
  TString filenameCL;
  TString filenameHeL;



// Below is the loop for adding chains for the Right Carbon runs
  for (int thisCRunNumberR=CRunNumberR; thisCRunNumberR<(endCRunNumberR+1); thisCRunNumberR++)
  {
 		if(thisCRunNumberR==20592){thisCRunNumberR=20731;}
		if(thisCRunNumberR==20735){thisCRunNumberR=22380;}
		if(thisCRunNumberR==22381){thisCRunNumberR=22389;}
		if(thisCRunNumberR==22390){thisCRunNumberR=22425;}
		if(thisCRunNumberR==22427){thisCRunNumberR=22461;}
		if(thisCRunNumberR==22462){thisCRunNumberR=99999;}

   for (int t=0; t<1000;t++)
    {
      filenameCR = "/home/ellie/physics/e05-102/terabyte/ROOTfiles/e05102_R_";
      filenameCR += thisCRunNumberR;
      if (t!=0)
      {
        filenameCR += "_";
        filenameCR += t;
      }
      filenameCR += ".root";
      ifstream ifileCR(filenameCR);
      if (ifileCR)
      {
        cout << "Adding file to chainCR: " << filenameCR << endl;
        chainCR->Add(filenameCR);
      }
      else
      {
        cout << "File " << filenameCR << " does not exist. Ending here." << endl;
        t=9999999;
      }

    }
	
// Uncommenting the line below will let the code only go through one run (Good for debugging purposes)
//	thisCRunNumberR = 99999999;

  }

// Below is the loop for adding chains for the Left Carbon runs
  for (int thisCRunNumberL=CRunNumberL; thisCRunNumberL<(endCRunNumberL+1); thisCRunNumberL++)
  {
 		if(thisCRunNumberL==1700){thisCRunNumberL=1825;}
		if(thisCRunNumberL==1829){thisCRunNumberL=9999;}

   for (int t=0; t<1000;t++)
    {
      filenameCL = "/home/ellie/physics/e05-102/terabyte/ROOTfiles/e05102_L_";
      filenameCL += thisCRunNumberL;
      if (t!=0)
      {
        filenameCL += "_";
        filenameCL += t;
      }
      filenameCL += ".root";
      ifstream ifileCL(filenameCL);
      if (ifileCL)
      {
        cout << "Adding file to chainCL: " << filenameCL << endl;
        chainCL->Add(filenameCL);
      }
      else
      {
        cout << "File " << filenameCL << " does not exist. Ending here." << endl;
        t=9999999;
      }

    }
	
// Uncommenting the line below will let the code only go through one run (Good for debugging purposes)
//	thisCRunNumberL = 99999999;

  }





// Below is the loop for adding chains for the Right 3He runs

  for (int thisHeRunNumberR=HeRunNumberR;thisHeRunNumberR<(endHeRunNumberR+1); thisHeRunNumberR++)
  {
	// Skipping Vertical Carbon Runs
	if(thisHeRunNumberR==20591){thisHeRunNumberR=20596;}
	if(thisHeRunNumberR==20731){thisHeRunNumberR=20738;}
	if(thisHeRunNumberR==20732){thisHeRunNumberR=20738;}
	if(thisHeRunNumberR==20733){thisHeRunNumberR=20738;}
	if(thisHeRunNumberR==20734){thisHeRunNumberR=20738;}
	if(thisHeRunNumberR==20736){thisHeRunNumberR=20738;}
	if(thisHeRunNumberR==20737){thisHeRunNumberR=20738;}
	if(thisHeRunNumberR==20791){thisHeRunNumberR=20814;}
	if(thisHeRunNumberR==20792){thisHeRunNumberR=20814;}

	// Skipping Longitudinal Carbon Runs
	if(thisHeRunNumberR==22380){thisHeRunNumberR=22393;}
	if(thisHeRunNumberR==22389){thisHeRunNumberR=22393;}
	if(thisHeRunNumberR==22425){thisHeRunNumberR=22436;}
	if(thisHeRunNumberR==22426){thisHeRunNumberR=22436;}

	// Skipping Transverse Carbon Runs
	if(thisHeRunNumberR==22461){thisHeRunNumberR=22465;}

    for (int t=0; t<1000;t++)
    {
      filenameHeR = "/home/ellie/physics/e05-102/terabyte/ROOTfiles/e05102_R_";
      filenameHeR += thisHeRunNumberR;
      if (t!=0)
      {
        filenameHeR += "_";
        filenameHeR += t;
      }
      filenameHeR += ".root";
      ifstream ifileHeR(filenameHeR);
      if (ifileHeR)
      {
        cout << "Adding file to chainHeR: " << filenameHeR << endl;
        chainHeR->Add(filenameHeR);
      }
      else
      {
        cout << "File " << filenameHeR << " does not exist. Ending here." << endl;
        t=9999999;
      }

    }

// Uncommenting the line below will let the code only go through one run (Good for debugging purposes)
//	thisHeRunNumberR = 999999999;

  }

// Below is the loop for adding chains for the Left 3He runs

  for (int thisHeRunNumberL=HeRunNumberL;thisHeRunNumberL<(endHeRunNumberL+1); thisHeRunNumberL++)
  {
	// Skipping Vertical Carbon Runs
	if(thisHeRunNumberL==1699){thisHeRunNumberL=1704;}
	if(thisHeRunNumberL==1825){thisHeRunNumberL=1832;}
	if(thisHeRunNumberL==1826){thisHeRunNumberL=1832;}
	if(thisHeRunNumberL==1827){thisHeRunNumberL=1832;}
	if(thisHeRunNumberL==1828){thisHeRunNumberL=1832;}
	if(thisHeRunNumberL==1830){thisHeRunNumberL=1832;}
	if(thisHeRunNumberL==1831){thisHeRunNumberL=1832;}
	if(thisHeRunNumberL==1884){thisHeRunNumberL=1906;}
	if(thisHeRunNumberL==1885){thisHeRunNumberL=1906;}

    for (int t=0; t<1000;t++)
    {
      filenameHeL = "/home/ellie/physics/e05-102/terabyte/ROOTfiles/e05102_L_";
      filenameHeL += thisHeRunNumberL;
      if (t!=0)
      {
        filenameHeL += "_";
        filenameHeL += t;
      }
      filenameHeL += ".root";
      ifstream ifileHeL(filenameHeL);
      if (ifileHeL)
      {
        cout << "Adding file to chainHeL: " << filenameHeL << endl;
        chainHeL->Add(filenameHeL);
      }
      else
      {
        cout << "File " << filenameHeL << " does not exist. Ending here." << endl;
        t=9999999;
      }

    }

// Uncommenting the line below will let the code only go through one run (Good for debugging purposes)
//	thisHeRunNumberL = 999999999;

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
	TH1F *HedpNoCut = new TH1F("HedpNoCut",titledpHe,400,-0.08,0.08);
	TH1F *HedpCut = new TH1F("HedpCut",titledpHe,400,-0.08,0.08);
	chainHeR->Draw("ExTgtCor_R.dp>>HedpNoCutR(400,-0.08,0.08)", "", "");
	chainHeR->Draw("ExTgtCor_R.dp>>HedpCutR(400,-0.08,0.08)", goldR, "");
	chainHeL->Draw("ExTgtCor_L.dp>>HedpNoCutL(400,-0.08,0.08)", "", "");
	chainHeL->Draw("ExTgtCor_L.dp>>HedpCutL(400,-0.08,0.08)", goldL, "");
	HedpNoCut->Add(HedpNoCutR,HedpNoCutL);
	HedpNoCut->SetTitle(titledpHe);
	HedpNoCut->Draw();
	HedpCut->Add(HedpCutR,HedpCutL);
	HedpCut->SetLineColor(kBlack);
	HedpCut->SetFillColor(kViolet);
	HedpCut->Draw("same");

	pad05->cd();
	TString titledpC = "dp Cut from 12C Runs";
	cout << "Drawing " << titledpC << "..." << endl;
	TH1F *CdpNoCut = new TH1F("CdpNoCut",titledpC,400,-0.8,0.8);
	TH1F *CdpCut = new TH1F("CdpCut",titledpC,400,-0.8,0.8);
	chainCR->Draw("ExTgtCor_R.dp>>CdpNoCutR(400,-0.08,0.08)", "", "");
	chainCR->Draw("ExTgtCor_R.dp>>CdpCutR(400,-0.08,0.08)", goldR, "");
	chainCL->Draw("ExTgtCor_L.dp>>CdpNoCutL(400,-0.08,0.08)", "", "");
	chainCL->Draw("ExTgtCor_L.dp>>CdpCutL(400,-0.08,0.08)", goldL, "");
	CdpNoCut->Add(CdpNoCutR,CdpNoCutL);
	CdpNoCut->SetTitle(titledpC);
	CdpNoCut->Draw();
	CdpCut->Add(CdpCutR,CdpCutL);
	CdpCut->SetLineColor(kBlack);
	CdpCut->SetFillColor(kViolet);
	CdpCut->Draw("same");

	pad02->cd();
	TString titleTargetHe = "Target Cut for 3He Runs";
	cout << "Drawing " << titleTargetHe << "..." << endl;
	TH1F *HeReactZNoCut = new TH1F("HeReactZNoCut",titleTargetHe,400,-0.3,0.3);
	TH1F *HeReactZCut = new TH1F("HeReactZCut",titleTargetHe,400,-0.3,0.3);
	chainHeR->Draw("ReactPt_R.z>>HeReactZNoCutR(400,-0.3,0.3)", "", "");
	chainHeR->Draw("ReactPt_R.z>>HeReactZCutR(400,-0.3,0.3)", targetR, "");
	chainHeL->Draw("ReactPt_L.z>>HeReactZNoCutL(400,-0.3,0.3)", "", "");
	chainHeL->Draw("ReactPt_L.z>>HeReactZCutL(400,-0.3,0.3)", targetL, "");
	HeReactZNoCut->Add(HeReactZNoCutR,HeReactZNoCutL);
	HeReactZNoCut->SetTitle(titleTargetHe);
	HeReactZNoCut->Draw();
	HeReactZCut->Add(HeReactZCutR,HeReactZCutL);
	HeReactZCut->SetLineColor(kBlack);
	HeReactZCut->SetFillColor(kViolet);
	HeReactZCut->Draw("same");

	pad06->cd();
	TString titleTargetC = "Target Cut for 12C Runs";
	cout << "Drawing " << titleTargetC << "..." << endl;
	TH1F *CReactZNoCut = new TH1F("CReactZNoCut",titleTargetC,400,-0.3,0.3);
	TH1F *CReactZCut = new TH1F("CReactZCut",titleTargetC,400,-0.3,0.3);
	chainCR->Draw("ReactPt_R.z>>CReactZNoCutR(400,-0.3,0.3)", "", "");
	chainCR->Draw("ReactPt_R.z>>CReactZCutR(400,-0.3,0.3)", targetR, "");
	chainCL->Draw("ReactPt_L.z>>CReactZNoCutL(400,-0.3,0.3)", "", "");
	chainCL->Draw("ReactPt_L.z>>CReactZCutL(400,-0.3,0.3)", targetL, "");
	CReactZNoCut->Add(CReactZNoCutR,CReactZNoCutL);
	CReactZNoCut->SetTitle(titleTargetC);
	CReactZNoCut->Draw();
	CReactZCut->Add(CReactZCutR,CReactZCutL);
	CReactZCut->SetLineColor(kBlack);
	CReactZCut->SetFillColor(kViolet);
	CReactZCut->Draw("same");

	pad03->cd();
	TString titleThetaPhiHe = "Theta and Phi, No Cut, for 3He";
	cout << "Drawing " << titleThetaPhiHe << "..." << endl;
	TH2F *HeThetaPhiNoCut = new TH2F("HeThetaPhiNoCut",titleThetaPhiHe,100,-0.05,0.05,100,-0.1,0.1);
	chainHeR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeThetaPhiNoCutR(100,-0.05,0.05,100,-0.1,0.1)", targetR, "");
	chainHeL->Draw("ExTgtCor_L.th:ExTgtCor_L.ph>>HeThetaPhiNoCutL(100,-0.05,0.05,100,-0.1,0.1)", targetL, "");
	HeThetaPhiNoCut->Add(HeThetaPhiNoCutR,HeThetaPhiNoCutL);
	HeThetaPhiNoCut->SetTitle(titleThetaPhiHe);
	HeThetaPhiNoCut->SetStats(kFALSE);
	HeThetaPhiNoCut->Draw("COLZ");

	pad07->cd();
	TString titleThetaPhiC = "Theta and Phi, No Cut, for 12C";
	cout << "Drawing " << titleThetaPhiC << "..." << endl;
	TH2F *CThetaPhiNoCut = new TH2F("CThetaPhiNoCut",titleThetaPhiC,100,-0.05,0.05,100,-0.1,0.1);
	chainCR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>CThetaPhiNoCutR(100,-0.05,0.05,100,-0.1,0.1)", targetR, "");
	chainCL->Draw("ExTgtCor_L.th:ExTgtCor_L.ph>>CThetaPhiNoCutL(100,-0.05,0.05,100,-0.1,0.1)", targetL, "");
	CThetaPhiNoCut->Add(CThetaPhiNoCutR,CThetaPhiNoCutL);
	CThetaPhiNoCut->SetTitle(titleThetaPhiC);
	CThetaPhiNoCut->SetStats(kFALSE);
	CThetaPhiNoCut->Draw("COLZ");

	pad04->cd();
	TString titleThetaCutHe = "Theta and Phi Cut for 3He";
	cout << "Drawing " << titleThetaCutHe << "..." << endl;
	TH2F *HeThetaPhiCut = new TH2F("HeThetaPhiCut",titleThetaCutHe,100,-0.05,0.05,100,-0.1,0.1);
	chainHeR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeThetaPhiCutR(100,-0.05,0.05,100,-0.1,0.1)", targetR && sieveR, "");
	chainHeL->Draw("ExTgtCor_L.th:ExTgtCor_L.ph>>HeThetaPhiCutL(100,-0.05,0.05,100,-0.1,0.1)", targetL && sieveL, "");
	HeThetaPhiCut->Add(HeThetaPhiCutR,HeThetaPhiCutL);
	HeThetaPhiCut->SetTitle(titleThetaCutHe);
	HeThetaPhiCut->SetStats(kFALSE);
	HeThetaPhiCut->Draw("COLZ");

	pad08->cd();
	TString titleThetaCutC = "Theta and Phi Cut for 12C";
	cout << "Drawing " << titleThetaCutC << "..." << endl;
	TH2F *CThetaPhiCut = new TH2F("CThetaPhiCut",titleThetaCutC,100,-0.05,0.05,100,-0.1,0.1);
	chainCR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>CThetaPhiCutR(100,-0.05,0.05,100,-0.1,0.1)", targetR && sieveR, "");
	chainCL->Draw("ExTgtCor_L.th:ExTgtCor_L.ph>>CThetaPhiCutL(100,-0.05,0.05,100,-0.1,0.1)", targetL && sieveL, "");
	CThetaPhiCut->Add(CThetaPhiCutR,CThetaPhiCutL);
	CThetaPhiCut->SetTitle(titleThetaCutC);
	CThetaPhiCut->SetStats(kFALSE);
	CThetaPhiCut->Draw("COLZ");

	pad15->cd();
	TString titleQ2WHe = "Q2 v. Omega for 3He";
	cout << "Drawing " << titleQ2WHe << "..." << endl;
	TH2F *Q2WHe = new TH2F("Q2WHe",titleQ2WHe,100,0.3,0.8,400,0,1.6);
	chainHeR->Draw("PriKineR.Q2:PriKineR.nu>>Q2WHeR(100,0.3,0.8,400,0,1.6)", cutsR, "");
	chainHeL->Draw("PriKineL.Q2:PriKineL.nu>>Q2WHeL(100,0.3,0.8,400,0,1.6)", cutsL, "");
	Q2WHe->Add(Q2WHeR,Q2WHeL);
	Q2WHe->SetTitle(titleQ2WHe);
	Q2WHe->SetStats(kFALSE);
	Q2WHe->Draw("COLZ");

	pad16->cd();
	TString titleQ2WC = "Q2 v. Omega for 12C";
	cout << "Drawing " << titleQ2WC << "..." << endl;
	TH2F *Q2WC = new TH2F("Q2WC",titleQ2WC,100,0.3,0.8,400,0,1.6);
	chainCR->Draw("PriKineR.Q2:PriKineR.nu>>Q2WCR(100,0.3,0.8,400,0,1.6,100)", cutsR, "");
	chainCL->Draw("PriKineL.Q2:PriKineL.nu>>Q2WCL(100,0.3,0.8,400,0,1.6,100)", cutsL, "");
	Q2WC->Add(Q2WCR,Q2WCL);
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
	TH1F *histCR = new TH1F("histCR",titleC,bins,plotmin,plotmax);
	TH1F *histCL = new TH1F("histCL",titleC,bins,plotmin,plotmax);
	histC->Sumw2();
	histCR->Sumw2();
	histCL->Sumw2();
	chainCR->Draw("PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315)>>histCR", cutsR, "E");
	chainCL->Draw("PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315)>>histCL", cutsL, "E");
	histCR->Scale(1/0.0161297);
	histCL->Scale(1/0.0063175);
	histC->Add(histCR,histCL);
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
//	TF1 *fitC3 = new TF1("fitC3","[0]*exp(-x*[1])",1.35,1.45);
//	fitC3->SetParNames("C Green p1","C Green p2");
//	Double_t fitC3const = fitC3->GetParameter(0);
//	Double_t fitC3expconst = fitC3->GetParameter(1);
//	Double_t fitC3exp = fitC3->GetParameter(2);
//	Double_t fitC3consterror = fitC3->GetParError(0);
//	Double_t fitC3expconsterror = fitC3->GetParError(1);
//	Double_t fitC3experror = fitC3->GetParError(2);
//	fitC3->SetLineColor(kGreen);
//
//	histC.Fit("fitC2","R");
//	histC.Fit("fitC3","R+");
//	histC.Fit("fitC1","R+");
	

	pad12->cd();
	pad12->SetLogy();
	cout << "Drawing " << titleC << " in log scale..." << endl;
	TH1F *histC = new TH1F("histC",titleC,bins,plotmin,plotmax);
	TH1F *histCR = new TH1F("histCR",titleC,bins,plotmin,plotmax);
	TH1F *histCL = new TH1F("histCL",titleC,bins,plotmin,plotmax);
	histC->Sumw2();
	histCR->Sumw2();
	histCL->Sumw2();
	chainCR->Draw("PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315)>>histCR", cutsR, "E");
	chainCL->Draw("PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315)>>histCL", cutsL, "E");
	histC->Add(histCR,histCL);
	histC->Draw();
//	histC.Fit("fitC1","R");
//	histC.Fit("fitC3","R+");
//	histC.Fit("fitC2","R+");

	pad10->cd();
	TString titleHe = "x for 3He at Q2 of ";
	titleHe += Q2;
//	titleHe += " and Target Cut of ";
//	titleHe += target;
	cout << "Drawing " << titleHe << "..." << endl;
	TH1F *histHe = new TH1F("histHe",titleHe,bins,plotmin,plotmax);
	TH1F *histHeR = new TH1F("histHeR",titleHe,bins,plotmin,plotmax);
	TH1F *histHeL = new TH1F("histHeL",titleHe,bins,plotmin,plotmax);
	histHe->Sumw2();
	histHeR->Sumw2();
	histHeL->Sumw2();
	chainHeR->Draw("PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315)>>histHeR", cutsR, "E");
	chainHeL->Draw("PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315)>>histHeL", cutsL, "E");
	histHeR->Scale(1/2.409416);
	histHeL->Scale(1/2.407866);
	histHe->Add(histHeR,histHeL);
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
//	TF1 *fitHe3 = new TF1("fitHe3","[0]*exp(-x*[1])",1.35,1.45);
//	fitHe3->SetParNames("He Green p1","He Green p2");
//	Double_t fitHe3const = fitHe3->GetParameter(0);
//	Double_t fitHe3expconst = fitHe3->GetParameter(1);
//	Double_t fitHe3exp = fitHe3->GetParameter(2);
//	Double_t fitHe3consterror = fitHe3->GetParError(0);
//	Double_t fitHe3expconsterror = fitHe3->GetParError(1);
//	Double_t fitHe3experror = fitHe3->GetParError(2);
//	fitHe3->SetLineColor(kGreen);



//	histHe.Fit("fitHe2","R");
//	histHe.Fit("fitHe3","R+");
//	histHe.Fit("fitHe1","R+");

	pad13->cd();
	pad13->SetLogy();
	cout << "Drawing " << titleHe << " in log scale..." << endl;
	TH1F *histHe = new TH1F("histHe",titleHe,bins,plotmin,plotmax);
	TH1F *histHeR = new TH1F("histHeR",titleHe,bins,plotmin,plotmax);
	TH1F *histHeL = new TH1F("histHeL",titleHe,bins,plotmin,plotmax);
	histHe->Sumw2();
	histHeR->Sumw2();
	histHeL->Sumw2();
	chainHeR->Draw("PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315)>>histHeR", cutsR, "E");
	chainHeL->Draw("PriKineL.Q2 / (PriKineL.nu * 2 * 0.9315)>>histHeL", cutsR, "E");
	histHe->Add(histHeR,histHeL);
	histHe->Draw();
//	histHe.Fit("fitHe1","R");
//	histHe.Fit("fitHe3","R+");
//	histHe.Fit("fitHe2","R+");

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

   
	TString imagename = "xbj_scaling_plots/Vertical_xbj_scaling_plots_all_at_Q2_of_";
	imagename += Q2;
	imagename += ".png";
	c1->Print(imagename);

	cout << "All done!" << endl;


}
