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

#include "glad/glad.h"
#include "main.hpp"
#include "Engine.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "ObjParser.hpp"
#include "Logger.hpp"
#include "pfm/pfm.hpp"
#include <cmath>
#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

int	main(void)
{
	Engine 	scop;
	GLuint	texture1;

	// Initialization
	try {
		scop.init();
	} catch (std::exception & e) {
		Logger::error(true) << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	// Create mesh
	ObjParser object;
	try {
		object.parse("./resources/obj/teapot.obj");
	} catch (std::exception & e) {
		Logger::error(true) << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	Mesh currMesh = object.buildMesh();

	
	// Load texture
	currMesh.attachedShader.CreateTextureJpg("./resources/textures/container.jpg", GL_TEXTURE0, 0, "texture1");

	// Projection Matrix
	currMesh.attachedShader.setProjMat(
		pfm::perspective(pfm::radians(90.f), (float)W_WIDTH/(float)W_HEIGHT, 0.1f, 100.f)
	);

	// Main loop
	while (!glfwWindowShouldClose(scop.window))
	{
		scop.computeDeltaTime();

		glClearColor(0.3f, 0.49f, 0.66f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Bind texture
		currMesh.attachedShader.BindTexture("texture1", GL_TEXTURE0);

		// Update viewMatrix
		currMesh.attachedShader.setViewMat(scop.camera.getViewMatrix());

		// Draw
		// Update model matrix
		currMesh.attachedShader.setModelMat(pfm::translate(pfm::mat4(1.f), pfm::vec3(0.f, 0.f, 0.f)));
		currMesh.attachedShader.setModelMat(pfm::rotate(
			currMesh.attachedShader.getModelMat(),
			(float)glfwGetTime() * pfm::radians(20.f), 
			pfm::vec3(0.5f, 1.0f, 0.0f))
		);

		glUseProgram(currMesh.attachedShader.program);
		glUniform1i(glGetUniformLocation(currMesh.attachedShader.program, "uGreyShading"), scop.greyShading);
		glUseProgram(0);

		currMesh.draw();

		// Unbind
		currMesh.attachedShader.UnbindTexture(GL_TEXTURE0);

        glfwSwapBuffers(scop.window);
        glfwPollEvents();
	}

	// todo // delete texture
	return (0);
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
