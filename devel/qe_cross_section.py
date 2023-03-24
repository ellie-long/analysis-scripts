import math
import numpy as np

# Gets the q vector
# outType=0 gives magnitude of q
# outType=1 gives theta_q
# outType=2 gives phi_q


def get_q_vec(E, Eprime, theta_e, phi_e, outType):
    qvec = math.sqrt((Eprime**2)*(math.sin(theta_e)**2*math.cos(phi_e)**2 + math.sin(phi_e)**2 + (E/Eprime - math.cos(theta_e)*math.cos(phi_e))**2))

    qx = -Eprime*math.sin(theta_e)*math.cos(phi_e)
    qy = -Eprime*math.sin(phi_e)
    qz = (E-Eprime*math.cos(theta_e)*math.cos(phi_e))
    theta_q = math.atan(qx/qz)
    phi_q = math.asin(qy/qvec)

    if (outType == 0): return qvec
    if (outType == 1): return theta_q
    if (outType == 2): return phi_q

    return qvec


# Gets the k' vector of the outgoing nucleon
# outType=0 gives magnitude of k'
# outType=1 gives theta_k'
# outType=2 gives phi_k'
def get_kp_vec(E, Eprime, theta_e, phi_e, kx, ky, kz, kp):
    kp = [0, 0, 0]
    kpvec = math.sqrt((kx-Eprime*math.sin(theta_e)*math.cos(phi_e))**2 + (ky-Eprime*math.sin(phi_e))**2 + (kz+E-Eprime*math.cos(theta_e)*math.cos(phi_e))**2)

    kpx = kx-Eprime*math.sin(theta_e)*math.cos(phi_e)
    kpy = ky-Eprime*math.sin(phi_e)
    kpz = kz+E-Eprime*math.cos(theta_e)*math.cos(phi_e)
    theta_kp = math.atan(kpx/kpz)
    phi_kp = math.asin(kpy/kpvec)

    kp[0] = kpvec
    kp[1] = theta_kp
    kp[2] = phi_kp

    return kp



def roundn(num, n):
    result = math.floor(num * (10**n) + 0.5) / (10**n)
    return result

