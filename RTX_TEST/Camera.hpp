//
//  Camera.hpp
//  RTX_TEST
//
//  Created by Daniel.Lin on 2019/5/28.
//  Copyright © 2019 Daniel.Lin. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const float YAW=-90.0f;
const float PITCH=0.0f;
const float SPEED=2.5f;
const float SENSITIVITY=0.1f;
const float ZOOM=45.0f;

enum Camera_Movement{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    
    float Yaw;
    float Pitch;
    
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    
    Camera(glm::vec3 position=glm::vec3(1,0,0),glm::vec3 up=glm::vec3(0,1,0),float yaw=YAW,float pitch=PITCH):Front(glm::vec3(0,0,-1)),MovementSpeed(SPEED),MouseSensitivity(SENSITIVITY),Zoom(ZOOM)
    {
        Position=position;
        WorldUp=up;
        Yaw=yaw;
        Pitch=pitch;
        updateCameraVectors();
    }
    
    Camera(float posX,float posY,float posZ,float upX,float upY,float upZ,float yaw,float pitch):Front(glm::vec3(0,0,-1)),MovementSpeed(SPEED),MouseSensitivity(SENSITIVITY),Zoom(ZOOM)
    {
        Position=glm::vec3(posX,posY,posZ);
        WorldUp=glm::vec3(upX,upY,upZ);
        Yaw=yaw;
        Pitch=pitch;
        updateCameraVectors();
    }
    
    glm::mat4 GetViewMatrix()
    {
      
//        printf("%f %f %f\n",Position.x,Position.y,Position.z);
//        printf("%f %f %f\n",Up.x,Up.y,Up.z);
//        printf("%f %f %f\n",Front.x,Front.y,Front.z);
//        printf("%f %f %f\n",Right.x,Right.y,Right.z);
        
        glm::mat4 translation=glm::mat4(1.0f);
        translation[3][0]=-Position.x;
        translation[3][1]=-Position.y;
        translation[3][2]=-Position.z;

        glm::mat4 rotation=glm::mat4(1.0f);
        rotation[0][0]=Right.x;
        rotation[1][0]=Right.y;
        rotation[2][0]=Right.z;

        rotation[0][1]=Up.x;
        rotation[1][1]=Up.y;
        rotation[2][1]=Up.z;

        rotation[0][2]=Front.x;
        rotation[1][2]=Front.y;
        rotation[2][2]=Front.z;
        
        glm::mat4 m=rotation*translation;
//        glm::mat4 m= glm::lookAt(Position, Position+Front, Up);
        
//        for(int i=0;i<4;i++)
//        {
//            for (int j=0; j<4; j++)
//            {
//                std::cout<<m[j][i]<<" ";
//            }
//            std::cout<<i<<" "<<std::endl;
//        }
        return m;
//        return glm::lookAt(Position, glm::vec3(0,0,0), Up);
    }
    
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity=MovementSpeed*deltaTime;
        if(direction==FORWARD)
            Position+=Front*velocity;
        if(direction==BACKWARD)
            Position-=Front*velocity;
        if(direction==LEFT)
            Position-=Right*velocity;
        if(direction==RIGHT)
            Position+=Right*velocity;
        std::cout<<Position.x<<" "<<Position.y<<" "<<Position.z<<std::endl;
    }
    
    void ProcessMouseMovement(float xoffset,float yoffset,bool constrainPitch=true)
    {
        xoffset*=MouseSensitivity;
        yoffset*=MouseSensitivity;
        
        Yaw+=xoffset;
        Pitch+=yoffset;
        
        if(constrainPitch){
            if(Pitch>89.0f)
                Pitch=89.0f;
            if(Pitch<-89.0f)
                Pitch=-89.0f;
        }
        std::cout<<Yaw<<" "<<Pitch<<std::endl;
        updateCameraVectors();
    }
    
    void ProcessMouseScroll(float yoffset)
    {
        if(Zoom>=1.0f && Zoom<=45.0f)
            Zoom-=yoffset;
        if(Zoom<=1.0f)
            Zoom=1.0f;
        if(Zoom>=45.0f)
            Zoom=45.0f;
    }
    
private:
    
    void updateCameraVectors()
    {
        glm::vec3 front;
        front.x=cos(glm::radians(Yaw))*cos(glm::radians(Pitch));
        front.y=sin(glm::radians(Pitch));
        front.z=sin(glm::radians(Yaw))*cos(glm::radians(Pitch));
        Front=glm::normalize(front);
        
        Right=glm::normalize(glm::cross(Front, WorldUp));
        Up=glm::normalize(glm::cross(Right, Front));
    };
};





#endif /* Camera_hpp */
