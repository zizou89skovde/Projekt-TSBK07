#version 150

in  vec3 in_Position;
in  vec3 in_Normal;
in  vec2 in_TexCoord;
out vec3 normal;
out vec3 lightdir;

uniform mat4 MV_Matrix;
uniform mat4 MVP_Matrix;

void main(void)
{
	vec2 temp = in_TexCoord;
	mat3 normalMatrix = mat3(MV_Matrix);
	lightdir = normalMatrix*vec3(0.0,1.0,0.0);
	normal = normalMatrix*in_Normal;
	gl_Position = MVP_Matrix*vec4(in_Position, 1.0);

}
