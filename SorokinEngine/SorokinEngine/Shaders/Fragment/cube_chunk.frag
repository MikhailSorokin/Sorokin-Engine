#version 330

in vec4 TexCoord;
out vec4 FragColor;

void main(void) {
	FragColor = vec4(TexCoord.w / 128.0, TexCoord.w / 256.0, TexCoord.w / 512.0, 1.0);
}