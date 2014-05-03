void textureInit(){
	textureList = malloc(MAX_NUM_TEXTURES*sizeof(Texture));
	numTextures = 0;
	addTexture("maskros.tga",TEXTURE_MASKROS);
}

void addTexture(char* filename, int id){
	textureList[numTextures]->id = id;
	LoadTGATextureSimple(filePath, &(textureList[numTextures]->handle));
	numTextures++;
}

GLuint getTexture(int id){
	for(int i = 0; i < numTextures; i++){
		if(textureList[i]->id == id)
		   return textureList[i]->handle;
	}
}

void texturesLoadTexture(Model* m, char* filePath){
	LoadTGATextureSimple(filePath, &(m->texture));
	glBindTexture(GL_TEXTURE_2D, m->texture);
}



