FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
LIBS = -lglfw3

all: Vectron.o
	g++ Vectron.o -o Vectron $(LIBS) $(FRAMEWORK)

Vectron.o: Vectron.cpp
	g++ -c Vectron.cpp