#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>


class Shader
{
private:
    unsigned int _id;
    std::string _name;

    static bool _debugFlag;
    bool _ok;

    Shader()
        : _id(0), _name(""), _ok(false)
    {

    }

    Shader(unsigned int id, std::string name)
        : _id(id), _name(name), _ok(true)
    {

    }

    static unsigned int compileShader(const char* code, unsigned int type)
    {
        unsigned int shaderId = glCreateShader(type);
        glShaderSource(shaderId, 1, &code, NULL);
        glCompileShader(shaderId);
        return shaderId;
    }

    static unsigned int linkProgram(unsigned int vertexId, unsigned int fragmentId)
    {
        unsigned int programId = glCreateProgram();
        glAttachShader(programId, vertexId);
        glAttachShader(programId, fragmentId);
        glLinkProgram(programId);

        glDeleteShader(vertexId);
        glDeleteShader(fragmentId);

        return programId;
    }

    static bool checkShader(unsigned int shaderId, std::string shaderName, std::string shaderPath)
    {
        int status;
        char debugLog[1024];
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
        if(!status)
        {
            if(Shader::_debugFlag)
            {
                glGetShaderInfoLog(shaderId, 1024, NULL, debugLog);
                std::cout << "ERROR: Failed to compile shader \"" << shaderName << "\"" << " in \"" << shaderPath << "\"" << std::endl << debugLog;
            }

            return false;
        }

        return true;
    }

    static bool checkShader(unsigned int shaderId, std::string shaderName)
    {
        int status;
        char debugLog[1024];
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
        if(!status)
        {
            if(Shader::_debugFlag)
            {
                glGetShaderInfoLog(shaderId, 1024, NULL, debugLog);
                std::cout << "ERROR: Failed to compile shader \"" << shaderName << "\"" << std::endl << debugLog;
            }

            return false;
        }

        return true;
    }

    static bool checkProgram(unsigned int programId, std::string shaderName)
    {
        int status;
        char debugLog[1024];
        glGetShaderiv(programId, GL_LINK_STATUS, &status);
        if(!status)
        {
            if(Shader::_debugFlag)
            {
                glGetShaderInfoLog(programId, 1024, NULL, debugLog);
                std::cout << "ERROR: Failed to link shader \"" << shaderName << "\"" << std::endl << debugLog;
            }

            return false;
        }

        return true;
    }

public:
    static Shader loadFromString(std::string shaderName, std::string vertex, std::string fragment)
    {
        unsigned int vertexId = compileShader(vertex.c_str(), GL_VERTEX_SHADER);
        if(!checkShader(vertexId, shaderName))
        {
            return Shader();
        }

        unsigned int fragmentId = compileShader(fragment.c_str(), GL_FRAGMENT_SHADER);
        if(!checkShader(fragmentId, shaderName))
        {
            return Shader();
        }

        unsigned int programId = linkProgram(vertexId, fragmentId);
        if(!checkProgram(programId, shaderName))
        {
            return Shader();
        }

        return Shader(programId, shaderName);
    }

    void use() const
    {
        glUseProgram(_id);
    }

    static void setDebug(bool flag)
    {
        Shader::_debugFlag = flag;
    }

    operator bool() const
    {
        return _ok;
    }
};

bool Shader::_debugFlag = true;
