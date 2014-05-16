#include "physics.h"


struct timespec tZero, tOne;

void physicsInit(){
	//time(&programStartTime);
	conversionFactor = 0.01;
	g = 9.82; // m/s^2, gravity
	airDensity = 1.225; // kg/m^3 
	functionCallCount = 0;

}

void addPhysicalObject(ArchObject* obj,vec3 initialPosition, GLfloat dragCoeff, GLfloat area, GLfloat mass,void (*fp)(void *)){
	obj->physicalObj.initialPosition = initialPosition;
	obj->physicalObj.position 	 = initialPosition;
	obj->physicalObj.dragCoeff = dragCoeff;
	obj->physicalObj.A = area;
	obj->physicalObj.mass = mass;
	obj->physicalObj.updateFunc = fp;
}

void staticObject(void *arg){
	PhysicalObject* object = (PhysicalObject*)arg;
	object->position = object->position;
}
/*
void moveLODTerrain(void *arg){

	PhysicalObject* object = (PhysicalObject*)arg;


	object.position = camObject.eye - offset;

	
	
}*/


void moveObject(void * arg) {
	PhysicalObject* object = (PhysicalObject* )arg;
	if(functionCallCount==0){ 
		clock_gettime(CLOCK_REALTIME, &tZero);
		functionCallCount ++;
		}
			
	clock_gettime(CLOCK_REALTIME, &tOne);	
	double tNano =  (double)(BILLION)*(tOne.tv_sec - tZero.tv_sec) + (double)(tOne.tv_nsec - tZero.tv_nsec);
	
	GLfloat vTerminal = sqrt((2*object->mass*g)/(airDensity*object->dragCoeff*object->A));   

	double t = tNano/BILLION;
	

	object->position.y = object->initialPosition.y - ((vTerminal*vTerminal/g)*log(cosh(g*t/vTerminal))); //0.5*g*t*t; 
	object->velocity = SetVector(0,-1,0);



    

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



