#ifndef _TEXTURES_
#define _TEXTURES_

#define TEXTURE_MASKROS 	0 
#define TEXTURE_GROUND 		1	 
#define TEXTURE_WATER 		2
#define TEXTURE_SKYBOX 		3
#define TEXTURE_TERRAIN 	4
#define TEXTURE_CHAR 		5
#define TEXTURE_CLOUDS 		6
#define TEXTURE_TERRAIN_NORMAL	7
#define TEXTURE_TERRAIN_LOD	8
#define TEXTURE_TERRAIN_SNOW	9
#define TEXTURE_TERRAIN_GRASS	10
#define TEXTURE_TERRAIN_ROCKS1	11
#define TEXTURE_TERRAIN_ROCKS2	12
#define TEXTURE_TERRAIN_ROCKS3	13

#define MAX_NUM_TEXTURES 20


#include "GL_utilities.h"
#include "VectorUtils3.h"
#include "loadobj.h"
#include "LoadTGA.h"
#include "graphics.h"
#include <stdlib.h>


int numTextures;

typedef struct{
	GLuint handle;
	int id;
}Texture;
Texture * textureList;
void textureInit();
void addTexture(char* fileName, int id);
GLuint getTexture(int id);

#endif

