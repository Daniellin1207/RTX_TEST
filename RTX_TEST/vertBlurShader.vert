
#version 330 core
layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec3 aColor;
layout(location = 1) in vec2 aTex;

out vec2 tex;

//uniform vec2 offsets[100];

void main()
{
    gl_Position = vec4(aPos,1);
    tex=aTex;
}
