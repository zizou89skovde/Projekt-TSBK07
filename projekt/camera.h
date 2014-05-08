#ifndef _CAMERA_
#define _CAMERA_
#include <stdlib.h>  
#include "VectorUtils3.h"
#include "types.h"
#define CAM_EYE_OFFSET 10.0
typedef struct{
vec3 eye;
vec3 center;
vec3 up;
ArchObject* obj;
}CameraObject;

CameraObject * cameraObject;

CameraObject* createCamera();
void setCameraEye(CameraObject * camObj,vec3 eye);
void AttachCameraToObject(CameraObject* cObj, ArchObject* aObj);
void setCameraCenter(CameraObject * camObj,vec3 eye);
mat4 getCameraMatrix(CameraObject * camObj);

#endif
