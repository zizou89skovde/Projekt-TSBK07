#version 150

in vec3 in_Position;
in vec2 in_TexCoord;

out vec2 TexCoord;
out vec3 frag_Position;
uniform mat4 V_Matrix;
uniform mat4 P_Matrix;

void main(void)
{
	TexCoord = in_TexCoord;
	frag_Position = in_Position;
	gl_Position =  P_Matrix*(mat4(mat3(V_Matrix))*vec4(in_Position, 1.0)); //mat4(mat3(V_Matrix))
}
