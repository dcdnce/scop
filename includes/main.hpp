#ifndef MAIN_HPP
#define MAIN_HPP

#ifdef __linux__
	#include <GL/glew.h>
	#include <GL/glut.h>
	#include <GLFW/glfw3.h>
#elif defined __APPLE__
	#include <glad/glad.h>
	#include <GLFW/glfw3.h>
#endif


#define	W_HEIGHT	600	
#define	W_WIDTH		800 

// shader.cpp
int		loadShader(GLuint *program);
// main.cpp
void	mouseCallback(GLFWwindow* window, double currMouseX, double currMouseY);

#endif
