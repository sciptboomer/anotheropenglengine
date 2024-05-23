#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


class Window
{
private:
    int _w;
    int _h;
    const char* _name;
    GLFWwindow* _window;

    static bool _debugFlag;
    bool _ok;

public:
    Window()
        : _w(0), _h(0), _window(nullptr), _ok(false)
    {

    }

    Window(int windowW, int windowH, const char* windowName)
        : _w(windowW), _h(windowH), _name(windowName), _ok(true)
    {
        if(!glfwInit())
        {
            if(Window::_debugFlag) {
                std::cout << "Failed to call glfwInit()\n";
            }
            _ok = false;
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        _window = glfwCreateWindow(_w, _h, _name, 0, 0);
        if(!_window)
        {
            if(Window::_debugFlag) {
                std::cout << "Failed to call glfwCreateWindow()\n";
            }
            _ok = false;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(_window);
        glewExperimental = GL_TRUE;
        if(glewInit() != GLEW_OK)
        {
            if(Window::_debugFlag) {
                std::cout << "Failed to call glewInit()\n";
            }
            _ok = false;
            glfwTerminate();
            return;
        }
    }

    ~Window()
    {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    inline void setClearColor(float r, float g, float b, float a = 1.0f)
    {
        glClearColor(r, g, b, a);
    }

    inline void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    inline void update()
    {
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }

    inline bool isOpen() const
    {
        return !glfwWindowShouldClose(_window);
    }

    static void setDebug(bool state)
    {
        Window::_debugFlag = state;
    }

    operator bool() const
    {
        return _ok;
    }
};

bool Window::_debugFlag = true;
