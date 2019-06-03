
#version 330 core

out vec4 FragColor;
in vec2 tex;
in vec3 FragPos;

uniform sampler2D colorTexture;
uniform sampler2D normTexture;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main(){
    
    vec3 normal=texture(normTexture,tex).rgb;
    normal=normalize(normal*2-1.0);
    
    float t=max(dot(normalize(reflect(-(lightPos-FragPos),normal)),normalize(viewPos-FragPos)),0.0);
    vec3 color=texture(colorTexture,tex).rgb*(t+0.2);
    
    FragColor=vec4(color,1.0f);
}
