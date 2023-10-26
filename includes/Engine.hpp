#pragma once

#include <glfw/glfw3.h>

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

