
#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aNormal;
//layout (location = 1) in vec3 aColor;
//layout (location = 2) in vec2 aTex;
//layout (location = 3) in mat4 m;

//out vec3 color;
//out vec2 tex;
//out vec3 FragPos;
//out vec3 normal;

uniform mat4 model;
uniform mat4 lightMat;

void main()
{
//    FragPos=vec3(model * vec4(aPos, 1.0));
    gl_Position =lightMat * model * vec4(aPos,1.0);
    //   color = aColor;
//    normal=aNormal;
//    tex=aTex;
    
}
