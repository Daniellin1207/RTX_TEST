
#version 330 core

layout(location = 0) in vec3 aPos;

layout(location = 1) in vec3 aNormal;

layout(location = 2) in vec2 aTex;

out vec3 Pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 pers;

void main(){
    Pos=vec3(model*vec4(aPos,1.0));
    vec4 p=pers * view * model * vec4(aPos,1.0f);
    gl_Position=p.xyww;
}
