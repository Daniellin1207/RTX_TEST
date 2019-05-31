#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

out vec3 normal;
out vec3 pos;
out vec2 tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 pers;

void main()
{
    pos=vec3(model*vec4(aPos,1.0f));
    normal=mat3(transpose(inverse(model)))*aNormal;
    gl_Position =pers * view * model * vec4(aPos, 1.0);
//   color = aColor;
   tex=aTex;
    
}
