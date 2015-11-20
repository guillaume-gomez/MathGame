OPTIONS  = -std=c++11

INCLUDES = -Iinclude

all :
	g++ $(OPTIONS) $(INCLUDES) -o bin/test main.cpp src/*


