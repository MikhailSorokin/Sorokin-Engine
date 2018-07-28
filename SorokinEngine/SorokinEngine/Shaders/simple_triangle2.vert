#version 330 core
// It was expressed that some drivers required this next line to function properly
precision highp float;

layout (location = 0) in vec2 in_Position;
layout (location = 1) in vec3 in_Color;

out vec3 ex_Color;

void main(void) {

	gl_Position = vec4(in_Position.x, in_Position.y, 0.0, 1.0);
	ex_Color = in_Color;
}