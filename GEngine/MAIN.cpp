//file is MAIN.cpp
#include "Core.h"

int main(int argc, char *argv[])
{
	//инициаизация и создание окна
	glfw(Width, Height, "BEngin");

	//сборка шейдеров
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//шейдерная программа
	GLuint shaderProgram = glCreateProgram();

	// присоединение шейдеров
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// удаление созданных шейдеров
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};


	GLuint VBO, VAO, EBO;
	// 0. Копируем массив с вершинами в буфер OpenGL
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);


	// 1. Затем установим указатели на вершинные атрибуты
	//упаковка данных 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // регистрация VBO в качестве связвнного буфера вершин

	glBindVertexArray(0); // отмена лишнего

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		//Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//render render;
		//render.clear_color();

		// Draw

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	//// Properly de-allocate all resources once they've outlived their purpose
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	//// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}