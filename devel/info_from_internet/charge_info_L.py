#!/usr/bin/env python2.3
#
#  charge_info.py
#  
#  This files should take the runs from run_number and the search for their corresponding
#  url from halog_end_of_run_urls and output the BCM data into these files in the folder ./BCM: 
#  bcmu#0, bcmu#++, bcmu#--, bcmu#-+, bcmu#+- where #=1, 3, 10  
#
#  Created by Elena Long on 1/15/10.
#  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
#

import urllib2
import os
import os.path
from httplib import HTTP
from urlparse import urlparse

# The variable below defines which files you want to look at
halogFile = "./all_halog_urls"
runNumFile = "./left-1st-pass-bcm-runs.txt"

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


# vvvvvvv This big block removes old BCM files and opens up clear, new ones
if (os.path.exists("./BCM_L/bcmu10")): os.remove("./BCM_L/bcmu10")
fu10 = open("./BCM_L/bcmu10","a")
fu10.write("This file contains the BCM u1 [0] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmu1++")): os.remove("./BCM_L/bcmu1++")
fu1upup = open("./BCM_L/bcmu1++","a")
fu1upup.write("This file contains the BCM u1 [++] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmu1-+")): os.remove("./BCM_L/bcmu1-+")
fu1downup = open("./BCM_L/bcmu1-+","a")
fu1downup.write("This file contains the BCM u1 [-+] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmu1+-")): os.remove("./BCM_L/bcmu1+-")
fu1updown = open("./BCM_L/bcmu1+-","a")
fu1updown.write("This file contains the BCM u1 [+-] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmu1--")): os.remove("./BCM_L/bcmu1--")
fu1downdown = open("./BCM_L/bcmu1--","a")
fu1downdown.write("This file contains the BCM u1 [--] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmu30")): os.remove("./BCM_L/bcmu30")
fu30 = open("./BCM_L/bcmu30","a")
fu30.write("This file contains the BCM u1 [0] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmu3++")): os.remove("./BCM_L/bcmu3++")
fu3upup = open("./BCM_L/bcmu3++","a")
fu3upup.write("This file contains the BCM u1 [++] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmu3-+")): os.remove("./BCM_L/bcmu3-+")
fu3downup = open("./BCM_L/bcmu3-+","a")
fu3downup.write("This file contains the BCM u1 [-+] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmu3+-")): os.remove("./BCM_L/bcmu3+-")
fu3updown = open("./BCM_L/bcmu3+-","a")
fu3updown.write("This file contains the BCM u1 [+-] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmu3--")): os.remove("./BCM_L/bcmu3--")
fu3downdown = open("./BCM_L/bcmu3--","a")
fu3downdown.write("This file contains the BCM u3 [--] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmu100")): os.remove("./BCM_L/bcmu100")
fu100 = open("./BCM_L/bcmu100","a")
fu100.write("This file contains the BCM u10 [0] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmu10++")): os.remove("./BCM_L/bcmu10++")
fu10upup = open("./BCM_L/bcmu10++","a")
fu10upup.write("This file contains the BCM u10 [++] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmu10-+")): os.remove("./BCM_L/bcmu10-+")
fu10downup = open("./BCM_L/bcmu10-+","a")
fu10downup.write("This file contains the BCM u10 [-+] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmu10+-")): os.remove("./BCM_L/bcmu10+-")
fu10updown = open("./BCM_L/bcmu10+-","a")
fu10updown.write("This file contains the BCM u10 [+-] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmu10--")): os.remove("./BCM_L/bcmu10--")
fu10downdown = open("./BCM_L/bcmu10--","a")
fu10downdown.write("This file contains the BCM u10 [--] Values based on Run # in run_number\n")

