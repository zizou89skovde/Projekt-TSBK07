#include "object.h"

	

void objectInit(){

	
 	physicsInit();
   	graphicsInitModels();
 	cameraObject = createCamera();

	archObjectList = malloc(MAX_NUM_OBJECTS*sizeof(ArchObject));

	archObjectListLength = 0;
	//generateTerrain(&(archObjectList[GROUND_OBJECT]), &(archObjectList[WATER_OBJECT]));	
	//archObjectListLength = archObjectListLength + 2;

	//OBS: (TODO) dessa två funkt lägger till ett element i listan, se till att index matchar.
	addModel(&(archObjectList[0]),"resources/groundsphere.obj", MODEL_GUBBE, TEXTURE_GROUND,SHADER_SPHERE);
	//addPhysicalObject(&(archObjectList[0]),SetVector(1,2,3), 1,1,1);
	archobjectListLength ++;


}


void updateObjectPosition(){	
	for(i = 0; i<archObjectListLength; i++) { moveObject(archObjectList[i]->PhysicalObj) }	 
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
