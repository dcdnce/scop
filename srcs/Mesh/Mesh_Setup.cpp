#include "Mesh.hpp"
#include "FacesType.hpp"
#include <stdlib.h>


void Mesh::_setupColors()
{
    for (size_t i = 0 ; i < vertices.size() ; i++)
    {
        vertices[i].color = {
            static_cast<float>(rand()%255) / 255.f,
            static_cast<float>(rand()%255) / 255.f,
            static_cast<float>(rand()%255) / 255.f
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