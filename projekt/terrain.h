#ifndef _TERRAIN_
#define _TERRAIN_

#include "textures.h"
#include "shaders.h"
#include "GL_utilities.h"
#include "VectorUtils3.h"
#include "loadobj.h"
#include "LoadTGA.h"

vec3 CalculateNormal(int x,int z,GLfloat stepSize,GLfloat stepSizeY, TextureData * tex);

void generateTerrain(ArchObject * groundArchObject ,ArchObject * waterArchObject );
void initializeTerrain(ArchObject * , int *);

typedef struct
{
	GLfloat dimX;
	GLfloat dimZ;
	GLfloat resolution;
	GLfloat * vertexArray;
	
} TerrainData;

TerrainData groundData; 

// vec3 getNormal(int x,int y,groundStruct * dkflg);

#endif
