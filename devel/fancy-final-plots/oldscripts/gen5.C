//  Plot GEn/GDipole


#include <cstring>
#include <TGraphAsymmErrors.h>
#include <cstdio>
#include <cstdlib>
#include <TMultiGraph.h>
#include <TFormula.h>
#include <TCanvas.h>
#include <iostream>
#include <TStyle.h>
#include <TLine.h>
#include <TFrame.h>
#include <TLegend.h>
#include <TMarker.h>
#include <TF1.h>
#include <TSystem.h>

#include "halla_plotting.h"

const char* psfile = "gen5";

using namespace std;

datafile_t datafiles[] = {
  //  { "formfactor_datafiles/GEn_Passchier.dat", "Passchier", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 5,1 },
  { "formfactor_datafiles/GEn_Herberg.dat", "Herberg", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,23,1 },
  { "formfactor_datafiles/GEn_Ostrick.dat", "Ostrick", "[0]", "[1]", "sqrt([2]*[2]+[4]*[4])", "sqrt([2]*[2]+[3]*[3])", 0,0,29,1 },
  { "formfactor_datafiles/GEn_Madey.dat", "Madey", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,22,2 },
  { "formfactor_datafiles/GEn_Seimetz.dat", "Seimetz", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,1 },
  { "formfactor_datafiles/GEn_Warren.dat", "Warren", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,21,2 },
  { "formfactor_datafiles/GEn_Becker.dat", "Becker", "[0]", "[1]", "[2]","[2]", 0,0,25,1 },
  { "formfactor_datafiles/GEn_Bermuth.dat", "Bermuth", "[0]", "[1]", "[2]", "[2]", 0,0,24,1 },
  //  { "e02013_proposal.dat", "E02-013 (proj)","[0]","[1]","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,26,2},
  { "e02013_results.dat", "E02-013","[0]","[1]","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,26,2},
  //  { "madey_proposal.dat", "E04-110 (proj)", "[0]", "0", "0.002", "0.002", 0, 0, 28, 2},
  { NULL }
};  

datafile_t theoryfiles1[] = {
  //  { "figure_input/Lattice/ffrng_all.dat", "Lattice", "[0]", "[10]", "[10]-[11]", "[12]-[10]", 0, 0, 1, 1, "F" },
  //  { "figure_input/Iachello/formfactor_10GeV.dat.2", "Iachello", "[0]", "[5]", "0", "0", 0, 0, 1, 1 },
  // { "figure_input/Bijker/spaceff.kees",             "Bijker",   "[0]", "[3]", "0", "0", 0, 0, 1, 4 },
  //  { "figure_input/Holzwarth/gen.dat.2",          "Holzwarth",   "[0]", "[1]", "0", "0", 0, 0, 2, 3 },
  //  { "figure_input/Hammer/genthf4.dat",              "Hammer",   "[0]", "[1]", "0", "0", 0, 0, 2, 4 },
  { "figure_input/Miller/GEn.dat.spl3",             "Miller",   "[0]", "[1]", "0", "0", 0, 0, 1, 3 },
  { "figure_input/Miller/GEn.qonly.dat.spl3",       "Miller (q-only)",  "[0]", "[1]", "0", "0", 0, 0, 4, 4 },
  //  { "figure_input/Miller/lattice.GEn.rtf","Miller Lattice",
  //    "[0]","[1]","[1]-[3]","[2]-[1]",0,0,1,3,"F" },
  { NULL }
};

Double_t gdipole(Double_t *x, Double_t *p) {
  Double_t Q2=*x;
  Double_t L2=.71;
  Double_t d = (1+Q2/L2)*(1+Q2/L2);
  return 1./d;
}

Double_t genff(Double_t *x, Double_t *p) {
  Double_t Q2=*x;
  Double_t scl=p[0];
  Double_t tau=Q2/(4*.939565*.939565);
  Double_t ch=0.;
  Double_t kappa=-1.91;
  Double_t lambda = .3; // GeV, lambda = 300 MeV
  Double_t L2 = .71;
  Double_t f2f1 = scl*TMath::Log(Q2/(lambda*lambda))*TMath::Log(Q2/(lambda*lambda))/Q2;
  Double_t muGe_Gm = (ch+kappa)*((1-tau*kappa*f2f1)/(1+kappa*f2f1));
  // now multiply by the dipole form factor to get ge for neutron
  Double_t gm = (ch+kappa)/(1+Q2/L2)/(1+Q2/L2);
  return gm*muGe_Gm/(ch+kappa)/gdipole(x,p);
}

Double_t genffq2(Double_t *x, Double_t *p) {
  Double_t Q2=*p;
  Double_t scl=x[0];
  Double_t tau=Q2/(4*.939565*.939565);
  Double_t ch=0.;
  Double_t kappa=-1.91;
  Double_t lambda = .3; // GeV, lambda = 300 MeV
  Double_t L2 = .71;
  Double_t f2f1 = scl*TMath::Log(Q2/(lambda*lambda))*TMath::Log(Q2/(lambda*lambda))/Q2;
  Double_t muGe_Gm = (ch+kappa)*((1-tau*kappa*f2f1)/(1+kappa*f2f1));
  // now multiply by the dipole form factor to get ge for neutron
  Double_t gm = (ch+kappa)/(1+Q2/L2)/(1+Q2/L2);
  return gm*muGe_Gm/(ch+kappa)/gdipole(x,p);
}

Double_t gen_bbba05(Double_t *x, Double_t *p) {
  Double_t Q2=*x;
  Double_t tau=Q2/(4*.939565*.939565);
  const int nA = 3;
  Double_t a[nA] = { 0., 1.25, 1.30 };
  const int nB = 5;
  Double_t b[nB] = {0, -9.86, 305, -758, 802};
  
  Double_t top=0., bot=1.;
  for (int k=0; k<nA; k++) top += a[k]*TMath::Power(tau,k);
  for (int k=0; k<nA; k++) bot += b[k]*TMath::Power(tau,k);
  return top/bot/gdipole(x,p);
}


TGraphAsymmErrors *fromGEntoGEnGd(TGraph *ogr) {
// take a curve (with errors) of GEn and make it into (GEn/Gd)
  if (!ogr) return 0;
  TGraphAsymmErrors *ogrE = dynamic_cast<TGraphAsymmErrors*>(ogr);
  int npts = ogr->GetN();
  Double_t x,y;
  Double_t Q2;
  Double_t Gd;
  TGraphAsymmErrors *gr = new TGraphAsymmErrors(npts);
  ogr->TAttMarker::Copy(*gr);
  ogr->TAttLine::Copy(*gr);
  ogr->TAttFill::Copy(*gr);
  gr->SetName(ogr->GetName());

  for (int i=0; i<npts; i++) {
    Double_t ex1=0,ex2=0,ey1=0,ey2=0;
    ogr->GetPoint(i,x,y);
    Q2=x;
    if (ogrE) {
      ex1 = ogrE->GetErrorXlow(i);
      ex2 = ogrE->GetErrorXhigh(i);
      ey1 = ogrE->GetErrorYlow(i);
      ey2 = ogrE->GetErrorYhigh(i);
    }
    Gd = gdipole(&Q2,0);
    y /= Gd;
    ey1 /= Gd;
    ey2 /= Gd;
    gr->SetPoint(i,x,y);
    gr->SetPointError(i,ex1,ex2,ey1,ey2);
  }
  return gr;
}


void gen5() {
  gROOT->SetStyle("HALLA");
  TCanvas *cn = new TCanvas("cn");
  cn->Draw();
  cn->UseCurrentStyle();
  TH1F *frm = new TH1F("frm","",100,0.,10.);
  frm->GetXaxis()->SetTitle("Q^{2}  [GeV^{2}]");
  frm->GetYaxis()->SetTitle("G_{E}^{n}/Gd");
  frm->SetMinimum(-.1);
  frm->SetMaximum(1.);
  frm->UseCurrentStyle();
  frm->Draw();
  frm->SetAxisRange(0.,5.,"X");

  TF1* galstergd = new TF1("galstergd",
			 "(1.+x/.71)*(1.+x/.71)*x/(4.*0.938*.938)*1.91/(1.+x/.71)^2/(1.+5.6*x/(4.*.938*.938))",
			 0.,4.);
  galstergd->SetLineColor(6);
  galstergd->SetLineStyle(3);
  galstergd->SetLineWidth(2);


  TF1 *genf = new TF1("genf",genff,1.,10.,1);
  genf->SetLineColor(2);
  genf->SetLineStyle(2);
  genf->SetParameter(0,1.);
  // match to Madey point just below 1.5
  // genf->SetParameter(0,.0411/genf->Eval(1.45));
  genf->SetParameter(0,-0.558645);

  TF1 *bbba05 = new TF1("BBBA05",gen_bbba05,0.,10.,0);
  bbba05->SetLineColor(7);
  bbba05->SetLineStyle(3);

 
  TMultiGraph* mgrDta = new TMultiGraph("Data","G_{E}^{n}/Gd");
  TLegend *legDta = new TLegend(.54,.6,.875,.90,"","brNDC");

  TMultiGraph* wgr = mgrDta;
  TLegend *wlg = legDta;

   // the data
  legDta->SetBorderSize(0); // turn off border
  legDta->SetFillStyle(0);
  
  datafile_t *f = datafiles;
  TGraph* gr=0;
  TGraph* ogr=0;
  while ( f && f->filename ) {
    ogr=OneGraph(f);
    if (ogr) {
      gr=fromGEntoGEnGd(ogr);
      if (f->lnpt) {
	mgrDta->Add(gr,f->lnpt);
	legDta->AddEntry(gr,f->label,f->lnpt);
      }
      else if (gr->GetMarkerStyle()>=20) {
	mgrDta->Add(gr,"p");
	legDta->AddEntry(gr,f->label,"p");
      }	
      else {
	mgrDta->Add(gr,"l");
	legDta->AddEntry(gr,f->label,"l");
      }
    }
    f++;
  }
    

  mgrDta->Draw("p");
  //  legDta->Draw();   don't draw the data legend
  
  TMultiGraph* mgrThry = new TMultiGraph("Theory","G_{E}^{n}/Gd");
  TLegend *legThry = new TLegend(.54,.6,.875,.9,"","brNDC");

  wgr = mgrThry;
  wlg = legThry;

  // the theory
  wlg->SetBorderSize(0); // turn off border
  wlg->SetFillStyle(0);
  
  f = theoryfiles1;
  ogr=0;
  gr=0;
  while ( f && f->filename ) {
    ogr=OneGraph(f);
    if (ogr) {
      gr=fromGEntoGEnGd(ogr);
      TGraphAsymmErrors *egr = dynamic_cast<TGraphAsymmErrors*>(gr);
      if (egr && egr->GetN()>1 && egr->GetEYhigh() && egr->GetEYhigh()[1]>0) {
	gr = toerror_band(egr);
	gr->SetFillStyle(3000+f->style);
      }
      if (f->lnpt) {
	wgr->Add(gr,f->lnpt);
	wlg->AddEntry(gr,f->label,f->lnpt);
      }
      else if (gr->GetMarkerStyle()>=20) {
	wgr->Add(gr,"p");
	wlg->AddEntry(gr,f->label,"p");
      }	
      else {
	wgr->Add(gr,"l");
	wlg->AddEntry(gr,f->label,"l");
      }
    }
    f++;
  }

  genf->Draw("same");
  mgrThry->Draw("c");
  galstergd->Draw("same");
  bbba05->Draw("same");
  legThry->AddEntry(genf,"F_{2}/F_{1} #propto ln^{2}(Q^{2}/#Lambda^{2})/Q^{2}","l");
  legThry->AddEntry(galstergd,"Galster fit","l");
  legThry->AddEntry(bbba05,"BBBA05","l");
  legThry->Draw();
  legDta->Draw();
  
  // draw a line at 1
  cn->Modified();

  cn->Update();
  cn->SaveAs(Form("%s.eps",psfile));
  cn->SaveAs(Form("%s.root",psfile));
  gSystem->Exec(Form("./replace_symbols.pl %s.eps",psfile));

  return;  // LEAVING HERE
}
