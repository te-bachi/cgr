#ifndef __TEXT_H__
#define __TEXT_H__

#include <SDL.h>
#include <SDL_ttf.h>

void SDL_GL_RenderText(char *text, TTF_Font *font, SDL_Color color, SDL_Rect *location);
void glEnable2D();
void glDisable2D();

#endif

