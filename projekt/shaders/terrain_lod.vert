#version 150

uniform sampler2D tex;

in  vec3 in_Position;
in  vec3 in_Normal;
in vec2 in_TexCoord;
out vec2 texCoord;
out vec3 normal;
out vec3 lightdir;
out float height_val;

uniform mat4 MV_Matrix;
uniform mat4 MVP_Matrix;
uniform vec3 u_Orientation;
uniform vec2 u_MetaData;

#define MAX_Y 10.0

void main(void)
{
	/*extract meta data */
	float size = u_MetaData.x;
	float max_size = u_MetaData.y;
	
	/*extract orientation */
	vec2 offset = u_Orientation.xy;

	texCoord = in_TexCoord;

	/* sample vertex y-pos from heightmap */
	vec2 tcoord = (in_Position.xy+offset)/max_size; 
	vec4 heightmap = texture(tex, tcoord);
	float height = heightmap.r*10.0;

	/* TODO sample normals from normalmap */
	mat3 normalMatrix = mat3(MV_Matrix);
	lightdir = normalMatrix*vec3(0.0,1.0,0.0);
	normal = normalMatrix*in_Normal;

	/*adjust y-pos */
	vec3 pos = in_Position.xzy;
	pos.y = height;
	height_val = height/10.0;;
	
	texCoord = in_TexCoord;
	gl_Position = MVP_Matrix * vec4(pos, 1.0);
}
