#include "object.h"

	

void objectInit(){

       
 	physicsInit();
   	graphicsInitModels();
 	cameraObject = createCamera();

	/*debug*/
	setCameraEye(cameraObject,SetVector(0,40,0));
	setCameraCenter(cameraObject,SetVector(50,40,0));
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
	numObjects++;
	*/
	initializeTerrain(archObjectList, &numObjects);
	
	/* Char */
	addModel(&(archObjectList[numObjects]),"resources/char.obj", TEXTURE_CHAR,SHADER_CHAR,&graphicsDisplay);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(200,80,600), 0.2 ,10,1,&moveObject);
	numObjects ++;

	/* Clouds */

	addModel(&(archObjectList[numObjects]),"resources/square.obj", TEXTURE_CLOUDS,SHADER_PARTICLE,&drawInstanced);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(0,80,1000), 0.2 ,0.1,1,&staticObject);
	addParticleSystem(&(archObjectList[numObjects]),CLUSTER,100,&updateParticles);
	numObjects ++;

	/*addModel(&(archObjectList[numObjects]),"resources/square.obj", TEXTURE_CLOUDS,SHADER_PARTICLE,&drawInstanced);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(-150,100,500), 0.2 ,0.1,1,&staticObject);
	addParticleSystem(&(archObjectList[numObjects]),CLUSTER,100,&updateParticles);
	numObjects ++;

	addModel(&(archObjectList[numObjects]),"resources/square.obj", TEXTURE_CLOUDS,SHADER_PARTICLE,&drawInstanced);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(0,100,450), 0.2 ,0.1,1,&staticObject);
	addParticleSystem(&(archObjectList[numObjects]),CLUSTER,100,&updateParticles);
	numObjects ++;

	addModel(&(archObjectList[numObjects]),"resources/square.obj", TEXTURE_CLOUDS,SHADER_PARTICLE,&drawInstanced);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(0,100,400), 0.2 ,0.1,1,&staticObject);
	addParticleSystem(&(archObjectList[numObjects]),CLUSTER,100,&updateParticles);
	numObjects ++;

	addModel(&(archObjectList[numObjects]),"resources/square.obj", TEXTURE_CLOUDS,SHADER_PARTICLE,&drawInstanced);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(150,150,305), 0.2 ,0.1,1,&staticObject);
	addParticleSystem(&(archObjectList[numObjects]),CLUSTER,100,&updateParticles);
	numObjects ++;*/



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
	   model.renderFunc((void*)(&model), viewMatrix);  
	}
}
