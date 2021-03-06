#!/bin/sh

# vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
#
# get_ay0.sh
#
# This shell script plots the 3He(e,e'n) Ay0 asymmetry.
#
# Elena Long
# ellie@jlab.org
# 7/2/2013
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

echo "get_ay0.sh for Q2=1.0 GeV^2"

workPrefix="/work/halla/e05102/disk1/ellie"
ayhome="${workPrefix}/analysis-scripts/devel/auto_asym/q2_1_vert"

# Definitions for Q2=0.1 GeV^2:
#     Polarization         = 51.4 +/- 0.8 +/- 4.6%
#                                 +/- 4.7% (total)
#     N2 Dilution          = 94.7 +/- 0.8%
#     Proton Contamination = 72.3 +/- 1.8%

pol="0.514"
dpol="0.047"

dilN2="0.9721"
ddilN2="0.0120"

pCont="0.508"
dpCont="0.005"


#Old definitions I think are wrong (as of 10/5/18):
#pol="0.514"
#dpol="0.024"
#dilN2="0.9721"
#ddilN2="0.0120"
#pCont="0.9907"
#dpCont="0.000097"


cp $ayhome/../../../../analysis-scripts/devel/neutron_hunt/results/targ_ssa/with_vetos/vert_3he_q2_1_ssa_target_asymmetry_runs_20596-20789.txt $ayhome
cp $ayhome/../../../../analysis-scripts/devel/neutron_hunt/results/targ_ssa/with_vetos/vert_3he_q2_1_asym_v_runnum_for_runs_20596-20789.txt $ayhome
cp $ayhome/../ch-lt/q2_1_vert/q2_1_ch-lt.txt $ayhome
#cp $ayhome/../../../../results/q2_1_vert_3he/q2_1_vert_3he_run_info.txt $ayhome/q2_1_ch-lt.txt



sort -t ' ' -k1 vert_3he_q2_1_asym_v_runnum_for_runs_20596-20789.txt > temp_results.txt
sort -t ' ' -k1 q2_1_ch-lt.txt > temp_charge.txt
sort -t ' ' -k1 q2_1_prescales.txt > temp_prescales.txt
join -t ' ' temp_results.txt temp_charge.txt > temp_q2_1_near_final.txt
join -t ' ' temp_q2_1_near_final.txt temp_prescales.txt > temp_q2_1_final.txt

# temp_q2_1_final.txt
# Run#	Bin3Up	Bin3Dn	Tup	Tdn	BGLup	BGLdn	BGRup	BGRdn	RSup	RSdn	RBG	ChTot	HeT2tot	HeTrtot	ChTUp	HeT2up	HeTrgUp	ChTDn	HeT2dn	HeTrgDn	ChBUp	BT2Up	BTrgUp	ChBdn	BT2Dn	BTrgDn	t1Sc	t1cUp	t1c0	t1cDn	ugChUp	ugCh0	ugChDn	ugChUpI	ugChoI	ugChDnI	PS1	PS2	PS3	PS4	PS5	PS6	PS7	PS8
# $1	$2	$3	$4	$5	$6	$7	$8	$9	$10	$11	$12	$13	$14	$15	$16	$17	$18	$19	$20	$21	$22	$23	$24	$25	$26	$27	$28	$29	$30	$31	$32	$33	$34	$35	$36	$37	$38	$39	$40	$41	$42	$43	$44	$45

file0="temp_q2_1_final.txt"
awk '$1>20000 && $1<30000 && $1!=20596 && $1!=20597 && $1!=20599 && $1!=20654 && $1!=20701 && $1!=20707 && $1!=20726 && $1!=20742 && $1!=20744 && $1!=20789 && $29>0 && $31>0 && ($6+$8)>0 && $12>0 {print $1,$2,$3,$32*1.5577E-10,$34*1.5577E-10,$17*$38/$29,$20*$38/$31,sqrt((sqrt($4)^2)+((1/(sqrt($6+$8)))*($10/$12))^2),sqrt((sqrt($5)^2)+((1/(sqrt($7+$9)))*($11/$12))^2) }' $file0 > temp_q2_1_evt_ch_lt.txt
# Run #	EvtUp	EvtDwn	ChUp	ChDwn	LtUp	LtDwn	dSup	dSdown
# $1	$2	$3	$4	$5	$6	$7	$8	$9


