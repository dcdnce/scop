#include "../includes/glad/glad.h"
#include "Mesh.hpp"
#include "FacesType.hpp"
#include <stdlib.h>


Mesh::Mesh(
    std::vector<Vertex> const& vertices, 
    std::vector<unsigned int> const& indices, 
    std::vector<Texture> const& textures, 
    int const facesType
    )
    : vertices(vertices), indices(indices), textures(textures), facesType(facesType)
{
    _setupColors();
    _setupBuffers();
    _setupShaders();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::Draw(void)
{
    glUseProgram(attached_shader.program);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Mesh::_setupColors()
{
    for (size_t i = 0 ; i < vertices.size() ; i++)
    {
        const float color = static_cast<float>(rand()%255) / 255.f;
        vertices[i].color = {
            color,
            color,
            color
        };
    }
}

void Mesh::_setupBuffers()
{
    /* Init objects */
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    /* Bind & fill objects */
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    /* Link the data */
        /* Position */
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
        /* Normal */
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, normal)));
        /* TexCoords */
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, texCoords)));
        /* Color */
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, color)));

    /* Unbind objects */
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::_setupShaders()
{
    attached_shader.loadShaders(FACE_TYPE_VVTVN_VERTEX_SHADER, FACE_TYPE_VVTVN_FRAG_SHADER);
}