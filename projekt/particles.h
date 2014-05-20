#ifndef _PARTICLES_
#define _PARTICLES_

#define DT 0.01

#define PARTICLES_CLOUDS 0
#define CLOUD_HEIGHT 20.0
#define CLOUD_BOUNDS_X 100.0
#define CLOUD_BOUNDS_Z 100.0
#define CLOUD_BOUNDS_Y 3.0
#define MAX_CLOUD_SPEED 4.0


/*TYPES*/
#define EMITTER 0
#define CLUSTER 1
#define RANDOM  2


#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "types.h"
#include "graphics.h"
#include "GL_utilities.h"
#include "VectorUtils3.h"


void spawnParticle(Particle * p,int type,vec3 iPos,int i);
void addParticleSystem(ArchObject* obj,int type,int numParticles,void (*fp)(void *,void * ));
void  createParticles(ParticleSystem * , int ,int);
void  updateParticlesPositions(ParticleSystem * ps,CameraObject* co);
void sortParticles(ParticleSystem* );
vec3 getInitialPosition(ParticleSystem * ps);
void updateParticles(void* ,void * );
GLfloat * getBuffer(ParticleSystem * );



#endif
