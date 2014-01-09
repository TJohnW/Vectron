FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
LIBS = -lglfw3
OPS = -std=c++11

all: Vectron.o Zone.o Grid.o
	g++ $(OPS) Zone.o Grid.o Vectron.o -o Vectron $(LIBS) $(FRAMEWORK)


Vectron.o: Vectron.cpp
	g++ -c Vectron.cpp

Zone.o: Zone.cpp
	g++ -c Zone.cpp

Grid.o: Grid.cpp
	g++ -c Grid.cpp