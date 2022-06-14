#include "main.hpp"
#include "my_GL.hpp"

void my_GL::initWindow(void)
{
	//Init GLFW
	glfwInit();
	//Create a window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	this->window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "OpenGL Tutorial", NULL, NULL);
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glViewport(0, 0, this->framebufferWidth, this->framebufferHeight);
	glfwMakeContextCurrent(this->window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << printf("error::main.cpp::glewInit()") << std::endl;
		return(glfwTerminate());
	}
}

my_GL::my_GL(void) : framebufferWidth(0), framebufferHeight(0), window(NULL), program(0)
{
	std::cout << "my_GL::Constructor!" << std::endl;
}

my_GL::~my_GL(void)
{
	if (program)
		glDeleteProgram(program);
	if (window)
		glfwDestroyWindow(this->window);
	glfwTerminate();
	std::cout << "my_GL::Destructor!" << std::endl;
}

