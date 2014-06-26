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
#include <TMath.h>
#include <TFrame.h>
#include <TLegend.h>
#include <TMarker.h>
#include <TF1.h>
#include <TSystem.h>
#include <TColor.h>
#include <TEllipse.h>

#include "halla_plotting.h"
#include "add_theory.h"

//#define PRELIMINARY

//#define NOFSI
//#define PLOTKIN1

#define PQCD
#define GALSTER

#define FAKE_SCHIAVILLA

//#define NEW_ROBERTS

//const char* psfile = "gen_riordan";
const char* psfile = "gen_newprop";

using namespace std;

datafile_t datafiles[] = {
  // MIT - Bates
//  { "formfactor_datafiles/GEn_Eden.dat", "Eden", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 23,kBlue },

  // NIKHEF
  { "formfactor_datafiles/GEn_Passchier.dat", "Passchier", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 5,kBlue },
 // Corrected by Golak
  // MAMI - Deuterium Polarization
  { "formfactor_datafiles/GEn_Herberg.dat", "Herberg", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,23,1 },
  { "formfactor_datafiles/GEn_Ostrick.dat", "Ostrick", "[0]", "[1]", "sqrt([2]*[2]+[4]*[4])", "sqrt([2]*[2]+[3]*[3])", 0,0,29,kBlack },


  { "formfactor_datafiles/GEn_Madey.dat", "Madey", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,26,kBlack },
  // PhD Thesis - MAINZ - Replaced by Glazier
//  { "formfactor_datafiles/GEn_Seimetz.dat", "Seimetz", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,1 },

  // A1 Collaboration - arXiv:nucl-ex/0410026
  { "formfactor_datafiles/GEn_Glazier.dat", "Glazier", "[0]", "[1]", "[2]", "[2]", 0,0,27,1 },
  
  // Replaces Zhu - E93-026
  { "formfactor_datafiles/GEn_Warren.dat", "Warren", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,21,kBlue },

  // MAMI - 3He Polarization
  { "formfactor_datafiles/GEn_Meyerhoff.dat", "Meyerhoff", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,kBlue },
  { "formfactor_datafiles/GEn_Becker.dat", "Becker", "[0]", "[1]", "[2]","[2]", 0,0,25,1 }, // Corrected by Golak
  { "formfactor_datafiles/GEn_Bermuth.dat", "Bermuth", "[0]", "[1]", "[2]", "[2]", 0,0,24,1 },
  { "formfactor_datafiles/GEn_Rohe.dat", "Rohe", "[0]", "[1]", "[2]", "[2]", 0,0,3,0 },


  // d(e,e')p - No polarization observables  (Huge error bars)
//  { "formfactor_datafiles/GEn_Lung.dat", "x", "[0]", "[1]", "[2]", "[2]", 0,0,28,kBlue },
//  { "formfactor_datafiles/GEn_Lung.dat", "Lung", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,28,kBlue },
//  { "formfactor_datafiles/GEn_Lung_new.dat", "x", "[0]", "[1]", "[2]", "[2]", 0,0,28,kBlue },
//  { "formfactor_datafiles/GEn_Lung_new.dat", "Lung (Naive Correction)", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,28,kBlue },
 // { "formfactor_datafiles/GEn_Hanson.dat", "Hanson", "[0]", "[1]", "[2]", "[2]", 0,0,30,1 },

//  { "formfactor_datafiles/GEn_Schiavilla.dat", "Schiavilla & Sick", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0, 0, 28, kBlack},
  {"formfactor_datafiles/GEn_Geis.dat", "Geis","[0]","[1]","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,22,kBlue},

// { "e02013_taken.dat", "E02-013, Taken","[0]","0","0","0",0,0,22,2},
#ifndef NOFSI
 //{ "e02013_results.dat", "x","[0]","[1]","[2]","[2]",0,0,22,2},

//  { "e02013_results.dat", "E02-013, This Work","[0]","[1]","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,22,2},
#endif
#ifdef NOFSI
// { "e02013_nofsi.dat", "x","[0]","[1]","[2]","[2]",0,0,22,2},
// {"e02013_nofsi.dat", "E02-013, This Work","[0]","[1]","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,22,2},
#endif

#ifdef PLOTKIN1
  {"e02013_proposal.dat", "x","[0]","0","[2]","[2]",0,0,22,2},
 {"e02013_proposal.dat", "x","[0]","0","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,22,2},
#endif
  //  { "madey_proposal.dat", "E04-110 (proj)", "[0]", "0", "0.002", "0.002", 0, 0, 28, 2},
  { NULL }
};  

datafile_t theoryfiles1[] = {
//{ "figure_input/GEn_Schiavilla.dat", "d(e,e'd) T_{20} - Schiavilla & Sick", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0, 0, 3, kGreen},
//  { "figure_input/DiehlKroll/GEn.dat", "GPD from FF - Diehl et. al.", "[0]", "[1]", "[2]-[1]", "[1]-[3]", 0, 0, 2, kMagenta},
  //  { "figure_input/Lattice/ffrng_all.dat", "Lattice", "[0]", "[10]", "[10]-[11]", "[12]-[10]", 0, 0, 1, 1, "F" },
  //  { "figure_input/Iachello/formfactor_10GeV.dat.2", "Iachello", "[0]", "[5]", "0", "0", 0, 0, 1, 1 },
 //  { "figure_input/Bijker/spaceff.kees",             "VMD - Bijker and Iachello",   "[0]", "[3]", "0", "0", 0, 0, 1, 4 },
  //  { "figure_input/Holzwarth/gen.dat.2",          "Holzwarth",   "[0]", "[1]", "0", "0", 0, 0, 2, 3 },
  //  { "figure_input/Hammer/genthf4.dat",              "Hammer",   "[0]", "[1]", "0", "0", 0, 0, 2, 4 },
//{ "figure_input/Roberts/gen.dat",             "DSE - C. Roberts",   "[0]", "[1]", "0", "0", 0, 0, 2, kRed },
  { "figure_input/Lomon/gen.dat.2",              "VMD - Lomon (2002)",   "[0]", "[1]", "0", "0", 0, 0, 2, 4 },
// { "figure_input/Roberts/gen2.dat",             "q(qq) Faddeev -  I. Cloet, ANL",   "[0]", "[1]", "0", "0", 0, 0, 9, kRed },
// PHYSICAL REVIEW C 66, 045501 (2002)
 { "figure_input/Miller/GEn.dat.spl3",             "CQM - G. Miller",   "[0]", "[1]", "0", "0", 0, 0, 1, kRed },
//  { "figure_input/Miller/GEn.qonly.dat.spl3",       "Miller (q-only)",  "[0]", "[1]", "0", "0", 0, 0, 4, 4 },
  //  { "figure_input/Miller/lattice.GEn.rtf","Miller Lattice",
  //    "[0]","[1]","[1]-[3]","[2]-[1]",0,0,1,3,"F" },
  { "figure_input/Null",       "x",  "[0]", "[1]", "0", "0", 0, 0, 1, 1 },
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
  // Kin 3:
//  Double_t fixedGEn = 0.011687;
//  Double_t fixedQ2  = 3.47;
//
  // Kin 4:
  //Our kinr
//  Double_t fixedGEn = 0.0343;
//  Double_t fixedQ2  = 1.71;

  //Double_t fixedGEn = 0.0317;
  //Double_t fixedQ2  = 1.72;
//  
//Madey
  Double_t fixedGEn = 0.0411;
  Double_t fixedQ2  = 1.45;

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

Double_t gen_ourfit(Double_t *x, Double_t *p){
	Double_t Q2 = x[0];
	Double_t tau = Q2/(4.0*0.939565*0.939565);
	Double_t GD = pow( 1.0 + Q2/0.71, -2.0 );

	Double_t A0 = 1.493;
	Double_t A1 = 0.0;
	Double_t B1 = 2.247;
	Double_t B2 = 0.0;

	return GD*( A0*tau + A1*tau*tau )/(1.0+B1*tau+B2*tau*tau);
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

Double_t roberts_gen(Double_t *x, Double_t *p){
	// Roberts - 10/16/2008
	// Supplied from Bogdan in email
	// Valid for 0.04 < Q^2/M_n^2 < 14
	Double_t Q2 = x[0];
	Double_t Y  = Q2/(0.939*0.939);

	Double_t a0 = -57.417365537964024;
	Double_t a1 = 234.58515115739985;
	Double_t a2 = -41.36358088250326;
	Double_t a3 =   1.6072864758748215;

	Double_t b0 =   -0.1815770760253892;
	Double_t b1 =  704.407716448618;
	Double_t b2 =  908.1767951358386;
	Double_t b3 = 1087.8147627172036;

	return (Y*(a0 + a1*Y + a2*Y*Y + a3*Y*Y*Y ))/( b0 + b1*Y + b2*Y*Y + b3*Y*Y*Y );
}

TGraph *draw_schiavilla(Int_t opt = 0){

	Double_t x, y, dy;

	Double_t gen[26];
	Double_t Q2[26];
	Double_t tau;
	Int_t i;

	FILE *f = fopen("figure_input/GEn_Schiavilla.dat", "r");

	for( i = 0; i < 13; i++ ){
		fscanf( f, "%lf%lf%lf", &x, &y, &dy );

		Q2[i]    = x;
		Q2[25-i] = x;

		if( opt == 0 ){
			gen[i]   = y+dy;
			gen[25-i]= y-dy;
		}

		if( opt == 1 ){
			gen[i]   = y;
			gen[25-i]= y;
		}
	}	

	TGraph *g = new TGraph( 20, Q2, gen );

	g->SetFillColor(kCyan-10);
	g->SetFillStyle(1001);
	g->SetLineColor(kGreen);

	g->SetMarkerStyle(23);

	return g;
}

void gen_riordan() {
  gROOT->SetStyle("HALLA");
  TCanvas *cn = new TCanvas("cn");
  cn->Draw();
  cn->UseCurrentStyle();
  //TH1F *frm = new TH1F("frm","",100,0.,10.);
  TH1F *frm = new TH1F("frm","",100,0.,3.);
  frm->GetXaxis()->SetTitle("Q^{2}  [GeV^{2}]");
  frm->GetXaxis()->CenterTitle();
  frm->GetYaxis()->SetTitle("G_{E}^{n}");
  frm->GetYaxis()->CenterTitle();
  frm->SetMinimum(.00);
  frm->SetMaximum(0.1);
  //frm->SetMaximum(0.3);
  frm->UseCurrentStyle();
  frm->Draw();
  frm->SetAxisRange(0.10,4.,"X");

  TF1* galster = new TF1("galster",
			 "x/(4.*0.938*.938)*1.91/(1.+x/.71)^2/(1.+5.6*x/(4.*.938*.938))",
			 0.,4.);
  galster->SetLineColor(kBlack);
  galster->SetLineStyle(kBlack);
  galster->SetLineWidth(2);


  TF1 *genf = new TF1("genf",genff,1.,10.,1);
  genf->SetLineColor(kBlue);
  genf->SetLineStyle(1);
  genf->SetParameter(0,1.);
  // match to Madey point just below 1.5
  // genf->SetParameter(0,.0411/genf->Eval(1.45));
//  genf->SetParameter(0,-0.558645);
  genf->SetParameter(0,-0.182645);

  TF1 *roberts_curve = new TF1("roberts",roberts_gen,0.035,12.344,1);
  roberts_curve->SetLineColor(kRed);
  roberts_curve->SetLineStyle(9);

  TF1 *ourfit = new TF1("ourfit",gen_ourfit,0.,10.,0);
  ourfit->SetLineColor(kBlue);
  ourfit->SetLineStyle(0);

  /*
  TF1 *bbba05 = new TF1("BBBA05",gen_bbba05,0.,10.,0);
  bbba05->SetLineColor(kGreen);
  bbba05->SetLineStyle(3);
  */

//  TF1 *lomon = new TF1("Lomon",Lomon_GEn,0.,10.,0);
 // lomon->SetLineColor(7);
 // lomon->SetLineStyle(4);
 
  


  TMultiGraph* mgrDta = new TMultiGraph("Data","G_{E}^{n}");
  //TLegend *legDta = new TLegend(.3448,.6123,.6810,.9110,"","brNDC");
  TLegend *legDta = new TLegend(.6020,.4004,.9382,.9089,"","brNDC");

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
  legDta->Draw();

  TMultiGraph* mgrThry = new TMultiGraph("Theory","G_{E}^{n}");
//  TLegend *legThry = new TLegend(.546,.6208,.8822,.9195,"","brNDC");
  TLegend *legThry = new TLegend(.2055,.7013,.6020,.8893,"","brNDC");

  wgr = mgrThry;
  wlg = legThry;

  // the theory
  wlg->SetBorderSize(0); // turn off border
  wlg->SetFillStyle(0);

  f = theoryfiles1;
  gr=0;
  Bool_t isfill;
  while ( f && f->filename ) {
	  gr=OneGraph(f);
	  gr->SetLineWidth(2);
	  isfill = kFALSE;
	  if (gr) {
		  TGraphAsymmErrors *egr = dynamic_cast<TGraphAsymmErrors*>(gr);
		  if (egr && egr->GetN()>1 && egr->GetEYhigh() && egr->GetEYhigh()[1]>0) {
			  gr = toerror_band(egr);
			  gr->SetFillStyle(3000+f->style);
			  gr->SetFillStyle(1);
			  gr->SetFillColor(gr->GetLineColor());
			  isfill = kTRUE;
		  }
		  if (f->lnpt) {
			  wgr->Add(gr,f->lnpt);
			  if( f->label[0] != 'x' )
				  wlg->AddEntry(gr,f->label,f->lnpt);
		  }
		  else if (gr->GetMarkerStyle()>=20) {
			  wgr->Add(gr,"p");
			  if( f->label[0] != 'x' )
				  wlg->AddEntry(gr,f->label,"p");
		  }	
		  else {
			  if( isfill ){
				  gr->SetLineStyle(0);
				  wgr->Add(gr,"f");
//				  wgr->Add( new TGraph(*egr),"l");
				  if( f->label[0] != 'x' )
					  wlg->AddEntry(gr,f->label,"lf");
			  } else {
				  wgr->Add(gr,"l");
				  if( f->label[0] != 'x' )
					  wlg->AddEntry(gr,f->label,"l");
			  }
		  }

	  }
	  f++;
  }


  TPaveLabel *prelim = new TPaveLabel( 0.3204, 0.1886, 0.9310, 0.4643, "PRELIMINARY", "NDC" );
  prelim->SetTextAngle(0);
  TColor *pink = new TColor(300, 1.0, 0.7, 0.7, "pink");
  prelim->SetTextColor(300);
  prelim->SetFillStyle(0);
  prelim->SetBorderSize(0);


#ifdef FAKE_SCHIAVILLA
  TGraph *schiagraph = draw_schiavilla();
  schiagraph->Draw("F");
  schiagraph = draw_schiavilla(1);
  schiagraph->Draw("C");
  legThry->AddEntry(schiagraph, "d(e,e'd) T_{20} - Schiavilla & Sick", "LF");
#endif

#ifdef PRELIMINARY
  prelim->Draw("same");
#endif

  TPaveLabel *nofsilab = new TPaveLabel( 0.4569, 0.1674, 0.7514, 0.2415, "No FSI Corrections", "NDC" );
  nofsilab->SetFillStyle(0);
  nofsilab->SetBorderSize(0);
  nofsilab->SetTextColor(kRed);

#ifdef NOFSI
  nofsilab->Draw("same");
#endif

#ifdef PQCD
  genf->Draw("same");
#endif
  mgrThry->Draw("c");
#ifdef GALSTER
  galster->Draw("same");
#endif

#ifdef NEW_ROBERTS
    roberts_curve->Draw("same");
#endif
//  ourfit->Draw("same");
  //  bbba05->Draw("same");
  //lomon->Draw("same");
  // bandi->Draw("same");
#ifdef PQCD  
  legThry->AddEntry(genf,"F_{2}/F_{1} #propto ln^{2}(Q^{2}/#Lambda^{2})/Q^{2}","l");
#endif
#ifdef GALSTER
  legThry->AddEntry(galster,"Galster fit (1971)","l");
#endif
#ifdef NEW_ROBERTS
    legThry->AddEntry(roberts_curve,"q(qq) Faddeev -  I. Cloet, ANL","l");
#endif
  //  legThry->AddEntry(bbba05,"BBBA05","l");
  //  legThry->AddEntry(lomon, "Lomon", "l");
  // legThry->AddEntry(ourfit, "Our Fit", "l");
  legThry->Draw();
  legDta->Draw();

  mgrDta->Draw("p");
  legDta->Draw();

  TEllipse *cir1 = new TEllipse(1.31, 0.0, 0.17, 0.0065);
  TEllipse *cir2 = new TEllipse(2.4, 0.0, 0.17, 0.0065);
  cir1->SetFillStyle(0);
  cir2->SetFillStyle(0);

#ifdef PLOTKIN1
  cir1->Draw("same");
  //  cir2->Draw("same");

  //  TPaveLabel *exacc = new TPaveLabel( 0.3779, 0.2691, 0.5963, 0.3114, "Expected Accuracy", "NDC");
  TPaveLabel *exacc = new TPaveLabel( 0.2716, 0.2733, 0.4899, 0.3136, "Expected Accuracy", "NDC");
  exacc->SetFillStyle(0);
  exacc->SetBorderSize(0);
  exacc->Draw("same");
#endif


  // draw a line at 1
  cn->Modified();

  cn->Update();
  cn->SaveAs(Form("%s.pdf",psfile));
  cn->SaveAs(Form("%s.eps",psfile));
  //  cn->SaveAs(Form("%s.root",psfile));
  //  gSystem->Exec(Form("./replace_symbols.pl %s.eps",psfile));

  //  cn->SaveAs("bogdan_gen.eps");
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
