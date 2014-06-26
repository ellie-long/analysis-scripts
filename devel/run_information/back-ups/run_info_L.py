#!/usr/bin/env python2.3
#
#  run_info_L.py
#  
#  This files should take the runs from runNumFile and the search for their corresponding
#  url from halogFile and output the run data into these files in the folder ./run_info: 
#  l_beam_energy, l_momentum, l_theta, l_target_type, l_target_pol, l_bhwp, l_events,
#  l_sieve, bb_theta, bb_sieve, bb_current
#
#  Note: For everything to work properly, be sure to insert a dummy run at the end of runNumFile
#	 i.e. 9999
#
#  There is a slight bug if there is no Start_of_Run file and there is an End_of_Run file.
#  Basically, it jumbles up the output of the runs in the summary file. Because of this,
#  I added a "Run #" for each of the event outputs so it is obvious which run is being talked
#  about when this jumbling happens. The bug is highlighted below under "BUG"
#
#  Created by Elena Long on 4/21/10.
#

import urllib2
import os
import os.path
from httplib import HTTP
from urlparse import urlparse

# Below are the variables to change which files you want to look at
halogFile = "./all_halog_urls"
runNumFile = "./vert_lhrs_runs"

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
if (os.path.exists("./run_info/l_beam_energy")): os.remove("./run_info/l_beam_energy")
beam_energy = open("./run_info/l_beam_energy","a")
beam_energy.write("This file contains the Beam Energy Values based on the Run # in " + runNumFile + "\n")
if (os.path.exists("./run_info/l_momentum")): os.remove("./run_info/l_momentum")
momentum = open("./run_info/l_momentum","a")
momentum.write("This file contains the Momentum Values based on the Run # in " + runNumFile + "\n")
if (os.path.exists("./run_info/l_theta")): os.remove("./run_info/l_theta")
theta = open("./run_info/l_theta","a")
theta.write("This file contains the Theta Values based on the Run # in " + runNumFile + "\n")
if (os.path.exists("./run_info/l_target_type")): os.remove("./run_info/l_target_type")
targettype = open("./run_info/l_target_type","a")
targettype.write("This file contains the Target Type Values based on the Run # in " + runNumFile + "\n")
if (os.path.exists("./run_info/l_target_pol")): os.remove("./run_info/l_target_pol")
targetpol = open("./run_info/l_target_pol","a")
targetpol.write("This file contains the Target Polarization Direction Values based on the Run # in " + runNumFile + "\n")
if (os.path.exists("./run_info/l_bhwp")): os.remove("./run_info/l_bhwp")
bhwp = open("./run_info/l_bhwp","a")
bhwp.write("This file contains the BHWP Values based on the Run # in " + runNumFile + "\n")
if (os.path.exists("./run_info/l_bhwp")): os.remove("./run_info/l_bhwp")
bhwp = open("./run_info/l_bhwp","a")
bhwp.write("This file contains the BHWP Values based on the Run # in " + runNumFile + "\n")
if (os.path.exists("./run_info/l_events")): os.remove("./run_info/l_events")
events = open("./run_info/l_events","a")
events.write("This file contains the Number of Events based on the Run # in " + runNumFile + "\n")


if (os.path.exists("./run_info/l_sieve")): os.remove("./run_info/l_sieve")
sieve = open("./run_info/l_sieve","a")
sieve.write("This file contains the Sieve Values based on the Run # in " + runNumFile + "\n")
if (os.path.exists("./run_info/bb_theta")): os.remove("./run_info/bb_theta")
bb_theta = open("./run_info/bb_theta","a")
bb_theta.write("This file contains the BigBite Theta Values based on the Run # in " + runNumFile + "\n")
if (os.path.exists("./run_info/bb_sieve")): os.remove("./run_info/bb_sieve")
bb_sieve = open("./run_info/bb_sieve","a")
bb_sieve.write("This file contains the BigBite Sieve Values based on the Run # in " + runNumFile + "\n")
if (os.path.exists("./run_info/bb_current")): os.remove("./run_info/bb_current")
bb_current = open("./run_info/bb_current","a")
bb_current.write("This file contains the BigBite Current Values based on the Run # in " + runNumFile + "\n")

if (os.path.exists("./run_info/_run_info_summary_l")): os.remove("./run_info/_run_info_summary_l")
fSummary = open("./run_info/_run_info_summary_l","a")
# fSummary.write("Run #	Beam e0	R Mom.	R Theta		Tgt Dir.		BHWP\n")
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


