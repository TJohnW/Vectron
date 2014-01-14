#Visual Studio - call with CC=nmake
#G++ = call with CC=g++
FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
LIBS = -lglfw3 -lGLEW
OPS = -std=c++11

OBJECTS = main.o Program.o Shader.o Helper.o
SRCPATH = source

all: $(OBJECTS)
	g++ $(OPS) $(OBJECTS) -o bin/Main $(LIBS) $(FRAMEWORK);

main.o: $(SRCPATH)/main.cpp
	g++ $(OPS) -c $(SRCPATH)/main.cpp

Program.o: $(SRCPATH)/Program.cpp
	g++ $(OPS) -c $(SRCPATH)/Program.cpp

Shader.o: $(SRCPATH)/Shader.cpp
	g++ $(OPS) -c $(SRCPATH)/Shader.cpp

Helper.o: $(SRCPATH)/Helper.cpp
	g++ $(OPS) -c $(SRCPATH)/Helper.cpp

