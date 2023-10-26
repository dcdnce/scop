#pragma once

#include <GLFW/glfw3.h>

class Engine
{
	private:

	public:
		Engine(void);
		~Engine(void);
		int init(void);

		int			framebufferWidth;
		int			framebufferHeight;
		GLFWwindow* window;
};

