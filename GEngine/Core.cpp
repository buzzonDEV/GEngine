#pragma once
// GLEW
#include <gl\glew.h>

// GLFW
#include <GLFW\glfw3.h>

// Подключение библиотек С
#include <stdlib.h>
#include <stdio.h> 

// Подключение локальных .h
#include "Config.h"
#include "Core.h"

void key_callback(GLFWwindow* main_window, int key, int scancode, int action, int mode)
{
	/*esc - Закрывает окно*/
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(main_window, GL_TRUE);
};

void cursor_position_callback(GLFWwindow* main_window, double xpos, double ypos)
{
	mouse.x = xpos;
	mouse.y = ypos;
};

void window_size_callback(GLFWwindow* main_window, int width, int height)
{
	glfwGetWindowSize(main_window, &Width, &Height);

	// Define the viewport dimensions
	glfwGetFramebufferSize(main_window, &Width, &Height);
	glViewport(0, 0, Width, Height);
};

Core::Core(GLint w, GLint h, const char name[])
{
	glfwInit(); // Инициализация окна
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_DECORATED, GL_FALSE); // Режим без рамок
	glfwWindowHint(GLFW_RESIZABLE, resizable);  // Отвечает за возможность изменения размера окна

	printf("glfwInit - Complete!\n");

	////////////////////////////////////////////////////////////////////
	//создание окна
	main_window = glfwCreateWindow(w, h, "BEngin", nullptr, nullptr);
	if (main_window != nullptr)
	{
		glfwMakeContextCurrent(main_window);
		printf("Create GLFW window - Complete!\n");
	}
	else
	{
		glfwTerminate();
		printf("Create GLFW window - Failed\n");
	}
	////////////////////////////////////////////////////////////////////

	// Функции возвращения
	glfwSetKeyCallback(main_window, key_callback);
	glfwSetWindowSizeCallback(main_window, window_size_callback);
	glfwSetCursorPosCallback(main_window, cursor_position_callback);

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
};

Core::~Core()
{
	// Удаление отработавших буферов
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// Переход на терминальный режим
	glfwTerminate();
}

/*Создает буферы*/
void Core::create_beffers()
{
	//массив координат объекта
	GLfloat vertices[] = {
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

	// Копируем массив с вершинами в буфер OpenGL
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Упаковка данных 
	// Атрибут с координатами
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Атрибуты с текстурой
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Отмена лишнего
};

/*Удаляет буверы*/
void  Core::remove_buffers()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}

/*Обновляет изображение*/
void Core::render()
{
	// Отрисовка
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Замена экранного буфера
	glfwSwapBuffers(main_window);
}
