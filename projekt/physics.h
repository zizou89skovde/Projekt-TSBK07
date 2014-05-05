#include <math.h>
#include <time.h>


conversionFactor = 0.01; // conversion between SI units and "world units"

//physical constants
g = 9.82; // m/s^2, gravity
airDensity = 1.225; // kg/m^3 

typedef struct
{
	GLfloat initialPosition[3];
	vec3 initialPosition2;
	GLfloat* position;
	GLfloat mass;
	GLfloat dragCoeff;
	GLfloat A; //area
} PhysicalObject;

void moveObject(PhysicalObject* object);

