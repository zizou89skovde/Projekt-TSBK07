#ifndef _UI_
#define _UI_

#include "MicroGlut.h"
#include "GL_utilities.h"
#include "VectorUtils3.h"
#include "camera.h"


GLfloat oldMouseX,oldMouseY;

void handleMouseInput(int x ,int y);
void handleKeyboardInput(CameraObject * cameraObject);


#endif
