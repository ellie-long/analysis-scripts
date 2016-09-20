// *************************************************** 
//
// This script should create a list of definitions for 
// all of the vetos and antivetos for the Hall A
// Neutron Detector 
//
// In order to use this, first add this to the top of 
// your script:
/*
	include# "hand_define_vetos.h"
*/
//
// Next, include the following boolean statements to decide
// whether we are going to use the vetos, antivetos, or have
// the antivetos act as vetos
/*
	bool includeVetos;
//	If includeVetos = false, then only good bars will be displayed. If 
//	includeVetos = true, then veto bars will be shown along with the good bars.
//	includeVetos = true;
	includeVetos = false;

	bool includeAntivetos;
//	If includeAntivetos = false, then only good bars will be displayed. If 
//	includeAntivetos = true, then antiveto bars will be shown along with the good bars.
//	includeAntivetos = true;
	includeAntivetos = false;

	bool antivetosAsVetos;
//	If antivetosAsVetos = false, then the antivetos will not be included in the veto cut
//	If antivetosAsVetos = true, then the antivetos will be included in the veto cut
//	Antivetos are the bars immediately following a goodBar
//	antivetosAsVetos = true; 
	antivetosAsVetos = false;
*/
// Then declare the min and max TDC values for the veto cuts:
// Note that this will change as the experiment goes on. For
// instance, for run 20791, min=1385 & max=1415 and for run
// 22441, min=750 & max=850
/*
	double vetoTDCcutmin = ###;
	double vetoTDCcutmin = ###;
*/
//
// Then declare these variables: 
/*
	TString veto1plane;
	TString veto1bar;
	TString veto2plane;
	TString veto2bar;
	TString veto3plane;
	TString veto3bar;
	TString veto4plane;
	TString veto4bar;
	TString veto5plane;
	TString veto5bar;
	TString veto6plane;
	TString veto6bar;
	TString antiveto1plane;
	TString antiveto1bar;
	TString antiveto2plane;
	TString antiveto2bar;
	TString antiveto3plane;
	TString antiveto3bar;
	TString allVetos;
	TString allAntivetos;
	TString vetoTDCslSt;
	TString vetoTDCsrSt;
	TCut vetoTDCsl;
	TCut vetoTDCsr;
	TCut vetoTDCs;
	TString antivetosTDCslSt;
	TString antivetosTDCsrSt;
*/
//
// And finally, add this line of code wherever you want
// to define the vetos:
/*
	hand_define_vetos(includeVetos, includeAntivetos, antivetosAsVetos, nplane, thisbar, veto1plane, veto2plane, veto3plane, veto4plane, veto5plane, veto6plane, veto1bar, veto2bar, veto3bar, veto4bar, veto5bar, veto6bar, antiveto1plane, antiveto2plane, antiveto3plane, antiveto1bar, antiveto2bar, antiveto3bar, allVetos, allAntivetos, vetoTDCslSt, vetoTDCsrSt, vetoTDCsl, vetoTDCsr, vetoTDCs, vetoTDCcutmin, vetoTDCcutmax, antivetosTDCslSt, antivetosTDCsrSt);
*/
//
//
//
// 2010-12-01
// Elena Long 
//
// Thank you, Vince, for helping me get this working
// 
// *************************************************** 

