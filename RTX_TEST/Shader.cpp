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

void Shader::createShader(const char* vertCode,const char* fragCode){
    unsigned int vertex,fragment;
    int success;
    char infoLog[512];
    
    vertex=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vertCode,NULL);
    glCompileShader(vertex);
    
    glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
    if(!success){
        cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }
    
    fragment=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fragCode,NULL);
    glCompileShader(fragment);
    
    glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
    if(!success){
        cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }
    
    ID=glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if(!success){
        cout<<"ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n"<<infoLog<<endl;
    }
    // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use(){
    glUseProgram(ID);
}
