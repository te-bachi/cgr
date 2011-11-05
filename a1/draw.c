
#include "main.h"
#include "draw.h"

void draw3D() {
    GLUquadricObj *q;
    
    
    // Sphere 1b
    glLoadIdentity();
    q = gluNewQuadric();
    glTranslatef(1.0f, -0.8f, -2.0f);
    glColor3f(1.0f, 0.0f, 1.0f);
    gluSphere(q, 0.5, 32, 16);
    
    // Sphere 1
    glLoadIdentity();
    q = gluNewQuadric();
    glTranslatef(1.0f, -1.0f, -3.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluSphere(q, 0.5, 32, 16);
    
    // Sphere 2
    glLoadIdentity();
    q = gluNewQuadric();
    glTranslatef(-1.0f, 1.0f, -5.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    gluSphere(q, 0.5, 32, 16);
    
    // Sphere 3
    glLoadIdentity();
    q = gluNewQuadric();
    glTranslatef(0.0f, 0.0f, -10.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluSphere(q, 0.5, 32, 16);
    
    
    gluDeleteQuadric(q);
}

void draw_screen() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    draw3D();
    
    SDL_GL_SwapBuffers( );
}

