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
	void (*renderFunc)(void *, mat4);
}ModelObject;

typedef struct{
   	GLfloat position[4];
   	GLfloat velocity[4];
	GLfloat lifetime;
	GLfloat distToCam;
}Particle;


typedef struct{
	int numParticles;
	int type;
	GLfloat* buff;
	vec3 iPos;
	Particle * particles;
	void (*updateFunc)(void *, void *);
	
}ParticleSystem;

typedef struct
{
	void (*updateFunc)(void *);
	vec3 initialPosition;
	vec3 position;
	vec3 velocity;
	GLfloat mass;
	GLfloat dragCoeff;
	GLfloat A; //area
} PhysicalObject;

typedef struct
{
	PhysicalObject physicalObj;
	ModelObject modelObj;
	ParticleSystem particleSystem;
	GLfloat position[3];
} ArchObject;


typedef struct{
vec3 eye;
vec3 center;
vec3 up;
ArchObject* obj;
}CameraObject;


 #endif
