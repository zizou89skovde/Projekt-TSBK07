#version 150

in vec3 in_Position;
in vec3 in_Normal;
in vec2 inTexCoord;
out vec3 normal;
out vec2 TexCoord;

uniform mat4 myMatrix;

void main(void)
{
	normal = mat3(myMatrix)*in_Normal;
	TexCoord = inTexCoord;
	gl_Position = myMatrix*vec4(in_Position, 1.0);
}