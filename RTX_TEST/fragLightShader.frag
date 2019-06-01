
#version 330 core
out vec4 FragColor;
//in vec3 color;
in vec3 normal;
in vec2 tex;
in vec3 FragPos;

//uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;
//uniform float ratio;
//uniform vec3 lightColor;
uniform sampler2D wall;
uniform vec3 viewPos;
uniform bool blinn;
struct Light{
    vec3 pos;
    vec3 color;
};
uniform Light light;
void main()
{
//    vec3 tColor=mix(texture(ourTexture1,tex).rgb ,texture(ourTexture2,vec2(1-tex.x,tex.y)).rgb,ratio);
//    FragColor = vec4(tColor, 1.0f);
    
    vec3 lightDir=normalize(light.pos-FragPos);
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 halfwayDir=normalize(lightDir+viewDir);
    
    float t=0.0;
    float spec=0.0f;
    if(blinn){
        t=dot(normal,halfwayDir);
        spec=pow(max(t,0.0),32);
    }else{
        t=dot(reflect(-lightDir,normal),viewDir);
        spec=pow(max(t,0.0),8);
    }
    
    vec3 specular=light.color*spec;
    FragColor=vec4(texture(wall,tex).rgb*0.2+specular*0.8,1.0f);
}
