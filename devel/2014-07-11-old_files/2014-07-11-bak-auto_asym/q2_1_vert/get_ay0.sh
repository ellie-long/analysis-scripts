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

sort -t ' ' -k1 vert_3he_q2_1_asym_v_runnum_for_runs_20596-20789.txt > temp_results.txt
sort -t ' ' -k1 q2_1_ch-lt.txt > temp_charge.txt
sort -t ' ' -k1 q2_1_prescales.txt > temp_prescales.txt
join -t ' ' temp_results.txt temp_charge.txt > temp_q2_1_near_final.txt
join -t ' ' temp_q2_1_near_final.txt temp_prescales.txt > temp_q2_1_final.txt


file0="temp_q2_1_final.txt"
awk '$1>20000 && $1<30000 && $29>0 && $31>0 && ($6+$8)>0 && $12>0 {print $1,$2,$3,$32*1.5577E-10,$34*1.5577E-10,$17*$38/$29,$20*$38/$31,sqrt((sqrt($4)^2)+((1/(sqrt($6+$8)))*($10/$12))^2),sqrt((sqrt($5)^2)+((1/(sqrt($7+$9)))*($11/$12))^2) }' $file0 > temp_q2_1_evt_ch_lt.txt
#							Run #	EvtUp	EvtDwn	ChUp	ChDwn	LtUp	LtDwn	dSup	dSdown
#							$1		$2		$3		$4		$5		$6		$7		$8		$9


file1="./temp_q2_1_evt_ch_lt.txt"
awk '$1>20000 && $1<30000 && $4*$6>0 && $5*$7>0 && ($2+$3)>0 {print $1,$2/($4*$6),$3/($5*$7),1/sqrt($2+$3),$8/($4*$6),$9/($5*$7)}' $file1 > temp_q2_1_yields.txt
#							Run #	YieldUp		YieldDwn	1/sqrt(N)	dYup	dYdown
#							$1		$2			$3			$4			$5		$6


file2="./temp_q2_1_yields.txt"
#awk '$1>20000 && $1<30000 && ($2+$3)>0 {print $1,($2-$3)/($2+$3),$4}' $file2 > temp_q2_1_asym.txt
#awk '$1>20000 && $1<30000 && ($2+$3)>0 {print $1,($2-$3)/($2+$3),(2/((($2/$3)+1)^2))*($2/$3)*sqrt(($5/$2)^2+($6/$3)^2)}' $file2 > final_q2_1_asym_runnum.txt
#							Run #	Ay0		dAy0
#							$1		$2		$3

awk '$1>20000 && $1<30000 && ($2+$3)>0 {print $1,(($2-$3)/($2+$3))*(1/(0.514*0.9721*0.9907)),(1/(0.514*0.9721*0.9907))*(2/((($2/$3)+1)^2))*($2/$3)*sqrt(($5/$2)^2+($6/$3)^2)}' $file2 > temp_final_q2_1_asym_runnum.txt

file9="./temp_final_q2_1_asym_runnum.txt"
#awk '$1>20000 && $1<30000 {print $1,$2,sqrt(($2*0.0120/0.9721)^2 + ($2*0.000097/0.9907)^2 + ($2*0.024/0.514)^2 + $3^2)}' $file9 > final_q2_1_asym_runnum.txt
awk '$1>20000 && $1<30000 {print $1,$2,3.08822*sqrt(($2*0.0120/0.9721)^2 + ($2*0.000097/0.9907)^2 + ($2*0.024/0.514)^2 + $3^2)}' $file9 > final_q2_1_asym_runnum.txt
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
S=`awk 'BEGIN{printf("%0.5f", sqrt('$chi2ovrdof'))}'`
echo "For 3He(e,e') Ay per run #, chi2=" $chi2 ", dof=" $dof ", chi2/dof=" $chi2ovrdof ", S=" $S



#xmgrace\
gracebat -hdevice PNG -printfile plot_q2_1_ay0.png \
		 -settype xydy		-block final_q2_1_asym_runnum.txt		-graph 0 -bxy 1:2:3 \
		 -settype xydy		-block temp_final_q2_1_asym_runnum.txt	-graph 0 -bxy 1:2:3 \
		 -settype xy		-block temp_ave_ay0.txt					-graph 0 -bxy 1:2 \
		 -p q2_1_asym.par	-noask

#display plot_q2_1_ay0.png



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

echo $totChUp
echo $totChDn
echo $totT2Up
echo $totT2Dn
echo $totScUp
echo $totScDn
echo $totLtUp
echo $totLtDn

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
awk '$1>0.010 && $1<3 && ($2+$3)>0 {print $1,(($2-$3)/($2+$3))*(1/(0.514*0.9721*0.9907)),(1/(0.514*0.9721*0.9907))*(2/((($2/$3)+1)^2))*($2/$3)*sqrt(($5/$2)^2+($6/$3)^2)}' $file5 > final_q2_1_nu_asym_stat.txt

file10="./final_q2_1_nu_asym_stat.txt"
awk '$1>0.010 && $1<3 {print $1,$2,$3,sqrt(($2*0.0120/0.9721)^2 + ($2*0.000097/0.9907)^2 + ($2*0.024/0.514)^2)}' $file10 > temp_q2_1_nu_asym_all.txt
file11="./temp_q2_1_nu_asym_all.txt"

echo "nu                  Ay0      e_s       e_N         e_p         e_t       e_n" > final_q2_1_nu_asym_all_errs.txt
awk '$1>0.010 && $1<3 {print $1,$2,$3,$2*0.0120/0.9721,$2*0.000097/0.9907,$2*0.024/0.514,sqrt(('$S'^2-1)*(($2*0.0120/0.9721)^2 + ($2*0.000097/0.9907)^2 + ($2*0.024/0.514)^2 + $3^2))}' $file11 >> final_q2_1_nu_asym_all_errs.txt

file12="./final_q2_1_nu_asym_all_errs.txt"
awk '$1>0.010 && $1<3 {print $1,$2,$3,sqrt($4^2 + $5^2 + $6^2 + $7^2)}' $file12 > final_q2_1_nu_asym_stat_sys.txt
awk '$1>0.010 && $1<3 {print $1,$2,sqrt($3^2 + $4^2 + $5^2 + $6^2 + $7^2)}' $file12 > final_q2_1_nu_asym_tot.txt
#                           Run #   Ay0     dAy0
#                           $1      $2      $3

#xmgrace\
gracebat -hdevice PNG -printfile plot_q2_1_nu_ay0.png \
         -settype xydy  -block final_q2_1_nu_asym_stat.txt  -graph 0 -bxy 1:2:3 \
         -settype xydy  -block final_q2_1_nu_asym_tot.txt  -graph 0 -bxy 1:2:3 \
         -p q2_1_nu_asym.par   -noask

#display plot_q2_1_nu_ay0.png





rm temp*







