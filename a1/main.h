
#ifndef __MAIN_H__
#define __MAIN_H__

#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL_syswm.h>
#include <SDL_byteorder.h>

void quit_program(int code);
void process_events();
bool init_OpenGL(int width, int height);
bool init_SDL_Video(int width, int height);
bool init_SDL();
int main(int argc, char* argv[]);

#endif
