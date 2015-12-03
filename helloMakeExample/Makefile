TARGET = helloMake

OBJDIR = o

# all : main.cpp
# 	g++ -o $(TARGET) main.cpp src/*

# .ONESHELL: o/main.o
# o/main.o: main.cpp
# 	@startTime=$$(date +'%s')

# 	mkdir o
# 	cd o
# 	g++ -c ../main.cpp

# 	echo 'build time : '$$(( $$(date +'%s') - $$startTime ))' sec'


$(TARGET): Objects
	g++ -o $(TARGET) o/*

.PHONY: Objects
Objects: main src

.PHONY: src
src: o/Ord.o


.PHONY: main
main: o/main.o


clean:
	rm -f $(TARGET)
	rm -rf o


.ONESHELL: o/%.o
o/%.o: %.cpp
	mkdir o
	cd o
	g++ -c ../$<



.ONESHELL: o/src/%.o
o/%.o: src/%.cpp
	mkdir o
	cd o
	g++ -c ../$<

