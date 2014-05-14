#include "particles.h"

#define RAND_UNI() 2.0*((float)rand()/(float)RAND_MAX - 0.5)
#define RAND() (float)rand()/(float)RAND_MAX
#define toVec3(X) SetVector(X[0],X[1],X[2])
#define LENGTH(X,Y) sqrt(dot(

void spawnParticle(Particle * p,int i){

	p->position[0] = RAND()*CLOUD_BOUNDS_X;
	p->position[1] = CLOUD_HEIGHT + RAND_UNI()*2;
	p->position[2] = RAND()*CLOUD_BOUNDS_Z;
	p->position[3] = 5 + 3*RAND();
	p->velocity[0] = RAND_UNI()*MAX_CLOUD_SPEED;
	p->velocity[1] = 0;
	p->velocity[2] = RAND_UNI()*MAX_CLOUD_SPEED;
	p->lifetime = 10 + 3*RAND_UNI();
}

void addParticleSystem(ArchObject* obj,int numParticles,void (*fp)(void *,void * )){

	obj->particleSystem.updateFunc = fp;
	obj->particleSystem.numParticles = numParticles;

	/*genereate offset buffer for instanced draw routine */
	createOffsetBuffer(&(obj->modelObj.model));
	obj->modelObj.model.numInstances = numParticles;

	/*spawn particles at random locations with random velocity */
	createParticles(&obj->particleSystem,numParticles,-1);
}

void  createParticles(ParticleSystem * ps, int numParticles,int type){

	ps->particles = malloc(sizeof(Particle)*numParticles);
	Particle * p;
	for(int i=0;i <numParticles; i++){
		p = &(ps->particles[i]);
		spawnParticle(p,i);
	}	

}
void  updateParticlesPositions(ParticleSystem * ps,CameraObject* co){
	Particle * p;
	for(int i=0;i < ps->numParticles; i++){

		p = &(ps->particles[i]);
		p->position[0] += p->velocity[0]*DT;
		p->position[1] += p->velocity[1]*DT;
		p->position[2] += p->velocity[0]*DT;

		ps->particles[i].lifetime -= DT;
		
		/* Calc distance to camera, this property is used for the sorting routine */
		vec3 pos = toVec3(p->position);
		//printf("particle pos x: %f y: %f z: %f \n ",p->position[0], p->position[1], p->position[2]);
		vec3 diff = VectorSub(pos,co->eye);
		//printf("pos-eye --- x: %f y: %f z: %f \n ",diff.x, diff.y, diff.z);
		ps->particles[i].distToCam =  sqrt(DotProduct(diff,diff));
		//printf("distance to camera: %f  \n ",ps->particles[i].distToCam);
		/* if a particle dies -> respawn him */
		if(ps->particles[i].lifetime <= 0){
		   spawnParticle(p,i);
		}
	}
}

void sortParticles(ParticleSystem* ps){
	Particle p;
	Particle pNext;
	for(int i=0;i<ps->numParticles-1;i++){

		p = ps->particles[i];
		pNext = ps->particles[i+1];
		/*
		if(p.distToCam < pNext.distToCam){
   			ps->particles[i] = pNext;
  			ps->particles[i+1] = p;
		}*/
		if(p.position[1] > pNext.position[1]){
   			ps->particles[i] = pNext;
  			ps->particles[i+1] = p;
		}
	
	}

}

void updateParticles(void* arg,void * arg_cam){
	CameraObject * co 	= (CameraObject *)arg_cam;
	ArchObject * obj  	= (ArchObject *)arg;
	ParticleSystem * ps 	= &(obj->particleSystem);
	ModelObject * modelObj 	= &(obj->modelObj);

	
	updateParticlesPositions(ps,co);

	/*sorting particles required for the alpha blending */
	for(int j = 0; j < 10; j++)
		sortParticles(ps);

	/*upload offset buffer for instanced draw routine */	
	GLfloat * buf = getBuffer(ps);
	uploadOffsetBuffer(&(modelObj->model), buf, ps->numParticles);
	free(buf);

}

GLfloat * getBuffer(ParticleSystem * ps){
	float * buf = malloc(4*ps->numParticles*sizeof(float));
	int idx = 0;
	
	for(int i=0; i < ps->numParticles ; i++){
		
		buf[idx++] = ps->particles[i].position[0];	
		buf[idx++] = ps->particles[i].position[1];
		buf[idx++] = ps->particles[i].position[2];
		buf[idx++] = ps->particles[i].position[3];
		//printf("distance to camera,: %f , particle: %d \n ",ps->particles[i].distToCam,i);
		//printf("particle pos x: %f y: %f z: %f \n ",ps->particles[i].position[0], ps->particles[i].position[1], ps->particles[i].position[2]);
	}
	return buf;
}


