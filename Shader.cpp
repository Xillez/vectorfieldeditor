#include "Shader.h"

static std::string LoadShader(const std::string & fileName);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader()
{
    // Make a program for shaders
    program = glCreateProgram();
    // Make vertex shader
    shaders[VERTEX_SHADER] = CreateShader(LoadShader("./shaders/vertexShader.glsl"), GL_VERTEX_SHADER);
    // Make geometry shader
    //shaders[GEOMETRY_SHADER] = CreateShader(LoadShader("./shaders/GeometryShader.glsl"), GL_GEOMETRY_SHADER);
    // Make fragment shader
    shaders[FRAGMENT_SHADER] = CreateShader(LoadShader("./shaders/fragmentShader.glsl"), GL_FRAGMENT_SHADER);

    // Attach all indevidual shaders to the program
    for (unsigned int i = 0; i < NUM_SHADERS; i++)
        glAttachShader(program, shaders[i]);

    // Bind the word "position" in the shader as "0"
    glBindAttribLocation(program, 0, "position");
    //
    glBindAttribLocation(program, 1, "color");

    // Link shader program
    glLinkProgram(program);
    // Check shader program for linking errors
    CheckShaderError(program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

    // Validate shader program
    glValidateProgram(program);
    // Check shader program for validation status
    CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

    uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");
}

Shader::~Shader()
{
    // Deleting all shaders
    for (unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(program, shaders[i]);
        glDeleteShader(shaders[i]);
    }
    // Delete shader program
    glDeleteProgram(program);
}

void Shader::bind()
{
    // Binds the program to window
    glUseProgram(program);
}

void Shader::update(const Transform& transform, const Camera& camera)
{
    glm::mat4 model = camera.getViewProjection() * transform.getModel();

    glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

std::string LoadShader(const std::string& fileName)
{
    std::ifstream file((fileName).c_str());

    std::string output;
    std::string line;

    if (file.is_open())
    {
        while (file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else
    {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if (isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if (success == GL_FALSE)
    {
        if (isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

GLuint CreateShader(const std::string& text, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    if (shader == 0)
        std::cerr << "Error: Shader creation failed!" << std::endl;

    const GLchar* shaderSourceStrings[1];
    shaderSourceStrings[0] = text.c_str();
    GLint shaderSourceStringLengths[1];
    shaderSourceStringLengths[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

    return shader;
}