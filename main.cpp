/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: difool <eric.cantelpi@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 11:52:37 by difool            #+#    #+#             */
/*   Updated: 2022/06/14 14:15:57 by difool           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_GL.hpp"
#include "main.hpp"
#include "math.h"

#define	A_RAND	"\e[38;5;222m"
#define A_ESC	"\e[0m"
float	vertices[] {
		// Points				// Color
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f
	};

void	scroll_callback(GLFWwindow *window, double x, double y)
{
	vertices[0] -= y / 10;
	vertices[1] -= y / 10;
	//vertices[2] += y / 10;

	vertices[6] += y / 10;
	vertices[7] -= y / 10;
	//vertices[8] += y / 10;

	//vertices[12] += y / 10;
	vertices[13] += y / 10;
	//vertices[14] += y / 10;
}

void	processInput(GLFWwindow *w)
{
	if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(w, true);
}

int	main(void)
{
	my_GL 	gl;
	GLuint	vbo;
	GLuint	vao;
	//GLuint	ebo;
	
	gl.initWindow();
	// Init Shader
	loadShader(&gl.program);

	glfwSetScrollCallback(gl.window, scroll_callback); 

	// Init VAO & buffers
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Link vbo data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// unbind VAO & buffers - only necessary if multiples entities are used
	// always unbind VAO first
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Main loop
	while (!glfwWindowShouldClose(gl.window))
	{
		processInput(gl.window);

		glClearColor(0.3f, 0.49f, 0.66f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// Draw
		glUseProgram(gl.program);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(gl.window);
        /* Poll for and process events */
        glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vao);
    glDeleteProgram(gl.program);
	return (0);
}
