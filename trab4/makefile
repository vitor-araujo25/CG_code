DEBUG_FLAGS = -g -Wall
LINKER_FLAGS = -lglut -lGLU -lm -lGL

all: trab4

trab4:  globals.h vector.o trab4.o
	g++ -o trab4 vector.o trab4.o globals.h $(LINKER_FLAGS) $(DEBUG_FLAGS)

vector.o: vector.h

trab4.o: vector.h globals.h