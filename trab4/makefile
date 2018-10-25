DEBUG_FLAGS = -g -Wall
LINKER_FLAGS = -lglut -lGLU -lm -lGL

all: trab4

trab4:  globals.h vector.o trab4.o jarvis.o
	g++ -o trab4 vector.o jarvis.o trab4.o globals.h $(LINKER_FLAGS) $(DEBUG_FLAGS)

jarvis.o: jarvis.h vector.h globals.h

vector.o: vector.h

trab4.o: vector.h globals.h