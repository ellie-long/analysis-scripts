//
//               in quasi-elastic region                           
//
//             based on Kelly parametrizaion                       
//
//             by Yawei Zhang @ 12/06/2012                        
//
//**************************************************************************//

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>

#define M_p 0.938272046
#define M_n 0.939565378
#define alpha 1.0 / 137.035999679
#define degtorad 0.0174532925

using namespace std;

//get mott cross section
double GetMottXS(double E, double theta, double Ep, double q2)
{
//  double xs;

  xs=pow(alpha/2/E,2) * pow(cos(theta/2),2) / pow(sin(theta/2),4) * Ep / E;

//  double mott = ((4*(7.29735257e-3)*(7.29735257e-3)*3.8937e-32)*Ep*Ep*(cos(theta/2)*cos(theta/2))*(1/(q2*q2)))*(Ep/E);
//  double mottInNb = mott*pow(10,-37);

  return xs;
//  return mottInNb;
}



int qe_cs_yawei()
{
  double Q2, E, theta, Ep;
  double Ge, Gm, mup, mun;
  double tau;
  double xs_mott, rosen,  xs;

  ofstream outfile;
  outfile.open ("neutron.txt");

  int target;
  theta=17;
  theta=theta*degtorad;

  double aep[2]={1, -0.24};
  double amp[2]={1, 0.12};
  double amn[2]={1, 2.33};

  double bep[3]={10.98, 12.82, 21.97};
  double bmp[3]={10.97, 18.86, 6.55};
  double bmn[3]={14.72, 24.20, 84.1};

  mup=2.793;
  mun=-1.913;

  cout<<"Input target name (0 for p and 1 for n):";
  cin>>target;

   cout<< "Q2	E		Ep		xs_mott		xs" <<endl;
//  for (int i=0; i<500; i++)
  for (int i=12; i<13; i++)
  {
   Q2=0.01+i*0.01;

// Proton Cross Section Calculation
   if(target==0)
     {
//       E=Q2/M_p+sqrt(Q2*Q2/M_p/M_p+8*Q2);
       E=Q2/M_p+sqrt(Q2*Q2/M_p/M_p+4*Q2/sin(theta/2)/sin(theta/2));
       E=E/4;
//       Ep=E/(1+E/M_p*(1-cos(theta)));
       Ep = E/(1+((E/M_p)*(1-cos(theta))));
//       Ep = cos(theta);
       tau=Q2/4/M_p/M_p;
       Ge=(aep[0]+aep[1]*tau)/(1+bep[0]*tau+bep[1]*tau*tau+bep[2]*tau*tau*tau);
//       Ge = (1+(aep[1]*tau))/(1+(bep[0]*tau)+(bep[1]*tau*tau)+(bep[2]*tau*tau*tau));
//       Gm=(amp[0]+amp[1]*tau)/(1+bmp[0]*tau+bmp[1]*tau*tau+bmp[2]*tau*tau*tau);
       Gm=mup*(amp[0]+amp[1]*tau)/(1+bmp[0]*tau+bmp[1]*tau*tau+bmp[2]*tau*tau*tau);
//       Gm = mup*((1+(amp[1]*tau))/(1+(bmp[0]*tau)+(bmp[1]*tau*tau)+(bmp[2]*tau*tau*tau)));
       xs_mott=GetMottXS(E, theta, Ep, Q2);
       rosen=(pow(Ge,2)+tau*pow(Gm,2))/(1+tau)+2*tau*pow(Gm,2)*pow(tan(theta/2),2);
     }
   else
     {
   // Neutron Cross Section Calculation
//       E=Q2/M_n+sqrt(Q2*Q2/M_n/M_n+8*Q2);
       E=Q2/M_p+sqrt(Q2*Q2/M_p/M_p+4*Q2/sin(theta/2)/sin(theta/2));
       E=E/4;
       Ep=E/(1+E/M_n*(1-cos(theta)));
       tau=Q2/4/M_n/M_n;
       Ge=1.70*tau/(1+3.30*tau)*pow(1+Q2/0.71,-2);
       Gm=mun*(amn[0]+amn[1]*tau)/(1+bmn[0]*tau+bmn[1]*tau*tau+bmn[2]*tau*tau*tau);
       xs_mott=GetMottXS(E, theta, Ep, Q2);
       rosen=(pow(Ge,2)+tau*pow(Gm,2))/(1+tau)+2*tau*pow(Gm,2)*pow(tan(theta/2),2);
     }

   xs=xs_mott*rosen;

   cout<<Q2<<"\t"<<E<<"\t"<<Ep<<"\t"<<xs_mott<<"\t"<<xs<<endl;
    outfile<<Q2<<"\t"<<E<<"\t"<<Ep<<"\t"<<xs_mott<<"\t"<<xs<<endl;
   cout << "GE = " << Ge << endl;
   cout << "GM = " << Gm << endl;
  }

  // outfile.close();

  return 0;
}
