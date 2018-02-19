#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"

int main(int argc, char *args[])
{
    Window window(windowWidth, windowHeight, "Vector Field Editor");
    Shader shader;
    Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), 70.0f, windowWidth / windowHeight, 0.0f, 100.0f);
    Transform trans(glm::vec3(0.0f, 0.0f, 3.0f)/*, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)*/);

    /*Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
                          Vertex(glm::vec3( 0.5, -0.5, 0.0), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)),
                          Vertex(glm::vec3( 0.5,  0.5, 0.0), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)), 
                          Vertex(glm::vec3(-0.5,  0.5, 0.0), glm::vec4(0.45f, 0.0f, 0.55f, 1.0f)) };
    int numV = 4;
    unsigned int indecies[] = { 0, 1, 2, 0, 3, 2};
    int numI = 6;*/

    //Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), GL_TRIANGLES, indecies, sizeof(indecies) / sizeof(indecies[0]));
    Mesh mesh(GL_TRIANGLES);

    // Append all vertices
    mesh.appendVertex(Vertex(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
    mesh.appendVertex(Vertex(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    mesh.appendVertex(Vertex(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
    mesh.appendVertex(Vertex(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec4(0.45f, 0.0f, 0.55f, 1.0f)));

    // Append all draw indecies
    mesh.appendDrawIndex(0);
    mesh.appendDrawIndex(1);
    mesh.appendDrawIndex(2);
    mesh.appendDrawIndex(0);
    mesh.appendDrawIndex(3);
    mesh.appendDrawIndex(2);

    mesh.init();

    while (window.isOpen())
    {
        // Clear window
        window.clear(0.0f, 0.0f, 0.0f, 0.0f);
        //glViewport(0.0f, window.getHeight()/2, window.getWidth()/2, window.getHeight()/2);
        shader.bind();
        shader.update(trans, camera);
        mesh.draw();
        // Update window
        window.update();
        // Handle events
        window.handleEvents(&camera);
    }
    return 0;
}

/*
// Move all positions and texCoords over
for (unsigned int i = 0; i < numVertices; i++)
{
positions.push_back(vertices[i].getPos());
colors.push_back(vertices[i].getColor());
}

for (unsigned int i = 0; i < numVertices; i++)
{
std::cout << "\n\nPosition: (" << positions[i].x <<
", " << positions[i].y <<
", " << positions[i].z << ")\n Color: (" << colors[i].x <<
", " << colors[i].y <<
", " << colors[i].z <<
", " << colors[i].w << ")";
}

std::cout << "\n\nIndecies: (";
for (unsigned int i = 0; i < numIndecies; i++)
{
std::cout << indecies[i] << ", ";
}
std::cout << ")";
*/

/*
bool Mesh::init()
{
bool noErr = true;
// Error checking for the draw count!
if (drawType != GL_POINTS &&
drawType != GL_LINES &&
drawType != GL_LINE_LOOP &&
drawType != GL_LINE_STRIP &&
drawType != GL_TRIANGLES &&
drawType != GL_TRIANGLE_STRIP &&
drawType != GL_TRIANGLE_FAN) { std::cerr << "Draw type is a non OpenGl Primitive!\nShould be:\n  - GL_POINTS\n  - GL_LINES\n  - GL_LINE_LOOP\n  - GL_LINE_STRIP\n  - GL_TRIANGLES\n  - GL_TRIANGLE_STRIP\n  - GL_TRIANGLE_FAN\n" << std::endl; noErr = false; }

// Error checking the number of vertices
if (numVertices < 1) { std::cerr << "Number of vertices can't be 0 or less!" << std::endl; noErr = false; }

// Error checking for number of indecies
if (numIndecies < 1) { std::cerr << "Number of indecies can't be 0 or less!" << std::endl; noErr = false; }

// Error checking for draw indecies array
if (!indecies) { std::cerr << "An array with draw sequence must be given!" << std::endl; noErr = false; }

// Escape and fail initialization!
if (!noErr) return noErr;

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
glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

// IDK, Something about vertex attributes as an array
glEnableVertexAttribArray(POSITION_VB);

// Get OpenGl how to use the vertex attribute array
glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);

// !!!! Make a buffer for the COLORS !!!!
// Bind the buffer
glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[COLOR_VB]);

// Put the given data in buffer
glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(colors[0]), &colors[0], GL_STATIC_DRAW);

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
}
*/

/*
// Set the drawType
this->drawType = dType;

// Set the Number of vertices to draw
this->numVertices = numV;
this->numIndecies = numI;

this->indecies = indexes;
*/