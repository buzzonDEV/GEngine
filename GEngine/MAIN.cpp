//file is MAIN.cpp
#include "Core.h"

int main(int argc, char *argv[])
{
	//инициаизация и создание окна
	glfw(Width, Height, "BEngin");
	
	//Подключение шейдеров;
	GLuint shaderProgram = glCreateProgram();
	load_shader(&shaderProgram, "default.vrtx", GL_VERTEX_SHADER);
	load_shader(&shaderProgram, "default.frgm", GL_FRAGMENT_SHADER);

	GLfloat vertices[] = {
		// Позиции         // Цвета
		 0.5f, -0.5f, 0.0f,	 0.0f, 0.0f, 1.0f,   // Нижний правый угол
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // Нижний левый угол
		 0.0f,  0.5f, 0.0f,	 1.0f, 0.0f, 0.0f    // Верхний угол
	};
	GLuint indices[] = {  // Помните, что мы начинаем с 0!
		0, 1, 3,   // Первый треугольник

	};


	GLuint VBO, VAO, EBO;
	// 0. Копируем массив с вершинами в буфер OpenGL
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	//упаковка данных 
	// Атрибут с координатами
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Атрибут с цветом
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // регистрация VBO в качестве связвнного буфера вершин

	glBindVertexArray(0); // отмена лишнего

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		//Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw our first triangle
		GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");

		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}