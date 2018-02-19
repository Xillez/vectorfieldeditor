#include "Mesh.h"

Mesh::Mesh()
{
    //
}

Mesh::Mesh(GLenum drawType)
{
    // Set the drawType
    this->drawType = drawType;
}

Mesh::Mesh(Vertex* vertices, const unsigned int numV, GLenum drawType, unsigned int* indexes, unsigned int numI)
{
    // Set the drawType
    this->drawType = drawType;

    // Set the Number of vertices to draw
    this->numVertices = numV;
    this->numIndecies = numI;

    // Prereserve enough memory
    positions.reserve(numVertices);
    colors.reserve(numVertices);

    // Move all positions and texCoords over
    for (unsigned int i = 0; i < numIndecies; i++)
    {
        positions.push_back(vertices[i].getPos());
        colors.push_back(vertices[i].getColor());
    }

    for (unsigned int i = 0; i < numIndecies; i++) { indecies.push_back(indexes[i]); }

    //init();
}

Mesh::~Mesh()
{
    // Delete vertex array
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(NUM_BUFFERS, vertexArrayBuffers);
}

int Mesh::appendVertex(Vertex vertex)
{
    positions.push_back(vertex.getPos());
    colors.push_back(vertex.getColor());
    numVertices++;
    return numVertices - 1;
}

void Mesh::appendDrawIndex(int index)
{
    indecies.push_back(index);
    numIndecies++;
}

GLenum Mesh::getDrawtype()
{
    return drawType;
}

void Mesh::setDrawtype(GLenum dt)
{
    // Error checking for the draw count!
    if (drawType != GL_POINTS &&
        drawType != GL_LINES &&
        drawType != GL_LINE_LOOP &&
        drawType != GL_LINE_STRIP &&
        drawType != GL_TRIANGLES &&
        drawType != GL_TRIANGLE_STRIP &&
        drawType != GL_TRIANGLE_FAN)
    {
        std::cerr << "Draw type is a non OpenGl Primitive!\nShould be:\n  - GL_POINTS\n  - GL_LINES\n  - GL_LINE_LOOP\n  - GL_LINE_STRIP\n  - GL_TRIANGLES\n  - GL_TRIANGLE_STRIP\n  - GL_TRIANGLE_FAN\n" << std::endl;
    }
    else { this->drawType = dt; }
}

void Mesh::draw()
{
    // Bind the vertex array object
    glBindVertexArray(vertexArrayObject);
    // Draw array
    //glDrawArrays(drawType, 0, numVertices);
    glDrawElements(drawType, numIndecies, GL_UNSIGNED_INT, 0);
    // Clear binding of vertex array
    glBindVertexArray(0);
}

bool Mesh::init()
{
    bool noErr = true;
    // Error checking for the draw type!
    if (drawType != GL_POINTS &&
        drawType != GL_LINES &&
        drawType != GL_LINE_LOOP &&
        drawType != GL_LINE_STRIP &&
        drawType != GL_TRIANGLES &&
        drawType != GL_TRIANGLE_STRIP &&
        drawType != GL_TRIANGLE_FAN) {
        std::cerr << "Draw type is a non OpenGl Primitive!\nShould be:\n  - GL_POINTS\n  - GL_LINES\n  - GL_LINE_LOOP\n  - GL_LINE_STRIP\n  - GL_TRIANGLES\n  - GL_TRIANGLE_STRIP\n  - GL_TRIANGLE_FAN\n" << std::endl; noErr = false;
    }

    // Error checking the number of vertices
    if (numVertices < 1) { std::cerr << "Number of vertices can't be 0 or less!" << std::endl; noErr = false; }

    // Error checking for number of indecies
    if (numIndecies < 1) { std::cerr << "Number of indecies can't be 0 or less!" << std::endl; noErr = false; }

    // Error checking for draw indecies array
    if (indecies.size() < 0) { std::cerr << "An array with draw sequence must be given!" << std::endl; noErr = false; }

    // Escape and fail initialization!
    if (!noErr) return noErr;

    /*for (unsigned int i = 0; i < numVertices; i++)
    {
    std::cout << "\n\nPosition: (" << positions[i].x <<
    ", " << positions[i].y <<
    ", " << positions[i].z << ")\n Color: (" << colors[i].x <<
    ", " << colors[i].y <<
    ", " << colors[i].z <<
    ", " << colors[i].w << ")";
    }*/

    // Generate vertex array object
    glGenVertexArrays(1, &vertexArrayObject);
    // Bind the vertex array object
    glBindVertexArray(vertexArrayObject);

    // Generate buffer
    glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

    // !!!! Make a buffer for VERTEX POSITIONS !!!!
    // Bind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);

    // Put the given data in buffer
    glBufferData(GL_ARRAY_BUFFER, numIndecies * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

    // IDK, Something about vertex attributes as an array
    glEnableVertexAttribArray(POSITION_VB);

    // Get OpenGl how to use the vertex attribute array
    glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // !!!! Make a buffer for the COLORS !!!!
    // Bind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[COLOR_VB]);

    // Put the given data in buffer
    glBufferData(GL_ARRAY_BUFFER, numIndecies * sizeof(colors[0]), &colors[0], GL_STATIC_DRAW);

    // IDK, Something about vertex attributes as an array
    glEnableVertexAttribArray(COLOR_VB);

    // Get OpenGl how to use the vertex attribute array
    glVertexAttribPointer(COLOR_VB, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // !!!! Make a buffer for the INDEX ARRAY !!!!
    // Bind the buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);

    // Put the given data in buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndecies * sizeof(indecies[0]), &indecies[0], GL_STATIC_DRAW);

    // Bind vertex array
    glBindVertexArray(0);

    return true;
}

/*void Mesh::InitMesh(const IndexedModel& model)
{
    // Set the amount of drawn points
    drawCount = model.indices.size(); //drawCount;

    // Generate vertex array object
    glGenVertexArrays(1, &vertexArrayObject);
    // Bind the vertex array object
    glBindVertexArray(vertexArrayObject);

    //

    // Generate buffer
    glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

    // !!!! Make a buffer for VERTEX POSITIONS !!!!
    // Bind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
    // Put the given data in buffer
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

    // IDK, Something about vertex attributes as an array
    glEnableVertexAttribArray(0);
    // Gett OpenGl how to use the vertex attribute array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // !!!! Make a buffer for TEXTURE COORDINATES !!!!
    // Bind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
    // Put the given data in buffer
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

    // IDK, Something about vertex attributes as an array
    glEnableVertexAttribArray(1);
    // Gett OpenGl how to use the vertex attribute array
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // !!!! Make a buffer for NORMALS !!!!
    // Bind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
    // Put the given data in buffer
    glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

    // IDK, Something about vertex attributes as an array
    glEnableVertexAttribArray(2);
    // Gett OpenGl how to use the vertex attribute array
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // !!!! Make a buffer for the INDEX ARRAY !!!!
    // Bind the buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);

    // Put the given data in buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

    // Bind vertex array
    glBindVertexArray(0);
}*/


