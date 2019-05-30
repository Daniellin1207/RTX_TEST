


#version 330 core
out vec4 FragColor;
//in vec3 color;
in vec2 tex;

uniform sampler2D grass;
//uniform sampler2D ourTexture2;
//uniform float ratio;
uniform vec3 lightColor;
void main()
{
    //    vec3 tColor=mix(texture(ourTexture1,tex).rgb ,texture(ourTexture2,vec2(1-tex.x,tex.y)).rgb,ratio);
    //    FragColor = vec4(tColor, 1.0f);
    vec4 texColor=texture(grass,tex);
    if(texColor.a<0.1)
        discard;
    FragColor=texColor;
}
