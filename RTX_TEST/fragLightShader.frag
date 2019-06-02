
#version 330 core
in vec4 FragPos;
out vec4 FragColor;
uniform float far;
uniform vec3 lightPos;

void main()
{
    float dis=length(FragPos.xyz-lightPos);
    dis=dis/far;
    gl_FragDepth=dis;
//    FragColor=vec4(vec3(gl_FragCoord.z),1);
}
