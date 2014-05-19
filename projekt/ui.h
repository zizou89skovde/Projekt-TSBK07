#ifndef _UI_
#define _UI_

#include "MicroGlut.h"
#include "GL_utilities.h"
#include "VectorUtils3.h"
#include "camera.h"
#include "stdio.h"
#include <time.h>

#define BILLION  1000000000L


GLfloat oldMouseX,oldMouseY;

void handleMouseInput(int x ,int y);
void handleKeyboardInput(CameraObject * camObj,PhysicalObject* physObj);
// also take CameraObject * cameraObject, as input later

int rotationInProgress;
int multiPressGuard;


#endif
