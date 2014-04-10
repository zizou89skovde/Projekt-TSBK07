// Lab 4, terrain generation

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

mat4 projectionMatrix;

Model* GenerateTerrain(TextureData *tex)
{
	int vertexCount = tex->width * tex->height;
	int triangleCount = (tex->width-1) * (tex->height-1) * 2;
	int x, z;

	GLfloat *vertexArray = malloc(sizeof(GLfloat) * 3 * vertexCount);
	GLfloat *normalArray = malloc(sizeof(GLfloat) * 3 * vertexCount);
	GLfloat *texCoordArray = malloc(sizeof(GLfloat) * 2 * vertexCount);
	GLuint *indexArray = malloc(sizeof(GLuint) * triangleCount*3);
	
	printf("bpp %d\n", tex->bpp);
	for (x = 0; x < tex->width; x++)
		for (z = 0; z < tex->height; z++)
		{
// Vertex array. You need to scale this properly
			vertexArray[(x + z * tex->width)*3 + 0] = x / 10.0;
			vertexArray[(x + z * tex->width)*3 + 1] = tex->imageData[(x + z * tex->width) * (tex->bpp/8)] /50.0;
			vertexArray[(x + z * tex->width)*3 + 2] = z / 10.0;
// Normal vectors. You need to calculate these.
			normalArray[(x + z * tex->width)*3 + 0] = 0.0;
			normalArray[(x + z * tex->width)*3 + 1] = 1.0;
			normalArray[(x + z * tex->width)*3 + 2] = 0.0;
// Texture coordinates. You may want to scale them.
			texCoordArray[(x + z * tex->width)*2 + 0] = x; // (float)x / tex->width;
			texCoordArray[(x + z * tex->width)*2 + 1] = z; // (float)z / tex->height;
		}
	for (x = 0; x < tex->width-1; x++)
		for (z = 0; z < tex->height-1; z++)
		{
		// Triangle 1
			indexArray[(x + z * (tex->width-1))*6 + 0] = x + z * tex->width;
			indexArray[(x + z * (tex->width-1))*6 + 1] = x + (z+1) * tex->width;
			indexArray[(x + z * (tex->width-1))*6 + 2] = x+1 + z * tex->width;
		// Triangle 2
			indexArray[(x + z * (tex->width-1))*6 + 3] = x+1 + z * tex->width;
			indexArray[(x + z * (tex->width-1))*6 + 4] = x + (z+1) * tex->width;
			indexArray[(x + z * (tex->width-1))*6 + 5] = x+1 + (z+1) * tex->width;
		}
	
	// End of terrain generation
	
	// Create Model and upload to GPU:

	Model* model = LoadDataToModel(
			vertexArray,
			normalArray,
			texCoordArray,
			NULL,
			indexArray,
			vertexCount,
			triangleCount*3);

	return model;
}


// vertex array object
Model *m, *m2, *tm;
// Reference to shader program
GLuint program;
GLuint tex1, tex2;
TextureData ttex; // terrain


#define CAM_ROTATION_SPEED 0.025
#define CAM_MOVEMENT_SPEED 0.01
vec3 camEye;
vec3 camCenter;
vec3 camUp;
GLfloat oldCamCenterX;
GLfloat oldCamCenterY;

void setCamCenter(int x, int y){
	//int screenWidth  =  glutGet(GLUT_WINDOW_WIDTH);
	//int screenHeight =  glutGet(GLUT_WINDOW_HEIGHT);
	vec3 lookDirection = Normalize(VectorSub(camCenter,camEye));
	vec3 strafeDirection = CrossProduct(camUp,lookDirection);
	GLfloat dX = x - oldCamCenterX;
	GLfloat dY = y/20 + 50;
	strafeDirection.y = 0;
	strafeDirection = Normalize(strafeDirection);
	strafeDirection  = ScalarMult(strafeDirection,dX*CAM_ROTATION_SPEED);
	lookDirection = VectorSub(lookDirection,strafeDirection);

		
	
	camCenter = VectorAdd(camEye,lookDirection);
	//camCenter.y = dY;
	oldCamCenterX = x;
	oldCamCenterY = y;


}


void updateCamera() {

	vec3 lookDirection = Normalize(VectorSub(camCenter,camEye));

	if (keyIsDown('a')) {
		vec3 strafeDirection = CrossProduct(camUp,lookDirection);
		camEye = VectorAdd(camEye,strafeDirection);
		camCenter = VectorAdd(camCenter,strafeDirection);
	}
	if (keyIsDown('d')){
		vec3 strafeDirection = CrossProduct(camUp,lookDirection);
		camEye = VectorSub(camEye,strafeDirection);
		camCenter = VectorSub(camCenter,strafeDirection);
	}
	if (keyIsDown('w')) {
		camEye = VectorAdd(camEye,lookDirection);
		camCenter = VectorAdd(camCenter,lookDirection);	
	}
	if (keyIsDown('s')) {
	 	camEye = VectorSub(camEye,lookDirection);
		camCenter = VectorSub(camCenter,lookDirection);	
	}
	

}

void init(void)
{
	// GL inits
	glClearColor(0.2,0.2,0.5,0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	printError("GL inits");

	projectionMatrix = frustum(-0.1, 0.1, -0.1, 0.1, 0.2, 100.0);

	// Load and compile shader
	program = loadShaders("terrain.vert", "terrain.frag");
	glUseProgram(program);
	printError("init shader");
	
	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, GL_TRUE, projectionMatrix.m);
	glUniform1i(glGetUniformLocation(program, "tex"), 0); // Texture unit 0
	LoadTGATextureSimple("rocks_5b.tga", &tex1);
	
// Load terrain data
	
	LoadTGATextureData("fft-terrain.tga", &ttex);
	tm = GenerateTerrain(&ttex);
	printError("init terrain");


	camUp.x = 0;
	camUp.y = 1;
	camUp.z = 0;
	camEye.x = 0; 
	camEye.y = 5;
	camEye.z = 8;
	camCenter.x = 2; 
	camCenter.y = 0;
	camCenter.z = 2;


}

void display(void)
{
	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	mat4 total, modelView, camMatrix;
	
	printError("pre display");
	
	glUseProgram(program);

	// Build matrix
	

/*	camMatrix = lookAt(cam.x, cam.y, cam.z,
				lookAtPoint.x, lookAtPoint.y, lookAtPoint.z,
				0.0, 1.0, 0.0);*/


	updateCamera();

	camMatrix = lookAt(camEye.x, camEye.y, camEye.z, 
		    	  camCenter.x, camCenter.y, camCenter.z,
		    	  camUp.x, camUp.y, camUp.z);


	modelView = IdentityMatrix();
	total = Mult(camMatrix, modelView);
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);
	
	glBindTexture(GL_TEXTURE_2D, tex1);		// Bind Our Texture tex1
	DrawModel(tm, program, "inPosition", "inNormal", "inTexCoord");

	printError("display 2");
	
	glutSwapBuffers();
}

void timer(int i)
{
	glutTimerFunc(20, &timer, i);
	glutPostRedisplay();
}

void mouse(int x, int y)
{
	printf("%d %d\n", x, y);
	setCamCenter(x,y);
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
	glutTimerFunc(20, &timer, 0);

	glutPassiveMotionFunc(mouse);

	glutMainLoop();
	exit(0);
}

