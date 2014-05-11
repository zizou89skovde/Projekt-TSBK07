#version 150

in  vec3 in_Position;
in  vec2 in_TexCoord;

out vec2 texCoord;

uniform mat4 MV_Matrix;
uniform mat4 MVP_Matrix;

void main(void)
{
	texCoord = in_TexCoord;
	
	gl_Position = MVP_Matrix*vec4(in_Position, 1.0);

}
