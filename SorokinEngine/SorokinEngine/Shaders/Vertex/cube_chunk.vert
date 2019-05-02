#version 330

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec2 in_TexCoord;

uniform mat4 projection, view, model;
out vec2 TexCoord;

void main(void) {
	TexCoord = in_TexCoord;
	gl_Position = projection * view * model * vec4(in_Position, 1.0);
}