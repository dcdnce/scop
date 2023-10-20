#pragma once

#include <glad/glad.h>

#define FACE_TYPE_V_VERTEX_SHADER "./shaders/vertex_V.glsl"
#define FACE_TYPE_V_FRAG_SHADER "./shaders/frag_V.glsl"
#define FACE_TYPE_VVTVN_VERTEX_SHADER "./shaders/vertex_VVTVN.glsl"
#define FACE_TYPE_VVTVN_FRAG_SHADER "./shaders/frag_VVTVN.glsl"

class Shader {
    private:

    public:
		GLuint		program;

        Shader();
        ~Shader();

        int	loadShaders(char * const vertexShaderPath, char * const fragmentShaderPath);
};