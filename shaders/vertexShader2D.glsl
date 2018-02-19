#version 420

layout (location = 0) in vec2 position;
layout (location = 1) in vec4 color;

uniform mat4 transform;

out vec4 color0;

void main()
{
    gl_Position = transform * vec4(position, 1.0, 1.0);
    color0 = color;
}