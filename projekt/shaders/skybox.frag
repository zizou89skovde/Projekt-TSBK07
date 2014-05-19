#version 150
in vec2 TexCoord;
in vec3 frag_Position;
out vec4 out_Color;
uniform sampler2D tex;
uniform vec3 light;

void main(void)
{
	vec3 inLight;
	vec3 pos = frag_Position;
	pos.x = abs(pos.x);
	float d  = length(normalize(pos) - normalize(light));

	/*Sky */
	float skyBrightness = pow(max(light.y,0.0),2.0);
	float illumationArea = 20.0;
	float skyIllumination = 0.8*max(1.0 - d/illumationArea,0.0);

	/*Sun*/
	float sunSize = 1.0;
	float sun = max(1.0 - d*sunSize,0.0);
	float sunIllumination = clamp(light.y+0.6,0.0,1.0);
	//sun = pow(sun,5.0);

	/*Sunset effect */
	float sunsetBrightness = max(light.y,0.0)+0.4;
	float sunsetFactor = clamp(1.0-sunsetBrightness,0.0,1.0);
	vec4 color = vec4(0.3*sunsetFactor,0.3-0.3*sunsetFactor,0.5-0.5*sunsetFactor,1.0);

	out_Color =  sun*sunIllumination +min((skyBrightness+skyIllumination),1.0)*color; //vec4(0.0,0.3,0.6,1.0); //texture(tex,TexCoord); 

}