i = 1
j = 0
k = 0
startrun = 0
endrun = 0
print "urlList length = " + str(haloglength)
print "runListLength = " + str(runListLength)
while ( i < haloglength):
	halogURL = str(urlList[i])[:67]
	startRunNumber = str(runNumList[j])[:4]
	endRunNumber = str(runNumList[k])[:4]
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!! BUG !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# Below doesn't work quite as hoped. See top text for details.
	if (startRunNumber == "20466"):
		fSummary.write("Run Number " + startRunNumber + " has no start of run file\n\n")
		targettype.write("Run Number " + startRunNumber + " has no start of run file\n")
		targetpol.write("Run Number " + startRunNumber + " has no start of run file\n")
		beam_energy.write("Run Number " + startRunNumber + " has no start of run file\n")
		bhwp.write("Run Number " + startRunNumber + " has no start of run file\n")
		momentum.write("Run Number " + startRunNumber + " has no start of run file\n")
		theta.write("Run Number " + startRunNumber + " has no start of run file\n")
		sieve.write("Run Number " + startRunNumber + " has no start of run file\n")
		bb_current.write("Run Number " + startRunNumber + " has no start of run file\n")
		bb_theta.write("Run Number " + startRunNumber + " has no start of run file\n")
		bb_sieve.write("Run Number " + startRunNumber + " has no start of run file\n")
		j += 1
	if (endRunNumber == "1603"):
		fSummary.write("\nRun Number " + endRunNumber + " has no end of run file\n\n")
		events.write("Run Number " + endRunNumber + " has no end of run file\n")
		k += 1
	if (endRunNumber == "2005"):
		fSummary.write("\nRun Number " + endRunNumber + " has no end of run file\n\n")
		events.write("Run Number " + endRunNumber + " has no end of run file\n")
		k += 1
	if (endRunNumber == "2009"):
		fSummary.write("\nRun Number " + endRunNumber + " has no end of run file\n\n")
		events.write("Run Number " + endRunNumber + " has no end of run file\n")
		k += 1

# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (startRunNumber == "9999"):
		if (endRunNumber == "9999"):
			i = haloglength
	if (checkURL(halogURL) == 1):
		print "Processing HALog URL " + halogURL
		print "Looking for Start of Run file for Run # " + startRunNumber
		print "Looking for End of Run file for Run # " + endRunNumber
		halogEntry = urllib2.urlopen(halogURL)
		startrun = 0
		endrun = 0
		for line in halogEntry:
			if "keyword=Start_Run_" in line:
				if (line[18:22] == startRunNumber):
					startrun = 1
					print "Found Run # " + startRunNumber + " Start of Run!  Processing...\n"
			elif (startrun == 1):
				if "target_type=" in line:
					targettype.write(line[12:])
					fSummary.write("Run # " + startRunNumber + "\n	" +"Target Type: " + line[12:] + "	")
				if "targetpol_poldir=" in line:
					targetpol.write(line[17:])
					fSummary.write("Target Polarization: " + line[17:] + "	")
				if "beam_e0=" in line:
					beam_energy.write(line[8:])
					fSummary.write("Beam Energy: " + line[8:] + "	")
				if "beam_halfwaveplate=" in line:
					bhwp.write(line[19:])
					fSummary.write("BHWP: " + line[19:] + "	")
				if "leftarm_p=" in line:
					momentum.write(line[10:])
					fSummary.write("LHRS Momentum: " + line[10:] + "	")
				if "leftarm_theta=" in line: 
					theta.write(line[14:])
					fSummary.write("LHRS Theta: " + line[14:] + "	")
				if "leftarm_sieve=" in line:
					sieve.write(line[14:])
					fSummary.write("LHRS Sieve: " + line[14:] + "	")
				if "bbarm_i=" in line:
					bb_current.write(line[8:])
					fSummary.write("BB Current: " + line[8:] + "	")
				if "bbarm_theta=" in line:
					bb_theta.write(line[12:])
					fSummary.write("BB Theta: " + line[12:] + "	")
				if "bbarm_sieve=" in line:
					bb_sieve.write(line[12:])
					fSummary.write("BB Sieve: " + line[12:] + "	")
					if (startRunNumber == "1603"):
						fSummary.write("\n\n")
					if (startRunNumber == "2005"):
						fSummary.write("\n\n")
					if (startRunNumber == "2009"):
						fSummary.write("\n\n")
					j += 1
#					if (j > runListLength):
#						i = haloglength
			elif (startrun == 0):
				if "keyword=End_of_Run_" in line:
					if (line[19:23] == endRunNumber):
						endrun = 1
						print "Found Run # " + endRunNumber + " End of Run! Processing...\n"
				elif (endrun == 1):
					if "EVENTS   : [ 0]: " in line:
						events.write(line[17:25] + "\n")
						fSummary.write("# of Events for Run # " + endRunNumber + ": " + line[17:25] + "\n\n")
						k += 1
	i += 1
	
print "All done!\n"



