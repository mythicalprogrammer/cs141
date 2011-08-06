CXX	= g++
CXXFLAGS= -g -W -Wall -Werror -ansi -pedantic
PROGRAM	= lab4
OBJS	= lab4helper.o lab4.o

$(PROGRAM): $(OBJS)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *~ *.o $(PROGRAM)

