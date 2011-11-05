/**************************************************/
/*                                                */
/*  Main Sourcecode Aufgabe 2                     */
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
#include "createTexture.h"

/**************************************************/
/* Variable definition                            */
/**************************************************/

char fontpath[] = "Fonts/ANTQUAB.TTF";

KeyFlag keyFlag;                                    // Placeholder for pressed keys
int width = 1024;                                   // Dimensions of our window
int height = 768;

bool fullscreen = false;                                // Fullscreen or windowed mode
bool shipCamera = false;
bool gridEnable = false;
bool pause = false;

Object sunsystem[PLANET_COUNT];

TTF_Font* font;

/**************************************************/
/* Exit                                           */
/**************************************************/

void quit_program( int code )
{
    SDL_Quit( );                                    // Quit SDL and restore previous video settings
    exit( code );                                   // Exit program
}

/**************************************************/
/* Poll Keyevents                                 */
/**************************************************/

void process_events() {
    SDL_Event event;                                // SDL event placeholder
    
    // Used for camera control
    //////////////////////////  
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            // Handle quit requests (like Ctrl-c)
            case SDL_QUIT:
                quit_program( 0 );
                break;
                
            // Handle each keydown
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ) {
                    case SDLK_ESCAPE:
                        quit_program(0);
                        break;
                        
                    case SDLK_RIGHT:
                        keyFlag.right = true;
                        break;
                        
                    case SDLK_LEFT:
                        keyFlag.left = true;
                        break;
                        
                    case SDLK_UP:
                        keyFlag.up = true;
                        break;
                        
                    case SDLK_DOWN:
                        keyFlag.down = true;
                        break;
                        
                    case SDLK_PAGEUP:
                        keyFlag.pageUp = true;
                        break;
                        
                    case SDLK_PAGEDOWN:
                        keyFlag.pageDown = true;
                        break;
                        
                    default:
                        break;
                }
                break;
            
            case SDL_KEYUP:                             // Handle each keyup
                switch(event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        keyFlag.right = false;              // Set keyflags
                        break;
                        
                    case SDLK_LEFT:
                        keyFlag.left = false;
                        break;
                        
                    case SDLK_UP:
                        keyFlag.up = false;
                        break;
                        
                    case SDLK_DOWN:
                        keyFlag.down = false;
                        break;
                        
                    case SDLK_PAGEUP:
                        keyFlag.pageUp = false;
                        break;
                        
                    case SDLK_PAGEDOWN:
                        keyFlag.pageDown = false;
                        break;
                        
                    case SDLK_s:
                        if (shipCamera) {
                            shipCamera = false;
                        } else {
                            shipCamera = true;
                        }
                        break;
                        
                    case SDLK_g:
                        if (gridEnable) {
                            gridEnable = false;
                        } else {
                            gridEnable = true;
                        }
                        break;
                        
                    case SDLK_p:
                        if (pause) {
                            pause = false;
                        } else {
                            pause = true;
                        }
                        break;
                        
                    case SDLK_F10:
                        if (fullscreen) {
                            fullscreen = false;
                        } else {
                            fullscreen = true;
                        }
                        
                        SDL_Quit();                             // Quit SDL
                        init_SDL();                             // Restart SDL
                        init_OpenGL();                          // Restart OpenGL
                        
                        break;
                
                    default:
                        break;
                }
                break;
                
            case SDL_VIDEORESIZE:                       // Handle resize events
                width = event.resize.w;                 // Set event width value
                height = event.resize.h;                // Set event height vlaue
                SDL_Quit();                             // Quit SDL
                init_SDL();                             // Restart SDL
                init_OpenGL();                          // Restart OpenGL
                break;
            
            default:
                break;
        }
    }
}

/**************************************************/
/* Init OpenGL                                    */
/* Returnvalue: true if init was successful       */
/**************************************************/
GLfloat GlobalAmbient[] = { 0.2f, 0.2f, 0.2f, 1.2f };

GLfloat LightAmbient[]  = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat LightDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

//GLfloat LightPosition[] = { 0.0f, 0.0f, 20.0f, 1.0f };
//GLfloat LightDirection[] = { 15.0f, 0.0f, 0.0f, 1.0f };

GLfloat MaterialSpecular[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat MaterialShininess[] = { 50.0f };
GLfloat MaterialAmbient[]   = { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat MaterialDiffuse[]   = { 0.4f, 0.8f, 0.4f, 1.0f };

bool init_OpenGL( ) {   
    
    float ratio = (float) width / (float) height;   // Calculate and store the aspect ratio of the display
    
    glMatrixMode( GL_PROJECTION );                  // Change to the projection matrix
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective( 60.0, ratio, 0.1, 1024.0 );     // Set view perspective
    
    glMatrixMode( GL_MODELVIEW );                   // Change to the modelview matrix
    
    glEnable(GL_DEPTH_TEST);                        // Enable hidden surface removal
    
    // Ambient Ligth
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GlobalAmbient);
    
    // Light0
    glLightfv( GL_LIGHT0, GL_AMBIENT, LightAmbient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, LightDiffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, LightSpecular );
    
    // Spot
    //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LightDirection);
    //glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);
    //glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 150.0);
    
    // Material
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MaterialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, MaterialShininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MaterialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MaterialDiffuse);
    
    // Texture
    loadTextures();
    
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    
    
	/* Irrelevant stuff for this demo */
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	/* Required if you want alpha-blended textures (for our fonts) */
	glBlendFunc(GL_ONE, GL_ONE);
    
    return true;
    
}

/**************************************************/
/* Init SDL                                       */
/* Returnvalue: true if init was successful       */
/**************************************************/

