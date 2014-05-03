#ifndef _GRAPHICS_
#define _GRAPHICS_

#include "include/GL_utilities.h"
#include "include/VectorUtils3.h"
#include "include/loadobj.h"
#include "textures.h"
#include "shaders.h"
#include <stdlib.h>

#define near 1.0
#define far 30.0
#define right 0.5
#define left -0.5
#define top 0.5
#define bottom -0.5

#define MAX_NUM_MODELS 20

#define MODEL_GUBBE 0 


int numModels;
typedef struct
{
	Model* model;

	GLuint program;
	GLuint texture;

	int id;

	mat4 translation_mat;
	mat4 rotation_mat;	

}Model_struct;

Model_struct * modelList;

mat4 projection_mat;
void graphicsInitModels();
void addModel(char* fileName, int id, int texture,int shader);
Model_struct* getModel(int id);
void graphicsTranslation(Model_struct* m, GLuint x, GLuint y, GLuint z);
void graphicsDisplay(Model_struct* m, mat4 view_mat);

#endif
