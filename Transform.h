#pragma once
#include "Global.h"

class Transform
{
public:
    Transform(const glm::vec3& pos = glm::vec3(), glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
    {
        this->pos = pos;
        this->rot = rot;
        this->scale = scale;
    };

    virtual ~Transform() {};

    inline glm::mat4 getModel() const
    {
        return glm::translate(pos) * (glm::rotate(rot.z, glm::vec3(0, 0, 1)) * glm::rotate(rot.y, glm::vec3(0, 1, 0)) * glm::rotate(rot.x, glm::vec3(1, 0, 0))) * glm::scale(scale);
    };

    inline glm::vec3& getPos() { return pos; };
    inline glm::vec3& getRot() { return rot; };
    inline glm::vec3& getScale() { return scale; };
    inline void setPos(glm::vec3& pos) { this->pos = pos; };
    inline void setRot(glm::vec3& rot) { this->rot = rot; };
    inline void setScale(glm::vec3& scale) { this->scale = scale; };

protected:
    //
private:
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;
};

