



#version 330 core
layout (location = 0) in vec3 aPos;

//out vec3 color;
out vec3 tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 pers;

void main()
{
    vec4 pos=pers * view * model * vec4(aPos, 1.0);
    gl_Position =pos.xyww;
    //   color = aColor;
    tex=aPos;
    
}
