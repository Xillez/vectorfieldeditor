#pragma once
#include "Global.h"
#include "Vertex.h"

class Mesh
{
public:
    Mesh();
    Mesh(GLenum drawType);
    Mesh(Vertex* vertices, const unsigned int numVertices, GLenum drawType, unsigned int* indecies, unsigned int numIndecies);
    virtual ~Mesh();

    int appendVertex(Vertex vertex);
    void appendDrawIndex(int index);
    GLenum getDrawtype();
    void setDrawtype(GLenum dt);
    void draw();
    bool init();
protected:
    //
private:
    enum {POSITION_VB, COLOR_VB, INDEX_VB, NUM_BUFFERS};

    // Number of vertices
    unsigned int numVertices = 0;
    // Number of Indecies
    unsigned int numIndecies = 0;
    // Primitive draw type
    GLenum drawType = NULL;

    // The vertex array object
    GLuint vertexArrayObject;
    // All vertex array buffers
    GLuint vertexArrayBuffers[NUM_BUFFERS];

    // Mesh buffers
    std::vector<glm::vec3> positions;
    std::vector<glm::vec4> colors;
    std::vector<int> indecies;
};
