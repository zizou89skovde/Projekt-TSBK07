

void addPhysicalObject(ArchObject* obj,vec3 initialPosition, GLfloat dragCoeff, GLfloat area, GLfloat mass){
	obj->physicalObject->initialPosition2 = initialPosition;
	obj->physicalObject->dragCoeff = dragCoeff;
	obj->physicalObject->A = area;
	obj->physicalObject->mass = mass;

}

void moveObject(physicalObject* object) {

	time_t now;
    	time(&now);
	t = difftime(programStartTime,now); // elapsed time, counting since program started.
	
	vTerminal = sqrt((2*object.mass*g)/(airDensity*object.dragCoeff*object.A));   

	object.position[1] = object.initialPosition[1] - conversionFactor*((vTerminal/g)*log(cosh(g*t/vTerminal)));

	/*if(Objectaboveground?(terrain, object.position)) {
		//  free fall with air restistance
		
 		
		}
	else {
 		// Move along terrain
		}
*/

}



