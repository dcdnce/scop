#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Camera.hpp"

class Engine
{
	private:
		void	_initWindow();
		void	_initGlad();
		void	_initEvents();
		void	_initGl();
	public:
		Engine(void);
		~Engine(void);
		void init(void);
		static void	mouseCallback(GLFWwindow* w, double currMouseX, double currMouseY);
		static void	keyCallback(GLFWwindow *w, int key, int scancode, int action, int mods);
		static void	MouseButtonCallback(GLFWwindow *w, int button, int action, int mods);
		void	computeDeltaTime();

		int			framebufferWidth;
		int			framebufferHeight;
		GLFWwindow* window;
		float deltaTime;
		float lastFrame;
		Camera	camera;
		bool	bColorRendering;
		float	uAlpha;
		pfm::vec2 mouse;
		pfm::vec2 previous_mouse;
		pfm::vec2 object_rotation_vector;
		bool is_left_mouse_button_pressed;
};

