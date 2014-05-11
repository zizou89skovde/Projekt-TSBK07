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

void createOffsetBuffer(Model *m){
	glGenBuffers(1, &m->ob);
}

void uploadOffsetBuffer(Model *m, GLfloat * buf, int size){

	glBindVertexArray(m->vao);
	// VBO for vertex data
	glBindBuffer(GL_ARRAY_BUFFER, m->ob);
	glBufferData(GL_ARRAY_BUFFER, size*sizeof(GLfloat), buf, GL_STATIC_DRAW);

}

void DrawInstanced(Model *m, GLuint program, char* vertexVariableName, char* normalVariableName, char* texCoordVariableName, char * offsetVariableName)
{
	if (m != NULL)
	{
		GLint loc;
		
		glBindVertexArray(m->vao);	// Select VAO

		glBindBuffer(GL_ARRAY_BUFFER, m->vb);
		loc = glGetAttribLocation(program, vertexVariableName);
		if (loc >= 0)
		{
			glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0); 
			glEnableVertexAttribArray(loc);
			glVertexAttribDivisor(loc, 0);
		}
		else
			fprintf(stderr, "DrawModel warning: '%s' not found in shader!\n", vertexVariableName);
		
		if (normalVariableName!=NULL)
		{
			loc = glGetAttribLocation(program, normalVariableName);
			if (loc >= 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m->nb);
				glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(loc);
				glVertexAttribDivisor(loc, 0);
			}
		}
	
		// VBO for texture coordinate data NEW for 5b
		if ((m->texCoordArray != NULL)&&(texCoordVariableName != NULL))
		{
			loc = glGetAttribLocation(program, texCoordVariableName);
			if (loc >= 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m->tb);
				glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(loc);
				glVertexAttribDivisor(loc, 0);
			}
			else
				fprintf(stderr, "DrawModel warning: '%s' not found in shader!\n", texCoordVariableName);
		}


		if (offsetVariableName != NULL)
		{
			loc = glGetAttribLocation(program, offsetVariableName);
			if (loc >= 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m->ob);
				glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(loc);
				glVertexAttribDivisor(loc, 1);
			}
			else
				fprintf(stderr, "DrawModel warning: '%s' not found in shader!\n", texCoordVariableName);
		}



		glDrawElements(GL_TRIANGLES, m->numIndices, GL_UNSIGNED_INT, 0L);
	}
}
