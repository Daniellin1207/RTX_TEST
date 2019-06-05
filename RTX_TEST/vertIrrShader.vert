#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTex;

out vec3 WorldPos;

//uniform mat4 model;
uniform mat4 view;
uniform mat4 pers;

void main(){
    WorldPos=aPos;
    gl_Position=pers * view * vec4(aPos,1.0f);
}
