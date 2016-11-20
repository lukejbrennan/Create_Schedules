//Time.h
//Class to represent an event with a start time and an end time, such as a class.

#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>

using namespace std;

class Time{

	public:

		//Constructor for Time object. hours go from 0-23, minutes go from 0-59
		Time(int startHour = 0, int startMinute = 0, int endHour = 0, int endMinute = 0);

		//Return startTime, the time in minutes from 12:00 AM to the start of the event
		int getStartTime();

		//Return endTime, the time in minutes from 12:00 AM to the end of the event
		int getEndTime();

		//Return startTime in 24-hour format (e.g. 13:30 for 1:30 PM)
		string getStartTime24Hour();

		//Return endTime in 24-hour format (e.g. 13:30 for 1:30 PM)
		string getEndTime24Hour();

		//Return startTime in 12-hour format (e.g. 1:30 PM)
		string getStartTime12Hour();

		//Return endTime in 12-hour format (e.g. 1:30 PM)
		string getEndTime12Hour();

		//Set the start time for the event. startHour goes from 0-23, and startMinute goes from 0-59
		void setStartTime(int startHour, int startMinute);

		//Set the end time for the event. endHour goes from 0-23, and endMinute goes from 0-59
		void setEndTime(int endHour, int endMinute);


	private:

		//Declare private member variables

		//Each time variable is stored as the number of minutes from 12:00 AM on a given day
		int startTime;
		int endTime;

};

#endif
