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
#include <TMath.h>

#include "halla_plotting.h"

#define PQCD
#define DIFF_LAB

using namespace std;

const char* psfile = "riordan_gepgmp";


datafile_t datafiles[] = {
  //  { "FFR_Andivahis.dat", "Andivahis", "[0]", "[1]", "[5]", "[4]" },
  //    { "FFR_Bartel.dat", "Bartel", "[0]", "[1]", "[2]", "[2]" },
  //    { "FFR_Berger.dat", "Berger", "[0]", "[1]", "[2]", "[2]" },
  //{ "formfactor_datafiles/FFR_Milbrath_p.dat", "Milbrath",   "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 29, 1 },
  //{ "formfactor_datafiles/FFR_Pospischil.dat", "Pospischil",   "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 22, 1 },
  { "formfactor_datafiles/FFR_Punjabi.dat",   "Punjabi",   "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 21, kBlack },
  //{ "formfactor_datafiles/FFR_Dieterich2.dat", "Dieterich", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 20, 1 },
  { "formfactor_datafiles/FFR_Gayou.dat",      "Gayou",        "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 23, 2 },
  { "formfactor_datafiles/FFR_GEpIII.dat",      "GEp-III",        "[0]", "2.79*[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 20, kGreen },
  { "formfactor_datafiles/FFR_SHMS.dat",      "SHMS PAC34",        "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 25, kBlue },
  { "formfactor_datafiles/FFR_GEpV.dat",      "GEp-V",        "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 20, kRed },
  //    { "FFR_Gayou2.dat",      "Gayou2",        "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])" },
  //  { "e04108_proposal.dat", "E04-108 (proj)", "[0]", "[1]", "[2]", "[2]", 0,0, 24, 2 },
  { 0 }
};

datafile_t rosenbluth_files[] = {
  { "formfactor_datafiles/FFR_Janssens.dat", "Janssens", "[0]", "[1]", "[2]", "[2]",0,0,24,3 },
  { "formfactor_datafiles/FFR_Bartel.dat", "Bartel", "[0]", "[1]", "[2]", "[2]",0,0,25,3 },
  { "formfactor_datafiles/FFR_Litt2.dat", "Litt", "[0]", "[1]", "[2]", "[2]",0,0,26,3 },
  { "formfactor_datafiles/FFR_Berger2.dat", "Berger", "[0]", "[1]", "[2]", "[2]",0,0,27,3 },
  { "formfactor_datafiles/FFR_Walker2.dat", "Walker", "[0]", "[1]", "[2]", "[2]",0,0,28,3 },
  { "formfactor_datafiles/FFR_Andivahis.dat", "Andivahis", "[0]", "[1]", "[5]", "[4]",0,0,30,3 },
  { NULL }
};


datafile_t newrosenfiles[] = {
  { "formfactor_datafiles/newrosen.dat", "Arrington","[0]","[1]","[2]","[2]", 0,0, 24},
  { "formfactor_datafiles/HallC_Christy.dat", "Christy", "[0]", "[5]", "[6]", "[6]", 0,0, 26+3*11 },
  { "formfactor_datafiles/FFR_Segel.dat", "Segel", "[0]", "[1]", "[3]", "[3]", 0,0, 25+1*11},
  { NULL }
};

datafile_t theoryfiles1[] = {
/*  { "figure_input/Lattice/ffrng_all.dat", "Lattice", "[0]", "2.79*[7]/[1]", 
    "2.79*[7]/[1]*sqrt(pow(.5*([9]-[8]),2)/([7]*[7])+pow(.5*([3]-[2]),2)/([1]*[1]))",
    "2.79*[7]/[1]*sqrt(pow(.5*([9]-[8]),2)/([7]*[7])+pow(.5*([3]-[2]),2)/([1]*[1]))",
    0,0, 1,1, "F" },
  //  { "figure_input/Iachello/formfactor_10GeV.dat.2", "Iachello", "[0]", "[1]", "0", "0", 0,0, 1,1 },
  { "figure_input/Bijker/spaceff.kees", "Bijker", "[0]", "[1]/[2]", "0", "0", 0,0, 1, 4 },
  { "figure_input/Holzwarth/mup-gep-gmp.dat.2", "Holzwarth", "[0]", "[1]", "0", "0", 0,0, 2, 3 },
  { "figure_input/Hammer/mup-gep-gmp.dat", "Hammer", "[0]", "[3]", "0", "0", 0,0, 2, 4 },
  */
 { "figure_input/Miller/mup_GEp_GMp.dat.spl3", "CQM - Miller", "[0]", "[1]", "0", "0", 0,0, 1, 3 },
  { "figure_input/Lomon/mup-gep-gmp.dat.2", "VMD - Lomon (2002)", "[0]", "[1]", "0", "0", 0,0, 9, kBlue },
//  { "figure_input/Roberts/gepgmp.dat", "Roberts", "[0]", "[1]", "0", "0", 0,0, 3, 4 },
  { "figure_input/Null", "x", "[0]", "[1]", "0", "0", 0,0, 3, 4 },
  
  { NULL }
};

Double_t fff(Double_t *x, Double_t *p) {
  Double_t Q2=*x;
  Double_t scl=p[0];
  Double_t tau=Q2/(4*.938272*.938272);
  Double_t ch=1.;
  Double_t kappa=1.79;
  Double_t lambda = .3; // GeV, lambda = 300 MeV
  Double_t L2 = .71;
  Double_t f2f1 = scl*TMath::Log(Q2/(lambda*lambda))*TMath::Log(Q2/(lambda*lambda))/Q2;
  Double_t muGe_Gm = (ch+kappa)*((1-tau*kappa*f2f1)/(1+kappa*f2f1));

  return muGe_Gm;
}

Double_t fffq2(Double_t *x, Double_t *p) {
  Double_t Q2=*p;
  Double_t scl=x[0];
  Double_t tau=Q2/(4*.938272*.938272);
  Double_t ch=1.;
  Double_t kappa=1.79;
  Double_t lambda = .3; // GeV, lambda = 300 MeV
  Double_t L2 = .71;
  Double_t f2f1 = scl*TMath::Log(Q2/(lambda*lambda))*TMath::Log(Q2/(lambda*lambda))/Q2;
  Double_t muGe_Gm = (ch+kappa)*((1-tau*kappa*f2f1)/(1+kappa*f2f1));

  return muGe_Gm;
}

void riordan_gepgmp() {
  gROOT->SetStyle("HALLA");
  TCanvas *cn = new TCanvas("cn");
  cn->Draw();
  TH1F *frm = new TH1F("frm","",100,0.,16.);
#ifndef DIFF_LAB
  frm->GetXaxis()->SetTitle("Q^{2}  [GeV^{2}]");
#endif
#ifdef DIFF_LAB
  frm->GetXaxis()->SetTitle("Q^{2} in GeV^{2}");
#endif

  frm->GetXaxis()->CenterTitle();
#ifndef DIFF_LAB
  frm->GetYaxis()->SetTitle("#mu_{p} G_{E}^{p}/G_{M}^{p}");
#endif
#ifdef DIFF_LAB
  frm->GetYaxis()->SetTitle("#muG_{Ep}/G_{Mp}");
#endif
  frm->GetYaxis()->CenterTitle();
  frm->SetMinimum(-0.5);
  frm->SetMaximum(1.0);
  frm->UseCurrentStyle();
  frm->Draw();

  TF1 *ff = new TF1("ff",fff,1.,10.,1.);
  ff->SetLineColor(2);
  ff->SetLineStyle(2);
  ff->SetParameter(0,1.);
  ff->SetParameter(1,.3);
  // match to Gayou point at 5.54 GeV^2
  ff->SetParameter(0,.1035);

  
  TMultiGraph* mgrDta = new TMultiGraph("Data","#frac{#mu_{p}G_{E}^{p}}{G_{M}^{p}}");
  //TLegend *legDta = new TLegend(.58,.565,.875,.9,"","brNDC");
  TLegend *legDta = new TLegend(.648,.682,.945,.900,"","brNDC");

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
 	gr->SetLineWidth(2);
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
   legDta->Draw();//   don't draw the data legend
  
  TMultiGraph* mgrThry = new TMultiGraph("Theory","#frac{#mu_{p}G_{E}^{p}}{G_{M}^{p}}");
//  TLegend *legThry = new TLegend(.585,.6,.9,.9,"","brNDC");
  TLegend *legThry = new TLegend(.335,.689,.649,.911,"","brNDC");

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
      if (egr && egr->GetEYhigh() && egr->GetEYhigh()[0]>0) {
	gr = toerror_band(egr);
	gr->SetFillStyle(3000+f->style);
      }
      gr->SetLineWidth(2);
      if (f->lnpt) {
		      wgr->Add(gr,f->lnpt);
	      if( f->label[0] != 'x' ){
		      wlg->AddEntry(gr,f->label,f->lnpt);
	      }
      }
      else if (gr->GetMarkerStyle()>=20) {
		      wgr->Add(gr,"p");
	      if( f->label[0] != 'x' ){
		      wlg->AddEntry(gr,f->label,"p");
	      }
      }	
      else {
		      wgr->Add(gr,"l");
	      if( f->label[0] != 'x' ){
		      wlg->AddEntry(gr,f->label,"l");
	      }
      }
    }
    f++;
  }

  mgrThry->Draw("c");
#ifdef PQCD
  ff->Draw("same");
  legThry->AddEntry(ff,"F2/F1 #propto ln^{2}(Q^{2}/#Lambda^{2})/Q^{2}","l");
#endif// PQCD
  legThry->Draw();



  cn->Modified();
  cn->Update();
  TFrame* frame = gPad->GetFrame();

  // draw a line at 1
  TLine *line1 = new TLine(frame->GetX1(),1.,frame->GetX2(),1.);
  line1->SetLineStyle(1);
  line1->Draw();

  return;
  cn->Update();
  cn->SaveAs(Form("%s.eps",psfile));
  cn->SaveAs(Form("%s.root",psfile));
  gSystem->Exec(Form("./replace_symbols.pl %s.eps",psfile));

  // now an overlay, hopefully matching dimensions
  // remove everything except the frame
  cn->Update();
  TList *clist = cn->GetListOfPrimitives();
  frame = cn->GetFrame();
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


  {
	  datafile_t goeckeler = { "figure_input/Goeckeler/goeckeler.dat","Goeckeler",
		  "[0]","[1]","[1]-[2]","[3]-[1]",0,0,1,4,"F" };

	  gr = OneGraph(&goeckeler);
	  TGraphAsymmErrors *egr = dynamic_cast<TGraphAsymmErrors*>(gr);
	  if (egr && egr->GetEYhigh() && egr->GetEYhigh()[egr->GetN()/2]>0) {
		  gr = toerror_band(egr);
		  gr->SetLineStyle(1);
		  gr->SetFillColor(gr->GetLineColor());
		  gr->SetFillStyle(3000+goeckeler.style);
	  }

	  gr->Draw("F");
	  cn->Update();
	  cn->SaveAs("mup_gep_gmp_goeckeler_Overlay.eps");
	  cn->SaveAs("mup_gep_gmp_goeckeler_Overlay.root");

	  // remove Goeckeler curve from plot
	  clist->Remove(gr);
  }

  {
	  datafile_t miller = { "figure_input/Miller/lattice.GEp_GMp.rtf","Miller",
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
	  cn->SaveAs("mup_gep_gmp_Miller_Overlay.eps");
	  cn->SaveAs("mup_gep_gmp_Miller_Overlay.root");
	  clist->Remove(gr);
  }
  {
	  datafile_t zanotti = { "figure_input/Zanotti/zanotti_gepgmp.dat","Zanotti",
		  "[0]","[1]","[1]-[2]","[3]-[1]",0,0,1,6,"F" };

	  gr = OneGraph(&zanotti);
	  TGraphAsymmErrors* egr = dynamic_cast<TGraphAsymmErrors*>(gr);
	  if (egr && egr->GetEYhigh() && egr->GetEYhigh()[egr->GetN()/2]>0) {
		  gr = toerror_band(egr);
		  gr->SetLineStyle(1);
		  gr->SetFillColor(gr->GetLineColor());
		  gr->SetFillStyle(3000+zanotti.style);
	  }

	  gr->Draw("F");
	  cn->Update();
	  cn->SaveAs("mup_gep_gmp_Zanotti_Overlay.eps");
	  cn->SaveAs("mup_gep_gmp_Zanotti_Overlay.root");
	  clist->Remove(gr);
  }

}
