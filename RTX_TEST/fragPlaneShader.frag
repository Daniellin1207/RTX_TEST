

#version 330 core
out vec4 FragColor;
in vec2 tex;

uniform sampler2D frame1;
uniform sampler2D frame2;
//uniform float exposure;

void main(){
    vec3 color1=texture(frame1,tex).rgb;
    vec3 color2=texture(frame2,vec2(tex.x,1-tex.y)).rgb;
//    FragColor=vec4(color/(color+1),1.0);
    
//    const float gamma=2.2;
    vec3 hdrColor=mix(color1,color2,0.3);
//    vec3 mapped=vec3(1.0)-exp(-hdrColor*exposure);
//    mapped=pow(mapped,vec3(1.0/gamma));
    FragColor=vec4(hdrColor.rgb,1.0);
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
