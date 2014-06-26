#!/usr/bin/env python2.3
#
#  get_start_or_run_urls.py
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
halogFile = "./all_halog_urls"
runNumFile = "./vert_rhrs_runs"
urlFile = "./start_urls_r"

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
if (os.path.exists(urlFile)): os.remove(urlFile)
fSummary = open(urlFile,"a")
fSummary.write("HALog URLs for Runs found in " + runNumFile + "\n")
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
	if (runNumber == "20466"):
		fSummary.write("No Start of Run for Run # 20466\n")
		j += 1
	if (checkURL(halogURL) == 1):
		print "Processing HALog URL " + halogURL
		print "	Looking for Run # " + runNumber
		try: halogEntry = urllib2.urlopen(halogURL)
		except: None
		startrun = 0
		for line in halogEntry:
			if "keyword=Start_Run_" in line:
				if (line[18:23] == runNumber):
					startrun = 1
					print "Found Run # " + runNumber + " Start of Run!  Processing...\n"
					fSummary.write(halogURL + "\n")
					j += 1
					if (j == runListLength):
						i = haloglength
	i += 1
	
print "All done!\n"



