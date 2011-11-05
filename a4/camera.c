#include "main.h"
#include "draw.h"

/**************************************************/
/* Calculate and set camera                       */
/**************************************************/

void camera() {

    static bool initCamera = true;
    static GLfloat cam_matrix[16]; 

    if (initCamera){                                    // Only on the fist loop
        glPushMatrix();
        glLoadIdentity();                               // load identity matrix 
        gluLookAt(100, 100, 100, 0, 0, 0, 0, 1, 0);
        //gluLookAt(20, 20, 0, 0, 0, 0, 0, 1, 0);
        glGetFloatv(GL_MODELVIEW_MATRIX, cam_matrix);   // save
        glPopMatrix();
        initCamera = false;
    }

    glLoadIdentity();
    if (keyFlag.pageUp)   glTranslated(0.0, 0.0,  0.3);     //translate in z direction
    if (keyFlag.pageDown) glTranslated(0.0, 0.0, -0.3);     //translate in z direction

    if (keyFlag.left)  glRotated(-1.5, 0.0, 1.0, 0.0);      //rotate around y-axis
    if (keyFlag.right) glRotated(+1.5, 0.0, 1.0, 0.0);      //rotate around y-axis

    if (keyFlag.up)   glRotatef(-1.5, 1.0, 0.0, 0.0);       //rotate around x-axis
    if (keyFlag.down) glRotatef(+1.5, 1.0, 0.0, 0.0);       //rotate around x-axis

    glMultMatrixf(cam_matrix);
    glGetFloatv(GL_MODELVIEW_MATRIX, cam_matrix);           // save
}