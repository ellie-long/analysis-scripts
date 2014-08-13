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

# Copy recent batch results to the main results folder
ls ../../../batch/results
read -rep $'\nWhich folder are the farmed result in?\n> ' farmDate
farmFolder="../../../batch/results/$farmDate"
#echo "$farmFolder"
date=`date +"%Y-%m-%d-%T"`
newFolder="../../../results/q2_01_vert_3he/$date"
mkdir "$newFolder"
mv ../../../results/q2_01_vert_3he/*.log "$newFolder/."
mv ../../../results/q2_01_vert_3he/*.out "$newFolder/."
mv ../../../results/q2_01_vert_3he/*.txt "$newFolder/."
mv ../../../results/q2_01_vert_3he/*.root "$newFolder/."
cp -v $farmFolder/* ../../../results/q2_01_vert_3he/.

# Add root files and analyze combined results
analyzer ../add_root_files/add_vert_3he_q2_01.C

