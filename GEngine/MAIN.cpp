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


class Core
{
public:
	/*окно*/
	GLFWwindow * window;
	/*Конструктор создани окна. Получаемые параметры w - стартовая ширина окна
	h - стартоваяя высота окна
	name - название процесса*/
	Core(GLint w, GLint h, const char name[]);

	/*Удаляет отработавшие буферы, переводит в режим терминала*/
	~Core();

	/*Создает буферы*/
	void create_beffers()
	{
		//массив координат объекта
		GLfloat vertices[] = {
			// Позиции			// Цвета			 // координаты текстур
			0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // верх право
			0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // низ право
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // низ лево
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // верх лево
		};
		GLuint indices[] = {  //связи
			0, 1, 3, // 1
			1, 2, 3  // 2
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
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->EBO);
	}

	/*Обновляет изображение*/
	void render()
	{
		// Отрисовка
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Замена экранного буфера
		glfwSwapBuffers(window);
	}

private:
	GLuint  VBO, // вершинный буфер
		VAO, // вершинный буфер
		EBO; //	объектный буфер
};

Core::Core(GLint w, GLint h, const char name[])
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

Core::~Core()
{
	// Удаление отработавших буферов
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// Переход на терминальный режим
	glfwTerminate();
}

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
	while (!glfwWindowShouldClose(Core.window))
	{
		// Проверка событий
		glfwPollEvents(); 

		// Очистка экрана
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Трансформация
		glm::mat4 transform;
		transform = glm::translate(transform, glm::vec3(-1+mouse.x/Width*2, -1*(-1 + mouse.y / Height * 2), 0.0f)); // Привязка к мыши
		transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 1.0f , glm::vec3(1.0f, 1.0f, 1.0f)); // Вращение каждый кадр

		// Get matrix's uniform location and set matrix
		GLint transformLoc = glGetUniformLocation(Shader.shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		// Обновление изображения
		Core.render();
	}
	return 0;
}