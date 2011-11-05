#include "main.h"
#include "shadow.h"

/**************************************************/
/* Build shadow matrix                            */
/**************************************************/

// Used for optional part only
////////////////////////////////////////////////////
void buildShadowMatrix(float* shadowMatrix, float* lightPos, float* normal, float* p) {

    float d = normal[0]*lightPos[0] + normal[1]*lightPos[1] + normal[2]*lightPos[2];
	float c = p[0]*normal[0] + p[1]*normal[1] + p[2]*normal[2] - d; 
	
    shadowMatrix[0]  = c + lightPos[0] * normal[0];	    // First row
    shadowMatrix[4]  =	   lightPos[0] * normal[1];
    shadowMatrix[8]  =	   lightPos[0] * normal[2];
    shadowMatrix[12] =	  -lightPos[0] * (c+d);
	
    shadowMatrix[1]  =	   lightPos[1] * normal[0];		// Second row
    shadowMatrix[5]  = c + lightPos[1] * normal[1];
    shadowMatrix[9]  =	   lightPos[1] * normal[2];
    shadowMatrix[13] =	  -lightPos[1] * (c+d);
	
    shadowMatrix[2]  =	   lightPos[2] * normal[0];		// Third row
    shadowMatrix[6]  =	   lightPos[2] * normal[1];
    shadowMatrix[10] = c + lightPos[2] * normal[2];
    shadowMatrix[14] =	  -lightPos[2] * (c+d);
	
    shadowMatrix[3]  = normal[0];		// Fourth row
    shadowMatrix[7]  = normal[1];
    shadowMatrix[11] = normal[2];
    shadowMatrix[15] = -d;
	for (int i=0;i<16;i++) shadowMatrix[i] /= shadowMatrix[15];
}

/***************/
/* Draw shadow */
/***************/

void drawShadow(float modelMatrix[],					// The model matrix of the sphere whose shadow shall be drawn
				float radius) {							// The spheres radius
	float shadowMatrix[16]; 
	float lightPosition[] = {centerOfUniverse[0], 
							 centerOfUniverse[1]+10.0f,	// 10 above centerOfUniverse
							 centerOfUniverse[2]}; 

	// TO DO 3.4:
	// //////////
    float shadowPlaneNormal[] = {				};		// Define the shadow plane by its normal
	float pointInPlane[]      = {				};		// and by an arbitrary point in it.
	
    // Build a shadow matrix using the light's current position and the plane
    buildShadowMatrix(shadowMatrix, lightPosition, shadowPlaneNormal, pointInPlane);
    
    glDisable(GL_LIGHTING);								// Disable light effects
    glColor3f(0.5f, 0.5f, 0.5f);						// Shadow's color
	glPolygonMode(GL_FRONT, GL_FILL);

	// TO DO 3.4:										// Draw the shadow
	// //////////




	
	glEnable(GL_DEPTH_TEST);							// Enable depth test to sea the shadow also from below
    glEnable(GL_LIGHTING);								// Enable light effects
	glDisable(GL_BLEND);								// Disable blending
}
