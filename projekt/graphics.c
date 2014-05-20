#include "graphics.h"
#define PI 3.14159265359
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
	obj->modelObj.rotation_mat = IdentityMatrix();
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
void graphicsRotation(ModelObject* m, mat4 rotationMat){	
	m->rotation_mat = rotationMat;
}
void graphicsTranslation(ModelObject* m, GLfloat x, GLfloat y, GLfloat z){
	m->translation_mat = T(x, y, z);
}
void updateLight(){
	vLight = SetVector(0,sin(fTIme),cos(fTIme));
	vLight = Normalize(vLight);
	fTIme += 0.01; //*sundirection;
	if(fTIme >3.18){
		fTIme = -0.4;
		//sundirection *= -1;
	}
}

void graphicsDisplay(void * arg, mat4 view_mat){	
	ModelObject * m = (ModelObject *)arg;
	mat4 modelWorld_mat = Mult(m->translation_mat,m->rotation_mat);
	mat4 modelView_mat = Mult(view_mat,modelWorld_mat);
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
	glUniform3f(glGetUniformLocation(m->program, "light"),vLight.x,vLight.y,vLight.z);
	DrawModel(&(m->model), m->program, "in_Position", "in_Normal", NULL);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

/*
	
	

	GLfloat height = eye.y;
	GLfloat lXY = sqrt(lookDir.x*lookDir.x +lookDir.z*lookDir.z);
	GLfloat aFrustLow = atan2(lookDir.y,lXY)-PI/4;	
	GLfloat lDistance = abs(height/sin(aFrustLow));
	GLfloat lToGround = sqrt(lDistance*lDistance - height*height);	
*/

void drawTerrain(void* arg, mat4 view_mat){	
	ModelObject * m = (ModelObject *)arg;
	
	
	glUseProgram(m->program);
		
	vec3 eye = cameraObject->eye;
	vec3 center = cameraObject->center;
		
	vec3 lookDir = VectorSub(center,eye); 
	GLfloat aLook = atan2(lookDir.z,lookDir.x);

	GLfloat height = eye.y;
	GLfloat lXY = sqrt(lookDir.x*lookDir.x +lookDir.z*lookDir.z);
	GLfloat aFrustLow = atan2(lookDir.y,lXY)-PI/4;	
	GLfloat lDistance = abs(height/sin(aFrustLow));
	GLfloat lToGround = sqrt(lDistance*lDistance - height*height);	
	GLfloat x = m->translation_mat.m[3];
	GLfloat z = m->translation_mat.m[11];
	GLfloat aZero = PI/4;
	GLfloat aAbsolute = aLook-aZero;
	GLfloat lOffset = sqrt(x*x + z*z);//+lToGround;
	GLfloat aOffset = atan2(z,x)+aAbsolute;

	mat4 tmat = T(eye.x + lOffset*cos(aOffset),0,eye.z + lOffset*sin(aOffset));
	mat4 rmat = Ry(aAbsolute);

	mat4 modelmat = Mult(tmat,rmat);
	mat4 modelView_mat = Mult(view_mat, modelmat);
	mat4 modelViewProjection_mat = Mult(projection_mat, modelView_mat);

	glUniformMatrix4fv(glGetUniformLocation(m->program, "MVP_Matrix"), 1, GL_TRUE, modelViewProjection_mat.m);
  	glUniformMatrix4fv(glGetUniformLocation(m->program, "M_Matrix"), 1, GL_TRUE ,modelmat.m);
	glUniform3f(glGetUniformLocation(m->program, "u_MetaData"),GRID_SIZE,WORLD_SIZE,HEIGHT_SCALE);
	glUniform3f(glGetUniformLocation(m->program, "u_Light"),vLight.x,vLight.y,vLight.z);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m->texture);
	glEnable(GL_TEXTURE_2D);
	glUniform1i (glGetUniformLocation(m->program, "tex"),0 );
	

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_TERRAIN_NORMAL));
	glEnable(GL_TEXTURE_2D);
	glUniform1i (glGetUniformLocation(m->program, "normalTex"),1 );

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_TERRAIN_SNOW));
	glEnable(GL_TEXTURE_2D);
	glUniform1i (glGetUniformLocation(m->program, "snowTex"),2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_TERRAIN_GRASS));
	glEnable(GL_TEXTURE_2D);
	glUniform1i (glGetUniformLocation(m->program, "grassTex"),3);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_TERRAIN_ROCKS1));
	glEnable(GL_TEXTURE_2D);
	glUniform1i (glGetUniformLocation(m->program, "rockTex1"),4);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_TERRAIN_ROCKS2));
	glEnable(GL_TEXTURE_2D);
	glUniform1i (glGetUniformLocation(m->program, "rockTex2"),5);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_TERRAIN_ROCKS3));
	glEnable(GL_TEXTURE_2D);
	glUniform1i (glGetUniformLocation(m->program, "rockTex3"),6);

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

	glUseProgram(m->program);

	/* Super messy camera informations to put particles in the right place)*/
	vec3 vLook = VectorSub(cameraObject->center,cameraObject->eye);
	//vLook.y = 0.0;
	vLook = Normalize(vLook);
	vec3 vSide = CrossProduct(SetVector(0,1,0),vLook);
	vSide =	Normalize(vSide);
	vec3 vUp = CrossProduct(vLook, vSide);
	glUniform3f(glGetUniformLocation(m->program, "u_CamRight"),vSide.x,vSide.y,vSide.z);
	glUniform3f(glGetUniformLocation(m->program, "u_CamUp"),vUp.x,vUp.y,vUp.z);

	/* Pass light vector */
	glUniform3f(glGetUniformLocation(m->program, "u_Light"),vLight.x,vLight.y,vLight.z);

	/* View projection matrix */
	mat4 VP_mat = Mult(projection_mat,view_mat);
	glUniformMatrix4fv(glGetUniformLocation(m->program, "VP_Matrix"), 1, GL_TRUE , VP_mat.m);

	/*Bind texture */
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

