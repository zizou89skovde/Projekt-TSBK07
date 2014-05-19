#ifndef _CAMERA_
#define _CAMERA_
#include <stdlib.h>  
#include "VectorUtils3.h"
#include "types.h"
#include "stdio.h"
#define CAM_EYE_OFFSET 7.0


CameraObject * cameraObject;

CameraObject* createCamera();
void setCameraEye(CameraObject * camObj,vec3 eye);
void attachCameraToObject(CameraObject* cObj, ArchObject* aObj);
void setCameraCenter(CameraObject * camObj,vec3 eye);
mat4 getCameraMatrix(CameraObject * camObj);

#endif
