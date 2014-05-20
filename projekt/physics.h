

#ifndef _PHYSICS_
#define _PHYISCS_ 

#define BILLION  1000000000L

#include <math.h>
#include <time.h>

#include "types.h"
#include "stdio.h"
#include "ui.h"
#include "camera.h"
#include "GL_utilities.h"
#include "VectorUtils3.h"

GLfloat conversionFactor; // conversion between SI units and "world units"

//physical constants
GLfloat g;
GLfloat airDensity; 
time_t programStartTime;


//timekeeping

double callPeriod;
int functionCallCount;

void physicsInit();
void moveObject(void * object);
void addPhysicalObject(ArchObject* obj,vec3 initialPosition, vec3 initialRotationAxis, GLfloat initialRotationAngle, 
		       GLfloat dragCoeff, GLfloat area, GLfloat mass, int isChar, void (*fp)(void *));
void addStaticPhysicalObject(ArchObject* obj,vec3 initialPosition);
void staticObject(void* arg);
#endif
