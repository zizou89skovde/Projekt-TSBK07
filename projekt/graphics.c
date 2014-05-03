void graphicsInitModels(){
	model = createAndLoadModel(MODEL_GUBBE, "gubbe.obj");
	model->texture = getTexture(TEXTURE_MASKROS);
}

Model* createAndLoadModel(char* modelName, char* filePath){
	Model* modelName = malloc(MAX_NUM_MODELS*sizeof(Model));
	modelName.model =  LoadModelPlus(filePath);
	return Model*;
}

void graphicsTranslation(Model* m, GLuint x, GLuint y, GLuint z){
	m.translation_mat = T(x, y, z);
}

void graphicsDisplay(Model* m, mat4 view_mat){	
	m->modelView_mat = Mult(view_mat, m->translation_mat);
	m->modelViewProjection_mat = Mult(projection_mat, m->modelView_mat);
	
	glUseProgram(m->program);

	glUniformMatrix4fv(glGetUniformLocation(m->program, "MVP_Matrix"), 1, GL_TRUE, m->modelViewProjection_mat.m);	
  	glUniformMatrix4fv(glGetUniformLocation(m->program, "MV_Matrix"), 1, GL_TRUE , m->modelView_mat.m);

	glBindTexture(GL_TEXTURE_2D, &(m->texture));
	
	DrawModel(m->model, m->program, "in_Position", "in_Normal", "in_TexCoord");
}

// TODO: get model, id och skit precis osm med textures

//en func för rot en för trans, ta in x,y,z som arg , dvs godtyckliga såna funktioner

