void qe_cross_section()
{

	double q2;
	double E;
	double Eprime;
	double theta;
	double mass;
	double tau;
	double GD;
	double GEp;
	double GEn;
	double GMp;
	double GMn;
	double mup = 2.7928;
	double mun = -1.9130;
	double a1;
	double b1;
	double b2;
	double b3;

	cout << "Q2 in (GeV/c)^2?" << endl;
	cin >> q2;
	cout << "Beam energy in GeV?" << endl;
	cin >> E;
	cout << "Angle of scattered electron (in degrees)?" << endl;
	cin >> theta;
	if ((q2<0) || (E<0))
	{
		cout << "Uh-oh! Something went wrong..." << endl;;
		return;
	}
	

	GD = 1/((1+q2/(0.71))*(1+q2/(0.71)));

	// Proton mass
	mass = 0.938272;

	tau = q2/(4*mass*mass);

	GEn = (1.70*tau*GD)/(1+(3.30*tau));

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


	cout << endl << endl << "At Q2=" << q2 << " (GeV/c)^2, E=" << E << " GeV, and Theta=" << theta << " degrees, we find that:" << endl;
	cout << "tau = " << tau << endl;

	theta = theta * 3.14159265359/180;
	Eprime = E/(1+((E/mass)*(1-cos(theta))));
	cout << "Eprime = " << Eprime << " GeV" << endl;
	cout << "-------------------------------" << endl;
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
	cout << "-------------------------------" << endl;
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










