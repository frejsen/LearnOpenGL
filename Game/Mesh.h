#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct TextureF {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureF>      textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureF> textures);
    void draw(Shader& shader);

private:
    GLuint _vao, _vbo, _ebo = NULL;

    void setupMesh();
};

