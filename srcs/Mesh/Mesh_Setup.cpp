#include "Mesh.hpp"
#include "FacesType.hpp"

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
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void * )(offsetof(Vertex, texCoords)));

    /* Unbind objects */
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::_setupShaders()
{
    if (facesType == FACE_TYPE_V)
        attachedShader.loadShaders(FACE_TYPE_V_VERTEX_SHADER, FACE_TYPE_V_FRAG_SHADER);
    else if (facesType == FACE_TYPE_VVTVN)
        attachedShader.loadShaders(FACE_TYPE_VVTVN_VERTEX_SHADER, FACE_TYPE_VVTVN_FRAG_SHADER);
}