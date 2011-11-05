#include "main.h"
#include "draw.h"
#include "createTexture.h"
#include "text.h"

void drawAxes();
void drawSun();
void drawMoon(float distanceToSun);
void drawSphere(float color[], double radius, int slices, int stacks, unsigned int texNumber);
void drawPlanet(float distanceToSun, float axisTilt, float years, float dayPerYear, float radius, unsigned int texNumber);
float fps;
float angle;
float dist;


GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };

char buffer[256];

void draw3D() {
	camera();
	
	incAnimationVars();
	
	glLightfv( GL_LIGHT0, GL_POSITION, LightPosition );
	
	
	
	
	// Debug
	
	drawSun();
    // distanceToSun, axisTilt, years, dayPerYear, radius, texNumber
    //drawPlanet(0.0f, 0.0f, 0, 0, 5, TEXTURE_SUN);
	
	// Merkur
    drawPlanet(10.0f, 23.0f, 0.8f, 365, 2, PLANET_MERCURY);
	
	// Venus
    drawPlanet(20.0f, 23.0f, 1.2f, 365, 4, PLANET_VENUS);
    
	// Earth
    drawPlanet(30.0f, 23.0f, 1.0f, 365, 3, PLANET_EARTH);
    
    // Moon
    drawMoon(30.0f);
    
	// Mars
    drawPlanet(40.0f, 23.0f, 1.0f, 365, 3, PLANET_MARS);
    
	// Jupiter
    drawPlanet(50.0f, 23.0f, 1.0f, 365, 3, PLANET_JUPITER);
    
	// Saturn
    drawPlanet(60.0f, 23.0f, 1.0f, 365, 3, PLANET_SATURN);
    
	// Uranus
    drawPlanet(70.0f, 23.0f, 1.0f, 365, 3, PLANET_URANUS);
    
	// Neptun
    drawPlanet(80.0f, 23.0f, 1.0f, 365, 3, PLANET_NEPTUNE);
    
	// Pluto
    drawPlanet(90.0f, 23.0f, 1.0f, 365, 3, PLANET_PLUTO);
	
    
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
	    // Axes
        glPushMatrix();
            drawAxes();
        glPopMatrix();
        
        // Axes translated
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
	/*
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
	*/
	
	{
        SDL_Color color;
        SDL_Rect position;
        glEnable2D();
        color.r = 255;
        color.g = 255;
        color.b = 255;
        
        position.x = 10;
        position.y = 0;
        sprintf(buffer, "Earth: %f / %f", sunsystem[PLANET_EARTH].angle, sunsystem[PLANET_EARTH].speed);
        SDL_GL_RenderText(buffer, font, color, &position);
        
        position.x = 10;
        position.y = 25;
        sprintf(buffer, "Venus: %f / %f", sunsystem[PLANET_VENUS].angle, sunsystem[PLANET_VENUS].speed);
        SDL_GL_RenderText(buffer, font, color, &position);
        
        position.x = 10;
        position.y = 50;
        sprintf(buffer, "FPS: %f", fps);
        SDL_GL_RenderText(buffer, font, color, &position);
        
        glDisable2D();
    }
}

void incAnimationVars() {
    if (!pause) {
        angle = angle + 30.0f/fps;
        dist = dist + 20.0f/fps;
    
        if (angle >= 360){angle = 0;}
        if (dist > 100){dist = -50;}
        
        
        for (int i = 0; i < PLANET_COUNT; i++) {
            if (fps > 0 && fps < 300) {
                sunsystem[i].angle += sunsystem[i].speed / fps;
            } else {
                sunsystem[i].angle += sunsystem[i].speed;
            }
            
            if (sunsystem[i].angle > 360.0f) {
                sunsystem[i].angle -= 360.0f;
            }
        }
    }
}

void drawSun() {
	float radius = 5.0f;
	float color[] = { 1.0f, 1.0f, 1.0f };
	int slices  = 32;
	int stacks  = 16;
	
	glPushMatrix();
        glPolygonMode(GL_BACK, GL_FILL);
        glDisable(GL_LIGHTING);
        drawSphere(color, radius, slices, stacks, PLANET_SUN);
        glEnable(GL_LIGHTING);
	glPopMatrix();
}

void drawMoon(float distanceToSun) {
	float color[] = { 1.0f, 1.0f, 1.0f };
	double radius  = 1;
	int slices  = 16;
	int stacks  = 8;
	
    glPushMatrix();
        glTranslatef(sin(M_PI * sunsystem[PLANET_EARTH].angle / 180.0f) * distanceToSun, 0.0f, cos(M_PI * sunsystem[PLANET_EARTH].angle / 180.0f) * distanceToSun);
        glRotatef(2 * angle, 0, 1, 0);
        glTranslatef(7.0f, 0.0f, 0.0f);
	    drawSphere(color, radius, slices, stacks, PLANET_MOON);
	glPopMatrix();
}

void drawPlanet(float distanceToSun, float axisTilt, float years, float dayPerYear, float radius, unsigned int texNumber) {
	float color[] = { 1.0f, 1.0f, 1.0f };
	int slices  = 32;
	int stacks  = 16;
	
	
    //glTranslatef(0.0f, 0.0f, distanceToSun);
    glPushMatrix();
        glTranslatef(sin(M_PI * sunsystem[texNumber].angle / 180.0f) * distanceToSun, 0.0f, cos(M_PI * sunsystem[texNumber].angle / 180.0f) * distanceToSun);
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

void drawSphere(float color[], double radius, int slices, int stacks, unsigned int texNumber) {
	GLUquadricObj *sphere;
	
    glRotatef(90.0f, 1, 0, 0);
    
    // Line
    if (gridEnable) {
        glDisable(GL_LIGHTING);
        glPolygonMode(GL_FRONT, GL_LINE);
        sphere = gluNewQuadric();
        glColor3f(color[0], color[1], color[2]);
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
    glColor3f(color[0], color[1], color[2]);
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
