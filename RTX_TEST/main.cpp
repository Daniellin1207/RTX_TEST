
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <cmath>
#include "Shader.hpp"
#include "Camera.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc // test commit // test commit 2
#include "tiny_obj_loader.h"


Camera camera(glm::vec3(0,0,0),glm::vec3(0,1,0),250,0);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window,double xpos,double ypos);
void scroll_callback(GLFWwindow *window,double xoffset,double yoffset);

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

std::vector<std::string > faces{
    "/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/skybox/left.jpg",
    "/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/skybox/right.jpg",
    "/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/skybox/top.jpg",
    "/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/skybox/bottom.jpg",
    "/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/skybox/back.jpg",
    "/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/skybox/front.jpg",
};

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
//    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if(glewInit()!=GLEW_OK){
        std::cout<<"Init Failed!"<<std::endl;
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
    glEnable(GL_PROGRAM_POINT_SIZE);
    Shader ourShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragShader.frag");
    Shader lightShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertLightShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragLightShader.frag");
    Shader singleShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertSingleColorShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragSingleColorShader.frag");
    Shader planeShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertPlaneShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragPlaneShader.frag");
    Shader skyboxShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertSkyboxShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragSkyboxShader.frag");
    Shader pointShader("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/vertPointShader.vert","/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/fragPointShader.frag");
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
        -1.0f, 1.0f,  0.0f,  0.0f,  0.0f,
        -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        1.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        
        -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        1.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  0.0f,  1.0f,  0.0f
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
    
    std::vector<Vertex> vertices;
    std::vector<unsigned int>indices;
    
    const std::string path = "/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Models/nanosuit/nanosuit.obj";
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn;
    std::string err;
    
    //    bool LoadObj(attrib_t *attrib, std::vector<shape_t> *shapes,
    //                 std::vector<material_t> *materials, std::string *warn,
    //                 std::string *err, const char *filename, const char *mtl_basedir,
    //                 bool trianglulate, bool default_vcols_fallback)
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
    
