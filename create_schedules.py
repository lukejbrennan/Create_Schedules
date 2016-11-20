#!/usr/bin/env python2.7

from bs4 import BeautifulSoup
import requests
import sys
import re
import os

#Retrieve table row in ClassSearch for each section of given class
def getCourseInfo(department, courseNumber, term):
	department = department.upper()
	table = getClassSearchTable(department, term)
	
	#Fill two dimensional array with info for each section of given class
	sections = []
	for row in table.findAll('tr'):
		cells = row.findAll('td')
		if re.match('' + department + courseNumber, cells[0].text):
			sections.append(cells)

	return sections

def getClassSearchTable(department, term):
	# parsing parameters
	data = {
		'TERM': term,         # will want to vary
		'DIVS': 'A',            
		'CAMPUS': 'M',          #may want to vary
		'SUBJ': department,         #need to include all classes
		'ATTR': '0ANY',
		'CREDIT': 'A'
	} #use a function to create data

	# parsing data
	response = requests.post(url, data=data)
	soup = BeautifulSoup(response.content) #.prettify()

	table = None
	try:
		table = soup.find('table', {'id':'resulttable'}).find('tbody')
	except AttributeError as e:
		print "Error: invalid department: " + department + ". Exiting..."
		sys.exit(1)
	
	return table

#Function to get the most recent term available on ClassSearch
def getMostRecentTerm():
	response = requests.post(url)
	soup = BeautifulSoup(response.content)

	#Find most recent term
	options = soup.find('select', {'name':'TERM'}).findAll('option')

	termNums = []
	for option in options:
		termNums.append(option['value'])
	
	return termNums[0]

def getCorecs(url):
	response = requests.post(url)
	soup = BeautifulSoup(response.content)

	spans = soup.find('table', {'class':'datadisplaytable'}).find('td').findAll('span', {'class', 'fieldlabeltext'})
	for tag in spans:
		if tag.text == "Corequisites:":
			data = soup.find('table', {'class':'datadisplaytable'}).find('td').text
			pattern1 = re.compile('Corequisites:.*Restrictions:', re.DOTALL)
			corecString = pattern1.findall(data)[0]
			pattern2 = re.compile('[a-zA-Z]{2,4} \d{5}')
			classSection = pattern2.findall(corecString)
			
			#Normalize each course number
			corecs = []
			for num in classSection:
				num = num.replace(" ", "")
				corecs.append(num)
			return corecs
	return []


def getComments(url, courseNum):
	response = requests.post(url)
	soup = BeautifulSoup(response.content)

	spans = soup.find('table', {'class':'datadisplaytable'}).find('td').findAll('span', {'class', 'fieldlabeltext'})
	for tag in spans:
		if tag.text == "Comments: ":
			ErrorMessages.append("********** Potential Extraneous Situation: Please check Class Search for " + courseNum + " Comments **********")
	return

def timeToHoursMins(time):
	hour = 0
	meridiem = time[-1]
	splitTime = time[:-1].split(':')
	splitTime = [int(splitTime[0]), int(splitTime[1])]
	minute = splitTime[1]

	if splitTime[0] == 12:
		if meridiem == "A":
			hour = 0
		else:
			hour = 12
	else:
		if meridiem == "A":
			hour = splitTime[0]
		else:
			hour = splitTime[0] + 12

	return (str(hour), str(minute))

#Converts time from ClassSearch into a reasonable format
def fixTime(timeString, Num):
	timeString = re.sub('\s', '', timeString)

	#Change times to hours and minutes
	
	#Account for possible multiple times
	TIM = re.compile("\(\d\)").split(timeString)
	if len(TIM) > 1:
		TIM=TIM[1:]
		ErrorMessages.append("********** Potential Extraneous Situation: Please check Class Search for " + Num + " Times **********")

	for t in TIM:
		times = t.split("-")
		startHour, startMinute = timeToHoursMins(times[1])
		endHour, endMinute = timeToHoursMins(times[2])

	return times[0] + " / " + startHour + " / " + startMinute + " / " + endHour + " / " + endMinute

#Take the entire course number field from ClassSearch and parse it to obtain the section number
def getSectionNumber(courseNumField):
	pattern = re.compile('\s\d\d')
	classSection = pattern.findall(courseNumField)[0]
	return classSection[1:]

def fixProf(profName):
	profName = profName.rstrip()
	profName = profName[::-1]
	profName = profName.rstrip()
	profName = profName[::-1]
	profName = profName.replace("\n", "")
	return profName


#Begin main execution

COURSENUMS = []
url = 'https://class-search.nd.edu/reg/srch/ClassSearchServlet'

#Read from stdin here
if not sys.stdin.isatty(): #User input a file
	for line in sys.stdin:
		line = line.rstrip()
		if line not in COURSENUMS:
			COURSENUMS.append(line)
else: #User is writing to stdin
	print "Please enter the course numbers (e.g. CSE30331) to add, pressing enter between each one. Finish adding by putting EOF on a line by itself and hitting enter."
	line = sys.stdin.readline().rstrip()
	while line != "EOF":
		if line not in COURSENUMS:
			COURSENUMS.append(line)
		line = sys.stdin.readline().rstrip()
	

#Go through and add all sections for each course
f = open('temp.txt', 'w+')
numOfClasses = len(COURSENUMS)
numOfClassesChecked = 0
ErrorMessages = []
TERM = getMostRecentTerm()
for num in COURSENUMS:
	#Make the course number uppercase
	num = num.upper()
	
	#Determine which department the course is in
	dept = ""
	pos = 0
	for char in num:
		if char.isalpha():
			dept += char
			pos += 1
		else:
			break
	
	#Get course number
	courseNum = num[pos:]

	#Get table row from ClassSearch for each subject and loop through them
	addedSection = False
	for section in getCourseInfo(dept, courseNum, TERM):

		#Determine if the class has open spots left
		if section[5].text == "0":
			print "Section " + getSectionNumber(section[0].text) + " of " + num + " could not be added. No open spots."
		else:
			#Call functions to parse/reformat ClassSearch info
			courseName = section[1].text
			crn = section[7].text
			time = fixTime(section[10].text, num)
			classSection = getSectionNumber(section[0].text)
			profName = fixProf(section[9].text)
		
			#Write class info to file
			entry = courseName + " / " + crn + " / " + num + " / " + classSection + " / " + profName + " / " +  time + " | "

			f.write(entry + '\n')
			f.flush()
			print "Section " + getSectionNumber(section[0].text) + " of " + num + " added"
			addedSection = True

	#If a section of the course was added and the given course was input by the user, get the corecs for that course
	if addedSection and numOfClassesChecked < numOfClasses:
		#Parse URL to course page
		table = getClassSearchTable(dept, TERM)
		elem = str(table(text=re.compile(num))[0].parent)
		pattern = re.compile("Servlet(\?[^']+)'")
		result = pattern.findall(elem)[0]
		result = result.replace('&amp;', '&')
		
		#Checking for comments
		getComments(url + result, num)

	
		#Obtain course numbers for corecs from the course page
		COURSENUMS += getCorecs(url + result)
		
	
    	numOfClassesChecked += 1	

f.close()
os.system('./main')

for message in ErrorMessages:
	print message
#suggest taking all class info and put it in a file?
#how to collect all classes (array?)
#pick and choose from what we printing now

