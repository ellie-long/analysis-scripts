#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

// Gets the q vector
// outType=0 gives magnitude of q
// outType=1 gives theta_q
// outType=2 gives phi_q
double get_q_vec(double E, double Eprime, double theta_e, double phi_e, int outType)
{
	double qvec = sqrt((Eprime**2)*(sin(theta_e)**2*cos(phi_e)**2 + sin(phi_e)**2 + (E/Eprime - cos(theta_e)*cos(phi_e))**2));

	double qx = -Eprime*sin(theta_e)*cos(phi_e);
	double qy = -Eprime*sin(phi_e);
	double qz = (E-Eprime*cos(theta_e)*cos(phi_e));
	double theta_q = atan(qx/qz);
	double phi_q = asin(qy/qvec);

	if (outType == 0) {return qvec;}
	if (outType == 1) {return theta_q;}
	if (outType == 2) {return phi_q;}

	return qvec;
}


// Gets the k' vector of the outgoing nucleon
// outType=0 gives magnitude of k'
// outType=1 gives theta_k'
// outType=2 gives phi_k'
double* get_kp_vec(double E, double Eprime, double theta_e, double phi_e, double kx, double ky, double kz,double kp[])
{
	double kpvec = sqrt((kx-Eprime*sin(theta_e)*cos(phi_e))**2 + (ky-Eprime*sin(phi_e))**2 + (kz+E-Eprime*cos(theta_e)*cos(phi_e))**2);

	double kpx = kx-Eprime*sin(theta_e)*cos(phi_e);
	double kpy = ky-Eprime*sin(phi_e);
	double kpz = kz+E-Eprime*cos(theta_e)*cos(phi_e);
	double theta_kp = atan(kpx/kpz);
	double phi_kp = asin(kpy/kpvec);

	kp[0] = kpvec;
	kp[1] = theta_kp;
	kp[2] = phi_kp;

	return kp;

}



double roundn(double num, double n)
{
	double result = floor(num*10**n + 0.5)/10**n;
	return result;
}

