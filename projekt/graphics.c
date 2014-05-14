#include "graphics.h"

void graphicsInitModels(){
	projection_mat = frustum(left, right, bottom, top, near, far);	
	
}
void addModel(ArchObject * obj,char* fileName, int texture,int shader, void (*fp)(void *, mat4)){
	Model * tempModel = &(obj->modelObj.model);
	obj->modelObj.program = getShader(shader);
	obj->particleSystem.numParticles = 0;
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
void graphicsRotation(ModelObject* m, vec3 axis, GLfloat theta){
	m->rotation_mat = ArbRotate(axis,theta);
}
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

void drawTerrain(void* arg, mat4 view_mat){	
	ModelObject * m = (ModelObject *)arg;
	mat4 modelView_mat = Mult(view_mat, m->translation_mat);
	mat4 modelViewProjection_mat = Mult(projection_mat, modelView_mat);
	
	glUseProgram(m->program);
	
	GLfloat x = m->translation_mat.m[3];
	GLfloat z = m->translation_mat.m[11];

	vec3 lookDir = VectorSub(cameraObject->eye, cameraObject->center); 
	GLfloat lookAngle = atan2(lookDir.x,lookDir.z);
	//printf("lookAngle : %f \n",lookAngle);
	glUniform3f(glGetUniformLocation(m->program, "u_Orientation"),x,z,lookAngle);
	glUniform2f(glGetUniformLocation(m->program, "u_MetaData"),100.0,100.0);

	glUniformMatrix4fv(glGetUniformLocation(m->program, "MVP_Matrix"), 1, GL_TRUE, modelViewProjection_mat.m);	
  	glUniformMatrix4fv(glGetUniformLocation(m->program, "MV_Matrix"), 1, GL_TRUE , modelView_mat.m);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m->texture);
	glEnable(GL_TEXTURE_2D);
	glUniform1i (glGetUniformLocation(m->program, "tex"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_TERRAIN_NORMAL));
	glEnable(GL_TEXTURE_2D);
	glUniform1i (glGetUniformLocation(m->program, "normalTex"),1 );

	DrawModel(&(m->model), m->program, "in_Position", "in_Normal", "in_TexCoord");
	glActiveTexture(GL_TEXTURE0);
}

void createOffsetBuffer(Model *m){
	glGenBuffers(1, &m->ob);
}

void uploadOffsetBuffer(Model *m, GLfloat * buf, int size){

	glBindVertexArray(m->vao);
	glBindBuffer(GL_ARRAY_BUFFER, m->ob);
	glBufferData(GL_ARRAY_BUFFER, 4*size*sizeof(GLfloat), buf, GL_STATIC_DRAW);

}

void drawInstanced(void * arg, mat4 view_mat){	
	ModelObject * m = (ModelObject *)arg;
	mat4 modelView_mat = Mult(view_mat, m->translation_mat);
	mat4 modelViewProjection_mat = Mult(projection_mat, modelView_mat);
	
	glUseProgram(m->program);

	glUniformMatrix4fv(glGetUniformLocation(m->program, "MVP_Matrix"), 1, GL_TRUE, modelViewProjection_mat.m);	
  	glUniformMatrix4fv(glGetUniformLocation(m->program, "MV_Matrix"), 1, GL_TRUE , modelView_mat.m);

	glBindTexture(GL_TEXTURE_2D, m->texture);
	
	DrawInstancedModel(&(m->model), m->program, "in_Position", "in_Normal", "in_TexCoord","in_Offset");
}

void DrawInstancedModel(Model *m, GLuint program, char* vertexVariableName, char* normalVariableName, char* texCoordVariableName, char * offsetVariableName)
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
				fprintf(stderr, "DrawModel warning: '%s' not found in shader!\n", offsetVariableName);
		}



		//glDrawElements(GL_TRIANGLES, m->numIndices, GL_UNSIGNED_INT, 0L);
		glEnable(GL_BLEND); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, m->numInstances);
		glDisable(GL_BLEND); 
	}
}
