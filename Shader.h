#pragma once
#include <string>
#include <GL\glew.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Transform.h"
#include "Camera.h"

class Shader
{
public:
    Shader();
    virtual ~Shader();

    void bind();
    void update(const Transform& trans, const Camera& camera);
protected:
    //
private:
   enum { TRANSFORM_U, NUM_UNIFORMS };
   enum { VERTEX_SHADER, FRAGMENT_SHADER, NUM_SHADERS };

    GLuint program;
    GLuint shaders[NUM_SHADERS];
    GLuint uniforms[NUM_UNIFORMS];
};

