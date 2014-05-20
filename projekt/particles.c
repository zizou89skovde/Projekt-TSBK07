#include "particles.h"

#define RAND_UNI() (float)(2.0*(((float)rand())/(float)RAND_MAX - 0.5))
#define RAND() (float)rand()/(float)RAND_MAX
#define toVec3(X) SetVector(X[0],X[1],X[2])
#define Multv3v3(V1,V2)  SetVector(V1.x*V2.x,V1.y*V2.y,V1.z*V2.z)
#define printVec3(String,v) printf("%s x: %f y: %f z: %f \n",String,v.x,v.y,v.z)
void spawnEmitter(Particle * p,vec3 iPos,int i){
	p->position[0] = iPos.x;
	p->position[1] = iPos.y;
	p->position[2] = iPos.z;
	
	p->position[3] = 0.1;// + 3*RAND();
	p->velocity[0] = RAND_UNI()*MAX_CLOUD_SPEED;
	p->velocity[1] = 0;
	p->velocity[2] = RAND_UNI()*MAX_CLOUD_SPEED;
	p->lifetime = 10 + 3*RAND_UNI();
}

void spawnCluster(Particle * p,vec3 iPos,int i){

	p->position[0] = iPos.x + 200.0*RAND_UNI();
	p->position[1] = iPos.y + RAND_UNI()*15.0;
	p->position[2] = iPos.z + 200.0*RAND_UNI();
	p->position[3] = 30.0; // + 3*RAND();


	p->velocity[0] = cos(iPos.x)*MAX_CLOUD_SPEED; ///+RAND_UNI();
	p->velocity[1] = 0.0;
	p->velocity[2] = sin(iPos.x)*MAX_CLOUD_SPEED; //+RAND_UNI();
	p->lifetime = 100000;
	

	
}

void spawnRandom(Particle * p,int i){
	p->position[0] = RAND()*CLOUD_BOUNDS_X;
	p->position[1] = CLOUD_HEIGHT + RAND_UNI()*2;
	p->position[2] = RAND()*CLOUD_BOUNDS_Z;
	p->position[3] = 5 + 3*RAND();
	p->velocity[0] = RAND_UNI()*MAX_CLOUD_SPEED;
	p->velocity[1] = 0;
	p->velocity[2] = RAND_UNI()*MAX_CLOUD_SPEED;
	p->lifetime = 10 + 3*RAND_UNI();
}

void spawnParticle(Particle * p,int type,vec3 iPos,int i){
	switch(type){
	case EMITTER: 
		//spawnEmitter(p,iPos,i);
	break;
	case CLUSTER:
		spawnCluster(p,iPos,i);

	break;
	case RANDOM: 
		//spawnRandom(p,i);
	break;

	default:
	break;
	}

}

void addParticleSystem(ArchObject* obj,int type,int numParticles,void (*fp)(void *,void * )){
	obj->particleSystem.type = type;
	obj->particleSystem.updateFunc = fp;
	obj->particleSystem.numParticles = numParticles;
	obj->particleSystem.iPos = obj->physicalObj.position;
	/*genereate offset buffer for instanced draw routine */
	createOffsetBuffer(&(obj->modelObj.model));
	obj->modelObj.model.numInstances = numParticles;

	/*spawn particles at random locations with random velocity */
	createParticles(&obj->particleSystem,numParticles,type);
}

vec3 getInitialPosition(ParticleSystem * ps){

	vec3 vLook = VectorSub(cameraObject->center,cameraObject->eye);
	vLook.y = 0.0;
	vLook = Normalize(vLook);
	vec3 vSide = CrossProduct(SetVector(0,1,0),vLook);
	vSide.y = 0.0;
	vSide = Normalize(vSide);
	vec3 pos    =  VectorAdd(ScalarMult(vSide,ps->iPos.x),ScalarMult(vLook,ps->iPos.z));
	vec3 eye    = cameraObject->eye;
	printVec3("eye",eye);		
	printVec3("vLook",vLook);		
	printVec3("vSide",vSide);		
	eye.y = 0;
	pos = VectorAdd(eye,pos);
	pos.y = ps->iPos.y;
	printVec3("pos",pos);
	return pos;

}

void  createParticles(ParticleSystem * ps, int numParticles,int type){
	
	ps->particles = malloc(sizeof(Particle)*numParticles);
	Particle * p;
	vec3 pos = getInitialPosition(ps);

	for(int i=0;i <numParticles; i++){
		p = &(ps->particles[i]);
		spawnParticle(p,type,pos,i);
	}	

}


bool isFrustum(Particle * p,CameraObject* co){
	
	vec3 pParticle =  toVec3(p->position);
	vec3 vLook     = VectorSub(co->center,co->eye);
	vec3 eye = VectorSub(co->eye,ScalarMult(Normalize(vLook),500.0));
	vLook = Normalize(vLook);	
	vec3 vParticle = VectorSub(pParticle,eye);
	vParticle = Normalize(vParticle);
	GLfloat dp = DotProduct(vParticle,vLook);
	//sprintf("dp x: %f",dp);
	return dp > 0.8;
	
}
void  updateParticlesPositions(ParticleSystem * ps,CameraObject* co){
	Particle * p;
	bool outOfFrustom = false;
	for(int i=0;i < ps->numParticles; i++){

		p = &(ps->particles[i]);
		p->position[0] += p->velocity[0]*DT;
		p->position[1] += p->velocity[1]*DT;
		p->position[2] += p->velocity[2]*DT;

		ps->particles[i].lifetime -= DT;
		
		/* Calc distance to camera, this property is used for the sorting routine */
		vec3 pos = toVec3(p->position);
		vec3 vEyeToPos  = VectorSub(pos,cameraObject->eye);
		vec3 vLook = Normalize(VectorSub(cameraObject->center,cameraObject->eye));
		GLfloat distance = DotProduct(vLook,vEyeToPos);
		ps->particles[i].distToCam = distance;
	
		/* if a particle dies -> respawn him */
		if(!isFrustum(p,co)){
		   outOfFrustom = true; 
		   break;   
		} 
	}
	if(outOfFrustom ){
	   printf("OUT OF FRUSTUM %d \n",1233);	
      	   vec3 pos = getInitialPosition(ps);
	
	   for(int i=0;i < ps->numParticles; i++){
		p = &(ps->particles[i]);	
		spawnParticle(p,ps->type,pos,i);
 	   }
	   outOfFrustom = false;
	 
	}
}

void sortParticles(ParticleSystem* ps){
	Particle p;
	Particle pNext;
	for(int i=0;i<ps->numParticles-1;i++){

		p = ps->particles[i];
		pNext = ps->particles[i+1];
		
		if(p.distToCam < pNext.distToCam){
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
		
	}
	return buf;
}




