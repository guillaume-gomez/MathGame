INCLUDES = -Iinclude

all :
	g++ $(INCLUDES) -o bin/test main.cpp src/*