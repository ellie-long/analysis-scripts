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
#include <TGaxis.h>
#include <TMath.h>

#include "halla_plotting.h"
#include "add_theory.h"

//#define PRELIMINARY
#define OUR_ERR

#define NOFSI
//#define PLOTKIN1

#define PQCD
//#define GALSTER

//#define FAKE_SCHIAVILLA

#define NEW_ROBERTS

//#define SHIFT_TITLE

//const char* psfile = "gen_riordan";
const char* psfile = "gengd_jan2009";

using namespace std;

datafile_t datafiles[] = {
  // MIT - Bates
//  { "formfactor_datafiles/GEn_Eden.dat", "Eden", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 23,kBlue },

  // NIKHEF
  { "formfactor_datafiles/GEn_Passchier.dat", "Passchier, NIKHEF", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])",0,0, 24,kBlack },
 // Corrected by Golak
  // MAMI - Deuterium Polarization
  { "formfactor_datafiles/GEn_Herberg.dat", "Herberg, MAMI", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,24,kBlack },
  { "formfactor_datafiles/GEn_Ostrick.dat", "Ostrick, MAMI", "[0]", "[1]", "sqrt([2]*[2]+[4]*[4])", "sqrt([2]*[2]+[3]*[3])", 0,0,24,kBlack },


{ "formfactor_datafiles/GEn_Madey.dat", "Madey, Hall C", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,kRed },


  // PhD Thesis - MAINZ - Replaced by Glazier
//  { "formfactor_datafiles/GEn_Seimetz.dat", "Seimetz", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,20,1 },

  // A1 Collaboration - arXiv:nucl-ex/0410026
  { "formfactor_datafiles/GEn_Glazier.dat", "Glazier, MAMI", "[0]", "[1]", "[2]", "[2]", 0,0,24,kBlack },
  
  // Replaces Zhu - E93-026
  { "formfactor_datafiles/GEn_Warren.dat", "Warren, Hall C", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,24,kBlack },

  // MAMI - 3He Polarization
  { "formfactor_datafiles/GEn_Meyerhoff.dat", "Meyerhoff, MAMI", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,24,kBlack},
  { "formfactor_datafiles/GEn_Becker.dat", "Becker, MAMI", "[0]", "[1]", "[2]","[2]", 0,0,24,kBlack }, // Corrected by Golak
  { "formfactor_datafiles/GEn_Bermuth.dat", "Bermuth, MAMI", "[0]", "[1]", "[2]", "[2]", 0,0,24,kBlack },
  { "formfactor_datafiles/GEn_Rohe.dat", "Rohe, MAMI", "[0]", "[1]", "[2]", "[2]", 0,0,24,kBlack },


  // d(e,e')p - No polarization observables  (Huge error bars)
