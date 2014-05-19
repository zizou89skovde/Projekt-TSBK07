#include "object.h"

	

void objectInit(){

       
 	physicsInit();
   	graphicsInitModels();
 	cameraObject = createCamera();

	/*debug*/
	setCameraEye(cameraObject,SetVector(0,40,0));
	setCameraCenter(cameraObject,SetVector(0,40,50));
	numObjects = 0;

	archObjectList = malloc(MAX_NUM_OBJECTS*sizeof(ArchObject));

	addModel(&(archObjectList[numObjects]),"resources/skybox.obj", TEXTURE_SKYBOX,SHADER_SKYBOX, &graphicsDisplaySkybox);
	addStaticPhysicalObject(&(archObjectList[numObjects]),SetVector(0,0,0));
	numObjects ++;
	/*
	generateTerrain(&(archObjectList[GROUND_OBJECT]), &(archObjectList[WATER_OBJECT]));	
	numObjects = numObjects + 2;*/

	

	/*
	addModel(&(archObjectList[numObjects]),"resources/groundsphere.obj", TEXTURE_GROUND,SHADER_SPHERE,&graphicsDisplay);
addPhysicalObject(&(archObjectList[numObjects]),SetVector(10,10,10),SetVector(10,10,10),0, 0.1 ,100,1,0,&moveObject);
	numObjects++;
	*/
	initializeTerrain(archObjectList, &numObjects);

	
	/* Character */
	addModel(&(archObjectList[numObjects]),"resources/char.obj", TEXTURE_CHAR,SHADER_CHAR,&graphicsDisplay);
	//addModel(&(archObjectList[numObjects]),"resources/char.obj", TEXTURE_CHAR,SHADER_CHAR,&graphicsDisplay);
addPhysicalObject(&(archObjectList[numObjects]),SetVector(20,70,20),SetVector(1,0,0),1.3, 0.2 ,100,1,1,&moveObject);
attachCameraToObject(cameraObject,&(archObjectList[numObjects]));	
numObjects ++;

	/* Clouds */
	addModel(&(archObjectList[numObjects]),"resources/square.obj", TEXTURE_CLOUDS,SHADER_PARTICLE,&drawInstanced);
	addStaticPhysicalObject(&(archObjectList[numObjects]),SetVector(0,0,0));
	addParticleSystem(&(archObjectList[numObjects]),10,&updateParticles);
	numObjects ++;

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
	   PhysicalObject obj = archObjectList[i].physicalObj;
	   graphicsRotation(&model, obj.rotationMat); 
	   graphicsTranslation(&model,p.x,p.y,p.z); 
	   model.renderFunc((void*)(&model), viewMatrix);  
	}
}
