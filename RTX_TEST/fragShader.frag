#version 330 core
out vec4 FragColor;
in vec3 color;
in vec2 tex;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
void main()
{
    vec3 tColor=mix(texture(ourTexture1,tex).rgb ,texture(ourTexture2,vec2(1-tex.x,tex.y)).rgb,0.2);
    FragColor = vec4(tColor, 1.0f);
}
