#version 150

out vec4 outColor;

in vec3 normal;
in vec3 lightdir;

void main(void)
{

	float intensity = clamp(dot(normalize(normal),normalize(lightdir)),0.0,1.0);
	float diffuse = intensity;
	float ambient = 0.4;
	outColor = (ambient + (1.0 - ambient)*diffuse)*vec4(0.1,0.9,0.15,1.0); 
}