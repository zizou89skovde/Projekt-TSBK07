#ifndef _TYPES_
#define _TYPES_


#include "GL_utilities.h"
#include "VectorUtils3.h"
#include "GL_utilities.h"
#include "loadobj.h"

typedef struct
{
	Model model;
	GLuint program;
	GLuint texture;
	int id;
	mat4 translation_mat;
	mat4 rotation_mat;	

}ModelObject;

typedef struct
{
	vec3 initialPosition;
	vec3 position;
	vec3 velocity;
	GLfloat mass;
	GLfloat dragCoeff;
	GLfloat A; //area
} PhysicalObject;

typedef struct{
   float position[4];
   float velocity[4];
   float lifetime;
   float distToCam;
}Particle;


typedef struct{
	int numInstances;
	float* buff;
	Particle * particles;
}ParticleSystem;


typedef struct
{
	PhysicalObject physicalObj;
	ModelObject modelObj;
	ParticleSystem particleSystem;

	GLfloat position[3];
} ArchObject;



 #endif
