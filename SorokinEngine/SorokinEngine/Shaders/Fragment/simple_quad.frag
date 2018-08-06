#version 330 core
// It was expressed that some drivers required this next line to function properly
precision highp float;

out vec4 gl_FragColor;

in vec3 outColor;
in vec2 outTexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

uniform float blendValue;

void main() {
	gl_FragColor = mix(texture(ourTexture1, outTexCoord),  texture(ourTexture2, vec2(1.0 - outTexCoord.x, outTexCoord.y),  texture(ourTexture2, outTexCoord).a * blendValue), blendValue);
}