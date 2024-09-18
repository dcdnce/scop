#include "Shader.hpp"
#include "Logger.hpp"
#include <iostream>
#include <fstream>
#include "stb/stb_image.h"

static inline int	createShader(GLuint *shaderRef, GLenum type, std::string const & path);
static inline void	LoadTextureJpg(GLuint *texture, std::string const & filename, GLenum activeTexture);

Shader::Shader() {
}


Shader::~Shader()
{
    glDeleteProgram(program);
}


int	Shader::loadShaders(std::string const & vertexShaderPath, std::string const & fragmentShaderPath)
{
	int			ret_value = 1;
	char		infoLog[512];
	GLint		status;
	GLuint		vertexShaderRef;
	GLuint		fragmentShaderRef;

	if (!createShader(&vertexShaderRef, GL_VERTEX_SHADER, vertexShaderPath))
		return (0);
	if (!createShader(&fragmentShaderRef, GL_FRAGMENT_SHADER, fragmentShaderPath))
		return (0);
	program = glCreateProgram();
	glAttachShader(program, vertexShaderRef);
	glAttachShader(program, fragmentShaderRef);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		Logger::error(true) << "Shader class linking error" << std::endl;
		Logger::error(false) << infoLog << std::endl;
		ret_value = 0;
	}
	glDeleteShader(vertexShaderRef);
	glDeleteShader(fragmentShaderRef);
	return (ret_value);
}

static int	createShader(GLuint *shaderRef, GLenum type, std::string const & path)
{
	GLint			status;
	char			infoLog[512];
	std::string		src = "";
	std::string		tmp = "";
	std::ifstream	file;

	// Vertex Shader
	file.open(path);
	if(file.is_open())
		while (std::getline(file, tmp))
			src += tmp + "\n";
	else
	{
		Logger::error(true) << "Shader class couldn't open shader file" << std::endl;
		return (0);	
	}
	*shaderRef = glCreateShader(type);	
	const GLchar	*source = src.c_str();
	glShaderSource(*shaderRef, 1, &source, NULL); 
	glCompileShader(*shaderRef);
	glGetShaderiv(*shaderRef, GL_COMPILE_STATUS, &status);
	file.close();
	if (!status)
	{
		glGetShaderInfoLog(*shaderRef, 512, NULL, infoLog);
		Logger::error(true) << "Shader class compile error" << std::endl;
		Logger::error(false) << infoLog << std::endl;
		return (0);
	}
	return (1);
}

void  Shader::setProjMat(pfm::mat4 const& newProjMat)
{
	_projMat = newProjMat;
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "uProj"), 1, GL_FALSE, &_projMat);
	glUseProgram(0);
}

void  Shader::SetViewMat(pfm::mat4 const& newViewMat)
{
	_viewMat = newViewMat;
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "uView"), 1, GL_FALSE, &_viewMat);
	glUseProgram(0);
}

void  Shader::setModelMat(pfm::mat4 const& newModelMat)
{
	_modelMat = newModelMat;
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "uModel"), 1, GL_FALSE, &_modelMat);
	glUseProgram(0);

}

void	Shader::setVec3(char * const uniformName, pfm::vec3 & v)	
{
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, uniformName), 1, GL_FALSE, &v);
	glUseProgram(0);
}

pfm::mat4	Shader::getProjMat() const
{
	return _projMat;
}

pfm::mat4	Shader::getViewMat() const
{
	return _viewMat;
}

pfm::mat4	Shader::getModelMat() const
{
	return _modelMat;
}

void Shader::CreateTextureJpg(std::string const & path, int const texture_unit, int const texture_index, std::string const & texture_name)
{
    if (path.substr(path.length() - 3, path.length()) != "jpg")
        throw std::runtime_error("CreateTextureJpg :: Texture file extension isn't .jpg");

	glUseProgram(program);
	textures_map[texture_name] = 0;
	LoadTextureJpg(&textures_map[texture_name], path, texture_unit);
	glUniform1i(glGetUniformLocation(program, texture_name.c_str()), texture_index);
	glUseProgram(0);
}

void Shader::BindTexture(std::string const & texture_name, int const texture_unit)
{
	glUseProgram(program);
	glActiveTexture(texture_unit);
	glBindTexture(GL_TEXTURE_2D, textures_map[texture_name]);
	glUseProgram(0);
}

void Shader::UnbindTexture(int const texture_unit)
{
	glActiveTexture(texture_unit);
	glBindTexture(GL_TEXTURE_2D, 0);
}

static inline void	LoadTextureJpg(GLuint *texture, std::string const & filename, GLenum activeTexture)
{
	glGenTextures(1, texture);
	glActiveTexture(activeTexture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// stbi Load
	unsigned char	*data;
	int				width, height, nbrChannels;
	data = stbi_load(filename.c_str(), &width, &height, &nbrChannels, 0);
	if (data) {
		/* Add(!) & Configure texture	*/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		throw std::runtime_error("LoadTextureJpg::stbi_load::couldn't load texture into data\n");
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}
