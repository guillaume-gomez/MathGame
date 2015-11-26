OPTIONS  = -std=c++11

INCLUDES = -Iinclude

SFGUI_DIR = extlibs/SFGUI-0.3.0



main :
	g++ $(OPTIONS) $(INCLUDES) -o bin/test main.cpp src/*


sfgui :
	cd $(SFGUI_DIR)*; \
	rm -r build; \
	mkdir build; \
	cd build; \
	cmake ../


all : sfgui main

