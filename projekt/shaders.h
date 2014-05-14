#ifndef _SHADERS_
#define _SHADERS_

#define SHADER_SKYBOX 		0
#define SHADER_GROUND 		1
#define SHADER_WATER 		2
#define SHADER_SPHERE 		3
#define SHADER_TERRAIN_LOD 	4
#define SHADER_CHAR 		5	
#define SHADER_PARTICLE		6


#define MAX_NUM_SHADERS 10


#include "GL_utilities.h"
#include "VectorUtils3.h"
#include "loadobj.h"
#include "LoadTGA.h"
#include "graphics.h"
#include <stdlib.h>


int numShaders;

typedef struct{
	GLuint handle;
	int id;
}Shader;
Shader * shaderList;
void shaderInit();
void addShader(char* fileNameVert,char* fileNameFrag,  int id);
GLuint getShader(int id);

#endif
