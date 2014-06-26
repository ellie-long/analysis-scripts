#! /usr/bin/env python

# This script will take run numbers from the file "./run_number" and put their HALog End-of-Run URLs into "halog_end_of_run_urls"

import urllib2
import os
from httplib import HTTP
from urlparse import urlparse

def checkURL(url):
	p = urlparse(url)
	h = HTTP(p[1])
	h.putrequest('HEAD', p[2])
	h.endheaders()
	if h.getreply()[0] == 200: return 1
	else: return 0

if (os.path.exists("./halog_end_of_run_urls")):os.remove("./halog_end_of_run_urls")
fhalog = open("./halog_end_of_run_urls","a")
fhalogURLs = open("../all_halog_urls","r")
halogURL_list = fhalogURLs.readlines()
frun = open("../run_number","r")
runnum_list = frun.readlines()
frun.close()
fhalogURLs.close()

fhalog.write("Beginning list of HALog End-of-Run URLs that correspond to runs in run_number\n")

i = 1
while (i < (len(halogURL_list))):
	halogURL = str(halogURL_list[i])
	print "Processing URL: " + halogURL
	# ------------------------ START NESTED PROGRAM --------------------------- #
	if (checkURL(halogURL) == 1):
		a = 1
		while (a < (len(runnum_list))):
			run_number = str(int(runnum_list[a]))
			endOfRunLine = ""
			halogEntry = urllib2.urlopen(halogURL)
			for line in halogEntry:
	#		for line in urllib2.urlopen(halogURL):
				if ("End_of_Run_") in line:
					endOfRunLine = line
			if ( run_number) in endOfRunLine:
				isEndOfRun = True
			else:
				isEndOfRun = False
	#		print "isEndOfRun = " + str(isEndOfRun) + " for run # " + run_number
			if isEndOfRun:
				halogList = [run_number, halogURL]
				known =  halogURL + " is the end of run file for run # " + run_number
				print known
				fhalog.write(halogURL + "\n")
	#		else:
	#			print halogURL + " is NOT the end of run file for run # " + run_number
			a = a + 1
	#---------------------------- END NESTED PROGRAM ------------------------------ #
	i = i + 1
fhalog.close()
