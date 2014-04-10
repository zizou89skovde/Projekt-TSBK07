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
#define far 100.0
#define right 0.5
#define left -0.5
#define top 0.5
#define bottom -0.5

#define CAM_ROTATION_SPEED 0.025
#define CAM_MOVEMENT_SPEED 0.05

// vertex array object

GLuint program,programGround,programSkybox;
GLuint myTex;
GLuint skyboxTex;
Model* mblade;
Model* mbalcony;
Model* mroof;
Model* mwalls;
Model* mcube;
Model* mskybox;

vec3 camEye;
vec3 camCenter;
vec3 camUp;

mat4 view_mat;

void init(void)
{
	// Reference to shader program
	dumpInfo();

	// GL inits
	glClearColor(0.2,0.2,0.5,0);
	glEnable(GL_DEPTH_TEST);
	printError("GL inits");

	// Load and compile shader
	program = loadShaders("lab3-3.vert", "lab3-3.frag");
	printError("init shader");
	programGround = loadShaders("lab3-3_ground.vert", "lab3-3_ground.frag");
	programSkybox = loadShaders("lab3-3_skybox.vert", "lab3-3_skybox.frag");
	printError("init shader");
	
	//Load model
	glUseProgram(program);
	mblade 	 =  LoadModelPlus("windmill/blade.obj");
	mbalcony =  LoadModelPlus("windmill/windmill-balcony.obj");
	mroof 	 =  LoadModelPlus("windmill/windmill-roof.obj");
	mwalls 	 =  LoadModelPlus("windmill/windmill-walls.obj");
	//glUseProgram(programGround);
	//mcube 	 =  LoadModelPlus("cube.obj");
	//printError("load cuboviche");
	glUseProgram(programSkybox);
	mskybox  =  LoadModelPlus("skybox.obj");
	printError("load skybox");

	//Load textures

	glUseProgram(programGround);
	LoadTGATextureSimple("maskros512.tga", &myTex);
	glBindTexture(GL_TEXTURE_2D, myTex);
	glUniform1i(glGetUniformLocation(programGround, "texUnit"), 1); // Texture unit 0	
	printError("init texture1");

	glUseProgram(programSkybox);
	LoadTGATextureSimple("SkyBox512.tga", &skyboxTex);
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, skyboxTex);
	glUniform1i(glGetUniformLocation(programSkybox, "texUnit"), 0); // Texture unit 0	
	printError("init texture2");	


	camEye.x = 40;
	camEye.y = 4;
	camEye.z = 40;

	camCenter.x = 0;
	camCenter.y = 0;
	camCenter.z = 0;

	camUp.x = 0;
	camUp.y = 1;
	camUp.z = 0;


}
GLfloat oldCamCenterX, oldCamCenterY;

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

 int count;

void loadLightData(){
	
	Point3D lightSourcesColorsArr[] = {{1.0f, 0.0f, 0.0f}, // Red light
		                         {0.0f, 1.0f, 0.0f}, // Green light
		                         {0.0f, 0.0f, 1.0f}, // Blue light
		                         {1.0f, 1.0f, 1.0f} }; // White light

	GLfloat specularExponent[] 	= {10.0, 20.0, 60.0, 5.0};
	GLint isDirectional[] 		= {0,0,1,1};

	Point3D lightSourcesDirectionsPositions[] = { {10.0f, 5.0f, 0.0f}, // Red light, positional
                                       	{0.0f, 5.0f, 10.0f}, // Green light, positional
                                       {-1.0f, 0.0f, 0.0f}, // Blue light along X
                                       {0.0f, 0.0f, -1.0f} }; // White light along Z
		

	lightSourcesDirectionsPositions[0] = MultVec3(view_mat, lightSourcesDirectionsPositions[0]);
	lightSourcesDirectionsPositions[1] = MultVec3(view_mat, lightSourcesDirectionsPositions[1]);
	lightSourcesDirectionsPositions[2] = MultVec3(view_mat, lightSourcesDirectionsPositions[2]);
	lightSourcesDirectionsPositions[3] = MultVec3(view_mat, lightSourcesDirectionsPositions[3]);

	if ( count  % 1000  == 0 ) {
		printf("light x: %f\n light y: %f\n light z: %f\n",	lightSourcesDirectionsPositions[2].x,
									lightSourcesDirectionsPositions[2].y,
									lightSourcesDirectionsPositions[2].z);
		count = 0;
	}
	count ++;
	
	glUniform3fv(glGetUniformLocation(program, "lightSourcesDirPosArr"), 4, &lightSourcesDirectionsPositions[0].x);	
	glUniform3fv(glGetUniformLocation(program, "lightSourcesColorArr"), 4, &lightSourcesColorsArr[0].x);
	glUniform1fv(glGetUniformLocation(program, "specularExponent"), 4, specularExponent);
	glUniform1iv(glGetUniformLocation(program, "isDirectional"), 4, isDirectional);
}

