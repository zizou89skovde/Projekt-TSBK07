#version 150

out vec4 outColor;
in vec2 texCoord;
in vec3 normal;
in vec3 lightdir;
in float height_val;

uniform sampler2D snowTex;
uniform sampler2D grassTex;
uniform sampler2D rockTex1;
uniform sampler2D rockTex2;
uniform sampler2D rockTex3;

void main(void)
{

	vec3 light = normalize(lightdir.xzy);
	light.y *=-1.0;
	float intensity = clamp(dot(normalize(normal),normalize(light)),0.0,1.0);
	float diffuse = intensity;
	float ambient = 0.1;
	vec4 color_grey = vec4(0.5);
	vec4 color_green = vec4(0.0,0.7,0.0,5.0);
	vec4 color_white = vec4(1.0);
	color_white.w = 0.5;

	vec4 color = vec4(0.5);

	vec4 color_grass = 0.7*texture(grassTex,texCoord*50.0);
	vec4 color_snow = texture(snowTex,texCoord*50.0);
	vec4 color_rock = texture(rockTex3,texCoord*50.0);

	float as = max(height_val - 0.2,0.0);
	float ag = max(0.25 - height_val,0.0);
	float ar = max( 0.9 - normal.z, 0.0);
	vec3 blend = normalize(vec3(as,ag,ar));
	color = color_snow;
	color = mix(color,color_grass,blend.y);
	color = mix(color,color_rock,blend.z);
/*
	if(height_val > 0.4 && normal.z < 0.8){
		color = color_snow;
	}else if(normal.z < 0.9){
		color = color_rock;
	}else{
		color = color_grass;
	}
*/	

	outColor = (ambient + (1.0 - ambient)*diffuse)*color; //jocke

}


