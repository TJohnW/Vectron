#Visual Studio - call with CC=nmake
#G++ = call with CC=g++
FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
LIBS = -lglfw3
OPS = -std=c++11

SRCPATH = src

all: Vectron.o Zone.o Grid.o
	g++ $(OPS) Zone.o Grid.o Vectron.o -o bin/Vectron $(LIBS) $(FRAMEWORK); \
	rm *.o



Vectron.o: $(SRCPATH)/Vectron.cpp
	g++ $(OPS) -c $(SRCPATH)/Vectron.cpp

Zone.o: $(SRCPATH)/Zone.cpp
	g++ $(OPS) -c $(SRCPATH)/Zone.cpp

Grid.o: $(SRCPATH)/Grid.cpp
	g++ $(OPS) -c $(SRCPATH)/Grid.cpp
