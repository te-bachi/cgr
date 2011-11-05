
SOURCES = main.c \
          draw.c \
          camera.c \
          drawShip.c \
          utils.c

CFLAGS  = `sdl-config --cflags` -D_REENTRANT -Wall
LDFLAGS = `sdl-config --libs` -lopengl32 -lglu32

OBJECTS = $(SOURCES:%.c=%.o)

all : Aufgabe2

Aufgabe2 : $(OBJECTS)
	g++ -o $@ $(OBJECTS) $(LDFLAGS)

%.o : %.c
	g++ $(CFLAGS) -c $<

clean :
	rm *.o

build : clean all

