#include "particles.h"

#define RAND_UNI() 2.0*((float)rand()/(float)RAND_MAX - 0.5)
#define RAND() (float)rand()/(float)RAND_MAX

void  particlesInit(void){

}
void  createParticles(ParticleObject * obj, int numParticles,int type){

	obj->particles = malloc(sizeof(Particle)*numPArticles);
	
	for(int i=0;i <numParticles; i++){
		obj->particles[i].position[0] = RAND()*CLOUD_BOUNDS_X;
		obj->particles[i].position[1] = CLOUD_HEIGHT + RAND_UNI()*2;
		obj->particles[i].position[2] = RAND()*CLOUD_BOUNDS_Z;

		obj->particles[i].velocity[0] = RAND_UNI)*MAX_CLOUDS_SPEED;
		obj->particles[i].velocity[1] = 0;
		obj->particles[i].velocity[2] = RAND_UNI()*MAX_CLOUDS_SPEED;
	}	

}
void  updateParticles(ParticleObject * obj){

}
float * getBuffer(ParticleObject * obj){

}

