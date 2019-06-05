
#version 330 core

layout(location = 0) out vec4 gPositionDepth;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gAlbedoSpec;
//out vec4 FragColor;
in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D diffTex;
uniform sampler2D specTex;

const float NEAR=0.1;
const float FAR=50.0f;
float LinearizeDepth(float depth)
{
    float z=depth*2.0-1.0;
    return (2.0* NEAR* FAR)/(FAR+NEAR-z*(FAR-NEAR));
}
void main(){
    gPositionDepth.rgb=FragPos;
    gPositionDepth.a=LinearizeDepth(gl_FragCoord.z);
    gNormal=normalize(Normal);
//    vec4 gAlbedoSpec;
    gAlbedoSpec.rgb=vec3(0.95);
//    gAlbedoSpec.rgb=texture(diffTex,TexCoords).rgb;
//    gAlbedoSpec.a=texture(specTex,TexCoords).r;
//    FragColor=vec4(gAlbedoSpec.,1.0f);
}
