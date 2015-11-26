OPTIONS  = -std=c++11

INCLUDES = -Iinclude

SFGUI_DIR = extlibs/SFGUI-0.3.0

SFML_DIR = extlibs/SFML

SFML_DEPENDENCIES = freetype2 libjpeg-turbo libx11 libxrandr libxcb xcb-util \
					xcb-util-image mesa flac libogg libvorbis openal

define buildExtLib =
cd $(1); \
rm -r build; \
mkdir build; \
cd build; \
cmake ..
endef


main :
	g++ $(OPTIONS) $(INCLUDES) -o bin/test main.cpp src/*



sfgui :
	$(call buildExtLib, $(SFGUI_DIR))

sfml :
	$(call buildExtLib, $(SFML_DIR))



extLibs : sfml sfgui



all : extLibs main

clean :



