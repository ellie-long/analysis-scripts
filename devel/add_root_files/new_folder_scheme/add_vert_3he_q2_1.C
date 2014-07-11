//macro to add histogram files
//NOTE: This macro is kept for back compatibility only.
//Use instead the executable $ROOTSYS/bin/hadd
//
//This macro will add histograms from a list of root files and write them
//to a target root file. The target file is newly created and must not be
//identical to one of the source files.
//
//Author: Sven A. Schmidt, sven.schmidt@cern.ch
//Date:   13.2.2001

//This code is based on the hadd.C example by Rene Brun and Dirk Geppert,
//which had a problem with directories more than one level deep.
//(see macro hadd_old.C for this previous implementation).
//
//The macro from Sven has been enhanced by
//   Anne-Sylvie Nicollerat <Anne-Sylvie.Nicollerat@cern.ch>
// to automatically add Trees (via a chain of trees).
//
//To use this macro, modify the file names in function hadd.
//
//NB: This macro is provided as a tutorial.
//    Use $ROOTSYS/bin/hadd to merge many histogram files



#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"

TList *FileList;
TFile *Target;

void MergeRootfile( TDirectory *target, TList *sourcelist );


void add_vert_3he_q2_1() {
	// in an interactive ROOT session, edit the file names
	// Target and FileList, then
	// root > .L hadd.C
	// root > hadd()

	bool includeVetos;
	TString vetoStr;
	cout << "Include vetos? (y or n)" << endl;
	cin >> vetoStr;
	if (vetoStr=="y") {includeVetos=true;}
	if (vetoStr=="n") {includeVetos=false;}
	cout << "includeVetos = " << includeVetos << endl;

        TString dataTypeStr;
        if (includeVetos)
        {
                cout << "Protons or Neutrons? (p or n)" << endl;
                cin >> dataTypeStr;
        }

	if(includeVetos) {Target = TFile::Open( "/home/ellie/physics/e05-102/analysis-scripts/devel/neutron_hunt/results/targ_ssa/with_vetos/vert_3he_q2_1.root", "RECREATE" );}
	if(!includeVetos) {Target = TFile::Open( "/home/ellie/physics/e05-102/analysis-scripts/devel/neutron_hunt/results/targ_ssa/without_vetos/vert_3he_q2_1.root", "RECREATE" );}

	FileList = new TList();
	if (includeVetos && dataTypeStr=="n")
	{
//	vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv Yawei's Bad Runs vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
/*		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20596.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20597.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20599.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20648.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20654.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20701.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20707.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20726.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20742.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20744.root") );
//	^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
*/		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20598.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20600.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20601.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20609.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20610.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20611.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20612.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20613.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20614.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20615.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20642.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20643.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20646.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20647.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20649.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20650.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20651.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20652.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20653.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20655.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20656.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20657.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20658.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20659.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20660.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20662.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20663.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20664.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20665.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20666.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20667.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20668.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20669.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20670.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20671.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20672.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20673.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20674.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20682.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20683.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20684.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20685.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20686.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20687.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20688.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20689.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20691.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20692.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20693.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20694.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20695.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20696.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20698.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20699.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20700.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20702.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20703.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20706.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20709.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20710.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20712.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20713.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20714.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20715.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20716.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20717.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20719.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20720.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20721.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20722.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20723.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20724.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20725.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20727.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20729.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20730.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20738.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20739.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20740.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20741.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20745.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20746.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20749.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20750.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20751.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20752.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20754.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20755.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20756.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20757.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20759.root") );

// *****************************************************************
//		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20789.root") );
		/*   FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20814.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20815.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20816.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20817.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20818.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20819.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20820.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20821.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20822.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20823.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20824.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20827.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20828.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20830.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20844.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20865.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20866.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20867.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20868.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20869.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20870.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20871.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20872.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20873.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20874.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20875.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20876.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20877.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_20878.root") );
*/	}
	if (includeVetos && dataTypeStr=="p")
	{
//	vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv Yawei's Bad Runs vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
/*		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20596.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20597.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20599.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20648.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20654.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20701.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20707.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20726.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20742.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20744.root") );
//	^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
*/		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20598.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20600.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20601.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20609.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20610.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20611.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20612.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20613.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20614.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20615.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20642.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20643.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20646.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20647.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20649.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20650.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20651.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20652.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20653.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20655.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20656.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20657.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20658.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20659.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20660.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20662.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20663.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20664.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20665.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20666.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20667.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20668.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20669.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20670.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20671.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20672.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20673.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20674.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20682.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20683.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20684.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20685.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20686.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20687.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20688.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20689.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20691.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20692.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20693.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20694.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20695.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20696.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20698.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20699.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20700.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20702.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20703.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20706.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20709.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20710.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20712.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20713.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20714.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20715.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20716.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20717.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20719.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20720.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20721.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20722.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20723.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20724.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20725.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20727.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20729.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20730.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20738.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20739.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20740.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20741.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20745.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20746.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20749.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20750.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20751.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20752.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20754.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20755.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20756.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20757.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20759.root") );

// *****************************************************************
//		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20789.root") );
		/*   FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20814.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20815.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20816.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20817.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20818.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20819.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20820.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20821.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20822.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20823.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20824.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20827.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20828.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20830.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20844.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20865.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20866.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20867.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20868.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20869.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20870.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20871.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20872.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20873.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20874.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20875.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20876.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20877.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/proton_cuts-hand_target_asym_vs_nu_for_run_20878.root") );
*/	}
	if (!includeVetos)
	{
//	vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv Yawei's Bad Runs vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
/*		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20596.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20599.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20648.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20654.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20701.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20707.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20726.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20742.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20744.root") );
// 	^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
*/		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20597.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20598.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20600.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20601.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20609.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20610.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20611.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20612.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20613.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20614.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20615.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20642.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20643.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20646.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20647.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20649.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20650.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20651.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20652.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20653.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20655.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20656.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20657.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20658.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20659.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20660.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20662.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20663.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20664.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20665.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20666.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20667.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20668.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20669.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20670.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20671.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20672.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20673.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20674.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20682.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20683.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20684.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20685.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20686.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20687.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20688.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20689.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20691.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20692.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20693.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20694.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20695.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20696.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20698.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20699.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20700.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20702.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20703.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20706.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20709.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20710.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20712.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20713.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20714.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20715.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20716.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20717.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20719.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20720.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20721.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20722.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20723.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20724.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20725.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20727.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20729.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20730.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20738.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20739.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20740.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20741.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20745.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20746.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20749.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20750.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20751.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20752.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20754.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20755.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20756.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20757.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20759.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20789.root") );
		/*   FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20814.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20815.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20816.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20817.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20818.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20819.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20820.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20821.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20822.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20823.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20824.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20827.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20828.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20830.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20844.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20865.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20866.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20867.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20868.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20869.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20870.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20871.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20872.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20873.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20874.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20875.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20876.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20877.root") );
		FileList->Add( TFile::Open("/home/ellie/physics/e05-102/results/q2_1_vert_3he/no_vetos-hand_target_asym_vs_nu_for_run_20878.root") );
*/	}


	MergeRootfile( Target, FileList );

}

