#version 150

uniform sampler2D tex;


in  vec3 in_Position;
in  vec3 in_Normal;
out vec2 texCoord;
out vec3 lightdir;
out float height_val;

uniform mat4 M_Matrix;
uniform mat4 MV_Matrix;
uniform mat4 MVP_Matrix;
uniform vec3 u_MetaData;


#define PI 3.1415926
#define ANGLE_0 PI/4.0
void main(void)
{
	/*extract meta data */
	float size = u_MetaData.x;
	float max_size = u_MetaData.y;
	float max_height = u_MetaData.z;
	/*extract orientation */
	vec4 offset    = M_Matrix*vec4(in_Position, 1.0);
	
	/* sample vertex y-pos from heightmap */
	highp vec2 tcoord = fract(offset.xz/max_size); 
	vec4 heightmap = texture(tex, tcoord);
	float height = heightmap.r*max_height;	

	/* TODO sample normals from normalmap */
	mat3 normalMatrix = mat3(MV_Matrix);

	lightdir = normalMatrix*vec3(0.0,1.0,0.0);


	/*adjust y-pos */
	vec3 pos = in_Position.xyz;
	pos.y = height;
	height_val = height/max_height;
	
	texCoord = tcoord; //jocke
	gl_Position = MVP_Matrix * vec4(pos, 1.0);
}