bool init_SDL()
{
    
    const SDL_VideoInfo* info = NULL;               // Information about the current video settings
    
    int bpp = 0;                                    // Color depth in bits of our window
    int flags = 0;                                  // Flags we will pass into SDL_SetVideoMode
    
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )            // First, initialize SDL's video subsystem (video only)
    {
        fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
        quit_program( 1 );                          // Failed, exit
    }
    
    info = SDL_GetVideoInfo( );                     // Get some video information
    
    if( !info )                                     // This should probably never happen
    {
        fprintf( stderr, "Video query failed: %s\n", SDL_GetError( ) );
        return false;
    }
    
    bpp = info->vfmt->BitsPerPixel;                 // Get color depth
    
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );      // Sets the color-depth of the red, green and blue color-part
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );    // to 8bit (standard today) 
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );   // Set depth buffer
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );  // Sets wether to enable or disable doublebuffering
    
    flags = SDL_OPENGL;                             // Set flags for SDL OpenGL
    flags = flags | SDL_RESIZABLE;
    
    if (fullscreen) {
        flags = flags | SDL_FULLSCREEN;             // Set flag for fullscreen or windowed mode
    }
    
    if(SDL_SetVideoMode(width, height, bpp, flags) == 0) {
        fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
        return false;
    }
    
    if(TTF_Init()) {
        fprintf(stderr, "TTF init failed: %s\n", TTF_GetError());
        return false;
    }
    
	if(!(font = TTF_OpenFont(fontpath, 20))) {
		printf("Error loading font: %s", TTF_GetError());
		return 1;
	}
	
    return true;
}

void init_Planet(int id, float radius, float distanceToSun, float axisTilt,
                 float angle, float speed, float twist, float twistPerAngle,
                 Planet *moon, Ring *ring) {

    //
    sunsystem[id].type                 = TYPE_PLANET;
    sunsystem[id].planet.id            = id;
    sunsystem[id].planet.radius        = radius;
    sunsystem[id].planet.distanceToSun = distanceToSun;
    sunsystem[id].planet.axisTilt      = axisTilt;
    sunsystem[id].planet.angle         = angle;
    sunsystem[id].planet.speed         = speed;
    sunsystem[id].planet.twist         = twist;
    sunsystem[id].planet.twistPerAngle = twistPerAngle;
    sunsystem[id].planet.moon          = moon;
    sunsystem[id].planet.ring          = ring;
}

void init_Ring(int id, float radiusIn, float radiusOut) {
    sunsystem[id].type           = TYPE_RING;
    sunsystem[id].ring.id        = id;
    sunsystem[id].ring.radiusIn  = radiusIn;
    sunsystem[id].ring.radiusOut = radiusOut;
}

void init_Sunsystem() {
    
    // Pre-Init
    
    init_Planet(PLANET_SUN, 5.0f, 0.0f, 30.0f,
                0.0f, 0.0f, 0.0f, 90.0f, NULL, NULL);
    
    init_Ring(PLANET_SATURNRING, 2.0f, 6.0f);
    
    // Init
    
    init_Planet(PLANET_MERCURY, 2.0f, 10.0f, 0.0f,
                45.0f, 24.0f, 0.0f, 90.0f, NULL, NULL);
    
    init_Planet(PLANET_MERCURY, 2.0f, 10.0f, 0.0f,
                45.0f, 24.0f, 0.0f, 90.0f, NULL, NULL);
    init_Planet(PLANET_VENUS, 4.0f, 20.0f, 0.0f,
                90.0f, 20.0f, 0.0f, 20.0f, NULL, NULL);
    init_Planet(PLANET_EARTH, 2.0f, 30.0f, 23.0f,
                0.0f, 30.0f, 0.0f, 20.0f, &(sunsystem[PLANET_MOON].planet), NULL);
    init_Planet(PLANET_MARS, 3.0f, 40.0f, 23.0f,
                0.0f, 30.0f, 0.0f, 20.0f, NULL, NULL);
    
    init_Planet(PLANET_JUPITER, 3.0f, 50.0f, 0.0f,
                0.0f, 30.0f, 0.0f, 20.0f, NULL, NULL);
    init_Planet(PLANET_SATURN, 3.0f, 60.0f, 0.0f,
                0.0f, 30.0f, 0.0f, 20.0f, NULL, NULL);
    init_Planet(PLANET_URANUS, 3.0f, 70.0f, 0.0f,
                0.0f, 30.0f, 0.0f, 20.0f, NULL, NULL);
    init_Planet(PLANET_NEPTUNE, 3.0f, 80.0f, 0.0f,
                0.0f, 30.0f, 0.0f, 20.0f, NULL, NULL);
    init_Planet(PLANET_PLUTO, 3.0f, 90.0f, 0.0f,
                0.0f, 30.0f, 0.0f, 20.0f, NULL, NULL);
    
    /*
    
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
    */
}

/**************************************************/
/* Main                                           */
/* Returnvalue: 0 if main was successful          */
/**************************************************/

int main( int argc, char* argv[] )
{
    if(!init_SDL())                 // If intialising of SDL fails -> quit the program with error code 1
    {
        quit_program( 1 );
    }
    
    if(!init_OpenGL())              // If intialising of OpenGL fails -> quit the program with error code 1
    {
        quit_program( 1 );
    }
    
    init_Sunsystem();
    
    while(true)                     // Repeat forever
    {
        draw_screen();              // Draw your graphics 
        process_events( );          // Process any ocuring events 
    }
    
    quit_program(0);                // You shouldn't get here. Only if someone changes the while condition...
}
