#version 150

in  vec3 inPosition;
in vec2 inTexCoord;
in vec3 inNormal;
out vec2 texCoord;
out vec3 normal;
out vec3 lightdir;

// NY
uniform mat4 projMatrix;
uniform mat4 mdlMatrix;
uniform float u_Time;

void main(void)
{
	mat3 normalMatrix = mat3(mdlMatrix);
	lightdir = normalMatrix*vec3(0.0,1.0,0.0);
	texCoord = inTexCoord;

	vec3 newPosition = inPosition;
	float kx = 40.0;
	float kz = 20.0;
	float phi = 0.5;
	float Ax = 0.1;
	float Az = 0.07;

	newPosition.y = newPosition.y + Ax*cos( kx*u_Time +  newPosition.x) + Az*cos( kz*u_Time + newPosition.z + phi );

	float dx =  -kx*Ax*sin( kx*u_Time + newPosition.x );
	float dz =  -kz*Az*sin( kz*u_Time + newPosition.z + phi );
	float dy = -kx*Ax*sin( kx*u_Time + newPosition.x )  -kz*Az*sin( kz*u_Time + newPosition.z + phi );
	vec3 newNormal =  normalize(vec3(dx,1,dz)); 
	normal = normalMatrix*newNormal;

	gl_Position = projMatrix * mdlMatrix * vec4(newPosition, 1.0);
}
