#include "Texture.h"

Texture::Texture()
{
    //
}

Texture::Texture(const std::string& fileName)
{
    int width;
    int height;
    int numComponents;
    // Load image
    unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);
    if (imageData == NULL)
        std::cerr << "Texture loading failed for texture: " << fileName << std::endl;
    // Get a newly generated texture from OpenGl
    glGenTextures(1, &texture);
    // Bind it to the texture
    glBindTexture(GL_TEXTURE_2D, texture);
    // Texture tiling logic
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Texture size logic
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Send texture to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    //Delete image data
    stbi_image_free(imageData);
}

Texture::~Texture()
{
    // Delete texture
    glDeleteTextures(1, &texture);
}

void Texture::bind(unsigned int unit)
{
    // Fail safe for unvalid texture unit
    assert(unit >= 0 && unit <= 31);
    // Set active texture
    glActiveTexture(GL_TEXTURE0 + unit);
    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, texture);
}
