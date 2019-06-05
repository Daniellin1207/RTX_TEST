#version 330 core
layout(location = 0)in vec3 aPos;
layout(location = 1)in vec3 aNormal;
layout(location = 2)in vec2 aTex;
//layout(location = 3)in mat4 matModel;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 matModel;
uniform mat4 view;
uniform mat4 pers;

void main(){
    TexCoords=aTex;
//    WorldPos=vec3(model*vec4(aPos,1.0));
    WorldPos=vec3(matModel*vec4(aPos,1.0));
    Normal=aNormal;
    gl_Position=pers * view * model * vec4(aPos,1.0f);
}
