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

#define MAX_Y 10.0

void main(void)
{
	texCoord = in_TexCoord;

	/* sample vertex y-pos from heightmap */
	vec2 tcoord = vec2(in_Position.x/40.0,in_Position.y/40.0);
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
	
	gl_Position = MVP_Matrix * vec4(pos, 1.0);
}
