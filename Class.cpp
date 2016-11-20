//Class.cpp
//Implementation for Class class, which is used to represent a section of a course.

#include <iostream>
#include <string>
#include "Time.h"
#include "Class.h"

using namespace std;

//Constructor. Creates object without times. Use set time functions of this class to set times
Class::Class(string Name, int CRN, string CourseNumber, int Section, string Professor){

	name = Name;
	crn = CRN;
	courseNumber = CourseNumber;
	section = Section;
	profName = Professor;

}

//Alternate constructor to initialize times based on a string
Class::Class(string Name, int CRN, string CourseNumber, int Section, string Professor, string TimeString, Time classTime){

	name = Name;
	crn = CRN;
	courseNumber = CourseNumber;
	section = Section;
	profName = Professor;

	for(int i = 0; i < TimeString.length(); i++){
		if(TimeString[i] == 'M'){
			times[0] = classTime;
		}
		else if(TimeString[i] == 'T'){
			times[1] = classTime;
		}
		else if(TimeString[i] == 'W'){
			times[2] = classTime;
		}
		else if(TimeString[i] == 'R'){
			times[3] = classTime;
		}
		else if(TimeString[i] == 'F'){
			times[4] = classTime;
		}
	}

}

//Returns the class's start time on a given day of the week. Numbers 0-4 denote Monday-Friday
int Class::getStartTime(int day){

	if(day < 0 || day > 4){
		return -1;
	}

	return times[day].getStartTime();

}

//Returns the class's end time on a given day of the week. Numbers 0-4 denote Monday-Friday
int Class::getEndTime(int day){

	if(day < 0 || day > 4){
		return -1;
	}

	return times[day].getEndTime();

}

//Returns the courseNumber variable
string Class::getCourseNumber(){

	return courseNumber;

}

//Set the start time for the class on a given day of the week. Days 0-4 denote Monday-Friday. startHour must be between 0-23, and startMinute between 0-59.
void Class::setStartTime(int day, int startHour, int startMinute){

	if(day < 0 || day > 4){
		return;
	}

	times[day].setStartTime(startHour, startMinute);

}

//Set the end time for the class on a given day of the week. Days 0-4 denote Monday-Friday. endHour must be between 0-23, and endMinute between 0-59.
void Class::setEndTime(int day, int endHour, int endMinute){

	if(day < 0 || day > 4){
		return;
	}

	times[day].setEndTime(endHour, endMinute);

}

//Determine if two classes can be taken concurrently. Return 1 if they can be taken concurrently, 0 otherwise.
int Class::canBeTakenConcurrently(Class newClass){

	//Loop through each day and make sure that the current class doesnt interfere with the new class on any day
	for(int day = 0; day < 5; day++){
		if(getStartTime(day) == 0 && getEndTime(day) == 0 && newClass.getStartTime(day) == 0 && newClass.getEndTime(day) == 0){
			continue;
		}

		if(newClass.getStartTime(day) >= getStartTime(day) && newClass.getStartTime(day) <= getEndTime(day)){
			return 0;
		}
		else if(newClass.getEndTime(day) >= getStartTime(day) && newClass.getEndTime(day) <= getEndTime(day)){
			return 0;;
		}
	}

	return 1;

}

//Print the info for each class
void Class::print(){

	cout << "Course Name: " << name << endl;
	cout << "CRN: " << crn << endl;
	cout << courseNumber << "-" << section << endl;
	cout << "Professor: " << profName << endl;

	/*cout << "Monday Time: " << times[0].getStartTime24Hour() << " - " << times[0].getEndTime24Hour() << endl;
	cout << "Tuesday Time: " << times[1].getStartTime24Hour() << " - " << times[1].getEndTime24Hour() << endl;
	cout << "Wednesday Time: " << times[2].getStartTime24Hour() << " - " << times[2].getEndTime24Hour() << endl;
	cout << "Thursday Time: " << times[3].getStartTime24Hour() << " - " << times[3].getEndTime24Hour() << endl;
	cout << "Friday Time: " << times[4].getStartTime24Hour() << " - " << times[4].getEndTime24Hour() << endl;*/

	cout << "Monday Time: " << times[0].getStartTime12Hour() << " - " << times[0].getEndTime12Hour() << endl;
	cout << "Tuesday Time: " << times[1].getStartTime12Hour() << " - " << times[1].getEndTime12Hour() << endl;
	cout << "Wednesday Time: " << times[2].getStartTime12Hour() << " - " << times[2].getEndTime12Hour() << endl;
	cout << "Thursday Time: " << times[3].getStartTime12Hour() << " - " << times[3].getEndTime12Hour() << endl;
	cout << "Friday Time: " << times[4].getStartTime12Hour() << " - " << times[4].getEndTime12Hour() << endl;

}
