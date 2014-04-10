#version 150

in vec3 in_Position;
in vec3 in_Normal;
out vec3 normal;

uniform mat4 myMatrix;

void main(void)
{
	normal = mat3(myMatrix)*in_Normal;
	gl_Position = myMatrix*vec4(in_Position, 1.0);
}
