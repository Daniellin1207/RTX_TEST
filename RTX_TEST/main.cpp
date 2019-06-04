
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <cmath>
#include <string>
#include "Shader.hpp"
#include "Camera.hpp"
#include "Light.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc // test commit // test commit 2
#include "tiny_obj_loader.h"


Camera camera(glm::vec3(5,0,0),glm::vec3(0,1,0),-10,0);
Light light(glm::vec3(5,3,2),glm::vec3(1,2,1),glm::vec3(200.0,200.0,100.0));
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window,double xpos,double ypos);
void scroll_callback(GLFWwindow *window,double xoffset,double yoffset);
unsigned int generateTex(std::string path);
unsigned int generateCubeTex(std::vector<std::string> faces);
unsigned int generateVAO(float* points,int size,const int x,const int y,const int z);
unsigned int generateVAO(float* points,int size,const int x,const int y);
unsigned int generateVAO(float* points,int size,const int x);
unsigned int generateVAO(std::vector<float>* points,int size,const int x,const int y,const int z);
unsigned int genFboTex(int k);
struct FRAME{
    unsigned int fbo;
    std::vector<unsigned int> textures;
};
FRAME generateFBO(int texNum);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float ratio=0.0f;
float zoom=0.01f;
float radius=8.0f;

float lastX = SCR_WIDTH/2.0f;
float lastY = SCR_HEIGHT/2.0f;
bool firstMouse=true;

float deltaTime=0.0f;
float lastFrame=0.0f;
int blinn=0;
float exposure=1.0f;

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex;
};

int main()
{
    // glfw: initialize and configure
    // -----------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if(glewInit()!=GLEW_OK){
        std::cout<<"Init Failed!"<<std::endl;
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_MULTISAMPLE);
    
//    Shader ourShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/geoShader.frag","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragShader.frag");
//    Shader lightShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertLightShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/geoLightShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragLightShader.frag");
//    Shader singleShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertSingleColorShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragSingleColorShader.frag");
    Shader planeShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertPlaneShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragPlaneShader.frag");
//    Shader skyboxShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertSkyboxShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragSkyboxShader.frag");
//    Shader pointShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertPointShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragPointShader.frag");
//    Shader geoShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertGeoShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/geoGeoShader.gs","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragGeoShader.frag");
//    Shader depthShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertDepthShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragDepthShader.frag");
//    Shader normShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertNormalShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragNormalShader.frag");
//    Shader hdrShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertHdrShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragHdrShader.frag");
//    Shader blurShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertBlurShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragBlurShader.frag");
    Shader easyShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertEasyShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragEasyShader.frag");
    Shader gBufferShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertGbufferShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragGbufferShader.frag");
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float lightVertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    
    float planeVertices[] = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
        -1.0f,  1.0,  0.0f,  0.0f,  0.0f,
        -1.0f, -1.0,  0.0f,  0.0f,  1.0f,
         1.0f, -1.0,  0.0f,  1.0f,  1.0f,
        
        -1.0f,  1.0,  0.0f,  0.0f,  0.0f,
         1.0f, -1.0,  0.0f,  1.0f,  1.0f,
         1.0f,  1.0,  0.0f,  1.0f,  0.0f
    };
    
    float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        
        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };
    
    float points[]={
        -0.5f,0.5f,1,0,0,
        0.5f,0.5f,0,1,0,
        0.5,-0.5,0,0,1,
        -0.5,-0.5,1,1,0
    };
    
    
    std::vector<Vertex> vertices;
    std::vector<unsigned int>indices;
    const std::string path = "/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Models/nanosuit/nanosuit.obj";
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn;
    std::string err;
    
    if(!tinyobj::LoadObj(&attrib,&shapes,&materials,&warn,&err,path.c_str()))
    {
        throw std::runtime_error(warn+err);
    }
    
    for(auto& shape:shapes)
    {
        for (auto& index: shape.mesh.indices)
        {
            Vertex vertex={};
            vertex.position={
                attrib.vertices[3*index.vertex_index+0],
                attrib.vertices[3*index.vertex_index+1],
                attrib.vertices[3*index.vertex_index+2],
            };
            vertex.normal={
                attrib.normals[3*index.normal_index+0],
                attrib.normals[3*index.normal_index+1],
                attrib.normals[3*index.normal_index+2],
            };
            vertex.tex={
                attrib.texcoords[2*index.texcoord_index+0],
                attrib.texcoords[2*index.texcoord_index+1],
            };
            vertices.push_back(vertex);
            indices.push_back(indices.size());
//            std::cout<<indices.size()<<std::endl;
        }
    }
    
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  10.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
//    unsigned int amount=1000;
//    glm::mat4 modelMatrices[amount];
//    srand(glfwGetTime());
//    float radius=50.0;
//    float offset=2.5f;
//    for (unsigned int i=0; i<amount; i++) {
//        glm::mat4 model=glm::mat4(1.0f);
//        float angle=(float)i/(float)amount*360.0f;
//        float displacement=(rand()%(int)(2*offset*100))/100.0f-offset;
//        float x=sin(angle)*radius+displacement;
//        displacement=(rand()%(int)(2*offset*100))/100.0f-offset;
//        float y=displacement*0.4f;
//        displacement=(rand()%(int)(2*offset*100))/100.0f-offset;
//        float z=cos(angle)*radius+displacement;
//        model=glm::translate(model, glm::vec3(x,y,z));
//
//        float scale=(rand()%20)/100.0f+0.05;
//        model=glm::scale(model,glm::vec3(scale));
//
//        float rotAngle=(rand()%360);
//        model=glm::rotate(model,rotAngle,glm::vec3(0.4,0.6,0.8));
//
//        modelMatrices[i]=model;
//    }
    
