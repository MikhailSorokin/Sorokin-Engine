#version 330

//uniform vec4 color;

in vec4 out_Color;
out vec4 gl_FragColor;

void main(void) {
	gl_FragColor = out_Color;
}