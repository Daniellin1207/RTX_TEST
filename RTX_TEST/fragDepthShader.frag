

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
//    float shadow=currentDepth>closestDepth?1.0:0.0;
    
    float shadow = 0.0;
    float bias = 0.05;
    float samples = 4.0;
    float offset = 0.1;
    for(float x = -offset; x < offset; x += offset / (samples * 0.5))
    {
        for(float y = -offset; y < offset; y += offset / (samples * 0.5))
        {
            for(float z = -offset; z < offset; z += offset / (samples * 0.5))
            {
                float closestDepth = texture(depthMap, fragToLight + vec3(x, y, z)).r;
                closestDepth *= far;   // Undo mapping [0;1]
                if(currentDepth - bias > closestDepth)
                    shadow += 1.0;
            }
        }
    }
    shadow /= (samples * samples * samples);
    
//    FragColor=vec4(texture(wall,fs_in.TexCoords).rgb*light.color*(1-shadow),1.0f);
//    FragColor=vec4(texture(depthMap,fragToLight).rrr,1.0);
    FragColor=vec4(texture(wall,fs_in.TexCoords).rgb*(1-shadow),1.0f);
//    FragColor=vec4(texture(wall,fs_in.TexCoords).rgb*shadow,1.0f);
}
