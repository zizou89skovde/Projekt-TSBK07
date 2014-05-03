#include "camera.h"



CameraObject * createCamera(){

   CameraObject * camObj = malloc(sizeof(CameraObject));

   camObj->eye.x = 0;
   camObj->eye.y = 0;
   camObj->eye.z = 0;

   camObj->center.x = 0;
   camObj->center.y = 0;
   camObj->center.z = 0;

   camObj->center.x = 0;
   camObj->center.y = 0;
   camObj->center.z = 0;

   camObj->up.x = 0;
   camObj->up.y = 1;
   camObj->up.z = 0;

   return camObj;

}


void setCameraEye(CameraObject * camObj,vec3 eye){
	camObj->eye.x = eye.x;
	camObj->eye.y = eye.y;
	camObj->eye.z = eye.z;
}

void setCameraCenter(CameraObject * camObj,vec3 center){
	camObj->center.x = center.x;
	camObj->center.y = center.y;
	camObj->center.z = center.z;
}

mat4 getCameraMatrix(CameraObject * camObj){

	mat4 camMatrix = lookAt(camObj->eye.x, camObj->eye.y, camObj->eye.z, 
    			        camObj->center.x, camObj->center.y, camObj->center.z,
			        camObj->up.x, camObj->up.y, camObj->up.z);
	return camMatrix;
}

