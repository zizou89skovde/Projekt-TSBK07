#include "graphics.h"

void graphicsInitModels(){
	projection_mat = frustum(left, right, bottom, top, near, far);	
	
}
void addModel(ArchObject * obj,char* fileName, int texture,int shader, void (*fp)(void *, mat4)){
	Model * tempModel = &(obj->modelObj.model);
	obj->modelObj.program = getShader(shader);
	glUseProgram(obj->modelObj.program);
	tempModel  = LoadModelPlus(fileName);
	obj->modelObj.model = *tempModel;
	if(texture != -1){
		obj->modelObj.texture = getTexture(texture);
	}

	obj->modelObj.renderFunc = fp;
}
/*
Model_struct* getModel(int id){
	for(int i = 0; i < numModels; i++){
		if(modelList[i].id == id)
		   return &(modelList[i]);
	}
	return NULL;
}
*/
void graphicsTranslation(ModelObject* m, GLfloat x, GLfloat y, GLfloat z){
	m->translation_mat = T(x, y, z);
}

void graphicsDisplay(void * arg, mat4 view_mat){	
	ModelObject * m = (ModelObject *)arg;
	mat4 modelView_mat = Mult(view_mat, m->translation_mat);
	mat4 modelViewProjection_mat = Mult(projection_mat, modelView_mat);
	
	glUseProgram(m->program);

	glUniformMatrix4fv(glGetUniformLocation(m->program, "MVP_Matrix"), 1, GL_TRUE, modelViewProjection_mat.m);	
  	glUniformMatrix4fv(glGetUniformLocation(m->program, "MV_Matrix"), 1, GL_TRUE , modelView_mat.m);

	glBindTexture(GL_TEXTURE_2D, m->texture);
	
	DrawModel(&(m->model), m->program, "in_Position", "in_Normal", "in_TexCoord");
}

void graphicsDisplaySkybox(void* arg, mat4 view_mat){	
	ModelObject * m = (ModelObject *)arg;
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	
	glUseProgram(m->program);

	glUniformMatrix4fv(glGetUniformLocation(m->program, "V_Matrix"), 1, GL_TRUE, view_mat.m);	
  	glUniformMatrix4fv(glGetUniformLocation(m->program, "P_Matrix"), 1, GL_TRUE , projection_mat.m);

	glBindTexture(GL_TEXTURE_2D, m->texture);
	
	DrawModel(&(m->model), m->program, "in_Position", "in_Normal", "in_TexCoord");

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}
