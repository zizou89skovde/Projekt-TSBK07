#version 150

out vec4 outColor;
in vec2 texCoord;
in vec3 normal;
in vec3 lightdir;
in float height_val;

void main(void)
{
	
	float intensity = clamp(dot(normalize(normal),normalize(lightdir)),0.0,1.0);
	float diffuse = intensity;
	float ambient = 0.2;
	vec4 color_grey = vec4(0.5);
	vec4 color_green = vec4(0.0,0.7,0.0,5.0);
	vec4 color_white = vec4(1.0);
	color_white.w = 0.5;
	vec4 color = vec4(0.5);
	if(height_val > 0.7){
		color = mix(color,color_white,0.5);
	}
	if(normal.z < 0.8) {
		color = mix(color,color_grey,0.5);
	}else{
		if(height_val <= 0.7){
			color = mix(color,color_green,0.5);
		}
	}
	outColor = (ambient+ (1.0-ambient)*diffuse)*color; //jocke
	//outColor = vec4(height_val); //jocke
}
