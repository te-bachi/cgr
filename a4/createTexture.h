#ifndef __CREATE_TEXTURE_H__
#define __CREATE_TEXTURE_H__

#include "main.h"

#define TEXTURE_PATH "textures/"

extern GLuint textures[PLANET_COUNT];

void loadTextures();
void createTexture(unsigned int texArray[], const char * strFileName, int textureID);

#endif

