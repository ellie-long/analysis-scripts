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

#sort -t ' ' -k1 vert_3he_q2_01_eeprime_asym_v_runnum_for_runs_20487-20511.txt > temp_eeprime.txt
sort -t ' ' -k1 vert_3he_q2_01_asym_v_runnum_for_runs_20487-20511.txt > temp_results.txt
sort -t ' ' -k1 q2_01_ch-lt.txt > temp_charge.txt
sort -t ' ' -k1 q2_01_prescales.txt > temp_prescales.txt
join -t ' ' temp_results.txt temp_charge.txt > temp_q2_01_near_final.txt
join -t ' ' temp_q2_01_near_final.txt temp_prescales.txt > temp_q2_01_final.txt

#join -t ' ' <(sort vert_3he_q2_01_eeprime_asym_v_runnum_for_runs_20487-20511.txt) <(sort q2_01_charge.txt) > temp_q2_01_final.txt

#file0="./q2_01_final4.txt"
file0="temp_q2_01_final.txt"
awk '$1>20000 && $1<30000 && $29>0 && $31>0 && ($6+$8)>0 && $12>0 {print $1,$2,$3,$32*1.5577E-10,$34*1.5577E-10,$17*$38/$29,$20*$38/$31,sqrt((sqrt($4)^2)+((1/(sqrt($6+$8)))*($10/$12))^2),sqrt((sqrt($5)^2)+((1/(sqrt($7+$9)))*($11/$12))^2) }' $file0 > temp_q2_01_evt_ch_lt.txt
#							Run #	EvtUp	EvtDwn	ChUp	ChDwn	LtUp	LtDwn	dSup	dSdown
#							$1		$2		$3		$4		$5		$6		$7		$8		$9


file1="./temp_q2_01_evt_ch_lt.txt"
awk '$1>20000 && $1<30000 && $4*$6>0 && $5*$7>0 && ($2+$3)>0 {print $1,$2/($4*$6),$3/($5*$7),1/sqrt($2+$3),$8/($4*$6),$9/($5*$7)}' $file1 > temp_q2_01_yields.txt
#							Run #	YieldUp		YieldDwn	1/sqrt(N)	dYup	dYdown
#							$1		$2			$3			$4			$5		$6


file2="./temp_q2_01_yields.txt"
#awk '$1>20000 && $1<30000 && ($2+$3)>0 {print $1,($2-$3)/($2+$3),$4}' $file2 > temp_q2_01_asym.txt
awk '$1>20000 && $1<30000 && ($2+$3)>0 {print $1,($2-$3)/($2+$3),(2/((($2/$3)+1)^2))*($2/$3)*sqrt(($5/$2)^2+($6/$3)^2)}' $file2 > temp_q2_01_asym.txt
#							Run #	Ay0		dAy0
#							$1		$2		$3


#xmgrace\
gracebat -hdevice PNG -printfile plot_q2_01_ay0.png \
        -settype xydy     -block temp_q2_01_asym.txt        -graph 0 -bxy 1:2:3 \
		-p q2_01_asym.par	-noask

display plot_q2_01_ay0.png

#rm temp*







