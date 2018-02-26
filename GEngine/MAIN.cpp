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

		// Обновление изображения
		core.render();
	}
	return 0;
}