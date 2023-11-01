#include "main.hpp"
#include "Engine.hpp"
#include "Logger.hpp"
#include <iostream>

int Engine::init(void)
{
	deltaTime = 0.f;
	lastFrame = 0.f;

	//Init glfw
	glfwInit();

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
    {
        Logger::error(true) << "Failed to create glfw window" << std::endl;
		return (0);
    }

	glfwMakeContextCurrent(window);

	// Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Logger::error(true) << "Failed to initialize GLAD" << std::endl;
		return (0);
	}

	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glViewport(0, 0, framebufferWidth, framebufferHeight);

	// Inputs
	glfwSetWindowUserPointer(window, this);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, Engine::mouseCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	glfwSetKeyCallback(window, Engine::keyCallback);

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

void	Engine::keyCallback(GLFWwindow *w, int key, int scancode, int action, int mods)
{
	Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(w));
	static int polygonMode[3] = {GL_FILL, GL_LINE, GL_POINT};
	static size_t i = 0;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(w, true);

	if (key == GLFW_KEY_W && action == GLFW_REPEAT | GLFW_PRESS)
		engine->camera.processKeyboard(FORWARD, engine->deltaTime);
	if (key == GLFW_KEY_S && action == GLFW_REPEAT | GLFW_PRESS)
		engine->camera.processKeyboard(BACKWARD, engine->deltaTime);
	if (key == GLFW_KEY_A && action == GLFW_REPEAT | GLFW_PRESS)
		engine->camera.processKeyboard(LEFT, engine->deltaTime);
	if (key == GLFW_KEY_D && action == GLFW_REPEAT | GLFW_PRESS)
		engine->camera.processKeyboard(RIGHT, engine->deltaTime);

	// if (key == GLFW_KEY_C && action == GLFW_PRESS)
	// 	greyShading = !greyShading;

	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		i = (i + 1) % 3;
		glPolygonMode(GL_FRONT_AND_BACK, polygonMode[i]);
	}
}

void Engine::mouseCallback(GLFWwindow* w, double currMouseX, double currMouseY)
{
	Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(w));
	static bool firstMouse = true;
	static float lastMouseX;
	static float lastMouseY;
    float xpos = static_cast<float>(currMouseX);
    float ypos = static_cast<float>(currMouseY);

    if (firstMouse)
    {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastMouseX;
    float yoffset = lastMouseY - ypos; // reversed since y-coordinates go from bottom to top
    lastMouseX = xpos;
    lastMouseY = ypos;

	engine->camera.processMouseMovement(xoffset, yoffset);
}

void Engine::computeDeltaTime()
{
	float	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}
