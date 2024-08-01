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

int	main(int ac, char **av)
{
	if (ac != 3) {
		Logger::error(false) << "./scop [.obj path] [.jpg path]" << std::endl;
		exit(EXIT_FAILURE);
	}

	Engine 	scop;

	// Initialization
	try {
		scop.init();
	} catch (std::exception & e) {
		Logger::error(true) << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	// Parse .obj
	ObjParser object;
	try {
		object.parse(av[1]);
	} catch (std::exception & e) {
		Logger::error(true) << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	// Create mesh
	Mesh currMesh = object.buildMesh();

	// Load texture
	try {
		currMesh.attachedShader.CreateTextureJpg(av[2], GL_TEXTURE0, 0, "texture1");
	} catch (std::exception & e) {
		Logger::error(true) << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

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

		// Color rendering uniform
		glUseProgram(currMesh.attachedShader.program);
		glUniform1i(glGetUniformLocation(currMesh.attachedShader.program, "uColorRendering"), scop.uColorRendering);
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