file1="./temp_q2_1_evt_ch_lt.txt"
awk '$1>20000 && $1<30000 && $4*$6>0 && $5*$7>0 && ($2+$3)>0 {print $1,$2/($4*$6),$3/($5*$7),1/sqrt($2+$3),$8/($4*$6),$9/($5*$7)}' $file1 > temp_q2_1_yields.txt
#							Run #	YieldUp		YieldDwn	1/sqrt(N)	dYup	dYdown
#							$1		$2				$3			$4				$5		$6


file2="./temp_q2_1_yields.txt"
#awk '$1>20000 && $1<30000 && ($2+$3)>0 {print $1,($2-$3)/($2+$3),$4}' $file2 > temp_q2_1_asym.txt
#awk '$1>20000 && $1<30000 && ($2+$3)>0 {print $1,($2-$3)/($2+$3),(2/((($2/$3)+1)^2))*($2/$3)*sqrt(($5/$2)^2+($6/$3)^2)}' $file2 > final_q2_1_asym_runnum.txt
#							Run #	Ay0		dAy0
#							$1		$2		$3

awk '$1>20000 && $1<30000 && ($2+$3)>0 {print $1,(($2-$3)/($2+$3))*(1/('$pol'*'$dilN2'*'$pCont')),(1/('$pol'*'$dilN2'*'$pCont'))*(2/((($2/$3)+1)^2))*($2/$3)*sqrt(($5/$2)^2+($6/$3)^2)}' $file2 > temp_final_q2_1_asym_runnum.txt

file9="./temp_final_q2_1_asym_runnum.txt"
awk '$1>20000 && $1<30000 {print $1,$2,sqrt(($2*'$ddilN2'/'$dilN2')^2 + ($2*'$dpCont'/'$pCont')^2 + ($2*'$dpol'/'$pol')^2 + $3^2)}' $file9 > final_q2_1_asym_runnum.txt
#awk '$1>20000 && $1<30000 {print $1,$2,3.08822*sqrt(($2*'$ddilN2'/'$dilN2')^2 + ($2*'$dpCont'/'$pCont')^2 + ($2*'$dpol'/'$pol')^2 + $3^2)}' $file9 > final_q2_1_asym_runnum.txt
#                           Run #   Ay0     dAy0
#                           $1      $2      $3



file7="./final_q2_1_asym_runnum.txt"
awk '{print 1}' $file7 > temp_dof2.txt
sed "s/e+0/*10^/g" temp_dof2.txt > temp_dof.txt
awk '{print 1/($3*$3)}' $file7 > temp_wi2.txt
sed "s/e+0/*10^/g" temp_wi2.txt > temp_wi.txt
awk '{print $2/($3*$3)}' $file7 > temp_wi_ay02.txt
sed "s/e+0/*10^/g" temp_wi_ay02.txt > temp_wi_ay0.txt

dof_temp="$(paste -sd+ temp_dof.txt | bc)"
sumWi="$(paste -sd+ temp_wi.txt | bc)"
sumWiAy0="$(paste -sd+ temp_wi_ay0.txt | bc)"
aveAy0=`awk 'BEGIN{printf("%0.5f", '$sumWiAy0' / '$sumWi')}'`
aveAy0err=`awk 'BEGIN{printf("%0.5f", 1/sqrt('$sumWi'))}'`
dof=`awk 'BEGIN{printf("%0.5f", '$dof_temp'-1)}'`

echo 0 $aveAy0 > temp_ave_ay0.txt
echo 30000 $aveAy0 >> temp_ave_ay0.txt

awk '{print 1/($3*$3)*('$aveAy0'-$2)*('$aveAy0'-$2)}' $file7 > temp_chi2i2.txt
sed "s/e-0/*10^-/g" temp_chi2i2.txt > temp_chi2i.txt
chi2="$(paste -sd+ temp_chi2i.txt | bc)"

echo "1" > temp_temptemp.txt

file8="./temp_temptemp.txt"
awk '{print '$chi2','$dof'}' $file8 > chi2_dof_ay0.txt

chi2ovrdof=`awk 'BEGIN{printf("%0.5f", '$chi2' / '$dof')}'`
calcS=`awk 'BEGIN{printf("%0.5f", sqrt('$chi2ovrdof'))}'`
S=1
echo "For 3He(e,e') Ay per run #, chi2=" $chi2 ", dof=" $dof ", chi2/dof=" $chi2ovrdof ", calcS=" $calcS ", S=" $S
echo "aveAy0		Err"
echo $aveAy0"  "$aveAy0err



