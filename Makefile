#Visual Studio - call with CC=nmake
#G++ = call with CC=g++
FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
LIBS = -lglfw3
OPS = -std=c++11

all: Vectron.o Zone.o Grid.o
	$(CC) $(OPS) Zone.o Grid.o Vectron.o -o Vectron $(LIBS) $(FRAMEWORK)

Vectron.o: Vectron.cpp
	$(CC) -c Vectron.cpp

Zone.o: Zone.cpp
	$(CC) -c Zone.cpp

Grid.o: Grid.cpp
	$(CC) -c Grid.cpp
	
clean:
	rm *.o