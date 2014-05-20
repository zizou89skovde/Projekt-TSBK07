#ifndef _GRAPHICS_
#define _GRAPHICS_

#include "types.h"
#include "include/GL_utilities.h"
#include "include/VectorUtils3.h"
#include "include/loadobj.h"
#include "textures.h"
#include "shaders.h"
#include "object.h"
#include "camera.h"
#include <stdlib.h>

#define near 1.0

#define far 1000.0
#define right 0.5
#define left -0.5
#define top 0.5
#define bottom -0.5
#define MODEL_GUBBE 0


#define WORLD_SIZE  800.0
#define GRID_SIZE 400.0
#define HEIGHT_SCALE 70

#define MAX_NUM_LEVELS 4



int numModels;
vec3 vLight;
GLfloat fTIme;
mat4 projection_mat;
void graphicsInitModels();
void createOffsetBuffer(Model *);
void uploadOffsetBuffer(Model *, GLfloat * , int );
void DrawInstancedModel(Model *, GLuint, char* , char* , char* , char * );
void drawInstanced(void * , mat4 );
void drawTerrain(void* , mat4);
void addModel(ArchObject * obj,char* fileName, int texture,int shader, void (*fp)(void *, mat4));
void graphicsTranslation(ModelObject* m, GLfloat x, GLfloat y, GLfloat z);
void graphicsRotation(ModelObject* m, mat4 rotationMat);
void graphicsDisplay(void* arg, mat4 view_mat);
void graphicsDisplaySkybox(void* arg, mat4 view_mat);

#endif

