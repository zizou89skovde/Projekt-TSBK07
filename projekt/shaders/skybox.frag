#version 150
in vec2 TexCoord;
out vec4 out_Color;
uniform sampler2D tex;

void main(void)
{
	out_Color =  texture(tex,TexCoord);
}
