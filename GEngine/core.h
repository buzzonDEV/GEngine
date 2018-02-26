#pragma once
// GLEW
#include <gl\glew.h>

//SOIL
#include <soil.h>

// GLFW
#include <GLFW\glfw3.h>

//GLMatrix
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

class core
{
public:
	GLFWwindow * window;
	core(GLint w, GLint h, const char name[]);
	~core();

	/*Создает буферы*/
	void create_beffers()
	{
		GLfloat vertices[] = {
			// Positions          // Colors           // Texture Coords
			0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
			0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
		};
		GLuint indices[] = {  // Note that we start from 0!
			0, 1, 3, // First Triangle
			1, 2, 3  // Second Triangle
		};

		// Копируем массив с вершинами в буфер OpenGL
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Упаковка данных 
		// Атрибут с координатами
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Атрибут с цветом
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		// Атрибуты с текстурой
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // Регистрация VBO в качестве связвнного буфера вершин

		glBindVertexArray(0); // Отмена лишнего
	}

	/*Удаляет буверы*/
	void remove_buffers()
	{
		// Properly de-allocate all resources once they've outlived their purpose
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->EBO);
	}

	/*Обновляет изображение*/
	void render()
	{
		// Очистка экрана
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Отрисовка
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Замена экранного буфера
		glfwSwapBuffers(window);
	}

private:
	GLuint VBO, VAO, EBO;
};

core::core(GLint w, GLint h, const char name[])
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

core::~core()
{
	// Удаление отработавших буферов
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}