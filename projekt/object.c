#include "object.h"

	

void objectInit(){

       
 	physicsInit();
   	graphicsInitModels();
 	cameraObject = createCamera();
	/*debug*/
	setCameraEye(cameraObject,SetVector(0,60,40));
	setCameraCenter(cameraObject,SetVector(10,40,40));
	numObjects = 0;

	archObjectList = malloc(MAX_NUM_OBJECTS*sizeof(ArchObject));
	addModel(&(archObjectList[numObjects]),"resources/skybox.obj", TEXTURE_SKYBOX,SHADER_SKYBOX, &graphicsDisplaySkybox);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(10,10,10), 1 ,0.1,10,&staticObject);
	numObjects ++;
	/*
	generateTerrain(&(archObjectList[GROUND_OBJECT]), &(archObjectList[WATER_OBJECT]));	
	numObjects = numObjects + 2;*/

	/*
	addModel(&(archObjectList[numObjects]),"resources/groundsphere.obj", TEXTURE_GROUND,SHADER_SPHERE,&graphicsDisplay);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(10,60,10), 0.1 ,5,1,&moveObject);
	/*Bind camera position to object */
	//numObjects++;

	addModel(&(archObjectList[numObjects]),"resources/char.obj", TEXTURE_CHAR,SHADER_CHAR,&graphicsDisplay);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(10,60,40), 0.2 ,10,1,&moveObject);
	//attachCameraToObject(cameraObject,&(archObjectList[numObjects]));
	numObjects ++;
 
	addModel(&(archObjectList[numObjects]),"resources/mesh_lod.obj", TEXTURE_TERRAIN,SHADER_TERRAIN_LOD, &drawTerrain);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(0,0,0), 1 ,0.1,10,&staticObject);
	numObjects ++;
/*
	addModel(&(archObjectList[numObjects]),"resources/TEST_OHLY.obj", TEXTURE_TERRAIN,SHADER_TERRAIN_LOD, &drawTerrain);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(40,0,0), 1 ,0.1,10,&staticObject);
	numObjects ++;

	addModel(&(archObjectList[numObjects]),"resources/TEST_OHLY.obj", TEXTURE_TERRAIN,SHADER_TERRAIN_LOD, &drawTerrain);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(40,0,40), 1 ,0.1,10,&staticObject);
	numObjects ++;
	addModel(&(archObjectList[numObjects]),"resources/TEST_OHLY.obj", TEXTURE_TERRAIN,SHADER_TERRAIN_LOD, &drawTerrain);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(0,0,40), 1 ,0.1,10,&staticObject);
	numObjects ++;

	addModel(&(archObjectList[numObjects]),"resources/groundsphere.obj", TEXTURE_GROUND,SHADER_SPHERE, &graphicsDisplay);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(10,10,10), 1 ,0.1,10,&moveObject);
	numObjects ++;
*/
	addModel(&(archObjectList[numObjects]),"resources/square.obj", TEXTURE_CLOUDS,SHADER_PARTICLE,&drawInstanced);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(0.01,0,0), 0.2 ,0.1,1,&staticObject);
	addParticleSystem(&(archObjectList[numObjects]),10,&updateParticles);
//	attachCameraToObject(cameraObject,&(archObjectList[numObjects]));
	numObjects ++;


	/*Bind camera position to object */
	//attachCameraToObject(cameraObject,&(archObjectList[numObjects]));


	//OBS: (TODO) dessa två funkt lägger till ett element i listan, se till att index matchar.

}


void updateObjectPosition(){	

	PhysicalObject * po;
	ParticleSystem * ps;

	for(int i = 0; i<numObjects; i++) {
		
		/*update physics*/
		po = &(archObjectList[i].physicalObj);	
		po->updateFunc((void *)po);
			
		/*update particles*/
		ps = &(archObjectList[i].particleSystem);
		if(ps->numParticles > 0){
			ps->updateFunc((void *)&archObjectList[i],(void *)cameraObject);
		}
	}	 
}

void renderObjects(){


	mat4 viewMatrix = getCameraMatrix(cameraObject);
	
	for(int i = 0; i < numObjects; i++){
	   ModelObject model = archObjectList[i].modelObj;
  	   vec3 p = archObjectList[i].physicalObj.position;  
	   graphicsTranslation(&model,p.x,p.y,p.z);
	  // printf("p y: %f \n",p.y);  
	   model.renderFunc((void*)(&model), viewMatrix);  
	}
}
