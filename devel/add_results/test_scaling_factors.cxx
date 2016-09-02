#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <math.h>
#include <iomanip>
#include "hand_draw.h"
#include "hand_scaling_factors.h"
#include "hand_class_draw_basic.h"
#include "hand_class_veto_cuts.h"
#include "hand_class_draw_bar_by_bar_cuts.h"
#include "hand_class_draw_tof_nu.h"

using namespace std;


void test_scaling_factors(){
	TString targ = "v";
	TString kine = "0.1";
	TString veto = "w";
// This bit of code should set the charge and livetime scaling factors
	double HeChargeScale; double Helivetime;
	double HeChargeScaleUp; double HelivetimeUp;
	double HeChargeScaleDown; double HelivetimeDown;
	double BeamChargeScaleUp; double BeamlivetimeUp;
	double BeamChargeScaleDown; double BeamlivetimeDown;
	int HeRunNumber = 20487;
	int endHeRunNumber = 20511;
		hand_scaling_factors(HeRunNumber, endHeRunNumber, HeChargeScale, Helivetime, HeChargeScaleUp, HelivetimeUp, HeChargeScaleDown, HelivetimeDown, BeamChargeScaleUp, BeamlivetimeUp, BeamChargeScaleDown, BeamlivetimeDown, kine, targ);
}
