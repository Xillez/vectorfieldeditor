#pragma once
class Vertex
{
public:
    Vertex(const glm::vec3& pos, glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
    {
        this->pos = pos;
        this->color = color;
    }

    virtual ~Vertex() {}

    inline glm::vec3 getPos() { return pos; }
    inline void setPos(glm::vec3 pos) { this->pos = pos; }
    inline glm::vec4 getColor() { return color; }
    inline void setColor(glm::vec4 pos) { this->color = color; }

    bool operator==(Vertex& other) const {}
    /*{
        return (pos == other.getPos() && color == other.getColor());
    }*/

protected:
    //
private:
    glm::vec3 pos;
    glm::vec4 color;
};

