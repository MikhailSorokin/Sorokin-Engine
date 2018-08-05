#version 330

uniform vec4 color;

in vec4 out_Color;
out vec4 gl_FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main(void) {
	gl_FragColor = texture(ourTexture, TexCoord);
}