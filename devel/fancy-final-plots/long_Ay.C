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

const char* psfile = "long_Ay";

using namespace std;

datafile_t datafiles[] = {
//{ "data file.dat", "Data Name", "Q2", "Ay", "Error Up", "Error Down", ?, ?, Shape, Color}
  { "asym_datafiles/Ay_NIKHEF.dat", "NIKHEF", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,26,9 },
  { "asym_datafiles/Ay_MAMI.dat", "MAMI", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,25,4 },
  { "asym_datafiles/Ay_Long.dat", "E08-005", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,6 },
  { "asym_datafiles/Ay_for_fit.dat", "World Data", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,6 },
//  { "asym_datafiles/Ay_fit_MAMI_NIKHEF.dat", "MAMI+NIKHEF", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,6 },
//  { "asym_datafiles/Ay_Long_raw.dat", "E08-005", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,6 },
  { NULL }
};  

datafile_t theoryfiles1[] = {
//{ "theory file.txt", "Data Name", "Q2 (Include range in theory file)", "Ay", "Error Up", "Error Down", ?, ?, 2, 3 },
  { "asym_theory/mami_ay_theory_full.txt", "FSI and MEC (Faddeev)", "[0]", "[1]", "0", "0", 0, 0, 2, 3 },
  { "asym_theory/mami_ay_theory_noMEC.txt", "FSI (Faddeev)", "[0]", "[1]", "0", "0", 0, 0, 1, 2 },
  { "asym_theory/nikhef_ay_theory.txt", "FSI (Faddeev)", "[0]", "[1]", "0", "0", 0, 0, 1, 2 },
  { "asym_theory/laget_original.txt", "Laget Original", "[0]", "[1]", "0", "0", 0, 0, 4, 1 },
  { NULL }
};

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
  return gm*muGe_Gm/(ch+kappa);
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
  return gm*muGe_Gm/(ch+kappa);
}

/*
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
  return top/bot;
}
*/

void long_Ay() {
  gROOT->SetStyle("HALLA");
  TCanvas *cn = new TCanvas("cn","cn",540,360);
  cn->Draw();
  cn->UseCurrentStyle();
  TH1F *frm = new TH1F("frm","",100,0.003,10.);
  frm->GetXaxis()->SetTitle("Q^{2}  (GeV/c)^{2}");
//  gPad->SetLogy();
  frm->GetYaxis()->SetTitle("A_{y}^{0}");
//  frm->SetMinimum(-.02);
  frm->SetMinimum(0);
  frm->SetMinimum(0.001);
  frm->SetMaximum(1.5);
//  frm->SetMaximum(0.04);
  frm->UseCurrentStyle();
  frm->Draw();
  frm->SetAxisRange(0.,1.1,"X");
//  frm->SetAxisRange(0.5,1.1,"X");

//  TF1* galster = new TF1("galster","x/(4.*0.938*.938)*1.91/(1.+x/.71)^2/(1.+5.6*x/(4.*.938*.938))",0.,4.);
//  galster->SetLineColor(6);
//  galster->SetLineStyle(3);
//  galster->SetLineWidth(2);


  TF1 *genf = new TF1("genf",genff,1.,10.,1);
  genf->SetLineColor(2);
  genf->SetLineStyle(2);
  genf->SetParameter(0,1.);
  // match to Madey point just below 1.5
  // genf->SetParameter(0,.0411/genf->Eval(1.45));
  genf->SetParameter(0,-0.558645);

//  TF1 *bbba05 = new TF1("BBBA05",gen_bbba05,0.,10.,0);
//  bbba05->SetLineColor(7);
//  bbba05->SetLineStyle(3);

  
  TMultiGraph* mgrDta = new TMultiGraph("Data","G_{E}^{n}");
  TLegend *legDta = new TLegend(.54,.6,.875,.90,"","brNDC");

  TMultiGraph* wgr = mgrDta;
  TLegend *wlg = legDta;

   // the data
  legDta->SetBorderSize(0); // turn off border
  legDta->SetFillStyle(0);
  
  datafile_t *f = datafiles;
  TGraph* gr=0;
  while ( f && f->filename ) {
    gr=OneGraph(f);
    if (gr) {
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
  legDta->Draw();
  TF1 *theFit = new TF1("theFit","expo");
//  theFit->SetParameter(2,0.1);
  gr->Fit(theFit);
  theFit->Draw("same");  
  TMultiGraph* mgrThry = new TMultiGraph("Theory","G_{E}^{n}");
  TLegend *legThry = new TLegend(.54,.3,.875,.6,"","brNDC");

  wgr = mgrThry;
  wlg = legThry;

  // the theory
  wlg->SetBorderSize(0); // turn off border
  wlg->SetFillStyle(0);
  
  f = theoryfiles1;
  gr=0;
  while ( f && f->filename ) {
    gr=OneGraph(f);
    if (gr) {
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

//  genf->Draw("same");
  mgrThry->Draw("c");
//  galster->Draw("same");
//  bbba05->Draw("same");
//  legThry->AddEntry(genf,"F_{2}/F_{1} #propto ln^{2}(Q^{2}/#Lambda^{2})/Q^{2}","l");
//  legThry->AddEntry(galster,"Galster fit","l");
//  legThry->AddEntry(bbba05,"BBBA05","l");
  legThry->Draw();
//  legDta->Draw();
  
  // draw a line at 1
  cn->Modified();

  cn->Update();
  cn->SaveAs(Form("%s.eps",psfile));
  cn->SaveAs(Form("%s.root",psfile));
  gSystem->Exec(Form("./replace_symbols.pl %s.eps",psfile));

  return;  // LEAVING HERE

  // now an overlay, hopefully matching dimensions

  // remove everything but the graph
  cn->Update();
  TList *clist = cn->GetListOfPrimitives();
  TFrame* frame = cn->GetFrame();
  for (int i=0; i<clist->GetSize(); ) {
    if (clist->At(i) != frame) {
      clist->RemoveAt(i);
    } else i++;
  }
  // draw markers in the corners
  TMarker *mkr = new TMarker(frame->GetX1(),frame->GetY1(),2);
  mkr->Draw();
  mkr = new TMarker(frame->GetX2(),frame->GetY1(),2);
  mkr->Draw();
  mkr = new TMarker(frame->GetX1(),frame->GetY2(),2);
  mkr->Draw();
  mkr = new TMarker(frame->GetX2(),frame->GetY2(),2);
  mkr->Draw();
  frame->SetLineColor(10);
  cn->Update();

  datafile_t miller = { "figure_input/Miller/lattice.GEn.rtf","Miller",
			"[0]","[1]","[1]-[3]","[2]-[1]",0,0,1,3,"F" };

  gr = OneGraph(&miller);
  TGraphAsymmErrors* egr = dynamic_cast<TGraphAsymmErrors*>(gr);
  if (egr && egr->GetEYhigh() && egr->GetEYhigh()[egr->GetN()/2]>0) {
    gr = toerror_band(egr);
    gr->SetFillStyle(3000+miller.style);
  }
  
  gr->Draw("F");

  cn->Update();
  cn->SaveAs("gen_Miller_Overlay.eps");
  cn->SaveAs("gen_Miller_Overlay.root");
  
}
