/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 11:52:37 by difool            #+#    #+#             */
/*   Updated: 2023/07/02 15:09:00by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Engine.hpp"
#include "math.h"
#include "Camera.hpp"

#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define	A_RAND	"\e[38;5;222m"
#define A_ESC	"\e[0m"

void	processInput(GLFWwindow *w);
void mouseCallback(GLFWwindow* window, double currMouseX, double currMouseY);
void	loadTexture_jpg(GLuint *texture, const char* filename);

float vertices[] = {
	// positions		  //texture coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};

Camera	camera;

float deltaTime = 0.f;
float lastFrame = 0.f;

bool	firstCursor = true;
float	lastMouseX = 0.f;
float	lastMouseY = 0.f;

int	main(void)
{
	Engine 	gl;
	GLuint	texture1;
	GLuint	vbo;
	GLuint	vao;

	if (!gl.initWindow())
		return (-1);

	// Init Shader
	if (!loadShader(&gl.program))
		return (-1);

	// Enable z-buffer
	glEnable(GL_DEPTH_TEST);

	glUseProgram(gl.program);

	// Load texture
	loadTexture_jpg(&texture1, "container.jpg");
	glUniform1i(glGetUniformLocation(gl.program, "texture1"), 0);

	// Projection Matrix
	glm::mat4	proj = glm::perspective(glm::radians(90.f), (float)W_WIDTH/(float)W_HEIGHT, 0.1f, 100.f);
	glUniformMatrix4fv(glGetUniformLocation(gl.program, "proj"), 1, GL_FALSE, glm::value_ptr(proj));
	glUseProgram(0);
		
	// Init VAO & buffers
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Link vbo data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// unbind VAO & buffers
	// - only necessary if multiples entities are used
	// - always unbind VAO first
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// Main loop
	while (!glfwWindowShouldClose(gl.window))
	{
		float	currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(gl.window);
		glClearColor(0.3f, 0.49f, 0.66f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Bind vao, bind texture, use program
		glBindVertexArray(vao);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glUseProgram(gl.program);

		// Update viewMatrix uniform
		glm::mat4	currViewMatrix = camera.getViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(gl.program, "view"), 1 , GL_FALSE, glm::value_ptr(currViewMatrix));

		// Draw cubes
		for (size_t i = 0 ; i < 10 ; i++)
		{
			glm::mat4 model = glm::translate(glm::mat4(1.f), cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.f * i + 1), glm::vec3(0.5f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(gl.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Unbind
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

        glfwSwapBuffers(gl.window);
        glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(gl.program);
	return (0);
}

void	processInput(GLFWwindow *w)
{
	if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(w, true);
	if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
		camera.processKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
		camera.processKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
		camera.processKeyboard(LEFT, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
		camera.processKeyboard(RIGHT, deltaTime);
}

void mouseCallback(GLFWwindow* window, double currMouseX, double currMouseY)
{
    float xpos = static_cast<float>(currMouseX);
    float ypos = static_cast<float>(currMouseY);

    if (firstCursor)
    {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstCursor = false;
    }

    float xoffset = xpos - lastMouseX;
    float yoffset = lastMouseY - ypos; // reversed since y-coordinates go from bottom to top
    lastMouseX = xpos;
    lastMouseY = ypos;

	camera.processMouseMovement(xoffset, yoffset);
}

void	loadTexture_jpg(GLuint *texture, const char* filename) {
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* stbi load */
	unsigned char	*data;
	int				width, height, nbrChannels;
	data = stbi_load(filename, &width, &height, &nbrChannels, 0);
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