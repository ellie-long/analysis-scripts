// Additional theory functions
#include <stdio.h>

// Lomon
// VMD Model
// Phys. Rev. C 66 (2002) 045501

Double_t F_sv_i_Lomon( Double_t Q2, Int_t sv, Int_t i ){
	Double_t F1_rho, F1_phi, F1_omega;
	Double_t F2_rho, F2_phi, F2_omega;
	Double_t F1_D, F2_D;
	
	// GKex(02S)
	Double_t gf_rhop      = 0.0401;
	Double_t kappa_rhop   = 6.8190;
	Double_t gf_omega     = 0.6739;
	Double_t kappa_omega  = 0.8762;
	Double_t gf_phi       = -0.1676;
	Double_t kappa_phi    = 7.0172;
	Double_t mu_phi       = 0.8544;
	Double_t gf_omegap    = 0.2552;
	Double_t kappa_omegap = 1.4916;
	Double_t L1           = 0.9407;
	Double_t LD           = 1.2111;
	Double_t L2           = 2.7891;
	Double_t LQCD         = 0.150;
	Double_t N            = 1.0;
	

	/*
	// GKex(02L)
	Double_t gf_rhop      = 0.0608;
	Double_t kappa_rhop   = 5.3038;
	Double_t gf_omega     = 0.6896;
	Double_t kappa_omega  = -2.8585;
	Double_t gf_phi       = -0.1852;
	Double_t kappa_phi    = 13.0037;
	Double_t mu_phi       = 0.6848;
	Double_t gf_omegap    = 0.2346;
	Double_t kappa_omegap = 18.2284;
	Double_t L1           = 0.9441;
	Double_t LD           = 1.2350;
	Double_t L2           = 2.8268;
	Double_t LQCD         = 0.150;
	Double_t N            = 1.0;
	*/
	

	Double_t m_rhop       = 1.450;
	Double_t m_rho        = 0.776;
	Double_t m_omega      = 0.784;
	Double_t m_phi        = 1.019;
	Double_t m_omegap     = 1.419;
	Double_t kappa_v      = 3.706;
	Double_t kappa_s      = -0.12;
	

	Double_t Q2t = Q2*(log( LD*LD + Q2 )/(LQCD*LQCD))/log(pow(LD/LQCD,2.0));
	
	Double_t Q2p1 = Q2/(L1*L1+Q2);
	Double_t Q2p1t = Q2p1*(log( LD*LD + Q2p1 )/(LQCD*LQCD))/log(pow(LD/LQCD,2.0));

	Double_t Q2p2 = L1*L1*(Q2+mu_phi*mu_phi)/(mu_phi*mu_phi*(L1*L1+Q2));
	Double_t Q2p2t = Q2p2*(log( LD*LD + Q2p2 )/(LQCD*LQCD))/log(pow(LD/LQCD,2.0));

	if( Q2 != 0 ){
		F1_rho = L1*L1*L2*L2/((L1*L1+Q2t)*(L2*L2+Q2t));
	} else {
		F1_rho = 0.0;
	}
	F1_omega = F1_rho;
	F1_phi = pow(L1*L1*L2*L2/((L1*L1+Q2p1t)*(L2*L2+Q2p1t)), 1.5);

	F2_rho = L1*L1*pow(L2*L2,2.0)/((L1*L1+Q2t)*pow(L2*L2+Q2t,2.0));
	F2_omega = F2_rho;
	F2_phi =  pow(L1*L1*pow(L2*L2,2.0)/((L1*L1+Q2p2t)*pow(L2*L2+Q2p2t,2.0)),1.5);

	F1_D = LD*LD*L2*L2/((LD*LD+Q2t)*(L2*L2+Q2t));
	F2_D = LD*LD*pow(L2*L2,2.0)/((LD*LD+Q2t)*pow(L2*L2+Q2t,2.0));

	Double_t F_iv_1, F_iv_2, F_is_1, F_is_2;

//	F_iv_1 = (N/2.0)*(1.0317+0.0875*pow(1.0+Q2/0.3176,-2.0))*F1_rho/(1.0+Q2/0.5496) + gf_rhop*m_rhop*m_rhop*F1_rho/(m_rhop*m_rhop+Q2) + (1.0 - 1.1192*N/2.0 - gf_rhop)*F1_D;
	F_iv_1 = (N)*(1.0317+0.0875*pow(1.0+Q2/0.3176,-2.0))*F1_rho/(1.0+Q2/0.5496) + gf_rhop*m_rhop*m_rhop*F1_rho/(m_rhop*m_rhop+Q2) + (1.0 - 1.1192*N - gf_rhop)*F1_D;

//	F_iv_2 = (N/2.0)*(5.7824+0.3907*pow(1.0+Q2/0.1422, -1.0))*F2_rho/(1.0+Q2/0.5362) + kappa_rhop*gf_rhop*m_rhop*m_rhop*F2_rho/(m_rhop*m_rhop+Q2) + (kappa_v - 6.1731*N/2.0 - kappa_rhop*gf_rhop)*F2_D;
	F_iv_2 = (N)*(5.7824+0.3907*pow(1.0+Q2/0.1422, -1.0))*F2_rho/(1.0+Q2/0.5362) + kappa_rhop*gf_rhop*m_rhop*m_rhop*F2_rho/(m_rhop*m_rhop+Q2) + (kappa_v - 6.1731*N - kappa_rhop*gf_rhop)*F2_D;
	
	F_is_1 = gf_omega*m_omega*m_omega*F1_omega/(m_omega*m_omega+Q2) + gf_omegap*m_omegap*m_omegap*F1_omega/(m_omegap*m_omegap+Q2) + gf_phi*m_phi*m_phi*F1_phi/(m_phi*m_phi+Q2) + (1.0 - gf_omega-gf_omegap)*F1_D;

	F_is_2 = kappa_omega*gf_omega*m_omega*m_omega*F2_omega/(m_omega*m_omega+Q2) + kappa_omegap*gf_omegap*m_omegap*m_omegap*F2_omega/(m_omegap*m_omegap+Q2) + kappa_phi*gf_phi*m_phi*m_phi*F2_phi/(m_phi*m_phi+Q2) + (kappa_s - kappa_omega*gf_omega - kappa_omegap*gf_omegap - kappa_phi*gf_phi)*F2_D;

	if( sv == 0 ){
		if( i == 1 ){ return F_is_1;}
		if( i == 2 ){ return F_is_2;}
		return 0;
	}

	if( sv == 1 ){
		if( i == 1 ){ return F_iv_1;}
		if( i == 2 ){ return F_iv_2;}
		return 0;
	}

	return 0;
}

