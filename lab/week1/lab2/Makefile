CXX	= g++
CXXFLAGS= -g -O3 -W -Wall -Werror -ansi -pedantic
LIBS	= -lgmp
PROGRAM	= lab2
OBJS	= Integer.o lab2.o

$(PROGRAM): $(OBJS)
	$(CXX) $^ $(LIBS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *~ *.o $(PROGRAM)

