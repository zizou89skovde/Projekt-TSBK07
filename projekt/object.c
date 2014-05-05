#include "object.h"

	

void objectInit(){

	
 	physicsInit();
   	graphicsInitModels();
 	cameraObject = createCamera();

	archObjectList = malloc(MAX_NUM_OBJECTS*sizeof(ArchObject));

	archObjectListLength = 0;
	generateTerrain(&(archObjectList[GROUND_OBJECT]), &(archObjectList[WATER_OBJECT]));	
	archObjectListLength = archObjectListLength + 2;
	addModel(&(archObjectList[0]),"resources/groundsphere.obj", TEXTURE_GROUND,SHADER_SPHERE);
	//OBS: (TODO) dessa två funkt lägger till ett element i listan, se till att index matchar.
	
	//addPhysicalObject(&(archObjectList[0]),SetVector(1,2,3), 1,1,1);
	archObjectListLength ++;


}


void updateObjectPosition(){	
	for(int i = 0; i<archObjectListLength; i++) { moveObject(&(archObjectList[i].physicalObj)); }	 
}

void renderObjects(){
   ModelObject m = archObjectList[0].modelObj;

   vec3 eye    = SetVector(0,10,0);
   vec3 center = SetVector(1,0,0);
   setCameraEye(cameraObject,eye);
   setCameraCenter(cameraObject,center);
   mat4   viewMatrix = getCameraMatrix(cameraObject);

   graphicsTranslation(&m,1,0,0);
   graphicsDisplay(&m,viewMatrix);
  
   ModelObject m2 = archObjectList[GROUND_OBJECT].modelObj;
   graphicsTranslation(&m2,0,0,0);
   graphicsDisplay(&m2,viewMatrix);
}
