#!/bin/bash
# vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
# 
# prep_q2_05.sh
#
# This script should entirely prepare and run
# the final piece of analysis for Ay0
#
# Elena Long
# ellie@jlab.org
# 8/13/2014
#
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

# Set folder definitions
home="."
bresults="$home/../../../results/q2_05_vert_3he"
chlt="$home/ch-lt/q2_05_vert"

# Copy recent batch results to the main results folder after backing up recent results
#ls $home/../../../batch/results
#read -rep $'\nWhich folder are the farmed result in?\n> ' farmDate
#farmFolder="$home/../../../batch/results/$farmDate"
#date=`date +"%Y-%m-%d-%T"`
#newFolder="$bresults/$date"
#mkdir "$newFolder"
#mv $bresults/*.log  $newFolder/.
#mv $bresults/*.out  $newFolder/.
#mv $bresults/*.txt  $newFolder/.
#mv $bresults/*.root $newFolder/.
#cp -v $farmFolder/* $bresults/.

# Copy charge/livetime information and output in correct format
cp -v $bresults/charge_lt_for_run_* $chlt/.
cat $bresults/charge_lt_for_run_* > $bresults/q2_05_vert_3he_run_info.txt
rm $chlt/q2_05_ch-lt.txt
cat $chlt/charge_lt_for_run_* > $chlt/q2_05_ch-lt.txt
sed -i.bak "s/Run\ //g" $chlt/q2_05_ch-lt.txt
sed -i.bak ':a;N;$!ba;s/\n/\ /g' $chlt/q2_05_ch-lt.txt
sed -i.bak 's/\ \ /&\
/g' $chlt/q2_05_ch-lt.txt

# Add root files and analyze combined root file
analyzer $home/../add_root_files/add_vert_3he_q2_05.C
analyzer $home/../add_results/add_class_targ_asymmetry_vs_nu.C

# Run final analysis script and get results
#$home/q2_05_vert/get_ay0.sh







