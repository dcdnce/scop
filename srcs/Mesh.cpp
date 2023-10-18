#include "../includes/Mesh.hpp"
#include "../includes/glad/glad.h"

Mesh::Mesh(std::vector<Vertex> const& vertices, std::vector<unsigned int> const& indices, std::vector<Texture> const& textures)
    : vertices(vertices), indices(indices), textures(textures)
{
    Setup();
}

void Mesh::Setup()
{
    /* Init & bind objects */
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /* Send data and link it */
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        /* Position */
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
        /* TexCoords */
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void * )(3 * sizeof(float)));

    /* Unbind objects */
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::Draw(void)
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}