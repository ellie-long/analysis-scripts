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


void add_long_3he_q2_04() {
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


	if (includeVetos){Target = TFile::Open( "../../../analysis-scripts/devel/neutron_hunt/results/targ_ssa/with_vetos/long_3he_q2_04.root", "RECREATE" );}
	if (!includeVetos){Target = TFile::Open( "../../../analysis-scripts/devel/neutron_hunt/results/targ_ssa/without_vetos/long_3he_q2_04.root", "RECREATE" );}

	FileList = new TList();
	if (includeVetos && dataTypeStr=="n")
	{
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21813.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21820.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21821.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21822.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21823.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21824.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21825.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21826.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21827.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21828.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21830.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21831.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21832.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21833.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21834.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21835.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21836.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21837.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21839.root") );

		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21840.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21841.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21842.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21843.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21844.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21845.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21846.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21847.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21851.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21852.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21853.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21855.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21856.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21857.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21858.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21859.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21860.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21861.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21862.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21863.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21864.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21865.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21866.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21867.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21868.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21869.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21870.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21871.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21873.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21876.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21877.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21878.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21879.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21880.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21881.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21882.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21883.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21884.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21885.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21886.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21887.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21888.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21889.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21900.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21901.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21902.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21903.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21904.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21905.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21906.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21907.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21908.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21909.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21910.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21911.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21912.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21913.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21914.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21915.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21916.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21917.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21918.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21919.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21920.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21921.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21922.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21923.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21924.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21925.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21926.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21927.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21928.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21929.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21930.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21935.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21936.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21937.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21938.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21954.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21955.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21957.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21958.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21959.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21960.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21961.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21962.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21963.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21964.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21965.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21966.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21967.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21968.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21969.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21970.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21971.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21972.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21986.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21969.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21970.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21971.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21972.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21986.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21987.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21988.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21989.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21990.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21991.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21992.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21993.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21994.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_21995.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22005.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22006.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22007.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22008.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22009.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22010.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22011.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22012.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22013.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22015.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22016.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22017.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22018.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22019.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22020.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22033.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22034.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22035.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22036.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22037.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22038.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22039.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22040.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22041.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22043.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22044.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22045.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22046.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22047.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22048.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22049.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22050.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22052.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22057.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22058.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22059.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22060.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22061.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22062.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22063.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22064.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22065.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22066.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22067.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22068.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22069.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22070.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22071.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22072.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22073.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22074.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22075.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22077.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22078.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22079.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22080.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22081.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22083.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22085.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22086.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22087.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22088.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22089.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22090.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22091.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22092.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22093.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22094.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22095.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22096.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22097.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22099.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22100.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22101.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22102.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22104.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22106.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22107.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22108.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22109.root") );
/*		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22110.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22111.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22116.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22117.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22118.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22119.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22122.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22123.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22124.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22125.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22126.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22128.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22130.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22131.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22132.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22133.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22134.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22135.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22136.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/neutron_cuts-hand_target_asym_vs_nu_for_run_22137.root") );
*/

	}
	if (includeVetos && dataTypeStr=="p")
	{
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21813.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21820.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21821.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21822.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21823.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21824.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21825.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21826.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21827.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21828.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21830.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21831.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21832.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21833.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21834.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21835.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21836.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21837.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21839.root") );

		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21840.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21841.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21842.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21843.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21844.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21845.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21846.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21847.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21851.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21852.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21853.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21855.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21856.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21857.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21858.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21859.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21860.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21861.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21862.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21863.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21864.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21865.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21866.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21867.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21868.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21869.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21870.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21871.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21873.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21876.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21877.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21878.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21879.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21880.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21881.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21882.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21883.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21884.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21885.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21886.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21887.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21888.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21889.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21900.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21901.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21902.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21903.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21904.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21905.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21906.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21907.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21908.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21909.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21910.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21911.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21912.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21913.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21914.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21915.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21916.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21917.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21918.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21919.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21920.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21921.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21922.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21923.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21924.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21925.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21926.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21927.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21928.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21929.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21930.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21935.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21936.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21937.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21938.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21954.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21955.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21957.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21958.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21959.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21960.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21961.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21962.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21963.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21964.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21965.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21966.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21967.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21968.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21969.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21970.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21971.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21972.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21986.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21969.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21970.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21971.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21972.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21986.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21987.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21988.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21989.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21990.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21991.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21992.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21993.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21994.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_21995.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22005.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22006.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22007.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22008.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22009.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22010.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22011.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22012.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22013.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22015.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22016.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22017.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22018.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22019.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22020.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22033.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22034.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22035.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22036.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22037.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22038.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22039.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22040.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22041.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22043.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22044.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22045.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22046.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22047.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22048.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22049.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22050.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22052.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22057.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22058.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22059.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22060.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22061.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22062.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22063.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22064.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22065.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22066.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22067.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22068.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22069.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22070.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22071.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22072.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22073.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22074.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22075.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22077.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22078.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22079.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22080.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22081.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22083.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22085.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22086.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22087.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22088.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22089.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22090.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22091.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22092.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22093.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22094.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22095.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22096.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22097.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22099.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22100.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22101.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22102.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22104.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22106.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22107.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22108.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22109.root") );
/*		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22110.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22111.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22116.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22117.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22118.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22119.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22122.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22123.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22124.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22125.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22126.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22128.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22130.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22131.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22132.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22133.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22134.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22135.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22136.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/proton_cuts-hand_target_asym_vs_nu_for_run_22137.root") );
*/

	}

	if (!includeVetos)
	{

		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21813.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21820.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21821.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21822.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21823.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21824.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21825.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21826.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21827.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21828.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21830.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21831.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21832.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21833.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21834.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21835.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21836.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21837.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21839.root") );

		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21840.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21841.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21842.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21843.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21844.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21845.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21846.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21847.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21851.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21852.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21853.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21855.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21856.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21857.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21858.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21859.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21860.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21861.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21862.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21863.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21864.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21865.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21866.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21867.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21868.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21869.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21870.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21871.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21873.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21876.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21877.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21878.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21879.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21880.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21881.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21882.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21883.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21884.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21885.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21886.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21887.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21888.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21889.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21900.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21901.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21902.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21903.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21904.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21905.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21906.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21907.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21908.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21909.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21910.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21911.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21912.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21913.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21914.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21915.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21916.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21917.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21918.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21919.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21920.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21921.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21922.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21923.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21924.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21925.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21926.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21927.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21928.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21929.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21930.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21935.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21936.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21937.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21938.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21954.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21955.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21957.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21958.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21959.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21960.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21961.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21962.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21963.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21964.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21965.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21966.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21967.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21968.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21969.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21970.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21971.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21972.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21986.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21969.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21970.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21971.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21972.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21986.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21987.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21988.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21989.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21990.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21991.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21992.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21993.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21994.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_21995.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22005.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22006.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22007.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22008.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22009.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22010.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22011.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22012.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22013.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22015.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22016.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22017.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22018.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22019.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22020.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22033.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22034.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22035.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22036.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22037.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22038.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22039.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22040.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22041.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22043.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22044.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22045.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22046.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22047.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22048.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22049.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22050.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22052.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22057.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22058.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22059.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22060.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22061.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22062.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22063.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22064.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22065.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22066.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22067.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22068.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22069.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22070.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22071.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22072.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22073.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22074.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22075.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22077.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22078.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22079.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22080.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22081.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22083.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22085.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22086.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22087.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22088.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22089.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22090.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22091.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22092.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22093.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22094.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22095.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22096.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22097.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22099.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22100.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22101.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22102.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22104.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22106.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22107.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22108.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22109.root") );
/*		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22110.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22111.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22116.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22117.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22118.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22119.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22122.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22123.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22124.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22125.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22126.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22128.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22130.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22131.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22132.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22133.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22134.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22135.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22136.root") );
		FileList->Add( TFile::Open("../../../results/q2_04_long_3he/no_vetos-hand_target_asym_vs_nu_for_run_22137.root") );
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

   cout << "All done!" << endl;
   gROOT->ProcessLine(".q");

}
