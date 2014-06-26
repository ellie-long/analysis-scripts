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

const char* psfile = "q4gmn";

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
 { "formfactor_datafiles/GMn_CLAS12.dat", "E12-07-104, CLAS12", "[0]", "0.5/([0]**2*(1.0+[0]/0.71)**(-2))", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0, 0, 21, kBlue },
 { "gmnprop.dat", "PR-09-019", "[0]", "0.55/([0]**2*(1.0+[0]/0.71)**(-2))", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0, 0, 26, kRed },
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

TGraphAsymmErrors *fromGMnGDtoQ4GMn(TGraph *ogr);

void q4gmn_jan2009() {
  gROOT->SetStyle("HALLA");
  TCanvas *cn = new TCanvas("cn");
  cn->Draw();
//  TH1F *frm = new TH1F("frm","",100,0.,5.5);
  TH1F *frm = new TH1F("frm","",100,0.,20.);
  frm->GetXaxis()->SetTitle("Q^{2}  [GeV^{2}]");
  frm->GetXaxis()->CenterTitle();
  frm->GetYaxis()->SetTitle("Q^{4} G_{M}^{n}/#mu_{n}");
  frm->GetYaxis()->CenterTitle();
  frm->SetMinimum(0.0);
  frm->SetMaximum(0.6);
  frm->UseCurrentStyle();
  frm->Draw();


  
  TMultiGraph* mgrDta = new TMultiGraph("Data","G_{M}^{n}/#mu_{n}G_{D}");
  TLegend *legDta = new TLegend(0.5029,.2076,.9095,.3877,"","brNDC");

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
	      gr = fromGMnGDtoQ4GMn(ogr);
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
  TLegend *legThry = new TLegend(0.1868,.1949,.5287,.3432,"","brNDC");

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
	      gr = fromGMnGDtoQ4GMn(ogr);
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

TGraphAsymmErrors *fromGMnGDtoQ4GMn(TGraph *ogr) {
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

