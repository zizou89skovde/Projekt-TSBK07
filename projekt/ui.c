#include "ui.h"

#define CAM_LOOK_SPEED 1.0
#define CAM_STRAFE_SPEED 1.0
#define printVec3(str,v) printf( %s: x: %f y: %f z: %f",str,v.x,v.y,v.z)
struct timespec tKeyDownStart,tADown,tDDown, tKeyDown, tHelp;
double keyDownTime = 0;
GLfloat speed = 0.03;
void handleKeyboardInput(CameraObject * camObj, PhysicalObject* physObj) {


	printf("pos: y %f  \n",physObj->position.y );
	//printf("vel: x %f y %f z %f \n", physObj->velocity.x, physObj->velocity.y, physObj->velocity.z );

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
	//int screenWidth  =  glutGet(GLUT_WINDOW_WIDTH);
	//int screenHeight =  glutGet(GLUT_WINDOW_HEIGHT);
/*
	vec3 lookDirection        = Normalize(VectorSub(camCenter,camEye));
	vec3 horizontalDirection  = CrossProduct(camUp,lookDirection);
	vec3 verticalDirection  = CrossProduct(horizontalDirection,lookDirection);

	GLfloat dX = x - oldMouseX;
	GLfloat dY = y - oldMouseY;

	oldMouseX = x;
	oldMouseX = y;

	horizontalDirection  = Normalize(horizontalDirection);
	horizontalDirection  = ScalarMult(horizontalDirection,dX*CAM_ROTATION_SPEED);

	verticalDirection    = Normalize(verticalDirection);
	verticalDirection    = ScalarMult(verticalDirection,dX*CAM_ROTATION_SPEED);

	vec3 resultDirection =  
	

*/

	//camCenter = VectorAdd(camEye,lookDirection);
	//camCenter.y = dY;
	

}






		//change velocity, should rotate the velocity by some angle here instead.
				//strafeDirection = Normalize(CrossProduct(camObj->up,lookDir));
				//vec3 newDir = Normalize(VectorAdd(physObj->velocity,strafeDirection));
			


				//Rotate char
				//rotaion1
				/*rotationAxis =	SetVector(0,1,0);
				vec3 lookDirVelOffset = VectorSub(lookDir,physObj->velocity);
				GLfloat lookDirVelOffsetLength = sqrt(DotProduct(lookDirVelOffset,lookDirVelOffset));
				GLfloat lookDirLength = sqrt(DotProduct(lookDir,lookDir));
				//rotationAngle = acos(DotProduct(lookDir,lookDirVelOffset)/(lookDirLength*lookDirVelOffsetLength)); */





//previous d

/*
				//change velocity
				strafeDirection = Normalize(CrossProduct(lookDir,camObj->up));
				vec3 newDir = Normalize(VectorAdd(physObj->velocity,strafeDirection));
				rotationAngle = acos(DotProduct(lookDir,newDir));
				physObj->velocity = MultMat3Vec3(mat4tomat3(Ry(-rotationAngle)),physObj->velocity);  
					//	physObj->velocity = ScalarMult(Normalize(VectorAdd(physObj->velocity,strafeDirection)),speed);// SetVector(keyDownTime*rotationSpeed,0,0);	
				//Rotate char
				*/
			
				//rotaion1
				/* rotationAxis =	SetVector(0,-1,0);
				vec3 lookDirVelOffset = VectorSub(lookDir,physObj->velocity);
				GLfloat lookDirVelOffsetLength = sqrt(DotProduct(lookDirVelOffset,lookDirVelOffset));
				GLfloat lookDirLength = sqrt(DotProduct(lookDir,lookDir));
				rotationAngle = acos(DotProduct(lookDir,lookDirVelOffset)/(lookDirLength*lookDirVelOffsetLength));*/
				/*physObj->helpAngle = physObj->helpAngle - rotationAngle; // Keep track of rotation for camera
				mat4 rotationMat1 = Ry(-rotationAngle); //ArbRotate(rotationAxis,rotationAngle);
				//rotation 2
				//rotationAxis = lookDirVelOffset;  //SetVector(0,0,-newLookDir.z);

				if(angleToRotate > maxRotationAngle)
					angleToRotate = maxRotationAngle;

				rotationAngle = 0.01;
				
				mat4 rotationMat2 = IdentityMatrix(); //ArbRotate(rotationAxis,rotationAngle);
				

				physObj->rotationMat = Mult(Mult(rotationMat2,rotationMat1),physObj->rotationMat); */
