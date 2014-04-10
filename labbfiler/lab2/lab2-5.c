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
#include "VectorUtils3.h"
#include "loadobj.h"
#include "LoadTGA.h"
#include <math.h>
// Globals
// Data would normally be read from files


GLfloat myMatrix[] = {    1.0f, 0.0f, 0.0f, 0.5f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f 
};

#define near 1.0
#define far 30.0
#define right 0.5
#define left -0.5
#define top 0.5
#define bottom -0.5
GLfloat projectionMatrix[] = {    2.0f*near/(right-left), 0.0f, (right+left)/(right-left), 0.0f,
                                            0.0f, 2.0f*near/(top-bottom), (top+bottom)/(top-bottom), 0.0f,
                                            0.0f, 0.0f, -(far + near)/(far - near), -2*far*near/(far - near),
                                            0.0f, 0.0f, -1.0f, 0.0f };



// vertex array object

unsigned int bunnyVertexArrayObjID;
GLuint program;
GLuint myTex;
Model *m;

void init(void)
{
	// vertex buffer object, used for uploading the geometry
	unsigned int bunnyVertexBufferObjID;
	unsigned int bunnyIndexBufferObjID;
	unsigned int bunnyNormalBufferObjID;
	unsigned int bunnyTexCoordBufferObjID;

	// Reference to shader program


	dumpInfo();

	// GL inits
	glClearColor(0.2,0.2,0.5,0);
	glEnable(GL_DEPTH_TEST);
	printError("GL inits");

	// Load and compile shader
	program = loadShaders("lab2-5.vert", "lab2-5.frag");
	printError("init shader");
	
	//Load model
	m = LoadModel("bunnyplus.obj");

	


	// Upload geometry to the GPU:
	
    	glGenVertexArrays(1, &bunnyVertexArrayObjID);
    	glGenBuffers(1, &bunnyVertexBufferObjID);
    	glGenBuffers(1, &bunnyIndexBufferObjID);
    	glGenBuffers(1, &bunnyNormalBufferObjID);
    	glGenBuffers(1, &bunnyTexCoordBufferObjID);
   	glBindVertexArray(bunnyVertexArrayObjID);

	//Load textures
	LoadTGATextureSimple("maskros512.tga", &myTex);
	glBindTexture(GL_TEXTURE_2D, myTex);
	glUniform1i(glGetUniformLocation(program, "texUnit"), 0); // Texture unit 0	
	printError("init texture");

    	// VBO for vertex data
    	glBindBuffer(GL_ARRAY_BUFFER, bunnyVertexBufferObjID);
    	glBufferData(GL_ARRAY_BUFFER, m->numVertices*3*sizeof(GLfloat), m->vertexArray, GL_STATIC_DRAW);
    	glVertexAttribPointer(glGetAttribLocation(program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
    	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Position"));
	printError("init vertex arrays");

	// VBO for normal data
	glBindBuffer(GL_ARRAY_BUFFER, bunnyNormalBufferObjID);
    	glBufferData(GL_ARRAY_BUFFER, m->numVertices*3*sizeof(GLfloat), m->normalArray, GL_STATIC_DRAW);
    	glVertexAttribPointer(glGetAttribLocation(program, "in_Normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
    	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Normal"));
	printError("init normal arrays");	



	if (m->texCoordArray != NULL)
	{
        	glBindBuffer(GL_ARRAY_BUFFER, bunnyTexCoordBufferObjID);
        	glBufferData(GL_ARRAY_BUFFER, m->numVertices*2*sizeof(GLfloat), m->texCoordArray, GL_STATIC_DRAW);
        	glVertexAttribPointer(glGetAttribLocation(program, "inTexCoord"), 2, GL_FLOAT, GL_FALSE, 0, 0);
        	glEnableVertexAttribArray(glGetAttribLocation(program, "inTexCoord"));
	}
    
    	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bunnyIndexBufferObjID);
    	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->numIndices*sizeof(GLuint), m->indexArray, GL_STATIC_DRAW);
	// End of upload of geometry

	mat4 mvp_mat;
	mat4 trans_mat;
	mat4 proj_mat;	
	mat4 view_mat;
	mat4 mv_mat;

	trans_mat = T(0, 0, 1);
	memcpy(proj_mat.m, projectionMatrix, 16 *sizeof(float));
	view_mat = lookAt(0, 0, 4, 
		    0, 0, 0,
		    0, 1, 0);

	modelview_mat = Mult(view_mat,trans_mat);
	mvp_mat       = Mult(proj_mat,mv_mat);

  	glUniformMatrix4fv(glGetUniformLocation(program, "MVP_Matrix"), 1, GL_TRUE, mvp_mat.m);	
  	glUniformMatrix4fv(glGetUniformLocation(program, "MV_Matrix"), 1, GL_TRUE , mv_mat.m);	
	printError("init texCoord array");
}


void display(void)
{
	printError("pre display");

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(bunnyVertexArrayObjID);    // Select VAO
   	glDrawElements(GL_TRIANGLES, m->numIndices, GL_UNSIGNED_INT, 0L);
	
	printError("display");
	
	glutSwapBuffers();
}

void OnTimer(int value)
{
   GLfloat t = (GLfloat)glutGet(GLUT_ELAPSED_TIME);
   GLfloat theta = t/500.0f;

   glUniform1f(glGetUniformLocation(program, "time"),t);

    
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
