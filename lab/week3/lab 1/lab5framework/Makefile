CXX	= g++
CXXFLAGS= -g -W -Wall -Werror -ansi -pedantic
PROGRAM	= lab5
OBJS	= lab5.o

$(PROGRAM): $(OBJS)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *~ *.o $(PROGRAM)

