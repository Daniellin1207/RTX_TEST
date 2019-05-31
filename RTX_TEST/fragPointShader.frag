


#version 330 core
out vec4 FragColor;
in vec2 tex;
//in vec3 color;
//in vec3 tex;
uniform sampler2D front;
uniform sampler2D back;
//uniform samplerCube skybox;
void main()
{
    //    vec3 tColor=mix(texture(ourTexture1,tex).rgb ,texture(ourTexture2,vec2(1-tex.x,tex.y)).rgb,ratio);
    //    FragColor = vec4(tColor, 1.0f);
//    FragColor=texture(skybox,tex);
//    FragColor=vec4(1);
    if(gl_FrontFacing)
        FragColor=texture(front,tex);
    else
        FragColor=texture(back,tex);
    
    if(gl_FragCoord.x<400)
        FragColor*=vec4(1.0,0,0,1.0f);
    else
        FragColor*=vec4(0,1,0,1);
}
