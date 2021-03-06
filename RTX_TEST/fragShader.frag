#version 330 core
out vec4 FragColor;
//in vec3 color;
//in vec3 normal;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 viewPos;

struct Material{
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light{
    vec3 position;
    vec3 direction;
    
    float cutoff;
    float cutout;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

uniform samplerCube skybox;
uniform sampler2D grass;
uniform Material material;
uniform Light light[1];
//uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;
//uniform float ratio;

//float near=0.1;
//float far=100.0f;
//float LinearizeDepth(float depth)
//{
//    float z=depth*2.0-1.0;
//    return(2.0*near*far)/(far+near-z*(far-near));
//}


void main()
{
//    vec4 color=vec4(0);
//    for(int i=0;i<1;i++){
//        vec3 ambient=material.ambient*light[i].ambient;
//
//        float distance=length(light[i].position-pos);
//        float attenuation=1.0/(light[i].constant+light[i].linear*distance+light[i].quadratic*distance*distance);
//
//        vec3 norm=normalize(normal);
//
//        vec3 lightDir=normalize(light[i].position-pos);
//        float theta=dot(lightDir,normalize(-light[i].direction));
//
//        float r=max(dot(lightDir,normal),0.0);
//        vec3 diffuse=r*light[i].diffuse*texture(material.diffuse,tex).rgb;
//
//
//        vec3 viewDir=normalize(viewPos-pos);
//        //    vec3 n=normalize(viewDir+lightDir);
//        //    float t=max(dot(n,norm),0.0);
//        float t=pow(max(dot(reflect(-lightDir,norm),viewDir),0.0),material.shininess); // reflect(I,N)=>> I-2cos(I,N)*N ==>>so need "-"
//        vec3 specular=t*light[i].specular*texture(material.specular,tex).rgb;
//
//        vec3 result=specular+diffuse;
//        //    vec3 result=result+ambient;
//        float ratio=0.0f;
//        if(theta>light[i].cutoff){
//            ratio=1.0f;
//        }else if(theta>light[i].cutout){
//            ratio=(theta-light[i].cutout)/(light[i].cutoff-light[i].cutout);
//        }
//        ratio=1.0f;
//
//        color+=vec4(result*attenuation*ratio,1.0f);
//
//    }
    
    
//    float ratio=1.00/1.52;
//    vec3 I=normalize(viewPos-pos);
//    vec3 R=refract(I,normalize(normal),ratio);
//    vec3 color=texture(skybox,R).rgb;
    
    
    
//    float depth=LinearizeDepth(gl_FragCoord.z)/far;

    FragColor=vec4(1,1,0,1.0f);
    

    
//    float ambientStrength=0.6;
//    vec3 ambient=ambientStrength*lightColor;
//    vec3 result=ambient*objectColor;
//    FragColor=vec4(result,1.0);
    
//    vec3 tColor=mix(texture(ourTexture1,tex).rgb ,texture(ourTexture2,vec2(1-tex.x,tex.y)).rgb,ratio);
//    FragColor = vec4(tColor, 1.0f);
}

