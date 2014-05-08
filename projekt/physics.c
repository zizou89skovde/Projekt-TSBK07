#include "physics.h"


struct timespec tZero, tOne;

void physicsInit(){
	//time(&programStartTime);
	conversionFactor = 0.01;
	g = 9.82; // m/s^2, gravity
	airDensity = 1.225; // kg/m^3 
	functionCallCount = 0;

}

void addPhysicalObject(ArchObject* obj,vec3 initialPosition, GLfloat dragCoeff, GLfloat area, GLfloat mass){
	obj->physicalObj.initialPosition = initialPosition;
	obj->physicalObj.position 	 = initialPosition;
	obj->physicalObj.dragCoeff = dragCoeff;
	obj->physicalObj.A = area;
	obj->physicalObj.mass = mass;
}



void moveObject(PhysicalObject* object) {



   // printf("Filtering took: %g secs\n", (etime.tv_sec  - stime.tv_sec) +
   //	   1e-9*(etime.tv_nsec  - stime.tv_nsec)) ;


	if(functionCallCount==0){ 
		clock_gettime(CLOCK_REALTIME, &tZero);
		functionCallCount ++;
		}
	/*else  if (functionCallFlag==1) {
		clock_gettime(CLOCK_REALTIME, &tOne);
		callPeriod = (double)BILLION)*(tOne.tv_sec - tZero.tv_sec) + (double)(tOne.tv_nsec - tZero.tv_nsec); 
		functionCallFlag = 0;
	}*/
		
	clock_gettime(CLOCK_REALTIME, &tOne);	
	double tNano =  (double)(BILLION)*(tOne.tv_sec - tZero.tv_sec) + (double)(tOne.tv_nsec - tZero.tv_nsec);
	
	GLfloat vTerminal = sqrt((2*object->mass*g)/(airDensity*object->dragCoeff*object->A));   

	double t = tNano/BILLION;
	

	object->position.y = object->initialPosition.y - ((vTerminal*vTerminal/g)*log(cosh(g*t/vTerminal))); //0.5*g*t*t; 
	


	double asdf = (vTerminal/g)*log(cosh(g*t/vTerminal));

    

printf("t: %f asdf: %f vTerm: %f \n ",(float)t, (float)asdf, (float)vTerminal);
	






	/*if(Objectaboveground?(terrain, object.position)) {
		//  free fall with air restistance
		
 		
		}
	else {
 		// Move along terrain
		}
*/

}



