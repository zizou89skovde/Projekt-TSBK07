#ifndef _CAMERA_
#define _CAMERA_
#include <stdlib.h>  
#include "VectorUtils3.h"
typedef struct{
vec3 eye;
vec3 center;
vec3 up;

}CameraObject;

CameraObject * cameraObject;

CameraObject* createCamera();
void setCameraEye(CameraObject * camObj,vec3 eye);
void setCameraCenter(CameraObject * camObj,vec3 eye);
mat4 getCameraMatrix(CameraObject * camObj);

#endif
