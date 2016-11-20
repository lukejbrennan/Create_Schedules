// ScheduleCreator.h
// Interface for our ScheduleCreator class. Composed of Class objects to store all of the possible sections of the courses the student would like to take

#ifndef SCHEDULECREATOR_H
#define SCHEDULECREATOR_H

#include <iostream>
#include <vector>
#include "Class.h"
#include "Schedule.h"

class ScheduleCreator {

	public:

		ScheduleCreator(); // default constructor
		void addClass(Class); // adds a Class object to the classList
		void addSchedule(Schedule); // adds a Schedule object to the scheduleList
		void printScheduleList(); // prints scheduleList
		void createSchedules(Schedule); // creates possible schedules based on comprehensive scheduleList
		void createSchedules();

	private:

		std::vector<std::vector<Class> > classList; // 2D vector of Class objects. First dimension represents a different course, second represents different sections fo that course.
													// stores all the sections of all the classes that the user would like to register for 
		std::vector<Schedule> scheduleList; // vector of schedule objects. All of the possible schedules that the user could choose (final product)
};

#endif
