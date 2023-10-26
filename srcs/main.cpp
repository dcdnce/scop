/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 11:52:37 by difool            #+#    #+#             */
/*   Updated: 2023/07/02 15:09:00 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Engine.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "ObjParser.hpp"
#include "Logger.hpp"

#include <cmath>
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "pfm/pfm.hpp"

void	processInput(GLFWwindow *w);
void 	mouseCallback(GLFWwindow* window, double currMouseX, double currMouseY);
void	loadTexture_jpg(GLuint *texture, const char* filename, GLenum activeTexture);

pfm::vec3 cubePositions[] = {
    pfm::vec3( 0.0f,  0.0f,  0.0f), 
    pfm::vec3( 4.0f,  10.0f, -30.0f), 
    pfm::vec3(-3.f, -4.f, -5.f),  
    pfm::vec3(-8.f, -4.0f, -24.f),  
    pfm::vec3( 5.f, -1.f, -7.f),  
    pfm::vec3(-4.f,  6.f, -15.f),  
    pfm::vec3( 2.f, -4.0f, -5.f),  
    pfm::vec3( 3.f,  4.0f, -5.f), 
    pfm::vec3( 3.f,  0.5f, -3.f), 
    pfm::vec3(-2.3f,  2.0f, -3.f)  
};

Camera	camera;

float deltaTime = 0.f;
float lastFrame = 0.f;

int	main(void)
{
	Engine 	scop;
	GLuint	texture1;

	if (!scop.init())
		return (-1);

	// Create current mesh
	ObjParser object;
	try {
		object.parse("./resources/teapot.obj");
	} catch (std::exception & e) {
		Logger::error(true) << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	Mesh currMesh = object.buildMesh();

	// Enable z-buffer
	glEnable(GL_DEPTH_TEST);
	
	// Load texture
	glUseProgram(currMesh.attachedShader.program);
	loadTexture_jpg(&texture1, "container.jpg", GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(currMesh.attachedShader.program, "texture1"), 0);
	glUseProgram(0);

	// Projection Matrix
	currMesh.attachedShader.setProjMat(
		pfm::perspective(pfm::radians(90.f), (float)W_WIDTH/(float)W_HEIGHT, 0.1f, 100.f)
	);
		
	// Main loop
	while (!glfwWindowShouldClose(scop.window))
	{
		float	currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(scop.window);
		glClearColor(0.3f, 0.49f, 0.66f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Bind texture
		glUseProgram(currMesh.attachedShader.program);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUseProgram(0);

		// Update viewMatrix
		currMesh.attachedShader.setViewMat(camera.getViewMatrix());

		// draw cubes
		for (size_t i = 0 ; i < 1 ; i++)
		{
			// Update modelmatrix
			currMesh.attachedShader.setModelMat(pfm::translate(pfm::mat4(1.f), cubePositions[i]));
			currMesh.attachedShader.setModelMat(pfm::rotate(
				currMesh.attachedShader.getModelMat(),
				(float)glfwGetTime() * pfm::radians(20.f * i + 1), 
				pfm::vec3(0.5f, 1.0f, 0.0f))
			);
			currMesh.draw();
		}

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

        glfwSwapBuffers(scop.window);
        glfwPollEvents();
	}

	// todo // delete texture
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
