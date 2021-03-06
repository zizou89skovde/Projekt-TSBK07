//#include <OpenGL/gl3.h>
#include "MicroGlut.h"
#include "GL_utilities.h"
#include "ui.h"
#include "object.h"
#include "textures.h"
#include "shaders.h"
#include "camera.h"


#define UPDATE_FREQUENCY 60.0
void init()
{
    glClearColor(0.2,0.2,0.5,0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    printError("GL inits");

    textureInit();
    shaderInit();
    objectInit();
 
}

void display()
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  renderObjects();
  glutSwapBuffers();

   
}


void tick(int i)
{
	/* h�rifr�n kan update-funktioner cycliskt anropas med frekvensen UPDATE_FREQUENCY */
	glutTimerFunc(1/UPDATE_FREQUENCY, &tick, i);
	glutPostRedisplay();

	updateObjectPosition();

}

void mouse(int x,int y){
	handleMouseInput(x,y);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	
	glutInitContextVersion(3, 2);

	glutInitWindowSize (1080, 1080);
	glutCreateWindow ("TSBK07 Lab 4");
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutDisplayFunc(display);
	init();
	initKeymapManager();
	glutTimerFunc(1, &tick, 0);

	glutPassiveMotionFunc(mouse);

	glutMainLoop();
	exit(0);
}
