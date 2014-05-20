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
        		
	vec3 defEyeOffset = SetVector(0,2,-6); 
	vec3 eyeOffset = VectorSub(defEyeOffset,ScalarMult(obj->physicalObj.velocity,3*obj->physicalObj.helpAngle));    

	vec3 center = obj->physicalObj.position; 
	mat3 rotationEye = mat4tomat3(Ry(obj->physicalObj.helpAngle)); 
	
	vec3 newOffset = MultMat3Vec3(rotationEye,defEyeOffset);
	
	vec3 eye = VectorAdd(obj->physicalObj.position,newOffset);
	
	vec3 up = SetVector(0,1,0);

	mat4 camMatrix = lookAt(eye.x, eye.y, eye.z, 
 	     		        center.x, center.y, center.z,
			        up.x, up.y, up.z);

	cameraObject->eye = eye;
	cameraObject->center = center;
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



