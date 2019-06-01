

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

out vec2 tex;
out vec3 normal;
out vec3 FragPos;
out vec4 lightPointPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 pers;
uniform mat4 lightMat;

void main()
{
    FragPos=vec3(model * vec4(aPos, 1.0));
    gl_Position =pers * view * vec4(FragPos,1.0);
    lightPointPos=lightMat*model*vec4(aPos,1.0);
    //   color = aColor;
    normal=aNormal;
    tex=aTex;
    
}
