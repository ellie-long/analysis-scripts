// *************************************************** 
//
// This script should create a list of definitions for 
// all of the vetos and antivetos for the Hall A
// Neutron Detector 





//void MyClass::hand_class_veto_cuts(int nplane, int thisbar, bool& madePastLVetoCuts, bool& madePastRVetoCuts, bool& madePastVetoCuts, double vetoTDCcutmin, double vetoTDCcutmax, Int_t jentry, TString& allVetos, bool& useIf, bool& useIfElse, bool& useSwitch) 
void neutron_analysis_class::hand_class_veto_cuts(int nplane, int thisbar, bool& madePastLVetoCuts, bool& madePastRVetoCuts, bool& madePastVetoCuts, double vetoTDCcutmin, double vetoTDCcutmax, Int_t jentry, TString& allVetos, bool& useIf, bool& useIfElse, bool& useSwitch) 
{

	useIfElse = true;

	bool includeVetos = true;
	bool includeAntivetos = false;
	bool antivetosAsVetos = false;

//	cout << "vvvvvvvvvvvvvvvvvvvvvvvvv hand_define_vetos.h vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
//	cout << "Plane: " << nplane << ", Bar: " << thisbar << ", jentry: " << jentry << endl;
//	cout << "Running hand_define_vetos.h for p" << nplane << "b" << thisbar << " where includeVetos=" << includeVetos <<  " where includeAntivetos=" << includeAntivetos << " and antivetosAsVetos=" << antivetosAsVetos << endl;
	// This huge set of if statements defines the vetos for each good bar we're
	// going to look at. So far the Good Bar with the most vetos has 6 vetos.
	// Most of the bars do not, in which case the last different veto is repeated 
	// in the remaining veto spaves so that extra bars aren't counted.
	// It should only turn on if includeVetos is set to TRUE.
	// Hopefully this works.
	TString veto1plane = "";
	int veto1bar;
	TString veto2plane = "";
	int veto2bar;
	TString veto3plane = "";
	int veto3bar;
	TString veto4plane = "";
	int veto4bar;
	TString veto5plane = "";
	int veto5bar;
	TString veto6plane = "";
	int veto6bar;
	TString antiveto1plane = "";
	int antiveto1bar;
	TString antiveto2plane = "";
	int antiveto2bar;
	TString antiveto3plane = "";
	int antiveto3bar;
	allVetos = "";
	TString allAntivetos = "";

	if (nplane==1){
		if (thisbar==0){
		veto1plane = "veto"; veto1bar = 0;
		veto2plane = "veto"; veto2bar = 1;
		veto3plane = "veto"; veto3bar = 1;
		veto4plane = "veto"; veto4bar = 1;
		veto5plane = "nd.p1"; veto5bar = 1;
		veto6plane = "nd.p1"; veto6bar = 1;
		antiveto1plane = "nd.p2"; antiveto1bar = 0;
		antiveto2plane = "nd.p2"; antiveto2bar = 1;
		antiveto3plane = "nd.p2"; antiveto3bar = 1;
		}
		else if (thisbar==1){
		veto1plane = "veto"; veto1bar = 0;
		veto2plane = "veto"; veto2bar = 1;
		veto3plane = "veto"; veto3bar = 1;
		veto4plane = "nd.p1"; veto4bar = 0;
		veto5plane = "nd.p1"; veto5bar = 2;
		veto6plane = "nd.p1"; veto6bar = 2;
		antiveto1plane = "nd.p2"; antiveto1bar = 0;
		antiveto2plane = "nd.p2"; antiveto2bar = 1;
		antiveto3plane = "nd.p2"; antiveto3bar = 1;
		}
		else if (thisbar==2){
		veto1plane = "veto"; veto1bar = 1;
		veto2plane = "veto"; veto2bar = 2;
		veto3plane = "veto"; veto3bar = 2;
		veto4plane = "veto"; veto4bar = 2;
		veto5plane = "nd.p1"; veto5bar = 1;
		veto6plane = "nd.p1"; veto6bar = 3;
		antiveto1plane = "nd.p2"; antiveto1bar = 1;
		antiveto2plane = "nd.p2"; antiveto2bar = 2;
		antiveto3plane = "nd.p2"; antiveto3bar = 2;
		}
		else if (thisbar==3){
		veto1plane = "veto"; veto1bar = 2;
		veto2plane = "veto"; veto2bar = 3;
		veto3plane = "veto"; veto3bar = 3;
		veto4plane = "veto"; veto4bar = 3;
		veto5plane = "nd.p1"; veto5bar = 2;
		veto6plane = "nd.p1"; veto6bar = 4;
		antiveto1plane = "nd.p2"; antiveto1bar = 2;
		antiveto2plane = "nd.p2"; antiveto2bar = 3;
		antiveto3plane = "nd.p2"; antiveto3bar = 3;
		}
		else if (thisbar==4){
		veto1plane = "veto"; veto1bar = 3;
		veto2plane = "veto"; veto2bar = 4;
		veto3plane = "veto"; veto3bar = 4;
		veto4plane = "veto"; veto4bar = 4;
		veto5plane = "nd.p1"; veto5bar = 3;
		veto6plane = "nd.p1"; veto6bar = 5;
		antiveto1plane = "nd.p2"; antiveto1bar = 3;
		antiveto2plane = "nd.p2"; antiveto2bar = 4;
		antiveto3plane = "nd.p2"; antiveto3bar = 4;
		}
		else if (thisbar==5){
		veto1plane = "veto"; veto1bar = 4;
		veto2plane = "veto"; veto2bar = 5;
		veto3plane = "veto"; veto3bar = 5;
		veto4plane = "veto"; veto4bar = 5;
		veto5plane = "nd.p1"; veto5bar = 4;
		veto6plane = "nd.p1"; veto6bar = 6;
		antiveto1plane = "nd.p2"; antiveto1bar = 3;
		antiveto2plane = "nd.p2"; antiveto2bar = 4;
		antiveto3plane = "nd.p2"; antiveto3bar = 5;
		}
		else if (thisbar==6){
		veto1plane = "veto"; veto1bar = 5;
		veto2plane = "veto"; veto2bar = 6;
		veto3plane = "veto"; veto3bar = 6;
		veto4plane = "veto"; veto4bar = 6;
		veto5plane = "nd.p1"; veto5bar = 5;
		veto6plane = "nd.p1"; veto6bar = 7;
		antiveto1plane = "nd.p2"; antiveto1bar = 4;
		antiveto2plane = "nd.p2"; antiveto2bar = 5;
		antiveto3plane = "nd.p2"; antiveto3bar = 5;
		}
		else if (thisbar==7){ 
		veto1plane = "veto"; veto1bar = 6;
		veto2plane = "veto"; veto2bar = 7;
		veto3plane = "veto"; veto3bar = 7;
		veto4plane = "veto"; veto4bar = 7;
		veto5plane = "nd.p1"; veto5bar = 6;
		veto6plane = "nd.p1"; veto6bar = 8;
		antiveto1plane = "nd.p2"; antiveto1bar = 5;
		antiveto2plane = "nd.p2"; antiveto2bar = 6;
		antiveto3plane = "nd.p2"; antiveto3bar = 6;
		}
		else if (thisbar==8){
		veto1plane = "veto"; veto1bar = 7;
		veto2plane = "veto"; veto2bar = 8; 
		veto3plane = "veto"; veto3bar = 10; 
		veto4plane = "veto"; veto4bar = 10;
		veto5plane = "nd.p1"; veto5bar = 7;
		veto6plane = "nd.p1"; veto6bar = 9;
		antiveto1plane = "nd.p2"; antiveto1bar = 6;
		antiveto2plane = "nd.p2"; antiveto2bar = 7;
		antiveto3plane = "nd.p2"; antiveto3bar = 7;
		}
		else if (thisbar==9){
		veto1plane = "veto"; veto1bar = 8;
		veto2plane = "veto"; veto2bar = 9; 
		veto3plane = "veto"; veto3bar = 10;
		veto4plane = "veto"; veto4bar = 11; 
		veto5plane = "nd.p1"; veto5bar = 8;
		veto6plane = "nd.p1"; veto6bar = 10;
		antiveto1plane = "nd.p2"; antiveto1bar = 7;
		antiveto2plane = "nd.p2"; antiveto2bar = 8;
		antiveto3plane = "nd.p2"; antiveto3bar = 8;
		}
		else if (thisbar==10){
		veto1plane = "veto"; veto1bar = 9;
		veto2plane = "veto"; veto2bar = 11;
		veto3plane = "veto"; veto3bar = 12;
		veto4plane = "veto"; veto4bar = 12;
		veto5plane = "nd.p1"; veto5bar = 9;
		veto6plane = "nd.p1"; veto6bar = 11;
		antiveto1plane = "nd.p2"; antiveto1bar = 7;
		antiveto2plane = "nd.p2"; antiveto2bar = 8;
		antiveto3plane = "nd.p2"; antiveto3bar = 9;
		}
		else if (thisbar==11){
		veto1plane = "veto"; veto1bar = 9;
		veto2plane = "veto"; veto2bar = 12;
		veto3plane = "veto"; veto3bar = 13;
		veto4plane = "veto"; veto4bar = 13;
		veto5plane = "nd.p1"; veto5bar = 10;
		veto6plane = "nd.p1"; veto6bar = 12;
		antiveto1plane = "nd.p2"; antiveto1bar = 8;
		antiveto2plane = "nd.p2"; antiveto2bar = 9;
		antiveto3plane = "nd.p2"; antiveto3bar = 9;
		}
		else if (thisbar==12){
		veto1plane = "veto"; veto1bar = 13;
		veto2plane = "veto"; veto2bar = 14;
		veto3plane = "veto"; veto3bar = 14;
		veto4plane = "veto"; veto4bar = 14;
		veto5plane = "nd.p1"; veto5bar = 11;
		veto6plane = "nd.p1"; veto6bar = 13;
		antiveto1plane = "nd.p2"; antiveto1bar = 9;
		antiveto2plane = "nd.p2"; antiveto2bar = 10;
		antiveto3plane = "nd.p2"; antiveto3bar = 10;
		}
		else if (thisbar==13){
		veto1plane = "veto"; veto1bar = 13;
		veto2plane = "veto"; veto2bar = 14;
		veto3plane = "veto"; veto3bar = 15;
		veto4plane = "veto"; veto4bar = 15;
		veto5plane = "nd.p1"; veto5bar = 12;
		veto6plane = "nd.p1"; veto6bar = 14;
		antiveto1plane = "nd.p2"; antiveto1bar = 10;
		antiveto2plane = "nd.p2"; antiveto2bar = 11;
		antiveto3plane = "nd.p2"; antiveto3bar = 11;
		}
		else if (thisbar==14){
		veto1plane = "veto"; veto1bar = 14;
		veto2plane = "veto"; veto2bar = 15;
		veto3plane = "veto"; veto3bar = 16;
		veto4plane = "veto"; veto4bar = 16;
		veto5plane = "nd.p1"; veto5bar = 13;
		veto6plane = "nd.p1"; veto6bar = 15;
		antiveto1plane = "nd.p2"; antiveto1bar = 11;
		antiveto2plane = "nd.p2"; antiveto2bar = 12;
		antiveto3plane = "nd.p2"; antiveto3bar = 12;
		}
		else if (thisbar==15){
		veto1plane = "veto"; veto1bar = 15;
		veto2plane = "veto"; veto2bar = 16;
		veto3plane = "veto"; veto3bar = 17;
		veto4plane = "veto"; veto4bar = 17;
		veto5plane = "nd.p1"; veto5bar = 14;
		veto6plane = "nd.p1"; veto6bar = 16;
		antiveto1plane = "nd.p2"; antiveto1bar = 11;
		antiveto2plane = "nd.p2"; antiveto2bar = 12;
		antiveto3plane = "nd.p2"; antiveto3bar = 12;
		}
		else if (thisbar==16){
		veto1plane = "veto"; veto1bar = 16;
		veto2plane = "veto"; veto2bar = 17;
		veto3plane = "veto"; veto3bar = 18;
		veto4plane = "veto"; veto4bar = 18;
		veto5plane = "nd.p1"; veto5bar = 15;
		veto6plane = "nd.p1"; veto6bar = 17;
		antiveto1plane = "nd.p2"; antiveto1bar = 12;
		antiveto2plane = "nd.p2"; antiveto2bar = 13;
		antiveto3plane = "nd.p2"; antiveto3bar = 13;
		}
		else if (thisbar==17){
		veto1plane = "veto"; veto1bar = 17;
		veto2plane = "veto"; veto2bar = 18;
		veto3plane = "veto"; veto3bar = 19;
		veto4plane = "veto"; veto4bar = 19;
		veto5plane = "nd.p1"; veto5bar = 16;
		veto6plane = "nd.p1"; veto6bar = 18;
		antiveto1plane = "nd.p2"; antiveto1bar = 13;
		antiveto2plane = "nd.p2"; antiveto2bar = 14;
		antiveto3plane = "nd.p2"; antiveto3bar = 14;
		}
		else if (thisbar==18){
		veto1plane = "veto"; veto1bar = 18;
		veto2plane = "veto"; veto2bar = 19;
		veto3plane = "veto"; veto3bar = 20;
		veto4plane = "veto"; veto4bar = 22;
		veto5plane = "nd.p1"; veto5bar = 17;
		veto6plane = "nd.p1"; veto6bar = 19;
		antiveto1plane = "nd.p2"; antiveto1bar = 14;
		antiveto2plane = "nd.p2"; antiveto2bar = 15;
		antiveto3plane = "nd.p2"; antiveto3bar = 15;
		}
		else if (thisbar==19){
		veto1plane = "veto"; veto1bar = 19;
		veto2plane = "veto"; veto2bar = 20;
		veto3plane = "veto"; veto3bar = 22;
		veto4plane = "veto"; veto4bar = 22;
		veto5plane = "nd.p1"; veto5bar = 18;
		veto6plane = "nd.p1"; veto6bar = 20;
		antiveto1plane = "nd.p2"; antiveto1bar = 15;
		antiveto2plane = "nd.p2"; antiveto2bar = 16;
		antiveto3plane = "nd.p2"; antiveto3bar = 16;
		}
		else if (thisbar==20){
		veto1plane = "veto"; veto1bar = 20;
		veto2plane = "veto"; veto2bar = 21;
		veto3plane = "veto"; veto3bar = 22;
		veto4plane = "veto"; veto4bar = 23;
		veto5plane = "nd.p1"; veto5bar = 19;
		veto6plane = "nd.p1"; veto6bar = 21;
		antiveto1plane = "nd.p2"; antiveto1bar = 15;
		antiveto2plane = "nd.p2"; antiveto2bar = 16;
		antiveto3plane = "nd.p2"; antiveto3bar = 17;
		}
		else if (thisbar==21){
		veto1plane = "veto"; veto1bar = 21;
		veto2plane = "veto"; veto2bar = 23;
		veto3plane = "veto"; veto3bar = 24;
		veto4plane = "veto"; veto4bar = 24;
		veto5plane = "nd.p1"; veto5bar = 20;
		veto6plane = "nd.p1"; veto6bar = 22;
		antiveto1plane = "nd.p2"; antiveto1bar = 16;
		antiveto2plane = "nd.p2"; antiveto2bar = 17;
		antiveto3plane = "nd.p2"; antiveto3bar = 17;
		}
		else if (thisbar==22){
		veto1plane = "veto"; veto1bar = 24;
		veto2plane = "veto"; veto2bar = 25;
		veto3plane = "veto"; veto3bar = 25;
		veto4plane = "veto"; veto4bar = 25;
		veto5plane = "nd.p1"; veto5bar = 21;
		veto6plane = "nd.p1"; veto6bar = 23;
		antiveto1plane = "nd.p2"; antiveto1bar = 17;
		antiveto2plane = "nd.p2"; antiveto2bar = 18;
		antiveto3plane = "nd.p2"; antiveto3bar = 18;
		}
		else if (thisbar==23){
		veto1plane = "veto"; veto1bar = 25;
		veto2plane = "veto"; veto2bar = 26;
		veto3plane = "veto"; veto3bar = 26;
		veto4plane = "veto"; veto4bar = 26;
		veto5plane = "nd.p1"; veto5bar = 22;
		veto6plane = "nd.p1"; veto6bar = 24;
		antiveto1plane = "nd.p2"; antiveto1bar = 18;
		antiveto2plane = "nd.p2"; antiveto2bar = 19;
		antiveto3plane = "nd.p2"; antiveto3bar = 19;
		}	
		else if (thisbar==24){
		veto1plane = "veto"; veto1bar = 26;
		veto2plane = "veto"; veto2bar = 27;
		veto3plane = "veto"; veto3bar = 27;
		veto4plane = "veto"; veto4bar = 27;
		veto5plane = "nd.p1"; veto5bar = 23;
		veto6plane = "nd.p1"; veto6bar = 25;
		antiveto1plane = "nd.p2"; antiveto1bar = 19;
		antiveto2plane = "nd.p2"; antiveto2bar = 20;
		antiveto3plane = "nd.p2"; antiveto3bar = 20;
		}	
		else if (thisbar==25){
		veto1plane = "veto"; veto1bar = 27;
		veto2plane = "veto"; veto2bar = 28;
		veto3plane = "veto"; veto3bar = 28;
		veto4plane = "veto"; veto4bar = 28;
		veto5plane = "nd.p1"; veto5bar = 24;
		veto6plane = "nd.p1"; veto6bar = 26;
		antiveto1plane = "nd.p2"; antiveto1bar = 19;
		antiveto2plane = "nd.p2"; antiveto2bar = 20;
		antiveto3plane = "nd.p2"; antiveto3bar = 21;
		}	
		else if (thisbar==26){
		veto1plane = "veto"; veto1bar = 27;
		veto2plane = "veto"; veto2bar = 28;
		veto3plane = "veto"; veto3bar = 29;
		veto4plane = "veto"; veto4bar = 29;
		veto5plane = "nd.p1"; veto5bar = 25;
		veto6plane = "nd.p1"; veto6bar = 27;
		antiveto1plane = "nd.p2"; antiveto1bar = 20;
		antiveto2plane = "nd.p2"; antiveto2bar = 21;
		antiveto3plane = "nd.p2"; antiveto3bar = 21;
		}	
		else if (thisbar==27){
		veto1plane = "veto"; veto1bar = 28;
		veto2plane = "veto"; veto2bar = 29;
		veto3plane = "veto"; veto3bar = 30;
		veto4plane = "veto"; veto4bar = 30;
		veto5plane = "nd.p1"; veto5bar = 26;
		veto6plane = "nd.p1"; veto6bar = 28;
		antiveto1plane = "nd.p2"; antiveto1bar = 21;
		antiveto2plane = "nd.p2"; antiveto2bar = 22;
		antiveto3plane = "nd.p2"; antiveto3bar = 22;
		}	
		else if (thisbar==28){
		veto1plane = "veto"; veto1bar = 29;
		veto2plane = "veto"; veto2bar = 30;
		veto3plane = "veto"; veto3bar = 31;
		veto4plane = "veto"; veto4bar = 31;
		veto5plane = "nd.p1"; veto5bar = 27;
		veto6plane = "nd.p1"; veto6bar = 29;
		antiveto1plane = "nd.p2"; antiveto1bar = 22;
		antiveto2plane = "nd.p2"; antiveto2bar = 23;
		antiveto3plane = "nd.p2"; antiveto3bar = 23;
		}	
		else if (thisbar==29){
		veto1plane = "veto"; veto1bar = 30;
		veto2plane = "veto"; veto2bar = 31;
		veto3plane = "veto"; veto3bar = 31;
		veto4plane = "veto"; veto4bar = 31;
		veto5plane = "nd.p1"; veto5bar = 28;
		veto6plane = "nd.p1"; veto6bar = 28;
		antiveto1plane = "nd.p2"; antiveto1bar = 22;
		antiveto2plane = "nd.p2"; antiveto2bar = 23;
		antiveto3plane = "nd.p2"; antiveto3bar = 23;
		}	
	}
	if (nplane==2){
		if (thisbar==0){
		veto1plane = "nd.p1"; veto1bar = 0;
		veto2plane = "nd.p1"; veto2bar = 1;
		veto3plane = "nd.p2"; veto3bar = 1;
		veto4plane = "nd.p2"; veto4bar = 1;
		veto5plane = "nd.p2"; veto5bar = 1;
		veto6plane = "nd.p2"; veto6bar = 1;
		antiveto1plane = "nd.p3"; antiveto1bar = 0;
		antiveto2plane = "nd.p3"; antiveto2bar = 0;
		antiveto3plane = "nd.p3"; antiveto3bar = 0;
		}
		else if (thisbar==1){
		veto1plane = "nd.p1"; veto1bar = 1;
		veto2plane = "nd.p1"; veto2bar = 2;
		veto3plane = "nd.p2"; veto3bar = 0;
		veto4plane = "nd.p2"; veto4bar = 2;
		veto5plane = "nd.p2"; veto5bar = 2;
		veto6plane = "nd.p2"; veto6bar = 2;
		antiveto1plane = "nd.p3"; antiveto1bar = 0;
		antiveto2plane = "nd.p3"; antiveto2bar = 1;
		antiveto3plane = "nd.p3"; antiveto3bar = 1;
		}
		else if (thisbar==2){
		veto1plane = "nd.p1"; veto1bar = 2;
		veto2plane = "nd.p1"; veto2bar = 3;
		veto3plane = "nd.p2"; veto3bar = 1;
		veto4plane = "nd.p2"; veto4bar = 3;
		veto5plane = "nd.p2"; veto5bar = 3;
		veto6plane = "nd.p2"; veto6bar = 3;
		antiveto1plane = "nd.p3"; antiveto1bar = 1;
		antiveto2plane = "nd.p3"; antiveto2bar = 2;
		antiveto3plane = "nd.p3"; antiveto3bar = 2;
		}
		else if (thisbar==3){
		veto1plane = "nd.p1"; veto1bar = 3;
		veto2plane = "nd.p1"; veto2bar = 4;
		veto3plane = "nd.p1"; veto3bar = 5;
		veto4plane = "nd.p2"; veto4bar = 2;
		veto5plane = "nd.p2"; veto5bar = 4;
		veto6plane = "nd.p2"; veto6bar = 4;
		antiveto1plane = "nd.p3"; antiveto1bar = 2;
		antiveto2plane = "nd.p3"; antiveto2bar = 3;
		antiveto3plane = "nd.p3"; antiveto3bar = 3;
		}
		else if (thisbar==4){
		veto1plane = "nd.p1"; veto1bar = 4;
		veto2plane = "nd.p1"; veto2bar = 5;
		veto3plane = "nd.p1"; veto3bar = 6;
		veto4plane = "nd.p2"; veto4bar = 3;
		veto5plane = "nd.p2"; veto5bar = 5;
		veto6plane = "nd.p2"; veto6bar = 5;
		antiveto1plane = "nd.p3"; antiveto1bar = 3;
		antiveto2plane = "nd.p3"; antiveto2bar = 4;
		antiveto3plane = "nd.p3"; antiveto3bar = 4;
		}
		else if (thisbar==5){
		veto1plane = "nd.p1"; veto1bar = 6;
		veto2plane = "nd.p1"; veto2bar = 7;
		veto3plane = "nd.p2"; veto3bar = 4;
		veto4plane = "nd.p2"; veto4bar = 6;
		veto5plane = "nd.p2"; veto5bar = 6;
		veto6plane = "nd.p2"; veto6bar = 6;
		antiveto1plane = "nd.p3"; antiveto1bar = 4;
		antiveto2plane = "nd.p3"; antiveto2bar = 5;
		antiveto3plane = "nd.p3"; antiveto3bar = 5;
		}
		else if (thisbar==6){
		veto1plane = "nd.p1"; veto1bar = 7;
		veto2plane = "nd.p1"; veto2bar = 8;
		veto3plane = "nd.p2"; veto3bar = 5;
		veto4plane = "nd.p2"; veto4bar = 7;
		veto5plane = "nd.p2"; veto5bar = 7;
		veto6plane = "nd.p2"; veto6bar = 7;
		antiveto1plane = "nd.p3"; antiveto1bar = 4;
		antiveto2plane = "nd.p3"; antiveto2bar = 5;
		antiveto3plane = "nd.p3"; antiveto3bar = 5;
		}
		else if (thisbar==7){ 
		veto1plane = "nd.p1"; veto1bar = 8;
		veto2plane = "nd.p1"; veto2bar = 9;
		veto3plane = "nd.p1"; veto3bar = 10;
		veto4plane = "nd.p2"; veto4bar = 6;
		veto5plane = "nd.p2"; veto5bar = 8;
		veto6plane = "nd.p2"; veto6bar = 8;
		antiveto1plane = "nd.p3"; antiveto1bar = 5;
		antiveto2plane = "nd.p3"; antiveto2bar = 6;
		antiveto3plane = "nd.p3"; antiveto3bar = 6;
		}
		else if (thisbar==8){
		veto1plane = "nd.p1"; veto1bar = 9;
		veto2plane = "nd.p1"; veto2bar = 10; 
		veto3plane = "nd.p1"; veto3bar = 11; 
		veto4plane = "nd.p2"; veto4bar = 7;
		veto5plane = "nd.p2"; veto5bar = 9;
		veto6plane = "nd.p2"; veto6bar = 9;
		antiveto1plane = "nd.p3"; antiveto1bar = 6;
		antiveto2plane = "nd.p3"; antiveto2bar = 7;
		antiveto3plane = "nd.p3"; antiveto3bar = 7;
		}
		else if (thisbar==9){
		veto1plane = "nd.p1"; veto1bar = 11;
		veto2plane = "nd.p1"; veto2bar = 12; 
		veto3plane = "nd.p2"; veto3bar = 8;
		veto4plane = "nd.p2"; veto4bar = 10; 
		veto5plane = "nd.p2"; veto5bar = 10;
		veto6plane = "nd.p2"; veto6bar = 10;
		antiveto1plane = "nd.p3"; antiveto1bar = 7;
		antiveto2plane = "nd.p3"; antiveto2bar = 8;
		antiveto3plane = "nd.p3"; antiveto3bar = 8;
		}
		else if (thisbar==10){
		veto1plane = "nd.p1"; veto1bar = 12;
		veto2plane = "nd.p1"; veto2bar = 13;
		veto3plane = "nd.p2"; veto3bar = 9;
		veto4plane = "nd.p2"; veto4bar = 11;
		veto5plane = "nd.p1"; veto5bar = 11;
		veto6plane = "nd.p1"; veto6bar = 14;
		antiveto1plane = "nd.p3"; antiveto1bar = 8;
		antiveto2plane = "nd.p3"; antiveto2bar = 9;
		antiveto3plane = "nd.p3"; antiveto3bar = 10;
		}
		else if (thisbar==11){
		veto1plane = "nd.p1"; veto1bar = 13;
		veto2plane = "nd.p1"; veto2bar = 14;
		veto3plane = "nd.p1"; veto3bar = 15;
		veto4plane = "nd.p2"; veto4bar = 10;
		veto5plane = "nd.p2"; veto5bar = 12;
		veto6plane = "nd.p2"; veto6bar = 12;
		antiveto1plane = "nd.p3"; antiveto1bar = 9;
		antiveto2plane = "nd.p3"; antiveto2bar = 10;
		antiveto3plane = "nd.p3"; antiveto3bar = 11;
		}
		else if (thisbar==12){
		veto1plane = "nd.p1"; veto1bar = 14;
		veto2plane = "nd.p1"; veto2bar = 15;
		veto3plane = "nd.p1"; veto3bar = 16;
		veto4plane = "nd.p2"; veto4bar = 11;
		veto5plane = "nd.p2"; veto5bar = 13;
		veto6plane = "nd.p2"; veto6bar = 13;
		antiveto1plane = "nd.p3"; antiveto1bar = 10;
		antiveto2plane = "nd.p3"; antiveto2bar = 11;
		antiveto3plane = "nd.p3"; antiveto3bar = 12;
		}
		else if (thisbar==13){
		veto1plane = "nd.p1"; veto1bar = 16;
		veto2plane = "nd.p1"; veto2bar = 17;
		veto3plane = "nd.p2"; veto3bar = 12;
		veto4plane = "nd.p2"; veto4bar = 14;
		veto5plane = "nd.p2"; veto5bar = 14;
		veto6plane = "nd.p2"; veto6bar = 14;
		antiveto1plane = "nd.p3"; antiveto1bar = 12;
		antiveto2plane = "nd.p3"; antiveto2bar = 13;
		antiveto3plane = "nd.p3"; antiveto3bar = 13;
		}
		else if (thisbar==14){
		veto1plane = "nd.p1"; veto1bar = 17;
		veto2plane = "nd.p1"; veto2bar = 18;
		veto3plane = "nd.p2"; veto3bar = 13;
		veto4plane = "nd.p2"; veto4bar = 15;
		veto5plane = "nd.p2"; veto5bar = 15;
		veto6plane = "nd.p2"; veto6bar = 15;
		antiveto1plane = "nd.p3"; antiveto1bar = 13;
		antiveto2plane = "nd.p3"; antiveto2bar = 14;
		antiveto3plane = "nd.p3"; antiveto3bar = 14;
		}
		else if (thisbar==15){
		veto1plane = "nd.p1"; veto1bar = 18;
		veto2plane = "nd.p1"; veto2bar = 19;
		veto3plane = "nd.p1"; veto3bar = 20;
		veto4plane = "nd.p2"; veto4bar = 14;
		veto5plane = "nd.p2"; veto5bar = 16;
		veto6plane = "nd.p2"; veto6bar = 16;
		antiveto1plane = "nd.p3"; antiveto1bar = 14;
		antiveto2plane = "nd.p3"; antiveto2bar = 15;
		antiveto3plane = "nd.p3"; antiveto3bar = 15;
		}
		else if (thisbar==16){
		veto1plane = "nd.p1"; veto1bar = 19;
		veto2plane = "nd.p1"; veto2bar = 20;
		veto3plane = "nd.p1"; veto3bar = 21;
		veto4plane = "nd.p2"; veto4bar = 15;
		veto5plane = "nd.p2"; veto5bar = 17;
		veto6plane = "nd.p2"; veto6bar = 17;
		antiveto1plane = "nd.p3"; antiveto1bar = 15;
		antiveto2plane = "nd.p3"; antiveto2bar = 16;
		antiveto3plane = "nd.p3"; antiveto3bar = 16;
		}
		else if (thisbar==17){
		veto1plane = "nd.p1"; veto1bar = 21;
		veto2plane = "nd.p1"; veto2bar = 22;
		veto3plane = "nd.p2"; veto3bar = 16;
		veto4plane = "nd.p2"; veto4bar = 18;
		veto5plane = "nd.p2"; veto5bar = 18;
		veto6plane = "nd.p2"; veto6bar = 18;
		antiveto1plane = "nd.p3"; antiveto1bar = 16;
		antiveto2plane = "nd.p3"; antiveto2bar = 17;
		antiveto3plane = "nd.p3"; antiveto3bar = 17;
		}
		else if (thisbar==18){
		veto1plane = "nd.p1"; veto1bar = 22;
		veto2plane = "nd.p1"; veto2bar = 23;
		veto3plane = "nd.p1"; veto3bar = 23;
		veto4plane = "nd.p2"; veto4bar = 17;
		veto5plane = "nd.p2"; veto5bar = 19;
		veto6plane = "nd.p2"; veto6bar = 19;
		antiveto1plane = "nd.p3"; antiveto1bar = 16;
		antiveto2plane = "nd.p3"; antiveto2bar = 17;
		antiveto3plane = "nd.p3"; antiveto3bar = 17;
		}
		else if (thisbar==19){
		veto1plane = "nd.p1"; veto1bar = 23;
		veto2plane = "nd.p1"; veto2bar = 24;
		veto3plane = "nd.p1"; veto3bar = 25;
		veto4plane = "nd.p2"; veto4bar = 18;
		veto5plane = "nd.p2"; veto5bar = 20;
		veto6plane = "nd.p2"; veto6bar = 20;
		antiveto1plane = "nd.p3"; antiveto1bar = 17;
		antiveto2plane = "nd.p3"; antiveto2bar = 18;
		antiveto3plane = "nd.p3"; antiveto3bar = 18;
		}
		else if (thisbar==20){
		veto1plane = "nd.p1"; veto1bar = 24;
		veto2plane = "nd.p1"; veto2bar = 25;
		veto3plane = "nd.p1"; veto3bar = 26;
		veto4plane = "nd.p2"; veto4bar = 19;
		veto5plane = "nd.p2"; veto5bar = 21;
		veto6plane = "nd.p2"; veto6bar = 21;
		antiveto1plane = "nd.p3"; antiveto1bar = 18;
		antiveto2plane = "nd.p3"; antiveto2bar = 19;
		antiveto3plane = "nd.p3"; antiveto3bar = 19;
		}
		else if (thisbar==21){
		veto1plane = "nd.p1"; veto1bar = 26;
		veto2plane = "nd.p1"; veto2bar = 27;
		veto3plane = "nd.p1"; veto3bar = 27;
		veto4plane = "nd.p2"; veto4bar = 20;
		veto5plane = "nd.p2"; veto5bar = 22;
		veto6plane = "nd.p2"; veto6bar = 22;
		antiveto1plane = "nd.p3"; antiveto1bar = 19;
		antiveto2plane = "nd.p3"; antiveto2bar = 20;
		antiveto3plane = "nd.p3"; antiveto3bar = 20;
		}
		else if (thisbar==22){
		veto1plane = "nd.p1"; veto1bar = 27;
		veto2plane = "nd.p1"; veto2bar = 28;
		veto3plane = "nd.p1"; veto3bar = 28;
		veto4plane = "nd.p2"; veto4bar = 21;
		veto5plane = "nd.p2"; veto5bar = 23;
		veto6plane = "nd.p2"; veto6bar = 23;
		antiveto1plane = "nd.p3"; antiveto1bar = 20;
		antiveto2plane = "nd.p3"; antiveto2bar = 21;
		antiveto3plane = "nd.p3"; antiveto3bar = 21;
		}
		else if (thisbar==23){
		veto1plane = "nd.p1"; veto1bar = 28;
		veto2plane = "nd.p1"; veto2bar = 29;
		veto3plane = "nd.p1"; veto3bar = 29;
		veto4plane = "nd.p2"; veto4bar = 22;
		veto5plane = "nd.p2"; veto5bar = 22;
		veto6plane = "nd.p2"; veto6bar = 22;
		antiveto1plane = "nd.p3"; antiveto1bar = 21;
		antiveto2plane = "nd.p3"; antiveto2bar = 21;
		antiveto3plane = "nd.p3"; antiveto3bar = 21;
		}
	}
	if (nplane==3){
		if (thisbar==0){
		veto1plane = "nd.p2"; veto1bar = 0;
		veto2plane = "nd.p2"; veto2bar = 1;
		veto3plane = "nd.p2"; veto3bar = 1;
		veto4plane = "nd.p2"; veto4bar = 1;
		veto5plane = "nd.p3"; veto5bar = 1;
		veto6plane = "nd.p3"; veto6bar = 1;
		antiveto1plane = "nd.p4"; antiveto1bar = 0;
		antiveto2plane = "nd.p4"; antiveto2bar = 0;
		antiveto3plane = "nd.p4"; antiveto3bar = 0;
		}
		else if (thisbar==1){
		veto1plane = "nd.p2"; veto1bar = 1;
		veto2plane = "nd.p2"; veto2bar = 2;
		veto3plane = "nd.p2"; veto3bar = 2;
		veto4plane = "nd.p2"; veto4bar = 2;
		veto5plane = "nd.p3"; veto5bar = 0;
		veto6plane = "nd.p3"; veto6bar = 2;
		antiveto1plane = "nd.p4"; antiveto1bar = 0;
		antiveto2plane = "nd.p4"; antiveto2bar = 1;
		antiveto3plane = "nd.p4"; antiveto3bar = 1;
		}
		else if (thisbar==2){
		veto1plane = "nd.p2"; veto1bar = 2;
		veto2plane = "nd.p2"; veto2bar = 3;
		veto3plane = "nd.p2"; veto3bar = 3;
		veto4plane = "nd.p2"; veto4bar = 3;
		veto5plane = "nd.p3"; veto5bar = 1;
		veto6plane = "nd.p3"; veto6bar = 3;
		antiveto1plane = "nd.p4"; antiveto1bar = 1;
		antiveto2plane = "nd.p4"; antiveto2bar = 1;
		antiveto3plane = "nd.p4"; antiveto3bar = 1;
		}
		else if (thisbar==3){
		veto1plane = "nd.p2"; veto1bar = 3;
		veto2plane = "nd.p2"; veto2bar = 4;
		veto3plane = "nd.p2"; veto3bar = 4;
		veto4plane = "nd.p2"; veto4bar = 4;
		veto5plane = "nd.p3"; veto5bar = 2;
		veto6plane = "nd.p3"; veto6bar = 4;
		antiveto1plane = "nd.p4"; antiveto1bar = 1;
		antiveto2plane = "nd.p4"; antiveto2bar = 2;
		antiveto3plane = "nd.p4"; antiveto3bar = 2;
		}
		else if (thisbar==4){
		veto1plane = "nd.p2"; veto1bar = 4;
		veto2plane = "nd.p2"; veto2bar = 5;
		veto3plane = "nd.p2"; veto3bar = 6;
		veto4plane = "nd.p2"; veto4bar = 6;
		veto5plane = "nd.p3"; veto5bar = 3;
		veto6plane = "nd.p3"; veto6bar = 5;
		antiveto1plane = "nd.p4"; antiveto1bar = 2;
		antiveto2plane = "nd.p4"; antiveto2bar = 3;
		antiveto3plane = "nd.p4"; antiveto3bar = 3;
		}
		else if (thisbar==5){
		veto1plane = "nd.p2"; veto1bar = 5;
		veto2plane = "nd.p2"; veto2bar = 6;
		veto3plane = "nd.p2"; veto3bar = 7;
		veto4plane = "nd.p2"; veto4bar = 7;
		veto5plane = "nd.p3"; veto5bar = 4;
		veto6plane = "nd.p3"; veto6bar = 6;
		antiveto1plane = "nd.p4"; antiveto1bar = 2;
		antiveto2plane = "nd.p4"; antiveto2bar = 3;
		antiveto3plane = "nd.p4"; antiveto3bar = 3;
		}
		else if (thisbar==6){
		veto1plane = "nd.p2"; veto1bar = 7;
		veto2plane = "nd.p2"; veto2bar = 8;
		veto3plane = "nd.p2"; veto3bar = 8;
		veto4plane = "nd.p2"; veto4bar = 8;
		veto5plane = "nd.p3"; veto5bar = 5;
		veto6plane = "nd.p3"; veto6bar = 7;
		antiveto1plane = "nd.p4"; antiveto1bar = 3;
		antiveto2plane = "nd.p4"; antiveto2bar = 4;
		antiveto3plane = "nd.p4"; antiveto3bar = 4;
		}
		else if (thisbar==7){
		veto1plane = "nd.p2"; veto1bar = 8;
		veto2plane = "nd.p2"; veto2bar = 9;
		veto3plane = "nd.p2"; veto3bar = 9;
		veto4plane = "nd.p2"; veto4bar = 9;
		veto5plane = "nd.p3"; veto5bar = 6;
		veto6plane = "nd.p3"; veto6bar = 8;
		antiveto1plane = "nd.p4"; antiveto1bar = 4;
		antiveto2plane = "nd.p4"; antiveto2bar = 4;
		antiveto3plane = "nd.p4"; antiveto3bar = 4;
		}
		else if (thisbar==8){
		veto1plane = "nd.p2"; veto1bar = 9;
		veto2plane = "nd.p2"; veto2bar = 10;
		veto3plane = "nd.p2"; veto3bar = 10;
		veto4plane = "nd.p2"; veto4bar = 10;
		veto5plane = "nd.p3"; veto5bar = 7;
		veto6plane = "nd.p3"; veto6bar = 9;
		antiveto1plane = "nd.p4"; antiveto1bar = 4;
		antiveto2plane = "nd.p4"; antiveto2bar = 5;
		antiveto3plane = "nd.p4"; antiveto3bar = 5;
		}
		else if (thisbar==9){
		veto1plane = "nd.p2"; veto1bar = 10;
		veto2plane = "nd.p2"; veto2bar = 11;
		veto3plane = "nd.p2"; veto3bar = 11;
		veto4plane = "nd.p2"; veto4bar = 11;
		veto5plane = "nd.p3"; veto5bar = 8;
		veto6plane = "nd.p3"; veto6bar = 10;
		antiveto1plane = "nd.p4"; antiveto1bar = 5;
		antiveto2plane = "nd.p4"; antiveto2bar = 5;
		antiveto3plane = "nd.p4"; antiveto3bar = 5;
		}
		else if (thisbar==10){
		veto1plane = "nd.p2"; veto1bar = 11;
		veto2plane = "nd.p2"; veto2bar = 12;
		veto3plane = "nd.p2"; veto3bar = 12;
		veto4plane = "nd.p2"; veto4bar = 12;
		veto5plane = "nd.p3"; veto5bar = 9;
		veto6plane = "nd.p3"; veto6bar = 11;
		antiveto1plane = "nd.p4"; antiveto1bar = 5;
		antiveto2plane = "nd.p4"; antiveto2bar = 6;
		antiveto3plane = "nd.p4"; antiveto3bar = 6;
		}
		else if (thisbar==11){
		veto1plane = "nd.p2"; veto1bar = 11;
		veto2plane = "nd.p2"; veto2bar = 12;
		veto3plane = "nd.p2"; veto3bar = 12;
		veto4plane = "nd.p2"; veto4bar = 12;
		veto5plane = "nd.p3"; veto5bar = 10;
		veto6plane = "nd.p3"; veto6bar = 12;
		antiveto1plane = "nd.p4"; antiveto1bar = 5;
		antiveto2plane = "nd.p4"; antiveto2bar = 6;
		antiveto3plane = "nd.p4"; antiveto3bar = 6;
		}
		else if (thisbar==12){
		veto1plane = "nd.p2"; veto1bar = 12;
		veto2plane = "nd.p2"; veto2bar = 13;
		veto3plane = "nd.p2"; veto3bar = 14;
		veto4plane = "nd.p2"; veto4bar = 14;
		veto5plane = "nd.p3"; veto5bar = 11;
		veto6plane = "nd.p3"; veto6bar = 13;
		antiveto1plane = "nd.p4"; antiveto1bar = 6;
		antiveto2plane = "nd.p4"; antiveto2bar = 6;
		antiveto3plane = "nd.p4"; antiveto3bar = 7;

//		antiveto1plane = "nd.p1"; antiveto1bar = 16;
//		antiveto2plane = "nd.p2"; antiveto2bar = 13;
//		antiveto3plane = "nd.p4"; antiveto3bar = 6;
		}
		else if (thisbar==13){
		veto1plane = "nd.p2"; veto1bar = 13;
		veto2plane = "nd.p2"; veto2bar = 14;
		veto3plane = "nd.p2"; veto3bar = 14;
		veto4plane = "nd.p2"; veto4bar = 14;
		veto5plane = "nd.p3"; veto5bar = 12;
		veto6plane = "nd.p3"; veto6bar = 14;
		antiveto1plane = "nd.p4"; antiveto1bar = 6;
		antiveto2plane = "nd.p4"; antiveto2bar = 7;
		antiveto3plane = "nd.p4"; antiveto3bar = 7;
		}
		else if (thisbar==14){
		veto1plane = "nd.p2"; veto1bar = 14;
		veto2plane = "nd.p2"; veto2bar = 15;
		veto3plane = "nd.p2"; veto3bar = 15;
		veto4plane = "nd.p2"; veto4bar = 15;
		veto5plane = "nd.p3"; veto5bar = 13;
		veto6plane = "nd.p3"; veto6bar = 15;
		antiveto1plane = "nd.p4"; antiveto1bar = 7;
		antiveto2plane = "nd.p4"; antiveto2bar = 7;
		antiveto3plane = "nd.p4"; antiveto3bar = 7;
		}
		else if (thisbar==15){
		veto1plane = "nd.p2"; veto1bar = 15;
		veto2plane = "nd.p2"; veto2bar = 16;
		veto3plane = "nd.p2"; veto3bar = 16;
		veto4plane = "nd.p2"; veto4bar = 16;
		veto5plane = "nd.p3"; veto5bar = 14;
		veto6plane = "nd.p3"; veto6bar = 16;
		antiveto1plane = "nd.p4"; antiveto1bar = 7;
		antiveto2plane = "nd.p4"; antiveto2bar = 8;
		antiveto3plane = "nd.p4"; antiveto3bar = 8;
		}
		else if (thisbar==16){
		veto1plane = "nd.p2"; veto1bar = 16;
		veto2plane = "nd.p2"; veto2bar = 17;
		veto3plane = "nd.p2"; veto3bar = 18;
		veto4plane = "nd.p2"; veto4bar = 18;
		veto5plane = "nd.p3"; veto5bar = 15;
		veto6plane = "nd.p3"; veto6bar = 17;
		antiveto1plane = "nd.p4"; antiveto1bar = 8;
		antiveto2plane = "nd.p4"; antiveto2bar = 9;
		antiveto3plane = "nd.p4"; antiveto3bar = 9;
		}
		else if (thisbar==17){
		veto1plane = "nd.p2"; veto1bar = 17;
		veto2plane = "nd.p2"; veto2bar = 18;
		veto3plane = "nd.p2"; veto3bar = 19;
		veto4plane = "nd.p2"; veto4bar = 19;
		veto5plane = "nd.p3"; veto5bar = 16;
		veto6plane = "nd.p3"; veto6bar = 18;
		antiveto1plane = "nd.p4"; antiveto1bar = 8;
		antiveto2plane = "nd.p4"; antiveto2bar = 9;
		antiveto3plane = "nd.p4"; antiveto3bar = 9;
		}
		else if (thisbar==18){
		veto1plane = "nd.p2"; veto1bar = 19;
		veto2plane = "nd.p2"; veto2bar = 20;
		veto3plane = "nd.p2"; veto3bar = 20;
		veto4plane = "nd.p2"; veto4bar = 20;
		veto5plane = "nd.p3"; veto5bar = 17;
		veto6plane = "nd.p3"; veto6bar = 19;
		antiveto1plane = "nd.p4"; antiveto1bar = 9;
		antiveto2plane = "nd.p4"; antiveto2bar = 10;
		antiveto3plane = "nd.p4"; antiveto3bar = 10;
		}
		else if (thisbar==19){
		veto1plane = "nd.p2"; veto1bar = 20;
		veto2plane = "nd.p2"; veto2bar = 21;
		veto3plane = "nd.p2"; veto3bar = 21;
		veto4plane = "nd.p2"; veto4bar = 21;
		veto5plane = "nd.p3"; veto5bar = 18;
		veto6plane = "nd.p3"; veto6bar = 20;
		antiveto1plane = "nd.p4"; antiveto1bar = 10;
		antiveto2plane = "nd.p4"; antiveto2bar = 10;
		antiveto3plane = "nd.p4"; antiveto3bar = 10;
		}
		else if (thisbar==20){
		veto1plane = "nd.p2"; veto1bar = 21;
		veto2plane = "nd.p2"; veto2bar = 22;
		veto3plane = "nd.p2"; veto3bar = 22;
		veto4plane = "nd.p2"; veto4bar = 22;
		veto5plane = "nd.p3"; veto5bar = 19;
		veto6plane = "nd.p3"; veto6bar = 21;
		antiveto1plane = "nd.p4"; antiveto1bar = 10;
		antiveto2plane = "nd.p4"; antiveto2bar = 11;
		antiveto3plane = "nd.p4"; antiveto3bar = 11;
		}
		else if (thisbar==21){
		veto1plane = "nd.p2"; veto1bar = 22;
		veto2plane = "nd.p2"; veto2bar = 23;
		veto3plane = "nd.p2"; veto3bar = 23;
		veto4plane = "nd.p2"; veto4bar = 23;
		veto5plane = "nd.p3"; veto5bar = 20;
		veto6plane = "nd.p3"; veto6bar = 20;
		antiveto1plane = "nd.p4"; antiveto1bar = 11;
		antiveto2plane = "nd.p4"; antiveto2bar = 11;
		antiveto3plane = "nd.p4"; antiveto3bar = 11;
		}
	}
	if (nplane==4){
		if (thisbar==0){
		veto1plane = "nd.p3"; veto1bar = 0;
		veto2plane = "nd.p3"; veto2bar = 1;
		veto3plane = "nd.p3"; veto3bar = 1;
		veto4plane = "nd.p3"; veto4bar = 1;
		veto5plane = "nd.p4"; veto5bar = 1;
		veto6plane = "nd.p4"; veto6bar = 1;
		}
		else if (thisbar==1){
		veto1plane = "nd.p3"; veto1bar = 1;
		veto2plane = "nd.p3"; veto2bar = 2;
		veto3plane = "nd.p3"; veto3bar = 3;
		veto4plane = "nd.p3"; veto4bar = 3;
		veto5plane = "nd.p4"; veto5bar = 0;
		veto6plane = "nd.p4"; veto6bar = 2;
		}
		else if (thisbar==2){
		veto1plane = "nd.p3"; veto1bar = 3;
		veto2plane = "nd.p3"; veto2bar = 4;
		veto3plane = "nd.p3"; veto3bar = 5;
		veto4plane = "nd.p3"; veto4bar = 5;
		veto5plane = "nd.p4"; veto5bar = 1;
		veto6plane = "nd.p4"; veto6bar = 3;
		}
		else if (thisbar==3){
		veto1plane = "nd.p3"; veto1bar = 4;
		veto2plane = "nd.p3"; veto2bar = 5;
		veto3plane = "nd.p3"; veto3bar = 6;
		veto4plane = "nd.p3"; veto4bar = 6;
		veto5plane = "nd.p4"; veto5bar = 2;
		veto6plane = "nd.p4"; veto6bar = 4;
		}
		else if (thisbar==4){
		veto1plane = "nd.p3"; veto1bar = 6;
		veto2plane = "nd.p3"; veto2bar = 7;
		veto3plane = "nd.p3"; veto3bar = 8;
		veto4plane = "nd.p3"; veto4bar = 8;
		veto5plane = "nd.p4"; veto5bar = 3;
		veto6plane = "nd.p4"; veto6bar = 5;
		}
		else if (thisbar==5){
		veto1plane = "nd.p3"; veto1bar = 8;
		veto2plane = "nd.p3"; veto2bar = 9;
		veto3plane = "nd.p3"; veto3bar = 10;
		veto4plane = "nd.p3"; veto4bar = 11;
		veto5plane = "nd.p4"; veto5bar = 4;
		veto6plane = "nd.p4"; veto6bar = 6;
		}
		else if (thisbar==6){
		veto1plane = "nd.p3"; veto1bar = 10;
		veto2plane = "nd.p3"; veto2bar = 11;
		veto3plane = "nd.p3"; veto3bar = 12;
		veto4plane = "nd.p3"; veto4bar = 13;
		veto5plane = "nd.p4"; veto5bar = 5;
		veto6plane = "nd.p4"; veto6bar = 7;
		}
		else if (thisbar==7){
		veto1plane = "nd.p3"; veto1bar = 13;
		veto2plane = "nd.p3"; veto2bar = 14;
		veto3plane = "nd.p3"; veto3bar = 15;
		veto4plane = "nd.p3"; veto4bar = 15;
		veto5plane = "nd.p4"; veto5bar = 6;
		veto6plane = "nd.p4"; veto6bar = 8;
		}
		else if (thisbar==8){
		veto1plane = "nd.p3"; veto1bar = 15;
		veto2plane = "nd.p3"; veto2bar = 16;
		veto3plane = "nd.p3"; veto3bar = 17;
		veto4plane = "nd.p3"; veto4bar = 17;
		veto5plane = "nd.p4"; veto5bar = 7;
		veto6plane = "nd.p4"; veto6bar = 9;
		}
		else if (thisbar==9){
		veto1plane = "nd.p3"; veto1bar = 16;
		veto2plane = "nd.p3"; veto2bar = 17;
		veto3plane = "nd.p3"; veto3bar = 18;
		veto4plane = "nd.p3"; veto4bar = 18;
		veto5plane = "nd.p4"; veto5bar = 8;
		veto6plane = "nd.p4"; veto6bar = 10;
		}
		else if (thisbar==10){
		veto1plane = "nd.p3"; veto1bar = 18;
		veto2plane = "nd.p3"; veto2bar = 19;
		veto3plane = "nd.p3"; veto3bar = 20;
		veto4plane = "nd.p3"; veto4bar = 20;
		veto5plane = "nd.p4"; veto5bar = 9;
		veto6plane = "nd.p4"; veto6bar = 11;
		}
		else if (thisbar==11){
		veto1plane = "nd.p3"; veto1bar = 20;
		veto2plane = "nd.p3"; veto2bar = 21;
		veto3plane = "nd.p3"; veto3bar = 21;
		veto4plane = "nd.p3"; veto4bar = 21;
		veto5plane = "nd.p4"; veto5bar = 10;
		veto6plane = "nd.p4"; veto6bar = 10;
		}
	}
	if (!includeVetos)
	{
			veto1plane = ""; veto1bar = 0;
			veto2plane = ""; veto2bar = 0;
			veto3plane = ""; veto3bar = 0;
			veto4plane = ""; veto4bar = 0;
			veto5plane = ""; veto5bar = 0;
			veto6plane = ""; veto6bar = 0;

	}
	if (!includeAntivetos)
	{
			antiveto1plane = ""; antiveto1bar = 0;
			antiveto2plane = ""; antiveto2bar = 0;
			antiveto3plane = ""; antiveto3bar = 0;
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

//	cout << "Vetos: " << allVetos << endl;
//	cout << "allAntivetos: " << allAntivetos << endl;

	// Below are the  veto cuts. They're split apart because I want
	// to be able to put this in a loop eventually to automize
	// the flow of data to histograms
	bool pastVeto1L=true;
	bool pastVeto2L=true;
	bool pastVeto3L=true;
	bool pastVeto4L=true;
	bool pastVeto5L=true;
	bool pastVeto6L=true;
	bool pastVeto1R=true;
	bool pastVeto2R=true;
	bool pastVeto3R=true;
	bool pastVeto4R=true;
	bool pastVeto5R=true;
	bool pastVeto6R=true;


// Define First Veto
	if (veto1plane=="veto") 
	{
		pastVeto1L = (NA_veto_lt_c[veto1bar]<vetoTDCcutmin || NA_veto_lt_c[veto1bar]>vetoTDCcutmax);
		pastVeto1R = (NA_veto_rt_c[veto1bar]<vetoTDCcutmin || NA_veto_rt_c[veto1bar]>vetoTDCcutmax);
	}
	else if (veto1plane=="nd.p1")
	{ 
		pastVeto1L = (NA_nd_p1_lt_c[veto1bar]<vetoTDCcutmin || NA_nd_p1_lt_c[veto1bar]>vetoTDCcutmax);
		pastVeto1R = (NA_nd_p1_rt_c[veto1bar]<vetoTDCcutmin || NA_nd_p1_lt_c[veto1bar]>vetoTDCcutmax);
	}
	else if (veto1plane=="nd.p2")
	{ 
		pastVeto1L = (NA_nd_p2_lt_c[veto1bar]<vetoTDCcutmin || NA_nd_p2_lt_c[veto1bar]>vetoTDCcutmax);
		pastVeto1R = (NA_nd_p2_rt_c[veto1bar]<vetoTDCcutmin || NA_nd_p2_rt_c[veto1bar]>vetoTDCcutmax);
	}
	else if (veto1plane=="nd.p3")
	{ 
		pastVeto1L = (NA_nd_p3_lt_c[veto1bar]<vetoTDCcutmin || NA_nd_p3_lt_c[veto1bar]>vetoTDCcutmax);
		pastVeto1R = (NA_nd_p3_rt_c[veto1bar]<vetoTDCcutmin || NA_nd_p3_rt_c[veto1bar]>vetoTDCcutmax);
	}
	else if (veto1plane=="nd.p4")
	{ 
		pastVeto1L = (NA_nd_p4_lt_c[veto1bar]<vetoTDCcutmin || NA_nd_p4_lt_c[veto1bar]>vetoTDCcutmax);
		pastVeto1R = (NA_nd_p4_rt_c[veto1bar]<vetoTDCcutmin || NA_nd_p4_rt_c[veto1bar]>vetoTDCcutmax);
	}
//	if (!pastVeto1L || !pastVeto1R) {return;}
// Define Second Veto
	if (veto2plane=="veto") 
	{
		pastVeto2L = (NA_veto_lt_c[veto2bar]<vetoTDCcutmin || NA_veto_lt_c[veto2bar]>vetoTDCcutmax);
		pastVeto2R = (NA_veto_rt_c[veto2bar]<vetoTDCcutmin || NA_veto_rt_c[veto2bar]>vetoTDCcutmax);
	}
	else if (veto2plane=="nd.p1")
	{ 
		pastVeto2L = (NA_nd_p1_lt_c[veto2bar]<vetoTDCcutmin || NA_nd_p1_lt_c[veto1bar]>vetoTDCcutmax);
		pastVeto2R = (NA_nd_p1_rt_c[veto2bar]<vetoTDCcutmin || NA_nd_p1_lt_c[veto1bar]>vetoTDCcutmax);
	}
	else if (veto2plane=="nd.p2")
	{ 
		pastVeto2L = (NA_nd_p2_lt_c[veto2bar]<vetoTDCcutmin || NA_nd_p2_lt_c[veto2bar]>vetoTDCcutmax);
		pastVeto2R = (NA_nd_p2_rt_c[veto2bar]<vetoTDCcutmin || NA_nd_p2_rt_c[veto2bar]>vetoTDCcutmax);
	}
	else if (veto2plane=="nd.p3")
	{ 
		pastVeto2L = (NA_nd_p3_lt_c[veto2bar]<vetoTDCcutmin || NA_nd_p3_lt_c[veto2bar]>vetoTDCcutmax);
		pastVeto2R = (NA_nd_p3_rt_c[veto2bar]<vetoTDCcutmin || NA_nd_p3_rt_c[veto2bar]>vetoTDCcutmax);
	}
	else if (veto2plane=="nd.p4")
	{ 
		pastVeto2L = (NA_nd_p4_lt_c[veto2bar]<vetoTDCcutmin || NA_nd_p4_lt_c[veto2bar]>vetoTDCcutmax);
		pastVeto2R = (NA_nd_p4_rt_c[veto2bar]<vetoTDCcutmin || NA_nd_p4_rt_c[veto2bar]>vetoTDCcutmax);
	}
//	if (!pastVeto2L || !pastVeto2R) {return;}
// Define Third Veto
	if (veto3plane=="veto") 
	{
		pastVeto3L = (NA_veto_lt_c[veto3bar]<vetoTDCcutmin || NA_veto_lt_c[veto3bar]>vetoTDCcutmax);
		pastVeto3R = (NA_veto_rt_c[veto3bar]<vetoTDCcutmin || NA_veto_rt_c[veto3bar]>vetoTDCcutmax);
	}
	else if (veto3plane=="nd.p1")
	{ 
		pastVeto3L = (NA_nd_p1_lt_c[veto3bar]<vetoTDCcutmin || NA_nd_p1_lt_c[veto1bar]>vetoTDCcutmax);
		pastVeto3R = (NA_nd_p1_rt_c[veto3bar]<vetoTDCcutmin || NA_nd_p1_lt_c[veto1bar]>vetoTDCcutmax);
	}
	else if (veto3plane=="nd.p2")
	{ 
		pastVeto3L = (NA_nd_p2_lt_c[veto3bar]<vetoTDCcutmin || NA_nd_p2_lt_c[veto3bar]>vetoTDCcutmax);
		pastVeto3R = (NA_nd_p2_rt_c[veto3bar]<vetoTDCcutmin || NA_nd_p2_rt_c[veto3bar]>vetoTDCcutmax);
	}
	else if (veto3plane=="nd.p3")
	{ 
		pastVeto3L = (NA_nd_p3_lt_c[veto3bar]<vetoTDCcutmin || NA_nd_p3_lt_c[veto3bar]>vetoTDCcutmax);
		pastVeto3R = (NA_nd_p3_rt_c[veto3bar]<vetoTDCcutmin || NA_nd_p3_rt_c[veto3bar]>vetoTDCcutmax);
	}
	else if (veto3plane=="nd.p4")
	{ 
		pastVeto3L = (NA_nd_p4_lt_c[veto3bar]<vetoTDCcutmin || NA_nd_p4_lt_c[veto3bar]>vetoTDCcutmax);
		pastVeto3R = (NA_nd_p4_rt_c[veto3bar]<vetoTDCcutmin || NA_nd_p4_rt_c[veto3bar]>vetoTDCcutmax);
	}
//	if (!pastVeto3L || !pastVeto3R) {return;}
// Define Fourth Veto
	if (veto4plane=="veto") 
	{
		pastVeto4L = (NA_veto_lt_c[veto4bar]<vetoTDCcutmin || NA_veto_lt_c[veto4bar]>vetoTDCcutmax);
		pastVeto4R = (NA_veto_rt_c[veto4bar]<vetoTDCcutmin || NA_veto_rt_c[veto4bar]>vetoTDCcutmax);
	}
	else if (veto4plane=="nd.p1")
	{ 
		pastVeto4L = (NA_nd_p1_lt_c[veto4bar]<vetoTDCcutmin || NA_nd_p1_lt_c[veto1bar]>vetoTDCcutmax);
		pastVeto4R = (NA_nd_p1_rt_c[veto4bar]<vetoTDCcutmin || NA_nd_p1_lt_c[veto1bar]>vetoTDCcutmax);
	}
	else if (veto4plane=="nd.p2")
	{ 
		pastVeto4L = (NA_nd_p2_lt_c[veto4bar]<vetoTDCcutmin || NA_nd_p2_lt_c[veto4bar]>vetoTDCcutmax);
		pastVeto4R = (NA_nd_p2_rt_c[veto4bar]<vetoTDCcutmin || NA_nd_p2_rt_c[veto4bar]>vetoTDCcutmax);
	}
	else if (veto4plane=="nd.p3")
	{ 
		pastVeto4L = (NA_nd_p3_lt_c[veto4bar]<vetoTDCcutmin || NA_nd_p3_lt_c[veto4bar]>vetoTDCcutmax);
		pastVeto4R = (NA_nd_p3_rt_c[veto4bar]<vetoTDCcutmin || NA_nd_p3_rt_c[veto4bar]>vetoTDCcutmax);
	}
	else if (veto4plane=="nd.p4")
	{ 
		pastVeto4L = (NA_nd_p4_lt_c[veto4bar]<vetoTDCcutmin || NA_nd_p4_lt_c[veto4bar]>vetoTDCcutmax);
		pastVeto4R = (NA_nd_p4_rt_c[veto4bar]<vetoTDCcutmin || NA_nd_p4_rt_c[veto4bar]>vetoTDCcutmax);
	}
//	if (!pastVeto4L || !pastVeto4R) {return;}
// Define Fifth Veto
	if (veto5plane=="veto") 
	{
		pastVeto5L = (NA_veto_lt_c[veto5bar]<vetoTDCcutmin || NA_veto_lt_c[veto5bar]>vetoTDCcutmax);
		pastVeto5R = (NA_veto_rt_c[veto5bar]<vetoTDCcutmin || NA_veto_rt_c[veto5bar]>vetoTDCcutmax);
	}
	else if (veto5plane=="nd.p1")
	{ 
		pastVeto5L = (NA_nd_p1_lt_c[veto5bar]<vetoTDCcutmin || NA_nd_p1_lt_c[veto1bar]>vetoTDCcutmax);
		pastVeto5R = (NA_nd_p1_rt_c[veto5bar]<vetoTDCcutmin || NA_nd_p1_lt_c[veto1bar]>vetoTDCcutmax);
	}
	else if (veto5plane=="nd.p2")
	{ 
		pastVeto5L = (NA_nd_p2_lt_c[veto5bar]<vetoTDCcutmin || NA_nd_p2_lt_c[veto5bar]>vetoTDCcutmax);
		pastVeto5R = (NA_nd_p2_rt_c[veto5bar]<vetoTDCcutmin || NA_nd_p2_rt_c[veto5bar]>vetoTDCcutmax);
	}
	else if (veto5plane=="nd.p3")
	{ 
		pastVeto5L = (NA_nd_p3_lt_c[veto5bar]<vetoTDCcutmin || NA_nd_p3_lt_c[veto5bar]>vetoTDCcutmax);
		pastVeto5R = (NA_nd_p3_rt_c[veto5bar]<vetoTDCcutmin || NA_nd_p3_rt_c[veto5bar]>vetoTDCcutmax);
	}
	else if (veto5plane=="nd.p4")
	{ 
		pastVeto5L = (NA_nd_p4_lt_c[veto5bar]<vetoTDCcutmin || NA_nd_p4_lt_c[veto5bar]>vetoTDCcutmax);
		pastVeto5R = (NA_nd_p4_rt_c[veto5bar]<vetoTDCcutmin || NA_nd_p4_rt_c[veto5bar]>vetoTDCcutmax);
	}
//	if (!pastVeto5L || !pastVeto5R) {return;}
// Define Sixth Veto
	if (veto6plane=="veto") 
	{
		pastVeto6L = (NA_veto_lt_c[veto6bar]<vetoTDCcutmin || NA_veto_lt_c[veto6bar]>vetoTDCcutmax);
		pastVeto6R = (NA_veto_rt_c[veto6bar]<vetoTDCcutmin || NA_veto_rt_c[veto6bar]>vetoTDCcutmax);
	}
	else if (veto6plane=="nd.p1")
	{ 
		pastVeto6L = (NA_nd_p1_lt_c[veto6bar]<vetoTDCcutmin || NA_nd_p1_lt_c[veto1bar]>vetoTDCcutmax);
		pastVeto6R = (NA_nd_p1_rt_c[veto6bar]<vetoTDCcutmin || NA_nd_p1_lt_c[veto1bar]>vetoTDCcutmax);
	}
	else if (veto6plane=="nd.p2")
	{ 
		pastVeto6L = (NA_nd_p2_lt_c[veto6bar]<vetoTDCcutmin || NA_nd_p2_lt_c[veto6bar]>vetoTDCcutmax);
		pastVeto6R = (NA_nd_p2_rt_c[veto6bar]<vetoTDCcutmin || NA_nd_p2_rt_c[veto6bar]>vetoTDCcutmax);
	}
	else if (veto6plane=="nd.p3")
	{ 
		pastVeto6L = (NA_nd_p3_lt_c[veto6bar]<vetoTDCcutmin || NA_nd_p3_lt_c[veto6bar]>vetoTDCcutmax);
		pastVeto6R = (NA_nd_p3_rt_c[veto6bar]<vetoTDCcutmin || NA_nd_p3_rt_c[veto6bar]>vetoTDCcutmax);
	}
	else if (veto6plane=="nd.p4")
	{ 
		pastVeto6L = (NA_nd_p4_lt_c[veto6bar]<vetoTDCcutmin || NA_nd_p4_lt_c[veto6bar]>vetoTDCcutmax);
		pastVeto6R = (NA_nd_p4_rt_c[veto6bar]<vetoTDCcutmin || NA_nd_p4_rt_c[veto6bar]>vetoTDCcutmax);
	}
//	if (!pastVeto6L || !pastVeto6R) {return;}


	madePastLVetoCuts = (pastVeto1L &&  pastVeto2L && pastVeto3L &&  pastVeto4L &&  pastVeto5L &&  pastVeto6L);
	madePastRVetoCuts = (pastVeto1R &&  pastVeto2R && pastVeto3R &&  pastVeto4R &&  pastVeto5R &&  pastVeto6R);

	if (includeVetos) {madePastVetoCuts = (madePastLVetoCuts && madePastRVetoCuts);}
//	if (!includeVetos) {madePastVetoCuts = true;}

//	if (includeVetos) {cout << "madePastVetoCuts: " << madePastLVetoCuts << ", Plane: " << nplane << ", Bar: " << thisbar << ", jentry: " << jentry << endl;}
//	if (!includeVetos) {cout << "Veto Cut: " << "No Vetos" << endl;}

//	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;



}