//    int indices[]={
//        0,1,2,
//        3,0,2
//    };
    
    
    
    unsigned int planeVAO;
    planeVAO=generateVAO(planeVertices, sizeof(planeVertices), 3, 2);
    unsigned int skyboxVAO;
    skyboxVAO=generateVAO(skyboxVertices, sizeof(skyboxVertices), 3);
//    unsigned int geoVAO;
//    geoVAO=generateVAO(points, 36, 2, 3);
    unsigned int lightVAO;
    lightVAO=generateVAO(lightVertices,sizeof(lightVertices),3,3,2);
//    unsigned int geoVAO,geoVBO;
//    glGenVertexArrays(1,&geoVAO);
//    glGenBuffers(1,&geoVBO);
//    glBindVertexArray(geoVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,geoVBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(lightVertices),lightVertices,GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
//    glEnableVertexAttribArray(2);
    
//    glGenVertexArrays(1,&lightVAO);
//    glBindVertexArray(lightVAO);
//    glGenBuffers(1,&lightVBO);
//    glBindBuffer(GL_ARRAY_BUFFER,lightVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
//    glEnableVertexAttribArray(2);
    
//    unsigned int buffer;
//    glGenBuffers(1,&buffer);
//    glBindBuffer(GL_ARRAY_BUFFER,buffer);
//    glBufferData(GL_ARRAY_BUFFER,amount*sizeof(glm::mat4),&modelMatrices[0],GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(3);
//    glVertexAttribPointer(3,4,GL_FLOAT,GL_FALSE,sizeof(glm::mat4),(void*)0);
//    glEnableVertexAttribArray(4);
//    glVertexAttribPointer(4,4,GL_FLOAT,GL_FALSE,sizeof(glm::mat4),(void*)(sizeof(glm::vec4)));
//    glEnableVertexAttribArray(5);
//    glVertexAttribPointer(5,4,GL_FLOAT,GL_FALSE,sizeof(glm::mat4),(void*)(2*sizeof(glm::vec4)));
//    glEnableVertexAttribArray(6);
//    glVertexAttribPointer(6,4,GL_FLOAT,GL_FALSE,sizeof(glm::mat4),(void*)(3*sizeof(glm::vec4)));
//
//    glVertexAttribDivisor(3,1);
//    glVertexAttribDivisor(4,1);
//    glVertexAttribDivisor(5,1);
//    glVertexAttribDivisor(6,1);

    unsigned int VAO,VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex)*vertices.size(),&vertices[0],GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    unsigned int EBO;
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    
//    glm::vec2 translations[100];
//    int index=0;
//    float offset=0.1f;
//    for (int y= -10; y<10; y+=2) {
//        for (int x=-10; x<10; x+=2) {
//            glm::vec2 translation;
//            translation.x=(float)x/10.0f+offset;
//            translation.y=(float)y/10.0f+offset;
//            translations[index++]=translation;
//        }
//    }
    
//    unsigned int instanceVBO;
//    glGenBuffers(1,&instanceVBO);
//    glBindBuffer(GL_ARRAY_BUFFER,instanceVBO);
//    glEnableVertexAttribArray(2);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec2)*100,&translations[0],GL_STATIC_DRAW);
//    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
//    glVertexAttribDivisor(2,1);

    
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    
    unsigned int texture[3];
    glGenTextures(3, texture);
    unsigned int textureID;
    glGenTextures(1,&textureID);
    
//    stbi_set_flip_vertically_on_load(true);
    texture[0]=generateTex("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/container.jpg");
    texture[1]=generateTex("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/parallax_mapping_height_map.png");
    texture[2]=generateTex("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/blending_transparent_window.png");
    
    std::vector<std::string > faces{
        "/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/skybox/left.jpg",
        "/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/skybox/right.jpg",
        "/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/skybox/top.jpg",
        "/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/skybox/bottom.jpg",
        "/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/skybox/back.jpg",
        "/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/skybox/front.jpg",
    };
    textureID=generateCubeTex(faces);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_CUBE_MAP,textureID);
    
