



void tof_by_run()
{

	TString targ;
	TString kine;
	TString veto;
	TString barbybar;
	bool check = false;

	cout << "Which target do you want to look at? (v=vertical 3He, l=longitudinal 3He, t=transverse 3He, c=All Carbon, h=All Hydrogen, n=All Nitrogen, vc=Vertish Carbon, ltc=Longtransish Carbon, vh=Vertish Hydrogen, lth=Longtransish Hydrogen, ltn=Longtransish Nitrogen)" << endl;
	cin >> targ;
	if ((targ == "v") || (targ == "l") || (targ == "t") || (targ == "c") || (targ == "vc") || (targ == "ltc") || (targ == "h") || (targ == "vh") || (targ == "lth") || (targ == "n") || (targ == "ltn")) { check = true;}
	if (!check) {cout << "Not a valid entry. Exiting..." << endl; return 0;} 
	check = false;
	cout << "What Q2 do you want to look at? (1.0, 0.5, 0.42, 0.1)" << endl;
	cin >> kine;
	if ((kine == "1.0") || (kine == "0.5") || (kine == "0.42") || (kine == "0.1")) { check = true;}
	if (!check) {cout << "Not a valid entry. Exiting..." << endl; return 0;}
	check = false;
	cout << "Do you want data with vetos or without vetos? (w, wo)" << endl;
	cin >> veto;
	if ((veto == "w") || (veto == "wo")) { check = true;}
	if (!check) { cout << "Not a valid entry. Exiting..." << endl; return 0;}
	check = false;
	cout << "Do you want to include bar-by-bar cuts? (y, n)" << endl;
	cin >> barbybar;
	if ((barbybar == "y") || (barbybar == "n")) { check = true;}
	if (!check) { cout << "Not a valid entry. Exiting..." << endl; return 0;}

	cout << "Did I make it here?" << endl;

	bool drawCuts = true;
//	bool drawCuts = false;

	bool includeVetos;
	if (veto == "w") {includeVetos = true;}
	if (veto == "wo") {includeVetos = false;}

	int HeRunNumber;
	int endHeRunNumber;
	if (kine == "1.0")
	{
//		if (targ == "v") {HeRunNumber = 20596; endHeRunNumber = 20789;}
		if (targ == "v") {HeRunNumber = 20596; endHeRunNumber = 20760;}
//		if (targ == "v") {HeRunNumber = 20751; endHeRunNumber = 20760;}
//		if (targ == "v") {HeRunNumber = 20751; endHeRunNumber = 20760;}
		if (targ == "l") {HeRunNumber = 22393; endHeRunNumber = 22438;}
		if (targ == "t") {HeRunNumber = 22447; endHeRunNumber = 22489;}
		if (targ == "vc") {HeRunNumber = 20591; endHeRunNumber = 20734;}
		if (targ == "ltc") {HeRunNumber = 22380; endHeRunNumber = 22461;}
		if (targ == "vh") {HeRunNumber = 20791; endHeRunNumber = 20792;}
		if (targ == "lth") {HeRunNumber = 22441; endHeRunNumber = 22441;}
		if (targ == "ltn") {HeRunNumber = 22442; endHeRunNumber = 22442;}
		double nuMax = 0.65;
		double nuMin = 0.35;
	}
	if (kine == "0.5")
	{
		if (targ == "v") {HeRunNumber = 20890; endHeRunNumber = 21005;}
		if (targ == "h") {HeRunNumber = 21383; endHeRunNumber = 21387;}
		double nuMax = 0.425;
		double nuMin = 0.125;
	}
	if (kine == "0.1")
	{
//		if (targ == "v") {HeRunNumber = 20487; endHeRunNumber = 20511;}
//		if (targ == "v") {HeRunNumber = 20498; endHeRunNumber = 20511;}
//		if (targ == "v") {HeRunNumber = 20533; endHeRunNumber = 20538;}
		if (targ == "h") {HeRunNumber = 20404; endHeRunNumber = 20407;}
		if (targ == "v") {HeRunNumber = 20487; endHeRunNumber = 20538;}
		double nuMin = 0;
		double nuMax = 0.13;
	}
	

	TString filenameHe;
	TString outFileName;
	bool fileExists = true;
	TString ToFCanvasName = "";

	TH1F *ToFTotal;
	for (int i=HeRunNumber; i<(endHeRunNumber+1); i++)
	{
		filenameHe = "/work/halla/e05102/disk1/ellie/results/";
		if (veto == "w") {filenameHe += "with_vetos/";}			
		if (veto == "wo") {filenameHe += "without_vetos/";}			
		if (kine == "1.0") {filenameHe += "q2_1_";}
		if (kine == "0.5") {filenameHe += "q2_05_";}
		if (kine == "0.1") {filenameHe += "q2_01_";}
		if (kine == "0.42") {filenameHe += "q2_042_";}
		if (targ == "v") {filenameHe += "vert_3he/";}
		if (targ == "l") {filenameHe += "long_3he/";}
		if (targ == "t") {filenameHe += "trans_3he/";}
		if (targ == "c") {filenameHe += "carbon/";}
		if (targ == "vc") {filenameHe += "v_carbon/";}
		if (targ == "ltc") {filenameHe += "lt_carbon/";}
		if (targ == "h") {filenameHe += "hydrogen/";}
		if (targ == "vh") {filenameHe += "v_hydrogen/";}
		if (targ == "lth") {filenameHe += "lt_hydrogen/";}
		if (targ == "n") {filenameHe += "nitrogen/";}
		if (targ == "ltn") {filenameHe += "lt_nitrogen/";}
		filenameHe += "hand_target_asym_vs_nu_for_run_";
		filenameHe += i;
		filenameHe += ".root";

                ifstream ifileHe(filenameHe);
                if (ifileHe)
                {
			fileExists = true;
                        cout << "Looking at file: " << filenameHe << endl;
                }
                else
                {
			fileExists = false;
                        cout << "File " << filenameHe << " does not exist. Ending here." << endl;
                }

		if (fileExists)
		{
			TFile fileHe(filenameHe);	

			ToFTotal = (TH1F*)fileHe.Get("ToFgoodEvent_Total");
//			ToFTotal = (TH1F*)fileHe.Get("HANDleft_p2_b11");
		
			ToFCanvasName = "Canvas_Run_";
			ToFCanvasName += i;
			cout << "CanvasName = " << ToFCanvasName << endl;
			TCanvas *ToFCanvas = new TCanvas(ToFCanvasName,ToFCanvasName,800,600); //x,y
//			ToFCanvas = new TCanvas(ToFCanvasName,ToFCanvasName,800,600); //x,y
			tofpad1  =  new  TPad("tofpad1","tofpad1",0.0000,0.0000,1.0000,1.0000,0,0,0);
			tofpad1->Draw();

			tofpad1->cd();
			ToFTotal->Draw();
			tofpad1->Update();
		}
	}

	TString exitst;
	cout << "Are you ready to finish?" << endl;
	cin >> exitst;

}





