#include "../includes/Mesh.hpp"
#include "../includes/glad/glad.h"

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