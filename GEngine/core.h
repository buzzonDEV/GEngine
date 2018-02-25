#pragma once

// GLEW
#include <gl\glew.h>

//SOIL
#include <soil.h>

// GLFW
#include <GLFW\glfw3.h>


//GLM
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

// Подключение библиотек С
#include <stdlib.h>
#include <stdio.h> 
#include <string>
#include <fstream>
#include <sstream>

// Подключение локальных .h
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
	//glfwWindowHint(GLFW_DECORATED, GL_FALSE); // Режим без рамок
	glfwWindowHint(GLFW_RESIZABLE, resizable);  // Отвечает за возможность изменения размера окна

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

	if (polygon_mod)
	{
		// Отвечает за режим линейной отрисовки полигонов. т.е рисует только ребра
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else 
	{
		// Отвечает за режим полной отрисовки полигонов. т.е рисует полигон полностью с двух сторон
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}