CXX	= g++
CXXFLAGS= -g -W -Wall -Werror -ansi -pedantic
PROGRAM	= lab3
OBJS	= lab3helper.o lab3.o

$(PROGRAM): $(OBJS)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *~ *.o $(PROGRAM)

