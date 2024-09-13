#include "../includes/Frame.hpp"

Frame::Frame(
        std::vector<pfm::vec3> const& positions,
        pfm::vec3 const& color
	) 
{
    for (size_t i = 0 ; i < 2 ; i++) {
        Vertex vertex;
        vertex.position = positions[i];
        vertex.color = color;
        vertices.push_back(vertex);
    }
	_SetupBuffers();
	_SetupShaders();
}

Frame::~Frame()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Frame::_SetupBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

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

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Frame::_SetupShaders()
{

    attached_shader.loadShaders(FRAME_VERTEX_SHADER, FRAME_FRAG_SHADER);
}

void Frame::Draw()
{
    glUseProgram(attached_shader.program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
    glUseProgram(0);
}