def qe_cross_section():
    global q2
    mup = 2.7928
    mun = -1.9130
    print("Beam energy E in GeV?")
    E = float(input())
    print("Scattered beam energy E' in GeV?")
    Eprime = float(input())
    print("Angle of scattered electron (in degrees)?")
    theta_deg = float(input())
    
    
    # Proton mass
    mass = 0.938272
    # Binding energy
    bindE = 0.002572681 # GeV for 3He
    
    pi = 3.141592653589793238462643383279502884197169399375105820974
    
 	# Hall A Website
 	# dTh = +/- 60 mrad = +/- 3.438 deg
 	# -------------------------------------
 	# ExtTgtCor_R.th 
 	# --> Note, th:ph_tgt are reversed. 
 	# dth_tgt = dphi_e & dphi_tgt=dth_e
 	# dTh = +/- 55 mrad = +/- 3.151 deg
 	# -------------------------------------
 	# R.tr.th
 	# dTh = +/- 65 mrad = +/- 3.724 deg
    dth_deg = 1.432 # deg
    
    # Hall A Website
    # dPh = +/- 28 mrad = +/- 1.604 deg
	# -------------------------------------
	# ExtTgtCor_R.ph
	# --> Note, th:ph_tgt are reversed. 
	# dth_tgt = dphi_e & dphi_tgt=dth_e
	# dPh = +/- 25 mrad = +/- 1.432 deg
	# -------------------------------------
	# R.tr.ph
	# dPh = +/- 40 mrad = +/- 2.292 deg
    dph_deg = 3.151 # deg
    
    phi_deg = 0
    
    phi = phi_deg * pi/180
    theta = theta_deg * pi/180
    dph = dph_deg * pi/180
    dth = dth_deg * pi/180
    dph_mrad = roundn(dph*1000,1)
    dth_mrad = roundn(dth*1000,1)
    
    theta_dth_up   = (theta_deg + dth_deg) * pi/180
    theta_dth_down = (theta_deg - dth_deg) * pi/180
    phi_dph_up     = (phi_deg + dph_deg) * pi/180
    phi_dph_down   = (phi_deg - dph_deg) * pi/180
    
    q2 = 4*E*Eprime*(math.sin(theta/2)**2)
    tau = q2/(4*mass*mass)
    nu = E - Eprime
    x = q2/(2*mass*nu)
    qvec = get_q_vec(E,Eprime,theta,phi,0)

    if ((q2<0) or (E<0)):
        print("Uh-oh! Something went wrong...")
        return
    
    GD = 1/((1+q2/(0.71))*(1+q2/(0.71)))

    qvec_dth_up   = get_q_vec(E,Eprime,theta_dth_up,phi,0)
    qvec_dth_down = get_q_vec(E,Eprime,theta_dth_down,phi,0)
    qvec_dph_up   = get_q_vec(E,Eprime,theta,phi_dph_up,0)
    qvec_dph_down = get_q_vec(E,Eprime,theta,phi_dph_down,0)

    theta_q = get_q_vec(E,Eprime,theta,phi,1)
    phi_q   = get_q_vec(E,Eprime,theta,phi,2)

    theta_q_up   = get_q_vec(E,Eprime,theta_dth_up,phi,1)
    theta_q_down = get_q_vec(E,Eprime,theta_dth_down,phi,1)

    phi_q_dph_up   = get_q_vec(E,Eprime,theta,phi_dph_up,2)
    phi_q_dph_down = get_q_vec(E,Eprime,theta,phi_dph_down,2)


    GEn = -(1.70*tau*GD)/(1+(3.30*tau))

    a1 = -0.24
    b1 = 10.98
    b2 = 12.82
    b3 = 21.97
    GEp = (1+(a1*tau))/(1+(b1*tau)+(b2*tau*tau)+(b3*tau*tau*tau))

    a1 = 0.12
    b1 = 10.97
    b2 = 18.86
    b3 = 6.55
    GMp = mup*((1+(a1*tau))/(1+(b1*tau)+(b2*tau*tau)+(b3*tau*tau*tau)))

    a1 = 2.33
    b1 = 14.72
    b2 = 24.20
    b3 = 84.1
    GMn = mun*((1+(a1*tau))/(1+(b1*tau)+(b2*tau*tau)+(b3*tau*tau*tau)))


    # print('tau = ',tau)


    # Nucleon initial momentum (kf=250 MeV)
    P=0;
    # P=0.250;
    # S= Binding Energy + P^2/(2M)
    S=bindE+P*P/(2*mass);
    # Calculate momentum of knocked-out nucleon
    Pprime1=np.sqrt(2*mass*nu+P*P+2*mass*S);
    # P=0.250 # GeV/c
    P=0.120 # GeV/c
    S=bindE+P*P/(2*mass)
    Pprime2=np.sqrt(2*mass*nu+P*P+2*mass*S)
    PprimeAve=(Pprime2 - Pprime1)/2 + Pprime1
    PprimePM=(Pprime2 - Pprime1)/2



    dtheta_q_up = theta_q - theta_q_up
    dtheta_q_down = theta_q_down - theta_q
    dphi_q = phi_q_dph_down - phi_q

    # print('theta_q = ',theta_q)
    # print('dtheta_q_up = ',dtheta_q_up)
    # print('dtheta_q_down = ',dtheta_q_down)
    # print('theta_q_down = ',theta_q_down)
    # print('phi_q = ',phi_q)
    # print('dphi_q = ',dphi_q)
    # print('phi_q_dph_down = ',phi_q_dph_down)

    if (q2>0.1 and q2<0.2):
        # hand_r	= 4	# m
        hand_r		= 6	# m
        # hand_r	= 8	# m
        hand_a		= 1*3 # m^2
        theta_n_deg	= 71 # deg
    elif (q2>0.4 and q2<0.6):
        hand_r		= 6	# m
        hand_a		= 1*3	# m^2
        theta_n_deg	= 62.5	# deg
    elif (q2>0.9 and q2<1.1):
        hand_r		= 8	# m
        hand_a		= 1*3 # m^2
        theta_n_deg	= 54 # deg
    else:
        print("!!!!!!!!!WARNING!!!!!!!!")
        print("HAND data not available!")
        print("!!!!!!!!!WARNING!!!!!!!!")
        hand_r		= 0
        hand_a		= 0
        theta_n_deg	= 0

    theta_n = theta_n_deg * math.pi/180

    
    kf = 0.120 # GeV/c for 3He
    k = math.sqrt(3.0/5.0) * kf
    S = bindE + k*k/(2*mass)
    kprime = math.sqrt(2*mass*nu + k*k + 2*mass*S)
    kp = [0, 0, 0]
    kx = 0
    ky = 0
    kz = 0
    thisTheta = 0
    thisPhi = 0
    thisTheta_q = 0
    kp_vec = get_kp_vec(E, Eprime, theta, phi, 0, 0, 0, kp)
    kpvec = [0, 0, 0]
    for i in range(3):
        kpvec[i] = kp_vec[i]

    kx = k * math.sin(theta_q)
    ky = 0
    kz = k * math.cos(theta_q)
    kp_vec = get_kp_vec(E, Eprime, theta, phi, kx, ky, kz, kp)
    kpvec_max = [0, 0, 0]
    for i in range(3):
        kpvec_max[i] = kp_vec[i]

    kp_vec = get_kp_vec(E, Eprime, theta, phi, -kx, 0, -kz, kp)
    kpvec_min = [0, 0, 0]
    for i in range(3):
        kpvec_min[i] = kp_vec[i]

    thisTheta = theta_dth_down
    thisTheta_q = get_q_vec(E, Eprime, theta, phi, 2)
    kx = k * math.sin(thisTheta_q + math.pi/2)
    ky = 0
    kz = k * math.cos(thisTheta_q + math.pi/2)
    kp_vec = get_kp_vec(E, Eprime, thisTheta, phi, kx, ky, kz, kp)
    kpvec_perp_max = [0, 0, 0]
    for i in range(3):
        kpvec_perp_max[i] = kp_vec[i]

    thisTheta = theta_dth_up
    thisTheta_q = get_q_vec(E, Eprime, theta, phi, 2)
    kx = k * math.sin(thisTheta_q - math.pi/2)
    ky = 0
    kz = k * math.cos(thisTheta_q - math.pi/2)
    kp_vec = get_kp_vec(E, Eprime, thisTheta, phi, kx, ky, kz, kp)
    kpvec_perp_min = [0, 0, 0]
    for i in range(3):
        kpvec_perp_min[i] = kp_vec[i]

    thisPhi = phi_dph_down
    kx = 0
    ky = k
    kz = 0
    kp_vec = get_kp_vec(E, Eprime, theta, thisPhi, kx, ky, kz, kp)
    kpvec_vert_max = [0, 0, 0]
    for i in range(3):
        kpvec_vert_max[i] = kp_vec[i]


    thisPhi = phi_dph_up
    kx = 0
    ky = -k
    kz = 0
    kp_vec = get_kp_vec(E, Eprime, theta, thisPhi, kx, ky, kz, kp)
    kpvec_vert_min = [0, 0, 0]
    for i in range(3):
        kpvec_vert_min[i] = kp_vec[i]


	# Oval area of neutrons or protons aimed towards HAND
    # r = length of side of rectangle
    n_r1 = hand_r * (math.tan(kpvec_perp_max[1]-kpvec[1]) + math.tan(kpvec[1]-kpvec_perp_min[1]))
    p_r1 = hand_r * (math.tan(dtheta_q_up) + math.tan(dtheta_q_down))
    n_r2 = hand_r * (math.tan(kpvec_vert_max[2]-kpvec[2]) + math.tan(kpvec[2]-kpvec_vert_min[2]))
    p_r2 = 2 * hand_r * math.tan(dphi_q)
    n_area = n_r1 * n_r2  # m^2
    p_area = p_r1 * p_r2  # m^2
    
    # print('[n_r1,n_r2]=',n_r1,n_r2)
    # print('hand_r=',hand_r)
    # Ratio of HAND area : Neutron area
    if (hand_r>0):
        hand_ovr_n = hand_a / n_area
        hand_ovr_p = hand_a / p_area
    else:
        hand_ovr_n = 0
        hand_ovr_p = 0
    
    # -------------------------------------------------------------------------------------------------
    
    # Converts all angles back to degrees
    # !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    # DO NOT DO ANY MATH AFTER THIS POINT
    # !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    theta_q = theta_q * 180 / math.pi
    theta_q_up = theta_q_up * 180 / math.pi
    theta_q_down = theta_q_down * 180 / math.pi
    phi_q_dph_up = phi_q_dph_up * 180 / math.pi
    phi_q_dph_down = phi_q_dph_down * 180 / math.pi
    dtheta_q_up = dtheta_q_up * 180 / math.pi
    dtheta_q_down = dtheta_q_down * 180 / math.pi
    dphi_q = dphi_q * 180 / math.pi

    print("\n\n\n")
    print("---------------------------------------------------------------------")
    print("---------------------------------------------------------------------")
    print("Input:")
    print(f"\tE\t= {E} GeV")
    print(f"\tE'\t= {Eprime} GeV")
    print(f"\ttheta_e\t= {theta_deg} +/- {dth_deg} deg (or +/- {dth_mrad} mrad)")
    print(f"\tphi_e\t= {phi_deg} +/- {dph_deg} deg (or +/- {dph_mrad} mrad)")
    print("- - - - - - - - - - - - - - - -")
    print("Scattered nucleon initial momentum:")
    print(f"\tk_f\t= {kf} GeV/c")
    print(f"\t|k|\t= {k} GeV/c")
    print("---------------------------------------------------------------------")
    print("---------------------------------------------------------------------")
    print("\n\n")
    print("---------------------------------------------------------------------")
    print("---------------------------------------------------------------------")
    print("Output:")
    print(f"\tQ^2\t= {q2} (GeV/c)^2")
    print(f"\tnu\t= {nu} GeV")
    print(f"\tx\t= {x}")
    print(f"\t|q|\t= {qvec} + {qvec_dth_down-qvec} - {qvec-qvec_dth_up} GeV/c")
    print(f"\ttheta_q\t= {theta_q} + {dtheta_q_up} - {dtheta_q_down} deg")
    print(f"\tphi_q\t= {phi_q} +/- {dphi_q} deg")
    print("---------------------------------------------------------------------")
    print("Scattered nucleon:")
    
    # print(" Along q-vector (kˆ = +qˆ):")
    # print(" (+ Longitudinal)")
    # print(f" |k'| = {kpvec_max[0]} GeV/c")
    # print(f" theta_k' = {(kpvec_max[1]*180/np.pi)} deg")
    # print(f" phi_k' = {(kpvec_max[2]*180/np.pi)} deg")
    # print(" - - - - - - - - - - - - - - - - - - - - - - -")
    # print(" Against q-vector (kˆ = -qˆ):")
    # print(" (- Longitudinal)")
    # print(f" |k'| = {kpvec_min[0]} GeV/c")
    # print(f" theta_k' = {(kpvec_min[1]*180/np.pi)} deg")
    # print(f" phi_k' = {(kpvec_min[2]*180/np.pi)} deg")
    # print(" - - - - - - - - - - - - - - - - - - - - - - -")
    # print(" Perpendicular to q-vector, Parallel to Scattering Plane (kˆ _|_ qˆ):")
    # print(" (+ Transverse, using theta_e - dtheta_e)")
    # print(f" |k'| = {kpvec_perp_max[0]} GeV/c")
    # print(f" theta_k' = {(kpvec_perp_max[1]*180/np.pi)} deg")
    # print(f" phi_k' = {(kpvec_perp_max[2]*180/np.pi)} deg")
    # print(" - - - - - - - - - - - - - - - - - - - - - - -")
    # print(" Perpendicular to neg. q-vector, Parallel to Scattering Plane (kˆ _|_ -qˆ):")
    # print(" (- Transverse, using theta_e + dtheta_e)")
    # print(f" |k'| = {kpvec_perp_min[0]} GeV/c")
    # print(f" theta_k' = {(kpvec_perp_min[1]*180/np.pi)} deg")
    # print(f" phi_k' = {(kpvec_perp_min[2]*180/np.pi)} deg")
    # print(" - - - - - - - - - - - - - - - - - - - - - - -")
    # print(" Perpendicular to q-vector, Perpendicular to Scattering Plane (kˆ _|_ qˆ):")
    # print(" (+ Vertical, using phi_e - dphi_e)")
    # print(f" |k'| = {kpvec_vert_max[0]} GeV/c")
    # print(f" theta_k' = {(kpvec_vert_max[1]*180/np.pi)} deg")
    # print(f" phi_k' = {(kpvec_vert_max[2]*180/np.pi)} deg")
    # print(" - - - - - - - - - - - - - - - - - - - - - - -")
    # print(" Perpendicular to neg. q-vector, Perpendicular to Scattering Plane (kˆ _|_ -qˆ):")
    # print(" (- Vertical, using phi_e + dphi_e)")
    # print(f" |k'| = {kpvec_vert_min[0]} GeV/c")
    # print(f" theta_k' = {(kpvec_vert_min[1]*180/np.pi)} deg")
    # print(f" phi_k' = {(kpvec_perp_max[2]*180/np.pi)} deg")
    # print(" - - - - - - - - - - - - - - - - - - - - - - -")
	# print("	Summary:")
    
    print(" |k'| = ", (kpvec_max[0]+kpvec_min[0])/2, " + ", kpvec_perp_max[0]-((kpvec_max[0]+kpvec_min[0])/2), " - ", ((kpvec_max[0]+kpvec_min[0])/2)-kpvec_perp_min[0], " GeV/c")
    print(" theta_k' = ", (kpvec[1]*180/pi), " + ", (kpvec_perp_max[1]-kpvec[1])*180/pi, " - ", (kpvec[1]-kpvec_perp_min[1])*180/pi, " deg")
    print(" phi_k' = ", (kpvec[2]*180/pi), " +/- ", (kpvec_vert_max[2]-kpvec[2])*180/pi, " deg")
    # print("Scattered Area for Elastic Protons from 1H:")
    # print(" phi_k' = ", (kpvec_vert_min[2]*180/pi), " deg")
    print("---------------------------------------------------------------------")
    print("HAND Information:")
    print(" HAND r = ", hand_r, " m")
    print(" HAND theta = ", theta_n_deg, " deg")
    print(" HAND area = ", hand_a, " m^2")
    print("- - - - - - - - - - - - - - - - - - - - - - - - - - - -")
    print("Scattered Area for QE Nucleons from 3He:")
    print(" Nucleon l1 (from dTh_k) = ", n_r1, " m")
    print(" Nucleon l2 (from dPh_k) = ", n_r2, " m")
    print(" Area of nucleons (l1*l2) at ", hand_r, " m = ", n_area, " m^2")
    print(" HAND area/Nucleon area = ", hand_ovr_n)
    print("- - - - - - - - - - - - - - - - - - - - - - - - - - - -")
    print("Scattered Area for Elastic Protons from 1H:")
    print(" Proton l1 (from dTh_k) = ", p_r1, " m")
    print(" Proton l2 (from dPh_k) = ", p_r2, " m")
    print(" Area of protons (l1*l2) at ", hand_r, " m = ", p_area, " m^2")
    print(" HAND area/Proton area = ", hand_ovr_p)
    print("- - - - - - - - - - - - - - - - - - - - - - - - - - - -")
    if (hand_r>0):
        print("Ratio of rough 3He knocked-out nucleon:1H acceptance based on areas above:")
        print(" A_n/A_p = ", hand_ovr_n/hand_ovr_p)
    print("---------------------------------------------------------------------")
    print("---------------------------------------------------------------------")
    # print("Nucleon (along q-vector):")
    # print("Initial momentum = " + str(0) + " GeV/c")
    # print("Final momentum = " + str(Pprime1) + " GeV/c")
    # print("- - - - - - - - - - - - - - - -")
    # print("Initial momentum = " + str(P) + " GeV/c")
    # print("Final momentum = " + str(Pprime2) + " GeV/c")
    # print("- - - - - - - - - - - - - - - -")
    # print("Final momentum ave = " + str(PprimeAve))
    # print("Final momentum +/- = " + str(PprimePM))

    print("---------------------------------------------------------------------")
    print("According to the JJ Kelly fit, ")
    print("GEn = " + str(GEn))
    print("GMn = " + str(GMn))
    print("GMn/(-1.91) = " + str(GMn/(-1.91)))
    print("GEp = " + str(GEp))
    print("GMp = " + str(GMp))
    print("GMp/2.79 = " + str(GMp/2.79))
    print(" - - - - - - - - - - - - - - - ")
    print("GEp/G_D = " + str(GEp/GD))
    print("GEn/G_D = " + str(GEn/GD))
    print("GMp/(mu_pG_D) = " + str(GMp/(mup*GD)))
    print("GMn/(mu_nG_D) = " + str(GMn/(mun*GD)))
    print("---------------------------------------------------------------------")
    print("---------------------------------------------------------------------")


    # crosssection = (4*(1/137)*(1/137)*3.8937e-32)*Eprime*Eprime*(cos(theta/2)*cos(theta/2))*(1/(q2*q2))*(Eprime/E)*(((GE*GE + tau*GM*GM)/(1+tau)) + 2*tau*GM*GM*(tan(theta/2)*tan(theta/2)))
    # crosssection = (4*(1/137)*(1/137)*3.8937)*Eprime*Eprime*(cos(theta/2)*cos(theta/2))*(1/(q2*q2))*(Eprime/E)*(((GE*GE + tau*GM*GM)/(1+tau)) + 2*tau*GM*GM*(tan(theta/2)*tan(theta/2)))
    # firstterm = (4*(7.29735257e-3)*(7.29735257e-3)*3.8937e-32)*Eprime*Eprime*(cos(theta/2)*cos(theta/2))*(1/(q2*q2))
    # secondterm = (Eprime/E)
    # thirdterm = (((GE*GE + tau*GM*GM)/(1+tau)) + 2*tau*GM*GM*(tan(theta/2)*tan(theta/2)))


    protoncs = ((4*(7.29735257e-3)*(7.29735257e-3)*3.8937e-32)*Eprime*Eprime*(math.cos(theta/2)*math.cos(theta/2))*(1/(q2*q2)))*(Eprime/E)*(((GEp*GEp + tau*GMp*GMp)/(1+tau)) + 2*tau*GMp*GMp*(math.tan(theta/2)*math.tan(theta/2)))
    neutroncs = ((4*(7.29735257e-3)*(7.29735257e-3)*3.8937e-32)*Eprime*Eprime*(math.cos(theta/2)*math.cos(theta/2))*(1/(q2*q2)))*(Eprime/E)*(((GEn*GEn + tau*GMn*GMn)/(1+tau)) + 2*tau*GMn*GMn*(math.tan(theta/2)*math.tan(theta/2)))
    
    print("Assuming free nucleons, we find:")
    print("(dsigma/dOmega)_p = ", protoncs, " m^2 = ", protoncs*1e31, " mb")
    print("(dsigma/dOmega)_n = ", neutroncs, " m^2 = ", neutroncs*1e31, " mb")
    print(" - - - - - - - - - - - - - - - ")
    print("If we take these to find the ratio of protons:neutrons in 3He, we find:")
    print("  (using 2*(dsigma/dOmega)_p/(dsigma/dOmega)_n )")
    print("P:N = ", (2*protoncs/neutroncs), ":1")






qe_cross_section()




