#pragma once

#include <glad/glad.h>
#include "pfm/pfm.hpp"
#include <map>

#define FACE_TYPE_V_VERTEX_SHADER "./shaders/vertex_V.glsl"
#define FACE_TYPE_V_FRAG_SHADER "./shaders/frag_V.glsl"
#define FACE_TYPE_VVTVN_VERTEX_SHADER "./shaders/vertex_VVTVN.glsl"
#define FACE_TYPE_VVTVN_FRAG_SHADER "./shaders/frag_VVTVN.glsl"
#define FRAME_VERTEX_SHADER "./shaders/vertex_frame.glsl"
#define FRAME_FRAG_SHADER "./shaders/frag_frame.glsl"

class Shader {
    private:
        pfm::mat4 _projMat;
        pfm::mat4 _viewMat;
        pfm::mat4 _modelMat;

    public:
        GLuint		program;
        std::map<std::string, GLuint> textures_map;

        Shader();
        ~Shader();


        void CreateTextureJpg(std::string const & path, int const texture_unit, int const texture_index, std::string const & texture_name);
        void BindTexture(std::string const & texture_name, int const texture_unit);
        void UnbindTexture(int const texture_unit);
        int	loadShaders(std::string const & vertexShaderPath, std::string const & fragmentShaderPath);

        void  setVec3(char * const uniformName, pfm::vec3 & v);
        void  setProjMat(pfm::mat4 const& newProjMat);
        void  SetViewMat(pfm::mat4 const& newViewMat);
        void  setModelMat(pfm::mat4 const& newModelMat);
        pfm::mat4 getProjMat() const;
        pfm::mat4 getViewMat() const;
        pfm::mat4 getModelMat() const;
};