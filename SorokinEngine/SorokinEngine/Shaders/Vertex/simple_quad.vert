#version 330 core
// It was expressed that some drivers required this next line to function properly
precision highp float;

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Color;
layout (location = 2) in vec2 in_TexCoord;

out vec3 outColor;
out vec2 outTexCoord;

uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(in_Position, 1.0);	
	outColor = in_Color;
	outTexCoord = in_TexCoord;
}