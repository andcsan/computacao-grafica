CXX = g++
CXXFLAGS = -g -Wall
LFLAGS = -lglut -lGL -lGLU

all: main.o relogio.o
	$(CXX) -o main.out main.o relogio.o $(CC_FLAGS) $(LFLAGS)

main.o: main.cpp
	$(CXX) -c main.cpp $(CC_FLAGS)

relogio.o: relogio.cpp relogio.h
	$(CXX) -c relogio.cpp $(CC_FLAGS)

clean:
	rm -rf *.o *~ main.out
