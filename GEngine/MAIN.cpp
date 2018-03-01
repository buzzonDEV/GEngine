#pragma once
// GLEW
#include <gl\glew.h>

//SOIL
#include <soil.h>

// GLFW
#include <GLFW\glfw3.h>

//GLMatrix для работы с матрицами
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

// Подключение библиотек С
#include <stdlib.h>
#include <stdio.h> 

// Подключение локальных .h
#include "Config.h"
#include "Shader.h"
#include "Core.h"

int main(int argc, char *argv[])
{
	// Инициаизация и создание окна
	Core Core(Width, Height, "BEngin");

	// Создание и развесовка буферов
	Core.create_beffers();
	
	// Подключение шейдеров
	Shader Shader;
	Shader.load_shader("default.vrtx", GL_VERTEX_SHADER);
	Shader.load_shader("default.frgm", GL_FRAGMENT_SHADER);

	// Загрузка терстур
	Shader.load_texture();

	// Запуск шейдерной порграммы
	Shader.use();	

	// Связывание текстур с использованием текстурных блоков
	Shader.bind_texture();

	// Игровой цикл
	while (!glfwWindowShouldClose(Core.main_window))
	{
		// Проверка событий
		glfwPollEvents(); 

		// Очистка экрана
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Трансформация
		glm::mat4 transform;
		transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f)); // Привязка к мыши
		transform = glm::rotate(transform,  20.0f, glm::vec3(1.0f, 0.0f, 1.0f)); // Вращение каждый кадр
		transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 3.0f , glm::vec3(1.0f, 1.0f, 0.0f)); // Вращение каждый кадр

		// Get matrix's uniform location and set matrix
		GLint transformLoc = glGetUniformLocation(Shader.shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		// Обновление изображения
		Core.render();
	}
	return 0;
}