if (os.path.exists("./BCM_L/bcmd10")): os.remove("./BCM_L/bcmd10")
fd10 = open("./BCM_L/bcmd10","a")
fd10.write("This file contains the BCM d1 [0] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmd1++")): os.remove("./BCM_L/bcmd1++")
fd1upup = open("./BCM_L/bcmd1++","a")
fd1upup.write("This file contains the BCM d1 [++] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmd1-+")): os.remove("./BCM_L/bcmd1-+")
fd1downup = open("./BCM_L/bcmd1-+","a")
fd1downup.write("This file contains the BCM d1 [-+] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmd1+-")): os.remove("./BCM_L/bcmd1+-")
fd1updown = open("./BCM_L/bcmd1+-","a")
fd1updown.write("This file contains the BCM d1 [+-] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmd1--")): os.remove("./BCM_L/bcmd1--")
fd1downdown = open("./BCM_L/bcmd1--","a")
fd1downdown.write("This file contains the BCM d1 [--] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmd30")): os.remove("./BCM_L/bcmd30")
fd30 = open("./BCM_L/bcmd30","a")
fd30.write("This file contains the BCM d1 [0] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmd3++")): os.remove("./BCM_L/bcmd3++")
fd3upup = open("./BCM_L/bcmd3++","a")
fd3upup.write("This file contains the BCM d1 [++] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmd3-+")): os.remove("./BCM_L/bcmd3-+")
fd3downup = open("./BCM_L/bcmd3-+","a")
fd3downup.write("This file contains the BCM d1 [-+] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmd3+-")): os.remove("./BCM_L/bcmd3+-")
fd3updown = open("./BCM_L/bcmd3+-","a")
fd3updown.write("This file contains the BCM d1 [+-] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmd3--")): os.remove("./BCM_L/bcmd3--")
fd3downdown = open("./BCM_L/bcmd3--","a")
fd3downdown.write("This file contains the BCM d3 [--] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmd100")): os.remove("./BCM_L/bcmd100")
fd100 = open("./BCM_L/bcmd100","a")
fd100.write("This file contains the BCM d10 [0] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmd10++")): os.remove("./BCM_L/bcmd10++")
fd10upup = open("./BCM_L/bcmd10++","a")
fd10upup.write("This file contains the BCM d10 [++] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmd10-+")): os.remove("./BCM_L/bcmd10-+")
fd10downup = open("./BCM_L/bcmd10-+","a")
fd10downup.write("This file contains the BCM d10 [-+] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmd10+-")): os.remove("./BCM_L/bcmd10+-")
fd10updown = open("./BCM_L/bcmd10+-","a")
fd10updown.write("This file contains the BCM d10 [+-] Values based on Run # in run_number\n")
if (os.path.exists("./BCM_L/bcmd10--")): os.remove("./BCM_L/bcmd10--")
fd10downdown = open("./BCM_L/bcmd10--","a")
fd10downdown.write("This file contains the BCM d10 [--] Values based on Run # in run_number\n")



if (os.path.exists("./BCM_L/_bcm_summary")): os.remove("./BCM_L/_bcm_summary")
fBCMuSummary = open("./BCM_L/_bcm_summary","a")
fBCMuSummary.write("Run #	Stream	Pol	BCM 1		BCM 3		BCM 10\n")


def noEndRun(runNum):	
	fBCMuSummary.write("\nRun Number " + runNum + " has no end of run file\n\n")
	fu10.write("Run Number " + runNum + " has no end of run file\n")
	fu30.write("Run Number " + runNum + " has no end of run file\n")
	fu100.write("Run Number " + runNum + " has no end of run file\n")
	fu1upup.write("Run Number " + runNum + " has no end of run file\n")
	fu3upup.write("Run Number " + runNum + " has no end of run file\n")
	fu10upup.write("Run Number " + runNum + " has no end of run file\n")
	fu1downdown.write("Run Number " + runNum + " has no end of run file\n")
	fu3downdown.write("Run Number " + runNum + " has no end of run file\n")
	fu10downdown.write("Run Number " + runNum + " has no end of run file\n")
	fu1updown.write("Run Number " + runNum + " has no end of run file\n")
	fu3updown.write("Run Number " + runNum + " has no end of run file\n")
	fu10updown.write("Run Number " + runNum + " has no end of run file\n")
	fu1downup.write("Run Number " + runNum + " has no end of run file\n")
	fu3downup.write("Run Number " + runNum + " has no end of run file\n")
	fu10downup.write("Run Number " + runNum + " has no end of run file\n")
	fd10.write("Run Number " + runNum + " has no end of run file\n")
	fd30.write("Run Number " + runNum + " has no end of run file\n")
	fd100.write("Run Number " + runNum + " has no end of run file\n")
	fd1upup.write("Run Number " + runNum + " has no end of run file\n")
	fd3upup.write("Run Number " + runNum + " has no end of run file\n")
	fd10upup.write("Run Number " + runNum + " has no end of run file\n")
	fd1downdown.write("Run Number " + runNum + " has no end of run file\n")
	fd3downdown.write("Run Number " + runNum + " has no end of run file\n")
	fd10downdown.write("Run Number " + runNum + " has no end of run file\n")
	fd1updown.write("Run Number " + runNum + " has no end of run file\n")
	fd3updown.write("Run Number " + runNum + " has no end of run file\n")
	fd10updown.write("Run Number " + runNum + " has no end of run file\n")
	fd1downup.write("Run Number " + runNum + " has no end of run file\n")
	fd3downup.write("Run Number " + runNum + " has no end of run file\n")
	fd10downup.write("Run Number " + runNum + " has no end of run file\n")

# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^



i=1
j=0
print "urlList length = " + str(haloglength)
print "runList Length = " + str(runListLength)
while (i < haloglength):
	halogURL = str(urlList[i])[:67]
	runNumber = str(runNumList[j])[:4]
