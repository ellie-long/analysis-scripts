// This was a program to chain together different
// root files and look at graphs from them
//
// Elena Long (ellie@jlab.org)



void chaining(int runnumber){


  TString vartodraw = "PriKineR.Q2 / (PriKineR.omega * 2 * 0.93827203)";
//Range is of the form (bins, start, end)
  TString range = "(800,0.5,4.0)";
  TString title = "12C, Target cut, Run # ";
  title += runnumber;

//  TCut cut = "";
  TCut cut = "PriKineR.Q2<10&&GoodElectron==1&&PriKineR.omega<10";
  TCut target =  "abs(ReactPt_R.z)<0.15";
//  TCut target = ""; 

  TCut cuts = target && cut;
  TString whattodraw = vartodraw;
  whattodraw += ">>";
  whattodraw += title;
  whattodraw += range;

  TCanvas *c1 = new TCanvas("c1","neut_kin2",800,700);//x,y

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
  chain->Draw(whattodraw, cuts);

}
