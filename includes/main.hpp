#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#define	W_HEIGHT	600	
#define	W_WIDTH		800

#define	A_RAND	"\e[38;5;222m"
#define A_ESC	"\e[0m"

void	mouseCallback(GLFWwindow* window, double currMouseX, double currMouseY);
void	keyCallback(GLFWwindow *w, int key, int scancode, int action, int mods);
