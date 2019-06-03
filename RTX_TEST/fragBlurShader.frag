


#version 330 core
out vec4 FragColor;
in vec2 tex;

uniform sampler2D frame;
//uniform float exposure;

void main(){
    vec2 tex_offset=1.0f/textureSize(frame,0);
    float weight[5]=float[](0.2270270270,0.1945945946,0.1216216216,0.0540540541,0.0162162162);
    vec3 result=texture(frame,tex).rgb*weight[0];
    for (int i=1; i<5; i++) {
        result+=texture(frame,tex+vec2(tex_offset.x*i,0.0)).rgb*weight[i];
        result+=texture(frame,tex-vec2(tex_offset.x*i,0.0)).rgb*weight[i];
    }
    for (int i=1; i<5; i++) {
        result+=texture(frame,tex+vec2(tex_offset.y*i,0.0)).rgb*weight[i];
        result+=texture(frame,tex-vec2(tex_offset.y*i,0.0)).rgb*weight[i];
    }
//    result=texture(frame,tex).rgb;
    
    
//    for (int i=1; i<5; i++) {
//        result+=texture(frame,tex+vec2(tex_offset.y*i,0.0)).rgb*weight[i];
//        result+=texture(frame,tex-vec2(tex_offset.y*i,0.0)).rgb*weight[i];
//    }
//    result/=2;
    //    vec3 color=texture(frame,tex).rgb;
    //    FragColor=vec4(color/(color+1),1.0);
    
//    const float gamma=2.2;
//    vec3 hdrColor=texture(frame,tex).rgb;
//    vec3 mapped=vec3(1.0)-exp(-hdrColor*0.2);
//    mapped=pow(mapped,vec3(1.0/gamma));
    FragColor=vec4(result.rgb/vec3(1.9),1.0);
}
