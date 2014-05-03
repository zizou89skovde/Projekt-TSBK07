//#include <OpenGL/gl3.h>
//#include "include/MicroGlut.h"
#include "include/GL_utilities.h"
#include "include/VectorUtils3.h"
#include "include/loadobj.h"
#include "include/LoadTGA.h"
#include "ui.h"
#include "graphics.h"
#include "textures.h"
#define UPDATE_FREQUENCY 0.5


/* Globala prylar deklareras h�r */
//CameraObject * cameraObject; // H�ller informations om kamerans orientering. 

void init()
{
	textureInit();
	graphicsInitModels();
/* h�rifr�n kan init-funktioner anropas */
  //cameraObject = createCamera(NULL,NULL)
}

void display()
{
 /* rendera modeller h�r */

}


void tick(int i)
{
	/* h�rifr�n kan update-funktioner cycliskt anropas med frekvensen UPDATE_FREQUENCY */
	handleKeyboardInput();
	glutTimerFunc(UPDATE_FREQUENCY, &tick, i);
	glutPostRedisplay();
}

void mouse(int x,int y){
	handleMouseInput(x,y);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitContextVersion(3, 2);

	glutInitWindowSize (1080, 1080);
	glutCreateWindow ("TSBK07 Lab 4");
	glutDisplayFunc(display);
	init ();
	initKeymapManager();
	glutTimerFunc(1, &tick, 0);

	glutPassiveMotionFunc(mouse);

	glutMainLoop();
	exit(0);
}
