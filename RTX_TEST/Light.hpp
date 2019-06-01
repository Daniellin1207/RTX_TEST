//
//  Light.hpp
//  RTX_TEST
//
//  Created by Daniel.Lin on 2019/6/1.
//  Copyright © 2019 Daniel.Lin. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Light{
public:
    glm::vec3 Position;
    glm::vec3 Direction;
    glm::vec3 Color;
    Light(glm::vec3 position=glm::vec3(3,0,0),glm::vec3 direction=glm::vec3(-1,0,0),glm::vec3 color=glm::vec3(1)){
        Position=position;
        Direction=direction;
        Color=color;
    }
};
#endif /* Light_hpp */
