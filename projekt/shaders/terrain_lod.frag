#version 150

out vec4 outColor;
in vec2 texCoord;
in vec3 normal;
in vec3 lightdir;
in float height_val;

void main(void)
{
	float intensity = clamp(dot(normalize(normal),normalize(lightdir)),0.0,1.0);
	outColor = vec4(height_val);
}
