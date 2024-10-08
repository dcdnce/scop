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
		static void	MouseCallback(GLFWwindow* w, double currMouseX, double currMouseY);
		static void	KeyCallback(GLFWwindow *w, int key, int scancode, int action, int mods);
		static void	MouseButtonCallback(GLFWwindow *w, int button, int action, int mods);
		static void ScrollCallback(GLFWwindow* w, double xoffset, double yoffset);
		void	ComputeDeltaTime();

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
		pfm::vec3 object_rotation_vector;
		bool left_mouse_button_pressed;
		bool e_key_pressed;
		bool q_key_pressed;
};

