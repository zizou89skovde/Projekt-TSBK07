//#include <OpenGL/gl3.h>
//#include "include/MicroGlut.h"
#include "GL_utilities.h"
#include "VectorUtils3.h"
#include "loadobj.h"
#include "LoadTGA.h"
#include "ui.h"
#include "graphics.h"
#include "textures.h"
#include "shaders.h"
#include "camera.h"

#define UPDATE_FREQUENCY 20.0


/* Globala prylar deklareras här */
CameraObject * cameraObject; // Håller informations om kamerans orientering. 

void init()
{

    glClearColor(0.2,0.2,0.5,0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    printError("GL inits");

    textureInit();
    shaderInit();
    graphicsInitModels();
    cameraObject = createCamera();

    
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 /* rendera modeller här */
   Model_struct * m = getModel(MODEL_GUBBE);

   vec3 eye    = SetVector(5,0,0);
   vec3 center = SetVector(1,0,1);

   setCameraEye(cameraObject,eye);
   setCameraCenter(cameraObject,center);

   graphicsTranslation(m,1,0,1);
   graphicsDisplay(m,getCameraMatrix(cameraObject));
   glutSwapBuffers();

   
}


void tick(int i)
{
	/* härifrån kan update-funktioner cycliskt anropas med frekvensen UPDATE_FREQUENCY */
	handleKeyboardInput(cameraObject);
	glutTimerFunc(UPDATE_FREQUENCY, &tick, i);
	glutPostRedisplay();

	#ifdef VERBOSE
	printf("VERBOSE");
	 #endif
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
	init();
	initKeymapManager();
	glutTimerFunc(1, &tick, 0);

	glutPassiveMotionFunc(mouse);

	glutMainLoop();
	exit(0);
}