//    int indices[]={
//        0,1,2,
//        3,0,2
//    };
    
    glm::vec3 lightPos(0,0,5);
    glm::vec3 lightColor(1.0,1.0,1.0);
    glm::vec3 objectColor(1.0,0.0f,1.0f);
    unsigned int lightVAO,lightVBO;
    glGenVertexArrays(1,&lightVAO);
    glBindVertexArray(lightVAO);
    glGenBuffers(1,&lightVBO);
    glBindBuffer(GL_ARRAY_BUFFER,lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    unsigned int EBO;
    glGenBuffers(1,&EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    unsigned int planeVBO,planeVAO;
    glGenVertexArrays(1,&planeVAO);
    glGenBuffers(1,&planeVBO);
    
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER,planeVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(planeVertices),planeVertices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    unsigned int skyboxVBO,skyboxVAO;
    glGenVertexArrays(1,&skyboxVAO);
    glGenBuffers(1,&skyboxVBO);
    
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER,skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(skyboxVertices),skyboxVertices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    unsigned int pointVBO,pointVAO;
    glGenVertexArrays(1,&pointVAO);
    glGenBuffers(1,&pointVBO);
    
    glBindVertexArray(pointVAO);
    glBindBuffer(GL_ARRAY_BUFFER,pointVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(skyboxVertices),skyboxVertices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    unsigned int texture[3];
    glGenTextures(3, texture);
    
    unsigned int textureID;
    glGenTextures(1,&textureID);
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/matrix.jpg", &width, &height, &nrChannels, 0);
    
    if (data)
    {
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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
    
//    stbi_set_flip_vertically_on_load(true);
    unsigned char *data1 = stbi_load("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/container2_specular.png", &width, &height, &nrChannels, 0);
    if (data1)
    {
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data1);
    
//    stbi_set_flip_vertically_on_load(false);
    unsigned char *data2 = stbi_load("/Users/daniel/CodeManager/RTX_TEST/RTX_TEST/Textures/blending_transparent_window.png", &width, &height, &nrChannels, 0);
    if (data2)
    {
        glBindTexture(GL_TEXTURE_2D, texture[2]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data2);
    
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
    
    
    glm::mat4 model=glm::mat4(1.0f);
    glm::mat4 view=glm::mat4(1.0f);
    glm::mat4 pers=glm::mat4(1.0f);
    
    glm::vec3 cameraDir=glm::vec3(0,0,-1);
    glm::vec3 cameraUp=glm::vec3(0,1,0);
    
    unsigned int framebuffer;
    glGenFramebuffers(1,&framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
    
    unsigned int textureColorBuffer;
    glGenTextures(1, &textureColorBuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,textureColorBuffer,0);
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame=glfwGetTime();
        deltaTime=currentFrame-lastFrame;
        lastFrame=currentFrame;
        // input
        // -----
        processInput(window);
        
        
//        glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
//        glEnable(GL_DEPTH_TEST);
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        view=camera.GetViewMatrix();
        pers=glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        model=glm::mat4(1.0f);

//        glDepthFunc(GL_LEQUAL);
//        skyboxShader.use();
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_CUBE_MAP,textureID);
//        model=glm::mat4(1.0f);
//        view=glm::mat4(glm::mat3(camera.GetViewMatrix()));
//        //        model=glm::translate(model, lightPos);
//        //        model=glm::scale(model, glm::vec3(3.0f));
//        //        view=glm::mat4(glm::mat3(camera.GetViewMatrix()));
//        glUniform1i(glGetUniformLocation(skyboxShader.ID,"skybox"),1);
//        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID,"model"),1,GL_FALSE,glm::value_ptr(model));
//        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID,"view"),1,GL_FALSE,glm::value_ptr(view));
//        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID,"pers"),1,GL_FALSE,glm::value_ptr(pers));
//        glBindVertexArray(skyboxVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glDepthFunc(GL_LESS);
//
//        ourShader.use();
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture[0]);
//        model=glm::mat4(1.0f);
//        model=glm::translate(model, lightPos);
//        model=glm::scale(model, glm::vec3(0.2f));
//        view=camera.GetViewMatrix();
//        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID,"model"),1,GL_FALSE,glm::value_ptr(model));
//        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID,"view"),1,GL_FALSE,glm::value_ptr(view));
//        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID,"pers"),1,GL_FALSE,glm::value_ptr(pers));
//
//        glUniform1i(glGetUniformLocation(ourShader.ID,"skybox"),0);
//        glUniform3f(glGetUniformLocation(ourShader.ID,"lightColor"),lightColor.x,lightColor.y,lightColor.z);
//        glUniform3f(glGetUniformLocation(ourShader.ID,"viewPos"),camera.Position.x,camera.Position.y,camera.Position.z);
//
//        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES,0, vertices.size());

        pointShader.use();
        glUniformMatrix4fv(glGetUniformLocation(pointShader.ID,"model"),1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(pointShader.ID,"view"),1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(pointShader.ID,"pers"),1,GL_FALSE,glm::value_ptr(pers));
        
        glBindVertexArray(pointVAO);
        glDrawArrays(GL_POINTS, 0, 36);
        

        
//        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//        glStencilMask(0x00);
//        glDisable(GL_DEPTH_TEST);
//        singleShader.use();
//        model=glm::scale(model, glm::vec3(1.2f));
//        glUniformMatrix4fv(glGetUniformLocation(singleShader.ID,"model"),1,GL_FALSE,glm::value_ptr(model));
//        glUniformMatrix4fv(glGetUniformLocation(singleShader.ID,"view"),1,GL_FALSE,glm::value_ptr(view));
//        glUniformMatrix4fv(glGetUniformLocation(singleShader.ID,"pers"),1,GL_FALSE,glm::value_ptr(pers));
//
//        glUniform3f(glGetUniformLocation(singleShader.ID,"lightColor"),lightColor.x,lightColor.y,lightColor.z);
//        glBindVertexArray(lightVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//        glStencilMask(0xFF);
//        glEnable(GL_DEPTH_TEST);
        
//        glBindFramebuffer(GL_FRAMEBUFFER,0);
//        glDisable(GL_DEPTH_TEST);
//
//        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
//        planeShader.use();
//        glUniform1i(glGetUniformLocation(planeShader.ID,"grass"),0);
//
//        glBindVertexArray(planeVAO);
//        glDrawArrays(GL_TRIANGLES,0, 6);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
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
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
