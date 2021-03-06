// ***************************************************
//
// This script should draw a picture of the HAND
//
// 07-21-10
// Elena Long
//
// ***************************************************

#include <iostream>
#include <string>
#include <string.h>

// Search for HAND to get to the PMT definitions

void neutron_detector_draw_nonumbers(){
			TString canvasName = "hand";
			TString canvasTitle = "HAND";
			TCanvas *handCanvas = new TCanvas(canvasName,canvasTitle,1400,770); //x,y
		//	TCanvas *hand = new TCanvas("hand","Neutron Data",1400,770); //x,y
			handpad01 =  new TPad("handpad01","handpad01",0.0000,0.0000,0.1000,1.0000,0,0,0);
			handpad02 =  new TPad("handpad02","handpad02",0.1000,0.5000,0.4000,1.0000,0,0,0);
			handpad03 =  new TPad("handpad03","handpad03",0.1000,0.0000,0.4000,0.5000,0,0,0);
			handpad04 =  new TPad("handpad04","handpad04",0.4000,0.5000,0.7000,1.0000,0,0,0);
			handpad05 =  new TPad("handpad05","handpad05",0.7000,0.5000,1.0000,1.0000,0,0,0);
			handpad06 =  new TPad("handpad06","handpad06",0.4000,0.0000,0.7000,0.5000,0,0,0);
			handpad07 =  new TPad("handpad07","handpad07",0.7000,0.0000,1.0000,0.5000,0,0,0);
			handpad01->Draw(); handpad02->Draw(); handpad03->Draw(); handpad04->Draw(); handpad05->Draw();
			handpad06->Draw(); handpad07->Draw();

			// This huge block is to draw the HAND. Data follows well below here.
			handpad01->cd();
//			handpad01->SetBackgroundColor(kBlack);
			// This set is for Plane Veto
			TPaveLabel *p0b10 = new TPaveLabel(0.1835,0.6650,0.2165,0.6980,"");
		//	p0b10->SetLineColor(kWhite);
			p0b10->SetFillColor(kMagenta);
			p0b10->Draw();
			TPaveLabel *p0b11 = new TPaveLabel(0.1835,0.6320,0.2165,0.6650,"");
		//	p0b11->SetLineColor(kWhite);
			p0b11->SetFillColor(kMagenta);
			p0b11->Draw();
			TPaveLabel *p0b12 = new TPaveLabel(0.1835,0.5990,0.2165,0.6320,"");
			p0b12->SetFillColor(kMagenta);
			p0b12->Draw();
			TPaveLabel *p0b13 = new TPaveLabel(0.1835,0.5660,0.2165,0.5990,"");
			p0b13->SetFillColor(kMagenta);
			p0b13->Draw();
			TPaveLabel *p0b14 = new TPaveLabel(0.1835,0.5330,0.2165,0.5660,"");
			p0b14->SetFillColor(kMagenta);
			p0b14->Draw();
			TPaveLabel *p0b15 = new TPaveLabel(0.1835,0.5000,0.2165,0.5330,"");
			p0b15->SetFillColor(kMagenta);
			p0b15->Draw();
			TPaveLabel *p0b16 = new TPaveLabel(0.1835,0.4670,0.2165,0.5000,"");
			p0b16->SetFillColor(kMagenta);
			p0b16->Draw();
			TPaveLabel *p0b17 = new TPaveLabel(0.1835,0.4340,0.2165,0.4670,"");
			p0b17->SetFillColor(kMagenta);
			p0b17->Draw();
			TPaveLabel *p0b18 = new TPaveLabel(0.1835,0.4010,0.2165,0.4340,"");
			p0b18->SetFillColor(kMagenta);
			p0b18->Draw();
			TPaveLabel *p0b19 = new TPaveLabel(0.1835,0.3680,0.2165,0.4010,"");
			p0b19->SetFillColor(kMagenta);
			p0b19->Draw();
			TPaveLabel *p0b20 = new TPaveLabel(0.1835,0.3350,0.2165,0.3680,"");
			p0b20->SetFillColor(kMagenta);
			p0b20->Draw();
			TPaveLabel *p0b21 = new TPaveLabel(0.1835,0.3020,0.2165,0.3350,"");
			p0b21->SetFillColor(kMagenta);
			p0b21->Draw();
			TPaveLabel *p0b00 = new TPaveLabel(0.2165,0.9170,0.2495,0.9500,"");
			p0b00->SetFillColor(kMagenta);
			p0b00->Draw();
			TPaveLabel *p0b01 = new TPaveLabel(0.2165,0.8840,0.2495,0.9170,"");
			p0b01->SetFillColor(kMagenta);
			p0b01->Draw();
			TPaveLabel *p0b02 = new TPaveLabel(0.2165,0.8510,0.2495,0.8840,"");
			p0b02->SetFillColor(kMagenta);
			p0b02->Draw();
			TPaveLabel *p0b03 = new TPaveLabel(0.2165,0.8180,0.2495,0.8510,"");
			p0b03->SetFillColor(kMagenta);
			p0b03->Draw();
			TPaveLabel *p0b04 = new TPaveLabel(0.2165,0.7850,0.2495,0.8180,"");
			p0b04->SetFillColor(kMagenta);
			p0b04->Draw();
			TPaveLabel *p0b05 = new TPaveLabel(0.2165,0.7520,0.2495,0.7850,"");
			p0b05->SetFillColor(kMagenta);
			p0b05->Draw();
			TPaveLabel *p0b06 = new TPaveLabel(0.2165,0.7190,0.2495,0.7520,"");
			p0b06->SetFillColor(kMagenta);
			p0b06->Draw();
			TPaveLabel *p0b07 = new TPaveLabel(0.2165,0.6860,0.2495,0.7190,"");
			p0b07->SetFillColor(kMagenta);
			p0b07->Draw();
			TPaveLabel *p0b08 = new TPaveLabel(0.2165,0.6530,0.2495,0.6860,"");
			p0b08->SetFillColor(kMagenta);
			p0b08->Draw();
			TPaveLabel *p0b09 = new TPaveLabel(0.2165,0.6200,0.2495,0.6530,"");
			p0b09->SetFillColor(kMagenta);
			p0b09->Draw();
			TPaveLabel *p0b22 = new TPaveLabel(0.2165,0.3470,0.2495,0.3800,"");
			p0b22->SetFillColor(kMagenta);
			p0b22->Draw();
			TPaveLabel *p0b23 = new TPaveLabel(0.2165,0.3140,0.2495,0.3470,"");
			p0b23->SetFillColor(kMagenta);
			p0b23->Draw();
			TPaveLabel *p0b24 = new TPaveLabel(0.2165,0.2810,0.2495,0.3140,"");
			p0b24->SetFillColor(kMagenta);
			p0b24->Draw();
			TPaveLabel *p0b25 = new TPaveLabel(0.2165,0.2480,0.2495,0.2810,"");
			p0b25->SetFillColor(kMagenta);
			p0b25->Draw();
			TPaveLabel *p0b26 = new TPaveLabel(0.2165,0.2150,0.2495,0.2480,"");
			p0b26->SetFillColor(kMagenta);
			p0b26->Draw();
			TPaveLabel *p0b27 = new TPaveLabel(0.2165,0.1820,0.2495,0.2150,"");
			p0b27->SetFillColor(kMagenta);
			p0b27->Draw();
			TPaveLabel *p0b28 = new TPaveLabel(0.2165,0.1490,0.2495,0.1820,"");
			p0b28->SetFillColor(kMagenta);
			p0b28->Draw();
			TPaveLabel *p0b29 = new TPaveLabel(0.2165,0.1160,0.2495,0.1490,"");
			p0b29->SetFillColor(kMagenta);
			p0b29->Draw();
			TPaveLabel *p0b30 = new TPaveLabel(0.2165,0.0830,0.2495,0.1160,"");
			p0b30->SetFillColor(kMagenta);
			p0b30->Draw();
			TPaveLabel *p0b31 = new TPaveLabel(0.2165,0.0500,0.2495,0.0830,"");
			p0b31->SetFillColor(kMagenta);
			p0b31->Draw();

			// This set is for Plane 1
			TPaveLabel *p1b00 = new TPaveLabel(0.2525,0.9200,0.4175,0.9500,"");
			p1b00->SetFillColor(kBlue);
			p1b00->Draw();
			TPaveLabel *p1b01 = new TPaveLabel(0.2525,0.8900,0.4175,0.9200,"");
			p1b01->SetFillColor(kBlue);
			p1b01->Draw();
			TPaveLabel *p1b02 = new TPaveLabel(0.2525,0.8600,0.4175,0.8900,"");
			p1b02->SetFillColor(kBlue);
			p1b02->Draw();
			TPaveLabel *p1b03 = new TPaveLabel(0.2525,0.8300,0.4175,0.8600,"");
			p1b03->SetFillColor(kBlue);
			p1b03->Draw();
			TPaveLabel *p1b04 = new TPaveLabel(0.2525,0.8000,0.4175,0.8300,"");
			p1b04->SetFillColor(kBlue);
			p1b04->Draw();
			TPaveLabel *p1b05 = new TPaveLabel(0.2525,0.7700,0.4175,0.8000,"");
			p1b05->SetFillColor(kBlue);
			p1b05->Draw();
			TPaveLabel *p1b06 = new TPaveLabel(0.2525,0.7400,0.4175,0.7700,"");
			p1b06->SetFillColor(kBlue);
			p1b06->Draw();
			TPaveLabel *p1b07 = new TPaveLabel(0.2525,0.7100,0.4175,0.7400,"");
			p1b07->SetFillColor(kBlue);
			p1b07->Draw();
			TPaveLabel *p1b08 = new TPaveLabel(0.2525,0.6800,0.4175,0.7100,"");
			p1b08->SetFillColor(kBlue);
			p1b08->Draw();
			TPaveLabel *p1b09 = new TPaveLabel(0.2525,0.6500,0.4175,0.6800,"");
			p1b09->SetFillColor(kBlue);
			p1b09->Draw();
			TPaveLabel *p1b10 = new TPaveLabel(0.2525,0.6200,0.4175,0.6500,"");
			p1b10->SetFillColor(kBlue);
			p1b10->Draw();
			TPaveLabel *p1b11 = new TPaveLabel(0.2525,0.5900,0.4175,0.6200,"");
			p1b11->SetFillColor(kBlue);
			p1b11->Draw();
			TPaveLabel *p1b12 = new TPaveLabel(0.2525,0.5600,0.4175,0.5900,"");
			p1b12->SetFillColor(kBlue);
			p1b12->Draw();
			TPaveLabel *p1b13 = new TPaveLabel(0.2525,0.5300,0.4175,0.5600,"");
			p1b13->SetFillColor(kBlue);
			p1b13->Draw();
			TPaveLabel *p1b14 = new TPaveLabel(0.2525,0.5000,0.4175,0.5300,"");
			p1b14->SetFillColor(kBlue);
			p1b14->Draw();
			TPaveLabel *p1b15 = new TPaveLabel(0.2525,0.4700,0.4175,0.5000,"");
			p1b15->SetFillColor(kBlue);
			p1b15->Draw();
			TPaveLabel *p1b16 = new TPaveLabel(0.2525,0.4400,0.4175,0.4700,"");
			p1b16->SetFillColor(kBlue);
			p1b16->Draw();
			TPaveLabel *p1b17 = new TPaveLabel(0.2525,0.4100,0.4175,0.4400,"");
			p1b17->SetFillColor(kBlue);
			p1b17->Draw();
			TPaveLabel *p1b18 = new TPaveLabel(0.2525,0.3800,0.4175,0.4100,"");
			p1b18->SetFillColor(kBlue);
			p1b18->Draw();
			TPaveLabel *p1b19 = new TPaveLabel(0.2525,0.3500,0.4175,0.3800,"");
			p1b19->SetFillColor(kBlue);
			p1b19->Draw();
			TPaveLabel *p1b20 = new TPaveLabel(0.2525,0.3200,0.4175,0.3500,"");
			p1b20->SetFillColor(kBlue);
			p1b20->Draw();
			TPaveLabel *p1b21 = new TPaveLabel(0.2525,0.2900,0.4175,0.3200,"");
			p1b21->SetFillColor(kBlue);
			p1b21->Draw();
			TPaveLabel *p1b22 = new TPaveLabel(0.2525,0.2600,0.4175,0.2900,"");
			p1b22->SetFillColor(kBlue);
			p1b22->Draw();
			TPaveLabel *p1b23 = new TPaveLabel(0.2525,0.2300,0.4175,0.2600,"");
			p1b23->SetFillColor(kBlue);
			p1b23->Draw();
			TPaveLabel *p1b24 = new TPaveLabel(0.2525,0.2000,0.4175,0.2300,"");
			p1b24->SetFillColor(kBlue);
			p1b24->Draw();
			TPaveLabel *p1b25 = new TPaveLabel(0.2525,0.1700,0.4175,0.2000,"");
			p1b25->SetFillColor(kBlue);
			p1b25->Draw();
			TPaveLabel *p1b26 = new TPaveLabel(0.2525,0.1400,0.4175,0.1700,"");
			p1b26->SetFillColor(kBlue);
			p1b26->Draw();
			TPaveLabel *p1b27 = new TPaveLabel(0.2525,0.1100,0.4175,0.1400,"");
			p1b27->SetFillColor(kBlue);
			p1b27->Draw();
			TPaveLabel *p1b28 = new TPaveLabel(0.2525,0.0800,0.4175,0.1100,"");
			p1b28->SetFillColor(kBlue);
			p1b28->Draw();
			TPaveLabel *p1b29 = new TPaveLabel(0.2525,0.0500,0.4175,0.0800,"");
			p1b29->SetFillColor(kBlue);
			p1b29->Draw();

			// This set is for Plane 2
			TPaveLabel *p2b00 = new TPaveLabel(0.4200,0.9125,0.5850,0.9500,"");
			p2b00->SetFillColor(kCyan);
			p2b00->Draw();
			TPaveLabel *p2b01 = new TPaveLabel(0.4200,0.8750,0.5850,0.9125,"");
			p2b01->SetFillColor(kCyan);
			p2b01->Draw();
			TPaveLabel *p2b02 = new TPaveLabel(0.4200,0.8375,0.5850,0.8750,"");
			p2b02->SetFillColor(kCyan);
			p2b02->Draw();
			TPaveLabel *p2b03 = new TPaveLabel(0.4200,0.8000,0.5850,0.8375,"");
			p2b03->SetFillColor(kCyan);
			p2b03->Draw();
			TPaveLabel *p2b04 = new TPaveLabel(0.4200,0.7625,0.5850,0.8000,"");
			p2b04->SetFillColor(kCyan);
			p2b04->Draw();
			TPaveLabel *p2b05 = new TPaveLabel(0.4200,0.7250,0.5850,0.7625,"");
			p2b05->SetFillColor(kCyan);
			p2b05->Draw();
			TPaveLabel *p2b06 = new TPaveLabel(0.4200,0.6875,0.5850,0.7250,"");
			p2b06->SetFillColor(kCyan);
			p2b06->Draw();
			TPaveLabel *p2b07 = new TPaveLabel(0.4200,0.6500,0.5850,0.6875,"");
			p2b07->SetFillColor(kCyan);
			p2b07->Draw();
			TPaveLabel *p2b08 = new TPaveLabel(0.4200,0.6125,0.5850,0.6500,"");
			p2b08->SetFillColor(kCyan);
			p2b08->Draw();
			TPaveLabel *p2b09 = new TPaveLabel(0.4200,0.5750,0.5850,0.6125,"");
			p2b09->SetFillColor(kCyan);
			p2b09->Draw();
			TPaveLabel *p2b10 = new TPaveLabel(0.4200,0.5375,0.5850,0.5750,"");
			p2b10->SetFillColor(kCyan);
			p2b10->Draw();
			TPaveLabel *p2b11 = new TPaveLabel(0.4200,0.5000,0.5850,0.5375,"");
			p2b11->SetFillColor(kCyan);
			p2b11->Draw();
			TPaveLabel *p2b12 = new TPaveLabel(0.4200,0.4625,0.5850,0.5000,"");
			p2b12->SetFillColor(kCyan);
			p2b12->Draw();
			TPaveLabel *p2b13 = new TPaveLabel(0.4200,0.4250,0.5850,0.4625,"");
			p2b13->SetFillColor(kCyan);
			p2b13->Draw();
			TPaveLabel *p2b14 = new TPaveLabel(0.4200,0.3875,0.5850,0.4250,"");
			p2b14->SetFillColor(kCyan);
			p2b14->Draw();
			TPaveLabel *p2b15 = new TPaveLabel(0.4200,0.3500,0.5850,0.3875,"");
			p2b15->SetFillColor(kCyan);
			p2b15->Draw();
			TPaveLabel *p2b16 = new TPaveLabel(0.4200,0.3125,0.5850,0.3500,"");
			p2b16->SetFillColor(kCyan);
			p2b16->Draw();
			TPaveLabel *p2b17 = new TPaveLabel(0.4200,0.2750,0.5850,0.3125,"");
			p2b17->SetFillColor(kCyan);
			p2b17->Draw();
			TPaveLabel *p2b18 = new TPaveLabel(0.4200,0.2375,0.5850,0.2750,"");
			p2b18->SetFillColor(kCyan);
			p2b18->Draw();
			TPaveLabel *p2b19 = new TPaveLabel(0.4200,0.2000,0.5850,0.2375,"");
			p2b19->SetFillColor(kCyan);
			p2b19->Draw();
			TPaveLabel *p2b20 = new TPaveLabel(0.4200,0.1625,0.5850,0.2000,"");
			p2b20->SetFillColor(kCyan);
			p2b20->Draw();
			TPaveLabel *p2b21 = new TPaveLabel(0.4200,0.1250,0.5850,0.1625,"");
			p2b21->SetFillColor(kCyan);
			p2b21->Draw();
			TPaveLabel *p2b22 = new TPaveLabel(0.4200,0.0875,0.5850,0.1250,"");
			p2b22->SetFillColor(kCyan);
			p2b22->Draw();
			TPaveLabel *p2b23 = new TPaveLabel(0.4200,0.0500,0.5850,0.0875,"");
			p2b23->SetFillColor(kCyan);
			p2b23->Draw();
			
			// This set is for Plane 3
			TPaveLabel *p3b00 = new TPaveLabel(0.5850,0.9050,0.7500,0.9500,"");
			p3b00->SetFillColor(kRed);
			p3b00->Draw();
			TPaveLabel *p3b01 = new TPaveLabel(0.5850,0.8600,0.7500,0.9050,"");
			p3b01->SetFillColor(kRed);
			p3b01->Draw();
			TPaveLabel *p3b02 = new TPaveLabel(0.5850,0.8150,0.7500,0.8600,"");
			p3b02->SetFillColor(kRed);
			p3b02->Draw();
			TPaveLabel *p3b03 = new TPaveLabel(0.5850,0.7700,0.7500,0.8150,"");
			p3b03->SetFillColor(kRed);
			p3b03->Draw();
			TPaveLabel *p3b04 = new TPaveLabel(0.5850,0.7250,0.7500,0.7700,"");
			p3b04->SetFillColor(kRed);
			p3b04->Draw();
			TPaveLabel *p3b05 = new TPaveLabel(0.5850,0.6800,0.7500,0.7250,"");
			p3b05->SetFillColor(kRed);
			p3b05->Draw();
			TPaveLabel *p3b06 = new TPaveLabel(0.5850,0.6425,0.7500,0.6800,"");
			p3b06->SetFillColor(kCyan);
			p3b06->Draw();
			TPaveLabel *p3b07 = new TPaveLabel(0.5850,0.6050,0.7500,0.6425,"");
			p3b07->SetFillColor(kCyan);
			p3b07->Draw();
			TPaveLabel *p3b08 = new TPaveLabel(0.5850,0.5675,0.7500,0.6050,"");
			p3b08->SetFillColor(kCyan);
			p3b08->Draw();
			TPaveLabel *p3b09 = new TPaveLabel(0.5850,0.5300,0.7500,0.5675,"");
			p3b09->SetFillColor(kCyan);
			p3b09->Draw();
			TPaveLabel *p3b10 = new TPaveLabel(0.5850,0.5000,0.7500,0.5300,"");
			p3b10->SetFillColor(kBlue);
			p3b10->Draw();
			TPaveLabel *p3b11 = new TPaveLabel(0.5850,0.4700,0.7500,0.5000,"");
			p3b11->SetFillColor(kBlue);
			p3b11->Draw();
			TPaveLabel *p3b12 = new TPaveLabel(0.5850,0.4325,0.7500,0.4700,"");
			p3b12->SetFillColor(kCyan);
			p3b12->Draw();
			TPaveLabel *p3b13 = new TPaveLabel(0.5850,0.3950,0.7500,0.4325,"");
			p3b13->SetFillColor(kCyan);
			p3b13->Draw();
			TPaveLabel *p3b14 = new TPaveLabel(0.5850,0.3575,0.7500,0.3950,"");
			p3b14->SetFillColor(kCyan);
			p3b14->Draw();
			TPaveLabel *p3b15 = new TPaveLabel(0.5850,0.3200,0.7500,0.3575,"");
			p3b15->SetFillColor(kCyan);
			p3b15->Draw();
			TPaveLabel *p3b16 = new TPaveLabel(0.5850,0.2750,0.7500,0.3200,"");
			p3b16->SetFillColor(kRed);
			p3b16->Draw();
			TPaveLabel *p3b17 = new TPaveLabel(0.5850,0.2300,0.7500,0.2750,"");
			p3b17->SetFillColor(kRed);
			p3b17->Draw();
			TPaveLabel *p3b18 = new TPaveLabel(0.5850,0.1850,0.7500,0.2300,"");
			p3b18->SetFillColor(kRed);
			p3b18->Draw();
			TPaveLabel *p3b19 = new TPaveLabel(0.5850,0.1400,0.7500,0.1850,"");
			p3b19->SetFillColor(kRed);
			p3b19->Draw();
			TPaveLabel *p3b20 = new TPaveLabel(0.5850,0.0950,0.7500,0.1400,"");
			p3b20->SetFillColor(kRed);
			p3b20->Draw();
			TPaveLabel *p3b21 = new TPaveLabel(0.5850,0.0500,0.7500,0.0950,"");
			p3b21->SetFillColor(kRed);
			p3b21->Draw();

			// This set is for Plane 4
			TPaveLabel *p4b00 = new TPaveLabel(0.7500,0.8750,0.9150,0.9500,"");
			p4b00->SetFillColor(kGreen);
			p4b00->Draw();
			TPaveLabel *p4b01 = new TPaveLabel(0.7500,0.8000,0.9150,0.8750,"");
			p4b01->SetFillColor(kGreen);
			p4b01->Draw();
			TPaveLabel *p4b02 = new TPaveLabel(0.7500,0.7250,0.9150,0.8000,"");
			p4b02->SetFillColor(kGreen);
			p4b02->Draw();
			TPaveLabel *p4b03 = new TPaveLabel(0.7500,0.6500,0.9150,0.7250,"");
			p4b03->SetFillColor(kGreen);
			p4b03->Draw();
			TPaveLabel *p4b04 = new TPaveLabel(0.7500,0.5750,0.9150,0.6500,"");
			p4b04->SetFillColor(kGreen);
			p4b04->Draw();
			TPaveLabel *p4b05 = new TPaveLabel(0.7500,0.5000,0.9150,0.5750,"");
			p4b05->SetFillColor(kGreen);
			p4b05->Draw();
			TPaveLabel *p4b06 = new TPaveLabel(0.7500,0.4250,0.9150,0.5000,"");
			p4b06->SetFillColor(kGreen);
			p4b06->Draw();
			TPaveLabel *p4b07 = new TPaveLabel(0.7500,0.3500,0.9150,0.4250,"");
			p4b07->SetFillColor(kGreen);
			p4b07->Draw();
			TPaveLabel *p4b08 = new TPaveLabel(0.7500,0.2750,0.9150,0.3500,"");
			p4b08->SetFillColor(kGreen);
			p4b08->Draw();
			TPaveLabel *p4b09 = new TPaveLabel(0.7500,0.2000,0.9150,0.2750,"");
			p4b09->SetFillColor(kGreen);
			p4b09->Draw();
			TPaveLabel *p4b10 = new TPaveLabel(0.7500,0.1250,0.9150,0.2000,"");
			p4b10->SetFillColor(kGreen);
			p4b10->Draw();
			TPaveLabel *p4b11 = new TPaveLabel(0.7500,0.0500,0.9150,0.1250,"");
			p4b11->SetFillColor(kGreen);
			p4b11->Draw();
			
			handpad01->Update();

			TString handOutTitle = "./hand-nonumbers.eps";
			handpad01->Print(handOutTitle);


	cout << "All done!" << endl;



}







































