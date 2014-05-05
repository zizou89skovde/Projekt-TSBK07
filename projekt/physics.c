#include "physics.h"

void physicsInit(){
	time(&programStartTime);
	conversionFactor = 0.01;
	g = 9.82; // m/s^2, gravity
	airDensity = 1.225; // kg/m^3 
}

void addPhysicalObject(ArchObject* obj,vec3 initialPosition, GLfloat dragCoeff, GLfloat area, GLfloat mass){
	obj->physicalObj.initialPosition = initialPosition;
	obj->physicalObj.dragCoeff = dragCoeff;
	obj->physicalObj.A = area;
	obj->physicalObj.mass = mass;
}

void moveObject(PhysicalObject* object) {

	time_t now;
    	time(&now);
	time_t t = difftime(programStartTime,now); // elapsed time, counting since program started.
	
	GLfloat vTerminal = sqrt((2*object->mass*g)/(airDensity*object->dragCoeff*object->A));   

	object->position.y = object->initialPosition.y - conversionFactor*((vTerminal/g)*log(cosh(g*t/vTerminal)));

	/*if(Objectaboveground?(terrain, object.position)) {
		//  free fall with air restistance
		
 		
		}
	else {
 		// Move along terrain
		}
*/

}



