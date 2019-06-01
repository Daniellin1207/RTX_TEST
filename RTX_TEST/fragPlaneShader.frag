

#version 330 core
out vec4 FragColor;
in vec3 fColor;

void main(){
    FragColor=vec4(fColor,1.0);
}


//#version 330 core
//out vec4 FragColor;
////in vec3 color;
//in vec2 tex;
//
//uniform sampler2D grass;
////uniform sampler2D ourTexture2;
////uniform float ratio;
//uniform vec3 lightColor;
//float offset=1.0/300.0;
//void main()
//{
//    //    vec3 tColor=mix(texture(ourTexture1,tex).rgb ,texture(ourTexture2,vec2(1-tex.x,tex.y)).rgb,ratio);
//    //    FragColor = vec4(tColor, 1.0f);
////    vec4 texColor=texture(grass,tex);
////    if(texColor.a<0.1)
////        discard;
////    FragColor=texColor;
//    vec2 offsets[9]=vec2[](
//        vec2(-offset,offset),
//        vec2(0,offset),
//        vec2(offset,offset),
//
//        vec2(-offset,0),
//        vec2(0,0),
//        vec2(offset,0),
//
//        vec2(-offset,-offset),
//        vec2(0,-offset),
//        vec2(offset,-offset)
//    );
//
//    float kernel[9]=float[](
//        -1,-1,-1,
//        -1,9,-1,
//        -1,-1,-1
//    );
//
//    vec3 col=vec3(0);
//    for (int i=0; i<9; i++) {
//        col+=vec3(texture(grass,tex.st+offsets[i]))*kernel[i];
//    }
//    FragColor=vec4(texture(grass,1-tex).rgb,1.0f);
//}
