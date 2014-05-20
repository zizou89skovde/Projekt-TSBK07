#version 150

out vec4 outColor;
in vec2 texCoord;
uniform vec3 u_Light;
in float height_val;

uniform sampler2D snowTex;
uniform sampler2D grassTex;
uniform sampler2D rockTex1;
uniform sampler2D rockTex2;
uniform sampler2D rockTex3;
uniform sampler2D normalTex;

void main(void)
{
	vec3 light = normalize(u_Light.xzy);
	vec4 normalmap = texture(normalTex,texCoord);
	vec3 normal =  2.0*(normalmap.rgb -0.5);
	float intensity = clamp(dot(normalize(normal),normalize(light)),0.0,1.0);
	float diffuse = intensity;
	float ambient = 0.2;

	vec4 color;
	
	vec4 color_grass = 0.7*texture(grassTex,texCoord*100.0);
	vec4 color_snow = texture(snowTex,texCoord*100.0);
	vec4 color_rock = texture(rockTex3,texCoord*100.0);

	float as = max(height_val - 0.2,0.0);
	float ag = max(0.25 - height_val,0.0);
	float ar = max( 0.9 - normal.z, 0.0);
	vec3 blend = normalize(vec3(as,ag,ar));
	color = color_snow;
	color = mix(color,color_grass,blend.y);
	color = mix(color,color_rock,blend.z);


	outColor = (ambient + (1.0 - ambient)*diffuse)*color; //jocke

}


