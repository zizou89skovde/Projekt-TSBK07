#ifndef _GRAPHICS_
#define _GRAPHICS_

#include "types.h"
#include "include/GL_utilities.h"
#include "include/VectorUtils3.h"
#include "include/loadobj.h"
#include "textures.h"
#include "shaders.h"
#include "object.h"
#include <stdlib.h>

#define near 1.0
#define far 30.0
#define right 0.5
#define left -0.5
#define top 0.5
#define bottom -0.5
#define MODEL_GUBBE 0

int numModels;



mat4 projection_mat;
void graphicsInitModels();
void addModel(ArchObject * obj,char* fileName, int texture,int shader, void (*fp)(void *, mat4));
void graphicsTranslation(ModelObject* m, GLfloat x, GLfloat y, GLfloat z);
void graphicsDisplay(void* arg, mat4 view_mat);
void graphicsDisplaySkybox(void* arg, mat4 view_mat);

#endif

