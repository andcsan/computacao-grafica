CXX = g++
CXXFLAGS = -g -Wall
LFLAGS = -lglut -lGL -lGLU

all: main.o
	$(CXX) -o main.out main.o $(CC_FLAGS) $(LFLAGS)

main.o: main.cpp
	$(CXX) -c main.cpp $(CC_FLAGS)

clean:
	rm -rf *.o *~ main.out
