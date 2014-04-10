#version 150


in vec3 in_Position;
in vec2 in_TexCoord;
out vec2 TexCoord;

uniform mat4 view_matrix;
uniform mat4 proj_matrix;


void main(void)
{
	
	
	TexCoord = in_TexCoord;
	gl_Position =  proj_matrix*mat4(mat3(view_matrix))*vec4(in_Position, 1.0);
}
