#include "object.h"


void objectInit(){
 	physicsInit();
   	graphicsInitModels();
 	cameraObject = createCamera();

	archObjectList = malloc(MAX_NUM_OBJECTS*sizeof(ArchObject));
	addModel(&(archObjectList[0]),"resources/groundsphere.obj", TEXTURE_GROUND,SHADER_SPHERE);
 	//generateTerrain(&(archObjectList[GROUND_OBJECT]), &(archObjectList[WATER_OBJECT]));	
	//addPhysicalObject(&(archObjectList[0]),SetVector(1,2,3), 1,1,1);
}

void updateObjectPosition(){

}

void renderObjects(){
   ModelObject m = archObjectList[0].modelObj;
   vec3 eye    = SetVector(5,0,0);
   vec3 center = SetVector(1,0,1);
   setCameraEye(cameraObject,eye);
   setCameraCenter(cameraObject,center);
   graphicsTranslation(&m,1,0,1);
   graphicsDisplay(&m,getCameraMatrix(cameraObject));
}
