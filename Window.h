#pragma once
#include "Global.h"
#include "Camera.h"

class Window
{
public:
    Window(int width, int height, const std::string& title);
    virtual ~Window();

    void update();
    void handleEvents(Camera* camera);
    bool isOpen();
    void clear(float r, float g, float b, float a);
    int getWidth();
    int getHeight();

    // Event callback functions
    void windowResizedEvent(Camera* camera, int x, int y);
    void windowShutdownEvent();
    void windowMouseEnterEvent();
    void windowMouseLeaveEvent();
    void windowFocusGainedEvent();
    void windowFocusLostEvent();

protected:
    //
private:
    // The Window
    SDL_Window* window;
    // Windows context
    SDL_GLContext glContext;
    // If the window is closed or not
    bool isWOpen = true;
    // Glew initialization status
    GLenum m_status;
    // Width
    int width = 0;
    // Height
    int height = 0;
};

