#version 150


in vec3 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoord;
out vec3 normal;
out vec3 positionInView;
out vec2 TexCoord;


uniform mat4 MV_Matrix;
uniform mat4 MVP_Matrix;




void main(void)
{
	normal 	 = mat3(MV_Matrix)*in_Normal;

	positionInView = vec3(MV_Matrix*vec4(in_Position, 1.0));
	
	TexCoord = in_TexCoord;
	gl_Position = MVP_Matrix*vec4(in_Position, 1.0);
}