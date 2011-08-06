CXX	= g++
CXXFLAGS= -O3 -W -Wall -Werror -ansi -pedantic
LIBS	= -lgmp
PROGRAM	= factoring
OBJS	= Integer.o factoring.o

$(PROGRAM): $(OBJS)
	$(CXX) $^ $(LIBS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *~ *.o $(PROGRAM)

