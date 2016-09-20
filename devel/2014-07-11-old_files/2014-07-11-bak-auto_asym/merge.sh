#!/bin/bash

awk 'BEGIN{
while ( ( getline < "q2_01_charge.txt" ) > 0){
   array_test[$1]=$0
}
}


{
print $1 " " $2 " " $3 " " $4 " " $5 " " $6 " " $7 " " $8 " " $9 " " $10 " " $11 " " array_test[$1]
}' vert_3he_q2_01_eeprime_asym_v_runnum_for_runs_20487-20511.txt


