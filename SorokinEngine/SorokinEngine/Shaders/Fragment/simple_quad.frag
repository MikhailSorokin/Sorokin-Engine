#version 330 core
// It was expressed that some drivers required this next line to function properly
precision highp float;

out vec4 gl_FragColor;

in vec3 outColor;
in vec2 outTexCoord;

uniform sampler2D ourTexture;

void main() {
	gl_FragColor = texture(ourTexture, outTexCoord) * outColor.y;
}