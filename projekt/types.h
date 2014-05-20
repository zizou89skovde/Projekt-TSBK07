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
	GLfloat* buff;
	Particle * particles;
	void (*updateFunc)(void *, void *);
	
}ParticleSystem;

typedef struct
{
	void (*updateFunc)(void *);
	vec3 initialPosition;
	mat4 rotationMat;
	GLfloat helpAngle; // rotated angle from init pos in xz plane
	GLfloat tiltAngle;
	vec3 velocity;
	vec3 position;
	GLfloat mass;
	GLfloat dragCoeff;
	GLfloat A; //area
	int isChar;
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
