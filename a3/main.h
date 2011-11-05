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
} ;

/**************************************************/
/* Variable definition                            */
/**************************************************/
extern KeyFlag keyFlag;
extern bool shipCamera;

/**************************************************/
/* Function definition                            */
/**************************************************/

void quit_program( int code );						// Quit program

void process_events( );								// Process keyevents

bool init_OpenGL( );								// Init OpenGL

bool init_SDL();									// Init SDL Engine

int main( int argc, char* argv[] );					// Main

#endif
