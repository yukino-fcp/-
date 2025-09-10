SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))

deviceSys : $(OBJECTS)
	gcc $(OBJECTS) -o $@
%.o : %.c
	gcc -g -c $^

clean :
	rm deviceSys *.o