void hand_define_vetos_for_bar_by_thph(bool includeVetos, bool includeAntivetos, bool antivetosAsVetos, int nplane, int thisbar, TString& veto1plane, TString& veto2plane, TString& veto3plane, TString& veto4plane, TString& veto5plane, TString& veto6plane, TString& veto1bar, TString& veto2bar, TString& veto3bar, TString& veto4bar, TString& veto5bar, TString& veto6bar, TString& antiveto1plane, TString& antiveto2plane, TString& antiveto3plane, TString& antiveto1bar, TString& antiveto2bar, TString& antiveto3bar, TString& allVetos, TString& allAntivetos, TString& vetoTDCslSt, TString& vetoTDCsrSt, TCut& vetoTDCsl, TCut& vetoTDCsr, TCut& vetoTDCs, double vetoTDCcutmin, double vetoTDCcutmax, TString& antivetosTDCslSt, TString& antivetosTDCsrSt) {


	cout << "vvvvvvvvvvvvvvvvvvvvvvvvv hand_define_vetos_for_bar_by_thph.h vvvvvvvvvvvvvvvvvv" << endl;

	bool includeVetosPlaceKeeper = includeVetos;
	
	if (nplane==0) {includeVetos = false;}

	cout << "Running hand_define_vetos.C for p" << nplane << "b" << thisbar << " where includeVetos=" << includeVetos <<  " where includeAntivetos=" << includeAntivetos << " and antivetosAsVetos=" << antivetosAsVetos << endl;

	if (includeVetos) { cout << "Vetos Included!!!!!!!!!!!" << endl;}
	if (!includeVetos) { cout << "Vetos NOT Included!!!!!!!!!!!" << endl;}

	// These veto bars are added so that I don't double-count events
	// while looking for the proton-to-neutron conversion factor
	TString veto7plane = "";
	TString veto7bar = "";
	TString veto8plane = "";
	TString veto8bar = "";
	TString veto9plane = "";
	TString veto9bar = "";
	TString veto10plane = "";
	TString veto10bar = "";
	TString veto11plane = "";
	TString veto11bar = "";
	TString veto12plane = "";
	TString veto12bar = "";
	TString veto13plane = "";
	TString veto13bar = "";
	TString veto14plane = "";
	TString veto14bar = "";
	TString veto15plane = "";
	TString veto15bar = "";
	TString veto16plane = "";
	TString veto16bar = "";
	TString veto17plane = "";
	TString veto17bar = "";
	TString veto18plane = "";
	TString veto18bar = "";
	TString veto19plane = "";
	TString veto19bar = "";
	TString veto20plane = "";
	TString veto20bar = "";
	TString veto21plane = "";
	TString veto21bar = "";


	// This huge set of if statements defines the vetos for each good bar we're
	// going to look at. So far the Good Bar with the most vetos has 6 vetos.
	// Most of the bars do not, in which case the last different veto is repeated 
	// in the remaining veto spaves so that extra bars aren't counted.
	// It should only turn on if includeVetos is set to TRUE.
	// Hopefully this works.
	veto1plane = "";
	veto1bar = "";
	veto2plane = "";
	veto2bar = "";
	veto3plane = "";
	veto3bar = "";
	veto4plane = "";
	veto4bar = "";
	veto5plane = "";
	veto5bar = "";
	veto6plane = "";
	veto6bar = "";
	antiveto1plane = "";
	antiveto1bar = "";
	antiveto2plane = "";
	antiveto2bar = "";
	antiveto3plane = "";
	antiveto3bar = "";
	allVetos = "";
	allAntivetos = "";

	if (nplane==1){
		if (thisbar==0){
		veto1plane = "veto";   veto1bar = "0";
		veto2plane = "veto";   veto2bar = "1";
		veto3plane = "veto";   veto3bar = "1";
		veto4plane = "veto";   veto4bar = "1";
		veto5plane = "nd.p1";  veto5bar = "1";
		veto6plane = "nd.p1";  veto6bar = "1";

		veto7plane  = "nd.p1"; veto7bar  = "1";
		veto8plane  = "nd.p1"; veto8bar  = "1";
		veto9plane  = "nd.p1"; veto9bar  = "1";
		veto10plane = "nd.p1"; veto10bar = "1";
		veto11plane = "nd.p1"; veto11bar = "1";
		veto12plane = "nd.p1"; veto12bar = "1";
		veto13plane = "nd.p1"; veto13bar = "1";
		veto14plane = "nd.p1"; veto14bar = "1";
		veto15plane = "nd.p1"; veto15bar = "1";
		veto16plane = "nd.p1"; veto16bar = "1";
		veto17plane = "nd.p1"; veto17bar = "1";
		veto18plane = "nd.p1"; veto18bar = "1";
		veto19plane = "nd.p1"; veto19bar = "1";
		veto20plane = "nd.p1"; veto20bar = "1";
		veto21plane = "nd.p1"; veto21bar = "1";

		antiveto1plane = "nd.p2"; antiveto1bar = "0";
		antiveto2plane = "nd.p2"; antiveto2bar = "1";
		antiveto3plane = "nd.p2"; antiveto3bar = "1";
		}
		if (thisbar==1){
		veto1plane = "veto"; veto1bar = "0";
		veto2plane = "veto"; veto2bar = "1";
		veto3plane = "veto"; veto3bar = "1";
		veto4plane = "nd.p1"; veto4bar = "0";
		veto5plane = "nd.p1"; veto5bar = "2";
		veto6plane = "nd.p1"; veto6bar = "2";

		veto7plane  = "nd.p1"; veto7bar  = "2";
		veto8plane  = "nd.p1"; veto8bar  = "2";
		veto9plane  = "nd.p1"; veto9bar  = "2";
		veto10plane = "nd.p1"; veto10bar = "2";
		veto11plane = "nd.p1"; veto11bar = "2";
		veto12plane = "nd.p1"; veto12bar = "2";
		veto13plane = "nd.p1"; veto13bar = "2";
		veto14plane = "nd.p1"; veto14bar = "2";
		veto15plane = "nd.p1"; veto15bar = "2";
		veto16plane = "nd.p1"; veto16bar = "2";
		veto17plane = "nd.p1"; veto17bar = "2";
		veto18plane = "nd.p1"; veto18bar = "2";
		veto19plane = "nd.p1"; veto19bar = "2";
		veto20plane = "nd.p1"; veto20bar = "2";
		veto21plane = "nd.p1"; veto21bar = "2";


		antiveto1plane = "nd.p2"; antiveto1bar = "0";
		antiveto2plane = "nd.p2"; antiveto2bar = "1";
		antiveto3plane = "nd.p2"; antiveto3bar = "1";
		}
		if (thisbar==2){
		veto1plane = "veto"; veto1bar = "1";
		veto2plane = "veto"; veto2bar = "2";
		veto3plane = "veto"; veto3bar = "2";
		veto4plane = "veto"; veto4bar = "2";
		veto5plane = "nd.p1"; veto5bar = "1";
		veto6plane = "nd.p1"; veto6bar = "3";

		veto7plane  = "nd.p1"; veto7bar  = "1";
		veto8plane  = "nd.p1"; veto8bar  = "1";
		veto9plane  = "nd.p1"; veto9bar  = "1";
		veto10plane = "nd.p1"; veto10bar = "1";
		veto11plane = "nd.p1"; veto11bar = "1";
		veto12plane = "nd.p1"; veto12bar = "1";
		veto13plane = "nd.p1"; veto13bar = "1";
		veto14plane = "nd.p1"; veto14bar = "1";
		veto15plane = "nd.p1"; veto15bar = "1";
		veto16plane = "nd.p1"; veto16bar = "1";
		veto17plane = "nd.p1"; veto17bar = "1";
		veto18plane = "nd.p1"; veto18bar = "1";
		veto19plane = "nd.p1"; veto19bar = "1";
		veto20plane = "nd.p1"; veto20bar = "1";
		veto21plane = "nd.p1"; veto21bar = "1";


		antiveto1plane = "nd.p2"; antiveto1bar = "1";
		antiveto2plane = "nd.p2"; antiveto2bar = "2";
		antiveto3plane = "nd.p2"; antiveto3bar = "2";
		}
		if (thisbar==3){
		veto1plane = "veto"; veto1bar = "2";
		veto2plane = "veto"; veto2bar = "3";
		veto3plane = "veto"; veto3bar = "3";
		veto4plane = "veto"; veto4bar = "3";
		veto5plane = "nd.p1"; veto5bar = "2";
		veto6plane = "nd.p1"; veto6bar = "4";

		veto7plane  = "nd.p1"; veto7bar  = "2";
		veto8plane  = "nd.p1"; veto8bar  = "2";
		veto9plane  = "nd.p1"; veto9bar  = "2";
		veto10plane = "nd.p1"; veto10bar = "2";
		veto11plane = "nd.p1"; veto11bar = "2";
		veto12plane = "nd.p1"; veto12bar = "2";
		veto13plane = "nd.p1"; veto13bar = "2";
		veto14plane = "nd.p1"; veto14bar = "2";
		veto15plane = "nd.p1"; veto15bar = "2";
		veto16plane = "nd.p1"; veto16bar = "2";
		veto17plane = "nd.p1"; veto17bar = "2";
		veto18plane = "nd.p1"; veto18bar = "2";
		veto19plane = "nd.p1"; veto19bar = "2";
		veto20plane = "nd.p1"; veto20bar = "2";
		veto21plane = "nd.p1"; veto21bar = "2";


		antiveto1plane = "nd.p2"; antiveto1bar = "2";
		antiveto2plane = "nd.p2"; antiveto2bar = "3";
		antiveto3plane = "nd.p2"; antiveto3bar = "3";
		}
		if (thisbar==4){
		veto1plane = "veto"; veto1bar = "3";
		veto2plane = "veto"; veto2bar = "4";
		veto3plane = "veto"; veto3bar = "4";
		veto4plane = "veto"; veto4bar = "4";
		veto5plane = "nd.p1"; veto5bar = "3";
		veto6plane = "nd.p1"; veto6bar = "5";

		veto7plane  = "nd.p1"; veto7bar  = "3";
		veto8plane  = "nd.p1"; veto8bar  = "3";
		veto9plane  = "nd.p1"; veto9bar  = "3";
		veto10plane = "nd.p1"; veto10bar = "3";
		veto11plane = "nd.p1"; veto11bar = "3";
		veto12plane = "nd.p1"; veto12bar = "3";
		veto13plane = "nd.p1"; veto13bar = "3";
		veto14plane = "nd.p1"; veto14bar = "3";
		veto15plane = "nd.p1"; veto15bar = "3";
		veto16plane = "nd.p1"; veto16bar = "3";
		veto17plane = "nd.p1"; veto17bar = "3";
		veto18plane = "nd.p1"; veto18bar = "3";
		veto19plane = "nd.p1"; veto19bar = "3";
		veto20plane = "nd.p1"; veto20bar = "3";
		veto21plane = "nd.p1"; veto21bar = "3";


		antiveto1plane = "nd.p2"; antiveto1bar = "3";
		antiveto2plane = "nd.p2"; antiveto2bar = "4";
		antiveto3plane = "nd.p2"; antiveto3bar = "4";
		}
		if (thisbar==5){
		veto1plane = "veto"; veto1bar = "4";
		veto2plane = "veto"; veto2bar = "5";
		veto3plane = "veto"; veto3bar = "5";
		veto4plane = "veto"; veto4bar = "5";
		veto5plane = "nd.p1"; veto5bar = "4";
		veto6plane = "nd.p1"; veto6bar = "6";

		veto7plane  = "nd.p1"; veto7bar  = "4";
		veto8plane  = "nd.p1"; veto8bar  = "4";
		veto9plane  = "nd.p1"; veto9bar  = "4";
		veto10plane = "nd.p1"; veto10bar = "4";
		veto11plane = "nd.p1"; veto11bar = "4";
		veto12plane = "nd.p1"; veto12bar = "4";
		veto13plane = "nd.p1"; veto13bar = "4";
		veto14plane = "nd.p1"; veto14bar = "4";
		veto15plane = "nd.p1"; veto15bar = "4";
		veto16plane = "nd.p1"; veto16bar = "4";
		veto17plane = "nd.p1"; veto17bar = "4";
		veto18plane = "nd.p1"; veto18bar = "4";
		veto19plane = "nd.p1"; veto19bar = "4";
		veto20plane = "nd.p1"; veto20bar = "4";
		veto21plane = "nd.p1"; veto21bar = "4";


		antiveto1plane = "nd.p2"; antiveto1bar = "3";
		antiveto2plane = "nd.p2"; antiveto2bar = "4";
		antiveto3plane = "nd.p2"; antiveto3bar = "5";
		}
		if (thisbar==6){
		veto1plane = "veto"; veto1bar = "5";
		veto2plane = "veto"; veto2bar = "6";
		veto3plane = "veto"; veto3bar = "6";
		veto4plane = "veto"; veto4bar = "6";
		veto5plane = "nd.p1"; veto5bar = "5";
		veto6plane = "nd.p1"; veto6bar = "7";

		veto7plane  = "nd.p1"; veto7bar  = "5";
		veto8plane  = "nd.p1"; veto8bar  = "5";
		veto9plane  = "nd.p1"; veto9bar  = "5";
		veto10plane = "nd.p1"; veto10bar = "5";
		veto11plane = "nd.p1"; veto11bar = "5";
		veto12plane = "nd.p1"; veto12bar = "5";
		veto13plane = "nd.p1"; veto13bar = "5";
		veto14plane = "nd.p1"; veto14bar = "5";
		veto15plane = "nd.p1"; veto15bar = "5";
		veto16plane = "nd.p1"; veto16bar = "5";
		veto17plane = "nd.p1"; veto17bar = "5";
		veto18plane = "nd.p1"; veto18bar = "5";
		veto19plane = "nd.p1"; veto19bar = "5";
		veto20plane = "nd.p1"; veto20bar = "5";
		veto21plane = "nd.p1"; veto21bar = "5";


		antiveto1plane = "nd.p2"; antiveto1bar = "4";
		antiveto2plane = "nd.p2"; antiveto2bar = "5";
		antiveto3plane = "nd.p2"; antiveto3bar = "5";
		}
		if (thisbar==7){ 
		veto1plane = "veto"; veto1bar = "6";
		veto2plane = "veto"; veto2bar = "7";
		veto3plane = "veto"; veto3bar = "7";
		veto4plane = "veto"; veto4bar = "7";
		veto5plane = "nd.p1"; veto5bar = "6";
		veto6plane = "nd.p1"; veto6bar = "8";

		veto7plane  = "nd.p1"; veto7bar  = "6";
		veto8plane  = "nd.p1"; veto8bar  = "6";
		veto9plane  = "nd.p1"; veto9bar  = "6";
		veto10plane = "nd.p1"; veto10bar = "6";
		veto11plane = "nd.p1"; veto11bar = "6";
		veto12plane = "nd.p1"; veto12bar = "6";
		veto13plane = "nd.p1"; veto13bar = "6";
		veto14plane = "nd.p1"; veto14bar = "6";
		veto15plane = "nd.p1"; veto15bar = "6";
		veto16plane = "nd.p1"; veto16bar = "6";
		veto17plane = "nd.p1"; veto17bar = "6";
		veto18plane = "nd.p1"; veto18bar = "6";
		veto19plane = "nd.p1"; veto19bar = "6";
		veto20plane = "nd.p1"; veto20bar = "6";
		veto21plane = "nd.p1"; veto21bar = "6";


		antiveto1plane = "nd.p2"; antiveto1bar = "5";
		antiveto2plane = "nd.p2"; antiveto2bar = "6";
		antiveto3plane = "nd.p2"; antiveto3bar = "6";
		}
		if (thisbar==8){
		veto1plane = "veto"; veto1bar = "7";
		veto2plane = "veto"; veto2bar = "8"; 
		veto3plane = "veto"; veto3bar = "10"; 
		veto4plane = "veto"; veto4bar = "10";
		veto5plane = "nd.p1"; veto5bar = "7";
		veto6plane = "nd.p1"; veto6bar = "9";

		veto7plane  = "nd.p1"; veto7bar  = "7";
		veto8plane  = "nd.p1"; veto8bar  = "7";
		veto9plane  = "nd.p1"; veto9bar  = "7";
		veto10plane = "nd.p1"; veto10bar = "7";
		veto11plane = "nd.p1"; veto11bar = "7";
		veto12plane = "nd.p1"; veto12bar = "7";
		veto13plane = "nd.p1"; veto13bar = "7";
		veto14plane = "nd.p1"; veto14bar = "7";
		veto15plane = "nd.p1"; veto15bar = "7";
		veto16plane = "nd.p1"; veto16bar = "7";
		veto17plane = "nd.p1"; veto17bar = "7";
		veto18plane = "nd.p1"; veto18bar = "7";
		veto19plane = "nd.p1"; veto19bar = "7";
		veto20plane = "nd.p1"; veto20bar = "7";
		veto21plane = "nd.p1"; veto21bar = "7";


		antiveto1plane = "nd.p2"; antiveto1bar = "6";
		antiveto2plane = "nd.p2"; antiveto2bar = "7";
		antiveto3plane = "nd.p2"; antiveto3bar = "7";
		}
		if (thisbar==9){
		veto1plane = "veto"; veto1bar = "8";
		veto2plane = "veto"; veto2bar = "9"; 
		veto3plane = "veto"; veto3bar = "10";
		veto4plane = "veto"; veto4bar = "11"; 
		veto5plane = "nd.p1"; veto5bar = "8";
		veto6plane = "nd.p1"; veto6bar = "10";

		veto7plane  = "nd.p1"; veto7bar  = "8";
		veto8plane  = "nd.p1"; veto8bar  = "8";
		veto9plane  = "nd.p1"; veto9bar  = "8";
		veto10plane = "nd.p1"; veto10bar = "8";
		veto11plane = "nd.p1"; veto11bar = "8";
		veto12plane = "nd.p1"; veto12bar = "8";
		veto13plane = "nd.p1"; veto13bar = "8";
		veto14plane = "nd.p1"; veto14bar = "8";
		veto15plane = "nd.p1"; veto15bar = "8";
		veto16plane = "nd.p1"; veto16bar = "8";
		veto17plane = "nd.p1"; veto17bar = "8";
		veto18plane = "nd.p1"; veto18bar = "8";
		veto19plane = "nd.p1"; veto19bar = "8";
		veto20plane = "nd.p1"; veto20bar = "8";
		veto21plane = "nd.p1"; veto21bar = "8";


		antiveto1plane = "nd.p2"; antiveto1bar = "7";
		antiveto2plane = "nd.p2"; antiveto2bar = "8";
		antiveto3plane = "nd.p2"; antiveto3bar = "8";
		}
		if (thisbar==10){
		veto1plane = "veto"; veto1bar = "9";
		veto2plane = "veto"; veto2bar = "11";
		veto3plane = "veto"; veto3bar = "12";
		veto4plane = "veto"; veto4bar = "12";
		veto5plane = "nd.p1"; veto5bar = "9";
		veto6plane = "nd.p1"; veto6bar = "11";

		veto7plane  = "nd.p1"; veto7bar  = "9";
		veto8plane  = "nd.p1"; veto8bar  = "9";
		veto9plane  = "nd.p1"; veto9bar  = "9";
		veto10plane = "nd.p1"; veto10bar = "9";
		veto11plane = "nd.p1"; veto11bar = "9";
		veto12plane = "nd.p1"; veto12bar = "9";
		veto13plane = "nd.p1"; veto13bar = "9";
		veto14plane = "nd.p1"; veto14bar = "9";
		veto15plane = "nd.p1"; veto15bar = "9";
		veto16plane = "nd.p1"; veto16bar = "9";
		veto17plane = "nd.p1"; veto17bar = "9";
		veto18plane = "nd.p1"; veto18bar = "9";
		veto19plane = "nd.p1"; veto19bar = "9";
		veto20plane = "nd.p1"; veto20bar = "9";
		veto21plane = "nd.p1"; veto21bar = "9";


		antiveto1plane = "nd.p2"; antiveto1bar = "7";
		antiveto2plane = "nd.p2"; antiveto2bar = "8";
		antiveto3plane = "nd.p2"; antiveto3bar = "9";
		}
		if (thisbar==11){
//		veto1plane = "veto"; veto1bar = "9";
//		veto2plane = "veto"; veto2bar = "12";
//		veto3plane = "veto"; veto3bar = "13";
//		veto4plane = "veto"; veto4bar = "13";
		veto1plane = "nd.p1"; veto1bar = "10";
		veto2plane = "nd.p1"; veto2bar = "10";
		veto3plane = "nd.p1"; veto3bar = "10";
		veto4plane = "nd.p1"; veto4bar = "10";

		veto5plane = "nd.p1"; veto5bar = "10";
		veto6plane = "nd.p1"; veto6bar = "12";

		veto7plane  = "nd.p1"; veto7bar  = "10";
		veto8plane  = "nd.p1"; veto8bar  = "10";
		veto9plane  = "nd.p1"; veto9bar  = "10";
		veto10plane = "nd.p1"; veto10bar = "10";
		veto11plane = "nd.p1"; veto11bar = "10";
		veto12plane = "nd.p1"; veto12bar = "10";
		veto13plane = "nd.p1"; veto13bar = "10";
		veto14plane = "nd.p1"; veto14bar = "10";
		veto15plane = "nd.p1"; veto15bar = "10";
		veto16plane = "nd.p1"; veto16bar = "10";
		veto17plane = "nd.p1"; veto17bar = "10";
		veto18plane = "nd.p1"; veto18bar = "10";
		veto19plane = "nd.p1"; veto19bar = "10";
		veto20plane = "nd.p1"; veto20bar = "10";
		veto21plane = "nd.p1"; veto21bar = "10";


		antiveto1plane = "nd.p2"; antiveto1bar = "8";
		antiveto2plane = "nd.p2"; antiveto2bar = "9";
		antiveto3plane = "nd.p2"; antiveto3bar = "9";
		}
		if (thisbar==12){
//		veto1plane = "veto"; veto1bar = "13";
//		veto2plane = "veto"; veto2bar = "14";
//		veto3plane = "veto"; veto3bar = "14";
//		veto4plane = "veto"; veto4bar = "14";
		veto1plane = "nd.p1"; veto1bar = "11";
		veto2plane = "nd.p1"; veto2bar = "11";
		veto3plane = "nd.p1"; veto3bar = "11";
		veto4plane = "nd.p1"; veto4bar = "11";
		veto5plane = "nd.p1"; veto5bar = "11";
		veto6plane = "nd.p1"; veto6bar = "13";
		veto7plane  = "nd.p1"; veto7bar  = "11";
		veto8plane  = "nd.p1"; veto8bar  = "11";
		veto9plane  = "nd.p1"; veto9bar  = "11";
		veto10plane = "nd.p1"; veto10bar = "11";
		veto11plane = "nd.p1"; veto11bar = "11";
		veto12plane = "nd.p1"; veto12bar = "11";
		veto13plane = "nd.p1"; veto13bar = "11";
		veto14plane = "nd.p1"; veto14bar = "11";
		veto15plane = "nd.p1"; veto15bar = "11";
		veto16plane = "nd.p1"; veto16bar = "11";
		veto17plane = "nd.p1"; veto17bar = "11";
		veto18plane = "nd.p1"; veto18bar = "11";
		veto19plane = "nd.p1"; veto19bar = "11";
		veto20plane = "nd.p1"; veto20bar = "11";
		veto21plane = "nd.p1"; veto21bar = "11";
		antiveto1plane = "nd.p2"; antiveto1bar = "9";
		antiveto2plane = "nd.p2"; antiveto2bar = "10";
		antiveto3plane = "nd.p2"; antiveto3bar = "10";
		}
		if (thisbar==13){
//		veto1plane = "veto"; veto1bar = "13";
//		veto2plane = "veto"; veto2bar = "14";
//		veto3plane = "veto"; veto3bar = "15";
//		veto4plane = "veto"; veto4bar = "15";
		veto5plane = "nd.p1"; veto5bar = "12";
		veto6plane = "nd.p1"; veto6bar = "14";

		veto1plane  = "nd.p1";  veto1bar = "12";
		veto2plane  = "nd.p1";  veto2bar = "12";
		veto3plane  = "nd.p1";  veto3bar = "12";
		veto4plane  = "nd.p1";  veto4bar = "12";
		veto7plane  = "nd.p1"; veto7bar  = "12";
		veto8plane  = "nd.p1"; veto8bar  = "12";
		veto9plane  = "nd.p1"; veto9bar  = "12";
		veto10plane = "nd.p1"; veto10bar = "12";
		veto11plane = "nd.p1"; veto11bar = "12";
		veto12plane = "nd.p1"; veto12bar = "12";
		veto13plane = "nd.p1"; veto13bar = "12";
		veto14plane = "nd.p1"; veto14bar = "12";
		veto15plane = "nd.p1"; veto15bar = "12";
		veto16plane = "nd.p1"; veto16bar = "12";
		veto17plane = "nd.p1"; veto17bar = "12";
		veto18plane = "nd.p1"; veto18bar = "12";
		veto19plane = "nd.p1"; veto19bar = "12";
		veto20plane = "nd.p1"; veto20bar = "12";
		veto21plane = "nd.p1"; veto21bar = "12";

		antiveto1plane = "nd.p2"; antiveto1bar = "10";
		antiveto2plane = "nd.p2"; antiveto2bar = "11";
		antiveto3plane = "nd.p2"; antiveto3bar = "11";
		}
		if (thisbar==14){
//		veto1plane = "veto"; veto1bar = "14";
//		veto2plane = "veto"; veto2bar = "15";
//		veto3plane = "veto"; veto3bar = "16";
//		veto4plane = "veto"; veto4bar = "16";
		veto5plane = "nd.p1"; veto5bar = "13";
		veto6plane = "nd.p1"; veto6bar = "15";

		veto1plane  = "nd.p1";  veto1bar = "13";
		veto2plane  = "nd.p1";  veto2bar = "13";
		veto3plane  = "nd.p1";  veto3bar = "13";
		veto4plane  = "nd.p1";  veto4bar = "13";
		veto7plane  = "nd.p1"; veto7bar  = "13";
		veto8plane  = "nd.p1"; veto8bar  = "13";
		veto9plane  = "nd.p1"; veto9bar  = "13";
		veto10plane = "nd.p1"; veto10bar = "13";
		veto11plane = "nd.p1"; veto11bar = "13";
		veto12plane = "nd.p1"; veto12bar = "13";
		veto13plane = "nd.p1"; veto13bar = "13";
		veto14plane = "nd.p1"; veto14bar = "13";
		veto15plane = "nd.p1"; veto15bar = "13";
		veto16plane = "nd.p1"; veto16bar = "13";
		veto17plane = "nd.p1"; veto17bar = "13";
		veto18plane = "nd.p1"; veto18bar = "13";
		veto19plane = "nd.p1"; veto19bar = "13";
		veto20plane = "nd.p1"; veto20bar = "13";
		veto21plane = "nd.p1"; veto21bar = "13";

		antiveto1plane = "nd.p2"; antiveto1bar = "11";
		antiveto2plane = "nd.p2"; antiveto2bar = "12";
		antiveto3plane = "nd.p2"; antiveto3bar = "12";
		}
		if (thisbar==15){
//		veto1plane = "veto"; veto1bar = "15";
//		veto2plane = "veto"; veto2bar = "16";
//		veto3plane = "veto"; veto3bar = "17";
//		veto4plane = "veto"; veto4bar = "17";
		veto5plane = "nd.p1"; veto5bar = "14";
		veto6plane = "nd.p1"; veto6bar = "16";

		veto1plane  = "nd.p1";  veto1bar = "14";
		veto2plane  = "nd.p1";  veto2bar = "14";
		veto3plane  = "nd.p1";  veto3bar = "14";
		veto4plane  = "nd.p1";  veto4bar = "14";
		veto7plane  = "nd.p1"; veto7bar  = "14";
		veto8plane  = "nd.p1"; veto8bar  = "14";
		veto9plane  = "nd.p1"; veto9bar  = "14";
		veto10plane = "nd.p1"; veto10bar = "14";
		veto11plane = "nd.p1"; veto11bar = "14";
		veto12plane = "nd.p1"; veto12bar = "14";
		veto13plane = "nd.p1"; veto13bar = "14";
		veto14plane = "nd.p1"; veto14bar = "14";
		veto15plane = "nd.p1"; veto15bar = "14";
		veto16plane = "nd.p1"; veto16bar = "14";
		veto17plane = "nd.p1"; veto17bar = "14";
		veto18plane = "nd.p1"; veto18bar = "14";
		veto19plane = "nd.p1"; veto19bar = "14";
		veto20plane = "nd.p1"; veto20bar = "14";
		veto21plane = "nd.p1"; veto21bar = "14";

		antiveto1plane = "nd.p2"; antiveto1bar ="11";
		antiveto2plane = "nd.p2"; antiveto2bar = "12";
		antiveto3plane = "nd.p2"; antiveto3bar = "12";
		}
		if (thisbar==16){
		veto1plane = "veto"; veto1bar = "16";
		veto2plane = "veto"; veto2bar = "17";
		veto3plane = "veto"; veto3bar = "18";
		veto4plane = "veto"; veto4bar = "18";
		veto5plane = "nd.p1"; veto5bar = "15";
		veto6plane = "nd.p1"; veto6bar = "17";
		veto7plane  = "nd.p1"; veto7bar  = "15";
		veto8plane  = "nd.p1"; veto8bar  = "15";
		veto9plane  = "nd.p1"; veto9bar  = "15";
		veto10plane = "nd.p1"; veto10bar = "15";
		veto11plane = "nd.p1"; veto11bar = "15";
		veto12plane = "nd.p1"; veto12bar = "15";
		veto13plane = "nd.p1"; veto13bar = "15";
		veto14plane = "nd.p1"; veto14bar = "15";
		veto15plane = "nd.p1"; veto15bar = "15";
		veto16plane = "nd.p1"; veto16bar = "15";
		veto17plane = "nd.p1"; veto17bar = "15";
		veto18plane = "nd.p1"; veto18bar = "15";
		veto19plane = "nd.p1"; veto19bar = "15";
		veto20plane = "nd.p1"; veto20bar = "15";
		veto21plane = "nd.p1"; veto21bar = "15";


		antiveto1plane = "nd.p2"; antiveto1bar = "12";
		antiveto2plane = "nd.p2"; antiveto2bar = "13";
		antiveto3plane = "nd.p2"; antiveto3bar = "13";
		}
		if (thisbar==17){
		veto1plane = "veto"; veto1bar = "17";
		veto2plane = "veto"; veto2bar = "18";
		veto3plane = "veto"; veto3bar = "19";
		veto4plane = "veto"; veto4bar = "19";
		veto5plane = "nd.p1"; veto5bar = "16";
		veto6plane = "nd.p1"; veto6bar = "18";
		veto7plane  = "nd.p1"; veto7bar  = "16";
		veto8plane  = "nd.p1"; veto8bar  = "16";
		veto9plane  = "nd.p1"; veto9bar  = "16";
		veto10plane = "nd.p1"; veto10bar = "16";
		veto11plane = "nd.p1"; veto11bar = "16";
		veto12plane = "nd.p1"; veto12bar = "16";
		veto13plane = "nd.p1"; veto13bar = "16";
		veto14plane = "nd.p1"; veto14bar = "16";
		veto15plane = "nd.p1"; veto15bar = "16";
		veto16plane = "nd.p1"; veto16bar = "16";
		veto17plane = "nd.p1"; veto17bar = "16";
		veto18plane = "nd.p1"; veto18bar = "16";
		veto19plane = "nd.p1"; veto19bar = "16";
		veto20plane = "nd.p1"; veto20bar = "16";
		veto21plane = "nd.p1"; veto21bar = "16";


		antiveto1plane = "nd.p2"; antiveto1bar = "13";
		antiveto2plane = "nd.p2"; antiveto2bar = "14";
		antiveto3plane = "nd.p2"; antiveto3bar = "14";
		}
		if (thisbar==18){
		veto1plane = "veto"; veto1bar = "18";
		veto2plane = "veto"; veto2bar = "19";
		veto3plane = "veto"; veto3bar = "20";
		veto4plane = "veto"; veto4bar = "22";
		veto5plane = "nd.p1"; veto5bar = "17";
		veto6plane = "nd.p1"; veto6bar = "19";
		veto7plane  = "nd.p1"; veto7bar  = "17";
		veto8plane  = "nd.p1"; veto8bar  = "17";
		veto9plane  = "nd.p1"; veto9bar  = "17";
		veto10plane = "nd.p1"; veto10bar = "17";
		veto11plane = "nd.p1"; veto11bar = "17";
		veto12plane = "nd.p1"; veto12bar = "17";
		veto13plane = "nd.p1"; veto13bar = "17";
		veto14plane = "nd.p1"; veto14bar = "17";
		veto15plane = "nd.p1"; veto15bar = "17";
		veto16plane = "nd.p1"; veto16bar = "17";
		veto17plane = "nd.p1"; veto17bar = "17";
		veto18plane = "nd.p1"; veto18bar = "17";
		veto19plane = "nd.p1"; veto19bar = "17";
		veto20plane = "nd.p1"; veto20bar = "17";
		veto21plane = "nd.p1"; veto21bar = "17";

		antiveto1plane = "nd.p2"; antiveto1bar = "14";
		antiveto2plane = "nd.p2"; antiveto2bar = "15";
		antiveto3plane = "nd.p2"; antiveto3bar = "15";
		}
		if (thisbar==19){
		veto1plane = "veto"; veto1bar = "19";
		veto2plane = "veto"; veto2bar = "20";
		veto3plane = "veto"; veto3bar = "22";
		veto4plane = "veto"; veto4bar = "22";
		veto5plane = "nd.p1"; veto5bar = "18";
		veto6plane = "nd.p1"; veto6bar = "20";
		veto7plane  = "nd.p1"; veto7bar  = "18";
		veto8plane  = "nd.p1"; veto8bar  = "18";
		veto9plane  = "nd.p1"; veto9bar  = "18";
		veto10plane = "nd.p1"; veto10bar = "18";
		veto11plane = "nd.p1"; veto11bar = "18";
		veto12plane = "nd.p1"; veto12bar = "18";
		veto13plane = "nd.p1"; veto13bar = "18";
		veto14plane = "nd.p1"; veto14bar = "18";
		veto15plane = "nd.p1"; veto15bar = "18";
		veto16plane = "nd.p1"; veto16bar = "18";
		veto17plane = "nd.p1"; veto17bar = "18";
		veto18plane = "nd.p1"; veto18bar = "18";
		veto19plane = "nd.p1"; veto19bar = "18";
		veto20plane = "nd.p1"; veto20bar = "18";
		veto21plane = "nd.p1"; veto21bar = "18";


		antiveto1plane = "nd.p2"; antiveto1bar = "15";
		antiveto2plane = "nd.p2"; antiveto2bar = "16";
		antiveto3plane = "nd.p2"; antiveto3bar = "16";
		}
		if (thisbar==20){
		veto1plane = "veto"; veto1bar = "20";
		veto2plane = "veto"; veto2bar = "21";
		veto3plane = "veto"; veto3bar = "22";
		veto4plane = "veto"; veto4bar = "23";
		veto5plane = "nd.p1"; veto5bar = "19";
		veto6plane = "nd.p1"; veto6bar = "21";
		veto7plane  = "nd.p1"; veto7bar  = "19";
		veto8plane  = "nd.p1"; veto8bar  = "19";
		veto9plane  = "nd.p1"; veto9bar  = "19";
		veto10plane = "nd.p1"; veto10bar = "19";
		veto11plane = "nd.p1"; veto11bar = "19";
		veto12plane = "nd.p1"; veto12bar = "19";
		veto13plane = "nd.p1"; veto13bar = "19";
		veto14plane = "nd.p1"; veto14bar = "19";
		veto15plane = "nd.p1"; veto15bar = "19";
		veto16plane = "nd.p1"; veto16bar = "19";
		veto17plane = "nd.p1"; veto17bar = "19";
		veto18plane = "nd.p1"; veto18bar = "19";
		veto19plane = "nd.p1"; veto19bar = "19";
		veto20plane = "nd.p1"; veto20bar = "19";
		veto21plane = "nd.p1"; veto21bar = "19";


		antiveto1plane = "nd.p2"; antiveto1bar = "15";
		antiveto2plane = "nd.p2"; antiveto2bar = "16";
		antiveto3plane = "nd.p2"; antiveto3bar = "17";
		}
		if (thisbar==21){
		veto1plane = "veto"; veto1bar = "21";
		veto2plane = "veto"; veto2bar = "23";
		veto3plane = "veto"; veto3bar = "24";
		veto4plane = "veto"; veto4bar = "24";
		veto5plane = "nd.p1"; veto5bar = "20";
		veto6plane = "nd.p1"; veto6bar = "22";
		veto7plane  = "nd.p1"; veto7bar  = "20";
		veto8plane  = "nd.p1"; veto8bar  = "20";
		veto9plane  = "nd.p1"; veto9bar  = "20";
		veto10plane = "nd.p1"; veto10bar = "20";
		veto11plane = "nd.p1"; veto11bar = "20";
		veto12plane = "nd.p1"; veto12bar = "20";
		veto13plane = "nd.p1"; veto13bar = "20";
		veto14plane = "nd.p1"; veto14bar = "20";
		veto15plane = "nd.p1"; veto15bar = "20";
		veto16plane = "nd.p1"; veto16bar = "20";
		veto17plane = "nd.p1"; veto17bar = "20";
		veto18plane = "nd.p1"; veto18bar = "20";
		veto19plane = "nd.p1"; veto19bar = "20";
		veto20plane = "nd.p1"; veto20bar = "20";
		veto21plane = "nd.p1"; veto21bar = "20";


		antiveto1plane = "nd.p2"; antiveto1bar = "16";
		antiveto2plane = "nd.p2"; antiveto2bar = "17";
		antiveto3plane = "nd.p2"; antiveto3bar = "17";
		}
		if (thisbar==22){
		veto1plane = "veto"; veto1bar = "24";
		veto2plane = "veto"; veto2bar = "25";
		veto3plane = "veto"; veto3bar = "25";
		veto4plane = "veto"; veto4bar = "25";
		veto5plane = "nd.p1"; veto5bar = "21";
		veto6plane = "nd.p1"; veto6bar = "23";
		antiveto1plane = "nd.p2"; antiveto1bar = "17";
		antiveto2plane = "nd.p2"; antiveto2bar = "18";
		antiveto3plane = "nd.p2"; antiveto3bar = "18";
		}
		if (thisbar==23){
		veto1plane = "veto"; veto1bar = "25";
		veto2plane = "veto"; veto2bar = "26";
		veto3plane = "veto"; veto3bar = "26";
		veto4plane = "veto"; veto4bar = "26";
		veto5plane = "nd.p1"; veto5bar = "22";
		veto6plane = "nd.p1"; veto6bar = "24";
		antiveto1plane = "nd.p2"; antiveto1bar = "18";
		antiveto2plane = "nd.p2"; antiveto2bar = "19";
		antiveto3plane = "nd.p2"; antiveto3bar = "19";
		}	
		if (thisbar==24){
		veto1plane = "veto"; veto1bar = "26";
		veto2plane = "veto"; veto2bar = "27";
		veto3plane = "veto"; veto3bar = "27";
		veto4plane = "veto"; veto4bar = "27";
		veto5plane = "nd.p1"; veto5bar = "23";
		veto6plane = "nd.p1"; veto6bar = "25";
		antiveto1plane = "nd.p2"; antiveto1bar = "19";
		antiveto2plane = "nd.p2"; antiveto2bar = "20";
		antiveto3plane = "nd.p2"; antiveto3bar = "20";
		}	
		if (thisbar==25){
		veto1plane = "veto"; veto1bar = "27";
		veto2plane = "veto"; veto2bar = "28";
		veto3plane = "veto"; veto3bar = "28";
		veto4plane = "veto"; veto4bar = "28";
		veto5plane = "nd.p1"; veto5bar = "24";
		veto6plane = "nd.p1"; veto6bar = "26";
		antiveto1plane = "nd.p2"; antiveto1bar = "19";
		antiveto2plane = "nd.p2"; antiveto2bar = "20";
		antiveto3plane = "nd.p2"; antiveto3bar = "21";
		}	
		if (thisbar==26){
		veto1plane = "veto"; veto1bar = "27";
		veto2plane = "veto"; veto2bar = "28";
		veto3plane = "veto"; veto3bar = "29";
		veto4plane = "veto"; veto4bar = "29";
		veto5plane = "nd.p1"; veto5bar = "25";
		veto6plane = "nd.p1"; veto6bar = "27";
		antiveto1plane = "nd.p2"; antiveto1bar = "20";
		antiveto2plane = "nd.p2"; antiveto2bar = "21";
		antiveto3plane = "nd.p2"; antiveto3bar = "21";
		}	
		if (thisbar==27){
		veto1plane = "veto"; veto1bar = "28";
		veto2plane = "veto"; veto2bar = "29";
		veto3plane = "veto"; veto3bar = "30";
		veto4plane = "veto"; veto4bar = "30";
		veto5plane = "nd.p1"; veto5bar = "26";
		veto6plane = "nd.p1"; veto6bar = "28";
		antiveto1plane = "nd.p2"; antiveto1bar = "21";
		antiveto2plane = "nd.p2"; antiveto2bar = "22";
		antiveto3plane = "nd.p2"; antiveto3bar = "22";
		}	
		if (thisbar==28){
		veto1plane = "veto"; veto1bar = "29";
		veto2plane = "veto"; veto2bar = "30";
		veto3plane = "veto"; veto3bar = "31";
		veto4plane = "veto"; veto4bar = "31";
		veto5plane = "nd.p1"; veto5bar = "27";
		veto6plane = "nd.p1"; veto6bar = "29";
		antiveto1plane = "nd.p2"; antiveto1bar = "22";
		antiveto2plane = "nd.p2"; antiveto2bar = "23";
		antiveto3plane = "nd.p2"; antiveto3bar = "23";
		}	
		if (thisbar==29){
		veto1plane = "veto"; veto1bar = "30";
		veto2plane = "veto"; veto2bar = "31";
		veto3plane = "veto"; veto3bar = "31";
		veto4plane = "veto"; veto4bar = "31";
		veto5plane = "nd.p1"; veto5bar = "28";
		veto6plane = "nd.p1"; veto6bar = "28";
		antiveto1plane = "nd.p2"; antiveto1bar = "22";
		antiveto2plane = "nd.p2"; antiveto2bar = "23";
		antiveto3plane = "nd.p2"; antiveto3bar = "23";
		}	
	}
	if (nplane==2){
		if (thisbar==0){
		veto1plane = "nd.p1"; veto1bar = "0";
		veto2plane = "nd.p1"; veto2bar = "1";
		veto3plane = "nd.p2"; veto3bar = "1";
		veto4plane = "nd.p2"; veto4bar = "1";
		veto5plane = "nd.p2"; veto5bar = "1";
		veto6plane = "nd.p2"; veto6bar = "1";
		antiveto1plane = "nd.p3"; antiveto1bar = "0";
		antiveto2plane = "nd.p3"; antiveto2bar = "0";
		antiveto3plane = "nd.p3"; antiveto3bar = "0";
		}
		if (thisbar==1){
		veto1plane = "nd.p1"; veto1bar = "1";
		veto2plane = "nd.p1"; veto2bar = "2";
		veto3plane = "nd.p2"; veto3bar = "0";
		veto4plane = "nd.p2"; veto4bar = "2";
		veto5plane = "nd.p2"; veto5bar = "2";
		veto6plane = "nd.p2"; veto6bar = "2";
		antiveto1plane = "nd.p3"; antiveto1bar = "0";
		antiveto2plane = "nd.p3"; antiveto2bar = "1";
		antiveto3plane = "nd.p3"; antiveto3bar = "1";
		}
		if (thisbar==2){
		veto1plane = "nd.p1"; veto1bar = "2";
		veto2plane = "nd.p1"; veto2bar = "3";
		veto3plane = "nd.p2"; veto3bar = "1";
		veto4plane = "nd.p2"; veto4bar = "3";
		veto5plane = "nd.p2"; veto5bar = "3";
		veto6plane = "nd.p2"; veto6bar = "3";
		antiveto1plane = "nd.p3"; antiveto1bar = "1";
		antiveto2plane = "nd.p3"; antiveto2bar = "2";
		antiveto3plane = "nd.p3"; antiveto3bar = "2";
		}
		if (thisbar==3){
		veto1plane = "nd.p1"; veto1bar = "3";
		veto2plane = "nd.p1"; veto2bar = "4";
		veto3plane = "nd.p1"; veto3bar = "5";
		veto4plane = "nd.p2"; veto4bar = "2";
		veto5plane = "nd.p2"; veto5bar = "4";
		veto6plane = "nd.p2"; veto6bar = "4";
		antiveto1plane = "nd.p3"; antiveto1bar = "2";
		antiveto2plane = "nd.p3"; antiveto2bar = "3";
		antiveto3plane = "nd.p3"; antiveto3bar = "3";
		}
		if (thisbar==4){
		veto1plane = "nd.p1"; veto1bar = "4";
		veto2plane = "nd.p1"; veto2bar = "5";
		veto3plane = "nd.p1"; veto3bar = "6";
		veto4plane = "nd.p2"; veto4bar = "3";
		veto5plane = "nd.p2"; veto5bar = "5";
		veto6plane = "nd.p2"; veto6bar = "5";
		antiveto1plane = "nd.p3"; antiveto1bar = "3";
		antiveto2plane = "nd.p3"; antiveto2bar = "4";
		antiveto3plane = "nd.p3"; antiveto3bar = "4";
		}
		if (thisbar==5){
		veto1plane = "nd.p1"; veto1bar = "6";
		veto2plane = "nd.p1"; veto2bar = "7";
		veto3plane = "nd.p2"; veto3bar = "4";
		veto4plane = "nd.p2"; veto4bar = "6";
		veto5plane = "nd.p2"; veto5bar = "6";
		veto6plane = "nd.p2"; veto6bar = "6";
		antiveto1plane = "nd.p3"; antiveto1bar = "4";
		antiveto2plane = "nd.p3"; antiveto2bar = "5";
		antiveto3plane = "nd.p3"; antiveto3bar = "5";
		}
		if (thisbar==6){
		veto1plane = "nd.p1"; veto1bar = "7";
		veto2plane = "nd.p1"; veto2bar = "8";
		veto3plane = "nd.p2"; veto3bar = "5";
		veto4plane = "nd.p2"; veto4bar = "7";
		veto5plane = "nd.p2"; veto5bar = "7";
		veto6plane = "nd.p2"; veto6bar = "7";
		antiveto1plane = "nd.p3"; antiveto1bar = "4";
		antiveto2plane = "nd.p3"; antiveto2bar = "5";
		antiveto3plane = "nd.p3"; antiveto3bar = "5";
		}
		if (thisbar==7){ 
		veto1plane = "nd.p1"; veto1bar = "8";
		veto2plane = "nd.p1"; veto2bar = "9";
		veto3plane = "nd.p1"; veto3bar = "10";
		veto4plane = "nd.p2"; veto4bar = "6";
		veto5plane = "nd.p2"; veto5bar = "8";
		veto6plane = "nd.p2"; veto6bar = "8";
		antiveto1plane = "nd.p3"; antiveto1bar = "5";
		antiveto2plane = "nd.p3"; antiveto2bar = "6";
		antiveto3plane = "nd.p3"; antiveto3bar = "6";
		}
		if (thisbar==8){
		veto1plane = "nd.p1"; veto1bar = "9";
		veto2plane = "nd.p1"; veto2bar = "10"; 
		veto3plane = "nd.p1"; veto3bar = "11"; 
		veto4plane = "nd.p2"; veto4bar = "7";
		veto5plane = "nd.p2"; veto5bar = "9";
		veto6plane = "nd.p2"; veto6bar = "9";

		veto7plane = "nd.p1"; veto7bar = "12";
		veto8plane = "nd.p1"; veto8bar = "13";
		veto9plane = "nd.p1"; veto9bar = "14";
		veto10plane = "nd.p1"; veto10bar = "15";

		antiveto1plane = "nd.p3"; antiveto1bar = "6";
		antiveto2plane = "nd.p3"; antiveto2bar = "7";
		antiveto3plane = "nd.p3"; antiveto3bar = "7";
		}
		if (thisbar==9){
		veto1plane = "nd.p1"; veto1bar = "11";
		veto2plane = "nd.p1"; veto2bar = "12"; 
		veto3plane = "nd.p2"; veto3bar = "8";
		veto4plane = "nd.p2"; veto4bar = "10"; 
		veto5plane = "nd.p2"; veto5bar = "10";
		veto6plane = "nd.p2"; veto6bar = "10";

		veto7plane = "nd.p1"; veto7bar = "12";
		veto8plane = "nd.p1"; veto8bar = "13";
		veto9plane = "nd.p1"; veto9bar = "14";
		veto10plane = "nd.p1"; veto10bar = "15";

		antiveto1plane = "nd.p3"; antiveto1bar = "7";
		antiveto2plane = "nd.p3"; antiveto2bar = "8";
		antiveto3plane = "nd.p3"; antiveto3bar = "8";
		}
		if (thisbar==10){
		veto1plane = "nd.p1"; veto1bar = "12";
		veto2plane = "nd.p1"; veto2bar = "13";
		veto3plane = "nd.p2"; veto3bar = "9";
		veto4plane = "nd.p2"; veto4bar = "11";
		veto5plane = "nd.p1"; veto5bar = "11";
		veto6plane = "nd.p1"; veto6bar = "14";

		veto7plane = "nd.p1"; veto7bar = "11";
		veto8plane = "nd.p1"; veto8bar = "13";
		veto9plane = "nd.p1"; veto9bar = "14";
		veto10plane = "nd.p1"; veto10bar = "15";

//		antiveto1plane = "nd.p3"; antiveto1bar = "8";
//		antiveto2plane = "nd.p3"; antiveto2bar = "9";
//		antiveto3plane = "nd.p3"; antiveto3bar = "10";

		antiveto1plane = "nd.p3"; antiveto1bar = "8";
		antiveto2plane = "nd.p3"; antiveto2bar = "9";
		antiveto3plane = "nd.p4"; antiveto3bar = "5";
		}
		if (thisbar==11){
		veto1plane = "nd.p1"; veto1bar = "13";
		veto2plane = "nd.p1"; veto2bar = "14";
		veto3plane = "nd.p1"; veto3bar = "15";
		veto4plane = "nd.p2"; veto4bar = "10";
		veto5plane = "nd.p2"; veto5bar = "12";
		veto6plane = "nd.p2"; veto6bar = "12";

		veto7plane = "nd.p1"; veto7bar = "11";
		veto8plane = "nd.p1"; veto8bar = "12";
		veto9plane = "nd.p1"; veto9bar = "13";
		veto10plane = "nd.p1"; veto10bar = "14";
		veto11plane = "nd.p1"; veto11bar = "15";

		antiveto1plane = "nd.p3"; antiveto1bar = "9";
		antiveto2plane = "nd.p3"; antiveto2bar = "10";
		antiveto3plane = "nd.p3"; antiveto3bar = "11";
		}
		if (thisbar==12){
		veto1plane = "nd.p1"; veto1bar = "14";
		veto2plane = "nd.p1"; veto2bar = "15";
		veto3plane = "nd.p1"; veto3bar = "16";
		veto4plane = "nd.p2"; veto4bar = "11";
		veto5plane = "nd.p2"; veto5bar = "13";
		veto6plane = "nd.p2"; veto6bar = "13";

		veto7plane = "nd.p1"; veto7bar = "11";
		veto8plane = "nd.p1"; veto8bar = "12";
		veto9plane = "nd.p1"; veto9bar = "13";
		veto10plane = "nd.p1"; veto10bar = "14";
		veto11plane = "nd.p1"; veto11bar = "15";

		antiveto1plane = "nd.p3"; antiveto1bar = "10";
		antiveto2plane = "nd.p3"; antiveto2bar = "11";
		antiveto3plane = "nd.p3"; antiveto3bar = "12";
		}
		if (thisbar==13){
		veto1plane = "nd.p1"; veto1bar = "16";
		veto2plane = "nd.p1"; veto2bar = "17";
		veto3plane = "nd.p2"; veto3bar = "12";
		veto4plane = "nd.p2"; veto4bar = "14";
		veto5plane = "nd.p2"; veto5bar = "14";
		veto6plane = "nd.p2"; veto6bar = "14";
		antiveto1plane = "nd.p3"; antiveto1bar = "12";
		antiveto2plane = "nd.p3"; antiveto2bar = "13";
		antiveto3plane = "nd.p3"; antiveto3bar = "13";
		}
		if (thisbar==14){
		veto1plane = "nd.p1"; veto1bar = "17";
		veto2plane = "nd.p1"; veto2bar = "18";
		veto3plane = "nd.p2"; veto3bar = "13";
		veto4plane = "nd.p2"; veto4bar = "15";
		veto5plane = "nd.p2"; veto5bar = "15";
		veto6plane = "nd.p2"; veto6bar = "15";
		antiveto1plane = "nd.p3"; antiveto1bar = "13";
		antiveto2plane = "nd.p3"; antiveto2bar = "14";
		antiveto3plane = "nd.p3"; antiveto3bar = "14";
		}
		if (thisbar==15){
		veto1plane = "nd.p1"; veto1bar = "18";
		veto2plane = "nd.p1"; veto2bar = "19";
		veto3plane = "nd.p1"; veto3bar = "20";
		veto4plane = "nd.p2"; veto4bar = "14";
		veto5plane = "nd.p2"; veto5bar = "16";
		veto6plane = "nd.p2"; veto6bar = "16";
		antiveto1plane = "nd.p3"; antiveto1bar = "14";
		antiveto2plane = "nd.p3"; antiveto2bar = "15";
		antiveto3plane = "nd.p3"; antiveto3bar = "15";
		}
		if (thisbar==16){
		veto1plane = "nd.p1"; veto1bar = "19";
		veto2plane = "nd.p1"; veto2bar = "20";
		veto3plane = "nd.p1"; veto3bar = "21";
		veto4plane = "nd.p2"; veto4bar = "15";
		veto5plane = "nd.p2"; veto5bar = "17";
		veto6plane = "nd.p2"; veto6bar = "17";
		antiveto1plane = "nd.p3"; antiveto1bar = "15";
		antiveto2plane = "nd.p3"; antiveto2bar = "16";
		antiveto3plane = "nd.p3"; antiveto3bar = "16";
		}
		if (thisbar==17){
		veto1plane = "nd.p1"; veto1bar = "21";
		veto2plane = "nd.p1"; veto2bar = "22";
		veto3plane = "nd.p2"; veto3bar = "16";
		veto4plane = "nd.p2"; veto4bar = "18";
		veto5plane = "nd.p2"; veto5bar = "18";
		veto6plane = "nd.p2"; veto6bar = "18";
		antiveto1plane = "nd.p3"; antiveto1bar = "16";
		antiveto2plane = "nd.p3"; antiveto2bar = "17";
		antiveto3plane = "nd.p3"; antiveto3bar = "17";
		}
		if (thisbar==18){
		veto1plane = "nd.p1"; veto1bar = "22";
		veto2plane = "nd.p1"; veto2bar = "23";
		veto3plane = "nd.p1"; veto3bar = "23";
		veto4plane = "nd.p2"; veto4bar = "17";
		veto5plane = "nd.p2"; veto5bar = "19";
		veto6plane = "nd.p2"; veto6bar = "19";
		antiveto1plane = "nd.p3"; antiveto1bar = "16";
		antiveto2plane = "nd.p3"; antiveto2bar = "17";
		antiveto3plane = "nd.p3"; antiveto3bar = "17";
		}
		if (thisbar==19){
		veto1plane = "nd.p1"; veto1bar = "23";
		veto2plane = "nd.p1"; veto2bar = "24";
		veto3plane = "nd.p1"; veto3bar = "25";
		veto4plane = "nd.p2"; veto4bar = "18";
		veto5plane = "nd.p2"; veto5bar = "20";
		veto6plane = "nd.p2"; veto6bar = "20";
		antiveto1plane = "nd.p3"; antiveto1bar = "17";
		antiveto2plane = "nd.p3"; antiveto2bar = "18";
		antiveto3plane = "nd.p3"; antiveto3bar = "18";
		}
		if (thisbar==20){
		veto1plane = "nd.p1"; veto1bar = "24";
		veto2plane = "nd.p1"; veto2bar = "25";
		veto3plane = "nd.p1"; veto3bar = "26";
		veto4plane = "nd.p2"; veto4bar = "19";
		veto5plane = "nd.p2"; veto5bar = "21";
		veto6plane = "nd.p2"; veto6bar = "21";
		antiveto1plane = "nd.p3"; antiveto1bar = "18";
		antiveto2plane = "nd.p3"; antiveto2bar = "19";
		antiveto3plane = "nd.p3"; antiveto3bar = "19";
		}
		if (thisbar==21){
		veto1plane = "nd.p1"; veto1bar = "26";
		veto2plane = "nd.p1"; veto2bar = "27";
		veto3plane = "nd.p1"; veto3bar = "27";
		veto4plane = "nd.p2"; veto4bar = "20";
		veto5plane = "nd.p2"; veto5bar = "22";
		veto6plane = "nd.p2"; veto6bar = "22";
		antiveto1plane = "nd.p3"; antiveto1bar = "19";
		antiveto2plane = "nd.p3"; antiveto2bar = "20";
		antiveto3plane = "nd.p3"; antiveto3bar = "20";
		}
		if (thisbar==22){
		veto1plane = "nd.p1"; veto1bar = "27";
		veto2plane = "nd.p1"; veto2bar = "28";
		veto3plane = "nd.p1"; veto3bar = "28";
		veto4plane = "nd.p2"; veto4bar = "21";
		veto5plane = "nd.p2"; veto5bar = "23";
		veto6plane = "nd.p2"; veto6bar = "23";
		antiveto1plane = "nd.p3"; antiveto1bar = "20";
		antiveto2plane = "nd.p3"; antiveto2bar = "21";
		antiveto3plane = "nd.p3"; antiveto3bar = "21";
		}
		if (thisbar==23){
		veto1plane = "nd.p1"; veto1bar = "28";
		veto2plane = "nd.p1"; veto2bar = "29";
		veto3plane = "nd.p1"; veto3bar = "29";
		veto4plane = "nd.p2"; veto4bar = "22";
		veto5plane = "nd.p2"; veto5bar = "22";
		veto6plane = "nd.p2"; veto6bar = "22";
		antiveto1plane = "nd.p3"; antiveto1bar = "21";
		antiveto2plane = "nd.p3"; antiveto2bar = "21";
		antiveto3plane = "nd.p3"; antiveto3bar = "21";
		}
	}
	if (nplane==3){
		if (thisbar==0){
		veto1plane = "nd.p2"; veto1bar = "0";
		veto2plane = "nd.p2"; veto2bar = "1";
		veto3plane = "nd.p2"; veto3bar = "1";
		veto4plane = "nd.p2"; veto4bar = "1";
		veto5plane = "nd.p3"; veto5bar = "1";
		veto6plane = "nd.p3"; veto6bar = "1";
		antiveto1plane = "nd.p4"; antiveto1bar = "0";
		antiveto2plane = "nd.p4"; antiveto2bar = "0";
		antiveto3plane = "nd.p4"; antiveto3bar = "0";
		}
		if (thisbar==1){
		veto1plane = "nd.p2"; veto1bar = "1";
		veto2plane = "nd.p2"; veto2bar = "2";
		veto3plane = "nd.p2"; veto3bar = "2";
		veto4plane = "nd.p2"; veto4bar = "2";
		veto5plane = "nd.p3"; veto5bar = "0";
		veto6plane = "nd.p3"; veto6bar = "2";
		antiveto1plane = "nd.p4"; antiveto1bar = "0";
		antiveto2plane = "nd.p4"; antiveto2bar = "1";
		antiveto3plane = "nd.p4"; antiveto3bar = "1";
		}
		if (thisbar==2){
		veto1plane = "nd.p2"; veto1bar = "2";
		veto2plane = "nd.p2"; veto2bar = "3";
		veto3plane = "nd.p2"; veto3bar = "3";
		veto4plane = "nd.p2"; veto4bar = "3";
		veto5plane = "nd.p3"; veto5bar = "1";
		veto6plane = "nd.p3"; veto6bar = "3";
		antiveto1plane = "nd.p4"; antiveto1bar = "1";
		antiveto2plane = "nd.p4"; antiveto2bar = "1";
		antiveto3plane = "nd.p4"; antiveto3bar = "1";
		}
		if (thisbar==3){
		veto1plane = "nd.p2"; veto1bar = "3";
		veto2plane = "nd.p2"; veto2bar = "4";
		veto3plane = "nd.p2"; veto3bar = "4";
		veto4plane = "nd.p2"; veto4bar = "4";
		veto5plane = "nd.p3"; veto5bar = "2";
		veto6plane = "nd.p3"; veto6bar = "4";
		antiveto1plane = "nd.p4"; antiveto1bar = "1";
		antiveto2plane = "nd.p4"; antiveto2bar = "2";
		antiveto3plane = "nd.p4"; antiveto3bar = "2";
		}
		if (thisbar==4){
		veto1plane = "nd.p2"; veto1bar = "4";
		veto2plane = "nd.p2"; veto2bar = "5";
		veto3plane = "nd.p2"; veto3bar = "6";
		veto4plane = "nd.p2"; veto4bar = "6";
		veto5plane = "nd.p3"; veto5bar = "3";
		veto6plane = "nd.p3"; veto6bar = "5";
		antiveto1plane = "nd.p4"; antiveto1bar = "2";
		antiveto2plane = "nd.p4"; antiveto2bar = "3";
		antiveto3plane = "nd.p4"; antiveto3bar = "3";
		}
		if (thisbar==5){
		veto1plane = "nd.p2"; veto1bar = "5";
		veto2plane = "nd.p2"; veto2bar = "6";
		veto3plane = "nd.p2"; veto3bar = "7";
		veto4plane = "nd.p2"; veto4bar = "7";
		veto5plane = "nd.p3"; veto5bar = "4";
		veto6plane = "nd.p3"; veto6bar = "6";
		antiveto1plane = "nd.p4"; antiveto1bar = "2";
		antiveto2plane = "nd.p4"; antiveto2bar = "3";
		antiveto3plane = "nd.p4"; antiveto3bar = "3";
		}
		if (thisbar==6){
		veto1plane = "nd.p2"; veto1bar = "7";
		veto2plane = "nd.p2"; veto2bar = "8";
		veto3plane = "nd.p2"; veto3bar = "8";
		veto4plane = "nd.p2"; veto4bar = "8";
		veto5plane = "nd.p3"; veto5bar = "5";
		veto6plane = "nd.p3"; veto6bar = "7";
		antiveto1plane = "nd.p4"; antiveto1bar = "3";
		antiveto2plane = "nd.p4"; antiveto2bar = "4";
		antiveto3plane = "nd.p4"; antiveto3bar = "4";
		}
		if (thisbar==7){
		veto1plane = "nd.p2"; veto1bar = "8";
		veto2plane = "nd.p2"; veto2bar = "9";
		veto3plane = "nd.p2"; veto3bar = "9";
		veto4plane = "nd.p2"; veto4bar = "9";
		veto5plane = "nd.p3"; veto5bar = "6";
		veto6plane = "nd.p3"; veto6bar = "8";

		veto7plane = "nd.p1"; veto7bar = "11";
		veto8plane = "nd.p1"; veto8bar = "12";
		veto9plane = "nd.p1"; veto9bar = "13";
		veto10plane = "nd.p1"; veto10bar = "14";
		veto11plane = "nd.p1"; veto11bar = "15";
		veto12plane = "nd.p2"; veto12bar = "8";
		veto13plane = "nd.p2"; veto13bar = "9";
		veto14plane = "nd.p2"; veto14bar = "10";
		veto15plane = "nd.p2"; veto15bar = "11";
		veto16plane = "nd.p2"; veto16bar = "12";

		antiveto1plane = "nd.p4"; antiveto1bar = "4";
		antiveto2plane = "nd.p4"; antiveto2bar = "4";
		antiveto3plane = "nd.p4"; antiveto3bar = "4";
		}
		if (thisbar==8){
		veto1plane = "nd.p2"; veto1bar = "9";
		veto2plane = "nd.p2"; veto2bar = "10";
		veto3plane = "nd.p2"; veto3bar = "10";
		veto4plane = "nd.p2"; veto4bar = "10";
		veto5plane = "nd.p3"; veto5bar = "7";
		veto6plane = "nd.p3"; veto6bar = "9";

		veto7plane = "nd.p1"; veto7bar = "11";
		veto8plane = "nd.p1"; veto8bar = "12";
		veto9plane = "nd.p1"; veto9bar = "13";
		veto10plane = "nd.p1"; veto10bar = "14";
		veto11plane = "nd.p1"; veto11bar = "15";
		veto12plane = "nd.p2"; veto12bar = "8";
		veto13plane = "nd.p2"; veto13bar = "9";
		veto14plane = "nd.p2"; veto14bar = "10";
		veto15plane = "nd.p2"; veto15bar = "11";
		veto16plane = "nd.p2"; veto16bar = "12";


		antiveto1plane = "nd.p4"; antiveto1bar = "4";
		antiveto2plane = "nd.p4"; antiveto2bar = "5";
		antiveto3plane = "nd.p4"; antiveto3bar = "5";
		}
		if (thisbar==9){
		veto1plane = "nd.p2"; veto1bar = "10";
		veto2plane = "nd.p2"; veto2bar = "11";
		veto3plane = "nd.p2"; veto3bar = "11";
		veto4plane = "nd.p2"; veto4bar = "11";
		veto5plane = "nd.p3"; veto5bar = "8";
		veto6plane = "nd.p3"; veto6bar = "10";

		veto7plane = "nd.p1"; veto7bar = "11";
		veto8plane = "nd.p1"; veto8bar = "12";
		veto9plane = "nd.p1"; veto9bar = "13";
		veto10plane = "nd.p1"; veto10bar = "14";
		veto11plane = "nd.p1"; veto11bar = "15";
		veto12plane = "nd.p2"; veto12bar = "8";
		veto13plane = "nd.p2"; veto13bar = "9";
		veto14plane = "nd.p2"; veto14bar = "10";
		veto15plane = "nd.p2"; veto15bar = "11";
		veto16plane = "nd.p2"; veto16bar = "12";


		antiveto1plane = "nd.p4"; antiveto1bar = "5";
		antiveto2plane = "nd.p4"; antiveto2bar = "5";
		antiveto3plane = "nd.p4"; antiveto3bar = "5";
		}
		if (thisbar==10){
		veto1plane = "nd.p2"; veto1bar = "11";
		veto2plane = "nd.p2"; veto2bar = "12";
		veto3plane = "nd.p2"; veto3bar = "12";
		veto4plane = "nd.p2"; veto4bar = "12";
		veto5plane = "nd.p3"; veto5bar = "9";
		veto6plane = "nd.p3"; veto6bar = "11";

		veto7plane = "nd.p1"; veto7bar = "11";
		veto8plane = "nd.p1"; veto8bar = "12";
		veto9plane = "nd.p1"; veto9bar = "13";
		veto10plane = "nd.p1"; veto10bar = "14";
		veto11plane = "nd.p1"; veto11bar = "15";
		veto12plane = "nd.p2"; veto12bar = "8";
		veto13plane = "nd.p2"; veto13bar = "9";
		veto14plane = "nd.p2"; veto14bar = "10";
		veto15plane = "nd.p2"; veto15bar = "11";
		veto16plane = "nd.p2"; veto16bar = "12";


		antiveto1plane = "nd.p4"; antiveto1bar = "5";
		antiveto2plane = "nd.p4"; antiveto2bar = "6";
		antiveto3plane = "nd.p4"; antiveto3bar = "6";
		}
		if (thisbar==11){
		veto1plane = "nd.p2"; veto1bar = "11";
		veto2plane = "nd.p2"; veto2bar = "12";
		veto3plane = "nd.p2"; veto3bar = "12";
		veto4plane = "nd.p2"; veto4bar = "12";
		veto5plane = "nd.p3"; veto5bar = "10";
		veto6plane = "nd.p3"; veto6bar = "12";

		veto7plane = "nd.p1"; veto7bar = "11";
		veto8plane = "nd.p1"; veto8bar = "12";
		veto9plane = "nd.p1"; veto9bar = "13";
		veto10plane = "nd.p1"; veto10bar = "14";
		veto11plane = "nd.p1"; veto11bar = "15";
		veto12plane = "nd.p2"; veto12bar = "8";
		veto13plane = "nd.p2"; veto13bar = "9";
		veto14plane = "nd.p2"; veto14bar = "10";
		veto15plane = "nd.p2"; veto15bar = "11";
		veto16plane = "nd.p2"; veto16bar = "12";


		antiveto1plane = "nd.p4"; antiveto1bar = "5";
		antiveto2plane = "nd.p4"; antiveto2bar = "6";
		antiveto3plane = "nd.p4"; antiveto3bar = "6";
		}
		if (thisbar==12){
		veto1plane = "nd.p2"; veto1bar = "12";
		veto2plane = "nd.p2"; veto2bar = "13";
		veto3plane = "nd.p2"; veto3bar = "14";
		veto4plane = "nd.p2"; veto4bar = "14";
		veto5plane = "nd.p3"; veto5bar = "11";
		veto6plane = "nd.p3"; veto6bar = "13";
		antiveto1plane = "nd.p4"; antiveto1bar = "6";
		antiveto2plane = "nd.p4"; antiveto2bar = "6";
		antiveto3plane = "nd.p4"; antiveto3bar = "7";

//		antiveto1plane = "nd.p1"; antiveto1bar = "16";
//		antiveto2plane = "nd.p2"; antiveto2bar = "13";
//		antiveto3plane = "nd.p4"; antiveto3bar = "6";
		}
		if (thisbar==13){
		veto1plane = "nd.p2"; veto1bar = "13";
		veto2plane = "nd.p2"; veto2bar = "14";
		veto3plane = "nd.p2"; veto3bar = "14";
		veto4plane = "nd.p2"; veto4bar = "14";
		veto5plane = "nd.p3"; veto5bar = "12";
		veto6plane = "nd.p3"; veto6bar = "14";
		antiveto1plane = "nd.p4"; antiveto1bar = "6";
		antiveto2plane = "nd.p4"; antiveto2bar = "7";
		antiveto3plane = "nd.p4"; antiveto3bar = "7";
		}
		if (thisbar==14){
		veto1plane = "nd.p2"; veto1bar = "14";
		veto2plane = "nd.p2"; veto2bar = "15";
		veto3plane = "nd.p2"; veto3bar = "15";
		veto4plane = "nd.p2"; veto4bar = "15";
		veto5plane = "nd.p3"; veto5bar = "13";
		veto6plane = "nd.p3"; veto6bar = "15";
		antiveto1plane = "nd.p4"; antiveto1bar = "7";
		antiveto2plane = "nd.p4"; antiveto2bar = "7";
		antiveto3plane = "nd.p4"; antiveto3bar = "7";
		}
		if (thisbar==15){
		veto1plane = "nd.p2"; veto1bar = "15";
		veto2plane = "nd.p2"; veto2bar = "16";
		veto3plane = "nd.p2"; veto3bar = "16";
		veto4plane = "nd.p2"; veto4bar = "16";
		veto5plane = "nd.p3"; veto5bar = "14";
		veto6plane = "nd.p3"; veto6bar = "16";
		antiveto1plane = "nd.p4"; antiveto1bar = "7";
		antiveto2plane = "nd.p4"; antiveto2bar = "8";
		antiveto3plane = "nd.p4"; antiveto3bar = "8";
		}
		if (thisbar==16){
		veto1plane = "nd.p2"; veto1bar = "16";
		veto2plane = "nd.p2"; veto2bar = "17";
		veto3plane = "nd.p2"; veto3bar = "18";
		veto4plane = "nd.p2"; veto4bar = "18";
		veto5plane = "nd.p3"; veto5bar = "15";
		veto6plane = "nd.p3"; veto6bar = "17";
		antiveto1plane = "nd.p4"; antiveto1bar = "8";
		antiveto2plane = "nd.p4"; antiveto2bar = "9";
		antiveto3plane = "nd.p4"; antiveto3bar = "9";
		}
		if (thisbar==17){
		veto1plane = "nd.p2"; veto1bar = "17";
		veto2plane = "nd.p2"; veto2bar = "18";
		veto3plane = "nd.p2"; veto3bar = "19";
		veto4plane = "nd.p2"; veto4bar = "19";
		veto5plane = "nd.p3"; veto5bar = "16";
		veto6plane = "nd.p3"; veto6bar = "18";
		antiveto1plane = "nd.p4"; antiveto1bar = "8";
		antiveto2plane = "nd.p4"; antiveto2bar = "9";
		antiveto3plane = "nd.p4"; antiveto3bar = "9";
		}
		if (thisbar==18){
		veto1plane = "nd.p2"; veto1bar = "19";
		veto2plane = "nd.p2"; veto2bar = "20";
		veto3plane = "nd.p2"; veto3bar = "20";
		veto4plane = "nd.p2"; veto4bar = "20";
		veto5plane = "nd.p3"; veto5bar = "17";
		veto6plane = "nd.p3"; veto6bar = "19";
		antiveto1plane = "nd.p4"; antiveto1bar = "9";
		antiveto2plane = "nd.p4"; antiveto2bar = "10";
		antiveto3plane = "nd.p4"; antiveto3bar = "10";
		}
		if (thisbar==19){
		veto1plane = "nd.p2"; veto1bar = "20";
		veto2plane = "nd.p2"; veto2bar = "21";
		veto3plane = "nd.p2"; veto3bar = "21";
		veto4plane = "nd.p2"; veto4bar = "21";
		veto5plane = "nd.p3"; veto5bar = "18";
		veto6plane = "nd.p3"; veto6bar = "20";
		antiveto1plane = "nd.p4"; antiveto1bar = "10";
		antiveto2plane = "nd.p4"; antiveto2bar = "10";
		antiveto3plane = "nd.p4"; antiveto3bar = "10";
		}
		if (thisbar==20){
		veto1plane = "nd.p2"; veto1bar = "21";
		veto2plane = "nd.p2"; veto2bar = "22";
		veto3plane = "nd.p2"; veto3bar = "22";
		veto4plane = "nd.p2"; veto4bar = "22";
		veto5plane = "nd.p3"; veto5bar = "19";
		veto6plane = "nd.p3"; veto6bar = "21";
		antiveto1plane = "nd.p4"; antiveto1bar = "10";
		antiveto2plane = "nd.p4"; antiveto2bar = "11";
		antiveto3plane = "nd.p4"; antiveto3bar = "11";
		}
		if (thisbar==21){
		veto1plane = "nd.p2"; veto1bar = "22";
		veto2plane = "nd.p2"; veto2bar = "23";
		veto3plane = "nd.p2"; veto3bar = "23";
		veto4plane = "nd.p2"; veto4bar = "23";
		veto5plane = "nd.p3"; veto5bar = "20";
		veto6plane = "nd.p3"; veto6bar = "20";
		antiveto1plane = "nd.p4"; antiveto1bar = "11";
		antiveto2plane = "nd.p4"; antiveto2bar = "11";
		antiveto3plane = "nd.p4"; antiveto3bar = "11";
		}
	}
	if (nplane==4){
		if (thisbar==0){
		veto1plane = "nd.p3"; veto1bar = "0";
		veto2plane = "nd.p3"; veto2bar = "1";
		veto3plane = "nd.p3"; veto3bar = "1";
		veto4plane = "nd.p3"; veto4bar = "1";
		veto5plane = "nd.p4"; veto5bar = "1";
		veto6plane = "nd.p4"; veto6bar = "1";
		}
		if (thisbar==1){
		veto1plane = "nd.p3"; veto1bar = "1";
		veto2plane = "nd.p3"; veto2bar = "2";
		veto3plane = "nd.p3"; veto3bar = "3";
		veto4plane = "nd.p3"; veto4bar = "3";
		veto5plane = "nd.p4"; veto5bar = "0";
		veto6plane = "nd.p4"; veto6bar = "2";
		}
		if (thisbar==2){
		veto1plane = "nd.p3"; veto1bar = "3";
		veto2plane = "nd.p3"; veto2bar = "4";
		veto3plane = "nd.p3"; veto3bar = "5";
		veto4plane = "nd.p3"; veto4bar = "5";
		veto5plane = "nd.p4"; veto5bar = "1";
		veto6plane = "nd.p4"; veto6bar = "3";
		}
		if (thisbar==3){
		veto1plane = "nd.p3"; veto1bar = "4";
		veto2plane = "nd.p3"; veto2bar = "5";
		veto3plane = "nd.p3"; veto3bar = "6";
		veto4plane = "nd.p3"; veto4bar = "6";
		veto5plane = "nd.p4"; veto5bar = "2";
		veto6plane = "nd.p4"; veto6bar = "4";
		}
		if (thisbar==4){
		veto1plane = "nd.p3"; veto1bar = "6";
		veto2plane = "nd.p3"; veto2bar = "7";
		veto3plane = "nd.p3"; veto3bar = "8";
		veto4plane = "nd.p3"; veto4bar = "8";
		veto5plane = "nd.p4"; veto5bar = "3";
		veto6plane = "nd.p4"; veto6bar = "5";

		veto7plane = "nd.p1"; veto7bar = "11";
		veto8plane = "nd.p1"; veto8bar = "12";
		veto9plane = "nd.p1"; veto9bar = "13";
		veto10plane = "nd.p1"; veto10bar = "14";
		veto11plane = "nd.p1"; veto11bar = "15";
		veto12plane = "nd.p2"; veto12bar = "8";
		veto13plane = "nd.p2"; veto13bar = "9";
		veto14plane = "nd.p2"; veto14bar = "10";
		veto15plane = "nd.p2"; veto15bar = "11";
		veto16plane = "nd.p2"; veto16bar = "12";
		veto17plane = "nd.p3"; veto17bar = "7";
		veto18plane = "nd.p3"; veto18bar = "8";
		veto19plane = "nd.p3"; veto19bar = "9";
		veto20plane = "nd.p3"; veto20bar = "10";
		veto21plane = "nd.p3"; veto21bar = "11";

		}
		if (thisbar==5){
		veto1plane = "nd.p3"; veto1bar = "8";
		veto2plane = "nd.p3"; veto2bar = "9";
		veto3plane = "nd.p3"; veto3bar = "10";
		veto4plane = "nd.p3"; veto4bar = "11";
		veto5plane = "nd.p4"; veto5bar = "4";
		veto6plane = "nd.p4"; veto6bar = "6";

		veto7plane = "nd.p1"; veto7bar = "11";
		veto8plane = "nd.p1"; veto8bar = "12";
		veto9plane = "nd.p1"; veto9bar = "13";
		veto10plane = "nd.p1"; veto10bar = "14";
		veto11plane = "nd.p1"; veto11bar = "15";
		veto12plane = "nd.p2"; veto12bar = "8";
		veto13plane = "nd.p2"; veto13bar = "9";
		veto14plane = "nd.p2"; veto14bar = "10";
		veto15plane = "nd.p2"; veto15bar = "11";
		veto16plane = "nd.p2"; veto16bar = "12";
		veto17plane = "nd.p3"; veto17bar = "7";
		veto18plane = "nd.p3"; veto18bar = "8";
		veto19plane = "nd.p3"; veto19bar = "9";
		veto20plane = "nd.p3"; veto20bar = "10";
		veto21plane = "nd.p3"; veto21bar = "11";


		}
		if (thisbar==6){
		veto1plane = "nd.p3"; veto1bar = "10";
		veto2plane = "nd.p3"; veto2bar = "11";
		veto3plane = "nd.p3"; veto3bar = "12";
		veto4plane = "nd.p3"; veto4bar = "13";
		veto5plane = "nd.p4"; veto5bar = "5";
		veto6plane = "nd.p4"; veto6bar = "7";

		veto7plane = "nd.p1"; veto7bar = "11";
		veto8plane = "nd.p1"; veto8bar = "12";
		veto9plane = "nd.p1"; veto9bar = "13";
		veto10plane = "nd.p1"; veto10bar = "14";
		veto11plane = "nd.p1"; veto11bar = "15";
		veto12plane = "nd.p2"; veto12bar = "8";
		veto13plane = "nd.p2"; veto13bar = "9";
		veto14plane = "nd.p2"; veto14bar = "10";
		veto15plane = "nd.p2"; veto15bar = "11";
		veto16plane = "nd.p2"; veto16bar = "12";
		veto17plane = "nd.p3"; veto17bar = "7";
		veto18plane = "nd.p3"; veto18bar = "8";
		veto19plane = "nd.p3"; veto19bar = "9";
		veto20plane = "nd.p3"; veto20bar = "10";
		veto21plane = "nd.p3"; veto21bar = "11";


		}
		if (thisbar==7){
		veto1plane = "nd.p3"; veto1bar = "13";
		veto2plane = "nd.p3"; veto2bar = "14";
		veto3plane = "nd.p3"; veto3bar = "15";
		veto4plane = "nd.p3"; veto4bar = "15";
		veto5plane = "nd.p4"; veto5bar = "6";
		veto6plane = "nd.p4"; veto6bar = "8";

		veto7plane = "nd.p1"; veto7bar = "11";
		veto8plane = "nd.p1"; veto8bar = "12";
		veto9plane = "nd.p1"; veto9bar = "13";
		veto10plane = "nd.p1"; veto10bar = "14";
		veto11plane = "nd.p1"; veto11bar = "15";
		veto12plane = "nd.p2"; veto12bar = "8";
		veto13plane = "nd.p2"; veto13bar = "9";
		veto14plane = "nd.p2"; veto14bar = "10";
		veto15plane = "nd.p2"; veto15bar = "11";
		veto16plane = "nd.p2"; veto16bar = "12";
		veto17plane = "nd.p3"; veto17bar = "7";
		veto18plane = "nd.p3"; veto18bar = "8";
		veto19plane = "nd.p3"; veto19bar = "9";
		veto20plane = "nd.p3"; veto20bar = "10";
		veto21plane = "nd.p3"; veto21bar = "11";


		}
		if (thisbar==8){
		veto1plane = "nd.p3"; veto1bar = "15";
		veto2plane = "nd.p3"; veto2bar = "16";
		veto3plane = "nd.p3"; veto3bar = "17";
		veto4plane = "nd.p3"; veto4bar = "17";
		veto5plane = "nd.p4"; veto5bar = "7";
		veto6plane = "nd.p4"; veto6bar = "9";
		}
		if (thisbar==9){
		veto1plane = "nd.p3"; veto1bar = "16";
		veto2plane = "nd.p3"; veto2bar = "17";
		veto3plane = "nd.p3"; veto3bar = "18";
		veto4plane = "nd.p3"; veto4bar = "18";
		veto5plane = "nd.p4"; veto5bar = "8";
		veto6plane = "nd.p4"; veto6bar = "10";
		}
		if (thisbar==10){
		veto1plane = "nd.p3"; veto1bar = "18";
		veto2plane = "nd.p3"; veto2bar = "19";
		veto3plane = "nd.p3"; veto3bar = "20";
		veto4plane = "nd.p3"; veto4bar = "20";
		veto5plane = "nd.p4"; veto5bar = "9";
		veto6plane = "nd.p4"; veto6bar = "11";
		}
		if (thisbar==11){
		veto1plane = "nd.p3"; veto1bar = "20";
		veto2plane = "nd.p3"; veto2bar = "21";
		veto3plane = "nd.p3"; veto3bar = "21";
		veto4plane = "nd.p3"; veto4bar = "21";
		veto5plane = "nd.p4"; veto5bar = "10";
		veto6plane = "nd.p4"; veto6bar = "10";
		}
	}
	if (!includeVetos)
	{
		veto1plane = "";  veto1bar = "";
		veto2plane = "";  veto2bar = "";
		veto3plane = "";  veto3bar = "";
		veto4plane = "";  veto4bar = "";
		veto5plane = "";  veto5bar = "";
		veto6plane = "";  veto6bar = "";
		veto7plane = "";  veto7bar = "";
		veto8plane = "";  veto8bar = "";
		veto9plane = "";  veto9bar = "";
		veto10plane = ""; veto10bar = "";
		veto11plane = ""; veto11bar = "";
		veto12plane = ""; veto12bar = "";
		veto13plane = ""; veto13bar = "";
		veto14plane = ""; veto14bar = "";
		veto15plane = ""; veto15bar = "";
		veto16plane = ""; veto16bar = "";
		veto17plane = ""; veto17bar = "";
		veto18plane = ""; veto18bar = "";
		veto19plane = ""; veto19bar = "";
		veto20plane = ""; veto20bar = "";
		veto21plane = ""; veto21bar = "";

	}
	if (!includeAntivetos)
	{
		antiveto1plane = ""; antiveto1bar = "";
		antiveto2plane = ""; antiveto2bar = "";
		antiveto3plane = ""; antiveto3bar = "";
	}

	// This allVetos is going to be used when drawing the
	// image of the HAND as a searchable string to find
	// out if any particular bar is a veto bar or not.
	// Similarly with goodBar and allAntivetos;
	// **************************************************
	allVetos = veto1plane;
	allVetos += ".";
	allVetos += veto1bar;
	allVetos += " ";
	allVetos += veto2plane;
	allVetos += ".";
	allVetos += veto2bar;
	allVetos += " ";
	allVetos += veto3plane;
	allVetos += ".";
	allVetos += veto3bar;
	allVetos += " ";
	allVetos += veto4plane;
	allVetos += ".";
	allVetos += veto4bar;
	allVetos += " ";
	allVetos += veto5plane;
	allVetos += ".";
	allVetos += veto5bar;
	allVetos += " ";
	allVetos += veto6plane;
	allVetos += ".";
	allVetos += veto6bar;
	allVetos += " ";
	allVetos += veto7plane;
	allVetos += ".";
	allVetos += veto7bar;
	allVetos += " ";
	allVetos += veto8plane;
	allVetos += ".";
	allVetos += veto8bar;
	allVetos += " ";
	allVetos += veto9plane;
	allVetos += ".";
	allVetos += veto9bar;
	allVetos += " ";
	allVetos += veto10plane;
	allVetos += ".";
	allVetos += veto10bar;
	allVetos += " ";
	allVetos += veto11plane;
	allVetos += ".";
	allVetos += veto11bar;
	allVetos += " ";
	allVetos += veto12plane;
	allVetos += ".";
	allVetos += veto12bar;
	allVetos += " ";
	allVetos += veto13plane;
	allVetos += ".";
	allVetos += veto13bar;
	allVetos += " ";
	allVetos += veto14plane;
	allVetos += ".";
	allVetos += veto14bar;
	allVetos += " ";
	allVetos += veto15plane;
	allVetos += ".";
	allVetos += veto15bar;
	allVetos += " ";
	allVetos += veto16plane;
	allVetos += ".";
	allVetos += veto16bar;
	allVetos += " ";
	allVetos += veto17plane;
	allVetos += ".";
	allVetos += veto17bar;
	allVetos += " ";
	allVetos += veto18plane;
	allVetos += ".";
	allVetos += veto18bar;
	allVetos += " ";
	allVetos += veto19plane;
	allVetos += ".";
	allVetos += veto19bar;
	allVetos += " ";
	allVetos += veto20plane;
	allVetos += ".";
	allVetos += veto20bar;
	allVetos += " ";
	allVetos += veto21plane;
	allVetos += ".";
	allVetos += veto21bar;
	allVetos += " ";

	allAntivetos = antiveto1plane;
	allAntivetos += ".";
	allAntivetos += antiveto1bar;
	allAntivetos += " ";
	allAntivetos += antiveto2plane;
	allAntivetos += ".";
	allAntivetos += antiveto2bar;
	allAntivetos += " ";
	allAntivetos += antiveto3plane;
	allAntivetos += ".";
	allAntivetos += antiveto3bar;
	allAntivetos += " ";

	if (nplane==0) {allVetos = "";}
	if (nplane==0) {allAntivetos = "";}
	if (antivetosAsVetos && includeVetos) { allVetos += allAntivetos;}

	cout << "Vetos: " << allVetos << endl;
	cout << "allAntivetos: " << allAntivetos << endl;

	// Below are the  veto cuts. They're split apart because I want
	// to be able to put this in a loop eventually to automize
	// the flow of data to histograms
	vetoTDCslSt =  "";
	if (includeVetos)
	{
		vetoTDCslSt =  "(NA.";      vetoTDCslSt += veto1plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto1bar;  vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;
		vetoTDCslSt += " || NA.";   vetoTDCslSt += veto1plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto1bar;  vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;
		vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto2plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto2bar;  vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;
		vetoTDCslSt += " || NA.";   vetoTDCslSt += veto2plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto2bar;  vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;
		vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto3plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto3bar;  vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;
		vetoTDCslSt += " || NA.";   vetoTDCslSt += veto3plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto3bar;  vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;
		vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto4plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto4bar;  vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;
		vetoTDCslSt += " || NA.";   vetoTDCslSt += veto4plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto4bar;  vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;
		vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto5plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto5bar;  vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;
		vetoTDCslSt += " || NA.";   vetoTDCslSt += veto5plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto5bar;  vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;
		vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto6plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto6bar;  vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;
		vetoTDCslSt += " || NA.";   vetoTDCslSt += veto6plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto6bar;  vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;
		if (veto7plane != "") {vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto7plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto7bar;  vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;}
		if (veto7plane != "") {vetoTDCslSt += " || NA.";   vetoTDCslSt += veto7plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto7bar;  vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;}
		if (veto8plane != "") {vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto8plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto8bar;  vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;}
		if (veto8plane != "") {vetoTDCslSt += " || NA.";   vetoTDCslSt += veto8plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto8bar;  vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;}
		if (veto9plane != "") {vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto9plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto9bar;  vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;}
		if (veto9plane != "") {vetoTDCslSt += " || NA.";   vetoTDCslSt += veto9plane;  vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto9bar;  vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;}
		if (veto10plane != "") {vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto10plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto10bar; vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;}
		if (veto10plane != "") {vetoTDCslSt += " || NA.";   vetoTDCslSt += veto10plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto10bar; vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;}
		if (veto11plane != "") {vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto11plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto11bar; vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;}
		if (veto11plane != "") {vetoTDCslSt += " || NA.";   vetoTDCslSt += veto11plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto11bar; vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;}
		if (veto12plane != "") {vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto12plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto12bar; vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;}
		if (veto12plane != "") {vetoTDCslSt += " || NA.";   vetoTDCslSt += veto12plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto12bar; vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;}
		if (veto13plane != "") {vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto13plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto13bar; vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;}
		if (veto13plane != "") {vetoTDCslSt += " || NA.";   vetoTDCslSt += veto13plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto13bar; vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;}
		if (veto14plane != "") {vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto14plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto14bar; vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;}
		if (veto14plane != "") {vetoTDCslSt += " || NA.";   vetoTDCslSt += veto14plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto14bar; vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;}
		if (veto15plane != "") {vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto15plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto15bar; vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;}
		if (veto15plane != "") {vetoTDCslSt += " || NA.";   vetoTDCslSt += veto15plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto15bar; vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;}
		if (veto16plane != "") {vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto16plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto16bar; vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;}
		if (veto16plane != "") {vetoTDCslSt += " || NA.";   vetoTDCslSt += veto16plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto16bar; vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;}
		if (veto17plane != "") {vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto17plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto17bar; vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;}
		if (veto17plane != "") {vetoTDCslSt += " || NA.";   vetoTDCslSt += veto17plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto17bar; vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;}
		if (veto18plane != "") {vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto18plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto18bar; vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;}
		if (veto18plane != "") {vetoTDCslSt += " || NA.";   vetoTDCslSt += veto18plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto18bar; vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;}
		if (veto19plane != "") {vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto19plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto19bar; vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;}
		if (veto19plane != "") {vetoTDCslSt += " || NA.";   vetoTDCslSt += veto19plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto19bar; vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;}
		if (veto20plane != "") {vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto20plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto20bar; vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;}
		if (veto20plane != "") {vetoTDCslSt += " || NA.";   vetoTDCslSt += veto20plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto20bar; vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;}
		if (veto21plane != "") {vetoTDCslSt += ") && (NA."; vetoTDCslSt += veto21plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto21bar; vetoTDCslSt += "]<"; vetoTDCslSt += vetoTDCcutmin;}
		if (veto21plane != "") {vetoTDCslSt += " || NA.";   vetoTDCslSt += veto21plane; vetoTDCslSt += ".lt_c["; vetoTDCslSt += veto21bar; vetoTDCslSt += "]>"; vetoTDCslSt += vetoTDCcutmax;}
		vetoTDCslSt += ")";
	}

	antivetosTDCslSt = "";
	if (antivetosAsVetos)
	{
		antivetosTDCslSt += "&& ((NA.";
		antivetosTDCslSt += antiveto1plane;
		antivetosTDCslSt += ".lt_c[";
		antivetosTDCslSt += antiveto1bar;
		antivetosTDCslSt += "]<";
		antivetosTDCslSt += vetoTDCcutmin;
		antivetosTDCslSt += " || NA.";
		antivetosTDCslSt += antiveto1plane;
		antivetosTDCslSt += ".lt_c[";
		antivetosTDCslSt += antiveto1bar;
		antivetosTDCslSt += "]>";
		antivetosTDCslSt += vetoTDCcutmax;
		antivetosTDCslSt += ") && (NA.";
		antivetosTDCslSt += antiveto2plane;
		antivetosTDCslSt += ".lt_c[";
		antivetosTDCslSt += antiveto2bar;
		antivetosTDCslSt += "]<";
		antivetosTDCslSt += vetoTDCcutmin;
		antivetosTDCslSt += " || NA.";
		antivetosTDCslSt += antiveto2plane;
		antivetosTDCslSt += ".lt_c[";
		antivetosTDCslSt += antiveto2bar;
		antivetosTDCslSt += "]>";
		antivetosTDCslSt += vetoTDCcutmax;
		antivetosTDCslSt += ") && (NA.";
		antivetosTDCslSt += antiveto3plane;
		antivetosTDCslSt += ".lt_c[";
		antivetosTDCslSt += antiveto3bar;
		antivetosTDCslSt += "]<";
		antivetosTDCslSt += vetoTDCcutmin;
		antivetosTDCslSt += " || NA.";
		antivetosTDCslSt += antiveto3plane;
		antivetosTDCslSt += ".lt_c[";
		antivetosTDCslSt += antiveto3bar;
		antivetosTDCslSt += "]>";
		antivetosTDCslSt += vetoTDCcutmax;
		antivetosTDCslSt += "))";
		vetoTDCslSt += antivetosTDCslSt;
	}
	vetoTDCsl = vetoTDCslSt;

	vetoTDCsrSt = "";
	if (includeVetos)
	{
		vetoTDCsrSt = "(NA.";       vetoTDCsrSt += veto1plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto1bar;  vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;
		vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto1plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto1bar;  vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;
		vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto2plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto2bar;  vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;
		vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto2plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto2bar;  vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;
		vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto3plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto3bar;  vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;
		vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto3plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto3bar;  vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;
		vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto4plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto4bar;  vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;
		vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto4plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto4bar;  vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;
		vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto5plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto5bar;  vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;
		vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto5plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto5bar;  vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;
		vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto6plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto6bar;  vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;
		vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto6plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto6bar;  vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;
		if (veto7plane != "")  {vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto7plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto7bar;  vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;}
		if (veto7plane != "")  {vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto7plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto7bar;  vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;}
		if (veto8plane != "")  {vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto8plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto8bar;  vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;}
		if (veto8plane != "")  {vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto8plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto8bar;  vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;}
		if (veto9plane != "")  {vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto9plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto9bar;  vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;}
		if (veto9plane != "")  {vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto9plane;  vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto9bar;  vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;}
		if (veto10plane != "") {vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto10plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto10bar; vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;}
		if (veto10plane != "") {vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto10plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto10bar; vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;}
		if (veto11plane != "") {vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto11plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto11bar; vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;}
		if (veto11plane != "") {vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto11plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto11bar; vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;}
		if (veto12plane != "") {vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto12plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto12bar; vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;}
		if (veto12plane != "") {vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto12plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto12bar; vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;}
		if (veto13plane != "") {vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto13plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto13bar; vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;}
		if (veto13plane != "") {vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto13plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto13bar; vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;}
		if (veto14plane != "") {vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto14plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto14bar; vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;}
		if (veto14plane != "") {vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto14plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto14bar; vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;}
		if (veto15plane != "") {vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto15plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto15bar; vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;}
		if (veto15plane != "") {vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto15plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto15bar; vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;}
		if (veto16plane != "") {vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto16plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto16bar; vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;}
		if (veto16plane != "") {vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto16plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto16bar; vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;}
		if (veto17plane != "") {vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto17plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto17bar; vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;}
		if (veto17plane != "") {vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto17plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto17bar; vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;}
		if (veto18plane != "") {vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto18plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto18bar; vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;}
		if (veto18plane != "") {vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto18plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto18bar; vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;}
		if (veto19plane != "") {vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto19plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto19bar; vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;}
		if (veto19plane != "") {vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto19plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto19bar; vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;}
		if (veto20plane != "") {vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto20plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto20bar; vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;}
		if (veto20plane != "") {vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto20plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto20bar; vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;}
		if (veto21plane != "") {vetoTDCsrSt += ") && (NA."; vetoTDCsrSt += veto21plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto21bar; vetoTDCsrSt += "]<"; vetoTDCsrSt += vetoTDCcutmin;}
		if (veto21plane != "") {vetoTDCsrSt += " || NA.";   vetoTDCsrSt += veto21plane; vetoTDCsrSt += ".rt_c["; vetoTDCsrSt += veto21bar; vetoTDCsrSt += "]>"; vetoTDCsrSt += vetoTDCcutmax;}
		vetoTDCsrSt += ")";
	}

	antivetosTDCsrSt = "";
	if (antivetosAsVetos)
	{
		antivetosTDCsrSt += "&& ((NA.";
		antivetosTDCsrSt += antiveto1plane;
		antivetosTDCsrSt += ".rt_c[";
		antivetosTDCsrSt += antiveto1bar;
		antivetosTDCsrSt += "]<";
		antivetosTDCsrSt += vetoTDCcutmin;
		antivetosTDCsrSt += " || NA.";
		antivetosTDCsrSt += antiveto1plane;
		antivetosTDCsrSt += ".rt_c[";
		antivetosTDCsrSt += antiveto1bar;
		antivetosTDCsrSt += "]>";
		antivetosTDCsrSt += vetoTDCcutmax;
		antivetosTDCsrSt += ") && (NA.";
		antivetosTDCsrSt += antiveto2plane;
		antivetosTDCsrSt += ".rt_c[";
		antivetosTDCsrSt += antiveto2bar;
		antivetosTDCsrSt += "]<";
		antivetosTDCsrSt += vetoTDCcutmin;
		antivetosTDCsrSt += " || NA.";
		antivetosTDCsrSt += antiveto2plane;
		antivetosTDCsrSt += ".rt_c[";
		antivetosTDCsrSt += antiveto2bar;
		antivetosTDCsrSt += "]>";
		antivetosTDCsrSt += vetoTDCcutmax;
		antivetosTDCsrSt += ") && (NA.";
		antivetosTDCsrSt += antiveto3plane;
		antivetosTDCsrSt += ".rt_c[";
		antivetosTDCsrSt += antiveto3bar;
		antivetosTDCsrSt += "]<";
		antivetosTDCsrSt += vetoTDCcutmin;
		antivetosTDCsrSt += " || NA.";
		antivetosTDCsrSt += antiveto3plane;
		antivetosTDCsrSt += ".rt_c[";
		antivetosTDCsrSt += antiveto3bar;
		antivetosTDCsrSt += "]>";
		antivetosTDCsrSt += vetoTDCcutmax;
		antivetosTDCsrSt += "))";
		vetoTDCsrSt += antivetosTDCsrSt;
	}
	vetoTDCsr = vetoTDCsrSt;
	vetoTDCs = "";
	if (includeVetos) {vetoTDCs = vetoTDCsl && vetoTDCsr;}
	else {vetoTDCs = "";}
	cout << "Veto Cut: " << vetoTDCslSt << " && " << vetoTDCsrSt << endl;



	includeVetos = includeVetosPlaceKeeper;

	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" >> endl;
}

