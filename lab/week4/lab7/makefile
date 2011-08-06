all:pair

point.o: point.cpp point.h
	g++ -c -w point.cpp
pair.o: pair.cpp pair.h
	g++ -c -w pair.cpp
Main.o: Main.cpp
	g++ -c -w Main.cpp
pair: point.o pair.o Main.o
	g++ point.o pair.o Main.o -o pair

clean:
	rm -rf *.o
	rm -rf pair
	rm -rf *~
