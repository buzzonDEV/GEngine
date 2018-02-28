#include "Core.h"

int main(int argc, char *argv[])
{
	// Инициаизация и создание окна
	core core(Width, Height, "BEngin");

	// Создание и развесовка буферов
	core.create_beffers();
	
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
	while (!glfwWindowShouldClose(core.window))
	{
		// Проверка событий
		glfwPollEvents(); 

		// Очистка экрана
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Create transformations
		glm::mat4 transform;
		transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 1.0f , glm::vec3(0.0f, 0.0f, 1.0f));

		// Get matrix's uniform location and set matrix
		GLint transformLoc = glGetUniformLocation(Shader.shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		// Обновление изображения
		core.render();
	}
	return 0;
}