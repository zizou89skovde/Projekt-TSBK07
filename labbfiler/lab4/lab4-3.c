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

typedef struct
{
	GLfloat dimX;
	GLfloat dimZ;
	GLfloat resolution;
	GLfloat * vertexArray;
} TerrainData;

TerrainData terrainData;

vec3 CalculateNormal(int x,int z,GLfloat stepSize,GLfloat stepSizeY, TextureData * tex) {
	GLfloat heightN;
	GLfloat heightNW;
	GLfloat heightNE;
	GLfloat heightS;
	GLfloat heightSW;
	GLfloat heightSE;
	GLfloat heightW;
	GLfloat heightE;

	GLfloat dx;
	GLfloat dz;
	vec3 normals;


	GLfloat center = tex->imageData[(x + z * tex->width) * (tex->bpp/8)] /stepSizeY;


	if(z == 0)
		heightS = center;
	else
		heightS = tex->imageData[(x + (z - 1) * tex->width) * (tex->bpp/8)] /stepSizeY;

	if(z == 0 || x == 0)
		heightSW = center;
	else
		heightSW = tex->imageData[(x - 1 + (z - 1) * tex->width) * (tex->bpp/8)] /stepSizeY;

	if(z == 0 || x == tex->width)
		heightSE = center;
	else
		heightSE = tex->imageData[(x + 1 + (z - 1) * tex->width) * (tex->bpp/8)] /stepSizeY;

	if(z == tex->height)
		heightN = center;
	else
		heightN = tex->imageData[(x + (z + 1) * tex->width) * (tex->bpp/8)] /stepSizeY;

	if(z == tex->width || x == 0)
		heightNW = center;
	else
		heightNW = tex->imageData[(x - 1 + (z + 1) * tex->width) * (tex->bpp/8)] /stepSizeY;

	if(z == tex->height || x == tex->width)
		heightNE = center;
	else
		heightNE = tex->imageData[(x + 1 + (z + 1) * tex->width) * (tex->bpp/8)] /stepSizeY;

	if(x == 0)
		heightW = center;
	else
		heightW = tex->imageData[(x - 1 + z * tex->width) * (tex->bpp/8)] / stepSizeY;	

	if(x == tex->width)
		heightE = center;
	else
		heightE = tex->imageData[(x + 1 + z * tex->width) * (tex->bpp/8)] /stepSizeY;

	/*	dx = (heightE - heightW)/(2/stepSize) + 1/sqrt(2)*( (heightNE - heightSW)/sqrt(8) + ( heightSE - heightNW)/sqrt(8))*stepSize;
	dz = (heightN - heightS)/(2/stepSize) + 1/sqrt(2)*( (heightNE - heightSW)/sqrt(8) + (heightNW - heightSE)/sqrt(8))*stepSize;

	normals.x = dx;
	normals.y = 1;
	normals.z = dz;

	normals = Normalize(normals);*/
	vec3 N;
	N.x = 0;
	N.y = heightN - center;
	N.z = -1/stepSize;

	vec3 E;
	E.x = 1/stepSize;
	E.y = heightE - center;
	E.z = 0;


	vec3 SE;
	SE.x = 1/stepSize;
	SE.y = heightSE - center;
	SE.z = 1/stepSize;


	vec3 S;
	S.x = 0;
	S.y = heightS - center;
	S.z = 1/stepSize;


	vec3 W;
	W.x = -1/stepSize;
	W.y = heightW - center;
	W.z = 0;


	vec3 NW;
	NW.x = -1/stepSize;
	NW.y = heightNW - center;
	NW.z = -1/stepSize;

	vec3 n1 = Normalize(CrossProduct(N,NW));
	vec3 n2 = Normalize(CrossProduct(NW,W));
	vec3 n3 = Normalize(CrossProduct(W,S));
	vec3 n4 = Normalize(CrossProduct(S,SE));
	vec3 n5 = Normalize(CrossProduct(SE,E));
	vec3 n6 = Normalize(CrossProduct(E,N));
	normals = VectorAdd(n1,VectorAdd(n2,VectorAdd(n3,VectorAdd(n4,VectorAdd(n5,n6)))));
	GLfloat wieghtFactor = 1.0/6.0;
	normals = ScalarMult(normals,wieghtFactor);
	normals = Normalize(normals);
	return normals;


}

Model* waterModel;

