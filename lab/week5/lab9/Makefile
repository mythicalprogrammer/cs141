CXX	= g++
CXXFLAGS= -g -W -Wall -ansi -pedantic
PROGRAM	= lab9
OBJS	= graph.o lab9.o

$(PROGRAM): $(OBJS)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *~ *.o $(PROGRAM)

