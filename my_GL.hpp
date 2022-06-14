#include "main.hpp"

class my_GL
{
	private:

	public:
		my_GL(void);
		~my_GL(void);
		void initWindow(void);

		int			framebufferWidth;
		int			framebufferHeight;
		GLFWwindow* window;
		GLuint		program;
};