//  { "formfactor_datafiles/GEn_Lung.dat", "x", "[0]", "[1]", "[2]", "[2]", 0,0,28,kBlue },
//  { "formfactor_datafiles/GEn_Lung.dat", "Lung", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,28,kBlue },
//  { "formfactor_datafiles/GEn_Lung_new.dat", "x", "[0]", "[1]", "[2]", "[2]", 0,0,28,kBlue },
//  { "formfactor_datafiles/GEn_Lung_new.dat", "Lung (Naive Correction)", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0,0,28,kBlue },
 // { "formfactor_datafiles/GEn_Hanson.dat", "Hanson", "[0]", "[1]", "[2]", "[2]", 0,0,30,1 },

  { "formfactor_datafiles/GEn_Schiavilla.dat", "Schiavilla & Sick", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0, 0, 24, kBlack},
  {"formfactor_datafiles/GEn_Geis.dat", "Geis, BATES","[0]","[1]","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,24,kBlack},

// { "e02013_taken.dat", "E02-013, Taken","[0]","0","0","0",0,0,22,2},
#ifndef NOFSI
 { "e02013_results.dat", "x","[0]","[1]","[2]","[2]",0,0,22,2},

 { "e02013_results.dat", "E02-013 (Prelim.)","[0]","[1]","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,22,kRed},
#endif
#ifdef NOFSI
// { "e02013_nofsi.dat", "x","[0]","[1]","[2]","[2]",0,0,22,2},
 {"e02013_nofsi.dat", "E02-013 (Prelim.)","[0]","[1]","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,22,kRed},
#endif

#ifdef PLOTKIN1
  {"e02013_proposal.dat", "x","[0]","0","[2]","[2]",0,0,22,2},
 {"e02013_proposal.dat", "x","[0]","0","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,22,2},
#endif
  { "gen_newprop.dat", "PR09-016, Hall A","[0]","[1]","sqrt([2]*[2]+[3]*[3])","sqrt([2]*[2]+[3]*[3])",0,0,4,2},
  //  { "madey_proposal.dat", "E04-110 (proj)", "[0]", "0", "0.002", "0.002", 0, 0, 28, 2},
  { NULL }
};  

datafile_t theoryfiles1[] = {
//{ "figure_input/GEn_Schiavilla.dat", "d(e,e'd) T_{20} - Schiavilla & Sick", "[0]", "[1]", "sqrt([2]*[2]+[3]*[3])", "sqrt([2]*[2]+[3]*[3])", 0, 0, 3, kGreen},
//  { "figure_input/DiehlKroll/GEn.dat", "GPD from FF - Diehl et. al.", "[0]", "[1]", "[2]-[1]", "[1]-[3]", 0, 0, 2, kMagenta},
//  { "figure_input/DiehlKroll/GEn.dat", "GPD from FF - Diehl et. al.", "[0]", "[1]", "0", "0", 0, 0, 2, kMagenta},
  //  { "figure_input/Lattice/ffrng_all.dat", "Lattice", "[0]", "[10]", "[10]-[11]", "[12]-[10]", 0, 0, 1, 1, "F" },
  //  { "figure_input/Iachello/formfactor_10GeV.dat.2", "Iachello", "[0]", "[5]", "0", "0", 0, 0, 1, 1 },
 //  { "figure_input/Bijker/spaceff.kees",             "VMD - Bijker and Iachello",   "[0]", "[3]", "0", "0", 0, 0, 1, 4 },
  //  { "figure_input/Holzwarth/gen.dat.2",          "Holzwarth",   "[0]", "[1]", "0", "0", 0, 0, 2, 3 },
  //  { "figure_input/Hammer/genthf4.dat",              "Hammer",   "[0]", "[1]", "0", "0", 0, 0, 2, 4 },
//{ "figure_input/Roberts/gen.dat",             "DSE - C. Roberts",   "[0]", "[1]", "0", "0", 0, 0, 2, kRed },
 // { "figure_input/Lomon/gen.dat.2",              "VMD - Lomon (2002)",   "[0]", "[1]", "0", "0", 0, 0, 2, 4 },
// { "figure_input/Roberts/gen2.dat",             "q(qq) Faddeev -  I. Cloet, ANL",   "[0]", "[1]", "0", "0", 0, 0, 9, kRed },
// PHYSICAL REVIEW C 66, 045501 (2002)
 { "figure_input/Miller/GEn.dat.spl3",             "CQM - G. Miller",   "[0]", "[1]", "0", "0", 0, 0, 1, kRed },
//  { "figure_input/Miller/GEn.qonly.dat.spl3",       "Miller (q-only)",  "[0]", "[1]", "0", "0", 0, 0, 4, 4 },
  //  { "figure_input/Miller/lattice.GEn.rtf","Miller Lattice",
  //    "[0]","[1]","[1]-[3]","[2]-[1]",0,0,1,3,"F" },
  { "figure_input/Null",       "x",  "[0]", "[1]", "0", "0", 0, 0, 1, 1 },
{ NULL }
};

TGraphAsymmErrors *fromGEntoGEnGd(TGraph *ogr);

Double_t genff(Double_t *x, Double_t *p) {
  Double_t Q2=x[0];

  Double_t scl;

  Double_t tau=Q2/(4*.939565*.939565);
  Double_t ch=0.;
  Double_t kappa=-1.91;
  Double_t lambda = .3; // GeV, lambda = 300 MeV
  Double_t L2 = .71;

  double gd = pow( 1.0 + Q2/0.71, -2.0);

  
  // Just calculate scl from a GEn point
  // Kin 3:
//  Double_t fixedGEn = 0.011687;
//  Double_t fixedQ2  = 3.47;
//
  // Kin 4:
  //Our kinr
//  Double_t fixedGEn = 0.0343;
//  Double_t fixedQ2  = 1.71;

  Double_t fixedGEn = 0.0317;
  Double_t fixedQ2  = 1.72;
//  
//Madey
 // Double_t fixedGEn = 0.0411;
 // Double_t fixedQ2  = 1.45;

  Double_t fixedgm  = (ch+kappa)/(1+fixedQ2/L2)/(1+fixedQ2/L2);
  Double_t fixedtau = fixedQ2/(4.0*0.938*0.938);
  Double_t gm       = (ch+kappa)/(1+Q2/L2)/(1+Q2/L2);


  Double_t fixedR = pow(TMath::Log(fixedQ2/(lambda*lambda)),2.0)/fixedQ2;
  Double_t R = pow(TMath::Log(Q2/(lambda*lambda)),2.0)/Q2;

  scl = (1.0 - fixedGEn/fixedgm)/((fixedGEn/fixedgm+fixedtau)*fixedR); 

  Double_t f2f1 = scl*R;

  Double_t Ge_Gm = (1-tau*f2f1)/(1+f2f1);

  // now multiply by the dipole form factor to get ge for neutron
  
  return gm*Ge_Gm/gd;
}


TGraph *gen_kelly2(Int_t type, Double_t Q2min, Double_t Q2max){
	Double_t Q2;
	Double_t tau;
	
	// Old 
	// full
	
	Double_t Aold[4] = {1.610858, 3.077307, 6.391098, -0.547720, };

	Double_t errmatold[4][4] = { { 0.143381, 5.329167, 5.458533, 3.507744, },
		{ 5.329167, 468.516648, 402.109403, 479.800744, },
		{ 5.458533, 402.109403, 355.754851, 385.891218, },
		{ 3.507744, 479.800744, 385.891218, 564.019307, },
	};

	// long num

	/*
	Double_t A[4] = {1.615811, 3.547106, 6.779211, 0.000000, };

	Double_t errmat[4][4] = { { 0.126236, 2.449253, 3.190157, 0.000000, },
		{ 2.449253, 63.841649, 77.860388, 0.000000, },
		{ 3.190157, 77.860388, 96.479055, 0.000000, },
		{ 0.000000, 0.000000, 0.000000, 0.0, }};

	// long den
	*/

	/*
	Double_t A[4] = {1.566092, 0.000000, 3.618638, -3.342209, };

	Double_t errmat[4][4] = { { 0.054263, 0.0, 0.530731, -1.039902 },
		{ 0.000000, 0.000000, 0.000000, 0.0 },
		{ 0.530731, 0.0, 5.791769, -12.455864 },
		{ -1.039902, 0.0, -12.455864, 30.631548 },
	};
	*/

	// Galster-type
	/*
	Double_t A[4] = {1.460063, 0.000000, 2.318842, 0.000000, };

	Double_t errmat[4][4] = { { 0.019083, 0.0, 0.111403, 0.000000, },
		{ 0.000000, 0.000000, 0.000000, 0.000000, },
		{ 0.111403,  0.0, 0.751357, 0.000000 },
		{ 0.000000, 0.000000, 0.000000, 0.000000, },
	};
	*/


	// Fit with E02-013 (NOFSI) results

	// Full
	
	Double_t A[4] = {1.392126, -1.195337, 0.906902, -1.364560, };

	Double_t errmat[4][4] = { { 0.011044, -0.033179, 0.039967, -0.100895, },
		 { -0.033179, 0.415256, 0.015105, 0.985325, },
		  { 0.039967, 0.015105, 0.246620, -0.129034, },
		   { -0.100895, 0.985325, -0.129034, 2.484318, },};
	// Long num

	
	/*
	Double_t A[4] = {1.362518, -0.546337, 1.087581, 0.000000, };

	Double_t errmat[4][4] = { { 0.012065, 0.031918, 0.089037, 0.000000, },
		 { 0.031918, 0.201968, 0.391964, 0.000000, },
		  { 0.089037, 0.391964, 0.885720, 0.000000, },
		   { 0.000000, 0.000000, 0.000000, 0.0, },
		    };

		    */
	// Long denom
	
	/*
	Double_t A[4] = {1.374387, 0.000000, 1.540838, 0.755373, };

	Double_t errmat[4][4] = { { 0.015642, 0.0, 0.097791, -0.089000},

		   { 0.000000, 0.000000, 0.000000, 0.0, },
		 { 0.097791, 0.0, 0.723054, -0.774333},
		  { -0.089000,0.0,  -0.774333, 1.085241},};

		  */



	// Galster
	
	/*
	Double_t A[4] = {1.442649, 0.000000, 2.116471, 0.000000, };

	Double_t errmat[4][4] = { { 0.008302, 0.0, 0.033482, 0.000000},
		  { 0.000000, 0.000000, 0.000000, 0.000000, },
		 { 0.033482, 0.0, 0.167220, 0.000000},
		  { 0.000000, 0.000000, 0.000000, 0.000000, },
		    };
		    */


	Double_t dG[4];
	Double_t points[400];
	Double_t Q2points[400];
	Int_t i, j, k;
	Double_t err = 0.0;
	Double_t gen = 0.0;
	Double_t num, den;


	for( i = 0; i < 200; i++ ){
		Q2 = ((Double_t) (Q2max-Q2min)*i)/199 + Q2min;
		Q2points[i] = Q2;
		Q2points[399-i] = Q2;

		tau = Q2/(4.0*0.939565*0.939565);

		num = 0;
		den = 1.0;
		for( j = 0; j < 2; j++ ){
			if(type==1){
				num += A[j]*pow(tau,j+1);
			} else {
				num += Aold[j]*pow(tau,j+1);
			}
		}
		for( j = 0; j < 2; j++ ){
			if(type==1){
				den += A[j+2]*pow(tau,j+1);
			} else {
				den += Aold[j+2]*pow(tau,j+1);
			}
		}

		gen = num/den;

		for( j = 0; j < 2; j++ ){
			dG[j] = pow(tau, j+1)/den;
		}
		for( j = 0; j < 2; j++ ){
			dG[j+2] = -pow(tau, j+1)*num/(den*den);
		}

		err = 0.0;
		for( j = 0; j < 4; j++ ){
			for( k = 0; k < 4; k++ ){
				if( type == 1 ){
					err += dG[j]*dG[k]*errmat[j][k];
				} else {
					err += dG[j]*dG[k]*errmatold[j][k];
				}
			}
		}
		//		err = 0.001;

		points[i] = gen+sqrt(fabs(err));
		points[399-i] = gen-sqrt(fabs(err));
	}

	TGraph *g = new TGraph(400, Q2points, points );

	return g;
}

TGraph *gen_ourbbba( Int_t type, Double_t Q2min, Double_t Q2max){
	Double_t Q2;
	Double_t tau;

	/*
	 du positive, no positivity on b coeffs
	Double_t A[6] = {0.979267, 1.500765, -4.056130, 185.296768, -385.171343, 483.247184, };
	Double_t errmat[6][6] = { { 0.081163, 0.148440, 1.559359, 3.683101, -4.894717, 22.170196, },
		 { 0.148440, 1.623186, 5.673689, -5.282183, 96.998042, 48.641390, },
		  { 1.559359, 5.673689, 37.651657, 40.141896, 95.181502, 508.296291, },
		   { 3.683101, -5.282183, 40.141896, 325.084160, -1067.763939, 592.246974, },
		    { -4.894717, 96.998042, 95.181502, -1067.763939, 9334.375341, -2203.452553, },
		     { 22.170196, 48.641390, 508.296291, 592.246974, -2203.452553, 10638.106886, },
		      };
		      */


	// du/u free (but positive)
	
	Double_t A[6] = {1.192616, 20.526765, 12.041059, 383.819637, 0.000001, 1444.973241, };
	Double_t errmat[6][6] = { { 0.787526, -1.647562, 17.664001, -45.798341, 0.000053, 24.431978, },
		 { -1.647562, 683.685961, 225.900075, 10235.195307, 0.005952, 49266.717467, },
		  { 17.664001, 225.900075, 523.950993, 2682.081190, 0.004495, 20287.930786, },
		   { -45.798341, 10235.195307, 2682.081190, 155923.038964, 0.067511, 725564.714066, },
		    { 0.000053, 0.005952, 0.004495, 0.067511, 0.001422, 0.333572, },
		     { 24.431978, 49266.717467, 20287.930786, 725564.714066, 0.333572, 3637486.191993, },
		      };


	/*
	  d/u = 0.2
	Double_t A[6] = {1.822078, 0.060245, 19.737132, 53.844627, 0.003420, 105.208968, };

	Double_t errmat[6][6] = { { 0.300467, 0.015055, 5.670592, -1.649464, -0.123390, -27.398964, },
		 { 0.015055, 0.001398, 0.322683, 0.189299, -0.008313, -2.414716, },
		  { 5.670592, 0.322683, 113.134741, 0.863575, -2.827294, -582.528929, },
		   { -1.649464, 0.189299, 0.863575, 218.001069, -1.464084, -325.622207, },
		    { -0.123390, -0.008313, -2.827294, -1.464084, 1.865613, 12.735708, },
		     { -27.398964, -2.414716, -582.528929, -325.622207, 12.735708, 4353.491820, },
		      };
		      */


	/*
//	   d/u = 0.5
	Double_t A[6] = {2.245668, 1.067977, 32.980805, 3.587944, 233.536863, 3.816078, };
	Double_t errmat[6][6] = { { 0.178552, -0.020917, 3.533314, -2.439159, -13.034967, 0.133151, },
		 { -0.020917, 7.821755, 9.317943, -5.310026, -516.583816, -24.924409, },
		  { 3.533314, 9.317943, 97.068710, -170.307652, -1076.144356, -18.955241, },
		   { -2.439159, -5.310026, -170.307652, 1163.264968, 2528.704606, -138.339509, },
		    { -13.034967, -516.583816, -1076.144356, 2528.704606, 39562.055309, 1044.836762, },
		     { 0.133151, -24.924409, -18.955241, -138.339509, 1044.836762, 648.450168, },
	};
	*/

	/*
	 // No contraints
	Double_t A[6] = {-0.199584, 287.421073, 84.830632, 4373.751985, 0.864122, 20737.870564, };
	Double_t errmat[6][6] = { { 3.387679, -1.428046, 59.524810, 23.133743, 8.799557, 409.787157, },
		 { -1.428046, 28.381274, -4.296615, -695.131084, -744.803073, -7320.508258, },
		  { 59.524810, -4.296615, 1775.756825, 9136.475620, -2070.985704, -33748.356449, },
		   { 23.133743, -695.131084, 9136.475620, 199249.841274, 39374.880975, -275273.148978, },
		    { 8.799557, -744.803073, -2070.985704, 39374.880975, 84705.000689, 644880.393743, },
		     { 409.787157, -7320.508258, -33748.356449, -275273.148978, 644880.393743, 14636260.057555, },
		      };

		      */

	Double_t dG[6];
	Double_t points[400];
	Double_t Q2points[400];
	Int_t i, j, k;
	Double_t err = 0.0;
	Double_t gen = 0.0;
	Double_t num, den, gd;


	for( i = 0; i < 200; i++ ){
		Q2 = ((Double_t) (Q2max-Q2min)*i)/199 + Q2min;
		Q2points[i] = Q2;
		Q2points[399-i] = Q2;
		gd = pow( 1.0 + Q2/0.71, -2.0);

		tau = Q2/(4.0*0.939565*0.939565);

		num = 0;
		den = 1.0;
		for( j = 0; j < 2; j++ ){
			num += A[j]*pow(tau,j+1);
		}

		for( j = 0; j < 4; j++ ){
			den += A[j+2]*pow(tau,j+1);
		}

		gen = num/(den*gd);

		for( j = 0; j < 2; j++ ){
			dG[j] = pow(tau, j+1)/(den*gd);
		}
		for( j = 0; j < 4; j++ ){
			dG[j+2] = -pow(tau, j+1)*num/(den*den*gd);
		}

		err = 0.0;
		for( j = 0; j < 6; j++ ){
			for( k = 0; k < 6; k++ ){
				err += dG[j]*dG[k]*errmat[j][k];
			}
		}

		if( type == 0 ){
			err = 0.000;
		}

		points[i] = (gen+sqrt(fabs(err)));
		points[399-i] = (gen-sqrt(fabs(err)));
	}

	TGraph *g = new TGraph(400, Q2points, points );

	return g;
}

Double_t gen_bbba05(Double_t *x, Double_t *p) {
	Double_t Q2=*x;
	Double_t tau=Q2/(4*.939565*.939565);
	const int nA = 3;
	Double_t a[nA] = { 0., 1.25, 1.30 };
	const int nB = 5;
	Double_t b[nB] = {0, -9.86, 305, -758, 802};

	double gd = pow( 1.0 + Q2/0.71, -2.0);

	Double_t top=0., bot=1.;
	for (int k=0; k<nA; k++) top += a[k]*TMath::Power(tau,k);
	for (int k=0; k<nA; k++) bot += b[k]*TMath::Power(tau,k);
	return top/(bot*gd);
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

	double gdi = pow( 1.0 + Q2/0.71, 2.0);
	return (Y*(a0 + a1*Y + a2*Y*Y + a3*Y*Y*Y ))*gdi/( b0 + b1*Y + b2*Y*Y + b3*Y*Y*Y );
}

TGraph *draw_schiavilla(Int_t opt = 0){

	Double_t x, y, dy;

	Double_t gen[26];
	Double_t Q2[26];
	Double_t tau;
	Int_t i;

	FILE *f = fopen("figure_input/GEn_Schiavilla.dat", "r");

	double gdi[26];
	for( i = 0; i < 13; i++ ){
		fscanf( f, "%lf%lf%lf", &x, &y, &dy );

		Q2[i]    = x;
		Q2[25-i] = x;
		gdi[i]= pow( 1.0 + Q2[i]/0.71, 2.0);
		gdi[25-i]= pow( 1.0 + Q2[25-i]/0.71, 2.0);
		if( opt == 0 ){
			gen[i]   = (y+dy)*gdi[i];
			gen[25-i]= (y-dy)*gdi[25-i];
		}

		if( opt == 1 ){
			gen[i]   = y*gdi[i];
			gen[25-i]= y*gdi[25-i];
		}
	}	

	TGraph *g = new TGraph( 20, Q2, gen );

	g->SetFillColor(kCyan-10);
	g->SetFillStyle(1001);
	g->SetLineColor(kGreen);

	g->SetMarkerStyle(23);

	return g;
}

void gengd_ourfits() {
	gROOT->SetStyle("HALLA");
	TCanvas *cn = new TCanvas("cn");
	cn->Draw();
	cn->UseCurrentStyle();

	Double_t xaxis_min = 0.0;
	//  Double_t xaxis_max = 4.0;
	//	Double_t xaxis_max = 12.0;
	Double_t xaxis_max = 4.0;
	  Double_t yaxis_min = -0.1;
	//Double_t yaxis_min = -0.2;
	//  Double_t yaxis_max = 0.8;
	Double_t yaxis_max = 1.0;

	Int_t addoneplot = 0;

	TH1F *frm = new TH1F("frm","",100,xaxis_min,xaxis_max);
	//  frm->GetXaxis()->SetTitle("Q^{2}  [GeV^{2}]");
	frm->GetXaxis()->SetTitle("Q^{2} [GeV^{2}]");
	frm->GetXaxis()->CenterTitle();
#ifndef SHIFT_TITLE
	frm->GetYaxis()->SetTitle("G_{E}^{n}/G_{D}");
#endif
	frm->GetYaxis()->CenterTitle();
	frm->SetMinimum(yaxis_min);
	frm->SetMaximum(yaxis_max);
	frm->UseCurrentStyle();
	frm->Draw();
	frm->SetAxisRange(xaxis_min,xaxis_max,"X");
	//frm->GetXaxis()->SetNdivisions(505, kTRUE);

	TGaxis *replax = new TGaxis(xaxis_min+xaxis_max*1e-3, yaxis_min, xaxis_max, yaxis_min, xaxis_min+xaxis_max*1e-3, xaxis_max, frm->GetXaxis()->GetNdivisions(), "");
	TGaxis *replaxtop = new TGaxis(xaxis_min, yaxis_max, xaxis_max, yaxis_max, xaxis_min, xaxis_max, frm->GetXaxis()->GetNdivisions(), "U-");
	replax->ImportAxisAttributes(frm->GetXaxis()); 
	frm->GetXaxis()->SetNdivisions(0, kTRUE);

	TF1* galster = new TF1("galster",
			"x*1.91/(4.0*0.938*0.938+5.6*x)",
			-0.1,12.);
	galster->SetLineColor(kBlack);
	galster->SetLineStyle(kBlack);
	galster->SetLineWidth(2);


	TF1 *genf = new TF1("genf",genff,1.,14.,1);
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


	TGraph *ourbbba = gen_ourbbba(0, 0.0, 3.6);
	ourbbba->SetLineColor(kBlack);
	ourbbba->SetFillColor(kBlack);
	ourbbba->SetLineColor(kBlack);
	ourbbba->SetLineStyle(0);

	TGraph *ourbbbaband = gen_ourbbba(1, 0.0, 3.6);
	ourbbbaband->SetLineColor(kBlack);
	ourbbbaband->SetFillColor(kAzure-8);
	ourbbbaband->SetLineColor(kAzure-8);
	ourbbbaband->SetLineStyle(0);

	TGraph *kelly2 = gen_kelly2(1, 0.0, 3.6);
	kelly2->SetLineColor(kWhite);
	kelly2->SetFillColor(kAzure-8);
	kelly2->SetLineColor(kAzure-8);
	kelly2->SetLineStyle(0);

	TGraph *kelly2old = gen_kelly2(0, 0.0, 3.6);
//	kelly2old->SetLineColor(kBlack);
//
	kelly2old->SetLineColor(kBlue-10);
	kelly2old->SetFillColor(kBlue-10);
	kelly2old->SetLineStyle(0);
//	kelly2old->SetFillStyle(3003);

	/*
	   TF1 *bbba05 = new TF1("BBBA05",gen_bbba05,0.,10.,0);
	   bbba05->SetLineColor(kGreen);
	   bbba05->SetLineStyle(3);
	   */

	//  TF1 *lomon = new TF1("Lomon",Lomon_GEn,0.,10.,0);
	// lomon->SetLineColor(7);
	// lomon->SetLineStyle(4);




	TMultiGraph* mgrDta = new TMultiGraph("Data","G_{E}^{n}");
	TLegend *legDta = new TLegend(.1624,.4533,.4986,.9195,"","brNDC");

	TMultiGraph* wgr = mgrDta;
	TLegend *wlg = legDta;

	// the data
	legDta->SetBorderSize(0); // turn off border
	legDta->SetFillStyle(0);

	datafile_t *f = datafiles;
	TGraph* ogr=0;
	TGraph *gr;
	while ( f && f->filename ) {
		ogr=OneGraph(f);

		if (ogr) {
			gr = fromGEntoGEnGd(ogr);

			if(gr->GetMarkerColor()==kRed){
				if( gr->GetMarkerStyle()==22){
					gr->SetMarkerSize(1.6);
				} else {
					gr->SetMarkerSize(1.2);
				}
			}

			if (f->lnpt) {
				mgrDta->Add(gr,f->lnpt);
				if( f->label[0] != 'x' )
					legDta->AddEntry(gr,f->label,f->lnpt);
			}
			gr->SetLineStyle(0);
			mgrDta->Add(gr,"p");

			if( f->label[0] != 'x' ){
				if( gr->GetMarkerColor()==kRed ){
					legDta->AddEntry(gr,f->label,"p");
				} else {
					if( addoneplot == 0 ){
//						legDta->AddEntry(gr,"Prior to JLab","p");
						addoneplot++;
					}
				}
			}
			/*
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
			   */
		}
		f++;
	}


	mgrDta->Draw("p");
	  legDta->Draw();

	TMultiGraph* mgrThry = new TMultiGraph("Theory","G_{E}^{n}");
	TLegend *legThry = new TLegend(.4253,.6928,.8204,.9131,"","brNDC");

	wgr = mgrThry;
	wlg = legThry;

	// the theory
	wlg->SetBorderSize(0); // turn off border
	wlg->SetFillStyle(0);

	f = theoryfiles1;
	gr=0;
	Bool_t isfill;
	while ( f && f->filename ) {
		ogr=OneGraph(f);
		ogr->SetLineWidth(2);
		isfill = kFALSE;
		if (ogr) {
			gr = fromGEntoGEnGd(ogr);
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

#ifdef OUR_ERR
//	ourbbbaband->Draw("sameF");
//	ourbbba->Draw("same");
	kelly2old->Draw("sameF");
	kelly2->Draw("sameF");
//	legThry->AddEntry(kelly2, "Galster-type Fit", "F");
//	legThry->AddEntry(kelly2old, "Galster-type Fit", "F");
#endif

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
	//  nofsilab->Draw("same");
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
	//    ourfit->Draw("same");
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
	legThry->AddEntry(roberts_curve,"q(qq) Faddeev Eq., Cloet (2008)","l");
#endif
	//  legThry->AddEntry(bbba05,"BBBA05","l");
	//  legThry->AddEntry(lomon, "Lomon", "l");
	// legThry->AddEntry(ourfit, "Our Fit", "l");

	legThry->Draw();
//	legDta->Draw();

	mgrDta->Draw("p");
//	 legDta->Draw();

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

	replax->SetTitle("");
	replax->Draw();
	replaxtop->Draw();

#ifdef SHIFT_TITLE
	TPaveLabel *shifted = new TPaveLabel( 0.0127, 0.3, 0.1638, 0.5, "G_{En}/G_{D}", "NDC");
	shifted->SetTextFont(62);
	shifted->SetTextAngle(90);
	shifted->SetFillStyle(0);
	shifted->SetBorderSize(0);
	shifted->SetFillColor(kWhite);
	shifted->Draw("same");
#endif

	TLine *axisline = new TLine(xaxis_min, 0.0, xaxis_max, 0.0 );
	axisline->Draw("same");


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

TGraphAsymmErrors *fromGEntoGEnGd(TGraph *ogr) {
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
		y /= Gd;
		ey1 /= Gd;
		ey2 /= Gd;
		gr->SetPoint(i,x,y);
		gr->SetPointError(i,ex1,ex2,ey1,ey2);
	}
	return gr;
}

