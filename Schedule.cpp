// Schedule.cpp
// member functions for the Schedule class

#include "Schedule.h"
using namespace std;

Schedule::Schedule() {


}

void Schedule::addClass(Class newClass) {

	int i;

	// logic to ensure that the new class is distinct from, and does not overlap with, the others in the schedule
	for(i=0; i<schedule.size(); i++) {
		if(newClass.getCourseNumber()==schedule[i].getCourseNumber() || !schedule[i].canBeTakenConcurrently(newClass))
			return; // do not add newClass
	}

	// adds the class to the schedule if the classes are different and the times do not overlap
	schedule.push_back(newClass);
}

//Function to remove the most recently added class from the schedule
void Schedule::removeLastClass(){

	//Remove last class
	schedule.pop_back();

}

void Schedule::print() {

	int i;

	// Formatting output for a printed schedule
	cout << "==================================================" << endl;
	for(i=0; i<schedule.size(); i++) {
		schedule[i].print(); // call to Class::print()
		if(i<schedule.size()-1) {
			cout << "----------------------------------------------" << endl;
		}
	}
	cout << "==================================================" << endl;
}

Class Schedule::returnClass(int index){
	return schedule[index];
}

int Schedule::getSize(){
	return schedule.size();
}
