COMPILER = g++

edit: main.o kbd.o command.o display.o \
       insert.o search.o files.o utils.o
	$(COMPILER) -o edit main.o kbd.o command.o display.o \
		   insert.o search.o files.o utils.o

main.o: main.c defs.h
	$(COMPILER) -c main.c
kbd.o: kbd.c defs.h command.h
	$(COMPILER) -c kbd.c
command.o: command.c defs.h command.h
	$(COMPILER) -c command.c
display.o: display.c defs.h buffer.h
	$(COMPILER) -c display.c
insert.o: insert.c defs.h buffer.h
	$(COMPILER) -c insert.c
search.o: search.c defs.h buffer.h
	$(COMPILER) -c search.c
files.o: files.c defs.h buffer.h command.h
	$(COMPILER) -c files.c
utils.o: utils.c defs.h
	$(COMPILER) -c utils.c
clean:
	rm edit main.o kbd.o command.o display.o \
	   insert.o search.o files.o utils.o