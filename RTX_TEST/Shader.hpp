//
//  Shader.hpp
//  RTX_TEST
//
//  Created by Daniel.Lin on 2019/5/26.
//  Copyright © 2019 Daniel.Lin. All rights reserved.
//

#ifndef SHADER_H
#define SHADER_H

#include "Shader.hpp"
#include <GL/glew.h>
#include <string>
class Shader{
public:
    Shader(const char* vertPath, const char* fragPath);
    Shader(const char* vertPath,const char* geoPath, const char* fragPath);
    void use();
    unsigned int ID;
private:
    std::string vertexCode;
    std::string geometryCode;
    std::string fragmentCode;
    std::string path;
    void createShader(const char* vertCode,const char* fragCode);
    
    void createShader(const char* vertCode,const char* geoCode,const char* fragCode);
};

#endif

