/**************************************************/
/*                                                */
/*  Main Header Aufgabe 2                         */
/*                                                */
/**************************************************/
/*  Authors:                Reto Bollinger        */
/*                          bolliret@zhwin.ch     */
/*                                                */
/*                          Hanspeter Brühlmann   */
/*                          bruehhan@zhwin.ch     */
/*                                                */
/**************************************************/
/*  Date:                   15. October 2004      */
/**************************************************/

#ifndef _MAIN_H
#define _MAIN_H

#ifdef WIN32 
#include <windows.h> 
#else 
#include <GL/glx.h> 
#include <stdarg.h> 
#endif 
 
#include <SDL.h> 
#include <GL/gl.h> 
#include <GL/glu.h> 
#include <stdio.h> 
#include <iostream> 
#include <stdlib.h>
#include <math.h>
#include <SDL_syswm.h> 
#include <SDL_byteorder.h> 
#include <SDL_ttf.h>
 
using namespace std;

/**************************************************/
/* Struct definition                              */
/**************************************************/

struct KeyFlag {
	bool right;
	bool left;
	bool up;
	bool down;
	bool pageUp;
	bool pageDown;
};

enum ObjectType {
    TYPE_PLANET = 0,
    TYPE_RING
};

enum PlanetEnum {
    PLANET_CLOUDS = 0,
    PLANET_EARTH,
    PLANET_JUPITER,
    PLANET_MARS,
    PLANET_MERCURY,
    PLANET_MOON,
    PLANET_NEPTUNE,
    PLANET_PLUTO,
    PLANET_SATURN,
    PLANET_SATURNRING,
    PLANET_SUN,
    PLANET_TITAN,
    PLANET_URANUS,
    PLANET_VENUS,
    PLANET_COUNT
};

typedef struct _Planet Planet;
typedef struct _Ring Ring;

typedef struct _Planet {
    int     id;
    float   radius;
    float   distanceToSun;
    float   axisTilt;
    float   angle;
    float   speed;
    float   twist;
    float   twistPerAngle;
    bool    ligthing;
    Planet *moon;
    Ring   *ring;
} Planet;

typedef struct _Ring {
    int     id;
    float   radiusIn;
    float   radiusOut;
} Ring;


typedef struct _Object {
    ObjectType type;
    union {
        Planet planet;
        Ring   ring;
    };
} Object;

/**************************************************/
/* Variable definition                            */
/**************************************************/
extern KeyFlag keyFlag;
extern bool shipCamera;
extern bool gridEnable;
extern bool pause;

extern Object sunsystem[PLANET_COUNT];

extern TTF_Font* font;

/**************************************************/
/* Function definition                            */
/**************************************************/

void quit_program(int code);
void process_events();
bool init_OpenGL();
bool init_SDL();
int main(int argc, char* argv[]);

#endif
