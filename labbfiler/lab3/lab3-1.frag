#version 150

in vec3 normal;
in vec2 TexCoord;
out vec4 out_Color;
uniform float time;
uniform sampler2D texUnit;

void main(void)
{


	const vec3 light = vec3(1.0,1.0,0.0);
	float diffuse_shading = max(dot(normalize(normal), normalize(light)),0.0);
//	diffuse_shading = 1.0;
	out_Color = diffuse_shading*vec4(1.0);	//texture(texUnit, vec2(TexCoord.x,TexCoord.y));
}