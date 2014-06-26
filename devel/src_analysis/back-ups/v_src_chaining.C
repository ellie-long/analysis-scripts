// This was a program to chain together different
// root files and look at graphs from them.
// In particular, it will output plots of x=Q2/(2m*omega)
// of 3He and 12C and of 12C/3He to look for short
// range correlation in E05-102 and E08-005.
//
// Elena Long (ellie@jlab.org)



void v_src_chaining(){

  int CRunNumber=20591;
  int endCRunNumber=22461;
  int HeRunNumber=20596;
  int endHeRunNumber=20879;

  TString Q2 = "1.0";
  TString vartodraw = "PriKineR.Q2 / (PriKineR.omega * 2 * 0.9315)";
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
	TCut kinematics = "PriKineR.Q2<10 && GoodElectron==1 && PriKineR.omega<10";
//	TCut eventtype = "D.evtypebits&(1<<1)>0";
	TCut eventtype = "(D.evtypebits&2)==2";
	TCut gold = "R.gold.dp>-0.04 && R.gold.dp<0.053";
	TCut target = "ReactPt_R.z>-0.1 && ReactPt_R.z<0.08";
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
		if(thisCRunNumber==endCRunNumber){cout << "--------------------Starting 3He Chain--------------------" << endl;}	
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
//              The lines below here shouldn't be needed, but are saved just in case
//		if(thisHeRunNumber==22423){thisHeRunNumber=22435;}
//		if(thisHeRunNumber==20583){thisHeRunNumber=20595;}

// Uncommenting the line below will let the code only go through one run (Good for debugging purposes)
//	thisHeRunNumber = 999999999;

  }


	

	TCanvas *c1 = new TCanvas("c1","x of 12C and 3He",1360,800);//x,y
	pad1 = new TPad("pad1","pad1",0,0,0.333,0.5,0,0,0);
	pad2 = new TPad("pad2","pad2",0.333,0,0.666,0.5,0,0,0);
	pad3 = new TPad("pad3","pad3",0.666,0,0.999,0.5,0,0,0);
	pad4 = new TPad("pad4","pad4",0,0.5,0.333,1.0,0,0,0);
	pad5 = new TPad("pad5","pad5",0.333,0.5,0.666,1.0,0,0,0);
	pad6 = new TPad("pad6","pad6",0.666,0.5,0.999,1.0,0,0,0);
	pad1->Draw();pad2->Draw();pad3->Draw();pad4->Draw();pad5->Draw();pad6->Draw();

	pad4->cd();
	TString titleC = "x for 12C at Q2 of ";
	titleC += Q2;
//	titleC += " and Target Cut of ";
//	titleC += target;
	TH1F *histC = new TH1F("histC",titleC,bins,plotmin,plotmax);
	histC->Sumw2();
	chainC->Draw(whattodrawC, cuts, "E");
	histC->Draw();
	
	pad1->cd();
	pad1->SetLogy();
	TH1F *histC = new TH1F("histC",titleC,bins,plotmin,plotmax);
	histC->Sumw2();
	chainC->Draw(whattodrawC, cuts, "E");
	histC->Draw();

	pad5->cd();
	TString titleHe = "x for 3He at Q2 of ";
	titleHe += Q2;
//	titleHe += " and Target Cut of ";
//	titleHe += target;
	TH1F *histHe = new TH1F("histHe",titleHe,bins,plotmin,plotmax);
	histHe->Sumw2();
	chainHe->Draw(whattodrawHe, cuts, "E");
	histHe->Draw();

	pad2->cd();
	pad2->SetLogy();
	TH1F *histHe = new TH1F("histHe",titleHe,bins,plotmin,plotmax);
	histHe->Sumw2();
	chainHe->Draw(whattodrawHe, cuts, "E");
	histHe->Draw();

	pad6->cd();
	TString titleCoverHe = "12C/3He for Q2 of ";
	titleCoverHe += Q2;
//	titleCoverHe += " and Target Cut of ";
//	titleCoverHe += target;
	TH1F *histCoverHe = new TH1F("histCoverHe",titleCoverHe,bins,plotmin,plotmax);
	histCoverHe->Sumw2();
	histCoverHe->Divide(histC,histHe,1,0.0918143);
	histCoverHe->Draw("E");

	pad3->cd();
	pad3->SetLogy();
	TH1F *histCoverHe = new TH1F("histCoverHe",titleCoverHe,bins,plotmin,plotmax);
	histCoverHe->Sumw2();
	histCoverHe->Divide(histC,histHe,1,0.0918143);
	histCoverHe->Draw("E");

  

}
