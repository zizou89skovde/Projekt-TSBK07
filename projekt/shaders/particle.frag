#version 150

out vec4 outColor;
uniform vec3 u_Light;
in vec2 texCoord;

uniform sampler2D tex;
void main(void)
{
	float attenutaion = u_Light.y;
	vec4 color = texture(tex, texCoord);
	color.a *= clamp(attenutaion,0.4,0.6);
	color.r -= clamp(1.0 - attenutaion,0.0,0.2);
	color.g -= clamp(1.0 - attenutaion,0.0,0.3);
	color.b -= clamp(1.0 - attenutaion,0.0,0.3);
	outColor = color - 0.1;
}
