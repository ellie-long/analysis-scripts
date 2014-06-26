// This script will take a ut and overlay the cut part in red
// on top of the original plot in black
//
// Elena Long (ellie@jlab.org) 07-28-2009



void draw_cuts2(int runnumber){
  TCut cut ="abs(ReactPt_R.z)<0.15";
  double plotmin = -0.3;
  double plotmax = 0.3;

  TString vartodraw = "ReactPt_R.z";
//Range is of the form (bins, start, end)
//  TString range = "(500,-0.3,0.3)";
  TString title = "12C Target Cut, Run # ";
  title += runnumber;

  TString whattodraw = vartodraw;
  whattodraw += ">>";
  whattodraw += title;
//  whattodraw += range;

  TCanvas *c1 = new TCanvas("c1","Cut in Red, Original in Black",800,700);//x,y

  TChain* chain = new TChain("T");


  ifstream inp;
  ofstream out;

  TString filename;

    for (int t=0; t<1000;t++)
    {
      filename = "/home/ellie/physics/e05-102/ellana/ROOTfiles/e05102_R_";
      filename += runnumber;
      if (t!=0)
      {
        filename += "_";
        filename += t;
      }

      filename += ".root";

      ifstream ifile(filename);
      if (ifile)
      {
        cout << "Adding file to chain: " << filename << endl;
        chain->Add(filename);
      }
      else
      {
        cout << "File " << filename << " does not exist. Ending here." << endl;
        t=9999999;
      }
    }

  c1->cd(1);

  gStyle->SetOptStat(kFALSE);
  TH1F *h1 = new TH1F("h1","Without Cut",500,plotmin,plotmax);
  h1->Fill(chain->Draw(vartodraw));
  h1->Draw();
  c1->Update();

  TH1F *h2 = new TH1F("h2","With Cut",500,plotmin,plotmax);
  h2->Fill(chain->Draw(vartodraw,cut));

  Float_t rightmax = 1.1*h1->GetMaximum();
  Float_t scale = gPad->GetUymax()/rightmax;
  h2->SetLineColor(kRed);
  h2->Scale(scale);  
  h2->Draw("same");

/*
  chain->SetLineColor(kBlack);
  chain->GetXaxis->SetRange(plotmin,plotmax);
  chain->Draw(whattodraw,"",);
  c1->Update();

  Float_t rightmax = 1.1*chain
  chain->SetLineColor(kRed);
  chain->Scale(scale);
  chain->Draw(whattodraw,cut,"SAME");
  c1->Update();
*/
}
