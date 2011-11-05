#include <stdlib.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include "text.h"

int round_ext(double x) {
	return (int)(x + 0.5);
}

int nextpoweroftwo(int x) {
	double logbase2 = log(x) / log(2);
	return round_ext(pow(2,ceil(logbase2)));
}

void SDL_GL_RenderText(char *text, TTF_Font *font, SDL_Color color, SDL_Rect *location) {
    SDL_Surface *initial;
    SDL_Surface *intermediary;
    int w,h;
    GLuint texture;
    
    /* Use SDL_TTF to render our text */
    initial = TTF_RenderText_Blended(font, text, color);
    
    /* Convert the rendered text to a known format */
    w = nextpoweroftwo(initial->w);
    h = nextpoweroftwo(initial->h);
    
    intermediary = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

    SDL_BlitSurface(initial, 0, intermediary, 0);
    
    /* Tell GL about our new texture */
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGRA, 
            GL_UNSIGNED_BYTE, intermediary->pixels );
    
    /* GL_NEAREST looks horrible, if scaled... */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   

    /* prepare to render our texture */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    /* Draw a quad at location */
    glBegin(GL_QUADS);
        /* Recall that the origin is in the lower-left corner
           That is why the TexCoords specify different corners
           than the Vertex coors seem to. */
        glTexCoord2f(0.0f, 1.0f); 
            glVertex2f(location->x    , location->y);
        glTexCoord2f(1.0f, 1.0f); 
            glVertex2f(location->x + w, location->y);
        glTexCoord2f(1.0f, 0.0f); 
            glVertex2f(location->x + w, location->y + h);
        glTexCoord2f(0.0f, 0.0f); 
            glVertex2f(location->x    , location->y + h);
    glEnd();
    
    /* Bad things happen if we delete the texture before it finishes */
    glFinish();
    
    /* return the deltas in the unused w,h part of the rect */
    location->w = initial->w;
    location->h = initial->h;
    
    /* Clean up */
    SDL_FreeSurface(initial);
    SDL_FreeSurface(intermediary);
    glDeleteTextures(1, &texture);
}

void glEnable2D() {
    int vPort[4];
    
    glGetIntegerv(GL_VIEWPORT, vPort);
    
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
        glLoadIdentity();
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
}

void glDisable2D() {
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();   
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

