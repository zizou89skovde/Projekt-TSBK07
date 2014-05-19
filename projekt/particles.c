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

	p->position[0] = iPos.x + 20.0*RAND_UNI();
	p->position[1] = iPos.y + RAND_UNI()*15.0;
	p->position[2] = iPos.z + 20.0*RAND_UNI();
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

void  createParticles(ParticleSystem * ps, int numParticles,int type){
	
	ps->particles = malloc(sizeof(Particle)*numParticles);
	Particle * p;

	vec3 vLook = VectorSub(cameraObject->center,cameraObject->eye);
	vLook.y = 0.0;
	vLook = Normalize(vLook);

	vec3 vSide = CrossProduct(vLook,SetVector(0,1,0));
	vSide.y = 0.0;
	vSide = Normalize(vSide);

	vec3 vComp1 = ScalarMult(vSide,DotProduct(ps->iPos,vLook));
	vec3 vComp2 = ScalarMult(vLook,DotProduct(ps->iPos,vSide));
	vec3 pos    =  VectorAdd(vComp1,vComp2);
	vec3 eye    = cameraObject->eye;
	eye.y = 0;
	pos = VectorAdd(eye,pos);
	pos.y = ps->iPos.y;
	printVec3("vLook",vLook);
	printVec3("vSide",vSide);
	printVec3("iPos",ps->iPos);
	printVec3("pos",pos);
	printVec3("eye",eye);	
	
	for(int i=0;i <numParticles; i++){
		p = &(ps->particles[i]);
		spawnParticle(p,type,pos,i);
	}	

}


bool isFrustum(Particle * p,CameraObject* co){
	
	vec3 pParticle =  toVec3(p->position);
	vec3 vLook     = VectorSub(co->center,co->eye);
	vec3 eye = VectorSub(co->eye,ScalarMult(Normalize(vLook),40.0));
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
		//printf("ARRAY particlePos x: %f y: %f z: %f \n ",p->position[0], p->position[1], p->position[2]);
		//printVec3("VEC particlePos",pos);
		vec3 diff = VectorSub(pos,cameraObject->eye);
		diff.y = 0;
		//printf("pos-eye --- x: %f y: %f z: %f \n ",diff.x, diff.y, diff.z);
		ps->particles[i].distToCam =  sqrt(DotProduct(diff,diff));
		//printf("distance to camera: %f p index: %d  \n ",ps->particles[i].distToCam,i);
		/* if a particle dies -> respawn him */
		if(!isFrustum(p,co)){
		   outOfFrustom = true; 
		   break;   
		}
	}
	if(outOfFrustom ){
	   printf("OUT OF FRUSTUM %d \n",1233);
	   vec3 vLook = VectorSub(cameraObject->center,cameraObject->eye);
	   vLook.y = 0.0;	
           mat4 viewMat  = getObjectFixedCameraMatrix(cameraObject)
	
           vec3 vComp1 = ScalarMult(vSide,DotProduct(ps->iPos,vLook));
	   vec3 vComp2 = ScalarMult(vLook,DotProduct(ps->iPos,vSide));
	   vec3 pos    =  VectorAdd(vComp1,vComp2);
	   vec3 eye    = cameraObject->eye;
	   eye.y = 0;
	   pos = VectorAdd(eye,pos);
	   pos.y = ps->iPos.y;
	   printVec3("vLook",vLook);
	   printVec3("vSide",vSide);
	   printVec3("iPos",ps->iPos);
	   printVec3("pos",pos);
	   printVec3("eye",eye);
	  // ArchObject * apa = NULL;
	   //apa->particleSystem = *ps;
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
		//printf("distance to camera,: %f , particle: %d \n ",ps->particles[i].distToCam,i);
		//printf("particle pos x: %f y: %f z: %f \n ",ps->particles[i].position[0], ps->particles[i].position[1], ps->particles[i].position[2]);
	}
	return buf;
}




