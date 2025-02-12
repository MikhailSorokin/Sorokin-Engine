#version 330

uniform vec4 color;

in vec4 out_Color;
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main(void) {
	FragColor = texture(ourTexture, TexCoord);
}