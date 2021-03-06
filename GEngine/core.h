#pragma once

// GLEW
#include <gl\glew.h>

// GLFW
#include <GLFW\glfw3.h>

//connect library C
#include <stdlib.h>
#include <stdio.h> 

//Connect local .h
#include "Config.h"
#include "Shader.h"
#include "Callback.h"

GLFWwindow* window;

void glfw(GLint w, GLint h, const char name[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_DECORATED, GL_FALSE); // без рамок
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	printf("glfwInit - Complete!\n");

	////////////////////////////////////////////////////////////////////
	//создание окна
	window = glfwCreateWindow(w, h, "BEngin", nullptr, nullptr);
	if (window != nullptr)
	{
		glfwMakeContextCurrent(window);
		printf("Create GLFW window - Complete!\n");
	}
	else
	{
		glfwTerminate();
		printf("Create GLFW window - Failed\n");
	}
	////////////////////////////////////////////////////////////////////

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	if (line_mod)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}