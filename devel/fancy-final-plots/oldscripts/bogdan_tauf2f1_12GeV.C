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
#include <TColor.h>
#include <TPaveLabel.h>
#include <TEllipse.h>

#include "halla_plotting.h"

//#define PRELIMINARY

const char* psfile = "bogdan_tauf2f1_12GeV";

using namespace std;

datafile_t datafiles[] = {
  { "formfactor_datafiles/GEn_Passchier.dat", "Passchier", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 5,1,"p" },
//  { "formfactor_datafiles/GEn_Herberg.dat", "Herberg", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,23,1,"p" },
  { "formfactor_datafiles/GEn_Ostrick.dat", "Ostrick", "[0]", "[1]", "sqrt([2]*[2]+[4]*[4])", "sqrt([2]*[2]+[3]*[3])", 0,0,29,1,"p" },
  { "formfactor_datafiles/GEn_Seimetz.dat", "Seimetz", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,1,"p" },
  { "formfactor_datafiles/GEn_Warren.dat", "Warren", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,21,1,"p" },
  { "formfactor_datafiles/GEn_Becker.dat", "Becker", "[0]", "[1]", "[2]","[2]", 0,0,25,1,"p" },
  { "formfactor_datafiles/GEn_Bermuth.dat", "Bermuth", "[0]", "[1]", "[2]", "[2]", 0,0,24,1,"p" },
  { "formfactor_datafiles/GEn_Madey.dat", "Madey", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,26,2,"p" },
   {"formfactor_datafiles/GEn_Geis.dat", "Geis","[0]","[1]","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,22,kGreen},
  //  { "e02013_proposal.dat", "E02-013 (proj)","[0]","[1]","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,26,2},
//  { "e02013_proposal.dat", "E02-013 (proj)","[0]","0","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,26,2,"p"},
//  { "e02013_noerr.dat", "E02-013 (taken)","[0]","0","0","0",0,0,20,8,"p"},
 // { "e02013_errbars.dat", "E02-013 (expected errors)","[0]","0","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,20,2,"p"},
//  { "e02013_errbars.dat", "E02-013 (preliminary)","[0]","0","[2]","[2]",0,0,8,2,"p"},
 // { "e02013_results.dat", "E02-013 (preliminary)","[0]","[1]","[2]","[2]",0,0,20,4,"p"},
//  { "e02013_results.dat", "x","[0]","[1]","[2]","[2]",0,0,22,2,"p"},
  { "e02013_nofsi.dat", "x","[0]","0","[2]","[2]",0,0,22,2,"p"},
  //{ "e02013_results.dat", "This Work","[0]","[1]","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,22,2,"p"},
  { "e02013_nofsi.dat", "E02-013","[0]","0","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,22,2,"p"},
    {"e02013_proposal.dat", "x","[0]","0","[2]","[2]",0,0,22,2},
      {"e02013_proposal.dat", "x","[0]","0","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,22,2},
  //  { "madey_proposal.dat", "E04-110 (proj)", "[1]", "0", "0.002", "0.002", 0, 0, 28, 2,"p"},
      {"12gevprop_7.dat", "12 GeV Plans","[0]","0","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,22,kBlue},
      {"12gevprop_10.dat", "12 GeV Plans","[0]","0","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,22,kBlack},
  { NULL }
};  

datafile_t theoryfiles1[] = {
  //  { "figure_input/Lattice/ffrng_all.dat", "Lattice", "[0]", "[10]", "[10]-[11]", "[12]-[10]", 0, 0, 4, 1, "F" },
  //  { "figure_input/Iachello/formfactor_10GeV.dat.2", "Iachello", "[0]", "[5]", "0", "0", 0, 0, 1, 1 },
  //  { "figure_input/Bijker/spaceff.kees",             "Bijker",   "[0]", "[3]", "0", "0", 0, 0, 6, 1 },
  //  { "figure_input/Holzwarth/gen.dat.2",          "Holzwarth",   "[0]", "[1]", "0", "0", 0, 0, 2, 1 },
  //  { "figure_input/Hammer/genthf4.dat",              "Hammer",   "[0]", "[1]", "0", "0", 0, 0, 4, 1 },
  { "figure_input/Roberts/gen.dat",             "DSE - C. Roberts",   "[0]", "[1]", "0", "0", 0, 0, 2, kRed },
  { "figure_input/Miller/GEn.dat.spl3.trunc",             "CQM - J. Miller",   "[0]", "[1]", "0", "0", 0, 0, 1, 8 },
  { "figure_input/Lomon/gen.dat.2",             "VMD - E. Lomon",   "[0]", "[1]", "0", "0", 0, 0, 2, 4 },
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

Double_t gengmnff(Double_t *x, Double_t *p) {
  Double_t Q2=*x;
  Double_t scl=p[0];
  Double_t tau=Q2/(4*.939565*.939565);
  Double_t ch=0.;
  Double_t kappa=-1.91;
  Double_t lambda = .3; // GeV, lambda = 300 MeV
  Double_t L2 = .71;
  Double_t f2f1 = scl*TMath::Log(Q2/(lambda*lambda))*TMath::Log(Q2/(lambda*lambda))/Q2;
  Double_t muGe_Gm = (ch+kappa)*((1-tau*kappa*f2f1)/(1+kappa*f2f1));
  return muGe_Gm;
}

Double_t f2f1(Double_t *x, Double_t *p) {
  Double_t Q2=*x;
  Double_t scl=p[0];
  Double_t tau=Q2/(4*.939565*.939565);
  Double_t ch=0.;
  Double_t kappa=-1.91;
  Double_t lambda = .3; // GeV, lambda = 300 MeV
  Double_t L2 = .71;
  Double_t f2f1 = scl*TMath::Log(Q2/(lambda*lambda))*TMath::Log(Q2/(lambda*lambda))/Q2;
  return kappa*f2f1*tau;
}

Double_t galster(Double_t *x, Double_t *p) {
  Double_t Q2=*x;
  Double_t tau=Q2/(4*.939565*.939565);
  Double_t ch=0.;
  Double_t kappa=-1.91;
  Double_t mu = (ch+kappa);
  Double_t gd = 1./((1.+Q2/.71)*(1.+Q2/.71));
  Double_t ge = -kappa*tau*gd/(1.+5.6*tau);

  // now, to mun*GEn/GMn
  Double_t gm = mu*gd;
  Double_t g = mu*ge/gm;
  Double_t r = ge/gm;

  // now, to kappa f2/f1
  Double_t f = (1-r)/(kappa*(r+tau));
  return f*kappa*tau;
}

Double_t galster_norm(Double_t *x, Double_t *p) {
  Double_t Q2=*x;
  Double_t tau=Q2/(4*.939565*.939565);
  Double_t ch=0.;
  Double_t kappa=-1.91;
  Double_t mu = (ch+kappa);
  Double_t gd = 1./((1.+Q2/.71)*(1.+Q2/.71));
  Double_t ge = -kappa*tau*gd/(1.+5.6*tau);

  return ge;
}


Double_t gengmnffq2(Double_t *x, Double_t *p) {
  Double_t Q2=*p;
  Double_t scl=x[0];
  Double_t tau=Q2/(4*.939565*.939565);
  Double_t ch=0.;
  Double_t kappa=-1.91;
  Double_t lambda = .3; // GeV, lambda = 300 MeV
  Double_t L2 = .71;
  Double_t f2f1 = scl*TMath::Log(Q2/(lambda*lambda))*TMath::Log(Q2/(lambda*lambda))/Q2;
  Double_t muGe_Gm = (ch+kappa)*((1-tau*kappa*f2f1)/(1+kappa*f2f1));
  return muGe_Gm;
}



Double_t gmn(Double_t Q2) {
  // dipole form for the magnetic form-factor
  Double_t ch=0.;
  Double_t kappa=-1.91;
  Double_t L2 = .71;
  Double_t gm = (ch+kappa)/(1+Q2/L2)/(1+Q2/L2);
  return gm;
}

TGraphAsymmErrors *fromGEntoGEnGMn(TGraph *ogr) {
// take a curve (with errors) of GEn and make it into (mun GEn/GMn)
  if (!ogr) return 0;
  TGraphAsymmErrors *ogrE = dynamic_cast<TGraphAsymmErrors*>(ogr);
  int npts = ogr->GetN();
  Double_t x,y;
  Double_t Q2;
  Double_t GMn;
  Double_t mun = gmn(0.);
  TGraphAsymmErrors *gr = new TGraphAsymmErrors(npts);
  ogr->TAttMarker::Copy(*gr);
  ogr->TAttLine::Copy(*gr);
  ogr->TAttFill::Copy(*gr);
  gr->SetName(ogr->GetName());
  
  for (int i=0; i<npts; i++) {
    Double_t ex1=0,ex2=0,ey1=0,ey2=0;
    ogr->GetPoint(i,x,y);
    Q2=x;
    Double_t tau=Q2/(4*.939565*.939565);
    if (ogrE) {
      ex1 = ogrE->GetErrorXlow(i);
      ex2 = ogrE->GetErrorXhigh(i);
      ey1 = ogrE->GetErrorYlow(i);
      ey2 = ogrE->GetErrorYhigh(i);
    }
    y /= gmn(x)/mun;
    ey1 /= gmn(x)/mun;
    ey2 /= gmn(x)/mun;
    gr->SetPoint(i,x,y);
    gr->SetPointError(i,ex1,ex2,ey1,ey2);
  }
  return gr;
}


TGraphAsymmErrors *fromGEntoF2F1(TGraph *ogr) {
// take a curve (with errors) of GEn and make it into (F2/F1)
  if (!ogr) return 0;
  TGraphAsymmErrors *ogrE = dynamic_cast<TGraphAsymmErrors*>(ogr);
  int npts = ogr->GetN();
  Double_t x,y;
  Double_t Q2;
  Double_t GMn;
  Double_t mun = gmn(0.);
  Double_t kappa=-1.91;
  Double_t r,er1,er2,f,ef1,ef2;
  TGraphAsymmErrors *gr = new TGraphAsymmErrors(npts);
  ogr->TAttMarker::Copy(*gr);
  ogr->TAttLine::Copy(*gr);
  ogr->TAttFill::Copy(*gr);
  gr->SetName(ogr->GetName());
  
  for (int i=0; i<npts; i++) {
    Double_t ex1=0,ex2=0,ey1=0,ey2=0;
    ogr->GetPoint(i,x,y);
    Q2=x;
    Double_t tau=Q2/(4*.939565*.939565);
    if (ogrE) {
      ex1 = ogrE->GetErrorXlow(i);
      ex2 = ogrE->GetErrorXhigh(i);
      ey1 = ogrE->GetErrorYlow(i);
      ey2 = ogrE->GetErrorYhigh(i);
    }
    r = y/(gmn(x));
    er1 = ey1/(gmn(x));
    er2 = ey2/(gmn(x));

    f = (1.-r)/(kappa*(r+tau));
    f *= -1.*Q2;
    if (y==0.) {
      // get r according to the galster parameterization
      // for a realistic error bar
      r = galster_norm(&x,0)/gmn(x);
    }
    ef1 = fabs(er1/((r+tau)*(r+tau))*(tau+1.)/kappa)*Q2;
    ef2 = fabs(er2/((r+tau)*(r+tau))*(tau+1.)/kappa)*Q2;
    
    gr->SetPoint(i,Q2,f);
    gr->SetPointError(i,ex1,ex2,ef1,ef2);
  }
  return gr;
}


TGraphAsymmErrors *fromGEntotauF2F1(TGraph *ogr) {
// take a curve (with errors) of GEn and make it into (tau*F2/F1)
  if (!ogr) return 0;
  TGraphAsymmErrors *ogrE = dynamic_cast<TGraphAsymmErrors*>(ogr);
  int npts = ogr->GetN();
  Double_t x,y;
  Double_t Q2;
  Double_t GMn;
  Double_t mun = gmn(0.);
  Double_t kappa=-1.91;
  Double_t r,er1,er2,f,ef1,ef2;
  TGraphAsymmErrors *gr = new TGraphAsymmErrors(npts);
  ogr->TAttMarker::Copy(*gr);
  ogr->TAttLine::Copy(*gr);
  ogr->TAttFill::Copy(*gr);
  gr->SetName(ogr->GetName());
  
  for (int i=0; i<npts; i++) {
    Double_t ex1=0,ex2=0,ey1=0,ey2=0;
    ogr->GetPoint(i,x,y);
    Q2=x;
    Double_t tau=Q2/(4*.939565*.939565);
    if (ogrE) {
      ex1 = ogrE->GetErrorXlow(i);
      ex2 = ogrE->GetErrorXhigh(i);
      ey1 = ogrE->GetErrorYlow(i);
      ey2 = ogrE->GetErrorYhigh(i);
    }
    r = y/(gmn(x));
    er1 = ey1/(gmn(x));
    er2 = ey2/(gmn(x));

    f = (1.-r)/(kappa*(r+tau));
    f *= 1.*tau*kappa;
    if (y==0.) {
      // get r according to the galster parameterization
      // for a realistic error bar
      r = galster_norm(&x,0)/gmn(x);
    }
    ef1 = -1.0*fabs(er1/((r+tau)*(r+tau))*(tau+1.)/kappa)*tau*kappa;
    ef2 = -1.0*fabs(er2/((r+tau)*(r+tau))*(tau+1.)/kappa)*tau*kappa;
    
    gr->SetPoint(i,Q2,f);
    gr->SetPointError(i,ex1,ex2,ef1,ef2);
  }
  return gr;
}

void bogdan_tauf2f1_12GeV() {
  gROOT->SetStyle("HALLA");
  gStyle->SetMarkerSize(1.);
  TCanvas *cn = new TCanvas("cn");
  cn->Draw();
  cn->UseCurrentStyle();
  TH1F *frm = new TH1F("frm","",100,0.,12.);
  frm->GetXaxis()->SetTitle("Q^{2}  [GeV^{2}]");
  frm->GetXaxis()->CenterTitle();
  frm->GetYaxis()->SetTitle("#tau F_{2}^{n}/F_{1}^{n}");
  frm->GetYaxis()->CenterTitle();
  frm->SetMinimum(0.);
  frm->SetMaximum(19./(4.0*0.938));
  frm->UseCurrentStyle();
  frm->Draw();
  frm->SetAxisRange(0.1,12.,"X");

  TF1* galst = new TF1("Galster",galster,0.,5.,0);
  galst->SetLineColor(kBlack);
  galst->SetLineStyle(1);


  TF1 *genf = new TF1("f2f1",f2f1,1.1,10.,1);
  genf->SetLineColor(kBlue);
  genf->SetLineStyle(1);
  genf->SetParameter(0,1.);
  genf->SetParameter(1,.3);
//  genf->SetParameter(0,-0.632);
  genf->SetParameter(0,-0.422);
  // match to Madey point just below 1.5
  //  genf->SetParameter(0,.0411/genf->Eval(1.45));
  
  TMultiGraph* mgrDta = new TMultiGraph("Data","G_{E}^{n}");
  TLegend *legDta = new TLegend(.633,.585,.970,.883,"","brNDC");

  TMultiGraph* wgr = mgrDta;
  TLegend *wlg = legDta;

   // the data
  legDta->SetBorderSize(0); // turn off border
  legDta->SetFillStyle(0);
  
  datafile_t *f = datafiles;
  TGraph* gr=0;
  TGraph* ogr=0;

  Int_t i;

  while ( f && f->filename ) {
	  cout << "Data file " << f->filename << " (" << f->label << ")" << endl;
    ogr=OneGraph(f);

    for( i = 0; i < ogr->GetN(); i++ ){
	    cout << (ogr->GetX())[i] << " " << (ogr->GetY())[i] << endl;
    }
    
    if (ogr) {
//      gr=fromGEntoF2F1(ogr);
      gr=fromGEntotauF2F1(ogr);
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
  legDta->Draw();//   don't draw the data legend
  
  TMultiGraph* mgrThry = new TMultiGraph("Theory","G_{E}^{n}");
  TLegend *legThry = new TLegend(.29,.591,.626,.890,"","brNDC");

  wgr = mgrThry;
  wlg = legThry;

  // the theory
  wlg->SetBorderSize(0); // turn off border
  wlg->SetFillStyle(0);
  
  f = theoryfiles1;
  gr=0;
  while ( f && f->filename ) {
    ogr=OneGraph(f);
    if (ogr) {
      gr=fromGEntotauF2F1(ogr);
      gr->SetLineWidth(2);
      
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

  TPaveLabel *prelim = new TPaveLabel( 0.0761, 0.2352, 0.9971, 0.6653, "PRELIMINARY", "NDC" );
  prelim->SetTextAngle(30);
  TColor *pink = new TColor(300, 1.0, 0.5, 0.5, "pink");
  prelim->SetTextColor(300);
  prelim->SetFillStyle(0);
  prelim->SetBorderSize(0);

#ifdef PRELIMINARY
  prelim->Draw("same");
#endif

  // GEn = 0 line
  TLine *gen0line = new TLine(0.5, 1.0, 11.0, 1.0);
  gen0line->Draw();
  TPaveLabel *gen0lab = new TPaveLabel(0.7443, 0.1335, 0.9037, 0.4025, "G_{E}^{n} = 0", "NDC");
//  TPaveLabel *gen0lab = new TPaveLabel(0.5187, 0.20551, 0.6796, 0.3623, "G_{E}^{n} = 0");
  gen0lab->SetFillStyle(0);
  gen0lab->SetBorderSize(0);
  gen0lab->Draw();

  genf->Draw("same");
//  galst->Draw("same");
  legThry->AddEntry(genf,"F_{2}/F_{1} #propto ln^{2}(Q^{2}/#Lambda^{2})/Q^{2}","l");
 // legThry->AddEntry(galst,"Galster fit","l");
  legThry->Draw();
  mgrThry->Draw("c");

  // draw a line at 1
  cn->Modified();
  cn->Update();
  TFrame* frame = gPad->GetFrame();

  /*
  // Circle two points
  TEllipse *cir1 = new TEllipse(1.31, 1.0, 0.17, 0.23);
  TEllipse *cir2 = new TEllipse(2.4, 1.0, 0.17, 0.23);

  cir1->Draw("same");
  cir2->Draw("same");

  TPaveLabel *exacc = new TPaveLabel( 0.306, 0.224, 0.5244, 0.2669, "Expected Accuracy", "NDC");
  exacc->SetFillStyle(0);
  exacc->SetBorderSize(0);

  exacc->Draw("same");
  */

  mgrDta->Draw("p");
  legDta->Draw();//   don't draw the data legend

  cn->Update();
  cn->SaveAs(Form("%s.eps",psfile));
  cn->SaveAs(Form("%s.root",psfile));
  gSystem->Exec(Form("./replace_symbols.pl %s.eps",psfile));

}
