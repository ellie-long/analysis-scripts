




//void MyClass::hand_class_fill_bar_by_bar_cuts(int HeRunNumber, int nplane, int thisbar, bool pastThetaCut, bool madePastLVetoCuts, bool madePastRVetoCuts, bool madePastVetoCuts,TH1F* HANDleft, TH1F* HANDleftcut, TH1F* HANDright, TH1F* HANDrightcut, TH1F* HeThetaCut, TH1F* HePhiCut, TH2F* HeThetaPhiCut, int goodTDCleftcutmin, int goodTDCleftcutmax, int goodTDCrightcutmin, int goodTDCrightcutmax)
void neutron_analysis_class::hand_class_fill_bar_by_bar_cuts(int HeRunNumber, int nplane, int thisbar, bool pastThetaCut, bool madePastLVetoCuts, bool madePastRVetoCuts, bool madePastVetoCuts,TH1F* HANDleft, TH1F* HANDleftcut, TH1F* HANDright, TH1F* HANDrightcut, TH1F* HeThetaCut, TH1F* HePhiCut, TH2F* HeThetaPhiCut, int goodTDCleftcutmin, int goodTDCleftcutmax, int goodTDCrightcutmin, int goodTDCrightcutmax)
{


//	cout << "vvvvvvvvvvvvvvvvv hand_class_fill_bar_by_bar_cuts.h vvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;


// vvvvvvvvvvvvvvvvvvvvvvvvvvvvv Defining goodTDC cut vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//cout << " vvvvvvvvvvvvvvvvvvvvvv Defining goodTDC cut vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
	bool goodLTDC = true;
	bool goodRTDC = true;
	if (nplane==0) 
	{
		

		goodLTDC = (NA_veto_lt_c[thisbar]>goodTDCleftcutmin) && (NA_veto_lt_c[thisbar]>goodTDCleftcutmax);
		goodRTDC = (NA_veto_rt_c[thisbar]>goodTDCrightcutmin) && (NA_veto_rt_c[thisbar]>goodTDCrightcutmax);
	}
	if (nplane==1) 
	{
		goodLTDC = (NA_nd_p1_lt_c[thisbar]>goodTDCleftcutmin) && (NA_nd_p1_lt_c[thisbar]>goodTDCleftcutmax);
		goodRTDC = (NA_nd_p1_rt_c[thisbar]>goodTDCrightcutmin) && (NA_nd_p1_rt_c[thisbar]>goodTDCrightcutmax);
	}
	if (nplane==2) 
	{
		goodLTDC = (NA_nd_p2_lt_c[thisbar]>goodTDCleftcutmin) && (NA_nd_p2_lt_c[thisbar]>goodTDCleftcutmax);
		goodRTDC = (NA_nd_p2_rt_c[thisbar]>goodTDCrightcutmin) && (NA_nd_p2_rt_c[thisbar]>goodTDCrightcutmax);
	}
	if (nplane==3) 
	{
		goodLTDC = (NA_nd_p3_lt_c[thisbar]>goodTDCleftcutmin) && (NA_nd_p3_lt_c[thisbar]>goodTDCleftcutmax);
		goodRTDC = (NA_nd_p3_rt_c[thisbar]>goodTDCrightcutmin) && (NA_nd_p3_rt_c[thisbar]>goodTDCrightcutmax);
	}
	if (nplane==4) 
	{
		goodLTDC = (NA_nd_p4_lt_c[thisbar]>goodTDCleftcutmin) && (NA_nd_p4_lt_c[thisbar]>goodTDCleftcutmax);
		goodRTDC = (NA_nd_p4_rt_c[thisbar]>goodTDCrightcutmin) && (NA_nd_p4_rt_c[thisbar]>goodTDCrightcutmax);
	}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Defining goodTDC cut ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^



// vvvvvvvvvvvvvvvvvv Fill Bar-by-Bar Cut Plots vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//cout << "vvvvvvvvvvvvvvvvvv Fill Bar-by-Bar Cut Plots vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
// The chunk below will fill all of the Bar-by-Bar Cut Plots
//cout << "Filling Vetos..." << endl;

	if (nplane==0)
	{
		HANDleft->Fill(NA_veto_lt_c[thisbar]);
		if (madePastLVetoCuts && goodLTDC) {HANDleftcut->Fill(NA_veto_lt_c[thisbar]);}
		HANDright->Fill(NA_veto_rt_c[thisbar]);
		if (madePastRVetoCuts && goodRTDC) {HANDrightcut->Fill(NA_veto_rt_c[thisbar]);}
	}
	if (nplane==1)
	{
		HANDleft->Fill(NA_nd_p1_lt_c[thisbar]);
		if (madePastLVetoCuts && goodLTDC) {HANDleftcut->Fill(NA_nd_p1_lt_c[thisbar]);}
		HANDright->Fill(NA_nd_p1_rt_c[thisbar]);
		if (madePastRVetoCuts && goodRTDC) {HANDrightcut->Fill(NA_nd_p1_rt_c[thisbar]);}
	}
	if (nplane==2)
	{
		HANDleft->Fill(NA_nd_p2_lt_c[thisbar]);
		if (madePastLVetoCuts && goodLTDC) {HANDleftcut->Fill(NA_nd_p2_lt_c[thisbar]);}
		HANDright->Fill(NA_nd_p2_rt_c[thisbar]);
		if (madePastRVetoCuts && goodRTDC) {HANDrightcut->Fill(NA_nd_p2_rt_c[thisbar]);}
	}
	if (nplane==3)
	{
		HANDleft->Fill(NA_nd_p3_lt_c[thisbar]);
		if (madePastLVetoCuts && goodLTDC) {HANDleftcut->Fill(NA_nd_p3_lt_c[thisbar]);}
		HANDright->Fill(NA_nd_p3_rt_c[thisbar]);
		if (madePastRVetoCuts && goodRTDC) {HANDrightcut->Fill(NA_nd_p3_rt_c[thisbar]);}
	}
	if (nplane==4)
	{
		HANDleft->Fill(NA_nd_p4_lt_c[thisbar]);
		if (madePastLVetoCuts && goodLTDC) {HANDleftcut->Fill(NA_nd_p4_lt_c[thisbar]);}
		HANDright->Fill(NA_nd_p4_rt_c[thisbar]);
		if (madePastRVetoCuts && goodRTDC) {HANDrightcut->Fill(NA_nd_p4_rt_c[thisbar]);}
	}
//cout << "Phi plots..." << endl;
	if (pastThetaCut) {HeThetaCut->Fill(ExTgtCor_R_th);}
	HePhiCut->Fill(ExTgtCor_R_ph);
	if (pastThetaCut) {HeThetaPhiCut->Fill(ExTgtCor_R_ph,ExTgtCor_R_th);}
// ^^^^^^^^^^^^^^^^^^ Fill Bar-by-Bar Cut Plots ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


//	cout << "^^^^^^^^^^^^^^^^^ hand_class_fill_bar_by_bar_cuts.h ^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
}
