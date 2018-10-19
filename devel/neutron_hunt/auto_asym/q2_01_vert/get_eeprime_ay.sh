#!/bin/sh

# vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
#
# get_eeprime_ay.sh
#
# This shell script plots the 3He(e,e') Ay asymmetry.
#
# Elena Long
# ellie@jlab.org
# 8/8/2013
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

sort -t ' ' -k1 vert_3he_q2_01_eeprime_asym_v_runnum_for_runs_20487-20511.txt > temp_eeprime.txt
sort -t ' ' -k1 q2_01_ch-lt.txt > temp_charge.txt
sort -t ' ' -k1 q2_01_prescales.txt > temp_prescales.txt
join -t ' ' temp_eeprime.txt temp_charge.txt > temp_q2_01_near_final.txt
join -t ' ' temp_q2_01_near_final.txt temp_prescales.txt > temp_q2_01_eeprime_final.txt


file0="temp_q2_01_eeprime_final.txt"
awk '$1>20000 && $1<30000 && $28>0 && $30>0 {print $1,$8,$9,$31*1.5577E-10,$33*1.5577E-10,$16*$37/$28,$19*$37/$30}' $file0 > temp_q2_01_eeprime_evt_ch_lt.txt
#							Run #	EvtUp	EvtDwn	ChUp	ChDwn	LtUp	LtDwn
#							$1		$2		$3		$4		$5		$6		$7	


file1="./temp_q2_01_eeprime_evt_ch_lt.txt"
awk '$1>20000 && $1<30000 && $4*$6>0 && $5*$7>0 && ($2+$3)>0 {print $1,$2/($4*$6),$3/($5*$7),1/sqrt($2+$3)}' $file1 > temp_q2_01_eeprime_yields.txt
#							Run #	YieldUp		YieldDwn	1/sqrt(N)	
#							$1		$2			$3			$4		


file2="./temp_q2_01_eeprime_yields.txt"
awk '$1>20000 && $1<30000 && ($2+$3)>0 {print $1,($2-$3)/($2+$3),$4}' $file2 > final_q2_01_eeprime_asym.txt
#							Run #	Ay0		dAy0
#							$1		$2		$3

file3="../yawei_info.txt"
awk '$1>20486 && $1<20512 {print $1,$10,$11}' $file3 > temp_q2_01_yawei_eeprime.txt
#							Run #	Ay0		dAy0
#							$1		$2		$3

file7="./final_q2_01_eeprime_asym.txt"
awk '{print 1}' $file7 > temp_dofeeprime2.txt
sed "s/e+0/*10^/g" temp_dofeeprime2.txt > temp_dofeeprime.txt
awk '{print 1/($3*$3)}' $file7 > temp_wieeprime2.txt
sed "s/e+0/*10^/g" temp_wieeprime2.txt > temp_wieeprime.txt
awk '{print $2/($3*$3)}' $file7 > temp_wi_eeprime_asym2.txt
sed "s/e+0/*10^/g" temp_wi_eeprime_asym2.txt > temp_wi_eeprime_asym.txt

dof_temp="$(paste -sd+ temp_dofeeprime.txt | bc)"
sumWi="$(paste -sd+ temp_wieeprime.txt | bc)"
sumWiAy="$(paste -sd+ temp_wi_eeprime_asym.txt | bc)"
aveAy=`awk 'BEGIN{printf("%0.5f", '$sumWiAy' / '$sumWi')}'`
dof=`awk 'BEGIN{printf("%0.5f", '$dof_temp'-1)}'`


echo 0 $aveAy > temp_ave_eeprime_asym.txt
echo 30000 $aveAy >> temp_ave_eeprime_asym.txt

awk '{print 1/($3*$3)*('$aveAy'-$2)*('$aveAy'-$2)}' $file7 > temp_chi2ieeprime.txt
chi2="$(paste -sd+ temp_chi2ieeprime.txt | bc)"

echo "dof_temp=" $dof_temp ", sumWi=" $sumWi ", sumWiAy=" $sumWiAy ", aveAy=" $aveAy ", chi^2=" $chi2 ", dof=" $dof
echo "1" > temp_temptempeeprime.txt

file8="./temp_temptempeeprime.txt"
awk '{print '$chi2','$dof'}' $file8 > chi2_dof_eeprime_asym.txt

chi2ovrdof=`awk 'BEGIN{printf("%0.5f", '$chi2' / '$dof')}'`
echo "For 3He(e,e') Ay per run #, chi2=" $chi2 ", dof=" $dof ", chi2/dof=" $chi2ovrdof




#xmgrace\
gracebat -hdevice PNG	-printfile plot_q2_01_eeprime_asym.png \
		 -settype xydy	-block temp_q2_01_yawei_eeprime.txt	-graph 0 -bxy 1:2:3 \
		 -settype xydy	-block final_q2_01_eeprime_asym.txt	-graph 0 -bxy 1:2:3 \
		 -settype xy	-block temp_ave_eeprime_asym.txt	-graph 0 -bxy 1:2 \
		 -p q2_01_eeprime_asym.par	-noask

display plot_q2_01_eeprime_asym.png

rm temp*







