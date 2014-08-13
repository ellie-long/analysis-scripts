#!/bin/bash
# vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
# 
# prep_q2_01.sh
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
bresults="$home/../../../results/q2_01_vert_3he"
chlt="$home/ch-lt/q2_01_vert"

# Copy recent batch results to the main results folder after backing up recent results
ls $home/../../../batch/results
read -rep $'\nWhich folder are the farmed result in?\n> ' farmDate
farmFolder="$home/../../../batch/results/$farmDate"
date=`date +"%Y-%m-%d-%T"`
newFolder="$bresults/$date"
mkdir "$newFolder"
mv $bresults/*.log  $newFolder/.
mv $bresults/*.out  $newFolder/.
mv $bresults/*.txt  $newFolder/.
mv $bresults/*.root $newFolder/.
cp -v $farmFolder/* $bresults/.

# Copy charge/livetime information and output in correct format
cp -v $bresults/charge-lt_for_run_* $chlt/.
$chlt/get_q2_01_chlt.sh

# Add root files and analyze combined results
analyzer ../add_root_files/add_vert_3he_q2_01.C
analyzer ../add_results/add_class_targ_asymmetry_vs_nu.C
