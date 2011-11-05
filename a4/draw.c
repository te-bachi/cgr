#include "main.h"
#include "draw.h"
#include "createTexture.h"

void drawAxes();
void drawSun();
void drawMoon();
void drawSphere(float color[], double radius, int slices, int stacks, unsigned int texNumber);
void drawPlanet(float distanceToSun, float axisTilt, float years, float dayPerYear, float radius, unsigned int texNumber);
float fps;
float angle;
float dist;


GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };

void draw3D() {
	camera();
	
	incAnimationVars();
	
	glLightfv( GL_LIGHT0, GL_POSITION, LightPosition );
	
	
	
	
	// Debug
	
	drawSun();
    // distanceToSun, axisTilt, years, dayPerYear, radius, texNumber
    //drawPlanet(0.0f, 0.0f, 0, 0, 5, TEXTURE_SUN);
	
	// Earth
	glPushMatrix();
	    // distanceToSun = 20, axisTilt = 23, years = 4, dayPerYear = 365, radius = 3
        drawPlanet(20.0f, 23.0f, 1, 365, 3, TEXTURE_EARTH);
        glPushMatrix();
            glRotatef(2 * angle, 0, 1, 0);
            glTranslatef(7.0f, 0.0f, 0.0f);
            drawMoon();
        glPopMatrix();
	glPopMatrix();
	
	// ...
	glPushMatrix();
	    // distanceToSun, axisTilt, years, dayPerYear, radius, texNumber
        drawPlanet(20.0f, 23.0f, 4, 365, 3, TEXTURE_EARTH);
        glPushMatrix();
            glRotatef(2 * angle, 0, 1, 0);
            glTranslatef(7.0f, 0.0f, 0.0f);
            drawMoon();
        glPopMatrix();
	glPopMatrix();
	
	
	/*
    glBegin(GL_QUADS);
        for () {
            glVertex3f(rIn * cos(
        }
    glEnd();
    
    
    glBegin(GL_QUAD_STRIP);
        for (int i = 0; i < n; i++) {
            glVertex3f(rIn * cos(i * delta), 0, -rIn * sin(i * delta));
            glVertex3f(rOut * cos(i * delta), 0, -rOut * sin(i * delta));
        }
    glEnd();
    */
	if (gridEnable) {
        glPushMatrix();
            drawAxes();
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, 20.0f);
            drawAxes();
        glPopMatrix();
        
        // Draw grid
        glPushMatrix();
            glTranslatef(0.0f, -5.0f, 0.0f);
            drawGrid();
        glPopMatrix();
    }
	
	// Draw Quad
	glPushMatrix();
		glTranslatef(0.0f, -5.0f, 0.0f);
	    glBegin(GL_QUADS);
	        glColor3ub(255, 255, 255);
			glVertex3f( 3, 0,  3);
			glVertex3f(-3, 0,  3);
			glVertex3f(-3, 0, -3);
			glVertex3f( 3, 0, -3);
	    glEnd();
	glPopMatrix();
}

void incAnimationVars() {
    if (!pause) {
        angle = angle + 30.0f/fps;
        dist = dist + 20.0f/fps;
    
        if (angle >= 360){angle = 0;}
        if (dist > 100){dist = -50;}
    }
}

void drawSun() {
	float radius = 5.0f;
	float color[] = { 1.0f, 1.0f, 0.0f };
	int slices  = 32;
	int stacks  = 16;
	
	glPushMatrix();
        glPolygonMode(GL_BACK, GL_FILL);
        glDisable(GL_LIGHTING);
        drawSphere(color, radius, slices, stacks, TEXTURE_SUN);
        glEnable(GL_LIGHTING);
	glPopMatrix();
	
}

void drawPlanet(float distanceToSun, float axisTilt, float years, float dayPerYear, float radius, unsigned int texNumber) {
	float color[] = { 0.0f, 1.0f, 0.0f };
	int slices  = 32;
	int stacks  = 16;
	
	
    //glTranslatef(0.0f, 0.0f, distanceToSun);
    glTranslatef(sin(M_PI * angle / 180) * distanceToSun, 0.0f, cos(M_PI * angle / 180) * distanceToSun);
    glPushMatrix();
        glRotatef(-axisTilt, 1, 0, 0);
        drawSphere(color, radius, slices, stacks, texNumber);
        
        // Pol-Linie
        if (gridEnable) {
            glLineWidth(3.0);
            glDisable(GL_LIGHTING);
            glBegin(GL_LINES);
                glColor3f(1.0f, 1.0f, 1.0f);
                glVertex3f(0, 0, -5);
                glVertex3f(0, 0, 5);
            glEnd();
            glEnable(GL_LIGHTING);
        }
        
    glPopMatrix();
}

void drawMoon() {
	float color[] = { 0.0f, 0.0f, 1.0f };
	double radius  = 1;
	int slices  = 16;
	int stacks  = 8;
	
	drawSphere(color, radius, slices, stacks, TEXTURE_MOON);
	
}

void drawSphere(float color[], double radius, int slices, int stacks, unsigned int texNumber) {
	GLUquadricObj *sphere;
	
    glRotatef(90.0f, 1, 0, 0);
    
    // Line
    if (gridEnable) {
        glDisable(GL_LIGHTING);
        glPolygonMode(GL_FRONT, GL_LINE);
        sphere = gluNewQuadric();
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, textures[texNumber]);
        gluQuadricDrawStyle(sphere, GLU_FILL);
        gluQuadricTexture(sphere, GL_TRUE);
        gluQuadricNormals(sphere, GL_SMOOTH);
        gluSphere(sphere, radius, slices, stacks);
        gluDeleteQuadric(sphere);
        glEnable(GL_LIGHTING);
	}
	
    // Fill
    glPolygonMode(GL_FRONT, GL_FILL);
	sphere = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textures[texNumber]);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GL_SMOOTH);
	gluSphere(sphere, radius - 0.01, slices, stacks);
	gluDeleteQuadric(sphere);
}

void drawAxes(void) {
	
	glLineWidth(3.0);
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);
		
		glColor3f(0,1,0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);
		
		glColor3f(0,0,1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1);
	glEnd();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}


void drawGrid() {
	
	glLineWidth(1.0);
	glColor3ub(0, 255, 0);
	
	glDisable(GL_LIGHTING);
	for(float i = -50; i <= 50; i += 1) {
		glBegin(GL_LINES); 
			glVertex3f(-50, 0, i);
			glVertex3f(50, 0, i);
			
			glVertex3f(i, 0, -50);
			glVertex3f(i, 0, 50);
		glEnd();
	}
	glEnable(GL_LIGHTING);
	
}

void draw_screen( ) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	draw3D();
	countFrames();
	
	SDL_GL_SwapBuffers();
}

void countFrames() {
	static double thisFrame, lastFrame;
	static int count = 0;
	
	thisFrame = SDL_GetTicks();
	count++;
	
	if ((thisFrame-lastFrame) > 10) {
		
		fps = 1000.0f*(float)count/(float)(thisFrame-lastFrame);
		
		lastFrame=thisFrame;
		count = 0;
	}
}
