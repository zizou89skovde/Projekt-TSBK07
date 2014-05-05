//#include <OpenGL/gl3.h>
//#include "include/MicroGlut.h"
#include "GL_utilities.h"
#include "VectorUtils3.h"
#include "loadobj.h"
#include "LoadTGA.h"
#include "ui.h"
#include "object.h"
#include "textures.h"
#include "shaders.h"
#include "camera.h"
#include "terrain.h"


#define UPDATE_FREQUENCY 20.0
 

void init()
{

    glClearColor(0.2,0.2,0.5,0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    printError("GL inits");

    textureInit();
    shaderInit();

    objectInit();
  
    cameraObject = createCamera();
    
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  renderObjects();
  glutSwapBuffers();
   
}


void update(int i)
{
	/* h�rifr�n kan update-funktioner cycliskt anropas med frekvensen UPDATE_FREQUENCY */
	//handleKeyboardInput(cameraObject);
	glutTimerFunc(UPDATE_FREQUENCY, &update, i);
	glutPostRedisplay();
	updateObjectPosition();
}

void mouse(int x,int y){
	//handleMouseInput(x,y);
}


int main(int argc, char **argv)
{


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitContextVersion(3, 2);

	glutInitWindowSize (1080, 1080);
	glutCreateWindow ("TSBK07 Lab 4");
	glutDisplayFunc(display);
	init();
	initKeymapManager();
	glutTimerFunc(1, &update, 0);

	glutPassiveMotionFunc(mouse);

	glutMainLoop();
	exit(0);
}
