#!/bin/sh

# vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
#
# get_q2_05_ch-lt.sh
#
# This shell script should output all charge/lt files in this 
# directory into a single file to be read by the auto_asym scripts
#
# Elena Long
# ellie@jlab.org
# 8/1/2014
#
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

rm q2_05_ch-lt.txt
cat charge_lt_for_run_* > q2_05_ch-lt.txt

sed -i.bak "s/Run\ //g" q2_05_ch-lt.txt
sed -i.bak ':a;N;$!ba;s/\n/\ /g' q2_05_ch-lt.txt
sed -i.bak 's/\ \ /&\
/g' q2_05_ch-lt.txt

