#include <cstring>
#include <TGraphAsymmErrors.h>
#include <cstdio>
#include <cstdlib>
#include <TPaveLabel.h>
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
#include "add_theory.h"

#define PRELIMINARY

const char* psfile = "galster_riordan";

using namespace std;

datafile_t datafiles[] = {
  // MIT - Bates
//  { "formfactor_datafiles/GEn_Eden.dat", "Eden", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 23,kBlue },

  // NIKHEF
  { "formfactor_datafiles/GEn_Passchier.dat", "Passchier", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 29,kBlue },
 // Corrected by Golak
  // MAMI - Deuterium Polarization
  { "formfactor_datafiles/GEn_Herberg.dat", "Herberg", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,23,1 },
  { "formfactor_datafiles/GEn_Ostrick.dat", "Ostrick", "[0]", "[1]", "sqrt([2]*[2]+[4]*[4])", "sqrt([2]*[2]+[3]*[3])", 0,0,29,1 },


  { "formfactor_datafiles/GEn_Madey.dat", "Madey", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,22,2 },
  // PhD Thesis - MAINZ - Replaced by Glazier
//  { "formfactor_datafiles/GEn_Seimetz.dat", "Seimetz", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,1 },

  // A1 Collaboration - arXiv:nucl-ex/0410026
  { "formfactor_datafiles/GEn_Glazier.dat", "Glazier", "[0]", "[1]", "[2]", "[2]", 0,0,27,1 },
  
  // Replaces Zhu - E93-026
  { "formfactor_datafiles/GEn_Warren.dat", "Warren", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,21,2 },

  // MAMI - 3He Polarization
  { "formfactor_datafiles/GEn_Meyerhoff.dat", "Meyerhoff", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,2 },
  { "formfactor_datafiles/GEn_Becker.dat", "Becker", "[0]", "[1]", "[2]","[2]", 0,0,25,1 }, // Corrected by Golak
  { "formfactor_datafiles/GEn_Bermuth.dat", "Bermuth", "[0]", "[1]", "[2]", "[2]", 0,0,24,1 },


  // d(e,e')p - No polarization observables  (Huge error bars)
//  { "formfactor_datafiles/GEn_Lung.dat", "Lung", "[0]", "[1]", "[2]", "[2]", 0,0,28,5 },
 // { "formfactor_datafiles/GEn_Hanson.dat", "Hanson", "[0]", "[1]", "[2]", "[2]", 0,0,30,1 },

 // { "e02013_results.dat", "x","[0]","[1]","[2]","[2]",0,0,26,2},
  //{ "e02013_results.dat", "This Work","[0]","[1]","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,26,2},
  //  { "madey_proposal.dat", "E04-110 (proj)", "[0]", "0", "0.002", "0.002", 0, 0, 28, 2},
  { NULL }
};  

datafile_t theoryfiles1[] = {
  //  { "figure_input/Lattice/ffrng_all.dat", "Lattice", "[0]", "[10]", "[10]-[11]", "[12]-[10]", 0, 0, 1, 1, "F" },
  //  { "figure_input/Iachello/formfactor_10GeV.dat.2", "Iachello", "[0]", "[5]", "0", "0", 0, 0, 1, 1 },
  // { "figure_input/Bijker/spaceff.kees",             "Bijker",   "[0]", "[3]", "0", "0", 0, 0, 1, 4 },
  //  { "figure_input/Holzwarth/gen.dat.2",          "Holzwarth",   "[0]", "[1]", "0", "0", 0, 0, 2, 3 },
  //  { "figure_input/Hammer/genthf4.dat",              "Hammer",   "[0]", "[1]", "0", "0", 0, 0, 2, 4 },
  //{ "figure_input/Lomon/gen.dat.2",              "Lomon",   "[0]", "[1]", "0", "0", 0, 0, 2, 4 },
  //{ "figure_input/Miller/GEn.dat.spl3",             "Miller",   "[0]", "[1]", "0", "0", 0, 0, 1, 3 },
  //{ "figure_input/Miller/GEn.qonly.dat.spl3",       "Miller (q-only)",  "[0]", "[1]", "0", "0", 0, 0, 4, 4 },
  //  { "figure_input/Miller/lattice.GEn.rtf","Miller Lattice",
  //    "[0]","[1]","[1]-[3]","[2]-[1]",0,0,1,3,"F" },
  { NULL }
};

