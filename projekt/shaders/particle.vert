#version 150

in  vec3 in_Position;
in  vec4 in_Offset;
in  vec2 in_TexCoord;
out vec2 texCoord;

uniform mat4 MV_Matrix;
uniform mat4 V_Matrix;
uniform mat4 P_Matrix;

void main(void)
{
	texCoord = in_TexCoord;
	float size = in_Offset.w;
	vec3 offs  = in_Offset.zyx;
	offs.z *=-1;
	vec3 pos   = in_Position.xzy*size + offs;
	gl_Position = P_Matrix*(V_Matrix*vec4(0.0,0.0,0.0,1.0) + vec4(pos, 1.0)); //(MV_Matrix*vec4(0.0,0.0,0.0,1.0) + 

}
