#include <math.h>
#include <time.h>


conversionFactor = 0.01; // conversion between SI units and "world units"

//physical constants
g = 9.82; // m/s^2, gravity
airDensity = 1.225; // kg/m^3 

typedef struct
{
GLfloat initialPosition[3];
GLfloat position[3];
GLfloat mass;
GLfloat dragCoeff;
GLfloat A; //area
} physicalObject;

void moveObject(Model* object, physicalObject* object);

