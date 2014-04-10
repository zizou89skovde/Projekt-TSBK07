#version 150

out vec4 out_Color;

in vec3 normal;
in vec3 positionInView;
in vec2 TexCoord;

uniform float specularExponent[4];
uniform bool isDirectional[4];
uniform vec3 lightSourcesDirPosArr[4];
uniform vec3 lightSourcesColorArr[4];

uniform sampler2D texRutor;
uniform sampler2D texMaskros;

void main(void)
{
	vec3 viewDir = -normalize(positionInView);
	float distance = length(positionInView);	
	vec3 lightDir;
	vec3 resulting_color = vec3(0.0);
	int i;
	for(i = 0; i < 4; i++){
		if(!isDirectional[i]){
			lightDir = normalize(lightSourcesDirPosArr[i] - positionInView);
		}else{
			lightDir = -normalize(lightSourcesDirPosArr[i]);	
		}

		float intensity = clamp(dot(normalize(normal),lightDir),0.0,1.0);
		float diffuse_shading = intensity;	

		float base = clamp(dot(normalize(normal), normalize(lightDir + viewDir) ),0.0,1.0);
	
		intensity = pow(base,specularExponent[i]); 		

		float specular_shading = intensity; 
		
		vec3 color = lightSourcesColorArr[i];

		resulting_color += 0.5*color*specular_shading + 0.2*color*diffuse_shading;

	}

	vec4 colorRutor = texture(texRutor,TexCoord);
	vec4 colorMaskros = texture(texMaskros,TexCoord);
	vec4 finalColor = mix(colorRutor,colorMaskros,0.8);
	
	out_Color = finalColor+vec4(resulting_color,1.0);
}
