#include "object.h"

	

void objectInit(){

	
 	physicsInit();
   	graphicsInitModels();
 	cameraObject = createCamera();

	archObjectList = malloc(MAX_NUM_OBJECTS*sizeof(ArchObject));

	numObjects = 0;
	//generateTerrain(&(archObjectList[GROUND_OBJECT]), &(archObjectList[WATER_OBJECT]));	
	//numObjects = numObjects + 2;

	addModel(&(archObjectList[numObjects]),"resources/skybox.obj", TEXTURE_SKYBOX,SHADER_SKYBOX, &graphicsDisplaySkybox);
	numObjects ++;

	addModel(&(archObjectList[numObjects]),"resources/TEST_OHLY.obj", TEXTURE_TERRAIN,SHADER_TERRAIN_LOD, &graphicsDisplay);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(0.1,0,0), 1 ,0.1,10);
	numObjects ++;

	/*Bind camera position to object */
	//attachCameraToObject(cameraObject,&(archObjectList[numObjects]));


	//OBS: (TODO) dessa två funkt lägger till ett element i listan, se till att index matchar.

}


void updateObjectPosition(){	
	for(int i = 2; i<numObjects; i++) {
		moveObject(&(archObjectList[i].physicalObj)); 
	}	 
}

void renderObjects(){

	vec3 eye    = SetVector(0,50,0);
	vec3 center = SetVector(30,0,30);
	setCameraEye(cameraObject,eye);
	setCameraCenter(cameraObject,center);
	mat4 viewMatrix = getCameraMatrix(cameraObject);
	
	/******** SPECIAL CASES *************
	//SKYBOX 
	ModelObject m;
	m = archObjectList[SKYBOX_OBJECT].modelObj;
	graphicsSkyboxDisplay(&m, viewMatrix);

	//GROUND
	m = archObjectList[GROUND_OBJECT].modelObj;
	graphicsTranslation(&m,0,0,0);
	graphicsDisplay(&m,viewMatrix);

	//WATER
	m = archObjectList[WATER_OBJECT].modelObj;
	graphicsTranslation(&m,1,0,0);
	graphicsDisplay(&m,viewMatrix);


	************************************/
	  
	for(int i = 0; i < numObjects; i++){
	   ModelObject model = archObjectList[i].modelObj;
  	   vec3 p = archObjectList[i].physicalObj.position;
           printf("x: %f y: %f z: %f \n",p.x,p.y,p.z);
	   graphicsTranslation(&model,p.x,p.y,p.z);
	/*if(i != WATER_OBJECT)*/
	   model.renderFunc((void*)(&model), viewMatrix);  // graphicsDisplay(&model,viewMatrix);
	}
}
