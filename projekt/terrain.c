
#include "terrain.h"

void generateTerrain(ArchObject * groundArchObject,ArchObject * waterArchObject) {
	// Genererar mark och vatten
	// groundData är global (unik för ground)

	Model* waterModel;
	Model* groundModel;
	
	TextureData * tex = NULL;
	LoadTGATextureData("fft-terrain.tga", tex);
	
	int vertexCount = tex->width * tex->height;
	int triangleCount = (tex->width-1) * (tex->height-1) * 2;
	int x, z;

	GLfloat stepSize = 10.0;
	GLfloat stepSizeY = 100.0;

	groundData.dimX = tex->width/stepSize;
	groundData.dimZ = tex->height/stepSize;
	groundData.resolution = 1/stepSize;

	GLfloat *vertexArray = malloc(sizeof(GLfloat) * 3 * vertexCount);
	GLfloat *normalArray = malloc(sizeof(GLfloat) * 3 * vertexCount);
	GLfloat *texCoordArray = malloc(sizeof(GLfloat) * 2 * vertexCount);

	GLfloat *vertexWaterArray = malloc(sizeof(GLfloat) * 3 * vertexCount);
	GLfloat *normalWaterArray = malloc(sizeof(GLfloat) * 3 * vertexCount);
	GLfloat *texCoordWaterArray = malloc(sizeof(GLfloat) * 2 * vertexCount);

	GLuint *indexWaterArray = malloc(sizeof(GLuint) * triangleCount*3);
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

	// Create groundModel and upload to GPU:
	groundModel = LoadDataToModel(
			vertexArray,
			normalArray,
			texCoordArray,
			NULL,
			indexArray,
			vertexCount,
			triangleCount*3);

	// Set ground Graphicstruct
	groundArchObject->modelObj.program = getShader(SHADER_GROUND);
	groundArchObject->modelObj.model = *groundModel;
	groundArchObject->modelObj.texture = getTexture(TEXTURE_GROUND);
	groundArchObject->modelObj.translation_mat = IdentityMatrix();	
	// Set ground Datastruct
	groundData.vertexArray = groundModel->vertexArray;

	
	// Create waterModel and upload to GPU:
	waterModel =  LoadDataToModel(
			vertexWaterArray,
			normalWaterArray,
			texCoordWaterArray,
			NULL,
			indexWaterArray,
			vertexCount,
			triangleCount*3);
	// Set ground Graphicstruct
	waterArchObject->modelObj.program = getShader(SHADER_WATER);
	waterArchObject->modelObj.model = *waterModel;
	waterArchObject->modelObj.texture = getTexture(TEXTURE_WATER);
	waterArchObject->modelObj.translation_mat = IdentityMatrix();

}

vec3 CalculateNormal(int x,int z,GLfloat stepSize,GLfloat stepSizeY, TextureData * tex) {
	GLfloat heightN;
	GLfloat heightNW;
	GLfloat heightNE;
	GLfloat heightS;
	GLfloat heightSW;
	GLfloat heightSE;
	GLfloat heightW;
	GLfloat heightE;

	
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
/*	GLfloat dx;
	GLfloat dz;
		dx = (heightE - heightW)/(2/stepSize) + 1/sqrt(2)*( (heightNE - heightSW)/sqrt(8) + ( heightSE - heightNW)/sqrt(8))*stepSize;
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