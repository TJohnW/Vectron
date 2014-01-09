FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
LIBS = -lglfw3
OPS = -std=c++11

SRCPATH = src

all: Vectron.o Zone.o Grid.o
	g++ $(OPS) Zone.o Grid.o Vectron.o -o bin/Vectron $(LIBS) $(FRAMEWORK); \
	rm *.o



Vectron.o: $(SRCPATH)/Vectron.cpp
	g++ -c $(SRCPATH)/Vectron.cpp

Zone.o: $(SRCPATH)/Zone.cpp
	g++ -c $(SRCPATH)/Zone.cpp

Grid.o: $(SRCPATH)/Grid.cpp
	g++ -c $(SRCPATH)/Grid.cpp