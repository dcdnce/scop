#pragma once

#include "./pfm/pfm.hpp"

#include <string>
#include <vector>

struct Vertex {
    pfm::vec3 position;
    pfm::vec3 normal;
    pfm::vec2 texCoords;
};

struct Texture {
    unsigned int    id;
    std::string type;
};

class Mesh {
    private:
        unsigned int VAO, VBO, EBO;
        void Setup(void);

    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        Mesh(std::vector<Vertex> const& vertices, std::vector<unsigned int> const& indices, std::vector<Texture> const& textures);

        void    Draw(void);
};