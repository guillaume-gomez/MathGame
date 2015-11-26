OPTIONS  = -std=c++11

INCLUDES = -Iinclude

SFGUI_DIR = extlibs/SFGUI-0.3.0


sfgui :
	cd $(SFGUI_DIR)*; \
	rm -r build; \
	mkdir build; \
	cd build; \
	cmake ../


main :
	g++ $(OPTIONS) $(INCLUDES) -o bin/test main.cpp src/*


all : sfgui main

