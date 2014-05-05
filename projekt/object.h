#ifndef _OBJECT_
#define _OBJECT_
#define GROUND_OBJECT 1
#define WATER_OBJECT 2	
#define MAX_NUM_OBJECTS 30

#include <stdlib.h>
#include "types.h"
#include "physics.h"
#include "camera.h"
#include "graphics.h"
#include "terrain.h"
#include "GL_utilities.h"
#include "VectorUtils3.h"

int archObjectListLength;

ArchObject * archObjectList; 

void objectInit();
void renderObjects();
void updateObjectPosition();



 #endif


