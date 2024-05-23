#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>


class Mesh
{
private:
    unsigned int _vao, _vbo, _ebo;
    std::vector<float> _vertices;
    std::vector<unsigned int> _indices;
    std::vector<unsigned int> _attributes;

    static bool _debugFlag;
    bool _ok;

public:
    Mesh()
        : _vao(0), _vbo(0), _ebo(0), _ok(false)
    {

    }

    Mesh(
        std::vector<float>& vertices,
        std::vector<unsigned int>& indices,
        std::vector<unsigned int>& attributes
    )
        : _ok(true)
    {
        if(vertices.size() == 0)
        {
            if(Mesh::_debugFlag) {
                std::cout << "ERROR(Mesh): Failed to call Mesh::Mesh(). Vertices array cannot be empty\n";
            }
            _ok = false;
            return;
        }

        if(indices.size() == 0)
        {
            if(Mesh::_debugFlag) {
                std::cout << "ERROR(Mesh): Failed to call Mesh::Mesh(). Indices array cannot be empty\n";
            }
            _ok = false;
            return;
        }

        if(attributes.size() == 0)
        {
            if(Mesh::_debugFlag) {
                std::cout << "ERORR(Mesh): Failed to call Mesh::Mesh(). Attributes array cannot be empty\n";
            }
            _ok = false;
            return;
        }

        _vertices.assign(vertices.begin(), vertices.end());
        _indices.assign(indices.begin(), indices.end());
        _attributes.assign(attributes.begin(), attributes.end());

        glGenVertexArrays(1, &_vao);
        glGenBuffers(1, &_vbo);
        glGenBuffers(1, &_ebo);

        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &_vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &_indices[0], GL_STATIC_DRAW);

        for(unsigned int i = 0; i < _attributes.size(); i++)
        {
            unsigned int size = _attributes[i];
            glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, size * sizeof(float), (void*)0);
            glEnableVertexAttribArray(i);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void draw() const
    {
        glBindVertexArray(_vao);
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    }

    unsigned int getVao() const
    {
        return _vao;
    }

    unsigned int getVbo() const
    {
        return _vbo;
    }

    unsigned int getEbo() const
    {
        return _ebo;
    }

    static void setDebug(bool state)
    {
        Mesh::_debugFlag = state;
    }

    operator bool() const
    {
        return _ok;
    }
};

bool Mesh::_debugFlag = true;
