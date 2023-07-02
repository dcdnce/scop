#pragma once

#include "main.hpp"

class Engine
{
	private:

	public:
		Engine(void);
		~Engine(void);
		int initWindow(void);

		int			framebufferWidth;
		int			framebufferHeight;
		GLFWwindow* window;
		GLuint		program;
};

