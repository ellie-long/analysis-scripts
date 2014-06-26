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
#include <TSystem.h>

#include "halla_plotting.h"

const char* psfile = "riordan_gmngd";

using namespace std;

datafile_t datafiles[] = {
  //  { "formfactor_datafiles/GMn_Arnold.dat", "Arnold", "[0]", "[1]", "[2]", "[2]",0,0 3,1 },
  { "formfactor_datafiles/GMn_Rock.dat", "Rock", "[0]", "[1]", "[2]", "[2]",0,0, 5,1,"p" },
//  { "formfactor_datafiles/GMn_Lung.dat", "Lung", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 2,1,"p" },
  //  { "formfactor_datafiles/GMn_Markowitz.dat", "Markowitz", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3]+[4]*[4])", "sqrt([2]*[2]+[3]*[3]+[4]*[4])",0,0, 29,1 },
 // { "formfactor_datafiles/GMn_Anklin2.dat", "Anklin(1994)", "[0]", "[1]", "[2]", "[2]",0,0,23,1 },
  //  { "formfactor_datafiles/GMn_Bruins.dat", "Bruins", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,22,1 },
 // { "formfactor_datafiles/GMn_Anklin.dat", "Anklin(1998)", "[0]", "[1]", "[2]", "[2]",0,0, 21,1 },
 // { "formfactor_datafiles/GMn_Kubon.dat", "Kubon", "[0]", "[1]", "[2]", "[2]", 0,0,20,1 },
  //  { "formfactor_datafiles/GMn_Gao.dat", "Gao", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3]+[4]*[4])", "sqrt([2]*[2]+[3]*[3]+[4]*[4])", 0,0,26,1 },
 // { "formfactor_datafiles/GMn_Xu.dat", "Xu(2000)", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 25,2 },
 // { "formfactor_datafiles/GMn_Xu02.dat", "Xu(2002)", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 24,2 },
// { "clas_gmngd_prelim.dat", "Lachniet (Preliminary)", "[0]", "[1]", "sqrt([2]*[2]+.03*.03*[1]*[1])", "sqrt([2]*[2]+.03*.03*[1]*[1])", 0, 0, 29, 2 },
 { "formfactor_datafiles/GMn_Lachniet.dat", "Lachniet (arXiv:0811.1716)", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0, 0, 29, kGreen },
 { "formfactor_datafiles/GMn_CLAS12.dat", "E12-07-104, CLAS12", "[0]", "0.8*[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0, 0, 21, kBlue },
 { "gmnprop.dat", "PR-09-019", "[0]", "1.1*[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0, 0, 22, kRed },
  { NULL }
};  

datafile_t theoryfiles1[] = {
 // { "figure_input/Lattice/ffrng_all.dat", "Lattice", "[0]", "[4]/(-1.91)*(1+[0]/.71)*(1+[0]/.71)",  "([4]-[5])/(-1.91)*(1+[0]/.71)*(1+[0]/.71)","([6]-[4])/(-1.91)*(1+[0]/.71)*(1+[0]/.71)", 0,0,1,1, "F" },
//  { "figure_input/Iachello/formfactor_10GeV.dat.2", "VMD - Iachello", "[0]", "[4]", "0", "0", 0,0,1,1 },
 // { "figure_input/Bijker/spaceff.kees", "Bijker", "[0]", "[4]", "0", "0", 0,0,1,4 },
 // { "figure_input/Holzwarth/gmn-gd.dat.2", "Holzwarth", "[0]", "[1]", "0", "0", 0,0,2,3 },
 // { "figure_input/Hammer/gmnthnf4.dat", "Hammer", "[0]", "[1]", "0", "0", 0,0,2,4 },
  { "figure_input/Miller/GMn_GD.dat.spl3", "CQM - G. Miller", "[0]", "[1]", "0", "0",0,0,1, 3 },
  { "figure_input/Lomon/gmn-gd.dat.2", "VMD - E. Lomon (2002)", "[0]", "[1]", "0", "0",0,0,1, kBlack},
  { NULL }
};

Double_t KellyGMn( Double_t *x, Double_t *par ){
	Double_t Q2 = x[0];

	Double_t tau = Q2/(4.0*0.939*0.939);
	return -1.91*(1.0 + 2.33*tau)/(1.0 + 14.72*tau + 24.20*tau*tau + 84.1*tau*tau*tau );

}

void riordan_gmngd() {
  gROOT->SetStyle("HALLA");
  TCanvas *cn = new TCanvas("cn");
  cn->Draw();
//  TH1F *frm = new TH1F("frm","",100,0.,5.5);
  TH1F *frm = new TH1F("frm","",100,0.,20.);
  frm->GetXaxis()->SetTitle("Q^{2}  [GeV^{2}]");
  frm->GetXaxis()->CenterTitle();
  frm->GetYaxis()->SetTitle("G_{M}^{n}/#mu_{n}G_{D}");
  frm->GetYaxis()->CenterTitle();
  frm->SetMinimum(0.3);
  frm->SetMaximum(1.3);
  frm->UseCurrentStyle();
  frm->Draw();


  
  TMultiGraph* mgrDta = new TMultiGraph("Data","G_{M}^{n}/#mu_{n}G_{D}");
  //TLegend *legDta = new TLegend(.6566,.6102,.8563,0.9089,"","brNDC");
  TLegend *legDta = new TLegend(0.1710,.3729,.5776,.5127,"","brNDC");

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
   legDta->Draw();  // don't draw the data legend
  
  TMultiGraph* mgrThry = new TMultiGraph("Theory","");
//  TLegend *legThry = new TLegend(0.4799,.7648,.6710,.8983,"","brNDC");
  TLegend *legThry= new TLegend(.1853,.2373,.5259,0.3729,"","brNDC");

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

    TF1 *kellyfit = new TF1("kellyfit", KellyGMn, 0, 20,1);
    kellyfit->SetLineColor(kBlack);

    kellyfit->Draw("same");
    legThry->AddEntry(kellyfit, "Kelly G_{M}^{n} Parameterization", "l");

  
  mgrThry->Draw("c");
  legThry->Draw();

  // draw a line at 1
  cn->Modified();
  cn->Update();
  TFrame* frame = gPad->GetFrame();

  TLine *line1 = new TLine(frame->GetX1(),1.,frame->GetX2(),1.);
  line1->SetLineStyle(1);
  line1->Draw();

  cn->Update();
  cn->SaveAs(Form("%s.eps",psfile));
  cn->SaveAs(Form("%s.root",psfile));
  gSystem->Exec(Form("./replace_symbols.pl %s.eps",psfile));

  return;

  // remove everything but the graph
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
  cn->Update();

  {
    datafile_t miller = { "figure_input/Miller/lattice.GMn.rtf","Miller",
			  "[0]","[1]/(-1.91)*(1+[0]/.71)*(1+[0]/.71)",
			  "([3]-[1])/(-1.91)*(1+[0]/.71)*(1+[0]/.71)",
			  "([1]-[2])/(-1.91)*(1+[0]/.71)*(1+[0]/.71)",
			  0,0,1,3,"F" };
    
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
    cn->SaveAs("gmngd_Miller_Overlay.eps");
    cn->SaveAs("gmngd_Miller_Overlay.root");
    clist->Remove(gr);
  }

  {
    datafile_t miller_spl = { "figure_input/Miller/lattice.GMn.spl3","Miller",
			      "[0]","[1]/(-1.91)*(1+[0]/.71)*(1+[0]/.71)",
			      "([3]-[1])/(-1.91)*(1+[0]/.71)*(1+[0]/.71)",
			      "([1]-[2])/(-1.91)*(1+[0]/.71)*(1+[0]/.71)",
			      0,0,1,3,"F" };
    
    gr = OneGraph(&miller_spl);
    TGraphAsymmErrors* egr = dynamic_cast<TGraphAsymmErrors*>(gr);
    if (egr && egr->GetEYhigh() && egr->GetEYhigh()[egr->GetN()/2]>0) {
      gr = toerror_band(egr);
      gr->SetLineStyle(1);
      gr->SetFillColor(gr->GetLineColor());
      gr->SetFillStyle(3000+miller_spl.style);
    }
    
    gr->Draw("F");
    
    cn->Update();
    cn->SaveAs("gmngd_Miller_Overlay_spl.eps");
    cn->SaveAs("gmngd_Miller_Overlay_spl.root");
    clist->Remove(gr);
  }

}
