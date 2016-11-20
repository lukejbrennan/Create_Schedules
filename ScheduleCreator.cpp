// ScheduleCreator.cpp
// Member functions for the Schedule class

#include "ScheduleCreator.h"
using namespace std;

// empty default constructor
ScheduleCreator::ScheduleCreator() {


}

void ScheduleCreator::addClass(Class newClass) {

	int i;

	// determines if the course is already present in the schedule
	for(i=0; i<classList.size(); i++) {
		if(!newClass.getCourseNumber().compare(classList[i][0].getCourseNumber())) {
			classList[i].push_back(newClass); // adds the class as another section of the course if another section of the same course has already been added
			return;
		}
	}

	// if the course number for this class does NOT match a course number already in the schedule
	// add a new course to the schedule and add the new class
	vector<Class> newCourse;
	classList.push_back(newCourse);
	classList[classList.size()-1].push_back(newClass);
}

void ScheduleCreator::addSchedule(Schedule newSchedule) {

	scheduleList.push_back(newSchedule);
}

void ScheduleCreator::printScheduleList() {

	int i;

	for(i=0; i<scheduleList.size(); i++) {
		cout <<endl << "           Schedule" << i+1 <<endl;
		scheduleList[i].print(); // calls the print member function from the Schedule class
	}
}

void ScheduleCreator::createSchedules(){

	Schedule newSchedule;		// creates a new schedule
	createSchedules(newSchedule);	// adds classes to schedule
}

void ScheduleCreator::createSchedules(Schedule newSchedule){

	int nCourses  = newSchedule.getSize();	// current schedule size

	if (classList.size() == nCourses){			// BASE CASE // if the working sched has one instance of every course

		scheduleList.push_back(newSchedule);	// add it to list of possible schedules
		return;
	}

	for ( int section=0; section<classList[nCourses].size(); section++ ){	// iterate through sections of a course
		int canBeAdded = 1;	// compatibility check
		for (int classIndex=0; classIndex<nCourses; classIndex++){ // iterate through courses
			if (!classList[nCourses][section].canBeTakenConcurrently(newSchedule.returnClass(classIndex))){ // if section cant be added
				canBeAdded = 0;
				break;
			}
		}
		if (canBeAdded){	// if section can be added
			newSchedule.addClass(classList[nCourses][section]); // add class to sched
			createSchedules(newSchedule);
			newSchedule.removeLastClass();
		}
	}
}

