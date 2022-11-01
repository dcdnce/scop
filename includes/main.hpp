#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <fstream>
#include <string>

#ifdef __linux__
	#include <GL/glew.h>
	#include <GL/glut.h>
	#include <GLFW/glfw3.h>
#elif defined __APPLE__
	#include <glad/glad.h>
	#include <GLFW/glfw3.h>
#endif

#define	W_HEIGHT	480
#define	W_WIDTH		640 


/* shader.cpp	*/
int		loadShader(GLuint *program);
#endif
