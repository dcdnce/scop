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
#include "Camera.hpp"

#include <cmath>
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "pfm/pfm.hpp"

void	processInput(GLFWwindow *w);
void 	mouseCallback(GLFWwindow* window, double currMouseX, double currMouseY);
void	loadTexture_jpg(GLuint *texture, const char* filename, GLenum activeTexture);

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

pfm::vec3 cubePositions[] = {
    pfm::vec3( 0.0f,  0.0f,  0.0f), 
    pfm::vec3( 2.0f,  5.0f, -15.0f), 
    pfm::vec3(-1.5f, -2.2f, -2.5f),  
    pfm::vec3(-3.8f, -2.0f, -12.3f),  
    pfm::vec3( 2.4f, -0.4f, -3.5f),  
    pfm::vec3(-1.7f,  3.0f, -7.5f),  
    pfm::vec3( 1.3f, -2.0f, -2.5f),  
    pfm::vec3( 1.5f,  2.0f, -2.5f), 
    pfm::vec3( 1.5f,  0.2f, -1.5f), 
    pfm::vec3(-1.3f,  1.0f, -1.5f)  
};

Camera	camera;

float deltaTime = 0.f;
float lastFrame = 0.f;

int	main(void)
{
	Engine 	gl;
	GLuint	texture1;
	GLuint	vbo;
	GLuint	vao;

	if (!gl.init())
		return (-1);

	// Init Shader
	if (!loadShader(&gl.program))
		return (-1);

	// Enable z-buffer
	glEnable(GL_DEPTH_TEST);

	glUseProgram(gl.program);

	// Load texture
	loadTexture_jpg(&texture1, "container.jpg", GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(gl.program, "texture1"), 0);

	// Projection Matrix
	glm::mat4	proj = glm::perspective(glm::radians(90.f), (float)W_WIDTH/(float)W_HEIGHT, 0.1f, 100.f);
	glUniformMatrix4fv(glGetUniformLocation(gl.program, "proj"), 1, GL_FALSE, glm::value_ptr(proj));
	glUseProgram(0);

	pfm::mat4 p;
	p[0][0]	= proj[0][0];
	p[0][1]	= proj[0][1];
	p[0][2]	= proj[0][2];
	p[0][3]	= proj[0][3];

	p[1][0]	= proj[1][0];
	p[1][1]	= proj[1][1];
	p[1][2]	= proj[1][2];
	p[1][3]	= proj[1][3];

	p[2][0]	= proj[2][0];
	p[2][1]	= proj[2][1];
	p[2][2]	= proj[2][2];
	p[2][3]	= proj[2][3];

	p[3][0]	= proj[3][0];
	p[3][1]	= proj[3][1];
	p[3][2]	= proj[3][2];
	p[3][3]	= proj[3][3];
		
	// Init VAO & buffers
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// Link VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// unbind VAO & buffers
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
		pfm::mat4	currViewMatrix = camera.getViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(gl.program, "view"), 1 , GL_FALSE, &currViewMatrix);
		//std::cout << "[view]\n" << currViewMatrix << std::endl;

		// Draw cubes
		for (size_t i = 0 ; i < 10 ; i++)
		{
			pfm::mat4 model = pfm::translate(pfm::mat4(1.f), cubePositions[i]);
			//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.f * i + 1), glm::vec3(0.5f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(gl.program, "model"), 1, GL_FALSE, &model);
			//std::cout << "[model]\n" << model << std::endl;

			pfm::mat4 mvp_test =  currViewMatrix * model;
			std::cout << mvp_test << std::endl;
			glUniformMatrix4fv(glGetUniformLocation(gl.program, "mvp_test"), 1, GL_FALSE, &mvp_test);

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
	static bool firstMouse = true;
	static float lastMouseX;
	static float lastMouseY;
    float xpos = static_cast<float>(currMouseX);
    float ypos = static_cast<float>(currMouseY);

    if (firstMouse)
    {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastMouseX;
    float yoffset = lastMouseY - ypos; // reversed since y-coordinates go from bottom to top
    lastMouseX = xpos;
    lastMouseY = ypos;

	camera.processMouseMovement(xoffset, yoffset);
}

void	loadTexture_jpg(GLuint *texture, const char* filename, GLenum activeTexture)
{
	glGenTextures(1, texture);
	glActiveTexture(activeTexture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// stbi Load
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
