#pragma once

#include <glfw/glfw3.h>
#include "Camera.hpp"

class Engine
{
	private:

	public:
		Engine(void);
		~Engine(void);
		int init(void);
		static void	mouseCallback(GLFWwindow* w, double currMouseX, double currMouseY);
		static void	keyCallback(GLFWwindow *w, int key, int scancode, int action, int mods);
		void	computeDeltaTime();

		int			framebufferWidth;
		int			framebufferHeight;
		GLFWwindow* window;
		float deltaTime;
		float lastFrame;
		Camera	camera;
};

