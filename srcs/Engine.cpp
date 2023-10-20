#include "main.hpp"
#include "Engine.hpp"

#include <iostream>

int Engine::init(void)
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

	this->window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Scop", NULL, NULL);
	if (this->window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
		return (0);
    }

	glfwMakeContextCurrent(this->window);

	// Glad
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

	return (1);
}

Engine::Engine(void) : framebufferWidth(0), framebufferHeight(0), window(NULL)
{
}

Engine::~Engine(void)
{
	if (window)
		glfwDestroyWindow(this->window);
	glfwTerminate();
}
