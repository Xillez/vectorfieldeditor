#pragma once
#include "Global.h"

class Camera
{
public:
    Camera(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar)
    {
        fieldOfView = fov;
        aspectRatio = aspect;
        zNearPlane = zNear;
        zFarPlane = zFar;
        perspective = glm::perspective(fieldOfView, aspectRatio, zNearPlane, zFarPlane);
        position = pos;
        forward = glm::vec3(0, 0, 1);
        up = glm::vec3(0, 1, 0);
    };

    inline void update(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar)
    {
        fieldOfView = fov;
        aspectRatio = aspect;
        zNearPlane = zNear;
        zFarPlane = zFar;
        perspective = glm::perspective(fov, aspect, zNear, zFar);
        position = pos;
        forward = glm::vec3(0, 0, 1);
        up = glm::vec3(0, 1, 0);
    };

    virtual ~Camera() {};

    inline glm::mat4 getViewProjection() const
    {
        return perspective * glm::lookAt(position, position + forward, up);
    };

    inline float getFOV() { return fieldOfView; };
    inline void setFOV(float fov) { fieldOfView = fov; };
    inline float getAspect() { return aspectRatio; };
    inline void setAspect(float aspect) { aspectRatio = aspectRatio; };
    inline float getZNear() { return zNearPlane; };
    inline void setZNear(float zNear) { zNearPlane = zNear; };
    inline float getZFar() { return zFarPlane; };
    inline void setZFar(float zFar) { zFarPlane = zFar; };
    inline glm::vec3 getPosition() { return position; };
    inline void setPosition(glm::vec3 posV) { position = posV; };
    inline glm::vec3 getForward() { return position; };
    inline void setForward(glm::vec3 forV) { forward = forV; };
    inline glm::vec3 getUp() { return position; };
    inline void setUp(glm::vec3 upV) { up = upV; };
protected:
    //
private: 
    float fieldOfView, aspectRatio, zNearPlane, zFarPlane;
    glm::mat4 perspective;
    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up;
};

