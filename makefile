OPTIONS = -std=c++11

SFGUI_DIR = extlibs/SFGUI-0.3.0

SFML_DIR = extlibs/SFML

THOR_DIR = extlibs/Thor

INCLUDES = -I../include -I../$(SFGUI_DIR)/include -I../$(THOR_DIR)/include -I../$(THOR_DIR)/extlibs/aurora/include

SFML_DEPENDENCIES = freetype2 libjpeg-turbo libx11 libxrandr libxcb xcb-util \
					xcb-util-image mesa flac libogg libvorbis openal

define buildExtLib =
cd $(1); \
rm -r build; \
mkdir build; \
cd build; \
cmake ..; \
make $(2)
endef

define cleanExtLib =
@if [ -d $(1)/build ]; \
then \
	echo rm $(1)/build ;\
	cd $(1); \
	rm -r build; \
fi
endef


main:
	rm -r o; \
	mkdir o; \
	cd o; \
	g++ $(OPTIONS) $(INCLUDES) -c ../main.cpp ../src/*



sfgui:
	$(call buildExtLib, $(SFGUI_DIR), sfgui)

sfml:
	$(call buildExtLib, $(SFML_DIR), all)

thor:
	$(call buildExtLib, $(THOR_DIR), thor)


extLibs: sfml sfgui thor



all: extLibs main



clean:
	$(call cleanExtLib, $(SFML_DIR))
	$(call cleanExtLib, $(SFGUI_DIR))
	$(call cleanExtLib, $(THOR_DIR))


