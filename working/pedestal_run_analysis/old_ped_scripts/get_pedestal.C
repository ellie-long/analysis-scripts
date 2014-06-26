// Neat idea, BUT IT'S NOT WORKING!!! GGAARRRRGGGG!!!!!
//
// Love,
// Ellie


void get_pedestal(){

	gSystem->Load("ND_nv_pedestals.so");
	gSystem->Load("ND_n1_pedestals.so");
	gSystem->Load("ND_n2_pedestals.so");
	gSystem->Load("ND_n3_pedestals.so");
	gSystem->Load("ND_n4_pedestals.so");
	
	ND_nv_pedestals();
	ND_n1_pedestals();
	ND_n2_pedestals();
	ND_n3_pedestals();
	ND_n4_pedestals();
}