Double_t Lomon_GEn( Double_t *x, Double_t *p){
	Double_t Q2 = *x;
	Double_t tau = Q2/(4.0*0.938*0.938);

	Double_t F1n, F2n;

	F1n = (F_sv_i_Lomon(Q2, 0, 1) - F_sv_i_Lomon(Q2, 1, 1))/2.0;
	F2n = (F_sv_i_Lomon(Q2, 0, 2) - F_sv_i_Lomon(Q2, 1, 2))/2.0;

	return F1n - tau*F2n;
}


// Bijker and Iachello
// VMD Model
// Phys. Rev. C 69 (2004) 068201

Double_t F_sv_i_Bijker( Double_t Q2, Int_t sv, Int_t i ){
	Double_t F_is_1, F_is_2, F_iv_1, F_iv_2;

	Double_t beta_rho = 0.512;
	Double_t beta_omega = 1.129;
	Double_t beta_phi = -0.263;
	Double_t alpha_rho = 2.675;
	Double_t alpha_phi = -0.200;
	Double_t gamma = 0.515;

	Double_t mu_p = 2.793;
	Double_t mu_n = -1.913;

	Double_t m_omega = 0.783;
	Double_t m_phi = 1.019;
	Double_t m_rho = 0.776;

	Double_t g = pow( 1.0 + gamma*Q2, -2.0);

	F_is_1 = 0.5*g*( 1.0 - beta_omega - beta_phi + beta_omega*m_omega*m_omega/(m_omega*m_omega+Q2) + beta_phi*m_phi*m_phi/(m_phi*m_phi+Q2));
	F_iv_1 = 0.5*g*(1.0 - beta_rho + beta_rho*m_rho*m_rho/(m_rho*m_rho+Q2));

	F_is_2 = 0.5*g*( (mu_p+mu_n-1.0-alpha_phi)*m_omega*m_omega/(m_omega*m_omega+Q2) + alpha_phi*m_phi*m_phi/(m_phi*m_phi+Q2));

	F_iv_2 = 0.5*g*( (mu_p - mu_n - 1.0 - alpha_rho)/(1.0+gamma*Q2) + alpha_rho*m_rho*m_rho/(m_rho*m_rho+Q2) );


	if( sv == 0 ){
		if( i == 1 ){ return F_is_1;}
		if( i == 2 ){ return F_is_2;}
		return 0;
	}

	if( sv == 1 ){
		if( i == 1 ){ return F_iv_1;}
		if( i == 2 ){ return F_iv_2;}
		return 0;
	}

	return 0;

}

Double_t Bijker_GEn( Double_t *x, Double_t *p){
	Double_t Q2 = *x;
	Double_t tau = Q2/(4.0*0.938*0.938);

	Double_t F1n, F2n;

	F1n = F_sv_i_Bijker(Q2, 0, 1) - F_sv_i_Bijker(Q2, 1, 1);
	F2n = F_sv_i_Bijker(Q2, 0, 2) - F_sv_i_Bijker(Q2, 1, 2);

	return F1n - tau*F2n;
}


