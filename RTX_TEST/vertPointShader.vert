




#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 pers;

void main()
{
    vec4 pos=pers * view * model * vec4(aPos, 1.0);
    gl_Position =pos.xyzw;
    //   color = aColor;
    gl_PointSize=gl_Position.z;
    
}
