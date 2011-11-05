#include "main.h"
#include "draw.h"

/**************************************************/
/* Draw The Ship                                  */
/**************************************************/

void drawShip() {
    // TO DO (2.1)
    float a[] = { -2.0f,  0.0f,  0.0f };
    float b[] = {  2.0f,  2.0f,  0.0f };
    float c[] = {  2.0f,  0.0f,  1.0f };
    float d[] = {  2.0f,  0.0f, -1.0f };
	
    //glLoadIdentity();
    
    glBegin(GL_TRIANGLES);
        //glNormal3f(0.0f, 0.0f, 1.0f);
        glColor3f(1.0, 0, 0);
        glVertex3fv(a);
        glColor3f(0, 1.0, 0);
	    glVertex3fv(c);
        glColor3f(0, 0, 1.0);
	    glVertex3fv(d);
	    
        glColor3f(1.0, 0, 0);
	    glVertex3fv(d);
        glColor3f(0, 1.0, 0);
	    glVertex3fv(c);
        glColor3f(0, 0, 1.0);
	    glVertex3fv(b);
	    
        glColor3f(1.0, 0, 0);
	    glVertex3fv(a);
        glColor3f(0, 1.0, 0);
	    glVertex3fv(d);
        glColor3f(0, 0, 1.0);
	    glVertex3fv(b);
	    
	    glColor3f(1.0, 0, 0);
	    glVertex3fv(a);
        glColor3f(0, 1.0, 0);
	    glVertex3fv(c);
        glColor3f(0, 0, 1.0);
	    glVertex3fv(b);
	glEnd();
	

}
