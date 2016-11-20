//Time.cpp
//Implementation for Time class

#include <iostream>
#include <string>
#include <sstream>
#include "Time.h"

using namespace std;

//Constructor for Time object. hours go from 0-23, minutes go from 0-59
Time::Time(int startHour, int startMinute, int endHour, int endMinute){

	setStartTime(startHour, startMinute);
	setEndTime(endHour, endMinute);

}

//Return startTime, the time in minutes from 12:00 AM to the start of the event
int Time::getStartTime(){

	return startTime;

}

//Return endTime, the time in minutes from 12:00 AM to the end of the event
int Time::getEndTime(){

	return endTime;

}

//Return startTime in 24-hour format (e.g. 13:30 for 1:30 PM)
string Time::getStartTime24Hour(){

	std::stringstream sstm;
	sstm << startTime / 60 << ":";
	if(startTime % 60 > 9){
		sstm << startTime % 60;
	}
	else{
		sstm << "0" << startTime % 60;
	}
	return sstm.str();

}

//Return endTime in 24-hour format (e.g. 13:30 for 1:30 PM)
string Time::getEndTime24Hour(){

	std::stringstream sstm;
	sstm << endTime / 60 << ":";
	if(endTime % 60 > 9){
		sstm << endTime % 60;
	}
	else{
		sstm << "0" << endTime % 60;
	}
	return sstm.str();

}

//Return startTime in 12-hour format (e.g. 1:30 PM)
string Time::getStartTime12Hour(){

	if (startTime == 0 && endTime == 0){
		return "N/A";
	}

	std::stringstream sstm;

	//Add hour to string stream
	if (startTime < 60){ //12 AM
		sstm << 12;
	}
	else if(startTime < 780){ //Between 1 AM and 12 PM
		sstm << startTime / 60;
	}
	else{
		sstm << startTime / 60 - 12;
	}

	sstm << ":";

	//Add minute to string stream
	int minute = startTime % 60;
	if (minute < 10){
		sstm << "0" << minute;
	}
	else{
		sstm << minute;
	}

	sstm << " ";	

	//Add meridiem to string stream
	if (startTime >= 720){
		sstm << "PM";
	}
	else{
		sstm << "AM";
	}

	return sstm.str();

}

//Return endTime in 12-hour format (e.g. 1:30 PM)
string Time::getEndTime12Hour(){

	if (startTime == 0 && endTime == 0){
		return "N/A";
	}

	std::stringstream sstm;

	//Add hour to string stream
	if (endTime < 60){ //12 AM
		sstm << 12;
	}
	else if(endTime < 780){ //Between 1 AM and 12 PM
		sstm << endTime / 60;
	}
	else{
		sstm << endTime / 60 - 12;
	}

	sstm << ":";

	//Add minute to string stream
	int minute = endTime % 60;
	if (minute < 10){
		sstm << "0" << minute;
	}
	else{
		sstm << minute;
	}

	sstm << " ";	

	//Add meridiem to string stream
	if (endTime >= 720){
		sstm << "PM";
	}
	else{
		sstm << "AM";
	}

	return sstm.str();

}

//Set the start time for the event. startHour goes from 0-23, and startMinute goes from 0-59
void Time::setStartTime(int startHour, int startMinute){

	startTime = (startHour % 24) * 60 + (startMinute % 60);

}

//Set the end time for the event. endHour goes from 0-23, and endMinute goes from 0-59
void Time::setEndTime(int endHour, int endMinute){

	endTime = (endHour % 24) * 60 + (endMinute % 60);

}