Double_t genff(Double_t *x, Double_t *p) {
  Double_t Q2=x[0];

  Double_t scl;

  Double_t tau=Q2/(4*.939565*.939565);
  Double_t ch=0.;
  Double_t kappa=-1.91;
  Double_t lambda = .3; // GeV, lambda = 300 MeV
  Double_t L2 = .71;

  
  // Just calculate scl from a GEn point
  Double_t fixedGEn = 0.011687;
  Double_t fixedQ2  = 3.47;
  Double_t fixedgm  = (ch+kappa)/(1+fixedQ2/L2)/(1+fixedQ2/L2);
  Double_t fixedtau = fixedQ2/(4.0*0.938*0.938);
  Double_t gm       = (ch+kappa)/(1+Q2/L2)/(1+Q2/L2);

  Double_t fixedR = pow(TMath::Log(fixedQ2/(lambda*lambda)),2.0)/fixedQ2;
  Double_t R = pow(TMath::Log(Q2/(lambda*lambda)),2.0)/Q2;

  scl = (1.0 - fixedGEn/fixedgm)/((fixedGEn/fixedgm+fixedtau)*fixedR); 

  Double_t f2f1 = scl*R;

  Double_t Ge_Gm = (1-tau*f2f1)/(1+f2f1);

  // now multiply by the dipole form factor to get ge for neutron
  
  return gm*Ge_Gm;
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

void galster_riordan() {
  gROOT->SetStyle("HALLA");
  TCanvas *cn = new TCanvas("cn");
  cn->Draw();
  cn->UseCurrentStyle();
  TH1F *frm = new TH1F("frm","",100,0.,10.);
  frm->GetXaxis()->SetTitle("Q^{2}  [GeV^{2}]");
  frm->GetYaxis()->SetTitle("G_{E}^{n}");
  frm->SetMinimum(-.02);
  frm->SetMaximum(0.1);
  frm->UseCurrentStyle();
  frm->Draw();
  frm->SetAxisRange(0.,5.,"X");

  TF1* galster = new TF1("galster",
			 "x/(4.*0.938*.938)*1.91/(1.+x/.71)^2/(1.+5.6*x/(4.*.938*.938))",
			 0.,4.);
  galster->SetLineColor(6);
  galster->SetLineStyle(3);
  galster->SetLineWidth(2);


  TF1 *genf = new TF1("genf",genff,0.,10.,1);
  genf->SetLineColor(2);
  genf->SetLineStyle(2);
  genf->SetParameter(0,1.);
  // match to Madey point just below 1.5
  // genf->SetParameter(0,.0411/genf->Eval(1.45));
//  genf->SetParameter(0,-0.558645);
  genf->SetParameter(0,-0.182645);

  TF1 *bbba05 = new TF1("BBBA05",gen_bbba05,0.,10.,0);
  bbba05->SetLineColor(kRed);
  bbba05->SetLineStyle(3);

//  TF1 *lomon = new TF1("Lomon",Lomon_GEn,0.,10.,0);
 // lomon->SetLineColor(7);
 // lomon->SetLineStyle(4);
 
  TF1 *bandi = new TF1("Bijker and Iachello", Bijker_GEn,0.,10.,0);
  bandi->SetLineColor(kRed);
  bandi->SetLineStyle(4);


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
			  if( f->label[0] != 'x' )
				  legDta->AddEntry(gr,f->label,f->lnpt);
		  }
		  else if (gr->GetMarkerStyle()>=20) {
			  mgrDta->Add(gr,"p");
			  if( f->label[0] != 'x' )
				  legDta->AddEntry(gr,f->label,"p");
		  }	
		  else {
			  mgrDta->Add(gr,"l");
			  if( f->label[0] != 'x' )
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
  galster->Draw("same");
 // bbba05->Draw("same");
  //lomon->Draw("same");
  //bandi->Draw("same");
//  legThry->AddEntry(genf,"F_{2}/F_{1} #propto ln^{2}(Q^{2}/#Lambda^{2})/Q^{2}","l");
  legThry->AddEntry(galster,"Galster fit","l");
//  legThry->AddEntry(bbba05,"BBBA05","l");
//  legThry->AddEntry(lomon, "Lomon", "l");
//  legThry->AddEntry(bandi, "Bijker and Iachello", "l");
  legThry->Draw();
  legDta->Draw();

  return;

  TPaveLabel *prelim = new TPaveLabel( 0.0632, 0.269, 0.984, 0.699, "PRELIMINARY", "NDC" );
  prelim->SetTextAngle(30);
  prelim->SetTextColor(kRed);
  prelim->SetFillStyle(0);
  prelim->SetBorderSize(0);

#ifdef PRELIMINARY
  prelim->Draw("same");
#endif

  // draw a line at 1
  cn->Modified();

  cn->Update();
//  cn->SaveAs(Form("%s.pdf",psfile));
//  cn->SaveAs(Form("%s.root",psfile));
  //  gSystem->Exec(Form("./replace_symbols.pl %s.eps",psfile));

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
	  cn->SaveAs("gen_Miller_Overlay.pdf");
	  cn->SaveAs("gen_Miller_Overlay.root");

}
