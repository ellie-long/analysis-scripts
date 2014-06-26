#! /usr/bin/env python

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

os.remove("./halog_urls")
fhalog = open("./halog_urls","a")
frun = open("./run_number","r")
runnum_list = frun.readlines()
frun.close()

fhalog.write("Beginning list of HALog End-of-Run URLs that correspond to runs in run_number\n")

halogPrefix = "http://www.jlab.org/~adaq/halog/html/"
halogMonthPrefix = "0904_archive/0904"
halogTime1 = 30042126
#halogTime = 30045757
halogTime = ""

halogDaysInt = 30
halogDays = str(halogDaysInt)

halogHoursInt = 0
halogHoursInt = 4
while (halogHoursInt < 24):
	if (halogHoursInt < 10): halogHours = "0" + str(halogHoursInt)
	else: halogHours = str(halogHoursInt)
	halogMinutesInt = 0
	halogMinutesInt = 20
	while (halogMinutesInt < 60):
		if (halogMinutesInt < 10): halogMinutes = "0" + str(halogMinutesInt)
		else: halogMinutes = str(halogMinutesInt)
		halogSecondsInt = 0
		while (halogSecondsInt < 60):
			if (halogSecondsInt < 10): halogSeconds = "0" + str(halogSecondsInt)
			else: halogSeconds = str(halogSecondsInt)
			halogTime = halogDays + halogHours + halogMinutes + halogSeconds
			halogURL = halogPrefix + halogMonthPrefix + halogDays + halogHours + halogMinutes + halogSeconds + ".html"
			print "Processing URL: " + halogURL
			# ------------------------ START NESTED PROGRAM --------------------------- #
			if (checkURL(halogURL) == 1):
				a = 0
				while (a < len(runnum_list)):
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
			halogSecondsInt = halogSecondsInt + 1
		halogMinutesInt = halogMinutesInt + 1
	halogHoursInt = halogHoursInt + 1

fhalog.close()
