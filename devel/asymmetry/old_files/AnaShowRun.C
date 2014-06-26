TTimer* tmer = NULL;
void flash()
{
	TCanvas* flashCanvas = new TCanvas("flashCanvas","flashCanvas",0,0,1200,900);
	flashCanvas->Draw();
	if(!tmer) tmer = new TTimer();
	if(tmer){
		tmer->SetCommand("if(gROOT->GetListOfCanvases()->FindObject(\"flashCanvas\")){flashCanvas->SetFillColor(gRandom->Rndm()*100);  flashCanvas->Modified(1); flashCanvas->Update();}");
		tmer->Start(1000);
	}
}

// void LHRS(int runN)
// {
//  replay_LHRS(runN,20000); 
//  online("detectorL",runN);
// flash();
// }

////////////////////////////////
#define REPLAY_EVT_NUM 50000
////////////////////////////////

void do_Lumi(int runN)
{

	TString LUMIPath="/adaqfs/home/adaq/lumi/Spring09";
    TString currentDir = gSystem.WorkingDirectory();
    cout<<"Current Directory: "<<currentDir<<endl;
    cout<<"Lumi Directory: "<<LUMIPath<<endl;
    gSystem.ChangeDirectory(LUMIPath.Data());
    TString name = "./lumiReplayAuto "; 
    name +=runN;
    cout<<name<<endl;
	gSystem.Exec(name.Data());
	gSystem.ChangeDirectory(currentDir);
	cout<<"And where are we now?: "<<gSystem.WorkingDirectory()<<endl;
	//lumi_plots(runN);
	online("lumi",runN);
	
	
	
	flash();
}

void BB(int runN)
{
	do_all(runN);
// 	replay_det_BB(runN,REPLAY_EVT_NUM); 
// 	replay_scalar_BB(runN,0,0,kTRUE);
// 	online("detectorBB",runN);
// 	online("cer",runN);
 // online("mwdcBB",runN);
// 	flash();
}


void phys(int runN)
{
	replay_phys_L(runN,REPLAY_EVT_NUM); 
	online("physicsL",runN);
	flash();
}

void LHRS(int runN)
{
	do_all(runN);
// 	replay_det_L(runN,REPLAY_EVT_NUM);
// 	online("detectorL",runN);
// 	//	online("richL",runN);
// 	online("pionrejL",runN);
// 	flash();
}




void show_all(int runN)
{
	if (runN<20000) {
  		online("bigbite",runN);
		online("detectorL",runN);
		online("pionrejL",runN);
		online("physicsL",runN);
	} else {
		online("detectorR",runN);
		online("showerR",runN);
		online("detectorND",runN);
		online("physicsR",runN);
	}
    //online("lumi",runN);
	//	online("richL",runN);
}

void do_all(int runN)
{
	if (runN<20000) {
	   
		replay_L(runN,REPLAY_EVT_NUM);
// 		replay_det_BB(runN,REPLAY_EVT_NUM); 
	} else {
		replay_R(runN,REPLAY_EVT_NUM);
  //show_simple(runN);	
	}
	//do_Lumi(runN)
	
	show_all(runN);
  
	flash();
}




void do_scalar(int RunL, int RunR)
{
        if(RunL<0 || RunL>=20000)
         cout << "Please choose L-arm run !!!!!!!!!!!!!!!!!!!!!!" << endl;
        else
        replay_scalar(RunL, 2100000);

        if(RunR<0 || RunR<=20000)
         cout << "Please choose R-arm run !!!!!!!!!!!!!!!!!!!!!!!" << endl;
        else
        replay_scalar(RunR, 2100000);

        ScalarStat(RunL, RunR, 3);
}

// do_range(startRun,endRun)
// {
//  for(int runN = startRun; runN <= endRun; runN++)
//  {
//    replay_det(runN,REPLAY_EVT_NUM);·
//    replay_phys(runN,REPLAY_EVT_NUM);
//    replay_deadtime(runN,100000);
//   // online("detectorL",runN);
//    online("bigbite",runN);
//    online("physics",runN);
//  }
// flash();
// }


int AnaShowRun(UInt_t myrun/*, UInt_t nevt=-1*/)
{
	do_all(myrun);
  //replay(myrun,nevt);
  //online("replay",myrun);
}
