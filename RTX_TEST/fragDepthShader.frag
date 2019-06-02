

#version 330 core
out vec4 FragColor;

in VS_OUT{
    vec3 Normal;
    vec3 FragPos;
    vec2 TexCoords;
}fs_in;

uniform float far;
uniform sampler2D wall;
uniform samplerCube depthMap;

uniform vec3 viewPos;
uniform bool blinn;
struct Light{
    vec3 pos;
    vec3 color;
};
uniform Light light;
void main()
{
    vec3 fragToLight=-light.pos+fs_in.FragPos;
    float closestDepth=texture(depthMap,fragToLight).r;
    closestDepth*=far;
    
    float currentDepth=length(fragToLight);
    float shadow=currentDepth>closestDepth?1.0:0.0;
    
    
//    FragColor=vec4(texture(wall,fs_in.TexCoords).rgb*light.color*(1-shadow),1.0f);
//    FragColor=vec4(texture(depthMap,fragToLight).rrr,1.0);
    FragColor=vec4(texture(wall,fs_in.TexCoords).rgb*(1-shadow),1.0f);
//    FragColor=vec4(texture(wall,fs_in.TexCoords).rgb*shadow,1.0f);
}
