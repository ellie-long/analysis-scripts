// This is a program swiped from Ramesh to look at
// data. Specifically, I'm using it for the Chain
// commands that are already set up in it.


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void neut_kin2(int runnumber){



  gStyle->SetOptFit(0);
  gStyle->SetPalette(1);

  gStyle->SetOptStat(0);
  gStyle->SetStatBorderSize(0);
  gStyle->SetStatColor(0);
  gStyle->SetStatW(0.18);
  gStyle->SetStatH(0.12);

  gStyle->SetCanvasColor(0); 
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15); 

  gStyle->SetOptTitle(1);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleFontSize(0.05);
  gStyle->SetTitleSize(0.05,"xyz");
  gStyle->SetTitleOffset(1.3,"xyz");




  TCanvas *c1 = new TCanvas("c1","neut_kin2",600,850);//x,y

  TChain* chain = new TChain("T");


  ifstream inp;
  ofstream out;

//  char filename[100];
  TString filename;
  FILE* fd;
  string thefilename;
  //for (int t=3211;t<=3414;t++) { // kin3
//  for (int t=2898;t<=3209;t++) {// kin2
  //for (int t=1868;t<=2895;t++) {// kin1
  //for (int t=2898;t<=3414;t++) { //kin2 and  kin3
  //for (int t=1868;t<=3414;t++) { //kin1, kin2 and  kin3

//    sprintf(filename, "/adaqfs/home/adaq/e05102/ellie/devel/ellana/ROOTfiles/e05102_R_%d",runnumber);
    for (int t=0; t<10;t++)
    {
      filename = "/adaqfs/home/adaq/e05102/ellie/devel/ellana/ROOTfiles/e05102_R_";
      filename += runnumber;
      if (t!=0)
      {
//        char numch = (char) t;
//        strcat(filename, "_");
//        strcat(filename,numch);
        filename += "_";
        filename += t;
      }

//    strcat(filename,"_%d.root");
      filename += ".root";

        cout << "Adding file to chain: " << filename << endl;


      fd = fopen(filename,"r");
      if (fd != NULL) {
        fclose(fd);
        chain->Add(filename);
      }
    }

