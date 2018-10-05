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


void add_beam_dsa_calibration_v_q2_1() {
	// in an interactive ROOT session, edit the file names
	// Target and FileList, then
	// root > .L hadd.C
	// root > hadd()

	FileList = new TList();
	bool includeVetos;
	TString vetoStr;
	cout << "Include vetos? (y or n)" << endl;
	cin >> vetoStr;
	if (vetoStr=="y") {includeVetos=true;}
	if (vetoStr=="n") {includeVetos=false;}
	cout << "includeVetos = " << includeVetos << endl;

	TString targ;
	cout << "Which target? (c=carbon, h=hydrogen, d=deuterium, e=empty, n=nitrogen)" << endl;
	cin >> targ;
	cout << "targ: " << targ << endl;

	if (targ=="c")
	{
		if (includeVetos)
		{
			Target = TFile::Open( "/home/ellie/physics/e05-102/analysis-scripts/devel/neutron_hunt/results/beam_dsa/with_vetos/v_carbon_q2_1.root", "RECREATE" );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_20591.root") );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_20731.root") );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_20732.root") );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_20733.root") );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_20734.root") );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_22380.root") );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_22389.root") );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_22425.root") );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_22426.root") );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_22461.root") );
		}
		if (!includeVetos)
		{
			Target = TFile::Open( "/home/ellie/physics/e05-102/analysis-scripts/devel/neutron_hunt/results/beam_dsa/without_vetos/v_carbon_q2_1.root", "RECREATE" );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_20591.root") );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_20731.root") );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_20732.root") );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_20733.root") );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_20734.root") );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_22380.root") );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_22389.root") );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_22425.root") );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_22426.root") );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_carbon/hand_beam_asym_vs_nu_for_run_22461.root") );
		}
	}
	if (targ=="h")
	{
		if (includeVetos)
		{
			Target = TFile::Open( "/home/ellie/physics/e05-102/analysis-scripts/devel/neutron_hunt/results/beam_dsa/with_vetos/v_hydrogen_q2_1.root", "RECREATE" );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_hydrogen/hand_beam_asym_vs_nu_for_run_20791.root") );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_hydrogen/hand_beam_asym_vs_nu_for_run_20792.root") );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_hydrogen/hand_beam_asym_vs_nu_for_run_22441.root") );
		}
		if (!includeVetos)
		{
			Target = TFile::Open( "/home/ellie/physics/e05-102/analysis-scripts/devel/neutron_hunt/results/beam_dsa/without_vetos/v_hydrogen_q2_1.root", "RECREATE" );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_hydrogen/hand_beam_asym_vs_nu_for_run_20791.root") );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_hydrogen/hand_beam_asym_vs_nu_for_run_20792.root") );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_hydrogen/hand_beam_asym_vs_nu_for_run_22441.root") );
		}
	}
	if (targ=="d")
	{
		if (includeVetos)
		{
			Target = TFile::Open( "/home/ellie/physics/e05-102/analysis-scripts/devel/neutron_hunt/results/beam_dsa/with_vetos/v_deuterium_q2_1.root", "RECREATE" );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_deuterium/hand_beam_asym_vs_nu_for_run_20736.root") );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_deuterium/hand_beam_asym_vs_nu_for_run_20737.root") );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_deuterium/hand_beam_asym_vs_nu_for_run_22463.root") );
		}
		if (!includeVetos)
		{
			Target = TFile::Open( "/home/ellie/physics/e05-102/analysis-scripts/devel/neutron_hunt/results/beam_dsa/without_vetos/v_deuterium_q2_1.root", "RECREATE" );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_deuterium/hand_beam_asym_vs_nu_for_run_20736.root") );
			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_deuterium/hand_beam_asym_vs_nu_for_run_20737.root") );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_deuterium/hand_beam_asym_vs_nu_for_run_22463.root") );
		}
	}
	if (targ=="e")
	{
		if (includeVetos)
		{
			Target = TFile::Open( "/home/ellie/physics/e05-102/analysis-scripts/devel/neutron_hunt/results/beam_dsa/with_vetos/v_empty_q2_1.root", "RECREATE" );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_empty/hand_beam_asym_vs_nu_for_run_22440.root") );
		}
		if (!includeVetos)
		{
			Target = TFile::Open( "/home/ellie/physics/e05-102/analysis-scripts/devel/neutron_hunt/results/beam_dsa/without_vetos/v_empty_q2_1.root", "RECREATE" );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_empty/hand_beam_asym_vs_nu_for_run_22440.root") );
		}
	}
	if (targ=="n")
	{
		if (includeVetos)
		{
			Target = TFile::Open( "/home/ellie/physics/e05-102/analysis-scripts/devel/neutron_hunt/results/beam_dsa/with_vetos/v_nitrogen_q2_1.root", "RECREATE" );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/with_vetos/q2_1_nitrogen/hand_beam_asym_vs_nu_for_run_22442.root") );
		}
		if (!includeVetos)
		{
			Target = TFile::Open( "/home/ellie/physics/e05-102/analysis-scripts/devel/neutron_hunt/results/beam_dsa/without_vetos/v_nitrogen_q2_1.root", "RECREATE" );
//			FileList->Add( TFile::Open("/work/halla/e05102/disk1/ellie/results/without_vetos/q2_1_nitrogen/hand_beam_asym_vs_nu_for_run_22442.root") );
		}
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
