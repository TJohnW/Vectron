#Visual Studio - call with CC=nmake
#G++ = call with CC=g++
FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
LIBS = -lglfw3 -lGLEW
OPS = -std=c++11

OBJECTS = Vectron.o Zone.o Input.o Screen.o Aamap.o AamapObject.o Wall.o WallPoint.o Mouse.o ScreenVars.o Shader.o

SRCPATH = src

all: $(OBJECTS)
	g++ $(OPS) $(OBJECTS) -o bin/Vectron $(LIBS) $(FRAMEWORK);

Vectron.o: $(SRCPATH)/Vectron.cpp
	g++ $(OPS) -c $(SRCPATH)/Vectron.cpp

Zone.o: $(SRCPATH)/Zone.cpp
	g++ $(OPS) -c $(SRCPATH)/Zone.cpp

Input.o: $(SRCPATH)/Input.cpp
	g++ $(OPS) -c $(SRCPATH)/Input.cpp

Screen.o: $(SRCPATH)/Screen.cpp
	g++ $(OPS) -c $(SRCPATH)/Screen.cpp

Aamap.o: $(SRCPATH)/Aamap.cpp
	g++ $(OPS) -c $(SRCPATH)/Aamap.cpp

AamapObject.o: $(SRCPATH)/AamapObject.cpp
	g++ $(OPS) -c $(SRCPATH)/AamapObject.cpp

Wall.o: $(SRCPATH)/Wall.cpp
	g++ $(OPS) -c $(SRCPATH)/Wall.cpp

WallPoint.o: $(SRCPATH)/WallPoint.cpp
	g++ $(OPS) -c $(SRCPATH)/WallPoint.cpp

Mouse.o: $(SRCPATH)/Mouse.cpp
	g++ $(OPS) -c $(SRCPATH)/Mouse.cpp

ScreenVars.o: $(SRCPATH)/ScreenVars.cpp
	g++ $(OPS) -c $(SRCPATH)/ScreenVars.cpp

Shader.o: $(SRCPATH)/Shader.cpp
	g++ $(OPS) -c $(SRCPATH)/Shader.cpp


