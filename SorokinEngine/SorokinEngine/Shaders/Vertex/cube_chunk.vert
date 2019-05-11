#version 330

layout (location = 0) in vec3 in_Position;

uniform mat4 projection, view, model;
out vec2 TexCoord;

void main(void) {
	TexCoord = in_Position.xy;
	gl_Position = projection * view * model * vec4(in_Position, 1.0);
}