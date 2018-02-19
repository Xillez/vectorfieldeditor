#include "Window.h"

Window::Window(int w, int h, const std::string& title)
{
    this->width = w;
    this->height = h;
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    // Sets SDL OpenGL Attributes
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Makes the window pointer
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    // If window creation failed
    if (window == NULL)
    {
        std::cerr << "SDL Error(couldn't create window): " << SDL_GetError() << std::endl;
    }

    // Sets the context for the given window
    glContext = SDL_GL_CreateContext(window);

    // If window context creation failed
    if (glContext == NULL)
    {
        std::cerr << "SDL Error(something about glcontext): " << SDL_GetError() << std::endl;
    }

    // Using an experimental version of OpenGl
    glewExperimental = GL_TRUE;
    // Initialize Glew
    GLenum status = glewInit();
    // Glew failed to initialize
    if (status = !GLEW_OK)
    {
        std::cerr << "GLEW Error(something about the initilazation): " << glewGetErrorString(status) << " | OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    }

    /*if (GLEW_VERSION_4_5)
    {
        std::cout << "We support version 4.5.0!" << std::endl;
    }*/

    //glEnable(GL_DEPTH_TEST);

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
}

Window::~Window()
{
    // Delete Window Context
    SDL_GL_DeleteContext(glContext);
    // Destroy window
    SDL_DestroyWindow(window);
    // SDL Should quit
    SDL_Quit();
}

void Window::update()
{
    // Swap buffers
    SDL_GL_SwapWindow(window);
}

void Window::handleEvents(Camera* camera)
{
    // Get all events
    SDL_Event e;
    // Extract all events
    while (SDL_PollEvent(&e))
    {
        // If SDL_QUIT event, then window should close
        switch (e.type)
        {
            case SDL_QUIT: windowShutdownEvent(); break; // isWOpen = false; break;
            case SDL_WINDOWEVENT_RESIZED: windowResizedEvent(camera, e.window.data1, e.window.data2); break;
            /*case SDL_WINDOWEVENT_SIZE_CHANGED: windowResizedEvent(/*camera,* e.window.data1, e.window.data2); break;
            case SDL_WINDOWEVENT_MINIMIZED: /*Pause simulation of particled once added pluss __________* break;
            case SDL_WINDOWEVENT_MAXIMIZED: windowResizedEvent(/*camera, *e.window.data1, e.window.data2); /*Unpause (if on) simulation of particled once added pluss __________* break;
            case SDL_WINDOWEVENT_ENTER: windowMouseEnterEvent(); break;
            case SDL_WINDOWEVENT_LEAVE: windowMouseLeaveEvent(); break;
            case SDL_WINDOWEVENT_FOCUS_GAINED: windowFocusGainedEvent(); break;
            case SDL_WINDOWEVENT_FOCUS_LOST: windowFocusLostEvent(); break;
            case SDL_WINDOWEVENT_EXPOSED: update(); break;*/
        }
    }
}

bool Window::isOpen()
{
    return isWOpen;
}

void Window::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int Window::getWidth()
{
    return width;
}

int Window::getHeight()
{
    return height;
}

void Window::windowResizedEvent(Camera* camera, int x, int y)
{
    windowWidth = x; windowHeight = y;
    SDL_SetWindowSize(window, windowWidth, windowHeight);
    camera->update(camera->getPosition(), camera->getFOV(), windowWidth/windowHeight, camera->getZNear(), camera->getZFar());
}

void Window::windowShutdownEvent()
{
    isWOpen = false;
}

void Window::windowMouseEnterEvent()
{
    //
}

void Window::windowMouseLeaveEvent()
{
    //
}

void Window::windowFocusGainedEvent()
{
    //
}

void Window::windowFocusLostEvent()
{
    //
}
