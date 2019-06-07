//
//  Shader.cpp
//  RTX_TEST
//
//  Created by Daniel.Lin on 2019/5/26.
//  Copyright © 2019 Daniel.Lin. All rights reserved.
//

#include "Shader.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;

Shader::Shader(const char* vertPath, const char* fragPath){
    std::string vertString;
    std::string fragString;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    path=(fragPath);
    // 保证ifstream对象可以抛出异常：
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // 打开文件
        vShaderFile.open(vertPath);
        fShaderFile.open(fragPath);
        std::stringstream vShaderStream, fShaderStream;
        // 读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件处理器
        vShaderFile.close();
        fShaderFile.close();
        // 转换数据流到string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    createShader(vShaderCode,fShaderCode);
}

Shader::Shader(const char* vertPath,const char* geoPath, const char* fragPath){
    std::string vertString;
    std::string geoString;
    std::string fragString;
    std::ifstream vShaderFile;
    std::ifstream gShaderFile;
    std::ifstream fShaderFile;
    path=(fragPath);
    // 保证ifstream对象可以抛出异常：
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // 打开文件
        vShaderFile.open(vertPath);
        gShaderFile.open(geoPath);
        fShaderFile.open(fragPath);
        std::stringstream vShaderStream,gShaderStream, fShaderStream;
        // 读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        gShaderStream << gShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件处理器
        vShaderFile.close();
        gShaderFile.close();
        fShaderFile.close();
        // 转换数据流到string
        vertexCode   = vShaderStream.str();
        geometryCode = gShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* gShaderCode = geometryCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    createShader(vShaderCode,gShaderCode,fShaderCode);
}

void Shader::createShader(const char* vertCode,const char* fragCode){
    unsigned int vertex,fragment;
    int success;
    char infoLog[512];
    
    vertex=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vertCode,NULL);
    glCompileShader(vertex);
    
    glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertex,1024,NULL,infoLog);
        cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
        cout<<path<<endl;
    }
    
    fragment=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fragCode,NULL);
    glCompileShader(fragment);
    
    glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragment,1024,NULL,infoLog);
        cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
        cout<<path<<endl;
    }
    
    ID=glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(ID,1024,NULL,infoLog);
        cout<<"ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n"<<infoLog<<endl;
    }
    // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::createShader(const char* vertCode,const char* geoCode,const char* fragCode){
    unsigned int vertex,geometry,fragment;
    int success;
    char infoLog[512];
    
    vertex=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vertCode,NULL);
    glCompileShader(vertex);
    
    glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertex,1024,NULL,infoLog);
        cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
        cout<<path<<endl;
    }
    
    geometry=glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry,1,&geoCode,NULL);
    glCompileShader(geometry);
    
    glGetShaderiv(geometry,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(geometry,1024,NULL,infoLog);
        cout<<"ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << endl;
        cout<<path<<endl;
    }
    
    fragment=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fragCode,NULL);
    glCompileShader(fragment);
    
    glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragment,1024,NULL,infoLog);
        cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
        cout<<path<<endl;
    } 
    
    ID=glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,geometry);
    glAttachShader(ID,fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(ID,1024,NULL,infoLog);
        cout<<"ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n"<<infoLog<<endl;
    }
    // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
    glDeleteShader(vertex);
    glDeleteShader(geometry);
    glDeleteShader(fragment);
}

void Shader::use(){
    glUseProgram(ID);
}
