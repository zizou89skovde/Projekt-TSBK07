#include "textures.h"
void shaderInit(){
	shaderList = malloc(MAX_NUM_SHADERS*sizeof(Shader));
	numShaders = 0;
	addShader("shaders/sphere.vert","shaders/sphere.frag",SHADER_SPHERE);
	addShader("shaders/terrain.vert", "shaders/terrain.frag",SHADER_GROUND);
	addShader("shaders/water.vert","shaders/water.frag",SHADER_WATER);
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


