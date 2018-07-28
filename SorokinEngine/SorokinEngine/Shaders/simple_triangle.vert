#version 330 core
// in_Position was bound to attribute index 0
layout (location = 0) in vec2 in_Position;

// We output the ex_Color variable to the next shader in the chain
out vec3 ex_Color;
void main(void) {
    // Since we are using flat lines, our input only had two points: x and y.
    // Set the Z coordinate to 0 and W coordinate to 1

    gl_Position = vec4(in_Position.x, in_Position.y, 0.0, 1.0);

    ex_Color = vec3(0.0, 0.0, 1.0);
}