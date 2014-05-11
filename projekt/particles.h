#ifndef _PARTICLES_
#define _PARTICLES_

#define DT 0.01

#define PARTICLES_CLOUDS 0
#define CLOUDS_HEIGHT 20.0
#define CLOUDS_BOUNDS_X 20.0
#define CLOUDS_BOUNDS_Y 20.0
#define MAX_CLOUDS_SPEED 4.0



#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "types.h"
#include "GL_utilities.h"
#include "VectorUtils3.h"

void  particlesInit(void);
void  createParticles(ParticleSystem * obj, int type);
void  updateParticles(ParticleSystem * obj);
void  respawnParticle(Particle * obj);
float * getBuffer(Particle * obj);

#endif