# Below are runs without an End of Run File
# ************************************************************************

	if (runNumber == "2464"):
		noEndRun(runNumber)
		j += 1
	if (runNumber == "1603"):
		noEndRun(runNumber)
		j += 1
	if (runNumber == "2005"):
		noEndRun(runNumber)
		j += 1
	if (runNumber == "2009"):
		noEndRun(runNumber)
		j += 1
	if (runNumber == "2183"):
		noEndRun(runNumber)
		j += 1
	if (runNumber == "2211"):
		noEndRun(runNumber)
		j += 1
	if (runNumber == "2220"):
		noEndRun(runNumber)
		j += 1
	if (runNumber == "2909"):
		noEndRun(runNumber)
		j += 1
	if (runNumber == "3073"):
		noEndRun(runNumber)
		j += 1
	if (runNumber == "3288"):
		noEndRun(runNumber)
		j += 1
	if (runNumber == "3348"):
		noEndRun(runNumber)
		j += 1
	if (runNumber == "3479"):
		noEndRun(runNumber)
		j += 1
	if (runNumber == "3493"):
		noEndRun(runNumber)
		j += 1
	if (runNumber == "3564"):
		noEndRun(runNumber)
		j += 1
# Below here we do the actual processing of the runs
# **********************************************************************
	if (runNumber == "9999"):
		i = haloglength
	if (checkURL(halogURL) == 1):
		print "Processing HALog URL " + halogURL
		print "Looking for End of Run file for Run # " + runNumber
		halogEntry = urllib2.urlopen(halogURL)
		endrun = 0
		for line in halogEntry:
			if "keyword=End_of_Run_" in line:
				if (line[19:23] == runNumber):
					endrun = 1
					print "Found Run # " + runNumber + " End of Run! Processing...\n"
			elif (endrun == 1):
				if "BCM u1 [ 0]:" in line:
					fu10.write(line[12:21] + "\n")
					fu30.write(line[39:48] + "\n")
					fu100.write(line[66:75] + "\n")
					fBCMuSummary.write(runNumber + "	Up	" + "[ 0]" + "	" + line[12:21] + "	" + line[39:48] + "	" + line[66:75] + "\n")
				if "BCM u1 [++]:" in line:
					fu1upup.write(line[12:21] + "\n")
					fu3upup.write(line[39:48] + "\n")
					fu10upup.write(line[66:75] + "\n")
					fBCMuSummary.write(runNumber + "	Up	" + "[++]" + "	" + line[12:21] + "	" + line[39:48] + "	" + line[66:75] + "\n")
				if "BCM u1 [--]:" in line:
					fu1downdown.write(line[12:21] + "\n")
					fu3downdown.write(line[39:48] + "\n")
					fu10downdown.write(line[66:75] + "\n")
					fBCMuSummary.write(runNumber + "	Up	" + "[--]" + "	" + line[12:21] + "	" + line[39:48] + "	" + line[66:75] + "\n")
				if "BCM u1 [+-]:" in line:
					fu1updown.write(line[12:21] + "\n")
					fu3updown.write(line[39:48] + "\n")
					fu10updown.write(line[66:75] + "\n")
					fBCMuSummary.write(runNumber + "	Up	" + "[+-]" + "	" + line[12:21] + "	" + line[39:48] + "	" + line[66:75] + "\n")
				if "BCM u1 [-+]:" in line:
					fu1downup.write(line[12:21] + "\n")
					fu3downup.write(line[39:48] + "\n")
					fu10downup.write(line[66:75] + "\n")
					fBCMuSummary.write(runNumber + "	Up	" + "[-+]" + "	" + line[12:21] + "	" + line[39:48] + "	" + line[66:75] + "\n\n")
				if "BCM d1 [ 0]:" in line:
					fd10.write(line[12:21] + "\n")
					fd30.write(line[39:48] + "\n")
					fd100.write(line[66:75] + "\n")
					fBCMuSummary.write(runNumber + "	Down	" + "[ 0]" + "	" + line[12:21] + "	" + line[39:48] + "	" + line[66:75] + "\n")
				if "BCM d1 [++]:" in line:
					fd1upup.write(line[12:21] + "\n")
					fd3upup.write(line[39:48] + "\n")
					fd10upup.write(line[66:75] + "\n")
					fBCMuSummary.write(runNumber + "	Down	" + "[++]" + "	" + line[12:21] + "	" + line[39:48] + "	" + line[66:75] + "\n")
				if "BCM d1 [--]:" in line:
					fd1downdown.write(line[12:21] + "\n")
					fd3downdown.write(line[39:48] + "\n")
					fd10downdown.write(line[66:75] + "\n")
					fBCMuSummary.write(runNumber + "	Down	" + "[--]" + "	" + line[12:21] + "	" + line[39:48] + "	" + line[66:75] + "\n")
				if "BCM d1 [+-]:" in line:
					fd1updown.write(line[12:21] + "\n")
					fd3updown.write(line[39:48] + "\n")
					fd10updown.write(line[66:75] + "\n")
					fBCMuSummary.write(runNumber + "	Down	" + "[+-]" + "	" + line[12:21] + "	" + line[39:48] + "	" + line[66:75] + "\n")
				if "BCM d1 [-+]:" in line:
					fd1downup.write(line[12:21] + "\n")
					fd3downup.write(line[39:48] + "\n")
					fd10downup.write(line[66:75] + "\n")
					fBCMuSummary.write(runNumber + "	Down	" + "[-+]" + "	" + line[12:21] + "	" + line[39:48] + "	" + line[66:75] + "\n\n")
					j += 1

	i += 1




print "All done!\n"





















