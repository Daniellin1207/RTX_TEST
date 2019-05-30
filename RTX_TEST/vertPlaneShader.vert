


#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTex;

//out vec3 color;
out vec2 tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 pers;

void main()
{
    gl_Position =vec4(aPos, 1.0);
    //   color = aColor;
    tex=aTex;
    
}