// frame
    unsigned int hdrFBO;
    unsigned int hdrColorBufferTexture[2];
    FRAME frame=generateFBO(2);
    hdrFBO=frame.fbo;
    for (int i=0; i<2; i++) {
        hdrColorBufferTexture[i]=frame.textures[i];
    }

    
    unsigned int blurFBO[2];
    unsigned int blurTexture[2];
    for (int i=0; i<2; i++) {
        frame=generateFBO(1);
        blurFBO[i]=frame.fbo;
        blurTexture[i]=frame.textures[0];
    }
    
    
    
    
    unsigned int gBuffer;
    unsigned int gPosition,gNormal,gAlbedoSpec;
    glGenFramebuffers(1,&gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER,gBuffer);
    
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,gPosition,0);
    
    
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT1,GL_TEXTURE_2D,gNormal,0);
    
    
    glGenTextures(1, &gAlbedoSpec);
    glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT2,GL_TEXTURE_2D,gAlbedoSpec,0);
    
    GLuint attachments[3]={GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2};
    glDrawBuffers(3,attachments);
    
    unsigned int rboDepth;
    glGenRenderbuffers(1,&rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER,rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT,SCR_WIDTH,SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,rboDepth);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE){
        std::cout<<"Framebuffer not complete!"<<std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    
    
    
//    unsigned int uniformBlockIndexOur=glGetUniformBlockIndex(ourShader.ID,"Matrices");
//    unsigned int uniformBlockIndexSkybox=glGetUniformBlockIndex(skyboxShader.ID,"Matrices");
//    unsigned int uniformBlockIndexPoint=glGetUniformBlockIndex(pointShader.ID,"Matrices");
//    glUniformBlockBinding(ourShader.ID,uniformBlockIndexOur,0);
//    glUniformBlockBinding(skyboxShader.ID,uniformBlockIndexSkybox,0);
//    glUniformBlockBinding(pointShader.ID,uniformBlockIndexPoint,0);
//    
//    unsigned int uboMatrices;
//    glGenBuffers(1,&uboMatrices);
//    glBindBuffer(GL_UNIFORM_BUFFER,uboMatrices);
//    glBufferData(GL_UNIFORM_BUFFER,2*sizeof(glm::mat4),NULL,GL_STATIC_DRAW);
//    glBindBufferRange(GL_UNIFORM_BUFFER,0,uboMatrices,0,2*sizeof(glm::mat4));
//    pers=glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
//    glBufferSubData(GL_UNIFORM_BUFFER,sizeof(glm::mat4),sizeof(glm::mat4),glm::value_ptr(pers));
//    glBindBuffer(GL_UNIFORM_BUFFER,0);
    

    

    glm::mat4 model=glm::mat4(1.0f);
    glm::mat4 view=glm::mat4(1.0f);
    glm::mat4 pers=glm::mat4(1.0f);
    
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame=glfwGetTime();
        deltaTime=currentFrame-lastFrame;
        lastFrame=currentFrame;
        processInput(window);
        
        
        
        glBindFramebuffer(GL_FRAMEBUFFER,gBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 0.10f, 0.0f, 1.0f);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture[2]);
        
        model=glm::mat4(1.0);
        view=camera.GetViewMatrix();
        pers=glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        gBufferShader.use();
        glUniformMatrix4fv(glGetUniformLocation(gBufferShader.ID,"model"),1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(gBufferShader.ID,"view"),1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(gBufferShader.ID,"pers"),1,GL_FALSE,glm::value_ptr(pers));
        
        glUniform1i(glGetUniformLocation(gBufferShader.ID,"diffTex"),0);
        glUniform1i(glGetUniformLocation(gBufferShader.ID,"specTex"),1);
        
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        
        glBindFramebuffer(GL_READ_FRAMEBUFFER,gBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
        glBlitFramebuffer(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,SCR_WIDTH,SCR_HEIGHT,GL_DEPTH_BUFFER_BIT,GL_NEAREST);
        
        
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 0.10f, 0.0f, 1.0f);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
        
        planeShader.use();
        glUniform1i(glGetUniformLocation(planeShader.ID,"gPosition"),0);
        glUniform1i(glGetUniformLocation(planeShader.ID,"gNormal"),1);
        glUniform1i(glGetUniformLocation(planeShader.ID,"gAlbedoSpec"),2);
        glBindVertexArray(planeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        easyShader.use();
        model=glm::translate(model, glm::vec3(4,0,0));
        glUniformMatrix4fv(glGetUniformLocation(easyShader.ID,"model"),1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(easyShader.ID,"view"),1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(easyShader.ID,"pers"),1,GL_FALSE,glm::value_ptr(pers));
        
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        blinn=1-blinn;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        exposure+=0.003;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        exposure-=0.002;
}