void qe_cross_section()
{

	double q2;		double qvec;		double x;
	double E;		double Eprime;
	double theta;	double theta_deg;	double theta_q;
	double phi;		double phi_deg;		double phi_q;
	double mass;	double tau;			double nu;
	double GD;		double GEp;			double GEn;
	double GMp;		double GMn;
	double mup = 2.7928;				double mun = -1.9130;
	double a1;
	double b1;		double b2;			double b3;
	double P;		double Pprime;		double Pprime1;
	double Pprime2;	double PprimeAve;	double PprimePM;
	double S;		double bindE;
	double dth;		double dph;
	double dth_deg;	double dph_deg;
	double dth_mrad;					double dph_mrad;
	double hand_r;	double theta_n_deg;	double theta_n;
	double hand_a;	double n_area;		double hand_ovr_n;


	cout << "Beam energy E in GeV?" << endl;
	cin >> E;
	cout << "Scattered beam energy E' in GeV?" << endl;
	cin >> Eprime;
	cout << "Angle of scattered electron (in degrees)?" << endl;
	cin >> theta_deg;

	GD = 1/((1+q2/(0.71))*(1+q2/(0.71)));

	// Proton mass
	mass = 0.938272;
	// Binding energy
	bindE = 0.002572681; // GeV for 3He

	double pi = 3.141592653589793238462643383279502884197169399375105820974;

	// Hall A Website
	// dTh = +/- 60 mrad = +/- 3.438 deg
	// -------------------------------------
	// ExtTgtCor_R.th 
	// --> Note, th:ph_tgt are reversed. 
	// dth_tgt = dphi_e & dphi_tgt=dth_e
	// dTh = +/- 55 mrad = +/- 3.151 deg
	// -------------------------------------
	// R.tr.th
	// dTh = +/- 65 mrad = +/- 3.724 deg
//	dth_deg = 3.151; // deg
	dth_deg = 1.432; // deg

	// Hall A Website
	// dPh = +/- 28 mrad = +/- 1.604 deg
	// -------------------------------------
	// ExtTgtCor_R.ph
	// --> Note, th:ph_tgt are reversed. 
	// dth_tgt = dphi_e & dphi_tgt=dth_e
	// dPh = +/- 25 mrad = +/- 1.432 deg
	// -------------------------------------
	// R.tr.ph
	// dPh = +/- 40 mrad = +/- 2.292 deg
//	dph_deg = 1.432; // deg
	dph_deg = 3.151; // deg

	phi_deg = 0;

	phi = phi_deg * pi/180;
	theta = theta_deg * pi/180;
	dph = dph_deg * pi/180;
	dth = dth_deg * pi/180;
	dph_mrad = roundn(dph*1000,1);
	dth_mrad = roundn(dth*1000,1);

	double theta_dth_up   = (theta_deg + dth_deg) * pi/180;
	double theta_dth_down = (theta_deg - dth_deg) * pi/180;
	double phi_dph_up     = (phi_deg + dph_deg) * pi/180;
	double phi_dph_down   = (phi_deg - dph_deg) * pi/180;

	q2 = 4*E*Eprime*sin(theta/2)*sin(theta/2);
	tau = q2/(4*mass*mass);
	nu = E - Eprime;
	x = q2/(2*mass*nu);
	qvec = get_q_vec(E,Eprime,theta,phi,0);

	if ((q2<0) || (E<0))
	{
		cout << "Uh-oh! Something went wrong..." << endl;;
		return;
	}

	double qvec_dth_up   = get_q_vec(E,Eprime,theta_dth_up,phi,0);
	double qvec_dth_down = get_q_vec(E,Eprime,theta_dth_down,phi,0);
	double qvec_dph_up   = get_q_vec(E,Eprime,theta,phi_dph_up,0);
	double qvec_dph_down = get_q_vec(E,Eprime,theta,phi_dph_down,0);

	theta_q = get_q_vec(E,Eprime,theta,phi,1); 
	phi_q   = get_q_vec(E,Eprime,theta,phi,2);

	double theta_q_up   = get_q_vec(E,Eprime,theta_dth_up,phi,1); 
	double theta_q_down = get_q_vec(E,Eprime,theta_dth_down,phi,1); 

	double phi_q_dph_up   = get_q_vec(E,Eprime,theta,phi_dph_up,2);
	double phi_q_dph_down = get_q_vec(E,Eprime,theta,phi_dph_down,2);


	GEn = -(1.70*tau*GD)/(1+(3.30*tau));

	a1 = -0.24;
	b1 = 10.98;
	b2 = 12.82;
	b3 = 21.97;
	GEp = (1+(a1*tau))/(1+(b1*tau)+(b2*tau*tau)+(b3*tau*tau*tau));

	a1 = 0.12;
	b1 = 10.97;
	b2 = 18.86;
	b3 = 6.55;
	GMp = mup*((1+(a1*tau))/(1+(b1*tau)+(b2*tau*tau)+(b3*tau*tau*tau)));

	a1 = 2.33;
	b1 = 14.72;
	b2 = 24.20;
	b3 = 84.1;
	GMn = mun*((1+(a1*tau))/(1+(b1*tau)+(b2*tau*tau)+(b3*tau*tau*tau)));



//	cout << "tau = " << tau << endl;


//	Nucleon initial momentum (kf=250 MeV)
	P=0;
//	P=0.250;
//	S= Binding Energy + P^2/(2M)
	S=bindE+P*P/(2*mass);
//	Calculate momentum of knocked-out nucleon
	Pprime1=sqrt(2*mass*nu+P*P+2*mass*S);
//	P=0.250; // GeV/c
	P=0.120; // GeV/c
	S=bindE+P*P/(2*mass);
	Pprime2=sqrt(2*mass*nu+P*P+2*mass*S);
	PprimeAve=(Pprime2 - Pprime1)/2 + Pprime1;
	PprimePM=(Pprime2 - Pprime1)/2;



	double dtheta_q_up = theta_q - theta_q_up;
	double dtheta_q_down = theta_q_down - theta_q;
	double dphi_q = phi_q_dph_down - phi_q;
/*
	cout << "theta_q = " << theta_q << endl;
	cout << "dtheta_q_up = " << dtheta_q_up << endl;
	cout << "dtheta_q_down = " << dtheta_q_down << endl;
	cout << "theta_q_down = " << theta_q_down << endl;
	cout << "phi_q = " << phi_q << endl;
	cout << "dphi_q = " << dphi_q << endl;
	cout << "phi_q_dph_down = " << phi_q_dph_down << endl;
*/
	if (q2>0.1 && q2<0.2)
	{
//		hand_r		= 4;	// m
		hand_r		= 6;	// m
//		hand_r		= 8;	// m
		hand_a		= 1*3;	// m^2
		theta_n_deg	= 71;	// deg
	}
	else if (q2>0.4 && q2<0.6)
	{
		hand_r		= 6;	// m
		hand_a		= 1*3;	// m^2
		theta_n_deg	= 62.5;	// deg
	}
	else if (q2>0.9 && q2<1.1)
	{
		hand_r		= 8;	// m
		hand_a		= 1*3;	// m^2
		theta_n_deg	= 54;	// deg
	}
	else
	{
		cout << endl;
		cout << "!!!!!!!!!WARNING!!!!!!!!" << endl;
		cout << "HAND data not available!" << endl;
		cout << "!!!!!!!!!WARNING!!!!!!!!" << endl;
		hand_r		= 0;
		hand_a		= 0;
		theta_n_deg	= 0;
	}

	theta_n = theta_n_deg * pi/180;

	double kf=0.120; // GeV/c for 3He
	double k=sqrt(3.0/5.0)*kf;
	S=bindE+k*k/(2*mass);
	double kprime=sqrt(2*mass*nu+k*k+2*mass*S);
	double kp[3]; 
	double kx; double ky; double kz;
	double thisTheta;
	double thisPhi;
	double thisTheta_q;

	double *kp_vec = get_kp_vec(E,Eprime,theta,phi,0,0,0,kp);
	double kpvec[3]; for (int i=0;i<3;i++) {kpvec[i] = kp_vec[i];}

	kx = k*sin(theta_q);	ky = 0; 	kz = k*cos(theta_q);
//	cout << "At theta_q: kx = " << kx << ", ky = " << ky << ", kz = " << kz << endl;
	kp_vec = get_kp_vec(E,Eprime,theta,phi,kx,ky,kz,kp);
	double kpvec_max[3]; for (int i=0;i<3;i++) {kpvec_max[i] = kp_vec[i];}

	kp_vec = get_kp_vec(E,Eprime,theta,phi,-kx,0,-kz,kp);
	double kpvec_min[3]; for (int i=0;i<3;i++) {kpvec_min[i] = kp_vec[i];}

	thisTheta = theta_dth_down;
	thisTheta_q = get_q_vec(E,Eprime,theta,phi,2);
	kx = k*sin(thisTheta_q+pi/2);	ky = 0; 	kz = k*cos(thisTheta_q+pi/2);
	kp_vec = get_kp_vec(E,Eprime,thisTheta,phi,kx,ky,kz,kp);
	double kpvec_perp_max[3]; for (int i=0;i<3;i++) {kpvec_perp_max[i] = kp_vec[i];}

	thisTheta = theta_dth_up;
	thisTheta_q = get_q_vec(E,Eprime,theta,phi,2);
	kx = k*sin(thisTheta_q-pi/2);	ky = 0; 	kz = k*cos(thisTheta_q-pi/2);
	kp_vec = get_kp_vec(E,Eprime,thisTheta,phi,kx,ky,kz,kp);
	double kpvec_perp_min[3]; for (int i=0;i<3;i++) {kpvec_perp_min[i] = kp_vec[i];}

	thisPhi = phi_dph_down;
	kx = 0;		ky = k; 	kz = 0;
	kp_vec = get_kp_vec(E,Eprime,theta,thisPhi,kx,ky,kz,kp);
	double kpvec_vert_max[3]; for (int i=0;i<3;i++) {kpvec_vert_max[i] = kp_vec[i];}

	thisPhi = phi_dph_up;
	kx = 0;		ky = -k; 	kz = 0;
	kp_vec = get_kp_vec(E,Eprime,theta,thisPhi,kx,ky,kz,kp);
	double kpvec_vert_min[3]; for (int i=0;i<3;i++) {kpvec_vert_min[i] = kp_vec[i];}


	// Oval area of neutrons or protons aimed towards HAND
	// r = length of side of rectangle
	double n_r1 = hand_r*(tan(kpvec_perp_max[1]-kpvec[1]) + tan(kpvec[1]-kpvec_perp_min[1]));
	double p_r1 = hand_r*(tan(dtheta_q_up) + tan(dtheta_q_down));
	double n_r2 = hand_r*(tan(kpvec_vert_max[2]-kpvec[2]) + tan(kpvec[2]-kpvec_vert_min[2]));
	double p_r2 = 2*hand_r*tan(dphi_q);
	n_area = n_r1*n_r2;	// m^2
	double p_area = p_r1*p_r2;	// m^2

	// Ratio of HAND area : Neutron area
	hand_ovr_n = hand_a/n_area;
	double hand_ovr_p = hand_a/p_area;



	// -------------------------------------------------------------------------------------------------

	// Converts all angles back to degrees
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// DO NOT DO ANY MATH AFTER THIS POINT
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	theta_q = theta_q * 180/pi;
	theta_q_up = theta_q_up * 180/pi;
	theta_q_down = theta_q_down * 180/pi;
	phi_q_dph_up = phi_q_dph_up * 180/pi;
	phi_q_dph_down = phi_q_dph_down * 180/pi;
	dtheta_q_up = dtheta_q_up * 180/pi;
	dtheta_q_down = dtheta_q_down * 180/pi;
	dphi_q =  dphi_q * 180/pi;

	cout << endl << endl << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << "Input:" << endl;
	cout << "	E	= " << E << " GeV" << endl;
	cout << "	E'	= " << Eprime << " GeV" << endl;
	cout << "	theta_e	= " << theta_deg << " +/- " << dth_deg << " deg (or +/- " << dth_mrad << " mrad)" << endl;
	cout << "	phi_e	= " << phi_deg << " +/- " << dph_deg << " deg (or +/- " << dph_mrad << " mrad)" << endl;
	cout << "- - - - - - - - - - - - - - - -" << endl;
	cout << "Scattered nucleon initial momentum:" << endl;
	cout << "	k_f	= " << kf << " GeV/c" << endl;
	cout << "	|k|	= " << k << " GeV/c" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << endl << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << "Output:" << endl;
	cout << "	Q^2	= " << q2 << " (GeV/c)^2" << endl;
	cout << "	nu	= " << nu << " GeV" << endl;
	cout << "	x	= " << x << endl;
	cout << "	|q|	= " << qvec << " + " << (qvec_dth_down-qvec) << " - " << (qvec-qvec_dth_up) << " GeV/c" << endl;
	cout << "	theta_q	= " << theta_q << " + " << dtheta_q_up << " - " << dtheta_q_down << " deg" << endl;
	cout << "	phi_q	= " << phi_q << " +/- " << dphi_q << " deg" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << "Scattered nucleon:" << endl;
/*	cout << "	Along q-vector (kˆ  = +qˆ):" << endl; // q ˆ p ˆ +/- theta e phi e
	cout << "	(+ Longitudinal)" << endl;
	cout << "		|k'| 	 = " << kpvec_max[0] << " GeV/c" << endl;
	cout << "		theta_k' = " << (kpvec_max[1]*180/pi) << " deg" << endl;
	cout << "		phi_k'	 = " << (kpvec_max[2]*180/pi) << " deg" << endl;
	cout << "	- - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << "	Against q-vector (kˆ = -qˆ):" << endl;
	cout << "	(- Longitudinal)" << endl;
	cout << "		|k'|	 = " << kpvec_min[0] << " GeV/c" << endl;
	cout << "		theta_k' = " << (kpvec_min[1]*180/pi) << " deg" << endl;
	cout << "		phi_k'	 = " << (kpvec_min[2]*180/pi) << " deg" << endl;
	cout << "	- - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << "	Perpendicular to q-vector, Parallel to Scattering Plane (kˆ _|_ qˆ):" << endl;
	cout << "	(+ Transverse, using theta_e - dtheta_e)" << endl;
	cout << "		|k'|	 = " << kpvec_perp_max[0] << " GeV/c" << endl;
	cout << "		theta_k' = " << (kpvec_perp_max[1]*180/pi) << " deg" << endl;
	cout << "		phi_k'	 = " << (kpvec_perp_max[2]*180/pi) << " deg" << endl;
	cout << "	- - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << "	Perpendicular to  neg. q-vector, Parallel to Scattering Plane (kˆ _|_ -qˆ):" << endl;
	cout << "	(- Transverse, using theta_e + dtheta_e)" << endl;
	cout << "		|k'|	 = " << kpvec_perp_min[0] << " GeV/c" << endl;
	cout << "		theta_k' = " << (kpvec_perp_min[1]*180/pi) << " deg" << endl;
	cout << "		phi_k'	 = " << (kpvec_perp_min[2]*180/pi) << " deg" << endl;
	cout << "	- - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << "	Perpendicular to q-vector, Perpendicular to Scattering Plane (kˆ _|_ qˆ):" << endl;
	cout << "	(+ Vertical, using phi_e - dphi_e)" << endl;
	cout << "		|k'| 	 = " << kpvec_vert_max[0] << " GeV/c" << endl;
	cout << "		theta_k' = " << (kpvec_vert_max[1]*180/pi) << " deg" << endl;
	cout << "		phi_k' 	 = " << (kpvec_vert_max[2]*180/pi) << " deg" << endl;
	cout << "	- - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << "	Perpendicular to  neg. q-vector, Perpendicular to Scattering Plane (kˆ _|_ -qˆ):" << endl;
	cout << "	(- Vertical, using phi_e + dphi_e)" << endl;
	cout << "		|k'| 	 = " << kpvec_vert_min[0] << " GeV/c" << endl;
	cout << "		theta_k' = " << (kpvec_vert_min[1]*180/pi) << " deg" << endl;
	cout << "		phi_k' 	 = " << (kpvec_vert_min[2]*180/pi) << " deg" << endl;
	cout << "	---------------------------------------------" << endl;
	cout << "	Summary:" << endl;
*/	cout << "		|k'| 	 = " << (kpvec_max[0]+kpvec_min[0])/2 << " + " << kpvec_perp_max[0]-((kpvec_max[0]+kpvec_min[0])/2) << " - " << ((kpvec_max[0]+kpvec_min[0])/2)-kpvec_perp_min[0] << " GeV/c" << endl;
	cout << "		theta_k' = " << (kpvec[1]*180/pi) << " + " << (kpvec_perp_max[1]-kpvec[1])*180/pi << " - " << (kpvec[1]-kpvec_perp_min[1])*180/pi << " deg" << endl;
	cout << "		phi_k' 	 = " << (kpvec[2]*180/pi) << " +/- " << (kpvec_vert_max[2]-kpvec[2])*180/pi << " deg" << endl;
//	cout << "Scattered Area for Elastic Protons from 1H:" << endl;
//	cout << "		phi_k' = " << (kpvec_vert_min[2]*180/pi) << " deg" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << "HAND Information:" << endl;
	cout << "	HAND r 		= " << hand_r << " m" << endl;
	cout << "	HAND theta	= " << theta_n_deg << " deg" << endl;
	cout << "	HAND area	= " << hand_a << " m^2" << endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << "Scattered Area for QE Nucleons from 3He:" << endl;
	cout << "	Nucleon l1 (from dTh_k)		= " << n_r1 << " m" << endl;
	cout << "	Nucleon l2 (from dPh_k)		= " << n_r2 << " m" << endl;
	cout << "	Area of nucleons (l1*l2) at " << hand_r << " m	= " << n_area << " m^2" << endl;
	cout << "	HAND area/Nucleon area		= " << hand_ovr_n << endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << "Scattered Area for Elastic Protons from 1H:" << endl;
	cout << "	Proton l1 (from dTh_k)		= " << p_r1 << " m" << endl;
	cout << "	Proton l2 (from dPh_k)		= " << p_r2 << " m" << endl;
	cout << "	Area of protons (l1*l2) at " << hand_r << " m	= " << p_area << " m^2" << endl;
	cout << "	HAND area/Proton area		= " << hand_ovr_p << endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << "Ratio of rough 3He knocked-out nucleon:1H acceptance based on areas above:" << endl;
	cout << "	A_n/A_p	= " << hand_ovr_n/hand_ovr_p << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------------------" << endl;
/*	cout <<	"Nucleon (along q-vector):" << endl;
	cout << "Initial momentum = " << "0" << " GeV/c" << endl; 
	cout << "Final momentum = " << Pprime1 << " GeV/c" << endl; 
	cout << "- - - - - - - - - - - - - - - -" << endl;
	cout << "Initial momentum = " << P << " GeV/c" << endl; 
	cout << "Final momentum = " << Pprime2 << " GeV/c" << endl; 
	cout << "- - - - - - - - - - - - - - - -" << endl;
	cout << "Final momentum ave = " << PprimeAve << endl;
	cout << "Final momentum +/- = " << PprimePM << endl;
*/	cout << "---------------------------------------------------------------------" << endl;
	cout << "According to the JJ Kelly fit, " << endl;
	cout << "GEn = " << GEn << endl;
	cout << "GMn = " << GMn << endl;
	cout << "GEp = " << GEp << endl;
	cout << "GMp = " << GMp << endl;
	cout << " - - - - - - - - - - - - - - - " << endl;
	cout << "GEp/G_D = " << (GEp/GD) << endl;
	cout << "GEn/G_D = " << (GEn/GD) << endl;
	cout << "GMp/(mu_p*G_D) = " << (GMp/(mup*GD)) << endl;
	cout << "GMn/(mu_n*G_D) = " << (GMn/(mun*GD)) << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------------------" << endl;
//	crosssection = (4*(1/137)*(1/137)*3.8937e-32)*Eprime*Eprime*(cos(theta/2)*cos(theta/2))*(1/(q2*q2))*(Eprime/E)*(((GE*GE + tau*GM*GM)/(1+tau)) + 2*tau*GM*GM*(tan(theta/2)*tan(theta/2)));
//	crosssection = (4*(1/137)*(1/137)*3.8937)*Eprime*Eprime*(cos(theta/2)*cos(theta/2))*(1/(q2*q2))*(Eprime/E)*(((GE*GE + tau*GM*GM)/(1+tau)) + 2*tau*GM*GM*(tan(theta/2)*tan(theta/2)));
//	double firstterm = (4*(7.29735257e-3)*(7.29735257e-3)*3.8937e-32)*Eprime*Eprime*(cos(theta/2)*cos(theta/2))*(1/(q2*q2));
//	double secondterm = (Eprime/E);
//	double thirdterm = (((GE*GE + tau*GM*GM)/(1+tau)) + 2*tau*GM*GM*(tan(theta/2)*tan(theta/2)));


	double protoncs = ((4*(7.29735257e-3)*(7.29735257e-3)*3.8937e-32)*Eprime*Eprime*(cos(theta/2)*cos(theta/2))*(1/(q2*q2)))*(Eprime/E)*(((GEp*GEp + tau*GMp*GMp)/(1+tau)) + 2*tau*GMp*GMp*(tan(theta/2)*tan(theta/2)));
	double neutroncs = ((4*(7.29735257e-3)*(7.29735257e-3)*3.8937e-32)*Eprime*Eprime*(cos(theta/2)*cos(theta/2))*(1/(q2*q2)))*(Eprime/E)*(((GEn*GEn + tau*GMn*GMn)/(1+tau)) + 2*tau*GMn*GMn*(tan(theta/2)*tan(theta/2)));

	cout << "Assuming free nucleons, we find:" << endl;
	cout << "(dsigma/dOmega)_p = " << protoncs << " m^2" << endl;
	cout << "(dsigma/dOmega)_n = " << neutroncs << " m^2" << endl;
	cout << " - - - - - - - - - - - - - - - " << endl;
	cout << "If we take these to find the ratio of protons:neutrons in 3He, we find:" << endl;
	cout << "  (using 2*(dsigma/dOmega)_p/(dsigma/dOmega)_n )" << endl;
	cout << "P:N = " << (2*protoncs/neutroncs) << ":1" << endl << endl;

}










