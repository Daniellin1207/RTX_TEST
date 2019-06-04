#version 330 core
out vec4 FragColor;
in vec2 tex;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

void main(){
    vec3 FragPos=texture(gPosition,tex).rgb;
    vec3 Normal=texture(gNormal,tex).rgb;
    vec3 Albedo=texture(gAlbedoSpec,tex).rgb;
    float Spec=texture(gAlbedoSpec,tex).a;
    
    FragColor=vec4(Albedo,1.0f);
    
}
