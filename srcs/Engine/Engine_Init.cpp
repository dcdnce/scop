#include <iostream>
#include "main.hpp"
#include "Engine.hpp"
#include "Logger.hpp"

void Engine::init(void)
{
	glfwInit();
	_initWindow();
	_initGlad();
	_initEvents();
	_initGl();
}

void	Engine::_initWindow()
{
	//Create a window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Scop", NULL, NULL);
	if (window == NULL)
		throw std::runtime_error("Failed to create glfw window");

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
}

void	Engine::_initEvents()
{
	glfwSetWindowUserPointer(window, this);

	glfwSetCursorPosCallback(window, Engine::MouseCallback);
	glfwSetMouseButtonCallback(window, Engine::MouseButtonCallback);
	glfwSetKeyCallback(window, Engine::KeyCallback);
	glfwSetScrollCallback(window, Engine::ScrollCallback);
}

void	Engine::_initGl()
{
	glViewport(0, 0, framebufferWidth, framebufferHeight);
	glEnable(GL_DEPTH_TEST);
	glPointSize(20.f);
}

void	Engine::_initGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("Failed to initialize glad");
}