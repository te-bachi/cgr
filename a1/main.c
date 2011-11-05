#include "main.h"
#include "draw.h"

int default_width = 1024;
int default_height = 768;

bool fullscreen = false;

bool enableDethTest = false;

void quit_program(int code) {
	SDL_Quit();
	exit(code);
}

void process_events() {
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		
		switch (event.type) {
			case SDL_QUIT:
				quit_program( 0 );
				break;
				
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					
					case SDLK_ESCAPE:
						quit_program(0);
						break;
						
					case SDLK_F1:
						quit_program(0);
						break;
						
					case SDLK_a:
						if (enableDethTest) {
							enableDethTest = false;
							printf("enable depth test\n");
							glEnable(GL_DEPTH_TEST);
						} else {
							enableDethTest = true;
							printf("disable depth test\n");
							glDisable(GL_DEPTH_TEST); 
						}
						fflush(stdout);
						break;
						
					default:
						break;
				}
				break;
			
			case SDL_VIDEORESIZE:
				init_SDL_Video(event.resize.w, event.resize.h);
				//init_OpenGL(event.resize.w, event.resize.h);
				break;
				
			case SDL_SYSWMEVENT:
				break;
				
			default:
				break;
		}
	}
}

bool init_OpenGL(int width, int height) {
	float ratio = (float) width / (float) height;	// Calculate and store the aspect ratio of the display
	
	glMatrixMode(GL_PROJECTION);					// Change to the projection matrix
	
	glLoadIdentity();
	gluPerspective(60.0, ratio, 0.1, width);	   // Set view perspective
	
	glMatrixMode(GL_MODELVIEW);						// Change to the modelview matrix
	
	//glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
	
	glEnable(GL_DEPTH_TEST);						// Enable hidden surface elimination
	
	
	return true;
}

bool init_SDL_Video(int width, int height) {
	
	const SDL_VideoInfo* info = NULL;				// Information about the current video settings
	
	int bpp = 0;									// Color depth in bits of our window
	int flags = 0;									// Flags we will pass into SDL_SetVideoMode
	
	info = SDL_GetVideoInfo( );						// Get some video information
	
	
	if (!info) {									// This should probably never happen
		fprintf( stderr, "Video query failed: %s\n", SDL_GetError( ) );
		return false;
	}
	
	bpp = info->vfmt->BitsPerPixel;					// Get color depth
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,	  8);	// Sets the color-depth of the red, green and blue color-part
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,	  8);	// to 8bit (standard today) 
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,	  8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,	 16);	// Set depth buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,  1);	// Sets wether to enable or disable doublebuffering
	
	flags = SDL_OPENGL | SDL_RESIZABLE;
	
	if (fullscreen) {
		flags = flags | SDL_FULLSCREEN;				// Set flag for fullscreen or windowed mode
	}
	
	// Set the video mode
	if (SDL_SetVideoMode(width, height, bpp, flags) == 0) {
		// If failed, print error message
		fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
		return false;
	}
	
	return true;
}

bool init_SDL() {
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {			// First, initialize SDL's video subsystem (video only)
		fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
		quit_program(1);						  // Failed, exit
	}
	
	init_SDL_Video(default_width, default_height);
	
	return true;
}

int main(int argc, char* argv[]) {
	// If intialising of SDL fails -> quit the program with error code 1
	if (!init_SDL()) {
		quit_program(1);
	}
	
	// If intialising of OpenGL fails -> quit the program with error code 1
	if (!init_OpenGL(default_width, default_height)) {
		quit_program(1);
	}
	
	// Repeat forever
	while(true) {
		// Draw your graphics
		draw_screen();
		
		// Process any ocuring events 
		process_events();
		fflush(stdout);
	}
	
	// You shouldn't get here. Only if someone changes the while condition...
	quit_program(0);
	
	return 0;
}
