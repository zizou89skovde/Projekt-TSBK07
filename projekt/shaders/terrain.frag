#version 150

out vec4 outColor;
in vec2 texCoord;
in vec3 normal;
in vec3 lightdir;
uniform sampler2D tex;

void main(void)
{
	float intensity = clamp(dot(normalize(normal),normalize(lightdir)),0.0,1.0);
	float diffuse = intensity;
	float ambient = 0.2;
	outColor = (ambient + (1.0 -ambient)*diffuse)*texture(tex, texCoord);
}
