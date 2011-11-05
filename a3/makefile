
SOURCES = main.c \
          draw.c \
          camera.c \
          utils.c

CFLAGS  = `sdl-config --cflags` -D_REENTRANT -Wall
LDFLAGS = `sdl-config --libs` -lopengl32 -lglu32

OBJECTS = $(SOURCES:%.c=%.o)

all : Aufgabe3

Aufgabe3 : $(OBJECTS)
	g++ -o $@ $(OBJECTS) $(LDFLAGS)

%.o : %.c
	g++ $(CFLAGS) -c $<

clean :
	rm *.o

build : clean all

