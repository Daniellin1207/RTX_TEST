

#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;
in vec2 tex;
in vec3 FragPos;

uniform sampler2D colorTexture;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

uniform float exposure;

void main(){
    const float gamma=2.2;
    vec3 hdrColor=lightColor*texture(colorTexture,tex).rgb;
    FragColor=vec4(hdrColor,1.0);
    if(dot(FragColor.rgb,vec3(0.2,0.7,0.1))>1.0){
        BrightColor=vec4(FragColor.rgb,1.0f);
    }else{
        BrightColor=vec4(0,0,0,1);
    }
    
//    FragColor=vec4(texture(colorTexture,tex).rgb,1.0);
    //    vec3 normal=texture(normTexture,tex).rgb;
    //    normal=normalize(normal*2-1.0);
    //
    //    float t=max(dot(normalize(reflect(-(lightPos-FragPos),normal)),normalize(viewPos-FragPos)),0.0);
    //    vec3 color=texture(colorTexture,tex).rgb*(t+0.2);
    
//    FragColor=vec4(texture(heightTexture,tex).rrr,1.0f);
//    FragColor=vec4(1.0f);
}
