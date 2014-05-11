#include "textures.h"
void textureInit(){
	textureList = malloc(MAX_NUM_TEXTURES*sizeof(Texture));
	numTextures = 0;
	addTexture("resources/rocks_2.tga", TEXTURE_GROUND);
	//addTexture("resources/tex_Water-jpg.tga",TEXTURE_WATER);
	addTexture("resources/SkyBox512.tga", TEXTURE_SKYBOX);
}

void addTexture(char* fileName, int id){
	textureList[numTextures].id = id;
	LoadTGATextureSimple(fileName, &(textureList[numTextures].handle));
	numTextures++;
}

GLuint getTexture(int id){
	for(int i = 0; i < numTextures; i++){
		if(textureList[i].id == id)
		   return textureList[i].handle;
	}
	return 0;
}


