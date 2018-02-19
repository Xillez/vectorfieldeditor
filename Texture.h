#pragma once
#include "stb_image.h"
#include <string>
#include <GL\glew.h>
#include <cassert>
#include <iostream>

class Texture
{
public:
    Texture();
    Texture(const std::string& fileName);
    virtual ~Texture();
    void bind(unsigned int unit);

protected:
    //
private:
    GLuint texture;

    Texture(const Texture& texture) {};
    void operator=(const Texture& texture) {};
};

