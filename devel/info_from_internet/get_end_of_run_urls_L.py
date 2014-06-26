#! /usr/bin/env python

# This script will take run numbers from the file "./run_number_L" and put their HALog End-of-Run URLs into "halog_end_of_run_urls_L"

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

os.remove("./halog_end_of_run_urls_L")
fhalog = open("./halog_end_of_run_urls_L","a")
frun = open("./run_number_L","r")
runnum_list = frun.readlines()
frun.close()

fhalog.write("Beginning list of HALog End-of-Run URLs that correspond to runs in run_number_L\n")

halogPrefix = "http://www.jlab.org/~adaq/halog/html/"
halogTime = ""

halogMonthInt = 4
while (halogMonthInt < 7):
	if (halogMonthInt == 4):
		halogMonthPrefix="0904_archive/0904"
		maxdays = 30
	if (halogMonthInt == 5):
		halogMonthPrefix="0905_archive/0905"
		maxdays = 31
	if (halogMonthInt == 6):
		halogMonthPrefix="0906_archive/0906"
		maxdays = 18 
	halogDaysInt = 0
	while (halogDaysInt < (maxdays + 1)):
		if (halogDaysInt < 10): halogDays = "0" + str(halogDaysInt)
		else: halogDays = str(halogDaysInt)
		halogHoursInt = 0
		while (halogHoursInt < 24):
			if (halogHoursInt < 10): halogHours = "0" + str(halogHoursInt)
			else: halogHours = str(halogHoursInt)
			halogMinutesInt = 0
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
						a = 1
						while (a < (len(runnum_list))):
							run_number = str(int(runnum_list[a]))
							endOfRunLine = ""
							print "a = " +str(a)
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
		halogDaysInt = halogDaysInt + 1
	halogMonthInt = halogMonthInt + 1
fhalog.close()
