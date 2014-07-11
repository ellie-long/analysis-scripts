// *************************************************** 
//
// This script should create a list of definitions for 
// the theta variable for each bar of the Hall A
// Neutron Detector.
//
// It is based off of the hand_define_vetos.h script 
//
// In order to use this, first add this to the top of 
// your script:
/*
	#include "hand_define_bar_th.h"
*/
//
// Then declare these variables: 
/*
	double thetaMin;
	double thetaMax;
	TString thetaCutSt;
	TCut pastThetaCut;
*/
//
// And finally, add this line of code wherever you want
// to define the vetos:
/*
	hand_define_bar_th(Q2, nplane, thisbar, thetaMin, thetaMax, thetaCutSt, pastThetaCut);
*/
//
//
//
// 2011-08-17
// Elena Long 
//
// *************************************************** 

// void MyClass::hand_class_bar_th_cuts(TString Q2, int nplane, int thisbar, bool& pastThetaCut)
void neutron_analysis_class::hand_class_bar_th_cuts(TString Q2, int nplane, int thisbar, bool& pastThetaCut)
{


//	cout << "vvvvvvvvvvvvvvvvvvvvvvvvv hand_class_bar_th_cuts.h vvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
//	cout << "Running hand_define_bar_th.h for p" << nplane << "b" << thisbar << " for Q2=" << Q2 << endl;

	// This huge set of if statements defines the theta cut for each good bar we're
	// going to look at. 
	// Hopefully this works.
	double thetaMin = -0.06;
	double thetaMax = 0.06;
//	TString thetaCutSt = "";
//	TString pastThetaCut = "";

	if (Q2=="0.1")
	{
		if (nplane==1){
			if (thisbar==0){
			thetaMin = 0.042;
			thetaMax = 0.070;
			}
			if (thisbar==1){
			thetaMin = 0.038;
			thetaMax = 0.066;
			}
			if (thisbar==2){
			thetaMin = 0.034;
			thetaMax = 0.062;
			}
			if (thisbar==3){
			thetaMin = 0.030;
			thetaMax = 0.058;
			}
			if (thisbar==4){
			thetaMin = 0.026;
			thetaMax = 0.054;
			}
			if (thisbar==5){
			thetaMin = 0.022;
			thetaMax = 0.050;
			}
			if (thisbar==6){
			thetaMin = 0.018;
			thetaMax = 0.046;
			}
			if (thisbar==7){ 
			thetaMin = 0.014;
			thetaMax = 0.042;
			}
			if (thisbar==8){
			thetaMin = 0.010;
			thetaMax = 0.038;
			}
			if (thisbar==9){
			thetaMin = 0.006;
			thetaMax = 0.034;
			}
			if (thisbar==10){
			thetaMin = 0.002;
			thetaMax = 0.030;
			}
			if (thisbar==11){
			thetaMin = -0.002;
			thetaMax = 0.026;
			}
			if (thisbar==12){
			thetaMin = -0.006;
			thetaMax = 0.022;
			}
			if (thisbar==13){
			thetaMin = -0.010;
			thetaMax = 0.018;
			}
			if (thisbar==14){
			thetaMin = -0.014;
			thetaMax = 0.014;
			}
			if (thisbar==15){
			thetaMin = -0.017;
			thetaMax = 0.010;
			}
			if (thisbar==16){
			thetaMin = -0.021;
			thetaMax = 0.006;
			}
			if (thisbar==17){
			thetaMin = -0.025;
			thetaMax = 0.002;
			}
			if (thisbar==18){
			thetaMin = -0.029;
			thetaMax = -0.002;
			}
			if (thisbar==19){
			thetaMin = -0.033;
			thetaMax = -0.006;
			}
			if (thisbar==20){
			thetaMin = -0.037;
			thetaMax = -0.010;
			}
			if (thisbar==21){
			thetaMin = -0.041;
			thetaMax = -0.014;
			}
			if (thisbar==22){
			thetaMin = -0.045;
			thetaMax = -0.018;
			}
			if (thisbar==23){
			thetaMin = -0.049;
			thetaMax = -0.023;
			}	
			if (thisbar==24){
			thetaMin = -0.053;
			thetaMax = -0.027;
			}	
			if (thisbar==25){
			thetaMin = -0.057;
			thetaMax = -0.031;
			}	
			if (thisbar==26){
			thetaMin = -0.061;
			thetaMax = -0.035;
			}	
			if (thisbar==27){
			thetaMin = -0.065;
			thetaMax = -0.039;
			}	
			if (thisbar==28){
			thetaMin = -0.069;
			thetaMax = -0.043;
			}	
			if (thisbar==29){
			thetaMin = -0.073;
			thetaMax = -0.047;
			}	
		}
		if (nplane==2){
			if (thisbar==0){
			thetaMin = 0.041;
			thetaMax = 0.070;
			}
			if (thisbar==1){
			thetaMin = 0.036;
			thetaMax = 0.065;
			}
			if (thisbar==2){
			thetaMin = 0.031;
			thetaMax = 0.060;
			}
			if (thisbar==3){
			thetaMin = 0.026;
			thetaMax = 0.055;
			}
			if (thisbar==4){
			thetaMin = 0.021;
			thetaMax = 0.050;
			}
			if (thisbar==5){
			thetaMin = 0.016;
			thetaMax = 0.045;
			}
			if (thisbar==6){
			thetaMin = 0.011;
			thetaMax = 0.040;
			}
			if (thisbar==7){ 
			thetaMin = 0.006;
			thetaMax = 0.035;
			}
			if (thisbar==8){
			thetaMin = 0.001;
			thetaMax = 0.030;
			}
			if (thisbar==9){
			thetaMin = -0.004;
			thetaMax = 0.025;
			}
			if (thisbar==10){
			thetaMin = -0.009;
			thetaMax = 0.020;
			}
			if (thisbar==11){
			thetaMin = -0.014;
			thetaMax = 0.015;
			}
			if (thisbar==12){
			thetaMin = -0.019;
			thetaMax = 0.010;
			}
			if (thisbar==13){
			thetaMin = -0.024;
			thetaMax = 0.005;
			}
			if (thisbar==14){
			thetaMin = -0.028;
			thetaMax = 0.000;
			}
			if (thisbar==15){
			thetaMin = -0.033;
			thetaMax = -0.005;
			}
			if (thisbar==16){
			thetaMin = -0.038;
			thetaMax = -0.010;
			}
			if (thisbar==17){
			thetaMin = -0.043;
			thetaMax = -0.015;
			}
			if (thisbar==18){
			thetaMin = -0.048;
			thetaMax = -0.020;
			}
			if (thisbar==19){
			thetaMin = -0.053;
			thetaMax = -0.025;
			}
			if (thisbar==20){
			thetaMin = -0.058;
			thetaMax = -0.031;
			}
			if (thisbar==21){
			thetaMin = -0.063;
			thetaMax = -0.036;
			}
			if (thisbar==22){
			thetaMin = -0.068;
			thetaMax = -0.041;
			}
			if (thisbar==23){
			thetaMin = -0.073;
			thetaMax = -0.046;
			}
		}
		if (nplane==3){
			if (thisbar==0){
			thetaMin = 0.038;
			thetaMax = 0.068;
			}
			if (thisbar==1){
			thetaMin = 0.033;
			thetaMax = 0.063;
			}
			if (thisbar==2){
			thetaMin = 0.028;
			thetaMax = 0.058;
			}
			if (thisbar==3){
			thetaMin = 0.023;
			thetaMax = 0.052;
			}
			if (thisbar==4){
			thetaMin = 0.017;
			thetaMax = 0.047;
			}
			if (thisbar==5){
			thetaMin = 0.012;
			thetaMax = 0.042;
			}
			if (thisbar==6){
			thetaMin = 0.007;
			thetaMax = 0.036;
			}
			if (thisbar==7){
			thetaMin = 0.002;
			thetaMax = 0.031;
			}
			if (thisbar==8){
			thetaMin = -0.003;
			thetaMax = 0.026;
			}
			if (thisbar==9){
			thetaMin = -0.009;
			thetaMax = 0.021;
			}
			if (thisbar==10){
			thetaMin = -0.014;
			thetaMax = 0.015;
			}
			if (thisbar==11){
			thetaMin = -0.019;
			thetaMax = 0.010;
			}
			if (thisbar==12){
			thetaMin = -0.024;
			thetaMax = 0.005;
			}
			if (thisbar==13){
			thetaMin = -0.029;
			thetaMax = -0.001;
			}
			if (thisbar==14){
			thetaMin = -0.035;
			thetaMax = -0.001;
			}
			if (thisbar==15){
			thetaMin = -0.040;
			thetaMax = -0.011;
			}
			if (thisbar==16){
			thetaMin = -0.045;
			thetaMax = -0.016;
			}
			if (thisbar==17){
			thetaMin = -0.050;
			thetaMax = -0.022;
			}
			if (thisbar==18){
			thetaMin = -0.055;
			thetaMax = -0.027;
			}
			if (thisbar==19){
			thetaMin = -0.060;
			thetaMax = -0.032;
			}
			if (thisbar==20){
			thetaMin = -0.066;
			thetaMax = -0.038;
			}
			if (thisbar==21){
			thetaMin = -0.071;
			thetaMax = -0.043;
			}
		}
		if (nplane==4){
			if (thisbar==0){
			thetaMin = 0.036;
			thetaMax = 0.070;
			}
			if (thisbar==1){
			thetaMin = 0.026;
			thetaMax = 0.060;
			}
			if (thisbar==2){
			thetaMin = 0.016;
			thetaMax = 0.050;
			}
			if (thisbar==3){
			thetaMin = 0.006;
			thetaMax = 0.040;
			}
			if (thisbar==4){
			thetaMin = -0.004;
			thetaMax = 0.030;
			}
			if (thisbar==5){
			thetaMin = -0.014;
			thetaMax = 0.020;
			}
			if (thisbar==6){
			thetaMin = -0.023;
			thetaMax = 0.010;
			}
			if (thisbar==7){
			thetaMin = -0.033;
			thetaMax = 0.000;
			}
			if (thisbar==8){
			thetaMin = -0.043;
			thetaMax = -0.010;
			}
			if (thisbar==9){
			thetaMin = -0.053;
			thetaMax = -0.020;
			}
			if (thisbar==10){
			thetaMin = -0.063;
			thetaMax = -0.031;
			}
			if (thisbar==11){
			thetaMin = -0.073;
			thetaMax = -0.041;
			}
		}
	}

	// Below are the theta cuts. They're split apart because I want
	// to be able to put this in a loop eventually to automize
	// the flow of data to histograms
	pastThetaCut = (ExTgtCor_R_th>thetaMin && ExTgtCor_R_th<thetaMax);



//	cout << "Theta Cut: " << thetaCutSt << endl;

//	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;



}