Model* GenerateTerrain(TextureData *tex)
																						{
	int vertexCount = tex->width * tex->height;
	int triangleCount = (tex->width-1) * (tex->height-1) * 2;
	int x, z;

	GLfloat stepSize = 10.0;
	GLfloat stepSizeY = 100.0;

	terrainData.dimX = tex->width/stepSize;
	terrainData.dimZ = tex->height/stepSize;
	terrainData.resolution = 1/stepSize;

	GLfloat *vertexArray = malloc(sizeof(GLfloat) * 3 * vertexCount);
	GLfloat *normalArray = malloc(sizeof(GLfloat) * 3 * vertexCount);
	GLfloat *texCoordArray = malloc(sizeof(GLfloat) * 2 * vertexCount);

	GLfloat *vertexWaterArray 	= malloc(sizeof(GLfloat) * 3 * vertexCount);
	GLfloat *normalWaterArray = malloc(sizeof(GLfloat) * 3 * vertexCount);
	GLfloat *texCoordWaterArray = malloc(sizeof(GLfloat) * 2 * vertexCount);

	GLuint *indexWaterArray 	= malloc(sizeof(GLuint) * triangleCount*3);
	GLuint *indexArray = malloc(sizeof(GLuint) * triangleCount*3);

	printf("bpp %d\n", tex->bpp);

	vec3 normals;

	for (x = 0; x < tex->width; x++)
		for (z = 0; z < tex->height; z++)
		{
			vertexWaterArray[(x + z * tex->width)*3 + 0] = x / stepSize;
			vertexWaterArray[(x + z * tex->width)*3 + 1] = 0.2;
			vertexWaterArray[(x + z * tex->width)*3 + 2] = z / stepSize;
			
			normalWaterArray[(x + z * tex->width)*3 + 0] = 0;
			normalWaterArray[(x + z * tex->width)*3 + 1] = 1;
			normalWaterArray[(x + z * tex->width)*3 + 2] = 0;

			texCoordWaterArray[(x + z * tex->width)*2 + 0] = x/50.0; // (float)x / tex->width;
			texCoordWaterArray[(x + z * tex->width)*2 + 1] = z/50.0; // (float)z / tex->height;


			// Vertex array. You need to scale this properly
			vertexArray[(x + z * tex->width)*3 + 0] = x / stepSize;
			vertexArray[(x + z * tex->width)*3 + 1] = tex->imageData[(x + z * tex->width) * (tex->bpp/8)] /stepSizeY;
			vertexArray[(x + z * tex->width)*3 + 2] = z / stepSize;
			// Normal vectors. You need to calculate these.
			normals = CalculateNormal(x,z,stepSize,stepSizeY,tex);
			normalArray[(x + z * tex->width)*3 + 0] = normals.x;
			normalArray[(x + z * tex->width)*3 + 1] = normals.y;
			normalArray[(x + z * tex->width)*3 + 2] = normals.z;
			
			// Texture coordinates. You may want to scale them.
			texCoordArray[(x + z * tex->width)*2 + 0] = x/50.0; // (float)x / tex->width;
			texCoordArray[(x + z * tex->width)*2 + 1] = z/50.0; // (float)z / tex->height;
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


			indexWaterArray[(x + z * (tex->width-1))*6 + 0] = x + z * tex->width;
			indexWaterArray[(x + z * (tex->width-1))*6 + 1] = x + (z+1) * tex->width;
			indexWaterArray[(x + z * (tex->width-1))*6 + 2] = x+1 + z * tex->width;
			// Triangle 2
			indexWaterArray[(x + z * (tex->width-1))*6 + 3] = x+1 + z * tex->width;
			indexWaterArray[(x + z * (tex->width-1))*6 + 4] = x + (z+1) * tex->width;
			indexWaterArray[(x + z * (tex->width-1))*6 + 5] = x+1 + (z+1) * tex->width;
		}

	// End of terrain generation

	// Create Model and upload to GPU:
	waterModel =  LoadDataToModel(
			vertexWaterArray,
			normalWaterArray,
			texCoordWaterArray,
			NULL,
			indexWaterArray,
			vertexCount,
			triangleCount*3);

	Model* model = LoadDataToModel(
			vertexArray,
			normalArray,
			texCoordArray,
			NULL,
			indexArray,
			vertexCount,
			triangleCount*3);

	terrainData.vertexArray = model->vertexArray;

	return model;
																						}


