#ifndef _GRAPHICS_
#define _GRAPHICS_

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

int numModels;
typedef struct
{
	Model* model;

	GLuint program;
	GLuint texture;

	int id;

	mat4 translation_mat;
	mat4 rotation_mat;	

}ModelObject;


mat4 projection_mat;
void graphicsInitModels();
void addModel(ObjectStruct * obj,char* fileName, int id, int texture,int shader);
void graphicsTranslation(ModelObject* m, GLuint x, GLuint y, GLuint z);
void graphicsDisplay(ModelObject* m, mat4 view_mat);

#endif

