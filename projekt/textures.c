#include "textures.h"
void textureInit(){
	textureList = malloc(MAX_NUM_TEXTURES*sizeof(Texture));
	numTextures = 0;

	addTexture("resources/rocks_2.tga",TEXTURE_GROUND);
	//addTexture("resources/char.tga",TEXTURE_CHAR);
	addTexture("resources/char.tga",TEXTURE_CHAR);
	addTexture("resources/tex_Water-jpg.tga",TEXTURE_WATER);
	//addTexture("resources/SkyBox512.tga", TEXTURE_SKYBOX);
	addTexture("resources/SkyBox.tga", TEXTURE_SKYBOX);
	//addTexture("resources/dendi.tga", TEXTURE_TERRAIN_LOD);
	addTexture("resources/terrainmap.tga", TEXTURE_TERRAIN_LOD);
	addTexture("resources/cloud_texture.tga", TEXTURE_CLOUDS);
	addTexture("resources/terrainmap_normal.tga", TEXTURE_TERRAIN_NORMAL);

	addTexture("resources/snow_2.tga", TEXTURE_TERRAIN_SNOW);
	addTexture("resources/grass.tga", TEXTURE_TERRAIN_GRASS);
	addTexture("resources/rocks_2.tga", TEXTURE_TERRAIN_ROCKS1);
	addTexture("resources/rocks_3.tga", TEXTURE_TERRAIN_ROCKS2);
	addTexture("resources/rocks_4.tga", TEXTURE_TERRAIN_ROCKS3);

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



