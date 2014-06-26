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

const char* psfile = "long_EPR";

using namespace std;

datafile_t datafiles[] = {
//{ "data file.day", "Data Name", "Q2", "EPR", "Error Up", "Error Down", ?, ?, Shape, Color}
//  { "epr_datafiles/epr_vert.dat", "Vertical", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,4 },
//  { "epr_datafiles/epr_long.dat", "Longitudinal", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,1 },
//  { "epr_datafiles/epr_trans.dat", "Transverse", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,2 },
  { "epr_datafiles/epr_vert_days.dat", "Vertical", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,4 },
  { "epr_datafiles/epr_long_days.dat", "Longitudinal", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,1 },
  { "epr_datafiles/epr_trans_days.dat", "Transverse", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,2 },
  { NULL }
};  

datafile_t theoryfiles1[] = {
  //  { "figure_input/Lattice/ffrng_all.dat", "Lattice", "[0]", "[10]", "[10]-[11]", "[12]-[10]", 0, 0, 1, 1, "F" },
  //  { "figure_input/Iachello/formfactor_10GeV.dat.2", "Iachello", "[0]", "[5]", "0", "0", 0, 0, 1, 1 },
  // { "figure_input/Bijker/spaceff.kees",             "Bijker",   "[0]", "[3]", "0", "0", 0, 0, 1, 4 },
  //  { "figure_input/Holzwarth/gen.dat.2",          "Holzwarth",   "[0]", "[1]", "0", "0", 0, 0, 2, 3 },
  //  { "figure_input/Hammer/genthf4.dat",              "Hammer",   "[0]", "[1]", "0", "0", 0, 0, 2, 4 },
  //  { "figure_input/Miller/GEn.dat.spl3",             "Miller",   "[0]", "[1]", "0", "0", 0, 0, 1, 3 },
  // { "figure_input/Miller/GEn.qonly.dat.spl3",       "Miller (q-only)",  "[0]", "[1]", "0", "0", 0, 0, 4, 4 },
  //  { "figure_input/Miller/lattice.GEn.rtf","Miller Lattice",
  //    "[0]","[1]","[1]-[3]","[2]-[1]",0,0,1,3,"F" },
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

void long_EPR() {
  gROOT->SetStyle("HALLA");
  TCanvas *cn = new TCanvas("cn","cn",540,270);
  cn->Draw();
  cn->UseCurrentStyle();
//  TH1F *frm = new TH1F("EPR","",100,2009.0422,2009.0605);
  TH1F *frm = new TH1F("EPR","",10000,1,50);
  frm->SetStats(kFALSE);
//  frm->GetXaxis()->SetTitle("Date");
  frm->GetXaxis()->SetTitle("# of Days with 1=2009/04/15");
  frm->GetYaxis()->SetTitle("Polarization   (%)");
  frm->SetMinimum(10);
  frm->SetMaximum(70);
  frm->UseCurrentStyle();
  frm->Draw();
//  frm->SetAxisRange(20090422,20090507,"X");

//  TF1* galster = new TF1("galster","x/(4.*0.938*.938)*1.91/(1.+x/.71)^2/(1.+5.6*x/(4.*.938*.938))",0.,4.);
//  galster->SetLineColor(6);
//  galster->SetLineStyle(3);
//  galster->SetLineWidth(2);


/*  TF1 *genf = new TF1("genf",genff,1.,10.,1);
  genf->SetLineColor(2);
  genf->SetLineStyle(2);
  genf->SetParameter(0,1.);
  // match to Madey point just below 1.5
  // genf->SetParameter(0,.0411/genf->Eval(1.45));
  genf->SetParameter(0,-0.558645);

  TF1 *bbba05 = new TF1("BBBA05",gen_bbba05,0.,10.,0);
  bbba05->SetLineColor(7);
  bbba05->SetLineStyle(3);
*/
  
  TMultiGraph* mgrDta = new TMultiGraph("Data","G_{E}^{n}");
  TLegend *legDta = new TLegend(.7,.2,.875,.35,"","brNDC");

  TMultiGraph* wgr = mgrDta;
  TLegend *wlg = legDta;

   // the data
  legDta->SetBorderSize(1); // turn off border
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
  //  legDta->Draw();   don't draw the data legend
  
  TMultiGraph* mgrThry = new TMultiGraph("Theory","G_{E}^{n}");
  TLegend *legThry = new TLegend(.54,.6,.875,.9,"","brNDC");

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
//  mgrThry->Draw("c");
//  galster->Draw("same");
//  bbba05->Draw("same");
//  legThry->AddEntry(genf,"F_{2}/F_{1} #propto ln^{2}(Q^{2}/#Lambda^{2})/Q^{2}","l");
//  legThry->AddEntry(galster,"Galster fit","l");
//  legThry->AddEntry(bbba05,"BBBA05","l");
//  legThry->Draw();
  legDta->Draw();
  
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
    gr->SetLineStyle(1);
    gr->SetFillColor(gr->GetLineColor());
    gr->SetFillStyle(3000+miller.style);
  }
  
  gr->Draw("F");

  cn->Update();
  cn->SaveAs("gen_Miller_Overlay.eps");
  cn->SaveAs("gen_Miller_Overlay.root");
  
}
