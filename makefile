OPTIONS  = -std=c++11

INCLUDES = -Iinclude

SFGUI_DIR = extlibs/SFGUI-0.3.0

SFML_DEPENDENCIES = freetype2 libjpeg-turbo libx11 libxrandr libxcb xcb-util \
					xcb-util-image mesa flac libogg libvorbis openal


main :
	g++ $(OPTIONS) $(INCLUDES) -o bin/test main.cpp src/*


sfgui :
	cd $(SFGUI_DIR)*; \
	rm -r build; \
	mkdir build; \
	cd build; \
	cmake ../

sfml :
	sudo pacman -S $(SFML_DEPENDENCIES)

all : sfgui main




