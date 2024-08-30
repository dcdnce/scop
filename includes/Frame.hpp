#pragma once

#include "pfm/pfm.hpp"
#include "Shader.hpp"
#include "Vertex.hpp"
#include <vector>

class Frame {
	private:
		GLuint VAO, VBO;
		void _SetupBuffers();
		void _SetupShaders();

	public:
		std::vector<Vertex> vertices;
		Shader attached_shader;
		
        Frame(std::vector<pfm::vec3> const& positions);
		~Frame();

		void Draw();
		void SetColor(pfm::vec3 const& new_color);
};