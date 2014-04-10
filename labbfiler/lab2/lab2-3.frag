#version 150

in vec3 normal;
in vec2 TexCoord;
out vec4 out_Color;
uniform float time;
uniform sampler2D texUnit;

void main(void)
{


	const vec3 light = vec3(0.0,1.0,0.0);
	float shade = max(dot(normalize(normal), light),0.0);
//	shade = 1.0;
	out_Color = shade*texture(texUnit, vec2(TexCoord.x+time/500.0,TexCoord.y));
}