void mouse_callback(GLFWwindow *window,double xpos,double ypos)
{
    if(firstMouse)
    {
        lastX=xpos;
        lastY=ypos;
        firstMouse=false;
    }
    float xoffset=xpos-lastX;
    float yoffset=lastY-ypos;
    
    lastX=xpos;
    lastY=ypos;
    
    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

unsigned int generateTex(std::string path){
    unsigned int textureID;
    glGenTextures(1,&textureID);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    
    if (data)
    {
        glBindTexture(GL_TEXTURE_2D, textureID);
        if(nrChannels==4){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else if(nrChannels==3){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return textureID;
}

unsigned int generateCubeTex(std::vector<std::string> faces){
    unsigned int textureID;
    int width, height, nrChannels;
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for (unsigned int i=0; i<faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        std::cout<<faces[i].c_str()<<std::endl;
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    return textureID;
}

unsigned int generateVAO(float* points,int size,const int x,const int y,const int z){
    unsigned int geoVBO,geoVAO;
    glGenVertexArrays(1,&geoVAO);
    glGenBuffers(1,&geoVBO);
    glBindVertexArray(geoVAO);
    glBindBuffer(GL_ARRAY_BUFFER,geoVBO);
    glBufferData(GL_ARRAY_BUFFER,size,points,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,x,GL_FLOAT,GL_FALSE,(x+y+z)*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,y,GL_FLOAT,GL_FALSE,(x+y+z)*sizeof(float),(void*)(x*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,z,GL_FLOAT,GL_FALSE,(x+y+z)*sizeof(float),(void*)((x+y)*sizeof(float)));
    glEnableVertexAttribArray(2);
    return geoVAO;
}
unsigned int generateVAO(float* points,int size,const int x,const int y){
    unsigned int geoVBO,geoVAO;
    glGenVertexArrays(1,&geoVAO);
    glGenBuffers(1,&geoVBO);
    glBindVertexArray(geoVAO);
    glBindBuffer(GL_ARRAY_BUFFER,geoVBO);
    glBufferData(GL_ARRAY_BUFFER,size,points,GL_STATIC_DRAW);

    glVertexAttribPointer(0,x,GL_FLOAT,GL_FALSE,(x+y)*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,y,GL_FLOAT,GL_FALSE,(x+y)*sizeof(float),(void*)(x*sizeof(float)));
    glEnableVertexAttribArray(1);
    return geoVAO;
}
unsigned int generateVAO(float* points,int size,const int x){
    unsigned int geoVBO,geoVAO;
    glGenVertexArrays(1,&geoVAO);
    glGenBuffers(1,&geoVBO);
    glBindVertexArray(geoVAO);
    glBindBuffer(GL_ARRAY_BUFFER,geoVBO);
    glBufferData(GL_ARRAY_BUFFER,size,points,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,x,GL_FLOAT,GL_FALSE,x*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    return geoVAO;
}
unsigned int generateVAO(std::vector<float>* points,int size,const int x,const int y,const int z){
    unsigned int geoVBO,geoVAO;
    glGenVertexArrays(1,&geoVAO);
    glGenBuffers(1,&geoVBO);
    glBindVertexArray(geoVAO);
    glBindBuffer(GL_ARRAY_BUFFER,geoVBO);
    glBufferData(GL_ARRAY_BUFFER,size,&points[0],GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,x,GL_FLOAT,GL_FALSE,(x+y+z)*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,y,GL_FLOAT,GL_FALSE,(x+y+z)*sizeof(float),(void*)(x*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,z,GL_FLOAT,GL_FALSE,(x+y+z)*sizeof(float),(void*)((x+y)*sizeof(float)));
    glEnableVertexAttribArray(2);
    return geoVAO;
}
FRAME generateFBO(int texNum){
    FRAME frame;
    unsigned int fbo;
    glGenFramebuffers(1,&fbo);
    glBindFramebuffer(GL_FRAMEBUFFER,fbo);

    unsigned int rboDepth;
    glGenRenderbuffers(1,&rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER,rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT,SCR_WIDTH,SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,rboDepth);
    
    unsigned int tex[texNum];
    unsigned int attachments[texNum];
    for (int i=0; i<texNum; i++) {
        tex[i]=genFboTex(i);
        attachments[i]=GL_COLOR_ATTACHMENT0+i;
        frame.textures.push_back(tex[i]);
    }
    glDrawBuffers(texNum,attachments);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE){
        std::cout<<"Framebuffer not complete!"<<std::endl;
    }
    frame.fbo=fbo;
    return frame;
}
unsigned int genFboTex(int k){
    unsigned int tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D,tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0+k, GL_TEXTURE_2D,tex,0);
    return tex;
}
