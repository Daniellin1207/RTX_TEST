

#version 330 core

out vec4 FragColor;
in vec2 tex;
in vec3 FragPos;

uniform sampler2D colorTexture;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

void main(){
    vec3 hdrColor=lightColor*texture(colorTexture,tex).rgb;
    vec3 mapped=hdrColor/(hdrColor+vec3(1.0));
    FragColor=vec4(mapped,1.0);
    
    FragColor=vec4(texture(colorTexture,tex).rgb,1.0);
    //    vec3 normal=texture(normTexture,tex).rgb;
    //    normal=normalize(normal*2-1.0);
    //
    //    float t=max(dot(normalize(reflect(-(lightPos-FragPos),normal)),normalize(viewPos-FragPos)),0.0);
    //    vec3 color=texture(colorTexture,tex).rgb*(t+0.2);
    
//    FragColor=vec4(texture(heightTexture,tex).rrr,1.0f);
//    FragColor=vec4(1.0f);
}
