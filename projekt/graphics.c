#include "graphics.h"

void graphicsInitModels(){
	projection_mat = frustum(left, right, bottom, top, near, far);
	modelList = malloc(MAX_NUM_MODELS*sizeof(Model_struct));
	numModels = 0;
	addModel("resources/groundsphere.obj", MODEL_GUBBE, TEXTURE_MASKROS,SHADER_SPHERE);	
}

void addModel(char* fileName, int id, int texture,int shader){
	modelList[numModels].model = LoadModelPlus(fileName);
	modelList[numModels].id = id;

	if(texture != -1){
		modelList[numModels].texture = getTexture(texture);
	}
	modelList[numModels].program = getShader(shader);
	LoadModelPlus(fileName);	
	numModels++;
}

Model_struct* getModel(int id){
	for(int i = 0; i < numModels; i++){
		if(modelList[i].id == id)
		   return &(modelList[i]);
	}
	return NULL;
}

void graphicsTranslation(Model_struct* m, GLuint x, GLuint y, GLuint z){
	m->translation_mat = T(x, y, z);
}

void graphicsDisplay(Model_struct* m, mat4 view_mat){	
	mat4 modelView_mat = Mult(view_mat, m->translation_mat);
	mat4 modelViewProjection_mat = Mult(projection_mat, modelView_mat);
	
	glUseProgram(m->program);

	glUniformMatrix4fv(glGetUniformLocation(m->program, "MVP_Matrix"), 1, GL_TRUE, modelViewProjection_mat.m);	
  	glUniformMatrix4fv(glGetUniformLocation(m->program, "MV_Matrix"), 1, GL_TRUE , modelView_mat.m);

	glBindTexture(GL_TEXTURE_2D, m->texture);
	
	DrawModel(m->model, m->program, "in_Position", "in_Normal", "in_TexCoord");
}

