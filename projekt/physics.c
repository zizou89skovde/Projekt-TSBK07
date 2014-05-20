#include "physics.h"


struct timespec tZero, tOne;

void physicsInit(){
	//time(&programStartTime);
	conversionFactor = 0.01;
	g = 9.82; // m/s^2, gravity
	airDensity = 1.225; // kg/m^3 
	functionCallCount = 0;

}

void addPhysicalObject(ArchObject* obj,vec3 initialPosition, vec3 initialRotationAxis, GLfloat initialRotationAngle, GLfloat dragCoeff, GLfloat area, GLfloat mass, int isChar,void (*fp)(void *)){
	obj->physicalObj.initialPosition = initialPosition;
	obj->physicalObj.rotationMat = ArbRotate(initialRotationAxis,initialRotationAngle);
	obj->physicalObj.velocity = SetVector(0,0,0);
	obj->physicalObj.helpAngle = 0;	
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



    

	//printf("t: %f asdf: %f vTerm: %f \n ",(float)t, (float)asdf, (float)vTerminal);
	
/*
	time_t now;
    	time(&now);
	time_t t = difftime(programStartTime,now); // elapsed time, counting since program started.
	programStartTime = now;
	GLfloat vTerminal = sqrt((2*object->mass*g)/(airDensity*object->dragCoeff*object->A));  
	clock_t ct = clock(); 
	printf("t: %f ct: %f", (float)t,(float)(ct/CLOCKS_PER_SEC));
	object->position.y = object->initialPosition.y - conversionFactor*((vTerminal/g)*log(cosh(g*t/vTerminal)));
	*/

	/*if(Objectaboveground?(terrain, object.position)) {
		//  free fall with air restistance
		
 		
		}
	else {
 		// Move along terrain
		}
*/

}



