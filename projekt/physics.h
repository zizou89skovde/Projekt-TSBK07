#ifndef _PHYSICS_
#define _PHYISCS_ 

#include <math.h>
#include <time.h>

#include "types.h"
#include "GL_utilities.h"
#include "VectorUtils3.h"

GLfloat conversionFactor; // conversion between SI units and "world units"

//physical constants
GLfloat g;
GLfloat airDensity; 
time_t programStartTime;

void physicsInit();
void moveObject(PhysicalObject* object);
void addPhysicalObject(ArchObject* obj,vec3 initialPosition, GLfloat dragCoeff, GLfloat area, GLfloat mass);

#endif
