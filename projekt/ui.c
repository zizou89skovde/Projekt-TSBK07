#include "ui.h"

#define CAM_LOOK_SPEED 1.0
#define CAM_STRAFE_SPEED 1.0
#define printVec3(str,v) printf( %s: x: %f y: %f z: %f",str,v.x,v.y,v.z)
struct timespec tKeyDownStart,tADown,tDDown, tKeyDown, tHelp;
double keyDownTime = 0;
GLfloat speed = 0.03;
void handleKeyboardInput(CameraObject * camObj, PhysicalObject* physObj) {

	GLfloat maxRotationAngle = 3.14/3;
	vec3 lookDir = VectorSub(camObj->center, camObj->eye);	
	vec3 rotationAxis;
	GLfloat rotationAngle;
	GLfloat tiltRotation;
	GLfloat angleIncrease = 0.05;
	GLfloat speedIncrease = 0.05;

	if( (keyIsDown('a')) || (keyIsDown('d')) || (keyIsDown('w')) || (keyIsDown('s')))
	{ 
			

			if (keyIsDown('a')) {	
							
				//set angle between new and old velocitydir and rotate velocity this angle.
				if((physObj->velocity.x == 0) && (physObj->velocity.y == 0) && (physObj->velocity.z == 0)) 
					rotationAngle = 0;
				else
					rotationAngle = -angleIncrease;

				physObj->velocity = MultMat3Vec3(mat4tomat3(Ry(rotationAngle)),physObj->velocity);  		
				physObj->helpAngle = physObj->helpAngle + rotationAngle; // Keep track of rotation for camera

				mat4 rotationMat1 = Ry(rotationAngle); 
				physObj->rotationMat = Mult(rotationMat1,physObj->rotationMat);
				//rotation 2
			
				if((physObj->tiltAngle < -0.25))
					tiltRotation = 0;
				else
					tiltRotation = 0.01;

				mat4 rotationMat2 = ArbRotate(SetVector(lookDir.x,0,lookDir.z),-tiltRotation);
				physObj->tiltAngle = physObj->tiltAngle - tiltRotation;
				
				physObj->rotationMat = Mult(rotationMat2,physObj->rotationMat);
				
			
			}
	
			if (keyIsDown('d')){
				//set angle between new and old velocitydir and rotate velocity this angle.
				if((physObj->velocity.x == 0) && (physObj->velocity.y == 0) && (physObj->velocity.z == 0)) 
					rotationAngle = 0;
				else
					rotationAngle = angleIncrease;
				physObj->velocity = MultMat3Vec3(mat4tomat3(Ry(rotationAngle)),physObj->velocity);  		
				physObj->helpAngle = physObj->helpAngle + rotationAngle; // Keep track of rotation for camera

				mat4 rotationMat1 = Ry(rotationAngle); 
				physObj->rotationMat = Mult(rotationMat1,physObj->rotationMat);
				//rotation 2
				if((physObj->tiltAngle > 0.25))
					tiltRotation = 0;
				else
					tiltRotation = 0.01;
	
				mat4 rotationMat2 = ArbRotate(SetVector(lookDir.x,0,lookDir.z),tiltRotation);
				physObj->tiltAngle = physObj->tiltAngle + tiltRotation;
				physObj->rotationMat = Mult(rotationMat2,physObj->rotationMat);
			}

			if (keyIsDown('w')) {

				//change velocity
				vec3 velocityDir = Normalize(SetVector(lookDir.x,0,lookDir.z));
				speed = speed + speedIncrease;
				physObj->velocity = ScalarMult(Normalize(VectorAdd(physObj->velocity, velocityDir)),speed);
			}

			if (keyIsDown('s')) {	
				vec3 velocityDir = Normalize(SetVector(lookDir.x,0,lookDir.z));
				speed = speed - speedIncrease;
				physObj->velocity = ScalarMult(Normalize(VectorAdd(physObj->velocity, velocityDir)),speed);
			}
	}
	if (keyIsDown('o')) {
		physObj->position.y = physObj->position.y + 0.3;
		
		}
		
	if (keyIsDown('l'))
		physObj->position.y = physObj->position.y - 0.3;
		
	// Ingen kontroll tangent nedtryckt TODO: återrotation
	
			
		
		
}

void handleMouseInput(int x ,int y) {
}
