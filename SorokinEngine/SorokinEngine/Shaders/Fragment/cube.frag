
#version 330

in vec2 TexCoord;
out vec4 gl_FragColor;

uniform float blendValue;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main(void)
{
	gl_FragColor = mix(texture(ourTexture1, TexCoord),  texture(ourTexture2, vec2(1.0 - TexCoord.x, TexCoord.y),  texture(ourTexture2, TexCoord).a * blendValue), blendValue);
}