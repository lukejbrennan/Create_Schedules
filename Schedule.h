// Schedule.h
// Interface for the Schedule class. Contains a single vector to represent a schedule of non-conflicting classes.

#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <iostream>
#include <vector>
#include "Class.h"

class Schedule {

	public:

		Schedule(); // default constructor
		void addClass(Class); // adds a class to schedule
		void removeLastClass(); //Removes the most recently added class
		void print(); // prints the schedule
		Class returnClass(int); // returns a class
		int getSize();	// returns the size of the schedule
		
	private:
		std::vector<Class> schedule; // represents a single schedule of classes
};

#endif
