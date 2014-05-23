#include "physics.h"


struct timespec tZero, tOne;
TextureData asdf;
TextureData* terrainTexture = &asdf;
void physicsInit(){
	//time(&programStartTime);
	conversionFactor = 0.01;
	g = 9.82; // m/s^2, gravity
	airDensity = 1.225; // kg/m^3 
	functionCallCount = 0;

	LoadTGATextureData("resources/terrainmap.tga", terrainTexture); 	
}

void addPhysicalObject(ArchObject* obj,vec3 initialPosition, vec3 initialRotationAxis, GLfloat initialRotationAngle, GLfloat dragCoeff, GLfloat area, GLfloat mass, int isChar,void (*fp)(void *)){
	obj->physicalObj.initialPosition = initialPosition;
	obj->physicalObj.rotationMat = ArbRotate(initialRotationAxis,initialRotationAngle);
	obj->physicalObj.velocity = SetVector(0,0,0);
	obj->physicalObj.helpAngle = 0;	
	obj->physicalObj.tiltAngle = 0;
	obj->physicalObj.position = initialPosition;
	obj->physicalObj.dragCoeff = dragCoeff;
	obj->physicalObj.A = area;
	obj->physicalObj.mass = mass;
	obj->physicalObj.updateFunc = fp;
	obj->physicalObj.isChar = isChar;
}



void staticObject(void *arg){
	PhysicalObject* object = (PhysicalObject*)arg;
	object->position = object->position;
}

void addStaticPhysicalObject(ArchObject* obj,vec3 initialPosition){
	obj->physicalObj.initialPosition = initialPosition;
	obj->physicalObj.rotationMat = ArbRotate(SetVector(0,0,0),0);
	obj->physicalObj.velocity = SetVector(0,0,0);
	obj->physicalObj.position = initialPosition;
	obj->physicalObj.dragCoeff = 0;
	obj->physicalObj.A = 0;
	obj->physicalObj.mass = 0;
	obj->physicalObj.updateFunc = &staticObject;
	obj->physicalObj.isChar = 0;

}


void moveObject(void * arg) {
	
	

	GLfloat dt= 1;
	PhysicalObject* object = (PhysicalObject* )arg;
	

	if(checkCollision(object) == 0){

		//Spara ner tid första gången funk. anropas
		if(functionCallCount==0){ 
			clock_gettime(CLOCK_REALTIME, &tZero);
			functionCallCount ++;
			}

		//Hantera tbord input om objectet är char.
		if(object->isChar){
			handleKeyboardInput(cameraObject,object); // also input cameraobject later
		}
			
		clock_gettime(CLOCK_REALTIME, &tOne);	
		double tNano =  (double)(BILLION)*(tOne.tv_sec - tZero.tv_sec) + (double)(tOne.tv_nsec - tZero.tv_nsec);
	
		GLfloat vTerminal = sqrt((2*object->mass*g)/(airDensity*object->dragCoeff*object->A));   

		double t = tNano/BILLION;
	
		double velocityDown = -vTerminal*tanh(g*t/vTerminal);
		object->velocity.y = 0.05*velocityDown;		
		//object->position.y = object->initialPosition.y - ((vTerminal*vTerminal/g)*log(cosh(g*t/vTerminal))); //0.5*g*t*t; 
		object->position = VectorAdd(object->position,object->velocity);
  	}
	else
		printf("Collision: %f \n" ,1.0); 

	//printf("t: %f asdf: %f vTerm: %f \n ",(float)t, (float)asdf, (float)vTerminal);
}



int checkCollision(PhysicalObject* object){


		
		int indexX,indexZ;   
                GLfloat terrainHeight;
                GLfloat topLeftPosX,topLeftPosZ;

                int WIDTH = groundData.dimX / groundData.resolution;

		
		float xUnitPerPixel = WORLD_SIZE /terrainTexture->width;
		float zUnitPerPixel = WORLD_SIZE /terrainTexture->height;
		int xPositionModWorldSize = (int)(object->position.x) % (int)WORLD_SIZE;
		int zPositionModWorldSize = (int)(object->position.z) % (int)WORLD_SIZE;
		if( xPositionModWorldSize < 0)
		   xPositionModWorldSize += WORLD_SIZE;
		if( zPositionModWorldSize < 0)
		   zPositionModWorldSize += WORLD_SIZE;
	
		int xObjectPixelPos = (int)(xPositionModWorldSize/xUnitPerPixel);
		int zObjectPixelPos = (int)(zPositionModWorldSize/zUnitPerPixel);
		printf(" xpizel %f , zpixel %f perpixel %f  \n", (float)xObjectPixelPos, (float)zObjectPixelPos, xUnitPerPixel);
 
	

                 terrainHeight = terrainTexture->imageData[(xObjectPixelPos + zObjectPixelPos * terrainTexture->width)*(terrainTexture->bpp/8)] / 255.0 *HEIGHT_SCALE;
/*		
                                        groundData.vertexArray[(indexX +1 + (indexZ + 1) * WIDTH)*3 +1] +                                      
                                        groundData.vertexArray[(indexX +1 + (indexZ) * WIDTH)*3 +1] +                                  
                                        groundData.vertexArray[(indexX + (indexZ + 1) * WIDTH)*3 +1])/3;
		
                 
                }else{
                        terrainHeight = (
                                        groundData.vertexArray[(indexX + (indexZ) * WIDTH)*3 +1] +                                     
                                        groundData.vertexArray[(indexX +1 + (indexZ) * WIDTH)*3 +1] +                                  
                                        groundData.vertexArray[(indexX + (indexZ + 1) * WIDTH)*3 +1])/3;       

                }*/

		printf("terrainHeight: %f object y %f \n", terrainHeight, object->position.y);

	if(object->position.y <= terrainHeight)
		return 1;
	else
		return 0;

}


