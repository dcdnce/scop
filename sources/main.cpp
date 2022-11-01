/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 11:52:37 by difool            #+#    #+#             */
/*   Updated: 2022/11/01 17:54:31 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_GL.hpp"
#include "main.hpp"
#include "math.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define	A_RAND	"\e[38;5;222m"
#define A_ESC	"\e[0m"

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
};

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
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

void	loadTexture(GLuint *texture) {
	/* Gen texture 
	 * & configure wrapping/filtering	*/
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* stbi load */
	unsigned char	*data;
	int				width, height, nbrChannels;
	data = stbi_load("container.jpg", &width, &height, &nbrChannels, 0);
	if (data) {
		/* Add(!) & Configure texture	*/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "main.cpp::stbi_load::couldn't load texture into data\n" << std::endl;
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int	main(void)
{
	my_GL 	gl;
	GLuint	texture;
	GLuint	vbo;
	GLuint	vao;
	GLuint	ebo;
	
	gl.initWindow();
	// Load texture
	loadTexture(&texture);
	// Init Shader
	loadShader(&gl.program);
	
	glfwSetScrollCallback(gl.window, scroll_callback); 

	// Init VAO & buffers
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Link vbo data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	// unbind VAO & buffers
	// - only necessary if multiples entities are used
	// - always unbind VAO first
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Main loop
	while (!glfwWindowShouldClose(gl.window))
	{
		processInput(gl.window);

		glClearColor(0.3f, 0.49f, 0.66f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

		/* Draw	*/
		glUseProgram(gl.program);
		// Rebind vao & texture
		glBindVertexArray(vao);
		//glBindTexture(GL_TEXTURE_2D, texture);
		// Draw data
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	

		// Unbind - only if multiple entities are used
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(gl.window);
        /* Poll for and process events */
        glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(gl.program);
	return (0);
}