// vertex array object
Model *m, *m2, *tm;
Model *msphere;
// Reference to shader program
GLuint program,programSphere,programWater;
GLuint tex1, tex2;
TextureData ttex; // terrain
GLfloat ballCurrentPosition[3];

#define CAM_ROTATION_SPEED 0.025
#define CAM_MOVEMENT_SPEED 0.05
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
		vec3 strafeDirection = Normalize(CrossProduct(camUp,lookDirection));
		strafeDirection = ScalarMult(strafeDirection,CAM_MOVEMENT_SPEED); 
		camEye = VectorAdd(camEye,strafeDirection);
		camCenter = VectorAdd(camCenter,strafeDirection);
	}
	if (keyIsDown('d')){
		vec3 strafeDirection = Normalize(CrossProduct(camUp,lookDirection));
		strafeDirection = ScalarMult(strafeDirection,CAM_MOVEMENT_SPEED); 
		camEye = VectorSub(camEye,strafeDirection);
		camCenter = VectorSub(camCenter,strafeDirection);
	}
	if (keyIsDown('w')) {
		lookDirection = ScalarMult(lookDirection,CAM_MOVEMENT_SPEED); 
		camEye = VectorAdd(camEye,lookDirection);
		camCenter = VectorAdd(camCenter,lookDirection);	
	}
	if (keyIsDown('s')) {
		lookDirection = ScalarMult(lookDirection,CAM_MOVEMENT_SPEED); 
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
	programSphere = loadShaders("sphere.vert","sphere.frag");
	programWater = loadShaders("water.vert","water.frag");
	glUseProgram(program);
	printError("init shader");

	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, GL_TRUE, projectionMatrix.m);
	glUniform1i(glGetUniformLocation(program, "tex"), 0); // Texture unit 0
	LoadTGATextureSimple("rocks_2.tga", &tex1);

	glUseProgram(programSphere);
	glUniformMatrix4fv(glGetUniformLocation(programSphere, "projMatrix"), 1, GL_TRUE, projectionMatrix.m);
	msphere =  LoadModelPlus("groundsphere.obj");

	glUseProgram(programWater);
	glUniformMatrix4fv(glGetUniformLocation(programSphere, "projMatrix"), 1, GL_TRUE, projectionMatrix.m);
	LoadTGATextureSimple("tex_Water-jpg.tga", &tex2);
	
	// Load terrain data
	glUseProgram(program);
	LoadTGATextureData("fft-terrain.tga", &ttex);
	tm = GenerateTerrain(&ttex);
	printError("init terrain");


	camUp.x = 0;
	camUp.y = 1;
	camUp.z = 0;
	camEye.x = 0; 
	camEye.y = 1;
	camEye.z = 8;
	camCenter.x = 2; 
	camCenter.y = 0;
	camCenter.z = 2;

	ballCurrentPosition[0] = 8.0;
	ballCurrentPosition[1] = 10.0; 
	ballCurrentPosition[2] = 15.0; 

}