void MergeRootfile( TDirectory *target, TList *sourcelist ) {

   //  cout << "Target path: " << target->GetPath() << endl;
   TString path( (char*)strstr( target->GetPath(), ":" ) );
   path.Remove( 0, 2 );

   TFile *first_source = (TFile*)sourcelist->First();
   first_source->cd( path );
   TDirectory *current_sourcedir = gDirectory;
   //gain time, do not add the objects in the list in memory
   Bool_t status = TH1::AddDirectoryStatus();
   TH1::AddDirectory(kFALSE);

   // loop over all keys in this directory
   TChain *globChain = 0;
   TIter nextkey( current_sourcedir->GetListOfKeys() );
   TKey *key, *oldkey=0;
   while ( (key = (TKey*)nextkey())) {

      //keep only the highest cycle number for each key
      if (oldkey && !strcmp(oldkey->GetName(),key->GetName())) continue;

      // read object from first source file
      first_source->cd( path );
      TObject *obj = key->ReadObj();

      if ( obj->IsA()->InheritsFrom( TH1::Class() ) ) {
	 // descendant of TH1 -> merge it

	 //      cout << "Merging histogram " << obj->GetName() << endl;
	 TH1 *h1 = (TH1*)obj;

	 // loop over all source files and add the content of the
	 // correspondant histogram to the one pointed to by "h1"
	 TFile *nextsource = (TFile*)sourcelist->After( first_source );
	 while ( nextsource ) {

	    // make sure we are at the correct directory level by cd'ing to path
	    nextsource->cd( path );
	    TKey *key2 = (TKey*)gDirectory->GetListOfKeys()->FindObject(h1->GetName());
	    if (key2) {
	       TH1 *h2 = (TH1*)key2->ReadObj();
	       h1->Add( h2 );
	       delete h2;
	    }

	    nextsource = (TFile*)sourcelist->After( nextsource );
	 }
      }
      else if ( obj->IsA()->InheritsFrom( TTree::Class() ) ) {

	 // loop over all source files create a chain of Trees "globChain"
	 const char* obj_name= obj->GetName();

	 globChain = new TChain(obj_name);
	 globChain->Add(first_source->GetName());
	 TFile *nextsource = (TFile*)sourcelist->After( first_source );
	 //      const char* file_name = nextsource->GetName();
	 // cout << "file name  " << file_name << endl;
	 while ( nextsource ) {

	    globChain->Add(nextsource->GetName());
	    nextsource = (TFile*)sourcelist->After( nextsource );
	 }

      } else if ( obj->IsA()->InheritsFrom( TDirectory::Class() ) ) {
	 // it's a subdirectory

	 cout << "Found subdirectory " << obj->GetName() << endl;

	 // create a new subdir of same name and title in the target file
	 target->cd();
	 TDirectory *newdir = target->mkdir( obj->GetName(), obj->GetTitle() );

	 // newdir is now the starting point of another round of merging
	 // newdir still knows its depth within the target file via
	 // GetPath(), so we can still figure out where we are in the recursion
	 MergeRootfile( newdir, sourcelist );

      } else {

	 // object is of no type that we know or can handle
	 cout << "Unknown object type, name: "
	 << obj->GetName() << " title: " << obj->GetTitle() << endl;
      }

      // now write the merged histogram (which is "in" obj) to the target file
      // note that this will just store obj in the current directory level,
      // which is not persistent until the complete directory itself is stored
      // by "target->Write()" below
      if ( obj ) {
	 target->cd();

	 //!!if the object is a tree, it is stored in globChain...
	 if(obj->IsA()->InheritsFrom( TTree::Class() ))
	    globChain->Merge(target->GetFile(),0,"keep");
	 else
	    obj->Write( key->GetName() );
      }

   } // while ( ( TKey *key = (TKey*)nextkey() ) )

   // save modifications to target file
   target->SaveSelf(kTRUE);
   TH1::AddDirectory(status);
}
