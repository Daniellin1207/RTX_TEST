
#version 330 core
out vec4 FragColor;
in vec3 Pos;
uniform samplerCube skybox;

void main(){
    vec3 color=texture(skybox,Pos).rgb;
    FragColor=vec4(color,1.0f);
}
