#include "object.h"

	

void objectInit(){

	
 	physicsInit();
   	graphicsInitModels();
 	cameraObject = createCamera();

	archObjectList = malloc(MAX_NUM_OBJECTS*sizeof(ArchObject));
	numObjects = 0;
	generateTerrain(&(archObjectList[GROUND_OBJECT]), &(archObjectList[WATER_OBJECT]));	
	numObjects = numObjects + 2;

	addModel(&(archObjectList[numObjects]),"resources/groundsphere.obj", TEXTURE_GROUND,SHADER_SPHERE);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(10,40,10), 0.1 ,5,1);
	/*Bind camera position to object */
	attachCameraToObject(cameraObject,&(archObjectList[numObjects]));
	numObjects ++;


	addModel(&(archObjectList[numObjects]),"resources/groundsphere.obj", TEXTURE_GROUND,SHADER_SPHERE);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(15,15,10), 0.2 ,0.1,1);
	numObjects ++;

	//OBS: (TODO) dessa två funkt lägger till ett element i listan, se till att index matchar.




}


void updateObjectPosition(){	
	for(int i = 2; i<numObjects; i++) {
		moveObject(&(archObjectList[i].physicalObj)); 
	}	 
}

void renderObjects(){

	vec3 eye    = SetVector(0,22,0);
	vec3 center = SetVector(10,10,10);
	setCameraEye(cameraObject,eye);
	setCameraCenter(cameraObject,center);
	mat4 viewMatrix = getCameraMatrix(cameraObject);
	ModelObject m;
	/******** SPECIAL CASES *************/
	/*GROUND*/
	m = archObjectList[0].modelObj;
	graphicsTranslation(&m,0,0,0);
	graphicsDisplay(&m,viewMatrix);
	/*WATER*/
	/*m = archObjectList[1].modelObj;
	graphicsTranslation(&m,1,0,0);
	graphicsDisplay(&m,viewMatrix);*/
	/************************************/
	  
	for(int i = 2; i < numObjects; i++){
	   ModelObject model = archObjectList[i].modelObj;
  	   vec3 p = archObjectList[i].physicalObj.position;
           printf("x: %f y: %f z: %f \n",p.x,p.y,p.z);
	   graphicsTranslation(&model,p.x,p.y,p.z);
	   graphicsDisplay(&model,viewMatrix);
	}
}
