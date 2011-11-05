/**************************************************/
/*                                                */
/*  Draw Sourcecode Aufgabe 2                     */
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

#include "main.h"
#include "draw.h"

void drawAxes();

/**************************************************/
/* Variable definition                            */
/**************************************************/
float fps;                                          // Frames per second
float angle;                                        // Rotation angle of ship
float dist;                                         // Ship translation

/**************************************************/
/* Draw 3D Objects                                */
/**************************************************/

void draw3D() {
    glLoadIdentity();                               // Load a new matrix

    camera();                                       // Calculate and set cameraview and cameraposition
    
    incAnimationVars();                                         

    // Draw Ship
    glPushMatrix();
        glTranslatef(0.0f, 0.0f,  -2.0f);
        drawShip();
    glPopMatrix();
    glPushMatrix();
        glRotatef(angle, 0, 1, 0);
        glTranslatef(0.0f, 0.0f,  -10.0f);
        drawShip();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, dist);
        glRotatef(90, 0, 1, 0);
        drawShip();
    glPopMatrix();
    
    drawAxes();
    
    // Draw grid
    ////////////////////
    glPushMatrix();                                 // Save matrix
    glTranslatef( 0.0f, -0.2f, 0.0f);               // Translate grid in the y-axis
    drawGrid();                                     // Draw a grid on the ground
    glPopMatrix();                                  // Restore matrix
}

/**************************************************/
/* Increment Animation Variables                  */
/**************************************************/

void incAnimationVars() {
    angle = angle + 60.0f/fps ;                     // deltaAngle = 60/fps; 60 degrees per second
    dist = dist + 20.0f/fps;                        // 20 units per second

    if (angle >= 360){angle = 0;}                   // reset angle, 360 degrees = 0 degrees
    if (dist > 100){dist = -50;}                    // reset distance to set a loop
}

void drawAxes(void) {
    
    glLineWidth(3.0);
    
    glBegin(GL_LINES);
        glColor3f(1,0,0); // X axis is red.
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);
        
        glColor3f(0,1,0); // Y axis is green.
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1, 0);
        
        glColor3f(0,0,1); // z axis is blue.
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 1);
    glEnd();
}
/**************************************************/
/* Draw Grid                                      */
/**************************************************/

void drawGrid() {
    
    glLineWidth(1.0);
    glColor3ub(0, 255, 0);                          // Turn the lines green
    /*
    glBegin(GL_LINES);
        glVertex3f(-50, 0, 0);
        glVertex3f(50, 0, 0);
        
        glVertex3f(0, 0, -50);
        glVertex3f(0, 0, 50);
    glEnd();
    */
    
    ///*
    for(float i = -50; i <= 50; i += 1) {           // Draw a 1x1 grid along the X and Z axis
        glBegin(GL_LINES);                          // Start drawing some lines 
            glVertex3f(-50, 0, i);                  // Do the horizontal lines (along the X)
            glVertex3f(50, 0, i);

            glVertex3f(i, 0, -50);                  // Do the vertical lines (along the Z)
            glVertex3f(i, 0, 50);
        glEnd();
    }
    //*/
}

/**************************************************/
/* Draw Screen                                    */
/**************************************************/

void draw_screen( ) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);             // Clear the screen and the depth buffer
    
    draw3D();
    countFrames();
    
    SDL_GL_SwapBuffers( );                                          // Swap the buffers
}

/**************************************************/
/* Count Frames                                   */
/**************************************************/

void countFrames() {
    static double thisFrame, lastFrame;                             // Define placeholders for frametimes
    static int count = 0;                                           // Define placeholder to count frames
    
    thisFrame = SDL_GetTicks();                                     // Get time
    count++;                                                        // Count frames
    
    if((thisFrame-lastFrame) > 10){                                 // Check if 10 millis are over
        
        fps = 1000.0f*(float)count/(float)(thisFrame-lastFrame);    // Calculate frames per second
        
        lastFrame=thisFrame;                                        // Set frametime value
        count = 0;                                                  // Reset count value
    }
}
