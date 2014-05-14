#include "ui.h"

#define CAM_LOOK_SPEED 1.0
#define CAM_STRAFE_SPEED 1.0


void handleKeyboardInput(CameraObject * cameraObject) {

	vec3 lookDirection = Normalize(VectorSub(cameraObject->center,cameraObject->eye));
	
	if (keyIsDown('a')) {
		vec3 strafeDirection = Normalize(CrossProduct(cameraObject->up,lookDirection));
		strafeDirection = ScalarMult(strafeDirection,CAM_STRAFE_SPEED); 
		cameraObject->eye = VectorAdd(cameraObject->eye,strafeDirection);
		cameraObject->center = VectorAdd(cameraObject->center,strafeDirection);
	}
	if (keyIsDown('d')){
		vec3 strafeDirection = Normalize(CrossProduct(cameraObject->up,lookDirection));
		strafeDirection = ScalarMult(strafeDirection,CAM_STRAFE_SPEED); 
		cameraObject->eye = VectorSub(cameraObject->eye,strafeDirection);
		cameraObject->center = VectorSub(cameraObject->center,strafeDirection);
	}
	if (keyIsDown('w')) {
		lookDirection = ScalarMult(lookDirection,CAM_STRAFE_SPEED); 
		cameraObject->eye = VectorAdd(cameraObject->eye,lookDirection);
		cameraObject->center = VectorAdd(cameraObject->center,lookDirection);	
	}
	if (keyIsDown('s')) {
		lookDirection = ScalarMult(lookDirection,CAM_STRAFE_SPEED); 
		cameraObject->eye = VectorSub(cameraObject->eye,lookDirection);
		cameraObject->center = VectorSub(cameraObject->center,lookDirection);	
	}

	GLfloat lookAngle;
	GLfloat length;
	vec3 lookDir = VectorSub(cameraObject->eye,cameraObject->center);
	if (keyIsDown('e')) {
		length = sqrt(lookDir.x*lookDir.x+lookDir.z*lookDir.z);
		lookAngle = atan2(lookDir.x,lookDir.z);
		printf("lookAngle : %f , length: %f \n",lookAngle,length);
		lookAngle += 0.01;
		cameraObject->center = SetVector(cameraObject->eye.x + length*sin(lookAngle),
						 cameraObject->center.y,
						 cameraObject->eye.z + length*cos(lookAngle));

		lookDir = VectorSub(cameraObject->eye,cameraObject->center);
		lookAngle = atan2(lookDir.x,lookDir.z);
		printf("lookAngle2 : %f \n", lookAngle);
	}

	if (keyIsDown('q')) {
		length = sqrt(lookDir.x*lookDir.x+lookDir.z*lookDir.z);
		lookAngle = atan2(lookDir.x,lookDir.z);
		lookAngle -= 0.01;
		cameraObject->center = SetVector(cameraObject->eye.x + length*cos(lookAngle),
						 cameraObject->center.y,
						 cameraObject->eye.z + length*sin(lookAngle));
	}

	

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
