// Driver program for ScheduleCreator

#include "Time.h"
#include "Class.h"
#include "Schedule.h"
#include "ScheduleCreator.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

ScheduleCreator readFile(ScheduleCreator);

int main(){

	// Instantiate ScheduleCreator object
	ScheduleCreator scheduleCreator;

	// Extract class data from temp.txt, create class objects, and add the classes to scheduleCreator
	scheduleCreator = readFile(scheduleCreator);

	// Creates schedules from class objects
	scheduleCreator.createSchedules();

	// Prints list of schedules to the terminal
	scheduleCreator.printScheduleList();

	return 0;
}

ScheduleCreator readFile(ScheduleCreator scheduleCreator) {

	ifstream inFile;
	inFile.open("temp.txt");
	vector<string> data;
	string item, string;
	Time *newTime;
	Class *newClass;

	while(inFile >> item) {
		if(item != "/" && item != "|") { 	// enters when a word is read
			string = string + ' ' + item;
		}
		else {		// enters when a '/' or '|' is read
			string = string.substr(1);
			data.push_back(string);
			string.clear();
			if(item == "|") {		// enters when a '|' is read, indicating the end of data for that class
				newTime = new Time(stoi(data[6]), stoi(data[7]), stoi(data[8]), stoi(data[9]));
				newClass = new Class(data[0], stoi(data[1]), data[2], stoi(data[3]), data[4], data[5], *newTime);
				scheduleCreator.addClass(*newClass);
				delete newTime;
				delete newClass;
				data.clear();
			}
		}
	}

	return scheduleCreator;
}

