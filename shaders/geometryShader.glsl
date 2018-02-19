#version 330
layout (points) in;
layout (points , max_vertices = 1) out;

in vec4 color0[];
out vec4 color1;

uniform mat4 transform;

void main()
{
    for (int i = 0; i < gl_in.length(); i++)
	{
		gl_Position =  transform * gl_in[i].gl_Position;
		color1 = color0[i];
		EmitVertex();
	}
    //color1 = color0;
}