#xmgrace\
gracebat -hdevice PNG -printfile plot_q2_1_ay0.png \
		 -settype xydy		-block final_q2_1_asym_runnum.txt		-graph 0 -bxy 1:2:3 \
		 -settype xydy		-block temp_final_q2_1_asym_runnum.txt	-graph 0 -bxy 1:2:3 \
		 -settype xy		-block temp_ave_ay0.txt					-graph 0 -bxy 1:2 \
		 -p q2_1_asym.par	-noask

display plot_q2_1_ay0.png



file6="./vert_3he_q2_1_ssa_target_asymmetry_runs_20596-20789.txt"
awk '$1>0.01 && $1<3 {print $1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12}' $file6 > temp_q2_1_nu.txt
#sort -t ' ' -k1 temp_q2_1_nu1.txt > temp_q2_1_nu.txt
# NuBin Up[3] Dn[3] Tup Tdn BGLup BGLdn BGRup BGRdn RSup RSdn RBG
# 1     2     3     4   5   6     7     8     9     10   11   12


#sort -t ' ' -k1 q2_1_ch-lt.txt > temp_charge_nu.txt
awk '$1>0 && $1!=20596 && $1!=20597 && $1!=20599 && $1!=20648 && $1!=20654 && $1!=20701 && $1!=20707 && $1!=20726 && $1!=20742 && $1!=20744 && $1<20789  {print $21}' q2_1_ch-lt.txt > temp_charge_up.txt
sed "s/e+0/*10^/g" temp_charge_up.txt > temp_charge_up2.txt
totChUp="$(paste -sd+ temp_charge_up2.txt | bc)"

awk '$1>0 && $1!=20596 && $1!=20597 && $1!=20599 && $1!=20648 && $1!=20654 && $1!=20701 && $1!=20707 && $1!=20726 && $1!=20742 && $1!=20744 && $1<20789  {print $23}' q2_1_ch-lt.txt > temp_charge_down.txt
sed "s/e+0/*10^/g" temp_charge_down.txt > temp_charge_down2.txt
totChDn="$(paste -sd+ temp_charge_down2.txt | bc)"

awk '$1>0 && $1!=20596 && $1!=20597 && $1!=20599 && $1!=20648 && $1!=20654 && $1!=20701 && $1!=20707 && $1!=20726 && $1!=20742 && $1!=20744 && $1<20789  {print $6}' q2_1_ch-lt.txt > temp_t2_up.txt
sed "s/e+0/*10^/g" temp_t2_up.txt > temp_t2_up2.txt
totT2Up="$(paste -sd+ temp_t2_up2.txt | bc)"

awk '$1>0 && $1!=20596 && $1!=20597 && $1!=20599 && $1!=20648 && $1!=20654 && $1!=20701 && $1!=20707 && $1!=20726 && $1!=20742 && $1!=20744 && $1<20789  {print $9}' q2_1_ch-lt.txt > temp_t2_down.txt
sed "s/e+0/*10^/g" temp_t2_down.txt > temp_t2_down2.txt
totT2Dn="$(paste -sd+ temp_t2_down2.txt | bc)"

awk '$1>0 && $1!=20596 && $1!=20597 && $1!=20599 && $1!=20648 && $1!=20654 && $1!=20701 && $1!=20707 && $1!=20726 && $1!=20742 && $1!=20744 && $1<20789  {print $18}' q2_1_ch-lt.txt > temp_t1c_up.txt
sed "s/e+0/*10^/g" temp_t1c_up.txt > temp_t1c_up2.txt
totScUp="$(paste -sd+ temp_t1c_up2.txt | bc)"

awk '$1>0 && $1!=20596 && $1!=20597 && $1!=20599 && $1!=20648 && $1!=20654 && $1!=20701 && $1!=20707 && $1!=20726 && $1!=20742 && $1!=20744 && $1<20789  {print $20}' q2_1_ch-lt.txt > temp_t1c_down.txt
sed "s/e+0/*10^/g" temp_t1c_down.txt > temp_t1c_down2.txt
totScDn="$(paste -sd+ temp_t1c_down2.txt | bc)"

totLtUp=`awk 'BEGIN{printf("%0.5f", '$totT2Up' / '$totScUp')}'`
totLtDn=`awk 'BEGIN{printf("%0.5f", '$totT2Dn' / '$totScDn')}'`

#echo $totChUp
#echo $totChDn
#echo $totT2Up
#echo $totT2Dn
#echo $totScUp
#echo $totScDn
#echo $totLtUp
#echo $totLtDn

