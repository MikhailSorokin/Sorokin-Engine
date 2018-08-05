#version 330
precision highp float;

layout (location = 0) in vec2 in_Position;
layout (location = 1) in vec3 in_Color;
layout (location = 2) in vec2 in_Texture;
uniform float deltaOffset;

out vec4 out_Color;
out vec2 out_TexCoord;

void main(void) {
	gl_Position = vec4(in_Position.x + deltaOffset, in_Position.y, 0.f, 1.f);	
	out_TexCoord = in_Texture;
	//out_Color = vec4(in_Position, 0.f, 1.f);
}