all: main

main: Time.o Class.o ScheduleCreator.o Schedule.o main.o
	g++ -std=c++11 -static-libstdc++ -o main $^

%.o: %.cpp
	g++ -std=c++11 -c -o $@ $^

clean:
	rm -f *.o main
