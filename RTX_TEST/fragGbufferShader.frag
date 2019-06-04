
#version 330 core

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gAlbedoSpec;
//out vec4 FragColor;
in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D diffTex;
uniform sampler2D specTex;

void main(){
    gPosition=FragPos;
    gNormal=normalize(Normal);
//    vec4 gAlbedoSpec;
    gAlbedoSpec.rgb=texture(diffTex,TexCoords).rgb;
    gAlbedoSpec.a=texture(specTex,TexCoords).r;
//    FragColor=vec4(gAlbedoSpec.,1.0f);
}
