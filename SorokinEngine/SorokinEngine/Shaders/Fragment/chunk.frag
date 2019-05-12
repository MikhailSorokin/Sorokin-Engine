
#version 330

in vec2 TexCoord;
out vec4 gl_FragColor;

uniform sampler2D ourTexture;

void main(void)
{
	gl_FragColor = texture(ourTexture, TexCoord);
}