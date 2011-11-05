#include "main.h"
#include "draw.h"
#include "utils.h"

/**************************************************/
/* Calculate and set camera                       */
/**************************************************/

void camera() {
    
    static bool initCamera = true;
    static GLfloat cam_matrix[16]; 
    
    if (initCamera) {
        glPushMatrix();
        glLoadIdentity();
        gluLookAt(20, 20, 20,
                   0,  0,  0,
                   0,  1,  0);
        glGetFloatv(GL_MODELVIEW_MATRIX, cam_matrix);
        glPopMatrix();
        initCamera = false;
    }
    
    glLoadIdentity();
    
    if (shipCamera) {
        gluLookAt(20, 20, 20,
                   0,  0,  dist,
                   0,  1,  0);
    } else {
        glMultMatrixf(cam_matrix);
        
        if (keyFlag.right)      glTranslatef(-0.2f, 0.0f,  0.2f);
        if (keyFlag.left)       glTranslatef( 0.2f, 0.0f, -0.2f);
        if (keyFlag.up)         glTranslatef( 0.2f, 0.0f,  0.2f);
        if (keyFlag.down)       glTranslatef(-0.2f, 0.0f, -0.2f);
        if (keyFlag.pageUp)     glTranslatef( 0.0f, 0.0f,  1.0f);
        if (keyFlag.pageDown)   glTranslatef( 0.0f, 0.0f,  1.0f);
        
        glGetFloatv(GL_MODELVIEW_MATRIX, cam_matrix);
    }
}