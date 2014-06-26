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

const char* psfile = "q4gmp";

using namespace std;


datafile_t datafiles[] = {
  { "formfactor_datafiles/GMp_Borkowski.dat", "Borkowski", "[0]", "[1]", "[2]", "[2]",0,0, 29,1 },
  { "formfactor_datafiles/GMp_Sill.dat", "Sill", "[0]", "[1]", "[2]", "[2]", 0,0,23,1 },
  { "formfactor_datafiles/GMp_Bosted.dat", "Bosted", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 22,1 },
  { "formfactor_datafiles/GMp_Walker.dat", "Walker", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3]+[4]*[4])", "sqrt([2]*[2]+[3]*[3]+[4]*[4])",0,0, 21,1 },
  { "formfactor_datafiles/GMp_Andivahis.dat", "Andivahis", "[0]", "[1]", "[2]", "[2]", 0,0, 20,1 },
  { "formfactor_datafiles/GMp_12GeVprop.dat", "PR12-07-108", "[0]", "0.5*(1.0+[0]/0.71)**2/[0]**2", "[2]", "[2]", 0,0, 4,kRed },
  { 0 }
};  

datafile_t theoryfiles1[] = {
/*  { "figure_input/Lattice/ffrng_all.dat", "Lattice", 
    "[0]", "[1]/2.79*(1+[0]/.71)*(1+[0]/.71)",
    "([1]-[2])/2.79*(1+[0]/.71)*(1+[0]/.71)", "([3]-[1])/2.79*(1+[0]/.71)*(1+[0]/.71)",
    0,0,1,1, "F" },
  //  { "figure_input/Iachello/formfactor_10GeV.dat.2", "Iachello", "[0]", "[3]", "0", "0", 0,0, 1,1 },
  { "figure_input/Bijker/spaceff.kees", "Bijker", "[0]", "[2]", "0", "0", 0,0, 1,4 },
  { "figure_input/Holzwarth/gmp.dat.2", "Holzwarth", "[0]", "[1]/2.79*(1+[0]/.71)*(1+[0]/.71)", "0", "0",0,0, 2,3 },
  { "figure_input/Hammer/gmpthnf4.dat", "Hammer", "[0]", "[1]", "0", "0",0,0, 2,4 },
  */
  { "figure_input/Miller/GMp_GD.dat.spl3", "CQM - G. Miller", "[0]", "[1]", "0", "0",0,0, 1,3 },
  { "figure_input/Lomon/gmp-gd.dat.2", "VMD - Lomon (2002)", "[0]", "[1]", "0", "0",0,0, 2,4 },
  
  { NULL }
};

TGraphAsymmErrors *fromGMpGDtoQ4GMp(TGraph *ogr);

void q4gmp_jan2009() {
  gROOT->SetStyle("HALLA");
  TCanvas *cn = new TCanvas("cn");
  cn->Draw();
  TH1F *frm = new TH1F("frm","",100,0.,20.);
  frm->GetXaxis()->SetTitle("Q^{2}  [GeV^{2}]");
  frm->GetYaxis()->SetTitle("Q^{4} G_{M}^{p}/#mu_{p}");

  frm->GetXaxis()->CenterTitle();
  frm->GetYaxis()->CenterTitle();

  frm->SetMinimum(0.0);
  frm->SetMaximum(0.6);
  frm->UseCurrentStyle();
  frm->Draw();


  
  TMultiGraph* mgrDta = new TMultiGraph("Data","#frac{G_{M}^{p}}{#mu_{p}G_{D}^{p}}");
//  TLegend *legDta = new TLegend(.7,.7,.9,1.,"","brNDC");
  TLegend *legDta = new TLegend(.2945,.2034,.5532,0.5826,"","brNDC");

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
	  gr = fromGMpGDtoQ4GMp(ogr);
	if (f->lnpt) {
	  mgrDta->Add(gr,f->lnpt);
	  legDta->AddEntry(gr,f->label,f->lnpt);
	}
//	else if (gr->GetMarkerStyle()>=20) {
	else {
	  mgrDta->Add(gr,"p");
	  legDta->AddEntry(gr,f->label,"p");
	}	
	/*
	else {
	  mgrDta->Add(gr,"l");
	  legDta->AddEntry(gr,f->label,"l");
	}
	*/
      }
      f++;
    }
  
    printf("data done\n");

  mgrDta->Draw("p");
    legDta->Draw(); 
  
  TMultiGraph* mgrThry = new TMultiGraph("Theory","#frac{#mu_{p}G_{E}^{p}}{G_{M}^{p}}");
  TLegend *legThry = new TLegend(.5489,.2097,.8103,.3814,"","brNDC");

  wgr = mgrThry;
  wlg = legThry;

  // the theory
    wlg->SetBorderSize(0); // turn off border
    wlg->SetFillStyle(0);

    f = theoryfiles1;
    ogr=0;
    while ( f && f->filename ) {
      ogr=OneGraph(f);
      if (ogr) {
	      ogr->SetLineWidth(2);
	      gr = fromGMpGDtoQ4GMp(ogr);
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
  
  mgrThry->Draw("c");
  legThry->Draw();



  // draw a line at 1
  cn->Modified();
  cn->Update();
  TFrame* frame = gPad->GetFrame();

  TLine *line1 = new TLine(frame->GetX1(),1.,frame->GetX2(),1.);
  line1->SetLineStyle(1);
  line1->Draw();

  return;

  cn->Update();
  cn->SaveAs(Form("%s.eps",psfile));
  cn->SaveAs(Form("%s.root",psfile));
  gSystem->Exec(Form("./replace_symbols.pl %s.eps",psfile));

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

  datafile_t miller = { "figure_input/Miller/lattice.GMp.rtf","Miller",
			"[0]","[1]/2.79*(1+[0]/.71)*(1+[0]/.71)",
			"([1]-[3])/2.79*(1+[0]/.71)*(1+[0]/.71)",
			"([2]-[1])/2.79*(1+[0]/.71)*(1+[0]/.71)",
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
  cn->SaveAs("gmpgd_Miller_Overlay.eps");
  cn->SaveAs("gmpgd_Miller_Overlay.root");

}

TGraphAsymmErrors *fromGMpGDtoQ4GMp(TGraph *ogr) {
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
		Gd = pow( 1.0 + Q2/0.71, -2.0);
		y *= pow(Q2,2.0)*Gd;
		ey1 *= pow(Q2,2.0)*Gd;
		ey2 *= pow(Q2,2.0)*Gd;
		gr->SetPoint(i,x,y);
		gr->SetPointError(i,ex1,ex2,ey1,ey2);
	}
	return gr;
}

