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
#include "Frame.hpp"
#include "pfm/pfm.hpp"
#include <cmath>
#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

inline static void ObjectRotationCallback(Engine & scop, Mesh & main_mesh, Frame & frame_y,Frame & frame_x, Frame & frame_z);

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

	// Create meshes
	Mesh main_mesh = object.buildMesh();
	float const max_frame_length = 1.5f * std::max(object.BoundingBox.max_x, std::max(object.BoundingBox.max_y, object.BoundingBox.max_z));
	Frame frame_y({pfm::vec3(0.f), pfm::vec3(0.f, max_frame_length, 0.f)}, pfm::vec3(1.f, 0.f, 0.f));
	Frame frame_x({pfm::vec3(0.f), pfm::vec3(max_frame_length, 0.f, 0.f)}, pfm::vec3(0.f, 0.f, 1.f));
	Frame frame_z({pfm::vec3(0.f), pfm::vec3(0.f, 0.f, max_frame_length)}, pfm::vec3(0.f, 1.f, 0.f));

	// Texture - create and load
	try {
		main_mesh.attached_shader.CreateTextureJpg(av[2], GL_TEXTURE0, 0, "texture1");
	} catch (std::exception & e) {
		Logger::error(true) << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	// Camera position
	scop.camera.position.z = 2.f * std::max(std::max(object.BoundingBox.max_x, object.BoundingBox.max_y), object.BoundingBox.max_z);
	// Projection Matrix
	pfm::mat4 projection_matrix = pfm::perspective(pfm::radians(90.f), (float)W_WIDTH/(float)W_HEIGHT, 0.1f, 100.f);
	main_mesh.attached_shader.setProjMat(projection_matrix);
	frame_y.attached_shader.setProjMat(projection_matrix);
	frame_x.attached_shader.setProjMat(projection_matrix);
	frame_z.attached_shader.setProjMat(projection_matrix);
	// Objects world position
	main_mesh.attached_shader.setModelMat(pfm::translate(pfm::mat4(1.f), pfm::vec3(0.f, 0.f, 0.f)));
	frame_y.attached_shader.setModelMat(pfm::translate(pfm::mat4(1.f), pfm::vec3(0.f, 0.f, 0.f)));
	frame_x.attached_shader.setModelMat(pfm::translate(pfm::mat4(1.f), pfm::vec3(0.f, 0.f, 0.f)));
	frame_z.attached_shader.setModelMat(pfm::translate(pfm::mat4(1.f), pfm::vec3(0.f, 0.f, 0.f)));

	// Main loop
	while (!glfwWindowShouldClose(scop.window))
	{
		scop.ComputeDeltaTime();

		glClearColor(0.3f, 0.49f, 0.66f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Bind texture
		main_mesh.attached_shader.BindTexture("texture1", GL_TEXTURE0);

		// Update viewMatrix
		main_mesh.attached_shader.SetViewMat(scop.camera.getViewMatrix());
		frame_y.attached_shader.SetViewMat(scop.camera.getViewMatrix());
		frame_x.attached_shader.SetViewMat(scop.camera.getViewMatrix());
		frame_z.attached_shader.SetViewMat(scop.camera.getViewMatrix());

		// Draw
		// Update model matrix
		if (scop.left_mouse_button_pressed || scop.e_key_pressed || scop.q_key_pressed)
			ObjectRotationCallback(scop, main_mesh, frame_y, frame_x, frame_z);

		// Color rendering alpha uniform
		glUseProgram(main_mesh.attached_shader.program);
		scop.uAlpha = std::min(std::max(scop.uAlpha + ((scop.bColorRendering) ? 0.01 : -0.01), 0.0), 1.0);
		glUniform1f(glGetUniformLocation(main_mesh.attached_shader.program, "uAlpha"), scop.uAlpha);
		glUseProgram(0);

		main_mesh.Draw();
		frame_y.Draw();
		frame_x.Draw();
		frame_z.Draw();

		// Unbind
		main_mesh.attached_shader.UnbindTexture(GL_TEXTURE0);

        glfwSwapBuffers(scop.window);
        glfwPollEvents();
	}

	return(EXIT_SUCCESS);
}


inline static void ObjectRotationCallback(Engine & scop, Mesh & main_mesh, Frame & frame_y,Frame & frame_x, Frame & frame_z)
{
	static double const res_magnitude = pfm::magnitude(pfm::vec2(W_WIDTH, W_HEIGHT));

	if (scop.left_mouse_button_pressed) {
		scop.object_rotation_vector = pfm::vec3(scop.mouse.x - scop.previous_mouse.x, scop.previous_mouse.y - scop.mouse.y, 0.f);
	}
	if (scop.e_key_pressed) {
		scop.object_rotation_vector = pfm::vec3(0.f, 0.f, 10.0f);
	}
	if (scop.q_key_pressed) {
		scop.object_rotation_vector = pfm::vec3(0.f, 0.f, -10.0f);
	}

	pfm::vec3 n = pfm::normalize(scop.object_rotation_vector);
	float angle = (pfm::magnitude(scop.object_rotation_vector) - 1) / res_magnitude * 360.f;

	main_mesh.attached_shader.setModelMat(pfm::rotate(
		main_mesh.attached_shader.getModelMat(),
		pfm::radians(angle),
		n.y * scop.camera.right + n.x*scop.camera.up + n.z*scop.camera.front)
	);

	frame_y.attached_shader.setModelMat(pfm::rotate(
		frame_y.attached_shader.getModelMat(),
		pfm::radians(angle),
		n.y * scop.camera.right + n.x*scop.camera.up + n.z*scop.camera.front)
	);

	frame_x.attached_shader.setModelMat(pfm::rotate(
		frame_x.attached_shader.getModelMat(),
		pfm::radians(angle),
		n.y * scop.camera.right + n.x*scop.camera.up + n.z*scop.camera.front)
	);

	frame_z.attached_shader.setModelMat(pfm::rotate(
		frame_z.attached_shader.getModelMat(),
		pfm::radians(angle),
		n.y * scop.camera.right + n.x*scop.camera.up + n.z*scop.camera.front)
	);
}