file3="temp_q2_1_nu.txt"
awk '$1>0.010 && $1<3 && $2>0 && $3>0 && ($6+$8)>0 && $12>0 {print $1,$2,$3,'$totChUp','$totChDn','$totLtUp','$totLtDn',sqrt((sqrt($4)^2)+((1/(sqrt($6+$8)))*($10/$12))^2),sqrt((sqrt($5)^2)+((1/(sqrt($7+$9)))*($11/$12))^2) }' $file3 > temp_q2_1_evt_nu_ch_lt.txt
#                           NuBin   EvtUp   EvtDwn  ChUp    ChDwn   LtUp    LtDwn   dSup    dSdown
#                           $1      $2      $3      $4      $5      $6      $7      $8      $9

file4="./temp_q2_1_evt_nu_ch_lt.txt"
awk '$1>0.010 && $1<3 && $4*$6>0 && $5*$7>0 && ($2+$3)>0 {print $1,$2/($4*$6),$3/($5*$7),1/sqrt($2+$3),$8/($4*$6),$9/($5*$7)}' $file4 > temp_q2_1_nu_yields.txt
#                           Run #   YieldUp     YieldDwn    1/sqrt(N)   dYup    dYdown
#                           $1      $2          $3          $4          $5      $6

file5="./temp_q2_1_nu_yields.txt"
#awk '$1>0.010 && $1<3 && ($2+$3)>0 {print $1,($2-$3)/($2+$3),(2/((($2/$3)+1)^2))*($2/$3)*sqrt(($5/$2)^2+($6/$3)^2)}' $file5 > final_q2_1_nu_asym.txt
#                           Run #   Ay0     dAy0
#                           $1      $2      $3
echo "S = "$S
awk '$1>0.010 && $1<3 && ($2+$3)>0 {print $1,(($2-$3)/($2+$3))*(1/('$pol'*'$dilN2'*'$pCont')),'$S'*(1/('$pol'*'$dilN2'*'$pCont'))*(2/((($2/$3)+1)^2))*($2/$3)*sqrt(($5/$2)^2+($6/$3)^2)}' $file5 > final_q2_1_nu_asym_stat.txt

file10="./final_q2_1_nu_asym_stat.txt"
awk '$1>0.010 && $1<3 {print $1,$2,$3,sqrt(($2*'$ddilN2'/'$dilN2')^2 + ($2*'$dpCont'/'$pCont')^2 + ($2*'$dpol'/'$pol')^2)}' $file10 > temp_q2_1_nu_asym_all.txt
file11="./temp_q2_1_nu_asym_all.txt"

echo "nu                  Ay0      e_s       e_N         e_p         e_t       e_n" > final_q2_1_nu_asym_all_errs.txt
#awk '$1>0.010 && $1<3 {print $1,$2,$3,$2*'$ddilN2'/'$dilN2',$2*'$dpCont'/'$pCont',$2*'$dpol'/'$pol',sqrt(('$S'^2-1)*(($2*'$ddilN2'/'$dilN2')^2 + ($2*'$dpCont'/'$pCont')^2 + ($2*'$dpol'/'$pol')^2 + $3^2))}' $file11 >> final_q2_1_nu_asym_all_errs.txt
awk '$1>0.010 && $1<3 {print $1,$2,$3,$2*'$ddilN2'/'$dilN2',$2*'$dpCont'/'$pCont',$2*'$dpol'/'$pol',0}' $file11 >> final_q2_1_nu_asym_all_errs.txt

file12="./final_q2_1_nu_asym_all_errs.txt"
awk '$1>0.010 && $1<3 {print $1,$2,$3,sqrt($4^2 + $5^2 + $6^2 + $7^2)}' $file12 > final_q2_1_nu_asym_stat_sys.txt
awk '$1>0.010 && $1<3 {print $1,$2,sqrt($3^2 + $4^2 + $5^2 + $6^2 + $7^2)}' $file12 > final_q2_1_nu_asym_tot.txt
#                           Run #   Ay0     dAy0
#                           $1      $2      $3

cat $ayhome/final_q2_1_nu_asym_all_errs.txt


#xmgrace\
gracebat -hdevice PNG -printfile plot_q2_1_nu_ay0.png \
         -settype xydy  -block final_q2_1_nu_asym_stat.txt  -graph 0 -bxy 1:2:3 \
         -settype xydy  -block final_q2_1_nu_asym_tot.txt  -graph 0 -bxy 1:2:3 \
         -p q2_1_nu_asym.par   -noask

display plot_q2_1_nu_ay0.png





rm temp*







