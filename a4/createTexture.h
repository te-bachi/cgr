#ifndef __CREATE_TEXTURE_H__
#define __CREATE_TEXTURE_H__

#define TEXTURE_PATH "textures/"

enum bla {
    TEXTURE_CLOUDS = 0,
    TEXTURE_EARTH,
    TEXTURE_JUPITER,
    TEXTURE_MARS,
    TEXTURE_MERCURY,
    TEXTURE_MOON,
    TEXTURE_NEPTUNE,
    TEXTURE_PLUTO,
    TEXTURE_SATURN,
    TEXTURE_SATURNRING,
    TEXTURE_SUN,
    TEXTURE_TITAN,
    TEXTURE_URANUS,
    TEXTURE_VENUS,
    TEXTURE_COUNT
};
    

extern GLuint textures[TEXTURE_COUNT];

void loadTextures();
void createTexture(unsigned int texArray[], const char * strFileName, int textureID);

#endif

