#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "shader/shader.hpp"
#include "mesh/mesh.hpp"
#include "window/window.hpp"


int main()
{
    Window window(512, 512, "MyEngine GLFW C++");
    if(!window)
    {
        std::cout << "Failed to call Window::Window()\n";
        return -1;
    }
    window.setClearColor(1.0f, 1.0f, 1.0f);

    std::string vertexCode = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		void main()
		{
		   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
	)";

    std::string fragmentCode = R"(
		#version 330 core
		out vec4 FragColor;
		void main()
		{
		   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		}
	)";

    auto shader = Shader::loadFromString("testShader", vertexCode, fragmentCode);
    if(!shader)
    {
        std::cout << "Failed to call Shader::loadFromString()\n";
        glfwTerminate();
        return -1;
    }

    std::vector<float> vertices = {
        0.5f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f,
        -0.5f,  0.5f,  0.0f
    };

    std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3
    };

    std::vector<unsigned int> attributes = {
        3
    };

    auto mesh = Mesh(vertices, indices, attributes);

    while(window.isOpen())
    {
        window.clear();

        shader.use();
        mesh.draw();

        window.update();
    }
}
