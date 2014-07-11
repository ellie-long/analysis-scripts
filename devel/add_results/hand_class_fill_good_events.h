



//void MyClass::hand_class_fill_good_events(TH1F* ToFgoodEvent, TH1F* ToFcut, TH1F* nuAllCuts, TH1F* nuUpAllCuts, TH1F* nuDownAllCuts, int tofCutMin, int tofCutMax)
void neutron_analysis_class::hand_class_fill_good_events(TH1F* ToFgoodEvent, TH1F* ToFcut, TH1F* nuAllCuts, TH1F* nuUpAllCuts, TH1F* nuDownAllCuts, int tofCutMin, int tofCutMax)
{
//	cout << "vvvvvvvvvvvvvvvvvvv hand_class_fill_good_events.h vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;


	bool goodToFcut = true;
	bool spinUp = true;
	bool spinDown = true;
	
	goodToFcut = ((NA_n_tof[0]>tofCutMin) && (NA_n_tof[0]<tofCutMax));
	spinUp = ((he3R_Spin==1) && (he3R_IsSpinValid==1));
	spinDown = ((he3R_Spin==-1) && (he3R_IsSpinValid==1));

	ToFgoodEvent->Fill(NA_n_tof[0]);
	if (goodToFcut) 
	{
		ToFcut->Fill(NA_n_tof[0]);
		nuAllCuts->Fill(PriKineR_nu);
		if (spinUp) { nuUpAllCuts->Fill(PriKineR_nu);}
		if (spinDown) { nuDownAllCuts->Fill(PriKineR_nu);}
	}

//	cout << "^^^^^^^^^^^^^^^^^^^ hand_class_fill_good_events.h ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
}
