// This was a program to chain together different
// root files and look at graphs from them.
// In particular, it will output plots of x=Q2/(2m*nu)
// of 3He and 12C and of 12C/3He to look for short
// range correlation in E05-102 and E08-005.
//
// Elena Long (ellie@jlab.org)



void v_src_fit(){

  int CRunNumberR=20591;
  int endCRunNumberR=22461;
  int HeRunNumberR=20596;
  int endHeRunNumberR=20789;
// NOTE: There is a problem with the BCM values. When fixed, swap below and above lines.
//  int endHeRunNumberR=20879;

  TString Q2 = "1.0";
  TString vartodraw = "PriKineR.Q2 / (PriKineR.nu * 2 * 0.9315)";
//Range is of the form (bins, start, end)
//  TString range = "(800,0.5,4.0)";
  double bins = 50;
  double plotmin = 0.5;
  double plotmax = 2.0;
  TString title = "12C/3He x with Target cut, Run # ";
  title += CRunNumberR;
  title += " & ";
  title += HeRunNumberR;

	TCut cut = "";  
	TCut kinematics = "PriKineR.Q2<10 && GoodElectron==1 && PriKineR.nu<10";
//	TCut eventtype = "D.evtypebits&(1<<1)>0";
	TCut eventtype = "(D.evtypebits&2)==2";
	TCut gold = "ExTgtCor_R.dp>-0.04 && ExTgtCor_R.dp<0.055";
	TCut target = "ReactPt_R.z>-0.172 && ReactPt_R.z<0.175";
	TCut sieve = "abs(ExTgtCor_R.ph)<0.03 && abs(ExTgtCor_R.th)<0.06";

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
  whattodrawC += ">>histCR";
  TString whattodrawHe = whattodraw;
  whattodrawHe += ">>histHeR";
  TChain* chainCR = new TChain("T");
  TChain* chainHeR = new TChain("T");

  gStyle->SetErrorX(.25);
  gStyle->SetEndErrorSize(.25);
  ifstream inp;
  ofstream out;

  TString filenameCR;
  TString filenameHeR;


// Below is the loop for adding chains for the Carbon run
  for (int thisCRunNumberR=CRunNumberR; thisCRunNumberR<(endCRunNumberR+1); thisCRunNumberR++)
  {
 		if(thisCRunNumberR==20592){thisCRunNumberR=20731;}
		if(thisCRunNumberR==20735){thisCRunNumberR=20762;}
		if(thisCRunNumberR==20765){thisCRunNumberR=22380;}
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




// Below is the loop for adding chains for the 3He run

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
	if(thisHeRunNumberR==20762){thisHeRunNumberR=20789;}
	if(thisHeRunNumberR==20763){thisHeRunNumberR=20789;}
	if(thisHeRunNumberR==20764){thisHeRunNumberR=20789;}
	if(thisHeRunNumberR==20791){thisHeRunNumberR=20814;}
	if(thisHeRunNumberR==20792){thisHeRunNumberR=20814;}

	// Skipping Longitudinal Carbon Runs
	if(thisHeRunNumberR==22380){thisHeRunNumberR=22393;}
	if(thisHeRunNumberR==22389){thisHeRunNumberR=22393;}
	if(thisHeRunNumberR==22425){thisHeRunNumberR=22436;}
	if(thisHeRunNumberR==22426){thisHeRunNumberR=22436;}

	// Skipping Transverse Carbon Runs
	if(thisHeRunNumberR==22461){thisHeRunNumberR=22465;}
	if(thisHeRunNumberR==20591){thisHeRunNumberR=20596;}

   if(thisHeRunNumberR==22397){thisHeRunNumberR=22398;}
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
	chainHeR->Draw("ExTgtCor_R.dp>>HedpNoCut(400,-0.08,0.08)", "", "");
	chainHeR->Draw("ExTgtCor_R.dp>>HedpCut(400,-0.08,0.08)", gold, "");
	HedpNoCut->SetTitle(titledpHe);
	HedpNoCut->Draw();
	HedpCut->SetLineColor(kBlack);
	HedpCut->SetFillColor(kViolet);
	HedpCut->Draw("same");

	pad05->cd();
	TString titledpC = "dp Cut from 12C Runs";
	cout << "Drawing " << titledpC << "..." << endl;
	chainCR->Draw("ExTgtCor_R.dp>>CdpNoCut(400,-0.08,0.08)", "", "");
	chainCR->Draw("ExTgtCor_R.dp>>CdpCut(400,-0.08,0.08)", gold, "");
	CdpNoCut->SetTitle(titledpC);
	CdpNoCut->Draw();
	CdpCut->SetLineColor(kBlack);
	CdpCut->SetFillColor(kViolet);
	CdpCut->Draw("same");

	pad02->cd();
	TString titleTargetHe = "Target Cut for 3He Runs";
	cout << "Drawing " << titleTargetHe << "..." << endl;
	chainHeR->Draw("ReactPt_R.z>>HeReactZNoCut(400,-0.3,0.3)", "", "");
	chainHeR->Draw("ReactPt_R.z>>HeReactZCut(400,-0.3,0.3)", target, "");
	HeReactZNoCut->SetTitle(titleTargetHe);
	HeReactZNoCut->Draw();
	HeReactZCut->SetLineColor(kBlack);
	HeReactZCut->SetFillColor(kViolet);
	HeReactZCut->Draw("same");

	pad06->cd();
	TString titleTargetC = "Target Cut for 12C Runs";
	cout << "Drawing " << titleTargetC << "..." << endl;
	chainCR->Draw("ReactPt_R.z>>CReactZNoCut(400,-0.3,0.3)", "", "");
	chainCR->Draw("ReactPt_R.z>>CReactZCut(400,-0.3,0.3)", target, "");
	CReactZNoCut->SetTitle(titleTargetC);
	CReactZNoCut->Draw();
	CReactZCut->SetLineColor(kBlack);
	CReactZCut->SetFillColor(kViolet);
	CReactZCut->Draw("same");

	pad03->cd();
	TString titleThetaPhiHe = "Theta and Phi, No Cut, for 3He";
	cout << "Drawing " << titleThetaPhiHe << "..." << endl;
	chainHeR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeSieveNoCut(100,-0.05,0.05,100,-0.1,0.1)", target, "");
	HeSieveNoCut->SetTitle(titleThetaPhiHe);
	HeSieveNoCut->SetStats(kFALSE);
	HeSieveNoCut->Draw("COLZ");

	pad07->cd();
	TString titleThetaPhiC = "Theta and Phi, No Cut, for 12C";
	cout << "Drawing " << titleThetaPhiC << "..." << endl;
	chainCR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>CSieveNoCut(100,-0.05,0.05,100,-0.1,0.1)", target, "");
	CSieveNoCut->SetTitle(titleThetaPhiC);
	CSieveNoCut->SetStats(kFALSE);
	CSieveNoCut->Draw("COLZ");

	pad04->cd();
	TString titleThetaCutHe = "Theta and Phi Cut for 3He";
	cout << "Drawing " << titleThetaCutHe << "..." << endl;
	chainHeR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>HeSieveCut(100,-0.05,0.05,100,-0.1,0.1)", target && sieve, "");
	HeSieveCut->SetTitle(titleThetaCutHe);
	HeSieveCut->SetStats(kFALSE);
	HeSieveCut->Draw("COLZ");

	pad08->cd();
	TString titleThetaCutC = "Theta and Phi Cut for 12C";
	cout << "Drawing " << titleThetaCutC << "..." << endl;
	chainCR->Draw("ExTgtCor_R.th:ExTgtCor_R.ph>>CSieveCut(100,-0.05,0.05,100,-0.1,0.1)", target && sieve, "");
	CSieveCut->SetTitle(titleThetaCutC);
	CSieveCut->SetStats(kFALSE);
	CSieveCut->Draw("COLZ");

	pad15->cd();
	TString titleQ2WHe = "Q2 v. Nu for 3He";
	cout << "Drawing " << titleQ2WHe << "..." << endl;
	chainHeR->Draw("PriKineR.Q2:PriKineR.nu>>Q2WHe(100,0.3,0.8,400,0,1.6)", cuts, "");
	Q2WHe->SetTitle(titleQ2WHe);
	Q2WHe->SetStats(kFALSE);
	Q2WHe->Draw("COLZ");

	pad16->cd();
	TString titleQ2WC = "Q2 v. Nu for 12C";
	cout << "Drawing " << titleQ2WC << "..." << endl;
	chainCR->Draw("PriKineR.Q2:PriKineR.nu>>Q2WC(100,0.3,0.8,400,0,1.6,100)", cuts, "");
	Q2WC->SetTitle(titleQ2WC);
	Q2WC->SetStats(kFALSE);
	Q2WC->Draw("COLZ");


	pad09->cd();
	TString titleC = "x for 12C at Q2 of ";
	titleC += Q2;
//	titleC += " and Target Cut of ";
//	titleC += target;
	cout << "Drawing " << titleC << "..." << endl;
	TH1F *histCR = new TH1F("histCR",titleC,bins,plotmin,plotmax);
	histCR->Sumw2();
	chainCR->Draw(whattodrawC, cuts, "E");
	histCR.Scale(1/0.0161297);
	histCR->Draw();
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

	histCR->Fit("fitC2","R");
	histCR->Fit("fitC3","R+");
	histCR->Fit("fitC1","R+");
	

	pad12->cd();
	pad12->SetLogy();
	cout << "Drawing " << titleC << " in log scale..." << endl;
	TH1F *histCR = new TH1F("histCR",titleC,bins,plotmin,plotmax);
	histCR->Sumw2();
	chainCR->Draw(whattodrawC, cuts, "E");
	histCR->Draw();
	histCR->Fit("fitC1","R");
	histCR->Fit("fitC3","R+");
	histCR->Fit("fitC2","R+");

	pad10->cd();
	TString titleHe = "x for 3He at Q2 of ";
	titleHe += Q2;
//	titleHe += " and Target Cut of ";
//	titleHe += target;
	cout << "Drawing " << titleHe << "..." << endl;
	TH1F *histHeR = new TH1F("histHeR",titleHe,bins,plotmin,plotmax);
	histHeR->Sumw2();
	chainHeR->Draw(whattodrawHe, cuts, "E");
	histHeR.Scale(1/2.33878);
	histHeR->Draw();
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

	histHeR->Fit("fitHe2","R+");
	histHeR->Fit("fitHe3","R+");
	histHeR->Fit("fitHe1","R+");
	
	pad13->cd();
	pad13->SetLogy();
	cout << "Drawing " << titleHe << " in log scale..." << endl;
	TH1F *histHeR = new TH1F("histHeR",titleHe,bins,plotmin,plotmax);
	histHeR->Sumw2();
	chainHeR->Draw(whattodrawHe, cuts, "E");
	histHeR->Draw();
	histHeR->Fit("fitHe1","R+");
	histHeR->Fit("fitHe3","R+");
	histHeR->Fit("fitHe2","R+");

	pad11->cd();
	TString titleCoverHe = "12C/3He for Q2 of ";
	titleCoverHe += Q2;
//	titleCoverHe += " and Target Cut of ";
//	titleCoverHe += target;
	cout << "Drawing " << titleCoverHe << "..." << endl;
	TH1F *histCoverHeR = new TH1F("histCoverHeR",titleCoverHe,bins,plotmin,plotmax);
	histCoverHeR->Sumw2();
	histCoverHeR->Divide(histCR,histHeR,1,0.0918143);
	histCoverHeR->Draw("E");

	pad14->cd();
	pad14->SetLogy();
	cout << "Drawing " << titleCoverHe << " in log scale..." << endl;
	TH1F *histCoverHeR = new TH1F("histCoverHeR",titleCoverHe,bins,plotmin,plotmax);
	histCoverHeR->Sumw2();
	histCoverHeR->Divide(histCR,histHeR,1,0.0918143);
	histCoverHeR->Draw("E");

   
	TString imagename = "xbj_scaling_plots/Vertical_xbj_scaling_plots_all_at_Q2_of_";
	imagename += Q2;
	imagename += ".png";
	c1->Print(imagename);

	cout << "All done!" << endl;


}
