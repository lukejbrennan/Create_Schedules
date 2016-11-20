//Class.h
//Class to represent a school class. Contains information related to scheduling for a specific section of a course

#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include "Time.h"

using namespace std;

class Class{

	public:
		
		//Constructor. Creates object without times. Use set time functions of this class to set times
		Class(string Name = "", int CRN = 0, string CourseNumber = "0", int Section = 0, string Professor = "");
		
		//Alternate constructor to initialize times based on a string
		Class(string Name, int CRN, string CourseNumber, int Section, string Professor, string TimeString, Time classTime);

		//Returns the class's start time on a given day of the week. Numbers 0-4 denote Monday-Friday. Returns -1 if day is out of range
		int getStartTime(int day);

		//Returns the class's end time on a given day of the week. Numbers 0-4 denote Monday-Friday. Returns -1 if day is out of range
		int getEndTime(int day);

		//Returns the courseNumber variable
		string getCourseNumber();

		//Set the start time for the class on a given day of the week. Days 0-4 denote Monday-Friday. startHour must be between 0-23, and startMinute between 0-59.
		void setStartTime(int day, int startHour, int startMinute);

		//Set the end time for the class on a given day of the week. Days 0-4 denote Monday-Friday. endHour must be between 0-23, and endMinute between 0-59.
		void setEndTime(int day, int endHour, int endMinute);

		//Determine if two classes can be taken concurrently. Return 1 if they can be taken concurrently, 0 otherwise.
		int canBeTakenConcurrently(Class newClass);

		//Print the info for each class
		void print();
		
	private:

		//Declare private member variables

		int crn;
		string courseNumber;
		string name;
		int section;
		string profName;
		Time times[5];

};

#endif
