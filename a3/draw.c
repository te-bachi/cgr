#include "main.h"
#include "draw.h"

void drawAxes();
void drawSun(float radius);

void drawMoon();
void drawSphere(float color[], double radius, int slices, int stacks);
void drawPlanet(float distanceToSun, float axisTilt, float years, float dayPerYear, float radius, unsigned int texNumber);
float fps;
float angle;
float dist;

GLfloat GlobalAmbient[]	= { 0.2f, 0.2f, 0.2f, 1.2f };

GLfloat LightAmbient[]	= { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat LightDiffuse[]	= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

//GLfloat LightPosition[] = { 0.0f, 0.0f, 20.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//GLfloat LightDirection[] = { 15.0f, 0.0f, 0.0f, 1.0f };

GLfloat MaterialSpecular[]	= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat MaterialShininess[] = { 50.0f };
GLfloat MaterialAmbient[]	= { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat MaterialDiffuse[]	= { 0.4f, 0.8f, 0.4f, 1.0f };

void draw3D() {
	camera();
	
	incAnimationVars();
	
	// Ligth
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GlobalAmbient);
	
	glLightfv( GL_LIGHT0, GL_AMBIENT, LightAmbient );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, LightDiffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, LightSpecular );
	
	glLightfv( GL_LIGHT0, GL_POSITION, LightPosition );
	
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LightDirection);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 150.0);
	
	// Material
	
	glMaterialfv(GL_FRONT, GL_SPECULAR,	 MaterialSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, MaterialShininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT,	 MaterialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,	 MaterialDiffuse);
	
	
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	
	
	
	// Debug
	
	drawSun(5.0f);
	
	// Earth
	// distanceToSun, axisTilt, years, dayPerYear, radius, texNumber
	glPushMatrix();
        drawPlanet(-20.0f, 230.0f, 4, 365, 3, 0);
        glPushMatrix();
            glRotatef(2 * angle, 0, 1, 0);
            glTranslatef(7.0f, 0.0f, 0.0f);
            drawMoon();
        glPopMatrix();
	glPopMatrix();
	
	
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

void incAnimationVars() {
	angle = angle + 60.0f/fps;
	dist = dist + 20.0f/fps;

	if (angle >= 360){angle = 0;}
	if (dist > 100){dist = -50;}
}

void drawSun(float radius) {
	float color[] = { 1.0f, 1.0f, 0.0f };
	int slices  = 32;
	int stacks  = 16;
	
	glPushMatrix();
        glPolygonMode(GL_BACK, GL_FILL);
        glDisable(GL_LIGHTING);
        drawSphere(color, radius, slices, stacks);
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
    glRotatef(90.0f - axisTilt, 1, 0, 0);
    glRotatef(angle, 0, 0, 1);
    drawSphere(color, radius, slices, stacks);
    
    // Pol-Linie
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
        glColor3f(1, 1, 1);
        glVertex3f(0, 0, -5);
        glVertex3f(0, 0, 5);
    glEnd();
    glEnable(GL_LIGHTING);
	
    glPopMatrix();
}

void drawMoon() {
	float color[] = { 0.0f, 0.0f, 1.0f };
	double radius  = 1;
	int slices  = 16;
	int stacks  = 8;
	
	drawSphere(color, radius, slices, stacks);
	
}

void drawSphere(float color[], double radius, int slices, int stacks) {
	GLUquadricObj *sphere;
	
    glDisable(GL_LIGHTING);
    glPolygonMode(GL_FRONT, GL_LINE);
	sphere = gluNewQuadric();
	glColor3f(color[0], color[1], color[2]);
	gluQuadricNormals(sphere, GL_SMOOTH);
	gluSphere(sphere, radius, slices, stacks);
	gluDeleteQuadric(sphere);
    glEnable(GL_LIGHTING);
	
    glPolygonMode(GL_FRONT, GL_FILL);
	sphere = gluNewQuadric();
	glColor3f(color[0], color[1], color[2]);
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
