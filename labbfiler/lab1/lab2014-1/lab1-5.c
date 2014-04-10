// Lab 1-1.
// This is the same as the first simple example in the course book,
// but with a few error checks.
// Remember to copy your file to a new on appropriate places during the lab so you keep old results.
// Note that the files "lab1-1.frag", "lab1-1.vert" are required.

// Should work as is on Linux and Mac. MS Windows needs GLEW or glee.
// See separate Visual Studio version of my demos.
#ifdef __APPLE__
	#include <OpenGL/gl3.h>
	#include "MicroGlut.h"
	// Linking hint for Lightweight IDE
	// uses framework Cocoa
#endif
#include "GL_utilities.h"
#include <math.h>
// Globals
// Data would normally be read from files


GLfloat vertices[8][3] = {
	{-0.5,-0.5,-0.5},
	{0.5,-0.5,-0.5},
	{0.5,0.5,-0.5},
	{-0.5,0.5,-0.5},
	{-0.5,-0.5,0.5},
	{0.5,-0.5,0.5},
	{0.5,0.5,0.5},
	{-0.5,0.5,0.5}
};
GLfloat colors[8][3] = {
	{0.8,0.5,0.5},
	{0.57,0.57,0.53},
	{0.1,0.2,0.3},
	{0.1,0.1,0.1},
	{0.22,0.33,0.77},
	{0.88,0.44,0.55},
	{0.11,0.58,0.58},
	{0.51,0.14,0.58}
};
GLubyte cubeIndices[36] = {
	0,3,2, 0,2,1,
	2,3,7, 2,7,6,
	0,4,7, 0,7,3,
	1,2,6, 1,6,5,
	4,5,6, 4,6,7,
	0,1,5, 0,5,4};

GLfloat myMatrix[] = {    1.0f, 0.0f, 0.0f, 0.5f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f 
};

// vertex array object
unsigned int vertexArrayObjID;
GLuint program;
void init(void)
{
	// vertex buffer object, used for uploading the geometry
	unsigned int vertexBufferObjID;
	unsigned int colorBufferObjID;
	unsigned int indexBufferObjID;

	// Reference to shader program


	dumpInfo();

	// GL inits
	glClearColor(0.2,0.2,0.5,0);
	glEnable(GL_DEPTH_TEST);
	printError("GL inits");

	// Load and compile shader
	program = loadShaders("lab1-1.vert", "lab1-1.frag");
	printError("init shader");
	
	// Upload geometry to the GPU:
	
	// Allocate and activate Vertex Array Object
	glGenVertexArrays(1, &vertexArrayObjID);
	glBindVertexArray(vertexArrayObjID);
	// Allocate Vertex Buffer Objects
	glGenBuffers(1, &vertexBufferObjID);
	glGenBuffers(1, &colorBufferObjID);
	glGenBuffers(1, &indexBufferObjID);

	// VBO for vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, 8*3*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Position"));

	// VBO for color data
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, 8*3*sizeof(GLfloat), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Color"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Color"));

	// IBO for color data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24*sizeof(GLuint), cubeIndices, GL_STATIC_DRAW);
	printError("init index");


	// Uniform myMatrix
	glUniformMatrix4fv(glGetUniformLocation(program, "myMatrix"), 1, GL_TRUE, myMatrix);
	
	// End of upload of geometry
	
	printError("init arrays");
}


void display(void)
{
	printError("pre display");

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vertexArrayObjID);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);
	
	printError("display");
	
	glutSwapBuffers();
}

void OnTimer(int value)
{
   GLfloat t = (GLfloat)glutGet(GLUT_ELAPSED_TIME);
   GLfloat theta = t/500.0f;

   GLfloat rotation[] = {
			cos(theta), 0.0f, -sin(theta), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
                        sin(theta), 0.0f, cos(theta), 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f,
			};

 GLfloat rotation2[] ={ 1.0f, 0.0f, 0.0f, 0.0f, 
			0.0f, cos(theta), -sin(theta), 0.0f,
			0.0f,sin(theta), cos(theta), 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f,
			};
    // Uniform myMatrix
    glUniformMatrix4fv(glGetUniformLocation(program, "myMatrix"), 1, GL_TRUE, rotation2);
    glutPostRedisplay();
    glutTimerFunc(20, &OnTimer, value);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(3, 2);
	glutCreateWindow ("GL3 white triangle example");
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutDisplayFunc(display); 
	init ();
	glutTimerFunc(20, &OnTimer, 0);
	glutMainLoop();
}
