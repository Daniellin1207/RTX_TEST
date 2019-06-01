

#version 330 core
layout (triangles) in;
layout (line_strip,max_vertices=6) out;

//in vec3 normal;
//in vec3 pos;
in VS_OUT{
    vec3 normal;
}gs_in[];
//out vec3 normal;

uniform float time;


vec3 GetNormal()
{
    vec3 a=vec3(gl_in[0].gl_Position)-vec3(gl_in[1].gl_Position);
    vec3 b=vec3(gl_in[2].gl_Position)-vec3(gl_in[1].gl_Position);
    return normalize(cross(a,b));
}

vec4 explode(vec4 position,vec3 normal)
{
    float magnitude=2.0;
    vec3 direction=normal*((sin(time)+1.02f)/2.0)*magnitude;
    return position+vec4(direction,0.0);
}

//void build_house(vec4 position){
//    fColor=vColor[0];
//    gl_Position=position+vec4(-0.2,-0.2,0,0);
//    EmitVertex();
//    gl_Position=position+vec4(0.2,-0.2,0,0);
//    EmitVertex();
//    gl_Position=position+vec4(-0.2,0.2,0,0);
//    EmitVertex();
//    gl_Position=position+vec4(0.2,0.2,0,0);
//    EmitVertex();
//    gl_Position=position+vec4(0,0.4,0,0);
//    fColor=vec3(1,1,1);
//    EmitVertex();
//    
//    EndPrimitive();
//}
void move(int index,vec3 norm)
{
    gl_Position=gl_in[index].gl_Position;
    EmitVertex();
    gl_Position=gl_in[index].gl_Position+vec4(gs_in[index].normal,0.0f)*0.1;
    EmitVertex();
    EndPrimitive();
}
void main(){
    vec3 normal=GetNormal();
    move(0,normal);
    move(1,normal);
    move(2,normal);
}
