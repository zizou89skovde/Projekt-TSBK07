#version 150

in  vec3 in_Position;
in  vec4 in_Offset;
in  vec2 in_TexCoord;
out vec2 texCoord;

uniform vec3 u_CamRight;
uniform vec3 u_CamUp;

uniform mat4 VP_Matrix;

void main(void)
{
	texCoord = in_TexCoord;
	float particleSize = in_Offset.w;
//	vec3 offs  = in_Offset.xyz;
//	vec3 pos   = in_Position.xzy*size + offs;
	vec3 vertexPosition_worldspace = 
		in_Offset.xyz
		+ u_CamRight * in_Position.x * particleSize
		+ u_CamUp * in_Position.z * particleSize;

	// Output position of the vertex
	gl_Position = VP_Matrix * vec4(vertexPosition_worldspace, 1.0f);
//	gl_Position = P_Matrix*(V_Matrix*vec4(0.0,0.0,0.0,1.0) + vec4(pos,1.0)); 
}

