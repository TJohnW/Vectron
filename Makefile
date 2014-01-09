FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
LIBS = -lglfw3

all: Vectron.o Zone.o
	g++ Zone.o Vectron.o -o Vectron $(LIBS) $(FRAMEWORK)


Vectron.o: Vectron.cpp
	g++ -c Vectron.cpp

Zone.o: Zone.cpp
	g++ -c Zone.cpp