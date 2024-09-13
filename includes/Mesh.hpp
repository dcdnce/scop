#pragma once

#include "pfm/pfm.hpp"
#include "Shader.hpp"
#include "Vertex.hpp"
#include <string>
#include <vector>

struct Texture {
    unsigned int    id;
    std::string type;
};

class Mesh {
    private:
        unsigned int VAO, VBO, EBO;
        void _setupColors(void);
        void _setupBuffers(void);
        void _setupShaders(void);

    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        int const facesType;
        Shader  attached_shader;  

        Mesh(std::vector<Vertex> const& vertices, std::vector<unsigned int> const& indices, std::vector<Texture> const& textures, int const facesType);
        ~Mesh();

        void    draw(void);
        void    toggleColorShading();
};