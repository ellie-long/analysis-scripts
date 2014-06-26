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

def checkURL(url):
	p = urlparse(url)
	h = HTTP(p[1])
	h.putrequest('HEAD', p[2])
	h.endheaders()
	if h.getreply()[0] == 200: return 1
	else: return 0
	
fhalog = open("./halog_end_of_run_urls","r")
frun = open("./run_number","r")
runNumList = frun.readlines()
urlList = fhalog.readlines()
fhalog.close()
frun.close()

# vvvvvvv This big block removes old BCM files and opens up clear, new ones
if (os.path.exists("./BCM/bcmu10")): os.remove("./BCM/bcmu10")
fu10 = open("./BCM/bcmu10","a")
fu10.write("This file contains the BCM u1 [0] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmu1++")): os.remove("./BCM/bcmu1++")
fu1upup = open("./BCM/bcmu1++","a")
fu1upup.write("This file contains the BCM u1 [++] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmu1-+")): os.remove("./BCM/bcmu1-+")
fu1downup = open("./BCM/bcmu1-+","a")
fu1downup.write("This file contains the BCM u1 [-+] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmu1+-")): os.remove("./BCM/bcmu1+-")
fu1updown = open("./BCM/bcmu1+-","a")
fu1updown.write("This file contains the BCM u1 [+-] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmu1--")): os.remove("./BCM/bcmu1--")
fu1downdown = open("./BCM/bcmu1--","a")
fu1downdown.write("This file contains the BCM u1 [--] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmu30")): os.remove("./BCM/bcmu30")
fu30 = open("./BCM/bcmu30","a")
fu30.write("This file contains the BCM u1 [0] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmu3++")): os.remove("./BCM/bcmu3++")
fu3upup = open("./BCM/bcmu3++","a")
fu3upup.write("This file contains the BCM u1 [++] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmu3-+")): os.remove("./BCM/bcmu3-+")
fu3downup = open("./BCM/bcmu3-+","a")
fu3downup.write("This file contains the BCM u1 [-+] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmu3+-")): os.remove("./BCM/bcmu3+-")
fu3updown = open("./BCM/bcmu3+-","a")
fu3updown.write("This file contains the BCM u1 [+-] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmu3--")): os.remove("./BCM/bcmu3--")
fu3downdown = open("./BCM/bcmu3--","a")
fu3downdown.write("This file contains the BCM u3 [--] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmu100")): os.remove("./BCM/bcmu100")
fu100 = open("./BCM/bcmu100","a")
fu100.write("This file contains the BCM u10 [0] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmu10++")): os.remove("./BCM/bcmu10++")
fu10upup = open("./BCM/bcmu10++","a")
fu10upup.write("This file contains the BCM u10 [++] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmu10-+")): os.remove("./BCM/bcmu10-+")
fu10downup = open("./BCM/bcmu10-+","a")
fu10downup.write("This file contains the BCM u10 [-+] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmu10+-")): os.remove("./BCM/bcmu10+-")
fu10updown = open("./BCM/bcmu10+-","a")
fu10updown.write("This file contains the BCM u10 [+-] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmu10--")): os.remove("./BCM/bcmu10--")
fu10downdown = open("./BCM/bcmu10--","a")
fu10downdown.write("This file contains the BCM u10 [--] Values based on Run # in run_number\n")

if (os.path.exists("./BCM/bcmd10")): os.remove("./BCM/bcmd10")
fd10 = open("./BCM/bcmd10","a")
fd10.write("This file contains the BCM d1 [0] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmd1++")): os.remove("./BCM/bcmd1++")
fd1upup = open("./BCM/bcmd1++","a")
fd1upup.write("This file contains the BCM d1 [++] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmd1-+")): os.remove("./BCM/bcmd1-+")
fd1downup = open("./BCM/bcmd1-+","a")
fd1downup.write("This file contains the BCM d1 [-+] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmd1+-")): os.remove("./BCM/bcmd1+-")
fd1updown = open("./BCM/bcmd1+-","a")
fd1updown.write("This file contains the BCM d1 [+-] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmd1--")): os.remove("./BCM/bcmd1--")
fd1downdown = open("./BCM/bcmd1--","a")
fd1downdown.write("This file contains the BCM d1 [--] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmd30")): os.remove("./BCM/bcmd30")
fd30 = open("./BCM/bcmd30","a")
fd30.write("This file contains the BCM d1 [0] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmd3++")): os.remove("./BCM/bcmd3++")
fd3upup = open("./BCM/bcmd3++","a")
fd3upup.write("This file contains the BCM d1 [++] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmd3-+")): os.remove("./BCM/bcmd3-+")
fd3downup = open("./BCM/bcmd3-+","a")
fd3downup.write("This file contains the BCM d1 [-+] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmd3+-")): os.remove("./BCM/bcmd3+-")
fd3updown = open("./BCM/bcmd3+-","a")
fd3updown.write("This file contains the BCM d1 [+-] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmd3--")): os.remove("./BCM/bcmd3--")
fd3downdown = open("./BCM/bcmd3--","a")
fd3downdown.write("This file contains the BCM d3 [--] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmd100")): os.remove("./BCM/bcmd100")
fd100 = open("./BCM/bcmd100","a")
fd100.write("This file contains the BCM d10 [0] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmd10++")): os.remove("./BCM/bcmd10++")
fd10upup = open("./BCM/bcmd10++","a")
fd10upup.write("This file contains the BCM d10 [++] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmd10-+")): os.remove("./BCM/bcmd10-+")
fd10downup = open("./BCM/bcmd10-+","a")
fd10downup.write("This file contains the BCM d10 [-+] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmd10+-")): os.remove("./BCM/bcmd10+-")
fd10updown = open("./BCM/bcmd10+-","a")
fd10updown.write("This file contains the BCM d10 [+-] Values based on Run # in run_number\n")
if (os.path.exists("./BCM/bcmd10--")): os.remove("./BCM/bcmd10--")
fd10downdown = open("./BCM/bcmd10--","a")
fd10downdown.write("This file contains the BCM d10 [--] Values based on Run # in run_number\n")



if (os.path.exists("./BCM/_bcm_summary")): os.remove("./BCM/_bcm_summary")
fBCMuSummary = open("./BCM/_bcm_summary","a")
fBCMuSummary.write("Run #	Stream	Pol	BCM 1		BCM 3		BCM 10\n")
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^



i=1
while (i < len(runNumList)):
	halogURL = str(urlList[i])[:67]
	runNumber = str(runNumList[i])[:5]
	print "Processing Run # " + runNumber
	if (checkURL(halogURL) == 1):
		halogEntry = urllib2.urlopen(halogURL)
		for line in halogEntry:
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



	else: 
		print "Error: URL " + halogURL + "for Run # " + runNumber + " does not exist."
		if (runNumber == "22389"):
			halogURL = str(urlList[i-1])[:67]
			halogEntry = urllib2.urlopen(halogURL)
			for line in halogEntry:
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
		print " Moving on to Run # " + str(runNumList[i+1])[:5]
	i += 1


print "All done!\n"





















