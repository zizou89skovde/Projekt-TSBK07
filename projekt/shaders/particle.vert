#version 150

in  vec3 in_Position;
in  vec4 in_Offset;
in  vec2 in_TexCoord;
out vec2 texCoord;

uniform mat4 MV_Matrix;
uniform mat4 MVP_Matrix;

void main(void)
{
	texCoord = in_TexCoord;
	float size = in_Offset.w;
	vec3 pos   = in_Position*size + in_Offset.xyz;
	gl_Position = MVP_Matrix*vec4(pos, 1.0);

}
