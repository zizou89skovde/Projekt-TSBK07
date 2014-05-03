

void moveObject(Model* object, physicalObject* object) {

	time_t now;
    	time(&now);
	t = difftime(programStartTime,now); // elapsed time 
	
	vTerminal = sqrt((2*object.mass*g)/(airDensity*object.dragCoeff*object.A));   


	if(Objectaboveground?(terrain, object.position)) {
		//  free fall with air restistance
		object.position[1] = object.initialPosition[1] - conversionFactor*((vTerminal/g)*log(cosh(g*t/vTerminal)));
 		
		}
	else {
 		// Move along terrain
		}

}


