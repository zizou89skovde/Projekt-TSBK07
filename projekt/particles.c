#include "particles.h"

#define RAND_UNI() 2.0*((float)rand()/(float)RAND_MAX - 0.5)
#define RAND() (float)rand()/(float)RAND_MAX
#define toVec3(X) SetVector(X[0],X[1],X[2])
#define LENGTH(X,Y) sqrt(dot(
void  particlesInit(void){

}
void spawnParticle(Particle * p){
	p->position[0] = RAND()*CLOUD_BOUNDS_X;
	p->position[1] = CLOUD_HEIGHT + RAND_UNI()*2;
	p->position[2] = RAND()*CLOUD_BOUNDS_Z;
	p->position[3] = 2 + RAND();
	p->velocity[0] = RAND_UNI)*MAX_CLOUDS_SPEED;
	p->velocity[1] = 0;
	p->velocity[2] = RAND_UNI()*MAX_CLOUDS_SPEED;
	p->lifetime = 10 + 3*RAND_UNI();
}

void  createParticles(ParticleSystem * obj, int numParticles,int type){

	obj->particles = malloc(sizeof(Particle)*numPArticles);
	Particle * p;
	for(int i=0;i <numParticles; i++){
		p = &(obj->particles[i]);
		spawnParticle(p);
	}	

}
void  updateParticlesPositions(ParticleSystem * ps,CameraObject* co){
	Particle * p;
	for(int i=0;i < ps.numParticles; i++){

		p = &(obj->particles[i]);
		p->position[0] += p->velocity[0]*DT;
		p->position[1] += p->velocity[1]*DT;
		p->position[2] += p->velocity[0]*DT;

		obj->particles[i].lifetime -= DT;
		
		/* Calc distance to camera, this property is used for the sorting routine */
		vec3 pos = toVec3(p->position);
		vec3 diff = VectorSub(pos,co->eye);
		obj->particles[i].distToCam =  sqrt(DotProduct(diff,diff));

		/* if a particle dies -> respawn him */
		if(obj->particles[i].lifetime <= 0){
		   spawnParticle(p);
		}
	}
}

void sortParticles(ParticleSystem* ps){
	Particle p;
	Particle pNext;
	for(int i=0;i<ps.numParticles-1;i++){

		p = obj->particles[i];
		p_next = obj->particles[i];

		if(p.distToCam > pNext->distToCam){
   			particles[i] = p_next;
  			particles[i+1] = p;
		}
	}

}

void updateParticles(ParticleSystem* ps,CameraObject* co){
	updateParticlePositions(ps,co);
	sortParticles(ps);

}

float * getBuffer(ParticleSystem * ps){
	float * buf = malloc(4*ps.numParticles*sizeof(float));
	int idx = 0;
	for(int i=0;i<ps.numParticles-1;i++){
		buf[idx++] = ps->particles[i].position[0];	
		buf[idx++] = ps->particles[i].position[1];
		buf[idx++] = ps->particles[i].position[2];
		buf[idx++] = ps->particles[i].position[3];
	}
}