void checkCollisionToGround(Model* object,GLfloat* objectPos) {


	GLfloat gravity = 0.01;

	if(objectPos[0] < terrainData.dimX  &&
			objectPos[0] > 0 &&
			objectPos[2] < terrainData.dimZ  &&
			objectPos[2] > 0) {

		int indexX,indexZ;   
		GLfloat terrainHeight;
		GLfloat topLeftPosX,topLeftPosZ;



		int WIDTH = terrainData.dimX / terrainData.resolution;

		indexX = objectPos[0]/terrainData.resolution;
		indexZ = objectPos[2]/terrainData.resolution;

		topLeftPosX = indexX*terrainData.resolution;
		topLeftPosZ = (indexZ + 1)*terrainData.resolution;


		GLfloat deltaX = ( objectPos[0] - topLeftPosX);
		GLfloat deltaZ = ( objectPos[2]	- topLeftPosZ);
		/*
		weight1 = sqrt(deltaX*deltaX + deltaY*deltaY);
		weight2 = sqrt((1-deltaX)*(1-deltaX) + deltaY*deltaY);
		weight3 = sqrt((1-deltaX)*(1-deltaX) + (1-deltaY)*(1-deltaY));*/

		vec3 v1;
		vec3 v2;
		vec3 normal;

		if(deltaZ/deltaX > -1){
			terrainHeight = (
					terrainData.vertexArray[(indexX +1 + (indexZ + 1) * WIDTH)*3 +1] +					
					terrainData.vertexArray[(indexX +1 + (indexZ) * WIDTH)*3 +1] +					
					terrainData.vertexArray[(indexX + (indexZ + 1) * WIDTH)*3 +1])/3;

			v1.x = 1 * terrainData.resolution;
			v1.y = terrainData.vertexArray[(indexX +1 + (indexZ + 1) * WIDTH)*3 +1] - terrainData.vertexArray[(indexX + indexZ  * WIDTH)*3 +1];
			v1.z = 1 * terrainData.resolution;

			v2.x = 1 * terrainData.resolution;
			v2.y = terrainData.vertexArray[(indexX +1 + indexZ  * WIDTH)*3 +1] - terrainData.vertexArray[(indexX + indexZ  * WIDTH)*3 +1];
			v2.z = 0;

			normal = Normalize(CrossProduct(v1,v2));


		}else{
			terrainHeight = (
					terrainData.vertexArray[(indexX + (indexZ) * WIDTH)*3 +1] +					
					terrainData.vertexArray[(indexX +1 + (indexZ) * WIDTH)*3 +1] +					
					terrainData.vertexArray[(indexX + (indexZ + 1) * WIDTH)*3 +1])/3;	

			v1.x = 1 * terrainData.resolution;
			v1.y = terrainData.vertexArray[(indexX +1 + (indexZ + 1) * WIDTH)*3 +1] - terrainData.vertexArray[(indexX + indexZ  * WIDTH)*3 +1];
			v1.z = 1 * terrainData.resolution;

			v2.x = 0;
			v2.y = terrainData.vertexArray[(indexX  + (indexZ  + 1) * WIDTH)*3 +1] - terrainData.vertexArray[(indexX + indexZ  * WIDTH)*3 +1];
			v2.z = 1 * terrainData.resolution;

			normal = Normalize(CrossProduct(v2,v1));

		}

		if(objectPos[1] <= terrainHeight){

			GLfloat delta = 0.01;

			GLfloat dx = normal.x;
			GLfloat dz = normal.z;

			objectPos[0] +=  dx*delta;
			objectPos[2] +=  dz*delta;

		}else{
			objectPos[1] -= gravity ;
		}
	}else{
		objectPos[1] -= gravity ;
	}

} 
float time2;
void display(void)
{
	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4 total, modelView, camMatrix, spherematrix;

	printError("pre display");

	// Build matrix
	time2 += 0.001;
	if(time2 > 100.0)
		time2 = 0.0;
	updateCamera();

	camMatrix = lookAt(camEye.x, camEye.y, camEye.z, 
			camCenter.x, camCenter.y, camCenter.z,
			camUp.x, camUp.y, camUp.z);


	checkCollisionToGround(msphere,ballCurrentPosition);
	mat4 transmat = T(ballCurrentPosition[0],ballCurrentPosition[1],ballCurrentPosition[2]);
	spherematrix = S(0.2,0.2,0.2);
	spherematrix = Mult(transmat,spherematrix);


	total = Mult(camMatrix, spherematrix);

	glUseProgram(programSphere);
	glUniformMatrix4fv(glGetUniformLocation(programSphere, "mdlMatrix"), 1, GL_TRUE, total.m);	
	DrawModel(msphere, programSphere, "inPosition", "inNormal", 0);	

	glUseProgram(program);
	modelView = IdentityMatrix();
	total = Mult(camMatrix, modelView);
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);

	glBindTexture(GL_TEXTURE_2D, tex1);		// Bind Our Texture tex1
	DrawModel(tm, program, "inPosition", "inNormal", "inTexCoord");

	glUseProgram(programWater);
	glUniformMatrix4fv(glGetUniformLocation(programWater, "mdlMatrix"), 1, GL_TRUE, total.m);
	glBindTexture(GL_TEXTURE_2D, tex2);		// Bind Our Texture tex1
	glUniform1f(glGetUniformLocation(programWater, "u_Time"), time2);
	
	DrawModel(waterModel, programWater, "inPosition", "inNormal", "inTexCoord");

	printError("display 2");

	glutSwapBuffers();
}

void timer(int i)
{
	glutTimerFunc(0.5, &timer, i);
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
	glutTimerFunc(1, &timer, 0);

	glutPassiveMotionFunc(mouse);

	glutMainLoop();
	exit(0);
}
