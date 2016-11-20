# User Manual: Schedule Builder #
## Luke Brennan, Sarah Drumm, Cameron Smick, Ryan Smick ##

To run create_schedules.py, users must have access to a python version older than python 3, preferably python 2.7. Additionally, their python distribution must include the BeautifulSoup and requests packages. The makefile compiles the C++ code with the -static-libstdc++ flag, allowing us to use a string to int function in main.

To run the Schedule Builder, a user must have access to all files present in the ClassScheduler repository on Bitbucket. The Makefile can be executed using the command *$ make*, at which point the user must simply run *$ create_schedules.py*.

Once the user runs the program, they can redirect input to a file of course numbers if they want, otherwise, the program will ask them to enter course numbers. After the user enters the course numbers, the python script scrapes Notre Dame’s ClassSearch website, finds each section of the given courses, finds each section of the corequisites for those courses, and outputs information about all of those to a file temp.txt. The script will then run main.cpp, which reads in the temp.txt file, creates objects representing each class section, and builds the possible schedules based on those courses. Finally, the possible schedules are output to the screen.

Thus, the user only needs to enter course numbers for the classes that they want to take, and the web scraper and schedule creation functions handle all of the work.

### Known Bugs ###
* If ClassSearch includes two or more distinct times in the time field for a class (which occurs infrequently), our program can’t handle it. We included a try-except to catch it and print an error message. The program includes the class using only the last time in the list, and then moves on to the next class.
* If certain sections of a course require that you take a certain section of the corequisite course (e.g. MATH10550), our program doesn’t take that into account. It will create schedules containing any of the sections of the corequisite course and not just those that are paired with that section of the main course.