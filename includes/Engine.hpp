#pragma once

#include "main.hpp"

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
		GLuint		program;
};

