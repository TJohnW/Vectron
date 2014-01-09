#Visual Studio - call with CC=nmake
#G++ = call with CC=g++
FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
LIBS = -lglfw3
OPS = -std=c++11

OBJECTS = Vectron.o Zone.o Grid.o Input.o Screen.o

SRCPATH = src

all: $(OBJECTS)
	g++ $(OPS) $(OBJECTS) -o bin/Vectron $(LIBS) $(FRAMEWORK); \
	rm *.o

Vectron.o: $(SRCPATH)/Vectron.cpp
	g++ $(OPS) -c $(SRCPATH)/Vectron.cpp

Zone.o: $(SRCPATH)/Zone.cpp
	g++ $(OPS) -c $(SRCPATH)/Zone.cpp

Grid.o: $(SRCPATH)/Grid.cpp
	g++ $(OPS) -c $(SRCPATH)/Grid.cpp

Input.o: $(SRCPATH)/Input.cpp
	g++ $(OPS) -c $(SRCPATH)/Input.cpp

Screen.o: $(SRCPATH)/Screen.cpp
	g++ $(OPS) -c $(SRCPATH)/Screen.cpp