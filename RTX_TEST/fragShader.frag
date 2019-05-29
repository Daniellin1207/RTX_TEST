#version 330 core
out vec4 FragColor;
in vec3 normal;
in vec3 pos;
//in vec3 color;
//in vec2 tex;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 viewPos;
//uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;
//uniform float ratio;
void main()
{
    float ambientStrength=0.1;
    vec3 ambient=ambientStrength*lightColor;
//
    vec3 norm=normalize(normal);
    
    vec3 lightDir=normalize(lightPos-pos);
    float r=max(dot(lightDir,normal),0.0);
    vec3 diffuse=r*lightColor*objectColor;
    
    
    vec3 viewDir=normalize(viewPos-pos);
    vec3 n=normalize(viewDir+lightDir);
    float t=max(dot(n,norm),0.0);
//    float t=pow(max(dot(reflect(-lightDir,norm),viewDir),0.0),32); // reflect(I,N)=>> I-2cos(I,N)*N ==>>so need "-"
    vec3 specular=t*lightColor*objectColor;
    
    
    
    vec3 result=specular;
//    vec3 result=result+ambient;
    FragColor=vec4(result,1.0f);
    
//    float ambientStrength=0.6;
//    vec3 ambient=ambientStrength*lightColor;
//    vec3 result=ambient*objectColor;
//    FragColor=vec4(result,1.0);
    
//    vec3 tColor=mix(texture(ourTexture1,tex).rgb ,texture(ourTexture2,vec2(1-tex.x,tex.y)).rgb,ratio);
//    FragColor = vec4(tColor, 1.0f);
}
