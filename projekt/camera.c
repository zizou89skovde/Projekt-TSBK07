#include "camera.h"

CameraObject * createCamera(){
	   CameraObject * camObj = malloc(sizeof(CameraObject));

	   camObj->eye.x = 0;
	   camObj->eye.y = 0;
	   camObj->eye.z = 0;

	   camObj->center.x = 0;
	   camObj->center.y = 0;
	   camObj->center.z = 0;

	   camObj->up.x = 0;
	   camObj->up.y = 1;
	   camObj->up.z = 0;
	
	   camObj->obj = NULL;

	   return camObj;
}

void attachCameraToObject(CameraObject* cObj, ArchObject* aObj){
   	cObj->obj = aObj;
}

void deattachObject(CameraObject* cObj){
	cObj->obj = NULL;
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

mat4 getObjectFixedCameraMatrix(ArchObject* obj){
        vec3 eye = obj->physicalObj.position;
        vec3 lookDir = SetVector(1,-1,0);
	lookDir = Normalize(lookDir);
	vec3 eyeOffset = ScalarMult(lookDir,CAM_EYE_OFFSET);

	vec3 center =  SetVector(eye.x + eyeOffset.x,
				 eye.y + eyeOffset.y,
			         eye.z + eyeOffset.z);
	
	eye = SetVector(eye.x - eyeOffset.x,
			eye.y - eyeOffset.y,
			eye.z - eyeOffset.z);

	vec3 up = SetVector(0,1,0);

	mat4 camMatrix = lookAt(eye.x, eye.y, eye.z, 
 	     		        center.x, center.y, center.z,
			        up.x, up.y, up.z);

	return camMatrix;
}
mat4 getCameraMatrix(CameraObject * camObj){
	mat4 camMatrix;
	if(camObj->obj == NULL){
		camMatrix = lookAt(camObj->eye.x, camObj->eye.y, camObj->eye.z, 
 	     		           camObj->center.x, camObj->center.y, camObj->center.z,
			           camObj->up.x, camObj->up.y, camObj->up.z);
	}else{
		camMatrix =getObjectFixedCameraMatrix(camObj->obj);
	}
	return camMatrix;
}



