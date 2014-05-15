#include "object.h"

	

void objectInit(){

       
 	physicsInit();
   	graphicsInitModels();
 	cameraObject = createCamera();
	/*debug*/
	setCameraEye(cameraObject,SetVector(0,60,0));
	setCameraCenter(cameraObject,SetVector(50,20,50));
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


	
	/* Char */
	addModel(&(archObjectList[numObjects]),"resources/char.obj", TEXTURE_CHAR,SHADER_CHAR,&graphicsDisplay);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(10,60,40), 0.2 ,10,1,&moveObject);
	//attachCameraToObject(cameraObject,&(archObjectList[numObjects]));
	numObjects ++;


/*

"resources/grid_100x100_66049v.obj"
"resources/grid_100x100_16641v.obj"
"resources/grid_100x100_4225v.obj"

"resources/grid_200x200_4225v.obj"

"resources/grid_400x400_1089v.obj"

"resources/grid_800x800_289v.obj"
"resources/grid_800x800_1089v.obj"

"resources/grid_1600x1600_81v.obj"
"resources/grid_1600x1600_1089v.obj",	

*/
	/* LOD */
	int MAX_NUM_GRIDS = 6;
	char *grids[] = {
		        "resources/grid_100x100_4225v.obj",
		        "resources/grid_100x100_4225v.obj",
		        "resources/grid_200x200_4225v.obj",
		        "resources/grid_400x400_1089v.obj",
			"resources/grid_800x800_1089v.obj",
			"resources/grid_1600x1600_1089v.obj"	
	   	};


	/* High res */
	addModel(&(archObjectList[numObjects]),grids[0], TEXTURE_TERRAIN_LOD,SHADER_TERRAIN_LOD, &drawTerrain);
	addPhysicalObject(&(archObjectList[numObjects]),SetVector(0,0,0), 1 ,0.1,10,&staticObject);
	numObjects ++;

	/* Low res */
	for(int i = 1; i < MAX_NUM_GRIDS-1; i++){
		addModel(&(archObjectList[numObjects]),grids[i], TEXTURE_TERRAIN_LOD,SHADER_TERRAIN_LOD, &drawTerrain);
		addPhysicalObject(&(archObjectList[numObjects]),SetVector(pow(2,i-1)*GRID_SIZE,0,0), 1 ,0.1,10,&staticObject);
		numObjects ++;

		addModel(&(archObjectList[numObjects]),grids[i], TEXTURE_TERRAIN_LOD,SHADER_TERRAIN_LOD, &drawTerrain);
		addPhysicalObject(&(archObjectList[numObjects]),SetVector(pow(2,i-1)*GRID_SIZE,0,pow(2,i-1)*GRID_SIZE), 1 ,0.1,10,&staticObject);
		numObjects ++;

		addModel(&(archObjectList[numObjects]),grids[i], TEXTURE_TERRAIN_LOD,SHADER_TERRAIN_LOD, &drawTerrain);
		addPhysicalObject(&(archObjectList[numObjects]),SetVector(0,0,pow(2,i-1)*GRID_SIZE), 1 ,0.1,10,&staticObject);
		numObjects ++;	
	}

	/* Clouds */
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
