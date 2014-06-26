#! /usr/bin/env python

# This script will search for all of the HALog entries during the Quasi-Elastic Family of Experiments that ran from April-June, 2009.

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

if (os.path.exists("./all_halog_urls")):os.remove("./all_halog_urls")
fhalog = open("./all_halog_urls","a")
frun = open("./run_number","r")
runnum_list = frun.readlines()
frun.close()

fhalog.write("Beginning list of all HALog entries for E05-102, E05-015, and E08-005.\n")

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
					if (checkURL(halogURL) == 1):
						fhalog.write(halogURL + "\n")
						print "Found one! Adding " + halogURL + " to all_halog_runs"
					halogSecondsInt = halogSecondsInt + 1
				halogMinutesInt = halogMinutesInt + 1
			halogHoursInt = halogHoursInt + 1
		halogDaysInt = halogDaysInt + 1
	halogMonthInt = halogMonthInt + 1
fhalog.close()
