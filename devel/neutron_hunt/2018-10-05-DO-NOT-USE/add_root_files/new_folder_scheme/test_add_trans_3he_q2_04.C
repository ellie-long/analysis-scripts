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


void test_add_trans_3he_q2_04() {
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


	if (includeVetos){Target = TFile::Open( "/home/ellie/physics/e05-102/analysis-scripts/devel/neutron_hunt/results/targ_ssa/with_vetos/trans_3he_q2_04.root", "RECREATE" );}
	if (!includeVetos){Target = TFile::Open( "/home/ellie/physics/e05-102/analysis-scripts/devel/neutron_hunt/results/targ_ssa/without_vetos/trans_3he_q2_04.root", "RECREATE" );}

	FileList = new TList();
	if (includeVetos && dataTypeStr=="n")
	{
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21693.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21694.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21695.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21696.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21697.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21698.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21699.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21700.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21701.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21702.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21703.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21704.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21705.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21706.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21707.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21708.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21709.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21710.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21711.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21712.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21713.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21717.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21718.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21724.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21725.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21726.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21727.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21728.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21729.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21730.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21731.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21732.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21733.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21735.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21736.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21737.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21738.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21739.root") );

/*
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21740.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21741.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21742.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21743.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21744.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21745.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21746.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21747.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21755.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21756.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21757.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21758.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21759.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21760.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21761.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21762.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21763.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21764.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21765.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21766.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21767.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21768.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21769.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21770.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21771.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21772.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21779.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21781.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21782.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21783.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21784.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21786.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21787.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21788.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21789.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21790.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21791.root") );
//		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21792.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21794.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21795.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21796.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21797.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21798.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21799.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21800.root") );


		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22139.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22140.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22141.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22142.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22143.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22144.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22145.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22146.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22147.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22148.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22149.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22150.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22151.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22152.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22153.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22154.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22155.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22156.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22157.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22158.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22159.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22160.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22162.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22163.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22164.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22165.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22166.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22167.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22168.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22169.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22170.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22171.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22172.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22173.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22174.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22175.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22176.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22177.root") );

//		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22179.root") );

		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22180.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22181.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22182.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22183.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22184.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22185.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22186.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22187.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22188.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22189.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22190.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22191.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22192.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22193.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22194.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22195.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22196.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22197.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22198.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22199.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22200.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22201.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22202.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22204.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22206.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22207.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22208.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22209.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22210.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22211.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22214.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22215.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22216.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22217.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22218.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22219.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22220.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22221.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22223.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22224.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22225.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22226.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22227.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22228.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22229.root") );

		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22230.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22231.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22232.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22233.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22234.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22235.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22237.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22238.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22240.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22251.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22252.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22253.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22254.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22255.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22256.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22257.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22258.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22259.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22260.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22261.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22262.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22263.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22264.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22265.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22266.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22267.root") );
*/
/*		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22280.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22281.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22298.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22299.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22300.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22301.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22304.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22305.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22306.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22307.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22308.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22309.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22310.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22311.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22312.root") );
*/

	}
	if (includeVetos && dataTypeStr=="p")
	{
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21693.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21694.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21695.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21696.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21697.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21698.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21699.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21700.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21701.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21702.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21703.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21704.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21705.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21706.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21707.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21708.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21709.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21710.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21711.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21712.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21713.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21717.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21718.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21724.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21725.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21726.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21727.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21728.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21729.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21730.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21731.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21732.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21733.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21735.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21736.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21737.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21738.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21739.root") );
/*

		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21740.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21741.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21742.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21743.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21744.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21745.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21746.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21747.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21755.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21756.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21757.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21758.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21759.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21760.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21761.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21762.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21763.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21764.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21765.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21766.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21767.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21768.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21769.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21770.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21771.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21772.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21779.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21781.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21782.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21783.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21784.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21786.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21787.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21788.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21789.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21790.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21791.root") );
//		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21792.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21794.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21795.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21796.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21797.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21798.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21799.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21800.root") );
*/

		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22139.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22140.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22141.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22142.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22143.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22144.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22145.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22146.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22147.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22148.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22149.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22150.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22151.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22152.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22153.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22154.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22155.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22156.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22157.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22158.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22159.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22160.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22162.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22163.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22164.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22165.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22166.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22167.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22168.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22169.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22170.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22171.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22172.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22173.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22174.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22175.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22176.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22177.root") );

//		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22179.root") );

		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22180.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22181.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22182.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22183.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22184.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22185.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22186.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22187.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22188.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22189.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22190.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22191.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22192.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22193.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22194.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22195.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22196.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22197.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22198.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22199.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22200.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22201.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22202.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22204.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22206.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22207.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22208.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22209.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22210.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22211.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22214.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22215.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22216.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22217.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22218.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22219.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22220.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22221.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22223.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22224.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22225.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22226.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22227.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22228.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22229.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22230.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22231.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22232.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22233.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22234.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22235.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22237.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22238.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22240.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22251.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22252.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22253.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22254.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22255.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22256.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22257.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22258.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22259.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22260.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22261.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22262.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22263.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22264.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22265.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22266.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22267.root") );
/*		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22280.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22281.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22298.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22299.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22300.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22301.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22304.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22305.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22306.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22307.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22308.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22309.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22310.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22311.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22312.root") );
*/


	
	}

	if (!includeVetos)
	{
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21693.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21694.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21695.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21696.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21697.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21698.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21699.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21700.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21701.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21702.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21703.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21704.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21705.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21706.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21707.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21708.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21709.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21710.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21711.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21712.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21713.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21717.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21718.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21724.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21725.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21726.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21727.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21728.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21729.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21730.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21731.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21732.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21733.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21735.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21736.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21737.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21738.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21739.root") );

		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21740.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21741.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21742.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21743.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21744.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21745.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21746.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21747.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21755.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21756.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21757.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21758.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21759.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21760.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21761.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21762.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21763.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21764.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21765.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21766.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21767.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21768.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21769.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21770.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21771.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21772.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21779.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21781.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21782.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21783.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21784.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21786.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21787.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21788.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21789.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21790.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21791.root") );
//		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21792.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21794.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21795.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21796.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21797.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21798.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21799.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_21800.root") );


		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22139.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22140.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22141.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22142.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22143.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22144.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22145.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22146.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22147.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22148.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22149.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22150.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22151.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22152.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22153.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22154.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22155.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22156.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22157.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22158.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22159.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22160.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22162.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22163.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22164.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22165.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22166.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22167.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22168.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22169.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22170.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22171.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22172.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22173.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22174.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22175.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22176.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22177.root") );

//		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22179.root") );

		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22180.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22181.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22182.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22183.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22184.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22185.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22186.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22187.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22188.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22189.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22190.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22191.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22192.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22193.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22194.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22195.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22196.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22197.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22198.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22199.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22200.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22201.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22202.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22204.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22206.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22207.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22208.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22209.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22210.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22211.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22214.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22215.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22216.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22217.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22218.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22219.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22220.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22221.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22223.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22224.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22225.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22226.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22227.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22228.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22229.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22230.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22231.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22232.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22233.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22234.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22235.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22237.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22238.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22240.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22251.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22252.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22253.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22254.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22255.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22256.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22257.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22258.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22259.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22260.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22261.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22262.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22263.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22264.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22265.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22266.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22267.root") );
/*		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22280.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22281.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22298.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22299.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22300.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22301.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22304.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22305.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22306.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22307.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22308.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22309.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22310.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22311.root") );
		FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/q2_04_trans_3he/no_vetos-hand_target_asym_vs_nu_for_run_22312.root") );
*/



	}

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
