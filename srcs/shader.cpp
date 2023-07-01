#include "main.hpp"

static int	createShader(GLuint *shaderRef, GLenum type, const char *path)
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
		std::cout << "ERROR::main.cpp::createShader::could_not_open_file" << std::endl;
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
		std::cout << "ERROR::main.cpp::createShader::compile_error" << std::endl;
		std::cout << infoLog << std::endl;
		return (0);
	}
	return (1);
}

int	loadShader(GLuint *program)
{
	int			ret_value = 1;
	char		infoLog[512];
	GLint		status;
	GLuint		vertexShaderRef;
	GLuint		fragmentShaderRef;

	if (!createShader(&vertexShaderRef, GL_VERTEX_SHADER, "shaders/vertex_core.glsl"))
		return (0);
	if (!createShader(&fragmentShaderRef, GL_FRAGMENT_SHADER, "shaders/fragment_core.glsl"))
		return (0);
	*program = glCreateProgram();
	glAttachShader(*program, vertexShaderRef);
	glAttachShader(*program, fragmentShaderRef);
	glLinkProgram(*program);
	glGetProgramiv(*program, GL_LINK_STATUS, &status);
	if (!status)
	{
		glGetProgramInfoLog(*program, 512, NULL, infoLog);
		std::cout << "ERROR::main.cpp::loadShader::linking_error" << std::endl;
		std::cout << infoLog << std::endl;
		ret_value = 0;
	}
	glDeleteShader(vertexShaderRef);
	glDeleteShader(fragmentShaderRef);
	return (ret_value);
}
