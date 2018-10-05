#!/bin/sh

# vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
#
# get_total_ay0.sh
#
# This shell script plots the 3He(e,e'n) Ay0 asymmetry.
#
# Elena Long
# ellie@jlab.org
# 7/2/2013
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

file0="q2_01_vert/final_q2_01_nu_asym_stat_sys.txt"
awk '$1>0.079 && $1<0.085 {print 0.127,$2,$3}' $file0 > final_ay0.txt
awk '$1>0.079 && $1<0.085 {print 0.127,$2,sqrt($3^2+$4^2)}' $file0 >> final_ay0.txt
awk '$1>0.079 && $1<0.085 {print 0.127,$2,$3,$4}' $file0 > final_ay0_stat_sys.txt
#awk '$1>0.079 && $1<0.085 {print 0.127,$2,sqrt(0.51599)*$3}' $file1 >> final_ay0.txt
#awk '$1>0.079 && $1<0.085 {print 0.127,$2,sqrt(0.89527)*$3}' $file1 >> final_ay0.txt

file1="q2_05_vert/final_q2_05_nu_asym_stat_sys.txt"
awk '$1>0.265 && $1<0.28 {print 0.456,$2,$3}' $file1 >> final_ay0.txt
awk '$1>0.265 && $1<0.28 {print 0.456,$2,sqrt($3^2+$4^2)}' $file1 >> final_ay0.txt
awk '$1>0.265 && $1<0.28 {print 0.456,$2,$3,$4}' $file1 >> final_ay0_stat_sys.txt
#awk '$1>0.265 && $1<0.28 {print 0.456,$2,sqrt(2.75398)*$3}' $file3 >> final_ay0.txt
#awk '$1>0.265 && $1<0.28 {print 0.456,$2,sqrt(2.75452)*$3}' $file3 >> final_ay0.txt

file2="q2_1_vert/final_q2_1_nu_asym_stat_sys.txt"
awk '$1>0.55 && $1<0.57 {print 0.953,$2,$3}' $file2 >> final_ay0.txt
awk '$1>0.55 && $1<0.57 {print 0.953,$2,sqrt($3^2+$4^2)}' $file2 >> final_ay0.txt
awk '$1>0.55 && $1<0.57 {print 0.953,$2,$3,$4}' $file2 >> final_ay0_stat_sys.txt
#awk '$1>0.55 && $1<0.57 {print 0.953,$2,sqrt(9.53712)*$3}' $file3 >> final_ay0.txt
#awk '$1>0.55 && $1<0.57 {print 0.953,$2,sqrt(9.25542)*$3}' $file3 >> final_ay0.txt


#xmgrace\
gracebat -hdevice PNG -printfile plot_ay0.png \
		 -settype xydy		-block final_ay0.txt		-graph 0 -bxy 1:2:3 \
		 -settype xydy		-block ay0_nikhef.txt	-graph 0 -bxy 1:2:3 \
		 -settype xydy		-block ay0_mami.txt		-graph 0 -bxy 1:2:3 \
		 -p asym.par	-noask

display plot_ay0.png

gracebat -hdevice PNG -printfile plot_ay0_log.png \
		 -settype xydy		-block final_ay0.txt		-log y	-graph 0 -bxy 1:2:3 \
		 -settype xydy		-block ay0_nikhef.txt	-log y	-graph 0 -bxy 1:2:3 \
		 -settype xydy		-block ay0_mami.txt		-log y	-graph 0 -bxy 1:2:3 \
		 -p asym_log.par	-noask

display plot_ay0_log.png






#rm temp*