/*
  TCut tgL =" abs(L.tr.tg_th[0])<0.06 && abs(L.tr.tg_dp[0])<0.045 && abs(L.tr.tg_ph[0])<0.03";
  TCut tgR =" abs(R.tr.tg_th[0])<0.06 && abs(R.tr.tg_dp[0])<0.045 && abs(R.tr.tg_ph[0])<0.03";
  TCut tg = tgL && tgR;
  TCut ct1 = "abs(CT.ct_2by1[0]*1.e9-99.0)<2.5";
  TCut ct2 = "abs(CT.ct_1by2[0]*1.e9-99.0)<2.5";
  TCut ct = ct1||ct2;
  // TCut em = "SK.emiss>0.03 && SK.emiss<0.25";
  TCut em = "SK.emiss>0.03 ";
  TCut pm = "SK.pmiss>0.37 && SK.pmiss<0.52";

  //TCut ha = "atan2(SK.prec_x,SK.prec_z)*180.0/3.1416<-88.0";// kin3 -85
   TCut ha = "atan2(SK.prec_x,SK.prec_z)*180.0/3.1416<-84.0";//kin2 
  //TCut va = "abs(atan2(SK.prec_y,sqrt(SK.prec_x*SK.prec_x+SK.prec_z*SK.prec_z))*180.0/3.1416)<15";

  TCut hrs = tg && ct && em && pm && ha;

  const Int_t Bin = 100;
  const Int_t bin = 2;//3
  const Double_t low = 0.37;//0.39
  const Double_t high = 0.52; //0.63
  double value, Value,Value_1,Value_2,error,error_1;
  Double_t Mp = 0.93827203;
  Double_t Mn = 0.93956536;

  c1->Divide(1,2);


  TH1F* pp31=new TH1F("pp31","",Bin,low,high);
  TH1F* pp = new TH1F("pp","",bin,low,high);

  TH1F* h = new TH1F("h","",bin,low,high);

  TH1F* hh1 = new TH1F("hh1","",bin,low,high);
  TH1F* hh2 = new TH1F("hh2","",bin,low,high);
  TH1F* hh3 = new TH1F("hh3","",bin,low,high);
  TH1F* hh4 = new TH1F("hh4","",bin,low,high);
  TH1F* hh5 = new TH1F("hh5","",bin,low,high);
  TH1F* hh6 = new TH1F("hh6","",bin,low,high);
  TH1F* hh7 = new TH1F("hh7","",bin,low,high);
  TH1F* hh8 = new TH1F("hh8","",bin,low,high);

  TH1F* sub = new TH1F("sub","",bin,low,high);
  TH1F* sub1 = new TH1F("sub1","",bin,low,high);
  TH1F* sub2 = new TH1F("sub2","",bin,low,high);
  TH1F* sub3 = new TH1F("sub3","",bin,low,high);
  TH1F* sub4 = new TH1F("sub4","",bin,low,high);
  TH1F* sub5 = new TH1F("sub5","",bin,low,high);
  TH1F* sub6 = new TH1F("sub6","",bin,low,high);
  TH1F* sub7 = new TH1F("sub7","",bin,low,high);

  TH1F* kin3 = new TH1F("kin3","",bin,low,high);
  TH1F* kin23 = new TH1F("kin23","",bin,low,high);




  TF1* total = new TF1("total","[0]+gaus(1)",200.0,470.0);
  Double_t par[4];
  par[0] = 300.0;
  par[1] = 80.0;
  par[2] = 315.0;
  par[3] = 10.0;
  total->SetParameters(par);


*/


  c1->cd(1);
  TCut hrs = "R.gold.y>-0.047&&R.gold.y<0.02";
  chain->Draw("NA.n.tof",hrs && "NA.n.tof>150 && NA.n.tof<500");


  /*  h1->SetTitle("");
  h1->GetXaxis()->CenterTitle();
  h1->GetXaxis()->SetTitle("Neutron Time [ns]");
  h1->GetYaxis()->CenterTitle();
  h1->GetYaxis()->SetTitle("Counts");

  h1->Fit(total,"R");
  h1->GetFunction("total")->SetLineColor(2);
  h1->GetFunction("total")->SetLineWidth(1);
  h1->GetFunction("total")->SetLineStyle(2);

  Double_t Ih =  h1->Integral(20,23)-4*h1->GetFunction("total")->GetParameter(0);
  Double_t bgr = 4*h1->GetFunction("total")->GetParameter(0);

  cout<<" (e,e'pn) from tof fit "<<Ih<<endl<<endl;
// for pmiss>0.35
  TLine* line = new TLine(300,0,300,380);
  line->SetLineStyle(2);
  line->Draw("same");


  TLine* line = new TLine(336,0,336,380);
  line->SetLineStyle(2);
  line->Draw("same");


  TLine* line = new TLine(300,h1->GetFunction("total")->GetParameter(0),336,h1->GetFunction("total")->GetParameter(0));
  line->SetLineStyle(2);
  line->Draw("same");


  c1->Update();

  c1->cd(2);

  // (e,e'p) signal

  chain->Draw("SK.pmiss>>pp",hrs,"e1 hist");
  Int_t ent=  (Int_t)pp->GetEntries();
  Double_t Pmiss_31 = pp->GetMean();

  cout<<" (e,e'p) signal = "<<pp->GetEntries()<<endl;
  cout<<" pp  "<<Pmiss_31<<endl;
  cout<<"\n kin2 (e,e'pn) / (e,e'p) = "<<Ih<<"/"<<ent <<" = "<<Ih/ent<<endl;

  // start background subtraction
  ///////////////////////////////// right of tof peak ////////////////////////////


    chain->Draw("SK.pmiss>>hh1",hrs && "(NA.n.tof+CT.vx_t1[0]*1.e9)<372.0 && (NA.n.tof+CT.vx_t1[0]*1.e9)>336.0");
    chain->Draw("SK.pmiss>>hh2",hrs && "(NA.n.tof+CT.vx_t1[0]*1.e9)<408.0 && (NA.n.tof+CT.vx_t1[0]*1.e9)>372.0");

    value=error=0;

    for (int i=1;i<=hh1->GetNbinsX(); i++) {
      value = 0.5*hh1->GetBinContent(i)+0.5*hh2->GetBinContent(i);
      error = sqrt((0.25*hh1->GetBinError(i)*hh1->GetBinError(i))+(0.25*hh2->GetBinError(i)*hh2->GetBinError(i)));
      sub1->SetBinContent(i,value);
      sub1->SetBinError(i,error);
    }


    /////////////////////////////////


    chain->Draw("SK.pmiss>>hh3",hrs && "(NA.n.tof+CT.vx_t1[0]*1.e9)<444.0 && (NA.n.tof+CT.vx_t1[0]*1.e9)>408.0");
    chain->Draw("SK.pmiss>>hh4",hrs && "(NA.n.tof+CT.vx_t1[0]*1.e9)<480.0 && (NA.n.tof+CT.vx_t1[0]*1.e9)>444.0");

    value=error=0;

    for (int i=1;i<=hh3->GetNbinsX(); i++) {
      value = 0.5*hh3->GetBinContent(i)+0.5*hh4->GetBinContent(i);
      error = sqrt((0.25*hh3->GetBinError(i)*hh3->GetBinError(i))+(0.25*hh4->GetBinError(i)*hh4->GetBinError(i)));
      sub2->SetBinContent(i,value);
      sub2->SetBinError(i,error);
    }

    /////////////////////////////

    value=error=0;

    for (int i=1;i<=sub1->GetNbinsX(); i++) {
      value = 0.5*sub1->GetBinContent(i)+0.5*sub2->GetBinContent(i);
      error = sqrt((0.25*sub1->GetBinError(i)*sub1->GetBinError(i))+(0.25*sub2->GetBinError(i)*sub2->GetBinError(i)));
      sub3->SetBinContent(i,value);
      sub3->SetBinError(i,error);
    }



    ///////////////////////////////  tof peak leftwards//////////////////////



    chain->Draw("SK.pmiss>>hh5",hrs && "(NA.n.tof+CT.vx_t1[0]*1.e9)<300.0 && (NA.n.tof+CT.vx_t1[0]*1.e9)>264.0");
    chain->Draw("SK.pmiss>>hh6",hrs && "(NA.n.tof+CT.vx_t1[0]*1.e9)<264.0 && (NA.n.tof+CT.vx_t1[0]*1.e9)>228.0");

    value=error=0;

    for (int i=1;i<=hh5->GetNbinsX(); i++) {
      value = 0.5*hh5->GetBinContent(i)+0.5*hh6->GetBinContent(i);
      error = sqrt((0.25*hh5->GetBinError(i)*hh5->GetBinError(i))+(0.25*hh6->GetBinError(i)*hh6->GetBinError(i)));
      sub4->SetBinContent(i,value);
      sub4->SetBinError(i,error);
    }

    //////////////////////////////////

    chain->Draw("SK.pmiss>>hh7",hrs && "(NA.n.tof+CT.vx_t1[0]*1.e9)<228.0 && (NA.n.tof+CT.vx_t1[0]*1.e9)>192.0");

    value=error=0;

    for (int i=1;i<=hh7->GetNbinsX(); i++) {
      value = hh7->GetBinContent(i);
      error = hh7->GetBinError(i);
      sub5->SetBinContent(i,value);
      sub5->SetBinError(i,error);
    }

    ////////////////////////


    value=error=0;

    for (int i=1;i<=sub5->GetNbinsX(); i++) {
      value = 0.5*sub4->GetBinContent(i)+0.5*sub5->GetBinContent(i);
      error = sqrt((0.25*sub4->GetBinError(i)*sub4->GetBinError(i))+(0.25*sub5->GetBinError(i)*sub5->GetBinError(i)));
      sub6->SetBinContent(i,value);
      sub6->SetBinError(i,error);
    }

    ////////////////////////////////////// all together ////////////////////////////

    value=error=0;

    for (int i=1;i<=sub3->GetNbinsX(); i++) {
      value = 0.5*sub3->GetBinContent(i)+0.5*sub6->GetBinContent(i);
      error = sqrt((0.25*sub3->GetBinError(i)*sub3->GetBinError(i))+(0.25*sub6->GetBinError(i)*sub6->GetBinError(i)));
      sub7->SetBinContent(i,value);
      sub7->SetBinError(i,error);
    }




    // neutronMomentum signal plus background

     chain->Draw("SK.pmiss>>h",hrs && "(NA.n.tof+CT.vx_t1[0]*1.e9)>300.0 && (NA.n.tof+CT.vx_t1[0]*1.e9)<336.0","e1 hist");



    // background subtraction



    value=error=0;

    for (int i=1;i<=h->GetNbinsX(); i++) {
      value = h->GetBinContent(i)-sub7->GetBinContent(i);
      error = sqrt((h->GetBinError(i)*h->GetBinError(i))+(sub7->GetBinError(i)*sub7->GetBinError(i)));
      sub->SetBinContent(i,value);
      sub->SetBinError(i,error);


    }



    cout<<"(e,e'pn) signal from bg subtraction  = "<<sub->Integral(1,bin)<<endl;




    /////////////////////
    value=error=0;

    cout<< "\n(e,e'pn)/(e,e'p) yield using bg subtration: \n"<<endl;

    for (int i=1;i<=pp->GetNbinsX(); i++) {
      if(pp->GetBinContent(i)!=0){
      value = 5.882*sub->GetBinContent(i)/pp->GetBinContent(i);
      if(sub->GetBinContent(i)!=0){
      error = value*sqrt(pow(sub->GetBinError(i)/sub->GetBinContent(i),2) + pow(pp->GetBinError(i)/pp->GetBinContent(i),2));

      }}
      cout<< i<<", value= "<<value<<", error= "<<error<<", (error/value)*100 % ="<<(error/value)*100<<"%"<<endl;


      kin23->SetBinContent(i,value);
      kin23->SetBinError(i,error);
    }

    kin23->Draw("e1");
    kin23->SetLineColor(4);
    kin23->SetMinimum(0.0);
    kin23->SetTitle("");
    kin23->GetXaxis()->CenterTitle();
    kin23->GetXaxis()->SetTitle("pmiss  [GeV/c]");
    kin23->GetYaxis()->CenterTitle();
    kin23->GetYaxis()->SetTitle("#frac{(e,e'pn)}{(e,e'p)}");
    c1->Update();


*/
}

/*

for emiss>0.03 && emiss<0.25 cut

ee'p = 10699
ee'pn = 194.491 from tof fit
ee'pn = 179.37  from background subtraction


for emiss>0.03 and ha cut

ee'p = 10216
ee'pn = 174.102 from tof fit
ee'pn = 160.125 from background subtraction




*/
