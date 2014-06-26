#!/usr/bin/env python2.3
#
#  run_info.py
#  
#  This files should take the runs from runNumFile and the search for their corresponding
#  url from all_halog_urls and output the run data into these files in the folder ./run_info: 
#  r_beam_energy, r_momentum, r_theta, r_target, r_bhwp
#
#  Created by Elena Long on 4/21/10.
#

import urllib2
import os
import os.path
from httplib import HTTP
from urlparse import urlparse

# Below are the variables to change which files you want to look at
halogFile = "./all_halog_urls_test"
runNumFile = "./vert_rhrs_runs"

def checkURL(url):
	p = urlparse(url)
	h = HTTP(p[1])
	h.putrequest('HEAD', p[2])
	h.endheaders()
	if h.getreply()[0] == 200: return 1
	else: return 0
	
fhalog = open(halogFile,"r")
urlList = fhalog.readlines()
haloglength = 0
fhalog.close()
for line in open(halogFile): haloglength += 1
frun = open(runNumFile,"r")
runNumList = frun.readlines()
runListLength = 0
frun.close()
for line in open(runNumFile): runListLength += 1

# vvvvvvv This block removes old run_info files and opens up clear, new ones
if (os.path.exists("./run_info/r_beam_energy")): os.remove("./run_info/r_beam_energy")
beam_energy = open("./run_info/r_beam_energy","a")
beam_energy.write("This file contains the Beam Energy Values based on the Run # in " + runNumFile + "\n")
if (os.path.exists("./run_info/r_momentum")): os.remove("./run_info/r_momentum")
momentum = open("./run_info/r_momentum","a")
momentum.write("This file contains the Momentum Values based on the Run # in " + runNumFile + "\n")
if (os.path.exists("./run_info/r_theta")): os.remove("./run_info/r_theta")
theta = open("./run_info/r_theta","a")
theta.write("This file contains the Theta Values based on the Run # in " + runNumFile + "\n")
if (os.path.exists("./run_info/r_target_type")): os.remove("./run_info/r_target_type")
targettype = open("./run_info/r_target_type","a")
targettype.write("This file contains the Target Type Values based on the Run # in " + runNumFile + "\n")
if (os.path.exists("./run_info/r_target_pol")): os.remove("./run_info/r_target_pol")
targetpol = open("./run_info/r_target_pol","a")
targetpol.write("This file contains the Target Polarization Direction Values based on the Run # in " + runNumFile + "\n")
if (os.path.exists("./run_info/r_bhwp")): os.remove("./run_info/r_bhwp")
bhwp = open("./run_info/r_bhwp","a")
bhwp.write("This file contains the BHWP Values based on the Run # in " + runNumFile + "\n")

if (os.path.exists("./run_info/_run_info_summary")): os.remove("./run_info/_run_info_summary")
fSummary = open("./run_info/_run_info_summary","a")
# fSummary.write("Run #	Beam e0	R Mom.	R Theta		Tgt Dir.		BHWP\n")
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


i = 1
j = 0
startrun = 0
endrun = 0
print "urlList length = " + str(haloglength)
print "runListLength = " + str(runListLength)
while ( i < haloglength):
	halogURL = str(urlList[i])[:67]
	runNumber = str(runNumList[j])[:5]
#	print "Processing HALog URL " + halogURL
#	print "URL Check: " + str(checkURL(halogURL))
#	if (checkURL(halogURL) == 1):
	if (1 == 1):
		print "Processing HALog URL " + halogURL
		halogEntry = urllib2.urlopen(halogURL)
		startrun = 0
		for line in halogEntry:
			if "keyword=Start_Run_" in line:
				if (line[18:23] == runNumber):
					startrun = 1
					print "Found Run # " + runNumber + " Start of Run!  Processing...\n"
			else:
				if (startrun == 1):
					if "target_type=" in line:
						targettype.write(line[12:])
						fSummary.write("Run # " + runNumber + "\n	" +"Target Type: " + line[12:] + "	")
					if "targetpol_poldir=" in line:
						targetpol.write(line[17:])
						fSummary.write("Target Polarization: " + line[17:] + "	")
					if "beam_e0=" in line:
						beam_energy.write(line[8:])
						fSummary.write("Beam Energy: " + line[8:] + "	")
					if "beam_halfwaveplate=" in line:
						bhwp.write(line[19:])
						fSummary.write("BHWP: " + line[19:] + "	")
					if "rightarm_p=" in line:
						momentum.write(line[11:])
						fSummary.write("RHRS Momentum: " + line[11:] + "	")
					if "rightarm_theta" in line: 
						theta.write(line[15:])
						fSummary.write("RHRS Theta: " + line[15:] + "\n")
						j += 1
						if (j > runListLength):
							i = haloglength
	i += 1
	
print "All done!\n"



