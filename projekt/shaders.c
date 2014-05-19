#include "textures.h"
void shaderInit(){
	shaderList = malloc(MAX_NUM_SHADERS*sizeof(Shader));
	numShaders = 0;
	addShader("shaders/sphere.vert","shaders/sphere.frag",SHADER_SPHERE);
	printError("init sphere shader");
	addShader("shaders/terrain.vert", "shaders/terrain.frag",SHADER_GROUND);
	printError("init ground  shader");
	addShader("shaders/water.vert","shaders/water.frag",SHADER_WATER);
	printError("init water shader");
	addShader("shaders/char.vert","shaders/char.frag",SHADER_CHAR);
	printError("init char shader");
	addShader("shaders/skybox.vert","shaders/skybox.frag",SHADER_SKYBOX);
	printError("init skybox shader");
	addShader("shaders/terrain_lod.vert", "shaders/terrain_lod.frag",SHADER_TERRAIN_LOD);
	printError("init ground  shader");
	addShader("shaders/particle.vert", "shaders/particle.frag",SHADER_PARTICLE);
	printError("init particle  shader");

}

void addShader(char* fileNameVert,char* fileNameFrag, int id){
	shaderList[numShaders].id = id;
	shaderList[numShaders].handle = loadShaders(fileNameVert,fileNameFrag);
	numShaders++;
}

GLuint getShader(int id){
	for(int i = 0; i < numShaders; i++){
		if(shaderList[i].id == id)
		   return shaderList[i].handle;
	}
	return 0;
}