void display(void)
{
	printError("pre display");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	GLfloat t = (GLfloat)glutGet(GLUT_ELAPSED_TIME);
	GLfloat theta = t/500.0f;

	glUniform1f(glGetUniformLocation(program, "time"),t);

	mat4 proj_mat = frustum(left, right, bottom, top, near, far);

	mat4 mblade_mat    = IdentityMatrix();
	mat4 mbalcony_mat  = IdentityMatrix();
	mat4 mroof_mat     = IdentityMatrix();
	mat4 mwalls_mat    = IdentityMatrix();
	mat4 mground_mat   = IdentityMatrix();
	mat4 mskybox_mat   = IdentityMatrix(); 
	mat4 mwindmillmat  = IdentityMatrix(); 
	mat4 rotation_mat;
	mat4 translation_mat;
	mat4 mv_mat;
	mat4 mvp_mat;
	

	vec3 rotate_axis;
	rotate_axis.x = 1;
	rotate_axis.y = 0;
	rotate_axis.z = 0;

	//GLfloat r = 40;
	

	updateCamera();

	view_mat = lookAt(camEye.x, camEye.y, camEye.z, 
		    	  camCenter.x, camCenter.y, camCenter.z,
		    	  camUp.x, camUp.y, camUp.z);
	

	mskybox_mat = Mult(proj_mat,view_mat);

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glUseProgram(programSkybox);
	glUniformMatrix4fv(glGetUniformLocation(programSkybox, "view_matrix"), 1, GL_TRUE, view_mat.m);
	glUniformMatrix4fv(glGetUniformLocation(programSkybox, "proj_matrix"), 1, GL_TRUE, proj_mat.m);		
	DrawModel(mskybox, programSkybox, "in_Position", "in_Normal", "in_TexCoord");

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	mground_mat = S(30,0,30);
	mv_mat 	= Mult(view_mat,mground_mat);
	mvp_mat = Mult(proj_mat,mv_mat);
	glUseProgram(programGround);
	glUniformMatrix4fv(glGetUniformLocation(programGround, "MVP_Matrix"), 1, GL_TRUE, mvp_mat.m);	
  	glUniformMatrix4fv(glGetUniformLocation(programGround, "MV_Matrix"), 1, GL_TRUE , mv_mat.m);	
	DrawModel(mcube, programGround, "in_Position", "in_Normal", "in_TexCoord");


	mwindmillmat = Ry(theta);;
	

	glUseProgram(program);
	loadLightData();

	rotation_mat = ArbRotate(rotate_axis, theta);
	translation_mat = T(4.5, 10, 0);

	mblade_mat = Mult(translation_mat,rotation_mat);
	mblade_mat = Mult(mwindmillmat,mblade_mat);
	mv_mat 	= Mult(view_mat,mblade_mat);
	mvp_mat = Mult(proj_mat,mv_mat);
	glUniformMatrix4fv(glGetUniformLocation(program, "MVP_Matrix"), 1, GL_TRUE, mvp_mat.m);	
  	glUniformMatrix4fv(glGetUniformLocation(program, "MV_Matrix"), 1, GL_TRUE , mv_mat.m);	
	DrawModel(mblade, program, "in_Position", "in_Normal", "in_TexCoord");
	

	loadLightData();
	rotation_mat = ArbRotate(rotate_axis, 3.14/2+theta);
	mblade_mat = Mult(translation_mat,rotation_mat);
	mblade_mat = Mult(mwindmillmat,mblade_mat);
	mv_mat 	= Mult(view_mat,mblade_mat);
	mvp_mat = Mult(proj_mat,mv_mat);
	glUniformMatrix4fv(glGetUniformLocation(program, "MVP_Matrix"), 1, GL_TRUE, mvp_mat.m);	
  	glUniformMatrix4fv(glGetUniformLocation(program, "MV_Matrix"), 1, GL_TRUE , mv_mat.m);	
	DrawModel(mblade, program, "in_Position", "in_Normal", "in_TexCoord");

	loadLightData();
	rotation_mat = ArbRotate(rotate_axis, 3.14+theta);
	mblade_mat = Mult(translation_mat,rotation_mat);
	mblade_mat = Mult(mwindmillmat,mblade_mat);
	mv_mat 	= Mult(view_mat,mblade_mat);
	mvp_mat = Mult(proj_mat,mv_mat);
	glUniformMatrix4fv(glGetUniformLocation(program, "MVP_Matrix"), 1, GL_TRUE, mvp_mat.m);	
  	glUniformMatrix4fv(glGetUniformLocation(program, "MV_Matrix"), 1, GL_TRUE , mv_mat.m);	
	DrawModel(mblade, program, "in_Position", "in_Normal", "in_TexCoord");

	loadLightData();
	rotation_mat = ArbRotate(rotate_axis, 3*3.14/2+theta);
	mblade_mat = Mult(translation_mat,rotation_mat);
	mblade_mat = Mult(mwindmillmat,mblade_mat);
	mv_mat 	= Mult(view_mat,mblade_mat);
	mvp_mat = Mult(proj_mat,mv_mat);
	glUniformMatrix4fv(glGetUniformLocation(program, "MVP_Matrix"), 1, GL_TRUE, mvp_mat.m);	
  	glUniformMatrix4fv(glGetUniformLocation(program, "MV_Matrix"), 1, GL_TRUE , mv_mat.m);	
	DrawModel(mblade, program, "in_Position", "in_Normal", "in_TexCoord");



	loadLightData();
	mbalcony_mat = Mult(mwindmillmat,mbalcony_mat);
	mv_mat  = Mult(view_mat,mbalcony_mat);
	mvp_mat = Mult(proj_mat,mv_mat);
	glUniformMatrix4fv(glGetUniformLocation(program, "MVP_Matrix"), 1, GL_TRUE, mvp_mat.m);	
  	glUniformMatrix4fv(glGetUniformLocation(program, "MV_Matrix"), 1, GL_TRUE , mv_mat.m);
	DrawModel(mbalcony, program, "in_Position", "in_Normal", "in_TexCoord");

	loadLightData();
	mroof_mat = Mult(mwindmillmat,mroof_mat);
	mv_mat  = Mult(view_mat,mroof_mat);
	mvp_mat = Mult(proj_mat,mv_mat);
	glUniformMatrix4fv(glGetUniformLocation(program, "MVP_Matrix"), 1, GL_TRUE, mvp_mat.m);	
  	glUniformMatrix4fv(glGetUniformLocation(program, "MV_Matrix"), 1, GL_TRUE , mv_mat.m);
	DrawModel(mroof, program, "in_Position", "in_Normal", "in_TexCoord");	

	loadLightData();
	mwalls_mat = Mult(mwindmillmat,mwalls_mat);
	mv_mat  = Mult(view_mat,mwalls_mat);
	mvp_mat = Mult(proj_mat,mv_mat);
	glUniformMatrix4fv(glGetUniformLocation(program, "MVP_Matrix"), 1, GL_TRUE, mvp_mat.m);	
  	glUniformMatrix4fv(glGetUniformLocation(program, "MV_Matrix"), 1, GL_TRUE , mv_mat.m);
	DrawModel(mwalls, program, "in_Position", "in_Normal", "in_TexCoord");


	printError("display");
	
	glutSwapBuffers();
}

void OnTimer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(20, &OnTimer, value);	

	printError("init texCoord array");
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(3, 2);
	glutPassiveMotionFunc(setCamCenter);
	glutCreateWindow ("GL3 white triangle example");
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutDisplayFunc(display); 
	initKeymapManager();
	init ();
	glutTimerFunc(20, &OnTimer, 0);
	glutMainLoop();
	fprintf(stderr, "program started");
}
