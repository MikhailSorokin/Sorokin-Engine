#version 330 core
// It was expressed that some drivers required this next line to function properly
precision highp float;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 outColor;
out vec2 outTexCoord;

void main() {
	gl_Position = vec4(position, 1.0);	
	outColor = color;
	outTexCoord = texCoord;
}