#include "main.hpp"
#include "Engine.hpp"

#include <iostream>

int Engine::initWindow(void)
{
	//Init GLFW
	glfwInit();

	//Create a window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	this->window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "OpenGL Tutorial", NULL, NULL);
	if (this->window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
		return (0);
    }

	glfwMakeContextCurrent(this->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return (0);
	}

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glViewport(0, 0, this->framebufferWidth, this->framebufferHeight);

	// Mouse setup
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return (0);
	}

	return (1);
}

Engine::Engine(void) : framebufferWidth(0), framebufferHeight(0), window(NULL), program(0)
{
	std::cout << "Engine::Constructor!" << std::endl;
}

Engine::~Engine(void)
{
	if (program)
		glDeleteProgram(program);
	if (window)
		glfwDestroyWindow(this->window);
	glfwTerminate();
	std::cout << "Engine::Destructor!" << std::endl;
}
